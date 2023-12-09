	;;;; LastEditDate="Thu Oct  7 14:42:12 1982"
	;;;; Written by Tony Hansen.
	;;;; join lines, leaving only one space between each.
	;;;; split lines to right-margin

(defun
    (join-lines
	(end-of-line)
	(save-excursion
	    (prefix-argument-loop
		(end-of-line)
		(delete-next-character)
		(delete-white-space)
		(insert-character ' ')
		(backward-character))))
)
; split-lines
(defun    
    (split-lines
	(prefix-argument-loop
	    (end-of-line)
	    (if (> (current-column) right-margin)
		(progn
		      (beginning-of-line)
		      (error-occured 
			  (provide-prefix-argument
			      (+ right-margin 1)
			      (forward-character)))
		      (re-search-reverse "[ \^I]")
		      (delete-white-space)
		      (newline)))))
)
