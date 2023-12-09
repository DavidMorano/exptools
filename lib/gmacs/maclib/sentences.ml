	;;;; LastEditDate="Mon Sep  6 17:38:53 1982"
(if (! (is-bound sentence-delimiters))
    (progn
	(declare-global sentence-delimiters)
	(setq sentence-delimiters "[.!?][ \n\t][ \n\t]*")
    ))

(defun
    (forward-sentence
	(prefix-argument-loop 				; TLH added loop
	    (re-search-forward sentence-delimiters)
	    (while (looking-at "")
		   (search-forward ""))))
)

(defun
    (backward-sentence stpos searchp
	(prefix-argument-loop 				; TLH added loop
	    (setq stpos (dot))
	    (preceding-char)
	    (if (error-occured (re-search-reverse sentence-delimiters))
		(beginning-of-file))
	    (setq searchp (dot))
	    (while (looking-at "")
		   (search-forward ""))
	    (if (>= (dot) stpos)
		(progn
		      (goto-character searchp)
		      (if (error-occured (re-search-reverse ""))
			  (beginning-of-file))
		      (while (looking-at "")
			     (search-forward "")))
	    )
	)
    )
)
