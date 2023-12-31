	;;;; LastEditDate="Tue Jun  4 16:04:47 1991"
;	In the distant past Andy Witkin from SRI wrote an initial
; 	version of the Info system.  This one is a total rewrite
;	by James Gosling (5/5/82).  Only a few names remain the same.

(message "Loading INFO, please wait...")
(sit-for 0)

(extend-database-search-list "info" "$TOOLS/lib/gmacs/databases/info");

(setq-default info-root-file "dir")
(setq-default &info-file info-root-file)
(setq-default &info-node "Top")
(setq-default &info-camefrom "")
(setq-default &info-doedit 0)

(defun (info (&info "dir" "top")))
(defun (describe-command
	   (&info "emacs" (get-tty-command ": describe-command "))))
(defun (describe-variable
	   (&info "emacs" (get-tty-variable ": describe-variable "))))

(defun
    (&info m fn i
	   (setq fn (arg 1))
	   (setq m (arg 2))
	   (save-window-excursion
	       (delete-other-windows)
	       (temp-use-buffer "*info-stack*")
	       (erase-buffer)
	       (switch-to-buffer "INFO")
	       (setq &info-camefrom "")
	       (find-node)
	       (if (is-bound &info-running)
		   (message "Recursive INFO call punted.")
		   (progn &info-running
			  (message "Type '^C' to resume editing, 'h' for help with INFO")
			  (sit-for 0)
			  (message "Type '^C' to resume editing, 'h' for help with INFO")
			  (recursive-edit)))
	   )
    )
)

(defun (#info-enable-edit
	(setq &info-doedit 1)
	(local-bind-to-key "#info-^r" "\e\^e")
	(message "Database editing enabled")))

(defun
    (#info-^r
     (use-local-map "&info-editing")
     (setq mode-line-format
	   (concat  "  INFO edit    File: "
	       &info-file
	       "   Node: "
	       &info-node
	       "   %M  %[%p%]"))
     (message "Type ^C to resume info")
     (use-syntax-table "text-mode")
     (save-excursion (recursive-edit))
     (use-syntax-table "info-syntax-table")
     (use-local-map "&info-commands")
     (if (& buffer-is-modified
	    (= (substr (get-tty-string "Save changes? ") 1 1) "y"))
	 (progn key
		(beginning-of-file)
		(set-mark)
		(insert-string &info-file ":" &info-node)
		(case-region-lower)
		(setq key (region-to-string))
		(erase-region)
		(put-database-entry "info" key)))
     (setq mode-line-format "   INFO     Node: %m       %M  %p")
    )
)

(defun
    (#info-g fn m s
     (setq s (get-tty-string "Node: "))
     (setq m "Top")(setq fn 0)
     (save-excursion
	 (temp-use-buffer "Hack Buffer")
	 (setq needs-checkpointing 0)
	 (setq case-fold-search 1)
	 (erase-buffer)
	 (use-syntax-table "info-syntax-table")
	 (insert-string s)
	 (beginning-of-line)
	 (get-node-and-file)
     )
     (find-node))
)

(defun
    (#info-h fn m
     (setq fn "info")
     (setq m "help")
     (find-node))
)

(defun
    (#info-hlp fn m
     (setq fn "cmds")
     (setq m "top")
     (find-node))
)

(defun
    (#info-d fn m
     (setq &info-camefrom "")
     (setq fn info-root-file)
     (setq m "Top")
     (find-node))
)

(defun
    (#info-l fn m dot
     (save-excursion 
	 (temp-use-buffer "*info-stack*")
	 (end-of-file)
	 (re-search-reverse ";\\(\\w\\w*\\),\\(\\w\\w*\\),\\(\\w\\w*\\);")
	 (region-around-match 1)
	 (setq dot (region-to-string))
	 (region-around-match 2)
	 (setq fn (region-to-string))
	 (region-around-match 3)
	 (setq m (region-to-string))
	 (region-around-match 0)
	 (end-of-file)
	 (erase-region)
     )
     (setq &info-camefrom "")
     (find-node)
     (goto-character dot))
)

(defun
    (#info-@ path m
     (setq path (get-tty-string "Path: "))
     (save-excursion
	 (temp-use-buffer "Hack Buffer")
	 (erase-buffer)
	 (insert-string path " ")
	 (beginning-of-file)
	 (while (! (error-occured (temp-use-buffer "Hack Buffer")
		       (re-search-forward "[ ]*\\(.[^ ]*\\)")))
		(region-around-match 1)
		(setq m (region-to-string))
		(if (error-occured 
			(temp-use-buffer "INFO")
			(&info-goto-menu-item))
		    (error-message "No such menu item: " m)))
     )
     (beginning-of-file))
)

(defun
    (#info-m m
     (setq m (get-tty-string "Menu item: "))
     (&info-goto-menu-item))
)

