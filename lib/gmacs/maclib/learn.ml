	;;;; LastEditDate="Tue Jun  4 16:27:50 1991"
; Package for the emacs tutorial
(defun
    (learn
	  (save-window-excursion old-pop-up-windows	; TLH - added opuw
	      (setq old-pop-up-windows pop-up-windows)	; TLH
	      (setq pop-up-windows 1)			; TLH
	      (delete-other-windows)
	      (switch-to-buffer "gmacs-tutorial")
	      (erase-buffer)
	      (insert-file "$TOOLS/lib/gmacs/databases/tutorial.txt")
	      (setq needs-checkpointing 0)
	      (recursive-edit)
	      (setq pop-up-windows old-pop-up-windows)	; TLH
	      ; TLH - if used in teach-emacs, don't load any files afterwards.
	      (argv 1)					; TLH
	      (novalue)					; TLH
	  )
    )
)
