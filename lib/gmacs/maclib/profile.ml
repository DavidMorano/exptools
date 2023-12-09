	; LastEditDate="Thu Jun  6 12:21:23 1991"

	; Set up library directory name - used by newshell.ml
(setq-default gemacs-library-directory "$TOOLS/lib/gmacs/lib") 

	; Load these packages from the regular macro library ;
(defun (help (info)))
(setq-default nrings 10)
(load "killring")
(setq-default &kill-lines-magic 1)

	; Load these packages LATER from the regular macro library ;
(autoload "add-tag"				"tags")
(autoload "backward-to-character"		"lgoto") 
(autoload "baseconvert"				"base")
(autoload "buffer-edit"				"buffer-edit")
(autoload "capitalize-word"			"capword")
(autoload "center-line"				"centre-line")
(autoload "centre-line"				"centre-line")
(autoload "copy-to-killbuffer"			"copy")
(autoload "ctags-to-tags"			"ctagstotags")
(autoload "define-db"				"database")
(autoload "delete-backward-changing-tabs"	"del")
(autoload "delete-blank-lines"			"del")
(autoload "delete-matching-lines"		"del")
(autoload "dired"				"dired")
(autoload "do-plus-args"			"doplusargs")
(autoload "electric-C++-mode"			"elec-c++")
(autoload "electric-c-mode"			"electric-c")
(autoload "electric-lisp-mode"			"electric-lisp")
(autoload "electric-lisp-mode"			"locallisp")
(autoload "electric-mlisp-mode"			"electric-lisp")
(autoload "electric-mlisp-mode"			"locallisp")
(autoload "electric-pascal-mode"		"pascal")
(autoload "encrypted-insert-file"		"encrypt")
(autoload "encrypted-visit-file"		"encrypt")
(autoload "encrypted-write-file"		"encrypt")
(autoload "fill-in-paragraph"			"fill")
(autoload "find-control-character"		"findctl")
(autoload "for-all-files"			"forall")
(autoload "forward-to-character"		"lgoto")
(autoload "goto-column"				"goto")
(autoload "goto-line"				"goto")
(autoload "goto-percent"			"goto")
(autoload "goto-tag"				"tags")
(autoload "hexadize"				"base")
(autoload "incremental-search"			"incr-search")
(autoload "indent-region"			"ind-region")
(autoload "interactive-shell"			"newshell")
(autoload "join-lines"				"join")
(autoload "line-to-bottom-of-window"		"line-bot")
(autoload "lower-case-word"			"capword")
(autoload "make-tag-table"			"tags")
(autoload "manual-entry"			"man")
(autoload "middle-of-window"			"lgoto") 
(autoload "name-keybd-macro"			"namekbd")
(autoload "new-redraw-display"			"redraw")
(autoload "new-undo"				"undo")
(autoload "new-visit-file"			"visit")
(autoload "next-file"				"nextfile")
(autoload "nroff-mode"				"nroff")
(autoload "octalize"				"base")
(autoload "one-line-buffer-list"		"buff")
(autoload "ovwt-mode"				"ovwtmode")
(autoload "parenthesize-word"			"srndword")
(autoload "postnews"				"postnews")
(autoload "previous-file"			"nextfile")
(autoload "query-db"				"database")
(autoload "quotify-word"			"srndword")
(autoload "recompute-all-tags"			"tags")
(autoload "redraw-window"			"redraw")
(autoload "reset-modified"			"revert")
(autoload "reverse-incremental-search"		"incr-search")
(autoload "revert-file"				"revert")
(autoload "scribe-mode"				"scribe")
(autoload "search-next"				"search")
(autoload "search-previous"			"search")
(autoload "shell"				"shell")
(autoload "shift-line-left"			"shift")
(autoload "shift-line-right"			"shift")
(autoload "spell"				"spell")
(autoload "split-lines"				"join")
(autoload "squeeze-mlisp-file"			"squeeze")
(autoload "srccom"				"srccom")
(autoload "stats"				"stats")
(autoload "strip-file"				"tabify")
(autoload "tabify-line"				"tabify")
(autoload "transpose-line"			"transp")
(autoload "transpose-windows"			"transp")
(autoload "transpose-word"			"transp")
(autoload "underscore-region"			"under")
(autoload "underscore-word"			"under")
(autoload "untabify-line"			"tabify")
(autoload "upper-case-word"			"capword")
(autoload "visit-function"			"tags")
(autoload "visit-tag-file"			"tags")
(autoload "write-region-to-file"		"writeregion")

	; Give bindings to non-default functions ;
	; First bind the various flavors of searches ;
