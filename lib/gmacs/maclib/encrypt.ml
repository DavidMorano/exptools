	;;;; LastEditDate="Thu Sep 30 16:35:37 1982"
	;;;; Written by Tony Hansen
	;;;; read and write a file, using an encryption key

(setq-default encryption-key "")
(declare-buffer-specific encryption-key)

(defun
    (encrypted-visit-file filename
	(setq filename (arg 1 "Encrypted File? "))
	(error-occured (visit-file filename))
	(if (! buffer-is-modified)
	    (progn
		  (setq encryption-key (arg 2 "Encryption Key? "))
		  (beginning-of-file)
		  (set-mark)
		  (end-of-file)
		  (filter-region (concat "crypt " encryption-key))
		  (beginning-of-file)
		  (setq buffer-is-modified 0))
	    (error-message "File already being edited!"))
	(novalue))
)
(defun
    (encrypted-insert-file filename key
	(setq filename (arg 1 "Encrypted File? "))
	(setq key (arg 2 "Encryption Key? "))
	(save-excursion
	    (temp-use-buffer " Temp Crypt Buffer")
	    (erase-buffer)
	    (read-file filename)
	    (beginning-of-file)
	    (set-mark)
	    (end-of-file)
	    (filter-region (concat "crypt " key)))
	(yank-buffer " Temp Crypt Buffer")
	(delete-buffer " Temp Crypt Buffer")
	(novalue))
)
(defun
    (encrypted-write-file filename buffer key
	(setq filename (current-file-name))
	(if (= filename "")
	    (setq filename (get-tty-string "Filename? ")))
	(setq buffer (current-buffer-name))
	(if (= encryption-key "")
	    (setq encryption-key (arg 1 "Encryption Key? ")))
	(save-window-excursion
	    (temp-use-buffer " Temp Crypt Buffer")
	    (erase-buffer)
	    (yank-buffer buffer)
	    (beginning-of-file)
	    (set-mark)
	    (end-of-file)
	    (filter-region (concat "crypt " encryption-key))
	    (write-named-file filename))
	(delete-buffer " Temp Crypt Buffer")
	(message (concat "Wrote (encrypted) " filename)))
)
