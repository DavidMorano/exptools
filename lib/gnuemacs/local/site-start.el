;;;
;;; Initialization for GNU emacs to allow machine independence
;;;
;;; Updated: 03/31/94 by Scott Thompson, Added support for version 19.XX
;;;

;;; Lisp version of environment variable which points at exptools
;;; tree.  Variable is set in the 'gnuemacs' front-end shell script.
;;;
(setq GNUEMACS_LIB (getenv "GNUEMACS_LIB"))

;;; Verify that appropriate environment variable exists!
;;;
(if (null GNUEMACS_LIB)
    (error "Environment variable 'GNUEMACS_LIB' has not been set!"))

;;; If exec-directory, data-directory and doc-directory have not been
;;; changed from paths.h settings, reset them point at exptools tree.
;;;
(if (equal exec-directory "/tmp/../")
    (setq exec-directory
	  (concat GNUEMACS_LIB "/dist/etc/"))) ; dist: ~/lib/emacs/<VER>/<ARCH>

(if (equal data-directory "/tmp/../")
    (setq data-directory
	  (concat GNUEMACS_LIB "/dist/etc/"))) ; dist: ~/lib/emacs/<VER>/etc

(if (equal doc-directory "/tmp/../")
    (setq data-directory
	  (concat GNUEMACS_LIB "/dist/etc/"))) ; dist: ~/lib/emacs/<VER>/etc

;;; Within exec-path, the executable search path (list), replace
;;; "PATH_EXEC" as defined in paths.h with local and dist dirs from
;;; exptools tree.
;;;
(setq exec-path
      (apply 'append
	     (mapcar '(lambda (e)
			(cond ((equal e "/tmp/../")
			       (list (concat GNUEMACS_LIB "/local/etc")
				     (concat GNUEMACS_LIB "/dist/etc")))
			      (t (list e))))
		     exec-path)))

; Now a function, see Info-default-directory-list below
;
;(setq Info-directory
;      (concat (getenv "GNUEMACS_LIB") "/dist/info"))

;;; Within Info-default-directory-list, the info search path (list),
;;; replace "PATH_INFO" as defined in paths.h with local and dist dirs
;;; from exptools tree.
;;;
(setq Info-default-directory-list
      (apply 'append
	     (mapcar '(lambda (e)
			(cond ((equal e "/tmp/../")
			       (list (concat GNUEMACS_LIB "/local/info")
				     (concat GNUEMACS_LIB "/dist/info")))
			      (t (list e))))
		     Info-default-directory-list)))

; for security reasons, let folks know about possible subterfuge
(setq inhibit-local-variables t)

; set up LISP code directory
(setq lisp-code-directory 
      (concat GNUEMACS_LIB "/local/etc/LCD-datafile"))
