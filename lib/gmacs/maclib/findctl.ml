	;;; LastEditDate="Thu Sep 30 16:38:22 1982"
	;;; Macro written by Tony Hansen ;
	;;; define find-control-character ;;;

(defun
    (find-control-character char
	(looking-at "[ -~\^I\^J\^M\^L]")
	(while				
	    (looking-at "")
	    (forward-character))
	(novalue))
)
