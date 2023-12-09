 		; LastEditDate="Mon Jun 16 14:16:16 1986" 
; 
; Enhanced history interactive shell macros for use with the special
; interactive shell hack on system III
; 
; 	written by Jishnu Mukerji	11.24.82
; 
; 
(declare-global last-line Shell-exists Shell-prompt)
; 	last-line holds the last command line after cleaning up
; 	Shell-exist = 1 if shell exists, 0 otherwise.
; 	Shell-prompt is the current shell prompt
(declare-global histlines maxhistlines)
; 	histlines is the number of commands that have been saved in history
; 	maxhistlines is the high water mark for number of saved commands.
(declare-global commlines)
; 	commlines is the number of commands that are to be found in .commands
(declare-global last-com last-hist-mode last-dot)
; 	last-com holds the last command that had a ! prefix
; 	last-hist-mode is 0 if last-com is numeric, non-zero otherwise
; 	last-dot holds the position in history buffer from where the last
; 		command was picked up.
(declare-global gemacs-library-directory)
(setq-default maxhistlines 100)		; maximum size of history
(setq histlines 0)			; initial size of history
(setq commlines 0)
(setq-default shell-version "Release 1.1.jm1")

(defun				; this function is called whenever 
    (pr-newline			; a ^m is hit in the shell buffer
	(end-of-line)
	(if (! (eobp))			; if not at the end of buffer
	    (progn com			; pick up the line after
		   (set-mark)		; dropping leading prompts and
		   (beginning-of-line)	; spaces, tabs and numerics
		   (narrow-region)
		   (while 
		     (! (error-occured 
			(search-forward Shell-prompt))
		     )
		     (novalue)
		   )
		   (error-occured (re-search-forward "[0-9]*[ \t]*"))
		   (set-mark)
		   (end-of-line)
		   (setq com (region-to-string))
		   (widen-region)
		   (end-of-file)
		   (set-mark)
		   (insert-string com) 	; and stick it at the end of the
	    )				; buffer
	    (progn 		; else remove space preceding the command
		(exchange-dot-and-mark)
		(error-occured (re-search-forward "\\=[ \t]*"))
		(exchange-dot-and-mark)
	    )
	)
	(while
	      (> (buffer-size) 10000)		; limit size of buffer
	      (progn				; ...
		  (beginning-of-file)		; ...
		  (provide-prefix-argument 500	; ...
		      (delete-next-character)))); ...
	(end-of-file)				; leave copy at end of buffer,
	(setq last-line (region-to-string))	; pick up command line
	(if (= "!" (substr last-line 1 1))	; do history stuff
          (progn 
	    (exchange-dot-and-mark)
	    (kill-to-end-of-line)
	    (set-mark)
	    (if (= 1 (length last-line))
		(setq last-line "!1"))
	    (history-shell (substr last-line 2 (length last-line)))
	  )
	(if (= "^" (substr last-line 1 1))	; do history repeat stuff
	  (progn 
	    (beginning-of-line)
	    (search-forward "^")
	    (backward-character)
	    (kill-to-end-of-line)
	    (set-mark)
	    (history-shell "")
	  )
	  (progn shelldir		; now do shell stuff
	    (check-shell-command)	; first eliminate restricteds
	    (if (= last-line "history")	; then list history
		(list-shell-history "*Shellhistory*" histlines)
	    (if (= last-line "commands") ;  then list commands
		(list-shell-history "*Shellcommands*" commlines)
	    ))
	    (if (| (= last-line "commands")
		  (| (= last-line "history") (= 0 (length last-line))))
		(setq last-line "")
				; if an useful command then save in history
	        (subshell-save-history last-line)
	    )
	    (newline)
 	    (sit-for 0)		; then process the unix command
				; First see if it is a cd
 				; and if so treat specially
	    (if (& (= "cd" (substr last-line 1 2))
		   (< (length last-line) 4)
		)
		(error-occured (cd "$HOME"))
	        (if (= "cd " (substr last-line 1 3))
	          (error-occured 
		    (cd (substr last-line 4 (length last-line)))
	          )
	        )
	    )
 				; then submit the command to unix shell
	    (subshell last-line)
 				; if it was a PS1= then update prompt
	    (if (= "PS1=" (substr last-line 1 4))
		(setq Shell-prompt (getenv "PS1"))
	    )
	    (set-mark)
	  ))
	)
    )
)

