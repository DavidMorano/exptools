	;;;; LastEditDate="Sat Aug 27 14:07:52 1983"
	;;;; written by Tony Hansen
	;;;; reset-modified (ESC-~) and revert-file

; reset-modified
(defun
    (reset-modified
	(setq buffer-is-modified 0))
)

; revert-file
(defun
    (revert-file dot
	(setq dot (+ 0 (dot)))
	(read-file (current-file-name))
	(goto-character dot)
	(novalue))
)

