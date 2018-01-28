--- Exercise 1.24
--- What happens when you modify the defining equation of 
--- ldp as follows?
---
--- ldp :: Integer -> Integer
--- ldp = ldpf primes1

ldp' :: Integer -> Integer
ldp' n = ldpf primes1 n

ldp :: Integer -> Integer
ldp = ldpf primes1

ldpf :: [Integer] -> Integer -> Integer
ldpf (p:ps) n | rem n p == 0 = p
              | p^2 > n      = n
              | otherwise    = ldpf ps n

primes1 :: [Integer]
primes1 = 2 : filter prime [3..]

prime :: Integer -> Bool
prime n | n < 1  = error "not a positive integer"
        | n == 1 = False
        | otherwise = ldp n == n

--- In both cases the output would be
--- *Main> primes1!!100000
--- 1299721
--- *Main> prime 1299721
--- True
--- *Main> prime 1299722
--- False
--- Nothing is changed because losing the n is just 
--- pointfree style. https://wiki.haskell.org/Pointfree

