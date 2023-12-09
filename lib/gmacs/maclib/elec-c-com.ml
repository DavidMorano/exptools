	;;;; LastEditDate="Sat Sep  2 14:15:31 1989"
	;;;;
	;;;; Routines common to electric-c-mode and electric-C++-mode
	;;;;

(declare-buffer-specific &C-comment-state)

(declare-global C-style)
(load (concat "electric-c" C-style))

(declare-global C-indent-size)
(if (= C-indent-size 0)
    (setq C-indent-size 4))

(declare-global C-show-paren-time)
(if (= C-show-paren-time 0)
    (setq C-show-paren-time 5))

(declare-global C-startup-mode)

(defun
    (C-do-indent-line x
	(setq x (arg 1))
	(beginning-of-line)
	(delete-white-space)
	(to-col x)
	(setq prefix-argument (- prefix-argument 1))
	(save-excursion
	    (prefix-argument-loop
		(next-line)
		(beginning-of-line)
		(delete-white-space)
		(to-col x)
	    )
	)
    )

    (C-re-indent-line				; re-indent line
	(provide-prefix-argument prefix-argument
	    (C-do-indent-line (current-C-indent))
	)
    )

    (C-dedent-line
	(provide-prefix-argument prefix-argument
	    (C-do-indent-line (- (current-indent) C-indent-size))
	)
    )

    (C-indent-line x
	(provide-prefix-argument prefix-argument
	    (C-do-indent-line (+ (current-indent) C-indent-size))
	)
    )

    (C-newline-and-indent x
	(provide-prefix-argument prefix-argument
	    (newline))
	(to-col (current-C-indent))
    )

    (C-paren
	    (prefix-argument-loop
		(insert-character (last-key-struck))
		(save-excursion
		    (backward-paren)
		    (if (dot-is-visible)
			(sit-for C-show-paren-time)
			(progn
			      (beginning-of-line)
			      (set-mark)
			      (end-of-line)
			      (message (region-to-string)))
		    )
		)
	    )
    )

    (electric-C-semi
	(provide-prefix-argument prefix-argument
	    (insert-string ";")
	)
	(if (& (eolp)
	       (save-excursion
		   (beginning-of-line)
		   (! (looking-at "[ \t]*for[ \t]*("))))
	    (C-newline-and-indent))
    )

    (electric-C->
	(provide-prefix-argument prefix-argument
	    (insert-string ">")
	)
	(if (& (eolp)
	       (save-excursion
		   (beginning-of-line)
		   (looking-at "#[ \t]*include[ \t]*<")))
	    (newline))
    )

    (electric-C-*
	(if (& (eolp) (= (preceding-char) '/'))
	    (progn
		  (delete-previous-character)
		  (if (! (bolp))
		      (progn
			    (delete-white-space)
			    (if (bolp) (delete-previous-character))
		      )
		  )
		  (begin-C-comment)
	    )
	    (provide-prefix-argument prefix-argument
		(insert-string "*")
	    )
	)
    )

    (skip-spaces
	(forward-character)
	(while (| (| (= (following-char) ' ')
		     (= (following-char) '^I'))
		  (= (following-char) 10))
	       (forward-character)
	)
    )

    (begin-C-comment
	(move-to-comment-column)
	(setq left-margin (current-column))
	(setq right-margin 78)
	(setq prefix-string "   ")
	(insert-string "/* ")
	(setq &C-comment-state 1)
    )

    (end-C-comment
	(if (!= (preceding-char) ' ') (insert-character ' '))
	(insert-string "*/")
	(setq right-margin 1000)
	(setq left-margin 0)
	(setq prefix-string "")
	(setq &C-comment-state 0)
    )

    ; Return the current indentation level for the line above.
    ; Don't trust lines which begin with comments, are blank,
    ; or appear to be labels.
    (current-C-indent
	;(looking-at "^\\([ \t]*/[/*]\\)\\|\\(.*:[ \t]*$\\)")
	;(looking-at "^\\([ \t]*/[/*].*\\)\\|\\(.*:[ \t]*\\)\\|\\([ \t]*]\\)$")
	;(looking-at "\\(^[ \t]*/[/*].*$\\)\\|\\(^.*:[ \t]*$\\)\\|\\(^[ \t]*]$\\)")
	(save-excursion
	    (while
		  (progn
			(previous-line)
			(beginning-of-line)
			(& (| (looking-at "[ \t]*/[/*]")
			      (looking-at "[^:\n]*\\:")
			      (looking-at "[ \t]*#")
			      (looking-at "[ \t]*$")
			   )
			   (! (bobp))
			)
		  )
		  (bolp)
	    )
	    (current-indent)
	)
    )
)
