(defun
    (write-region-to-file fname
	(setq fname (arg 1 ": write-region-to-file "))
	(save-excursion
	    (copy-region-to-buffer "write-temp")
	    (temp-use-buffer "write-temp")
	    (write-named-file fname))
	(novalue)
    )
    
    ; added by TLH
    (append-region-to-file fname
	(setq fname (arg 1 ": append-region-to-file "))
	(save-excursion
	    (copy-region-to-buffer "write-temp")
	    (temp-use-buffer "write-temp")
	    (append-to-file fname))
	(novalue)
    )
)
