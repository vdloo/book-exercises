--- Exercise 1.17
--- Write a function substring :: String -> String -> Bool
--- that checks whether str1 is a substring of str1. The
--- substrings of an arbitrary string ys are given by:
--- 1. if xs is a prefix of ys, xs is a substring of ys
--- 2. if ys equals y:ys' and xs is a substring of ys', 
--- xs is a substring of ys
--- 3. nothing else is a substring of ys

prefix :: String -> String -> Bool
prefix [] ys         = True
prefix (x:xs) []     = False
prefix (x:xs) (y:ys) = (x==y) && prefix xs ys

substring :: String -> String -> Bool
substring xs [] = False
substring xs (y:ys) | prefix xs (y:ys) = True
                    | substring xs ys  = True
                    | otherwise        = False

--- *Main> substring "some_string" "string"
--- False
--- *Main> substring "string" "some_string"
--- True

