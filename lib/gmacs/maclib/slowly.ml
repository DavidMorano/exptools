	; LastEditDate="Wed Nov 17 10:58:05 1982"
	; Macro written by Tony Hansen ;
	; set terminal for slow baud rates ;;;

(progn
    (delete-other-windows)			; start out with clean window
    (setq mode-line-format			; don't display file name or %
	  " Buffer: %b  %M (%m) %*")
    (setq-default mode-line-format		; don't display file name or %
	  " Buffer: %b  %M (%m) %*")
    (setq help-on-command-completion 0)		; give help on incorrect cmds
    (setq quick-redisplay 1)			; update multi-windows
    (remove-binding '^?')			; munge DEL
    (split-current-window)			; divide window
    (provide-prefix-argument 4 (enlarge-window)); change size of window
)

