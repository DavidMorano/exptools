	; LastEditDate="Thu Mar  4 13:53:22 1982"
	; Macro written by Tony Hansen ;
	; define copy-to-killbuffer ;
(defun
    (copy-to-killbuffer save-mod-flag
	(setq save-mod-flag buffer-is-modified)	; remember modified flag
	(save-excursion				; remember where we are
	    (if (error-occured (kill-region))	; check if using new kills
		(progn				; if not,
		      (delete-to-killbuffer)	;    then old delete
		      (yank-from-killbuffer))	;    followed by yank
		(yank-kill)))			; if so, use new yank
	(setq buffer-is-modified save-mod-flag) ; reset modified flag
	(novalue))
)
