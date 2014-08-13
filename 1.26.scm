; The square procedure first evaluates the given input 
; and then multiplies the result with itself, 
;
; the instructions
;
(* (expmod base (/ exp 2) m)
   (expmod base (/ exp 2) m)
)
; will make the program evaluate the expmod twice, 
; which makes the process Theta(f(n)) instead of 
; Theta(f(log(n))) in complexity by making the process
; tree recursive instead of linear recursive because
; each call to expmod where exp is even will result in
; two calls to expmod instead of only one.