(defun
    (interactive-shell		; initialize interactive shell
      (pop-to-buffer "Newshell")
      (if (= Shell-exists 0)	; if a shell does not already exist
       (progn 			; then make one
	(shell-read-in (concat (getenv "HOME") "/.commands")
		"*Shellcommands*")
	(shell-read-in (concat (getenv "HOME") "/.shellhist")
		"*Shellhistory*")
	(shell-read-in (concat gemacs-library-directory "/Shellrestrict")
		"*Shellrestrict*")
	(setq histlines (shell-lines-in-buf "*Shellhistory*"))
	(setq commlines (shell-lines-in-buf "*Shellcommands*"))
        (use-abbrev-table "shell")
        (setq abbrev-mode 1)
	(setq mode-line-format  (concat 
	  ">\^IEmacs Interactive Shell\^I\^I - %p - \^I " shell-version))
        (define-local-abbrev "~" (getenv "HOME"))
        (use-syntax-table "shell")
        (modify-syntax-entry "w    ~")
	(setq Shell-prompt (getenv "PS1"))
	(setq needs-checkpointing 0)
	(local-bind-to-key "pr-newline" '^m')
	(local-bind-to-key "send-eot" '')
	(local-bind-to-key "send-int-signal" '\177')
	(local-bind-to-key "send-quit-signal" '^\')
;	(local-bind-to-key "grab-last-line" (+ 128 '='))
	(setq Shell-exists 1)
	(subshell "")		; this is where the shell gets created
	(novalue)
       )
      )
      (end-of-file)
    )
)

(defun				; function for logging out of the shell
    (send-eot			; the shell buffer is deleted by
				; exit-subshell, but history is not removed
				; logging out happens only if this function
				; is invoked at the end of the buffer
	(if (eobp)
	  (progn 
	    (save-excursion 
	      (temp-use-buffer "*Shellhistory*")
	      (write-named-file (concat (getenv "HOME") "/.shellhist"))
	    )
	    (exit-subshell)
	    (setq Shell-exists 0)
	    (delete-buffer "*Shellhistory*")
	    (delete-buffer "*Shellrestrict*")
	    (delete-buffer "*Shellcommands*")
	    (error-occured (delete-buffer "Shelltemp"))
	  )
	  (delete-next-character)
	)
    )
)

(defun				; function for sending an interrupt to the
				; shell
    (send-int-signal
	(interrupt-subshell)
	(sit-for 10)
	(read-subshell)
))

(defun				; function for sending a quit signal to the
				; shell
    (send-quit-signal
	(signal-quit-subshell)
	(sit-for 10)
	(read-subshell)
))


(defun				; function to insert the last-line at the
				; end of the shell buffer. used by the
				; history stuff.
    (grab-last-line
      (save-excursion 
	(temp-use-buffer "Newshell")
	(end-of-file)
	(set-mark)
	(insert-string last-line)
      )
    )
)

(defun				; Wonder why this is here! didn't have the
				; heart to remove it although it is not
				; really used anywhere
    (shell-cd
	(novalue)))

(defun 
    (copy-line			; copies a line from the current buffer into
				; the variable last-line
	(beginning-of-line)
	(set-mark)
	(end-of-line)
	(setq last-line (region-to-string))
    )
)

(defun 				; saves the given argument in history buffer
				; truncates the buffer by one line if it
				; grows bigger than maximum size
    (subshell-save-history
      (if (> (length (arg 1)) 0)
	(save-excursion 
	    (temp-use-buffer "*Shellhistory*")
	    (if (>= histlines maxhistlines) 
		(progn 
		    (end-of-file)(previous-line)(beginning-of-line)
		    (kill-to-end-of-line)(kill-to-end-of-line)
		    (setq histlines (- histlines 1))
		)
	    )
	    (beginning-of-file)
	    (insert-string (arg 1))(newline)
	    (setq histlines (+ histlines 1))
	)
      )
    )
)

(defun 
    (history-shell hist-line-number
; invoked by beginning a command line with a !
; the rest of the line is then interpreted as follows:
; if there is nothing else then the previous ! line is repeated
; 	without moving dot to the beginning of the buffer
; if the line contains any alphabetics then a search back is done in the 
; 	history buffer for the first match of the pattern starting at
; 	the beginning of line and if found the line is grabbed back
; if the line contains no alphabetic then it is interpreted as a number N
; 	and the Nth previous command is grabbed back from history
; 
; For historical reasons hist-line-number holds the rest of the !line
; 
	(save-excursion 
	    (temp-use-buffer "*Shellhistory*")
	    (setq hist-line-number 
		(arg 1)
	    )
	    (if (= 0 (length hist-line-number))
	     (progn 
	      (if (= last-hist-mode 0)	; last was a number
		(progn 
		  (setq hist-line-number (+ last-com 1))
		  (if (> hist-line-number maxhistlines)
		    (setq hist-line-number (- hist-line-number 1)))
		)
		(progn 			; last was a string
		  (setq hist-line-number last-com)
		)
	      )
	     )
	     (progn 
	       (beginning-of-file)
	       (set-mark)
	       (setq last-dot (mark))
	     )
	    )
	    (setq last-com hist-line-number)
	    (end-of-file)
	    (set-mark)(narrow-region)
	    (insert-string hist-line-number)
	    (if (error-occured (re-search-reverse "[A-z]"))
				; It is a pure number
		(progn 
		    (setq last-hist-mode 0)
		    (erase-buffer)(widen-region)
		    (if (<= hist-line-number histlines)
		      (progn 
		        (goto-line hist-line-number)
			(set-mark)
			(setq last-dot (mark))
			(copy-line)
			(grab-last-line)
		      )
		      (progn 
			(message "Asking for prehistoric line!")
			(sit-for 10)
		      )
		    )
		)
				; It is a string to be searched for
		(progn 
		    (erase-buffer)(widen-region)
		    (setq last-hist-mode 1)
		    (goto-character last-dot)
		    (if (error-occured 
			(re-search-forward (concat "^" hist-line-number)))
		      (progn 
			(message "Asking for non-existent command line!")
			(sit-for 10)
		      )
		    		; found it so grab it
		      (progn 
			(set-mark)
			(setq last-dot (mark))
			(copy-line)
			(grab-last-line)
		      )
                    )
		)
	    )
	)
	(novalue)
    )
)

(defun 				; function to list the history buffer
				; implements the history command
 				; prompts for number of commands
 				; if a number is specified and it is less
				; than the current size (# of lines) of the
				; history buffer then it prints that many
				; lines, otherwise it prints the whole
				; history buffer
    (list-shell-history line-no no-of-lines
	(newline)
	(save-excursion 
	    (temp-use-buffer "Shelltemp")
	    (setq needs-checkpointing 0)
	    (erase-buffer)
	    (setq no-of-lines (get-tty-string "Number of commands: "))
	    (if (= 0 (length no-of-lines))(setq no-of-lines (arg 2)))
	    (if (> no-of-lines (arg 2))(setq no-of-lines (arg 2)))
	    (yank-buffer (arg 1))
	    (beginning-of-file)
	    (if (< no-of-lines (arg 2))
	      (progn 
		(goto-line no-of-lines)
		(next-line)
		(set-mark)
		(end-of-file)
		(kill-region)
	      )
	    )
	    (beginning-of-file)
	    (setq line-no 1)
	    (insert-string (concat line-no "\t"))
	    (while (! (eobp))
		(setq line-no (+ line-no 1))
		(next-line)
		(if (! (eobp))
		  (progn 
		    (beginning-of-line)
		    (insert-string (concat line-no "\t"))
		    (novalue)
		  )
		)
	    )
	)
	(yank-buffer "Shelltemp")
    )
)

(defun 				; function to check for restricted commands
    (check-shell-command this-command not-restricted
	(setq not-restricted 0)
 	(save-excursion 
	    (temp-use-buffer "Shelltemp")
	    (setq needs-checkpointing 0)
	    (erase-buffer)
	    (insert-string last-line)
	    (beginning-of-file)(set-mark)
	    (error-occured (forward-word))
	    (setq this-command (region-to-string))
	    (temp-use-buffer "*Shellrestrict*")
	    (beginning-of-file)
	    (if (> (length this-command) 0)
	      (if (error-occured 
		(re-search-forward (concat "^" this-command)))
		(progn 
		    (setq not-restricted 1)
		)
		(progn tempword
		    (beginning-of-line)
		    (set-mark)
		    (end-of-line)
		    (setq tempword (region-to-string))
		    (if (!= this-command tempword)
			(setq not-restricted 1)
		    )
		)
	      )
	      (setq not-restricted 1)
	    )
	)
	(end-of-file)
	(if (! not-restricted)
	    (progn 
		(insert-string (concat "\n"
			this-command " not permitted in this shell")
		)
		(setq last-line "")
	    )
	)
	(set-mark)
    )
)

(defun 
    (shell-lines-in-buf n m
	(save-excursion 
	    (temp-use-buffer (arg 1))
	    (beginning-of-file)
	    (setq n 0)
	    (while (! (error-occured (search-forward "\n")))
		(setq n (+ n 1))
	    )
	)
	(setq m n)
    )
)

(defun 				; invoked as
				; shell-read-in filename buffername
				; creates buffer and reads in file and
				; then detaches file from buffer
    (shell-read-in
	(save-excursion 
	 (temp-use-buffer "Shelltemp")
	 (setq needs-checkpointing 0)
         (if (file-exists (arg 1)) (read-file (arg 1)))
	)
        (save-excursion max-var-name
         (temp-use-buffer (arg 2))	; 
         (setq needs-checkpointing 0)
         (setq mode-line-format "Do Not Touch! For internal use only")
	 (yank-buffer "Shelltemp")
	 (delete-buffer "Shelltemp")
        )
    )
)	
