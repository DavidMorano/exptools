;From uucp Tue Jan 11 15:13 EST 1983
;>From jis Tue Jan 11 15:10:32 1983 remote from hocsd
;FROM: j.mukerji
;TO: hansen
;DATE: 11 Jan 1983  15:10 EST
;SUBJECT: postnews macro for PCS system
; 
; 
;Following is a copy of the file postnews.ml that is used here to
;interface netnews and PCS bulletin boards with gemacs. Any newsgroup
;name that does not contain a period is assumed to be the name of a PCS
;bulletin board and an appropriate posting is attempted. For all other
;newsgroup names a posting is done on the corresponding netnews
;newsgroup.
; 
;Change the setq for bblib and newslib to reflect the spool directories
;at your site for PCS bb and netnews respectively. Posting on PCS bb
;uses the PCS program post. The PCS program caldate is also used.
;---------------------------------------------------------------------------
	;;;; LastEditDate="Sat Aug 27 13:48:22 1983"
; 
; 	This macro is used for submitting a news article to inews
; 	for posting in netnews v9.
; 
; CAUTION This version has directory names frozen into it!!!!
; 

(defun 
    (get-date
	(save-excursion 
	    (temp-use-buffer "posttemp")
	    (erase-buffer)
	    (set-mark)
	    (filter-region "caldate")
	    (beginning-of-file)(set-mark)
	    (end-of-file)(backward-character)
	    (region-to-string)
	)
    )
)

(defun 
    (get-news-title ltitle oltitle
				; invoke immediately after invoking
				; get news board to ensure proper
				; handling of bboard titles
        (setq post-attempt 1)
	(while (> post-attempt 0)
	     (setq  ltitle (get-tty-string "Title of the article: "))
	     (if (= (length ltitle) 0)(setq ltitle otitle))
	     (if (= bbpost 1)
	      (progn 
	       (save-excursion 
		(temp-use-buffer "posttemp")
	        (erase-buffer)
		(insert-string  ltitle)
		(beginning-of-file)
		(goto-character 14)
		(kill-to-end-of-line)
		(beginning-of-file)
		(error-occured (re-replace-string " " "_"))
		(insert-character ' ')	; This is a temporary hack for
		(delete-previous-character); circumventing a bug in emacs
		(set-mark)
		(end-of-file)
		(setq oltitle ltitle)
		(setq ltitle (region-to-string))
	       )
	       (if (file-exists (concat bblib "/" bboard "/" ltitle))
	       (progn 
		    (message (concat "Title: " title " already exists"))
		    (sit-for 20)
		    (message "Please choose another one")(sit-for 20)
		)
		(progn 
		    (setq otitle oltitle)
		    (setq title ltitle)
		    (save-excursion 
		      (temp-use-buffer "netnews")
	              (setq mode-line-format (concat "Post on bulletin board "
			bboard ", Title: " otitle))
		    )
		    (setq post-attempt 0)
		)
	       )
	      )
	      (progn 
		(setq post-attempt 0)		    
		(setq title ltitle)
		(setq otitle title)
		(save-excursion 
		  (temp-use-buffer "netnews")
	          (setq mode-line-format (concat "Postnews in newsgroup(s) " 
			bboard ", Title: " title))
		)
	      )
	     )
	)
    )

    (get-news-board tboard
				; get-news-title must be called after
				; this to remap title for bulletin boards
	(setq post-attempt 1)
	(while (> post-attempt 0)
	  (setq tboard (get-tty-string (concat 
			 "Name of the board [" bboard "]: ")))
	  (if (& (= (length tboard) 0) (! firsttime))
	    (progn 
	      (setq post-attempt 0)
	      (setq firsttime 0)
	    )
	    (progn 
	      (if (& firsttime (= (length tboard) 0))
	       (progn 
		(setq tboard bboard)
		(setq firsttime 0)
	       )
	      )
	      (save-excursion 
		(temp-use-buffer "posttemp")
		(erase-buffer)
		(insert-string tboard)
		(beginning-of-file)
		(if (error-occured (search-forward "."))
		    (setq bbpost 1)
		    (setq bbpost 0)
		)
	      )
	     (if (= bbpost 1)
 	      (progn 
	       (if (! 
		(file-exists (concat bblib "/" tboard))
		  )
		(progn 
		  (message (concat "Bulletin board "
			 tboard  " doesn't exist"))
		  (sit-for 20)
		)
		(progn 
		  (setq post-attempt 0)
		  (setq bboard tboard)
		)
	       )
	      )
	      (if (! (file-exists (concat newslib "/" tboard)))
		(progn 
		  (message (concat "Newsgroup " tboard " doesn't exist!"))
		  (sit-for 20)
		)
		(progn 
		  (setq post-attempt 0)
		  (setq bboard tboard)
		)
	      )
	    )
	    )
	  )
	)
    )

    (show-news-title-board
	(message (concat  "Title: " title))
	(sit-for 20)
    )

    (modify-title-board
        (get-news-board)
        (get-news-title)
	(novalue)
    )

    (news-help
	    (message (concat 
		"^X? - for help"
		", ^Xt - to modify board or title"
		", ^C - to post the article"
			   )
	    )
    )
)

