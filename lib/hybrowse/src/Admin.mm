.\" Set this string for 5ESS (value = 5e) or exptools (any other value)
.ds 5e
.\" Macro filename depends on whether it is 5ESS
.ie '\*(5e'5e' .ds hm /usr/5ess/src/toolcom_1.0/data/macros/hy_mm
.el .ds hm $TOOLS/lib/hybrowse/src/mm.macros
.\"=======================================================================
.\"           Print header info only if formatting for paper copy
.if !'\*(hB'hybrowse'\{'br
.ds HF 3 3 3 3 3 3
.ds HP +2 +2 +2 +2 +2 +2
.de HX\" Show references after every section
.RP 0 3
.sp 3
..
.de hR\" Simulate browser-only references
\\*(Rf
.RS
\\&\\$1^\\$2
.RF
..
.TL
Hybrowse Administrators Guide
.AU "L. H. Stanfield" LHS IHP 55412 37433 2F-539
.MT "Online Hybrowse Document"
'br\}
.nr Hs 5
.nr Cl 5
.H 1 "Introduction"
This document tells how to create and maintain documents for hybrowse.
It won't be of interest to you if you're just using hybrowse to read
documents formatted by someone else.
.P
If your application requires only basic browsing,
you don't need to read the more detailed sections of this guide.
Here's an overview to get you started:
.AL
.LI
Documents should be formatted so hybrowse can find their section headings.
Reference \*(Rf
.RS
^A Simple Example
.RF
shows formatting commands that work for most documents.
.LI
You can format the references in your documents so the browser
can find the referenced documents.
See Reference \*(Rf
.RS
^Browser-only References
.RF
and \*(Rf
.RS
^Browser and Paper References
.RF
.LI
You'll probably want a Catalog to help readers find the documents they want.
The Catalog is just a document with references to other documents.
.if !'\*(5e'5e'\{'br
You can use the file $TOOLS/lib/hybrowse/src/Catalog.mm
as a template.
'br\}
.LI
The hybrowse command needs parameters to locate your documents, so
you should write a shell script to provide the parameters.
Reference \*(Rf
.RS
^Access Scripts
.RF
shows some sample scripts.
The hybrowse manual page and reference \*(Rf
.RS
^Hybrowse Command
.RF
give more details on the command line parameters.
.LI
If you have problems making nroff ignore "pic" graphics
or if you want to include "pic" graphics in your documents see reference \*(Rf
.RS
^Pic
.RF
.LI
If you need more features than hybrowse provides, you can extend your
application by providing shell scripts \*(Rf
.RS
^Escape Scripts
.RF
or macros \*(Rf
.RS
^Macro File
.RF
.LE
.H 1 "Applications"
Online documents are appropriate for some applications because:
.AL "" "" 1
.LI
they can be updated more easily than paper documents
.LI
they're easily accessible
.LI
references reduce the need to duplicate information
.LI
users see only the information they are interested in, so the quantity of
documentation is less intimidating than a stack of paper might be.
.LE
.P
Some specific applications are:
.AL "" "" 1
.LI
Reference manuals
.LI
Help systems
.LI
Textual databases
.LI
Tutorials
.LI
Development documents
.LI
Process/methodology documents
.LE
.H 1 "Hybrowse Command"
The browser command is called "hybrowse" (short for "hypertext browser").
.P
Its usage is:
.sp
.in +5
.ti -3
hybrowse
[-kgqrb]
[-a\ macrofile]
[-c\ catalog_doc]
[-d\ document]
.br
[-m\ menus]
[-n\ line]
[-p\ path]
[-s\ section]
.br
[-t\ title_file]
[-u\ pattern]
[-v\ vmenu]
[document]
.in -5
.P
The following subsections explain the parameters:
.de xx
.ie \\n(:R-8 .LI "\\*(Rf"
.el .LI "\ \\*(Rf"
.RS
^\\$2
.RF
\\$1
..
.VL 5 "" "" 1
.xx "-a macrofile" "Macro File"
.xx "-b" "No Beep"
.xx "-c catalog_doc" "Catalog Name"
.xx "-d document" "Initial Document"
.xx "-m menus" "Menu Definitions"
.xx "-n line" "Initial Line"
.xx "-p path" "Directory Path"
.xx "-q" "Defensive Exit"
.xx "-r" "Restricted Command Set"
.xx "-s section" "Initial Section"
.xx "-t title_file" "Title File"
.xx "-u pattern" "Unbuffered Documents"
.xx "-v vmenus" "Mouse Menu Definitions"
.xx "document" "Initial Document"
.LE
.H 2 "Macro File"
The "-a macrofile" parameter can be used to load application-specific
browser macros.
The document path (-p) isn't used to find the macro file, so use a full path.
.P
Macros are just a way to avoid typing long commands such as
shell escapes or jumps to named sections.
Macro definitions are more complex than the other browser commands,
so skip this section unless you really need them.
.P
Definitions in the macrofile consist of:
.DL "" 1
.LI
the character "%" in column 1
.LI
the character "a"  (it stands for "application")
.LI
the macro name
(exactly one character, after applying escapes described below)
.LI
the character "="
.LI
the text of the macro
.LI
a newline, which terminates (but is not included in) the definition
.LE
.P
The macro name and text can contain:
.AL
.LI
regular characters
.LI
^X, where X is a character to be converted to its control-key equivalent
.LI
backslash escapes:
.DS 
\\\\n - newline
\\\\t - tab
\\\\r - return
\\\\b - backspace
.DE
.LE
.P
The sequence \\<newline> is ignored, so definitions can extend over multiple
lines.
Other characters after a backslash (in particular, ^ and \\)
are taken literally.
.P
The text of a macro can consist of any browser commands, including calls
to other macros.
.P
The browser's display is not refreshed during macro execution, but the
output of shell escapes will be printed and the user (not the macro)
will be prompted to "Press any key to continue".
All other input to the browser, including responses to prompts, is taken
from the macro.
Don't forget the "\\n" to terminate prompts.
.P
Macros are invoked by typing the letter "a" followed by the macro name.
.P
The macros "ah" and "a?" are reserved to display the macro file, so
the file should include "help" information in addition to the macro definitions.
The help commands can't be redefined as macros.
.P
The commands ESCAPE and ^G are used to cancel input modes, so "aESC" and
"a^G" are reserved to cancel the "a" command without running a macro.
They can't be redefined as macros.
.P
Any error opening the macro file is silently ignored.
Any error in the syntax of a macro definition causes that definition to
be silently ignored.
Errors during macro execution cause the remainder of the macro to be
skipped.
.if !'\*(5e'5e'\{'br
.P
The file $TOOLS/lib/hybrowse/src/appcmds is a sample macro file.
'br\}
.H 2 "No Beep"
The "-b" flag prevents hybrowse from beeping on errors.
Some errors don't generate any error message other than a beep, so
this can be confusing if your computer has poor response time.
.H 2 "Catalog Name"
The "-c catalog_doc" paramater can be used to make the "c" command go to
a document called something other than "Catalog".
This is only necessary if you need to have multiple Catalogs in a single
directory.
.H 2 "Initial Document"
The "-d file" parameter specifies the initial document to be displayed.
.P
The "-d" can be left off if the document name is the last parameter on the
command line.
Therefore, "hybrowse file" is equivalent to "hybrowse -d file".
.P
If this parameter isn't specified, the name "Tutorial" will be used.
This is a safe choice since some users may not be familiar with the
browsing commands.
.H 2 "Distributed Table of Contents"
Hybrowse normally creates a single, global Table of Contents for each document.
For larger documents, the Table of Contents can be so long that you cannot
easily see the document's structure.
In that case, you can use the "-g" parameter to create a distributed
Table of Contents.
.P
The -g flag causes these changes:
.DL
.LI
The Table of Contents shows only highest-level headings.
.LI
Sections that contain subsections are replaced by a list of subsections.
.LI
If a section has both text and subsections
its text is moved to a lower-level section named "<text before first header>".
.LE
.P
.H 2 "Menu Definitions"
The "-m menus" parameter defines the menu line that is
displayed when the tab key is pressed.
You can add items to the standard menus or completely replace the standard
menus.
Items can be nested in submenus and can execute arbitrary hybrowse commands.
.P
See the manual page for details on how to use the flag.
.H 2 "Initial Line"
The "-n line" parameter specifies the initial line to be displayed.
.P
Hybrowse considers the first line of text on the screen to be the
"current line".
.P
The default is to start at line 1.
.H 2 "Directory Path"
The "-p path" parameter lists the directories that hybrowse should
search for documents.
.P
The path consists of directories separated by colons.
Null entries in the path (i.e., consecutive/leading/trailing colons)
are treated as the directory ".".
.P
If the "-p" parameter is not given on the command line, hybrowse uses the value
in the environment variable "HYPATH".
If HYPATH is null, the path is taken to be just ".".
.P
A directory of standard documents is automatically added to the end
of the path.
The builtin browser documents (Help, Tutorial, and Admin) are normally found
in a standard directory, but they can be overridden by providing files of
the appropriate names in the application directories.
.H 2 "Defensive Exit"
The "-q" flag prevents the "q" command from exiting from the browser.
The user thus has to enter "Q" (capitalized) or a multi-character
editor-specific command to exit.
.P
This flag should be used only for applications where an accidental exit
would be exceptionally inconvenient.
.H 2 "Restricted Command Set"
The "-r" flag is for applications that run on public logins.
It ties off the commands for escaping to the shell and writing to files.
.H 2 "Initial Section"
The "-s section" parameter specifies the name of the initial section to
be displayed.
.P
If this parameter isn't specified, the first section (after the 
Table of Contents) will be displayed.
.H 2 "Title File"
Hybrowse normally prints the current document's file name on the first
status line.
The "-t title_file" parameter can be used to add descriptive text to the
document status line.
If the file contains a title for a document, the status line will print as:
.ti +5
<document_filename> -- <title>
.P
Each line of the title_file should contain:
.AL "" "" 1
.LI
a document name in column 1
.LI
one or more blanks and/or tabs
.LI
descriptive text to be displayed in the document heading
.LE
.P
Blank lines and lines beginning with "#" are ignored; they can be used
as comments.
.P
Any errors that occur while opening, reading, or parsing the file are
silently ignored.
.P
Since the file isn't a document, it isn't found down the "-p" path.
Specify a full pathname.
.H 2 "Unbuffered Documents"
The "-u" flag is for applications that have documents that can change
during a browsing session.
.P
Normally, hybrowse buffers several of the most-recently-displayed documents
in memory so you can efficiently return to them.
The flag "-u\ pattern" disables buffering of all documents whose
names match the pattern (the pattern is a regular expression of the form
accepted by regcmp(3)).
Those documents will thus be re-read every time you jump to them, so you
you will always see the latest version.
.P
On BSD systems (e.g., SUN workstations), hybrowse does not support regular
expressions, so the pattern value be a string that exactly matches the name
of the unbuffered document.
.H 2 "Mouse Menu Definitions"
The "-v vmenu" parameter adds items to the menu line that is
displayed when mouse button 2 is pressed in viterm, emacsterm,
or etermx.
Menu items can execute arbitrary hybrowse commands.
.P
See the manual page for details on how to use the flag.
.H 1 "Access Scripts"
A set of documents and shell scripts for use with hybrowse
will be referred to as an "application".
Hybrowse provides the user interface;
application files provide the functionality.
.P
Several parameters are needed to make hybrowse do anything useful,
so each application should provide a shell script to 
call hybrowse with appropriate parameters.
Users may have several scripts in their PATH for invoking hybrowse on
different sets of documents, so the scripts should have names that describe
the documents (i.e., they shouldn't all be called "browse").
.P
The simplest access script just lists directories where hybrowse
can find documents:
.DS I
hybrowse -p `logdir me`/my_docs:`logdir proj`/proj_docs
.DE
________________________
.P
If all users of your script know how to use the browser, the script
can start them off in the Catalog:
.DS I
hybrowse -p`logdir xyz`/doc_dir -d Catalog
.DE
________________________
.P
A script can provide access to application-specific commands (see
references \*(Rf
.RS
^Macro File
.RF
and \*(Rf):
.RS
^Escape Scripts
.RF
.DS I
PROJDIR=`logdir xyz`/browse
PATH=$PROJDIR/bin:$PATH
hybrowse -p $PROJDIR/docs -a proj_macros
.DE
________________________
.P
When used as a help system, a starting file and section might be given:
.DS I
hybrowse -p`logdir xyz`/help_dir -d help_doc -s 'Table of Contents'
.DE
________________________
.P
The help command can be made context-sensitive by providing a starting section
relevant to what the user is currently doing.
For example, the invoking command might set "SECT" to the name of the
currently-relevant section and then execute:
.DS I
hybrowse -p`logdir xyz`/help_dir -d help_doc -s "$SECT"
.DE
.H 1 "Standard Files"
The directory
.ie '\*(5e'5e' /usr/5ess/src/toolcom_1.0/data/hydocs
.el $TOOLS/lib/hybrowse/docs
contains:
.VL 15
.LI Tutorial
tutorial on how to use hybrowse commands
.LI Help
documentation on all hybrowse commands
.LI Admin
instructions on how to create and maintain hybrowse documents (this document)
.LI Catalog
references to sample documents - every application should provide its
own Catalog to override this one
.LE
.if !'\*(5e'5e'\{'br
.P
$TOOLS/lib/hybrowse/src contains additional support files:
.VL 15
.LI Catalog.mm
a skeletal source file for the Catalog.
The source can be copied and modified for your application or you can
format your Catalog in any other way that you prefer.
.LI mm.macros
redefinitions of mm macros to produce hybrowse-compatible output.
(See the following sections for usage.)
.LI menus
default definitions for the TAB menu.
If you want to define your own menu items, this file
is a good example of how to do it.
.LI appcmds
sample macro definitions for use with the -a parameter.
.LE
'br\}
.P
The file names "Help" and "Catalog" are hard-coded into hybrowse for
the "?" and "c" commands.
"Tutorial" is hardcoded as the default initialization file.
However, the paths to them are not hardcoded, so you can override them
by creating documents of the same names earlier in the path of the
hybrowse -p flag.
.P
All applications should redefine Catalog to reference application-specific
documents.
The other standard documents can be redefined in the same way,
but most applications should just use the default versions.
Beware that redefining these files will prevent you from seeing any
updates made to the default documents.
(Using the defaults doesn't require any action on your part since hybrowse
automatically adds them to the document path.)
.P
The file \*(hm redefines some
mm macros to work with hybrowse.
See the following sections for usage.
.H 1 "Formatting Documents"
.H 2 "A Simple Example"
Documents for hybrowse are formatted with nroff and a modified
set of "mm" macros.
The file of macro modifications, \*(hm,
must be passed to nroff before your source file.
.P
.if '\*(5e'5e'\{'br
If a document can be formatted with printvol, you can format it and run
hybrowse by typing:
.ti +5
printvol -T hybrowse <other_printvol_args>
.P
If you don't want to run hybrowse immediately, you can save the
output in a file by adding the -o flag:
.ti +5
printvol -T hybrowse -o hy  <other_printvol_args>
.P
If you do not use printvol, you will have to generate the formatting
commands manually:
'br\}
.AL
.LI
Start with the mm source file for an existing document.
For simplicity, use a document without eqn or pic commands.
.LI
Format the document:
.DS I
tbl -TX \*(hm your_mm_file |
      nroff -mm -Tlp |
      col -x >temp
.DE
.LI
Enter hybrowse by typing "hybrowse temp"
.LE
.P
Read the following sections for details.
.H 2 "Changes to Standard Macros"
This section gives an overview of the mm macros that are modified by \*(hm.
The macro file is commented,
so see it if you need a complete list of the changes.
.DL
.LI
The H and HU macros generate header lines in the format expected by hybrowse.
.LI
The AS macro produces a section heading equivalent to ".H\ 1\ Abstract".
.LI
Lines between PS and PE (pic data) and between NS and NE (distribution lists)
are ignored.
.LI
The TC (Table of Contents) macro is ignored.
.LI
Page headers and footers are ignored
(there aren't any fixed page boundaries in online documents).
.LI
Footnotes are surrounded by parentheses and placed inline.
.LI
A separate reference page is generated for each section.
This has the side-effect of resetting the reference numbers to "1"
at the start of each section.
.LE
.P
If you have private macros for formatting attachments, they should work
with the redefinitions as long as they generate ".H" or ".HU" commands.
.H 2 "Browser-specific Macros"
The macro file defines several macros just for browseable files.
The macros are never required, but they make it a little easier
to add hybrowse functionality to documents.
.P
You can leave calls to these macros in the source even when formatting
paper copies; troff and nroff will ignore them when the hybrowse macro
definition file is not used.
.P
The following subsections describe each macro.
.H 3 "Browser-only References"
The .hR macro generates a reference formatted for hybrowse.
If paper copies are made (without the hybrowse macro definitions),
no reference will be generated.
.P
Its parameters are:
.AL
.LI
The document file name.  The default is the current document.
.LI
The section name, exactly as it appears in a .H macro.
The default is the first section in the referenced document.
.LE
.P
The hR macro provides the \\*(Rf, .RS, and .RF lines.
.P
Example:
.DS I
The xx command
\&.hR cmd_doc "The XX Command"
can be used for this.
.DE
.P
Note the wording of the text around the reference - it makes sense regardless
of whether the reference is expanded.
.H 3 "Browser and Paper References"
The .hT macro generates one type of reference for the browser and a different
type (such as document ordering information) for paper copies.
.DL "" 1
.LI
You must provide the \\*(Rf, .RS, and .RF lines.
.LI
This macro must be called immediately after the .RS line.
.LI
It has the same parameters as the .hR macro.
.LE
.P
Example:
.DS I
See reference \\\\*(Rf
\&.RS
\&.hT cmd_doc "The XX Command"
T.H.E. Author, "The Commands", 12345.01IM, January 1, 1980.
\&.RF
for additional details.
.DE
.P
When formatted for the hybrowse, only the browser-style reference will
be generated.
When formatted without the macros, only the normal reference will be generated.
.H 2 "Pic"
.if '\*(5e'5e'\{'br
If you use printvol to format documents, you can skip this section;
the pic interactions are handled automatically.
.P
'br\}
Most nroff preprocessors (e.g., diffmk and tbl) produce output compatible
with hybrowse.
The exception is pic, which generates output only for troff (not for nroff).
An additional complication is that there are three ways to delimit pic commands:
.VL 12
.LI ".PS/.PE"
handled properly (replaced with a "picture ignored" line) by the macros
unless nested inside DS/DE
.LI ".PS <file"
can be handled by running the file through pic before using nroff with the
macros
.LI ".PS/.PF"
requires changes to the macros (.PF is rarely used)
.LE
.P
One way to get good results (except when .PF is used)
is to run the file through the pic command before sending it to nroff.
This is wasteful since the pic output is then discarded, but it's simple
and it works.
.P
If your documents contain PS/PE inside DS/DE, you will have to write an awk
script to replace the PS/PE data with a line saying "Picture not available".
(The macros can't handle this case due to restrictions on using .ig inside
a diversion.)
Do this processing before running the document through nroff.
.P
The hy.format script \*(Rf
.RS
^hy.format
.RF
is a general way to format documents; it formats the text normally and
generates calls to the "proof" tool to display pictures on 5620 and
630 terminals.
It also handles the case of PS/PE inside DS/DE.
You can modify it to skip the "proof" calls if you don't need online pictures.
.H 1 "Document File Format"
.H 2 "Overview"
The macro definition file normally handles the details of formatting documents;
the format of processed documents is described here in case you want
to use a text formatter other than "nroff\ -mm".
.P
.AL
.LI
Lines should be no more than 70 characters long since that's the minimum
window width that hybrowse supports.
Lines longer than the terminal's window will require that reader use
horizontal scrolling.
.hR "Help" "Horizontal Scrolling"
.LI
To conserve screen space,
hybrowse compresses sequences of blank lines to just three blank lines.
.LI
Hybrowse divides the document into sections based on section headers.
Section headers consist of:
.DL "" 1
.LI
an ^ in column one
.LI
the section nesting level (first argument to .H)
.LI
another ^
.LI
the section name (not quoted).
.LE
.LI
Lines that come before the first section header are put into a section called
"<text before first header>".
Unformatted files can therefore be read into hybrowse;
they are treated as having a single section called "<text before first header>".
.P
"<text before first header>" won't be created if the first line of the document is a section header.
.LI
The Table of Contents is created from the section headers when hybrowse
reads the document.
There should not be output from ".TC" in the document.
.LI
The word REFERENCES on a line by itself (even if underlined and
preceded by blanks) is interpreted as the beginning of a reference page;
everything up to the next section header or end of
document is treated as references to other documents.
(This convention is compatible with the .RP macro.)
.P
Hybrowse never prints the reference page; it is only used internally.
.LE
.P
The following sections tell how hybrowse processes the reference page.
.H 2 "Reference Page"
When a number is typed as a hybrowse command,
hybrowse looks up the number on the reference page.
Each section of a document has its own reference page, so the meaning of
a reference number varies depending on which section is currently displayed.
.P
Hybrowse does not require "[n]" in the displayed text;
that's just a convention used by the mm macros.
(Hybrowse uses the bracketed number only for interpreting mouse clicks.)
.P
Each reference in the reference page consists of:
.DL "" 1
.LI
blanks
.LI
a number
.LI
a period
.LI
blanks
.LI
the body of the reference.
.LE
.SP
(This is compatible with output from the .RS/.RF macros.)
.P
Hybrowse recognizes the following reference body formats:
.SP
.VL 6 "" "" 1
.LI \*(Rf
.RS
^Section References
.RF
file_name^section_name
.LI \*(Rf
.RS
^Line References
.RF
file_name^line_number^section_name
.LI \*(Rf
.RS
^Active References
.RF
%text
.LI \*(Rf
.RS
^Paper References
.RF
text
.LE
.H 3 "Section References"
A reference of the form
.sp
.ti +5
file^section
.sp
indicates a jump to line 1 of a specific section.
.P
.DL "" 1
.LI
"file" is the name of a document
.LI
"section" is the section name from a .H macro in "file"
.LE
.P
If the document has multiple sections with the same name, hybrowse will
assume that the link refers to the first one.
.P
The file name defaults to "current document" and the section defaults
to "the first section".
.H 3 "Line References"
A reference of the form
.sp
.ti +5
file^number^section
.sp
indicates a jump to a specific line.
.P
"number" must consist only of (one or more) digits.
.P
The file name defaults to "current document" and the section defaults
to "the first section".
.H 3 "Active References"
A reference of the form
.sp
.ti +5
%text
.sp
is executed (interpreted by hybrowse) as if it had been typed at the keyboard.
The result is similar to a macro except that it can only be executed when the
section containing the reference is displayed.
.P
This sort of reference could be used, for example, to run a graphics editor
when a reference to a picture is selected.
.hR "" "hy.format"
.P
Control characters in the reference are expanded in the same way as 
macros in the "-a" file \*(Rf.
.RS
^Macro File
.RF
You'll need at least four backslashes to get a single backslash
inserted into the reference page; it may take even more,
depending on which nroff macros you use to format the reference.
.H 3 "Paper References"
A reference of the form
.sp
.ti +5
text
.sp
is treated as a paper-style reference.
.P
If a user selects this reference, hybrowse displays the text.
This allows hybrowse to be used on references that aren't specially formatted.
.H 1 "Indirect-Indexed Sections"
Most browsable documents are formatted before you enter hybrowse,
so you can arrange their references to go to any document you want.
However, index documents created by the hybrowse "i" command
.hR Help "Index Document"
are less flexible; you have to accept the index format and references
that hybrowse supplies.
One case where you might want to modify the index file references is
when your document is an externally-generated index.
For example, assume that:
.AL
.LI
Each line of your document contains the NAME section of a manual page and
a reference to the actual manual page.
I.e, it is an index to the manual pages.
.LI
A user runs the "i" command on your document to narrow the
list of manual pages to just those that refer to some particular topic.
.LI
The user then selects a reference from the "i" document.
.LE
.P
The user probably wants to go to the selected manual page instead
of to the index document you provided.
In other words, they expect references from the "i" document to
jump \fIindirectly\fP through your index to the manual page.
.P
To make the indexing work as users expect, you can mark sections
of your documents as indices by making their first non-blank line be:
.in +5
#hybrowse\ index
.in -5
.P
The "#" must be in column 1 and there must be exactly one blank in front
of the word "index".
An easy way to get it in column 1 is to precede it by \e!.
The #hybrowse line is special in the following ways:
.DL
.LI
It will not print on the user's terminal
.LI
It tells hybrowse that any jumps to this section from
an "i" document should be indirect.
.LE
.P
Hybrowse implements indirection by looking for the first number in brackets
on the line and then executing the corresponding reference.
Note that this limits index sections to single-line entries.
.P
If indirection fails for any reason, hybrowse ignores the indirection
indicator and just jumps to the line in your document.

.if !'\*(5e'5e'\{'br
.H 1 "Preprocessing Scripts"
There are so many ways to prepare information for browsing
that a standard formatting script isn't provided with hybrowse.
The following subsections provide sample scripts that you can modify
to meet your own specific needs.
.P
You can use the "w" command if you want to write out a copy of any of the
scripts.
You may have to do a little editing to get the scripts into shape before
executing them; nroff adds leading blanks to the lines and changes tabs into
a series of blanks.
.H 2 "hy.format"
.nf
.nj
.in 0
#
# Format documents for hybrowse
#
# This script generates active references so people with 5620 or 630 terminals
# can display any pictures in the documents.
#
# Input is a list of mm source file names.  The files may contain SDL and pic.
# Output is a hybrowse document and zero or more proof files
#  with suffix ".p<n>", where <n> is a number.
#
# This script assumes that PATH includes exptools
#
# You'll need the script "hy.proof" in your PATH to display graphics.
#

if [ ! -r \*(hm ]
then
	echo "$0: ERROR: can't open \*(hm >&2
	exit 1
fi

for SRC
do
	if [ ! -r $SRC ]
	then
		echo "$SRC not readable" 2>&1
		continue
	fi
	FILE=`basename $SRC .mm`
	if [ "$FILE" = "`basename $SRC`" ]
	then
		# Input didn't have .mm, so add .hy for uniqueness
		OUTFILE=$FILE.hy
	else
		# Input had .mm, so output file will be just base name
		OUTFILE=$FILE
	fi

	# If generated file name has more than 14 chars
	# The "x" is to ensure file name isn't an expr operator (like "/")
	# There are 15 dots, which represent any char.
	if expr "x$OUTFILE" : 'x...............' > /dev/null
	then
		echo "$0: ERROR: File name $SRC is too long (limit is 11 chars plus optional .mm)" >&2
		continue
	fi

	# Split file into main document and separate picture files
	# Replace each pic section with a reference to a proof window

	/usr/lib/xpand \*(hm $SRC |
	sdlpic |
	pic |
	nawk  '
		# Replace pic code with reference
		/^\\.PS/	{
			++picnum
			outfile = "'$FILE'.p" picnum
			outcmd = "troff >" outfile
			graphics = 1
			print ".lg 0" | outcmd
			print ".nf" | outcmd

			print ".br"
			print "Picture \\\\*(Rf - only on terminals running layers"
			print ".br"
			print ".RS"
			print "%!!hy.proof " outfile "^J"
			print ".RF"
			}

		# Process the graphics lines
		graphics == 1	{
			print | outcmd
			}

		# Terminate this graphics section
		/^\\.PE/	{
			close(outcmd);
			graphics = 0
			next
			}

		# Just pass through other lines
		graphics == 0 {
			print
			}
	' |
	tbl -TX |
	nroff -mm -Tlp |
	col -x >$OUTFILE
done
exit 0
.in
.fi
.H 2 "hy.proof"
.nf
.nj
.in 0
###################################################################
# Interface to pic files - calls are generated by hy.format
#
# Arg. is name of troff output file
###################################################################

FILE=`dirname $HYDOCP`/`basename "$1"`

NTERM=`ttype -Tdmd`
case $NTERM in
	viterm | emacsterm)
		echo "Graphics not available while running $NTERM" 2>&1
		exit 1
		;;
	630|730*)
		CMD='xproof -c'
		;;
	dmd)
		CMD='proof'
		;;
	*)
		echo "Graphics only available on 630 and 5620 terminals" 2>&1
		exit 1
		;;
esac

/usr/add-on/630/bin/ismpx - || {
	echo "Graphics only available when running layers"
	exit 1
}

echo "
	Entering proof

Type  x  when you want to exit from graphics mode"
sleep 2

$CMD $FILE

if [ "$CMD" = proof     -a    `ttype -Tdmd` != dmd ]
then
	unproof
fi
exit 0
.H 2 "hy.audit"
.nf
.nj
.in 0
# Audit documents for invalid references
#
# Input is a list of (formatted) document filenames
#
# Output is list of invalid references and the file::section where they occur
#

nawk  '
	BEGIN	{
			# Initialize global variables
			FS = "^"
			defined[""] = 1
			referenced[""] = ""
		}

	FILENAME != file	{
			# Update globals for new file
			file = FILENAME
			here = file "::<text before first header>"
			defined[FILENAME "::"] = 1
			defined[FILENAME "::Table of Contents"] = 1
			inref = 0
		}

	NF > 2 && $1 == ""	{
			# Entering a new section
			here = FILENAME "::" $3
			defined[here] = 1
			inref = 0
			next
		}

	/^ *_.R_.E_.F_.E_.R_.E_.N_.C_.E_.S *$/	||  /^ *REFERENCES *$/	{
			# Entering a reference page
			inref = 1
			next
		}

	inref == 1  &&  NF > 1	{
			# Reference that seems to include file name
			if (match($1, /^ *[0-9]+\\. */) == 0)
				next
			reffile = substr($1, RLENGTH+1)
			if (reffile == "")
				reffile = FILENAME
			referenced[reffile "::"  $2] = here
		}

	END	{
			if (0) {	# Change to 1 for debugging
				for (def in defined)
						print def	
				print
				for (ref in referenced)
						print referenced[ref], ref	
			}

			# Check each reference against list of sections
			for (ref in referenced) {
				if (!defined[ref]) {
				   print referenced[ref] "\\t\\t\\t" ref	
				}
			}
		}
'  $*
.in
.H 2 "hman"
This section describes how to format manual pages.
The script is rather slow since it formats the manual pages each time
you call hman; you might want to modify it to save the results for reuse.
.P
Don't process too many manual pages at once; hybrowse will read the
entire formatted document into memory at once.
.P
First create a file called hman.macs to make the "man" macros work
like "mm" macros:
.sp
.nf
\&.de TH
\&.H 1 "\\\\$1 (\\\\$2)"
\&..
\&.de SH
\&.H 2 "\\\\$1 \\\\$2 \\\\$3 \\\\$4 \\\\$5 \\\\$6 \\\\$7 \\\\$8 \\\\$9"
\&..
\&.de SS
\&.H 3 "\\\\$1 \\\\$2 \\\\$3 \\\\$4 \\\\$5 \\\\$6 \\\\$7 \\\\$8 \\\\$9"
\&..
\&.rm }C }H }F )G
.fi
.P
Then create a script called hman:
.sp
.nf
.in +5
#
# Find manual pages, format, and enter hybrowse
#
if [ $# = 0 ]
then
	echo "Usage: $0 cmd..." 2>&1
	exit 1
fi

# Need explicit check - otherwise neqn can hang waiting for input from stdin
TEMP=`man -w $*`
if [ -z "$TEMP" ]
then
	exit 1
fi

# Format the files
neqn  $TEMP | tbl -TX |
nroff -man -Tlp \*(hm YOUR_DIR/hman.macs - |
col -x >hman.out

# Browse
hybrowse -s "Table of Contents" -d hman.out

# Cleanup
rm hman.out
.fi
.in -5
.P
(This section derived from ideas submitted by M. B. Brilliant.)
.P
Another way to browse manual pages is to create a Catalog with references to
existing preformatted pages.
The catalog entries would consist of the NAME section from the manual pages
with a reference to the full text.
This works well if the pages are short enough that you don't need
a separate section for the manual page headings.
'br\}
.H 1 "Escape Scripts"
Hybrowse sets several environment variables during shell escapes:
.VL 10
.LI HYDOC
the name of the current document (without the path)
.LI HYDOCP
the name of the current document (with the path)
.LI HYSECT
the name of the current section
.LI HYLINE
the line within the section (the top line on the screen)
.LE
.P
These variables are intended to be used by shell scripts 
called from the hybrowse "!" command.
Commands that call hybrowse should change $PATH to pick up any
applicable shell scripts (see reference \*(Rf).
.RS
^Access Scripts
.RF
.P
The following subsections show some simple examples.
If you want to use the examples, just write out the example sections
and then edit the examples to do what you want.
.P
Scripts can be hidden inside macros to make them look like builtin
browser commands.
See the "-a" parameter \*(Rf
.RS
^Macro File
.RF
for details.
.H 2 "One-line Notes"
The following script, called note, prompts for a one-line comment
and saves the comment, with an indication of what document/section/line
it applies to, in a file called notes.
It might be useful for taking notes keyed to the document,
as for online review of a document:
.DS I
echo "Enter your one-line note (without any quotes)"
NOTE=`line`
echo "\\\\n$HYDOC $HYSECT $HYLINE\\\\n$NOTE"  >>notes
.DE
.P
Users could run the script by typing "!note".
.H 2 "Multi-line Notes"
The following script, called longnote, might be useful for 
taking notes keyed to the document, as for online review of a document:
.DS I
echo "\\\\n$HYDOC $HYSECT $HYLINE" >>notes
$EDITOR +50000 notes
.DE
.P
"50000" is just a big number to get to the end of the note file.
.P
Users could run the script by typing "!longnote".
.H 2 "Source Editing"
The following script, called edsrc, can be used to modify the
nroff source for a document.
It enters the editor (either vi or emacs) at the appropriate section header.
.DS I
if [ ! -w $HYDOCP.mm ]
then
	echo "Sorry, that source can't be edited" 2>&1
	exit
fi
$EDITOR "+/^\\\\.H *[U1-5] *\\\\"*$HYSECT\\\\"* *$/" $HYDOCP.mm 
.DE
.P
As written, the script assumes that the document is in a directory with the
source files and that the source for document XX is named XX.mm.
You might have to modify these assumptions for your application.
.P
Hybrowse keeps the most-recently-used documents in memory, so if you
escape from the editor to reformat the document, don't expect to see the
results when you return to hybrowse
(to see the changes, you'll have to exit and reenter hybrowse).
.H 1 "Creating Browser-Specific Documents"
Hybrowse can be used with most regular memos, but better results
(from the readers' viewpoint) can be obtained by taking the browser's
strengths and weaknesses into account.
If you want to write browser-specific documents, the following subsections
may provide you with some ideas.
.H 2 "Writing Style"
When documents are written for online access, the browser's facilities and
the limitations of display terminals encourage changes to writing style:
.DL
.LI
Sections, paragraphs, and sentences should be short.
.LI
Section headings should be informative.
.LI
The hierarchical structure of sections should be laid out carefully.
.LI
White space should be used to enhance readability.
.LI
References should be made to other documents rather than repeating
their content.
.LI
Changes should be made to existing documents rather than issuing separate
updates.
.LI
Diagrams and paper attachments should be avoided.
.LE
.H 2 "Special Effects"
The following subsections show how documents can be more than just
an online version of what you would write on paper.
.H 3 Menus
Menus are just lists of references that provide users some guidance in finding
the sections they want to read.
They're most commonly used in the Catalog, but can appear in any section.
.P
Sample menu:
.P
Would you like to reread the section on:
.VL 5 "" "" 1
.LI "\*(Rf"
.RS
^Formatting with mm macros
.RF
formatting documents
.LI "\*(Rf"
.RS
^Formatting Documents
.RF
preprocessors
.LI "\*(Rf"
.RS
^Access Scripts
.RF
shell scripts for calling hybrowse
.LE
.H 3 "Programmed Documents"
High-level sections of a document could end with the sentence "If you
would like to skip the details on this subject, press the "}" key".
.P
Menus can also be used to encourage readers to skip directly to the
sections most relevant to them.
.H 3 "Flip Cards"
.DS
   You can do simple animation
   But don't overdo it
.DE
.P
Short sections print like flashcards which can be "flipped" as the reader walks
through the sections.
This gives the impression of objects moving on the screen.
.H 3 "Flip Cards 1"
.DS
=> You can do simple animation
   But don't overdo it
.DE
.H 3 "Flip Cards 2"
.DS
   You can do simple animation
=> But don't overdo it
.DE
.P
.H 3 "Flip Cards 3"
.DS
   You can do simple animation
   But don't overdo it
   Because it gets old quickly
.DE
.H 1 "The End"
This is the end of the hybrowse administrators' guide.
.TC
