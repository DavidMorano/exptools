	;;;;
	;;;; LastEditDate="Tue Apr  9 14:35:23 1991"
	;;;; Written by Tony Hansen.
	;;;;
	;;;; A semi-standardized convention has been created by vi
	;;;; such that invoking the editor as in
	;;;;
	;;;;	vi +n file
	;;;;
	;;;; will place you on line "n" within "file". Similarly,
	;;;;
	;;;;	vi +$ file
	;;;;	vi +/re file
	;;;; and
	;;;;	vi +?re file
	;;;;
	;;;; will go to the last line, and search for the pattern
	;;;; "re" from the beginning and end of "file", respectively.
	;;;;
	;;;; Similarly,
	;;;;
	;;;;	vi +ttag
	;;;;
	;;;; will go to the indicated tag.
	;;;;
	;;;; By adding the following lines to your $HOME/.emacs_pro.ml file,
	;;;;
	;;;;	(autoload "do-plus-args" "doplusargs")
	;;;;	(auto-execute "do-plus-args" "+*")
	;;;;
	;;;; gmacs can also be invoked by any of the above five methods.
	;;;; This macro assumes that argv[1] is the + argument and
	;;;; that argv[2] is the file name.
	;;;;
	;;;; In addition, a number followed by the letter "c" will go
	;;;; forward that number of characters, as in
	;;;;
	;;;;	+35c
	;;;;
	;;;; A number followed by the letter "%" will go to that percentage
	;;;; within the file, as in
	;;;;
	;;;;	+35%
	;;;;
	;;;; A series of mlisp expressions
	;;;;
	;;;;	'+(mlisp-expression)(mlisp-expression)...'
	;;;;
	;;;; can be used and the mlisp expressions will be executed upon
	;;;; entry into the file.
	;;;;

(defun
    (do-plus-args plus-arg second-char rest-of-arg last-char
	(setq plus-arg (argv 1))
	(delete-buffer (current-buffer-name))
	(setq second-char (substr plus-arg 2 1))
	(setq rest-of-arg (substr plus-arg 3 -2))
	(setq last-char (substr plus-arg -1 1))
	(if (= second-char "t")
	    (progn tag-name
		   (setq tag-name rest-of-arg)
		   (if (file-exists ".tags")
		       (load "tags")
		       (file-exists "tags")
		       (load "ctags")
		       (error-message "no .tags or tags file!"))
		   (goto-tag tag-name))
	    (progn
		  (if (> (argc) 2)
		      (visit-file (argv 2))
		      (error-message "no file specified!"))
		  (if (= second-char "/")	; search forward
		      (re-search-forward rest-of-arg)
		      (= second-char "$")	; go to end of file
		      (end-of-file)
		      (= second-char "?")	; search reverse
		      (progn
			    (end-of-file)
			    (re-search-reverse rest-of-arg))
		      (= second-char "(")	; execute mlisp expression
		      (progn
			    (execute-mlisp-line
				(concat "(progn (" rest-of-arg
					")")))
		      (= last-char "%")		; goto percent
		      (progn percent
			     (setq percent (substr plus-arg 2 -2))
			     (provide-prefix-argument goto-percent))
		      (= last-char "c")		; goto char
		      (progn char-number
			     (setq char-number (substr plus-arg 2 -2))
			     (provide-prefix-argument (- char-number 1)
				 (forward-character)))
		      (progn line-number	; goto line
			     (setq line-number (substr plus-arg 2 -1))
			     (provide-prefix-argument (- line-number 1)
				 (next-line)))
		  )
	    )
	)
	(message "")
	(novalue)
    )
)
