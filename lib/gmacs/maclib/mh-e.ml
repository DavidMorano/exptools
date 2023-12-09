; This file implements "mhe", the display-oriented front end to the MH mail
; system. Documentation is in file mh-doc.ml.
; 
;  Brian K. Reid, Stanford, April 1982
; 
    (declare-global             ;*marks installation constants
         mh-keymap-defined      ; T iff keymap exists.
         mh-folder              ; string name, e.g. "inbox"
         mh-path                ; "/mnt/reid/Mail", or whatever
         mh-progs               ;*"/usr/local/lib/mh", or whatever
         bboard-path            ;*"/usr/spool/netnews", or whatever
         mh-buffer-filename     ; "/mnt/reid/Mail/inbox", or whatever
         t-buffer-filename      ; scratch for side effect from mh-folder
         mh-flist               ; "inbox,carbons,news", or whatever
         mh-direction           ; 1 is up, -1 is down.
         mh-annotate            ; are we annotating processed msgs?
         mh-writeable           ; is this folder write-enabled?
         mh-last-destination    ; destination of last "move" command
         mhe-debug              ; are we debugging macro package?
    )

    (argc)                      ; is this early enough, James?
    (setq mh-keymap-defined 0)
    (setq mhe-debug 0)
    (setq-default mh-annotate 1)
    (setq-default mh-writeable 1)
    (setq bboard-path "/usr/spool/news")
    (setq mh-path "")
    (setq mh-progs "/usr/local/lib/mh")
    (setq mh-flist "")
    (setq-default right-margin 77)
    (setq-default mh-direction 1)
    (setq pop-up-windows 1)     ; mhe requires popup windows!

    (declare-buffer-specific
        mh-direction
        mh-buffer-filename
        mh-folder-title
        mh-annotate
        mh-writeable
        backup-before-writing
    )

