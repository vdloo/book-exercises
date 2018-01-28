--- Exercise 1.10
--- Define a function removeFst that removes the first
--- occurence of an integer m from a list of integers.
--- If m does not occur in the list, the list remains
--- unchanged.

removeFstIter :: [Int] -> Int -> [Int] -> [Int]
removeFstIter [] m acc    = acc
removeFstIter (x:xs) m acc 
  | m == x    = removeFstIter xs m acc
  | otherwise = removeFstIter xs m (x:acc)

removeFst :: [Int] -> Int -> [Int]
removeFst (x:xs) m = reverse (removeFstIter (x:xs) m [])

