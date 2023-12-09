;From hogpc!houti!ariel!vax135!floyd!harpo!seismo!hao!hplabs!sri-unix!Jerry.Agin@CMU-RI-FAS.ARPA Mon Aug 15 10:52:00 1983
;Subject: line-to-bottom-of-window
;Newsgroups: net.emacs
; 
;Here's an improved version of line-to-bottom-of-window based on Hans
;Koomen's message of 30 Jul 83:

(error-occured		; window-width is already defined in some versions
    (defun (window-width 79)))
(defun
    (line-to-bottom-of-window	lines2skip chars2skip physlines
	(setq chars2skip (- (window-width) 1))
	(setq lines2skip (window-height))
	(setq physlines  (+ 1 (/ (- (current-column) 2) chars2skip)))
	(setq lines2skip (- lines2skip physlines))
	(save-excursion
	    (while (> lines2skip 0)
		   (previous-line)
		   (end-of-line)
		   (setq physlines (+ 1 (/ (- (current-column) 2) chars2skip)))
		   (setq lines2skip (- lines2skip physlines)))
	    (if (< lines2skip 0)
		(next-line))
	    (line-to-top-of-window)
	)
    )
)

;From hogpc!houti!ariel!hou5f!hou5g!hou5h!eagle!harpo!seismo!hao!hplabs!hp-pcd!rocheste!koomen Wed Dec 31 19:00:00 1969
;Relay-Version: version B 2.10 5/3/83; site pegasus.UUCP
;Posting-Version: version B 2.10 5/3/83; site hp-pcd.UUCP
;Path: pegasus!hogpc!houti!ariel!hou5f!hou5g!hou5h!eagle!harpo!seismo!hao!hplabs!hp-pcd!rocheste!koomen
;From: koomen@rocheste.UUCP
;Newsgroups: net.emacs
;Subject: Re: Orphaned Response - (nf)
;Message-ID: <1737@hp-pcd.UUCP>
;Date: Sun, 4-Sep-83 03:40:12 EDT
;Article-I.D.: hp-pcd.1737
;Posted: Sun Sep  4 03:40:12 1983
;Date-Received: Mon, 5-Sep-83 23:47:22 EDT
;Sender: netnews@hp-pcd.UUCP
;Organization: Hewlett-Packard, Corvallis OR
;Lines: 100
; 
;#R:sri-arpa:0:rocheste:-1:37777777600:2625
;rocheste!koomen    Jul 30 23:43:00 1983
; 
;From: Hans.Koomen
;Yeah, I've often wondered about that wrap feature myself.
;Here's my solution:
; 
;****************
;(defun					; "HaKo 05-12-83"
;    (window-width 80)	; should be built-in a la (window-height) !@#$%!
;
;    (line-to-bottom-of-window	curpos prevpos nextpos
;				lines2skip chars2skip physlines
;	(setq chars2skip (window-width))
;	(setq lines2skip (window-height))
;	(setq curpos (dot))
;	(line-to-top-of-window)
;	(beginning-of-line)
;	(setq nextpos (dot))
;	(setq physlines  (+ 1 (/ (- curpos nextpos) chars2skip)))
;	(setq lines2skip (- lines2skip physlines))
;	(while (> lines2skip 0)
;	       (previous-line)
;	       (beginning-of-line)
;	       (setq prevpos nextpos)
;	       (setq nextpos (dot))
;	       (setq physlines  (+ 1 (/ (- prevpos nextpos) chars2skip)))
;	       (setq lines2skip (- lines2skip physlines)))
;	(line-to-top-of-window)
;	(goto-character curpos)
;	(if (< lines2skip 0)
;	    (scroll-one-line-up))))
;
;****************
;
;I use this function to force the last line in the shell buffer to stay
;at the bottom of the window (simulating usual scrolling). Just in case
;you wonder how: (process.ml)
;
;****************
;(defun
;    (pr-newline
;	(end-of-line)
;	(if (eobp)
;	    (newline)
;	    (progn com
;		   (beginning-of-line)
;		   (if (looking-at shell-prompt) (region-around-match 0)
;		       (looking-at lisp-prompt) (region-around-match 0))
;		   (set-mark)
;		   (end-of-line)
;		   (forward-character)
;		   (setq com (region-to-string))
;		   (end-of-file)
;		   (set-mark)
;		   (insert-string com)
;	    )
;	)
;	(line-to-bottom-of-window)	; "HaKo 05-12-83"
;	(setq last-line (region-to-string))
;	(region-to-process (active-process))
;	(set-mark)
;    )
;
;    (shell
;	(pop-to-buffer "shell")
;	(setq needs-checkpointing 0)
;	(if (< (process-status "shell") 0)
;	    (start-filtered-process "csh -i" "shell" "more-shell-stuff"))
;;	    (start-process "csh -i" "shell"))	; "HaKo 05-12-83"
;	(local-bind-to-key "pr-newline" '^m')
;	(local-bind-to-key "send-eot" '')
;	(local-bind-to-key "send-int-signal" '')
;	(local-bind-to-key "send-quit-signal" '^\')
;	(local-bind-to-key "grab-last-line" "\e=")
;;	(local-bind-to-key "stop-shell" "\e\^Z")
;	(end-of-file)
;	(novalue)
;    )
;
;    (more-shell-stuff				; "HaKo 05-12-83"
;	(if (= (current-buffer-name) "shell")
;	    (progn (end-of-file)
;		   (insert-string (process-output))
;		   (set-mark)
;		   (line-to-bottom-of-window)
;		   (sit-for 0))
;	    (save-excursion 
;		(temp-use-buffer "shell")
;	    	(end-of-file)
;	    	(insert-string (process-output))
;	    	(set-mark)))))
;
;****************
;
;
;I know, it's a crock. Enjoy, anyway!
;
;-- Hans  (Koomen@Rochester or ..!seismo!rochester!koomen)
