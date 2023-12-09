; From uucp Mon Jan 10 12:28 EST 1983
; >From jis Mon Jan 10 11:20:43 1983 remote from hocsd
; FROM: j.mukerji
; TO: hansen
; DATE: 10 Jan 1983  11:20 EST
; SUBJECT: gemacs pcsrmail
; 
; 
; Following is the macro file that interfaces gemacs with the PCS
; sendmail program. The macro rmail-reply is the hook through which this
; package hooks onto any readmail program for generating a reply form.
; For this it uses the contents of the buffer current-message, so this
; sendmail package should be able to generate a skeleton buffer for a
; reply message from the current-message buffer.
; 
; This file could do with a significant amount of cleaning up, because it
; has sort of grown over a period of time. But it certainly works fine!
; 
; Jishnu.
; ------------------------------------------------------------
	;;;; LastEditDate="Sat Aug 27 13:50:01 1983"
; Unix Emacs RMail facility.  implements  smail (send mail).
; using the pcs sendmail command for dispatching mail and info command
; for verfying addresses
; 
; "smail" is used for sending mail.  It places you in a buffer for
; constructing the message and locally defines a few commands:
;  ^Xt	positions you in the To: field of the message.
;  ^Xc	positions you in the Cc: field of the message, creating it if it
;	doesn't already exist.
;  ^Xs	positions you in the Subject: field of the message.
;  ^Xa	positions you to the end of the body of the message, ready to
; 	append more text.
;  ^Xi	insert contents of buffer current-saved-message at the cursor
; 	between markers "Begin Forwarded Message" and "End Forwarded Message"
;  ^C   to send the mail or quit. The user is prompted for various
; 	options that are available to him at the bottom of the screen.


(declare-global gemacs-library-directory null-field)
(setq null-field "")

(defun
    (smail-com i
	(pop-to-buffer "send-mail")
	(setq needs-checkpointing 0)
	(setq case-fold-search 1)
	(erase-buffer)
	(setq i 1)
	(newline)
	(while (> (argc) i)
	       (if (!= (substr (argv i) 1 1) "-")
		   (progn
			 (insert-string (argv i))
			 (if (> (argc) i) (insert-character ','))
		   )
	       )
	       (setq i (+ i 1))
	)
	(newline)
	(do-mail-setup)
	(exit-emacs)
    )

; 	This function is an interface with the old emacs mail reading
; 	macros, to format a reply to a message.

    (rmail-reply dest subject excess
      (save-window-excursion 
	(delete-window)
	(position-on-dirent)
	(pick-up-message)
	(setq subject "")
	(setq dest "")
	(setq excess "")
	(save-excursion
	    (temp-use-buffer "current-message")
	    (if (error-occured
                (beginning-of-file)
		(re-search-forward "^SUBJECT:[ \t]*")
		(set-mark)
		(end-of-line)
		(setq subject (region-to-string))
		)
	      ( error-occured
		 (beginning-of-file)
		(re-search-forward "^Subject:[ \t]*")
		(set-mark)
		(end-of-line)
		(setq subject (region-to-string))
	      )
	    )
	    (if (& 
		    (!= (substr subject 1 3) "Re:")
		    (!= (substr subject 1 3) "re:")
		)
		(setq subject (concat "Re: " subject))
	    )
	    (if (error-occured 
	      (beginning-of-file)
	      (re-search-forward "^FROM:[ \t]*") ;  pcs mail
	      (set-mark)
	      (end-of-line)
	      (setq dest (region-to-string))
		)
	      (if (error-occured
	        (beginning-of-file)
		(re-search-forward "^>From ") ; remote mail
		(while (looking-at "\*\*")
			(re-search-forward "^>From ")
		)
		(set-mark)
		(re-search-forward " ")
		(backward-character)
		(setq dest (region-to-string))
		(re-search-forward "remote from ")
		(set-mark)
		(end-of-line)
		(setq dest (concat (region-to-string) "!" dest))
		)
	       (error-occured 
		(beginning-of-file)
		(re-search-forward "^From ")
		(set-mark)
		(re-search-forward " ")
		(backward-character)
		(setq dest (region-to-string))
	       )
	      )
	    )	
	    (beginning-of-file)
	    (error-occured 
	      (if (error-occured (re-search-forward "^Date:[ \t]*"))
		(re-search-forward "^DATE:[ \t]*"))
	      (set-mark)
	      (end-of-line)
	      (setq excess (concat
				 "In-Reply-To: Your"
				 " message of "
				 (region-to-string)
				 "\n"))
	    )
	    (pop-to-buffer "send-mail")
	    (setq case-fold-search 1)
	    (erase-buffer)
	    (insert-string subject)
	    (newline)
	    (insert-string dest)
	    (newline)
	    (insert-string excess)
	    (do-mail-setup)
	)
	(position-on-dirent)
	(if (looking-at "^>[N ]")
	    (progn
		(forward-character)
		(delete-next-character)
		(insert-character 'A')
		(beginning-of-line)))
      )
    )
)

