;;;
;;; Blit and DMD running myx
;;;
(progn
    (defun
	  (myx-get-coordinate multiplier offset x
	      (setq multiplier (get-tty-character))
	      (if (< multiplier ' ')
		  (progn
			(setq offset (get-tty-character))
			(+ (* multiplier 95)
			   (- offset 31)))
		  (- multiplier 31)))
	  (myx-mouse button x y
	      (setq button (get-tty-character))
	      (setq x (myx-get-coordinate))
	      (setq y (myx-get-coordinate))
	      (if (= button '1')
		  (move-dot-to-x-y x y)
	      )
	  )
	  (myx-mark
	      (set-mark)
	      (myx-mouse)
	  )
    )
    (bind-to-key "myx-mark" "\^X\^_")
)
