	; LastEditDate="Thu Jun 20 11:00:24 1985"
	; Macros written by Tony Hansen ;

(defun
    (new-split-current-window name
	(if (! prefix-argument-provided)
	    (setq name (get-tty-buffer "Buffer Name: ")))
	(split-current-window)
	(if (! prefix-argument-provided)
	    (switch-to-buffer name))
    )
)
