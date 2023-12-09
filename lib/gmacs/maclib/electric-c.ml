	;;;; LastEditDate="Sat Apr  2 01:26:33 1988"
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
	;;;; Three additional functions were added for use when
	;;;; editing a C file:
	;;;;
	;;;;	insert-C-comment [ESC-;] and
	;;;;	C-re-indent-line [ESC-i].
	;;;;	electric->
	;;;;
	;;;;			Tony Hansen

; load the functions common between C and C++ modes
(load "elec-c-com")

; functions specific to C mode
(defun
    (insert-C-comment				; insert a /*  */ pair
	(begin-C-comment)			; leaving the cursor
	(save-excursion				; lying between the
	    (insert-string " */")))		; comment chars

    (electric-C-/
	(if (& (eolp) (= (preceding-char) '*'))
	    (progn
		  (delete-previous-character)
		  (end-C-comment)
	    )
	    (insert-string "/")
	)
    )

    (C-high-voltage-on
	(local-bind-to-key "electric-C-semi" ';')
	(local-bind-to-key "electric-C-{" '{')
	(local-bind-to-key "electric-C-}" '}')
	(local-bind-to-key "electric-C->" '>')
	(local-bind-to-key "electric-C-*" '*')
	(local-bind-to-key "electric-C-/" '/')
	(local-bind-to-key "C-high-voltage-off" '\036')	; ^^
	(setq mode-string "electric-c,ON")
	(message "high voltage on...")
    )

    (C-high-voltage-off
	(local-bind-to-key "self-insert" ';')
	(local-bind-to-key "self-insert" '{')
	(local-bind-to-key "self-insert" '>')
	(local-bind-to-key "C-paren" '}')
	(local-bind-to-key "self-insert" '*')
	(local-bind-to-key "self-insert" '/')
	(local-bind-to-key "C-high-voltage-on" '\036')	; ^^
	(setq mode-string "electric-c")
	(message "...high voltage off")
    )

    (electric-c-mode
	(setq mode-string "electric-c")
	(use-syntax-table "C")
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
	(modify-syntax-entry  "   }/*")	; *, with /, ends comments:    */
	(remove-all-local-bindings)			; TLH
	(local-bind-to-key "C-re-indent-line" "\ei")	; TLH ESC-i
	(local-bind-to-key "backward-paren" "\e(")
	(local-bind-to-key "begin-C-comment" "\e`")
	(local-bind-to-key "C-indent" "\ej")
	(local-bind-to-key "C-paren" ')')
	(local-bind-to-key "C-paren" ']')
	(local-bind-to-key "C-paren" '}')
	(local-bind-to-key "end-C-comment" "\e'")
	(local-bind-to-key "forward-paren" "\e)")
	(local-bind-to-key "insert-C-comment" "\e;")	; TLH ESC-;
	(local-bind-to-key "C-high-voltage-on" '\036')	; ^^
	(use-abbrev-table "electric-c")
	(if C-startup-mode
	    (C-high-voltage-on))
	(novalue)
    )
)
(novalue)