(defun                          ; (mh "folder" "range")
    (mh folder range
        (temp-use-buffer "cmd-buffer") (erase-buffer)
        (setq backup-before-writing 0)
        (find-path)
        (setq folder (arg 1 (concat ": mh on folder? ["
                                    mh-folder "] ")))
        (if (= folder "")
            (setq folder mh-folder))
        (if (= '+' (string-to-char (substr folder 1 1)))
            (setq folder (substr folder 2 -1)))
        (setq range (arg 2))
        (setq mh-folder (get-folder-name "??" folder 1))
        (&mh-read-folder mh-folder range t-buffer-filename mh-folder)
        (progn stop-loop
               (setq stop-loop 0)
               (while (! stop-loop)
                      (error-occured (recursive-edit))
                      (setq stop-loop (&mh-exit))
               )
        )
    )
)
; This function creates the header buffer that represents a message or
; bboard directory. It associates several buffer-specific variables
; with it: mh-buffer-filename, which is the actual Unix file name of the
; directory; mh-folder-title, which is either the tail of the directory
; name or the whole thing depending on whether it is in your mail path.
; call: (&mh-read-folder "folder" "range" "pathname" "title")
(defun 
    (&mh-read-folder name rnge title
        (setq name (arg 1)) (setq rnge (arg 2))
        (pop-to-buffer (concat "+" mh-folder))
        (setq mh-folder name)
        (switch-to-buffer (concat "+" name))
        (setq backup-before-writing 0)
        (if (= (buffer-size) 0)
            (progn 
                   (if (!= 0 (length mh-flist))
                       (setq mh-flist (concat mh-flist ",")))
                   (setq mh-flist (concat mh-flist name))
                   (setq mh-buffer-filename (arg 3))
                   (setq mh-folder-title (arg 4))
                   (use-local-map "&mh-keymap")
                   (setq mode-line-format " please wait         %M")
                   (message  "scan +" mh-folder-title " " rnge)
                   (sit-for 0)
                   (erase-buffer) (set-mark)
                   (filter-region  (concat mh-progs "/scan +" mh-folder-title " " rnge))
                   (beginning-of-file)
                   (if (! (looking-at "No messages "))
                       (progn t ; position the cursor in the header buffer
                              (end-of-file) (beginning-of-window)
                              (if (! (bobp))
                                  (progn 
                                         (end-of-file)
                                         (setq t (dot))
                                         (while (= t (dot))
                                                (progn 
                                                       (scroll-one-line-down)
                                                       (sit-for 0)
                                                ))
                                         (scroll-one-line-up)
                                  )
                              )
                              (end-of-file)
                              (&mh-previous-line)
                       )
                       (progn 
                              (if (= rnge "")
                                  (message  "Folder +" name " is empty.")
                                  (message  "No messages in +" name " range " rnge)
                                  (erase-buffer)
                              )
                              (sit-for 15)
                       )
                   )
                   (setq mode-line-format
                         (concat "{%b} %[%] "
                                 "Cmds: n p d ^ ! u t e m f i r g b ?  Exit: ^X^C   %M"))
                   (setq buffer-is-modified 0)
            )
        )
    )
)
; This function marks a message as being deleted. This mark has two parts.
; The letter "D" is placed in column 4 of the header line, and the message
; number is added to the text of an "rmm" command that is being assembled
; in the command buffer.
(defun 
    (&mh-Mark-file-deleted
        (pop-to-buffer (concat "+" mh-folder))
        (if (! mh-writeable)
            (error-message "Sorry; this folder is read-only."))
        (beginning-of-line)
        (goto-character (+ (dot) 3))
        (if (| (= (following-char) ' ') (= (following-char) '+'))
            (progn 
                   (delete-next-character)
                   (insert-string "D")
                   (setq buffer-is-modified 0)
                   (temp-use-buffer "cmd-buffer")
                   (beginning-of-file)
                   (if (error-occured
                           (re-search-forward
                               (concat "^rmm +" mh-folder)))
                       (progn 
                              (end-of-file)
                              (insert-string (concat "rmm +" mh-folder "\n"))
                              (backward-character)
                       )
                   )
                   (end-of-line)
                   (insert-string (concat " " (&mh-get-msgnum)))
                   (setq buffer-is-modified 0)
                   (pop-to-buffer (concat "+" mh-folder))
            )
        )
        (another-line)
    )
)
; These functions create (and make current) a header buffer on a new message
; or bboard directory.
(defun 
    (&mh-new-folder which
        (setq which (get-folder-name "New" "" 1))
        (&mh-read-folder which "" t-buffer-filename which)
    )
    
    (&mh-bboard which
        (setq which (get-bboard-name))
        (&mh-read-folder which "" t-buffer-filename t-buffer-filename)
        (setq mh-annotate 0)
        (setq mh-writeable 0)
    )
)

