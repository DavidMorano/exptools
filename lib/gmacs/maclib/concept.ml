	;;;; LastEditDate="Mon Jun 13 12:29:35 1983"
 				; The following commands support
				; the C108 cursor keys.
  				; The command character of the keyboard must
				; be changed to ^_ (control-underbar) before
				; these will work.  This is done by gmacs to
				; C108 terminals automatically.

(bind-to-key "previous-line" ";")
(bind-to-key "next-line" "<")
(bind-to-key "backward-character" ">")
(bind-to-key "forward-character" "=")
(bind-to-key "next-page" "-")
(bind-to-key "previous-page" ".")
(bind-to-key "forward-sentence" "[")
(bind-to-key "backward-sentence" "\\")
(bind-to-key "forward-word" "]")
(bind-to-key "backward-word" "_")
(bind-to-key "beginning-of-window" "?")

				; The following function aids in the setting
				; up of Concept programmable function keys.
				; It prompts for appropriate information,
				; then either downloads the given key or
				; inserts the code into the current buffer.
(defun 
    (setup-fn-key   fn-key first-char len k t msg n m code ans done
	(setq fn-key (arg 1 "Function key *name* (fn  or  Fn): "))
	(setq first-char (substr fn-key 1 1))
	(if (& (!= first-char "f") (!= first-char "F"))
	    (error-message "First character must be 'f' or 'F' -- aborting!"))
	(setq n (substr fn-key 2 -1))
	(if (| (< n 1) (> n 14))
	    (error-message "Number must be in range 1 to 14, inclusive."
		" -- aborting!"))
	(setq m (+ '$' n))
	(if (= first-char "f")
	    (setq m (+ m 16)))
	(if (& (= first-char "F") (> n 11))
	    (setq m (+ m 19)))
	(setq k (char-to-string m))
	(setq msg (arg 2 "Enter code to be loaded into key: "))
	(setq ans (arg 3 "Enter mode (t=transmit, x=execute): "))
	(if (& (!= ans "t") (!= ans "x"))
	    (error-message "Mode must be 't' or 'x' -- aborting!"))
	(if (= ans "t")
	    (setq t "\"")
	    (setq t "#")
	)
	(setq len (char-to-string (+ ' ' (length msg))))
	(setq code (concat "\e4" len k t msg))
	(setq done 0)
	(while (! done)
	       (setq ans (arg 4 "Download key? Insert into editor? or Both? (d i or b): "))
	       (if (| (= ans "d") (= ans "b"))
		   (progn 
			  (send-string-to-terminal code)
			  (message (concat "Key " fn-key " downloaded!"))
			  (setq done 1)
		   )
	       )
	       (if (| (= ans "i") (= ans "b"))
		   (progn 
			  (insert-string code)
			  (setq done 1))
	       )
	)
	(novalue)
    )
)
(novalue)
