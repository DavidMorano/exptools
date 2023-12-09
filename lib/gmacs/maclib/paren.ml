	; LastEditDate="Wed Mar  3 18:26:01 1982"
	; Macro written by Tony Hansen ;
	; define find-matching-paren ;;;
(defun
    (find-matching-paren
	paren match forward level stillgoing checkchar
	(setq paren (following-char))
	(setq level 1)
	(if (= paren '(')
	    (setq match ')')
	    (= paren '[')
	    (setq match ']')
	    (= paren '{')
	    (setq match '}')
	    (= paren '<')
	    (setq match '>')
	    (= paren ')')
	    (setq match '(')
	    (= paren ']')
	    (setq match '[')
	    (= paren '}')
	    (setq match '{')
	    (= paren '>')
	    (setq match '<')
	    (error-message "Not a paren!"))
	(if (= paren '(')
	    (setq forward 1)
	    (= paren '[')
	    (setq forward 1)
	    (= paren '{')
	    (setq forward 1)
	    (= paren '<')
	    (setq forward 1)
	    (= paren ')')
	    (setq forward 0)
	    (= paren ']')
	    (setq forward 0)
	    (= paren '}')
	    (setq forward 0)
	    (= paren '>')
	    (setq forward 0))
	(if forward
	    (while level
		   (forward-character)
		   (setq checkchar (following-char))
		   (if (= checkchar 0) 
		       (error-message "End of buffer reached!")
		       (= checkchar match) 
		       (setq level (- level 1))
		       (= checkchar paren) 
		       (setq level (+ level 1))))
	    ;else
	    (while level
		   (setq checkchar (preceding-char))
		   (if (= checkchar 0) 
		       (error-message "Beginning of buffer reached!")
		       (= checkchar match)
		       (setq level (- level 1))
		       (= checkchar paren) 
		       (setq level (+ level 1)))
		   (backward-character)))
	(novalue))
)

    ;;; define show-matching-paren ;;;
(defun
    (show-matching-paren
	(save-excursion
	    (find-matching-paren)
	    (sit-for 10))
	(novalue))
)
