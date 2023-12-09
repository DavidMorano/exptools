; LastEditDate="Tue Jun  4 20:56:10 1991"
; Edit 7
; Fri Jul 16 18:05:28 1982

; twenex-like tags package		J. Gosling, November 81
;
; A tag file is a sequence of lines of the following forms:

; ^_filename
; ^Atagline^Bposition

; A tagline/position pair refers to the preceeding file

(declare-global last-search-tag)

(defun
    (goto-tag fn str pos restart
	(setq restart 0)
	(if (! prefix-argument-provided)
	    (progn
		  (setq last-search-tag
			(concat "\^A[^\^B]*" (quote (arg 1 ": goto-tag "))))
		  (setq restart 1)))
	(save-excursion
	    (to-tag-buffer)
	    (if restart (beginning-of-file))
	    (re-search-forward last-search-tag)
	    (beginning-of-line)
	    (re-search-forward "\^A\\([^\^B]*\\)\^B\\(.*\\)")
	    (region-around-match 1)
	    (setq str (region-to-string))
	    (region-around-match 2)
	    (setq pos (- (region-to-string) 300))
	    (save-excursion
		(re-search-reverse "\^_\\(.*\\)")
		(region-around-match 1)
		(setq fn (region-to-string)))
	)
	(visit-file fn)
	(goto-character pos)
	(if (error-occured (search-forward str))
	    (search-reverse ""))
	(beginning-of-line)
	(line-to-top-of-window)
    )

    ; goto-tag-in-buffer
    ; Similar to describe-word-in-buffer
    (goto-tag-in-buffer			; TLH - added function
	(error-occured (forward-character))
	(backward-word)
	(set-mark)
	(forward-word)
	(goto-tag (region-to-string))
    )

    (visit-function func
	(save-window-excursion
	    (goto-tag-in-buffer)
	    (message "Type ^C to go back")
	    (recursive-edit)
	)
    )
)

; auxiliary functions used to create and maintain the tags table
(defun
    (to-tag-buffer
	(temp-use-buffer "*TAG*")
	(if (& (= (buffer-size) 0) (= (current-file-name) ""))
	    (progn
		  (if (error-occured (read-file ".tags"))
		      (progn
			    (write-named-file ".tags")
			    (message "New tag file")))
		  (beginning-of-file)))
    )

    (visit-tag-table tagfn
	(setq tagfn (arg 1 ": visit-tag-table "))
	(save-excursion
	    (temp-use-buffer "*TAG*")
	    (read-file tagfn))
    )

    (find-pos-str*
	(beginning-of-line)
	(setq pos (+ (dot) 0))
	(set-mark)
	(end-of-line)
	(setq str (region-to-string))
    )

    (store-pos-str*
	(insert-character '^A')
	(insert-string str)
	(insert-character '^B')
	(insert-string pos)
	(newline))

    (add-tag
	    (save-excursion pos str fn
		(find-pos-str*)
		(setq fn (current-file-name))
		(to-tag-buffer)
		(beginning-of-file)
		(if (error-occured (re-search-forward
				       (concat "\^_" fn "[^\^_]*")))
		    (progn
			  (beginning-of-file)
			  (insert-character '^_')
			  (insert-string fn)
			  (newline)))
		(store-pos-str*)
		(beginning-of-file)))

    (add-tag* pos str
	(find-pos-str*)
	(save-excursion
	    (temp-use-buffer "*TAG*")
	    (store-pos-str*)))

    (add-all-tags pattern fn
	(setq pattern (arg 1 ": add-all-tags (pattern) "))
	(setq fn (current-file-name))
	(save-excursion
	    (to-tag-buffer)
	    (if (error-occured (search-forward (concat "\^_" fn "\n")))
		(progn
		      (beginning-of-file)
		      (insert-character '^_')
		      (insert-string fn)
		      (newline))
		(progn
		      (set-mark)
		      (while (= (following-char) '^A')
			     (next-line))
		      (erase-region))
	    )
	)
	(save-excursion
	    (error-occured
		(beginning-of-file)
		(while 1
		       (re-search-forward pattern)
		       (add-tag*))))
	(novalue)
    )

    (add-typed-tags* ext pattern
	(setq ext (substr (current-file-name) -2 2))
	(add-all-tags
	    (if
	       (= ext ".l") "^(def"
	       ;(= ext ".c") "^[A-z].*(.*)"		; TLH
	       (| (= ext ".c")
		  (= ext ".h")
		  (= ext ".C")
		  (= ext ".H"))
	       "^[A-z].*(.*)\\|^#[ \t]*define[ \t][ \t]*[A-Za-z_][A-Za-z_]*("
	       (= ext "ml") "^(defun[ \t\n]*("
	       (= ext "ss") "@section\\|@chapter\\|@subsection"
	       (= ext ".p") "function\\|procedure"
	       (error (concat "Can't tag " (current-file-name)))
	    )
	)
    )

    (tag-file fn cur-file		; TLH added cur-file
	(if (is-bound current-file)
	    (setq cur-file current-file)
	    (setq cur-file ""))
	(setq fn (arg 1 ": tag-file (filename) "))
	(message (concat "Tagging " fn))
	(save-window-excursion
	    (error-occured
		(visit-file fn)
		(add-typed-tags*)
		(if (& (!= cur-file fn)	; TLH
		       (= buffer-is-modified 0)); TLH
		    (delete-buffer fn))		; TLH
	    )))

    (recompute-all-tags current-file	; TLH added current-file
	(setq current-file (current-file-name)); TLH
	(save-window-excursion
	    (to-tag-buffer)
	    (beginning-of-file)
	    (error-occured
		(while 1
		       (re-search-forward "\^_\\(.*\\)")
		       (region-around-match 1)
		       (tag-file (region-to-string)))
	    )
	    (write-named-file ".tags")))

    (make-tag-table fns current-file	; TLH added current-file
	(setq fns (arg 1 ": make-tag-table (from filenames) "))
	(setq current-file (current-file-name)); TLH
	(save-window-excursion
	    (temp-use-buffer "*TEMP*")
	    (erase-buffer)
	    (set-mark)
	    (filter-region (concat "ls " fns))
	    (beginning-of-file)
	    (while (! (eobp))
		   (set-mark)
		   (end-of-line)
		   (tag-file (region-to-string))
		   (next-line)
		   (beginning-of-line))
	    (delete-buffer "*TEMP*")
	    (temp-use-buffer "*TAG*")
	    (write-named-file ".tags"))
	(novalue)
    )
)
