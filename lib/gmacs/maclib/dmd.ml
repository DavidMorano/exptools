;;; Blit running netty
;;;
;;; (load "mouse.ml")
;;;
(progn
    (defun
	  (netty-mouse button x y
	      (setq button (get-tty-character))
	      (setq x (- (get-tty-character) 31))
	      (setq y (- (get-tty-character) 31))
	      (if (= button '1')
		  (move-dot-to-x-y x y)
	      )
	  )
	  (netty-mark
	      (set-mark)
	      (netty-mouse)
	  )
	  (netty-copy
	      (set-mark)
	      (netty-mouse)
	      (copy-region)
	  )
	  (netty-kill
	      (set-mark)
	      (netty-mouse)
	      (kill-region)
	  )
	  (netty-change-mouse-action
	      (if (= prefix-argument 1)
		  (progn
			(bind-to-key "netty-mark" "\^X\^_")
			(message "Mouse button one marks the region")
		  )
		  (= prefix-argument 2)
		  (progn
			(bind-to-key "netty-copy" "\^X\^_")
			(message "Mouse button one copies the region")
		  )
		  (= prefix-argument 3)
		  (progn
			(bind-to-key "netty-kill" "\^X\^_")
			(message "Mouse button one kills the region")
		  )
	      )
	  )
    )
    (bind-to-key "netty-mark" "\^X\^_")
    (bind-to-key "netty-change-mouse-action" "\^X6")
    
    (defun
	  (netty-func-keys c
	      (setq c (get-tty-character))
	      (if (= c 'A') (prefix-argument-loop (previous-line))
		  (= c 'B') (prefix-argument-loop (next-line))
		  (= c 'C') (prefix-argument-loop (backward-character))
		  (= c 'D') (prefix-argument-loop (forward-character))
		  (= c 'E') (prefix-argument-loop (backward-word))
		  (= c 'F') (prefix-argument-loop
				(progn (scroll-one-line-down)
				       (beginning-of-window)
				       (beginning-of-line)))
		  (= c 'G') (prefix-argument-loop
				(progn (scroll-one-line-up)
				       (end-of-window)
				       (beginning-of-line)))
		  (= c 'H') (prefix-argument-loop (forward-word))
		  (message "Blit Cursor Pad Key Undefined.")
	      )
	  )
    )
    (bind-to-key "netty-func-keys" "\^XO")
    
    (bind-to-key "scroll-one-line-up" "\e\^N")
    (bind-to-key "scroll-one-line-down" "\e\^P")
    
    ;;;
    ;;; BTL EMACS compatability
    ;;;
    (bind-to-key "set-mark" "\e ")
    (bind-to-key "copy-region" "\ep")
)
