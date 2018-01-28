--- Exercise 1.15
--- Write a function strString :: [String] -> [String]
--- that sorts a list of strings in alphabetical order.

--- strString uses quicksort, but it is not in place so
--- it is not a 'true' quicksort.
strString :: [String] -> [String]
strString [] = []
strString (x:xs) = 
    strString (filter (\y -> y < x) xs) ++ 
    [x] ++ strString (filter (\y -> y >= x) xs)

--- *Main> strString ["6", "5", "3", "1", "8", "ab", "aaa", "4"]
--- ["1","3","4","5","6","8","aaa","ab"]

