	; !!!! DOESN'T WORK !!!!
	; LastEditDate="Wed Mar  3 18:24:25 1982"
	; Macros written by Tony Hansen ;
	; Define metaquote ; ESC-^Q ;
	; But it doesn't work (!!!!!!) because insert-character
	; AND's its argument with 0177 before using it.
	; Oh well....

(defun
    (metaquote
	(insert-character (+ 0200 (get-tty-character))))
)
