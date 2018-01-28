--- Exercise 1.7
--- The Haskell system has a command for checking the
--- types of expressions. Explain the following:

divides :: Integer -> Integer -> Bool
divides d n = rem n d == 0

--- Prelude> :l 1.7
--- [1 of 1] Compiling Main             ( 1.7.hs, interpreted )
--- Ok, modules loaded: Main.
--- *Main> :t divides 5
--- divides 5 :: Integer -> Bool
--- *Main> :t divides 5 7
--- divides 5 7 :: Bool
--- *Main> 
---
--- This happens because Haskell uses currying. If you apply
--- a function with partial arguments you will get back a 
--- function that is the same function with the previously
--- specified argument filled in.

