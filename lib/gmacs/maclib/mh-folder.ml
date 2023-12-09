(defun 
    (&mh-read-folder name range
        (pop-to-buffer (concat "+" name)) (sit-for 0)
        (if (= (buffer-size) 0)
            (insert-string " "))
        (setq mode-line-format " please wait ")
        (message "scan +" name " " range)
        (sit-for 0)
        (erase-buffer) (set-mark)
        (filter-region  (concat mh-progs "/scan +" name " " range))
        (beginning-of-file)
        
        (if (! (looking-at "No messages "))
            (progn t
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
                   (if (= range "")
                       (message  "Folder +" name " is empty.")
                       (message  "No messages in +" name " range " range)
                   )
                   (sit-for 15)
            )
        )
        (setq mode-line-format
              (concat "{%b} %[+" name "%]"
                      "  Cmds  n p d ^ u t e m f i r   Exit ^X^C ^X^F  Help ?"))
        (setq buffer-is-modified 0)
    )
)