(defun    
    (&mh-remove
        (pop-to-buffer (concat "+" mh-folder))
        (beginning-of-line)
        (&mh-unmark)
        (kill-to-end-of-line) (kill-to-end-of-line)
        (setq buffer-is-modified 0)
    )

; This function gets redefined when &mh-move is autoloaded. Shame on me for
; giving it a name so similar to the function above.
    (&mh-re-move
        (error-message "I can't repeat the last ^ command because you haven't typed one yet")
    )

    (&mh-summary
        (message
                "nxt prev del ^put !rpt unmrk typ edit mail forw inc repl get bboard ^X^C ?")
    )
)
; These functions are used to preserve the contents of the kill buffer
; across things that we want to be invisible, so that the keyboard-level
; user does not have to worry about system functions clobbering the kill
; buffer.
(defun     
    (&mh-save-killbuffer
        (save-excursion 
            (temp-use-buffer "Kill save")
            (setq backup-before-writing 0)
            (erase-buffer)
            (yank-buffer "Kill buffer")
            (setq buffer-is-modified 0)
        )
    )
    
    (&mh-restore-killbuffer
        (save-excursion 
            (temp-use-buffer "Kill buffer")
            (erase-buffer)
            (yank-buffer "Kill save")
        )
    )
)
; These functions are used to run shell commands and check for errors.
(defun    
    (send-to-shell
        (filter-region (arg 1))
    )
    (show-shell-errors
        (if (!= (buffer-size) 0)
            (progn
                  (beginning-of-file)
                  (set-mark)
                  (error-occured (re-replace-string "\n\n* *" "; "))
                  (end-of-line)
                  (backward-character) (backward-character)
                  (kill-to-end-of-line)
                  (send-string-to-terminal "\")
                  (message (region-to-string))
                  (send-string-to-terminal "\")
                  (sit-for 30)
            )
        )
    )
)
; These utility functions return message number, file name, or path
; information.
(defun     
    (&mh-get-msgnum
        (save-excursion
            (pop-to-buffer (concat "+" mh-folder))
            (beginning-of-line)
            (while (= (following-char) ' ') (forward-character))
            (set-mark)
            (beginning-of-line)
            (goto-character (+ (dot) 3))
            (region-to-string)
        )
    )
    
    (&mh-get-fname
        (concat mh-buffer-filename "/" (&mh-get-msgnum))
    )

    (find-path                  ; Look in ~/.mh_profile to find inbox path
        (save-window-excursion 
            (temp-use-buffer "mhprofile")
            (setq backup-before-writing 0)
            (erase-buffer)
            (if (= 0 (file-exists (concat (getenv "HOME") "/.mh_profile")))
                (progn
                      (pop-to-buffer "sorry") (delete-other-windows)
                      (insert-string "\n\nI can't find your .mh_profile file.\n"
                                 "That means I can't continue. Sorry.\n"
                                 "If you don't know what this means, then"
                                 " you should run the program\n"
                                 "'install-mh' now, to build that file.\n")
                      (sit-for 0)
                      (setq stack-trace-on-error 0)
                      (exit-emacs)
                ))
            (read-file (concat (getenv "HOME") "/.mh_profile"))
            (setq mh-path "Mail")
            (error-occured 
                (search-forward "Path:")
                (while (looking-at "[\t ]") (forward-character))
                (set-mark) (end-of-line)
                (setq mh-path (region-to-string))
            )
            (if (!= (string-to-char (substr mh-path 1 1)) '/')
                (setq mh-path (concat (getenv "HOME") "/" mh-path)))
            
            (beginning-of-file)
            (error-occured 
                (search-forward "current-folder:")
                (while (looking-at "[\t ]") (forward-character))
                (set-mark) (end-of-line)
                (setq mh-folder (region-to-string))
            )
            (delete-buffer "mhprofile")
        )
    )
)
; These functions move the cursor around in a header buffer, and possibly
; also display the message that the cursor now points to.
(defun     
    (&mh-next-line
        (pop-to-buffer (concat "+" mh-folder))
        (setq mh-direction 1)
        (next-line) (beginning-of-line)
        (if (eobp)
            (progn (previous-line)
                   (setq mh-direction -1)))
    )
    (&mh-previous-line
        (pop-to-buffer (concat "+" mh-folder))
        (setq mh-direction -1)
        (previous-line) (beginning-of-line)
        (if (bobp)
            (setq mh-direction 1))
    )
    
    (another-line old-direction
        (setq old-direction mh-direction)
        (if (> mh-direction 0)
            (&mh-next-line)
            (&mh-previous-line)
        )
        (if (!= old-direction mh-direction)
            (if (> mh-direction 0)
                (beginning-of-line)
                (&mh-previous-line)
            )
        )
    )
    
)
; These functions query the user for various things, and error-check the
; responses. "get-response" reads a 1-letter response code in the minibuffer.
; "get-folder-name" extracts the string name of an MH folder or file.
; "get-bboard-name" gets the string name of a bboard file.
(defun     
    (get-response chr ok s c pr
        (setq ok 0) (setq pr (arg 1))
        (while (! ok)
               (setq chr
                     (string-to-char 
                         (setq c
                               (get-tty-string pr)
                         )
                     )
               )
               
               (setq s (arg 2))
               (while (> (length s) 0)
                      (if (= chr (string-to-char (substr s 1 1)))
                          (progn (setq ok 1) (setq s ""))
                          (setq s (substr s 2 -1))
                      )
               )
               (if (= ok 0)
                   (progn (if (!= chr '?')
                              (setq pr (concat "Illegal response '"
                                               (char-to-string chr)
                                               "'. " (arg 1)))
                              (setq pr (arg 3))
                          )
                   )
               )
        )
        (if (& (>= chr 'A') (<= chr 'Z'))
            (+ chr (- 'a' 'A'))
            chr
        )
    )
    
    (get-folder-name            ; (g-f-n "prompt" "default" can-create)
        exists msgg name defarg
        (setq exists 0)
        (if (> (nargs) 1) (setq defarg (arg 2)) (setq defarg ""))
        (setq msgg (concat (arg 1) " folder name? "))
        (while (! exists)
               (if (= 0 (length defarg))
                   (setq name (get-tty-string msgg))
                   (setq name defarg)
               )
               (setq defarg "")
               (if (= 0 (length name))
                   (error-message "Aborted."))
               (if (!= (string-to-char (substr name 1 1)) '/')
                   (setq t-buffer-filename (concat mh-path "/" name))
                   (setq t-buffer-filename name)
               )
               (setq exists (file-exists t-buffer-filename))
               (if (& (!= exists 1) (!= (arg 3) 0))
                   (progn ans
                          (setq ans (get-response
                                        (concat "Folder +" name " does not exist. May I create it for you? ")
                                        "yYnN\"
                                        "Please answer y or n"))
                          (if (= ans 'y')
                              (progn 
                                     (message "OK, I will create one for you.")
                                     (set-mark)
                                     (send-to-shell 
                                         (concat "mkdir " t-buffer-filename))
                                     (setq exists 1)
                              )
                          )
                   )
               )
               (if (!= exists 1)
                   (setq msgg  (concat "Sorry, no such folder as `" name
                                       "'.  Folder name? "))
               )
        )
        name
    )
    
    (get-bboard-name  exists msgg name
        (setq exists 0)
        (setq msgg "BBoard name? ")
        (while (! exists)
               (setq name (get-tty-string msgg))
               (if (= 0 (length name))
                   (error-message "Aborted."))
               (if (!= (string-to-char (substr name 1 1)) '/')
                   (setq t-buffer-filename (concat bboard-path "/" name))
                   (setq t-buffer-filename name)
               )
               (setq exists (file-exists t-buffer-filename))
               (if (!= exists 1)
                   (setq msgg  (concat "Sorry, no such BBoard as `" name
                                       "'.  BBoard name? "))
               )
        )
        name
    )
)
; These functions are the initial entry points to mhe. "startup" is 
; expecting an argv like "emacs -lmh-e.ml -estartup +inbox 100-last
(defun
    (startup
            (mh (if (> (argc) 3)
                    (argv 3)
                    "")
                (if (> (argc) 4)
                    (argv 4)
                    "")
            )
            (exit-emacs)
    )
    
    (debug-startup
        (setq mh-progs "/usr/local/src/cmd/mh/progs")
        (setq stack-trace-on-error 1)
        (startup)
    )
)

    (autoload "&mh-send" "mh-send.ml")
    (autoload "&mh-show" "mh-show.ml")
    (autoload "&mh-edit" "mh-edit.ml")
    (autoload "&mh-repl" "mh-repl.ml")
    (autoload "&mh-inc" "mh-inc.ml")
    (autoload "&mh-help" "mh-help.ml")
    (autoload "&mh-move" "mh-move.ml")
    (autoload "&mh-unmark" "mh-unmark.ml")
    (autoload "&mh-forw" "mh-forw.ml")
    (autoload "&mh-exit" "mh-exit.ml")
    (autoload "annotate" "mh-annot.ml")
    (autoload "mail-mode" "mh-mode.ml")
    (load "time.ml")
    (time)

    (progn loop
        (save-excursion
            (temp-use-buffer "+inbox")
            (define-keymap "&mh-keymap")
            (use-local-map "&mh-keymap")
            (setq loop 0)
            (while (<= loop 127)
                (local-bind-to-key "&mh-summary" loop)
                (setq loop (+ loop 1))
            )
            (setq loop '0')
            (while (<= loop '9')
                (local-bind-to-key "digit" loop)
                (setq loop (+ loop 1))
            )
            (local-bind-to-key "&mh-help" "?")
            (local-bind-to-key "&mh-Mark-file-deleted" "d")
            (local-bind-to-key "&mh-Mark-file-deleted" "D")
            (local-bind-to-key "&mh-Mark-file-deleted" "^D")
            (local-bind-to-key "&mh-move" "^")
            (local-bind-to-key "&mh-re-move" "!")
            (local-bind-to-key "&mh-previous-line" "\^H")
            (local-bind-to-key "&mh-previous-line" "\^B")
            (local-bind-to-key "&mh-previous-line" "p")
            (local-bind-to-key "&mh-previous-line" "P")
            (local-bind-to-key "previous-line" "\^P")
            (local-bind-to-key "next-line" "\^N")
            (local-bind-to-key "&mh-next-line" "n")
            (local-bind-to-key "&mh-next-line" "N")
            (local-bind-to-key "&mh-next-line" "\^F")
            (local-bind-to-key "redraw-display" "\^L")
            (local-bind-to-key "search-forward" "\^S")
            (local-bind-to-key "search-reverse" "\^R")
            (local-bind-to-key "argument-prefix" "\^U")
            (local-bind-to-key "previous-window" "\^Xp")
            (local-bind-to-key "previous-window" "\^XP")
            (local-bind-to-key "next-window" "\^Xn")
            (local-bind-to-key "next-window" "\^XN")
            (local-bind-to-key "delete-window" "\^Xd")
            (local-bind-to-key "delete-window" "\^XD")
            (local-bind-to-key "delete-other-windows" "\^X1")
            (local-bind-to-key "visit-file" "\^X\^V")
            (local-bind-to-key "next-page" "\^V")
            (local-bind-to-key "redraw-display" "\^L")
            (local-bind-to-key "previous-page" "\ev")
            (local-bind-to-key "previous-page" "\eV")
            (local-bind-to-key "scroll-one-line-up" "")
            (local-bind-to-key "scroll-one-line-down" "\e")
            (local-bind-to-key "beginning-of-file" "\e<")
            (local-bind-to-key "end-of-file" "\e>")
            (local-bind-to-key "return-to-monitor" "\^_")
            (local-bind-to-key "&mh-unmark" "u")
            (local-bind-to-key "&mh-unmark" "U")
            (local-bind-to-key "exit-emacs" "\^X\")
            (local-bind-to-key "&mh-show" "t")
            (local-bind-to-key "&mh-show" "T")
            (local-bind-to-key "&mh-edit" "e")
            (local-bind-to-key "&mh-edit" "E")
            (local-bind-to-key "&mh-repl" "R")
            (local-bind-to-key "&mh-repl" "r")
            (local-bind-to-key "&mh-send" "m")
            (local-bind-to-key "&mh-send" "M")
            (local-bind-to-key "&mh-forw" "f")
            (local-bind-to-key "&mh-forw" "F")
            (local-bind-to-key "&mh-remove" "\^K")
            (local-bind-to-key "&mh-new-folder" "\^X\^F")
            (local-bind-to-key "&mh-new-folder" "g")
            (local-bind-to-key "&mh-new-folder" "G")
            (local-bind-to-key "&mh-bboard" "b")
            (local-bind-to-key "&mh-bboard" "B")
            (local-bind-to-key "&mh-inc" "i")
            (local-bind-to-key "&mh-inc" "I")
        )
    )

