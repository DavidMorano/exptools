	;;;; LastEditDate="Wed Sep 15 08:48:51 1982"
(defun
    (new-undo c
	(undo)
	(while
	      (progn
		    (message "Hit <space> to undo more, <return> to stop")
		    ;(message "Hit <space> to undo more"); TLH
		    (= (setq c (get-tty-character)) ' '))
	      (undo-boundary)
	      (undo-more))
	(message "Finished undoing.")
	(if (& (!= c '\n')
	       (!= c '\r'))
	    (push-back-character c))
    )
)
