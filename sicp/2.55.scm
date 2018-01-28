; exercise 2.55
; These all return the function 'quote' because these are all the same thing.
; '(a b) is a list, so '('quote 'a) is a list too. If you write ''a you're
; effectively writing '(<symbol1> <symbol2>) and then the car of that would
; be the first symbol, which in this case is 'quote.
(car ''abracadabra)
; quote
(car (quote (quote abracadabra)))
; quote
(car '(quote abracadabra))
; quote
(car (quote 'abracadabra))
; quote

