	;;;; LastEditDate="Sat Apr  2 01:26:32 1988"
	;;;;
	;;;; A C++ mode based on C mode
	;;;;
	;;;; Three styles of brace indenting are allowed. To get a
	;;;; particular style of brace indenting, execute the following
	;;;; before loading electric-c:
	;;;;
	;;;;     (set-default C-style 0) (the default), or
	;;;;     (set-default C-style 1) or
	;;;;     (set-default C-style 2)
	;;;;
	;;;; C-style 0:
	;;;;
	;;;;    while (i > 0)
	;;;;        {
	;;;;        printf("hello #%d",i--);
	;;;;        }
	;;;;
	;;;; C-style 1:
	;;;;
	;;;;    while (i > 0) {
	;;;;        printf("hello #%d",i--);
	;;;;    }
	;;;;
	;;;; C-style 2:
	;;;;
	;;;;    while (i > 0)
	;;;;    {
	;;;;        printf("hello #%d",i--);
	;;;;    }
	;;;;
	;;;; The default indentation size is 4. To change it,
	;;;; execute the following before loading electric-c:
	;;;;
	;;;;    (set-default C-indent-size 8)
	;;;;
	;;;; C++ mode usually comes up with electricity turned off.
	;;;; To change this, execute the following before loading electric-c:
	;;;;
	;;;;    (set-default C++-startup-mode 8)
	;;;;
	;;;;			Tony Hansen

; load the functions common between C and C++ modes
(load "elec-c-com")

; functions specific to C++ mode
(defun
    (electric-C++-newline
	(if (= &C-comment-state 2)
	    (end-C++-comment))
	(newline)
    )

    (electric-C++-newline-and-indent
	(if (= &C-comment-state 2)
	    (end-C++-comment))
	(C-newline-and-indent)
    )

    (electric-C++-/
	(if (eolp)
	    (if (= (preceding-char) '*')
		(progn
		      (delete-previous-character)
		      (end-C-comment)
		)
		(= (preceding-char) '/')
		(progn
		      (delete-previous-character)
		      (begin-C++-comment)
		)
		(insert-string "/")
	    )
	    (insert-string "/")
	)
    )

    (begin-C++-comment
	(move-to-comment-column)
	(setq left-margin (current-column))
	(setq right-margin 78)
	(setq prefix-string "// ")
	(insert-string "// ")
	(setq &C-comment-state 2)
    )

    (end-C++-comment
	(setq right-margin 1000)
	(setq prefix-string "")
	(setq left-margin 0)
	(setq &C-comment-state 0)
    )

    (C++-high-voltage-on
	(local-bind-to-key "electric-C-semi" ';')
	(local-bind-to-key "electric-C-{" '{')
	(local-bind-to-key "electric-C-}" '}')
	(local-bind-to-key "electric-C->" '>')
	(local-bind-to-key "electric-C-*" '*')
	(local-bind-to-key "electric-C++-/" '/')
	(local-bind-to-key "C++-high-voltage-off" '\036')	; ^^
	(setq mode-string "electric-C++,ON")
	(message "high voltage on...")
    )

    (C++-high-voltage-off
	(local-bind-to-key "self-insert" ';')
	(local-bind-to-key "self-insert" '{')
	(local-bind-to-key "self-insert" '>')
	(local-bind-to-key "C-paren" '}')
	(local-bind-to-key "self-insert" '*')
	(local-bind-to-key "self-insert" '/')
	(local-bind-to-key "C++-high-voltage-on" '\036')	; ^^
	(setq mode-string "electric-C++")
	(message "...high voltage off")
    )

    (electric-C++-mode
	(setq mode-string "electric-C++")
	(use-syntax-table "C++")
	(modify-syntax-entry  "()   (")
	(modify-syntax-entry  ")(   )")
	(modify-syntax-entry  "(}   {")
	(modify-syntax-entry  "){   }")
	(modify-syntax-entry  "(]   [")
	(modify-syntax-entry  ")[   ]")
	(modify-syntax-entry  """    '")
	(modify-syntax-entry  """    """)
	(modify-syntax-entry  "\\    \\")
	(modify-syntax-entry  "w    _")			; TLH
	(modify-syntax-entry  "  { */")	; /, with *, begins comments: /*
	;(modify-syntax-entry  "  { //"); /, with /, begins comments: //
	(modify-syntax-entry  "   }/*")	; *, with /, ends comments:    */
	(remove-all-local-bindings)			; TLH
	(local-bind-to-key "C-re-indent-line" "\ei")	; TLH ESC-i
	(local-bind-to-key "backward-paren" "\e(")
	(local-bind-to-key "begin-C++-comment" "\e`")
	(local-bind-to-key "C-indent" "\ej")
	(local-bind-to-key "C-paren" ')')
	(local-bind-to-key "C-paren" ']')
	(local-bind-to-key "C-paren" '}')
	(local-bind-to-key "end-C++-comment" "\e'")
	(local-bind-to-key "forward-paren" "\e)")
	(local-bind-to-key "C++-high-voltage-on" '\036')	; ^^
	(local-bind-to-key "electric-C++-newline" "\r")
	(local-bind-to-key "electric-C++-newline-and-indent" "\n")
	(use-abbrev-table "electric-C++")
	(if C-startup-mode
	    (C++-high-voltage-on))
	(novalue)
    )
)
(novalue)
