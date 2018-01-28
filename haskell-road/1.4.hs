--- Exercise 1.4
--- Suppose in the definition of ldf we replace the condition
--- k^2 > n by k^2 >= n, where >= expresses 'greater than or 
--- equal'. Would that make any difference to the meaning of
--- the program? Why (not)?

divides d n = rem n d == 0

ldf k n | divides k n = k
        | k^2 >  n    = n
        | otherwise   = ldf (k+1) n

--- Answer: that does not make a difference because in all 
--- cases where k^2 > (n + 1) would have already been caught 
--- by the previous guarded equation, 'divides k n = k'. If
--- 'k^2 = n' is True then 'divides k n = k' will also be True.

