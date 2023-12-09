	; LastEditDate="Mon Sep 27 16:31:07 1982"
	; Macro written by Tony Hansen ;
	; define name-keybd-macro ; [unbound]
(defun
    (name-keybd-macro
	macname key1 key-sequence key-string reply question loopctl yesreply
	(setq macname (get-tty-string "Name to be assigned: "))
	(message "Key to be assigned: ")
	(setq key1 (get-tty-character))
	(setq key-sequence (char-to-string key1))
	(if (= key1 '\033')	; ESC ?
	    (progn key2
		   (setq key-string "ESC-")
		   (message "Key to be assigned: ESC-")
		   (setq key2 (get-tty-character))
		   (setq key-sequence 
			 (concat key-sequence (char-to-string key2)))
		   (setq key-string
			 (concat key-string (&char-to-printing-string key2))))
	    (= key1 '\030')	; ^X ?
	    (progn
		  (setq key-string "^X-")
		  (message "Key to be assigned: ^X-")
		  (setq key2 (get-tty-character))
		  (setq key-sequence 
			(concat key-sequence (char-to-string key2)))
		  (setq key-string
			(concat key-string (&char-to-printing-string key2))))
	    ; else
	    (setq key-string (&char-to-printing-string key1)))
	(setq question
	      (concat "Bind """ macname """ to """ 
		      key-string """: Y or N? ; "))
	(message question)
	(setq reply (get-tty-character))
	(setq loopctl 1)
	(while loopctl
	       (if (| (= reply 'N') (= reply 'n'))
		   (progn
			 (setq loopctl 0)
			 (setq yesreply 0))
		   (| (= reply 'Y') (= reply 'y'))
		   (progn
			 (setq loopctl 0)
			 (setq yesreply 1))
		   (progn
			 (message question)
			 (setq reply (get-tty-character)))
	       ))
	(if yesreply
	    (progn
		  (define-keyboard-macro macname)
		  (bind-to-key macname key-sequence)
		  (message "Assigned"))
	    (novalue)
	))

    ; define &char-to-print-string ;
    (&char-to-printing-string arg1 string
	(setq arg1 (arg 1 "String to build"))
	(if (= arg1 0177)
	    "^?"
	    (< arg1 32)
	    (concat "^" (char-to-string (+ arg1 0100)))
	    (char-to-string arg1)))
)
