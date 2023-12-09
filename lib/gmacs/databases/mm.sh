#  @(#)  SID: 1.1;  module: mm.sh;  last changed: 6/23/91  11:21:21 */
#
#  This is the script that defines the gmacs database for the mm macros.

PATH=$TOOLS/lib/gmacs/bin:$PATH		# Make sure we can get to db commands

dbcreate mm

dbadd mm 'miscellaneous' <<"</FoO ThE bAr/>"
miscellaneous
	SA	Justify the right margin.
	2C	Two-column output.
	1C	One-column output.
</FoO ThE bAr/>
dbadd mm 'references' <<"</FoO ThE bAr/>"
references
	RS	Reference start.
	RF	Reference end.
	Rf	Reference numbering string.
	RP	Reference page.
	Rp	Reference-page title string.
</FoO ThE bAr/>
dbadd mm 'registers' <<"</FoO ThE bAr/>"
registers
	C	Copy type (Original, DRAFT, etc.).
	Cl	TOC heading level register.
	De	Floating-display end-processing control register.
	Df	Floating-display output control register.
	Ej	Start-of-page heading level register.
	Hb	Stand-alone heading level register.
	Hc	Centering heading level register.
	Hs	Trailing-blank-line heading level register.
	Ht	Mark-concatenation heading control register.
	Hu	Unnumbered-heading level register.
	Pi	Paragraph-indent amount register.
	Pt	Paragraph-indent control register.
</FoO ThE bAr/>
dbadd mm 'footnotes' <<"</FoO ThE bAr/>"
footnotes
	FS	Footnote start.
	FE	Footnote end.
	FD	Footnote default format.
	F	Footnote numbering string.
</FoO ThE bAr/>
dbadd mm 'headings' <<"</FoO ThE bAr/>"
headings
	P	Paragraph.
	Pt	Paragraph-style control register.
	Pi	Paragraph-indent amount register.
	Np	Numbered-paragraph control register.
	nP	Numbered paragraph.
	H	Numbered heading.
	HU	Unnumbered heading.
	Hu	Unnumbered-heading level register.
	HF	Heading-font control string.
	HM	Heading-mark style.
	TC	Table of contents.
	Cl	TOC heading level register.
	Ej	Start-of-page heading level register.
	Hb	Stand-alone heading level register.
	Hc	Centering heading level register.
	Hs	Trailing-blank-line heading level register.
	Ht	Mark-concatenation heading control register.
</FoO ThE bAr/>
dbadd mm 'displays' <<"</FoO ThE bAr/>"
displays
	DS	Static display.
	DF	Floating display.
	DE	Display end.
	Df	Floating-display output control register.
	De	Floating-display end-processing control register.
	FG	Figure title.
	Of	Figure-title style control register.
	EQ	Equation display start.
	EN	Equation display end.
	Eq	Equation-label style control register.
	EC	Equation caption.
	TS	Table start.
	T&	Redefine columns in a table.
	TE	Table end.
	TB	Table title.
</FoO ThE bAr/>
dbadd mm 'strings' <<"</FoO ThE bAr/>"
strings
	DT	Date string.
	F	Footnote numbering string.
	HF	Heading-font control string.
	Le	Equation-list title string.
	Lf	Figure-list title string.
	Lt	Table-list title string.
	Rf	Reference numbering string.
	Rp	Reference-page title string.
</FoO ThE bAr/>
dbadd mm 'headers' <<"</FoO ThE bAr/>"
headers
	PH	Page header.
	OH	Odd-page header.
	EH	Even-page header.
	PF	Page footer.
	OF	Odd-page footer.
	EF	Even-page footer.
</FoO ThE bAr/>
dbadd mm 'topics' <<"</FoO ThE bAr/>"
topics
	displays (regular displays, tables, equations, figures, titles)
	fonts
	footnotes
	headers (page headers and footers)
	headings (headings, paragraphs, table of contents)
	lists
	references
	registers
	strings
	styles (abstracts, memo types, authors, notations, dates)
	miscellaneous (right justification, two-column output)
	models (memo skeletons that can be copied and used)
</FoO ThE bAr/>
dbadd mm 'styles' <<"</FoO ThE bAr/>"
styles
	MT	Memorandum type.
	TL	Memorandum title.
	AS	Abstract start.
	AE	Abstract end.
	NS	Notation.
	AU	Author identification.
	AT	Author title.
	FC	Formal closing.
	SG	Signature.
	ND	New date.
	DT	Current-date string.
