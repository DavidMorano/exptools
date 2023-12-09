	;;;; LastEditDate="Wed Jan 12 13:15:46 1983"
	;;;; redraw line, redraw window, and new-redisplay
	;;;; written by Tony Hansen

; Redraw a single line on the screen.
(defun
    (redraw-line modflag char
	(setq modflag buffer-is-modified)
	(setq char (+ (dot) 0))
	(beginning-of-line)
	(insert-string "a")
	(beginning-of-line)
	; should check for length of line and insert the
	; necessary number of newlines.
	(kill-to-end-of-line)
	(setq buffer-is-modified modflag)
	(sit-for 0)
	(yank-from-killbuffer)
	(beginning-of-line)
	(delete-next-character)
	(goto-character char)
	(setq buffer-is-modified modflag))
)

; Redraw the whole window. Faster than the whole screen, slower than a
; single line.
(defun
    (redraw-window window-size modflag
	(setq modflag buffer-is-modified)
	(setq window-size (window-height))
	(save-excursion
	    (beginning-of-window)
	    (provide-prefix-argument window-size
		(newline-and-backup))
	    (setq buffer-is-modified modflag)
	    (sit-for 0)
	    (provide-prefix-argument window-size
		(delete-next-character)))
	(setq buffer-is-modified modflag))
)

; new-redraw-display
(defun
    (new-redraw-display
	(if prefix-argument-provided
	    (redraw-line)
	    (redraw-display)))
)