(defun
    (mail-file-insert
	(mail-append)
	(save-excursion 
	    (insert-string "\n_____________*** Forwarded File ***_______________\n\n")
	  (save-excursion 
	    (temp-use-buffer "temp")
	    (read-file (get-tty-string "name of file:"))
	    (beginning-of-file)
	    (error-occured (re-replace-string "^From" ">&"))
	  )
	  (yank-buffer "temp")
	  (delete-buffer "temp")
	  (insert-string "\n______________*** End of Forwarded File ***__________\n\n")
	)
    )
    (mail-insert
	(mail-append)
	(save-excursion
	    (insert-string "\n____________*** Forwarded Message ***_____________\n\n")
	    (save-excursion 
		(temp-use-buffer "current-saved-message")
		(beginning-of-file)
		(error-occured (re-replace-string "^From" ">&"))
	    )
	    (yank-buffer "current-saved-message")
	    (insert-string "\n_________** End of Forwarded Message **___________\n\n")
	)
	(error-occured (re-replace-string "^From \\|^Date:" ">&")))
)

(defun    
    (smail 	        ; initiate mail sending
	(save-window-excursion
	    (pop-to-buffer "send-mail")
	    (setq case-fold-search 1)
	    (erase-buffer)
	    (insert-string "\n\n")	; for subject and to
	    (do-mail-setup)
	)
	(novalue)
    )
    
    ; set things up in a mail sending buffer.
    (do-mail-setup mail-do-send
	(setq mode-string "SMail")
	(setq mail-do-send 1)
	(beginning-of-file)
	(insert-string "SUBJECT: ")
	(next-line)(beginning-of-line)
	(insert-string "TO: ")
	(beginning-of-file)
	(search-forward " ")
	(setq right-margin 72)
	(local-bind-to-key "mail-to" "\^Xt")
	(local-bind-to-key "mail-append" "\^Xa")
	(local-bind-to-key "mail-cc" "\^Xc")
	(local-bind-to-key "mail-subject" "\^Xs")
	(local-bind-to-key "mail-insert" "\^Xi")
	(local-bind-to-key "smail-help" "h")
	(local-bind-to-key "justify-paragraph" "\ej")
	(setq mode-line-format 
		"Send Mail\t%[%p%]\t\t^C to send/quit  ^Xh for HELP")
	(while mail-do-send
	       (save-excursion
		   (recursive-edit)
		   (smail-what-next)
	       )
	)
	(delete-buffer "send-mail")
	(error-occured (delete-buffer "mail-info"))
    )
)

(defun 
    (mail-collect-recip
	(beginning-of-file)
	(if (error-occured (re-search-forward "^To:[ \t]*"))
	    (setq recip (get-tty-string "To: "))
	    (progn 
		(set-mark)
		(end-of-line)
		(setq recip (region-to-string))
	    )
	)
	(setq copy-to "")
	(while (! (error-occured (re-search-forward "^Cc:[ \t]*")))
	    (set-mark)
	    (end-of-line)
	    (setq copy-to (concat copy-to " " (region-to-string)))
	)
	(setq all-recip (concat recip copy-to))
    )

    (mail-check unknown
	(save-excursion 
	    (temp-use-buffer "mail-info")
	    (erase-buffer)
	    (set-mark)
	    (filter-region (concat "info " all-recip))
	    (setq unknown "")
	    (beginning-of-file)
	    (while (! (error-occured (search-forward "unknown")))
		(beginning-of-line)
		(set-mark)
		(search-forward ":")
		(backward-character)
		(setq unknown (concat unknown " " (region-to-string)))
		(end-of-line)
	    )
	    (if (!= (length unknown) 0)
		(progn 
		    (message (concat "Unknown: " unknown))
		    (sit-for 20)
		)
	    )
	)
	(length unknown)
    )

    (mail-check-show
	(mail-check)
	(save-window-excursion 
	    (pop-to-buffer "mail-info")
	    (setq mode-line-format 
			"List of recipients  %[%p%]\t\t^C to return to mail")
	    (recursive-edit)
	)
    )

    (mail-send-options sresp soresp
	(setq sresp "")
	(setq options "")
	(setq soresp 
	  (get-tty-string 
	    "send options: standard, notify, filecopy? [standard] ")
	)
	(if (> (length soresp) 0)
	  (save-excursion 
	    (temp-use-buffer "mail-temp")
	    (erase-buffer)
	    (insert-string soresp)
	    (beginning-of-file)
	    (while (! (error-occured (re-search-forward "\\([a-z][a-z]*\\)")))
		(region-around-match 1)
		(setq soresp (region-to-string))
		(setq sresp (substr soresp 1 1))
		(if (= sresp "n") (setq options (concat options " +notify"))
		(if (= sresp "s") (setq options (concat options ""))
		(if (= sresp "f") (setq options (concat options " +filecopy"))
		(if (= sresp "q") (setq mail-do-send 0)
; 		else default
		    (progn 
			(message 
			  (concat "Unknown option " soresp " ignored"))
			(sit-for 20)
		    )
		))))
	    )
	  )
	)
	(error-occured (delete-buffer "mail-temp"))
	(if (!= sresp "q")
	    (send-mail-try)
	    (setq response "q")
	)
    )

    (send-mail-try
	(message (concat "Options: " options))(sit-for 10)
	(message "Please wait while I verify the addresses")(sit-for 0)
	(if (mail-check) 
	    (message "Please modify the To and/or Cc fields")
	    (send-mail)
	)
	(setq response "q")
    )

    (smail-what-next response options all-recip recip copy-to
	(setq response "i")
	(mail-collect-recip)
	(setq options "")
	(while (!= response "q")
	    (setq response (get-tty-string 
		"send, review, check, quit? [send standard] "))
	    (if (= 0 (length response))
		(setq response " ")
		(setq response (substr response 1 1))
	    )
	    (if (= response " ") (send-mail-try)
	    (if (= response "s") (mail-send-options)
	    (if (= response "c") (mail-check-show)
	    (if (= response "q") (setq mail-do-send 0)
	    (if (= response "r") (setq response "q")
; 	    else default
		(progn 
		    (message "unknown command")(sit-for 10)
		)
	    )))))
	)
    )
)

