; LastEditDate="Tue Jun  4 16:01:36 1991"
; This function slides a region left or right by "argument prefix" spaces.
; It is useful in manually meddling with indentation in block-structured
;    languages.
;  "argument prefix" defaults to 4 if not provided. 
;  I usually bind it to ESC-^I
;       Brian Reid  March 82
;
;  This function misbehaves if track-eol-on-^N-^P is on and blank (empty)
;  lines are encountered in the region.  I have made the fixes below marked
;  GVEO.              George Otto   April 83
;
(defun
    (indent-region n
        (if prefix-argument-provided
            (setq n prefix-argument)
            (setq n 4))
        (if (> (dot) (mark))
            (exchange-dot-and-mark))
        (beginning-of-line)
        (exchange-dot-and-mark)
        (end-of-line)
        (save-excursion 
            (narrow-region)
            (beginning-of-file)
            (while (! (eobp))
                   (indent-line n)
                   (next-line)
            )
            (widen-region)
        )
    )
    (indent-line
        (error-occured
	    (beginning-of-line)	; GVEO -- must go to line beginning *now*
            (while (looking-at "[\^I ]")
                   (forward-character))
            (if (! (eolp))
                (progn oc oq or
                       (setq oc (+ (current-column)
                                   (- (arg 1) 1)))
                       (if (< oc 0) (setq oc 0))
                       (beginning-of-line)
                       (delete-white-space)
                       (setq oq (/ oc 8))
                       (setq or (- oc (* oq 8)))
                       (while oq
                              (insert-character '\t')
                              (setq oq (- oq 1))
                       )
                       (while or
                              (insert-character ' ')
                              (setq or (- or 1))
                       )
		       ; (beginning-of-line)	; GVEO -- not the right time
                )
                (progn
                      ; (beginning-of-line)	; GVEO -- not the right time
                      (delete-white-space)
                )
            )
        )
    )
)