(defun 
    (postnews title bboard command post-attempt bbpost newslib bblib
		actual-name otitle resp firsttime
      (setq actual-name (users-full-name))
      (save-window-excursion 
	(setq firsttime 1)
	(pop-to-buffer "netnews")
	(erase-buffer)
	(text-mode)
	(local-bind-to-key "news-help" "?")
	(local-bind-to-key "modify-title-board" "t")
	(setq mode-string "")
	(setq mode-line-format "Postnews")
	(setq post-attempt 1)
        (setq bblib "/gaz/pcs/lib/boards")	; *** DIRECTORY NAME ***
	(setq newslib "/fsbin/netnews/spool")	; *** DIRECTORY NAME ***
	(setq bboard "general")	; default bulletin board
	(setq otitle "")	; default real title
	(setq title "")		; default mapped title
	(get-news-board)
	(get-news-title)
	(message "type in the article and when you are done hit ^C, for help ^X?")
	(recursive-edit)
        (setq resp (get-tty-string (concat "post this article"
				" on bboard/newsgroup " bboard "? ")))
	(if (| (= (length resp) 0) (= (string-to-char resp) 'y'))
	      (if (= bbpost 0)
	        (progn 		;  post on netnews
	          (setq command 
		    (concat "/gaz/bin/inews -t \"" title "\" -n " bboard)
		  )
;	          (message (concat "executing: " command))(sit-for 10)
		  (beginning-of-file)
		  (insert-string (concat ">From: " actual-name "\n"))
		  (insert-string (concat ">Date: " (current-time) "\n"))
		  (newline)
	          (beginning-of-file)
	          (set-mark)
	          (end-of-file)
	          (filter-region-in command)
	          (if (= (buffer-size) 0)
		    (progn 
		      (message "Article posted")(sit-for 20)
		    )
		  )
		)
	        (progn 		; post on bboard
		  (beginning-of-file)
		  (insert-string (concat "FROM: " actual-name "\n"))
		  (insert-string (concat "DATE: " (get-date) "\n"))
		  (insert-string (concat "BOARD: " bboard "\n"))
		  (insert-string (concat "TITLE: " otitle "\n\n"))
	          (write-named-file (concat bblib "/" bboard "/" title))
	          (setq command (concat 
		      "/gaz/pcs/bin/post -m " bblib "/" bboard "/" title)
		  )
	          (execute-monitor-command (concat 
		      "/bin/chmod 644 " bblib "/" bboard "/" title)
		  )
		  (execute-monitor-background command)
	          (message "Article posted")(sit-for 20)
		)
	      )
	     (progn 
	      (message "Article not posted")
	      (sit-for 10)
	     )
	)
      )
      (message "postnews says Adios!")(sit-for 10)
      (delete-buffer "netnews")
      (error-occured (delete-buffer "posttemp"))
      (novalue)
    )
)
(novalue)

---------------------------------------------------------------------------

By the way, I also have the hack for obtaining the actual name of an
user from the PCS database for use in the actual-name function of
gemacs. If you are interested in that let me know.

Hopefully in the next couple of days I should be able to clean up the
interactive shell stuff sufficiently to be able to send it to you.

Also, you might have already noticed that the PCS sendmail macro uses
the new filter-region-in function. I found that without that an
attempt to send mail to a mailing list takes for ever! You can of
course use plain 'ol filter-region function (perhaps with a little
tweaking), if you prefer so.

Jishnu.



