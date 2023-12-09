; ctags-to-tags
; - take a file created by the BSD ctags(1) program and change it into the
;   format usable by the emacs tags facility.
;
; Tony Hansen, 1983

; ctags files are made of lines of the form:
;	function-name\tfilename\t?regular-expression?
; 
; emacs tag files are of the form
;	^_filename
;	^Aregular-expression^Bposition
;

(defun
    (ctags-to-tags tag-file new-tag-file
	(setq tag-file (arg 1 "Name of ctags file? [tags is default] "))
	(if (= tag-file "")
	    (setq tag-file "tags"))
	(setq new-tag-file (arg 2 "New tag file name [.tags by default] "))
	(if (= new-tag-file "")
	    (setq new-tag-file ".tags"))
	(message "Working....")
	(sit-for 0)

	(save-window-excursion
	    (switch-to-buffer "*temp-ctag*")
	    (setq needs-checkpointing 0)
	    (erase-buffer)
	    (insert-file tag-file)

	    ; change over-all format from
	    ;	function-name\tfilename\t?regular-expression?
	    ;	...
	    ; into
	    ;	^_filename
	    ;	^A?regular-expression?^Bfunction-name
	    ;	^_filename
	    ;	^A?regular-expression?^Bfunction-name
	    ;	...
	    ; sorted by filenames.
	    (progn
		  (beginning-of-file)
		  (re-replace-string
		      "^\\([^\t]*\\)\t\\([^\t]*\\)\t\\(.*\\)$"
		      "\^_\\2\^A\\3\^B\\1")
		  (set-mark)
		  (end-of-file)
		  (filter-region "sort")
		  (beginning-of-file)
		  (re-replace-string "\\(\^_[^\^A]*\\)\^A" "\\1\n\^A"))

	    ; Get rid of extra file names.
	    ; from
	    ;	^_filename
	    ;	^A?regular-expression?^Bfunction-name
	    ;	^_filename
	    ;	^A?regular-expression?^Bfunction-name
	    ;	...
	    ; into
	    ;	^_filename
	    ;	^A?regular-expression?^Bfunction-name
	    ;	^A?regular-expression?^Bfunction-name
	    ;	^A?regular-expression?^Bfunction-name
	    ;	...
	    (progn last-file current-file
		   (beginning-of-file)
		   (setq last-file "")
		   (while (! (error-occured (search-forward "\^_")))
			  (set-mark)
			  (end-of-line)
			  (setq current-file (region-to-string))
			  (if (= current-file last-file)
			      (progn
				    (beginning-of-line)
				    (kill-to-end-of-line)
				    (delete-next-character))
			      (setq last-file current-file))))

	    ; Change relative filename references into absolute ones.
	    (progn
		  (beginning-of-file)
		  (re-replace-string
		      "\^_\\([^/]\\)"
		      (concat "\^_" (working-directory) "\\1")
		  ))

	    ; change ctags ?regular-expression? lines into .tags format
	    ; and change function-name into absolute position reference
	    ;
	    ; from
	    ;	^_filename
	    ;	^A?regular-expression?^Bfunction-name
	    ;	^A?regular-expression?^Bfunction-name
	    ;	^A?regular-expression?^Bfunction-name
	    ;	...
	    ; into
	    ;	^_filename
	    ;	^Aregular-expression^Blocation
	    ;	^Aregular-expression^Blocation
	    ;	^Aregular-expression^Blocation
	    ;	...
	    (progn current-file last-file
		   (setq current-file "")
		   (beginning-of-file)
		   (if (! (looking-at "\^_"))
		       (error-message "Missing file name!"))
		   (while (! (eobp))
			  ; looking at a file name?
			  (if (looking-at "\^_\\(.*\\)")
			      (progn
				    (if (!= current-file "")
					(save-window-excursion
					    (visit-file current-file)
					    (if (! buffer-is-modified)
						(delete-buffer (current-buffer-name)))))
				    (region-around-match 1)
				    (setq current-file (region-to-string)))

			      ; looking at a function name?
			      (looking-at "\^A\\([^\^B]*\\)\^B\\(.*\\)")
			      (progn pattern function-name location
				     (region-around-match 1)
				     (setq pattern (region-to-string))
				     (region-around-match 2)
				     (setq function-name (region-to-string))
				     (beginning-of-line)
				     (if (looking-at "\^A.*main.*\^BM.*")
					 (setq function-name "main"))
				     ; strip '?^' or '/^' from beginning and
				     ; strip '$?' or '$/' from end.
				     (if (= "?" (substr pattern 1 1))
					 (setq pattern (substr pattern 2 -1))
					 (= "/" (substr pattern 1 1))
					 (setq pattern (substr pattern 2 -1)))
				     (if (= "^" (substr pattern 1 1))
					 (setq pattern (substr pattern 2 -1)))
				     (if (= "?" (substr pattern -1 1))
					 (setq pattern (substr pattern 1 -1))
					 (= "/" (substr pattern -1 1))
					 (setq pattern (substr pattern 1 -1)))
				     (if (= "$" (substr pattern -1 1))
					 (setq pattern (substr pattern 1 -1)))
				     (save-excursion
					 (visit-file current-file)
					 (if (error-occured (re-search-forward pattern))
					     (if (error-occured (re-search-reverse pattern))
						(if (error-occured (re-search-forward function-name))
						   (if (error-occured (re-search-reverse function-name))
						       (error-message "Cannot find " function-name " in " current-file)))))
					 (beginning-of-line)
					 (setq location (+ (dot) 0)))
				     (beginning-of-line)
				     (kill-to-end-of-line)
				     (insert-string (concat "\^A" pattern
							    "\^B" location))
				     (end-of-line))
			      (error-message "Mal-formed tags line")
			  )
			  (error-occured (forward-character))))

	    (write-named-file new-tag-file))
	(delete-buffer "*temp-ctag*")
	(message "Done!")
	(novalue)
    )
)
