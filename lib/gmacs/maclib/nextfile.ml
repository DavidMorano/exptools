; LastEditDate="Tue Jun  4 21:57:08 1991"

; next-file - go to next file on argument list
; previous-file - go to previous file on argument list

(progn
    (declare-global &next-file-number)
    (setq-default &next-file-number 0)
    (defun
	  (next-file cf
	      (setq cf (current-file-name))
	      (setq &next-file-number (+ 1 &next-file-number))
	      (if (>= &next-file-number (argc))
		  (progn
			(setq &next-file-number 0)
			(error-message "No more files"))
		  (visit-file (argv &next-file-number)))
	      (if (= cf (current-file-name))
		  (next-file))
	      (novalue))

	  (previous-file cf
	      (setq cf (current-file-name))
	      (setq &next-file-number (- &next-file-number 1))
	      (if (<= &next-file-number 0)
		  (progn
			(setq &next-file-number (argc))
			(error-message "No more files"))
		  (visit-file (argv &next-file-number)))
	      (if (= cf (current-file-name))
		  (previous-file))
	      (novalue))
	  )
)
