	;;;; LastEditDate="Thu Feb 27 00:19:29 1992"
; This is an attempt at a dired package.

    (declare-global Dired-keymap-defined Dired-directory)
    (setq Dired-keymap-defined 0)
    (setq Dired-directory (working-directory))

(defun
    (dired directory
	   (save-window-excursion
	       (setq directory (arg 1 (concat ": dired on directory? ["
					      Dired-directory "] ")))
	       (if (= directory "")
		   (setq directory Dired-directory))
	       (if (= "/" (substr directory -1 1))
		   (setq directory (substr directory 1 -1)))
	       (setq Dired-directory directory)
	       (pop-to-buffer "dired")
	       (use-local-map "&dired-keymap")
	       (setq mode-line-format
		     (concat "  Editing  directory:  " directory
			     "      %M   %[%p%]"))
	       (erase-buffer)  (set-mark)
	       (message (concat "Getting contents of " directory))
	       (sit-for 0)
	       (filter-region (concat "/bin/ls -l " directory))
	       ;(filter-region (concat "/usr/ucb/ls -l " directory)); TLH
	       (beginning-of-file)
	       (if (looking-at "total")
		   (progn
			 ; delete total
			 (kill-to-end-of-line) (kill-to-end-of-line)
			 (beginning-of-file)
			 ; remove all directory listings
			 (re-replace-string "^d.*\n" "")
			 ; put a space at beginning of each line
			 (beginning-of-file)
			 (re-replace-string "^" " ")
			 (beginning-of-file)
		   )
		   (progn
			 (re-replace-string "\n" "; ")
			 (end-of-file)
			 (error-message (region-to-string))
		   )
	       )
	       (message "Type ^C to exit, ? for help")
	       (save-excursion (recursive-edit))
	       (&dired-done)
	       (novalue)
	   )
    )
    
    (&dired-Mark-file-deleted
	(if (= 0 (buffer-size))
	    (error-message "dired already done!")
	    (prefix-argument-loop
		(beginning-of-line)
		(if (looking-at " d")
		    (error-message "Can't delete a directory with dired"))
		(delete-next-character)
		(insert-string "D")
		(next-line)
		(beginning-of-line)
	    )
	)
    )
    
    (&dired-summary
	(message
		"d-elete, u-ndelete, q-uit, r-emove, e,v-isit, n-ext, p-revious, ?-help")
    )
    
    (&dired-UnMark-file-deleted
	(if (= 0 (buffer-size))
	    (error-message "dired already done!")
	    (prefix-argument-loop
		(beginning-of-line)
		(delete-next-character)
		(insert-string " ")
		(next-line)
		(beginning-of-line)
	    )
	)
    )
    
    (&dired-backup-unmark
	(if (= 0 (buffer-size))
	    (error-message "dired already done!")
	    (! (bobp))
	    (prefix-argument-loop 
		(previous-line)
		(beginning-of-line)
		(delete-next-character)
		(insert-string " ")
		(beginning-of-line)
	    )
	)
    )
    
    (&dired-examine ans
	(save-excursion
	    (error-occured
		(visit-file (&dired-get-fname))
		(message "Type ^C to return to DIRED")
		(recursive-edit)
	    )
	)
    )
    
    (&dired-remove
	(prefix-argument-loop 
	    (beginning-of-line)
	    (kill-to-end-of-line) (kill-to-end-of-line)
	)
    )
    
    (&dired-get-fname
	(save-excursion
	    (beginning-of-line)
	    (goto-character (+ (dot) 55))
	    ;(goto-character (+ (dot) 43))		; TLH
	    (set-mark)
	    (end-of-line)
	    (concat Dired-directory "/" (region-to-string))
	)
    )
    
    (&dired-done ans
	(beginning-of-file)
	(re-replace-string "^ .*\n" "")
	(if (!= 0 (buffer-size))
	    (progn
		  (message
			  "? [y-go through marked files; d-delete all marked files; Anything else quits]")
		  (setq ans (get-tty-character))
		  (if (| (= ans 'd') (= ans 'D'))
		      (progn
			    (while
				  (! (eobp))
				  (progn thisfile
					 (setq thisfile (&dired-get-fname))
					 (if (unlink-file thisfile)
					     (progn
						   (message "Couldn't delete " thisfile "!")
						   (sit-for 5)))
					 (next-line)
					 (beginning-of-line)))
			    (delete-buffer "dired"))
		      (| (= ans 'y') (= ans 'Y'))
		      (progn
			    (while (! (eobp))
				   (if (= (following-char) 'D')
				       (progn thisfile ans
					      (setq thisfile (&dired-get-fname))
					      (message (concat "Delete " thisfile "?"))
					      (setq ans (get-tty-character))
					      (if (| (= ans 'y') (= ans 'Y'))
						  (if (unlink-file thisfile)
						      (progn
							    (message "Couldn't delete it!")
							    (sit-for 2))))
				       )
				   )
				   (next-line)
			    )
			    (delete-buffer "dired")
		      )
		      (progn
			    (delete-buffer "dired")
			    (error-message "Nothing deleted")
		      )
		  )
	    )
	)
	(message "Dired says ""Adios""")
	(novalue)
    )
)    