(defun (#info-mouse-menu ldot
	(setq ldot (dot))
	(beginning-of-line)
	(if (bobp)
	    (progn
		  (set-mark)
		  (end-of-line)
		  (narrow-region)
		  (goto-character ldot)
		  (re-search-reverse "[\t,:]")
		  (search-forward ":")
		  (widen-region)
		  (get-node-and-file)
		  (find-node)
	    )
	    (if (looking-at "^* \\(\\w*\\):")
		(progn
		      (re-search-forward "")
		      (if (= (following-char) ':')
			  (progn (setq fn "")
				 (region-around-match 1)
				 (setq m (region-to-string)))
			  (get-node-and-file))
		      (setq &info-camefrom "     Up: ")
		      (find-node))
		(error-message "No menu item on this line"))
	))
)

(defun
    (&info-goto-menu-item fn
	(if (error-occured
		(beginning-of-file)
		(search-forward  (concat (char-to-string 10)
					 "* menu:")))
	    (error-message "This node has no menu."))
	(if (error-occured
		(re-search-forward
		    (concat "^* \\(" m "\\w*\\):")))
	    (error-message "No such menu item: " m))
	(if (= (following-char) ':')
	    (progn (setq fn "")
		   (region-around-match 1)
		   (setq m (region-to-string)))
	    (get-node-and-file))
	(setq &info-camefrom "     Up: ")
	(find-node))
)

(defun
    (get-node-and-file
	(if (looking-at "[ ]*(\\(\\w*\\))[ ]*\\(\\w*\\)")
	    (progn 
		   (region-around-match 1)
		   (setq fn (region-to-string))
		   (region-around-match 2)
		   (if (| (= fn "dir")
			  (= fn "Dir")
			  (= fn "DIR"))
		       (setq fn info-root-file))
	    )
	    (looking-at "[ ]*\\(\\w*\\)")
	    (progn
		  (region-around-match 1)
		  (setq fn "")
	    )
	    (error-message "Missing node specification.")
	)
	(setq m (region-to-string))
	(if (= m "") (setq m "top"))
    )
)

(defun
    (#info-f m fn
     (setq m (get-tty-string "Footnote: "))
     (save-excursion
	 (beginning-of-file)
	 (if (error-occured (re-search-forward
				(concat "*note \\(" m "\\w*\\):")))
	     (error-message "No such footnote: " m))
	 (if (= (following-char) ':')
	     (progn (setq fn "")
		    (region-around-match 1)
		    (setq m (region-to-string)))
	     (get-node-and-file))
     )
     (setq &info-camefrom "")
     (find-node))
)

(defun
    (#info-p m fn
     (setq m "Top")
     (beginning-of-file)
     (end-of-line)
     (if (error-occured
	     (re-search-reverse "Prev[ious]*:"))
	 (error-message "This node has no previous."))
     (search-forward "")
     (get-node-and-file)
     (setq &info-camefrom "     Next: ")
     (find-node))
)

(defun
    (#info-n m fn
     (setq m "Top")
     (beginning-of-file)
     (end-of-line)
     (if (error-occured
	     (search-reverse "Next:"))
	 (error-message "This node has no next."))
     (search-forward "")
     (get-node-and-file)
     (setq &info-camefrom "     Previous: ")
     (find-node))
)

(defun
 (#info-u m fn
   (setq m "Top")
   (beginning-of-file)
   (end-of-line)
   (if (error-occured
	 (search-reverse "Up:"))
       (error-message "This node has no up."))
   (search-forward "")
   (get-node-and-file)
   (find-node))
)

(defun
    (find-node dot sav file execstr
	(setq dot (dot))
	(setq sav 0)
	(if (error-occured key keyc
		(switch-to-buffer "INFO")
		(erase-buffer)
		(set-mark)
		(insert-string (if (= "" fn) &info-file fn) ":" m)
		(setq keyc (region-to-string))
		(case-region-lower)
		(setq key (region-to-string))
		(erase-buffer)
		(if (error-occured (fetch-database-entry "info" key))
		    (fetch-database-entry "info" keyc))
	    )
	    (progn
		  (switch-to-buffer "INFO")
		  (if (& &info-doedit
			 (= (substr (progn
					  (message "Asking.....XXXXXX")
					  (sit-for 1)
				   (get-tty-string "Not found, should I create it? ")) 1 1) "y"))
		      (&info-make-node)
		      (progn lfn lm
			     (setq lfn fn)
			     (setq lm m)
			     (error-occured 
				 (if (& (!= &info-node m)
					(| (= fn "") (!= &info-file fn)))
				     (progn (setq fn &info-file)
					    (setq m &info-node)
					    (find-node))))
			     (error-message "No information on ("
				 (if (= lfn "") &info-file lfn)
				 ") " lm)
		      )))
	)
	(if (!= fn "") (setq &info-file fn))
	(setq &info-node m)
	(setq mode-string m)
	(temp-use-buffer "*info-stack*")
	(end-of-file)
	(insert-string ";" (+ dot 0) ","  &info-file "," &info-node)
	(switch-to-buffer "INFO")
	(beginning-of-file)
	(if (!= execstr "")
	    (error-occured
		(execute-mlisp-line execstr)))
	(setq mode-line-format "   INFO     Node: %m       %M  %p")
    )
)

