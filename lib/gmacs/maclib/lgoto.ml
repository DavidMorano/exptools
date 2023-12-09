	;;;; LastEditDate="Wed Feb 20 09:49:22 1985"
	;;;; Written by Tony Hansen.
	;;;;
	;;;; forward-to-character - ^]
	;;;; backward-to-character - ESC-^]
	;;;;
	;;;;	Go forward or backward to the char in the line matching
	;;;;	the next character typed. This was inspired by the similar
	;;;;	capabilities available in emacs mode within ksh.
	;;;;
	;;;; middle-of-window - ESC-m
	;;;;
	;;;;	Go to the line in the middle of the window.
	;;;;

(defun
    (forward-to-character char current-dot
	(setq current-dot (dot))
	(setq char (get-tty-character))
	(prefix-argument-loop
	    (if (= char (following-char))
		(forward-character))
	    (while (& (!= char (following-char))
		      (! (eolp)))
		   (forward-character))
	    (if (eolp)
		(progn
		      (beginning-of-line)
		      (while (& (!= char (following-char))
				(< (dot) current-dot))
			     (forward-character))
		      (if (= (dot) current-dot)
			  (error-message (char-to-string char) " not found!"))
		))
	))
    
    (backward-to-character char current-dot
	(setq current-dot (dot))
	(setq char (get-tty-character))
	(prefix-argument-loop
	    (while (& (!= char (preceding-char))
		      (! (bolp)))
		   (backward-character))
	    (if (bolp)
		(progn
		      (end-of-line)
		      (while (& (!= char (preceding-char))
				(> (dot) current-dot))
			     (backward-character))
		      (if (= (dot) current-dot)
			  (error-message (char-to-string char) " not found!"))
		))
	    (backward-character)))

    ; This is fairly simple minded. If lines are folding, it will mess
    ; up, but won't do worse than go to the last line in the window.
    (middle-of-window
	(beginning-of-window)
	(provide-prefix-argument (/ (window-height) 2)
	    (next-line))
	(while (! (dot-is-visible))
	       (previous-line))
    )
)
