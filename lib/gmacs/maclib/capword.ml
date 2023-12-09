	; LastEditDate="Mon Sep 27 16:30:20 1982"
	; Macro written by Tony Hansen ;
	; define "capitalize-word" ; ESC-C
(defun
    (capitalize-word
	(prefix-argument-loop
	    (insert-string " a ")		; mark spot
	    (forward-word)			; to end of word
	    (case-word-capitalize)		; capitalize word
	    (backward-word)			; back to spot
	    (backward-word)			; ...
	    (delete-previous-character)		; remove spot
	    (delete-next-character)		; ...
	    (delete-next-character)		; ...
	    (forward-word)			; to end of word
	))
)
    ; define "upper-case-word" ; ESC-U ;
(defun
    (upper-case-word
	(prefix-argument-loop
	    (insert-string " a ")		; mark spot
	    (forward-word)			; to end of word
	    (case-word-upper)			; make word upper-case
	    (backward-word)			; back to spot
	    (backward-word)			; ...
	    (delete-previous-character)		; remove spot
	    (delete-next-character)		; ...
	    (delete-next-character)		; ...
	    (forward-word)			; to end of word
	))
)
    ; define "lower-case-word" ; ESC-L ;
(defun
    (lower-case-word
	(prefix-argument-loop
	    (insert-string " a ")		; mark spot
	    (forward-word)			; to end of word
	    (case-word-lower)			; make word lower-case
	    (backward-word) 			; back to spot
	    (backward-word)			; ...
	    (delete-previous-character)		; remove spot
	    (delete-next-character)		; ...
	    (delete-next-character)		; ...
	    (forward-word)			; to end of word
	))
)
