-module(countTest).

-spec count_matching(fun((T) -> boolean()), list(T)) -> non_neg_integer().
-export([count_matching/2]).


count_matching(Pred, Lst) -> count_matching(Pred, Lst, 0).
count_matching(_, [], Count) -> Count;
count_matching(Pred, [Head|Rest], Count) ->
        case Pred(Head) of
                true -> count_matching(Pred, Rest, Count + 1);
                false -> count_matching(Pred, Rest, Count)
        end.
