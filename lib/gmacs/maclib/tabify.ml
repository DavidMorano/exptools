	;;;; LastEditDate="Tue Jun  4 20:56:10 1991"
	;;;; Macros written by Tony Hansen
	;;;;
	;;;; tabify-line	change leading white space to tabs & blanks
	;;;; untabify-line	change leading white space to blanks
	;;;; strip-file		tabify leading blanks and strip trailing
	;;;;			blanks from buffer

; define tabify-line ; [unbound] ;
(defun
    (tabify-line curind
	(setq curind (current-indent))		; where does line start?
	(save-excursion
	    (beginning-of-line)			; replace spaces
	    (delete-white-space)		; ...
	    (to-col curind))			; with tabs
	(novalue))
)

; define untabify-beginning-of-line ; [unbound] ;
(defun
    (untabify-beginning-of-line curind
	(setq curind (- (current-indent) 1))	; where does line start?
	(save-excursion
	    (beginning-of-line)			; replace tabs
	    (delete-white-space)		; ...
	    (provide-prefix-argument  curind	; with spaces
		(insert-character ' ')))	; ...
	(novalue))
)

; define strip-file ; [unbound] ;
(defun
    (strip-file
	(save-excursion
	    (beginning-of-file)				; start at beginning
	    (while (! (eobp))				; for entire file
		   (tabify-line)			; get rid of leading
		   (end-of-line)			; get rid of trailing
		   (delete-white-space)
		   (next-line)))
	(novalue))
)
