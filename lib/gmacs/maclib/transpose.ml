	; LastEditDate="Mon Sep 27 16:32:22 1982"
	; Macro written by Tony Hansen ;

; define transpose-lines ; ^X-^T ;
(defun
    (transpose-lines curcol
	(beginning-of-line)
	(kill-to-end-of-line) 
	(delete-next-character)
	(previous-line)
	(yank-from-killbuffer) 
	(newline))
)    
    ; define transpose-words ; ESC-t, ESC-T ;
(defun
    (transpose-words
	(save-excursion
	    (backward-word) (set-mark)		; get new first word
	    (forward-word)			; ...
	    (delete-to-killbuffer)		; ...
	    (insert-string " a ")		; spot place
	    (backward-word)			; ...
	    (backward-word)			; ...
	    (yank-from-killbuffer)		; retrieve 1st word
	    (set-mark) (forward-word)		; get new 2nd word
	    (delete-to-killbuffer)		; ...
	    (forward-word)			; ...
	    (delete-previous-character)		; get rid of spot
	    (delete-previous-character)		; ...
	    (delete-next-character)		; ...
	    (yank-from-killbuffer)))		; retrieve 2nd word
)
