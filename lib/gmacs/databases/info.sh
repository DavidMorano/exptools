# @(#)info.sh	1.4
dbadd info "emacs:files-should-end-with-newline" <<"</FoO ThE bAr/>"
Node: files-should-end-with-newline	Up: Variables, Previous: ctlchar-with-^, Next: global-mode-string

Indicates that when a buffer is written to a file, and the  buffer  doesn't
end  in  a  newline,  then  the user should be asked if they want to have a
newline appended.  It used to be that this was the default action, but some
people objected to the question being asked. (default ON)
</FoO ThE bAr/>
dbadd info "emacs:remove-all-local-bindings" <<"</FoO ThE bAr/>"
Node: remove-all-local-bindings		Up: Commands, Previous: region-to-string, Next: remove-binding

Perform a remove-local-binding for all possible  keys;  effectively  undoes
all  local  bindings.   Mode packages should execute this to initialize the
local binding table to a clean state.
</FoO ThE bAr/>
dbadd info "emacs:delete-previous-character" <<"</FoO ThE bAr/>"
Node: delete-previous-character		Up: Commands, Previous: delete-previous-character, Next: delete-previous-word

Delete  the  character  immediatly preceding dot; that is, the character to
the left of the terminals cursor.  If you've just typed a character, RUBOUT
will delete it.  Lines may be merged by deleting newlines.
</FoO ThE bAr/>
dbadd info "emacs:default-case-fold-search" <<"</FoO ThE bAr/>"
Node: default-case-fold-search		Up: Top		Next: default-comment-column, Previous: ctlchar-with-^

default-case-fold-search
            Default-case-fold-search provides the default value  for  case-
          fold-search,  which  is  used  whenever  a new buffer is created.
          (default OFF)
</FoO ThE bAr/>
dbadd info "emacs:some necessary notation" <<"</FoO ThE bAr/>"
Node: Some Necessary Notation		Next: Character Operations, Up: Quick

                                   Any  ordinary  character  goes  into the
                                   buffer  (no  insert   command   needed).
                                   Commands  are  all control characters or
                                   other characters prefixed by Escape or a
                                   control-X. Escape  is  sometimes  called
                                   Meta or Altmode in EMACS.
^                                  A  control character.  ^F means "control
                                   F".
ESC                                A two-character command  sequence  where
                                   the  first  character  is Escape.  ESC-F
                                   means "ESCAPE then F".
ESC-X string                       A command designated "by hand".   "ESC-x
                                   read-file"  means:   type "Escape", then
                                   "x", then "read-file", then <cr>.
dot                                EMACS  term  for  cursor   position   in
                                   current buffer.
mark                               An  invisible set position in the buffer
                                   used by region commands.
region                             The area of the buffer between  the  dot
                                   and mark.
</FoO ThE bAr/>
dbadd info "emacs:silently-kill-processes" <<"</FoO ThE bAr/>"
Node: silently-kill-processes		Up: Variables, Previous: scroll-step, Next: stack-trace-on-error

If ON Emacs will kill processes when it exits without asking any questions.
Normally, if you have processes running when Emacs exits, the question "You
have processes on the prowl, should I hunt them down  for  you"  is  asked.
(default OFF)
</FoO ThE bAr/>
dbadd info "emacs:send-string-to-terminal" <<"</FoO ThE bAr/>"
Node: send-string-to-terminal		Up: Commands, Previous: self-insert, Next: set

(send-string-to-terminal  "string")  sends  the  string argumetn out to the
terminal with no conversion or interpretation.  This should  only  be  used
for  such  applications  as loading function keys when Emacs starts up.  If
you screw up the screen, Emacs won't know about it  and  won't  fix  it  up
automatically for you -- you'll have to type ^L.
</FoO ThE bAr/>
dbadd info "emacs:re-query-replace-string" <<"</FoO ThE bAr/>"
Node: re-query-replace-string		Up: Commands, Previous: quote-character, Next: re-replace-string

re-query-replace-string is identical to  query-replace-string  except  that
the  search  string  is  a  regular expression rather than an uninterpreted
sequence of characters.  See the section on searching, section  page 20 for
more information.
</FoO ThE bAr/>
dbadd info "emacs:execute-monitor-command" <<"</FoO ThE bAr/>"
Node: execute-monitor-command		Up: Commands, Previous: execute-mlisp-line, Next: exit-emacs

Prompt for a Unix command then execute it, placing its output into a buffer
called Command execution and making that buffer visible in a window.    The
command  will  not  be  able  to  read  from its standard input (it will be
connected to  /dev/null).    For  now,  there  is  no  way  to  execute  an
interactive subprocess.
</FoO ThE bAr/>
dbadd info "emacs:delete-region-to-buffer" <<"</FoO ThE bAr/>"
Node: delete-region-to-buffer		Up: Commands, Previous: delete-previous-word, Next: delete-to-killbuffer

Wipe  (kill,  delete) all characters between dot and the mark.  The deleted
text is moved to a buffer whose name is  prompted  for,  which  is  emptied
first.
</FoO ThE bAr/>
dbadd info "emacs:ask-about-buffer-names" <<"</FoO ThE bAr/>"
Node: ask-about-buffer-names		Up: Variables, Next: backup-by-copying

The ask-about-buffer-names variable controls what  the  visit-file  command
does  if  it  detects  a  collision  when  constructing  a buffer name.  If
ask-about-buffer-names is true (the default) then Emacs will ask for a  new
buffer  name  to be given, or for <CR> to be typed which will overwrite the
old buffer.  If it is false then a  buffer  name  will  be  synthesized  by
appending  "<n>" to the buffer name, for a unique value of n.  For example,
if I visit-file "makefile" then the buffer name will be "makefile"; then if
I visit-file "man/makefile" the buffer name will be "makefile<2>".
</FoO ThE bAr/>
dbadd info "compiling (make) operations." <<"</FoO ThE bAr/>"
Node: Compiling (Make) Operations.	Next: Mail

* new-compile-it::           ^X-^E Execute the "make" (or  other)  command,
                                   saving output in a buffer
* next-error::               ^X-^N Go to the next error in the file
* execute-monitor-command::   ^X-! Execute the given command, saving output
                                   in a buffer
</FoO ThE bAr/>
dbadd info "emacs:copy-region-to-buffer" <<"</FoO ThE bAr/>"
Node: copy-region-to-buffer		Up: Commands, Previous: continue-process, Next: current-buffer-name

Copies  the region between dot and mark to the named buffer.  The buffer is
emptied before the text is copied into it; the region between dot and  mark
is left undisturbed.
</FoO ThE bAr/>
dbadd info "emacs:prefix-argument-loop" <<"</FoO ThE bAr/>"
Node: prefix-argument-loop		Up: Commands, Previous: preceding-char, Next: prepend-region-to-buffer

(prefix-argument-loop  <statements>)  executes <statements> prefix-argument
times.  Every function invocation is  always  prefixed  by  some  argument,
usually by the user typing ^Un.  If no prefix argument has been provided, 1
is  assumed.  See also the command provide-prefix-argument and the variable
prefix-argument.
</FoO ThE bAr/>
dbadd info "emacs:execute-mlisp-buffer" <<"</FoO ThE bAr/>"
Node: execute-mlisp-buffer		Up: Commands, Previous: execute-keyboard-macro, Next: execute-mlisp-line

Parse  the  current  buffer as as a single MLisp expression and execute it.
This is what is generally used for testing out new  functions:  stick  your
functions  in  a  buffer wrapped in a defun and use execute-mlisp-buffer to
define them.
</FoO ThE bAr/>
dbadd info "emacs:delete-previous-word" <<"</FoO ThE bAr/>"
Node: delete-previous-word		Up: Commands, Previous: delete-previous-character, Next: delete-region-to-buffer

If not in the middle of a word, delete characters backwards (to  the  left)
until a word is found.  Then delete the word to the left of dot.  A word is
a sequence of alphanumerics.
</FoO ThE bAr/>
dbadd info "emacs:delete-other-windows" <<"</FoO ThE bAr/>"
Node: delete-other-windows		Up: Commands, Previous: delete-next-word, Next: delete-previous-character

Go back to one-window mode.  Generally useful when Emacs has  spontaneously
generated a window (as for ESC-? or ^X^B) and you want to get rid of it.
</FoO ThE bAr/>
dbadd info "emacs:default-right-margin" <<"</FoO ThE bAr/>"
Node: default-right-margin		Up: Top		Next: default-tab-size, Previous: default-mode-line-format

default-right-margin
            Default-right-margin  provides  the  default  value  for right-
          margin, which is used whenever a new  buffer  is  created.    Its
          initial value is some very large number.
</FoO ThE bAr/>
dbadd info "emacs:modify-syntax-entry" <<"</FoO ThE bAr/>"
Node: modify-syntax-entry		Up: Commands, Previous: message, Next: move-dot-to-x-y

Modify-syntax-entry is used to modify a set of entries in the syntax  table
associated  with  the  current  buffer.   Syntax tables are associated with
buffers by using the use-syntax-table command.  Syntax tables are  used  by
commands  like  forward-paren  to do a limited form of parsing for language
dependent routines.  They define such things as which characters are  parts
of  words,  which  quote  strings  and  which  delimit comments (currently,
nothing uses the comment specification).  To see the contents of  a  syntax
table, use the dump-syntax-table command.

The   parameter  to  modify-syntax-entry  is  a  string  whose  first  five
characters  specify  the  interpretation  of  the   sixth   and   following
characters.

The first character specifies the type.  It may be one of the following:

'w'             A  word character, as used by such commands as forward-word
                and case-word-capitalize.

space           A character with no special interpretation.

'('             A left parenthesis.  Typical candidates for this  type  are
                the  characters  '(', '[' and '{'.  Characters of this type
                also have a matching right parenthesis specified (')',  ']'
                and  '}' for example) which appears as the second character
                of the parameter to modify-syntax-entry.

')'             A right parenthesis.  Typical candidates for this type  are
                the  characters  ')', ']' and '}'.  Characters of this type
                also have a matching left parenthesis specified  ('(',  '['
                and  '{' for example) which appears as the second character
                of the parameter to modify-syntax-entry.

'"'             A quote character.  The C string delimiters  "  and  '  are
                usually given this class, as is the Lisp |.

'\'             A prefix character, like \ in C or / in MacLisp.

The  second  character  of the parameter is the matching parenthesis if the
character is of the left or right parenthesis type. If you specify that '('
is a right parenthesis matched by ')', then you should  also  specify  that
')' is a left parenthesis matched by '('.

The  third character, if equal to '{', says that the character described by
this syntax entry can begin a comment; the forth character, if equal to '}'
says that the character described by this syntax entry can end  a  comment.
If  either the beginning or ending comment sequence is two characters long,
then the fifth character provides  the  second  character  of  the  comment
sequence.

The  sixth  and following characters specify which characters are described
by this entry; a range of characters can be  specified  by  putting  a  '-'
between them, a '-' can be described if it appears as the sixth character.

A few examples, to help clear up my muddy exposition:

    (modify-syntax-entry "w    -")  ; makes '-' behave as a normal word
                                    ; character (ESC-F will consider
                                    ; one as part of a word)
    (modify-syntax-entry "(]   [")  ; makes '[' behave as a left parent
                                    ; which is matched by ']'
    (modify-syntax-entry ")[   ]")  ; makes ']' behave as a right paren
                                    ; which is matched by '['

</FoO ThE bAr/>
dbadd info "emacs:kill-to-end-of-line" <<"</FoO ThE bAr/>"
Node: kill-to-end-of-line		Up: Commands, Previous: kill-process, Next: last-key-struck

Deletes characters forward from dot to the immediatly following end-of-line
(or end of buffer if there isn't an end of line).  If dot is positioned  at
the  end of a line then the end-of-line character is deleted.  Text deleted
by the ^K command is placed into the Kill buffer (which really is a  buffer
that  you  can  look at).  A ^K command normally erases the contents of the
kill buffer first; subsequent ^K's in an unbroken sequence  append  to  the
kill buffer.
</FoO ThE bAr/>
dbadd info "emacs:define-buffer-macro" <<"</FoO ThE bAr/>"
Node: define-buffer-macro		Up: Commands, Previous: declare-global, Next: define-global-abbrev

Take the contents of the current buffer and define it as a macro whose name
is associated with the buffer.  This is how one redefines a macro that  has
been edited using edit-macro.
</FoO ThE bAr/>
dbadd info "emacs:track-eol-on-^N-^P" <<"</FoO ThE bAr/>"
Node: track-eol-on-^N-^P		Up: Variables, Previous: this-command, Next: unlink-checkpoint-files

If ON then ^N and ^P will "stick" to the end of a line if they are  started
there.  If OFF ^N and ^P will try to stay in the same column as you move up
and down even if you started at the end of a line.  (default ON)
</FoO ThE bAr/>
dbadd info "emacs:set-auto-fill-hook" <<"</FoO ThE bAr/>"
Node: set-auto-fill-hook		Up: Commands, Previous: set, Next: set-default

set-auto-fill-hook associates a command with the current buffer.  When  the
right  margin  is  passed  by the attempt to insert some character the hook
procedure for that buffer is invoked.  The  character  that  triggered  the
hook will not have been inserted, but will be inserted immediatly after the
hook  procedure  returns  [unless  the  procedure  returns  0].    The hook
procedure  is  responsible   for   maintaining   the   position   of   dot.
last-key-struck  may be usually used to determine which character triggered
the hook.  If no hook procedure is associated with a buffer  then  the  old
action  (break  the  line and indent) will be taken.  This procedure may be
used for such  things  as  automatically  putting  boxes  around  paragraph
comments as they are typed.
</FoO ThE bAr/>
dbadd info "emacs:put-database-entry" <<"</FoO ThE bAr/>"
Node: put-database-entry		Up: Commands, Previous: push-back-character, Next: query-replace-string

(put-database-entry dbname key) takes the current buffer and stores it into
the named database under the given key.
</FoO ThE bAr/>
dbadd info "emacs:dealing with files" <<"</FoO ThE bAr/>"
File: emacs     Node: Dealing with files     Up: Commands

	This node needs a volunteer to finish writing it!
</FoO ThE bAr/>
dbadd info "emacs:backward-paragraph" <<"</FoO ThE bAr/>"
Node: backward-paragraph		Up: Commands, Previous: backward-character, Next: backward-paren

Moves to the beginning of the current or previous paragraph.  Blank  lines,
and Scribe and nroff command lines separate paragraphs and are not parts of
paragraphs.
</FoO ThE bAr/>
dbadd info "emacs:Compiling programs" <<"</FoO ThE bAr/>"
Node: Compiling programs		Up: Basics, Previous: Terminal types

One  of  the  most powerful features of Unix Emacs is the facility provided
for compiling programs and coping with error messages from  the  compilers.
It  essential  that  you understand the standard Unix program make (even if
you don't use Emacs).  This program takes  a  database  (a  makefile)  that
describes  the  relationships among files and how to regenerate (recompile)
them.  If you have a program that is made up of  many  little  pieces  that
have  to  be  individually  compiled  and carefully crafted together into a
single executable file, make can make your life orders of magnitude easier;
it  will  automatically  recompile  only  those  pieces  that  need  to  be
recompiled  and  put  them  together.    Emacs  has  a set of commands that
gracefully interact with this facility.

The ^X^E (execute) command writes all modified  buffers  and  executes  the
make program.  The output of make will be placed into a buffer called Error
log which will be visible in some window on the screen. As soon as make has
finished  Emacs parses all of its output to find all the error messages and
figure out the files and lines referred to.  All  of  this  information  is
squirreled away for later use by the ^X^N command.

The  ^X^N (next) command takes the next error message from the set prepared
by ^X^E and does three things with it:

   - Makes the message itself visible at the top of  a  window.    The
     buffer will be named Error log.

   - Does  a  visit  (see  the  ^X^V command) on the file in which the
     error occurred.

   - Sets dot to the beginning of the line where the compiler saw  the
     error. This setting of dot takes into account changes to the file
     that  may  have  been  made  since the compilation was attempted.
     Emacs perfectly compensates for any changes that  may  have  been
     made  and  always  positions  the text on the correct line (well,
     correct as far as the compiler was concerned; the compiler itself
     may have been a trifle confused about where the error occurred)

If you've seen all the error messages ^X^N will say so and do nothing else.

So, the general scenario for dealing with programs is:

   - Build a make database to describe  how  your  program  is  to  be
     compiled.

   - Compile your program from within Emacs by typing ^X^E.

   - If   there  were  errors,  step  through  them  by  typing  ^X^N,
     correcting the error, and typing ^X^N to get the next.

   - When you run  out  of  error  messages,  type  ^X^E  to  try  the
     compilation again.

   - When  you finally manage to get your beast to compile without any
     errors, type ^C to say goodbye to Emacs.

   - You'll probably want to use sdb, the symbolic debugger, to  debug
     your program.

</FoO ThE bAr/>
dbadd info "emacs:start-remembering" <<"</FoO ThE bAr/>"
Node: start-remembering			Up: Commands, Previous: start-process, Next: stop-process

All following keystrokes will be remembered by Emacs.
</FoO ThE bAr/>
dbadd info "emacs:region-to-process" <<"</FoO ThE bAr/>"
Node: region-to-process			Up: Commands, Previous: region-around-match, Next: region-to-string

(region-to-process  "process-name") -- The region is wrapped up and sent to
the process.
</FoO ThE bAr/>
dbadd info "emacs:backup-by-copying" <<"</FoO ThE bAr/>"
Node: backup-by-copying			Up: Variables, Previous: ask-about-buffer-names, Next: backup-by-copying-when-linked

If true, then when a backup of a file is  made  (see  the  section  on  the
backup-before-writing   variable)   then   rather   than  doing  the  fancy
link/unlink footwork, Emacs copies the original file onto the backup.  This
preserves all link and owner information & ensures that the files  I-number
doesn't  change  (you're  crazy  if  you  worry  about  a  files I-number).
Backup-by-copying incurs a fairly heafty  performance  penalty.    See  the
section  on the backup-by-copying-when-linked variable for a description of
a compromise.  (default OFF)
</FoO ThE bAr/>
dbadd info "emacs:use-syntax-table" <<"</FoO ThE bAr/>"
Node: use-syntax-table			Up: Commands, Previous: use-old-buffer, Next: users-full-name

Associates the named syntax  table  with  the  current  buffer.    See  the
description  of  the  modify-syntax-entry  command  for more information on
syntax tables.
</FoO ThE bAr/>
dbadd info "emacs:use-abbrev-table" <<"</FoO ThE bAr/>"
Node: use-abbrev-table			Up: Commands, Previous: unlink-file, Next: use-global-map

Sets the current local abbrev table to the one with the given name.   Local
abbrev  tables  are  buffer  specific  and are usually set depending on the
major mode.  Several buffers may have the same  local  abbrev  table.    If
either  the  selected abbrev table or the global abbrev table have had some
abbrevs defined in them, abbrev-mode is turned on for the current buffer.  
</FoO ThE bAr/>
dbadd info "emacs:unbound commands" <<"</FoO ThE bAr/>"
Node: Unbound Commands			Up: Basics, Previous: Basic Commands, Next: Getting Help

Even though the number of characters available to use for Emacs commands is
large, there are  still  more  commands  than  characters.    You  probably
wouldn't want to bind them all to keys even if you could.  Each command has
a  long  name and by that long name may be bound to a key.  For example, ^F
is normally bound to the command named forward-character  which  moves  dot
forward one character.

There are many commands that are not normally bound to keys.  These must be
executed  with  the  ESC-X  command  or  by  binding them to a key (via the
bind-to-key command).  Heaven help the twit who rebinds ESC-X.

The ESC-X command will print ": " on the  last  line  of  the  display  and
expect  you to type in the name of a command.  Space and ESC characters may
be struck to invoke Tenex style command completion (ie.  you  type  in  the
first  part  of  the command, hit the space bar, and Emacs will fill in the
rest for you -- it will complain if it can't figure out what you're  trying
to say).  If the command requires arguments, they will also be prompted for
on the bottom line.  
</FoO ThE bAr/>
dbadd info "emacs:previous-command" <<"</FoO ThE bAr/>"
Node: previous-command			Up: Commands, Previous: prepend-region-to-buffer, Next: previous-line

(previous-command) usually returns the character  value  of  the  keystroke
that  invoked  the previous command.  In is something like last-key-struck,
which returns the keystroke that invoked the current command.   However,  a
function may set the variable this-command to some value, which will be the
value  of  previous-command after the next command invocation.  This rather
bizarre command/variable pair is intended to be used in the  implementation
of  MLisp  functions  which  behave  differently when chained together (ie.
executed one after the other).  A good example is  ^K,  kill-to-end-of-line
which appends the text from chained kills to the killbuffer.

To use this technique for a set of commands which are to exhibit a chaining
behaviour, first pick a magic number.  -84, say.  Then each command in this
set  which  is chainable should (setq this-command -84).  Then to tell if a
command is being chained, it suffices to check to see if (previous-command)
returns -84.

Did I hear you scream ``hack''??
</FoO ThE bAr/>
dbadd info "emacs:local-binding-of" <<"</FoO ThE bAr/>"
Node: local-binding-of			Up: Commands, Previous: local-bind-to-key, Next: looking-at

Returns the name of the procedure to which a keystroke sequence is bound in
the local keymap. "nothing" is returned if the sequence is  unbound.    The
procedure  global-binding-of  performs  a  similar  function for the global
keymap.
</FoO ThE bAr/>
dbadd info "emacs:get-tty-variable" <<"</FoO ThE bAr/>"
Node: get-tty-variable			Up: Commands, Previous: get-tty-string, Next: getenv

(get-tty-variable prompt) prompts for  the  name  of  a  declared  variable
(using  command  completion  &  providing help) and returns the name of the
variable as a string.  For example, the expand-mlisp-variable  function  is
simply (insert-string (get-tty-variable ": expand-mlisp-variable ")).
</FoO ThE bAr/>
dbadd info "emacs:case-word-invert" <<"</FoO ThE bAr/>"
Node: case-word-invert			Up: Commands, Previous: case-word-capitalize, Next: case-word-lower

Invert  the  case of all alphabetic characters in the current word (the one
above or to the left of dot).
</FoO ThE bAr/>
dbadd info "emacs:case-fold-search" <<"</FoO ThE bAr/>"
Node: case-fold-search			Up: Variables, Previous: buffer-is-modified, Next: checkpoint-frequency

If  set  ON  all  searches  will  ignore the case of alphabetics when doing
comparisons.  (default OFF)
</FoO ThE bAr/>
dbadd info "emacs:Unbound Commands" <<"</FoO ThE bAr/>"
Node: Unbound Commands			Up: Basics, Previous: Basic Commands, Next: Getting Help

Even though the number of characters available to use for Emacs commands is
large,  there  are  still  more  commands  than  characters.   You probably
wouldn't want to bind them all to keys even if you could.  Each command has
a long name and by that long name may be bound to a key.  For  example,  ^F
is  normally  bound  to the command named forward-character which moves dot
forward one character.

There are many commands that are not normally bound to keys.  These must be
executed with the ESC-X command or by  binding  them  to  a  key  (via  the
bind-to-key command).  Heaven help the twit who rebinds ESC-X.

The  ESC-X  command  will  print  ":  " on the last line of the display and
expect you to type in the name of a command.  Space and ESC characters  may
be  struck  to  invoke  Tenex style command completion (ie. you type in the
first part of the command, hit the space bar, and Emacs will  fill  in  the
rest  for you -- it will complain if it can't figure out what you're trying
to say).  If the command requires arguments, they will also be prompted for
on the bottom line.  
</FoO ThE bAr/>
dbadd info "emacs:users-full-name" <<"</FoO ThE bAr/>"
Node: users-full-name			Up: Commands, Previous: use-syntax-table, Next: users-login-name

MLisp function that returns the users full name as a  string.  [Really,  it
returns the contents of the gecos field of the passwd entry for the current
user, which is used on many systems for the users full name.]
</FoO ThE bAr/>
dbadd info "emacs:trivial example" <<"</FoO ThE bAr/>"
File: emacs     Node: trivial example     Up: Init files, Next: default profile

A profile is simply a file containing a bunch of MLisp statements that get
executed when Emacs starts up.  The following profile just causes long lines
to wrap around on the display and the "spell" command to be automatically
loaded from "spell.ml" if it is exeucted:

	(autoload "time" "time.ml")
	(setq wrap-long-lines 1)

* menu:
* autoload::		explaination of the autoload function
* setq::		the assignment function
* load::		profiles are really "loaded" into emacs, this
			explains what "load" means.
</FoO ThE bAr/>
dbadd info "emacs:default profile" <<"</FoO ThE bAr/>"
File: emacs     Node: default profile     Up: Init files, Previous: trivial example, Next: complicated profile

This is the profile loaded at CMU for users who don't have .emacs_pro files
in their home directories.

(autoload "time" "time.ml")
(autoload "spell" "spell.ml")
(autoload "incremental-search" "incr-search.ml")
(autoload "reverse-incremental-search" "incr-search.ml")
(autoload "electric-c-mode" "electric-c.ml")
(autoload "electric-lisp-mode" "electric-lisp.ml")
(autoload "electric-mlisp-mode" "electric-lisp.ml")
(autoload "scribe-mode" "scribe.ml")
(autoload "lisp" "process.ml")
(setq quick-redisplay 1)
(setq default-mode-line-format " %[Buffer: %b%*  File: %f  %M (%m)  %p%]")
(setq wrap-long-lines 1)
(setq backup-before-writing 1)
(setq backup-by-copying-when-linked 1)
(auto-execute "electric-c-mode" "*.c")
(auto-execute "electric-c-mode" "*.h")
(auto-execute "text-mode" "/tmp/*")
(auto-execute "scribe-mode" "*.mss")
(auto-execute "electric-mlisp-mode" "*.ml")
(auto-execute "electric-lisp-mode" "*.l")
(auto-execute "electric-mlisp-mode" "*.emacs_pro")

</FoO ThE bAr/>
dbadd info "emacs:character moves" <<"</FoO ThE bAr/>"
File: emacs     Node: character moves     Up: Moving around

* menu:
* backward-character::			(^B)
* forward-character::			(^F)
* goto-character::
</FoO ThE bAr/>
dbadd info "paragraph operations" <<"</FoO ThE bAr/>"
Node: Paragraph Operations		Next: Getting Out

* backward-paragraph::       ESC-[ Move to beginning of the paragraph
* forward-paragraph::        ESC-] Move to end of the paragraph
* indent-C-procedure::       ESC-j Justify the current paragraph
</FoO ThE bAr/>
dbadd info "emacs:sentence moves" <<"</FoO ThE bAr/>"
File: emacs     Node: sentence moves     Up: Moving around

* menu:
* backward-sentence::			(ESC-a)
* forward-sentence::			(ESC-e)
</FoO ThE bAr/>
dbadd info "emacs:pop-up-windows" <<"</FoO ThE bAr/>"
Node: pop-up-windows			Up: Variables, Previous: needs-checkpointing, Next: prefix-argument

If ON Emacs will try to use some window other than the current one when  it
spontaneously generates a buffer that it wants you to see or when you visit
a  file  (it  may  split the current window).  If OFF the current window is
always used.  (default ON)
</FoO ThE bAr/>
dbadd info "emacs:list-processes" <<"</FoO ThE bAr/>"
Node: list-processes			Up: Commands, Previous: list-databases, Next: load

(list-processes) -- Analagous to "list-buffers".  Processes which have died
only appear once in this list before completely disappearing.
</FoO ThE bAr/>
dbadd info "emacs:list-databases" <<"</FoO ThE bAr/>"
Node: list-databases			Up: Commands, Previous: list-buffers, Next: list-processes

(list-databases) lists all data base search lists.
</FoO ThE bAr/>
dbadd info "emacs:goto-character" <<"</FoO ThE bAr/>"
Node: goto-character			Up: Commands, Previous: global-binding-of, Next: if

Goes to the given character-position.  (goto-character 5) goes to character
position 5.
</FoO ThE bAr/>
dbadd info "emacs:following-char" <<"</FoO ThE bAr/>"
Node: following-char			Up: Commands, Previous: filter-region, Next: forward-balanced-paren-line

(following-char) is an MLisp function that returns the character immediatly
following  dot.  The null character (0) is returned if dot is at the end of
the buffer.  Remember that dot is not `at' some character,  it  is  between
two characters.
</FoO ThE bAr/>
dbadd info "emacs:enlarge-window" <<"</FoO ThE bAr/>"
Node: enlarge-window			Up: Commands, Previous: end-of-window, Next: eobp

Makes the current window one line taller, and the window below (or the  one
above  if  there  is  no  window below) one line shorter.  Can't be used if
there is only one window on the screen.
</FoO ThE bAr/>
dbadd info "emacs:current-column" <<"</FoO ThE bAr/>"
Node: current-column			Up: Commands, Previous: current-buffer-name, Next: current-file-name

(current-column)  is  an  MLisp  function  that returns the printing column
number of the character immediately following dot.
</FoO ThE bAr/>
dbadd info "emacs:char-to-string" <<"</FoO ThE bAr/>"
Node: char-to-string			Up: Commands, Previous: change-directory, Next: checkpoint

Takes a numeric argument and returns a one character  string  that  results
from considering the number as an ascii character.
</FoO ThE bAr/>
dbadd info "emacs:Basic Commands" <<"</FoO ThE bAr/>"
Node: Basic Commands			Up: Basics, Previous: Invoking Emacs, Next: Unbound Commands

Normally  each character you type is interpreted individually by Emacs as a
command.  The instant you type a character the  command  it  represents  is
performed immediatly.

All  of  the  normal printing characters when struck just insert themselves
into the buffer at dot.

To move dot there are several simple commands.  ^F moves  dot  forward  one
character,  ^B  moves  it backward one character.  ^N moves dot to the same
column on the next line, ^P moves it to the same  column  on  the  previous
line.

String  searches  may be used to move dot by using the ^S command to search
in the forward direction and ^R to search in the reverse direction.

Deletions may be performed using ^H (backspace) to delete the character  to
the left of dot and ^D to delete the character to the right of dot.

The following table summarizes all of the motion and deletion commands.
                                        Direction
                                   Move          Delete
Units of Motion                 Left   Right   Left   Right
Characters                       ^B     ^F      ^H      ^D
Words                          ESC-B   ESC-F   ESC-H  ESC-D
Intra line                       ^A     ^E       ^K
Inter line                       ^P     ^N
</FoO ThE bAr/>
dbadd info "emacs:start-process" <<"</FoO ThE bAr/>"
Node: start-process			Up: Commands, Previous: start-filtered-process, Next: start-remembering

(start-process "command" "buffer-name") -- The home shell is used to  start
a  process  executing  the  command.    This  process is tied to the buffer
"buffer-name" unless it is null  in  which  case  the  "Command  execution"
buffer  is  used.  Output from the process is automatically attached to the
end of the buffer.  Each time this is done, the mark is left at the end  of
the output (which is the end of the buffer).
</FoO ThE bAr/>
dbadd info "emacs:previous-page" <<"</FoO ThE bAr/>"
Node: previous-page			Up: Commands, Previous: previous-line, Next: previous-window

Repositions  the  current window on the current buffer so that the previous
page of the buffer is visible in the window (where a page  is  a  group  of
lines  slightly  smaller  than  a  window).    In other words, it flips you
backward a page in the buffer.  Its inverse is ^V.   If  possible,  dot  is
kept where it is, otherwise it is moved to the middle of the new page.
</FoO ThE bAr/>
dbadd info "emacs:pop-to-buffer" <<"</FoO ThE bAr/>"
Node: pop-to-buffer			Up: Commands, Previous: pause-emacs, Next: preceding-char

Switches to a buffer whose name is provided  and  ties  that  buffer  to  a
popped-up  window.    Pop-to-buffer is exactly the same as switch-to-buffer
except that  switch-to-buffer  ties  the  buffer  to  the  current  window,
pop-to-buffer finds a new window to tie it to.
</FoO ThE bAr/>
dbadd info "emacs:insert-string" <<"</FoO ThE bAr/>"
Node: insert-string			Up: Commands, Previous: insert-filter, Next: int-process

(insert-string  stringexpressions)  is  an  MLisp function that inserts the
strings that result from evaluating the given stringexpressions and inserts
them into the current buffer just before dot.
</FoO ThE bAr/>
dbadd info "emacs:forward-paren" <<"</FoO ThE bAr/>"
Node: forward-paren			Up: Commands, Previous: forward-paragraph, Next: forward-sentence

Moves dot forward until an unmatched close parenthesis, ')', or the end  of
the  buffer  is  found.    This  can  be  used to aid in skipping over Lisp
S-expressions.  The definitions of parenthesis and strings from the  syntax
table for the current buffer are used.
</FoO ThE bAr/>
dbadd info "emacs:delete-window" <<"</FoO ThE bAr/>"
Node: delete-window			Up: Commands, Previous: delete-white-space, Next: describe-bindings

Removes the current window from the screen and gives  it's  space  to  it's
neighbour below (or above) and makes the current window and buffer those of
the neighbour.
</FoO ThE bAr/>
dbadd info "emacs:Extensibility" <<"</FoO ThE bAr/>"
Node: Extensibility			Up: Basics, Previous: Abbrev mode, Next: Searching

Unix Emacs has two extension features: macros and a built in  Lisp  system.
Macros  are  used  when  you have something quick and simple to do, Lisp is
used when you want  to  build  something  fairly  complicated  like  a  new
language  dependant  mode.    A  macro  is  just a piece of text that Emacs
remembers in a special way.  When a macro is executed the  characters  that
make  up  the  macro  are  treated  as  though  they  had been typed at the
keyboard.  If you have some common sequence of keystrokes you can define  a
macro  that contains them and instead of retyping them just call the macro.
There are two ways of defining macros:

The easiest is called a keyboard macro.  A keyboard  macro  is  defined  by
typing  the  start-remembering command (^X() then typing the commands which
you want to have saved (which will be executed as you type them so that you
can make sure that they are right) then typing the stop-remembering command
(^X)).  To execute the keyboard macro just type the  execute-keyboard-macro
command  (^Xe).    You  can only have one keyboard macro at a time.  If you
define a new keyboard macro the old keyboard macro vanishes into the mist.

Named macros are slightly more complicated.  They  have  names,  just  like
commands and MLisp functions and can be called by name (or bound to a key).
They  are  defined  by using the define-string-macro command (which must be
executed by typing ESC-Xdefine-string-macro since it isn't usually bound to
a key) which asks for the name of the macro and it's body.    The  body  is
typed  in  as  a string in the prompt area at the bottom the the screen and
hence all special characters in it must be quoted by  prefixing  them  with
^Q.    A  named  macro  may  be executed by typing ESC-Xname-of-macro or by
binding it to a key with bind-to-key.

The current keyboard macro can be converted into a named macro by using the
define-keyboard-macro command which takes a name a defines a macro by  that
name  whose body is the current keyboard macro.  The current keyboard macro
ceases to exist.  Unix Emacs contains an interpreter for a language that in
many  respects  resembles  Lisp.    The  primary  (some  would  say   only)
resemblance  between Mock Lisp and any real Lisp is the general syntax of a
program, which many feel is Lisp's weakest point.  The differences  include
such  things as the lack of a cons function and a rather peculiar method of
passing parameters.

    The syntax of MLisp expressions

There are four basic syntactic entities out of which MLisp expressions  are
built.  The two simplest are integer constants (which are optionally signed
strings of digits) and string constants (which are sequences of  characters
bounded by double quote [``"''] characters -- double quotes are included by
doubling  them:  """"  is a one character string. The third are names which
are used to refer to things: variables or procedures.  These three are  all
tied  together  by the use of procedure calls.  A procedure call is written
as a left parenthesis, ``('', a name which refers to the procedure, a  list
of whitespace separated expressions which serve as arguments, and a closing
right  parenthesis,  ``)''.    An  expression  is  simply one of these four
things: an integer constant, a string constant, a name, or a call which may
itself be recursivly composed of other expressions.

String constants may contain the  usual  C  excape  sequences,  "\n"  is  a
newline,  "\t"  is  a  tab, "\r" is a carriage return, "\b" is a backspace,
"\e" is the escape (033) character, "\nnn" is  the  character  whose  octal
representation is nnn, and "^\c" is the control version of the character c.

For example, the following are legal MLisp expressions:

1               The integer constant 1.

"hi"            A two character string constant

"\^X\^F"        A two character string constant

"""what?"""     A seven character string constant

(+ 2 2)         An  invocation of the "+" function with integer arguments 2
                and  2.    "+"  is  the  usual  addition  function.    This
                expression evaluates to the integer 4.

(setq bert (* 4 12))
                An  invocation  of the function setq with the variable bert
                as its first argument and and expression that evaluates the
                product of 4 and 12 as its second argument.  The evaluation
                of this expression assigns the integer 48 to  the  variable
                bert.

(visit-file "mbox")
                An  invocation  of  the function visit-file with the string
                "mbox" as its first  argument.    Normally  the  visit-file
                function  is  tied  to  the  key  ^X^B.  When it is invoked
                interactively, either by typing ^X^B or ESC-Xvisit-file, it
                will prompt in the minibuf for the name of the file.   When
                called from MLisp it takes the file name from the parameter
                list.    All  of the keyboard-callable function behave this
                way.

Names may contain virtually any character, except whitespace or parens  and
they cannot begin with a digit, ``"'' or ``-''.

    The evaluation of MLisp expressions

Variables  must  be  declared  (bound)  before  they  can  be  used.    The
declare-global command can be used to declare a global variable; a local is
declared by listing it at the beginning of a progn or a function body  (ie.
immediatly  after  the  function  name  or  the  word  progn and before the
executable statements).  For example:

    (defun
        (foo i
            (setq i 5)
        )
    )

defines a rather pointless function called  foo  which  declares  a  single
local variable i and assigns it the value 5.  Unlike real Lisp systems, the
list of declared variables is not surrounded by parenthesis.

Expressions  evaluate  to  values  that  are  either  integers,  strings or
markers.  Integers and strings are converted automaticly from  one  to  the
other  type  as needed: if a function requires an integer parameter you can
pass it a string and the characters that make it up will be  parsed  as  an
integer; similarly passing an integer where a string is required will cause
the integer to be converted.  Variables may have either type and their type
is decided dynamically when the assignment is made.

Marker  values  indicate  a position in a buffer.  They are not a character
number.  As insertions and deletions are performed  in  a  buffer,  markers
automatically follow along, maintaining their position.  Only the functions
mark  and  dot  return  markers;  the  user may define ones that do and may
assign markers to variables.  If  a  marker  is  used  in  a  context  that
requires  an  integer  value  then  the  ordinal of the position within the
buffer is used; if a marker is used in a context  that  requires  a  string
value  then  the  name of the marked buffer is used.  For example, if there
has been assigned some marker, then (pop-to-buffer there) will pop  to  the
marked buffer.  (goto-character there) will set dot to the marked position.

A  procedure  written  in  MLisp is simply an expression that is bound to a
name.  Invoking the name causes the associated expression to be  evaluated.
Invocation  may  be  triggered  either by the evaluation of some expression
which calls the procedure, by the  user  typing  it's  name  to  the  ESC-X
command, or by striking a key to which the procedure name has been bound.

All   of   the   commands   listed   in  section  COMMANDDESCRIPTION  (page
COMMANDDESCRIPTION) may be called as MLisp procedures.  Any parameters that
they normally prompt the user for are taken as string expressions from  the
argument  list  in  the same order as they are asked for interactivly.  For
example, the switch-to-buffer command, which is normally tied  to  the  ^XB
key,  normally  prompts for a buffer name and may be called from MLisp like
this:  (switch-to-buffer string-expression).

    Scope issues

There are several sorts  of  names  that  may  appear  in  MLisp  programs.
Procedure, buffer and abbrev table names are all global and occupy distinct
name space. For variables there are three cases:

   1. Global variables: these variables have a single instance and are
      created   either   by   using   declare-global,  set-default  or
      setq-default.  Their lifetime is the entire editing session from
      the time they are created.

   2. Local variables: these have an instance for each declaration  in
      a  procedure body or local block (progn).  Their lifetime is the
      lifetime of the block which declares them.   Local  declarations
      nest and hide inner local or global declarations.

   3. Buffer-specific  variables: these have a default instance and an
      instance for each buffer in  which  they  have  been  explicitly
      given    a    value.        They    are    created    by   using
      declare-buffer-specific.    When  a  variable  which  has   been
      declared  to  be  buffer  specific  is  assigned  a value, if an
      instance for the current buffer hasn't been created then it will
      be.  The value is assigned to the instance associated  with  the
      current buffer.  If a buffer specific variable is referenced and
      an instance doesn't exist for this buffer then the default value
      is used.  This default value may be set with either setq-default
      or  set-default.  If a global instance exists when a variable is
      declared buffer-specific  then  the  global  value  becomes  the
      default.

    MLisp functions

An MLisp function is defined by executing the defun function.  For example:


    (defun
        (silly
            (insert-string "Silly!")
        )
    )

defines  a  function  called  silly  which,  when invoked, just inserts the
string "Silly!" into the current buffer.

MLisp has a rather strange (relative to other languages) parameter  passing
mechanism.   The arg function, invoked as (arg i prompt) evaluates the i'th
argument of the invoking function  if  the  invoking  function  was  called
interactivly  or, if the invoking function was not called interactivly, arg
uses the prompt to ask you for the value.  Consider the following function:

    (defun
        (in-parens
            (insert-string "(")
            (insert-string (arg 1 "String to insert? "))
            (insert-string ")")
        )
    )

If you type ESC-Xin-parens to invoke in-parens interactivly then Emacs will
ask in the minibuffer "String to insert? " and then insert the string typed
into the current buffer surrounded by parenthesis.  If in-parens is invoked
from an MLisp function by (in-parens "foo")  then  the  invocation  of  arg
inside in-parens will evaluate the expression "foo" and the end result will
be that the string "(foo)" will be inserted into the buffer.

The  function  interactive  may  be  used  to  determine whether or not the
invoking function was called interactivly.  Nargs will return the number of
arguments passed to the invoking function.

This  parameter passing mechanism may be used to do some primitive language
extension.  For  example,  if  you  wanted  a  statement  that  executed  a
statement n times, you could use the following:

    (defun
        (dotimes n
            (setq n (arg 1))
            (while (> n 0)
                (setq n (- n 1))
                (arg 2)
            )
        )
    )

Given  this,  the  expression (dotimes 10 (insert-string "<>")) will insert
the string "<>" 10 times.  [Note: The prompt argument may be omitted if the
function can never be called interactivly] .

    Debugging

Unfortunatly, debugging MLisp functions is something of a black art.    The
biggest  problem  right  now  is  that  if  an  MLisp function goes into an
infinite loop there is no way to stop it.

There is no breakpoint facility.  All that you can do is get a stack  trace
whenever  an  error  occurs  by  setting the stack-trace-on-error variable.
With this set, any time that an error occurs a dump of the MLisp  execution
call  stack  and  some  other  information  is  dumped to the "Stack trace"
buffer.

The following piece of MLisp code  is  the  Scribe  mode  package.    Other
implementations  of  Emacs, on ITS and on Multics have modes that influence
the behaviour of Emacs on a file.  This behaviour is usually some  sort  of
language-specific  assistance.   In Unix Emacs a mode is no more that a set
of functions, variables and key-bindings.  This mode package is designed to
be useful when editing Scribe source files.

(defun
                    The apply-look  function  makes  the  current  word
                    "look"  different  by  changing the font that it is
                    printed in.  It positions dot at the  beginning  of
                    the  word  so  you can see where the change will be
                    made and reads a character from the tty.   Then  it
                    inserts  "@c["  (where c is the character typed) at
                    the  front  of  the  word  and  "]"  at  the  back.
                    Apply-look  gets  tied  to  the key ESC-l so typing
                    ESC-l i when the cursor is positioned on  the  word
                    "begin" will change the word to "@i[begin]".
    (apply-look go-forward
        (save-excursion c
            (if (! (eolp)) (forward-character))
            (setq go-forward -1)
            (backward-word)
            (setq c (get-tty-character))
            (if (> c ' ')
                (progn (insert-character '@')
                    (insert-character c)
                    (insert-character '[')
                    (forward-word)
                    (setq go-forward (dot))
                    (insert-character ']')
                )
            )
        )
        (if (= go-forward (dot)) (forward-character))
    )
)

(defun
                    This function is called to set a buffer into Scribe
                    mode
    (scribe-mode
        (remove-all-local-bindings)
                    If the string "LastEditDate=""" exists in the first
                    2000  characters of the document then the following
                    string constant is changed  to  the  current  date.
                    The  intent of this is that you should stick at the
                    beginning   of   your    file    a    line    like:
                    ``@string(LastEditDate="Sat Jul 11 17:59:01 1981")''.
                    This  will  automatically get changed each time you
                    edit the file to reflect that last  date  on  which
                    the file was edited.
        (if (! buffer-is-modified)
            (save-excursion
                (error-occurred
                    (goto-character 2000)
                    (search-reverse "LastEditDate=""")
                    (search-forward """")
                    (set-mark)
                    (search-forward """")
                    (backward-character)
                    (delete-to-killbuffer)
                    (insert-string (current-time))
                    (setq buffer-is-modified 0)
                )
            )
        )
        (local-bind-to-key "justify-paragraph" "\ej")
        (local-bind-to-key "apply-look" "\el")
        (setq right-margin 77)
        (setq mode-string "Scribe")
        (setq case-fold-search 1)
        (use-syntax-table "text-mode")
        (modify-syntax-entry "w    -'")
        (use-abbrev-table "text-mode")
        (setq left-margin 1)
        (novalue)
    )
)

(novalue)

When  Emacs  is  invoked,  it  does several things that are not of too much
interest to the beginning user.

   1. Emacs looks for  a  file  called  ``.emacs pro''  in  your  home
      directory,  if  it  exists  then  it  is  loaded,  with the load
      command.  This is the mechanism used for  user  profiles  --  in
      your  .emacs pro  file,  place  the commands needed to customize
      Emacs to suit your  taste.    If  a  user  has  not  set  up  an
      .emacs pro file then Emacs will use a site-specific default file
      for    initialization.       At   CMU   this   file   is   named
      /usr/local/lib/emacs/maclib/profile.ml

   2. Emacs  will  then  interprete   its   command   line   switches.
      "-l<filename>"  loads  the  given  file (only one may be named),
      "-e<funcname>" executes the named function (again, only one  may
      be named).  -l and -e are executed in that order, after the user
      profile  is  read, but before and file visits are done.  This is
      intended to be used along with the csh alias mechanism to  allow
      you  to  invoke Emacs packages from the shell (that is, assuming
      that there is anyone out there who  still  uses  the  shell  for
      anything  other  than  to run under Emacs!). For example: "alias
      rmail emacs -lrmail -ermail-com"  will  cause  the  csh  "rmail"
      command  to invoke Emacs running rmail.  Exiting rmail will exit
      Emacs.

   3. If neither argv nor argc have  yet  been  called  (eg.  by  your
      startup  or  by the command line named package) then the list of
      arguments will be considered as file names and will be  visited;
      if  there are no arguments then the arguments passed to the last
      invocation of Emacs will be used.

   4. Finally, Emacs invokes it's keyboard  command  interpreter,  and
      eventually terminates.

</FoO ThE bAr/>
dbadd info "emacs:setq-default" <<"</FoO ThE bAr/>"
Node: setq-default			Up: Commands, Previous: setq, Next: shell

Setq-default is used to set the default value of some variable.  It can  be
a  global  parameter,  a buffer-specific variable or a system variable.  It
makes no matter, setq-default will set the default.   Setq-default  is  the
command  to  use from within some MLisp program, like your start up profile
(".Emacs pro").  For example, (setq-default right-margin 60) will  set  the
default right margin for newly created buffers to 60.  In previous versions
of  Emacs  certain system variables had default versions from which default
values were taken. So, to set the default value of right-margin  one  would
assign  a  value  to default-right-margin -- but no more.  Use setq-default
(or set-default instead.

The precise semantics of setq-default are:

   - If the variable being assigned to has not yet been declared, then
     declare it as a global variable.

   - If it is a global variable (whether or not  the  declaration  was
     implicit)  then  assign  the value to it just as the setq command
     would have done.

   - Otherwise, if the  variable  is  buffer  specific  then  set  the
     default value for the variable.  This will be used in all buffers
     where the variable hasn't been explicitly assigned a value.  Note
     that  if  you have a global variable which is eventually declared
     buffer-specific then the global value becomes the default.    The
     intent of this is that users should be able to put setq-default's
     in  their .emacs_pro's without concerning themselves over whether
     the  variable   will   eventually   be   a   simple   global   or
     buffer-specific.

</FoO ThE bAr/>
dbadd info "emacs:reset-filter" <<"</FoO ThE bAr/>"
Node: reset-filter			Up: Commands, Previous: replace-string, Next: return-prefix-argument

Removes the filter that had been bound to some process in a buffer.
</FoO ThE bAr/>
dbadd info "emacs:erase-buffer" <<"</FoO ThE bAr/>"
Node: erase-buffer			Up: Commands, Previous: eot-process, Next: erase-region

Deletes  all text from the current buffer.  Doesn't ask to make sure if you
really want to do it.
</FoO ThE bAr/>
dbadd info "emacs:Getting Help" <<"</FoO ThE bAr/>"
Node: Getting Help			Up: Basics, Previous: Unbound Commands, Next: Buffers and Windows

Emacs has many commands that let you ask Emacs for help about  how  to  use
Emacs.    The  simplest one is ESC-? (apropos) which asks you for a keyword
and then displays a list of those commands whose  full  name  contains  the
keyword  as  a  substring.    For  example,  to find out which commands are
available for dealing with windows, type ESC-?, Emacs will  ask  "Keyword:"
and you reply "window".  A list like the following appears:

    beginning-of-window          ESC-,
    delete-other-windows         ^X1
    delete-window                ^XD
    end-of-window                ESC-.
    enlarge-window               ^XZ
    line-to-top-of-window        ESC-!
    next-window                  ^XN
    page-next-window             ESC-^V
    previous-window              ^XP
    shrink-window                ^X^Z
    split-current-window         ^X2

To  get  detailed  information  about  some  command,  the describe-command
command can be used.  It asks for the name of a command, then displays  the
long documentation for it from the manual.  For example, if you wanted more
information     about     the     shrink-window    command,    just    type
"ESC-Xdescribe-command shrink-window" and Emacs will reply:

     shrink-window
                 Makes the current window one line shorter, and the win
               (or the one above if there is no window below) one  line
               Can't be used if there is only one window on the screen.

If you want to find  out  what  command  is  bound  to  a  particular  key,
describe-key  will  do it for you.  Describe-bindings can be used to make a
"wall chart" description of the  key  bindings  in  the  currently  running
Emacs, taking into account all of the bindings you have made.
</FoO ThE bAr/>
dbadd info "emacs:system-name" <<"</FoO ThE bAr/>"
Node: system-name			Up: Commands, Previous: switch-to-buffer, Next: temp-use-buffer

Is  an MLisp function that returns the name of the system on which Emacs is
being run.  This should be the ArpaNet or EtherNet (or whatever) host  name
of the machine.
</FoO ThE bAr/>
dbadd info "emacs:left-margin" <<"</FoO ThE bAr/>"
Node: left-margin			Up: Variables, Next: mode-line-format

The left margin for automatic text justification.  After  an  automatically
generated newline the new line will be indented to the left margin.
</FoO ThE bAr/>
dbadd info "emacs:interactive" <<"</FoO ThE bAr/>"
Node: interactive			Up: Commands, Previous: int-process, Next: is-bound

An MLisp function which is true iff the invoking MLisp function was invoked
interactively (ie. bound to a key or by ESC-X).
</FoO ThE bAr/>
dbadd info "emacs:end-of-line" <<"</FoO ThE bAr/>"
Node: end-of-line			Up: Commands, Previous: end-of-file, Next: end-of-window

Move  dot  to  the end of the line in the current buffer that contains dot;
that is, to just after the following end-of-line or the end of the buffer.
</FoO ThE bAr/>
dbadd info "emacs:bind-to-key" <<"</FoO ThE bAr/>"
Node: bind-to-key			Up: Commands, Previous: beginning-of-window, Next: bobp

Bind a named macro or procedure to a given key.  All future hits on the key
will cause the named macro or procedure to be called.  The  key  may  be  a
control key, and it may be prefixed by ^X or ESC.  For example, if you want
ESC-=    to    behave    the    way    ESC-Xprint    does,    then   typing
ESC-Xbind-to-key print ESC-= will do it.
</FoO ThE bAr/>
dbadd info "info:differences" <<"</FoO ThE bAr/>"
Node: differences	Previous: Teco	  Up: Teco	Next: Features	

All (non controlified) commands are LOWER CASE ONLY.

VAX INFO currently does not take a menu path as an argument.  However,
the "@" command (*note Path: Expert.) prompts for a menu path once you're
inside INFO.

VAX INFO  lacks the 1-5 commands.  (Anyone who's lazy enough to want
to use them is too lazy to write them.)

The "S" command is just a string search on the current node, i.e. it
can't cross node boundaries.

"A" and "Z" scroll the screen one line down and up respectively.
"R" and "^R" are reverse string search, 
"S" and "^S" are forward string search,
C-V and M-V are next and previous screen respectively.

The command for recursive edit is C-M-E rather than C-R  (E for edit is more
mnemonic than either R for recursive or ^R for TECO ^R mode).   A
control-meta was chosen to make it harder for the unwary to stumble into
recursive edit by accident.  The command to exit is ^C (people tend to use
C-M-Z for things) and cannot be rewired.  Recursive edit behaves a little
differently than the TECO version, because VAX emacs lacks virtual buffer
bounds:  Visiting nodes is done by multi-buffer juggling.  So there's no such
thing as widening bounds to hop across a node boundary, then narrowing them
again. And the buffer you're editing is just a copy of part of the buffer
that really points to the file.  So saving inside a recursive edit is done
by pasting your changes back, then saving the appropriate buffer.  The
command that does this, info-^r-save, is locally bound to C-X C-S.  Doing an
ordinary save (e.g. C-X C-W ) in a recursive edit would not usually be useful.
Your changes are also pasted back (without saving) when you exit the
recursive edit with ^C.

</FoO ThE bAr/>
dbadd info "emacs:electric-c" <<"</FoO ThE bAr/>"
Node: electric-c			Up: Packages, Previous: dired, Next: el-lisp

</FoO ThE bAr/>
dbadd info "line operations" <<"</FoO ThE bAr/>"
Node: Line Operations			Next: Paragraph Operations

* beginning-of-line::           ^A Move to the beginning of the line
* end-of-line::                 ^E Move to the end of the line
* newline-and-backup::          ^O Open up a line for typing
* kill-to-end-of-line::         ^K Kill  from  dot to end of line (^Y yanks
                                   it back at dot)
</FoO ThE bAr/>
dbadd info "emacs:searching" <<"</FoO ThE bAr/>"
Node: Searching				Up: Basics, Previous: Extensibility, Next: Keymaps

Emacs  is  capable  of performing two kinds of searches(Regular and Vanilla
for those of you with no taste).  There are two parallel sets of  searching
and  replacement commands that differ only in the kind of search performed.
The  commands  search-forward,  search-reverse,  query-replace-string   and
replace-string  all  do  simple  searches.  That is, the search string that
they use is matched directly against successive substrings of  the  buffer.
The  characters of the search string have no special meaning.  These search
forms are the easiest to understand and are what most people will  want  to
use.    They  are  what is conventionally bound to ^S, ^R, ESC-Q and ESC-R.
The commands re-search-forward, re-search-reverse, re-query-replace-string,
re-replace-string and looking-at all do regular expression searches.    The
search  string  is  interpreted as a regular expression and matched against
the buffer according to the following rules:

   1. Any character except a special character matches itself. Special
      characters are `\' `[' `.' and sometimes `^' `*' `$'.

   2. A `.' matches any character except newline.

   3. A `\' followed by any character except those  mentioned  in  the
      following rules matches that character.

   4. A  `\w'  Matches  any  word  character, as defined by the syntax
      tables.

   5. A `\W' Matches any non-word character, as defined by the  syntax
      tables.

   6. A  `\b'  Matches  at  a  boundary  between a word and a non-word
      character, as defined by the syntax tables.

   7. A `\B' Matches anywhere but at a boundary between a word  and  a
      non-word character, as defined by the syntax tables.

   8. A `\`' Matches at the beginning of the buffer.

   9. A `\'' Matches at the end of the buffer.

  10. A `\<' Matches anywhere before dot.

  11. A `\>' Matches anywhere after dot.

  12. A `\=' Matches at dot.

  13. A  nonempty  string s bracketed ``[ s ]'' (or ``[^ s ]'' matches
      any character in (or not in) s.    In  s,  `\'  has  no  special
      meaning,  and  `]'  may  only  appear  as  the  first  letter. A
      substring a-b, with a and b in ascending ASCII order, stands for
      the inclusive range of ASCII characters.

  14. A `\' followed by a digit n matches a copy of  the  string  that
      the  bracketed  regular  expression beginning with the n th `\('
      matched.

  15. A regular expression of one of the preceeding forms followed  by
      `*'  matches  a  sequence  of  0  or more matches of the regular
      expression.

  16. A regular expression, x, bracketed ``\( x \)''  matches  what  x
      matches.

  17. A  regular expression of this or one of the preceeding forms, x,
      followed by a regular expression of one of the preceeding forms,
      y matches a match for x followed by a match for y,  with  the  x
      match  being  as  long  as  possible  while still permitting a y
      match.

  18. A regular expression of one of the preceeding forms preceded  by
      `^'  (or  followed by `$'), is constrained to matches that begin
      at the left (or end at the right) end of a line.

  19. A sequence of regular expressions of one of the preceeding forms
      seperated by `\|'s matches any one of the regular expressions.

  20. A regular expression of one of the preceeding  forms  picks  out
      the  longest  amongst the leftmost matches if searching forward,
      rightmost if searching backward.

  21. An empty regular expression  stands  for  a  copy  of  the  last
      regular expression encountered.

In  addition,  in  the  replacement  commands,  re-query-replace-string and
re-replace-string, the characters in the replacement string  are  specially
interpreted:

   - Any character except a special character is inserted unchanged.

   - A  `\'  followed  by  any  character  except  a digit causes that
     character to be inserted unchanged.

   - A `\' followed by a digit n causes the string matched by the  nth
     bracketed expression to be inserted.

   - An  `&'  causes the string matched by the entire search string to
     be inserted.

The following examples should clear a little of the mud:

Pika            Matches the simple string ``Pika''.

Whiskey.*Jack   Matches the string ``Whiskey'',  followed  by  the  longest
                possible  sequence  of  non-newline characters, followed by
                the string ``Jack''.  Think of it as finding the first line
                that contains the string ``Whiskey'' followed eventually on
                the same line by the string ``Jack''

[a-z][a-z]*     Matches a non-null  sequence  of  lower  case  alphabetics.
                Using  this in the re-replace-string command along with the
                replacement string ``(&)'' will  place  parenthesis  around
                all sequences of lower case alphabetics.

Guiness\|Bass   Matches either the string `Guiness' or the string `Bass'.

\Bed\b          Matches `ed' found as the suffix of a word.

\bsilly\W*twit\b
                Matches  the sequence of words `silly' and `twit' seperated
                by arbitrary punctuation.

</FoO ThE bAr/>
dbadd info "emacs:read-file" <<"</FoO ThE bAr/>"
Node: read-file				Up: Commands, Previous: read-abbrev-file, Next: recursion-depth

Prompt  for  the  name of a file; erase the contents of the current buffer;
read the file into the buffer and associate the name with the buffer.   Dot
is set to the beginning of the buffer.
</FoO ThE bAr/>
dbadd info "emacs:next-line" <<"</FoO ThE bAr/>"
Node: next-line				Up: Commands, Previous: next-error, Next: next-page

Move  dot  to  the  next  line.   ^N and ^P attempt to keep dot at the same
horizontal position as you move from line to line.
</FoO ThE bAr/>
dbadd info "emacs:lisp-mode" <<"</FoO ThE bAr/>"
Node: lisp-mode				Up: Packages, Previous: info, Next: occur

</FoO ThE bAr/>
dbadd info "emacs:Searching" <<"</FoO ThE bAr/>"
Node: Searching				Up: Basics, Previous: Extensibility, Next: Keymaps

Emacs  is  capable  of performing two kinds of searches(Regular and Vanilla
for those of you with no taste).  There are two parallel sets of  searching
and  replacement commands that differ only in the kind of search performed.
The  commands  search-forward,  search-reverse,  query-replace-string   and
replace-string  all  do  simple  searches.  That is, the search string that
they use is matched directly against successive substrings of  the  buffer.
The  characters of the search string have no special meaning.  These search
forms are the easiest to understand and are what most people will  want  to
use.    They  are  what is conventionally bound to ^S, ^R, ESC-Q and ESC-R.
The commands re-search-forward, re-search-reverse, re-query-replace-string,
re-replace-string and looking-at all do regular expression searches.    The
search  string  is  interpreted as a regular expression and matched against
the buffer according to the following rules:

   1. Any character except a special character matches itself. Special
      characters are `\' `[' `.' and sometimes `^' `*' `$'.

   2. A `.' matches any character except newline.

   3. A `\' followed by any character except those  mentioned  in  the
      following rules matches that character.

   4. A  `\w'  Matches  any  word  character, as defined by the syntax
      tables.

   5. A `\W' Matches any non-word character, as defined by the  syntax
      tables.

   6. A  `\b'  Matches  at  a  boundary  between a word and a non-word
      character, as defined by the syntax tables.

   7. A `\B' Matches anywhere but at a boundary between a word  and  a
      non-word character, as defined by the syntax tables.

   8. A `\`' Matches at the beginning of the buffer.

   9. A `\'' Matches at the end of the buffer.

  10. A `\<' Matches anywhere before dot.

  11. A `\>' Matches anywhere after dot.

  12. A `\=' Matches at dot.

  13. A  nonempty  string s bracketed ``[ s ]'' (or ``[^ s ]'' matches
      any character in (or not in) s.    In  s,  `\'  has  no  special
      meaning,  and  `]'  may  only  appear  as  the  first  letter. A
      substring a-b, with a and b in ascending ASCII order, stands for
      the inclusive range of ASCII characters.

  14. A  `\'  followed  by a digit n matches a copy of the string that
      the bracketed regular expression beginning with the  n  th  `\('
      matched.

  15. A  regular expression of one of the preceeding forms followed by
      `*' matches a sequence of 0  or  more  matches  of  the  regular
      expression.

  16. A  regular  expression,  x, bracketed ``\( x \)'' matches what x
      matches.

  17. A regular expression of this or one of the preceeding forms,  x,
      followed by a regular expression of one of the preceeding forms,
      y  matches  a  match for x followed by a match for y, with the x
      match being as long as  possible  while  still  permitting  a  y
      match.

  18. A  regular expression of one of the preceeding forms preceded by
      `^' (or followed by `$'), is constrained to matches  that  begin
      at the left (or end at the right) end of a line.

  19. A sequence of regular expressions of one of the preceeding forms
      seperated by `\|'s matches any one of the regular expressions.

  20. A  regular  expression  of one of the preceeding forms picks out
      the longest amongst the leftmost matches if  searching  forward,
      rightmost if searching backward.

  21. An  empty  regular  expression  stands  for  a  copy of the last
      regular expression encountered.

In addition,  in  the  replacement  commands,  re-query-replace-string  and
re-replace-string,  the  characters in the replacement string are specially
interpreted:

   - Any character except a special character is inserted unchanged.

   - A `\' followed by  any  character  except  a  digit  causes  that
     character to be inserted unchanged.

   - A  `\' followed by a digit n causes the string matched by the nth
     bracketed expression to be inserted.

   - An `&' causes the string matched by the entire search  string  to
     be inserted.

The following examples should clear a little of the mud:

Pika            Matches the simple string ``Pika''.

Whiskey.*Jack   Matches  the  string  ``Whiskey'',  followed by the longest
                possible sequence of non-newline  characters,  followed  by
                the string ``Jack''.  Think of it as finding the first line
                that contains the string ``Whiskey'' followed eventually on
                the same line by the string ``Jack''

[a-z][a-z]*     Matches  a  non-null  sequence  of  lower case alphabetics.
                Using this in the re-replace-string command along with  the
                replacement  string  ``(&)''  will place parenthesis around
                all sequences of lower case alphabetics.

Guiness\|Bass   Matches either the string `Guiness' or the string `Bass'.

\Bed\b          Matches `ed' found as the suffix of a word.

\bsilly\W*twit\b
                Matches the sequence of words `silly' and `twit'  seperated
                by arbitrary punctuation.

</FoO ThE bAr/>
dbadd info "info:directory" <<"</FoO ThE bAr/>"
Node: directory		Previous: Live		Up: Top

	This node needs a volunteer to finish writing it!
</FoO ThE bAr/>
dbadd info "emacs:processp" <<"</FoO ThE bAr/>"
Node: processP				Up: Packages, Previous: pascal, Next: pwd

The  process  package  provides  high  level  access to the process control
features of Unix Emacs.  It allows you to interact with a shell through  an
Emacs window, just as though you were talking to the shell normally.

shell           The  shell  command  is  used  to either start or reenter a
                shell process.  When the shell command is  executed,  if  a
                shell  process  doesn't  exist then one is created (running
                the standard ``sh'') tied to a buffer named ``shell'.    In
                any  case, the shell buffer becomes the current one and dot
                is positioned at the end of it.  In that buffer output from
                the shell and programs run with it will appear.    Anything
                typed  into  it  will  get  sent to the subprocess when the
                return key is struck.  This lets you interact with a  shell
                using  Emacs,  and  all  of  it's editing capability, as an
                intermediary.    You  can  scroll backwards over a session,
                pick up pieces of text from other places and  use  them  as
                input,  edit  while watching the execution of some program,
                and much more...

lisp            The lisp command is exactly the same as the  shell  command
                except  that  it  starts  up  ``cmulisp''  in  the ``lisp''
                buffer.  You can have both a shell and a lisp process going
                at the same time.  You can even have as many  shells  going
                as you want, but this package doesn't support it.

grab-last-line  (ESC-=)  This  command takes the last string typed as input
                to the process and brings it back, as though you had  typed
                it  again.  So if you muff a command, just type ESC-=, edit
                the line, and hit return again.

lisp-kill-output
                (^X^K) [this only applies to  lisp  processes]  Erases  the
                output from the last command.  If you don't want to see the
                output  of the last command any more, just type ^X^K and it
                will go away.

pr-newline      (^M -- return) Takes the text of the current line and sends
                it as input to the process  tied  to  the  current  buffer.
                Actually,  if  dot  is  on  the last line of the buffer, it
                takes the region from mark to the end  of  the  buffer  and
                sends it as input (output from a process causes the mark to
                be  set after the inserted text); if dot is not on the last
                line, just the text of that line is shipped (presuming that
                your prompt is "$ ").

send-eot        (^D) If dot is at the end of the buffer,  then  ^D  behaves
                just  as it does outside of Emacs -- it sends an EOT to the
                subprocess (end of file to some folks).  If  dot  isn't  at
                the  end  of  the  buffer, then it does the usual character
                deletion.

send-int-signal (\177 -- rubout) Sends an INT  (Interrupt)  signal  to  the
                subprocess, which should make it stop whatever it is doing.

send-quit-signal
                (^\)  Sends a QUIT signal to the subprocess, making it stop
                whatever it is doing and produce a core dump.

</FoO ThE bAr/>
dbadd info "emacs:processP" <<"</FoO ThE bAr/>"
Node: processP				Up: Packages, Previous: pascal, Next: pwd

The  process  package  provides  high  level  access to the process control
features of Unix Emacs.  It allows you to interact with a shell through  an
Emacs window, just as though you were talking to the shell normally.

shell           The  shell  command  is  used  to either start or reenter a
                shell process.  When the shell command is  executed,  if  a
                shell  process  doesn't  exist then one is created (running
                the standard ``sh'') tied to a buffer named ``shell'.    In
                any  case, the shell buffer becomes the current one and dot
                is positioned at the end of it.  In that buffer output from
                the shell and programs run with it will appear.    Anything
                typed  into  it  will  get  sent to the subprocess when the
                return key is struck.  This lets you interact with a  shell
                using  Emacs,  and  all  of  it's editing capability, as an
                intermediary.  You can scroll  backwards  over  a  session,
                pick  up  pieces  of text from other places and use them as
                input, edit while watching the execution of  some  program,
                and much more...

lisp            The  lisp  command is exactly the same as the shell command
                except that  it  starts  up  ``cmulisp''  in  the  ``lisp''
                buffer.  You can have both a shell and a lisp process going
                at  the  same time.  You can even have as many shells going
                as you want, but this package doesn't support it.

grab-last-line  (ESC-=) This command takes the last string typed  as  input
                to  the process and brings it back, as though you had typed
                it again. So if you muff a command, just type  ESC-=,  edit
                the line, and hit return again.

lisp-kill-output
                (^X^K)  [this  only  applies  to lisp processes] Erases the
                output from the last command.  If you don't want to see the
                output of the last command any more, just type ^X^K and  it
                will go away.

pr-newline      (^M -- return) Takes the text of the current line and sends
                it  as  input  to  the  process tied to the current buffer.
                Actually, if dot is on the last  line  of  the  buffer,  it
                takes  the  region  from  mark to the end of the buffer and
                sends it as input (output from a process causes the mark to
                be set after the inserted text); if dot is not on the  last
                line, just the text of that line is shipped (presuming that
                your prompt is "$ ").

send-eot        (^D)  If  dot  is at the end of the buffer, then ^D behaves
                just as it does outside of Emacs -- it sends an EOT to  the
                subprocess  (end  of  file to some folks).  If dot isn't at
                the end of the buffer, then it  does  the  usual  character
                deletion.

send-int-signal (\177  --  rubout)  Sends  an INT (Interrupt) signal to the
                subprocess, which should make it stop whatever it is doing.

send-quit-signal
                (^\) Sends a QUIT signal to the subprocess, making it  stop
                whatever it is doing and produce a core dump.

</FoO ThE bAr/>
dbadd info "emacs:is-bound" <<"</FoO ThE bAr/>"
Node: is-bound				Up: Commands, Previous: interactive, Next: justify-paragraph

an MLisp predicate that is true iff all of its variable name arguments  are
bound.  
</FoO ThE bAr/>
dbadd info "emacs:autoload" <<"</FoO ThE bAr/>"
Node: autoload				Up: Commands, Previous: auto-execute, Next: backward-balanced-paren-line

(autoload command file) defines the associated  command  to  be  autoloaded
from  the  named  file.    When  an  attempt  to  execute  the  command  is
encountered, the file is loaded and then the execution is attempted  again.
the  loading  of  the file must have redefined the command.  Autoloading is
useful when you have some command written in MLisp but you  don't  want  to
have  the code loaded in unless it is actually needed.  For example, if you
have a function named box-it in a file named box-it.ml,  then  the  command
(autoload  "box-it"  "box-it.ml") will define the box-it command, but won't
load its definition from box-it.ml.  The loading will happen when  you  try
to execute the box-it command.
</FoO ThE bAr/>
dbadd info "info:checking" <<"</FoO ThE bAr/>"
File: info,  Node: checking,  Previous: Tags,  Up: Top

Checking an INFO File:

  When creating an INFO file, it is easy to forget the name of a node
when you are making a pointer to it from another node.  If you put in
the wrong name for a node, this will not be detected until someone
tries to go through the pointer using INFO.  Verification of the INFO
file is an automatic process which checks all pointers to nodes and
reports any pointers which are invalid.  Every Next, Previous, and Up
is checked, as is every menu item and every footnode.  In addition,
any Next which doesn't have a Previous pointing back is reported.
Only pointers within the file are checked, because checking pointers
to other files would be terribly slow.  But those are usually few.

  To check an INFO file, do M-X Run$INFO$Check INFO File<cr> with the
INFO file visited in EMACS, or do X Check INFO File<cr> while looking
at a node in the file with INFO.
</FoO ThE bAr/>
dbadd info "emacs:sit-for" <<"</FoO ThE bAr/>"
Node: sit-for				Up: Commands, Previous: shrink-window, Next: split-current-window

Updates  the  display  and pauses for n/10 seconds.  (sit-for 10) waits for
one second.  This is useful in such things as a Lisp auto-paren balencer.
</FoO ThE bAr/>
dbadd info "emacs:novalue" <<"</FoO ThE bAr/>"
Node: novalue				Up: Commands, Previous: nothing, Next: page-next-window

Does  nothing.    (novalue)  is a complete no-op, it performs no action and
returns no value.  Generally the value of a function is the  value  of  the
last  expression evaluated in it's body, but this value may not be desired,
so (novalue) is provided so that you can throw it away.
</FoO ThE bAr/>
dbadd info "emacs:caveats" <<"</FoO ThE bAr/>"
Node: caveats		Previous: Variables		Up: mscompil


(1) Subprocesses DO NOT INHERIT THEIR CREATORS LOGICAL NAMES.  Therefore,
if you rely on ASSIGN's or DEFINE's done in your login file, you will
be screwed.  You can either avoid such dependence, or place some names
in the group logical name table.  If you're not sure how to do this, don't.
If you do, NEVER use a group name to overide a system name, because this
will screw EVERYONE IN YOUR GROUP.  Also, don't trash other people's group
table entries.  This unfortunate state of affairs will allegedly be fixed
in the next release of VMS.

(2) This currently doesn't work with vanilla mainsail, because it relies
on the inton/intoff feature of testbed mainsail's errmod to inhibit error
responses.
</FoO ThE bAr/>
dbadd info "dir:beginning" <<"</FoO ThE bAr/>"
Node: beginning							Up: Top






		     You must be joking....
</FoO ThE bAr/>
dbadd info "emacs:mstags" <<"</FoO ThE bAr/>"
Node: mstags		Up: tags	Previous: ctags

A MAINSAIL tag is  "procedure" preceded by newline, control-l, or
whitespace, and followed by whitespace followed by a word.  The word (i.e.
the procedure name) is the tag name.

First, do M-X load emacslib:mstags

If a function called &mstags-load-hook is defined, it will be executed
on load (good, e.g. for key bindings.)

To make a tag table, Say M-X make-mstag-table.

You will be prompted for a filespec, giving the files you want to be
included in the table.  This should be a UNIX filespec that doesn't depend
on any current default.  E.G. /sys/quam/*.msl  will do all the .msl files
on quam's directory.

You will then be prompted for an output filename for the tag table.

To use mstags, say "M-X goto-mstag" (or bind it to a key.)
You will be prompted for a tag name.  This should be a leading
substring of the name of the procedure you want.  You get the
first match to that substring (which just might be part of the module 
declaration -- what can you do.)  If it's not the one you want, say
M-X next-mstag (or bind it to a key), and you'll see the next match.

When no tags file has been loaded, goto-mstag will prompt for a tag-table
file name after it prompts for the tag string.  If you want to explicitly
load a tag-table (e.g to change tables) you can say M-X visit-mstag-table.

There is currently no way to incrementally update a tag table, or to specify
arbitrarily compicated file specifications (beyond what you can do with
wildcards.)  This is because the tags files are generated by grep, giving
almost zero flexibility.

</FoO ThE bAr/>
dbadd info "emacs:length" <<"</FoO ThE bAr/>"
Node: length				Up: Commands, Previous: last-key-struck, Next: line-to-top-of-window

Returns the length of its string parameter.  (length "time") => 4.
</FoO ThE bAr/>
dbadd info "emacs:concat" <<"</FoO ThE bAr/>"
Node: concat				Up: Commands, Previous: compile-it, Next: continue-process

Takes a set of string arguments and returns their concatenation.
</FoO ThE bAr/>
dbadd info "info:trees:" <<"</FoO ThE bAr/>"
File: info     Node: trees:

	This node needs to have a volunteer create it.
</FoO ThE bAr/>
dbadd info "emacs:quote" <<"</FoO ThE bAr/>"
Node: quote				Up: Commands, Previous: quit-process, Next: quote-character

Takes a string and inserts quote characters so that  any  characters  which
would  have been treated specially by the reqular expression search command
will be treated as plain characters.  For example,  (quote  "a.b")  returns
"a\.b".
</FoO ThE bAr/>
dbadd info "emacs:progn" <<"</FoO ThE bAr/>"
Node: progn				Up: Commands, Previous: process-status, Next: provide-prefix-argument

(progn expressions...) is an MLisp function that evaluates the  expressions
and  returns  the value of the last expression evaluated.  Progn is roughly
equivalent to a compound statement (begin-end block) in  more  conventional
languages  and  is  used where you want to execute several expressions when
there is space for  only  one  (eg.  the  then  or  else  parts  of  an  if
expression).
</FoO ThE bAr/>
dbadd info "emacs:print" <<"</FoO ThE bAr/>"
Node: print				Up: Commands, Previous: previous-window, Next: process-filter-name

Print the value of the named variable.  This is the command  you  use  when
you want to inquire about the setting of some switch or parameter.
</FoO ThE bAr/>
dbadd info "emacs:marks" <<"</FoO ThE bAr/>"
File: emacs     Node: Marks     Up: Commands

A "marker" exists for each buffer.  It is much like "dot" in that it points
to a position in the buffer, but it must be set explicitly with the set-mark
command.  The mark and dot cooperate to define the bounds of a region of
text which is manipulated by many commands.

* menu:
* exchange-dot-and-mark::		(^X-^X)
* mark::
* set-mark::				(^@)
</FoO ThE bAr/>
dbadd info "emacs:ctags" <<"</FoO ThE bAr/>"
Node: ctags	Previous: ltags		Up: tags	Next: mstags


To invoke, say M-X load ctags

To make a tags file, you use the unix program CTAGS.

visit-ctag-table, goto-ctag, and next-ctag then do appropriate things.

The function &ctags-load-hook is evaled when the library is loaded.
(useful, e.g. for key bindings -- none are done by default.

(for documentation on the unix CTAGS program, say
	u man ctags
 at DCL.)
</FoO ThE bAr/>
dbadd info "emacs:atags" <<"</FoO ThE bAr/>"
File: emacs     Node: atags     Up: tags

This is so bloody crazy!!  Who the hell would want to use ADA?
</FoO ThE bAr/>
dbadd info "emacs:text" <<"</FoO ThE bAr/>"
File: emacs, Node: text, Next: fundamental, Up: top, Previous: lisp

invoke by M-X text-mode

functions:

forward-paragraph		M-]
	places you at start of next paragraph
backward-paragraph		M-[
	places you at start of previous paragrph
mark-paragraph
	places mark at start of current paragraph, and dot at end.
fill-paragraph			M-Q
fill-region			[unbound]
	Doesn't work right yet.
set-fill-prefix			C-X .
	Sets fill-prefix to be the text between dot and the beginning
	of the current line.
auto-fill			[unbound]
nofill				[unbound]

	
Variables:

fill-column		default=78
</FoO ThE bAr/>
dbadd info "emacs:goto" <<"</FoO ThE bAr/>"
Node: goto				Up: Packages, Previous: el-lisp, Next: incr-search

goto-line       Moves  the  cursor  to beginning of the indicated line. The
                line number is taken from the  prefix  argument  if  it  is
                provided,  it  is  prompted  for otherwise.  Line numbering
                starts at 1.

goto-percent    Moves dot to the indicated percentage of  the  buffer.  The
                percentage  is  taken  from  the  prefix  argument if it is
                provided, it is prompted for  otherwise.  (goto-percent  n)
                goes  to the character that is n% from the beginning of the
                buffer.

</FoO ThE bAr/>
dbadd info "emacs:eobp" <<"</FoO ThE bAr/>"
Node: eobp				Up: Commands, Previous: enlarge-window, Next: eolp

(eobp) is an MLisp predicate that is true iff dot is  at  the  end  of  the
buffer.
</FoO ThE bAr/>
dbadd info "emacs:argc" <<"</FoO ThE bAr/>"
Node: argc				Up: Commands, Previous: arg, Next: argument-prefix

Is  an MLisp function that returns the number of arguments that were passed
to Emacs when it was invoked from the Unix shell. If either  argc  or  argv
are  called  early enough then Emacs's startup action of visiting the files
named on the command line is suppressed.
</FoO ThE bAr/>
dbadd info "emacs:arg" <<"</FoO ThE bAr/>"
Node: arg				Up: Commands, Previous: apropos, Next: argc

(arg i [prompt]) evaluates to the i'th argument of the invoking function or
prompts  for  it  if called interactively [the prompt is optional, if it is
omitted, the function cannot be called interactivly]. For example, 

    (arg 1 "Enter a number: ")

Evaluates to the value of the first argument of the  current  function,  if
the current function was called from MLisp.  If it was called interactively
then it is prompted for. As another example, given:  

    (defun (foo (+ (arg 1 "Number to increment? ") 1)))

then (foo 10) returns 11, but typing "ESC-Xfoo" causes emacs to ask "Number
to  increment?  ".    Language  purists will no doubt cringe at this rather
primitive  parameter  mechanism,  but  what-the-hell...    it's   amazingly
powerful.
</FoO ThE bAr/>
dbadd info "emacs:>=" <<"</FoO ThE bAr/>"
Node: >=				Up: Commands, Previous: >, Next: >>

(>= e  e ) MLisp function that returns true iff e  >= e .
     1  2                                        1     2
</FoO ThE bAr/>
dbadd info "emacs:-" <<"</FoO ThE bAr/>"
Node: -					Up: Commands, Previous: +, Next: /

(- e  e ) MLisp function that returns e  - e .
    1  2                               1    2
</FoO ThE bAr/>
dbadd info "emacs:&" <<"</FoO ThE bAr/>"
Node: &					Up: Commands, Previous: %, Next: *

(& e  e ) MLisp function that returns e  & e .
    1  2                               1    2
</FoO ThE bAr/>
dbadd info "emacs:!" <<"</FoO ThE bAr/>"
Node: !					Up: Commands, Next: !=

(! e ) MLisp function that returns not e .
    1                                   1
</FoO ThE bAr/>
dbadd info "search" <<"</FoO ThE bAr/>"
Node: Search				Next: Replace

* re-search-forward::           ^S Search forward
* re-search-reverse::           ^R Search backward
</FoO ThE bAr/>
dbadd info "emacs:" <<"</FoO ThE bAr/>"

</FoO ThE bAr/>
dbadd info "emacs:command prefix, also known as meta" <<"</FoO ThE bAr/>"
Node: Command prefix, also known as META	Up: Comm

The next character typed will be interpreted as a command based on the fact
that  it  was  preceded  by ESC.  The name meta for the ESC character comes
from  funny  keyboards at Stanford and MIT that have a Meta-shift key which
is used to extend the ASCII character set.  Lacking a Meta key, we make  do
with prefixing with an ESC character.  You may see (and hear) commands like
ESC-V  referred to as Meta-V.  Sometimes the ESC key is confusingly written
as $, so ESC-V would be written as $V.  ESC is also  occasionally  referred
to  as Altmode, from the labeling of a key on those old favorites, model 33
teletypes.
</FoO ThE bAr/>
dbadd info "emacs:dealing with collections of files" <<"</FoO ThE bAr/>"
Node: Dealing with collections of files	Up: Basic

The ^X^E command doesn't always execute the make program: if it is given  a
non-zero  argument it will prompt for a Unix command line to be executed in
place of make.  All of the other parts of ^X^E  are  unchanged,  namely  it
still  writes  all modified buffers before executing the command and parses
the output of the command execution for line numbers and file names.

This can be used in some very powerful ways.   For  example,  consider  the
grep  program.    Typing  "^U^X^Egrep  -n  MyProc  *.cESC"  will scan all C
programs in the current directory and  look  for  all  occurrences  of  the
string  "MyProc".   After grep has finished you can use Emacs (via the ^X^N
command) to examine and possibly change every instance of the string from a
whole collection of files.  This makes the task of changing all calls to  a
particular  procedure  much easier.  Note: this only works with the version
of grep in /usr/jag/bin which has been modified to print line numbers in  a
format that Emacs can understand.

There  are  many  more  uses.  The lint program, for example.  Scribe users
might find "cat MyReport.otl" to be useful.

A file name/line number pair is just a string  embedded  someplace  in  the
text  of  the error log that has the form "FileName, line LineNumber".  The
FileName may or may  not  be  surrounded  by  quotes  (").    The  critical
component  is the string ", line " that comes between the file name and the
line number.  Roll your own file scanning programs, it can make  your  life
much easier.
</FoO ThE bAr/>
dbadd info "emacs:Dealing with collections of files" <<"</FoO ThE bAr/>"
Node: Dealing with collections of files	Up: Basic

The  ^X^E command doesn't always execute the make program: if it is given a
non-zero argument it will prompt for a Unix command line to be executed  in
place  of  make.    All of the other parts of ^X^E are unchanged, namely it
still writes all modified buffers before executing the command  and  parses
the output of the command execution for line numbers and file names.

This  can  be  used  in some very powerful ways.  For example, consider the
grep program.  Typing  "^U^X^Egrep  -n  MyProc  *.cESC"  will  scan  all  C
programs  in  the  current  directory  and  look for all occurrences of the
string "MyProc".  After grep has finished you can use Emacs (via  the  ^X^N
command) to examine and possibly change every instance of the string from a
whole  collection of files.  This makes the task of changing all calls to a
particular procedure much easier.  Note: this only works with  the  version
of  grep in /usr/jag/bin which has been modified to print line numbers in a
format that Emacs can understand.

There are many more uses.  The lint program, for  example.    Scribe  users
might find "cat MyReport.otl" to be useful.

A  file  name/line  number  pair is just a string embedded someplace in the
text of the error log that has the form "FileName, line LineNumber".    The
FileName  may  or  may  not  be  surrounded  by  quotes  (").  The critical
component is the string ", line " that comes between the file name and  the
line  number.   Roll your own file scanning programs, it can make your life
much easier.
</FoO ThE bAr/>
dbadd info "emacs:screen and screen operations" <<"</FoO ThE bAr/>"
Node: Screen And Screen Operations, Next: Buffer And File Operations, Up: Quick

* Menu:
* menu:
* next-page::                   ^V Show next screen page
* previous-page::            ESC-V Show previous screen page
* redraw-display::              ^L Redisplay screen
* scroll-one-line-up::          ^Z Scroll screen up
* scroll-one-line-down::     ESC-Z Scroll screen down
* line-to-top-of-window::    ESC-! Move  the  line  dot is on to top of the
                                   screen
* beginning-of-window::      ESC-, Move cursor to beginning of window
* end-of-window::            ESC-. Move cursor to end of window
* split-current-window::      ^X-2 Split the current window in two  windows
                                   (same buffer shown in each)
* delete-other-windows::      ^X-1 Resume   single  window  (using  current
                                   buffer)
* delete-window::             ^X-d Delete the current window, giving  space
                                   to window below
* next-window::               ^X-n Move cursor to next window
* previous-window::           ^X-p Move cursor to previous window
* page-next-window::        ESC-^V Display  the  next  screen  page  in the
                                   other window
* shrink-window::            ^X-^Z Shrink window
* enlarge-window::            ^X-z Enlarge window
</FoO ThE bAr/>
dbadd info "emacs:compiling (make) operations." <<"</FoO ThE bAr/>"
Node: Compiling (Make) Operations.	Next: Mail, Up: Quick

* Menu:
* compile-it::               ^X-^E Execute the "make" (or  other)  command,
                                   saving output in a buffer
* next-error::               ^X-^N Go to the next error in the file
* execute-monitor-command::   ^X-! Execute the given command, saving output
                                   in a buffer
</FoO ThE bAr/>
dbadd info "emacs:backward-balanced-paren-line" <<"</FoO ThE bAr/>"
Node: backward-balanced-paren-line	Up: Commands, Previous: autoload, Next: backward-character

Moves dot backward until either

   - The beginning of the buffer is reached.

   - An  unmatched  open  parenthesis,  '(', is encountered.  That is,
     unmatched between there and the starting position of dot.

   - The beginning of a line  is  encountered  at  "parenthesis  level
     zero".   That is, without an unmatched ')' existing between there
     and the starting position of dot.

The definitions of parenthesis and strings from the syntax  table  for  the
current buffer are used.
</FoO ThE bAr/>
dbadd info "emacs:define-hooked-global-abbrev" <<"</FoO ThE bAr/>"
Node: define-hooked-global-abbrev	Up: Commands, Previous: define-global-abbrev, Next: define-hooked-local-abbrev

The  commands  define-hooked-global-abbrev  and  define-hooked-local-abbrev
behave  exactly  as  the  unhooked  versions  do  (define-global-abbrev and
define-local-abbrev) except that they also associate a named  command  with
the   abbrev.    When  the  abbrev  triggers,  rather  than  replacing  the
abbreviation with the expansion phrase the hook procedure is  invoked.  The
character  that trigged the abbrev will not have been inserted, but will be
inserted immediatly after the hook procedure returns [unless the  procedure
returns  0].    The abbreviation will be the word immediatly to the left of
dot, and the function abbrev-expansion returns the phrase that  the  abbrev
would have expanded to.
</FoO ThE bAr/>
dbadd info "emacs:buffer and file operations" <<"</FoO ThE bAr/>"
Node: Buffer And File Operations, Next: Help And Helper Functions, Up: Quick

* Menu:
* yank-from-killbuffer::        ^Y Yank back the last  thing  killed  (kill
                                   and delete are different)
* visit-file::               ^X-^V Get a file into a buffer for editing
* read-file::                ^X-^R Read a file into current buffer, erasing
                                   old contents
* insert-file::              ^X-^I Insert file at dot
* to-buffer::                ^X-^O Select   a  different  buffer  (it  must
                                   already exist)
* switch-to-buffer::          ^X-B Select a different buffer (it  need  not
                                   pre-exist)
* list-buffers::             ^X-^B Display a list of available buffers
* yank-buffer::             ESC-^Y Insert selected buffer at dot
* beginning-of-file::        ESC-< Move to the top of the current buffer
* end-of-file::              ESC-> Move to the end of the current buffer
</FoO ThE bAr/>
dbadd info "emacs:quietly-read-abbrev-file" <<"</FoO ThE bAr/>"
Node: quietly-read-abbrev-file		Up: Commands, Previous: query-replace-string, Next: quit-process

Read in and define abbrevs appearing in a named file.    This  file  should
have  been  written  using  write-abbrev-file.  Unlike read-abbrev-file, an
error message is not printed if the file cannot be found.
</FoO ThE bAr/>
dbadd info "emacs:prefix-argument-provided" <<"</FoO ThE bAr/>"
Node: prefix-argument-provided		Up: Variables, Previous: prefix-argument, Next: prefix-string

True iff the execution of the current function was prefixed  by  a  numeric
argument.  Use prefix-argument to get it's value.
</FoO ThE bAr/>
dbadd info "emacs:provide-prefix-argument" <<"</FoO ThE bAr/>"
Node: provide-prefix-argument		Up: Commands, Previous: progn, Next: push-back-character

(provide-prefix-argument  <value> <statement>) provides the prefix argument
<value> to the <statement>.  For example, the most efficient  way  to  skip
forward 5 words is:  

    (provide-prefix-argument 5 (forward-word))

See also the command prefix-argument-loop and the variable prefix-argument.

</FoO ThE bAr/>
dbadd info "emacs:describe-word-in-buffer" <<"</FoO ThE bAr/>"
Node: describe-word-in-buffer		Up: Commands, Previous: describe-variable, Next: digit

Takes the word nearest the cursor and looks it up in a data base and prints
the information found.  This data base contains short one-line descriptions
of  all  of the Unix standard procedures and Franz Lisp standard functions.
The idea is that if you've just typed in the name  of  some  procedure  and
can't  quite  remember  which  arguments go where, just type ^X^D and Emacs
will try to tell you.
</FoO ThE bAr/>
dbadd info "emacs:declare-buffer-specific" <<"</FoO ThE bAr/>"
Node: declare-buffer-specific		Up: Commands, Previous: current-time, Next: declare-global

Takes a list of variables and declares them to have buffer-specific values.
A  buffer-specific  variable  has  a  distinct  instance for each buffer in
existance and a default value which is used when new buffers  are  created.
When  a  buffer-specific  variable  is  assigned  a value only the instance
associated with the currently selected buffer is  affected.    To  set  the
default   value   for  a  buffer-specific  variable,  use  setq-default  or
set-default.  Note that if you have a global variable which  is  eventually
declared buffer-specific then the global value becomes the default.
</FoO ThE bAr/>
dbadd info "emacs:case-region-capitalize" <<"</FoO ThE bAr/>"
Node: case-region-capitalize		Up: Commands, Previous: c=, Next: case-region-invert

Capitalize all the words in the region between dot and mark by making their
first characters upper case and all the rest lower case.
</FoO ThE bAr/>
dbadd info "emacs:save-window-excursion" <<"</FoO ThE bAr/>"
Node: save-window-excursion		Up: Commands, Previous: save-restriction, Next: scroll-one-line-down

save-window-excursion  is  identical  to save-excursion except that it also
saves (in a rough sort of  way)  the  state  of  the  windows.    That  is,
(save-window-excursion  expressions...) saves the current dot, mark, buffer
and window state, executes the expressions, restores the saved  information
and returns the value of the last expression evaluated.

When  the window state is saved Emacs remembers which buffers were visible.
When it is restored, Emacs  makes  sure  that  exactly  those  buffers  are
visible.   Emacs does not save and restore the exact layout of the windows:
this is a feature, not a bug.  
</FoO ThE bAr/>
dbadd info "emacs:yank-from-killbuffer" <<"</FoO ThE bAr/>"
Node: yank-from-killbuffer		Up: Commands, Previous: yank-buffer, Next: |

Take  the  contents of the kill buffer and inserts it at dot in the current
buffer.  Dot is left after the inserted text.
</FoO ThE bAr/>
dbadd info "emacs:transpose-characters" <<"</FoO ThE bAr/>"
Node: transpose-characters		Up: Commands, Previous: to-col, Next: undo

Take the two characters preceding dot and exchange them.  One of  the  most
common  errors for typists to make is transposing two letters, typing "hte"
when "the" is meant.  ^T makes correcting these errors easy, especially  if
you can develop a "^T reflex".
</FoO ThE bAr/>
dbadd info "emacs:remove-local-binding" <<"</FoO ThE bAr/>"
Node: remove-local-binding		Up: Commands, Previous: remove-binding, Next: replace-string

Removes the local binding of the  given  key.    The  global  binding  will
subsequently  be  used when interpreting the key.  Bug: there really should
be some way of saving the current binding  of  a  key,  then  restoring  it
later.
</FoO ThE bAr/>
dbadd info "emacs:query-replace-string" <<"</FoO ThE bAr/>"
Node: query-replace-string		Up: Commands, Previous: put-database-entry, Next: quietly-read-abbrev-file

Replace all occurrences of one string with another,  starting  at  dot  and
ending at the end of the buffer.  Emacs prompts for an old and a new string
in  the minibuffer (the line at the bottom of the screen).  See the section
on searching, section  page 20 for more information on search strings.  For
each  occurrence  of the old string, Emacs requests that the user type in a
character to tell it what to do (dot will  be  positioned  just  after  the
found string).  The possible replies are:

<space>         Change this occurrence and continue to the next.
n               Don't change this occurrence, but continue to the next
r               Enter  a recursive-edit.  This allows you to make some
                local changes, then continue the  query-replace-string
                by typing ^C.
!               Change  this  occurrence  and  all  the  rest  of  the
                occurrences without bothering to ask.
.               Change this one and stop: don't do any more replaces.
^G              Don't change this occurrence and stop:  don't  do  any
                more replaces.
?               (or   anything   else)  Print  a  short  list  of  the
                query/replace options.

</FoO ThE bAr/>
dbadd info "emacs:character operations" <<"</FoO ThE bAr/>"
Node: Character Operations		Next: Word Operations, Up: Quick

* Menu:
* backward-character::          ^B Move left (Back)
* forward-character::           ^F Move right (Forward)
* previous-line::               ^P Move up (Previous)
* next-line::                   ^N Move down (Next)
* delete-next-character::       ^D Delete right
* delete-previous-character::                    ^H or BS or DEL or RUBOUT
                                   Delete left
* transpose-characters::        ^T Transpose  previous 2 characters (ht_ ->
                                   th_)
* quote-character::             ^Q Literally  inserts  (quotes)  the   next
                                   character typed (e.g. ^Q-^L)
* argument-prefix::             ^U Provide  a  numeric argument of n to the
                                   command that follows (n defaults  to  4,
                                   eg. try ^U-^N and ^U-^U-^F)
* newline::               ^M or CR Newline
* newline-and-indent::    ^J or NL newline followed by an indent
</FoO ThE bAr/>
dbadd info "emacs:region-around-match" <<"</FoO ThE bAr/>"
Node: region-around-match		Up: Commands, Previous: redraw-display, Next: region-to-process

Region-around-match sets dot and mark around the region matched by the last
search.  An argument of n puts dot and  mark  around  the  n'th  subpattern
matched  by  `\('  and  `\)'.    This  can  then be used in conjuction with
region-to-string to extract fields matched  by  a  patter.    For  example,
consider  the  following  fragment  that extracts user names and host names
from mail addresses:

    (re-search-forward "\\([a-z][a-z]*\\) *@ *\\([a-z][a-z]*\\)")
    (region-around-match 1)
    (setq username (region-to-string))
    (region-around-match 2)
    (setq host (region-to-string))

Applying this MLisp code to the text "send it to jag@vlsi"  would  set  the
variable `username' to "jag" and `host' to "vlsi".
</FoO ThE bAr/>
dbadd info "emacs:push-back-character" <<"</FoO ThE bAr/>"
Node: push-back-character		Up: Commands, Previous: provide-prefix-argument, Next: put-database-entry
Takes  the  character  provided as its argument and causes it to be used as
the next character read from the keyboard.  It is generally only useful  in
MLisp  functions  which read characters from the keyboard, and upon finding
one that they don't understand, terminate and behave as though the key  had
been  struck  to  the  Emacs keyboard command interpreter. For example, ITS
style incremental search.
</FoO ThE bAr/>
dbadd info "emacs:process-filter-name" <<"</FoO ThE bAr/>"
Node: process-filter-name		Up: Commands, Previous: print, Next: process-id

Returns the name of the filter procedure attached to some buffer.
</FoO ThE bAr/>
dbadd info "emacs:parenthesised moves" <<"</FoO ThE bAr/>"
File: emacs     Node: parenthesised moves     Up: Moving around

* menu:
* backward-balanced-paren-line::
* backward-paren::
* forward-balanced-paren-line::
* forward-paren::
</FoO ThE bAr/>
dbadd info "emacs:needs-checkpointing" <<"</FoO ThE bAr/>"
Node: needs-checkpointing		Up: Variables, Previous: mode-string, Next: pop-up-windows

A  buffer-specific variable which if ON indicates that the buffer should be
checkpointed periodically.  If it is OFF, then no checkpoints will be done.
(default ON)
</FoO ThE bAr/>
dbadd info "emacs:default-left-margin" <<"</FoO ThE bAr/>"
Node: default-left-margin		Up: Top		Next: default-mode-line-format, Previous: default-comment-column

default-left-margin
            Default-left-margin provides the default value for left-margin,
          which is used whenever a new buffer is created.  (default 1)
</FoO ThE bAr/>
dbadd info "emacs:buffers and windows" <<"</FoO ThE bAr/>"
Node: Buffers and Windows		Up: Basics, Previous: Getting Help, Next: Terminal types

There are two fundamental objects in Emacs, buffers and windows.  A  buffer
is  a  chunk of text that can be edited, it is often the body of a file.  A
window is a region on the screen through which a buffer may be viewed.    A
window looks at one buffer, but a buffer may be on view in several windows.
It  is  often  handy to have two windows looking at the same buffer so that
you can be looking at two separate parts of the same file, for  example,  a
set  of  declarations  and  a  piece  of code that uses those declarations.
Similarly, it is often handy to have two different buffers on view  in  two
windows.

The  commands which deal with windows and buffers are:  beginning-of-window
(ESC-,),  delete-other-windows  (^X1),  delete-region-to-buffer   (ESC-^W),
delete-window   (^XD),   end-of-window   (ESC-.),   enlarge-window   (^XZ),
line-to-top-of-window  (ESC-!),  list-buffers  (^X^B),  next-window  (^XN),
page-next-window  (ESC-^V),  previous-window  (^XP),  shrink-window (^X^Z),
split-current-window (^X2), switch-to-buffer (^XB),  use-old-buffer  (^X^O)
and  yank-buffer  (ESC-^Y).    See the command description section for more
details on each of these.
</FoO ThE bAr/>
dbadd info "emacs:beginning-of-window" <<"</FoO ThE bAr/>"
Node: beginning-of-window		Up: Commands, Previous: beginning-of-line, Next: bind-to-key

Move  dot  to  just  in  front  of  the  first  character of the first line
displayed in the current window.
</FoO ThE bAr/>
dbadd info "emacs:Buffers and Windows" <<"</FoO ThE bAr/>"
Node: Buffers and Windows		Up: Basics, Previous: Getting Help, Next: Terminal types

There  are two fundamental objects in Emacs, buffers and windows.  A buffer
is a chunk of text that can be edited, it is often the body of a file.    A
window  is  a region on the screen through which a buffer may be viewed.  A
window looks at one buffer, but a buffer may be on view in several windows.
It is often handy to have two windows looking at the same  buffer  so  that
you  can  be looking at two separate parts of the same file, for example, a
set of declarations and a piece  of  code  that  uses  those  declarations.
Similarly,  it  is often handy to have two different buffers on view in two
windows.

The commands which deal with windows and buffers are:   beginning-of-window
(ESC-,),   delete-other-windows  (^X1),  delete-region-to-buffer  (ESC-^W),
delete-window   (^XD),   end-of-window   (ESC-.),   enlarge-window   (^XZ),
line-to-top-of-window  (ESC-!),  list-buffers  (^X^B),  next-window  (^XN),
page-next-window  (ESC-^V),  previous-window  (^XP),  shrink-window (^X^Z),
split-current-window (^X2), switch-to-buffer (^XB),  use-old-buffer  (^X^O)
and  yank-buffer  (ESC-^Y).    See the command description section for more
details on each of these.
</FoO ThE bAr/>
dbadd info "emacs:track-eol-on-^n-^p" <<"</FoO ThE bAr/>"
Node: track-eol-on-^N-^P		Up: Variables, Previous: this-command, Next: unlink-checkpoint-files

If ON then ^N and ^P will "stick" to the end of a line if they are  started
there.  If OFF ^N and ^P will try to stay in the same column as you move up
and down even if you started at the end of a line.  (default ON)
</FoO ThE bAr/>
dbadd info "emacs:newline-and-indent" <<"</FoO ThE bAr/>"
Node: newline-and-indent		Up: Commands, Previous: newline-and-backup, Next: next-error

Insert  a  newline, just as typing RETURN does, but then insert enough tabs
and spaces so that the newly created line has the same indentation  as  the
old one had.  This is quite useful when you're typing in a block of program
text, all at the same indentation level.
</FoO ThE bAr/>
dbadd info "emacs:indent-c-procedure" <<"</FoO ThE bAr/>"
Node: indent-C-procedure		Up: Commands, Previous: illegal-operation, Next: insert-character

Take the current C procedure and reformat it using the  indent  program,  a
fairly  sophisticated  pretty printer.  Indent-C-procedure is God's gift to
those who don't like  to  fiddle  about  getting  their  formatting  right.
Indent-C-procedure  is usually bound to ESC-J.  When switching from mode to
mode, ESC-J will be bound to procedures appropriate  to  that  mode.    For
example, in text mode ESC-J is bound to justify-paragraph.
</FoO ThE bAr/>
dbadd info "emacs:indent-C-procedure" <<"</FoO ThE bAr/>"
Node: indent-C-procedure		Up: Commands, Previous: illegal-operation, Next: insert-character

Take the current C procedure and reformat it using the  indent  program,  a
fairly  sophisticated  pretty printer.  Indent-C-procedure is God's gift to
those who don't like  to  fiddle  about  getting  their  formatting  right.
Indent-C-procedure  is usually bound to ESC-J.  When switching from mode to
mode, ESC-J will be bound to procedures appropriate  to  that  mode.    For
example, in text mode ESC-J is bound to justify-paragraph.
</FoO ThE bAr/>
dbadd info "emacs:global-mode-string" <<"</FoO ThE bAr/>"
Node: global-mode-string		Up: Variables, Previous: files-should-end-with-newline

Global-mode-string is a global variable used in the  construction  of  mode
lines see section , page 21 for more information.
</FoO ThE bAr/>
dbadd info "emacs:delete-white-space" <<"</FoO ThE bAr/>"
Node: delete-white-space		Up: Commands, Previous: delete-to-killbuffer, Next: delete-window

Deletes all whitespace characters (spaces and tabs) on either side of dot.
</FoO ThE bAr/>
dbadd info "emacs:backward-character" <<"</FoO ThE bAr/>"
Node: backward-character		Up: Commands, Previous: backward-balanced-paren-line, Next: backward-paragraph

Move  dot backwards one character. Ends-of-lines and tabs each count as one
character.  You can't move back to before the beginning of the buffer.
</FoO ThE bAr/>
dbadd info "emacs:return-to-monitor" <<"</FoO ThE bAr/>"
Node: return-to-monitor			Up: Commands, Previous: return-prefix-argument, Next: save-excursion

Recursivly invokes a new shell, allowing the user  to  enter  normal  shell
commands and run other programs.  Return to Emacs by exiting the shell; ie.
by typing ^D.
</FoO ThE bAr/>
dbadd info "emacs:re-replace-string" <<"</FoO ThE bAr/>"
Node: re-replace-string			Up: Commands, Previous: re-query-replace-string, Next: re-search-forward

re-replace-string is identical to replace-string  except  that  the  search
string  is  a  regular  expression rather than an uninterpreted sequence of
characters.  See the section on  searching,  section    page  20  for  more
information.
</FoO ThE bAr/>
dbadd info "emacs:justify-paragraph" <<"</FoO ThE bAr/>"
Node: justify-paragraph			Up: Commands, Previous: is-bound, Next: kill-process

Take the current paragraph (bounded by blank lines or Scribe control lines)
and  pipe  it through the "fmt" command which does paragraph justification.
justify-paragraph is usually bound to ESC-J when in text mode.
</FoO ThE bAr/>
dbadd info "emacs:global-binding-of" <<"</FoO ThE bAr/>"
Node: global-binding-of			Up: Commands, Previous: getenv, Next: goto-character

Returns the name of the procedure to which a keystroke sequence is bound in
the  global  keymap. "nothing" is returned if the sequence is unbound.  The
procedure local-binding-of  performs  a  similar  function  for  the  local
keymap.
</FoO ThE bAr/>
dbadd info "emacs:get-tty-character" <<"</FoO ThE bAr/>"
Node: get-tty-character			Up: Commands, Previous: get-tty-buffer, Next: get-tty-command

Reads  a  single  character from the terminal and returns it as an integer.
The cursor is not moved to the message area, it is left in the text window.
This is useful when  writing  things  like  query-replace  and  incremental
search.
</FoO ThE bAr/>
dbadd info "emacs:forward-character" <<"</FoO ThE bAr/>"
Node: forward-character			Up: Commands, Previous: forward-balanced-paren-line, Next: forward-paragraph

Move  dot  forwards one character. Ends-of-lines and tabs each count as one
character.  You can't move forward to after the end of the buffer.
</FoO ThE bAr/>
dbadd info "emacs:describe-variable" <<"</FoO ThE bAr/>"
Node: describe-variable			Up: Commands, Previous: describe-key, Next: describe-word-in-buffer

Uses the Info system to describe some named variable.  You will be prompted
in  the minibuf for the name of a variable and then Info will be invoked to
show you the manual entry describing it.  You can then use Info  to  browse
around, or simply type ^C to resume editing.
</FoO ThE bAr/>
dbadd info "emacs:current-file-name" <<"</FoO ThE bAr/>"
Node: current-file-name			Up: Commands, Previous: current-column, Next: current-indent

MLisp function that returns the  file  name  associated  with  the  current
buffer  as  a string.  If there is no associated file name, the null string
is returned.
</FoO ThE bAr/>
dbadd info "emacs:backward-sentence" <<"</FoO ThE bAr/>"
Node: backward-sentence			Up: Commands, Previous: backward-paren, Next: backward-word

Move dot backward to the beginning of the preceeding sentence; if dot is in
the  middle  of  a sentence, move to the beginning of the current sentence.
Sentences are seperated by a `.', `?' or `!' followed by whitespace.
</FoO ThE bAr/>
dbadd info "emacs:switch-to-buffer" <<"</FoO ThE bAr/>"
Node: switch-to-buffer			Up: Commands, Previous: substr, Next: system-name

Prompt for the name of the buffer and associate it with the current window.
The  old  buffer associated with this window merely loses that association:
it is not erased or changed in any way.  If the new buffer does not  exist,
it will be created, in contrast with ^X^O.
</FoO ThE bAr/>
dbadd info "emacs:region-to-string" <<"</FoO ThE bAr/>"
Node: region-to-string			Up: Commands, Previous: region-to-process, Next: remove-all-local-bindings

Returns the region between dot and mark as a string.  Please be kind to the
storage allocator, don't use huge strings.
</FoO ThE bAr/>
dbadd info "emacs:read-abbrev-file" <<"</FoO ThE bAr/>"
Node: read-abbrev-file			Up: Commands, Previous: re-search-reverse, Next: read-file

Read  in  and  define  abbrevs appearing in a named file.  This file should
have been written using write-abbrev-file.  An error message is printed  if
the file cannot be found.
</FoO ThE bAr/>
dbadd info "emacs:insert-character" <<"</FoO ThE bAr/>"
Node: insert-character			Up: Commands, Previous: indent-C-procedure, Next: insert-file

Inserts  its  numeric  argument  into  the  buffer  as  a single character.
(insert-character '0') inserts the character '0' into the buffer.
</FoO ThE bAr/>
dbadd info "emacs:delete-next-word" <<"</FoO ThE bAr/>"
Node: delete-next-word			Up: Commands, Previous: delete-next-character, Next: delete-other-windows

Delete characters forward from dot until the next end of a word.  If dot is
currently not in a word, all punctuation up to the beginning of the word is
deleted as well as the word.
</FoO ThE bAr/>
dbadd info "emacs:temp-use-buffer" <<"</FoO ThE bAr/>"
Node: temp-use-buffer			Up: Commands, Previous: system-name, Next: to-col

Switch  to  a  named  buffer  without  changing  window  associations.  The
commands pop-to-buffer and switch-to-buffer both cause a window to be  tied
to  the  selected  buffer, temp-use-buffer does not.  There are a couple of
problems that you must beware  when  using  this  command:    The  keyboard
command  driver  insists  that the buffer tied to the current window be the
current buffer, if it sees a difference then it changes the current  buffer
to  be the one tied to the current window.  This means that temp-use-buffer
will be ineffective from the  keyboard,  switch-to-buffer  should  be  used
instead.  The other problem is that "dot" is really a rather funny concept.
There  is  a  value  of  "dot"  associated  with each window, not with each
buffer.  This is done so that there is a valid interpretation to having the
same buffer visible in several windows.  There is also  a  value  of  "dot"
associated  with  the  current  buffer.    When you switch to a buffer with
temp-use-buffer, this "transient dot" is what gets used.  So, if you switch
to another buffer, then use temp-use-buffer to get back,  "dot"  will  have
been set to 1.  You can use save-excursion to remember your position.
</FoO ThE bAr/>
dbadd info "emacs:quote-character" <<"</FoO ThE bAr/>"
Node: quote-character			Up: Commands, Previous: quote, Next: re-query-replace-string

Insert  into the buffer the next character typed without interpreting it as
a command.  This is how you insert  funny  characters.    For  example,  to
insert  a  ^L  (form  feed or page break character) type ^Q^L.  This is the
only situation where ^G isn't interpreted as an abort character.
</FoO ThE bAr/>
dbadd info "emacs:quick-redisplay" <<"</FoO ThE bAr/>"
Node: quick-redisplay			Up: Variables, Previous: prefix-string, Next: replace-case

If  ON  Emacs  won't  worry  so much about the case where you have the same
buffer on view in several windows --  it  may  let  the  other  windows  be
inaccurate  for  a  short  while  (but  they  will eventually be fixed up).
Turning this ON speeds up Emacs substantially when the same  buffer  is  on
view  in several windows.  When it is OFF, all windows are always accurate.
(default OFF)
</FoO ThE bAr/>
dbadd info "emacs:last-key-struck" <<"</FoO ThE bAr/>"
Node: last-key-struck			Up: Commands, Previous: kill-to-end-of-line, Next: length

The  last  command  character struck.  If you have a function bound to many
keys the function may use last-key-struck to tell which  key  was  used  to
invoke it.  (insert-character (last-key-struck)) does the obvious thing.
</FoO ThE bAr/>
dbadd info "emacs:current-process" <<"</FoO ThE bAr/>"
Node: current-process			Up: Commands, Previous: current-indent, Next: current-time

(current-process)  -- Returns the name of the current process as defined in
the section describing the process mechanism.
</FoO ThE bAr/>
dbadd info "dir:operating systems" <<"</FoO ThE bAr/>"
Node: operating systems		Up: Top

There's a patch of old snow in a corner,
   That I should have guessed
 Was a blow-away paper the rain
   Had brought to rest.

 It is speckled with grime as if
   Small print overspread it,
 The news of a day I've forgotten --
   If I ever read it.

			-- Robert Frost
			   "A patch of old snow"

	This node needs a volunteer to finish writing it!
</FoO ThE bAr/>
dbadd info "emacs:use-global-map" <<"</FoO ThE bAr/>"
Node: use-global-map			Up: Commands, Previous: use-abbrev-table, Next: use-local-map

(use-global-map "mapname") uses the named map to be  used  for  the  global
interpretation  of  all  key  strokes.  use-local-map is used to change the
local interpretation of key strokes. See the section on keymaps,  page  21,
for more information.
</FoO ThE bAr/>
dbadd info "emacs:the killbuffer" <<"</FoO ThE bAr/>"
File: emacs     Node: The Killbuffer     Up: Commands

	This node needs a volunteer to finish writing it!
</FoO ThE bAr/>
dbadd info "emacs:string-to-char" <<"</FoO ThE bAr/>"
Node: string-to-char			Up: Commands, Previous: stop-remembering, Next: string-to-process

Returns  the  integer  value of the first character of its string argument.
(string-to-char "0") = '0'.
</FoO ThE bAr/>
dbadd info "emacs:search-forward" <<"</FoO ThE bAr/>"
Node: search-forward			Up: Commands, Previous: scroll-one-line-up, Next: search-reverse

Prompt  for  a  string and search for a match in the current buffer, moving
forwards from dot, stopping at the end of the buffer.  Dot is left  at  the
end  of  the matched string if a match is found, or is unmoved if not.  See
the section on searching, section  page 20 for more information.
</FoO ThE bAr/>
dbadd info "emacs:redraw-display" <<"</FoO ThE bAr/>"
Node: redraw-display			Up: Commands, Previous: recursive-edit, Next: region-around-match

Clear  the  screen  and  rewrite  it.   This is useful if some transmission
glitch, or a message from a friend, has messed up the screen.
</FoO ThE bAr/>
dbadd info "emacs:recursive-edit" <<"</FoO ThE bAr/>"
Node: recursive-edit			Up: Commands, Previous: recursion-depth, Next: redraw-display

The   recursive-edit   function    is    a    call    on    the    keyboard
read/interpret/execute  routine.    After recursive-edit is called the user
can enter commands from the keyboard as usual, except that  when  he  exits
Emacs  by  calling exit-emacs (typing ^C) it actually returns from the call
to recursive-edit.  This function is handy for packages that  want  to  pop
into  some  state,  let  the  user  do some editing, then when they're done
perform some cleanup and let the user resume.  For example, a  mail  system
could use this for message composition.
</FoO ThE bAr/>
dbadd info "emacs:process-status" <<"</FoO ThE bAr/>"
Node: process-status			Up: Commands, Previous: process-output, Next: progn

(process-status  "process-name")  --  Returns  -1 if "process-name" isn't a
process, 0 if the process is stopped, and 1 if the process is running.
</FoO ThE bAr/>
dbadd info "emacs:process-output" <<"</FoO ThE bAr/>"
Node: process-output			Up: Commands, Previous: process-id, Next: process-status

(process-output)  --  Can  only  be  called  by  the on-output-procedure to
procure the output  generated  by  the  process  whose  name  is  given  by
MPX-process. Returns the output as a string.
</FoO ThE bAr/>
dbadd info "emacs:get-tty-string" <<"</FoO ThE bAr/>"
Node: get-tty-string			Up: Commands, Previous: get-tty-command, Next: get-tty-variable

Reads  a  string  from the terminal using its single string parameter for a
prompt.  Generally used inside MLisp programs to ask questions.
</FoO ThE bAr/>
dbadd info "emacs:declare-global" <<"</FoO ThE bAr/>"
Node: declare-global			Up: Commands, Previous: declare-buffer-specific, Next: define-buffer-macro

Takes  a  list of variables and for each that is not already bound a global
binding is created.  Global bindings outlive all function calls.
</FoO ThE bAr/>
dbadd info "emacs:comment-column" <<"</FoO ThE bAr/>"
Node: comment-column			Up: Variables, Previous: checkpoint-frequency, Next: ctlchar-with-^

The column at which comments are to start.  Used by the  language-dependent
commenting  features  through the move-to-comment-column command.  (default
33)
</FoO ThE bAr/>
dbadd info "emacs:Terminal types" <<"</FoO ThE bAr/>"
Node: Terminal types			Up: Basics, Previous: Buffers and Windows, Next: Compiling programs

Grim reality being what it is, Emacs has to deal with a wide assortment  of
displays  from  many  manufacturers.    Each  manufacturer  has  their  own
perverted idea of how programs should communicate with the display,  so  it
is  important for Emacs to correctly be told what type of terminal is being
used.  Under Unix, this is done by setting the environment variable `TERM'.
Normally, the operating system should set this to correspond to the type of
terminal that you are using and you won't have to concern yourself with it.
However, problems may arise and there are a  few  things  that  you  should
know.

`TERM' is a string variable whose value is the name of the type of terminal
that  you  are  using.    If  you are using the standard Unix shell then it
should be set using the commands:  

    TERM=...
    export TERM

If you're using the C shell (csh) then it should be set using the  command:


    setenv TERM ...

where  `...'  is  the  appropriate  terminal  type.    Consult  your system
administrator for a current list of valid terminal types.  A good place  to
look  is the file ``/etc/termcap'', it contains a list of all the terminals
supported by Emacs.  A few of the more common values are:

concept-lnz     For Concepts with the special firmware for Emacs.
concept         Concept 100, 104 and 108's from HDS.
h19             For Heathkit or Zenith model 19 terminals.
vt100           For  VT100's  from  DEC,  or  any  of  the   thousands   of
                look-alikes.
aaa             For the Ann Arbor Ambassador.

</FoO ThE bAr/>
dbadd info "emacs:summary table" <<"</FoO ThE bAr/>"
File: emacs     Node: summary table     Up: Moving around

This table summarises the Emacs commands for moving the cursor.  It's laid
out so that the symmetry of the commands should be apparent.




                                  ^P	Previous line
                                  |
<-- ESC-A <-- ^A <-- ESC-B <-- ^B + ^F --> ESC-F --> ^E --> ESC-E -->
     Beginning      Backward      |       Forward      End
   Sentence  Line    Words    Characters   Words     Line  Sentence
                                  |
                                  ^N	Next line
</FoO ThE bAr/>
dbadd info "emacs:shrink-window" <<"</FoO ThE bAr/>"
Node: shrink-window			Up: Commands, Previous: shell, Next: sit-for

Makes the current window one line shorter, and the window below (or the one
above if there is no window below) one line taller.  Can't be used if there
is only one window on the screen.
</FoO ThE bAr/>
dbadd info "emacs:previous-line" <<"</FoO ThE bAr/>"
Node: previous-line			Up: Commands, Previous: previous-command, Next: previous-page

Move dot to the previous line.  ^N and ^P attempt to keep dot at  the  same
horizontal position as you move from line to line.
</FoO ThE bAr/>
dbadd info "emacs:insert-filter" <<"</FoO ThE bAr/>"
Node: insert-filter			Up: Commands, Previous: insert-file, Next: insert-string

Insert a filter-procedure between a process and Emacs. This function should
subsume the start-filtered-process function, but we should retain that  one
for compatibility I suppose...
</FoO ThE bAr/>
dbadd info "emacs:extensibility" <<"</FoO ThE bAr/>"
Node: Extensibility                               Up: Basics, Prev: Abbrev mode, Next: Searching

Unix Emacs has two extension features: macros and a built in  Lisp  system.
Macros  are  used  when  you have something quick and simple to do, Lisp is
used when you want  to  build  something  fairly  complicated  like  a  new
language  dependant  mode.    A  macro  is  just a piece of text that Emacs
remembers in a special way.  When a macro is executed the  characters  that
make  up  the  macro  are  treated  as  though  they  had been typed at the
keyboard.  If you have some common sequence of keystrokes you can define  a
macro  that contains them and instead of retyping them just call the macro.
There are two ways of defining macros:

The easiest is called a keyboard macro.  A keyboard  macro  is  defined  by
typing  the  start-remembering command (^X() then typing the commands which
you want to have saved (which will be executed as you type them so that you
can make sure that they are right) then typing the stop-remembering command
(^X)).  To execute the keyboard macro just type the  execute-keyboard-macro
command  (^Xe).    You  can only have one keyboard macro at a time.  If you
define a new keyboard macro the old keyboard macro vanishes into the mist.

Named macros are slightly more complicated.  They  have  names,  just  like
commands and MLisp functions and can be called by name (or bound to a key).
They  are  defined  by using the define-string-macro command (which must be
executed by typing ESC-Xdefine-string-macro since it isn't usually bound to
a key) which asks for the name of the macro and it's body.    The  body  is
typed  in  as  a string in the prompt area at the bottom the the screen and
hence all special characters in it must be quoted by  prefixing  them  with
^Q.    A  named  macro  may  be executed by typing ESC-Xname-of-macro or by
binding it to a key with bind-to-key.

The current keyboard macro can be converted into a named macro by using the
define-keyboard-macro command which takes a name a defines a macro by  that
name  whose body is the current keyboard macro.  The current keyboard macro
ceases to exist.



    MLisp
    -----

Unix Emacs contains an interpreter for a language that in many  respects
resembles  Lisp.    The  primary  (some  would  say   only) resemblance
between Mock Lisp and any real Lisp is the general syntax of a program,
which many feel is Lisp's weakest point.  The differences  include such
things as the lack of a cons function and a rather peculiar method of
passing parameters.

    The syntax of MLisp expressions

There are four basic syntactic entities out of which MLisp expressions  are
built.  The two simplest are integer constants (which are optionally signed
strings of digits) and string constants (which are sequences of  characters
bounded by double quote [``"''] characters -- double quotes are included by
doubling  them:  """"  is a one character string. The third are names which
are used to refer to things: variables or procedures.  These three are  all
tied  together  by the use of procedure calls.  A procedure call is written
as a left parenthesis, ``('', a name which refers to the procedure, a  list
of whitespace separated expressions which serve as arguments, and a closing
right  parenthesis,  ``)''.    An  expression  is  simply one of these four
things: an integer constant, a string constant, a name, or a call which may
itself be recursivly composed of other expressions.

String constants may contain the  usual  C  excape  sequences,  "\n"  is  a
newline,  "\t"  is  a  tab, "\r" is a carriage return, "\b" is a backspace,
"\e" is the escape (033) character, "\nnn" is  the  character  whose  octal
representation is nnn, and "^\c" is the control version of the character c.

For example, the following are legal MLisp expressions:

1               The integer constant 1.

"hi"            A two character string constant

"\^X\^F"        A two character string constant

"""what?"""     A seven character string constant

(+ 2 2)         An  invocation of the "+" function with integer arguments 2
                and  2.    "+"  is  the  usual  addition  function.    This
                expression evaluates to the integer 4.

(setq bert (* 4 12))
                An  invocation  of the function setq with the variable bert
                as its first argument and and expression that evaluates the
                product of 4 and 12 as its second argument.  The evaluation
                of  this  expression assigns the integer 48 to the variable
                bert.

(visit-file "mbox")
                An invocation of the function visit-file  with  the  string
                "mbox"  as  its  first  argument.   Normally the visit-file
                function is tied to the key  ^X^B.    When  it  is  invoked
                interactively, either by typing ^X^B or ESC-Xvisit-file, it
                will  prompt in the minibuf for the name of the file.  When
                called from MLisp it takes the file name from the parameter
                list.  All of the keyboard-callable  function  behave  this
                way.

Names  may contain virtually any character, except whitespace or parens and
they cannot begin with a digit, ``"'' or ``-''.

    The evaluation of MLisp expressions

Variables  must  be  declared  (bound)  before  they  can  be  used.    The
declare-global command can be used to declare a global variable; a local is
declared  by listing it at the beginning of a progn or a function body (ie.
immediatly after the function  name  or  the  word  progn  and  before  the
executable statements).  For example:

    (defun
        (foo i
            (setq i 5)
        )
    )

defines  a  rather  pointless  function  called foo which declares a single
local variable i and assigns it the value 5.  Unlike real Lisp systems, the
list of declared variables is not surrounded by parenthesis.

Expressions evaluate  to  values  that  are  either  integers,  strings  or
markers.    Integers  and strings are converted automaticly from one to the
other type as needed: if a function requires an integer parameter  you  can
pass  it  a  string and the characters that make it up will be parsed as an
integer; similarly passing an integer where a string is required will cause
the integer to be converted.  Variables may have either type and their type
is decided dynamically when the assignment is made.

Marker values indicate a position in a buffer.  They are  not  a  character
number.    As  insertions  and deletions are performed in a buffer, markers
automatically follow along, maintaining their position.  Only the functions
mark and dot return markers; the user may  define  ones  that  do  and  may
assign  markers  to  variables.    If  a  marker  is used in a context that
requires an integer value then the  ordinal  of  the  position  within  the
buffer  is  used;  if  a marker is used in a context that requires a string
value then the name of the marked buffer is used.  For  example,  if  there
has  been  assigned some marker, then (pop-to-buffer there) will pop to the
marked buffer.  (goto-character there) will set dot to the marked position.

A procedure written in MLisp is simply an expression that  is  bound  to  a
name.   Invoking the name causes the associated expression to be evaluated.
Invocation may be triggered either by the  evaluation  of  some  expression
which  calls  the  procedure,  by  the  user  typing it's name to the ESC-X
command, or by striking a key to which the procedure name has been bound.

All  of  the  commands   listed   in   section   COMMANDDESCRIPTION   (page
COMMANDDESCRIPTION) may be called as MLisp procedures.  Any parameters that
they  normally prompt the user for are taken as string expressions from the
argument list in the same order as they are asked for  interactivly.    For
example,  the  switch-to-buffer  command, which is normally tied to the ^XB
key, normally prompts for a buffer name and may be called from  MLisp  like
this:  (switch-to-buffer string-expression).

    Scope issues

There  are  several  sorts  of  names  that  may  appear in MLisp programs.
Procedure, buffer and abbrev table names are all global and occupy distinct
name space. For variables there are three cases:

   1. Global variables: these variables have a single instance and are
      created  either  by   using   declare-global,   set-default   or
      setq-default.  Their lifetime is the entire editing session from
      the time they are created.

   2. Local  variables: these have an instance for each declaration in
      a procedure body or local block (progn).  Their lifetime is  the
      lifetime  of  the block which declares them.  Local declarations
      nest and hide inner local or global declarations.

   3. Buffer-specific variables: these have a default instance and  an
      instance  for  each  buffer  in  which they have been explicitly
      given   a    value.        They    are    created    by    using
      declare-buffer-specific.     When  a  variable  which  has  been
      declared to be buffer  specific  is  assigned  a  value,  if  an
      instance for the current buffer hasn't been created then it will
      be.    The value is assigned to the instance associated with the
      current buffer.  If a buffer specific variable is referenced and
      an instance doesn't exist for this buffer then the default value
      is used.  This default value may be set with either setq-default
      or set-default.  If a global instance exists when a variable  is
      declared  buffer-specific  then  the  global  value  becomes the
      default.

    MLisp functions

An MLisp function is defined by executing the defun function.  For example:


    (defun
        (silly
            (insert-string "Silly!")
        )
    )

defines a function called silly  which,  when  invoked,  just  inserts  the
string "Silly!" into the current buffer.

MLisp  has a rather strange (relative to other languages) parameter passing
mechanism.  The arg function, invoked as (arg i prompt) evaluates the  i'th
argument  of  the  invoking  function  if  the invoking function was called
interactivly or, if the invoking function was not called interactivly,  arg
uses the prompt to ask you for the value.  Consider the following function:

    (defun
        (in-parens
            (insert-string "(")
            (insert-string (arg 1 "String to insert? "))
            (insert-string ")")
        )
    )

If you type ESC-Xin-parens to invoke in-parens interactivly then Emacs will
ask in the minibuffer "String to insert? " and then insert the string typed
into the current buffer surrounded by parenthesis.  If in-parens is invoked
from  an  MLisp  function  by  (in-parens "foo") then the invocation of arg
inside in-parens will evaluate the expression "foo" and the end result will
be that the string "(foo)" will be inserted into the buffer.

The function interactive may be  used  to  determine  whether  or  not  the
invoking function was called interactivly.  Nargs will return the number of
arguments passed to the invoking function.

This  parameter passing mechanism may be used to do some primitive language
extension.  For  example,  if  you  wanted  a  statement  that  executed  a
statement n times, you could use the following:

    (defun
        (dotimes n
            (setq n (arg 1))
            (while (> n 0)
                (setq n (- n 1))
                (arg 2)
            )
        )
    )

Given  this,  the  expression (dotimes 10 (insert-string "<>")) will insert
the string "<>" 10 times.  [Note: The prompt argument may be omitted if the
function can never be called interactivly] .

    Debugging

Unfortunatly, debugging MLisp functions is something of a black art.    The
biggest  problem  right  now  is  that  if  an  MLisp function goes into an
infinite loop there is no way to stop it.

There is no breakpoint facility.  All that you can do is get a stack  trace
whenever  an  error  occurs  by  setting the stack-trace-on-error variable.
With this set, any time that an error occurs a dump of the MLisp  execution
call  stack  and  some  other  information  is  dumped to the "Stack trace"
buffer.

The following piece of MLisp code  is  the  Scribe  mode  package.    Other
implementations  of  Emacs, on ITS and on Multics have modes that influence
the behaviour of Emacs on a file.  This behaviour is usually some  sort  of
language-specific  assistance.   In Unix Emacs a mode is no more that a set
of functions, variables and key-bindings.  This mode package is designed to
be useful when editing Scribe source files.

(defun
                    The apply-look  function  makes  the  current  word
                    "look"  different  by  changing the font that it is
                    printed in.  It positions dot at the  beginning  of
                    the  word  so  you can see where the change will be
                    made and reads a character from the tty.   Then  it
                    inserts  "@c["  (where c is the character typed) at
                    the  front  of  the  word  and  "]"  at  the  back.
                    Apply-look  gets  tied  to  the key ESC-l so typing
                    ESC-l i when the cursor is positioned on  the  word
                    "begin" will change the word to "@i[begin]".
    (apply-look go-forward
        (save-excursion c
            (if (! (eolp)) (forward-character))
            (setq go-forward -1)
            (backward-word)
            (setq c (get-tty-character))
            (if (> c ' ')
                (progn (insert-character '@')
                    (insert-character c)
                    (insert-character '[')
                    (forward-word)
                    (setq go-forward (dot))
                    (insert-character ']')
                )
            )
        )
        (if (= go-forward (dot)) (forward-character))
    )
)

(defun
                    This function is called to set a buffer into Scribe
                    mode
    (scribe-mode
        (remove-all-local-bindings)
                    If the string "LastEditDate=""" exists in the first
                    2000  characters of the document then the following
                    string constant is changed  to  the  current  date.
                    The  intent of this is that you should stick at the
                    beginning   of   your    file    a    line    like:
                    ``@string(LastEditDate="Sat Jul 11 17:59:01 1981")''.
                    This  will  automatically get changed each time you
                    edit the file to reflect that last  date  on  which
                    the file was edited.
        (if (! buffer-is-modified)
            (save-excursion
                (error-occurred
                    (goto-character 2000)
                    (search-reverse "LastEditDate=""")
                    (search-forward """")
                    (set-mark)
                    (search-forward """")
                    (backward-character)
                    (delete-to-killbuffer)
                    (insert-string (current-time))
                    (setq buffer-is-modified 0)
                )
            )
        )
        (local-bind-to-key "justify-paragraph" "\ej")
        (local-bind-to-key "apply-look" "\el")
        (setq right-margin 77)
        (setq mode-string "Scribe")
        (setq case-fold-search 1)
        (use-syntax-table "text-mode")
        (modify-syntax-entry "w    -'")
        (use-abbrev-table "text-mode")
        (setq left-margin 1)
        (novalue)
    )
)

(novalue)

When  Emacs  is  invoked,  it  does several things that are not of too much
interest to the beginning user.

   1. Emacs looks for  a  file  called  ``.emacs pro''  in  your  home
      directory,  if  it  exists  then  it  is  loaded,  with the load
      command.  This is the mechanism used for  user  profiles  --  in
      your  .emacs pro  file,  place  the commands needed to customize
      Emacs to suit your  taste.    If  a  user  has  not  set  up  an
      .emacs pro file then Emacs will use a site-specific default file
      for    initialization.       At   CMU   this   file   is   named
      /usr/local/lib/emacs/maclib/profile.ml

   2. Emacs  will  then  interprete   its   command   line   switches.
      "-l<filename>"  loads  the  given  file (only one may be named),
      "-e<funcname>" executes the named function (again, only one  may
      be named).  -l and -e are executed in that order, after the user
      profile  is  read, but before and file visits are done.  This is
      intended to be used along with the csh alias mechanism to  allow
      you  to  invoke Emacs packages from the shell (that is, assuming
      that there is anyone out there who  still  uses  the  shell  for
      anything  other  than  to run under Emacs!). For example: "alias
      rmail emacs -lrmail -ermail-com"  will  cause  the  csh  "rmail"
      command  to invoke Emacs running rmail.  Exiting rmail will exit
      Emacs.

   3. If neither argv nor argc have  yet  been  called  (eg.  by  your
      startup  or  by the command line named package) then the list of
      arguments will be considered as file names and will be  visited;
      if  there are no arguments then the arguments passed to the last
      invocation of Emacs will be used.

   4. Finally, Emacs invokes it's keyboard  command  interpreter,  and
      eventually terminates.

</FoO ThE bAr/>
dbadd info "emacs:emacs-version" <<"</FoO ThE bAr/>"
Node: emacs-version			Up: Commands, Previous: edit-macro, Next: end-of-file

Returns a string that describes the current Emacs version.
</FoO ThE bAr/>
dbadd info "emacs:window moves" <<"</FoO ThE bAr/>"
File: emacs     Node: window moves     Up: Moving around

* menu:
* beginning-of-window::			(ESC-,)
* end-of-window::			(ESC-.)
* line-to-top-of-window::		(ESC-!)
* next-window::				(^X-n)
* page-next-window::			(ESC-^V)
* previous-window::			(^X-p)
</FoO ThE bAr/>
dbadd info "emacs:widen-region" <<"</FoO ThE bAr/>"
Node: widen-region			Up: Commands, Previous: while, Next: window-height

The widen-region command sets  the  restriction  to  encompass  the  entire
buffer.    It  is  usualy  used  after  a  narrow-region to restore Emacs's
attention to the whole buffer.
</FoO ThE bAr/>
dbadd info "emacs:this-command" <<"</FoO ThE bAr/>"
Node: this-command			Up: Variables, Previous: tab-size, Next: track-eol-on-^N-^P

The meaning of the variable this-command is tightly  intertwined  with  the
meaning  of the function previous-command.  Look at its documentation for a
description of this-command.
</FoO ThE bAr/>
dbadd info "emacs:subprocesses" <<"</FoO ThE bAr/>"
File: emacs     Node: Subprocesses     Up: Commands

	This node needs a volunteer to finish writing it!
</FoO ThE bAr/>
dbadd info "emacs:right-margin" <<"</FoO ThE bAr/>"
Node: right-margin			Up: Variables, Previous: replace-case, Next: scroll-step

The right margin for automatic text  justification.    If  a  character  is
inserted  at  the  end of a line and to the right of the right margin Emacs
will automatically insert at the beginning of the preceding word a newline,
tabs and spaces to indent to the left margin, and the prefix string.   With
the  right  margin  set  to  something  like (for eg.) 72 you can type in a
document without worrying about when to hit  the  return  key,  Emacs  will
automatically do it for you at exactly the right place.
</FoO ThE bAr/>
dbadd info "emacs:replace-case" <<"</FoO ThE bAr/>"
Node: replace-case			Up: Variables, Previous: quick-redisplay, Next: right-margin

If ON Emacs will alter the case of strings substituted with  replace-string
or  query-replace-string  to  match  the  case of the original string.  For
example, replacing "which" by "that" in the string "Which is silly" results
in "That is silly"; in the string "the car which is red"  results  in  "the
car  that  is  red";  and  in  the  string "WHICH THING?"  results in "THAT
THING?".
</FoO ThE bAr/>
dbadd info "emacs:quit-process" <<"</FoO ThE bAr/>"
Node: quit-process			Up: Commands, Previous: quietly-read-abbrev-file, Next: quote

(quit-process "process-name") -- Send a quit signal to the process.
</FoO ThE bAr/>
dbadd info "emacs:kill-process" <<"</FoO ThE bAr/>"
Node: kill-process			Up: Commands, Previous: justify-paragraph, Next: kill-to-end-of-line

(kill-process "process-name") -- Send a kill signal to the process.
</FoO ThE bAr/>
dbadd info "emacs:describe-key" <<"</FoO ThE bAr/>"
Node: describe-key			Up: Commands, Previous: describe-command, Next: describe-variable

Describe  the  given  key.    ESC-Xdescribe-key  ESC-X  will  print a short
descrition of the ESC-X key.  It tells you the name of the command to which
the  key  is  bound.    To  find  out   more   about   the   command,   use
describe-command.
</FoO ThE bAr/>
dbadd info "emacs:current-time" <<"</FoO ThE bAr/>"
Node: current-time			Up: Commands, Previous: current-process, Next: declare-buffer-specific

MLisp function that returns the current time of day  as  a  string  in  the
format  described in CTIME(3), with the exception that the trailing newline
will have been stripped off.  (substr (current-time) -4 4) is  the  current
year.
</FoO ThE bAr/>
dbadd info "emacs:writeregion" <<"</FoO ThE bAr/>"
Node: writeregion			Up: Packages, Previous: undo

This package only  implements  one  function,  write-region-to-file,  which
takes the region between dot and mark and writes it to the named file.
</FoO ThE bAr/>
dbadd info "emacs:scroll-step" <<"</FoO ThE bAr/>"
Node: scroll-step			Up: Variables, Previous: right-margin, Next: silently-kill-processes

The  number of lines by which windows are scrolled if dot moves outside the
window. If dot has moved more than scroll-step lines outside of the  window
or  scroll-step  is zero then dot is centered in the window.  Otherwise the
window is moved up or down scroll-step lines.   Setting  scroll-step  to  1
will  cause  the  window to scroll by 1 line if you're typing at the end of
the window and hit RETURN.
</FoO ThE bAr/>
dbadd info "emacs:mice     up" <<"</FoO ThE bAr/>"
File: emacs     Node: Mice     Up     Up: Mice

[body]

* menu:
</FoO ThE bAr/>
dbadd info "emacs:insert-file" <<"</FoO ThE bAr/>"
Node: insert-file			Up: Commands, Previous: insert-character, Next: insert-filter

Prompt for the name of a file and insert its contents at dot in the current
buffer.
</FoO ThE bAr/>
dbadd info "emacs:eot-process" <<"</FoO ThE bAr/>"
Node: eot-process			Up: Commands, Previous: eolp, Next: erase-buffer

(eot-process "process-name") -- Send an EOT to the process.
</FoO ThE bAr/>
dbadd info "macro operations" <<"</FoO ThE bAr/>"
Node: Macro Operations			Next: Compiling (Make) Operations.

* start-remembering::         ^X-( Start remembering keystrokes, ie.  start
                                   defining a keyboard macro
* stop-remembering::          ^X-) Stop remembering keystrokes, ie. end the
                                   definition
* execute-keyboard-macro::    ^X-e Execute   remembered   keystrokes,   ie.
                                   execute the keyboard macro
</FoO ThE bAr/>
dbadd info "emacs:visit-file" <<"</FoO ThE bAr/>"
Node: visit-file			Up: Commands, Previous: users-login-name, Next: while

Visit-file  asks  for  the  name  of  a  file and switches to a buffer that
contains it.  The file name is expanded to it's full  absolute  form  (that
is, it will start with a '/').  If no buffer contains the file already then
Emacs  will  switch to a new buffer and read the file into it.  The name of
this new  buffer  will  be  just  the  last  component  of  the  file  name
(everything  after the last '/' in the name).  If there is already a buffer
by that name, and it contains some other file, then Emacs will ask "Enter a
new buffer name or <CR> to overwrite the old buffer".  For example,  if  my
current  directory  is  "/usr/jag/emacs" and I do a ^X^V and give Emacs the
file  name  "../.emacs pro"then  the  name  of  the  new  buffer  will   be
".emacs pro"  and  the file name will be "/usr/jag/.emacs pro". ^X^V is the
approved way of switching from one file to another within an invocation  of
Emacs.
</FoO ThE bAr/>
dbadd info "emacs:process-id" <<"</FoO ThE bAr/>"
Node: process-id			Up: Commands, Previous: process-filter-name, Next: process-output

Returns the process id of the process attached to some buffer.
</FoO ThE bAr/>
dbadd info "emacs:mode lines" <<"</FoO ThE bAr/>"
Node: Mode Lines			Up: Basics, Previous: Region Restrictions

A  mode  line  is  the  line  of descriptive text that appears just below a
window on the screen.  It usually provides a description of  the  state  of
the  buffer  and is usually shown in reverse video.  The standard mode line
shows the name of the buffer, an `*' if the buffer has been  modified,  the
name  of  the  file associated with the buffer, the mode of the buffer, the
current position of dot within the buffer expressed as a percentage of  the
buffer size and and indication of the nesting within recursive-edit's which
is  shown  by  wrapping  the  mode line in an appropriate number of `[' `]'
pairs.

It is often the case that for some silly or practical reason one  wants  to
alter  the  layout  of  the  mode  line,  to  show  more, less or different
information.  Emacs has a fairly general facility for  doing  this.    Each
buffer  has associated with it a format string that describes the layout of
the mode line for that buffer whenever it appears in a window.  The  format
string  is  interpreted  in a manner much like the format argument to the C
printf subroutine.  Unadorned characters appear in the mode line unchanged.
The `%' character and the following format designator character cause  some
special  string  to  appear  in  the  mode line in their place.  The format
designators are:

b               Inserts the name of the buffer.
f               Inserts the name of the file associated with the buffer.
m               Inserts  the  value   of   the   buffer-specific   variable
                mode-string.
M               Inserts the value of the variable global-mode-string.
p               Inserts the position of "dot" as a percentage.
*               Inserts an `*' if the buffer has been modified.
[               Inserts (recursion-depth) `['s.
]               Inserts (recursion-depth) `]'s.

If  a  number  n appears between the `%' and the format designator then the
inserted string is constrained to be exactly n characters wide.  Either  by
padding or truncating on the right.

At CMU the default mode line is built using the following format:  

    " %[Buffer: %b%*  File: %f  %M (%m)  %p%]"

The following variables are involved in generating mode lines:

mode-line-format
                This  is  the  buffer  specific  variable that provides the
                format of a buffers mode line.

default-mode-line-format
                This is the value to which mode-line-format is  initialized
                when a buffer is created.

mode-string     This  buffer-specific  string variable can be inserted into
                the mode line by using `%m' in the format.   This  is  it's
                only   use   by   Emacs.    Usually,  mode  packages  (like
                `lisp-mode' or `c-mode') put some string  into  mode-string
                to  indicate  the mode of the buffer.  It is the appearance
                of this piece of descriptive  information  that  gives  the
                mode line its name.

global-mode-string
                This  is  similar  to  mode-string except that it is global
                -- the same string will be inserted into all mode lines  by
                `%M'.    It  is  usually  used  for  information  of global
                interest.  For example, the time package puts  the  current
                time of day and load average there.

</FoO ThE bAr/>
dbadd info "emacs:exit-emacs" <<"</FoO ThE bAr/>"
Node: exit-emacs			Up: Commands, Previous: exit-emacs, Next: expand-file-name

Exit  Emacs.    Will  ask if you're sure if there are any buffers that have
been modified but not written out.
</FoO ThE bAr/>
dbadd info "emacs:edit-macro" <<"</FoO ThE bAr/>"
Node: edit-macro			Up: Commands, Previous: dump-syntax-table, Next: emacs-version

Take the body of the named macro and place it  in  a  buffer  called  Macro
edit.    The name of the macro is associated with the buffer and appears in
the information bar at the bottom of the window.  The buffer may be  edited
just like any other buffer (this is, in fact, the intent).  After the macro
body has been edited it may be redefined using define-buffer-macro.
</FoO ThE bAr/>
dbadd info "emacs:checkpoint" <<"</FoO ThE bAr/>"
Node: checkpoint			Up: Commands, Previous: char-to-string

Causes  all  modified  buffers  with  an  out of date checkpoint file to be
checkpointed.    This  function  is  normally  called  automatically  every
checkpoint-frequency keystrokes.
</FoO ThE bAr/>
dbadd info "emacs:The Screen" <<"</FoO ThE bAr/>"
Node: The Screen			Up: Basics, Next: Input Conventions

Emacs  divides a screen into several areas called windows, at the bottom of
the screen there is a one line area that is used for messages and questions
from Emacs.  Most people will only be using one window, at least until they
become more familiar with Emacs.  A window is displayed as a set of  lines,
at the bottom of each window is its mode line (For more information on mode
lines  see  section  ,  page 21).  The lines above the mode line contain an
image of the text you are editing in the region around dot (or point).  Dot
is the reference around which editing takes place.  Dot is a pointer  which
points  at  a  position  between two characters.  On the screen, the cursor
will be positioned on the character that  immediatly  follows  dot.    When
characters  are  inserted,  they  are  inserted  at  the position where dot
points; commands exist that delete characters both to the left and  to  the
right  of  dot.    The text on the screen always reflects they way that the
text looks now.  
</FoO ThE bAr/>
dbadd info "emacs:Mode Lines" <<"</FoO ThE bAr/>"
Node: Mode Lines			Up: Basics, Previous: Region Restrictions

A  mode  line  is  the  line  of descriptive text that appears just below a
window on the screen.  It usually provides a description of  the  state  of
the  buffer  and is usually shown in reverse video.  The standard mode line
shows the name of the buffer, an `*' if the buffer has been  modified,  the
name  of  the  file associated with the buffer, the mode of the buffer, the
current position of dot within the buffer expressed as a percentage of  the
buffer size and and indication of the nesting within recursive-edit's which
is  shown  by  wrapping  the  mode line in an appropriate number of `[' `]'
pairs.

It is often the case that for some silly or practical reason one  wants  to
alter  the  layout  of  the  mode  line,  to  show  more, less or different
information.  Emacs has a fairly general facility for  doing  this.    Each
buffer  has associated with it a format string that describes the layout of
the mode line for that buffer whenever it appears in a window.  The  format
string  is  interpreted  in a manner much like the format argument to the C
printf subroutine.  Unadorned characters appear in the mode line unchanged.
The `%' character and the following format designator character cause  some
special  string  to  appear  in  the  mode line in their place.  The format
designators are:

b               Inserts the name of the buffer.
f               Inserts the name of the file associated with the buffer.
m               Inserts  the  value   of   the   buffer-specific   variable
                mode-string.
M               Inserts the value of the variable global-mode-string.
p               Inserts the position of "dot" as a percentage.
*               Inserts an `*' if the buffer has been modified.
[               Inserts (recursion-depth) `['s.
]               Inserts (recursion-depth) `]'s.

If  a  number  n appears between the `%' and the format designator then the
inserted string is constrained to be exactly n characters wide.  Either  by
padding or truncating on the right.

At CMU the default mode line is built using the following format:  

    " %[Buffer: %b%*  File: %f  %M (%m)  %p%]"

The following variables are involved in generating mode lines:

mode-line-format
                This  is  the  buffer  specific  variable that provides the
                format of a buffers mode line.

default-mode-line-format
                This is the value to which mode-line-format is  initialized
                when a buffer is created.

mode-string     This  buffer-specific  string variable can be inserted into
                the mode line by using `%m' in the format.   This  is  it's
                only   use   by   Emacs.    Usually,  mode  packages  (like
                `lisp-mode' or `c-mode') put some string  into  mode-string
                to  indicate  the mode of the buffer.  It is the appearance
                of this piece of descriptive  information  that  gives  the
                mode line its name.

global-mode-string
                This  is  similar  to  mode-string except that it is global
                -- the same string will be inserted into all mode lines  by
                `%M'.    It  is  usually  used  for  information  of global
                interest.  For example, the time package puts  the  current
                time of day and load average there.

</FoO ThE bAr/>
dbadd info "emacs:next-page" <<"</FoO ThE bAr/>"
Node: next-page				Up: Commands, Previous: next-line, Next: next-window

Reposition the current window on the current buffer so that the  next  page
of  the  buffer  is visible in the window (where a page is a group of lines
slightly smaller than a window).  In other words, it flips  you  forward  a
page  in the buffer.  Its inverse is ESC-V.  If possible, dot is kept where
it is, otherwise it is moved to the middle of the new page.
</FoO ThE bAr/>
dbadd info "info:footnotes" <<"</FoO ThE bAr/>"
File: info, Node: footnotes, Previous: Menus, Up: Top

Creating Footnotes:

  A footnote can be placed anywhere in the text, unlike a menu item
which must go at the front of a line.  A footnote looks like a menu
item except that it has "*note" instead of "*".  In addition, the
footnote's node name can be terminated by a ".", as well as by a
",", Tab, or CR.  It CANNOT be terminated by a ")", because ")"'s
are so often part of node names.  If you wish to enclose a footnote
in parentheses, terminate it with a period first.  Here are two
examples of footnote pointers:

     *Note details: commands.  (see *note 3: Full Proof.)
         (These are bogus notes -- don't bother trying to visit them.)
</FoO ThE bAr/>
dbadd info "emacs:tab-size" <<"</FoO ThE bAr/>"
Node: tab-size				Up: Variables, Previous: stack-trace-on-error, Next: this-command

A buffer-specific variable which specifies the number of characters between
tab  stops.    It's  not  clear that user specifiable tabs are a good idea,
since the rest of Unix and most other DEC styled operating systems have the
magic number 8 so deeply wired into them. (default 8)
</FoO ThE bAr/>
dbadd info "info:help-foo" <<"</FoO ThE bAr/>"
File: info	Node: help-foo	Up: Help-M

The U command

  Congratulations!  This is Help-FOO.  Unlike the other nodes you have
seen, this one has an "Up".  It is "Help-M", the node you just came
from via the "M" command.  That is the usual convention - a node's
subnodes have "Up"'s pointing back at it.  Menus move Down in the
tree, and Up moves Up.  Previous, on the other hand, is usually
used to "stay on the same level but go backwards".

  You can go back to the node Help-M by typing the command
"U" for "Up".  That will put you at the FRONT of the node - to get
back to where you were reading you will have to type some Spaces.

>> Now type "U" to move back up to Help-M.
</FoO ThE bAr/>
dbadd info "info:features" <<"</FoO ThE bAr/>"
Node: features	Previous: differences	Up: Teco

VAX-EMACS allows an arbitrary piece of MLISP code to be associated with
a node, and executed whenever that node is visited.  For a description
of functional nodes, see *note Live::.

VAX-EMACS INFO allows the creation of documentation trees independent of
the default tree whose root is (dir)Top.  Sharing of structures with the
default tree and with other trees is permitted, usually without undue
confusion.  See *note Trees::.
</FoO ThE bAr/>
dbadd info "emacs:windows" <<"</FoO ThE bAr/>"
File: emacs     Node: Windows     Up: Commands

A window in Emacs is a region on the screen through which a buffer is
viewed.  The following commands may be used to move around relative to them
and to manipulate them.

* menu:
* beginning-of-window::			(ESC-,)
* delete-other-windows::		(^X-1)
* delete-window::			(^X-d)
* end-of-window::			(ESC-.)
* enlarge-window::			(^X-z)
* line-to-top-of-window::		(ESC-!)
* next-window::				(^X-n)
* page-next-window::			(ESC-^V)
* previous-window::			(^X-p)
* save-window-excursion::
* shrink-window::			(^X-^Z)
* split-current-window::		(^X-2)
</FoO ThE bAr/>
dbadd info "emacs:replace" <<"</FoO ThE bAr/>"
Node: Replace				Next: Region Operations, Up: Quick

* Menu:
* replace-string::           ESC-r Replace one string with another
* query-replace-string::     ESC-q Query Replace, one string with another
</FoO ThE bAr/>
dbadd info "emacs:nothing" <<"</FoO ThE bAr/>"
Node: nothing				Up: Commands, Previous: next-window, Next: novalue

Nothing evaluates the same as novalue (ie. it returns a void result) except
that  if  it  is bound to some key or attached to some hook then the key or
hook behave as though no command was bound to them.  For  example,  if  you
want to remove the binding of a single key, just bind it to "nothing".
</FoO ThE bAr/>
dbadd info "emacs:message" <<"</FoO ThE bAr/>"
Node: message				Up: Commands, Previous: mark, Next: modify-syntax-entry

(message stringexpressions) is an MLisp function that  places  the  strings
that  result  from  the  evaluation of the given stringexpressions into the
message region on the display (the line at the bottom).
</FoO ThE bAr/>
dbadd info "emacs:keymaps" <<"</FoO ThE bAr/>"
Node: Keymaps				Up: Basics, Previous: Searching, Next: Region Restrictions

When a user is typing to Emacs  the  keystrokes  are  interpreted  using  a
keymap.   A keymap is just a table with one entry for each character in the
ASCII character set.  Each entry either names a function or another keymap.
When the user strikes a key, the corresponding keymap entry is examined and
the indicated action is performed.  If the key is bound to a function, then
that function will be invoked.  If the key is bound to another keymap  then
that keymap is used for interpreting the next keystroke.

There  is  always a global keymap and a local keymap, as keys are read from
the keyboard the two trees are traversed in  parallel  (you  can  think  of
keymaps  as  FSMs, with keystrokes triggering transitions).  When either of
the traversals reaches a leaf, that function is invoked and  interpretation
is reset to the roots of the trees.

The  root  keymaps  are  selected using the use-global-map or use-local-map
commands.  A new empty keymap is created using the define-keymap command.

The contents of a keymap can  be  changed  by  using  the  bind-to-key  and
local-bind-to-key  commands.    These  two commands take two arguments: the
name of the function to be bound and the keystroke sequence to which it  is
to  be  bound.    This  keystroke  sequence  is interpreted relative to the
current     local     or     global     keymaps.          For      example,
(bind-to-key  "define-keymap"  "\^Zd")  binds the define-keymap function to
the keystroke sequence `^Z' followed by `d'.

A named keymap behaves just like a function, it can be bound to  a  key  or
executed  within  an  MLisp  function.   When it is executed from within an
MLisp function, it causes the next keystroke to be interpreted relative  to
that map.

The  following  sample uses the keymap to partially simulate the vi editor.
Different keymaps are used to simulate the different modes in  vi:  command
mode and insertion mode.

(defun
    (insert-before              ; Enter insertion mode
        (use-global-map "vi-insertion-mode"))

    (insert-after               ; Also enter insertion mode, but after
                                ; the current character
        (forward-character)
        (use-global-map "vi-insertion-mode"))

    (exit-insertion             ; Exit insertion mode and return to
                                ; command mode
        (use-global-map "vi-command-mode"))

    (replace-one
        (insert-character (get-tty-character))
        (delete-next-character))

    (next-skip
        (beginning-of-line)
        (next-line)
        (skip-white-space))

    (prev-skip
        (beginning-of-line)
        (previous-line)
        (skip-white-space))

    (skip-white-space
        (while (& (! (eolp)) (| (= (following-char) ' ') (= (following-
            (forward-character)))

    (vi                         ; Start behaving like vi
        (use-global-map "vi-command-mode"))
)

; setup vi mode tables
(define-keymap "vi-command-mode")
(define-keymap "vi-insertion-mode")

(use-global-map "vi-insertion-mode"); Setup the insertion mode map
(bind-to-key "execute-extended-command" "\^X")
(progn i
    (setq i ' ')
    (while (< i 0177)
        (bind-to-key "self-insert" i)
        (setq i (+ i 1))))
(bind-to-key "self-insert" "\011")
(bind-to-key "newline" "\015")
(bind-to-key "self-insert" "\012")
(bind-to-key "delete-previous-character" "\010")
(bind-to-key "delete-previous-character" "\177")
(bind-to-key "exit-insertion" "\033")

(use-global-map "vi-command-mode"); Setup the command mode map
(bind-to-key "execute-extended-command" "\^X")
(bind-to-key "next-line" "\^n")
(bind-to-key "previous-line" "\^p")
(bind-to-key "forward-word" "w")
(bind-to-key "backward-word" "b")
(bind-to-key "search-forward" "/")
(bind-to-key "search-reverse" "?")
(bind-to-key "beginning-of-line" "0")
(bind-to-key "end-of-line" "$")
(bind-to-key "forward-character" " ")
(bind-to-key "backward-character" "\^h")
(bind-to-key "backward-character" "h")
(bind-to-key "insert-after" "a")
(bind-to-key "insert-before" "i")
(bind-to-key "replace-one" "r")
(bind-to-key "next-skip" "+")
(bind-to-key "next-skip" "\^m")
(bind-to-key "prev-skip" "-")
(use-global-map "default-global-keymap")

</FoO ThE bAr/>
dbadd info "emacs:command" <<"</FoO ThE bAr/>"
Node: Command		Up: Top		Next: command-prefix, Previous: char-to-string

Command prefix (also known as META
             ESC) The next character typed will be interpreted as a command
          based on the fact that it was preceded by ESC.  The name meta for
          the ESC character comes from funny keyboards at Stanford and  MIT
          that  have  a  Meta-shift  key  which is used to extend the ASCII
          character set.  Lacking a Meta key, we  make  do  with  prefixing
          with an ESC character.  You may see (and hear) commands like ESC-
          V  referred  to  as Meta-V.  Sometimes the ESC key is confusingly
          written as $, so ESC-V would be written  as  $V.    ESC  is  also
          occasionally  referred  to as Altmode, from the labeling of a key
          on those old favorites, model 33 teletypes.
</FoO ThE bAr/>
dbadd info "info:help-ft" <<"</FoO ThE bAr/>"
File: info	Node: help-ft

  This is the node reached by the footnote "Ftnt".

  While this node is specifically intended to be a footnote,
many footnotes are simply cross-references to other places in the
structure of nodes.  So you can't expect the footnote to have
a Next, Previous or Up pointing back to where you came from.
In general, the "L" command is the only way to get back there.

>> Type "L" to return to where the footnote was.
</FoO ThE bAr/>
dbadd info "info:help-^l" <<"</FoO ThE bAr/>"
File: info	Node: help-^l	Next: Help-M	Previous: Help-P

Space, Backspace, B and ^L commands.

  This node's header tells you that you are now at node "Help-^L", and
that "P" would get you back to "Help-P".  The line starting "Space,"
is a "Title", saying what the node is about (most nodes have one).

  This is a big node and it doesn't all fit on your display screen.
You can tell that there is more that isn't visible because of the
"--MORE--" that appears on a line near the bottom of the screen.

  The Space, Backspace and B commands exist to allow you to "move
around" in a node that doesn't all fit at once.
Space moves forward, to show what was below the bottom of the screen.
Backspace moves backward, to show what was above the top of the screen
(there isn't anything above the top until you have typed some spaces).
>> Now try typing a Space (afterward, type a Backspace to return here).

  When you type the space, the two lines that were at the bottom of the 
screen appear at the top, followed by more lines.  Backspace takes the
two lines from the top and moves them to the bottom, USUALLY, but if
there are not a full screen's worth of lines above them they may not
make it all the way to the bottom.

  If you type a Space when there is no more to see, it will do
nothing. The same goes for a Backspace when the Header of the node
is visible.

  Two more commands, A and Z, let you position the text on the
screen exactly as you want it:  "A" scrolls the screen one line
down, letting you see the line just above the one visible at the
top of the screen.  "Z" scrolls one line up, letting you see the
line below the lowest visible line.  If you're already at the top
(bottom) of a node, A (Z) does nothing.
>> Type a few A's and Z's now.

  If your screen is ever garbaged, you can tell INFO to print it out
again by typing a ^L (Control-L, that is - hold down "Control" and
type an "L").
>> Type a ^L now.

  To move back to the beginning of the node you are on, you can type
a lot of Backspaces.  You can also type simply "B" for beginning.
>> Try that now.  (I have put in enough verbiage to make sure you are
not on the first screenful now).  Then come back, with Spaces.

  You have just learned a considerable number of commands.  If you
want to use one but have trouble remembering which, you should type
a "?" which will print out a brief list of commands.  (This list is
really just a regular node.) When you are finished looking at the
list, type "l" to make it go away and get back where you were.

>> Type a "?" now.  After it finishes, type "l".

  From now on, you will encounter large nodes without warning, and
will be expected to know how to use Space and Backspace to move
around in them without being told.  Since not all terminals have
the same size screen, it would be impossible to warn you anyway.

>> Now type "N" to see the description of the "M" command.
</FoO ThE bAr/>
dbadd info "emacs:to-col" <<"</FoO ThE bAr/>"
Node: to-col				Up: Commands, Previous: temp-use-buffer, Next: transpose-characters

(to-col  n)  is  an  MLisp function that insert tabs and spaces to move the
following character to printing column n.
</FoO ThE bAr/>
dbadd info "emacs:scribe" <<"</FoO ThE bAr/>"
Node: scribe				Up: Packages, Previous: rmail, Next: scribe-bib

Scribe mode binds justify-paragraph to ESC-j, defines appply-look and binds
it to ESC-l, turns on autofill, sets the right margin to 77 and updates the
LastEditDate to the current date.

If the  string  ``LastEditDate="''  exists  somewhere  in  the  first  2000
characters  of  the  document then then the region extending from it to the
next `"' is replaced by the current date and  time.    You're  intended  to
stick in your document something like:  

    @String(LastEditDate="Sat Nov 28 11:17:29 1981")

Emacs  will  automatically maintain the date.  The date will only change in
the file you make some changes, the mere act of starting  scribe-mode  does
not cause the date change to be permanent.

Apply-look  reads  a  single  character and then surrounds the current word
with ``@c['' and ``]''.  So, if you've just typed ``begin'', typing ESC-l-i
will  change  it  to  ``@i[begin]'',  which  appears  in  the  document  as
``begin''.  This use of the word ``look'' comes from the Bravo text editor.

</FoO ThE bAr/>
dbadd info "emacs:killer" <<"</FoO ThE bAr/>"
Node: killer	Previous: tags		Up: top		Next: util

To invoke say M-X load killer

Killer contains alternate definitions for the delete/yank commands.
They offer the advantage of a kill ring (holding 9 saves), with
appending of consecutive kills to a single element of the ring.  (also,
yank-from-kill-ring leaves the mark at the beginning of the yank,
facilitating un-yanking if desired.)

The key assignments follow the defaults (see the end of the file), except
that the function yank-next-from-kill-ring, which has no default
counterpart, is bound to C-M-Y.  Use it as follows to go around the ring:
type C-Y to get back the last thing you killed.  If you don't like it,
travel back in time by typing C-M-Y repeatedly, replacing the un-kill with
its predecessor on the ring.  Eventually you get back where you started.

The rules for appending/prepending successive kills follow those for teco
emacs: successive line or word deletions in the same direction get stuck
together.  Character deletions preceded by kills of larger units also get
tacked on.

Default Bindings: (globally bound at load time)

^D	 Delete-next-character
<DEL>	 Delete-previous-character 
M-D	 Delete-next-word 
M-<DEL>	 Delete-previous-word 
^K	 Kill-to-end-of-line 
M-W	 region-to-kill-ring 
^W	 delete-region-to-kill-ring 
^Y	 yank-from-kill-ring
C-M-Y	 yank-next-from-kill-ring

</FoO ThE bAr/>
dbadd info "emacs:getenv" <<"</FoO ThE bAr/>"
Node: getenv				Up: Commands, Previous: get-tty-variable, Next: global-binding-of

(getenv  "varname")  returns  the  named  shell  environment variable.  for
example, (getenv "HOME")  will  return  a  string  which  names  your  home
directory.
</FoO ThE bAr/>
dbadd info "info:help-q" <<"</FoO ThE bAr/>"
File: info	Node: help-q	Previous: Help-Adv	Up: Top

  To get out of Info, back to Emacs, type "Q" for "Quit".

  This is the end of the course on using INFO.  There are some other
commands that are not essential or meant for experienced users;  they
are useful, and you can find them by looking in the directory for
documentation on INFO.  Finding them will be a good exercise in using
INFO in the usual manner.

>> Go to the directory with "D", type "MInfo" and Return to get to the
node about INFO and see what is available.
</FoO ThE bAr/>
dbadd info "info:help-p" <<"</FoO ThE bAr/>"
File: info	Node: help-p	Next: Help-^L	Previous: Help

This node is called "Help-P".  The "Previous" node, as you see, is
"Help", which is the one you just came from using the "N" command.
Another "N" command now would take you to the Next node, "Help-^L".

>> But don't do that yet.  First, try the "P" command, which takes
you to the Previous node.  When you get there, you can do an "N"
again to return here.

  This all probably seems insultingly simple so far, but DON'T be
led into skimming.  Things will get more complicated soon.  Also,
don't try a new command until you are told it's time to.  Otherwise,
you may make INFO skip past an important warning that was coming up.
 ">>" in the margin means it is really time to try a command.

>> Now do an "N" to get to the node "Help-^L" and learn more.
</FoO ThE bAr/>
dbadd info "info:help-m" <<"</FoO ThE bAr/>"
File: info	Node: help-m	Next: Help-Adv	Previous: Help-^L

Menus and the M command

  With only the "N" and "P" commands for moving between nodes, nodes
are restricted to a linear sequence.  Menus allow a branching
structure.  A menu is a list of other nodes you can move to.  It is
actually just part of the text of the node formatted specially so that
INFO can interpret it.  The beginning of a menu is always identified
by a line which starts with "* Menu:".  A node contains a menu if and
only if it has a line in it which starts that way.  The only menu you
can use at any moment is the one in the node you are in.  To use a
menu in any other node, you must move to that node first. 

  After the start of the menu, each line that starts with a "*"
identifies one subtopic.  The line will usually contain a brief name
for the subtopic (followed by a ":"), the name of the node that talks
about that subtopic, and optionally some further description of the
subtopic.  Lines in the menu that don't start with a "*" have no
special meaning - they are only for the human reader's benefit and do
not define additional subtopics.  Here is an example:
* Foo:  FOO's Node      This tells about FOO
The subtopic name is Foo, and the node describing it is "FOO's Node".
The rest of the line is just for the reader's information.

  When you use a menu to go to another node (in a way that will be
described soon), what you specify is the subtopic name, the first
thing in the menu line.  INFO uses it to find the menu line, extracts
the node name from it, and goes to that node.  The reason that there
is both a subtopic name and a node name is that the node name must be
meaningful to the computer and may therefore have to be ugly looking.
The subtopic name can be chosen just to be convenient for the user to
specify.  Often the node name is convenient for the user to specify
and so both it and the subtopic name are the same.  There is an
abbreviation for this:
* Foo::   This tells about FOO
This means that the subtopic name and node name are the same; they are
both "Foo".

>>  Now use Spaces to find the menu in this node, then come back to
the front with a "B".  As you see, a menu is actually visible
in its node.  If you can't find a menu in a node by looking at it,
then the node doesn't have a menu.  The only menu you can use is the
one (if any) in the current node.  To use a menu in another node,
you must first get to that node somehow.

  The command to go to one of the subnodes is "M" - but DON'T DO IT
YET!  Before you use "M", you must understand the difference between
commands and arguments.  So far, you have learned several commands
that do not need arguments.  When you type one, INFO processes it and
is instantly ready for another command.  The "M" command is different:
it is incomplete without the NAME OF THE SUBTOPIC.  Once you have
typed "M", INFO tries to read the name.

  INFO tells you when it wants to read an argument by prompting at
the bottom of the screen.  (For example, when you type "M" (DON'T DO
IT YET), you will see "Menu item: " appear at the bottom of the
screen.) At such times, commands won't work, because INFO will try
to use them as the argument.  You must either type the argument and
finish the command you started, or type Control-G to cancel the
command. When you have done one of those things, the prompt at the
bottom of the screen will disappear.

  The command to go to a subnode via a menu is "M".  When you type an
"M", the top of the menu will appear on the screen if it wasn't
already visible.  If the menu doesn't all fit on the screen, you can use
Space and Backspace as usual to move around in it.  When you have
decided which subtopic to look at, type the subtopic's name, ended
by a CR (Carriage-Return).  You can abbreviate the topic name.  If
the abbreviation is not unique, the first matching topic is chosen.
Some menus will put the shortest possible abbreviation for each topic
name in capital letters, so you can see how much you need to type.
You should not put any spaces at the end, or inside of the item name,
except for one space where a space appears in the item in the menu.

  Here is a menu to give you a chance to practice.

* Menu:    The menu starts here.  Type a space if you need to.

This menu givs you three ways of going to one place, Help-FOO.

* Foo:  Help-FOO	A node you can visit for fun
* Bar:  Help-FOO	Strange!  two ways to get to the same place.
* Help-FOO::		And yet another!

>>  Now type just an "M" and see what happens:

  Now you are "inside" an "M" command.  Commands can't be used now;
the next thing you will type must be the name of a subtopic.  Notice
how the prompt "Menu item: " has appeared at the bottom of the
screen to tell you what INFO expects next.

  You can change your mind about doing the "M" by typing a Rubout.
>> Try that now;  notice the "Menu item: " disappear.
>> Then type another "M".

>> Now type "Foo", the item name.  Don't type CR yet.

  While you are typing the item name, you can use the Rubout
character to cancel one character at a time if you make a mistake.
>> Type one to cancel the last "O".  You could type another "O" to
replace it.  You don't have to, since "FO" is a valid abbreviation.
>> Now you are ready to go.  Type a CR.

  After visiting Help-FOO, you should return here.

>> Type "N" to see more commands.
</FoO ThE bAr/>
dbadd info "emacs:spell" <<"</FoO ThE bAr/>"
Node: spell				Up: Packages, Previous: scribe-bib, Next: tags

The spell package implements the single function  spell.    It  provides  a
simple facility for doing spelling correction.  If you invoke spell it will
scan  your  file  looking  for  spelling  errors, then it will go through a
dialogue to let you fix them up.  For each misspelled word Emacs will  show
you  the  word, some context around it and ask you what to do.  If you type
`e' or `^G' the spelling corrector will exit.  If you  type  `  '  it  will
ignore  the  word.    If  you  type  `r' it will ask for the text to use in
replacing the word and perform a query-replace.  Bug: This  uses  the  Unix
spell  command  which  believes  that  its  input  is a source for the Unix
standard text formatter troff/nroff; Spell misbehaves on Scribe .mss files.

</FoO ThE bAr/>
dbadd info "emacs:nargs" <<"</FoO ThE bAr/>"
Node: nargs				Up: Commands, Previous: move-to-comment-column, Next: narrow-region

An  MLisp  function  which  returns  the  number of arguments passed to the
invoking MLisp function.  For example, within the execution of foo  invoked
by (foo x y) the value of nargs will be 2.
</FoO ThE bAr/>
dbadd info "emacs:defun" <<"</FoO ThE bAr/>"
Node: defun				Up: Commands, Previous: define-string-macro, Next: delete-buffer

(defun  (name expressions... )... ) is an MLisp function that defines a new
MLisp function with the given  name  and  a  body  composed  of  the  given
expressions.    The  value  of  the  function  is  the  value  of  the last
expression.  For example:

    (defun
        (indent-line                ; this function just sticks a tab a
            (save-excursion         ; the beginning of the current line
                (beginning-of-line) ; without moving dot.
                (insert-string "    ")
            )
        )
    )

</FoO ThE bAr/>
dbadd info "emacs:time" <<"</FoO ThE bAr/>"
Node: time				Up: Packages, Previous: text-mode, Next: undo

This package only implements one user-visible function,  time,  which  puts
the  current  time  of day and load average (continuously updating!) in the
mode line of each window.  It uses global-mode-string  and  the  subprocess
control facility.  Major!  
</FoO ThE bAr/>
dbadd info "emacs:mark" <<"</FoO ThE bAr/>"
Node: mark				Up: Commands, Previous: looking-at, Next: message

An MLisp function that returns the position of the marker  in  the  current
buffer.    An  error is signaled if the marker isn't set.  The value of the
function is an object of type "marker" -- if it is assigned to  a  variable
then  as  changes  are made to the buffer the variable's value continues to
indicate the same position in the buffer.
</FoO ThE bAr/>
dbadd info "emacs:lisp" <<"</FoO ThE bAr/>"
File: emacs, Node: lisp, Next: text, Up: top, Previous: mscompil

Invoke by M-X lisp-mode

Principle features are automatic flashing of matching parens (when you type a
closing parens), and lisp-indenting on the fly: <tab> re-indents the current
line, and <lf> does a newline and indents.

If you don't like the default bindings, define a function called
&atomic-lisp-hook.  This function, if it exists, is run by lisp-mode
after it does the local bindings.

 Global variables:
 
 paren-flash-wait   determines time (in tenths of a second) that
		    paren-flash holds (default= 10). 

 paren-flash-message  if non zero, when matching paren is not on screen,
		      show the line with the matching paren in the message
		      area, with the match preceded by " >>".  (default=1)

 lisp-default-indent  determines # of columns per level of indentation
		      (default=2)

 lisp-indent-under-arg  if non-zero, be smart about where to indent.
		        When zero, always use lisp-default-indent. (default=1)
  

 Bindings:
 M-;		lisp-comment
 M-N   		lisp-next-comment
 <TAB>		lisp-indent-line
 M-<TAB>	inserts a tab char
 <LF>		lisp-indent-and-newline
 <DEL>		delete-backwards-hacking-tabs
 <unbound>	lisp-indent-region
 )		paren-flash
 M-^   		delete-indentation


</FoO ThE bAr/>
dbadd info "emacs:info" <<"</FoO ThE bAr/>"
Node: info				Up: Packages, Previous: incr-search, Next: lisp-mode

Info  is  a  system  which  lets  you  browse through the documentation for
various systems.  In particular, all the Emacs documentation  is  available
online  through  it.    Both  the  describe-command  and  describe-variable
functions use it.

Rather than document Info extensivly here, I suggest that you run Info  and
use it to describe itself.  
</FoO ThE bAr/>
dbadd info "emacs:bobp" <<"</FoO ThE bAr/>"
Node: bobp				Up: Commands, Previous: bind-to-key, Next: bolp

(bobp) is an MLisp predicate which is true iff dot is at the  beginning  of
the buffer.
</FoO ThE bAr/>
dbadd info "info:teco" <<"</FoO ThE bAr/>"
Node: teco		Next: differences			Up: Top

Vax-emacs INFO is closely modeled after teco-emacs INFO.  It uses an
incompatible (but much higher performance) file format.  Utilities exist for
converting teco-emacs INFO databases to Vax-emacs databases [There use is
left as an exercise to the reader].

* menu:
* Differences::		differences in effect and availability of commands.
* Features::		additional features.

</FoO ThE bAr/>
dbadd info "info:tags" <<"</FoO ThE bAr/>"
File: info,  Node: tags,  Previous: Footnotes,  Up: Top,  Next: Checking

Tag Tables for INFO Files:

  You can speed up the access to nodes of a large INFO file by giving
it a tag table.  Unlike the tag table for a program, the tag table for
an INFO file lives inside the file itself and will automatically be
used whenever INFO reads in the file.  For information on how to
construct and update the tag table, see *Note Tags: (TAGS)INFO.
</FoO ThE bAr/>
dbadd info "info:live" <<"</FoO ThE bAr/>"
Node: live	Previous: Trees		Up: Top		Next: Directory

	This node needs a volunteer to finish writing it!
</FoO ThE bAr/>
dbadd info "emacs:top" <<"</FoO ThE bAr/>"
Node: Top				Next: Introduction, Up: (dir)

Emacs is an extensible display editor.  This Info tree attempts to describe
how to use it.  Start with the introduction if you're new to Emacs, look in
the commands section if you're just looking for some particular command (or
better yet, you should have used the Emacs "describe-command" command).

* menu:

* Introduction::	a gentle introduction to Emacs
* Commands::		the Emacs commands grouped by function
* Variables::		the various that can be set to customize Emacs to
			the users taste.
* Init files::		all about emacs profile files
* Extensibility::	how to deal with MLisp, the Emacs extension language.
* Packages::		the various packages that are available
* Mice::		how to use mice and tablets with Emacs
* Searching::		how to construct search strings
</FoO ThE bAr/>
dbadd info "emacs:pwd" <<"</FoO ThE bAr/>"
Node: pwd				Up: Packages, Previous: processP, Next: rmail

pwd             Prints the current working directory in the mode line, just
                like the shell command ``pwd''.

cd              Changes  the current working directory, just like the shell
                command ``cd''.  You should beware that cd only changes the
                current directory for Emacs, if it has  already  spawned  a
                subprocess  (a  shell,  for  example) then a cd from within
                Emacs has no effect on the shell.

</FoO ThE bAr/>
dbadd info "cmds:top" <<"</FoO ThE bAr/>"
Node: top	Info Command Summary                    Up: (dir)

Type "l" to resume info.  Type "h" for an INFO tutorial.  Type <space> to
see the next screen.

<space>,C-V     next screen
<bs>,M-V        previous screen (^H)
?               visit this node (command-summary)
@               menu path (enter menu items separated by spaces.)
a               scroll one line down
b               beginning of node
d               go to dir node (the top of the tree)
e               end of node
f               go to a footnote (prompts for footnote name)
g               go to a node (prompts for nodespec)
h               help -- visit an info tutorial
l               return to last node (retrace your path through the tree)
m               go to a menu item (prompts for item name)
n               go to Next node in sequence
p               go to Previous node in sequence
q               quit info
r, C-R          search-reverse   (string-search)
s, C-S          search-forward   (string-search)
u               go Up to this node's father
x, M-X          execute-extended-command
z               scroll one line up
C-M-E           edit current node (^] exits recursive edit)

     (most C-X commands not pertaining to file saving also work.)

Type "l" to return to INFO, or <backspace> (^H) to see the previous screen
</FoO ThE bAr/>
dbadd info "emacs:>" <<"</FoO ThE bAr/>"
Node: >					Up: Commands, Previous: =, Next: >=

(> e  e ) MLisp function that returns true iff e  > e .
    1  2                                        1    2
</FoO ThE bAr/>
dbadd info "emacs:=" <<"</FoO ThE bAr/>"
Node: =					Up: Commands, Previous: <=, Next: >

(= e  e ) MLisp function that returns true iff e  = e .
    1  2                                        1    2
</FoO ThE bAr/>
dbadd info "emacs:/" <<"</FoO ThE bAr/>"
Node: /					Up: Commands, Previous: -, Next: <

(/ e  e ) MLisp function that returns e  / e .
    1  2                               1    2
</FoO ThE bAr/>
dbadd info "emacs:%" <<"</FoO ThE bAr/>"
Node: %					Up: Commands, Previous: !=, Next: &

(% e  e ) MLisp function that returns e  % e  (the C mod operator).
    1  2                               1    2
</FoO ThE bAr/>
dbadd info "mail" <<"</FoO ThE bAr/>"
Node: Mail

* rmail::                     ^X-r Read mail.
* smail::                     ^X-m Send mail
</FoO ThE bAr/>
dbadd info "emacs:help and helper functions" <<"</FoO ThE bAr/>"
Node: Help And Helper Functions		Next: Search, Up: Quick

* Menu:
* illegal-operation::           ^G Abort anything at any time.
* apropos::                  ESC-? Show  every  command  containing  string
                                   (try ESC-? para)
* info::                ESC-X info Browse through the Emacs manual.
</FoO ThE bAr/>
dbadd info "emacs:prepend-region-to-buffer" <<"</FoO ThE bAr/>"
Node: prepend-region-to-buffer		Up: Commands, Previous: prefix-argument-loop, Next: previous-command

Prepends the region between dot and mark to the named buffer.  Neither  the
original  text in the destination buffer nor the text in the region between
dot and mark will be disturbed.
</FoO ThE bAr/>
dbadd info "emacs:default-mode-line-format" <<"</FoO ThE bAr/>"
Node: default-mode-line-format		Up: Top		Next: default-right-margin, Previous: default-left-margin

default-mode-line-format
            This is the value given to mode-line-format when  a  buffer  is
          created.
</FoO ThE bAr/>
dbadd info "emacs:return-prefix-argument" <<"</FoO ThE bAr/>"
Node: return-prefix-argument		Up: Commands, Previous: reset-filter, Next: return-to-monitor

(return-prefix-argument  n)  sets the numeric prefix argument to be used by
the next function invocation to n.  The next function  may  be  either  the
next  function  in  the normal flow of MLisp execution or the next function
invoked from  a  keystroke.    Return-prefix-argument  is  to  be  used  by
functions  that  are  to be bound to keys and which are to provide a prefix
argument for the next keyboard command.
</FoO ThE bAr/>
dbadd info "emacs:move-to-comment-column" <<"</FoO ThE bAr/>"
Node: move-to-comment-column		Up: Commands, Previous: move-dot-to-x-y, Next: nargs

If  the cursor is not at the beginning of a line, ESC-C moves the cursor to
the column specified by the comment-column variable by inserting  tabs  and
spaces  as needed.  In any case, it the sets the right margin to the column
finally reached.  This is usually  used  in  macros  for  language-specific
comments.
</FoO ThE bAr/>
dbadd info "emacs:execute-keyboard-macro" <<"</FoO ThE bAr/>"
Node: execute-keyboard-macro		Up: Commands, Previous: execute-extended-command, Next: execute-mlisp-buffer

Takes the keystrokes remembered with ^X( and ^X) and treats them as  though
they  had  been typed again.  This is a cheap and easy macro facility.  For
more  power,  see  the   define-string-macro,   define-keyboard-macro   and
bind-to-key commands.
</FoO ThE bAr/>
dbadd info "emacs:default-comment-column" <<"</FoO ThE bAr/>"
Node: default-comment-column		Up: Top		Next: default-left-margin, Previous: default-case-fold-search

default-comment-column
            Default-comment-column provides the default value for  comment-
          column,  which  is  used  whenever  a new buffer is created.  Its
          initial value is 33.  
</FoO ThE bAr/>
dbadd info "emacs:change-current-process" <<"</FoO ThE bAr/>"
Node: change-current-process		Up: Commands, Previous: case-word-upper, Next: change-directory

(change-current-process "process-name") -- Sets the current process to  the
one named.
</FoO ThE bAr/>
dbadd info "emacs:delete-next-character" <<"</FoO ThE bAr/>"
Node: delete-next-character		Up: Commands, Previous: delete-macro, Next: delete-next-word

Delete  the  character  immediatly following dot; that is, the character on
which the terminals cursor sits.  Lines may be merged by deleting newlines.
</FoO ThE bAr/>
dbadd info "emacs:define-keyboard-macro" <<"</FoO ThE bAr/>"
Node: define-keyboard-macro		Up: Commands, Previous: define-hooked-local-abbrev, Next: define-keymap

Give  a name to the current keyboard macro.  A keyboard macro is defined by
using the ^X( and ^X)  command;  define-keyboard-macro  takes  the  current
keyboard  macro,  squirrels  it  away in a safe place, gives it a name, and
erases the keyboard macro.  define-string-macro is another way to define  a
macro.
</FoO ThE bAr/>
dbadd info "emacs:split-current-window" <<"</FoO ThE bAr/>"
Node: split-current-window		Up: Commands, Previous: sit-for, Next: start-filtered-process

Enter two-window mode.  Actually, it takes the current window and splits it
into two windows, dividing the space on the screen equally between the  two
windows.    An arbitrary number of windows can be created -- the only limit
is on the amount of space available on the screen, which, sigh, is only  24
lines on most terminals available these days (with the notable exception of
the Ann Arbor Ambassador which has 60).
</FoO ThE bAr/>
dbadd info "emacs:define-global-abbrev" <<"</FoO ThE bAr/>"
Node: define-global-abbrev		Up: Commands, Previous: define-buffer-macro, Next: define-hooked-global-abbrev

Define  (or redefine) an abbrev with the given name for the given phrase in
the global abbreviation table.
</FoO ThE bAr/>
dbadd info "emacs:checkpoint-frequency" <<"</FoO ThE bAr/>"
Node: checkpoint-frequency		Up: Variables, Previous: case-fold-search, Next: comment-column

The number of keystrokes between checkpoints. Every  "checkpoint-frequency"
keystrokes  all  buffers  which  have  been  modified  since they were last
checkpointed are written to a file named "file.CKP".  File is the file name
associated with the buffer, or if that is null, the  name  of  the  buffer.
Proper  account is taken of the restriction on file names to 14 characters.
(default 300)
</FoO ThE bAr/>
dbadd info "emacs:case-word-capitalize" <<"</FoO ThE bAr/>"
Node: case-word-capitalize		Up: Commands, Previous: case-region-upper, Next: case-word-invert

Capitalize the current word (the one above or to the left of dot) by making
its first character upper case and all the rest lower case.
</FoO ThE bAr/>
dbadd info "help and helper functions" <<"</FoO ThE bAr/>"
Node: Help And Helper Functions		Next: Search

* illegal-operation::           ^G Abort anything at any time.
* apropos::                  ESC-? Show  every  command  containing  string
                                   (try ESC-? para)
* info::                ESC-X info Browse through the Emacs manual.
</FoO ThE bAr/>
dbadd info "emacs:define-string-macro" <<"</FoO ThE bAr/>"
Node: define-string-macro		Up: Commands, Previous: define-local-abbrev, Next: defun

Define  a  macro  given  a  name  and  a  body  as  a string entered in the
minibuffer.  Note: to get a control character into the body of the macro it
must be quoted with ^Q.  define-keyboard-macro is another way to  define  a
macro.
</FoO ThE bAr/>
dbadd info "emacs:define-local-abbrev" <<"</FoO ThE bAr/>"
Node: define-local-abbrev		Up: Commands, Previous: define-keymap, Next: define-string-macro

Define  (or redefine) an abbrev with the given name for the given phrase in
the local abbreviation table.  A local abbrev table must have already  been
set up with use-abbrev-table.
</FoO ThE bAr/>
dbadd info "emacs:complicated profile" <<"</FoO ThE bAr/>"
File: emacs     Node: complicated profile     Up: Init files, Previous: default profile

This is the profile used by the author of Emacs.  It is by no means the most
complicated Emacs profile ever written.


(defun
    (pop-out-of-emacs
	(write-modified-files)
	(pause-emacs))
    (to-buffer
	(pop-to-buffer (get-tty-buffer ": to-buffer ")))
)
(autoload "add-change-log-entry" "add-log.ml")
(autoload "new-compile-it" "newcompile.ml")
(autoload "goto-line" "goto.ml")
(autoload "goto-tag" "tags.ml")
(autoload "time" "time.ml")
(autoload "spell" "spell.ml")
(autoload "incremental-search" "incr-search.ml")
(autoload "reverse-incremental-search" "incr-search.ml")
(autoload "new-electric" "new-el-mode.ml")
(autoload "dired" "dired.ml")
(autoload "electric-c-mode" "electric-c.ml")
(autoload "electric-lisp-mode" "electric-lisp.ml")
(autoload "electric-mlisp-mode" "electric-lisp.ml")
(autoload "scribe-mode" "scribe.ml")
(autoload "lisp" "process.ml")
(setq silently-kill-processes 1)
(setq scroll-step 1)
(setq ask-about-buffer-names 0)
(setq visible-bell 1)
(setq quick-redisplay 1)
(setq track-eol-on-^N-^P 0)
(setq ctlchar-with-^ 1)
(setq help-on-command-completion-error 0)
(setq wrap-long-lines 1)
(setq backup-before-writing 1)
(setq backup-by-copying-when-linked 1)
(setq default-mode-line-format "         Emacs: %20b %M (%m)    %[%3p%] %*")
(bind-to-key "re-search-forward" '^S')
(bind-to-key "re-search-reverse" '^R')
(bind-to-key "delete-white-space" "\ek")
(bind-to-key "new-compile" "\^X\^E")
(bind-to-key "pop-out-of-emacs" "\eg")
(bind-to-key "case-word-capitalize" "\ec")
(bind-to-key "incremental-search" "\es")
(bind-to-key "reverse-incremental-search" "\er")
(bind-to-key "rmail" "\^Xr")
(bind-to-key "smail" "\^Xm")
(bind-to-key "goto-tag" "\^X\^G")
(bind-to-key "define-global-abbrev" "\^X")
(bind-to-key "shell" "\e-")
(bind-to-key "to-buffer" "\^X\^O")
(auto-execute "electric-c-mode" "*.c")
(auto-execute "electric-c-mode" "*.h")
(auto-execute "text-mode" "/tmp/*")
(auto-execute "scribe-mode" "*.mss")
(auto-execute "electric-mlisp-mode" "*.ml")
(auto-execute "electric-lisp-mode" "*.l")
(auto-execute "electric-mlisp-mode" "*.emacs_pro")
(auto-execute "new-electric" "*.nwl")
(quietly-read-abbrev-file ".abbrevs")
(time)
(setq global-mode-string (emacs-version))

</FoO ThE bAr/>
dbadd info "emacs:backup-when-writing" <<"</FoO ThE bAr/>"
Node: backup-when-writing		Up: Variables, Previous: backup-by-copying-when-linked, Next: buffer-is-modified

If ON Emacs will make a backup of a file just before the first time that it
is overwritten.  The backup will have the same name as the original, except
that the string ".BAK" will be appended; unless the last name in  the  path
has  more  than  10  characters,  in  which case it will be truncated to 10
characters.  "foo.c" gets backed up  on  "foo.c.BAK";  "/usr/jag/foo.c"  on
"/usr/jag/foo.c.BAK"; and "EtherService.c" on "EtherServi.BAK".  The backup
will only be made the first time that the file is rewritten from within the
same  invocation  of  Emacs, so if you write out the file several times the
.BAK file will contain the file as it was before Emacs was  invoked.    The
backup  is  normally  made  by  fancy  footwork  with links and unlinks, to
achieve acceptable performance:  when "foo.c" is  to  be  rewritten,  Emacs
effectivly  executes  a "mv foo.c foo.c.BAK" and then creates foo.c a write
the new copy.  The file protection of foo.c is copied from the  old  foo.c,
but  old links to the file now point to the .BAK file, and the owner of the
new file is the person running Emacs.  If you don't  like  this  behaviour,
see   the  switches  backup-by-copying  and  backup-by-copying-when-linked.
(default OFF)
</FoO ThE bAr/>
dbadd info "emacs:scroll-one-line-up" <<"</FoO ThE bAr/>"
Node: scroll-one-line-up		Up: Commands, Previous: scroll-one-line-down, Next: search-forward

Repositions the current window on the current buffer so that the line which
is currently the second line in the window becomes the first --  effectivly
it moves the buffer up one line in the window.  ESC-Z is its inverse.
</FoO ThE bAr/>
dbadd info "emacs:newline-and-backup" <<"</FoO ThE bAr/>"
Node: newline-and-backup		Up: Commands, Previous: newline, Next: newline-and-indent

Insert  an  end-of-line  immediatly after dot, effectivly opening up space.
If dot is positioned at the beginning of a line,  then  ^O  will  create  a
blank line preceding the current line and position dot on that new line.
</FoO ThE bAr/>
dbadd info "emacs:execute-mlisp-line" <<"</FoO ThE bAr/>"
Node: execute-mlisp-line		Up: Commands, Previous: execute-mlisp-buffer, Next: execute-monitor-command

Prompt for a string, parse it as an MLisp expression and execute it.
</FoO ThE bAr/>
dbadd info "dir:document preparation" <<"</FoO ThE bAr/>"
Node: document preparation					Up: Top

There are currently two text formatting systems available on the VAX Unix
systems at CMU.  The one most people use is Scribe.  It supports many
devices, styles and formats and is very well human engineered. The other is
the Bell standard troff/nroff/dtroff (dtroff is troff for the Dover). Troff
supports multiple fonts, etc, and, via the preprocessors EQN and TBL, math
typesetting and tables.  It requires a degree in advanced Greek to be
understood.
</FoO ThE bAr/>
dbadd info "some necessary notation" <<"</FoO ThE bAr/>"
Node: Some Necessary Notation		Next: Character Operations

                                   Any  ordinary  character  goes  into the
                                   buffer  (no  insert   command   needed).
                                   Commands  are  all control characters or
                                   other characters prefixed by Escape or a
                                   control-X. Escape  is  sometimes  called
                                   Meta or Altmode in EMACS.
^                                  A  control character.  ^F means "control
                                   F".
ESC                                A two-character command  sequence  where
                                   the  first  character  is Escape.  ESC-F
                                   means "ESCAPE then F".
ESC-X string                       A command designated "by hand".   "ESC-x
                                   read-file"  means:   type "Escape", then
                                   "x", then "read-file", then <cr>.
dot                                EMACS  term  for  cursor   position   in
                                   current buffer.
mark                               An  invisible set position in the buffer
                                   used by region commands.
region                             The area of the buffer between  the  dot
                                   and mark.
</FoO ThE bAr/>
dbadd info "emacs:working-directory" <<"</FoO ThE bAr/>"
Node: working-directory			Up: Commands, Previous: window-height, Next: write-abbrev-file

Returns the pathname of the current working directory.
</FoO ThE bAr/>
dbadd info "emacs:string-to-process" <<"</FoO ThE bAr/>"
Node: string-to-process			Up: Commands, Previous: string-to-char, Next: substr

(string-to-process "process-name" "string") -- The string is  sent  to  the
process.
</FoO ThE bAr/>
dbadd info "emacs:re-search-reverse" <<"</FoO ThE bAr/>"
Node: re-search-reverse			Up: Commands, Previous: re-search-forward, Next: read-abbrev-file

re-search-reverse is identical to search-reverse  except  that  the  search
string  is  a  regular  expression rather than an uninterpreted sequence of
characters.  See the section on  searching,  section    page  20  for  more
information.
</FoO ThE bAr/>
dbadd info "emacs:input conventions" <<"</FoO ThE bAr/>"
Node: Input Conventions			Up: Basics, Previous: The Screen, Next: Invoking Emacs
Throughout  this  manual, characters which are used as commands are printed
in bold face: X.  They will  sometimes  have  a  control  prefix  which  is
printed  as  an  uparrow character: ^X is control-X and is typed by holding
down  the  control  (often  labeled  ctrl  on  the  top  of  the  key)  and
simultaneously  striking  X.    Some  will have an escape (sometimes called
meta) prefix which is usually printed thus: ESC-X and typed by striking the
escape key (often labeled esc) then X.  And some  will  have  a  ^X  prefix
which  is  printed  ^XX  which  is  typed  by holding down the control key,
striking X, releasing the control key then striking X again.

For example, ESC-^J is typed by striking ESC then holding down the  control
key and striking J.  
</FoO ThE bAr/>
dbadd info "emacs:forward-paragraph" <<"</FoO ThE bAr/>"
Node: forward-paragraph			Up: Commands, Previous: forward-character, Next: forward-paren

Moves to the end of the current or following paragraph.  Blank  lines,  and
Scribe  and  nroff  command  lines separate paragraphs and are not parts of
paragraphs.
</FoO ThE bAr/>
dbadd info "emacs:expand-mlisp-word" <<"</FoO ThE bAr/>"
Node: expand-mlisp-word			Up: Commands, Previous: expand-mlisp-variable, Next: extend-database-search-list

Prompt for the name of a command then insert the  name  as  text  into  the
current  buffer.   This is very handly for typing in MLisp functions.  It's
also fairly useful to bind it to a key for easy access.
</FoO ThE bAr/>
dbadd info "emacs:dump-syntax-table" <<"</FoO ThE bAr/>"
Node: dump-syntax-table			Up: Commands, Previous: dot, Next: edit-macro

Dumps  a  readable  listing  of a syntax table into a buffer and makes that
buffer visible.
</FoO ThE bAr/>
dbadd info "emacs:describe-bindings" <<"</FoO ThE bAr/>"
Node: describe-bindings			Up: Commands, Previous: delete-window, Next: describe-command

Places  in  the  Help  window  a  list  of all the keys and the name of the
procedure that they are bound to.  This listing is  suitable  for  printing
and  making you own quick-reference card for your own customized version of
Emacs.
</FoO ThE bAr/>
dbadd info "emacs:beginning-of-line" <<"</FoO ThE bAr/>"
Node: beginning-of-line			Up: Commands, Previous: beginning-of-file, Next: beginning-of-window

Move  dot  to the beginning of the line in the current buffer that contains
dot; that is, to just after the preceeding end-of-line or the beginning  of
the buffer.
</FoO ThE bAr/>
dbadd info "emacs:beginning-of-file" <<"</FoO ThE bAr/>"
Node: beginning-of-file			Up: Commands, Previous: baud-rate, Next: beginning-of-line

Move dot to just before the first character of the current buffer.
</FoO ThE bAr/>
dbadd info "emacs:users-login-name" <<"</FoO ThE bAr/>"
Node: users-login-name			Up: Commands, Previous: users-full-name, Next: visit-file

MLisp function that returns the users login name as a string.
</FoO ThE bAr/>
dbadd info "emacs:stop-remembering" <<"</FoO ThE bAr/>"
Node: stop-remembering			Up: Commands, Previous: stop-process, Next: string-to-char

Stops  remembering  keystrokes,  as  initiated  by  ^X(.    The  remembered
keystrokes are not forgotten and may be re-executed with ^XE.
</FoO ThE bAr/>
dbadd info "emacs:save-restriction" <<"</FoO ThE bAr/>"
Node: save-restriction			Up: Commands, Previous: save-excursion, Next: save-window-excursion

Save-restriction  is  only  useful to people writing MLisp programs.  It is
used to save the region restriction for the current buffer  (and  only  the
region  restriction)  during  the  execution  of  some  subexpression  that
presumably  uses  region  restrictions.    The  value  of   (save-excursion
expressions...) is the value of the last expression evaluated.
</FoO ThE bAr/>
dbadd info "emacs:page-next-window" <<"</FoO ThE bAr/>"
Node: page-next-window			Up: Commands, Previous: novalue, Next: parse-error-messages-in-region

Repositions the window below the current one (or the top one if the current
window is the lowest one on the screen) on the displayed buffer so that the
next page of the buffer is visible in the window (where a page is  a  group
of  lines  slightly  smaller  than a window).  In other words, it flips you
forward a page in the buffer of the other window.

If ESC-^V is given an argument it will flip the buffer  backwards  a  page,
rather  than  forwards.  So ESC-^V is roughly equivalent to ^V and ^UESC-^V
is roughly equivalent to ESC-V except that they deal with the other window.
Yes, yes, yes.  I realize that this is a bogus  command  structure,  but  I
didn't invent it.  Besides, you can learn to love it.
</FoO ThE bAr/>
dbadd info "emacs:mlisp statements" <<"</FoO ThE bAr/>"
File: emacs     Node: MLisp statements     Up: Commands

There are several MLisp statements that deal with control flow in MLisp
programs:

* menu:
* while::			For loops
* if::				For conditionals
* progn::			For block structuring
* save-excursion::		Execute a block of statements in a protected
				environment.
* save-window-excursion::	Like save excursion
* error-occurred::		Error trap
</FoO ThE bAr/>
dbadd info "emacs:macro operations" <<"</FoO ThE bAr/>"
Node: Macro Operations		Next: Compiling (Make) Operations., Up: Quick

* Menu:
* start-remembering::         ^X-( Start remembering keystrokes, ie.  start
                                   defining a keyboard macro
* stop-remembering::          ^X-) Stop remembering keystrokes, ie. end the
                                   definition
* execute-keyboard-macro::    ^X-e Execute   remembered   keystrokes,   ie.
                                   execute the keyboard macro
</FoO ThE bAr/>
dbadd info "emacs:forward-sentence" <<"</FoO ThE bAr/>"
Node: forward-sentence			Up: Commands, Previous: forward-paren, Next: forward-word

Move  dot  forward  to  the  beginning of the next sentence.  Sentences are
seperated by a `.', `?' or `!' followed by whitespace.
</FoO ThE bAr/>
dbadd info "emacs:expand-file-name" <<"</FoO ThE bAr/>"
Node: expand-file-name			Up: Commands, Previous: exit-emacs, Next: expand-mlisp-variable

Takes a string representing a file name and expands  it  into  an  absolute
pathname.    For  example,  if  the  current directory is "/usr/frodo" then
(expand-file-name "../bilbo") will return "/usr/bilbo".
</FoO ThE bAr/>
dbadd info "emacs:describe-command" <<"</FoO ThE bAr/>"
Node: describe-command			Up: Commands, Previous: describe-bindings, Next: describe-key

Uses the Info system to describe some named command.  You will be  prompted
in  the  minibuf for the name of a command and then Info will be invoked to
show you the manual entry describing it.  You can then use Info  to  browse
around, or simply type ^C to resume editing.
</FoO ThE bAr/>
dbadd info "emacs:continue-process" <<"</FoO ThE bAr/>"
Node: continue-process			Up: Commands, Previous: concat, Next: copy-region-to-buffer

(continue-process  "process-name")  --  Continue  a  process   stopped   by
stop-process.
</FoO ThE bAr/>
dbadd info "emacs:change-directory" <<"</FoO ThE bAr/>"
Node: change-directory			Up: Commands, Previous: change-current-process, Next: char-to-string

Changes  the  current  directory  (for  Emacs) to the named directory.  All
future file write and reads (^X^S, ^X^V, etc.) will be interpreted relative
to that directory.
</FoO ThE bAr/>
dbadd info "emacs:word operations" <<"</FoO ThE bAr/>"
Node: Word Operations			Next: Line Operations, Up: Quick

* Menu:
* backward-word::            ESC-b Move left (Back)
* forward-word::             ESC-f Move right (Forward)
* delete-next-word::         ESC-d Delete word right
* delete-previous-word::     ESC-h Delete word left
* case-word-capitalize::     ESC-c Capitalize word
* case-word-lower::          ESC-l Lowercase word
* case-word-upper::          ESC-u Uppercase word
* case-word-invert::         ESC-^ Invert case of word
</FoO ThE bAr/>
dbadd info "emacs:move-dot-to-x-y" <<"</FoO ThE bAr/>"
Node: move-dot-to-x-y			Up: Commands, Previous: modify-syntax-entry, Next: move-to-comment-column

(move-dot-to-x-y x y) switches to the buffer and sets dot to the positon of
the  character  that  was  displayed at screen coordinates x,y.  If x and y
don't point to a valid character (eg. if they are out of bounds or point to
a mode line) an error is flagged.

This function is intended for use supporting mice and tablets.  One way  to
do  this is to have depressions of the tablet button generate a sequence of
keystrokes that Emacs sees as normal tty  input.    If,  for  example,  the
tablet  was  to  transmit  the four charcters ESC-M-x-y when the button was
depressed over character x,y then  the  following  function  would  provide
simple support for it:

    (defun (mouse-set-dot x y
               (setq x (get-tty-character))
               (setq y (get-tty-character))
               (move-dot-to-x-y x y)
           ))

    (bind-to-key "mouse-set-dot" "\eM")

</FoO ThE bAr/>
dbadd info "emacs:line operations" <<"</FoO ThE bAr/>"
Node: Line Operations			Next: Paragraph Operations, Up: Quick

* Menu:
* beginning-of-line::           ^A Move to the beginning of the line
* end-of-line::                 ^E Move to the end of the line
* newline-and-backup::          ^O Open up a line for typing
* kill-to-end-of-line::         ^K Kill  from  dot to end of line (^Y yanks
                                   it back at dot)
</FoO ThE bAr/>
dbadd info "emacs:get-tty-command" <<"</FoO ThE bAr/>"
Node: get-tty-command			Up: Commands, Previous: get-tty-character, Next: get-tty-string

(get-tty-command prompt) prompts for the name of a declared function (using
command  completion  & providing help) and returns the name of the function
as a string.    For  example,  the  expand-mlisp-word  function  is  simply
(insert-string (get-tty-command ": expand-mlisp-word ")).
</FoO ThE bAr/>
dbadd info "emacs:case-word-upper" <<"</FoO ThE bAr/>"
Node: case-word-upper			Up: Commands, Previous: case-word-lower, Next: change-current-process

Change  all  alphabetic characters in the current word (the one above or to
the left of dot) to upper case.
</FoO ThE bAr/>
dbadd info "emacs:use-old-buffer" <<"</FoO ThE bAr/>"
Node: use-old-buffer			Up: Commands, Previous: use-local-map, Next: use-syntax-table

Prompt for the name of the buffer and associate it with the current window.
The old buffer associated with this window merely loses  that  association:
it  is not erased or changed in any way.  The buffer must already exist, in
contrast with ^XB.
</FoO ThE bAr/>
dbadd info "emacs:search-reverse" <<"</FoO ThE bAr/>"
Node: search-reverse			Up: Commands, Previous: search-forward, Next: self-insert

Prompt for a string and search for a match in the  current  buffer,  moving
backwards  from  dot, stopping at the beginning of the buffer.  Dot is left
at the beginning of the matched string if a match is found, or  is  unmoved
if  not.    See  the  section  on  searching,  section    page  20 for more
information.
</FoO ThE bAr/>
dbadd info "emacs:replace-string" <<"</FoO ThE bAr/>"
Node: replace-string			Up: Commands, Previous: remove-local-binding, Next: reset-filter

Replace  all  occurrences  of  one  string for another, starting at dot and
ending and the end of the buffer.  Emacs prompts  for  an  old  and  a  new
string  in  the  minibuffer (the line at the bottom of the screen).  Unlike
query-replace-string Emacs  doesn't  ask  any  questions  about  particular
occurrences, it just changes them.  Dot will be left after the last changed
string.    See  the  section  on  searching,  section    page  20  for more
information on search strings.
</FoO ThE bAr/>
dbadd info "emacs:preceding-char" <<"</FoO ThE bAr/>"
Node: preceding-char			Up: Commands, Previous: pop-to-buffer, Next: prefix-argument-loop

(preceding-char) is an MLisp function that returns the character immediatly
preceding  dot.    The  null  character  (0)  is  returned if dot is at the
beginning of the buffer.  Remember that dot is not `at' some character,  it
is between two characters.
</FoO ThE bAr/>
dbadd info "emacs:invoking emacs" <<"</FoO ThE bAr/>"
Node: Invoking Emacs			Up: Basics, Previous: Input Conventions, Next: Basic Commands

Emacs is invoked as a Unix command by typing 

    emacs files

to  the Shell (the Unix command interpreter).  Emacs will start up, editing
the named files.  You will probably only want to name one  file.    If  you
don't  specify  any  names, Emacs will use the same names that it was given
the last time that it was invoked.  Gory details on the invocation of Emacs
can be found in section , page 20.
</FoO ThE bAr/>
dbadd info "emacs:current-indent" <<"</FoO ThE bAr/>"
Node: current-indent			Up: Commands, Previous: current-file-name, Next: current-process

(current-indent) is an MLisp function the returns the amount of  whitespace
at the beginning of the line which dot is in (the printing column number of
the first non-whitespace character).
</FoO ThE bAr/>
dbadd info "emacs:ctlchar-with-^" <<"</FoO ThE bAr/>"
Node: ctlchar-with-^			Up: Variables, Previous: comment-column, Next: files-should-end-with-newline

If  set  ON control characters are printed as ^C (an '^' character followed
by the upper case alphabetic that corresponds to  the  control  character),
otherwise  they  are  printed  according  to the usual Unix convention ('\'
followed by a three digit octal number).  (default OFF)
</FoO ThE bAr/>
dbadd info "emacs:basic commands" <<"</FoO ThE bAr/>"
Node: Basic Commands			Up: Basics, Previous: Invoking Emacs, Next: Unbound Commands

Normally each character you type is interpreted individually by Emacs as  a
command.    The  instant  you type a character the command it represents is
performed immediatly.

All of the normal printing characters when struck  just  insert  themselves
into the buffer at dot.

To  move  dot  there are several simple commands.  ^F moves dot forward one
character, ^B moves it backward one character.  ^N moves dot  to  the  same
column  on  the  next  line, ^P moves it to the same column on the previous
line.

String searches may be used to move dot by using the ^S command  to  search
in the forward direction and ^R to search in the reverse direction.

Deletions  may be performed using ^H (backspace) to delete the character to
the left of dot and ^D to delete the character to the right of dot.

The following table summarizes all of the motion and deletion commands.
                                        Direction
                                   Move          Delete
Units of Motion                 Left   Right   Left   Right
Characters                       ^B     ^F      ^H      ^D
Words                          ESC-B   ESC-F   ESC-H  ESC-D
Intra line                       ^A     ^E       ^K
Inter line                       ^P     ^N
</FoO ThE bAr/>
dbadd info "emacs:append-to-file" <<"</FoO ThE bAr/>"
Node: append-to-file			Up: Commands, Previous: append-region-to-buffer, Next: apropos

Takes the contents of the current buffer and appends it to the named  file.
If the files doesn't exist, it will be created.
</FoO ThE bAr/>
dbadd info "emacs:Invoking Emacs" <<"</FoO ThE bAr/>"
Node: Invoking Emacs			Up: Basics, Previous: Input Conventions, Next: Basic Commands

Emacs is invoked as a Unix command by typing 

    emacs files

to the Shell (the Unix command interpreter).  Emacs will start up,  editing
the  named  files.    You will probably only want to name one file.  If you
don't specify any names, Emacs will use the same names that  it  was  given
the last time that it was invoked.  Gory details on the invocation of Emacs
can be found in section , page 20.
</FoO ThE bAr/>
dbadd info "character operations" <<"</FoO ThE bAr/>"
Node: Character Operations		Next: Word Operations

* backward-character::          ^B Move left (Back)
* forward-character::           ^F Move right (Forward)
* previous-line::               ^P Move up (Previous)
* next-line::                   ^N Move down (Next)
* delete-next-character::       ^D Delete right
* delete-previous-character::                    ^H or BS or DEL or RUBOUT
                                   Delete left
* transpose-characters::        ^T Transpose  previous 2 characters (ht_ ->
                                   th_)
* quote-character::             ^Q Literally  inserts  (quotes)  the   next
                                   character typed (e.g. ^Q-^L)
* argument-prefix::             ^U Provide  a  numeric argument of n to the
                                   command that follows (n defaults  to  4,
                                   eg. try ^U-^N and ^U-^U-^F)
* newline::               ^M or CR Newline
* newline-and-indent::    ^J or NL newline followed by an indent
</FoO ThE bAr/>
dbadd info "emacs:window-height" <<"</FoO ThE bAr/>"
Node: window-height			Up: Commands, Previous: widen-region, Next: working-directory

Returns the number of text lines of  a  window  that  are  visible  on  the
screen.  
</FoO ThE bAr/>
dbadd info "emacs:use-local-map" <<"</FoO ThE bAr/>"
Node: use-local-map			Up: Commands, Previous: use-global-map, Next: use-old-buffer

(use-local-map  "mapname")  uses  the  named  map  to be used for the local
interpretation of all key strokes.  use-global-map is used  to  change  the
global  interpretation  of  key strokes.  See the section on keymaps,  page
21, for more information.
</FoO ThE bAr/>
dbadd info "emacs:prefix-string" <<"</FoO ThE bAr/>"
Node: prefix-string			Up: Variables, Previous: prefix-argument-provided, Next: quick-redisplay

The  string  that is inserted after an automatic newline has been generated
in response to going past the right margin.  This is generally used by  the
language-dependent commenting features.  (default "")
</FoO ThE bAr/>
dbadd info "emacs:narrow-region" <<"</FoO ThE bAr/>"
Node: narrow-region			Up: Commands, Previous: nargs, Next: newline

The  narrow-region  command  sets  the  restriction to encompass the region
between dot and mark.  Text outside this region will henceforth be  totally
invisible.    It  won't appear on the screen and it won't be manipulable by
any editing commands.  This can be useful, for instance, when you  want  to
perform a replacement within a few paragraphs: just narrow down to a region
enclosing the paragraphs and execute replace-string.
</FoO ThE bAr/>
dbadd info "emacs:filter-region" <<"</FoO ThE bAr/>"
Node: filter-region			Up: Commands, Previous: file-exists, Next: following-char

Take  the  region between dot and mark and pass it as the standard input to
the given command line.  Its standard output replaces  the  region  between
dot and mark.  Use this to run a region through a Unix style-filter.
</FoO ThE bAr/>
dbadd info "emacs:error-message" <<"</FoO ThE bAr/>"
Node: error-message			Up: Commands, Previous: erase-region, Next: error-occured

(error-message  "string-expressions")  Sends  the string-expressions to the
screen as an error message where it  will  appear  at  the  bottom  of  the
screen.      Emacs   will  return  to  keyboard  level,  unless  caught  by
error-occured.
</FoO ThE bAr/>
dbadd info "emacs:delete-buffer" <<"</FoO ThE bAr/>"
Node: delete-buffer			Up: Commands, Previous: defun, Next: delete-macro

Deletes the named buffer.
</FoO ThE bAr/>
dbadd info "emacs:backward-word" <<"</FoO ThE bAr/>"
Node: backward-word			Up: Commands, Previous: backward-sentence, Next: baud-rate

If in the middle of a word, go to the beginning of that word, otherwise  go
to  the  beginning  of  the  preceding  word.    A  word  is  a sequence of
alphanumerics.
</FoO ThE bAr/>
dbadd info "emacs:stop-process" <<"</FoO ThE bAr/>"
Node: stop-process			Up: Commands, Previous: start-remembering, Next: stop-remembering

(stop-process  "process-name")  -- Tell the process to stop by sending it a
stop signal.  Use continue-process to carry on.
</FoO ThE bAr/>
dbadd info "emacs:list-buffers" <<"</FoO ThE bAr/>"
Node: list-buffers			Up: Commands, Previous: line-to-top-of-window, Next: list-databases

Produces  a listing of all existing buffers giving their names, the name of
the associated file (if there is one), the  number  of  characters  in  the
buffer  and  an  indication  of whether or not the buffer has been modified
since it was read or written from the associated file.
</FoO ThE bAr/>
dbadd info "emacs:getting help" <<"</FoO ThE bAr/>"
Node: Getting Help			Up: Basics, Previous: Unbound Commands, Next: Buffers and Windows

Emacs  has  many  commands that let you ask Emacs for help about how to use
Emacs.  The simplest one is ESC-? (apropos) which asks you  for  a  keyword
and  then  displays  a  list of those commands whose full name contains the
keyword as a substring.  For  example,  to  find  out  which  commands  are
available  for  dealing with windows, type ESC-?, Emacs will ask "Keyword:"
and you reply "window".  A list like the following appears:

    beginning-of-window          ESC-,
    delete-other-windows         ^X1
    delete-window                ^XD
    end-of-window                ESC-.
    enlarge-window               ^XZ
    line-to-top-of-window        ESC-!
    next-window                  ^XN
    page-next-window             ESC-^V
    previous-window              ^XP
    shrink-window                ^X^Z
    split-current-window         ^X2

To get  detailed  information  about  some  command,  the  describe-command
command  can be used.  It asks for the name of a command, then displays the
long documentation for it from the manual.  For example, if you wanted more
information    about    the    shrink-window     command,     just     type
"ESC-Xdescribe-command shrink-window" and Emacs will reply:

     shrink-window
                 Makes the current window one line shorter, and the win
               (or the one above if there is no window below) one  line
               Can't be used if there is only one window on the screen.

If  you  want  to  find  out  what  command  is  bound to a particular key,
describe-key will do it for you.  Describe-bindings can be used to  make  a
"wall  chart"  description  of  the  key  bindings in the currently running
Emacs, taking into account all of the bindings you have made.
</FoO ThE bAr/>
dbadd info "emacs:erase-region" <<"</FoO ThE bAr/>"
Node: erase-region			Up: Commands, Previous: erase-buffer, Next: error-message

Erases the region between dot and mark.  It  is  like  delete-to-killbuffer
except that it doesn't move the text to the kill buffer.
</FoO ThE bAr/>
dbadd info "emacs:delete-macro" <<"</FoO ThE bAr/>"
Node: delete-macro			Up: Commands, Previous: delete-buffer, Next: delete-next-character
Delete the named macro.
</FoO ThE bAr/>
dbadd info "emacs:auto-execute" <<"</FoO ThE bAr/>"
Node: auto-execute			Up: Commands, Previous: argv, Next: autoload

Prompt for and remember a command name and a file name  pattern.    When  a
file  is  read  in via visit-file or read-file whose name matches the given
pattern the given command will be executed.  The command is  generally  one
which sets the mode for the buffer.  Patterns must be of the form "*string"
or  "string*":    "*string"  matches any filename whose suffix is "string";
"string*"  matches  any  filename  prefixed  by  "string".    For  example,
auto-execute  c-mode  *.c will put Emacs into C mode for all files with the
extension ".c".
</FoO ThE bAr/>
dbadd info "emacs:yank-buffer" <<"</FoO ThE bAr/>"
Node: yank-buffer			Up: Commands, Previous: write-named-file, Next: yank-from-killbuffer

Take the contents of the buffer whose name is prompted for and insert it at
dot in the current buffer.  Dot is left after the inserted text.
</FoO ThE bAr/>
dbadd info "emacs:set-default" <<"</FoO ThE bAr/>"
Node: set-default			Up: Commands, Previous: set-auto-fill-hook, Next: set-mark

This  commands bears the same relationship to setq-default that set does to
setq.  It is the command that you use from the keyboard to set the  default
value  of  some  variable.    See  the description of setq-default for more
detailed information.
</FoO ThE bAr/>
dbadd info "emacs:self-insert" <<"</FoO ThE bAr/>"
Node: self-insert			Up: Commands, Previous: search-reverse, Next: send-string-to-terminal

This is tied to those keys which  are  supposed  to  self-insert.    It  is
roughly the same as (insert-character (last-key-struck)) with the exception
that it doesn't work unless it is bound to a key.
</FoO ThE bAr/>
dbadd info "emacs:pause-emacs" <<"</FoO ThE bAr/>"
Node: pause-emacs			Up: Commands, Previous: parse-error-messages-in-region, Next: pop-to-buffer

Pause, giving control back to the superior  shell  using  the  job  control
facility  of  Berkeley  Unix.    The  screen is cleaned up before the shell
regains control, and when the shell gives control back to Emacs the  screen
will  be fixed up again.  Users of the sea-shell (csh) will probably rather
use this command than "return-to-monitor", which is similar, except that it
recursivly invokes a new shell.
</FoO ThE bAr/>
dbadd info "emacs:int-process" <<"</FoO ThE bAr/>"
Node: int-process			Up: Commands, Previous: insert-string, Next: interactive

(int-process "process-name") -- Send an interrupt signal to the process.
</FoO ThE bAr/>
dbadd info "emacs:getting out" <<"</FoO ThE bAr/>"
Node: Getting Out		Next: Screen And Screen Operations, Up: Quick

* Menu:
* write-current-file::       ^X-^S Save the file being worked on
* write-named-file::         ^X-^W Write the current  buffer  into  a  file
                                   with a different name
* write-modified-files::     ^X-^M Write out all modified files
* write-file-exit::          ^X-^F Write out all modified files and exit
* exit-emacs::   ^C or ESC-^C or ^X-^C Finish by exiting to the shell
* return-to-monitor::           ^_ Recursively push (escape) to a new shell
</FoO ThE bAr/>
dbadd info "emacs:end-of-file" <<"</FoO ThE bAr/>"
Node: end-of-file			Up: Commands, Previous: emacs-version, Next: end-of-line

Move dot to just after the last character of the buffer.
</FoO ThE bAr/>
dbadd info "emacs:abbrev mode" <<"</FoO ThE bAr/>"
Node: Abbrev mode			Up: Basics, Next: Extensibility

Abbrev  mode allows the user to type abbreviations into a document and have
Emacs automatically expand them.  If you have an abbrev called  "rhp"  that
has  been  defined  to  expand  to  the string "rhinocerous party" and have
turned on abbrev mode then  typing  the  first  non-alphanumeric  character
after  having  typed  "rhp"  causes  the  string  "rhp"  to  be replaced by
"rhinocerous party".  The  capitalization  of  the  typed  in  abbreviation
controls  the  capitalization  of  the  expansion:    "Rhp" would expand as
"Rhinocerous party" and "RHP" would expand as "Rhinocerous Party".

Abbreviations are defined in abbrev tables.  There is a global abbrev table
which is used regardless of which buffer you are in,  and  a  local  abbrev
table which is selected on a buffer by buffer basis, generally depending on
the major mode of the buffer.

Define-global-abbrev  takes  two arguments: the name of an abbreviation and
the phrase that it is to expand to.  The abbreviation will  be  defined  in
the  global abbrev table.  Define-local-abbrev is like define-global-abbrev
except that it defines the abbreviation in the current local abbrev table.

The use-abbrev-table command is used to select (by name) which abbrev table
is to be used locally in this buffer.  The same abbrev table may be used in
several buffers.  The mode packages (like electric-c and text) all  set  up
abbrev tables whose name matches the name of the mode.

The  switch  abbrev-mode  must  be  turned  on before Emacs will attempt to
expand abbreviations.  When abbrev-mode is turned on, the  string  "abbrev"
appears   in   the   mode   section  of  the  mode  line  for  the  buffer.
Use-abbrev-table automatically turns on abbrev-mode if either the global or
new local abbrev tables are non-empty.

All abbreviations currently defined can be written out to a file using  the
write-abbrev-file  command.    Such  a file can be edited (if you wish) and
later  read   back   in   to   define   the   same   abbreviations   again.
Read-abbrev-file  reads  in  such a file and screams if it cannot be found,
quietly-read-abbrev-file doesn't complain  (it  is  primarily  for  use  in
startups  so  that  you  can load a current-directory dependant abbrev file
without worrying about the case where the file doesn't exist).

People writing MLisp programs can have procedures invoked when an abbrev is
triggered.      Use   the    commands    define-hooked-global-abbrev    and
define-hooked-local-abbrev  to  do  this.    These  behave  exactly  as the
unhooked versions do except that they also associate a named  command  with
the   abbrev.    When  the  abbrev  triggers,  rather  than  replacing  the
abbreviation with the expansion phrase the hook procedure is  invoked.  The
character  that trigged the abbrev will not have been inserted, but will be
inserted immediatly after the hook procedure returns [unless the  procedure
returns  0].    The abbreviation will be the word immediatly to the left of
dot, and the function abbrev-expansion returns the phrase that  the  abbrev
would have expanded to.
</FoO ThE bAr/>
dbadd info "emacs:word moves" <<"</FoO ThE bAr/>"
File: emacs     Node: word moves     Up: Moving around

* menu:
* backward-word::			(ESC-b)
* forward-word::			(ESC-f)
</FoO ThE bAr/>
dbadd info "emacs:scribe-bib" <<"</FoO ThE bAr/>"
Node: scribe-bib			Up: Packages, Previous: scribe, Next: spell

Scribe-bib mode provides a set of functions that create Scribe bibliography
database  entries.  For  each  bibliography type scribe-bib mode provides a
function that when executed prompts the user  for  appropriate  fields  and
constructs  a  new  entry  of  the  proper  type. The name of each of these
functions is identical to the name of the corresponding bibliography  type.
Once  the  entry is created it can be edited using standard Emacs commands.
The bibliography creation functions are invoked by name using ESC-X and are
listed below:

@article         Create an @Article bibliography entry.

@book            Create an @Book bibliography entry.

@booklet         Create an @Booklet bibliography entry.

@inbook          Create an @InBook bibliography entry.

@incollection    Create an @InCollection bibliography entry.

@inproceedings   Create an @InProceedings bibliography entry.

@manual          Create an @Manual bibliography entry.

@mastersthesis   Create an @MastersThesis bibliography entry.

@misc            Create an @Misc bibliography entry.

@phdthesis       Create an @PhdThesis bibliography entry.

@proceedings     Create an @Proceedings bibliography entry.

@techreport      Create an @TechReport bibliography entry.

@unpublished     Create an @Unpublished bibliography entry.

</FoO ThE bAr/>
dbadd info "emacs:newcompile" <<"</FoO ThE bAr/>"
Node: newcompile			Up: Packages, Previous: occur, Next: paragraphs

</FoO ThE bAr/>
dbadd info "emacs:looking-at" <<"</FoO ThE bAr/>"
Node: looking-at			Up: Commands, Previous: local-binding-of, Next: mark

(looking-at "SearchString") is true iff the given regular expression search
string matches the text immediatly following dot.    This  is  for  use  in
packages that want to do a limited sort of parsing.  For example, if dot is
at  the  beginning of a line then (looking-at "[ \t]*else]) will be true if
the line starts with an "else".  See section , page 20 for more information
on regular expressions.
</FoO ThE bAr/>
dbadd info "emacs:init files" <<"</FoO ThE bAr/>"
Node: init files					Up: top

When EMACS starts up, it looks for a file called ".emacs_pro" on your login
directory.  If it finds one, it loads it.  .emacs_pro files are used to
customize key bindings, pre-load libraries you use frequently, and define
personal functions that don't rate a library of their own.  They are written
as a series of MLisp expressions that are executed as they are read. The
best way to learn about .emacs_pro files is to ask someone who knows.

* menu:
* trivial example::
* default profile::		This is the profile that is used if you
				don't define one yourself.
* complicated profile::		The profile used by the author of Emacs,
				but far from the most complicated profile
				around.
* Extensibility::		How to write MLisp functions (not for the
				faint of heart!)
</FoO ThE bAr/>
dbadd info "word operations" <<"</FoO ThE bAr/>"
Node: Word Operations			Next: Line Operations

* backward-word::            ESC-b Move left (Back)
* forward-word::             ESC-f Move right (Forward)
* delete-next-word::         ESC-d Delete word right
* delete-previous-word::     ESC-h Delete word left
* case-word-capitalize::     ESC-c Capitalize word
* case-word-lower::          ESC-l Lowercase word
* case-word-upper::          ESC-u Uppercase word
* case-word-invert::         ESC-^ Invert case of word
</FoO ThE bAr/>
dbadd info "emacs:variables" <<"</FoO ThE bAr/>"
Node: variables,    		Up: Top,	    Next:  Commands

The following variables may be set from within Emacs to control the way that
it behaves:

* menu:
* ask-about-buffer-names::
* backup-by-copying::
* backup-by-copying-when-linked::
* backup-when-writing::
* buffer-is-modified::
* case-fold-search::
* checkpoint-frequency::
* comment-column::
* ctlchar-with-^::
* files-should-end-with-newline::
* global-mode-string::
* help-on-command-completion::
* left-margin::
* mode-line-format::
* mode-string::
* needs-checkpointing::
* pop-up-windows::
* prefix-argument::
* prefix-argument-provided::
* prefix-string::
* quick-redisplay::
* replace-case::
* right-margin::
* scroll-step::
* silently-kill-processes::
* stack-trace-on-error::
* tab-size::
* this-command::
* track-eol-on-^N-^P::
* unlink-checkpoint-files::
* visible-bell::
* wrap-long-lines::
</FoO ThE bAr/>
dbadd info "emacs:undo-more" <<"</FoO ThE bAr/>"
Node: undo-more				Up: Commands, Previous: undo-boundary, Next: unlink-file

Undoes one more command from what was  last  undone.    undo-more  must  be
preceeded by either an undo or an undo-more.  This is usually used by first
invoking undo to undo a command, then invoking undo-more repeatedly to undo
more  and more commands, until you've retreated to the state you want to be
back to.  See the section on undoing, page UNDOING.
</FoO ThE bAr/>
dbadd info "emacs:text-mode" <<"</FoO ThE bAr/>"
Node: text-mode				Up: Packages, Previous: tags, Next: time

Implements  the text-mode command which ties ESC-j to justify-paragraph and
sets up autofill with a left margin of 1 and a right margin of 77.  
</FoO ThE bAr/>
dbadd info "emacs:baud-rate" <<"</FoO ThE bAr/>"
Node: baud-rate				Up: Commands, Previous: backward-word, Next: beginning-of-file

An MLisp function that returns what Emacs thinks is the baud  rate  of  the
communication  line  to  the terminal.  The baud rate is (usually) 10 times
the number of characters transmitted ber second.  (Baud-rate) can  be  used
for  such  things  as  conditionally  setting  the  display-file-percentage
variable            in            your            Emacs            profile:
(setq display-file-percentage (> (baud-rate) 600)) 
</FoO ThE bAr/>
dbadd info "emacs:set-mark" <<"</FoO ThE bAr/>"
Node: set-mark				Up: Commands, Previous: set-default, Next: setq

Puts the marker for this buffer at the place where dot is now,  and  leaves
it  there.    As text is inserted or deleted around the mark, the mark will
remain in place.  Use ^X^X to move to the currently marked position.
</FoO ThE bAr/>
dbadd info "emacs:packages" <<"</FoO ThE bAr/>"
File: emacs     Node: Packages     Up: Top

All of the following packages are a standard part of the Emacs library.  To
gain access to any of the commands that they define, just load them in using
the 'load' commane (*Note:: load)

* menu:
* c-mode::		C program assistance
* dired::		a simple directory editor
* electric-c::		slightly more assistance with C programs
* undo::		undo the effects of previous commands
* incr-search::		incremental search
* info::		the info system that you're using now
* lisp-mode::		another lisp assist package
* newcompile::		a replacement for ^X^E
* paragraphs::		paragraph motion commands
* pascal::		assistance for Pascal programming
* processP::		commands for controlling processes
* pwd::			pwd and cd commands
* rmail::		a wizzo mail system
* scribe::		assistance for writing Scribe documents
* scribe-bib::		assistance for writing Scribe bibliographies
* spell::		check the spelling in a document
* tags::		finds routines from a collection of modules
* text-mode::		assistance for writing simple text
* time::		time and load stats for the mode line
* writeregion::		write a region to a file
* buff::		one line buffer listing
* el-lisp::		assistance with lisp programs
* goto::		a goto-line function
* occur::		find all occurances of a string
</FoO ThE bAr/>
dbadd info "emacs:newline" <<"</FoO ThE bAr/>"
Node: newline				Up: Commands, Previous: narrow-region, Next: newline-and-backup

Just inserts a newline character into the buffer -- this is what the RETURN
(^M) key is generally bound to.
</FoO ThE bAr/>
dbadd info "emacs:el-lisp" <<"</FoO ThE bAr/>"
Node: el-lisp				Up: Packages, Previous: electric-c, Next: goto

</FoO ThE bAr/>
dbadd info "emacs:Keymaps" <<"</FoO ThE bAr/>"
Node: Keymaps				Up: Basics, Previous: Searching, Next: Region Restrictions

When  a  user  is  typing  to  Emacs the keystrokes are interpreted using a
keymap.  A keymap is just a table with one entry for each character in  the
ASCII character set.  Each entry either names a function or another keymap.
When the user strikes a key, the corresponding keymap entry is examined and
the indicated action is performed.  If the key is bound to a function, then
that  function will be invoked.  If the key is bound to another keymap then
that keymap is used for interpreting the next keystroke.

There is always a global keymap and a local keymap, as keys are  read  from
the  keyboard  the  two  trees  are traversed in parallel (you can think of
keymaps as FSMs, with keystrokes triggering transitions).  When  either  of
the  traversals reaches a leaf, that function is invoked and interpretation
is reset to the roots of the trees.

The root keymaps are selected using  the  use-global-map  or  use-local-map
commands.  A new empty keymap is created using the define-keymap command.

The  contents  of  a  keymap  can  be  changed by using the bind-to-key and
local-bind-to-key commands.  These two commands  take  two  arguments:  the
name  of the function to be bound and the keystroke sequence to which it is
to be bound.  This  keystroke  sequence  is  interpreted  relative  to  the
current      local     or     global     keymaps.          For     example,
(bind-to-key "define-keymap" "\^Zd") binds the  define-keymap  function  to
the keystroke sequence `^Z' followed by `d'.

A  named  keymap  behaves just like a function, it can be bound to a key or
executed within an MLisp function.  When it  is  executed  from  within  an
MLisp  function, it causes the next keystroke to be interpreted relative to
that map.

The following sample uses the keymap to partially simulate the  vi  editor.
Different  keymaps  are used to simulate the different modes in vi: command
mode and insertion mode.

(defun
    (insert-before              ; Enter insertion mode
        (use-global-map "vi-insertion-mode"))

    (insert-after               ; Also enter insertion mode, but after
                                ; the current character
        (forward-character)
        (use-global-map "vi-insertion-mode"))

    (exit-insertion             ; Exit insertion mode and return to
                                ; command mode
        (use-global-map "vi-command-mode"))

    (replace-one
        (insert-character (get-tty-character))
        (delete-next-character))

    (next-skip
        (beginning-of-line)
        (next-line)
        (skip-white-space))

    (prev-skip
        (beginning-of-line)
        (previous-line)
        (skip-white-space))

    (skip-white-space
        (while (& (! (eolp)) (| (= (following-char) ' ') (= (following-
            (forward-character)))

    (vi                         ; Start behaving like vi
        (use-global-map "vi-command-mode"))
)

; setup vi mode tables
(define-keymap "vi-command-mode")
(define-keymap "vi-insertion-mode")

(use-global-map "vi-insertion-mode"); Setup the insertion mode map
(bind-to-key "execute-extended-command" "\^X")
(progn i
    (setq i ' ')
    (while (< i 0177)
        (bind-to-key "self-insert" i)
        (setq i (+ i 1))))
(bind-to-key "self-insert" "\011")
(bind-to-key "newline" "\015")
(bind-to-key "self-insert" "\012")
(bind-to-key "delete-previous-character" "\010")
(bind-to-key "delete-previous-character" "\177")
(bind-to-key "exit-insertion" "\033")

(use-global-map "vi-command-mode"); Setup the command mode map
(bind-to-key "execute-extended-command" "\^X")
(bind-to-key "next-line" "\^n")
(bind-to-key "previous-line" "\^p")
(bind-to-key "forward-word" "w")
(bind-to-key "backward-word" "b")
(bind-to-key "search-forward" "/")
(bind-to-key "search-reverse" "?")
(bind-to-key "beginning-of-line" "0")
(bind-to-key "end-of-line" "$")
(bind-to-key "forward-character" " ")
(bind-to-key "backward-character" "\^h")
(bind-to-key "backward-character" "h")
(bind-to-key "insert-after" "a")
(bind-to-key "insert-before" "i")
(bind-to-key "replace-one" "r")
(bind-to-key "next-skip" "+")
(bind-to-key "next-skip" "\^m")
(bind-to-key "prev-skip" "-")
(use-global-map "default-global-keymap")

</FoO ThE bAr/>
dbadd info "emacs:search" <<"</FoO ThE bAr/>"
Node: Search				Next: Replace, Up: Quick

* Menu:
* re-search-forward::           ^S Search forward
* re-search-reverse::           ^R Search backward
</FoO ThE bAr/>
dbadd info "emacs:pascal" <<"</FoO ThE bAr/>"
Node: pascal				Up: Packages, Previous: paragraphs, Next: processP

</FoO ThE bAr/>
dbadd info "emacs:basics" <<"</FoO ThE bAr/>"
File: emacs     Node: Basics     Up: Top

Fool!  There is no such thing as a gentle introduction to Emacs.  Trial by
fire is the only way.  You might try reading the manual.


The following tidbits might help though:

* menu:
* The Screen::
* Input Conventions::
* Invoking Emacs::
* Basic Commands::
* Unbound Commands::
* Getting Help::
* Buffers and Windows::
* Terminal types::
* Compiling programs::
* Searching::
* Dealing with collections of files::
* Abbrev mode::
* Extensibility::
* Keymaps::
* Region Restrictions::
* Mode Lines::
</FoO ThE bAr/>
dbadd info "emacs:while" <<"</FoO ThE bAr/>"
Node: while				Up: Commands, Previous: visit-file, Next: widen-region

(while  test  expressions...)  is an MLisp function that executes the given
expressions while the test is true.
</FoO ThE bAr/>
dbadd info "emacs:usage" <<"</FoO ThE bAr/>"
Node: usage		Up: mscompil		Next: Variables

First, say M-X load mscompil.

Then, with a mainsail source file in the buffer, when you're ready to
compile do C-X C-E.  Mscompil first saves the file if necessary, then ships
it to mainsail to compile.  Mscompil knows about packages: if the file is a
multi-module package file, it will prompt for

MODULE (mod1 mod2..): 

just like MAINSAIL does.  (Except that Mscompil doesn't care if you
put it in quotes or not.)

When the compilation is over, a log of the compilation (what you would have
seen MAINSAIL type out) appears in the bottom window, with your source file
on top.  Mscompil tells you whether there were any errors.  If there were,
you will find that the cursor is positioned at the first error's location in
the source code, and the bottom window shows the error-message.  You can fix
the error, then say C-X C-N to see the next error.  Mscompil will tell you
when none are left.  When you think you've fixed everything, you can say C-X
C-E again.

Mscompil uses the "page nnn line mmm" message to find the error in
the source file, so if you've added or deleted lines in correcting
an error, positioning on subsequent errors will be off by that
amount.

Mscompil uses position in the log file to keep track of which error is
next.  So if you want to run through the errors again, switch to the
window whose mode-line says "MSCOMPIL...", move to the top
of the buffer, go back to the window with the source file, and say
C-X C-N.
</FoO ThE bAr/>
dbadd info "emacs:shell" <<"</FoO ThE bAr/>"
Node: shell				Up: Commands, Previous: setq-default, Next: shrink-window

The shell command is used to either start or reenter a shell process.  When
the shell command is executed, if a shell process doesn't exist then one is
created  (running the standard ``sh'') tied to a buffer named ``shell'.  In
any case, the shell buffer becomes the current one and dot is positioned at
the end of it.  In that buffer output from the shell and programs run  with
it  will  appear.    Anything typed into it will get sent to the subprocess
when the return key is struck.  This lets you interact with a  shell  using
Emacs,  and  all  of  it's editing capability, as an intermediary.  You can
scroll backwards over a session, pick up pieces of text from  other  places
and  use  them as input, edit while watching the execution of some program,
and much more...
</FoO ThE bAr/>
dbadd info "emacs:occur" <<"</FoO ThE bAr/>"
Node: occur				Up: Packages, Previous: lisp-mode, Next: newcompile

The  occur  package  allows  one  to  find  the occurances of a string in a
buffer.  It contains one function

Occurances      When  invoked,  prompts with "Search for all occurances of:
                ".  It then lists (in a new buffer) all lines  contain  the
                string you type following dot.  Possible options (listed at
                the  bottom  of  the  screen) allow you to page through the
                listing buffer or abort the function.

In addition, a global variable controls the action of the function:

&Occurances-Extra-Lines
                is  a  global  variable  that  controls  how   many   extra
                surrounding  lines  are  printed  in  addition  to the line
                containing the string found.  If this variable is 0 then NO
                additional lines are printed.  If this variable is  greater
                than  0  then it will print that many lines above and below
                the line on which the string was found.  When printing more
                than one line per match in this fashion, it will also print
                a seperator of '----------------' so you can tell where the
                different matches begin and end.  At the end of the  buffer
                it prints '<<<End of Occur>>>'.

</FoO ThE bAr/>
dbadd info "emacs:dired" <<"</FoO ThE bAr/>"
Node: dired				Up: Packages, Previous: c-mode, Next: electric-c

The  dired  package implements the dired command which provides some simple
convenient directory editing facilities.  When you run dired  it  will  ask
for  the  name  of  a  directory, displays a listing of it in a buffer, and
processes commands to examine files and possibly mark  them  for  deletion.
When  you're through with dired it actually deletes the marked files, after
asking for confirmation.  The commands it recognizes are:

d               Marks the current file for deletion.  A `D' will appear  at
                the  left margin.  It does not actually delete the file, it
                just marks it.  The deletion will be performed  when  dired
                is exited.  It also makes the next file be the current one.

u               Removes  the  deletion mark from the current file.  This is
                the command to use if you change your mind about deleting a
                file.  It also makes the next file be the current one.

RUBOUT          Removes the deletion mark  from  the  line  preceeding  the
                current  one.  If you mark a file for deletion with `d' the
                current file will be advanced to the  next  line.    RUBOUT
                undoes both the advancing and the marking for deletion.

e, v            Examine a file put putting it in another window and doing a
                recursive-edit on it.  To resume dired type ^C.

r               Removes  the  current  file from the directory listing.  It
                doesn't delete the file, it just gets rid of the  directory
                listing  entry.    Use  it to remove some of the clutter on
                your screen.

q, ^C           Exits dired.  For  each  file  that  has  been  marked  for
                deletion you will be asked for confirmation.  If you answer
                `y' the file will be deleted, otherwise not.

n, ^N           Moves to the next entry in the directory listing.

p, ^P           Moves to the previous entry in the directory listing.

^V              Moves to the next page in the directory listing.

ESC-v           Moves to the previous page in the directory listing.

ESC-<           Moves to the beginning of the directory listing.

ESC->           Moves to the end of the directory listing.

</FoO ThE bAr/>
dbadd info "info:vital" <<"</FoO ThE bAr/>"
(progn (beginning-of-file)
       (replace-string "@@@" (users-full-name))
       (beginning-of-file))

Node: vital						Up: live

Dear @@@,

Are you tired of the same old humdrum routine?
Well, @@@, this letter can change your life!
Imagine the pride you'll feel (and the bits you'll save)
in your NEW CAREER:

	@@@, Professional Comment Stripper!

Call UNIX enterprises today!
(US citizens only -- must be fluent in upper-case).


</FoO ThE bAr/>
dbadd info "info:trees" <<"</FoO ThE bAr/>"
Node: trees	Previous: Footnotes	Up: Top		Next: Live

	This node needs a volunteer to finish writing it!
</FoO ThE bAr/>
dbadd info "emacs:mice" <<"</FoO ThE bAr/>"
File: emacs     Node: Mice     Up: Top

Emacs now supports the perq tablet (the facility is quite general, but only
the perq is currently implemented).  To enable the tablet, you must be using
a suitable version of c100 (/usr/jag/perq/c100.seg on VLSI will do) and you
must load "mouse".

When using the tablet you will see two cursors on the screen: one being the
arrow associated with the tablet, and the other being the standard Emacs
cursor (usually a flashing blob).  Whenever you release a mouse button the
Emacs cursor will be set to the character pointed to by the tablet cursor
and a function dependent on the button will be executed.

Normally the four buttons are interpreted as:
			Yellow: page forward
	White: set dot and mark		Green: set dot
			Blue: page backward

In an info window they are interpreted as:
			Yellow: page forward
	White: Move to object		Green: Move to object
			Blue: page backward
		(the "object" is denoted by a menu item or header field
		 pointer)


* menu:
* move-dot-to-x-y::	Documentation for the MLisp function that makes
			tablet and mouse support possible.
</FoO ThE bAr/>
dbadd info "emacs:mail" <<"</FoO ThE bAr/>"
Node: Mail		Up: Quick

* Menu:
* rmail::		^X-r	Read mail
* rmail::		^X-m	Send mail
</FoO ThE bAr/>
dbadd info "emacs:eolp" <<"</FoO ThE bAr/>"
Node: eolp				Up: Commands, Previous: eobp, Next: eot-process

(eolp) is an MLisp predicate that is true iff dot is at the end of a line.
</FoO ThE bAr/>
dbadd info "emacs:buff" <<"</FoO ThE bAr/>"
Node: buff				Up: Packages, Next: c-mode

Loading   the   buff  package  replaces  the  binding  for  ^X-^B  (usually
list-buffers) with one-line-buffer-list.

one-line-buffer-list
                Gives a one-line buffer list in the mini-buffer.    If  the
                buffer  list  is longer than one line, it will print a line
                at a time and wait for  a  character  to  be  typed  before
                moving  to  the  next line.  Buffers that have been changed
                since they were last saved are prefixed  with  an  asterisk
                (*),  buffers  with  no associated file are prefixed with a
                hash-mark (#), and  empty  buffers  are  prefixed  with  an
                at-sign (@).

</FoO ThE bAr/>
dbadd info "emacs:bolp" <<"</FoO ThE bAr/>"
Node: bolp				Up: Commands, Previous: bobp, Next: buffer-size

(bolp) is an MLisp predicate which is true iff dot is at the beginning of a
line.
</FoO ThE bAr/>
dbadd info "info:help" <<"</FoO ThE bAr/>"
File: info	Node: help	Next: Help-P

You are talking to a program INFO, for reading documentation.

  Right now you are looking at one "Node" of information.
A node contains text describing a specific topic at a specific
level of detail.  This node's topic is "how to use INFO".

  The top line of a node is its "Header".  This node's header (look at
it now) says that it is the node named "Help" in the file "INFO".
It says that the Next node after this one is the node called "Help-P".
An advanced INFO command lets you go to any node whose name you know.

  Besides a "Next", a node can have a "Previous" or an "Up".
But this node doesn't have either of those, as you can see.

  Now it's time to move on to the Next node, named "Help-P".
>> Type "N" to move there.
</FoO ThE bAr/>
dbadd info "emacs:set" <<"</FoO ThE bAr/>"
Node: set				Up: Commands, Previous: send-string-to-terminal, Next: set-auto-fill-hook

Set  the  value of some variable internal to Emacs.  Emacs will ask for the
name of a variable and a value to set it to.  The  variables  control  such
things as margins, display layout options, the behavior of search commands,
and  much  more.    The  available  variables  and  switches  are described
elsewhere.  Note that if set is used from MLisp the variable name must be a
string: (set "left-margin" 77).
</FoO ThE bAr/>
dbadd info "info:top" <<"</FoO ThE bAr/>"
File: info	Node: top	Up: (DIR)	Next: Add

INFO is a subsystem of emacs for reading documentation, which you are using
now.  

To learn how to use INFO, type the command "h".  It will bring you
to a programmed instruction sequence.

* Menu:

* Teco::	If you're familiar with INFO for PDP-10s you should
		visit this node for a summary of differences.
* Expert::      Advanced INFO commands: @, g, and control-meta-e
* Add::         Described how to add new nodes to the hierarchy.
                Also tells what nodes look like.
* Menus::       How to add to or create menus in info nodes.
* Footnotes::   How to add footnotes to info nodes.
* Trees::	How to create separate trees independent of the DIR node.
* Live::	Nodes with functionality
* Directory::	A list of all the files on the info directory
</FoO ThE bAr/>
dbadd info "info:add" <<"</FoO ThE bAr/>"
File: info	Node: add	Up: Top		Next: Menus

To add a new topic to the list in the directory, you must
 1) Create a pointer to it (a menu entry) in some node that
    already exists.
 2) Select that node (usually via the 'm' command) at which
    point Info will notice that it doesn't exist and ask you
    if you want to create it.  Answer "yes" and Info will create
    a template for the node and lets you edit it.  When you're
    done editing it will be added to the Info tree.

NOTE: You must have write permission on the database in order to add or
      edit nodes.

  The keywords "Node", "Previous", "Up" and "Next",  may appear in any
order, anywhere in the header line, but the recommended order is the
one in this sentence.  Each keyword must be followed by a colon,
spaces and tabs, and then the appropriate name.  The name may be
terminated with a Tab, a comma, or a CRLF.  A space does not end it -
node names may contain spaces.  The case of letters in the names is
insignificant. 

A node name has two forms.  A node in the current file is named by what
appears after the "Node: " in that node's first line.  For example, this
node's name is "ADD".  A node in another file is named by
"(filename)node-within-file", as in "(INFO)ADD" for this node.  Parts of the
filename which are the same as the default should be omitted for clarity;
usually, just the first name of the file suffices.  The name "(filename)Top"
can be abbreviated to just "(filename)".  By convention, the name "Top" is
used for the "highest" node in any single file - the node whose "Up" points
out of the file.  The Directory node is "(DIR)". The Top node of a document
file listed in the Directory should have an "Up: (DIR)" in it.

  The "Node:" name, in which a node states its own name, must not
contain a filename, since INFO when searching for a node does not
expect one to be there.  The Next, Previous and Up names may contain
them.  In this node, since the Up node is in the same file, it was not
necessary to use one. 

  Note that the nodes in this file have a File name in the header
line.  The File names are ignored by INFO, but they help the user
keep track of where he is (after all, just "Top" isn't much help).
</FoO ThE bAr/>
dbadd info "emacs:<<" <<"</FoO ThE bAr/>"
Node: <<				Up: Commands, Previous: <, Next: <=

(<<  e   e )  MLisp  function  that  returns  e   <<  e   (the C shift left
      1   2                                    1       2
operator).
</FoO ThE bAr/>
dbadd info "replace" <<"</FoO ThE bAr/>"
Node: Replace				Next: Region Operations

* replace-string::           ESC-r Replace one string with another
* query-replace-string::     ESC-q Query Replace, one string with another
</FoO ThE bAr/>
dbadd info "emacs:^" <<"</FoO ThE bAr/>"
Node: ^					Up: Commands, Previous: >>, Next: active-process

(^ e  e ) MLisp function that returns e  ^ e  (the C XOR operator).
    1  2                               1    2
</FoO ThE bAr/>
dbadd info "emacs:<" <<"</FoO ThE bAr/>"
Node: <					Up: Commands, Previous: /, Next: <<

(< e  e ) MLisp function that returns true iff e  < e .
    1  2                                        1    2
</FoO ThE bAr/>
dbadd info "emacs:*" <<"</FoO ThE bAr/>"
Node: *					Up: Commands, Previous: &, Next: +

(* e  e ) MLisp function that returns e  * e .
    1  2                               1    2
</FoO ThE bAr/>
dbadd info "dir:top" <<"</FoO ThE bAr/>"
Node: top					This is the top of the tree

This is the vax-emacs INFO structured documentation reader.  Type "h" for a
tutorial introduction to INFO, "?" for a list of INFO commands. Visit node
Info to find out how to add documentation to this tree.

* menu:

* Info: (info)Top		How to add to INFO
* Emacs: (emacs)Top		The vax EMACS editor
* Quick: (emacs)quick:		Quick reference to Emacs commands.
* Beginning::			Getting started on the VAX		
* Operating Systems::		VMS, UNIX and EUNICE
* Programming Systems::		Languages and support
* Document preparation::	Formatting systems for text: troff, ms
* Utilities::			Useful programs
</FoO ThE bAr/>
dbadd info "emacs:Command prefix, also known as META" <<"</FoO ThE bAr/>"
Node: Command prefix, also known as META	Up: Comm

The next character typed will be interpreted as a command based on the fact
that  it  was  preceded  by ESC.  The name meta for the ESC character comes
from  funny  keyboards at Stanford and MIT that have a Meta-shift key which
is used to extend the ASCII character set.  Lacking a Meta key, we make  do
with prefixing with an ESC character.  You may see (and hear) commands like
ESC-V  referred to as Meta-V.  Sometimes the ESC key is confusingly written
as $, so ESC-V would be written as $V.  ESC is also  occasionally  referred
to  as Altmode, from the labeling of a key on those old favorites, model 33
teletypes.
</FoO ThE bAr/>
dbadd info "emacs:help-on-command-completion-error" <<"</FoO ThE bAr/>"
Node: help-on-command-completion-error	Up: Variab

If ON Emacs will print a list of possibilities when an ambiguous command is
given,  otherwise  it  just  rings the bell and waits for you to type more.
(default ON)
</FoO ThE bAr/>
dbadd info "emacs:parse-error-messages-in-region" <<"</FoO ThE bAr/>"
Node: parse-error-messages-in-region	Up: Commands, Previous: page-next-window, Next: pause-emacs

Parses  the  region  between  dot  and  mark  for error messages (as in the
compile-it (^X^E) command)  and  sets  up  for  subsequent  invocations  of
next-error  (^X^N).    See  the  description of the compile-it command, and
section  (page 18).
</FoO ThE bAr/>
dbadd info "emacs:backup-by-copying-when-linked" <<"</FoO ThE bAr/>"
Node: backup-by-copying-when-linked	Up: Variables, Previous: backup-by-copying, Next: backup-when-writing

If true, then when a backup of a file is  made  (see  the  section  on  the
backup-before-writing  variable)  then  if  the  link  count of the file is
greater than 1, rather than doing the  fancy  link/unlink  footwork,  Emacs
copies the original file onto the backup.  If the link count is 1, then the
link/unlink  trick  is  pulled.  This preserves link information when it is
important, but still manages reasonable performance the rest of  the  time.
See  the  section  on the backup-by-copying variable for a description of a
how to have owner & I-number information preserved.  (default OFF)
</FoO ThE bAr/>
dbadd info "emacs:forward-balanced-paren-line" <<"</FoO ThE bAr/>"
Node: forward-balanced-paren-line	Up: Commands, Previous: following-char, Next: forward-character

Moves dot forward until either

   - The end of the buffer is reached.

   - An  unmatched  close  parenthesis, ')', is encountered.  That is,
     unmatched between there and the starting position of dot.

   - The beginning of a line  is  encountered  at  "parenthesis  level
     zero".   That is, without an unmatched '(' existing between there
     and the starting position of dot.

The definitions of parenthesis and strings from the syntax  table  for  the
current buffer are used.
</FoO ThE bAr/>
dbadd info "emacs:extend-database-search-list" <<"</FoO ThE bAr/>"
Node: extend-database-search-list	Up: Commands, Previous: expand-mlisp-word, Next: fetch-database-entry

(extend-database-search-list dbname filename) adds the given data base file
to the data base search list (dbname).  If the database is already  in  the
search  list  then  it  is left, otherwise the new database is added at the
beginning of the list of databases.
</FoO ThE bAr/>
dbadd info "emacs:define-hooked-local-abbrev" <<"</FoO ThE bAr/>"
Node: define-hooked-local-abbrev	Up: Commands, Previous: define-hooked-global-abbrev, Next: define-keyboard-macro

See the description of define-hooked-global-abbrev.
</FoO ThE bAr/>
dbadd info "emacs:execute-extended-command" <<"</FoO ThE bAr/>"
Node: execute-extended-command		Up: Commands, Previous: exchange-dot-and-mark, Next: execute-keyboard-macro

Emacs will prompt in the minibuffer (the line at the bottom of the  screen)
for a command from the extended set.  These deal with rarely used features.
Commands are parsed using a Twenex style command interpreter:  you can type
ESC or space to invoke command completion, or '?' for help with what you're
allowed  to type at that point.  This doesn't work if it's asking for a key
or macro name.
</FoO ThE bAr/>
dbadd info "emacs:unlink-checkpoint-files" <<"</FoO ThE bAr/>"
Node: unlink-checkpoint-files		Up: Variables, Previous: track-eol-on-^N-^P, Next: visible-bell

If  ON Emacs will unlink the corresponding checkpoint file after the master
copy is written -- this avoids having a lot of .CKP files lying around  but
it  does compromise safety a little.  For example, as you're editing a file
called "foo.c" Emacs will be periodically  be  writing  a  checkpoint  file
called  "foo.c.CKP"  that  contains  all  of your recent changes.  When you
rewrite the file (with ^X^F or ^X^S for example) if unlink-checkpoint-files
is ON then the .CKP file will be  unlinked,  otherwise  it  will  be  left.
(default OFF)
</FoO ThE bAr/>
dbadd info "emacs:append-region-to-buffer" <<"</FoO ThE bAr/>"
Node: append-region-to-buffer		Up: Commands, Previous: active-process, Next: append-to-file

Appends the region between dot and mark to the named buffer.   Neither  the
original  text in the destination buffer nor the text in the region between
dot and mark will be disturbed.
</FoO ThE bAr/>
dbadd info "screen and screen operations" <<"</FoO ThE bAr/>"
Node: Screen And Screen Operations	Next: Buffer And File Operations

* next-page::                   ^V Show next screen page
* previous-page::            ESC-V Show previous screen page
* redraw-display::              ^L Redisplay screen
* scroll-one-line-up::          ^Z Scroll screen up
* scroll-one-line-down::     ESC-Z Scroll screen down
* line-to-top-of-window::    ESC-! Move  the  line  dot is on to top of the
                                   screen
* beginning-of-window::      ESC-, Move cursor to beginning of window
* end-of-window::            ESC-. Move cursor to end of window
* split-current-window::      ^X-2 Split the current window in two  windows
                                   (same buffer shown in each)
* delete-other-windows::      ^X-1 Resume   single  window  (using  current
                                   buffer)
* delete-window::             ^X-d Delete the current window, giving  space
                                   to window below
* next-window::               ^X-n Move cursor to next window
* previous-window::           ^X-p Move cursor to previous window
* page-next-window::        ESC-^V Display  the  next  screen  page  in the
                                   other window
* shrink-window::            ^X-^Z Shrink window
* enlarge-window::            ^X-z Enlarge window
</FoO ThE bAr/>
dbadd info "emacs:start-filtered-process" <<"</FoO ThE bAr/>"
Node: start-filtered-process		Up: Commands, Previous: split-current-window, Next: start-process

(start-filtered-process   "command"   "buffer-name"  "on-output-procedure")
-- Does the same thing as start-process except that things are  set  up  so
that "on-output-procedure" is automatically called whenever output has been
received  from  this  process.    This procedure can access the name of the
process producing the output by refering to the variable  MPX-process,  and
can retrieve the output itself by calling the procedure process-output.

     The   filter  procedure  must  be  careful  to  avoid  generating
     side-effects (eg. search-forward).  Moreover, if it  attempts  to
     go  to  the terminal for information, output from other processes
     may be lost.
</FoO ThE bAr/>
dbadd info "emacs:line-to-top-of-window" <<"</FoO ThE bAr/>"
Node: line-to-top-of-window		Up: Commands, Previous: length, Next: list-buffers

What  more  can  I  say?  This one is handy if you've just searched for the
declaration of a procedure, and want to see the whole body (or as  much  of
it as possible).
</FoO ThE bAr/>
dbadd info "emacs:expand-mlisp-variable" <<"</FoO ThE bAr/>"
Node: expand-mlisp-variable		Up: Commands, Previous: expand-file-name, Next: expand-mlisp-word

Prompts for the name of a declared variable then inserts the name  as  text
into  the  current  buffer.    This  is  very  handly  for  typing in MLisp
functions.  It's also fairly useful to bind it to a key for easy access.
</FoO ThE bAr/>
dbadd info "emacs:exchange-dot-and-mark" <<"</FoO ThE bAr/>"
Node: exchange-dot-and-mark		Up: Commands, Previous: error-occured, Next: execute-extended-command

Sets  dot  to  the  currently marked position and marks the old position of
dot.  Useful for bouncing back and forth between  two  points  in  a  file;
particularly  useful  when  the two points delimit a region of text that is
going to be operated on by some command like ^W (erase region).
</FoO ThE bAr/>
dbadd info "emacs:write-modified-files" <<"</FoO ThE bAr/>"
Node: write-modified-files		Up: Commands, Previous: write-file-exit, Next: write-named-file

Write each modified buffer (as indicated by ^X^B) onto the file whose  name
is  associated  with  the buffer.  Emacs will complain if a modified buffer
does not have an associated file.
</FoO ThE bAr/>
dbadd info "emacs:stack-trace-on-error" <<"</FoO ThE bAr/>"
Node: stack-trace-on-error		Up: Variables, Previous: silently-kill-processes, Next: tab-size

If  ON  Emacs  will  write  a MLisp stack trace to the "Stack trace" buffer
whenever an error is encountered from within an MLisp function (even inside
an error-occured).  This is  all  there  is  in  the  way  of  a  debugging
facility. (default OFF)
</FoO ThE bAr/>
dbadd info "emacs:scroll-one-line-down" <<"</FoO ThE bAr/>"
Node: scroll-one-line-down		Up: Commands, Previous: save-window-excursion, Next: scroll-one-line-up

Repositions the current window on the current buffer so that the line which
is currently the second to the last line in the  window  becomes  the  last
--  effectivly  it moves the buffer down one line in the window.  ^Z is its
inverse.
</FoO ThE bAr/>
dbadd info "emacs:paragraph operations" <<"</FoO ThE bAr/>"
Node: Paragraph Operations		Next: Getting Out, Up: Quick

* Menu:
* backward-paragraph::       ESC-[ Move to beginning of the paragraph
* forward-paragraph::        ESC-] Move to end of the paragraph
* indent-C-procedure::       ESC-j Justify the current paragraph
</FoO ThE bAr/>
dbadd info "emacs:fetch-database-entry" <<"</FoO ThE bAr/>"
Node: fetch-database-entry		Up: Commands, Previous: extend-database-search-list, Next: file-exists

(fetch-database-entry  dbname  key)  takes  the  entry  in  the  data  base
corresponding to the given key and inserts it into the current buffer.
</FoO ThE bAr/>
dbadd info "emacs:delete-to-killbuffer" <<"</FoO ThE bAr/>"
Node: delete-to-killbuffer		Up: Commands, Previous: delete-region-to-buffer, Next: delete-white-space

Wipe  (kill,  delete) all characters between dot and the mark.  The deleted
text is moved to the kill buffer, which is emptied first.
</FoO ThE bAr/>
dbadd info "buffer and file operations" <<"</FoO ThE bAr/>"
Node: Buffer And File Operations	Next: Help And Helper Functions

* yank-from-killbuffer::        ^Y Yank back the last  thing  killed  (kill
                                   and delete are different)
* visit-file::               ^X-^V Get a file into a buffer for editing
* read-file::                ^X-^R Read a file into current buffer, erasing
                                   old contents
* insert-file::              ^X-^I Insert file at dot
* to-buffer::                ^X-^O Select   a  different  buffer  (it  must
                                   already exist)
* switch-to-buffer::          ^X-B Select a different buffer (it  need  not
                                   pre-exist)
* list-buffers::             ^X-^B Display a list of available buffers
* yank-buffer::             ESC-^Y Insert selected buffer at dot
* beginning-of-file::        ESC-< Move to the top of the current buffer
* end-of-file::              ESC-> Move to the end of the current buffer
</FoO ThE bAr/>
dbadd info "emacs:region restrictions" <<"</FoO ThE bAr/>"
Node: Region Restrictions		Up: Basics, Previous: Keymaps, Next: Mode Lines

The  portion  of  the buffer which Emacs considers visible when it performs
editing operations may be restricted to some subregion of the whole buffer.

The narrow-region command sets the  restriction  to  encompass  the  region
between  dot and mark.  Text outside this region will henceforth be totally
invisible.  It won't appear on the screen and it won't  be  manipulable  by
any  editing  commands.    It  will,  however,  be read and written by file
manipulation commands like read-file and write-current-file.  This  can  be
useful,  for  instance, when you want to perform a replacement within a few
paragraphs: just narrow down to  a  region  enclosing  the  paragraphs  and
execute replace-string.

The  widen-region  command  sets  the  restriction  to encompass the entire
buffer.  It is usually  used  after  a  narrow-region  to  restore  Emacs's
attention to the whole buffer.

Save-restriction  is  only  useful to people writing MLisp programs.  It is
used to save the region restriction for the current buffer  (and  only  the
region  restriction)  during  the  execution  of  some  subexpression  that
presumably uses  region  restrictions.    The  value  of  (save-restriction
expressions...) is the value of the last expression evaluated.
</FoO ThE bAr/>
dbadd info "emacs:current-buffer-name" <<"</FoO ThE bAr/>"
Node: current-buffer-name		Up: Commands, Previous: copy-region-to-buffer, Next: current-column

MLisp function that returns the current buffer name as a string.
</FoO ThE bAr/>
dbadd info "emacs:Region Restrictions" <<"</FoO ThE bAr/>"
Node: Region Restrictions		Up: Basics, Previous: Keymaps, Next: Mode Lines

The portion of the buffer which Emacs considers visible  when  it  performs
editing operations may be restricted to some subregion of the whole buffer.

The  narrow-region  command  sets  the  restriction to encompass the region
between dot and mark.  Text outside this region will henceforth be  totally
invisible.    It  won't appear on the screen and it won't be manipulable by
any editing commands.  It will,  however,  be  read  and  written  by  file
manipulation  commands  like read-file and write-current-file.  This can be
useful, for instance, when you want to perform a replacement within  a  few
paragraphs:  just  narrow  down  to  a  region enclosing the paragraphs and
execute replace-string.

The widen-region command sets  the  restriction  to  encompass  the  entire
buffer.    It  is  usually  used  after  a narrow-region to restore Emacs's
attention to the whole buffer.

Save-restriction  is  only  useful to people writing MLisp programs.  It is
used to save the region restriction for the current buffer  (and  only  the
region  restriction)  during  the  execution  of  some  subexpression  that
presumably uses  region  restrictions.    The  value  of  (save-restriction
expressions...) is the value of the last expression evaluated.
</FoO ThE bAr/>
dbadd info "emacs:write-current-file" <<"</FoO ThE bAr/>"
Node: write-current-file		Up: Commands, Previous: write-abbrev-file, Next: write-file-exit

Write the contents of  the  current  buffer  to  the  file  whose  name  is
associated with the buffer.
</FoO ThE bAr/>
dbadd info "emacs:compiling programs" <<"</FoO ThE bAr/>"
Node: Compiling programs		Up: Basics, Previous: Terminal types

One  of  the  most powerful features of Unix Emacs is the facility provided
for compiling programs and coping with error messages from  the  compilers.
It  essential  that  you understand the standard Unix program make (even if
you don't use Emacs).  This program takes  a  database  (a  makefile)  that
describes  the  relationships among files and how to regenerate (recompile)
them.  If you have a program that is made up of  many  little  pieces  that
have  to  be  individually  compiled  and carefully crafted together into a
single executable file, make can make your life orders of magnitude easier;
it  will  automatically  recompile  only  those  pieces  that  need  to  be
recompiled  and  put  them  together.    Emacs  has  a set of commands that
gracefully interact with this facility.

The ^X^E (execute) command writes all modified  buffers  and  executes  the
make program.  The output of make will be placed into a buffer called Error
log which will be visible in some window on the screen. As soon as make has
finished  Emacs parses all of its output to find all the error messages and
figure out the files and lines referred to.  All  of  this  information  is
squirreled away for later use by the ^X^N command.

The  ^X^N (next) command takes the next error message from the set prepared
by ^X^E and does three things with it:
   - Makes  the  message  itself  visible at the top of a window.  The
     buffer will be named Error log.

   - Does a visit (see the ^X^V command) on  the  file  in  which  the
     error occurred.

   - Sets  dot to the beginning of the line where the compiler saw the
     error. This setting of dot takes into account changes to the file
     that may have been made  since  the  compilation  was  attempted.
     Emacs  perfectly  compensates  for any changes that may have been
     made and always positions the text on  the  correct  line  (well,
     correct as far as the compiler was concerned; the compiler itself
     may have been a trifle confused about where the error occurred)

If you've seen all the error messages ^X^N will say so and do nothing else.

So, the general scenario for dealing with programs is:

   - Build  a  make  database  to  describe  how your program is to be
     compiled.

   - Compile your program from within Emacs by typing ^X^E.

   - If  there  were  errors,  step  through  them  by  typing   ^X^N,
     correcting the error, and typing ^X^N to get the next.

   - When  you  run  out  of  error  messages,  type  ^X^E  to try the
     compilation again.

   - When you finally manage to get your beast to compile without  any
     errors, type ^C to say goodbye to Emacs.

   - You'll  probably want to use sdb, the symbolic debugger, to debug
     your program.

</FoO ThE bAr/>
dbadd info "emacs:case-region-invert" <<"</FoO ThE bAr/>"
Node: case-region-invert		Up: Commands, Previous: case-region-capitalize, Next: case-region-lower

Invert the case of all alphabetic characters in the region between dot  and
mark.
</FoO ThE bAr/>
dbadd info "emacs:buffer-is-modified" <<"</FoO ThE bAr/>"
Node: buffer-is-modified		Up: Variables, Previous: backup-when-writing, Next: case-fold-search

Buffer-is-modified is true iff the current buffer has been  modified  since
it  was  last written out.  You may set if OFF (ie. to 0) if you want Emacs
to ignore the mods that have been made to this buffer -- it doesn't get you
back to the unmodified version, it just tells Emacs not  to  write  it  out
with the other modified files.  Emacs sets buffer-is-modified true any time
the buffer is modified.
</FoO ThE bAr/>
dbadd info "emacs:write-abbrev-file" <<"</FoO ThE bAr/>"
Node: write-abbrev-file			Up: Commands, Previous: working-directory, Next: write-current-file

Write  all  defined  abbrevs  to  a  named file.  This file is suitable for
reading back with read-abbrev-file.
</FoO ThE bAr/>
dbadd info "emacs:region operations" <<"</FoO ThE bAr/>"
Node: Region Operations			Next: Macro Operations, Up: Quick

* Menu:
* set-mark::                    ^@ Set the mark
* exchange-dot-and-mark::    ^X-^X Interchange dot and mark (i.e. go to the
                                   other end of the region)
* delete-to-killbuffer::        ^W Kill region (^Y yanks it back at dot)
</FoO ThE bAr/>
dbadd info "emacs:re-search-forward" <<"</FoO ThE bAr/>"
Node: re-search-forward			Up: Commands, Previous: re-replace-string, Next: re-search-reverse

re-search-forward  is  identical  to  search-forward except that the search
string is a regular expression rather than  an  uninterpreted  sequence  of
characters.    See  the  section  on  searching,  section  page 20 for more
information.
</FoO ThE bAr/>
dbadd info "emacs:local-bind-to-key" <<"</FoO ThE bAr/>"
Node: local-bind-to-key			Up: Commands, Previous: load, Next: local-binding-of

Prompt for the name of a command and a key and bind  that  command  to  the
given key but unlike bind-to-key the binding only has effect in the current
buffer.    This  is  generally  used  for  mode specific bindings that will
generally differ from buffer to buffer.
</FoO ThE bAr/>
dbadd info "emacs:illegal-operation" <<"</FoO ThE bAr/>"
Node: illegal-operation			Up: Commands, Previous: if, Next: indent-C-procedure

Illegal-operation  is  bound  to  those  keys  that  do  not have a defined
interpretation.  Executing illegal-operation is an error.    Most  notably,
^G,  ESC-^G, ^X^G are bound to illegal-opetation by default, so that typing
^G will always get you out of whatever strange state you are in.
</FoO ThE bAr/>
dbadd info "emacs:case-region-upper" <<"</FoO ThE bAr/>"
Node: case-region-upper			Up: Commands, Previous: case-region-lower, Next: case-word-capitalize

Change all alphabetic characters in the region  between  dot  and  mark  to
upper case.
</FoO ThE bAr/>
dbadd info "emacs:case-region-lower" <<"</FoO ThE bAr/>"
Node: case-region-lower			Up: Commands, Previous: case-region-invert, Next: case-region-upper

Change  all  alphabetic  characters  in  the region between dot and mark to
lower case.
</FoO ThE bAr/>
dbadd info "emacs:Input Conventions" <<"</FoO ThE bAr/>"
Node: Input Conventions			Up: Basics, Previous: The Screen, Next: Invoking Emacs

Throughout this manual, characters which are used as commands  are  printed
in  bold  face:  X.    They  will  sometimes have a control prefix which is
printed as an uparrow character: ^X is control-X and is  typed  by  holding
down  the  control  (often  labeled  ctrl  on  the  top  of  the  key)  and
simultaneously striking X.  Some will  have  an  escape  (sometimes  called
meta) prefix which is usually printed thus: ESC-X and typed by striking the
escape  key  (often  labeled  esc)  then X.  And some will have a ^X prefix
which is printed ^XX which is  typed  by  holding  down  the  control  key,
striking X, releasing the control key then striking X again.

For  example, ESC-^J is typed by striking ESC then holding down the control
key and striking J.  
</FoO ThE bAr/>
dbadd info "dir:programming systems" <<"</FoO ThE bAr/>"
Node: programming systems	Up: Top

	This node needs a volunteer to finish writing it!
</FoO ThE bAr/>
dbadd info "emacs:write-named-file" <<"</FoO ThE bAr/>"
Node: write-named-file			Up: Commands, Previous: write-modified-files, Next: yank-buffer

Prompt for a name; write the contents of the current buffer  to  the  named
file.
</FoO ThE bAr/>
dbadd info "emacs:mode-line-format" <<"</FoO ThE bAr/>"
Node: mode-line-format			Up: Variables, Previous: left-margin, Next: mode-string

mode-line-format  is  a buffer specific variable used to specify the format
of a mode line.  See section , page 21 for more information.
</FoO ThE bAr/>
dbadd info "emacs:default-tab-size" <<"</FoO ThE bAr/>"
Node: default-tab-size		Up: Top		Next: files-should-end-with-newline, Previous: default-right-margin

default-tab-size
            This  is  the value given to tab-size when a buffer is created.
          (default 8).
</FoO ThE bAr/>
dbadd info "emacs:write-file-exit" <<"</FoO ThE bAr/>"
Node: write-file-exit			Up: Commands, Previous: write-current-file, Next: write-modified-files

Write  all modified buffers to their associated files and if all goes well,
Emacs will exit.
</FoO ThE bAr/>
dbadd info "emacs:wrap-long-lines" <<"</FoO ThE bAr/>"
Node: wrap-long-lines			Up: Variables, Previous: visible-bell

If ON Emacs will display long lines by "wrapping" their  continuation  onto
the  next line (the first line will be terminated with a '\').  If OFF long
lines get truncated at the right edge of the screen and a '$' is display to
indicate that this has happened.  (default OFF)
</FoO ThE bAr/>
dbadd info "emacs:recursion-depth" <<"</FoO ThE bAr/>"
Node: recursion-depth			Up: Commands, Previous: read-file, Next: recursive-edit

Returns  the depth of nesting within recursive-edit's.  It returns 0 at the
outermost level.
</FoO ThE bAr/>
dbadd info "emacs:previous-window" <<"</FoO ThE bAr/>"
Node: previous-window			Up: Commands, Previous: previous-page, Next: print

Switches  to  the  window (and associated buffer) that is above the current
window.
</FoO ThE bAr/>
dbadd info "emacs:prefix-argument" <<"</FoO ThE bAr/>"
Node: prefix-argument			Up: Variables, Previous: pop-up-windows, Next: prefix-argument-provided

Every function invocation is always prefixed by a numeric argument,  either
explicitly  with ^Un or provide-prefix-argument.  The value of the variable
prefix-argument is the argument prefixed to the invocation of  the  current
MLisp function.  For example, if the following function:

    (defun
        (show-it
            (message (concat "The prefix argument is " prefix-argument)
        )
    )

were  bound  to  the  key ^A then typing ^U^A would cause the message ``The
prefix argument is 4'' to be printed, and ^U13^A would print  ``The  prefix
argument   is  13''.    See  also  the  commands  prefix-argument-loop  and
provide-prefix-argument.
</FoO ThE bAr/>
dbadd info "emacs:paragraph moves" <<"</FoO ThE bAr/>"
File: emacs     Node: paragraph moves     Up: Moving around

* menu:
* backward-paragraph::			(ESC-[)
* forward-paragraph::			(ESC-])
</FoO ThE bAr/>
dbadd info "emacs:case-word-lower" <<"</FoO ThE bAr/>"
Node: case-word-lower			Up: Commands, Previous: case-word-invert, Next: case-word-upper

Change all alphabetic characters in the current word (the one above  or  to
the left of dot) to lower case.
</FoO ThE bAr/>
dbadd info "emacs:argument-prefix" <<"</FoO ThE bAr/>"
Node: argument-prefix			Up: Commands, Previous: argc, Next: argv

When followed by a string of digits ^U causes that string of digits  to  be
interpreted as a numeric argument which is generally a repetition count for
the  following command.  For example, ^U10^N moves down 10 lines (the 10'th
next).  A string of n ^U's followed by a command provides  an  argument  to
                    n
that  command  of  4 .  For example, ^U^N moves down four lines, and ^U^U^N
moves down 16.  Argument-prefix  should  never  be  called  from  an  MLisp
function.
</FoO ThE bAr/>
dbadd info "emacs:abort-operation" <<"</FoO ThE bAr/>"
Node: abort-operation		Up: Top		Next: active-process, Previous: ^

abort-operation                                                          ^G
            Emacs  gives up on what it is trying to do now and goes back to
          standard input mode.  Rings the bell.  Use ^G whenever  Emacs  is
          in  a  state you don't like, for example, asking you for a string
          to be searched for when you decide that you don't want to  search
          for a string.
</FoO ThE bAr/>
dbadd info "emacs:terminal types" <<"</FoO ThE bAr/>"
Node: Terminal types			Up: Basics, Previous: Buffers and Windows, Next: Compiling programs

Grim reality being what it is, Emacs has to deal with a wide assortment  of
displays  from  many  manufacturers.    Each  manufacturer  has  their  own
perverted idea of how programs should communicate with the display,  so  it
is  important for Emacs to correctly be told what type of terminal is being
used.  Under Unix, this is done by setting the environment variable `TERM'.
Normally, the operating system should set this to correspond to the type of
terminal that you are using and you won't have to concern yourself with it.
However, problems may arise and there are a  few  things  that  you  should
know.

`TERM' is a string variable whose value is the name of the type of terminal
that  you  are  using.    If  you are using the standard Unix shell then it
should be set using the commands:  

    TERM=...
    export TERM

If you're using the C shell (csh) then it should be set using the  command:


    setenv TERM ...

where  `...'  is  the  appropriate  terminal  type.    Consult  your system
administrator for a current list of valid terminal types.  A good place  to
look  is the file ``/etc/termcap'', it contains a list of all the terminals
supported by Emacs.  A few of the more common values are:

concept-lnz     For Concepts with the special firmware for Emacs.
concept         Concept 100, 104 and 108's from HDS.
h19             For Heathkit or Zenith model 19 terminals.
vt100           For  VT100's  from  DEC,  or  any  of  the   thousands   of
                look-alikes.
aaa             For the Ann Arbor Ambassador.

</FoO ThE bAr/>
dbadd info "emacs:save-excursion" <<"</FoO ThE bAr/>"
Node: save-excursion			Up: Commands, Previous: return-to-monitor, Next: save-restriction

(save-excursion  expressions...)  is  an  MLisp function that evaluates the
given expressions and returns the value of the last  expression  evaluated.
It  is  much like progn except that before any expressions are executed dot
and the current buffer are "marked" (via the marker mechanism)  then  after
the last expression is executed dot and the current buffer are reset to the
marked  values.   This properly takes into account all movements of dot and
insertions and deletions that occur.  Save-excursion  is  useful  in  MLisp
functions  where you want to go do something somewhere else in this or some
other buffer but want to return to the same place  when  you're  done;  for
example, inserting a tab at the beginning of the current line.
</FoO ThE bAr/>
dbadd info "emacs:remove-binding" <<"</FoO ThE bAr/>"
Node: remove-binding			Up: Commands, Previous: remove-all-local-bindings, Next: remove-local-binding

Removes the global binding of the given key.  Actually, it just rebinds the
key to illegal-operation.
</FoO ThE bAr/>
dbadd info "emacs:get-tty-buffer" <<"</FoO ThE bAr/>"
Node: get-tty-buffer			Up: Commands, Previous: forward-word, Next: get-tty-character

Given a prompt string it reads the name of a buffer from the tty using  the
minibuf and providing command completion.
</FoO ThE bAr/>
dbadd info "emacs:command-prefix" <<"</FoO ThE bAr/>"
Node: command-prefix			Up: Commands, Next: compile-it

The next character typed will be interpreted as a command based on the fact
that it was preceded by ^X.
</FoO ThE bAr/>
dbadd info "emacs:backward-paren" <<"</FoO ThE bAr/>"
Node: backward-paren			Up: Commands, Previous: backward-paragraph, Next: backward-sentence

Moves  dot  backward  until  an  unmatched  open  parenthesis,  '(', or the
beginning of the buffer is found.  This can be used to aid in skipping over
Lisp S-expressions.  The definitions of parenthesis and  strings  from  the
syntax table for the current buffer are used.
</FoO ThE bAr/>
dbadd info "emacs:active-process" <<"</FoO ThE bAr/>"
Node: active-process			Up: Commands, Previous: ^, Next: append-region-to-buffer

(active-process)  --  Returns  the name of the active process as defined in
the section describing the process mechanism.
</FoO ThE bAr/>
dbadd info "emacs:undo-boundary" <<"</FoO ThE bAr/>"
Node: undo-boundary			Up: Commands, Previous: undo, Next: undo-more

undo-boundary lays down the boundary between two undoable commands.    When
commands  are  undone,  a  `command'  is  considered  to  be  the series of
operations between undo boundaries.  Normally, they are laid  down  between
keystrokes  but  MLisp  functions  may  choose  to  lay down more.  See the
section on undoing, page UNDOING.  
</FoO ThE bAr/>
dbadd info "emacs:moving around" <<"</FoO ThE bAr/>"
File: emacs     Node: Moving around     Up: Commands

All of the motion commands move the cursor up, down, left or right in terms
of some basic unit.

* menu:
* character moves::
* word moves::
* line moves::
* sentence moves::
* paragraph moves::
* window moves::
* parenthesised moves::
* summary table::
</FoO ThE bAr/>
dbadd info "emacs:error-occured" <<"</FoO ThE bAr/>"
Node: error-occured			Up: Commands, Previous: error-message, Next: exchange-dot-and-mark

(error-occured expressions...) executes the given expressions  and  ignores
their  values.   If all executed successfully, error-occured returns false.
Otherwise  it  returns  true  and  all  expressions  after  the  one  which
encountered the error will not be executed.
</FoO ThE bAr/>
dbadd info "emacs:end-of-window" <<"</FoO ThE bAr/>"
Node: end-of-window			Up: Commands, Previous: end-of-line, Next: enlarge-window

Move dot to just after the last character visible in the window.
</FoO ThE bAr/>
dbadd info "emacs:define-keymap" <<"</FoO ThE bAr/>"
Node: define-keymap			Up: Commands, Previous: define-keyboard-macro, Next: define-local-abbrev

(define-keymap "mapname") defines a new, empty, keymap with the given name.
See the section on keymaps,  page 21, for more information.
</FoO ThE bAr/>
dbadd info "emacs:visible-bell" <<"</FoO ThE bAr/>"
Node: visible-bell			Up: Variables, Previous: unlink-checkpoint-files, Next: wrap-long-lines

If  ON  Emacs  will  attempt  to  use  a visible bell, usually a horrendous
flashing of the screen, instead of the audible bell, when it  is  notifying
you  of  some  error.   This is a more "socially acceptable" technique when
people are working in a crowded terminal room.  (default OFF)
</FoO ThE bAr/>
dbadd info "emacs:introduction" <<"</FoO ThE bAr/>"
File: emacs     Node: Introduction     Up: Top

The documentation for Emacs is in a very sad state.  If you'd like to
volunteer to put in some work on the Info structures or the manual, please
contact James.Gosling@CMUA (only if you're at CMU, please...  if you're
elsewhere, you're on your own).

For now, the only documentation is in the manual, which is contained in this
Info tree.  If you start reading from the menu item labeled "The Screen"
you'll see most of the introductory parts of the manual.

* menu:
* The Screen::
* Input Conventions::
* Invoking Emacs::
* Basic Commands::
* Unbound Commands::
* Getting Help::
* Buffers and Windows::
* Terminal types::
* Compiling programs::
* Dealing with collections of files::
* Abbrev mode::
* Extensibility::
* Searching::
* Keymaps::
* Region Restrictions::
* Mode Lines::
</FoO ThE bAr/>
dbadd info "emacs:forward-word" <<"</FoO ThE bAr/>"
Node: forward-word			Up: Commands, Previous: forward-sentence, Next: get-tty-buffer

Move dot forward to the end of a word.  If not currently in the middle of a
word, skip all intervening punctuation.  Then skip over the  word,  leaving
dot  positioned after the last character of the word.  A word is a sequence
of alphanumerics.
</FoO ThE bAr/>
dbadd info "region operations" <<"</FoO ThE bAr/>"
Node: Region Operations			Next: Macro Operations

* set-mark::                    ^@ Set the mark
* exchange-dot-and-mark::    ^X-^X Interchange dot and mark (i.e. go to the
                                   other end of the region)
* delete-to-killbuffer::        ^W Kill region (^Y yanks it back at dot)
</FoO ThE bAr/>
dbadd info "emacs:unlink-file" <<"</FoO ThE bAr/>"
Node: unlink-file			Up: Commands, Previous: undo-more, Next: use-abbrev-table

(unlink-file fn) attempts to unlink (remove) the file named fn.  It returns
true if the unlink failed.
</FoO ThE bAr/>
dbadd info "emacs:next-window" <<"</FoO ThE bAr/>"
Node: next-window			Up: Commands, Previous: next-page, Next: nothing

Switches to the window (and associated buffer) that is  below  the  current
window.
</FoO ThE bAr/>
dbadd info "emacs:mode-string" <<"</FoO ThE bAr/>"
Node: mode-string			Up: Variables, Previous: mode-line-format, Next: needs-checkpointing

Mode-string is a buffer specific variable used in the construction of  mode
lines see section , page 21 for more information.
</FoO ThE bAr/>
dbadd info "emacs:incr-search" <<"</FoO ThE bAr/>"
Node: incr-search			Up: Packages, Previous: goto, Next: info

ITS Emacs has  a  the  search  command  that  is  unusual  in  that  it  is
"incremental";  it  begins  to  search  before you have finished typing the
search string. As you type in the search string, Emacs shows you  where  it
would  be  found.    When  you have typed enough characters to identify the
place you want, you can stop.  The incr-search package  perfectly  emulates
this  in  Unix  Emacs.    Typically  one binds incremental-search to ^S and
reverse-incremental-search to ^R.

The command to search is ^S (incremental-search).  ^S reads  in  characters
and positions the cursor at the first occurrence of the characters that you
have  typed.    If you type ^S and then F, the cursor moves right after the
first "F".  Type an "O", and see the cursor move to after the  first  "FO".
After  another  "O",  the  cursor  is after the first "FOO" after the place
where you started the search.  At the same time, the "FOO"  has  echoed  at
the bottom of the screen.

If  you  type  a  mistaken  character,  you can rub it out.  After the FOO,
typing a rubout makes the "O" disappear from  the  bottom  of  the  screen,
leaving only "FO".  The cursor moves back to the "FO".  Rubbing out the "O"
and "F" moves the cursor back to where you started the search.

When  you  are  satisfied  with the place you have reached, you can type an
ESC, which stops searching, leaving the cursor where the search brought it.
Also, any command not specially meaningful in searches stops the  searching
and  is then executed.  Thus, typing ^A would exit the search and then move
to the beginning of the line.  ESC is necessary only if  the  next  command
you  want  to  type  is a printing character, Rubout, ESC or another search
command, since those are the characters that would not exit the search.

Sometimes you search for "FOO" and find it, but not the one you expected to
find.  There was a second FOO that you forgot about,  before  the  one  you
were  looking  for.  Then type another ^S and the cursor will find the next
FOO.  This can be done any number of times.  If you overshoot, you can  rub
out  the  ^S's.    You  can also repeat the search after exiting it, if the
first thing you type after entering another search (when  the  argument  is
still empty) is a ^S.

If  your string is not found at all, the echo area says "Failing I-Search".
The cursor is after the place where Emacs found as much of your  string  as
it  could.    Thus, if you search for FOOT, and there is no FOOT, you might
see the cursor after the FOO in FOOL.  At  this  point  there  are  several
things you can do.  If your string was mistyped, you can rub some of it out
and  correct it.  If you like the place you have found, you can type ESC or
some other Emacs command to "accept what the search offered".  Or  you  can
type  ^G, which throws away the characters that could not be found (the "T"
in "FOOT"), leaving those that were found (the "FOO" in "FOOT").  A  second
^G at that point undoes the search entirely.

The  ^G  "quit"  command  does  special  things during searches; just what,
depends on the status of the search.  If the  search  has  found  what  you
specified  and  is  waiting  for  input, ^G cancels the entire search.  The
cursor moves back to where you started the search.  If ^G  is  typed  while
the  search is actually searching for something or updating the display, or
after search failed to find some of your input (having searched all the way
to the end of the file), then only the characters which have not been found
are discarded.  Having discarded them, the search  is  now  successful  and
waiting for more input, so a second ^G will cancel the entire search.  Make
sure  you  wait  for the first ^G to ding the bell before typing the second
one; if typed too soon, the second ^G may be confused with  the  first  and
effectively lost.

You can also type ^R at any time to start searching backwards.  If a search
fails because the place you started was too late in the file, you should do
this.    Repeated  ^R's  keep looking for more occurrences backwards.  A ^S
starts going forwards again.  ^R's can be rubbed  out  just  like  anything
else.    If  you  know  that  you  want to search backwards, you can use ^R
instead  of  ^S  to  start  the  search,  because  ^R  is  also  a  command
(reverse-incremental-search) to search backward.  
</FoO ThE bAr/>
dbadd info "emacs:fundamental" <<"</FoO ThE bAr/>"
File: emacs, Node: fundamental, Next: Isearch, Up: top, Previous: text

To invoke:

Say M-X load fundmode, or use the definition of fundamental-mode in
Util (see *note Util::.).


Fundamental mode is like normal mode, but delimiter-matching is turned
on for {[()]}; and tab is bound to indent-relative, which tries to do
reasonable things with indentation for random code; and M-tab is bound
to dedent-relative, which tries to align with the last line less indented
than the current one.
</FoO ThE bAr/>
dbadd info "emacs:file-exists" <<"</FoO ThE bAr/>"
Node: file-exists			Up: Commands, Previous: fetch-database-entry, Next: filter-region

(file-exists  fn) returns 1 if the file named by fn exists and is writable,
0 if it does not exist, and -1  if  it  exists  and  is  readable  but  not
writable.
</FoO ThE bAr/>
dbadd info "emacs:buffer-size" <<"</FoO ThE bAr/>"
Node: buffer-size			Up: Commands, Previous: bolp, Next: c-mode

(buffer-size) is an MLisp function that returns the number of characters in
the current buffer.
</FoO ThE bAr/>
dbadd info "emacs:Abbrev mode" <<"</FoO ThE bAr/>"
Node: Abbrev mode			Up: Basics, Next: Extensibility

Abbrev mode allows the user to type abbreviations into a document and  have
Emacs  automatically  expand them.  If you have an abbrev called "rhp" that
has been defined to expand to  the  string  "rhinocerous  party"  and  have
turned  on  abbrev  mode  then  typing the first non-alphanumeric character
after having typed  "rhp"  causes  the  string  "rhp"  to  be  replaced  by
"rhinocerous  party".    The  capitalization  of  the typed in abbreviation
controls the capitalization of  the  expansion:    "Rhp"  would  expand  as
"Rhinocerous party" and "RHP" would expand as "Rhinocerous Party".

Abbreviations are defined in abbrev tables.  There is a global abbrev table
which  is  used  regardless  of which buffer you are in, and a local abbrev
table which is selected on a buffer by buffer basis, generally depending on
the major mode of the buffer.

Define-global-abbrev takes two arguments: the name of an  abbreviation  and
the  phrase  that  it is to expand to.  The abbreviation will be defined in
the global abbrev table.  Define-local-abbrev is like  define-global-abbrev
except that it defines the abbreviation in the current local abbrev table.

The use-abbrev-table command is used to select (by name) which abbrev table
is to be used locally in this buffer.  The same abbrev table may be used in
several  buffers.   The mode packages (like electric-c and text) all set up
abbrev tables whose name matches the name of the mode.

The switch abbrev-mode must be turned  on  before  Emacs  will  attempt  to
expand  abbreviations.   When abbrev-mode is turned on, the string "abbrev"
appears  in  the  mode  section  of  the  mode   line   for   the   buffer.
Use-abbrev-table automatically turns on abbrev-mode if either the global or
new local abbrev tables are non-empty.

All  abbreviations currently defined can be written out to a file using the
write-abbrev-file command.  Such a file can be edited  (if  you  wish)  and
later   read   back   in   to   define   the   same   abbreviations  again.
Read-abbrev-file reads in such a file and screams if it  cannot  be  found,
quietly-read-abbrev-file  doesn't  complain  (it  is  primarily  for use in
startups so that you can load a  current-directory  dependant  abbrev  file
without worrying about the case where the file doesn't exist).

People writing MLisp programs can have procedures invoked when an abbrev is
triggered.        Use    the   commands   define-hooked-global-abbrev   and
define-hooked-local-abbrev to  do  this.    These  behave  exactly  as  the
unhooked  versions  do except that they also associate a named command with
the  abbrev.    When  the  abbrev  triggers,  rather  than  replacing   the
abbreviation  with  the expansion phrase the hook procedure is invoked. The
character that trigged the abbrev will not have been inserted, but will  be
inserted  immediatly after the hook procedure returns [unless the procedure
returns 0].  The abbreviation will be the word immediatly to  the  left  of
dot,  and  the function abbrev-expansion returns the phrase that the abbrev
would have expanded to.
</FoO ThE bAr/>
dbadd info "emacs:the screen" <<"</FoO ThE bAr/>"
Node: The Screen			Up: Basics, Next: Input Conventions

Emacs divides a screen into several areas called windows, at the bottom  of
the screen there is a one line area that is used for messages and questions
from Emacs.  Most people will only be using one window, at least until they
become  more familiar with Emacs.  A window is displayed as a set of lines,
at the bottom of each window is its mode line (For more information on mode
lines see section , page 21).  The lines above the  mode  line  contain  an
image of the text you are editing in the region around dot (or point).  Dot
is  the reference around which editing takes place.  Dot is a pointer which
points at a position between two characters.  On  the  screen,  the  cursor
will  be  positioned  on  the  character that immediatly follows dot.  When
characters are inserted, they  are  inserted  at  the  position  where  dot
points;  commands  exist that delete characters both to the left and to the
right of dot.  The text on the screen always reflects  they  way  that  the
text looks now.  
</FoO ThE bAr/>
dbadd info "emacs:paragraphs" <<"</FoO ThE bAr/>"
Node: paragraphs			Up: Packages, Previous: newcompile, Next: pascal

</FoO ThE bAr/>
dbadd info "emacs:next-error" <<"</FoO ThE bAr/>"
Node: next-error			Up: Commands, Previous: newline-and-indent, Next: next-line

Take  the next error message (as returned from the ^X^E (compile) command),
do a visit (^X^V) on the file in which the error occurred and  set  dot  to
the  line on which the error occurred.  The error message will be displayed
at the top of the window associated with the Error log buffer.
</FoO ThE bAr/>
dbadd info "emacs:line moves" <<"</FoO ThE bAr/>"
File: emacs     Node: line moves     Up: Moving around

* menu:
* beginning-of-line::			(^A)
* end-of-line::				(^E)
* goto-line::
* next-line::				(^N)
* previous-line::			(^P)
</FoO ThE bAr/>
dbadd info "emacs:compile-it" <<"</FoO ThE bAr/>"
Node: compile-it			Up: Commands, Previous: command-prefix, Next: concat

Make is a standard Unix program which takes a description of how to compile
a set of programs and compiles them.  The output of make (and the compilers
it calls) is placed in a buffer which is displayed in a  window.    If  any
errors  were  encountered,  Emacs  makes  a note of them for later use with
^X^N.  Presumably, a data base has been set up for  make  that  causes  the
files  which  have been edited to be compiled.  ^X^E then updates the files
that have been changed and make  does  the  necessary  recompilations,  and
Emacs notes any errors and lets you peruse them with ^X^N.

If  ^X^E is given a non-zero argument, then rather than just executing make
Emacs will prompt for a Unix command line to be executed.  Modified buffers
will still be written out, and the output will still go to  the  Error  log
buffer  and be parsed as error messages for use with ^X^N.  One of the most
useful applications of this feature involves the grep program.  "^U^X^Egrep
-n MyProc *.cESC" will scan through all C  source  files  looking  for  the
string "MyProc" (which could be the name of a procedure).  You can then use
^X^N  to  step  through  all  places  in all the files where the string was
found.  Note: The version of grep in my bin  directory,  /usr/jag/bin/grep,
must  be  used:  it  prints  line numbers in a format that is understood by
Emacs.  (ie.  "FileName, line LineNumber)
</FoO ThE bAr/>
dbadd info "emacs:inserting" <<"</FoO ThE bAr/>"
File: emacs     Node: Inserting     Up: Commands

Normally, to insert text into a buffer you just type them in.  When you hit
the 'a' key, an 'a' will be inserted.  That is because all of the simple
keys are bound to "self-insert".  The other commands in the following list
perform more complicated forms of insertion.

* menu:
* insert-character::
* insert-file::				(^X-^I)
* insert-filter::
* insert-string::
* mail-insert::
* self-insert::				(^I,  ..,, .../, :..~)
* yank-buffer::				(ESC-^Y)
* yank-from-killbuffer::		(^Y)
</FoO ThE bAr/>
dbadd info "emacs:mscompil" <<"</FoO ThE bAr/>"
Node: mscompil		Up: Top		Next: lisp


Mscompil is a library that makes MAINSAIL program development much
less painful:  You compile the MAINSAIL file in the current buffer
by saying C-X C-E (the file is first saved if necessary.)
If there were errors in compilation, mscompil shows you a two-window
display, with the first error-message in the bottom window, and the 
corresponding sourcefile location on top.  After you fix the error,
say C-X C-N to see the next error.  When you've fixed all the errors, 
you can recompile.  NB:  mscompil currently  does NOT work on
VANILLA mainsail.  (It uses TESTBED mainsail by default.)

* menu:
* Usage::		How to invoke mscompil
* Variables::		How to control where and how your file is compiled.
* Caveats::		How not to get screwed
</FoO ThE bAr/>
dbadd info "emacs:deleting" <<"</FoO ThE bAr/>"
File: emacs     Node: Deleting     Up: Commands

* menu:
* delete-buffer::
* delete-next-character::		(^D)
* delete-next-word::			(ESC-d)
* delete-other-windows::		(^X-1)
* delete-previous-character::		(^H, ^?)
* delete-previous-word::		(ESC-h)
* delete-region-to-buffer::		(ESC-^W)
* delete-to-killbuffer::		(^W)
* delete-white-space::			(ESC-k)
* delete-window::			(^X-d)
* rmail-delete-message::
* rmail-undelete-message::
</FoO ThE bAr/>
dbadd info "emacs:commands" <<"</FoO ThE bAr/>"
File: emacs     Node: Commands     Up: Top

Here are the commands available in Emacs, grouped by function.

* menu:

* Windows::		how to manipulate them
* Buffers::		how to manipulate them
* Deleting::		deletion of characters, words, lines and regions
* Inserting::		how to get text into a buffer
* Moving around::	how to move from place to place within a buffer
* Marks::		how to mark positions in buffers
* The Killbuffer::	moving and deleteing regions of text
* Subprocesses::	manipulating processes under Emacs
* MLisp statements::	simple control flow commands
* Dealing with files::	reading and writing them to and from buffers
* Abbrevs::		abbreviations for keywords
* Mode Lines::		dealing with those funny lines at the bottoms
			of windows
</FoO ThE bAr/>
dbadd info "info:help-adv" <<"</FoO ThE bAr/>"
File: info	Node: help-adv	Next: Help-Q	Previous: Help-M

Some advanced INFO commands

  The course is almost over, so please stick with it to the end.

  If you have been moving around to different nodes and wish to
retrace your steps, the "L" command ("L" for "Last") will do that, one
node at a time.  If you have been following directions, an "L" command
now will get you back to Help-M.  Another L command would undo the U
and get you back to FOO-Node.  Another L would undo the M and get you
back to Help-M.

>> Try typing three L's, pausing in between to see what each L does.
Then follow directions again and you will end up back here.

  Note the difference between L and P:  L moves to where YOU last
were, whereas P always moves to the node which the Header says
is the "Previous" node (from this node, to Help-M).

  The "D" command gets you instantly to the Directory node.
This node, which is the first one you saw when you entered INFO,
has a menu which leads (directly, or indirectly through other menus),
to all the nodes that exist.

>> Try doing a "D", then do an L to return here (yes, DO return).

  Sometimes, in INFO documentation, you will see a footnote-pointer.
Footnote pointers look like this: *Note ftnt: Help-Ft.  That is a
real, live footnote pointer which is named "Ftnt" and points at the
node named "Help-Ft".

  If you wish to look at a footnote, you must use the "F" command.
The "F" must be followed by the footnote name (in this case, "Ftnt").
You can use Rubout and ^L to edit the footnote name, and if you change
your mind about looking at any footnote you can use a lot of Rubouts
to cancel the command.

>> Type "F", followed by "Ftnt", and a CR.

>> Now type "N" to see the last node of the course.
</FoO ThE bAr/>
dbadd info "emacs:isearch" <<"</FoO ThE bAr/>"
File: emacs, Node: isearch, Next: tags, Up: top, Previous: fundamental

(To invoke:  M-X load incr-search)

Like other editors, EMACS has commands for searching for an occurrence
of a string.  The search command is unusual in that it is "incremental";
it begins to search before you have finished typing the search string.
As you type in the search string, EMACS shows you where it would be
found.  When you have typed enough characters to identify the place you
want, you can stop.

        C-S         Search forward.
        C-R         Search backward.

The command to search is C-S (incremental-search).  C-S reads in
characters and positions the cursor at the first occurrence of the
characters that you have typed.  If you type C-S and then F, the cursor
moves right after the first "F".  Type an "O", and see the cursor move
to after the first "FO".  After another "O", the cursor is after the
first "FOO" after the place where you started the search.  At the same
time, the "FOO" has echoed at the bottom of the screen.

If you type a mistaken character, you can rub it out.  After the FOO,
typing a rubout makes the "O" disappear from the bottom of the screen,
leaving only "FO".  The cursor moves back to the "FO".  Rubbing out the
"O" and "F" moves the cursor back to where you started the search.

When you are satisfied with the place you have reached, you can type an
Altmode, which stops searching, leaving the cursor where the search
brought it.  Also, any command not specially meaningful in searches
stops the searching and is then executed.  Thus, typing C-A would exit
the search and then move to the beginning of the line.  Altmode is
necessary only if the next command you want to type is a printing
character, Rubout, Altmode or another search command, since those are
the characters that would not exit the search.

Sometimes you search for "FOO" and find it, but not the one you expected
to find.  There was a second FOO that you forgot about, before the one
you were looking for.  Then type another C-S and the cursor will find
the next FOO.  This can be done any number of times.  If you overshoot,
you can rub out the C-S's.  You can also repeat the search after exiting
it, if the first thing you type after entering another search (when the
argument is still empty) is a C-S.

If your string is not found at all, the echo area says "Failing
I-Search".  The cursor is after the place where EMACS found as much of
your string as it could.  Thus, if you search for FOOT, and there is no
FOOT, you might see the cursor after the FOO in FOOL.  At this point
there are several things you can do.  If your string was mistyped, you
can rub some of it out and correct it.  If you like the place you have
found, you can type Altmode or some other EMACS command to "accept what
the search offered".  Or you can type C-G, which throws away the
characters that could not be found (the "T" in "FOOT"), leaving those
that were found (the "FOO" in "FOOT").  A second C-G at that point
undoes the search entirely.

The C-G "quit" command does special things during searches; just what,
depends on the status of the search.  If the search has found what you
specified and is waiting for input, C-G cancels the entire search.  The
cursor moves back to where you started the search.  If C-G is typed
while the search is actually searching for something or updating the
display, or after search failed to find some of your input (having
searched all the way to the end of the file), then only the characters
which have not been found are discarded.  Having discarded them, the
search is now successful and waiting for more input, so a second C-G
will cancel the entire search.  Make sure you wait for the first C-G to
ding the bell before typing the second one; if typed too soon, the
second C-G may be confused with the first and effectively lost.

You can also type C-R at any time to start searching backwards.  If a
search fails because the place you started was too late in the file, you
should do this.  Repeated C-R's keep looking for more occurrences
backwards.  A C-S starts going forwards again.  C-R's can be rubbed out
just like anything else.  If you know that you want to search backwards,
you can use C-R instead of C-S to start the search, because C-R is also
a command (reverse-incremental-search) to search backward.
</FoO ThE bAr/>
dbadd info "emacs:buffers" <<"</FoO ThE bAr/>"
File: emacs     Node: Buffers     Up: Commands

A Buffer is the basic object which Emacs deals with.  It is simply a piece
of text, often representing the contents of a file.  The following commands
are used to manipulate buffers.  Other commands to manipulate characters
within buffers may be found by moving "up" from this node.

* menu:
* append-region-to-buffer::
* buffer-size::
* compile-buffer-to-db::
* copy-region-to-buffer::
* current-buffer-name::
* define-buffer-macro::
* delete-buffer::
* delete-region-to-buffer::		(ESC-^W)
* delete-to-killbuffer::		(^W)
* describe-word-in-buffer::		(^X-^D)
* erase-buffer::
* execute-mlisp-buffer::
* get-tty-buffer::
* list-buffers::			(^X-^B)
* pop-to-buffer::
* prepend-region-to-buffer::
* switch-to-buffer::			(^X-b)
* temp-use-buffer::
* use-old-buffer::			(^X-^O)
* yank-buffer::				(ESC-^Y)
* yank-from-killbuffer::		(^Y)
</FoO ThE bAr/>
dbadd info "emacs:apropos" <<"</FoO ThE bAr/>"
Node: apropos				Up: Commands, Previous: append-to-file, Next: arg

Prompts  for a keyword and then prints a list of those commands whose short
description contains that keyword.    For  example,  if  you  forget  which
commands deal with windows, just type "ESC-?windowESC".
</FoO ThE bAr/>
dbadd info "dir:utilities" <<"</FoO ThE bAr/>"
File: dir     Node: Utilities     Up: Top

	This node needs a volunteer to finish writing it!
</FoO ThE bAr/>
dbadd info "emacs:substr" <<"</FoO ThE bAr/>"
Node: substr				Up: Commands, Previous: string-to-process, Next: switch-to-buffer

(substr str pos n) returns the substring of string str starting at position
pos  (numbering  from 1) and running for n characters.  If pos is less than
0, then length of the string is added to  it;  the  same  is  done  for  n.
(substr "kzin" 2 2) = "zi"; (substr "blotto.c" -2 2) = ".c".
</FoO ThE bAr/>
dbadd info "emacs:c-mode" <<"</FoO ThE bAr/>"
Node: c-mode				Up: Packages, Previous: buff, Next: dired

begin-C-comment (ESC-`)  Initiates  the  typing in of a comment.  Moves the
                cursor over to the comment column, inserts "/* " and  turns
                on  autofill.    If ESC-` is typed in the first column, the
                the comment begins there, otherwise it  begins  where  ever
                comment-column says it should.

end-C-comment   (ESC-') Closes off the current comment.

indent-C-procedure
                (ESC-j)  Takes  the  current function (the one in which dot
                is) and fixes up its indentation by running it through  the
                "indent" program.

</FoO ThE bAr/>
dbadd info "info:expert" <<"</FoO ThE bAr/>"
File: info	Node: expert		Up: Top

Some Advanced INFO Commands ("@", "g" and "ESC-^E").

If you would like to descend through several levels of menu all at once,
you can type "@", then supply a sequence of menu items separated by
spaces (each can be abbreviated as for the "M" command.)  The effect
is the same as typing each item preceded by an "M" and followed by a
carriage return.

If you know a node's name, you can go there by typing
"G", the name, and a CR.  Thus, "GTop<CR>" would go to the node
called Top in this file (its directory node).  "GExpert<CR>"
would come back.

Unlike M, G does not allow the use of abbreviations.

To go to a node in another file, you can include the filename in the
node name by putting it at the front, in parentheses.  Thus,
"G(DIR)Top<CR>" would go to the INFO Directory node, which is node Top
in the file DIR (which is short for [INFO]DIR.).

The "x" command is the same as the EMACS command Meta-X.  It lets you
type in the name of an EMACS MM command and its arguments, and
executes them.  Command name completion is provided.

The INFO command "ESC-^E" enters a recursive editing level for you to edit the
text of the current node.  To get back to INFO, you must give a command to
exit.  This command is "^C" If you have changed the text of the node, then
when you visit a node in a different file INFO will offer to save this
file.
</FoO ThE bAr/>
dbadd info "getting out" <<"</FoO ThE bAr/>"
Node: Getting Out			Next: Screen And Screen Operations

* write-current-file::       ^X-^S Save the file being worked on
* write-named-file::         ^X-^W Write the current  buffer  into  a  file
                                   with a different name
* write-modified-files::     ^X-^M Write out all modified files
* write-file-exit::          ^X-^F Write out all modified files and exit
* exit-emacs::   ^C or ESC-^C or ^X-^C Finish by exiting to the shell
* return-to-monitor::           ^_ Recursively push (escape) to a new shell
</FoO ThE bAr/>
dbadd info "emacs:rmail" <<"</FoO ThE bAr/>"
Node: rmail				Up: Packages, Previous: pwd, Next: scribe

Emacs may be used to send and receive electronic mail.  The  rmail  command
(Usually  invoked  as "ESC-Xrmail") is used for reading mail, smail is used
for sending mail.  

    Sending Mail

When sending mail, either by using the smail command or from within  rmail,
Emacs  constructs  a  buffer  that contains an outline of the message to be
sent and allows you to edit it. All that you have to  do  is  fill  in  the
blanks.    When  you  exit  from smail (by typing ^C usually -- when you're
editing the message body you will be in a recursive-edit) the message  will
be  sent  to the destinations and blindcopied to you.  Several commands are
available to help you in composing the message:

justify-paragraph
                (ESC-j) Fixes up the line breaks in the  current  paragraph
                according to the current left and right margins.

exit-emacs      (^C)  Exits mail composition and attempts to send the mail.
                If all goes well the mail composition window will disappear
                and a confirmation message will appear at the bottom of the
                screen.  If there is some sort of delivery error  you  will
                be  placed  back  into the composition window and a message
                will appear.  Bug: when delivery is attempted and there are
                errors  in  the  delivery,  the  message  will  have   been
                delivered  to  the  acceptable  addresses  and  not  to the
                others.  This makes retrying the  message  difficult  since
                you  have  to manually eliminate the addresses to which the
                message has already been sent.

mail-abort-send (^X^A) Aborts the message.    If  you're  part-way  through
                composing  a message and decide that you don't want to send
                it, ^X^A will throw it away, after asking for confirmation.

mail-noblind-exit
                (^X^C) Exits smail and send the message, just as  ^C  will,
                except that a blind copy of the message will not be kept.

exit-emacs      (^X^F) Same as ^C.

exit-emacs      (^X^S) Same as ^C.

mail-append     (^Xa) Positions dot at the end of the body and sets margins
                and abbrev tables appropriatly.

mail-cc         (^Xc)  Positions  dot  to  the  "cc:" field, creating it if
                necessary.

mail-insert     (^Xi) Inserts  the  body  of  the  message  that  was  most
                recently  looked at with rmail into the body of the message
                being composed.  If, for instance, what you want to  do  is
                forward  a  message  to someone, just read the message with
                rmail, then compose a message to the  person  you  want  to
                forward to, and type ^Xi.

mail-subject    (^Xs) Positions dot to the "subject:" field of the message.

mail-to         (^Xt) Positions dot to the "to:" field of the message.

    Reading Mail

The  rmail  command provides a facility for reading mail from within Emacs.
When it is running there are usually two windows on the screen: one shows a
summary of all the messages in your mailbox  and  the  other  displays  the
``current'' message.  The summary window may contain something like this:
    02621525335022 29 Oct 1981  research!dmr    [empty]
  B 02621525335030 29 Oct 1981  =>Unix-Wizards  A plea for understanding
    02621525335040 31 Oct 1981  CSVAX.dmr       rc etymology
    02621525335072 3 Nov 1981   EHF             fyi
 A  02621352421000 3 Nov 1981   JIM             copyrights
  B 02621353040000 3 Nov 1981   =>JIM           Re: copyrights
    02621646433000 [empty]      [empty]         [empty]
  B 02621647417000 4 Nov 1981   =>research!ikey Emacs
>N  02622024522003 5 November   flaco           cooking class
This is broken into five columns, as indicated by the underlining.

   - The  first  column contains some flags: '>' indicates the current
     message, 'B' indicates that the message is  a  blindcopy  (ie.  A
     copy  of  a message that you sent to someone else), 'A' indicates
     that you've answered the message,  and  'N'  indicates  that  the
     message is new.

   - The  second  column  contains  a  long  string  of digits that is
     internal information for the mail system.

   - The third contains the date on which the mail was sent.

   - The  forth  contains  the  sender  of the message, unless it is a
     blindcopy, in which case it contains the  destination  (indicated
     by the "=>").

   - The fifth column contains the subject of the message.

When in the summary window Rmail responds to the following commands:

rmail-shell     (!)  Puts  you into a command shell so that you can execute
                Unix commands.  Resume mail reading by typing ^C.

execute-extended-command
                (:) An emergency trap-door for  executing  arbitrary  Emacs
                commands.  You should never need this.

rmail-first-message
                (<) Look at the first message in the message file.

rmail-last-message
                (>) Look at the last message in the message file.

rmail-help      (?) Print a very brief help message

exit-emacs      (^C)  Leave  rmail.    Changes  marked  in the message file
                directory (eg. deletions) will be made.

rmail-search-reverse
                (^R) Prompts for a search string and positions at the first
                message,  scanning  in  reverse,  whose   directory   entry
                contains the string.

rmail-search-forward
                (^S) Prompts for a search string and positions at the first
                message,  scanning  forward, whose directory entry contains
                the string.

rmail-append    (a) Append the current message to a file.

rmail-previous-page
                (b) Moves backward in the window that contains the  current
                message.

rmail-delete-message
                (d)  Flag  the  current  message  for  deletion.   It won't
                actually be deleted until you leave rmail.

rmail-next-page (f) Moves forward in the window that contains  the  current
                message.   To read a message that is longer than the window
                that contains it, just keep typing f and  rmail  will  show
                you successive pages of it.

rmail-goto-message
                (g) Moves to the nth message.

smail           (m) Lets you send some mail.

rmail-next-message
                (n) Moves to the next message.

rmail-previous-message
                (p) Moves to the previous message.

exit-emacs      (q) the same as ^C

rmail-reply     (r) Constructs a reply to the current message.

rmail-skip      (s) Moves to the nth message relative to this one.

rmail-undelete-message
                (u)  If  the  current  message  was  marked for deletion, u
                removes that mark.

</FoO ThE bAr/>
dbadd info "emacs:quick" <<"</FoO ThE bAr/>"
Node: quick		Up: (dir)top		Next: Some Necessary Notation

This is a quick reference to the Emacs commands that most people are likely
to use.  Either look at the section that interests you or read through it
all sequentially using the info 'n' command.

* Menu:
* Some Necessary Notation::
* Character Operations::
* Word Operations::
* Line Operations::
* Paragraph Operations::
* Getting Out::
* Screen And Screen Operations::
* Buffer And File Operations::
* Help And Helper Functions::
* Search::
* Replace::
* Region Operations::
* Macro Operations::
* Compiling (Make) Operations.::
* Mail::
* Mice::		how to use mice and tablets with Emacs
</FoO ThE bAr/>
dbadd info "emacs:ltags" <<"</FoO ThE bAr/>"
Node: ltags		Up: tags		Next: ctags

First, you have to make a tags file skeleton.  Using emacs,
Create a file of the following form:

^_filespec
^_filespec
   .
   .

(where ^_ is control underscore)  naming each file you want to access from
ltags. Save the file, and say M-X make-tag-table.  You will be prompted for
the file name.  Ltags recognizes as a tag any line beginning with "(def".

To update the tag table after adding functions, just say M-X make-tag-table
again.

To use tags,  say M-X goto-tag (or bind goto-tag to a key).  You
will be prompted for a function name.  You may supply a LEADING substring
of the name, and you will get the first tag that matches.  If this isnt
what you wanted, you may say M-X next-tag (or bind it someplace) to find
the next matching tag.

When no tag table is loaded, goto-tag will prompt for a tags file.  If
you want to change tag tables, say M-X visit-tag-table, and supply a filespec.

</FoO ThE bAr/>
dbadd info "emacs:digit" <<"</FoO ThE bAr/>"
Node: digit				Up: Commands, Previous: describe-word-in-buffer, Next: dot

Heavy wizardry:  you  don't  want  to  know.    "digit"  should  eventually
disappear.
</FoO ThE bAr/>
dbadd info "info:menus" <<"</FoO ThE bAr/>"
File: info, Node: menus, Previous: Add, Up: Top, Next: Footnotes

How to Create Menus:

  Any node in the INFO hierarchy may have a MENU - a list of subnodes. 
The M command searches the current node's menu for the topic which it
reads from the TTY. 

  A menu begins with a line starting with "* Menu:".  The rest of the
line is a comment.  After the starting line, every line that begins
with a "* " lists a single topic.  The name of the topic - the arg
that the user must give to the M command to select this topic -
comes right after the star and space, and is followed by 
a colon, spaces and tabs, and the name of the node which discusses
that topic.  The node name, like node names following Next,
Previous and Up, must be terminated with a tab, comma, or CRLF.
If the node name and topic name are the same, than rather than
giving the name twice, the abbreviation "* <name>::" may be used
(and should be used, whenever possible, as it reduces the visual
clutter in the menu).

  It is considerate to choose the topic names so that
they differ from each other very near the beginning - this allows
the user to type short abbreviations.  In a long menu, it is a good
idea to capitalize the beginning of each item name which is the
minimum acceptable abbreviation for it (a long menu is more than 5 or
so entries).

  The node's listed in a node's menu are called its "subnodes", and
it is their "father".  They should each have an "Up:" pointing at
the father.  It is often useful to arrange all or most of the
subnodes in a sequence of Next's/Previous's so that someone who
wants to see them all need not keep revisiting the Menu.

  The INFO Directory is simply the menu of the node "(DIR)TOP" - that
is, node Top in file <INFO>DIR.INFO.  You can put new entries in that
menu just like any other menu.  The INFO Directory is NOT the same as
the file directory called INFO.  It happens that many of INFO's files
live on that file directory, but they don't have to; and files on that
directory are not automatically listed in the INFO Directory node.

  Also, although the INFO node graph is claimed to be a "Hierarchy",
in fact it can be ANY directed graph.  Shared structures and
pointer cycles are perfectly possible, and can be used if they are
appropriate to the meaning to be expressed.  There is no need
for all the nodes in a file to form a connected structure.  In fact,
this file has two connected components.  You are in one of them,
which is under the node Top;  the other contains the node Help which
the "H" command goes to.  In fact, since there is no
garbage collector, nothing terrible happens if a substructure
is not pointed to, but such a substructure will be rather useless
since nobody will ever find out that it exists.  
</FoO ThE bAr/>
dbadd info "emacs:undo" <<"</FoO ThE bAr/>"
Node: undo				Up: Packages, Previous: time, Next: writeregion

The  new-undo  command,  which  is usually bound to ^X^U allows the user to
interactively undo the effects of previous commands.   Typing  ^X^U  undoes
the  effects  of the last command typed.  It will then ask ``Hit <space> to
undo more'', each <space> that you then hit will  undo  one  more  command.
Typing anything but space will terminate undoing.  If it is terminated with
anything  other  than  <return>  the termination character will be executed
just as though it were a normal command.  new-undo is an undoable  command,
just  like the others, so if you find that you've undone too much just type
^X^U again to undo the undo's.  
</FoO ThE bAr/>
dbadd info "emacs:tags" <<"</FoO ThE bAr/>"
Node: tags				Up: Packages, Previous: spell, Next: text-mode

The tags package closely resembles the tags package found in Twenex  Emacs.
The database used by the tag package (called a tagfile) correlates function
definitions  to  the  file  in  which  the definitions appear.  The primary
function of the tag package is to allow the user to specify the name  of  a
function,  and then have Emacs locate the definition of that function.  The
commands implemented are:

add-tag         Adds the current line (it should be the definition line for
                some function) to the current tagfile.

goto-tag         goto-tag takes a single string argument which  is  usually
                the  name of a function and visits the file containing that
                function with the first line of the function at the top  of
                the  window.  The string may actually be a substring of the
                function name (actually, any substring of the first line of
                the function definition).  If goto-tag is given  a  numeric
                argument  then  rather than asking for a new string it will
                use the old string and search for the  next  occurrence  of
                that  string  in  the  tagfile.   This is used for stepping
                through a set of tags that contain the same string.

                This is the most commonly used command in the  tag  package
                so  it  is  often  bound to a key: Twenex Emacs binds it to
                ESC-.,  but  the  Unix  tag  package  doesn't  bind  it  to
                anything,  it  presumes  that  the user will bind it (I use
                ^X^G).

make-tag-table  Takes a list of file names  (with  wildcards  allowed)  and
                builds a tagfile for all the functions in all of the files.
                It determines the language of the contents of the file from
                the  extension.    This  command  may take a while on large
                directories, be prepared to wait.  A common use is to  type
                "make-tag-table *.c".

recompute-all-tags
                Goes  through  your  current  tag  file  and  for each file
                mentioned refinds all of the tags.  This is used to rebuild
                an entire tag file if you've made very extensive changes to
                the files mentioned and the tag package is no  longer  able
                to  find functions.  The tagfile contains hints to help the
                system locate the tagged function, as you make  changes  to
                the   various   files   the   hints  become  out  of  date.
                Periodically (no  too  often!)  you  should  recompute  the
                tagfile.

visit-function  Takes  the  function name at or before dot, does a goto-tag
                on that name, then puts you into a recursive-edit  to  look
                at the function definition.  To get back to where you were,
                just  type ^C.  This is used when you're editing something,
                have dot positioned at some function invocation, then  want
                to look at the function.

visit-tag-table Normally  the name of the tagfile is ".tags" in the current
                directory.    If  you  want  to  use  some  other  tagfile,
                visit-tag-table lets you do that.

</FoO ThE bAr/>
dbadd info "emacs:setq" <<"</FoO ThE bAr/>"
Node: setq				Up: Commands, Previous: set-mark, Next: setq-default

Assigns a new value to a variable.  Variables may  have  either  string  or
integer  values.   (setq i 5) sets i to 5; (setq s (concat "a" "b")) sets s
to "ab".
</FoO ThE bAr/>
dbadd info "emacs:load" <<"</FoO ThE bAr/>"
Node: load				Up: Commands, Previous: list-processes, Next: local-bind-to-key

Read the named file as a series of  MLisp  expressions  and  execute  them.
Typically  a  loaded file consists primarily of defun's and buffer-specific
variable assignments and key bindings.  Load is usually used to load  macro
libraries  and  is  used to load ".emacs pro" from your home directory when
Emacs starts up.

For example, loading this file:

    (setq right-margin 75)
    (defun (my-linefeed
                (end-of-line)
                (newline-and-indent)
           )
    )
    (bind-to-key "my-linefeed" 10)

sets the right-margin to 75 and defines a function called  my-linefeed  and
binds it to the linefeed key (which is the ascii character 10 (decimal))

The  file  name  given  to  load  is  interpreted  relative  to  the  EPATH
environment variable, which is  interpreted  in  the  same  manner  as  the
shell's  PATH  variable.    That  is, it provides a list of colon-separated
names that are taken to be the names of directories that are  searched  for
the  named  files.    The  default  value  of  EPATH  searches your current
directory and then a central system directory.

Temporary hack: in previous versions of Emacs loaded files were treated  as
a  sequence  of  keystrokes.    This  behaviour  has been decreed bogus and
unreasonable, hence it has been changed.  However, to avoid loud  cries  of
anguish  the  load  command  still  exhibits the old behaviour if the first
character of the loaded file is an ESC.
</FoO ThE bAr/>
dbadd info "emacs:argv" <<"</FoO ThE bAr/>"
Node: argv				Up: Commands, Previous: argument-prefix, Next: auto-execute

(argv  i)  returns  the  ith  argument that was passed to Emacs when it was
invoked from the Unix Shell.  If Emacs were invoked as "emacs blatto"  then
(argv  1)  would  return  the  string "blatto".  If either argc or argv are
called early enough then Emacs's startup action of visiting the files named
on the command line is suppressed.
</FoO ThE bAr/>
dbadd info "emacs:dot" <<"</FoO ThE bAr/>"
Node: dot				Up: Commands, Previous: digit, Next: dump-syntax-table

(dot)  is  an  MLisp  function that returns the number of characters to the
left of dot plus 1 (ie. if dot is at the beginning  of  the  buffer,  (dot)
returns  1).  The value of the function is an object of type "marker" -- if
it is assigned to a variable then as changes are made  to  the  buffer  the
variable's value continues to indicate the same position in the buffer.
</FoO ThE bAr/>
dbadd info "emacs:if" <<"</FoO ThE bAr/>"
Node: if				Up: Commands, Previous: goto-character, Next: illegal-operation

(if  test  thenclause  elseclause)  is  an MLisp function that executes and
returns the value of thenclause iff test is  true;  otherwise  it  executes
elseclause if it is present.  For example:

    (if (eolp)
        (to-col 33)
    )

will tab over to column 33 if dot is currently at the end of a line.
</FoO ThE bAr/>
dbadd info "emacs:c=" <<"</FoO ThE bAr/>"
Node: c=				Up: Commands, Previous: c-mode, Next: case-region-capitalize

(c=  e   e )  MLisp function that returns true iff e  is equal to e  taking
      1   2                                         1              2
into account the character translations indicated by case-fold-search.   If
word-mode-search  is  in  effect, then upper case letters are "c=" to their
lower case equivalents.
</FoO ThE bAr/>
dbadd info "emacs:>>" <<"</FoO ThE bAr/>"
Node: >>				Up: Commands, Previous: >=, Next: ^

(>> e  e ) MLisp function  that  returns  e   >>  e   (the  C  shift  right
     1  2                                  1       2
operator).
</FoO ThE bAr/>
dbadd info "emacs:<=" <<"</FoO ThE bAr/>"
Node: <=				Up: Commands, Previous: <<, Next: =

(<= e  e ) MLisp function that returns true iff e  <= e .
     1  2                                        1     2
</FoO ThE bAr/>
dbadd info "emacs:!=" <<"</FoO ThE bAr/>"
Node: !=				Up: Commands, Previous: !, Next: %

(!= e  e ) MLisp function that returns true iff e  != e .
     1  2                                        1     2
</FoO ThE bAr/>
dbadd info "emacs:|" <<"</FoO ThE bAr/>"
Node: |					Up: Commands, Previous: yank-from-killbuffer

(| e  e ) MLisp function that returns e  | e .
    1  2                               1    2
</FoO ThE bAr/>
dbadd info "emacs:+" <<"</FoO ThE bAr/>"
Node: +					Up: Commands, Previous: *, Next: -

(+ e  e ) MLisp function that returns e  + e .
    1  2                               1    2
</FoO ThE bAr/>
