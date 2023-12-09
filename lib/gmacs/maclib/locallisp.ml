	; LastEditDate="Fri Oct  8 16:10:01 1982"
(load "electric-lisp.ml")
(defun
    (locallisp-mode
	(add-date)
	(electric-lisp-mode))
)
(defun
    (localmlisp-mode
	(add-date)
	(local-bind-to-key "expand-mlisp-variable" "|")
	(use-syntax-table "mlisp")
	(modify-syntax-entry "w    #")
	(electric-mlisp-mode))
)

; add edit date
(defun
    (add-date
	(if (! buffer-is-modified)
	    (save-excursion
		(error-occured
		    (search-forward "LastEditDate=""")
		    (set-mark)
		    (search-forward """")
		    (backward-character)
		    (delete-to-killbuffer)
		    (insert-string (current-time))
		    (setq buffer-is-modified 0)
		))))
)
(novalue)
