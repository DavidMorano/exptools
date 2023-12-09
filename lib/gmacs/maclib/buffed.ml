;;;  Buffed  -  a Dired-like package for Emacs Buffers
;;;
;;;  Jay Lark  Stanford University  3/11/82

(declare-global &Buffed-dot 
                &Buffed-cb)

(defun

; Go into a sort of Dired on buffer names

 (buffed i
    (if (= (current-buffer-name) "Buffer list")
        (error-message "You're already in Buffer Edit!"))
    (setq &Buffed-cb (current-buffer-name))
    (setq &Buffed-dot (dot))  
    (switch-to-buffer "Buffer list")
    (delete-other-windows)
    (use-local-map "&Buffed-map")
    (list-buffers)
    (setq mode-string "Buffer Edit")
    (beginning-of-file)
    (error-occured (search-forward &Buffed-cb))
    (beginning-of-line)
    (recursive-edit)
    (if (= this-command -888)
        (progn (#Buffed-return)
               (error-message "Buffed aborted"))
        (#Buffed-delete-buffers))
    (#Buffed-return)
    (novalue)
    )

;;; Delete buffers marked for deletion
 (#Buffed-delete-buffers
     (beginning-of-file)
     (next-line) (next-line)
     (while (! (eobp))
            (if (= (following-char) 'D')
                (save-excursion buff del
                   (setq buff (#Buffed-get-name))
                   (switch-to-buffer buff)
                   (if (= buff "Buffer list")
                       (progn (message "Cannot delete Buffer list buffer")
                              (sit-for 10)
                              (setq del 0))
                       buffer-is-modified
                       (progn c
                          (message (concat buff " is modified.  Delete anyway?"))
                          (setq c (get-tty-character))
                          (setq del (c= c 'y')))
                       (setq del 1))
                   (switch-to-buffer "Buffer list")
                   (if del
                       (progn (if (= buff &Buffed-cb)
                                  (setq &Buffed-cb ""))
                              (error-occured (delete-buffer buff))))))
            (next-line)
            (beginning-of-line)))

;;; Return to original buffer if it still exists
 (#Buffed-return new
     (if (= &Buffed-cb "")
         (setq new (get-tty-buffer "Select buffer to return to: "))
         (setq new &Buffed-cb))
     (switch-to-buffer new)
     (if (!= &Buffed-cb "")
         (goto-character &Buffed-dot)))

;;; Blast our way out of Buffed
 (#Buffed-a
     (setq this-command -888)   ;my magic number for aborting
     (exit-emacs)
     )

;;; Mark buffer as modified for Buffed
 (#Buffed-m
     (save-excursion
        (beginning-of-line)
        (while (<= (current-column) 14) (forward-character))
        (delete-next-character)
        (insert-character 'M')
        (temp-use-buffer (#Buffed-get-name))
        (set "buffer-is-modified" 1)
        )
     (novalue)
     )

;;; Saves current buffer
 (#Buffed-s
     (#Buffed-r)
     (save-excursion
        (temp-use-buffer (#Buffed-get-name))
        (if (error-occured (write-current-file))
            (progn file
               (setq file (get-tty-string "Write buffer to file: "))
               (write-named-file file))))
     (novalue))

;;; Marks current buffer for deletion
 (#Buffed-d
     (beginning-of-line)
     (delete-next-character)
     (insert-character 'D')
     (#Buffed-n))

;;; Unmarks current buffer for deletion
 (#Buffed-u
     (beginning-of-line)
     (delete-next-character)
     (insert-character ' ')
     (backward-character)
     (novalue))

;;; Removes buffer listing from Buffed
 (#Buffed-k
     (beginning-of-line)
     (while (! (eolp)) (delete-next-character))
     (delete-next-character)
     (novalue))

;;; Calls recursive edit on current buffer
 (#Buffed-i
     (save-window-excursion
        (use-old-buffer (#Buffed-get-name))
        (message "Execute (exit-emacs) to return to Buffed (usually ^C)")
        (recursive-edit)
        (novalue)))

;;; Marks current buffer as unmodified
 (#Buffed-r
     (save-excursion
        (beginning-of-line)
        (while (<= (current-column) 14) (forward-character))
        (delete-next-character)
        (insert-character ' ')
        (temp-use-buffer (#Buffed-get-name))
        (set "buffer-is-modified" 0)
        )
     (novalue)
     )

;;; Next buffer
 (#Buffed-n
     (next-line)
     (beginning-of-line))

;;; Previous buffer
 (#Buffed-p
     (previous-line)
     (beginning-of-line))

;;; Mini help message
 (#Buffed-mini-help
     (message
        "(A)bort, (D)elete, (U)ndelete, (H)elp, (E)xit, (I)nspect, (S)ave"))

;;; Big help message
 (#Buffed-h buf pos lf char
    (setq buf (current-buffer-name))
    (setq pos (dot))  
    (setq lf (char-to-string 10))
    (switch-to-buffer "Help")
    (erase-buffer)
    (insert-string
       (concat
"Buffer Edit commands:       ( Hit any key to resume Buffer Edit. )" lf lf

"a,A            Abort:          exit Buffed without deleting buffers." lf
"d,D            Delete:         marks current buffer for deletion." lf
"e,E            Exit:           exit Buffed and delete marked buffers." lf
"h,H,?          Help:           prints this message." lf
"i,I            Inspect:        inspect current buffer." lf
"k,K            Kill:      same as Exit." lf
"r,R            Restore:        marks current buffer as unmodified." lf
"s,S            Save:           saves contents of current buffer." lf
"u,U            Undelete:       undeletes current buffer." lf
       ))
    (setq buffer-is-modified 0)
    (beginning-of-file)
    (get-tty-character)
    (switch-to-buffer buf)
    (goto-character pos)
    (novalue))

;;; Function to return the buffer name for the current line
 (#Buffed-get-name puw s err
    (if (= (save-excursion
              (end-of-line)
              (set-mark)
              (beginning-of-line)
              (region-to-string))
           "   Size  Type   Buffer          File            Mode")
        (error-message "This line has no buffer!"))
    (setq puw pop-up-windows)
    (setq pop-up-windows 0)
    (setq s "")(setq err 0)
    (beginning-of-line)
    (save-excursion
       (while (<= (current-column) 16) (forward-character))
       (setq err
             (error-occured
                (set-mark)(search-forward " ")
                (while (error-occured
                          (save-excursion
                             (backward-character)
                             (use-old-buffer (region-to-string))
                             (setq s (current-buffer-name))))
                       (search-forward " ")))))
    (setq pop-up-windows puw)
    (if err (error-message " No buffer found for this line"))
    s)

);end of big defun

;;; Buffed key bindings
(save-excursion i
   (temp-use-buffer "Buffer list")
   (setq needs-checkpointing 0)
   (setq i 32)
   (define-keymap "&Buffed-map")
   (use-local-map "&Buffed-map")
   (while (<= i 127)
          (local-bind-to-key "#Buffed-mini-help" i)
          (setq i (+ 1 i)))
   (local-bind-to-key "exit-emacs" 3)   ;^C
   (local-bind-to-key "#Buffed-a" 'A')
   (local-bind-to-key "#Buffed-a" 'a')
   (local-bind-to-key "#Buffed-d" 'd')
   (local-bind-to-key "#Buffed-d" 'D')
   (local-bind-to-key "#Buffed-d" '^?')   ;<DEL>
   (local-bind-to-key "exit-emacs" 'e')
   (local-bind-to-key "exit-emacs" 'E')
   (local-bind-to-key "#Buffed-h" 'h')
   (local-bind-to-key "#Buffed-h" 'H')
   (local-bind-to-key "#Buffed-h" '?')
   (local-bind-to-key "#Buffed-i" 'i')
   (local-bind-to-key "#Buffed-i" 'I')
   (local-bind-to-key "#Buffed-k" 'k')
   (local-bind-to-key "#Buffed-k" 'K')
   (local-bind-to-key "#Buffed-m" 'm')
   (local-bind-to-key "#Buffed-m" 'M')
   (local-bind-to-key "#Buffed-n" 'n')
   (local-bind-to-key "#Buffed-n" 'N')
   (local-bind-to-key "#Buffed-n" 13)   ;<CR>
   (local-bind-to-key "#Buffed-p" 'p')
   (local-bind-to-key "#Buffed-p" 'P')
   (local-bind-to-key "#Buffed-p" 8)    ;<BS>
   (local-bind-to-key "exit-emacs" 'q')
   (local-bind-to-key "exit-emacs" 'Q')
   (local-bind-to-key "#Buffed-r" 'r')
   (local-bind-to-key "#Buffed-r" 'R')
   (local-bind-to-key "#Buffed-s" 's')
   (local-bind-to-key "#Buffed-s" 'S')
   (local-bind-to-key "#Buffed-u" 'u')
   (local-bind-to-key "#Buffed-u" 'U')
   )

(novalue)
