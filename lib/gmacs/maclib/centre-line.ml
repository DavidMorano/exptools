	;;;; LastEditDate="Fri Oct  8 12:45:20 1982"
; function to centre the current line
(defun
    (centre-line width
	(save-excursion
	    (prefix-argument-loop 			; TLH
		(beginning-of-line)
		(delete-white-space)
		(end-of-line)
		(delete-white-space)
		(setq width (current-column))
		(beginning-of-line)
		(to-col (/ (- (- right-margin 3) width) 2)) ; TLH
		;(to-col (/ (- 74 width) 2))		; TLH
		(next-line))				; TLH
	)
    )

    (center-line
	(provide-prefix-argument prefix-argument
	    (centre-line)))
)
