	;;;; LastEditDate="Mon Jun  3 23:26:34 1991"
	;;;; Written by Tony Hansen.
	;;;;
	;;;; Take an mlisp file and invoke mlispcc on it.
	;;;;
	;;;; By convention, this file name should be the file's
	;;;; name without the .ml extension, and you will get that
	;;;; if you just type return.
	;;;;
	;;;; It is assumed that dot starts in the file you want
	;;;; squeezed down.

(defun
    (mlispcc
	filename					; current file name
	sfilename					; squeezed file name
	default-sfilename				; default squeezed fn

	(setq filename (current-file-name))		; fill in values
	(save-restriction old-mod-flag			; get squeezed file name
	    (setq old-mod-flag buffer-is-modified)	; ....
	    (set-mark)					; ....
	    (narrow-region)				; ....
	    (insert-string filename)			; ....
	    (error-occured (search-reverse "/"))	; .... find basename
	    (if (error-occured (search-forward "."))	; .... any suffix?
		(setq default-sfilename "No default")	; ....
		(progn (end-of-line)			; .... remove suffix
		       (search-reverse ".")		; ....
		       (setq default-sfilename		; ....
			     (region-to-string))))	; ....
	    (erase-buffer)				; .... clean up
	    (setq buffer-is-modified old-mod-flag))	; ....
	(setq sfilename					; .... ask user
	      (get-tty-string				; ....
		  (concat "File to write out to ["	; ....
			  default-sfilename "]? ")))	; ....
	(if (= sfilename "")				; .... give default
	    (if (= default-sfilename "No default")	; ....
		(setq sfilename "/dev/null")		; ....
		(setq sfilename default-sfilename)))	; ....
	(message "Compiling...." filename " -> " sfilename)
	(sit-for 0)
	(if buffer-is-modified
	    (write-current-file))
	(execute-monitor-command
	    (concat "$TOOLS/lib/gmacs/bin/mlispcc " filename " " sfilename))
	(message filename " >>> " sfilename "!")
	(novalue)
    )
)
