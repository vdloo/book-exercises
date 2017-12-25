--- Exercise 1.9
--- Define a function that gives the maximum of a list
--- of integers. Use the predefined function max.

mxmInt :: [Int] -> Int
mxmInt [] = error "empty list"
mxmInt [x] = x
mxmInt (x:xs) = max x (mxmInt xs)

