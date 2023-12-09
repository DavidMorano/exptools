	;;;; LastEditDate="Thu Sep 30 14:28:49 1982"
(declare-global kill-ring-size kill-ring-pos kill-buffer-name)
(setq kill-ring-size 10)
(setq kill-ring-pos -1)

(progn number			; TLH
    (setq number 0)
    (save-excursion
	(while (< number kill-ring-size)
	       (temp-use-buffer (concat "kill-buffer-" number))
	       (setq needs-checkpointing 0)
	       (setq number (+ number 1))))
)

(defun
    (perform-kill
	(if (!= (previous-command) -84)
	    (progn
		(setq kill-ring-pos (% (+ kill-ring-pos 1) kill-ring-size))
		(setq kill-buffer-name (concat "kill-buffer-" kill-ring-pos))
		(copy-region-to-buffer kill-buffer-name))
	    (if (< (dot) (mark))
		(prepend-region-to-buffer kill-buffer-name)
		(append-region-to-buffer kill-buffer-name)))
	(erase-region)
	(setq this-command -84)))

(defun
    (kill-next-word
	(save-excursion
	    (set-mark)
	    (provide-prefix-argument prefix-argument (forward-word))
	    (perform-kill)))
)

(defun    
    (kill-previous-word
	(save-excursion
	    (set-mark)
	    (provide-prefix-argument prefix-argument (backward-word))
	    (perform-kill)))
)

(defun    
    (kill-lines-ITS
	(save-excursion
	    (set-mark)
	    (if prefix-argument-provided
		(progn 
		    (beginning-of-line)
		    (provide-prefix-argument prefix-argument (next-line)))
		(if (eolp) (forward-character) (end-of-line)))
	    (perform-kill)))
)

; Macros written by Tony Hansen ;
(defun
    (copy-region save-mod-flag
	(setq save-mod-flag buffer-is-modified)	; remember modified flag
	(save-excursion				; remember where we are
	    (perform-kill)			; delete
	    (yank-kill))			; then yank
	(setq buffer-is-modified save-mod-flag) ; reset modified flag
	(novalue))
    
    (copy-lines save-mod-flag
	(setq save-mod-flag buffer-is-modified)	; remember modified flag
	(provide-prefix-argument		; delete it
	    prefix-argument
	    (kill-lines-ITS))
	(yank-kill)				; get it back
	(setq buffer-is-modified save-mod-flag) ; reset modified flag
    )

    (kill-region
	(perform-kill))

    (kill-next-character
	(save-excursion
	    (if prefix-argument-provided
		(progn
		      (set-mark)
		      (provide-prefix-argument
			  prefix-argument
			  (forward-character))
		      (perform-kill))
		(delete-next-character))))

    (kill-previous-character
	(save-excursion
	    (if prefix-argument-provided
		(progn
		      (set-mark)
		      (provide-prefix-argument
			  prefix-argument
			  (backward-character))
		      (perform-kill))
		(delete-previous-character))))
)

(defun
    (yank-kill
	(if prefix-argument-provided
	    (yank-cycle)
	    (progn
		(set-mark)
		(yank-buffer kill-buffer-name))))
)

(defun
    (yank-cycle dot mark
	(setq kill-ring-pos (- kill-ring-pos 1))
	(if (< kill-ring-pos 0)
 	    (setq kill-ring-pos (- kill-ring-size 1)))
	(setq kill-buffer-name (concat "kill-buffer-" kill-ring-pos))
	(if (< (dot) (mark)) (exchange-dot-and-mark))
	(setq dot (dot))
	(setq mark (mark))
	(set-mark)
	(yank-buffer kill-buffer-name)
	(save-excursion
	    (goto-character mark)
	    (set-mark)
	    (goto-character dot)
	    (delete-region-to-buffer kill-buffer-name)))
)

(bind-to-key "kill-next-word" "\ed")			; TLH
(bind-to-key "kill-previous-word" "\eh")		; TLH
(bind-to-key "kill-lines-ITS" "\^K")			; TLH
(bind-to-key "kill-region" "\^W")			; TLH
(bind-to-key "kill-next-character" "\^D")		; TLH
(bind-to-key "kill-previous-character" "\^H")		; TLH
(bind-to-key "copy-region" "\ew")			; TLH
(bind-to-key "copy-lines" "\ek")			; TLH
(bind-to-key "yank-kill" "\^Y")				; TLH
(novalue)