(progn loop
    (save-excursion
	(temp-use-buffer "dired")
	(define-keymap "&dired-keymap")
	(use-local-map "&dired-keymap")
	(setq loop 0)
	(while (<= loop 127)
	       (local-bind-to-key "&dired-summary" loop)
	       (setq loop (+ loop 1))
	)
	(setq loop '0')
	(while (<= loop '9')
	       (local-bind-to-key "meta-digit" loop)
	       (setq loop (+ loop 1))
	)
	(local-bind-to-key "&dired-Mark-file-deleted" "d")
	(local-bind-to-key "&dired-Mark-file-deleted" "D")
	(local-bind-to-key "&dired-Mark-file-deleted" "")
	(local-bind-to-key "&dired-backup-unmark" "\0177")
	(local-bind-to-key "previous-line" "\^H")
	(local-bind-to-key "previous-line" "p")
	(local-bind-to-key "previous-line" "P")
	(local-bind-to-key "previous-line" "\^P")
	(local-bind-to-key "next-line" "n")
	(local-bind-to-key "next-line" "N")
	(local-bind-to-key "next-line" "\^N")
	(local-bind-to-key "next-line" 13)
	(local-bind-to-key "next-line" 10)
	(local-bind-to-key "next-line" " ")
	(local-bind-to-key "argument-prefix" "\^U")
	(local-bind-to-key "previous-window" "\^Xp")
	(local-bind-to-key "previous-window" "\^XP")
	(local-bind-to-key "next-window" "\^Xn")
	(local-bind-to-key "next-window" "\^XN")
	(local-bind-to-key "delete-window" "\^Xd")
	(local-bind-to-key "delete-window" "\^XD")
	(local-bind-to-key "delete-other-windows" "\^X1")
	(local-bind-to-key "&dired-examine" "\^X\^V")
	(local-bind-to-key "next-page" "\^V")
	(local-bind-to-key "previous-page" "\ev")
	(local-bind-to-key "previous-page" "\eV")
	(local-bind-to-key "beginning-of-file" "\e<")
	(local-bind-to-key "end-of-file" "\e>")
	(local-bind-to-key "&dired-UnMark-file-deleted" "u")
	(local-bind-to-key "&dired-UnMark-file-deleted" "U")
	(local-bind-to-key "exit-emacs" "\^C")
	(local-bind-to-key "exit-emacs" "q")
	(local-bind-to-key "exit-emacs" "Q")
	(local-bind-to-key "&dired-examine" "e")
	(local-bind-to-key "&dired-examine" "E")
	(local-bind-to-key "&dired-examine" "v")
	(local-bind-to-key "&dired-examine" "V")
	(local-bind-to-key "&dired-remove" "r")
	(local-bind-to-key "&dired-remove" "R")
    )
)
