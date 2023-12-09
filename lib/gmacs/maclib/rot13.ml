; LastEditDate="Tue Jun  4 21:57:08 1991"
; Path: pegasus!mtuxo!houxm!vax135!cornell!uw-beaver!tektronix!reed!agb
; >From: agb@reed.UUCP (Alexander G. Burchell)
; Newsgroups: net.jokes.d,net.emacs
; Subject: ROT13 functions for Gosling EMACS
; Date: Thu, 21-Nov-85 01:15:29 EST
; 
; Folks --
; 
; 	Here is some fun and useful code for Gosling EMACS.  To use it,
; just get in your file, and either set the mark at the start of the text
; to be rotated (usually ^@), then go to the end of it and use "rot13-region".
; Or, you may rotate the entire buffer with "rot13".
; 
(defun
   (rot13 odot
	  (setq odot (dot))
	  (message "Rotating buffer")
	  (sit-for 0)
	  (beginning-of-file)
	  (set-mark)
	  (end-of-file)
	  (rot13-region)
	  (goto-character odot))
   (rot13-region
	  (filter-region "tr [A-Z][a-z] [N-Z][A-M][n-z][a-m]")
	  (message "done"))
)
; 
; Have Fun!
; 
; 					Alexander G. Burchell
; 						
; UUCP:	..!{decvax,ucbvax,hplabs,ihnp4,zehntel}!tektronix!reed!agb
; MAIL:	Box 172, Reed College, 3203 SE Woodstock Dr., Portland OR 97202
