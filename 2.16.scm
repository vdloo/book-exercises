; Explain, in general, why equivalent algebraic expressions may lead to different
; answers. Can you devise an interval-arithmetic package that does not have this shortcoming, or is this 
; task impossible?

; Because if the same interval is present multiple times in the process it can result in unwanted expansions when each occurrence is taken independently. You could stop that from happening by rewriting the function to eliminate double variables but not all functions are capable of that.
