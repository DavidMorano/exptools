


     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



     NNNNAAAAMMMMEEEE
          emacs - interactive screen editor

     SSSSYYYYNNNNOOOOPPPPSSSSIIIISSSS
          emacs [-i init_file] [+line_number] [+/re/] [-xsSR] [file]

     DDDDEEEESSSSCCCCRRRRIIIIPPPPTTTTIIIIOOOONNNN
          Emacs is an interactive screen editor which can be  used  to
          construct and edit files on UNIX.  A window of text from the
          file being edited is displayed on the terminal screen, along
          with  a  status  line describing the editor version and file
          being edited.  Ordinary characters typed are inserted in the
          file, while escape sequences and control characters are used
          to invoke editing functions. Several files can be edited  at
          the  same  time in different editing buffers, and two of the
          active buffers can be displayed on the same screen.

          If given a _f_i_l_e argument, emacs  reads  the  file  into  the
          buffer "Main".  Otherwise, an empty buffer is created.  If a
          _l_i_n_e__n_u_m_b_e_r is given, emacs moves to that line number in the
          specified  file.   If  -_x  is  specified,  emacs asks for an
          encryption key and uses ccccrrrryyyypppptttt((((1111)))) to read or write any  files
          edited  in  that session. (See also the ^Xk command.)  If an
          _i_n_i_t__f_i_l_e is specified, emacs will  treat  the  contents  of
          that  file  as  emacs  commands  to  be executed on startup.
          Emacs also looks in your home directory  for  a  file  named
          ._e_m_a_c_s__i_n_i_t  and interprets commands from it before those in
          the specified _i_n_i_t__f_i_l_e are executed.  This option can  also
          be  specified  with ....iiii, in which case it suppresses the pro-
          cessing of ._e_m_a_c_s__i_n_i_t.  If an ._e_m_a_c_s__i_n_i_t does  not  exist,
          emacs looks in the emacs library directory (see below) for a
          standard ._e_m_a_c_s__i_n_i_t.

          The arguments -_s, and -_R specify restrictions  on  the  com-
          mands  that  can  be  used in the editor, and can be used to
          allow users with restricted access to a system to use a res-
          tricted version of emacs.  -_s limits you to be able to write
          only the file specified on the command  line,  and  prevents
          any  shell  escapes  other  than "ls" and "pwd".  -_S further
          limits you to only be able to read the file on  the  command
          line  and prevents all shell escapes.  -_R prevents any writ-
          ing of any files.

          Emacs can be customized by the  user  through  user  defined
          macro  commands, which can re-define the effect of the basic
          editing commands.  Emacs has a number of  built  in  editing
          modes that customize some of the commands to support editing
          of particular types of files, such as C source  programs  or
          word processing source documents.

          There are a number of self-help features in emacs to aid  in
          learning  how  to  use  the  editor.  Complete documentation



     Page 1                                           (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



          appears in:

                    An Interactive Screen Editor for Unix
          and
                    A New and Improved Macro Facility for Emacs

          Emacs supports editing on most of the commonly  used  dislay
          terminals  including  vt100,  vt52,  adm (adm3a), adm31, and
          most of the Hewlett-Packard  and  Teletype  terminals.   The
          terminal  type  can be entered when emacs is invoked, or set
          in the environment variables TERM or  TERM4EMACS.   On  some
          systems, the ttttttttyyyyppppeeee((((1111)))) command can be used to set your termi-
          nal type automatically by putting

                    TERM=`ttype`
                    export $TERM

          in your .profile.

          If TERM is a given as a full path name, it will use  a  user
          supplied   terminal   descriptor   file.   If  the  variable
          TERM4EMACS is given, emacs will use  it  instead  of  $TERM.
          This  allows  you  to use non-standard terminal descriptions
          with emacs that have been tailored to work better with emacs
          and not interfere with other screen oriented software.

     MMMMIIIISSSSCCCCEEEELLLLLLLLAAAANNNNEEEEOOOOUUUUSSSS CCCCOOOONNNNVVVVEEEENNNNTTTTIIIIOOOONNNNSSSS
          Emacs  treats  the   following   characters   specially   in
          filenames:

          $NAME           Substitute the environment variable NAME
          ~USER           Substitute the home directory of USER.
          ~EMACS          Specifies the emacs library directory. (contains
                          standard macros, etc.)
          *,?             Can be used for matching in partially specified
                          filenames.
          `COMMAND`       Substitute the output of running COMMAND.
          {,[             Used as they are with the shell.

          If you try to read a file that  does  not  exist,  and  have
          defined  either  $VPATH  or  $EDIT_PATH in your environment,
          emacs use one or both of these variables to determine a list
          of  alternate  places  to  look.   VPATH is interpreted as a
          viewpath and used the same  way  as  other  tools  that  use
          viewpaths,  such  as  build,  use  it.  EDIT_PATH provides a
          simpler mechanism and simply contains a list of  alternative
          directories  to search for the file if it cannot be found in
          the current directory.

          Emacs uses the following notation to display and input  non-
          printing characters:




     Page 2                                           (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



          ^X              Control-X, where X is any character.  These
                          characters are input by holding down the control key
                          and another key simultaneously on your terminal.
                          Emacs also provides a special mode (controlify) to
                          allow you to input control characters that your
                          terminal cannot send to your system (see the
                          discussion of modes).  Some of the control
                          characters displayed are not very intuitive:
                                  ^?      Rubout
                                  ^[      Escape
                                  ^]      Control-right-bracket
                                  ^\      Control-backslash
                                  ^_      Control-underline
                                  ^@      Null
                                  ^H      Backspace (Displays as ^H when
                                          backspace mode is off, see below).
                                  ^I      Tab (Displays as ^I when notabs mode
                                          is on.)
                                  ^J      Newline (Displays as ^J in searches)
                                  ^M      Carriage return

          M-x             Meta-x, where x is any character (including a
                          control character.  Meta characters are entered by
                          typing escape followed by another character.

          Many emacs commands take an optional numeric argument.   The
          argument  for a command precedes the command itself, and can
          be specified a number of ways.  Typing ^U specifies an argu-
          ment  of  4, or 4 times the current argument.  Typing escape
          followed by a sequence of digits with or without  a  leading
          '-' specifies a decimal value. Some examples:

          ^U^U^N          Go forward 16 lines
          M-123^N         Go forward 123 lines
          M--12^N         Go forward -12 lines (goes back 12 lines).


          Some emacs commands prompt for a string parameter, such as a
          file name.  Some of the normal emacs commands can be used to
          edit  the  parameter  while  it  is  being  entered.   These
          include:  ^F,^B,^D,^H,^A,^E,^K,^U.  In addition, typing your
          kill character (usually @) deletes  the  string,  typing  ^X
          substitutes  the contents of the current line in the buffer,
          and ^Y substitutes the current file name.  (The latter is  a
          very  convenient  way  of finding files with similar names.)
          Typing ^V while typing a string will cause emacs  to  expand
          any  shell  meta  characters  ($,*,?,etc.) in the string and
          show the first candidate in the result.  If  there  is  more
          than one expansion (e.g. foo.c and bar.c for *.c), ^N and ^P
          will allow you to move backwards or forwards in them.

     RRRREEEEGGGGUUUULLLLAAAARRRR EEEEXXXXPPPPRRRREEEESSSSSSSSIIIIOOOONNNNSSSS



     Page 3                                           (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



          Emacs uses an extension of  the  regular  expression  syntax
          used  by  eeeedddd(1)  and ggggrrrreeeepppp(1) for regular expression searches
          and query replace.  The following character  sequences  have
          special meaning:

          [xyz]           Matches one character among the set enclosed
                          in brackets. (If the first character is ^, it
                          matches all but the specified characters.)
                          If a '-' appears in the brackets, it designates
                          a range of character values (i.e. [a-ez] is
                          equivalent to [abcdez]).  The sequence \n can
                          be used to specify a newline as one of the
                          alternatives.
          *               Matches 0 or more of the preceding expression
                          (a single character, specified as such or * or
                          [])
          +               Matches 1 or more of the preceding expression
          \{x,y\}         Matches x through y occurrences of the
                          preceding expression. If y is omitted, it
                          defaults to 255. If x is omitted it defaults
                          to 0.
          \(expr\)        Matches expr, and saves the text so matches
                          for later reference.
          \(ex1\|ex2\)    Matches expression ex1 or ex2 and saves the text
                          matched for later reference.  Note that any number
                          of alternative expressions can be separated by \|.
                          This expression cannot be followed by '*', '+', or a
                          range to specify multiple matches.
          \<              Matches 0 characters at the beginning of a word.
          \>              Matches 0 characters at the end of a word.
          ^               Matches 0 characters at the beginning of a line
          $               Matches 0 characters at the end of a line.
          \n              Matches on newline at end of a line.


          The following special sequences apply in the strings to
          replace with in query replace.

          &               Specifies the entire string matched by the
                          from string.
          %               Specifies the previous To string.
          \_n              Specifies the string matched by the _nth
                          occurrence of \(expr\) (Regular expression
                          replace only).
          ^J  or  \n      Specifies a newline is to be inserted at
                          this point.


     CCCCOOOOMMMMMMMMAAAANNNNDDDD SSSSUUUUMMMMMMMMAAAARRRRYYYY
          The following chart summarizes  the  available  commands  by
          category.  Some  commands  appear in more than one category.
          Commands that are marked with '*' take  a  numeric  argument



     Page 4                                           (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



          that  indicates  how many times to do the command.  Commands
          that are marked  with  '+'  take  a  numeric  argument  that
          changes the behavior of the command in some other way.

                  GGGGeeeennnneeeerrrraaaallll CCCCoooommmmmmmmaaaannnnddddssss

           ^G     Quit (Stops commands that prompt for things)
           ^Z     Exit one level (Usually exits emacs)
           ^X^C   Exit emacs
           M-u    Undo.  Undoes the result of the last modification
           M-^Z     Suspend emacs, (Requires a second ^Z on System 5 Unix)
           M-?    Help - Prompts for a command and displays its function.
           M-w    Put a wall chart of command explanations in the current buffer
          +^L     Refresh the screen. (Argument indicates where to put the
                  current line)

                  CCCChhhhaaaarrrraaaacccctttteeeerrrr oooorrrriiiieeeennnntttteeeedddd ccccoooommmmmmmmaaaannnnddddssss

          *^F     Move forward one character
          *^B     Move backward one character
          *^D     Delete the character under the cursor
          *^H,^?  Delete the previous character
          *^T     transpose the current and next character, move forward.
          *^C     Capitalize the current character
           M-i    Insert mode (macro, usually loaded from ~EMACS/.emacs_init)
           M-o    Overwrite mode (macro, usually loaded from ~EMACS/.emacs_init)

                  WWWWoooorrrrdddd oooorrrriiiieeeennnntttteeeedddd ccccoooommmmmmmmaaaannnnddddssss

          *M-f    move forward one word
          *M-b    move backward one word
          *M-d    delete forward one word
          *M-^?,M-^h delete backwards one word
          *M-c    Capitalize the next word
          *M-_    Underline the next word
           M-a    Move to the beginning of the sentence
           M-e    Move to the end of the sentence

                  LLLLiiiinnnneeee oooorrrriiiieeeennnntttteeeedddd ccccoooommmmmmmmaaaannnnddddssss

           ^A     move to beginning of line
           ^E     move to end of line
          ^M-<    Move to beginning of file
          ^M->    Move to end of file
          *^P     move back one line
          *^N     move forward one line
          +M-g    Go to the line specified by the argument
          *^O     Create a blank line in front of the cursor
          *^J,^M  Make a new line (Just moves through empty lines).
          *^K     Kill (delete) to the end of line (with argument, kills whole lines)

                  DDDDeeeelllleeeetttteeee ccccoooommmmmmmmaaaannnnddddssss



     Page 5                                           (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



          *^D     Delete the character under the cursor
          *^H,^?  Delete the previous character
          *M-d    delete forward one word
          *M-^?,M-^h delete backwards one word
          *^K     Kill (delete) to the end of line (with argument, kills whole lines)
          +^W     Delete the marked region (argument specifies a mark number)
          *^Y     Restore the last deletion (sets mark in front of it).
          *M-Y    Replace the marked region with the previous deletion
                          (Use only immediately ofter ^Y)

                  DDDDiiiissssppppllllaaaayyyy ccccoooommmmmmmmaaaannnnddddssss

           ^L     Redraw the screen
          *^V     Display the next page
          *M-v    Display the previous page
           M-<    Move to beginning of file
           M->    Move to end of file
           M-^L   redraw with the current line at the top of the screen

                  BBBBuuuuffffffffeeeerrrr ccccoooommmmmmmmaaaannnnddddssss

          (Most prompt for a buffer name, entering return gets a list of active
                  buffers).

           ^X^B   change working buffer
          +^X^F   Find file (does change buffer if file is in one, creates a new
                          buffer and reads the file if not).
           ^X^K   Kill buffer
          +^X^N   Change buffer name (with argument, changes file name)
           ^X^T   Send region to buffer
           ^X=    Display statistics on buffer
           ^X2    Enter two window mode (prompts for buffer name for second window)
           ^X1    Make current window the only window
           ^X^O   Switch windows.

                  FFFFiiiilllleeee ccccoooommmmmmmmaaaannnnddddssss

          +^X^R   Read file into current buffer (with an argument, inserts the
                          file at the current position)
          +^X^W   Write buffer to file (With an argument, appends to the file)
           ^X^S   Save current buffer into current file.
          +^X^F   Find file (does change buffer if file is in one, creates a new
                          buffer and reads the file if not).
          +^X^N   Change buffer name (with argument, changes file name)
          +^X^L   Load macros from file. (With an argument, undefines all
                          previously defined macros.)

                  RRRReeeeggggiiiioooonnnn ccccoooommmmmmmmaaaannnnddddssss

          +M-(space) Set mark at position (argument the mark number)
          +^X^X   Exchange mark and cursor position (argument is mark number)
          +^W     Delete the region and put it on the kill stack



     Page 6                                           (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



          +M-p    Put the marked region in the kill stack without deleting it.

                  SSSSeeeeaaaarrrrcccchhhh aaaannnndddd RRRReeeeppppllllaaaacccceeee ccccoooommmmmmmmaaaannnnddddssss
          (All prompt for search and replace strings.)

           ^S,^R  Forward and reverse incremental search.  (Both display the
                  string currently matched.  ^S moves to next occurrence, ^R
                  moves to previous occurrence.  ^H deletes last character, ^G
                  quits search, escape exits search at currently displayed
                  position.  See below on regular expression search.

           M-^S   Regular expression search.  (waits for whole expression to
                  be typed).  ^S following M-^S goes to next occurrence.

           M-r,M-^R Ordinary and regular expression query replace. (Prompts at
                  each occurrence of from string for the following:

                  y               Replace with "to" string and move on.
                  n               Do not replace this occurrence and move on.
                  r               Replace all of the rest, showing each replacement.
                  R               Replace the rest silently
                  p               Move to previous occurrence of from string.
                  .               Replace this one and stop
                  <               Go back to the last replacement and stop
                  ^G              Quit query replace
                  <escape>        Prompt for new to string, and replace this
                                  occurrence with it.

                  WWWWiiiinnnnddddoooowwww ccccoooommmmmmmmaaaannnnddddssss

           ^X2    Enter two window mode (prompts for buffer name for second window)
           ^X1    Make current window the only window
           ^X^O   Switch windows.
          *^X^^   Make current window grow by one line.

                  SSSSppppeeeecccciiiiaaaallll iiiinnnnppppuuuutttt ccccoooommmmmmmmaaaannnnddddssss

          *^Q     Takes the next input character and inserts it, even if it is
                  a control character
          *M-Q    Takes the next input character, makes it a meta character,
                  and inserts it.
          +M-\    Converts it's argument to an ascii character and inserts it.

                  IIIInnnntttteeeerrrraaaaccccttttiiiioooonnnn wwwwiiiitttthhhh UUUUnnnniiiixxxx

          +M-!    Prompt for a unix command and execute it (with an argument,
                  passes the buffer as standard input.
          +M-$    Execute unix command, put output in .exec (with an argument,
                  appends to .exec., with an argument of 0, starts a
                  sub-process).
          +^X^G   Interrupt sub-process.
           ^X^D   Change working directory



     Page 7                                           (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



           M-^M   Send the current buffer as mail.  (Lines starting To: or Cc:
                  are taken as destinations.)
           M-S    Run ssssppppeeeellllllll(1) on current buffer (macro, usually
                  loaded from ~EMACS/.emacs_init).

                  MMMMiiiisssscccceeeellllllllaaaannnneeeeoooouuuussss ccccoooommmmmmmmaaaannnnddddssss

          +^X^M   Specifies modes (See below)
           M-s    Prints emacs statistics
           M-z    File an electronic trouble report. (MAY NOT SAVE BUFFERS)
          +M-"    Re-adjusts line boundaries in the whole buffer to fill
                  lines evenly. (With an argument, it works only on the
                  current region.
           M-/    Start a C comment.


     MMMMooooddddeeeessss
          Mode parameters allow you to customize the behavior of  cer-
          tain  commands.   Some  modes  are switches, indicating only
          that something is either off or on, while others are numeric
          parameters.   Modes  can be set by the ^X^M command.  Typing
          ^X^M followed by the name of a switch mode turns it on, typ-
          ing  ^U^X^M  followed  by  the  name  turns  it off.  To set
          numeric modes, give the value you want  as  an  argument  to
          ^X^M.  (i.e. M-500^X^Msave).  Modes can be set automatically
          by putting ^X^M commands in  your  .emacs_init.   Modes  can
          also   be   attached   to  a  file  by  putting  the  string
          "EMACS_MODES: " followed by a list of mode settings  in  the
          first  10 lines of the file.  (The mode settings can be pre-
          ceded or followed by anything, to allow  you  to  make  them
          look  like a comment to other software processing the file.)
          The mode settings are separated by commas and can be of  the
          following form:

          modename:       set this switch mode
          !modename:      Turn this switch mode off
          modename=x:     Set this numeric parameter to x.

          The following indicates the modes  and  their  default  set-
          tings.  Switches  are  listed  as  either  ON  or OFF, while
          numeric parameters have specified  values.   _N_o_t_e  _t_h_a_t  _t_h_e
          _s_y_s_t_e_m  _d_e_f_a_u_l_t ._e_m_a_c_s__i_n_i_t _m_a_y _a_l_t_e_r _t_h_e_s_e _s_e_t_t_i_n_g_s _o_n _y_o_u_r
          _l_o_c_a_l _m_a_c_h_i_n_e.

          ssssaaaavvvveeee             (OFF)   Automatically saves each buffer
                                   after savetype characters of input or
                                   when you change buffers or run commands
          ssssaaaavvvveeeettttyyyyppppeeee         (256)   Number of characters between
                                   automatic saves
          mmmmaaaaiiiillllttttyyyyppppeeee         (100)   Number of characters between
                                   checks for new mail
          cccc                (OFF)   Automatically indents during



     Page 8                                           (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



                                   typing for C programs
          vvvveeeerrrrbbbboooosssseeee          (ON)    provides prompts for meta and
                                   control-x commands.
          ffffiiiillllllll             (ON)    Automatically replaces a space
                                   with a newline when you type past the
                                   end of line or past fillcol  characters.
          ffffiiiillllllllccccoooollll          (72)    column beyond which lines are wrapped.
          eeeeooooffffnnnnllll            (ON)    Causes a newline to be appended
                                   to any file that doesn't end in one.
          eeeennnndddd____nnnneeeewwwwlllliiiinnnneeee      (OFF)   Causes attempts to move beyond
                                   the end of the file to add newlines.
          kkkkeeeeeeeeppppssssccccrrrroooollllllll       (0)     Number of lines kept from previous
                                   screen during ^V and M-v
          sssslllloooowwwwssssccccrrrroooollllllll       (OFF)   Scrolls only one line when cursor
                                   goes off screen due to ^N or ^P
          ssssmmmmooooooootttthhhhssssccccrrrroooollllllll     (OFF)   Updates display via scrolling instead
                                   of jumping
          rrrreeeeaaaaddddoooonnnnllllyyyy         (OFF)   Prevents saving the current buffer
          ppppiiiiccccttttuuuurrrreeee          (OFF)   Enables 2-dimensional editing
                                   (See the manual)
          ttttaaaabbbbssssttttoooopppp          (8)     Width of a tab character
          oooovvvveeeerrrrwwwwrrrriiiitttteeee        (OFF)   Causes input to replace characters
                                   already there, rather than insert.
          nnnnooooddddeeeelllleeeetttteeee         (OFF)   Causes deletions to replace the
                                   characters with whitespace rather than
                                   deleting them.
          rrrriiiiggggiiiidddd____nnnneeeewwwwlllliiiinnnneeee    (OFF)   Causes newline to always insert
                                   a new line, even if the next line is empty.
          nnnnoooottttaaaabbbbssss           (OFF)   Causes tabs to be expanded to
                                   spaces on input, and tabs in files to
                                   display as ^I
          ccccoooommmmccccoooollll           (40)    Column where the M-/ commands
                                   starts a comment.
          bbbbaaaacccckkkkssssppppaaaacccceeee        (?)     Causes backspaces to appear as
                                   cursor motion, not  ^H.  This mode is
                                   set ON if your terminal handles underscored
                                   characters, OFF otherwise.
          nnnnoooobbbbeeeellllllll           (OFF)   Causes emacs not to ring the
                                   terminal bell on an error
          ccccaaaasssseeeelllleeeessssssss         (OFF)   Causes all searches to ignore
                                   upper/lower case distinctions
          uuuussssiiiilllleeeennnntttt          (OFF)   Causes output from unix commands
                                   run from emacs to be discarded.
          nnnnooooeeeecccchhhhoooo           (OFF)   Causes output from M-$ commands
                                   not to be echoed.
          ccccoooonnnnttttrrrroooolllliiiiffffyyyy       (OFF)   Causes a sequence of ctl_char
                                   followed by another character to translate
                                   into the second character made
                                   a control character.
          ccccttttllll____cccchhhhaaaarrrr         (30)    Prefix for controlify (This is an
                                   integer specifying  the ascii code of the
                                   character, the default is ^^.



     Page 9                                           (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



          llllnnnnuuuummmmbbbb            (ON)    Displays line numbers
          llllnnnnoooowwwwiiiidddd           (4)     Width of line numbers.
          ttttiiiimmmmeeee             (OFF)   Displays a clock
          ddddiiiissssppppllllaaaayyyy____ppppeeeerrrrcccceeeennnntttt  (OFF)   Displays current position as a
                                   percentage of the whole file.
          fffflllloooowwww____lllliiiimmmm         (0)     If non-zero, flow control will be
                                   enabled whenever flow_lim characters are
                                   sent to the terminal in a burst.
          hhhheeeeiiiigggghhhhtttt           (?)     Height of screen area for buffer
                                   display (set automatically)
          wwwwiiiiddddtttthhhh            (?)     Width of screen
          ttttssssppppeeeeeeeedddd           (?)     Describes your terminal to host speed.
          aaaauuuuttttoooollllooooaaaadddd         (ON)    Automatically loads macros when first
                                   referenced.
          VVVVPPPPAAAATTTTHHHH            (OFF)   Uses viewpathing to expand file names
          lllleeeeffffttttmmmmaaaarrrrggggiiiinnnn       (0)     In picture mode, this is the number
                                   of characters to the left of the screen.
          ddddiiiissssppppllllaaaayyyy____eeeeuuuucccc      (?)     Determines whether characters with
                                   the high order bit are considered extended
                                   ASCII or emacs meta-characters.
                                   (Set on if your terminal will display them)


     EEEENNNNVVVVIIIIRRRROOOONNNNMMMMEEEENNNNTTTT
          If either of the environment variables TERM4EMACS or TERM is
          set, it is used to determine the terminal type. The variable
          MAIL is the file name that emacs looks at for newly  arrived
          mail.   If your mail is forwarded to some other system, MAIL
          should not be exported.   The  environment  variable  MAILER
          optionally  specifies  the name of a mail command to use for
          sending mail.  The environment variable SHELL specifies  the
          shell  to use to execute shell commands.  If the environment
          variable TEMP4EMACS is set it is taken as the pathname of  a
          directory in which emacs should place it's temporary files.

     FFFFIIIILLLLEEEESSSS
          $HOME/.emacs_init
          ~EMACS/.emacs_init
          $HOME/emacs[0-11]
          ~EMACS/macros
          ~EMACS/terminals
          ~EMACS/helpfile
          ~EMACS/errfile
          The .emacs_init files, if present, contain a standard set of
          initializations  to be made when you start emacs.  The char-
          acters in the file will be interpreted as if you had entered
          them as commands from your terminal.  The most common appli-
          cation of this is to set modes different  from  the  default
          modes.

          When emacs is killed by an internal error, the kkkkiiiillllllll(1)  com-
          mand,  or  by hanging up during an editing session, it saves



     Page 10                                          (printed 2/9/96)






     EEEEMMMMAAAACCCCSSSS((((1111))))            UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV ((((eeeexxxxppppttttoooooooollllssss))))             EEEEMMMMAAAACCCCSSSS((((1111))))



          your buffers in the files emacs0-emacs11 in your home direc-
          tory.   You  will  receive  mmmmaaaaiiiillll(1)  notifying  you  of what
          buffers were saved.

          The directory ~EMACS is the emacs library, the  location  of
          which  depends on your local installation.  Pathnames start-
          ing with ~EMACS will be translated to the local path of this
          directory  by emacs (but _n_o_t by other tools).  ~EMACS/macros
          contains a number of  useful  macro  packages  that  can  be
          loaded.   ~EMACS/terminals contains terminal information for
          emacs.  The other two files contain internal data for emacs.

          On exptools machines, if $TOOLS is set,  ~EMACS  is  set  to
          $TOOLS/lib/emacs.   If  $TOOLS  is not set, ~EMACS is set to
          ~exptools/lib/emacs.

     SSSSEEEEEEEE AAAALLLLSSSSOOOO
          dired (1), ecomp (1),
          _A_n _I_n_t_e_r_a_c_t_i_v_e _S_c_r_e_e_n _E_d_i_t_o_r _f_o_r _U_N_I_X by  Warren  Montgomery
                         55235-851008-02TM
          _A _N_e_w _a_n_d  _I_m_p_r_o_v_e_d  _M_a_c_r_o  _F_a_c_i_l_i_t_y  by  Warren  Montgomery
                         55235-851014-01TM

     PPPPRRRROOOOVVVVIIIIDDDDEEEERRRR
          Warren Montgomery (ixserve!warren)






























     Page 11                                          (printed 2/9/96)



