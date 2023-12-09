; From hogpc!houti!ariel!vax135!floyd!harpo!seismo!hao!hplabs!sri-unix!thomas%UTAH-GR@utah-cs Thu Jul 21 02:58:02 1983
; Subject: Re: looking for modes
; Newsgroups: net.emacs
; 
; From:  thomas%UTAH-GR@utah-cs (Spencer W. Thomas)
; 
; We have a C mode which we like.  Here are some relevant info entries.
; 
; =Spencer
; 
; File: emacs	Node: utah-c-mode	Up: Packages, Previous: time, Next: writeregion
; Date: Fri Oct 15 01:43 1982
; 
; Utah-c-mode provides a number of functions tailored for editing C code.
; Most of these functions provide control over indentation.  The comment
; library is also loaded, and several local variables set to provide C
; comments (*Note comment: commentP:.).
; 
; * menu:
; * Make-c-standard-header::	A function which puts a 'standard' header
; 				at the beginning of a C program.
; * MOdification-notice::		Add a modification notice to the standard
; 				header.
; * MAKE-Includes::		Inserts #include lines painlessly.
; * MAKE-Function::		A nifty way to set up a function declaration.
; * Up-brace::			Moves up one level of block nesting backwards
; 				in the file.
; * Down-brace::			Moves up one level of block nesting forwards
; 				in the file.
; * C-Paren::			Inserts a paren-type character and shows
; 				the matching paren.
; * C-Indent::			Uses the indent command to indent the current
; 				procedure.
; * {: electric-{			Inserts a {} pair and indents, or indents
; 				the lines inside a {} pair.
; * }: electric-}			Insert a } and adjust indentation.
; * CR: C-newline			Newline, skipping the end of a comment.
; * LF: C-newline-and-indent	newline-and-indent for C mode.
; * hook: _utah-c-mode-hook	How to customize the C mode.
; 
; Variables controlling some actions are
; * bounce: paren-bounce-time	How long the cursor sits on the matching
; 				paren in c-paren.
; 
; Key bindings in utah-c-mode are:
; > C-newline-and-indent::		^J (line feed)
; > C-newline::				^M (return)
; * backward-paren::			ESC-(
; > c-indent::				ESC-j
; > c-paren::				)
; > c-paren::				]
; * comment::				ESC-;
; * dedent-to-tab-stop::			ESC-I
; * delete-comment::			^Z-;
; > down-brace::				ESC-^N
; > electric-{:: 				ESC-{
; > electric-}::				}
; * forward-paren::			ESC-)
; * global-comment::			^X-;
; * indent-nested::			tab
; * indent-new-comment::			ESC-^J
; * indent-region::			^X-tab
; * indent-to-tab-stop::			ESC-i
; * indent-under::			^X-i
; * next-comment::			ESC-n
; * previous-comment::			ESC-p
; * tab-to-tab-stop::			ESC-tab
; > up-brace::				ESC-^P
; 
; File: emacs     Node: indent     Up: Packages, Previous: incr-search, Next: info
; 
; The indentation package (tabs.ml) defines a number of general purpose
; indentation functions.
; 
; * menu:
; * dedent-line::		dedent the line by an increment (opposite of indent)
; * dedent-to-tab-stop::	re-indent the line to the previous tab stop.
; * delete-indentation::	push the line against the left margin
; * edit-tab-stops::	edit the tab-stops string.
; * indent-line::		indent the line by an increment
; * indent-nested::	create program nesting easily.
; * indent-region::	change the indentation of all the lines in the region
; * indent-to-tab-stop::	re-indent the line to the next tab stop.
; * indent-under::	re-indent the line under a specified string.
; * tab-to-tab-stop::	move to the next tab stop.
; 
; Variables:
; * indent-increment::	Multiplier used by indent-nested.
; * tab-stops::		Define tab stop positions.
; 
; File: emacs     Node: commentP     Up: Packages, Previous: c-mode, Next: dired
; Date: Fri Oct 15 01:02 1982
; 
; This package provides a number of language-independent functions for
; creating and editting comments.  The actions of the functions defined by the
; comment package depend on a number of buffer-specific variables, described
; below.  The package may be loaded explicitly, or the function load-comment
; may be defined as autoloaded.  Several language-specific packages invoke
; load-comment (*Note utah-c-mode::.) to load the comment package if it has
; not already been loaded.
; 
; 
; * menu:
; * Comment::		Create or move to the comment on the current line.
; * Delete-comment::	Kill the comment on the current line.
; * Global-comment::	Create or edit a multi-line ("global") comment.
; * Hook: _comment_hook	How to customize the comment package
; * Indent-new-comment::	Start a comment on a new line, aligned with current.
; * Next-comment::	Move to (or create) the comment on the next line.
; * Previous-comment::	ditto for previous line.
; 
;  The variables which control the behaviour of the comment package are:
; * Begin: comment-begin	The string used to begin a comment.  In C, "/* ".
; * End:   comment-end	The string used to end a comment.  In C, " */".
; * Start: comment-start	The string which starts a comment.  In C, "/*".
; * CONt:  comment-continuation	Used in multi-line comments.  In C, " * ".
; * Wrap:  dont-wrap-comments	Help for keeping comments on a single line.
; 
