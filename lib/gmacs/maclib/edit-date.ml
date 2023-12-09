(defun 
    (edit-date
	(save-excursion
	    (error-occured
		(goto-character 2000)
		(search-reverse "LastEditDate=""")
		(search-forward """")
		(set-mark)
		(search-forward """")
		(backward-character)
		(delete-to-killbuffer)
		(insert-string (current-time))
	    )
	    
	)
	(message "...date updated")
    )
)
(novalue)
