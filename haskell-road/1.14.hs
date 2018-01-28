--- Exercise 1.14
--- Write a function blowup that converts a string
--- a1a2a3 into a1a2a2a3a3a3. "bang!" should yield
--- "baannngggg!!!!!"

blowup :: String -> String
blowup xs  = concat (map (uncurry replicate) (zip [1..] xs))