(defun (convert-ITS-info-file fn
	   (setq fn (current-buffer-name))
	   (beginning-of-file)
	   (setq case-fold-search 1)
	   (error-occured 
	       (while 1
		      (progn node HasCode
			     (re-search-forward "\^_\^_*\\|\^L")
			     (setq HasCode (= (preceding-char) '^L'))
			     (re-search-forward "[\^_\^L\n\t ]*")
			     (set-mark)
			     (if HasCode (re-search-forward "\^_[\^_\^L\n\t ]*"))
			     (save-excursion
			     (if (! (looking-at ".*node: *\\([^,\n\t]*\\)"))
				 (error-message "bad format"))
			     (region-around-match 1)
			     (case-region-lower)
			     (setq node (region-to-string))
			     (beginning-of-line)
			     (if (looking-at ".*file:[ \t]*\\([^, \t\n]*\\)")
				 (progn
				       (region-around-match 1)
				       (case-region-lower)
				       (setq fn (region-to-string))))
			     )
			     (re-search-forward "\^L\\|\^_\\|\\'")
			     (if (! (eobp)) (backward-character))
			     (copy-region-to-buffer "INFO")
			     (save-excursion
				 (temp-use-buffer "INFO")
				 (put-database-entry "info"
				     (concat fn ":" node))
			     )
			     (message "Wrote " fn ":" node)
			     (sit-for 0)
		      )))
       )
)

(defun (&info-make-node
	   (switch-to-buffer "INFO")
	   (erase-buffer)
	   (insert-string "File: " &info-file "     Node: " m)
	   (if (!= &info-camefrom "")
	       (progn
		     (insert-string &info-camefrom)
		     (if (!= fn "")
			 (progn
			       (insert-string "(" &info-file ")")
			 ))
		     
		     (insert-string &info-node)
	       ))
	   (insert-string "\n\n[body]\n\n* menu:\n")
	   (search-reverse "[")
	   (if (!= fn "") (setq &info-file fn))
	   (setq &info-node m)
	   (#info-^r)
       )
)

(save-excursion c
    (temp-use-buffer "*info-stack*")
    (setq needs-checkpointing 0)
    (use-syntax-table "info-stack-syntax-table")
    (modify-syntax-entry "w     -~")
    (modify-syntax-entry "     ,")
    (erase-buffer)
    (temp-use-buffer "INFO")
    (setq needs-checkpointing 0)
    (define-keymap "&info-editing")
    (use-local-map "&info-editing")
    (local-bind-to-key "exit-emacs" '^]')
    (local-bind-to-key "exit-emacs" "\^X\^S")
    (local-bind-to-key "justify-paragraph" "\ej")
    (setq right-margin 77)
    (define-keymap "&info-commands")
    (use-local-map "&info-commands")
    (setq case-fold-search 1)
    (use-syntax-table "info-syntax-table")
    (modify-syntax-entry "w     -~")
    (modify-syntax-entry "     .,:")
    (setq c 0)
    (while (<= c 0177)
	   (local-bind-to-key "illegal-operation" c)
	   (setq c (+ c 1)))
    (local-bind-to-key  "execute-extended-command" 'x')
    (local-bind-to-key  "search-forward" 's')
    (local-bind-to-key  "search-forward" '^s')
    (local-bind-to-key  "search-reverse" 'r')
    (local-bind-to-key  "search-reverse" '^r')
    (local-bind-to-key  "redraw-display" '^l')
    (local-bind-to-key  "#info-@" '@')
    (local-bind-to-key  "scroll-one-line-down" 'a')
    (local-bind-to-key  "scroll-one-line-up" 'z')
    (local-bind-to-key  "scroll-one-line-up" '^z')
    (local-bind-to-key  "#info-hlp" '?')
    (local-bind-to-key  "exit-emacs" 'q')
    (local-bind-to-key  "exit-emacs" '^C')
    (local-bind-to-key  "#info-m" 'm')
    (local-bind-to-key  "#info-n" 'n')
    (local-bind-to-key  "#info-p" 'p')
    (local-bind-to-key  "#info-f" 'f')
    (local-bind-to-key  "#info-u" 'u')
    (local-bind-to-key  "next-page" ' ')
    (local-bind-to-key  "next-page" '^v')
    (local-bind-to-key  "previous-page" '')
    (local-bind-to-key  "beginning-of-file" 'b')
    (local-bind-to-key  "end-of-file" 'e')
    (local-bind-to-key  "#info-mouse-menu" "\eB")
    (local-bind-to-key  "#info-mouse-menu" "\eD")
    (local-bind-to-key  "#info-l" 'l')
    (local-bind-to-key  "#info-d" 'd')
    (local-bind-to-key  "#info-h" 'h')
    (local-bind-to-key  "#info-g" 'g')
    (local-bind-to-key  "#info-enable-edit" "\e\")
    (local-bind-to-key  "execute-extended-command" ":")
)

(novalue)
