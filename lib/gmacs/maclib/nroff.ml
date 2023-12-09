	;;;; LastEditDate="Thu Aug  1 21:34:46 1985"
	;;;; macro mode written by Tony Hansen

(defun
    (nroff-justify-paragraph
	(save-excursion
	    (save-restriction
		(if (error-occured (re-search-reverse "^[.']"))
		    (beginning-of-file)
		    (next-line))
		(set-mark)
		(if (error-occured (re-search-forward "^[.']"))
		    (end-of-file))
		(beginning-of-line)
		(narrow-region)
		(backward-character)
		(justify-paragraph))))

    ; apply-italic will stick the \fI and \fP around a word to make it italic.
    (apply-italic
	(save-excursion
	    (forward-character)
	    (backward-word)
	    (insert-string "\\fI")
	    (provide-prefix-argument prefix-argument
		(forward-word))
	    (insert-string "\\fP")))
    
    ; apply-bold will stick the \fB and \fP around a word to make it bold.
    (apply-bold
	(save-excursion
	    (forward-character)
	    (backward-word)
	    (insert-string "\\fB")
	    (provide-prefix-argument prefix-argument
		(forward-word))
	    (insert-string "\\fP")))
    
    ; join-lines
    (nroff-join-lines
	(end-of-line)
	(save-excursion
	    (prefix-argument-loop
		(end-of-line)
		(delete-next-character)
		(delete-white-space)
		(insert-character ' ')
		(backward-character))))
    
    ; split-lines
    (nroff-split-lines
	(prefix-argument-loop
	    (end-of-line)
	    (if (> (current-column) right-margin)
		(progn
		      (beginning-of-line)
		      (error-occured
			  (provide-prefix-argument
			      (+ right-margin 1)
			      (forward-character)))
		      (re-search-reverse "[ \^I]")
		      (delete-white-space)
		      (newline)))))
    
    ; electric punctuation does a newline after inserting itself
    (electric-punctuation
	(if (bolp)
	    (self-insert)
	    prefix-argument-provided
	    (provide-prefix-argument prefix-argument
		(self-insert))
	    (progn
		  (self-insert)
		  (if (eolp)
		      (newline)))))
    
    ; electric space will not insert itself at the beginning of a line.
    (electric-space
	(if (! (bolp))
	    (provide-prefix-argument prefix-argument
		(self-insert))))
    
    ; electric-nroff turns on electricity
    (electric-nroff-mode
	(local-bind-to-key "electric-punctuation" '.')
	(local-bind-to-key "electric-punctuation" '?')
	(local-bind-to-key "electric-punctuation" '!')
	(local-bind-to-key "electric-space" ' ')
	(local-bind-to-key "end-electric-nroff-mode" '\036')
	(setq mode-string "nroff-mode,ON")
	(message "Electricity on..."))
    
    ; end-electric-nroff turns off electricity
    (end-electric-nroff-mode
	(local-bind-to-key "self-insert" '.')
	(local-bind-to-key "self-insert" '!')
	(local-bind-to-key "self-insert" '?')
	(local-bind-to-key "self-insert" ' ')
	(local-bind-to-key "electric-nroff-mode" '\036')
	(setq mode-string "nroff-mode")
	(message "... electricity off."))
    
    ; insert comment characters at end of line
    (nroff-comment
	(end-of-line)
	(delete-white-space)
	(to-col comment-column)
	(insert-string "\\"" "))
	
	; nroff-mode starts up everything
    (nroff-mode
	(remove-all-local-bindings)
	(if (! buffer-is-modified)
	    (save-excursion
		(error-occured
		    (goto-character 2000)
		    (search-reverse "LastEditDate=""")
		    (search-forward """")
		    (set-mark)
		    (search-forward """")
		    (backward-character)
		    (delete-to-killbuffer)
		    (insert-string (current-time))
		    (setq buffer-is-modified 0))))
	(local-bind-to-key "nroff-justify-paragraph" "\ej")
	(local-bind-to-key "nroff-join-lines" "\eJ")
	(local-bind-to-key "nroff-split-lines" "\eS")
	(local-bind-to-key "apply-italic" "\ei")
	(local-bind-to-key "apply-bold" "\eI")
	(local-bind-to-key "nroff-comment" "\e;")
	(local-bind-to-key "electric-nroff-mode" '\036')	; ^^
	(setq case-fold-search 1)
	(setq right-margin 77)
	(setq mode-string "nroff-mode")
	(use-syntax-table "nroff-mode")
	(modify-syntax-entry "w    -")
	(modify-syntax-entry "w    '")
	(use-abbrev-table "text-mode")
	(setq left-margin 1)
	(novalue))
)
