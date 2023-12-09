#  @(#)  SID: 1.1;  module: concept.sh;  last changed: 6/23/91  11:20:57 */
#
#  This is the script that defines the gmacs database for the commands
#  used to program the concept 108 terminals.

PATH=$TOOLS/lib/gmacs/bin:$PATH		# Make sure we can get to db commands

dbcreate concept

dbadd concept 'transmission' <<"</FoO ThE bAr/>"
transmission
	O baud		Set buad rate
	P parity	Set parity
	Sp,< sbits	Set stop bits
	Sp,V		CTS/RTS protocol on
	Sp,v		CTS/RTS protocol off
	Sp,F		Buffer overflow control on
	Sp,f		Buffer overflow control off
	Sp,P		Parity check on
	Sp,p		Parity check off
	^T		Transmit line/field
	Sp,4		Transmit line/field (alternate)
	^D		Transmit window
	Sp,$		Transmit window (alternate)
	^V		Transmit all line/field
	Sp,6		Transmit all line/field (alternate)
	^F		Transmit all window
	Sp,&		Transmit all window (alternate)
	Sp,-		Create screen
	Sp,T		Trailing blank suppress on
	Sp,t		Trailing blank suppress off
	Sp,U		Underline transmit on
	Sp,u		Underline transmit off
	1		Start of print/transmit
	Sp,, delay	Set transmission delay
	rub		Initate break
</FoO ThE bAr/>
dbadd concept 'fkeys/data' <<"</FoO ThE bAr/>"
fkeys/data
	2 k		Display function key
	6 k		Program function key-screen
	4 len,k,t,msg	Program function key-general
	Sp,e k		Execute function key
	$		Reset all function keys
	Sp,= oper,k	Stored data display/storage
	Sp,I del,msg,del	Program latent expression
	Sp,E		Execute latent expression
	Sp,H del,msg,del	Program answerback message
	Sp,:		Transmit answerback message
	Sp,C		Store communications configuration
	Sp,S		Store configuration
	Sp,a		Display stored configuration
	Sp,~		Factory configuration reset
	Sp,/ pgs	Allocate memory
</FoO ThE bAr/>
dbadd concept 'APL/ASCII' <<"</FoO ThE bAr/>"
APL/ASCII
	0		APL mode
	)		ASCII mode
</FoO ThE bAr/>
dbadd concept 'keyboard' <<"</FoO ThE bAr/>"
keyboard
	Sp,K		Keyboard lock
	Sp,k		Keyboard unlock
	Sp,B		Keyboard bell enable
	Sp,b		Keyboard bell disable
	Sp,) dev	Keyboard communication line
	X		Set cursor pad to transmit
	x		Set cursor pad to execute
	Sp,X		Set cursor pad to transmit & execute
	Sp,\		Disable cursor pad
	Sp,x ckey,clev,cm	Set cursor pad keys--general
</FoO ThE bAr/>
dbadd concept 'network' <<"</FoO ThE bAr/>"
network	The device(s) that are to receive output from the requesting device
	coded as 32 + following value (or char in char code table):

	Display = 16		Line 1 = 8
	Line 2 = 4		Line 3 = 2
</FoO ThE bAr/>
dbadd concept 'general' <<"</FoO ThE bAr/>"
general
	Sp,? test	Self Test
	,		Reset
	o mess,char	Change message character
	Sp,y n		Attribute list selection
	Sp,Y n		Copy attribute list
	Sp,z n		Window selection
