--- Exercise 1.21
--- Use map to write a function lengths that takes a list
--- of lists and returns the sum of their lengths.

sumLengths :: [[a]] -> Int
sumLengths xs = sum (map length xs)

