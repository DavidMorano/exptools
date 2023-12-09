	;;;; LastEditDate="Sun Nov  9 21:52:02 1986"
	;;;; written by Tony Hansen
	;;;; search-next and search-previous ; ESC-n and ESC-p

(defun
    ; search-next
    (search-next
	(prefix-argument-loop
	    (re-search-forward "")))

    ; search-previous
    (search-previous
	(prefix-argument-loop
	    (re-search-reverse "")))
)
