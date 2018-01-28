--- Exercise 2.13
--- Implement checks for the principles from Theorem 2.12

--- Need FlexibleInstances otherwise you'd get:
--- • Illegal instance declaration for ‘TF (Bool -> p)’
---     (All instance types must be of the form (T a1 ... an)
---      where a1 ... an are *distinct type variables*,
---      and each type variable appears at most once in the instance head.
---      Use FlexibleInstances if you want to disable this.)
--- • In the instance declaration for ‘TF (Bool -> p)’
{-# LANGUAGE FlexibleInstances #-}

                 
class TF p where
  valid :: p -> Bool
  lequiv :: p -> p -> Bool

instance TF Bool
  where
    valid = id
    lequiv f g = f == g

instance TF p => TF (Bool -> p)
  where
    valid f = valid (f True) && valid (f False)
    lequiv f g = (f True) `lequiv` (g True)
                 && (f False) `lequiv` (g False)

(==>) :: Bool -> Bool -> Bool
True ==> x = x
False ==> x = True

--- 1. ¬ T ≡ ⊥; ¬ ⊥ ≡ T
---
--- ¬ T ≡ ⊥
test1a = lequiv (not True) False
--- *Main> test1a
--- True
---
--- ¬ ⊥ ≡ T
test1b = lequiv (not False) True
--- *Main> test1b
--- True

--- 2. P ⇒ ⊥ ≡ ¬ P
---
--- P ⇒ ⊥ ≡ ¬ P
test2 = lequiv (\ p -> p ==> False) (\ p -> not p)
--- *Main> test2
--- True

--- 3. P ∨ T ≡ T; P ∧ ⊥ ≡ ⊥ (dominance laws)
---
--- P ∨ T ≡ T
test3a = lequiv (\ p -> p || True) (\ p -> True)
--- *Main> test3a
--- True
---
--- P ∧ ⊥ ≡ ⊥ 
test3b = lequiv (\ p -> p && False) (\ p -> False)
--- *Main> test3b
--- True

--- 4. P ∨ ⊥ ≡ P; P ∧ T ≡ P (identity laws)
---
--- P ∨ ⊥ ≡ T
test4a = lequiv (\ p -> p || False) (\ p -> p)
--- *Main> test4a
--- True
---
--- P ∧ T ≡ P 
test4b = lequiv (\ p -> p && True) (\ p -> p)
--- *Main> test4b
--- True

--- 5. P ∨ ¬ P ≡ T (laws of excluded middle)
---
--- P ∨ ¬ P ≡ T 
test5 = lequiv (\ p -> p || not p) (\ p -> True)
--- *Main> test5
--- True

--- 6. P ∧ ¬ P ≡ ⊥ (contradiction)
test6 = lequiv (\ p -> p && not p) (\ p -> False)
--- *Main> test6
--- True

