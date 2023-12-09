	;;;; LastEditDate="Fri Sep  7 18:09:19 1984"
	;;;;
	;;;; MLisp Macro written by Tony Hansen
	;;;;
	;;;; The purpose of these macros is to
	;;;; provide a rudimentary shell within a window
	;;;; without requiring Berkeley's mpxio facilities.
	;;;; It is not an interactive shell; any commands
	;;;; requiring input will be effectively tied to
	;;;; /dev/null.
	;;;;
	;;;; To start up the shell, use the "shell"
	;;;; command. It can be "autoloaded" from the file
	;;;; shell.ml in the local macro library.
	;;;;
	;;;; new commands:
	;;;; 
	;;;; ^M or <CR>
	;;;; The carriage return takes the current line,
	;;;; makes a copy of it at the end of the buffer if it
	;;;; is not already there, executes the command, places
	;;;; the output after the command, and leaves the cursor
	;;;; at the beginning of the output.
	;;;;
	;;;; ^G
	;;;; Restores the status line.
	;;;;
	;;;; ESC-=
	;;;; To make this package more compatible with the shell command
	;;;; from the process package, ESC-= will grab the last line
	;;;; executed and place it at the end of the buffer.
	;;;;
	;;;; ~ is defined as a word character and is the abbreviation for a
	;;;; user's home directory.  So you can type "~/foo" and get the
	;;;; csh action in a more electric way.
	;;;;

(progn
    (declare-global 
	Shell-mode-line-stopped		; mode line when not executing
	Shell-mode-line-running		; mode line when executing
	Shell-commandline)		; last command executed
    (setq Shell-mode-line-stopped ">\^I\^I Shell\^I\^I - %p")
    (setq Shell-mode-line-running ">\^I\^I Shell\^I\^I RUNNING ")
)

(defun
    (shell-return doacopy
	(end-of-line)				; check for end of buffer
	(setq doacopy 0)			; copy command to end?
	(if (eobp)				; if not eob, mark line to
	    (newline-and-backup)		;         no, copy!
	    (< (dot) (- (buffer-size) 5))	;     not even close?
	    (setq doacopy 1))			;         no, copy
	(set-mark)				; save command line
	(beginning-of-line)			; ...
	(setq Shell-commandline			; ...
	      (region-to-string))		; ...
	(while
	      (> (buffer-size) 10000)		; limit size of buffer
	      (progn				; ...
		  (beginning-of-file)		; ...
		  (provide-prefix-argument 500	; ...
		      (delete-next-character)))); ...
	(end-of-file)				; leave copy at end of buffer,
	(if doacopy				; but only if necessary
	    (progn				; ...
		(if (! (bolp))			; ...
		    (newline))			; ...
		(insert-string Shell-commandline); ...
		(newline)))			; ...
	(save-excursion				; stay at beginning of output
	    (set-mark)				; give a null-input
	    (setq mode-line-format		; show command is executing
		  Shell-mode-line-running)
	    (sit-for 0)				; ...
	    (filter-region Shell-commandline)	; execute the command
	    ;(save-excursion 			; execute the command
		;(execute-monitor-command Shell-commandline))
	    ;(yank-buffer "Command execution")	; get output
	    (setq mode-line-format		; show command is done
		  Shell-mode-line-stopped)
	    (novalue))				; finished!
    )
)

(defun
    (grab-last-shell-line
	(end-of-file)
	(if (! (bolp))
	    (newline))
	(insert-string Shell-commandline)
	(beginning-of-line))
)

(defun
    (shell-abort
	(setq mode-line-format			; reset mode line
	      Shell-mode-line-stopped)
	(error-message "")			; abort
    )
)

; taken from process.ml
(defun
    (shell-cd
	(if (= (current-column) 3)
	    (progn (cd (get-tty-string ": cd "))
		   (insert-string " " (working-directory))
		   (newline)
		   ;(shell-return)
		   0)
	    1))
)


(defun
    (shell
	(pop-to-buffer "Shell")			; give shell its own buffer
	(end-of-file)				; easy to do, why not?
	(if (! (eolp))				; ...
	    (newline))				; ...
	(setq needs-checkpointing 0)		; we dont want to checkpoint
	(use-abbrev-table "shell")		; for '~'
	(use-syntax-table "shell")		; ....
	(setq abbrev-mode 1)			; ....
	(define-local-abbrev "~"		; ....
	    (getenv "HOME"))
	(modify-syntax-entry "w    ~")		; ....
	(define-hooked-local-abbrev "cd"	; do an electric cd
	    "cd" "shell-cd")
	(local-bind-to-key			; use <CR> to execute line
	    "shell-return" '^M')
	(local-bind-to-key "shell-abort" '^G')	; to change back mode line
	(local-bind-to-key			; to get last mode line back
	    "grab-last-shell-line" "\e=")
	(setq mode-line-format 			; to tell when running shell
	      Shell-mode-line-stopped)
	(novalue)
    )

    (start-shell
	  (start-shell))
)
(novalue)
