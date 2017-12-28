--- Exercise 1.13
--- Write a function count for counting the number
--- of occurrences of a character in a string.


count :: Char -> String -> Int
count c [] = 0
count c (x:xs) | x == c    = 1 + count c xs
               | otherwise = count c xs

