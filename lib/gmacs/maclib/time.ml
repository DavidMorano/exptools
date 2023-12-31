	;;;; LastEditDate="Tue Jun  4 21:12:43 1991"
(declare-global time-running)
(setq time-running 0)

(defun
    (time dead
	(if (|
		(setq dead (< (process-status "newtime") 0))
		(! time-running))
	    (save-excursion
		(if (! dead)
		    (kill-process "newtime"))
		(setq global-mode-string "time and load")
		(setq time-running 0)
		(start-filtered-process 
		    "$TOOLS/lib/gmacs/etc/loadst -n 60"
		    "newtime" "newtime-filter")))
	(novalue)
    )
)

(defun
    (newtime-filter
	(setq global-mode-string (process-output))
	(setq time-running 1)
	(sit-for 0)
    )
)
