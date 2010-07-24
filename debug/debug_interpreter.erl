-module(debug_interpreter).

-export([start/0, start_loop/0]).

-define(DEBUG(Text,Parameters),  io:format( [0] ++ "---" ++ Text ++ [0], Parameters )).
-define(OUTPUT(Text, Parameters), io:format([0] ++ Text ++ [0] , Parameters )).


start() ->
  application:start(sasl),
  ?DEBUG("starting debug system on: ~w",[self()]),
  ?DEBUG("erlang:register: [~w]", [erlang:register(internal_meta, spawn(fun() -> start_loop() end))]),
  ?DEBUG("erlang:register: [~w]", [erlang:register(input_reader_proc, spawn(fun() -> input_reader_sync() end))]).

input_reader_sync() ->
  receive
    started ->
      input_reader()
  end.

input_reader() ->
  case io:read("") of
    eof ->
      ok;
    { error, Reason } ->
      ?DEBUG("ERROR INPUT ~w", [Reason]);
    { ok, Term } ->
      ?DEBUG("Readed term ~w",[Term]),
      internal_meta ! { user_input, Term }
  end,  
  input_reader().

start_loop() ->
  ?DEBUG("Starting debug loop", []),
  ?DEBUG("Starting int: [~w]", [int:start()]),
  ?DEBUG("Subscribe: ~w", [int:subscribe()]),
  %?DEBUG("Stack trace: ~w", [int:stack_trace(all)]),  
  input_reader_proc ! started,
  loop(). 

process_user_input({ interpret , Module }) ->
  ?DEBUG("Trying to interpret module [~w]", [Module]),
  case int:i(Module) of
    { module, M } ->
      ?OUTPUT("interpret|ok|~w", [M]);
    error ->
      ?OUTPUT("interpret|error|~w }", [Module])
  end;

process_user_input({launch, { Module, Function, Parameters }}) ->
  ?DEBUG("Trying launch function [~w] from module [~w] and parameters ~w", [Module, Function, Parameters] ),
  ?DEBUG("spawn result: [~w]", [spawn(Module, Function, Parameters)]);

process_user_input({ action, Action, Pid }) ->
  PID = list_to_pid(Pid),
  ?DEBUG("Sending action [~w] to pid [~w]:[~w]", [Action, PID, int:meta(PID, Action)]);

process_user_input({ var_list , Meta }) ->
  ?DEBUG("Trying to convert to meta pid: [~s]", [Meta]),
  META = list_to_pid(Meta),
  ?DEBUG("Trying to get variable list for MetaProcess [~w]", [META]),    
  VariablesList = int:meta(META, bindings, nostack),
  ?DEBUG("Variable list is : ~w",[VariablesList]),
  ParsedData = start_parsing_variables(VariablesList),
  ?DEBUG("Parsed data is : ~s", [ParsedData]),
  ?OUTPUT("variables_list|~s", [ParsedData]);

process_user_input({ break_remove , Module , Line }) ->
  ?DEBUG("Trying remove a breakpoint for module [~w] on line [~p] ", [Module, Line] ),
  ?OUTPUT("break_remove|~w|~w|~p", [int:delete_break(Module, Line), Module, Line]);

process_user_input({ break , Module , Line }) ->
  ?DEBUG("Trying create a breakpoint for module [~s] on line [~p] ", [Module, Line] ),
  case int:break(Module, Line) of
    ok ->
      ?OUTPUT("break_set|ok|~w", [Module]);
    { error, break_exists } ->
      ?OUTPUT("break_set|ok|~w", [Module])
  end.

%%% Message handling

handle({ user_input , UserInput }) -> 
  process_user_input(UserInput);

handle({int, {new_process, { Process , FunctionInfo , Status , Info} } }) ->
  ?DEBUG("Trapped a new process info, trying to attach it to debugger... [~w] [~w] [~w]", [FunctionInfo, Status, Info]),
  case int:attached(Process) of
    { ok, Meta } ->
      ?DEBUG("Got MetaProcess [~w] for process [~w]", [Meta, Process]),
      ?OUTPUT("meta|~w|~w", [ Process, Meta ] );	    
    error ->
      ignore
  end;

