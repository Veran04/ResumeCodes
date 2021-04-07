

-module(concatTest).
-spec concatTest(Lists :: [[T]]) -> [T].
-export([concatTest/1]).
	concatTest([]) -> [];  
	concatTest([H|T]) -> H ++ concatTest(T).