</FoO ThE bAr/>
dbadd mm 'models' <<"</FoO ThE bAr/>"
models
	memo	Ordinary, basic memorandum.
	memo2	Memorandum with footnotes, references, TOC, & appendices.
</FoO ThE bAr/>
dbadd mm 'memo2' <<"</FoO ThE bAr/>"
memo2	Memorandum with footnotes, references, TOC, & appendices.
	(Write this to a file and run mm on it to see how it works.)

.SA 1
.nr Pt 0
.tr ~
.TL 12003-1641 40288-700
*** title
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.AU "G.V.E. Otto" GVEO IX 55633 1253 1G-307 55633-yymmdd.nnMF
.AS 2
*** abstract
.AE
.NS
*** people to get memo  (delete this section if Abstract is deleted)
.NE
.NS "abstract only"
*** people to get abstract  (delete this section if Abstract is deleted)
.NE
.MT "MEMORANDUM FOR FILE"
.H 1 "INTRODUCTION"
*** what this memo is about
.H 1 "*** body section title"
*** body of memo
.P
This is an example\*(Rf
.RS
This is the first reference.
.RF
of how references can be used in a paper and then printed\*F
.FS
This is a footnote.
.FE
at the end of the paper.
.H 1 "CONCLUSION"
*** what this memo was about
.SG ""
.NS 4
*** list of attachments
.NE
.NS
*** people to get memo  (delete this section if Abstract is used)
.NE
.*
.*  Reference page generated here.
.RP 0 1
.*
.*  Set up for appendix processing.
.nr Hu 1
.HM A 1 1 1 1 1 1
.nr H1 0
.*
.*  Define the appendix header macro: .aH
.de aH
.nr Hc 1
.if !'\\$3'' .if \\$3 .nr P 0
.PH "''''"
.SK
.HU "APPENDIX \\\\\\\\n(H1: \\$1"
.ie '\\$2'' .PH "'APPENDIX \\\\\\\\n(H1:'- \\\\\\\\nP -'\\$1'"
.el         .PH "'APPENDIX \\\\\\\\n(H1:'- \\\\\\\\nP -'\\$2'"
..
.*
.*  Example use of .aH
.*	First argument is title to appear on main page
.*	Second argument is short title to appear in heading of all following
.*		pages.  If omitted, this defaults to the first argument.
.*	Third argument controls whether the appendix page numbering will
.*		continue normally or restart at 1.
.*			0	(Default) Continue normally.
.*			1	Restart at one.
.*
.aH "MAIN TITLE OF TYPICAL ATTACHMENT" "SHORT TITLE" 1
.*
.* Table of contents generated here.
.TC
</FoO ThE bAr/>
dbadd mm 'lists' <<"</FoO ThE bAr/>"
lists
	AL	Automatic list.
	BL	Bullet list.
	DL	Dash list.
	ML	Marked list.
	RL	Reference list.
	VL	Variable list.
	LI	List item.
	LE	List end.
</FoO ThE bAr/>
dbadd mm 'fonts' <<"</FoO ThE bAr/>"
fonts
	I	Italic font.
	B	Bold font.
	R	Roman font.
	IR	Italic/Roman fonts.
	RI	Roman/Italic fonts.
	IB	Italic/Bold fonts.
	BI	Bold/Italic fonts.
	RB	Roman/Bold fonts.
	BR	Bold/Roman fonts.
</FoO ThE bAr/>
dbadd mm 'memo' <<"</FoO ThE bAr/>"
memo	Ordinary, basic memorandum.
	(Write this to a file and run mm on it to see how it works.)

.SA 1
.nr Pt 0
.tr ~
.TL 12003-1641 40288-700
*** title of memo
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.AU "G.V.E. Otto" GVEO IX 55633 1253 1G-307 55633-yymmdd.nnMF
.AS 2
*** abstract text
.AE
.NS
*** people to get memo  (delete this section if Abstract is deleted)
.NE
.NS "abstract only"
*** people to get abstract  (delete this section if Abstract is deleted)
.NE
.MT "MEMORANDUM FOR FILE"
.H 1 "INTRODUCTION"
*** what this memo is about
.H 1 "*** body section title"
*** body of memo
.H 1 "CONCLUSION"
*** what this memo was about
.SG ""
.NS 4
*** list of attachments
.NE
.NS
*** people to get memo  (delete this section if Abstract is used)
.NE
</FoO ThE bAr/>
dbadd mm 'nP' <<"</FoO ThE bAr/>"
nP	Numbered paragraph.

.nP
	Produce an alternate paragraph numbering style.  The paragraphs are
	numbered within *second*-level headings, and the first *two* lines
	of the paragraph are indented to better accentuate the numbers.
</FoO ThE bAr/>
dbadd mm 'VL' <<"</FoO ThE bAr/>"
VL	variable list

.VL indent [mark-indent] [1]
	indent		Number of chars of indentation for list text.
	mark-indent	Number of chars of indentation for mark.
	1		List is to be single spaced.
</FoO ThE bAr/>
dbadd mm 'TS' <<"</FoO ThE bAr/>"
TS	table start

.TS
	Begin a table definition to be processed by TBL.  The basic format of
	information in such a definition is as follows:
		options ;
		format .
		data

	The possible options are as follows:
		center		Center the table (default is left adjust).
		expand		Make table as wide as the current line length.
		box		Enclose the table in a box.
		allbox		Enclose each item in the table in a box.
		doublebox	Enclose the table in two boxes.
		tab(x)		Use x instead of tab to separate data items.
		linesize(N)	Set lines or rules in N point type.
		delim(xy)	Recognize x and y as "eqn" delimiters.

	The possible format data are as follows:
		L or l		A left-adjusted column entry.
		R or r		A right-adjusted column entry.
		C or c		A centered column entry.
		N or n		A numerical column entry, to be aligned with
				other numerical entries so that the units
				digits of numbers line up.
		A or a		An alphabetic subcolumn.  All corresponding
				entries are aligned on the left and positioned
				so that the widest is centered within the
				column.
		S or s		A spanned heading, i.e., the entry from the
				previous row continues down through this
				row.
		^		A vertically spanned heading, i.e., the entry
				from the previous row continues down through
				this row.
</FoO ThE bAr/>
dbadd mm 'TL' <<"</FoO ThE bAr/>"
TL	Memorandum title.

.TL [charging-case] [filing-case]
	The actual title of the memo is entered on the lines following the
	.TL macro, up to the next encountered macro.  A break request (.br)
	can be used to break the title up into separate lines, if needed.
</FoO ThE bAr/>
dbadd mm 'TE' <<"</FoO ThE bAr/>"
TE	table end

.TE
	This macro ends the table definition.
</FoO ThE bAr/>
dbadd mm 'TC' <<"</FoO ThE bAr/>"
TC	Table of contents.

.TC [slevel] [spacing] [tlevel] [tab] [head1] [head2] [head3] [head4] [head5]
	slevel	Lowest level of heading to be preceded by blank lines.
		(Default: 1)
	spacing	The number of blank lines to precede above headings.
		(Default: 1)
	tlevel	Lowest level of heading to have right-justified page numbers.
		(Default: 2)
	tab	0	(Default) Dots separate headings & page numbers.
		1	Spaces separate headings & page numbers.
	headN	Centered titles preceding the table of contents.
</FoO ThE bAr/>
dbadd mm 'TB' <<"</FoO ThE bAr/>"
TB	table title

.TB [title] [override] [flag]
	title		The title of the figure.
	override	String used to modify the figure number.
	flag	0	Use "override" as prefix to normal figure number.
	      none	Use "override" as prefix to normal figure number.
		1	Use "override" as suffix to normal figure number.
		2	Use "override" to replace normal figure number.
</FoO ThE bAr/>
dbadd mm 'T&' <<"</FoO ThE bAr/>"
T&	Redefine columns in a table.

.T&
	This macro is used within a table to redefine its columns.  The
	organization of information following this macro is as follows:
		format .
		data

	Format has the same meaning as explained in the .TS macro.
</FoO ThE bAr/>
dbadd mm 'SG' <<"</FoO ThE bAr/>"
SG	signature

.SG [arg] [1]
	arg	Initials of the typist.  Use "" if no such initials nor
		leading hyphen is to be displayed.
	1	Reference data (dept no., etc) is to be put on first author
		line.  Default is to put this on the last author line.
</FoO ThE bAr/>
dbadd mm 'SA' <<"</FoO ThE bAr/>"
SA	Justify the right margin.

.SA [arg]
	where arg is
		0	Sets the current and default justification flags
			to "right justification off."
		1	Sets the current and default justification flags
			to "right justification on."
	      none	Sets the current justification flag to the value
			found in the default flag.
</FoO ThE bAr/>
dbadd mm 'Rp' <<"</FoO ThE bAr/>"
Rp	Reference-page title string.

.ds Rp "New Title"
	This string contains the title to be used on the reference page.
	Default: "REFERENCES".
</FoO ThE bAr/>
dbadd mm 'Rf' <<"</FoO ThE bAr/>"
Rf	Reference numbering string.

\*(Rf
	This string is used in text wherever an automatically-generated
	reference number is to be printed.  It should be followed immediately
	by the reference text between .RS and .RF macros.
</FoO ThE bAr/>
dbadd mm 'RS' <<"</FoO ThE bAr/>"
RS	Reference start.

.RS [string-name]
	string-name	The name of a string that is to be assigned the
			current reference number.  This allows multiple
			uses of a given reference number in the text.
</FoO ThE bAr/>
dbadd mm 'RP' <<"</FoO ThE bAr/>"
RP	reference page

.RP [arg1] [arg2]
	arg1	0	Reset reference counter (default).
		1	Do not reset reference counter.
	arg2	0	Put on separate page (default).
		1	Do not cause a following .SK .
		2	Do not cause a preceding .SK .
		3	No .SK before or after.
</FoO ThE bAr/>
dbadd mm 'RL' <<"</FoO ThE bAr/>"
RL	reference list

.RL [indent] [1]
	indent	Number of chars of indentation for list text.
	1	List is to be single spaced.
</FoO ThE bAr/>
dbadd mm 'RI' <<"</FoO ThE bAr/>"
RI	Roman/Italic fonts.

.RI [arg1] [arg2] [arg3] [arg4] [arg5] [arg6]
	This macro alternates between the Roman and Italic fonts as it
	processes each argument, contatenating the arguments together
	without space between them.
	This is useful for producing words that are partially in one font
	and partially in another.
</FoO ThE bAr/>
dbadd mm 'RF' <<"</FoO ThE bAr/>"
RF	Reference end.

.RF
</FoO ThE bAr/>
dbadd mm 'RB' <<"</FoO ThE bAr/>"
RB	Roman/Bold fonts.

.RB [arg1] [arg2] [arg3] [arg4] [arg5] [arg6]
	This macro alternates between the Roman and bold fonts as it
	processes each argument, contatenating the arguments together
	without space between them.
	This is useful for producing words that are partially in one font
	and partially in another.
</FoO ThE bAr/>
dbadd mm 'Pt' <<"</FoO ThE bAr/>"
Pt	Paragraph-indent control register.

.nr Pt N
	where N is
		0	if paragraphs are *never* indented,
		1	if paragraphs are *always* indented, or
		2	(default) if paragraphs are indented *except* after
			headings, lists, and displays.
</FoO ThE bAr/>
dbadd mm 'Pi' <<"</FoO ThE bAr/>"
Pi	Paragraph-indent amount register.

.nr Pi N
	where N is the paragraph indent in characters (or ens).
</FoO ThE bAr/>
dbadd mm 'PH' <<"</FoO ThE bAr/>"
PH	Page header.

.PH [arg]
	where arg is of the form  "'left-part'center-part'right-part'"  and
	it defines the three fields of the page header: the left-justified,
	centered, and right-justified parts.  The single-quote delimiter
	can be replaced throughout the arg by any other character.
	Default: "''- \\\\nP - ''"
</FoO ThE bAr/>
dbadd mm 'PF' <<"</FoO ThE bAr/>"
PF	Page footer.

.PF [arg]
	where arg is a string to appear at the bottom of each page.
	Default: blank.
</FoO ThE bAr/>
dbadd mm 'Of' <<"</FoO ThE bAr/>"
Of	Figure-title style control register

.nr Of N
	where N is	0	Use "Figure N. Title" form.
			1	Use "Figure N - Title" form.
</FoO ThE bAr/>
dbadd mm 'OH' <<"</FoO ThE bAr/>"
OH	Odd-page header.

.OH [arg]
	where arg is a string to appear on the next line after the header
	on odd-numbered pages.
	Default: blank.
</FoO ThE bAr/>
dbadd mm 'OF' <<"</FoO ThE bAr/>"
OF	Odd-page footer.

.OF [arg]
	where arg is a string to be printed at the bottom of each
	odd-numbered page.
	Default: blank.
</FoO ThE bAr/>
dbadd mm 'Np' <<"</FoO ThE bAr/>"
Np	Numbered-paragraph control register.

.nr Np N
	where N is
		0	(default) Do not number the individual paragraphs.
		1	Number the paragraphs within first level headings.
</FoO ThE bAr/>
dbadd mm 'NS' <<"</FoO ThE bAr/>"
NS	notation

.NS [code]
	code	""	Copy to
		0	Copy to
			Copy to
		1	Copy (with att.) to
		2	Copy (without att.) to
		3	Att.
		4	Atts.
		5	Enc.
		6	Encs.
		7	Under Separate Cover
		8	Letter to
		9	Memorandum to
	     "string"	Copy (string) to
</FoO ThE bAr/>
dbadd mm 'ND' <<"</FoO ThE bAr/>"
ND	Define a new date.

.ND "New Date"
	This macro allows the user to define a new date, which redefines
	the contents of the DT string.  This date should be in the form
	"Month Day, Year".
</FoO ThE bAr/>
dbadd mm 'MT' <<"</FoO ThE bAr/>"
MT	memorandum type

.MT [code]
	code	""	no memorandum type is printed
		0	no memorandum type is printed
			MEMORANDUM FOR FILE
		1	MEMORANDUM FOR FILE
		2	PROGRAMMER'S NOTES
		3	ENGINEER'S NOTES
		4	Released-Paper style
		5	External-Letter style
	     "string"	string
</FoO ThE bAr/>
dbadd mm 'ML' <<"</FoO ThE bAr/>"
ML	mark list

.ML mark [indent] [1]
	mark	String to be used to mark list.
	indent	Number of chars of indentation for list text.
	1	List is to be single spaced.
</FoO ThE bAr/>
dbadd mm 'Lt' <<"</FoO ThE bAr/>"
Lt	Table-list title string.

.ds Lt "New Title"
	This string contains the title to be used on the table of contents
	Tables list.
	Default: "LIST OF TABLES".
</FoO ThE bAr/>
dbadd mm 'Lf' <<"</FoO ThE bAr/>"
Lf	Figure-list title string.

.ds Lf "New Title"
	This string contains the title to be used on the table of contents
	Figures list.
	Default: "LIST OF FIGURES".
</FoO ThE bAr/>
dbadd mm 'Le' <<"</FoO ThE bAr/>"
Le	Equation-list title string.

.ds Le "New Title"
	This string contains the title to be used on the table of contents
	Equations list.
	Default: "LIST OF EQUATIONS".
</FoO ThE bAr/>
dbadd mm 'LI' <<"</FoO ThE bAr/>"
LI	list item

.LI [mark] [1]
	mark	Mark to be used on list item.
	1	Given mark is to be used in addition to normal mark.
</FoO ThE bAr/>
dbadd mm 'LE' <<"</FoO ThE bAr/>"
LE	list end

.LE [1]
	1	The list is be followed by a blank line.
</FoO ThE bAr/>
dbadd mm 'IR' <<"</FoO ThE bAr/>"
IR	Italic/Roman fonts.

.IR [arg1] [arg2] [arg3] [arg4] [arg5] [arg6]
	This macro alternates between the Italic and Roman fonts as it
	processes each argument, contatenating the arguments together
	without space between them.
	This is useful for producing words that are partially in one font
	and partially in another.
</FoO ThE bAr/>
dbadd mm 'IB' <<"</FoO ThE bAr/>"
IB	Italic/Bold fonts.

.IB [arg1] [arg2] [arg3] [arg4] [arg5] [arg6]
	This macro alternates between the Italic and bold fonts as it
	processes each argument, contatenating the arguments together
	without space between them.
	This is useful for producing words that are partially in one font
	and partially in another.
</FoO ThE bAr/>
dbadd mm 'Hu' <<"</FoO ThE bAr/>"
Hu	Unnumbered-heading level register.

.nr Hu N
	where N is the heading level to be used by unnumbered headings (.HU).
</FoO ThE bAr/>
dbadd mm 'Ht' <<"</FoO ThE bAr/>"
Ht	Mark-concatenation heading control register.

.nr Ht N
	where N is	0	(default) if heading marks are to be
				concatenated in the heading,
			1	if only the current level mark is to be
				displayed in the heading.
</FoO ThE bAr/>
dbadd mm 'Hs' <<"</FoO ThE bAr/>"
Hs	Trailing-blank-line heading level register.

.nr Hs N
	where N is the lowest heading level after which there is a
	blank line.
	Default: 2
</FoO ThE bAr/>
dbadd mm 'Hc' <<"</FoO ThE bAr/>"
Hc	Centering heading level register.

.nr Hc N
	where N is lowest heading level that is centered.
	Default: 0
</FoO ThE bAr/>
dbadd mm 'Hb' <<"</FoO ThE bAr/>"
Hb	Stand-alone heading level register.

.nr Hb N
	where N is the lowest heading level that is stand alone, i.e., *not*
	run together with the following text.
	Default: 2
</FoO ThE bAr/>
dbadd mm 'HU' <<"</FoO ThE bAr/>"
HU	Unnumbered heading.

.HU heading-text
	This macro is similar to .H, except that no heading mark is printed
	with the heading text.  The level of such headings is controlled by
	the "Hu" number register.
</FoO ThE bAr/>
dbadd mm 'HM' <<"</FoO ThE bAr/>"
HM	Heading-mark style.

.HM [arg1] [arg2] ... [arg7]
	Each of the 7 arguments controls the printing style of the mark
	of the corresponding heading level.  The legal values of the
	arguments are as follows:
		1	Arabic (default for all levels).
	      0001	Arabic with enough leading zeros to get the specified
			number of digits.
		A	Upper-case alphabetic.
		a	Lower-case alphabetic.
		I	Upper-case Roman.
		i	Lower-case Roman.
</FoO ThE bAr/>
dbadd mm 'HF' <<"</FoO ThE bAr/>"
HF	Heading-font control string.

.ds HF 3 3 2 2 2 2 2
	This string controls the fonts used by each heading level.  The
	above is the default (levels 1 to 2 bold, 3 to 7 italic), where
			1 indicates roman (regular)
			2 indicates italic (underlined), and
			3 indicates bold (overstruck) font.
</FoO ThE bAr/>
dbadd mm 'FS' <<"</FoO ThE bAr/>"
FS	footnote

.FS [label]
	label	Label to be used to mark the footnote text.
</FoO ThE bAr/>
dbadd mm 'FG' <<"</FoO ThE bAr/>"
FG	Figure title.

.FG [title] [override] [flag]
	title		The title of the figure.
	override	String used to modify the figure number.
	flag	0	Use "override" as prefix to normal figure number.
			Use "override" as prefix to normal figure number.
		1	Use "override" as suffix to normal figure number.
		2	Use "override" to replace normal figure number.
</FoO ThE bAr/>
dbadd mm 'FE' <<"</FoO ThE bAr/>"
FE	end footnote

.FE
</FoO ThE bAr/>
dbadd mm 'FD' <<"</FoO ThE bAr/>"
FD	footnote format

.FD [arg] [1]
		   hyphenation adjust text-indent  label-justification
	arg	0	no	yes	yes		left   (troff default)
		1	yes	yes	yes		left
		2	no	no	yes		left
		3	yes	no	yes		left
		4	no	yes	no		left
		5	yes	yes	no		left
		6	no	no	no		left
		7	yes	no	no		left
		8	no	yes	yes		right
		9	yes	yes	yes		right
	       10	no	no	yes		right  (nroff default)
	       11	yes	no	yes		right
	    If arg null or omitted, the default value is used.

	1	   First-level headings reset automatic footnote numbering.
</FoO ThE bAr/>
dbadd mm 'FC' <<"</FoO ThE bAr/>"
FC	formal closing

.FC [closing]
	closing		Closing to be used at the end of a letter.
			Default is "Yours very truly,".
</FoO ThE bAr/>
dbadd mm 'Eq' <<"</FoO ThE bAr/>"
Eq	Equation-label style control register.

.nr Eq N
	where N is	0	Label is to appear at right margin.
			1	Label is to appear at left margin.
</FoO ThE bAr/>
dbadd mm 'Ej' <<"</FoO ThE bAr/>"
Ej	Start-of-page heading level register.

.nr Ej N
	where N is the lowest heading level that forces the start of a
	new page.
	Default: 0
</FoO ThE bAr/>
dbadd mm 'EQ' <<"</FoO ThE bAr/>"
EQ	equation display start

.EQ [label]
	label	The label of the equation to appear at the "vertical center"
		of the space used.
</FoO ThE bAr/>
dbadd mm 'EN' <<"</FoO ThE bAr/>"
EN	equation display end

.EN
</FoO ThE bAr/>
dbadd mm 'EH' <<"</FoO ThE bAr/>"
EH	Even-page header.

.EH [arg]
	where arg is a string to appear on the next line after the header
	on even-numbered pages.
	Default: blank.
</FoO ThE bAr/>
dbadd mm 'EF' <<"</FoO ThE bAr/>"
EF	Even-page footer.

.EF [arg]
	where arg is a string to be printed at the bottom of each
	even-numbered page.
	Default: blank.
</FoO ThE bAr/>
dbadd mm 'EC' <<"</FoO ThE bAr/>"
EC	equation caption.

.EC [title] [override] [flag]
	title		The title of the figure.
	override	String used to modify the figure number.
	flag	0	Use "override" as prefix to normal figure number.
			Use "override" as prefix to normal figure number.
		1	Use "override" as suffix to normal figure number.
		2	Use "override" to replace normal figure number.
</FoO ThE bAr/>
dbadd mm 'Df' <<"</FoO ThE bAr/>"
Df	floating-display output control register

.nr Df N
	where N is	0	(default) No special action occurs.
			1	A page eject will *always* follow the output
				of each floating display, so only one floating
				display will appear on a page and no text
				will follow it.
</FoO ThE bAr/>
dbadd mm 'De' <<"</FoO ThE bAr/>"
De	floating-display end-processing control register

.nr De N
	where N is
		0	Floating displays will not be output until end of
			section or end of document.
		1	Output the new floating display on the current page,
			if there is room, otherwise hold it until the end
			of the document.
		2	Output exactly one floating display from the queue
			at the top of a new page or column (when in two-
			column mode).
		3	Output one floating display on current page if there
			is room.  Output exactly one floating display at
			the top of a new page or column.
		4	Output as many displays as will fit, starting at the
			top of a new page or column.  Note that if register
			'De' is set to 1, each display will be followed by
			a page eject, causing a new top-of-page to be reached
			where at least one more display will be output.
			(This also applies to value 5 below.)
		5	(Default) Output  new floating display on the current
			page if there is room.  Output at least one, but as
			many displays as will fit starting at the top of a
			new page or column.
</FoO ThE bAr/>
dbadd mm 'DT' <<"</FoO ThE bAr/>"
DT	date string

\*(DT
	Date in the form "Month Day, Year."
</FoO ThE bAr/>
dbadd mm 'DS' <<"</FoO ThE bAr/>"
DS	static display

.DS [format] [fill] [rindent]
	format	""		no indent
		0 or L		no indent
		1 or I		indent by standard amount
		2 or C		center
		3 or CB		center as a block
	fill	""		no-fill mode
		0 or N		no-fill mode
		1 or F		fill mode
	rindent		Amount of indentation from right margin.
</FoO ThE bAr/>
dbadd mm 'DL' <<"</FoO ThE bAr/>"
DL	dash list

.DL [indent] [1]
	indent	Number of chars of indentation for list text.
	1	List is to be single spaced.
</FoO ThE bAr/>
dbadd mm 'DF' <<"</FoO ThE bAr/>"
DF	floating display

.DF [format] [fill] [rindent]
	format	""		no indent
		0 or L		no indent
		1 or I		indent by standard amount
		2 or C		center
		3 or CB		center as a block
	fill	""		no-fill mode
		0 or N		no-fill mode
		1 or F		fill mode
	rindent		Amount of indentation from right margin.
</FoO ThE bAr/>
dbadd mm 'DE' <<"</FoO ThE bAr/>"
DE	end a display

.DE
</FoO ThE bAr/>
dbadd mm 'Cl' <<"</FoO ThE bAr/>"
Cl	TOC heading level register.

.nr Cl N
	where N is the lowest heading level to be saved for the table
	of contents.
	Default: 2
</FoO ThE bAr/>
dbadd mm 'CS' <<"</FoO ThE bAr/>"
CS	Cover sheet.

.CS [pages] [other] [total] [figs] [tbls] [refs]
	This macro generates a cover sheet in either the released paper or
	Technical Memorandum style.  The automatically-generated numbers
	for page count, figure count, table count, etc., can be overridden
	by supplying arguments to this macro.  Such arguments are ignored
	with the released-paper style.
</FoO ThE bAr/>
dbadd mm 'BR' <<"</FoO ThE bAr/>"
BR	Bold/Roman fonts.

.BR [arg1] [arg2] [arg3] [arg4] [arg5] [arg6]
	This macro alternates between the bold and Roman fonts as it
	processes each argument, contatenating the arguments together
	without space between them.
	This is useful for producing words that are partially in one font
	and partially in another.
</FoO ThE bAr/>
dbadd mm 'BL' <<"</FoO ThE bAr/>"
BL	bullet list

.BL [indent] [1]
	indent	Number of chars of indentation for list text.
	1	List is to be single spaced.
</FoO ThE bAr/>
dbadd mm 'BI' <<"</FoO ThE bAr/>"
BI	Bold/Italic fonts.

.BI [arg1] [arg2] [arg3] [arg4] [arg5] [arg6]
	This macro alternates between the bold and Italic fonts as it
	processes each argument, contatenating the arguments together
	without space between them.
	This is useful for producing words that are partially in one font
	and partially in another.
</FoO ThE bAr/>
dbadd mm 'AU' <<"</FoO ThE bAr/>"
AU	author information

.AU name [initials] [loc] [dept] [ext] [room] [arg] [arg] [arg]
</FoO ThE bAr/>
dbadd mm 'AT' <<"</FoO ThE bAr/>"
AT	author title

.AT [title1] [title2] ... [title9]
	titleN	The title lines to appear in the signature block, each
		on a separate line.
</FoO ThE bAr/>
dbadd mm 'AS' <<"</FoO ThE bAr/>"
AS	abstract start

.AS [arg] [indent]
	arg	0	Abstract will appear on page 1 *and* on cover sheet
			(if any) of external papers and Technical Memoranda.
			With Memoranda for File and all other documents
			(other than external letters) the abstract will appear
			*only* on page 1, with no cover sheet being made.
		1	Abstract will appear *only* on cover sheet (if any)
			of external papers and Technical Memoranda.
		2	With documents other than external letters, external
			papers, and Memoranda for File, the abstract will
			appear *only* on the cover sheet, which will be
			produced automatically without the need for a .CS
			macro.

	indent	Amount of indentation from both left and right margins
		for abstract.
</FoO ThE bAr/>
dbadd mm 'AL' <<"</FoO ThE bAr/>"
AL	automatic list

.AL [type] [indent] [1]
	type	1, A, a, I, or i; if omitted, defaults to 1.
	indent	Number of chars of indentation for list text.
	1	List is to be single spaced.
</FoO ThE bAr/>
dbadd mm 'AE' <<"</FoO ThE bAr/>"
AE	abstract end

.AE
</FoO ThE bAr/>
dbadd mm '2C' <<"</FoO ThE bAr/>"
2C	Two-column output.

.2C
	Begin two-column processing.
</FoO ThE bAr/>
dbadd mm '1C' <<"</FoO ThE bAr/>"
1C	One-column output.

.1C
	Resume one-colume processing.
</FoO ThE bAr/>
dbadd mm 'R' <<"</FoO ThE bAr/>"
R	Roman font.

.R
	This macro changes the font to Roman.
</FoO ThE bAr/>
dbadd mm 'P' <<"</FoO ThE bAr/>"
P	Paragraph.

.P [type]
	where type is
		0	Force the paragraph to be left justified.
		1	Force the paragraph to be indented.
</FoO ThE bAr/>
dbadd mm 'I' <<"</FoO ThE bAr/>"
I	Italic font.

.I [italic-arg] [previous-font-arg] [italic-arg] ...
	When called without arguments, this macro changes the font to Italic
	until another font-macro is encountered that changes it to something
	else.
	When called with arguments (up to 6), the font alternates between
	the Italic and the previous font as it processes each argument,
	contatenating the arguments together without space between them.
	This is useful for producing words that are only partly Italicized.
</FoO ThE bAr/>
dbadd mm 'H' <<"</FoO ThE bAr/>"
H	Numbered heading.

.H level [heading-text] [heading-suffix]
	level		A number from 1 (highest) to 7 (lowest) indicating
			the level of the given heading.
	heading-text	The text to be used in the heading.
	heading-suffix	The heading suffix which is to be appended to the
			heading text but which should not appear in the
			Table of Contents, such as footnote marks.
</FoO ThE bAr/>
dbadd mm 'F' <<"</FoO ThE bAr/>"
F	Footnote numbering string

\*F
	This string is used in text wherever an automatically generated
	footnote number is to be printed, followed immediately by the
	footnote text between .FS and .FE macros.
</FoO ThE bAr/>
dbadd mm 'C' <<"</FoO ThE bAr/>"
C	Copy type

-nCn  (must be set on the command line)
	where "n" is
		0	(Default) Original.
		1	OFFICIAL FILE COPY.
		2	DATE FILE COPY.
		3	DRAFT, single spaced, default paragraph style.
		4	DRAFT, double spaced, 10-space paragraph indent.
	Default: 2
</FoO ThE bAr/>
dbadd mm 'B' <<"</FoO ThE bAr/>"
B	Bold font.

.B [bold-arg] [previous-font-arg] [bold-arg] ...
	When called without arguments, this macro changes the font to bold
	until another font-macro is encountered that changes it to something
	else.
	When called with arguments (up to 6), the font alternates between
	the bold and the previous font as it processes each argument,
	contatenating the arguments together without space between them.
	This is useful for producing words that are only partly emboldend.
</FoO ThE bAr/>
