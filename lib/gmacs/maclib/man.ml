	;;;; LastEditDate="Fri Oct  1 16:16:50 1982"
(defun
    (manual-entry entry-name
	(setq entry-name (arg 1 ": manual-entry (for) "))
	(save-excursion
	    (pop-to-buffer "man-entry")
	    (setq mode-line-format (concat "   Manual entry for "
					   entry-name
					   "     %M  %[%p%]"))
	    (setq needs-checkpointing 0)
	    (erase-buffer)
	    (set-mark)
	    (filter-region
		(concat "man "
			entry-name
			"| sed -e 's/_//g' -e 's/.//g'"
			" -e '/^[A-Z][A-Z]*([0-9]*).*)$/d'"
			" -e '/^Printed [0-9].*[0-9]$/d'"
		))
	    (beginning-of-file)
	    (while (! (error-occured (re-replace-string "\n\n\n\n*" "\n\n")))
		   (novalue))
	    (if (looking-at "\n\n*")
		(progn
		      (region-around-match 0)
		      (erase-region)))
	)
    )
)
