	; LastEditDate="Wed Mar  3 18:27:58 1982"
	; Macro written by Tony Hansen ;
	; define set-up-defun ; [unbound] ;
(defun
    (set-up-defun fun-name
	(setq fun-name (arg 1 "Function name: ")) (newline)
	(insert-string (concat (concat "\^I; define " fun-name) " ;"))
	(newline)
	(insert-string "(defun") (newline)
	(insert-string (concat "    (" fun-name)) (newline)
	(insert-string "\^I(")
	(novalue)
    )
)
