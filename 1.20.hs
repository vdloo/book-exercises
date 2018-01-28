--- Exercise 1.20
--- Use map to write a function lengths that takes a list
--- of lists and returns a list of the corresponding list 
--- lengths.

lengths :: [[a]] -> [Int]
lengths xs = map length xs

