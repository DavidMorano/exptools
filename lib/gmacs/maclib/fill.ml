	;;;; LastEditDate="Mon Sep 27 16:30:40 1982"
	;;;; Macro written by Tony Hansen ;
	;;;; define fill-in-paragraph and unfill-paragraph

(defun
    (fill-in-paragraph
	save-right-margin save-left-margin linenumber
	(setq save-right-margin right-margin)	; check right and
	(setq save-left-margin left-margin)	;     left margins
	(if (> save-right-margin 200)		; give right margin
	    (setq save-right-margin 77))	;     a reasonable value
	(if (>= save-left-margin		; if left margin is
		save-right-margin)		;     unreasonable,
	    (setq save-right-margin		;     reset right
		  (+ save-left-margin 77)))	;     margin
	(save-excursion
	    (prefix-argument-loop		; do prefix paragraphs
		(save-restriction
		    (while			; not at beginning of para.?
			(! (beginning-of-paragraph))
			(previous-line))	;     then get there
		    (beginning-of-line)		; mark beginning
		    (set-mark)			;     of para.
		    (while			; not at end of para.?
			(! (end-of-paragraph))	; ...
			(next-line))		;     then get there
		    (end-of-line)		; surround paragraph
		    (error-occured		; ...
			(forward-character))	; ...
		    (narrow-region)		; stuff it away
		    (setq linenumber 1)		; going to use this later
		    (beginning-of-file)		; unfill paragraph
		    (error-occured		;     get rid of tabs
			(replace-string 	;     ...
			    "\^I" " ")) 	;     ...
		    (while			;     ...
			(! (error-occured	;     get rid of spaces
			       (replace-string	;     ...
				   "  " " ")))	;     ...
			(beginning-of-file))	;     no-op to do something
		    (justify-paragraph)		; let justify do some work
		    (while			; now start filling
			(! (end-of-paragraph))	;     to end of para.
			(if (% linenumber 2)	; even/odd check
			    (&fill-in-line)	;     even = fill in
			    (&fill-out-line))	;     odd = fill out
			(setq linenumber	; advance counter
			      (+ linenumber 1))	;     ...
			(next-line))		; go to next line
		    (beginning-of-line)		; special case for last line
		    (delete-white-space)	;     ...
		    (to-col left-margin))	;     ...
		(if (> prefix-argument 1)	; if doing more than
		    (progn			;     one para.,
			(next-line)		;     go to next
			(next-line)))))		;     paragraph.
	(message "Done")			; tell about being done
	(novalue))

    ; &fill-out-line works towards the middle of a line from the outside
    ; edges, alternating adding spaces on the left and right side.
    (&fill-out-line addlspaces edge
	(beginning-of-line)			; go to beginning of line
	(if (<= (current-indent) left-margin)	;     to check left margin
	    (progn				; if not correct,
		(delete-white-space)		;     delete space there
		(to-col left-margin)))		;     & make it right
	; justify line
	(end-of-line)				; go to end of line
	(while (< (current-column)		; while not enough
		  right-margin)			;     characters on line
	       (delete-next-character)		; get some from next line
	       (delete-white-space)		;     ...
	       (insert-string " ")		;     ...
	       (end-of-line))			;     ...
	(delete-white-space)			; get rid of trailing spaces
	(if (> (current-column) right-margin)	; oops, added too much?
	    (progn				; okay, get rid of some
		(beginning-of-line)		;     ...
		(provide-prefix-argument	;     go past right margin
		    (+ right-margin 1)		;     ...
		    (forward-character))	;     ...
		(back-to-space)			;     back up
		(if (> (current-column)		; is line all one word?
		       left-margin)		; if not,
		    (newline-and-backup))))	;     add a newline
	(delete-white-space)			; get rid of white space
	; fill line
	(setq addlspaces			; figure out how many
	      (- right-margin			;     spaces need to be
		 (current-column)))		;     added
	(back-to-space)				; start at right side
	(if (<= (current-column)		; check again for
		left-margin)			;     line being
	    (setq addlspaces 0))		;     all one word
	(while					; while spaces need to
	    (> addlspaces 0)			;     be added
	    (beginning-of-line)			; set mark at beginning
	    (set-mark)				;     of line so that we
	    (end-of-line)			;     can flip/flop between
	    (setq edge 0)			; not at edge of line
	    (while				; while
		(& (> addlspaces 0)		;     still spaces
		   (! edge))			;     & not at edge
		(back-to-space)			; start at right-most space
		(if (<= (current-column)	; edge =
			left-margin)		;     left margin == curcol
		    (setq edge 1)		;     so say so
		    (progn			; otherwise,
			(insert-string " ") 	;   add a space
			(setq addlspaces	; update count
			      (- addlspaces 1))))
		(exchange-dot-and-mark)		; switch to beginning of line
		(forward-to-space)		; and left-most space
		(if (= addlspaces 0)		; oops, no spaces left to add
		    (novalue)			;     so dont do anything
		    (eolp)			; oops, end of line == edge
		    (setq edge 1)		;     so say so
		    (progn			; otherwise
			(insert-string " ") ;   add a space
			(setq addlspaces	; update count
			      (- addlspaces 1))))
		(exchange-dot-and-mark))))	; switch to end of line

    ; &fill-in-line works towards the outside of a line from the middle edges,
    ; alternating adding spaces on the left and right side of the middle
    (&fill-in-line addlspaces edgeright edgeleft middle
	(setq middle				; where is the middle?
	      (/ (- right-margin left-margin)
		 2))
	(beginning-of-line)			; go to beginning of line
	(if (<= (current-indent) left-margin)	;     to check left margin
	    (progn				; if not correct,
		(delete-white-space)		;     delete space there
		(to-col left-margin)))		;     & make it right
	; justify line
	(end-of-line)				; go to end of lien
	(while (< (current-column)		; while not enough
		  right-margin)			;     characters on line
	       (delete-next-character)		; get some from next line
	       (delete-white-space)		;     ...
	       (insert-string " ")		;     ...
	       (end-of-line))			;     ...
	(delete-white-space)			; get rid of trailing spaces
	(if (> (current-column) right-margin)	; oops, added too much?
	    (progn				; okay, get rid of some
		(beginning-of-line)		;     ...
		(provide-prefix-argument	;     go past right margin
		    (+ right-margin 1)		;     ...
		    (forward-character))	;     ...
		(back-to-space)			;     back up
		(if (> (current-column)		; is line all one word?
		       left-margin)		; if not,
		    (newline-and-backup))))	;     add a newline
	(delete-white-space)			; get rid of white space
	; fill line
	(setq addlspaces			; figure out how many
	      (- right-margin			;     spaces need to be
		 (current-column)))		;     added
	(back-to-space)				; start at right side
	(if (<= (current-column)		; check again for
		left-margin)			;     line being
	    (setq addlspaces 0))		;     all one word
	(while					; while spaces need to
	    (> addlspaces 0)			;     be added
	    (beginning-of-line)			; get to the middle of
	    (while				;     the line
		(< (current-column) middle)	;     before starting
		(forward-character))		;     ...
	    (set-mark)				; put mark there in middle
	    (setq edgeleft 0)			; not at left edge
	    (setq edgeright 0)			; not at right edge
	    (while				; while
		(& (> addlspaces 0)		;     still spaces
		   (! (& edgeright		;     & not right edge
			 edgeleft)))		;     & not left edge
		(back-to-space)			; start marching left
		(if edgeleft			; at edge
		    (novalue)			;     so do nothing
		    (<= (current-column)	; edge =
			left-margin)		;     left margin == curcol
		    (setq edgeleft 1)		;     so say so
		    (progn			; otherwise
			(insert-string " ") 	;  add a space
			(setq addlspaces	; update count
			      (- addlspaces 1))))
		(exchange-dot-and-mark)		; switch back to middle
		(forward-to-space)		; start marching right
		(if edgeright			; oops, at edge of line
		    (novalue)			;     so do nothing
		    (= addlspaces 0)		; oops, no spaces left to add
		    (novalue)			;     so do nothing
		    (eolp)			; oops, end of line == edge
		    (setq edgeright 1)		;     so say so
		    (progn			; otherwise
			(insert-string " ") 	;  add a space
			(setq addlspaces	; update count
			      (- addlspaces 1))))
		(exchange-dot-and-mark))))	; go back to left side
    ; back-to-space moves the cursor past current white
    ; space back to where white space starts in again.
    ; It stays on the current line.
    (back-to-space
	(while
	      (| (= (preceding-char) ' ')
		 (= (preceding-char) '^I'))
	      (backward-character))
	(while
	      (& (! (bolp))
		 (!= (preceding-char) ' ')
		 (!= (preceding-char) '^I'))
	      (backward-character)))

    ; forward-to-space moves the cursor forward past current white space
    ; up to where white space starts in again.
    ; It stays on the current line.
    (forward-to-space
	(while
	      (| (= (following-char) ' ')
		 (= (following-char) '^I'))
	      (forward-character))
	(while
	      (& (! (eolp))
		 (!= (following-char) ' ')
		 (!= (following-char) '^I'))
	      (forward-character)))

    ; beginning-of-paragraph tells when the current line is at the beginning
    ; of a paragraph. Indented lines at the beginning of a paragraph are
    ; handled correctly.
    (beginning-of-paragraph
	(save-excursion
	    (|  (>  (current-indent) ; check for indented line
		    left-margin)
		(progn		; check if at beginning of buffer
		    (previous-line)
		    (beginning-of-line)
		    (bobp))
		(progn		     ; check for n/troff line
		    (beginning-of-line)
		    (looking-at "[.']"))
		(=  (preceding-char) ; check for page break
		    '^L')
		(progn		; check if on a blank line
		    (end-of-line)
		    (=	(current-column)
			(current-indent))))))

    ; end-of-paragraph tells when the current line is at the end
    ; of a paragraph. Indented lines at the beginning of a paragraph
    ; are handled correctly.
    (end-of-paragraph
	(save-excursion
	    (next-line)
	    (end-of-line)
	    (| (eobp)		; check end of buffer
	       (= (current-column) ; check if on a blank line
		  (current-indent))
	       (> (current-indent) ; check for indented line
		  left-margin)
	       (progn
		     (beginning-of-line) ; check for page break
		     (looking-at ".*\^L"))
	       (looking-at "[.']")
	    )))
)

; unfill-paragraph removes all blanks and tabs from
; a paragraph which had been previously filled.
(defun
    (unfill-paragraph
	(save-excursion
	    (save-restriction
		(while				; go to beginning of para.
		    (! (beginning-of-paragraph))
		    (previous-line))
		(beginning-of-line)			; mark off beginning
		(set-mark)				;    of para.
		(while				; not at end of para.?
		    (! (end-of-paragraph))		;    ...
		    (next-line))			;    then get there
		(end-of-line)			; surround paragraph
		(error-occured 			;    ...
		    (forward-character))		;    ...
		(narrow-region)			; move para. to temp buffer
		(beginning-of-file)
		(error-occured			; get rid of tabs
		    (replace-string "\^I" " "))	;     ...
		(while				; get rid of extra spaces
		    (! (error-occured		;     ...
			   (replace-string	;     ...
			       "  " " ")))	;     ...
		    (beginning-of-file))	;     no-op for while
		(while				; get rid of spaces at
		    (! (eobp))		;     ...
		    (beginning-of-line)	;     beginning of each line
		    (delete-white-space)	;     ...
		    (next-line))))		;     ...
	(message "Done")
	(sit-for 0)
	(novalue))
)
