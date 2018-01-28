--- Exercise 1.18
--- Find expressions with the following types:

--- 1. [String]
--- Prelude> :t ["SomeString"]
--- ["SomeString"] :: [[Char]]

--- 2. (Bool, String)
--- Prelude> :t (True, "SomeString")
--- (True, "SomeString") :: (Bool, [Char])

--- 3. [(Bool,String)]
--- Prelude> :t [(True, "SomeString")]
--- [(True, "SomeString")] :: [(Bool, [Char])]

--- 4. ([Bool], String)
--- Prelude> :t ([True], "SomeString")
--- ([True], "SomeString") :: ([Bool], [Char])

--- 5. Bool -> Bool
--- Prelude> :t \True -> True
--- \True -> True :: Bool -> Bool