</FoO ThE bAr/>
dbadd concept 'editing' <<"</FoO ThE bAr/>"
editing
	Sp,m		Form feed--clear screen
	Sp,M		Form feed--top of page
	^P		Insert mode on
	Sp,0		Insert mode on (alternate)
	^@		Insert mode off
	Sp,Sp		Insert mode off (alternate)
	^Q		Delete character in line/field
	Sp,1		Delete character in line/field (alternate)
	^A		Delete character in window
	Sp,!		Delete character in window (alternate)
	^R		Insert line
	Sp,2		Insert line (alternate)
	^B		Delete line
	Sp,"		Delete line (alternate)
	^S		Clear to end of line/field
	Sp,3		Clear to end of line/field (alternate)
	^C		Clear to end of window
	Sp,#		Clear to end of window (alternate)
	^U		Clear all to EOL
	Sp,5		Clear all to EOL (alternate)
	^E		Clear all to EOW
	Sp,%		Clear all to EOW (alternate)
	^G intype	Set insert type
	Sp,' intype	Set insert type (alternate)
	^H m,w,char	Define clear characteristics
	Sp,( m,w,char	Define clear characteristics (alternate)
	Sp,+ margin	Set margin bell offset
</FoO ThE bAr/>
dbadd concept 'display' <<"</FoO ThE bAr/>"
display
	C		Blink on
	c		Blink off
	D		Reverse video on
	d		Reverse video off
	E		Half bright on
	e		Half bright off
	G		Underline on
	g		Underline off
	H		Nondisplay on
	h		Nondisplay off
	I		Protection on
	i		Protection off
	j cset		Select character set
	k		Screen reverse video
	K		Screen normal video
	M		Half bright protected fields
	m		Normal protected fields
	N w		Set attribute word
	n		Read attribute word
	J m,w,lns,cls	Set attribute of block
	r char,len	Repeat character horizontal
	R char,len	Repeat character vertical
	Sp,r		Replace character & attribute
	Sp,R		Replace character only
	Sp,A		Character & attribute display
	Sp,`		Set underline to change attribute
	Sp,@		Set underline to normal character
</FoO ThE bAr/>
dbadd concept 'devices' <<"</FoO ThE bAr/>"
devices
	Q dev,msg,EOF	Function route
	Y network	Set output network
	y		Read output network
	}		Attach printer
	~		Detach printer
	{		Print window
	|		Print line
	Z		Formfeed prior to print on
	z		Formfeed prior to print off
	@		Attach tape
	^		Detach tape
	`		Message to tape
</FoO ThE bAr/>
dbadd concept 'topics' <<"</FoO ThE bAr/>"
topics
	general		cursor		transmission
	APL/ASCII	editing		screen
	status		display		fkeys/data
	mode		devices		keyboard
</FoO ThE bAr/>
dbadd concept 'status' <<"</FoO ThE bAr/>"
status
	+		User status
	Sp,d		Scroll status lines forward
	Sp,D		Scroll status lines backward
	/ sline,dev	Display/transmit status
	Sp,.		Status line display off
	Sp,* del,msg,del	Set alert line message
	Sp,G		Alert line displayable
	Sp,g		Alert line not displayable
	Sp,; n		Set background status line
</FoO ThE bAr/>
dbadd concept 'screen' <<"</FoO ThE bAr/>"
screen
	!		Display width 80 columns
	"		Display width 132 columns
	v line,col,lns,cls	Define window
	Sp,^		Reset all windows
	Sp,Z		Define relative window
	-		Page up
	.		Page down
	\		Scroll up
	[		Scroll down
	V line		Start of screen
</FoO ThE bAr/>
dbadd concept 'parity' <<"</FoO ThE bAr/>"
parity	The parity to use
	none = Sp	even = !	odd = "
	mark = #	space = $
</FoO ThE bAr/>
dbadd concept 'margin' <<"</FoO ThE bAr/>"
margin	The number of columns from right side of window to right margin
	No margin = Sp		96 column offset = ^A,Sp
	1 column offset = !	97 column offset = ^A,!
	.			.
	.			131 column offset = ^A,C
	95 column offset = rub
</FoO ThE bAr/>
dbadd concept 'intype' <<"</FoO ThE bAr/>"
intype	The insert type to be used
	In window = Sp		In line = !
</FoO ThE bAr/>
dbadd concept 'cursor' <<"</FoO ThE bAr/>"
cursor
	Sp,L		Reverse line feed
	'		Back tab
	]		Tab set
	_		Tab clear
	Sp,_		Clear all tabs
	;		Cursor up
	<		Cursor down
	=		Cursor right
	>		Cursor left
	?		Home cursor
	a line,col	Write address (go to address)
	A		Read address
	p		End of text
	w		Set cursor to underline
	W		Set cursor to block
</FoO ThE bAr/>
dbadd concept 'sline' <<"</FoO ThE bAr/>"
sline	Selects a status line for display/transmission
	User = Sp		Programmer = !
	Tab Settings = "	Message Characters = #
	Alert Line = $
</FoO ThE bAr/>
dbadd concept 'sbits' <<"</FoO ThE bAr/>"
sbits	The number of stop bits
	1 stop bit = !		2 stop bits = "
</FoO ThE bAr/>
dbadd concept 'delay' <<"</FoO ThE bAr/>"
delay	The transmission delay
	No delay = Sp		100ms = !		200ms = "
	300ms = #		...			9500ms = rub
</FoO ThE bAr/>
dbadd concept 'Sp,Sp' <<"</FoO ThE bAr/>"
Sp,Sp		(Editing)	Insert mode off (alternate)
</FoO ThE bAr/>
dbadd concept 'test' <<"</FoO ThE bAr/>"
test	The self tests to be performed, 64 + following value
	(or 32 + following value in char code table):

	ROM test = 1		NVM test = 2
	RAM test = 4		communications character test = 8
	communications controls test = 16
	loop until failure = 32
</FoO ThE bAr/>
dbadd concept 'oper' <<"</FoO ThE bAr/>"
oper	The operation to be performed
	Setup and Display Function Key = Sp
	Display Function Key = !
	Program Function Key = "
	Setup and Display Answerback Message = #
	Display Answerback Message = $
	Define Answerback Message = %
	Setup and Display Latent Expression = &
	Display Latent Expression = '
	Define Latent Expression = (
</FoO ThE bAr/>
dbadd concept 'mode' <<"</FoO ThE bAr/>"
mode
	u		User mode
	U		Programmer mode
	f		Text mode
	F		Form mode
	s		Scroll mode
	S		Page mode
	7		Character mode
	&		Block mode
	5		Upper/lower case mode
	%		Caps lock mode
	8		Full duplex mode
	*		Half duplex mode
	9		Remode mode
	(		Local mode
	t		Transparent mode off
	T		Transparent mode on
	Sp,w		Auto wraparound off
	Sp,W		Auto wraparound on
	l		Auto linefeed off
	L		Auto linefeed on
	b		Auto tab off
	B		Auto tab on
</FoO ThE bAr/>
dbadd concept 'mess' <<"</FoO ThE bAr/>"
mess	The message character to be changed
	ESC = Sp	ACK = !		NAK = "
	SOM = #		EOF = $		EOL = %
	EOM = &		FKID = '	XON = (
	XOFF = )	Pad EOM = *	DLY = +
</FoO ThE bAr/>
dbadd concept 'line' <<"</FoO ThE bAr/>"
line	The line number, beginning at 0
	0 = Sp		96 = ^A,Sp
	1 = !		97 = ^A,!
	.		.
	.		.
	95 = rub	191 = ^A,rub
</FoO ThE bAr/>
dbadd concept 'cset' <<"</FoO ThE bAr/>"
cset	The character set
	ASCII = Sp	Graphics = !	APL = #
</FoO ThE bAr/>
dbadd concept 'clev' <<"</FoO ThE bAr/>"
clev	The key level
	All levels = Sp		Unshifted = !
	Shifted = "		Control-unshifted = #
	Control-shifted = $
</FoO ThE bAr/>
dbadd concept 'ckey' <<"</FoO ThE bAr/>"
ckey	Individual cursor pad key
	Mult-Code = Sp		Reset/Stat = !		Print = "
	Page = #		Cursor up = $		Tape = %
	Cursor left= &		Home = '		Cursor right = (
	Scrol = )		Cursor down= *		Tab Clr/Set = +
	Break = ,		B Tab = -
</FoO ThE bAr/>
dbadd concept 'char' <<"</FoO ThE bAr/>"
char	The actual character to be used
</FoO ThE bAr/>
dbadd concept 'baud' <<"</FoO ThE bAr/>"
baud	The baud rate
	50 = Sp		75 = !		110 = "
	134.5 = #	150 = $		300 = %
	600 = &		1200 = '	1800 = (
	2000 = )	2400 = *	3600 = +
	4800 = ,	7200 = -	9600 = .
