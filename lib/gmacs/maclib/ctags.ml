; twenex-like tags package		J. Gosling, November 81
; modified to use ctags files		Tim Mann, 9-4-84
;
; As a hack, I've modified the Emacs tags package to use the "tags" files
; created by the ctags program instead of building its own.  This is a win for
; several reasons, the primary one being that ved (and also vi) uses this kind
; of tags file, so you only need one.  Another reason is that ctags builds a
; tags file much faster than Emacs can.
;
; To use the modified tags package, add the following to your .emacs_pro file:
;
; (autoload "goto-tag" "ctags.ml")
; (autoload "goto-tag-in-buffer" "ctags.ml")
; (bind-to-key "goto-tag" "\^Xt")
; (bind-to-key "goto-tag-in-buffer" "\^X\^T")
;
; This binds "goto-tag" to ^Xt and "goto-tag-in-buffer" to ^X^T.  Goto-tag
; prompts you for the name of a function or typedef, then visits the file
; containing the function or type definition at the first line of the
; definition.  If there is more than one object of the same name listed in
; the tags file, ^Xt will find the first one, and repeatedly typing ^U^Xt
; will step through the others.  Goto-tag-in-buffer is used when the cursor
; is positioned on or just after the name of a function or type; it finds the
; name in the buffer, then visits the file as in goto-tag.
;
; The first time you use one of these functions, it will look for the tags
; file in the current directory, and if none is found, in your home directory.
; From then on the same tags file will be used until you either exit or call
; the function "visit-tag-table" with a new file name.
;
; When you run ctags, you will probably want to use the switches -tw.  This
; causes tags to be generated for typedefs as well as functions, and suppresses
; (useless) warning messages.  Both emacs and ved (as of now) understand tags
; on both functions and typedefs.  (Macros too, I think.)
;
(declare-global last-search-tag)

(defun
    ; some versions of ctags quote *'s and others don't. handle both.
    (&tags-optional-quote
	(if (looking-at ".*[\\][*]")
	    (arg 1)
	    (quote (arg 1)))
    )	
    
    (goto-tag fn pat restart pos
	(setq restart 0)
	(if (! prefix-argument-provided)
	    (progn
		  (setq last-search-tag
			(concat "^" (quote (arg 1 ": goto-tag ")) "[^\^I]*\^I"))
		  (setq restart 1)))
	(setq pos -2)
	(save-excursion
	    (to-tag-buffer)
	    (if restart (beginning-of-file))
	    (re-search-forward last-search-tag)
	    (set-mark)
	    (search-forward "\^I")
	    (backward-character)
	    (setq fn (region-to-string))
	    (forward-character)
	    (if (looking-at "/^")
		(progn
		      (forward-character)
		      (forward-character)
		      (set-mark)
		      (end-of-line)
		      (backward-character)
		      (backward-character)
		      (exchange-dot-and-mark)
		      (setq pat (concat "^" (&tags-optional-quote (region-to-string))))
		)
		(looking-at "/")
		(progn
		      (forward-character)
		      (set-mark)
		      (end-of-line)
		      (backward-character)
		      (exchange-dot-and-mark)
		      (setq pat (&tags-optional-quote (region-to-string)))
		)
		(looking-at "?^")
		(progn
		      (setq pos -1)
		      (forward-character)
		      (forward-character)
		      (set-mark)
		      (end-of-line)
		      (backward-character)
		      (backward-character)
		      (exchange-dot-and-mark)
		      (setq pat (concat "^" (&tags-optional-quote (region-to-string))))
		)
		(looking-at "?")
		(progn
		      (setq pos -1)
		      (forward-character)
		      (set-mark)
		      (end-of-line)
		      (backward-character)
		      (exchange-dot-and-mark)
		      (setq pat (&tags-optional-quote (region-to-string)))
		)
		; ancient ctags could put out a line number
		(progn
		      (set-mark)
		      (end-of-line)
		      (exchange-dot-and-mark)
		      (setq pos (- (&tags-optional-quote (region-to-string)) 1))
		)
	    )
	)
	
	(visit-file fn)
	(if (= pos -2)
	    (if (error-occured (re-search-forward pat))
		(re-search-reverse "")
	    )
	    (= pos -1)
	    (progn (end-of-file)
		   (search-reverse pat)
	    )
	    (progn
		  (beginning-of-file)
		  (provide-prefix-argument pos (next-line))
	    )
	)
	(beginning-of-line)
	(line-to-top-of-window)
    )
    
    ; goto-tag-in-buffer
    ; Similar to describe-word-in-buffer
    (goto-tag-in-buffer
	(error-occured (forward-character))
	(backward-word)
	(set-mark)
	(forward-word)
	(goto-tag (region-to-string))
    )
    
    (visit-function func
	(save-window-excursion
	    (goto-tag-in-buffer)
	    (message "Type ^C to go back")
	    (recursive-edit)
	)
    )
)
    
    ; auxiliary functions used to create and maintain the tags table
    (defun
	  (to-tag-buffer
	      (temp-use-buffer "*TAG*")
	      (if (& (= (buffer-size) 0) (= (current-file-name) ""))
		  (progn
			(if (error-occured (read-file "tags"))
			    (if (error-occured (read-file "~/tags"))
				(message "Can't read tags file")
			    )
			)
			(beginning-of-file)
			(error-occured (replace-string "*" "\\*"))
			(setq buffer-is-modified 0)
		  )
	      )
	  )
	  
	  (visit-tag-table tagfn
	      (setq tagfn (arg 1 ": visit-tag-table "))
	      (save-excursion
		  (temp-use-buffer "*TAG*")
		  (read-file tagfn)
		  (error-occured (replace-string "*" "\\*"))
		  (setq buffer-is-modified 0)
	      )
	  )
    )
