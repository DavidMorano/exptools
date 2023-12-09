	;;;; LastEditDate="Tue Jun  4 16:01:36 1991"
	;;;; Written by Tony Hansen.
	;;;; Do a visit on all files of a given name (wildcards accepted)
	;;;; and do a recursive edit on each, one at a time.

    ; Visits all files in a given list, doing a recursive-edit at each.

(defun
    (for-all-files files file
	(save-window-excursion
	    (setq files
		  (get-tty-string "Files to visit? "))
	    (execute-monitor-command (concat "ls " files))
	    (temp-use-buffer "  Temp Command")
	    (setq needs-checkpointing 0)
	    (erase-buffer)
	    (yank-buffer "Command execution")
	    (beginning-of-file)
	    (while (! (eobp))
		  (set-mark)
		  (end-of-line)
		  (setq file (region-to-string))
		  (erase-region)
		  (delete-next-character)
		  (if (error-occured
			  (visit-file file))
		      (message "New file: file"))
		  (message (concat "For file = " file))
		  (recursive-edit)
		  (temp-use-buffer "  Temp Command")
		  (beginning-of-file)))
	(message "Done with for!")
    )

	; Implements a 'for' call similar to the shell 'for' loop.

	; NOT DONE YET!!!!

;(defun
;    (for
;	(if (interactive)
;	    (progn fn varname counter
;		   (setq counter 0)
;		   (setq fn
;			 (get-tty-string "Mlisp function to be executed: "))
;		   (setq varname
;			 (get-tty-string "Variable name to be changed: "))
;		   (declare-global varname)
;		   (while
;			 (setq counter (+ counter 1))
;			 (!= ""
;			     (set varname
;				   (get-tty-string
;				       (concat "Value " counter
;					       " for " varname "? "))))
;			 (execute-mlisp-line fn)))
;	    (progn varname argcounter
;		   (setq varname (arg 1))
;		   (declare-global varname)
;		   (while (< argcounter (nargs))
;			  (set varname (arg argcounter))
;			  (arg (nargs))
;			  (setq argcounter (- argcounter 1))))
;	))
;)

)
