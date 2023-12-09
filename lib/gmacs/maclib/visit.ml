	;;;; LastEditDate="Wed Oct 20 17:00:28 1982"
	;;;; Written by Tony Hansen.
	;;;;
	;;;; new-visit-file, ^X-^V
	;;;;
	;;;; This is a replacement for the normal visit-file ^X-^V command.
	;;;; Used normally, there is no visible difference.
	;;;; However, if a numeric argument is given, as in ^U-^X-^V,
	;;;; then a list of filenames is accepted (wildcards allowed) and a
	;;;; visit-file is done on each. The cursor is left in the first file.

(defun
    (new-visit-file
	(if prefix-argument-provided			; ^U-^V
	    (progn
		  wildcard-filename			; list of names
		  (setq wildcard-filename		; get name list
			(get-tty-string			; ....
			    "Visit file [wildcards allowed]: "))
		  (execute-monitor-command		; expand out names
		      (concat "ls " wildcard-filename))	; ....
		  (temp-use-buffer "Command execution")	; go to names
		  (setq needs-checkpointing 0)		; ....
		  (beginning-of-file)			; start at first one
		  (if (looking-at ".* not found")	; oops, not there?
		      (error-message wildcard-filename	; tell user
			  " not found!")
		      (progn
			    first-file			; name of 1st file
			    filelist			; save expanded list
			    (setq filelist "")		; ....
			    (set-mark)			; save first name
			    (end-of-line)		; ....
			    (setq first-file		; ....
				  (region-to-string))	; ....
			    (save-window-excursion	; loop thru names
				file			; current file name
				(while (! (eobp))
				       (beginning-of-file); get name
				       (set-mark)	; ....
				       (end-of-line)	; ....
				       (setq file	; ....
					     (region-to-string))
				       (setq filelist	; save name
					     (concat filelist file " "))
				       (erase-region)	; get rid of it
				       (delete-next-character); ....
				       (visit-file file); go to it
				       (temp-use-buffer	; return
					   "Command execution")))
			    (visit-file first-file)	; go to 1st name
			    (message "Files: " filelist); tell user
		      )))
	    (visit-file					; plain visit, no
		(get-tty-string "Visit file: ")))	;     argument given
	(novalue))
    
)
