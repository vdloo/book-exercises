--- Exercise 2.15
--- Write Haskell definitions of contradiction tests for 
--- propositional functions with one, two and three variables.

contradiction1 :: (Bool -> Bool) -> Bool
contradiction1 bf = not ((bf True) || (bf False))

contradiction2 :: (Bool -> Bool -> Bool) -> Bool
contradiction2 bf = not ((bf True True) 
                    || (bf True False) 
                    || (bf False True) 
                    || (bf False False))

contradiction3 :: (Bool -> Bool -> Bool -> Bool) -> Bool
contradiction3 bf = not (or [ bf p q r | p <- [True, False],
                                         q <- [True, False],
                                         r <- [True, False]])

