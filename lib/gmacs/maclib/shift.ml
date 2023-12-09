	;;;; LastEditDate="Mon Sep 27 16:31:59 1982"
(defun
    (shift-line-left shift
	(setq shift (get-tty-string "How far left? "))
	(save-excursion curind oldprefix
	    (setq oldprefix prefix-argument)
	    (if (< prefix-argument 0)
		(setq prefix-argument (- 0 prefix-argument)))
	    (prefix-argument-loop
		(beginning-of-line)
		(setq curind (current-indent))
		(delete-white-space)
		(if (> curind shift)
		    (to-col (- curind shift)))
		(if (> oldprefix 0)
		    (next-line)
		    (previous-line)))))
)

(defun
    (shift-line-right shift
	(setq shift (get-tty-string "How far right? "))
	(save-excursion curind oldprefix
	    (setq oldprefix prefix-argument)
	    (if (< prefix-argument 0)
		(setq prefix-argument (- 0 prefix-argument)))
	    (prefix-argument-loop
		(beginning-of-line)
		(setq curind (current-indent))
		(delete-white-space)
		(to-col (+ curind shift))
		(if (> oldprefix 0)
		    (next-line)
		    (previous-line)))))
)