(bind-to-key "incremental-search"		"\e\^S")	; ESC-^S
(bind-to-key "reverse-incremental-search"	"\e\^R")	; ESC-^R
(bind-to-key "re-search-forward"		"\^X\S")	; ^X-S
(bind-to-key "re-search-forward"		"\^X\R")	; ^X-R
(bind-to-key "search-next"			"\en")		; ESC-n
(bind-to-key "search-previous"			"\ep")		; ESC-p

	; Now bind the various flavors of replaces ;
(bind-to-key "re-replace-string"		"\eR")		; ESC-R
(bind-to-key "re-query-replace-string"		"\eQ")		; ESC-Q

	; Now bind the various flavors of case manipulations
(bind-to-key "capitalize-word"			"\eC")		; ESC-C
(bind-to-key "case-word-capitalize"		"\ec")		; ESC-c
(bind-to-key "lower-case-word"			"\eL")		; ESC-L
(bind-to-key "upper-case-word"			"\eU")		; ESC-U

	; Now bind the various flavors of deletes
(bind-to-key "delete-backward-changing-tabs"	"\177")		; change DEL
(bind-to-key "delete-blank-lines"		"\e\^O")	; ESC-^O
(bind-to-key "delete-buffer"			"\^XD")		; ^X-D
(bind-to-key "delete-white-space"		"\e\\")		; ESC-\
(bind-to-key "delete-matching-lines"		"\e\^D")	; ESC-^D

	; Now bind the various flavors of gotos
(bind-to-key "backward-to-character"		"\e\^]")	; ESC-^]
(bind-to-key "forward-to-character"		"\^]")		; ^]
(bind-to-key "goto-column"			"\e|")		; ESC-|
(bind-to-key "goto-line"			"\e#")		; ESC-#
(bind-to-key "goto-percent"			"\e%")		; ESC-%
(bind-to-key "goto-tag"				"\eG")		; ESC-G
(bind-to-key "middle-of-window"			"\em")		; ESC-m
(bind-to-key "next-file"			"\e\^N")	; ESC-^N
(bind-to-key "previous-file"			"\e\^P")	; ESC-^P

	; Now bind the various flavors of help
(bind-to-key "describe-command"			"\eO")		; ESC-O
(bind-to-key "describe-key"			"\eo")		; ESC-o

	; Now bind other functions
(bind-to-key "buffer-edit"			"\^X\^B")	; ^X-^B
(bind-to-key "copy-region"			"\ep")		; ESC-p
(bind-to-key "define-local-abbrev"		"\^X\^A")	; ^X-^A
(bind-to-key "delete-previous-word"		"\e\^?")	; ESC-RUBOUT
(bind-to-key "fill-in-paragraph"		"\eP")		; ESC-P
(bind-to-key "interactive-shell"		"\e=")		; ESC-=
(bind-to-key "join-lines"			"\eJ")		; ESC-J
(bind-to-key "new-redraw-display"		"\^L")		; ^L
(bind-to-key "new-undo"				"\^X\^U")	; ^X-^U
(bind-to-key "new-visit-file"			"\^X\^V")	; ^X-^V
(bind-to-key "quotify-word"			"\e\"")		; ESC-"
(bind-to-key "reset-modified"			"\e~")		; ESC-~
(bind-to-key "return-to-monitor"		"\e\^-")	; ESC-^_; 
(bind-to-key "shift-line-left"			"\^X<")		; ^X-<
(bind-to-key "shift-line-right"			"\^X>")		; ^X->
(bind-to-key "split-lines"			"\eS")		; ESC-S
(bind-to-key "srccom"				"\e+")		; ESC-+
(bind-to-key "stats"				"\^X=")		; ^X-=
(bind-to-key "transpose-line"			"\^X\^T")	; ^X-^T
(bind-to-key "transpose-word"			"\et")		; ESC-t
(bind-to-key "underscore-word"			"\e_")		; ESC-_

	; Set the values of various global variables ;
