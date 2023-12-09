; LastEditDate="Tue Jun  4 16:01:36 1991"
; TLH - load in whether two spaces or one space are to
; be used between sentences
(declare-global justify-paragraph-style)

(defun
    (justify-paragraph
	(error-occured
	    (save-excursion
		(beginning-of-line)
		(while (& (! (bobp))
			  (! (eolp))
			  (!= (following-char) '@'))
		       (progn (previous-line)(beginning-of-line)))
		(if (| (eolp) (= (following-char) '@'))
		    (progn (next-line)(beginning-of-line)))
		(if (& (! (eolp))
		       (!= (following-char) '@'))
		    (progn last-col c-col
			   (delete-white-space)
			   (to-col left-margin)
			   (while (progn
					(end-of-line)
					(if (! (eobp)) (forward-character))
					(& (! (eolp))
					   (!= (following-char) '@')))
				  (delete-previous-character)
				  (delete-white-space)
				  (if (& (< (preceding-char) '@')
					 (= justify-paragraph-style 0) ; TLH
					 (| (= (preceding-char) '.')
					    (= (preceding-char) '!')
					    (= (preceding-char) '?')))
				      (insert-string " "))
				  (insert-string " ")
			   )
			   (if (bolp) (backward-character))
			   (setq c-col (current-column))
			   (while (progn
					(setq last-col c-col)
					(insert-character '!')
					(delete-previous-character)
					(beginning-of-line)
					(if (= (following-char) '@')
					    (insert-character ' '))
					(end-of-line)
					(setq c-col (current-column))
					(< c-col last-col))
				  (novalue))
		    )
		)
	    )
	    (message "Done!")
	    (novalue)
	)
    )
)
