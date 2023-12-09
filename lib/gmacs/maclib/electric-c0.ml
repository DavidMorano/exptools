	;;;; LastEditDate="Tue Jun  4 15:56:09 1991"
	;;;;
	;;;; Defines curly braces to do what I think they should do.
	;;;; This is the style used by Plauger in 1980.
	;;;;
	;;;; That is, the keystrokes:
	;;;;
	;;;;     main(){int i = 10;while (i > 0){printf("hello #%d",i--);}}
	;;;;
	;;;; will produce:
	;;;;
	;;;;     main()
	;;;;     {
	;;;;         int i = 10;
	;;;;         while (i > 0)
	;;;;     	{
	;;;;     	printf("hello #%d",i--);
	;;;;     	}
	;;;;     }
	;;;;
	;;;;
	;;;;			Tony Hansen

(defun
    (electric-C-{
	(if (eolp)
	    (progn
		  (if (!= (current-column) 1)
		      (C-newline-and-indent))
		  (if (bolp)
		      (progn
			    (provide-prefix-argument prefix-argument
				(insert-string "{"))
			    (newline)
			    (C-indent-line))
		      (progn
			    (C-indent-line)
			    (provide-prefix-argument prefix-argument
				(insert-string "{"))
			    (C-newline-and-indent))))
	    (provide-prefix-argument prefix-argument
		(insert-string "{")
	    )
	)
    )

    (electric-C-}
	(if (eolp)
	    (progn
		  (delete-white-space)
		  (if (! (bolp))
		      (C-newline-and-indent)
		      (progn
			    (delete-previous-character)
			    (C-newline-and-indent)
		      )
		  )
		  (provide-prefix-argument prefix-argument
		      (C-paren))
		  (if (= (save-excursion
			     (previous-line)
			     (end-of-line)
			     (preceding-char))
			'}')
		      (C-dedent-line))
		  (if (= (current-indent)
			 (+ C-indent-size 1))
		      (C-dedent-line))
		  (end-of-line)
		  (C-newline-and-indent)
		  (C-dedent-line)
	    )
	    (provide-prefix-argument prefix-argument
		(C-paren)
	    )
	)
    )

    (C-indent old-dot old-size
	(setq old-dot (+ (dot) 0))
	(setq old-size (buffer-size))
	(save-excursion
	    (if prefix-argument-provided
		(progn
		      (beginning-of-file)
		      (set-mark)
		      (end-of-file))
		(progn
		      (previous-line)
		      (re-search-forward "^}")
		      (set-mark)
		      (backward-paren)
		      (beginning-of-line)
		      (exchange-dot-and-mark)
		      (end-of-line)
		      (error-occured
			  (forward-character))))
	    (filter-region
		(concat "$TOOLS/lib/gmacs/etc/indent -st -bl -i"
			C-indent-size
			" -c" comment-column))
	    ; TLH -v
	    (save-restriction cur-indent
		(narrow-region)
		(beginning-of-file)
		(while (! (error-occured
			      (re-search-forward "^[ \^I][ \^I]*[{}]")))
		       (beginning-of-line)
		       (setq cur-indent (current-indent))
		       (delete-white-space)
		       (to-col (+ cur-indent C-indent-size))))
	    ; TLH -^
	)
	(goto-character (/ (* (buffer-size) old-dot) old-size))
	(message "Done!")
	(novalue)
    )
)
