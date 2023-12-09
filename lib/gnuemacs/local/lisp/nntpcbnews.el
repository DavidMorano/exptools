;;; This file contains stuff peculiar to using the
;;; psuedo-authenticated NNTP servers provided by AT&T Bell Labs in
;;; Columbus.  To use this quasi-transparently, put a line like:
;;;
;;;  (require 'nntpcbnews)
;;;
;;; at the bottom of nntp.el.  Look over the defvars just below to see
;;; if you need to change anything in your personal config.
;;; Byte-compile things and away you go.

(defvar cbnews-authinfo-method nil
  "Way in which authorization info is passed to cbnews NNTP servers.  For
people using machines named 'cbnews*', leave this nil and you'll get the plain
vanilla userid/username stuff.  If you're on a 'nntp*' machine, set this to
the string 'md5' (lower case).  Something like this:

	(setq cbnews-authinfo-method \"md5\")")

(defvar cbnews-md5-authfile nil
  "Name of a file containing the MD5 hash for cbnews md5 authorization.
If you don't specify, the file ~/.nntpauth will be used.  You create this by
running $TOOLS/lib/gnuemacs/local/etc/md5cbnews.")

(defvar cbnews-authinfo-username (user-login-name)
  "If for some reason you are authorized on cbnews NNTP servers as something
other than your real alpha login, set this variable to name your claimed
alias.  You're likely to not have any reason to do this.  See also
cbnews-authinfo-usernumber.")

(defvar cbnews-authinfo-usernumber (user-uid)
  "If for some reason you are authorized on cbnews NNTP servers as something
other than your real numeric userid, set this variable to name your claimed
alias.  You're likely to not have any reason to do this (it only applies to
to older authentication style anyhow).  See also cbnews-authinfo-username.")

;;
;; end of user-servicable parts
;;

(defun nntp-wait-for-response (regexp)
  "Wait for server response which matches REGEXP."
  (save-excursion
    (let ((status t)
	  (wait t))
      (set-buffer nntp-server-buffer)
      ;; Wait for status response (RFC977).
      ;; 1xx - Informative message.
      ;; 2xx - Command ok.
      ;; 3xx - Command ok so far, send the rest of it.
      ;; 4xx - Command was correct, but couldn't be performed for some
      ;;       reason.
      ;; 5xx - Command unimplemented, or incorrect, or a serious
      ;;       program error occurred.
      (nntp-accept-response)
      (while wait
		(goto-char (point-min))
		;;; wjc: added the following to toss initial noise
		(while (and (not (eobp)) (not (looking-at "[1-9][0-9][0-9][^0-9]"))) (kill-line))
		(if (and (looking-at "[1-9][0-9][0-9][^0-9]") (nntp-check-handlers))
			(progn
			  (goto-char (point-min))
			  (cond ((looking-at "[23]")
					 (setq wait nil))
					((looking-at "[45]")
					 (setq status nil)
					 (setq wait nil))
					))
		  (nntp-accept-response)))
      ;; Save status message.
      (end-of-line)
      (setq nntp-status-message-string
	    (buffer-substring (point-min) (point)))
      (if status
	  (progn
	    (setq wait t)
	    (while wait
	      (goto-char (point-max))
	      (forward-line -1)		;(beginning-of-line)
	      ;;(message (buffer-substring
	      ;;	 (point)
	      ;;	 (save-excursion (end-of-line) (point))))
	      (if (looking-at regexp)
		  (setq wait nil)

		  (if nntp-debug-read
			  (message "NNTP: Reading [%d]..." (buffer-size))) ;; wjc
;;		(message "NNTP: Reading...")
		(nntp-accept-response)
		(message "")
		))
	    ;; Successfully received server response.
	    t
	    ))
      )))


(defun nntp-check-handlers ()
  "doc to be provided"
  (save-excursion
		(re-search-forward "\\([0-9][0-9][0-9]\\)\\(.*\\)$")
		(goto-char (point-min))
		(let* (
			  (code (buffer-substring (match-beginning 1) (match-end 1)))
			  (note (buffer-substring (match-beginning 2) (match-end 2)))
			  (funk-NNN
			   (intern-soft
				(concat "nntp-response-handler-" code)))
			  (funk-NN-
			   (intern-soft
				(concat "nntp-response-handler-" (substring code 0 2) "-")))
			  (funk-N--
			   (intern-soft
				(concat "nntp-response-handler-" (substring code 0 1) "--")))
			  (funk----
			   (intern-soft
				"nntp-response-handler----"))
			  )
		  ; try progressively less specific handlers
		  (if (and funk-NNN (fboundp funk-NNN))
			  (funcall funk-NNN code note)
			(if (and funk-NN- (fboundp funk-NN-))
				(funcall funk-NN- code note)
			  (if (and funk-N-- (fboundp funk-N--))
				  (funcall funk-N-- code note)
				(if (and funk---- (fboundp funk----))
					(funcall funk---- code note)
				  t))))
		  ))
)

(defun cbnews-force-feed-authinfo (method)
  (save-excursion (set-buffer nntp-server-buffer) (erase-buffer))
  (if (equal "md5" method)
	  (let ((md5-result (cbnews-get-md5-result)))
		(if md5-result
			(nntp-send-strings-to-server
			 (message "%s" (concat "authinfo md5 " cbnews-authinfo-username " " md5-result)))
		  (nntp-response-trubble "999" "Can't cope with your md5 file")
		  (nntp-close-server)
		  (error "")
		  )))

  (if (not method)
	  (nntp-send-strings-to-server
	   (message "%s"
		(concat "authinfo " cbnews-authinfo-usernumber " " cbnews-authinfo-username)
		)))
t)

(defun nntp-response-handler-380 (code note)
  (cbnews-force-feed-authinfo nil))

(defun nntp-response-handler-4-- (code note)
  (nntp-response-trubble code note)
  t)

(defun nntp-response-handler-5-- (code note)
  (nntp-response-trubble code note)
  t)

(setq nntp-cbnews-access-errors
  '((502 .   ;;; ERR_ACCESS
	 "You are not authorized to use this machine as an NNTP server.
This could be due to one of two reasons:

	a)  This is not the NNTP server you should be using, or
	b)  You have not gone through the NNTP authorization process.

When you run GNUS, you should specify which machine to use as an NNTP
server via the shell environment variable NNTPSERVER or the GNUemacs
variable gnus-nntp-server.  Otherwise, specify the correct machine when
prompted.

To establish NNTP authorization, you need to run one of the following
commands.  If using DATAKIT, run 'dk nntpX.nntpauth' on your NNTP
client to authorize yourself for DK NNTP service.  If you are using
TCP/IP, run 'telnet nntpX.cb.att.com 1119' on your NNTP client to
authorize yourself for TCP NNTP service.  (Where 'nntpX' should be
replaced by the name of your particular news server: e.g., 'nntpb'.)
You'll be stepped through a sequence that will gather the necessary
information to establish your authorization for NNTP service.

You'll also need to create or recreate your MD5 auth file (either
pointed to by the elisp variable cbnews-md5-authfile or the default
file ~/.nntpauth).  To do that, you should run the program
'md5cbnews'.  On an exptools machine you will normally find this under
$TOOLS/lib/gnuemacs/local/etc/, a directory automatically on your
$PATH when running GNUemacs.  If it's not there, you will probably
find the files to build it and put it somewhere else on your $PATH.
See comments in $TOOLS/lib/gnuemacs/local/etc/md5cbnews.c.

If that's still too much bother, try running any cbnews *supported*
newsreader (ie, not GNUS) at least as far as the authentication step.
It will create the necessary file for you.

If you have news questions not specifically about GNUemacs or GNUS,
please call the Computing Technology Center Helpdesk at +1 614 860
4100 or send email to netnews!postmaster or postmaster@netnews.att.com.
Questions about using GNUS or GNUemacs should be directed to the
exptools GNUemacs providers (run 'providers gnuemacs' from the shell
prompt for contact information).
")
	(480 .   ;;; ERR_AUTHBAD
	 "This client machine did not send authorization information to the
NNTP server.
")
	(481 .   ;;; ERR_AUTHSYS
	 "There is a problem with the authorization data files on the NNTP
server.  Please call the Computing Technology Center Helpdesk to
inform them of the problem.  The number is +1 614 860 4100.
")
	(452 .   ;;; ERR_AUTHREJ
	 "The authorization information provided by GNUS did not match up
with the authorization information stored on the NNTP server.  Please
try again after verifying that you are using the appropriate NNTP
server machine (the one where you authorized yourself earlier).

If you are seeing this message multiple times, it may be that you
typed your NNTP password incorrectly the last time it was requested.
Try removing the file ~/.nntpauth and running the program

	$TOOLS/lib/gnuemacs/local/etc/md5cbnews

If there is no such program on your machine, look at the comments at
the top of the file $TOOLS/lib/gnuemacs/local/etc/md5cbnews.c to
create the program somewhere on your $PATH.
")
	(482 .   ;;; ERR_AUTHREJ
	 "The authorization information provided by GNUS did not match up
with the authorization information stored on the NNTP server.  Please
try again after verifying that you are using the appropriate NNTP
server machine (the one where you authorized yourself earlier).

If you are seeing this message multiple times, it may be that you
typed your NNTP password incorrectly the last time it was requested.
Try removing the file ~/.nntpauth and running the program

	$TOOLS/lib/gnuemacs/local/etc/md5cbnews

If there is no such program on your machine, look at the comments at
the top of the file $TOOLS/lib/gnuemacs/local/etc/md5cbnews.c to
create the program somewhere on your $PATH.
")
	(483 .   ;;; ERR_AUTHEXP
	 "Your authorization on the selected NNTP server has expired.
To rejuvenate your authorization, you need to run one of the following
commands.  If using DATAKIT, run 'dk nnptX.nntpauth' on your NNTP
client to authorize yourself for DK NNTP service.  If you are using
TCP/IP, run 'telnet nntpX.cb.att.com 1119' on your NNTP client to
authorize yourself for TCP NNTP service.  (Where 'nntpX' should be
replaced by the name of your particular news server: e.g., 'nntpb'.)
You'll be stepped through a sequence that will gather the necessary
information to rejuvenate your authorization for NNTP service.

You'll also need to create or recreate your MD5 auth file (either
pointed to by the elisp variable cbnews-md5-authfile or the default
file ~/.nntpauth).  To do that, you should run the program
'md5cbnews'.  On an exptools machine you will normally find this under
$TOOLS/lib/gnuemacs/local/etc/, a directory automatically on your
$PATH when running GNUemacs.  If it's not there, you will probably
find the files to build it and put it somewhere else on your $PATH.
See comments in $TOOLS/lib/gnuemacs/local/etc/md5cbnews.c.

If that's still too much bother, try running any cbnews *supported*
newsreader (ie, not GNUS) at least as far as the authentication step.
It will create the necessary file for you.

If you have news questions not specifically about GNUemacs or GNUS,
please call the Computing Technology Center Helpdesk at +1 614 860
4100 or send email to netnews!postmaster or postmaster@netnews.att.com.
Questions about using GNUS or GNUemacs should be directed to the
exptools GNUemacs providers (run 'providers gnuemacs' from the shell
prompt for contact information).
")

	(998 .   ;;; generic authorization help
	 "There is no specific detailed help message in GNUS for whatever problem
occured.  Although GNUS tries to have specific detailed descriptions
for all the authorization-specific problems, this depends on the NNTP server
responding with a specific error code (the number at the beginning of the
message).  Since that's a rather fragile arrangement, here is some generic
help, in case it looks to you like it's an authorization problem.  You might
also like to read over the file $TOOLS/lib/gnuemacs/local/tips/GNUSandNNTP
for a discussion of authorization and other sorts of configuration puzzles.

If your authorization is expired or otherwise rejected, you should
rejuvenate your authorization on the NNTP server and then recreate your
local MD5 auth file.

To rejuvenate your authorization, you need to run one of the following
commands.  If using DATAKIT, run 'dk nnptX.nntpauth' on your NNTP
client to authorize yourself for DK NNTP service.  If you are using
TCP/IP, run 'telnet nntpX.cb.att.com 1119' on your NNTP client to
authorize yourself for TCP NNTP service.  (Where 'nntpX' should be
replaced by the name of your particular news server: e.g., 'nntpb'.)
You'll be stepped through a sequence that will gather the necessary
information to rejuvenate your authorization for NNTP service.

To recreate your MD5 auth file (either pointed to by the elisp
variable cbnews-md5-authfile or the default file ~/.nntpauth), you
should run the program 'md5cbnews'.  On an exptools machine you will
normally find this under $TOOLS/lib/gnuemacs/local/etc/, a directory
automatically on your $PATH when running GNUemacs.  If it's not there,
you will probably find the files to build it and put it somewhere else
on your $PATH.  See comments in $TOOLS/lib/gnuemacs/local/etc/md5cbnews.c.

If that's still too much bother, try running any cbnews *supported*
newsreader (ie, not GNUS) at least as far as the authentication step.
It will create the necessary file for you.

If you have news questions not specifically about GNUemacs or GNUS,
please call the Computing Technology Center Helpdesk at +1 614 860
4100 or send email to netnews!postmaster or postmaster@netnews.att.com.
Questions about using GNUS or GNUemacs should be directed to the
exptools GNUemacs providers (run 'providers gnuemacs' from the shell
prompt for contact information).
")
	(999 .   ;;; local problem with md5cbnews
	 "GNUemacs can't find, can't read, or otherwise can't cope with
your MD5 auth file (either pointed to by the elisp variable
cbnews-md5-authfile or the default file ~/.nntpauth).  If you need to
regenerate this file, you should run the program 'md5cbnews'.  On an
exptools machine you will normally find this under
$TOOLS/lib/gnuemacs/local/etc/, a directory automatically on your
$PATH when running GNUemacs.  If it's not there, you will probably
find the files to build it and put it somewhere else on your $PATH.
See comments in $TOOLS/lib/gnuemacs/local/etc/md5cbnews.c.

If that's still too much bother, try running any cbnews *supported*
newsreader (ie, not GNUS) at least as far as the authentication step.
It will create the necessary file for you.
")
	))

(defun nntp-response-trubble (code note)
  (with-output-to-temp-buffer " *cbnews access trouble report*"
	  (princ "=============================================================\n")
	  (princ (format "%s %s\n" code note))
	  (princ "=============================================================\n")
	  (if (assoc (string-to-int code) nntp-cbnews-access-errors)
		  (princ (cdr (assoc (string-to-int code) nntp-cbnews-access-errors)))
		(princ (cdr (assoc 998 nntp-cbnews-access-errors)))
		)
	)
  (sleep-for 2)
)  

;; (defun nntp-response-handler-21- (code note)
;;   (message "@-%s<%s>" code note)
;;   (sleep-for 2)
;;   t)

;; (defun nntp-response-handler-2-- (code note)
;;   (message "@--%s<%s>" code note)
;;   (sleep-for 2)
;;   t)

;; (defun nntp-response-handler---- (code note)
;;   (message "@---%s<%s>" code note)
;;   (sleep-for 2)
;;   t)

(defun nntp-open-server (host &optional service)
  "Open news server on HOST.
If HOST is nil, use value of environment variable `NNTPSERVER'.
If optional argument SERVICE is non-nil, open by the service name."
  (let ((host (or host (getenv "NNTPSERVER")))
	(status nil))
    (setq nntp-status-string "")
    (cond ((and host (nntp-open-server-internal host service))
	   (setq status (nntp-wait-for-response "^[23].*\r$"))
	   ;; Do check unexpected close of connection.
	   ;; Suggested by feldmark@hanako.stars.flab.fujitsu.junet.
	   (if status
	       (set-process-sentinel nntp-server-process 'nntp-default-sentinel)
	     ;; We have to close connection here, since function
	     ;;  `nntp-server-opened' may return incorrect status.
	     (nntp-close-server-internal))
		 (if cbnews-authinfo-method
			 (progn
			   (cbnews-force-feed-authinfo cbnews-authinfo-method)
			   (setq status (nntp-wait-for-response "^[23].*\r$"))
			   (if status
				   (set-process-sentinel nntp-server-process 'nntp-default-sentinel)
				 (nntp-close-server-internal))
			   )
		   ))
	  ((null host)
	   (setq nntp-status-string "NNTP server is not specified."))
	  )
    status
    ))

(defun cbnews-get-md5-result ()
  (let ((authfile)
		(md5hash))
	(setq authfile (if cbnews-md5-authfile cbnews-md5-authfile
					 (expand-file-name "~/.nntpauth")))
	(if (file-exists-p authfile)
		(unwind-protect
			(save-excursion
			  (setq authbuf (find-file-noselect authfile))
			  (set-buffer authbuf)
			  (goto-char (point-min))
			  (forward-line)
			  (if (>= (- (point-max) (point)) 32)
				  (setq md5hash (buffer-substring (point) (+ 32 (point)))))
			  )
		  (kill-buffer authbuf))
	  )
	md5hash
))

(provide 'nntpcbnews)