</FoO ThE bAr/>
dbadd concept 'Sp,~' <<"</FoO ThE bAr/>"
Sp,~		(FKeys/Data)	Factory configuration reset
</FoO ThE bAr/>
dbadd concept 'Sp,z' <<"</FoO ThE bAr/>"
Sp,z n		(General)	Window selection
</FoO ThE bAr/>
dbadd concept 'Sp,y' <<"</FoO ThE bAr/>"
Sp,y n		(General)	Attribute list selection
</FoO ThE bAr/>
dbadd concept 'Sp,x' <<"</FoO ThE bAr/>"
Sp,x ckey,clev,cm	(Keyboard)	Set cursor pad keys--general
</FoO ThE bAr/>
dbadd concept 'Sp,w' <<"</FoO ThE bAr/>"
Sp,w		(Mode)		Auto wraparound off
</FoO ThE bAr/>
dbadd concept 'Sp,v' <<"</FoO ThE bAr/>"
Sp,v		(Transmission)	CTS/RTS protocol off
</FoO ThE bAr/>
dbadd concept 'Sp,u' <<"</FoO ThE bAr/>"
Sp,u		(Transmission)	Underline transmit off
</FoO ThE bAr/>
dbadd concept 'Sp,t' <<"</FoO ThE bAr/>"
Sp,t		(Transmission)	Trailing blank suppress off
</FoO ThE bAr/>
dbadd concept 'Sp,r' <<"</FoO ThE bAr/>"
Sp,r		(Display)	Replace character & attribute
</FoO ThE bAr/>
dbadd concept 'Sp,p' <<"</FoO ThE bAr/>"
Sp,p		(Transmission)	Parity check off
</FoO ThE bAr/>
dbadd concept 'Sp,m' <<"</FoO ThE bAr/>"
Sp,m		(Editing)	Form feed--clear screen
</FoO ThE bAr/>
dbadd concept 'Sp,k' <<"</FoO ThE bAr/>"
Sp,k		(Keyboard)	Keyboard unlock
</FoO ThE bAr/>
dbadd concept 'Sp,g' <<"</FoO ThE bAr/>"
Sp,g		(Status)	Alert line not displayable
</FoO ThE bAr/>
dbadd concept 'Sp,f' <<"</FoO ThE bAr/>"
Sp,f		(Transmission)	Buffer overflow control off
</FoO ThE bAr/>
dbadd concept 'Sp,e' <<"</FoO ThE bAr/>"
Sp,e k		(FKeys/Data)	Execute function key
</FoO ThE bAr/>
dbadd concept 'Sp,d' <<"</FoO ThE bAr/>"
Sp,d		(Status)	Scroll status lines forward
</FoO ThE bAr/>
dbadd concept 'Sp,b' <<"</FoO ThE bAr/>"
Sp,b		(Keyboard)	Keyboard bell disable
</FoO ThE bAr/>
dbadd concept 'Sp,a' <<"</FoO ThE bAr/>"
Sp,a		(FKeys/Data)	Display stored configuration
</FoO ThE bAr/>
dbadd concept 'Sp,`' <<"</FoO ThE bAr/>"
Sp,`		(Display)	Set underline to change attribute
</FoO ThE bAr/>
dbadd concept 'Sp,_' <<"</FoO ThE bAr/>"
Sp,_		(Cursor)	Clear all tabs
</FoO ThE bAr/>
dbadd concept 'Sp,^' <<"</FoO ThE bAr/>"
Sp,^		(Screen)	Reset all windows
</FoO ThE bAr/>
dbadd concept 'Sp,\' <<"</FoO ThE bAr/>"
Sp,\		(Keyboard)	Disable cursor pad
</FoO ThE bAr/>
dbadd concept 'Sp,Z' <<"</FoO ThE bAr/>"
Sp,Z		(Screen)	Define relative window
</FoO ThE bAr/>
dbadd concept 'Sp,Y' <<"</FoO ThE bAr/>"
Sp,Y n		(General)	Copy attribute list
</FoO ThE bAr/>
dbadd concept 'Sp,X' <<"</FoO ThE bAr/>"
Sp,X		(Keyboard)	Set cursor pad to transmit & execute
</FoO ThE bAr/>
dbadd concept 'Sp,W' <<"</FoO ThE bAr/>"
Sp,W		(Mode)		Auto wraparound on
</FoO ThE bAr/>
dbadd concept 'Sp,V' <<"</FoO ThE bAr/>"
Sp,V		(Transmission)	CTS/RTS protocol on
</FoO ThE bAr/>
dbadd concept 'Sp,U' <<"</FoO ThE bAr/>"
Sp,U		(Transmission)	Underline transmit on
</FoO ThE bAr/>
dbadd concept 'Sp,T' <<"</FoO ThE bAr/>"
Sp,T		(Transmission)	Trailing blank suppress on
</FoO ThE bAr/>
dbadd concept 'Sp,S' <<"</FoO ThE bAr/>"
Sp,S		(FKeys/Data)	Store configuration
</FoO ThE bAr/>
dbadd concept 'Sp,R' <<"</FoO ThE bAr/>"
Sp,R		(Display)	Replace character only
</FoO ThE bAr/>
dbadd concept 'Sp,P' <<"</FoO ThE bAr/>"
Sp,P		(Transmission)	Parity check on
</FoO ThE bAr/>
dbadd concept 'Sp,M' <<"</FoO ThE bAr/>"
Sp,M		(Editing)	Form feed--top of page
</FoO ThE bAr/>
dbadd concept 'Sp,L' <<"</FoO ThE bAr/>"
Sp,L		(Cursor)	Reverse line feed
</FoO ThE bAr/>
dbadd concept 'Sp,K' <<"</FoO ThE bAr/>"
Sp,K		(Keyboard)	Keyboard lock
</FoO ThE bAr/>
dbadd concept 'Sp,I' <<"</FoO ThE bAr/>"
Sp,I del,msg,del	(FKeys/Data)	Program latent expression
</FoO ThE bAr/>
dbadd concept 'Sp,H' <<"</FoO ThE bAr/>"
Sp,H del,msg,del	(FKeys/Data)	Program answerback message
</FoO ThE bAr/>
dbadd concept 'Sp,G' <<"</FoO ThE bAr/>"
Sp,G		(Status)	Alert line displayable
</FoO ThE bAr/>
dbadd concept 'Sp,F' <<"</FoO ThE bAr/>"
Sp,F		(Transmission)	Buffer overflow control on
</FoO ThE bAr/>
dbadd concept 'Sp,E' <<"</FoO ThE bAr/>"
Sp,E		(FKeys/Data)	Execute latent expression
</FoO ThE bAr/>
dbadd concept 'Sp,D' <<"</FoO ThE bAr/>"
Sp,D		(Status)	Scroll status lines backward
</FoO ThE bAr/>
dbadd concept 'Sp,C' <<"</FoO ThE bAr/>"
Sp,C		(FKeys/Data)	Store communications configuration
</FoO ThE bAr/>
dbadd concept 'Sp,B' <<"</FoO ThE bAr/>"
Sp,B		(Keyboard)	Keyboard bell enable
</FoO ThE bAr/>
dbadd concept 'Sp,A' <<"</FoO ThE bAr/>"
Sp,A		(Display)	Character & attribute display
</FoO ThE bAr/>
dbadd concept 'Sp,@' <<"</FoO ThE bAr/>"
Sp,@		(Display)	Set underline to normal character
</FoO ThE bAr/>
dbadd concept 'Sp,?' <<"</FoO ThE bAr/>"
Sp,? test	(General)	Self Test
</FoO ThE bAr/>
dbadd concept 'Sp,=' <<"</FoO ThE bAr/>"
Sp,= oper,k	(FKeys/Data)	Stored data display/storage
</FoO ThE bAr/>
dbadd concept 'Sp,<' <<"</FoO ThE bAr/>"
Sp,< sbits	(Transmission)	Set stop bits
</FoO ThE bAr/>
dbadd concept 'Sp,;' <<"</FoO ThE bAr/>"
Sp,; n		(Status)	Set background status line
</FoO ThE bAr/>
dbadd concept 'Sp,:' <<"</FoO ThE bAr/>"
Sp,:		(FKeys/Data)	Transmit answerback message
</FoO ThE bAr/>
dbadd concept 'Sp,6' <<"</FoO ThE bAr/>"
Sp,6		(Transmission)	Transmit all line/field (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,5' <<"</FoO ThE bAr/>"
Sp,5		(Editing)	Clear all to EOL (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,4' <<"</FoO ThE bAr/>"
Sp,4		(Transmission)	Transmit line/field (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,3' <<"</FoO ThE bAr/>"
Sp,3		(Editing)	Clear to end of line/field (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,2' <<"</FoO ThE bAr/>"
Sp,2		(Editing)	Insert line (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,1' <<"</FoO ThE bAr/>"
Sp,1		(Editing)	Delete character in line/field (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,0' <<"</FoO ThE bAr/>"
Sp,0		(Editing)	Insert mode on (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,/' <<"</FoO ThE bAr/>"
Sp,/ pgs	(FKeys/Data)	Allocate memory
</FoO ThE bAr/>
dbadd concept 'Sp,.' <<"</FoO ThE bAr/>"
Sp,.		(Status)	Status line display off
</FoO ThE bAr/>
dbadd concept 'Sp,-' <<"</FoO ThE bAr/>"
Sp,-		(Transmission)	Create screen
</FoO ThE bAr/>
dbadd concept 'Sp,,' <<"</FoO ThE bAr/>"
Sp,, delay	(Transmission)	Set transmission delay
</FoO ThE bAr/>
dbadd concept 'Sp,+' <<"</FoO ThE bAr/>"
Sp,+ margin	(Editing)	Set margin bell offset
</FoO ThE bAr/>
dbadd concept 'Sp,*' <<"</FoO ThE bAr/>"
Sp,* del,msg,del	(Status)	Set alert line message
</FoO ThE bAr/>
dbadd concept 'Sp,)' <<"</FoO ThE bAr/>"
Sp,) dev	(Keyboard)	Keyboard communication line
</FoO ThE bAr/>
dbadd concept 'Sp,(' <<"</FoO ThE bAr/>"
Sp,( m,w,char	(Editing)	Define clear characteristics (alternate)
</FoO ThE bAr/>
dbadd concept "Sp,'" <<"</FoO ThE bAr/>"
Sp,' intype	(Editing)	Set insert type (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,&' <<"</FoO ThE bAr/>"
Sp,&		(Transmission)	Transmit all window (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,%' <<"</FoO ThE bAr/>"
Sp,%		(Editing)	Clear all to EOW (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,$' <<"</FoO ThE bAr/>"
Sp,$		(Transmission)	Transmit window (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,#' <<"</FoO ThE bAr/>"
Sp,#		(Editing)	Clear to end of window (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,"' <<"</FoO ThE bAr/>"
Sp,"		(Editing)	Delete line (alternate)
</FoO ThE bAr/>
dbadd concept 'Sp,!' <<"</FoO ThE bAr/>"
Sp,!		(Editing)	Delete character in window (alternate)
</FoO ThE bAr/>
dbadd concept 'tie' <<"</FoO ThE bAr/>"
tie	The window to use
	Keyboard's = Sp		Window 1 = !
	Window 2 = "		Window 3 = #
</FoO ThE bAr/>
dbadd concept 'rub' <<"</FoO ThE bAr/>"
rub		(Transmission)	Initate break
</FoO ThE bAr/>
dbadd concept 'pgs' <<"</FoO ThE bAr/>"
pgs	The number of pages of display memory
	1 page = !	2 pages = "	3 pages = #
	4 pages = $	5 pages = %	6 pages = &
	7 pages = '	8 pages = (
</FoO ThE bAr/>
dbadd concept 'msg' <<"</FoO ThE bAr/>"
msg	A sequence of characters defining a message
</FoO ThE bAr/>
dbadd concept 'lns' <<"</FoO ThE bAr/>"
lns	The number of lines to use
	0 = Sp		96 = ^A,Sp	   192 = ^B,Sp
	1 = !		97 = ^A,!
	.		.
	.		.
	95 = rub	191 = ^A,rub
</FoO ThE bAr/>
dbadd concept 'len' <<"</FoO ThE bAr/>"
len	Length
	0 = Sp		96 = ^A,Sp
	1 = !		97 = ^A,!
	.		.
	.		131 = ^A,C
	95 = rub
</FoO ThE bAr/>
dbadd concept 'dev' <<"</FoO ThE bAr/>"
dev	One of the terminal devices
	Keyboard/Display = Sp	Line 1 = !
	Line 2 = "		Line 3 = #
</FoO ThE bAr/>
dbadd concept 'del' <<"</FoO ThE bAr/>"
del	A delimiter character
</FoO ThE bAr/>
dbadd concept 'col' <<"</FoO ThE bAr/>"
col	The column number, beginning with 0
	0 = Sp		96 = ^A,Sp
	1 = !		97 = ^A,!
	.		.
	.		131 = ^A,C
	95 = rub
</FoO ThE bAr/>
dbadd concept 'cls' <<"</FoO ThE bAr/>"
cls	The number of columns to use
	1 = !		96 = ^A,Sp
	2 = "		97 = ^A,!
	3 = #		98 = ^A,"
	.		.
	.		132 = ^A,D
	95 = rub
</FoO ThE bAr/>
dbadd concept 'EOF' <<"</FoO ThE bAr/>"
EOF	The end of field character
	Default: ^W
</FoO ThE bAr/>
dbadd concept 'cm' <<"</FoO ThE bAr/>"
cm	The key mode
	Transmit = Sp			Execute = !
	Transmit & execute = "		Disable = #
</FoO ThE bAr/>
dbadd concept '^V' <<"</FoO ThE bAr/>"
^V		(Transmission)	Transmit all line/field
</FoO ThE bAr/>
dbadd concept '^U' <<"</FoO ThE bAr/>"
^U		(Editing)	Clear all to EOL
</FoO ThE bAr/>
dbadd concept '^T' <<"</FoO ThE bAr/>"
^T		(Transmission)	Transmit line/field
</FoO ThE bAr/>
dbadd concept '^S' <<"</FoO ThE bAr/>"
^S		(Editing)	Clear to end of line/field
</FoO ThE bAr/>
dbadd concept '^R' <<"</FoO ThE bAr/>"
^R		(Editing)	Insert line
</FoO ThE bAr/>
dbadd concept '^Q' <<"</FoO ThE bAr/>"
^Q		(Editing)	Delete character in line/field
</FoO ThE bAr/>
dbadd concept '^P' <<"</FoO ThE bAr/>"
^P		(Editing)	Insert mode on
</FoO ThE bAr/>
dbadd concept '^H' <<"</FoO ThE bAr/>"
^H m,w,char	(Editing)	Define clear characteristics
</FoO ThE bAr/>
dbadd concept '^G' <<"</FoO ThE bAr/>"
^G intype	(Editing)	Set insert type
</FoO ThE bAr/>
dbadd concept '^F' <<"</FoO ThE bAr/>"
^F		(Transmission)	Transmit all window
</FoO ThE bAr/>
dbadd concept '^E' <<"</FoO ThE bAr/>"
^E		(Editing)	Clear all to EOW
</FoO ThE bAr/>
dbadd concept '^D' <<"</FoO ThE bAr/>"
^D		(Transmission)	Transmit window
</FoO ThE bAr/>
dbadd concept '^C' <<"</FoO ThE bAr/>"
^C		(Editing)	Clear to end of window
</FoO ThE bAr/>
dbadd concept '^B' <<"</FoO ThE bAr/>"
^B		(Editing)	Delete line
</FoO ThE bAr/>
dbadd concept '^A' <<"</FoO ThE bAr/>"
^A		(Editing)	Delete character in window
</FoO ThE bAr/>
dbadd concept '^@' <<"</FoO ThE bAr/>"
^@		(Editing)	Insert mode off
</FoO ThE bAr/>
dbadd concept '~' <<"</FoO ThE bAr/>"
~		(Devices)	Detach printer
</FoO ThE bAr/>
dbadd concept '}' <<"</FoO ThE bAr/>"
}		(Devices)	Attach printer
</FoO ThE bAr/>
dbadd concept '|' <<"</FoO ThE bAr/>"
|		(Devices)	Print line
</FoO ThE bAr/>
dbadd concept '{' <<"</FoO ThE bAr/>"
{		(Devices)	Print window
</FoO ThE bAr/>
dbadd concept 'z' <<"</FoO ThE bAr/>"
z		(Devices)	Formfeed prior to print off
</FoO ThE bAr/>
dbadd concept 'y' <<"</FoO ThE bAr/>"
y		(Devices)	Read output network
</FoO ThE bAr/>
dbadd concept 'x' <<"</FoO ThE bAr/>"
x		(Keyboard)	Set cursor pad to execute
</FoO ThE bAr/>
dbadd concept 'w' <<"</FoO ThE bAr/>"
w	The desired attribute setting, 64 + following values
	(or 32 + following value in char code table):

	Nondisplay = 1		Blink on = 2
	Underline on = 4	Unprotected = 8
	Half bright on = 16	Reverse video = 32
</FoO ThE bAr/>
dbadd concept 'v' <<"</FoO ThE bAr/>"
v line,col,lns,cls	(Screen)	Define window
</FoO ThE bAr/>
dbadd concept 'u' <<"</FoO ThE bAr/>"
u		(Mode)		User mode
</FoO ThE bAr/>
dbadd concept 't' <<"</FoO ThE bAr/>"
t	The function key transmission mode
	Restore default sequence and set transmit mode = Sp
	Restore default sequence and set execute mode = !
	Set transmit mode only = "
	Set execute mode only = #
</FoO ThE bAr/>
dbadd concept 's' <<"</FoO ThE bAr/>"
s		(Mode)		Scroll mode
</FoO ThE bAr/>
dbadd concept 'r' <<"</FoO ThE bAr/>"
r char,len	(Display)	Repeat character horizontal
</FoO ThE bAr/>
dbadd concept 'p' <<"</FoO ThE bAr/>"
p		(Cursor)	End of text
</FoO ThE bAr/>
dbadd concept 'o' <<"</FoO ThE bAr/>"
o mess,char	(General)	Change message character
</FoO ThE bAr/>
dbadd concept 'n' <<"</FoO ThE bAr/>"
n		(Display)	Read attribute word
</FoO ThE bAr/>
dbadd concept 'm' <<"</FoO ThE bAr/>"
m	The attributes which are to be affected, 64 + following values:
	(32 + following values in character code table)

	Display/Nondisplay = 1		Blink on/off = 2
	Underlining = 4			Protection = 8
	Brightness = 16			Normal/Reverse video = 32
</FoO ThE bAr/>
dbadd concept 'l' <<"</FoO ThE bAr/>"
l		(Mode)		Auto linefeed off
</FoO ThE bAr/>
dbadd concept 'k' <<"</FoO ThE bAr/>"
k	Function key
	
	Key		Un/shifted		Key	Un/shifted
	Insert		0/Sp			F6	:/*
	Del Char	1/!			F7	;/+
	Line Ins/Del	2/"			F8	</,
	Clear EOL/EOP	3/#			F9	=/-
	Send		4/$			F10	>/.
	F1		5/%			F11	?//
	F2		6/&			F12	@/C
	F3		7/'			F13	A/D
	F4		8/(			F14	B/E
	F5		9/)
	
	If command is entered from keyboard, actual function key
	can be pressed.
</FoO ThE bAr/>
dbadd concept 'j' <<"</FoO ThE bAr/>"
j cset		(Display)	Select character set
</FoO ThE bAr/>
dbadd concept 'i' <<"</FoO ThE bAr/>"
i		(Display)	Protection off
</FoO ThE bAr/>
dbadd concept 'h' <<"</FoO ThE bAr/>"
h		(Display)	Nondisplay off
</FoO ThE bAr/>
dbadd concept 'g' <<"</FoO ThE bAr/>"
g		(Display)	Underline off
</FoO ThE bAr/>
dbadd concept 'f' <<"</FoO ThE bAr/>"
f		(Mode)		Text mode
</FoO ThE bAr/>
dbadd concept 'e' <<"</FoO ThE bAr/>"
e		(Display)	Half bright off
</FoO ThE bAr/>
dbadd concept 'd' <<"</FoO ThE bAr/>"
d		(Display)	Reverse video off
</FoO ThE bAr/>
dbadd concept 'c' <<"</FoO ThE bAr/>"
c		(Display)	Blink off
</FoO ThE bAr/>
dbadd concept 'b' <<"</FoO ThE bAr/>"
b		(Mode)		Auto tab off
</FoO ThE bAr/>
dbadd concept 'a' <<"</FoO ThE bAr/>"
a line,col	(Cursor)	Write address (go to address)
</FoO ThE bAr/>
dbadd concept '`' <<"</FoO ThE bAr/>"
`		(Devices)	Message to tape
</FoO ThE bAr/>
dbadd concept '_' <<"</FoO ThE bAr/>"
_		(Cursor)	Tab clear
</FoO ThE bAr/>
dbadd concept '^' <<"</FoO ThE bAr/>"
^		(Devices)	Detach tape
</FoO ThE bAr/>
dbadd concept ']' <<"</FoO ThE bAr/>"
]		(Cursor)	Tab set
</FoO ThE bAr/>
dbadd concept '\' <<"</FoO ThE bAr/>"
\		(Screen)	Scroll up
</FoO ThE bAr/>
dbadd concept '[' <<"</FoO ThE bAr/>"
[		(Screen)	Scroll down
</FoO ThE bAr/>
dbadd concept 'Z' <<"</FoO ThE bAr/>"
Z		(Devices)	Formfeed prior to print on
</FoO ThE bAr/>
dbadd concept 'Y' <<"</FoO ThE bAr/>"
Y network	(Devices)	Set output network
</FoO ThE bAr/>
dbadd concept 'X' <<"</FoO ThE bAr/>"
X		(Keyboard)	Set cursor pad to transmit
</FoO ThE bAr/>
dbadd concept 'W' <<"</FoO ThE bAr/>"
W		(Cursor)	Set cursor to block
</FoO ThE bAr/>
dbadd concept 'V' <<"</FoO ThE bAr/>"
V line		(Screen)	Start of screen
</FoO ThE bAr/>
dbadd concept 'U' <<"</FoO ThE bAr/>"
U		(Mode)		Programmer mode
</FoO ThE bAr/>
dbadd concept 'T' <<"</FoO ThE bAr/>"
T		(Mode)		Transparent mode on
</FoO ThE bAr/>
dbadd concept 'S' <<"</FoO ThE bAr/>"
S		(Mode)		Page mode
</FoO ThE bAr/>
dbadd concept 'R' <<"</FoO ThE bAr/>"
R char,len	(Display)	Repeat character vertical
</FoO ThE bAr/>
dbadd concept 'Q' <<"</FoO ThE bAr/>"
Q dev,msg,EOF	(Devices)	Function route
</FoO ThE bAr/>
dbadd concept 'P' <<"</FoO ThE bAr/>"
P parity	(Transmission)	Set parity
</FoO ThE bAr/>
dbadd concept 'O' <<"</FoO ThE bAr/>"
O baud		(Transmission)	Set buad rate
</FoO ThE bAr/>
dbadd concept 'N' <<"</FoO ThE bAr/>"
N w		(Display)	Set attribute word
</FoO ThE bAr/>
dbadd concept 'M' <<"</FoO ThE bAr/>"
M		(Display)	Half bright protected fields
</FoO ThE bAr/>
dbadd concept 'L' <<"</FoO ThE bAr/>"
L		(Mode)		Auto linefeed on
</FoO ThE bAr/>
dbadd concept 'K' <<"</FoO ThE bAr/>"
K		(Display)	Screen normal video
</FoO ThE bAr/>
dbadd concept 'J' <<"</FoO ThE bAr/>"
J m,w,lns,cls	(Display)	Set attribute of block
</FoO ThE bAr/>
dbadd concept 'I' <<"</FoO ThE bAr/>"
I		(Display)	Protection on
</FoO ThE bAr/>
dbadd concept 'H' <<"</FoO ThE bAr/>"
H		(Display)	Nondisplay on
</FoO ThE bAr/>
dbadd concept 'G' <<"</FoO ThE bAr/>"
G		(Display)	Underline on
</FoO ThE bAr/>
dbadd concept 'F' <<"</FoO ThE bAr/>"
F		(Mode)		Form mode
</FoO ThE bAr/>
dbadd concept 'E' <<"</FoO ThE bAr/>"
E		(Display)	Half bright on
</FoO ThE bAr/>
dbadd concept 'D' <<"</FoO ThE bAr/>"
D		(Display)	Reverse video on
</FoO ThE bAr/>
dbadd concept 'C' <<"</FoO ThE bAr/>"
C		(Display)	Blink on
</FoO ThE bAr/>
dbadd concept 'B' <<"</FoO ThE bAr/>"
B		(Mode)		Auto tab on
</FoO ThE bAr/>
dbadd concept 'A' <<"</FoO ThE bAr/>"
A		(Cursor)	Read address
</FoO ThE bAr/>
dbadd concept '@' <<"</FoO ThE bAr/>"
@		(Devices)	Attach tape
</FoO ThE bAr/>
dbadd concept '?' <<"</FoO ThE bAr/>"
?		(Cursor)	Home cursor
</FoO ThE bAr/>
dbadd concept '>' <<"</FoO ThE bAr/>"
>		(Cursor)	Cursor left
</FoO ThE bAr/>
dbadd concept '=' <<"</FoO ThE bAr/>"
=		(Cursor)	Cursor right
</FoO ThE bAr/>
dbadd concept '<' <<"</FoO ThE bAr/>"
<		(Cursor)	Cursor down
</FoO ThE bAr/>
dbadd concept ';' <<"</FoO ThE bAr/>"
;		(Cursor)	Cursor up
</FoO ThE bAr/>
dbadd concept '9' <<"</FoO ThE bAr/>"
9		(Mode)		Remode mode
</FoO ThE bAr/>
dbadd concept '8' <<"</FoO ThE bAr/>"
8		(Mode)		Full duplex mode
</FoO ThE bAr/>
dbadd concept '7' <<"</FoO ThE bAr/>"
7		(Mode)		Character mode
</FoO ThE bAr/>
dbadd concept '6' <<"</FoO ThE bAr/>"
6 k		(FKeys/Data)	Program function key-screen
</FoO ThE bAr/>
dbadd concept '5' <<"</FoO ThE bAr/>"
5		(Mode)		Upper/lower case mode
</FoO ThE bAr/>
dbadd concept '4' <<"</FoO ThE bAr/>"
4 len,k,t,msg	(FKeys/Data)	Program function key-general
</FoO ThE bAr/>
dbadd concept '2' <<"</FoO ThE bAr/>"
2 k		(FKeys/Data)	Display function key
</FoO ThE bAr/>
dbadd concept '1' <<"</FoO ThE bAr/>"
1		(Transmission)	Start of print/transmit
</FoO ThE bAr/>
dbadd concept '0' <<"</FoO ThE bAr/>"
0		(APL/ASCII)	APL mode
</FoO ThE bAr/>
dbadd concept '/' <<"</FoO ThE bAr/>"
/ sline,dev	(Status)	Display/transmit status
</FoO ThE bAr/>
dbadd concept '.' <<"</FoO ThE bAr/>"
.		(Screen)	Page down
</FoO ThE bAr/>
dbadd concept '-' <<"</FoO ThE bAr/>"
-		(Screen)	Page up
</FoO ThE bAr/>
dbadd concept ',' <<"</FoO ThE bAr/>"
,		(General)	Reset
</FoO ThE bAr/>
dbadd concept '+' <<"</FoO ThE bAr/>"
+		(Status)	User status
</FoO ThE bAr/>
dbadd concept '*' <<"</FoO ThE bAr/>"
*		(Mode)		Half duplex mode
</FoO ThE bAr/>
dbadd concept ')' <<"</FoO ThE bAr/>"
)		(APL/ASCII)	ASCII mode
</FoO ThE bAr/>
dbadd concept '(' <<"</FoO ThE bAr/>"
(		(Mode)		Local mode
</FoO ThE bAr/>
dbadd concept "'" <<"</FoO ThE bAr/>"
'		(Cursor)	Back tab
</FoO ThE bAr/>
dbadd concept '&' <<"</FoO ThE bAr/>"
&		(Mode)		Block mode
</FoO ThE bAr/>
dbadd concept '%' <<"</FoO ThE bAr/>"
%		(Mode)		Caps lock mode
</FoO ThE bAr/>
dbadd concept '$' <<"</FoO ThE bAr/>"
$		(FKeys/Data)	Reset all function keys
</FoO ThE bAr/>
dbadd concept '"' <<"</FoO ThE bAr/>"
"		(Screen)	Display width 132 columns
</FoO ThE bAr/>
dbadd concept '!' <<"</FoO ThE bAr/>"
!		(Screen)	Display width 80 columns
</FoO ThE bAr/>
