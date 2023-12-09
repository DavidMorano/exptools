	;;;; LastEditDate="Sat Aug 27 14:12:05 1983"
	;;;; Macro written by Tony Hansen ;
	;;;;
	;;;; Report current line and character ; ^X-= or ESC-=
	;;;; statistics in a convenient form.
	;;;; Statistics are reported in the format of: ;
	;;;; before + current + after = total ;

(defun
    (stats linesabove linesbelow charsabove charsbelow
	   (setq linesabove 0)			; zero out variables
	   (setq linesbelow 0)			; ...
	   (setq charsabove 0)			; ...
	   (setq charsbelow 0)			; ...
	   (save-excursion
	       (beginning-of-line)		; count lines above
	       (while (! (bobp))
		      (previous-line)
		      (setq linesabove
			    (+ linesabove 1))))
	   (save-excursion
	       (end-of-line)			; count lines below
	       (error-occured (forward-character))
	       (while (! (eobp))
		      (next-line) (end-of-line)
		      (setq linesbelow
			    (+ linesbelow 1))))
	   (setq charsabove (+ 0 (dot)))	; get chars above
	   (setq charsbelow			; get chars below
		 (- (buffer-size) (dot) 1))

	   (message				; print it all out
		   (concat
			  "Lines: "		; give lines count
			  linesabove
			  " + 1 + "
			  linesbelow
			  " = "
			  (+ linesabove linesbelow 1)
			  ", characters: "	; give char count
			  charsabove
			  " + 1 + "
			  charsbelow
			  " = "
			  (buffer-size)
			  ", column: "		; give column
			  (current-column)
			  "."))
	   (novalue))
)
