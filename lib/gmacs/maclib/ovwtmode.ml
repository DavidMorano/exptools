	; LastEditDate="Mon Sep 27 16:31:33 1982"
	; Macro mode written by Tony Hansen ;
	; define functions necessary for overwrite mode ;;;

(defun
    (ovwt-mode i
	(remove-all-local-bindings)
	(setq mode-string "ovwt")
	(setq i 32)
	(while (< i 127)
	    (local-bind-to-key "overwrite-character" i)
	    (setq i (+ i 1)))
	(local-bind-to-key "ovwt-tab" '^I')			      ; ^I
	(local-bind-to-key "ovwt-delete-backward" '^?')		      ; ^?
	(local-bind-to-key "ovwt-delete-backward" '^H')		      ; BS, ^H
	(local-bind-to-key "ovwt-delete-forward" '^D')		      ; ^D
	(local-bind-to-key "ovwt-del-word-backward" "\e\^?")          ; ESC-^?
	(local-bind-to-key "ovwt-del-word-backward" "\eH")	      ; ESC-H
	(local-bind-to-key "ovwt-del-word-backward" "\eh")	      ; ESC-h
	(local-bind-to-key "ovwt-del-word-forward" "\eD")	      ; ESC-D
	(local-bind-to-key "ovwt-del-word-forward" "\ed")	      ; ESC-d
	(local-bind-to-key "delete-next-character" "\e\^D")	      ; ESC-^D
	(local-bind-to-key "delete-previous-character" "\e\^H")	      ; ESC-^H
	(local-bind-to-key "ovwt-nextline" '^N')		      ; ^N
	(local-bind-to-key "ovwt-previousline" '^P')		      ; ^P
	(novalue)
    )
)
(defun
    (overwrite-character
	(prefix-argument-loop
	    (if (= (following-char) '^I')
		(progn (ovwt-del-tab-forward) (backward-character)))
	    (if (! (eolp)) (delete-next-character))
	    (insert-character (last-key-struck) ) ))
)
(defun
    (overwrite-char-with-arg
	(if (= (following-char) '^I')
	    (progn (ovwt-del-tab-forward) (backward-character)))
	(if (! (eolp)) (delete-next-character))
	(insert-character (arg 1)))
)
(defun
    (ovwt-tab i
	(prefix-argument-loop
	    (setq i (- 8 (% (current-column) 8)))
	    (while i (overwrite-char-with-arg ' ') (setq i (- i 1) ) ) ))
)
(defun
    (ovwt-del-tab-forward i
	(setq i (- 8 (% (current-column) 8)))
	(delete-next-character)
	(while i (insert-string " ") (backward-character) (setq i (- i 1)))
	(insert-string " "))
)
(defun
    (ovwt-del-tab-backward i
	(backward-character)
	(setq i (- 8 (% (current-column) 8)))
	(delete-next-character)
	(while i (insert-string " ") (setq i (- i 1)))
	(insert-string " ") (backward-character))
)
(defun
    (ovwt-delete-backward
	(prefix-argument-loop
	    (if (bobp) (abort-operation)
		(bolp) (backward-character)
		(= (preceding-char) '^I') (ovwt-del-tab-backward)
		(progn (delete-previous-character) (insert-string " ")
		    (backward-character) ) ) ))
)
(defun
    (ovwt-delete-forward
	(prefix-argument-loop
	    (if (eobp) (abort-operation)
		(eolp) (forward-character)
		(= (following-char) '^I') (ovwt-del-tab-forward)
		(progn (delete-next-character) (insert-string " ") ) ) ))
)
(defun
    (ovwt-del-word-backward loopctl char
	(prefix-argument-loop
	    (while (! (save-excursion
			  (backward-character)
			  (looking-at "\w")))
		(ovwt-delete-backward))
	    (setq loopctl 1)
	    (while loopctl
		(setq char (preceding-char))
		(if (bobp)
		    (setq loopctl 0)
		    (bolp)
		    (backward-character)
		    (save-excursion 
			(backward-character)
			(looking-at "\w"))
		    (ovwt-delete-backward)
		    ; else
		    (setq loopctl 0) ) ) ))
)
(defun
    (ovwt-del-word-forward loopctl char
	(prefix-argument-loop
	    (while (! (looking-at "\w"))
		(ovwt-delete-forward) )
	    (setq loopctl 1)
	    (while loopctl
		(setq char (following-char))
		(if (eobp) (setq loopctl 0)
		    (eolp) (forward-character)
		    (looking-at "\w") (ovwt-delete-forward)
		    (setq loopctl 0)))))
)
(defun
    (ovwt-nextline oldcol
	(setq oldcol (current-column))
	(provide-prefix-argument prefix-argument (next-line))
	(if (!= oldcol (current-column)) (to-col oldcol))
    )
)
(defun
    (ovwt-previousline oldcol
	(setq oldcol (current-column))
	(provide-prefix-argument prefix-argument (previous-line))
	(if (!= oldcol (current-column)) (to-col oldcol))
    )
)
(defun
    (ovwt-off i
	(remove-all-local-bindings)
	(setq mode-string "Normal")
	(novalue)
    )
)
