-module(%{APPNAME}_sup).

-behaviour(supervisor).

-export([start_link/0]).
-export([init/1]).

start_link() ->
    supervisor:start_link(%{APPNAME}_sup, []).

init(_Args) ->
  %%Your code here
    ok.