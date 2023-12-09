; 
;  This file contains the definition of the mlisp commands:
; 		goto-commands
; 		execute-command
; 		execute-background
; 
;  The user is expected to have a bunch of commonly used commands listed
;  one per line in ~/.commands. ~/.commands is created when this package
;  is invoked for the first time. When goto-commands is invoked s/he is 
;  presented with the contents of the command file. At this point s/he is
;  expected to set the cursor on the line which contains the command that
;  s/he wishes to execute, and then hit ^C to exit from goto-commands.
;  Subsequently, that command can be executed either in foreground with
;  output capture or in the background with no output capture by 
;  ESC-^M or ESC-^N respectively.
; 
;  If the command line contains one or more %'s, the user is prompted for
;  arguments to replace the %'s before the command line is submitted for
;  execution.
; 
;  Caution: This package requires the execute-monitor-background command
;  in gemacs.
; 
;  Written by J.Mukerji 10.19.83
; 
(defun 
    (goto-commands
	(save-window-excursion 
	    (pop-to-buffer "*Shellcommands*")
	    (setq mode-line-format "My list of commands\t\t\t^C to return")
	    (sit-for 0)
	    (if (= (buffer-size) 0)
	      (error-occured 
		(read-file (concat (getenv "HOME") "/.commands"))
	      )
	    )
	    (message "^C to return")(sit-for 10)
	    (bind-to-key "execute-command" "")
	    (bind-to-key "execute-background" "")
	    (recursive-edit)
	    (temp-use-buffer "*Shellcommands*")
	    (if (> (buffer-size) 0)
	        (write-named-file (concat (getenv "HOME") "/.commands"))
	    )
	    (setq mode-line-format "Do not touch. For internal use only.")
	)
    )
)

(defun 
    (collect-command command-image
	(save-excursion 		; pick up current command
	    (temp-use-buffer "*Shellcommands*")
	    (if (= (buffer-size) 0)
		(goto-commands)
	    )
	    (if (= (buffer-size) 0)
	      (progn 
		(message "No commands in commands file!")
		(sit-for 20)
		(set-mark)
		(setq command-image (region-to-string))
	      )
	      (progn 
		(beginning-of-line)(set-mark)
		(end-of-line)
		(setq command-image (region-to-string))
	      ) 			; else
	    )
	)
;  This portion added to prompt for arguments
	(save-excursion 
	    (temp-use-buffer "comm-temp")
	    (erase-buffer)(insert-string command-image)
	    (beginning-of-file)(set-mark)
	    (while (! (error-occured (search-forward "%")))
		(delete-previous-character)
		(insert-string (get-tty-string 
		    (concat "command: " (region-to-string) " ? "))
		)
	    )
	    (beginning-of-file)(set-mark)(end-of-file)
	    (setq command-image (region-to-string))
	)
	(delete-buffer "comm-temp")
	(setq command-image command-image)
    )
    (execute-command current-command
	(setq current-command (collect-command))
	(if (> (length current-command) 0)
	    (save-excursion
		(message 
		  (concat "executing command " current-command)
		)
		(sit-for 20)
		(execute-monitor-command current-command)
		(pop-to-buffer "Command execution")
	    )
	    (message "Cursor not positioned on a command line")
	)
    )
    (execute-background current-command
	(setq current-command (collect-command))
	(if (> (length current-command) 0)
	    (save-excursion
		(message 
		  (concat "command in background " current-command)
		)
		(sit-for 20)
		(execute-monitor-background current-command)
	    )
	    (message "Cursor not positioned on a command line")
	)
    )
)
