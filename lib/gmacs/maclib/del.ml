	; LastEditDate="Sat Apr 19 11:24:13 1986"
	; Macros written by Tony Hansen ;
	; 
	; define delete-backward-changing-tabs ; BS or DEL ;
	; define "delete-blank-lines" ; ESC-^O ;
	; define "delete-matching-lines" ; not bound

(defun
    (delete-backward-changing-tabs newcolumn
	(prefix-argument-loop
	    (setq newcolumn			; set destination at 1 less
		  (- (current-column) 1))	;     than current column
	    (if (bobp)				; cannot go past beginning
	    (abort-operation)			; ...
		(!= (preceding-char) 9)		; if not tab,
		(delete-previous-character)	;     delete it
		(progn				; if is a tab
		    (delete-previous-character)	;     delete it,
		    (to-col newcolumn))		;     go up to destination
	    )))

    (delete-blank-lines
	loopctl curind curcol
	(beginning-of-line)			; start at beginning
	(while					; delete white space
	    (| (= (preceding-char) 10)		;     new-line?
	       (| (= (preceding-char) 32)	;     space?
		  (= (preceding-char) 9)	;     tab?
	       ))
	    (delete-previous-character))	; ok, delete it
	(newline)				; put back newline
	(newline)				; add an extra one
	(setq loopctl 1)			; loopctl == white space
	(while loopctl				; while white space
	       (end-of-line)			; to end of line
	       (setq curind (current-indent))	; line is blank if
	       (setq curcol (current-column))	;     curind == curcol
	       (if (eobp)			; eob?
		   (progn			;     then stop
		       (delete-white-space)	;     after deleting white
		       (setq loopctl 0))	;     space
		   (= curind curcol)		; blank line?
		   (progn			;     then delete it.
		       (delete-white-space)	;     first white space,
		       (delete-next-character))	;     then new-line
		   (setq loopctl 0)		; else done
	       ))
	(beginning-of-line))			; why not?

    (delete-matching-lines pattern count
	(setq count 0)
	(setq pattern (arg 1 "delete-matching-lines (pattern) "))
	(save-excursion
	    (beginning-of-file)
	    (while (! (error-occured (re-search-forward pattern)))
		   (setq count (+ count 1))
		   (beginning-of-line)
		   (set-mark)
		   (end-of-line)
		   (error-occured (forward-character))
		   (erase-region)))
	(message count " lines deleted")
	(novalue))
)