(defun
    (mail-to 		        ; move to the "To:" field
	(beginning-of-file)
	(re-search-forward "^to:.*")
	(setq left-margin 10)
    )
    
    (mail-subject 	        ; move to the "Subject:" field
	(beginning-of-file)
	(re-search-forward "^subject:.*")
	(setq left-margin 10)
    )
    
    (mail-append 	        ; move to the body
	(end-of-file)
	(setq left-margin 1)
    )
    
    (mail-cc 		        ; move to the "cc:" field.
	(beginning-of-file)
	(if (error-occured (re-search-forward "^cc:.*"))
	    (progn (re-search-forward "\n\n\\|^to:.*\n.")
		(backward-character)
		(backward-character)
		(insert-string "\nCC: ")
	    )
	)
    )
    (smail-help
	(save-window-excursion 
	    (switch-to-buffer "smail-help")
	    (if (< (buffer-size) 1)
	        (read-file (concat gemacs-library-directory "/smail.hlp"))
	    )
	    (get-tty-string "hit RETURN to return")
	)
    )
    
    (send-mail subject sendcom		; finally send the mail
	(beginning-of-file)
	(error-occured 
	    (re-search-forward "^subject:[ \t]*")
	    (set-mark)
	    (end-of-line)
	    (setq subject (region-to-string))
	)
	(beginning-of-file)
	(set-mark)
	(if (error-occured  (re-search-forward "^Cc:"))
	    (re-search-forward "^To:")
	)
	(beginning-of-line)
	(next-line)
	(delete-region-to-buffer "temp")
	(set-mark)
	(end-of-file)
	(insert-character '.')
	(newline)
	(setq recip (concat recip " "))
	(setq sendcom
		 (concat "sendmail - " options " "
			recip "subject=""" subject """ "))
	(if (> (length copy-to) 0) (setq sendcom (concat sendcom 
				"copy_to=""" copy-to """")))
	(filter-region-in sendcom)
	(if (= (buffer-size) 0)
	    (progn
		(setq mail-do-send 0)
		(setq response "q")
		(message "The message is on its way!")
		(sit-for 20)
	    )
	    (progn
		(beginning-of-file)
		(set-mark)
		(error-occured (re-replace-string "\n\n* *" "; "))
		(end-of-line)
		(message (region-to-string))
		(erase-buffer)
		(yank-from-killbuffer)
		(beginning-of-file)
		(yank-buffer "temp")
		(end-of-file)
		(delete-previous-character)
	    )
	)
	(novalue)
    )
)
------------------------------------------------------------

You will notice that gemacs-library-directory is globally defined. This
you can define locally. At hocs* gemacs-library-directory is defined in
profile.ml. You will also notice that the help file in this is kept in
the gemacs library directory. Ideally this should be put into the info
system, but I haven't gotten around to doing so yet. The help file
follows:
------------------------------------------------------------
^Xt	goto To: field			^Xa	goto end of message
^Xc	goto Cc: field			^Xi	insert mail for forwarding
^Xs	goto Subject: field		^Xh	HELP

^C when the letter has been completed. This brings up a menu on the bottom
	line which looks like:
		send, review, check, quit? [send standard]
   To do a standard send hit return, to specify additional sending options 
   type 'send' followed by return. It comes up with a further menu:
		standard, notify, filecopy? [standard]
   Type in the options you want followed by return.
------------------------------------------------------------


