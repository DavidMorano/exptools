	;;;; LastEditDate="Sat Sep 22 09:48:42 1984"
	; Macro written by James Gosling.
	; Updated by Tony Hansen to include help functions,
	; recursive-edit '^R', and next 'n'.

	; I've made some changes to the gmacs spell macro and I would 
	; appreciate it if you would include this in future releases. 
	; Basically, I've add the 'g' function. Hitting 'g' on any misspelled
	; word will invoke grope. Grope is a popular program on many UNIX
	; systems which attempts to find the correct spelling of a misspelled
	; word. Once in grope mode, a space will return the next choice 
	; (up to 25) and 'r' will replace the misspelled word with the
	; correct one. If grope is not found on the system, an appropriate
	; message is printed. Here's the code:

	;					Steve Goldsmith
	;					AT&T Bell Laboratories
	;					582-7746, mhuxr!sbg

(defun
    (spell cur-file-name cur-buffer-name cur-dot
	(message (concat "Looking for errors in " (current-file-name)
		     ", please wait..."))
	(sit-for 0)
	(setq cur-file-name (current-file-name))
	(setq cur-buffer-name (current-buffer-name))
	(setq cur-dot (+ (dot) 0))
	(save-excursion spellfiles		; TLH - added .spell files
	    ;(compile-it (concat "spell -b " cur-file-name))
	    (compile-it
		(concat "spell "
			(if (file-exists ".spell")
			    "+.spell "
			    " ")
			(if (file-exists "~/.spell")
			    "+$HOME/.spell "
			    " ")
			cur-file-name)))
	(save-excursion
	    (switch-to-buffer "  temp-spell-buffer")
	    (erase-buffer)
	    (yank-buffer cur-buffer-name)
	    (error-occured (correct-spelling-mistakes)))
	(erase-buffer)
	(yank-buffer "  temp-spell-buffer")
	(delete-buffer "  temp-spell-buffer")
	(goto-character cur-dot)
	(message "Done!")
	(novalue)
    )

    (correct-spelling-mistakes word action continue loopctl search-word
	gword gaction gloop maxg maxgg
	(setq continue 1)
	(setq maxg 25)
	(progn
	      (while continue
		     (save-excursion
			 (temp-use-buffer "Error log")
			 (beginning-of-file)
			 (set-mark)
			 (end-of-line)
			 (setq word (region-to-string))
			 (forward-character)
			 (delete-to-killbuffer))
		     (beginning-of-file)
		     (setq search-word (concat "\\b" (quote word) "\\b"))
		     (if (error-occured
			     (re-search-forward search-word))
			 (progn
			       (message word " not found. Any char continues")
			       (get-tty-character)
			 ))
		     (&spell-ask)
		     (setq loopctl 1)
		     (while loopctl
			    (if
			       (| (= action '^G')
				  (= action 'e'))
			       (progn
				     (setq continue 0)
				     (setq loopctl 0))

			       (= action ' ')
			       (setq loopctl 0)

			       (= action 'n')
			       (progn
				     (if (error-occured
					     (re-search-forward search-word))
					 (progn
					       (message word " not found. Any char continues")
					       (get-tty-character)
					 ))
				     (&spell-ask))

			       (= action '^L')
			       (progn
				     (redraw-display)
				     (&spell-ask))

			       (= action 'r')
			       (error-occured
				   (setq loopctl 0)
				   (beginning-of-line)
				   (re-query-replace-string ""
				       (get-tty-string
					   (concat "Using query-replace: "
						   word " => "))))

			       (= action '^R')
			       (progn
				     (message "Use ^C to return")
				     (sit-for 0)
				     (recursive-edit)
				     (&spell-ask))

			       (= action 'g')
			       (progn 
				  (save-excursion 
				      (message (concat "Groping for " word "..."))
				      (sit-for 10)
				      (temp-use-buffer "Grope")
				      (beginning-of-file)
				      (set-mark)
				      (end-of-file)
				      (delete-to-killbuffer)
				      (setq maxgg maxg)
				      (while (>=  maxgg  2)
					     (progn 
						    (setq maxgg (- maxgg 1))
						    (insert-string "\n")))
				      (insert-string "q\n")
				      (filter-region (concat "grope " word))
				      (beginning-of-file)
				      (next-line)
				      (if (eobp)
					  (progn 
						 (message "Grope program not found.  Any char continues")
						 (get-tty-character)
						 (setq action '?')
						 (setq gloop 0))
					  (setq gloop 1)))
				  (while gloop
				    (save-excursion 
					(temp-use-buffer "Grope")
					(beginning-of-file)
					(set-mark)
					(end-of-line)
					(if (bolp)
					    (progn 
						   (message 
						       (concat "Max of " maxg " grope items"))
						   (sit-for 10)
						   (setq action '?')
						   (setq gaction 'e'))
					    (progn 
						   (setq gword (region-to-string))
						   (forward-character)
						   (delete-to-killbuffer)
						   (message (concat word  " => " gword " ? "))
						   (setq gaction (get-tty-character)))))

				    (if 
					    (| (= gaction '^G')
					       (= gaction 'e'))
					       (progn 
						      (setq action '?')
						      (setq gloop 0))

					    (= gaction 'r')
					    (error-occured 
						   (beginning-of-line)
						   (message 
						       (concat "Using query-replace: " word " => " gword))
						   (re-query-replace-string word gword)
						   (setq loopctl 0)
						   (setq gloop 0))

					    (= gaction ' ')
					    (progn
						  (setq gloop 1))

					    ; default
					    (progn 
						   (message
							   (concat word " => " gword
						     " ?  'r'=replace, ' '=next grope choice, 'e'=end groping"))
				 		    (setq gaction (get-tty-character))))))


			       ; default
			       (progn
				     (message word
					 " ? SP=OK, 'r'=replace, 'e'=end, '^R'=edit, 'n'=next, 'g'=grope")
				     (setq action (get-tty-character)))
		     ))))
	(novalue)
    )

    (&spell-ask
	(message word " ? ")
	(setq action (get-tty-character)))

)
