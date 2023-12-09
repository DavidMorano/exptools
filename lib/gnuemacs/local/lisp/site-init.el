;;;
;;; Initialization file for AT&T local version of GNUemacs
;;;

(setq news-path "/usr/spool/news/")
(if (null purify-flag)
    (setq news-inews-program (expand-file-name "~news/inews")))

;;;
(setq send-mail-function 'feedmail-send-it)
(autoload 'feedmail-send-it "feedmail")

;;; Commands added by calc-private-autoloads on Sat Oct  5 14:33:30 1991.
(autoload 'calc-dispatch	   "calc" "Calculator Options" t)
(autoload 'full-calc		   "calc" "Full-screen Calculator" t)
(autoload 'full-calc-keypad	   "calc" "Full-screen X Calculator" t)
(autoload 'calc-eval		   "calc" "Use Calculator from Lisp")
(autoload 'defmath		   "calc" nil t t)
(autoload 'calc			   "calc" "Calculator Mode" t)
(autoload 'quick-calc		   "calc" "Quick Calculator" t)
(autoload 'calc-keypad		   "calc" "X windows Calculator" t)
(autoload 'calc-embedded	   "calc" "Use Calc inside any buffer" t)
(autoload 'calc-embedded-activate  "calc" "Activate =>'s in buffer" t)
(autoload 'calc-grab-region	   "calc" "Grab region of Calc data" t)
(autoload 'calc-grab-rectangle	   "calc" "Grab rectangle of data" t)
(autoload 'edit-kbd-macro	   "macedit" "Edit Keyboard Macro" t)
(autoload 'edit-last-kbd-macro	   "macedit" "Edit Keyboard Macro" t)
(autoload 'read-kbd-macro	   "macedit" "Read Keyboard Macro" t)
;;;(global-set-key "\e#" 'calc-dispatch)
;;; End of Calc autoloads.

;(autoload 'sc-cite-original "sc" "Hookified Supercite 2.2" t)
;(autoload 'sc-cite "sc" "Interactive Supercite 2.2" t)
;(autoload 'sc-describe "sc" "Describe Supercite 2.2" t)
;(setq mail-yank-hooks 'sc-cite-original)
;(setq mh-yank-hooks   'sc-cite-original)

(autoload 'lisp-dir-apropos "lispdir" "Public-Domain Lisp Code Apropos" t)

(autoload 'extract-buffer "cms" "CMS Functions" t nil)
(autoload 'feature-lines "cms" "CMS Functions" t nil)
(autoload 'feature-region "feature" nil t nil)
(autoload 'find-vpath-file "cms" "CMS Functions" t nil)
(autoload 'gnus "gnus" "GNU NNTP News Reader" t nil)
(autoload 'inspect-mode "inspect-mode" nil t nil)
(autoload 'ispell-buffer "ispell" "Check spelling of words in the buffer" t)
(autoload 'ispell-complete-word "ispell" "Complete word at or before point" t)
(autoload 'ispell-region "ispell" "Check spelling of words in the region" t)
(autoload 'ispell-word "ispell" "Check spelling of word at or before point" t)
(autoload 'monkey-directory "monkey" "Alternate directory edit mode" t nil)
(autoload 'rmail-buffer-to-vm "rmail2vm" "Rmail Conversion Functions" t nil)
(autoload 'rmail-folder-to-vm "rmail2vm" "Rmail Conversion Functions" t nil)
(autoload 'rmail-hierarchy-to-vm "rmail2vm" "Rmail Conversion Functions" t nil)
(autoload 'rmail-message-to-vm "rmail2vm" "Rmail Conversion Functions" t nil)
(autoload 'set-c-style "c-style" nil t)

(autoload 'vm "vm" "Visual Mail Reader" t nil)
(autoload 'vm-visit-folder "vm" "Visual Mail Reader" t nil)

; Under construction? Chip?
;(setq load-filters (nconc load-filters '((".Z" "zcat")
;					 (".z" "pcat" t)
;					 (".el.exe" t)))
;      load-suffixes ".elc:.el:.el.exe:.elc.Z:.elc.z:.el.Z:.el.z:.Z:.z:")
