	;;;; LastEditDate="Mon Sep  6 17:27:29 1982"
(if (! (is-bound paragraph-delimiters))
    (progn
	(declare-global paragraph-delimiters)
	(setq paragraph-delimiters "^\n\\|^[@.' \t].*\n")
    ))

(defun
    (forward-paragraph
	(prefix-argument-loop 				; TLH - added loop
	    (beginning-of-line)
	    (re-search-forward paragraph-delimiters)
	    (while (looking-at "")
		   (search-forward ""))))
)

(defun
    (backward-paragraph
	(prefix-argument-loop 				; TLH - added loop
	    (beginning-of-line)
	    (previous-line)
	    (while (& (looking-at paragraph-delimiters) (! (bobp)))
		   (progn (previous-line) (beginning-of-line)))
	    (if (error-occured (re-search-reverse ""))
		(beginning-of-file))
	    (while (looking-at "")
		   (search-forward ""))))
)
