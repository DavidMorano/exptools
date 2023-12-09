	; LastEditDate="Thu Aug 24 11:07:55 1989"
	; Macros written by Tony Hansen ;

(defun
    ; change a decimal number to octal or hexadecimal
    (baseconvert dividend remainder i string divisor prefix suffix
	(setq i (arg 1 "decimal number? "))
	(setq divisor (arg 2 "base? "))
	(setq prefix (arg 3 "prefix? "))
	(setq suffix (arg 4 "suffix? "))
	(setq string "")
	(while (progn (setq remainder (% i divisor))
		      (setq string (concat (substr "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
						   (+ remainder 1) 1)
					   string))
		      (setq dividend (/ i divisor)))
	       (setq i dividend))
	(concat prefix string suffix))
    (octalize (baseconvert (arg 1 "decimal number? ") 8 "0" ""))
    (hexadize (baseconvert (arg 1 "decimal number? ") 16 "0x" ""))
)
