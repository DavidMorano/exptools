	;;;; LastEditDate="Tue Jun  4 15:59:38 1991"
	;;;;
	;;;; Defines curly braces for a modified Plauger style.
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
	;;;;         {
	;;;;     	printf("hello #%d",i--);
	;;;;         }
	;;;;     }
	;;;;
	;;;;			Tony Hansen

(defun
    (electric-C-{
	(if (eolp)
	    (progn
		  (if (! (bolp))
		      (C-newline-and-indent))
		  (provide-prefix-argument prefix-argument
		      (insert-string "{"))
		  (newline-and-indent)
		  (C-indent-line)
	    )
	    (provide-prefix-argument prefix-argument
		(insert-string "{"))
	)
    )

    (electric-C-}
	(if (eolp)
	    (progn
		  (delete-white-space)
		  (if (bolp)
		      (delete-previous-character)
		  )
		  (C-newline-and-indent)
		  (provide-prefix-argument prefix-argument
		      (C-paren))
		  (C-dedent-line)
		  (end-of-line)
		  (newline-and-indent)
	    )
	    (provide-prefix-argument prefix-argument
		(C-paren))
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
	)
	(goto-character (/ (* (buffer-size) old-dot) old-size))
	(message "Done!")
	(novalue)
    )
)
