-module(debug_interpreter).

-export([start/0, start_loop/0]).

-define(DEBUG(Text,Parameters),  io:format("--- " ++ Text ++ "~n", Parameters)).
-define(OUTPUT(Text, Parameters), io:format("~c" ++ Text ++ "~n" , [1] ++ Parameters)).
start() ->
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
  ?DEBUG("Trying to get variable list for MetaProcess [~w]", [Meta]),
  META = list_to_pid(Meta),
  ?DEBUG("teste [~w]", [int:meta(META, bindings, nostack)]);

process_user_input({ break , Module , Line }) ->
  ?DEBUG("Trying create a breakpoint for module [~w] on line [~p] ", [Module, Line] ),
  case int:break(Module, Line) of
    ok ->
      ?OUTPUT("break_set|ok|~w", [Module]);
    { error, break_exists } ->
      ?OUTPUT("break_set|ok|~w }", [Module])
  end.

loop() ->
  ?DEBUG("debug: loop" , []),
  receive
    { user_input , UserInput } ->
      process_user_input(UserInput),
      loop();

    {int, {new_process, { Process , FunctionInfo , Status , Info} } } ->
      ?DEBUG("Trapped a new process info, trying to attach it to debugger... [~w] [~w] [~w]", [FunctionInfo, Status, Info]),
      case int:attached(Process) of
	  { ok, Meta } ->
	    ?DEBUG("Got MetaProcess [~w] for process [~w]", [Meta, Process]),
	    ?OUTPUT("meta|~w|~w", [ Process, Meta ] );	    
	   error ->
	    ignore
       end,
       loop();
    {int, { new_status, Process ,break, { Module, Line } } } ->
       ?DEBUG("Trapped a break on module [~w] and line [~w]", [Module, Line ]),
       ?OUTPUT("break|~s|~w|~w",[int:file(Module), Line, Process]),
       loop();

    Data ->
      ?DEBUG("received: ~w~n", [Data]),
      loop()
  end.
