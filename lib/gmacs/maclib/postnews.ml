	;;;; LastEditDate="Wed Oct 20 17:00:28 1982"
	;;;; Written by Tony Hansen.
	;;;;
	;;;; postnews [unbound]
	;;;;
	;;;; This macro posts a news item for netnews/readnews.
	;;;;

(defun
    (postnews title newsgroup
	(setq title (get-tty-string "Title of article: "))
	(setq newsgroup (get-tty-string "News group [btl.general]: "))
	(if (= newsgroup "") (setq newsgroup "btl.general"))
	(save-window-excursion
	    (switch-to-buffer " Post News")
	    (text-mode)
	    (setq needs-checkpointing 0)
	    (message "Type news, end with control-C")
	    (recursive-edit)
	    (switch-to-buffer " Post News")
	    (beginning-of-file)
	    (set-mark)
	    (end-of-file)
	    (if (> (buffer-size) 0)
		(progn
		      (message "Posting ....")
		      (sit-for 0)
		      (if (file-exists "~/.postnews")
			  (filter-region (concat "tee -a $HOME/.postnews | "
						 "inews -t """ title
						 """ -n """ newsgroup))
			  (filter-region (concat "inews -t """ title
						 """ -n """ newsgroup)))
		      (message "... posted!"))
		(message "Aborted!")))
	(delete-buffer " Post News")
	(novalue))
)
