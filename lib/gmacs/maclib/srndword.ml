	;;;; LastEditDate="Sat Nov 27 15:54:18 1982"
	;;;; Macro written by Tony Hansen ;
	;;;; define quotify-word and parenthesize-word
	;;;; ESC-" and ESC-lparen

; define quotify-word - ESC-"
(defun
    (quotify-word
	(provide-prefix-argument prefix-argument
	    (&-surround-word 34 34)))
    
    (&-surround-word
	(save-excursion
	    (error-occured
		(forward-character))		; position self
	    (prefix-argument-loop
		(backward-word)			; ... at front of current word
		(insert-character (arg 1))	; insert left mark
		(forward-word)			; goto end of word
		(insert-character (arg 2))	; insert right mark
		(forward-word)			; next word
	    )))
)

    ; define parenthesize-word		; ESC-lparen ;
(defun    
    (parenthesize-word
	(provide-prefix-argument prefix-argument
	    (&-surround-word 40 41)))
)
