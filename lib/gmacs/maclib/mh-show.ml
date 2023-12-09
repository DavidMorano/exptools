;  This autoloaded file implements the "t" command of mhe
(defun 
    (&mh-show msgn sm fn fl
        (delete-other-windows)
        (error-occured
            (setq msgn (&mh-get-msgnum))
            (message  "showing message " msgn)
            (setq fn (&mh-get-fname))
            (setq fl mh-folder)
            (pop-to-buffer "show")
            (read-file fn)
            (setq mode-line-format
                  (concat "{%b} %[%p of +" fl "/" msgn
                          "%]   ^X^C exits to top level"))
            (use-local-map "&mh-keymap")
            
            (setq mode-line-format
                  (concat "{%b} %[%p of +" fl "/" msgn "%]"))
        )
    )
)

