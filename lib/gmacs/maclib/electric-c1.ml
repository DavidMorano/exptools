	;;;; LastEditDate="Tue Jun  4 15:59:05 1991"
	;;;; moved from electric-c.ml by TLH
	;;;;
	;;;; Defines curly braces for a Kernighan-Ritchie style.
	;;;;
	;;;; That is, the keystrokes:
	;;;;
	;;;;     main(){int i = 10;while (i > 0){printf("hello #%d",i--);}}
	;;;;
	;;;; will produce:
	;;;;
	;;;;     main() {
	;;;;         int i = 10;
	;;;;         while (i > 0) {
	;;;;     	printf("hello #%d",i--);
	;;;;         }
	;;;;     }
	;;;;


(defun
    (electric-C-{
	(if (eolp)
	    (progn
		  (if (! (= (preceding-char) ' '))
		      (insert-string " "))
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
		(concat "$TOOLS/lib/gmacs/etc/indent -st -br -i"
			C-indent-size
			" -c" comment-column))
	)
	(goto-character (/ (* (buffer-size) old-dot) old-size))
	(message "Done!")
	(novalue)
    )
)
