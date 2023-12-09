	; LastEditDate="Fri Oct  1 14:15:45 1982"
(defun
)

(defun
    (spell
	  (message
		  (concat "Looking for errors in " (current-file-name)
			  ", please wait..."))
	  (sit-for 0)
	  (save-excursion
	      (if (file-exists ".spell")
		  (compile-it (concat "spell +.spell " (current-file-name)))
		  (compile-it (concat "spell " (current-file-name)))))
	  (error-occured (correct-spelling-mistakes))
	  (message "Done!")
	  (novalue))
)
