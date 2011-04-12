-module(%{APPNAME}_app).

-behaviour(application).

-export([start/2,stop/1]).

start(Type, StartArgs) ->
    case %{APPNAME}_sup:start_link() of
      {ok, Pid} ->
	  {ok, Pid};
      Error ->
        Error
    end.

shutdown() ->
    application:stop(%{APPNAME}_app).

stop(State) ->
    ok.