handle({ int, { new_status, Process ,break, { Module, Line } } }) ->
  ?DEBUG("Trapped a break on module [~w] and line [~w]", [Module, Line ]),
  {ok, Meta} = dbg_iserver:call({get_meta, Process}),  
%   TODO: check problems with variable controller
%   VariablesList = int:meta(Meta, bindings, nostack),
%   ?DEBUG("Variable list is : ~w", [VariablesList]),
%   ParsedData = start_parsing(VariablesList),
%   ?DEBUG("Parsed data is : ~s", [ParsedData]),
%   ?OUTPUT("variables_list|~s", [ParsedData]),
  Backtrace = int:meta(Meta, backtrace, all),
  ?DEBUG("backtrace message is: [~w]", [Backtrace]),
  ?OUTPUT("stack_trace|~w|~s", [ Process, start_parsing_stack(Meta, Backtrace)]),
  ?OUTPUT("break|~s|~w|~w",[int:file(Module), Line, Process]);

handle({ int, { new_status, Process , Action, Info } }) ->
  ?DEBUG("Trapped a status update [~w] on process [~w] and info [~w]", [Action, Process, Info]),
  ?OUTPUT("process_status_update|~w|~w|~w",[Process, Action, Info]);

handle(Unknown) ->
  ?DEBUG("received: ~w", [Unknown]).


%%%%%%%%%%%%%%%%%%%%%%%% STACK TRACE PARSING %%%%%%%%%%%%%%%%%%%%%%

start_parsing_stack(Meta, [ { SP , { Module, Function, _ } } | T ]) ->
  Item = int:meta(Meta, stack_frame, { up , SP + 1 }),
  ?DEBUG("Item is: [~w]", [Item]),
  { _ , { _ , Line } , _ } = Item,
  Name = case int:file(Module) of
    { error, _ } -> "";
    Ok -> Ok    
  end,
  io_lib:format("~p,~s:~s,~s,~p ", [ SP, Module, Function, Name, Line ]) ++ start_parsing_stack(Meta, T);

start_parsing_stack( _ , [ ]) -> "".

%%%%%%%%%%%%%%%%%%%%%%%% STACK TRACE PARSING END %%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%% VARIABLE LIST TO XML CONVERSION %%%%%%%%%%%%%%%%%%

start_parsing_variables(Data) ->
  io_lib:format("<variables>~s</variables>" , [ parse(Data) ]).

parse([]) -> "";

parse([H|T]) ->
  parse(H) ++ parse(T);

parse({ VariableName , Variable }) ->
  io_lib:format("<variable name=\"~s\"><raw_value><![CDATA[~w]]></raw_value>~s</variable>",[erlang:atom_to_list(VariableName), Variable, parse_variable(Variable)]).

parse_variable(RawValue) when is_list(RawValue) ->
  io_lib:format("<item kind=\"list\"><raw_value><![CDATA[~w]]></raw_value>~s</item>",[RawValue, parse_list_items(RawValue)]);

parse_variable( RawValue ) when is_tuple(RawValue) ->
  io_lib:format("<item kind=\"tuple\"><raw_value><![CDATA[~w]]></raw_value>~s</item>",[RawValue, parse_list_items(erlang:tuple_to_list(RawValue))]);

parse_variable( Other )->
   io_lib:format("<value><![CDATA[~w]]></value>", [Other]).

parse_list_items([]) -> "";

parse_list_items([ H | T ]) ->
  parse_variable(H) ++ parse_list_items(T).

%%%%%%%%%%% END VARIABLE LIST TO XML CONVERSION %%%%%%%%%%%%%%%%%%

%%% End message handling

loop() ->
  receive
    Data ->      
      handle(Data),
      loop()    
  end.
