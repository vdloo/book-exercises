--- Exercise 2.4
--- Check that the truth table for exclusive or from
--- exercise 2.2 is equivalent to the table for 
--- ¬ (P ⇔ Q). Conclude that the Haskell implementation
--- of the function <+> for exclusive or in the frame
--- below is correct.
--- 
--- P Q | ¬ (P ⇔ Q)
--- t t | f
--- t f | t
--- f t | t
--- f f | f

--- *Main Data.Bool> not (True == True)
--- False
--- *Main Data.Bool> not (True == False)
--- True
--- *Main Data.Bool> not (False == True)
--- True
--- *Main Data.Bool> not (False == False)
--- False

infixr 2 <+> 

(<+>) :: Bool -> Bool -> Bool
x <+> y = x /= y

--- *Main Data.Bool> True <+> True
--- False
--- *Main Data.Bool> True <+> False
--- True
--- *Main Data.Bool> False <+> True
--- True
--- *Main Data.Bool> False <+> False
--- False

