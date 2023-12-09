	; LastEditDate="Mon Jun 20 21:06:06 1983"
(defun
    (define-db
	(extend-database-search-list
	    "DB-list"
	    (concat "$TOOLS/lib/gmacs/databases/" (arg 1 "Database: "))
	)
    )
    (query-db item line-count
	(setq item (arg 1 "Item: "))
	(save-excursion 
	    (pop-to-buffer "DB Display")
	    (erase-buffer)
	    (setq needs-checkpointing 0)
	    (fetch-database-entry "DB-list" item)
	    (setq buffer-is-modified 0)
	    (setq line-count 0)
	    (beginning-of-file)
	    (end-of-line)
	    (while (! (eobp))
		   (next-line)
		   (end-of-line)
		   (setq line-count (+ line-count 1))
	    )
	    (if (> line-count 11)
		(progn
		      (setq line-count 11)
		      (setq mode-string "Some lines *BEYOND* window")
		)
		(setq mode-string "All lines within window")
	    )
	    (if (> (window-height) line-count)
		(provide-prefix-argument 
		    (- (window-height) line-count)
		    (shrink-window))
	    )
	    (if (< (window-height) line-count)
		(provide-prefix-argument 
		    (- line-count (window-height))
		    (enlarge-window))
	    )
	    (beginning-of-file)
	)
    )
)