(progn
    (setq ask-about-buffer-names	0)
    (setq backup-before-writing		1)
    (setq backup-by-copying-when-linked	1)
    (setq ctlchar-with-^		1)
    (setq-default C-style		0)
    (setq files-should-end-with-newline	1)
    (setq-default mode-line-format	" %<r(Read-only) %>%<n(Narrowed) %>%<e%D %>Buffer: %b        %M (%m)    %p %*")
    (setq mode-line-format		" %<r(Read-only) %>%<n(Narrowed) %>%<e%D %>Buffer: %b        %M (%m)    %p %*")
    (setq quick-redisplay		1)
    (setq stack-trace-on-error		0)
    (setq track-eol-on-^N-^P		0)
    (setq unlink-checkpoint-files	1)
    (setq wrap-long-lines		1)
)

	; These functions will be automatically executed when a ;
	; file matching the given pattern is loaded in. ;
(auto-execute "text-mode"			"/tmp/*")
(auto-execute "text-mode"			"/usr/tmp/*")
(auto-execute "do-plus-args"			"+*")
(auto-execute "electric-pascal-mode"		"*.p")
(auto-execute "electric-c-mode"			"*.c")
(auto-execute "electric-C++-mode"		"*.C")
(auto-execute "electric-c-mode"			"*.h")
(auto-execute "electric-C++-mode"		"*.H")
(auto-execute "electric-lisp-mode"		"*.l")
(auto-execute "electric-mlisp-mode"		"*.emacs_pro")
(auto-execute "electric-mlisp-mode"		"*.ml")
(auto-execute "nroff-mode"			"*.man")
(auto-execute "nroff-mode"			"*.mm")
(auto-execute "nroff-mode"			"*.nr")
(auto-execute "nroff-mode"			"*.tr")
(auto-execute "nroff-mode"			"*.tbl")
(auto-execute "nroff-mode"			"*.doc")
(auto-execute "nroff-mode"			"*.vgs")
(auto-execute "nroff-mode"			"*.1")
(auto-execute "nroff-mode"			"*.1c")
(auto-execute "nroff-mode"			"*.1m")
(auto-execute "nroff-mode"			"*.2")
(auto-execute "nroff-mode"			"*.3")
(auto-execute "nroff-mode"			"*.4")
(auto-execute "nroff-mode"			"*.5")
(auto-execute "nroff-mode"			"*.6")
(auto-execute "nroff-mode"			"*.7")
(auto-execute "nroff-mode"			"*.8")
(auto-execute "scribe-mode"			"*.mss")
(auto-execute "text-mode"			"*mbox")
(auto-execute "text-mode"			"*.txt")
(auto-execute "text-mode"			"Message*")

; reset minibuf keymaps to allow Meta functions
(progn
    (save-window-excursion
	(use-global-map "Minibuf-local-NS-map")
	(bind-to-key "ESC-prefix" "\e")
	(use-global-map "Minibuf-local-map")
	(bind-to-key "ESC-prefix" "\e")
	(use-global-map "default-global-keymap")
    )
)

(quietly-read-abbrev-file ".abbrevs")
(quietly-read-abbrev-file "~/.abbrevs")

(set "prepend-extension" 1)
(novalue)
