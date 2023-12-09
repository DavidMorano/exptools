	;;;; LastEditDate="Tue Jun  4 15:19:55 1991"
(extend-database-search-list "subr-names"
	"$TOOLS/lib/gmacs/databases/quickinfo")
(error-occured
    (extend-database-search-list "subr-names"
	(concat (getenv "HOME") "/.subr-names")))

(defun
    (describe-word-in-buffer subr-name
	(if (> prefix-argument 1)
	    (progn
		(error-occured (forward-character))
		(backward-word)
		(set-mark)
		(forward-word)
		(edit-description (region-to-string)))
	    (progn
		(save-excursion
		    (error-occured (forward-character))
		    (backward-word)
		    (set-mark)
		    (forward-word)
		    (setq subr-name (region-to-string))
		    (temp-use-buffer "subr-help")
		    (setq needs-checkpointing 0)
		    (erase-buffer)
		    (if (error-occured
			    (fetch-database-entry "subr-names" subr-name))
			(error-message (concat "No help for " subr-name))
			(progn
			    (beginning-of-file)
			    (set-mark)
			    (end-of-line)
			    (message (region-to-string))))
		)
	    )
	)
	(novalue)
    )
    
    (edit-description
	(setq edit-name (arg 1 ": edit-description (of routine) "))
	(pop-to-buffer "Edit description")
	(erase-buffer)
	(if (error-occured (fetch-database-entry "subr-names" edit-name))
	    (message "New entry."))
	(setq mode-string (concat "  Editing database entry for " edit-name))
	(setq user-mode-line 1)
	(local-bind-to-key "replace-db-entry" "\^X\^S")	; ^X^S
	(local-bind-to-key "replace-db-entry" "\^X\^F")	; ^X^F
	(local-bind-to-key "replace-db-entry" "\^X\^W")	; ^X^W
	(local-bind-to-key "replace-db-entry" "\^X\^C")	; ^X^C
	(local-bind-to-key "replace-db-entry" "\^C")	; ^C
	(novalue)
    )
    
    (replace-db-entry
	(put-database-entry "subr-names" edit-name)
	(delete-window)
    )
)

(declare-global edit-name)
