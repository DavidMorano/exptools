	; LastEditDate="Thu Sep 30 17:12:40 1982"
	; Macros written by Tony Hansen ;
	; define underscore-next-word ; ESC-_
	; define underscore-region

(defun
    (underscore-word
	(save-excursion
	    (save-excursion
		(prefix-argument-loop
		    (forward-word))		; surround word(s)
		(set-mark))			; ... with a
	    (backward-word)			; ... region
	    (underscore-region)))		; underscore it
)    

(defun
    (underscore-region
	(save-restriction
	    (narrow-region)			; move it to temp place
	    (beginning-of-file)			; start at beginning
	    (while (! (eobp))			; until the end
		   (insert-string "_\^H")	; ... put in an underscore
		   (forward-character)))	; ... move forward
    )
)
