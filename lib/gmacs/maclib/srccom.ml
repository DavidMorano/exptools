; LastEditDate="Tue Jun  4 17:54:33 1991"
; srccom: compare text in two windows

; To begin the comparison, place the dot at the beginning of one of the
; two pieces of text to be compared, switch to the other window, and place
; the dot at the beginning of the other piece of text.  (If there are more
; than two windows, the two windows to be compared must be adjacent, and
; the dot must be left in the upper one.)  When this command is invoked, it
; will search forward, stopping when either a difference is encountered
; or the end of the buffer is reached.  case-fold-search governs comparison
; of case differences.  The region is left around the equal portions in both
; windows.

; HISTORY:
; 	1 June 1982 -- Jerry Agin at Carnegie-Mellon University -- created
;	23 Aug 1984 -- Tony Hansen -- added messages

(defun
    (srccom c1 c2 eob1 eob2 success
	(message "Comparing source....")
	(sit-for 0)
	(set-mark)
	(next-window)
	(set-mark)
	(previous-window)
	(setq success 1)
	(while success 
	    (setq c1 (following-char))
	    (setq eob1 (eobp))
	    (next-window)
	    (setq c2 (following-char))
	    (setq eob2 (eobp))
	    (if (| eob1 eob2)
		(progn
		      (setq success 0)
		      (if (& eob1 eob2)
			  (message "...buffers are identical")
			  (error-message "end of buffer found")
		      )
		)
		(progn
		    (if (c= c1 c2)
			(progn
			    (forward-character)
			    (previous-window)
			    (forward-character)
			)
			(progn
			    (setq success 0)
			    (previous-window)
			    (error-message "Char '" (char-to-string c1)
				"' is not equal to '" (char-to-string c2)
				"'")
			)
		    )
		)
	    )
	)
    )
)
