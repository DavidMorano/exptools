;  This autoloaded file implements the "m" command of mhe. We call "comp" to
;  compose the message into buffer "draft", and then when we are ready to
;  send it we call "send" to do the evil deed.
(defun 
    (&mh-send actn exfl sm
        (save-window-excursion 
            (error-occured
                (&mh-save-killbuffer)
                (message "Composing a message...") (sit-for 0)
                (pop-to-buffer (concat "+" mh-folder))
                (setq sm mode-line-format)
                (delete-other-windows)
                (pop-to-buffer "draft") (erase-buffer)
                (set-mark)
                (unlink-file (concat mh-path "/draft"))
                (send-to-shell (concat mh-progs "/comp -build"))
                (show-shell-errors)
                (read-file (concat mh-path "/draft"))
                (local-bind-to-key "exit-emacs" "\^X\")
                (mail-mode) (header-line-position)
                (sit-for 0) (setq exfl 0)
                (while (= exfl 0)
                       (error-occured
                           (save-window-excursion
                               (pop-to-buffer (concat "+" mh-folder))
                               (setq mode-line-format
                                     "{%b}      ^X^C exits to top level         %M")
                               (pop-to-buffer "draft")
                               (setq mode-line-format
                                     (concat "{%b}      %[%p of "
                                             mh-path "/draft%]  "
                                             "^X^C exits to top level   %M"))
                               (&mh-restore-killbuffer)
                               (recursive-edit)
                               (&mh-save-killbuffer)
                               (setq mode-line-format
                                     (concat "{%b}      %[%p of "
                                             mh-path "/draft%]  %M"))
                               (pop-to-buffer (concat "+" mh-folder))
                               (setq mode-line-format " ")
                           )
                       )
                       (setq actn (get-response "Action? (m, q, e, or ?) " "mMqQeE\" 
                                      "m: mail it, q: quit, e: resume editing, ?: this msg."))
                       (if (= actn 'm')
                           (progn (message "Sending.") (sit-for 0)
                                  (write-current-file)
                                  (message "Sending..") (sit-for 0)
                                  (temp-use-buffer "scratch")
                                  (set-mark)
                                  (send-to-shell 
                                      (concat mh-progs "/send -noverbose "
                                              mh-path "/draft"
                                      ))
                                  (message "Sending...") (sit-for 0)
                                  (show-shell-errors)
                                  (setq buffer-is-modified 0)
                                  (message "Sending... Sent.") (sit-for 5)
                                  (setq exfl 1))
                           (= actn 'q')
                           (error-message "Not sent.")
                       )
                )
            )
        )
        (&mh-restore-killbuffer)
        (pop-to-buffer (concat "+" mh-folder)) (delete-other-windows)
        (setq mode-line-format sm)
        (pop-to-buffer "draft") (previous-window)
    )
)

