--- Exercise 1.5
--- Add the definitions for the prime0 implementation and
--- try it out.

divides d n = rem n d == 0

ldf k n | divides k n = k
        | k^2 >  n    = n
        | otherwise   = ldf (k+1) n

ld n = ldf 2 n

prime0 n | n < 1      = error "not a positive integer"
         | n == 1     = False
         | otherwise  = ld n == n

--- Run like
--- $ stack ghci
--- Prelude> :l 1.5
--- [1 of 1] Compiling Main             ( 1.5.hs, interpreted )
--- Ok, modules loaded: Main.
--- *Main> prime0 11
--- True
--- *Main> prime0 10
--- False

