


     VVVVSSSSHHHH((((1111))))                    UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV                    VVVVSSSSHHHH((((1111))))



     NNNNAAAAMMMMEEEE
          vsh - visual shell

     SSSSYYYYNNNNOOOOPPPPSSSSIIIISSSS
          vvvvsssshhhh [ -altv ] [ directory ]

     DDDDEEEESSSSCCCCRRRRIIIIPPPPTTTTIIIIOOOONNNN
          _V_s_h is a highly interactive, visually oriented shell which
          eases many programming activities.  Most commands involve
          only a single key press.  These commands cause directories
          to be displayed, editors to be entered, and compilers to be
          invoked.

          If no _d_i_r_e_c_t_o_r_y is given, _v_s_h displays the entries of the
          current directory on the screen; otherwise _v_s_h looks for
          _d_i_r_e_c_t_o_r_y using the CDPATH environment variable, just like
          _k_s_h(1), and displays its entries on the screen.  Directories
          are shown in brackets ([]) and executable files are marked
          by an asterisk (*).  These options change the display:

          ----aaaa   Display all entries, including those whose names begin
               with a period (.).
          ----llll   Long format display in a similar manner to _l_s(1).
          ----mmmm   Use the _v_i_t_e_r_m(EXPTOOLS) or _e_m_a_c_s_t_e_r_m(EXPTOOLS) mouse
               exclusively so more than 26 selections can be
               displayed.
          ----tttt   Display file types in a similar manner to _f_i_l_e(1).
          ----vvvv   Display files in the viewpath (see VIEWPATH section).

          Each entry of the directory is labeled with a letter.  To
          select a entry, press its corresponding letter.  What
          happens after selection depends on the nature of the entry.
          If the entry is a directory, _v_s_h changes to that directory,
          whereas text files are edited.  Full details are given
          later.

          _V_s_h displays up to twenty files at a time.  Directories
          which are larger are broken into twenty-file pages.  To
          select a page, one presses a digit 0000----9999.  Pages are numbered
          one through ten with 0000 selecting page ten.

          A well integrated feature of _v_s_h is its connection between
          compilers and editors.  To start a compile, one presses MMMM.
          _V_s_h then calls _m_a_k_e(1) (or _b_u_i_l_d(1) if the current directory
          is in the first node of the viewpath).  The output of this
          compile step is saved, and one can later review for
          compile-time errors.  _V_s_h labels each error with a letter.
          One can select an error by typing in its letter.  After
          selection, _v_s_h calls an editor, sending one to the proper
          file at the offending line.  One can jump between the editor
          and _v_s_h until one is ready for another compile.




     Page 1                                         (printed 12/13/90)






     VVVVSSSSHHHH((((1111))))                    UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV                    VVVVSSSSHHHH((((1111))))



          _V_s_h also provides an on-line symbol cross-reference of the
          files in the directory by using _g_r_e_p(1) to find the symbol
          in the files and using the same editor interface described
          above to examine the context surrounding each symbol.

     FFFFIIIILLLLEEEE NNNNAAAAMMMMEEEESSSS
          When you are prompted for a file or directory name, you
          cannot use the shell file name generation meta-characters
          (*?[]).  You can use tilde (~) by itself to represent your
          home directory (e.g.  ~/_f_i_l_e_n_a_m_e), or tilde followed by a
          user name to represent their home directory (e.g.
          ~_u_s_e_r/_f_i_l_e_n_a_m_e).

     FFFFIIIILLLLEEEE SSSSEEEELLLLEEEECCCCTTTTIIIIOOOONNNN
          As indicated before, one selects a file by pressing its
          corresponding letter.  What happens after selection depends
          on the nature of the file.

          FFFFiiiilllleeee ttttyyyyppppeeee  AAAAccccttttiiiioooonnnn

          DDDDiiiirrrreeeeccccttttoooorrrryyyy  Change to new directory.
          AAAArrrrcccchhhhiiiivvvveeee    Print archive directory.  This works for both
                     _a_r(1) and _c_p_i_o(1) format archives.
          CCCCoooorrrreeee       Call debugger.
          OOOObbbbjjjjeeeecccctttt     Print the symbol name list with _n_m(1).
          SSSSCCCCCCCCSSSS       Call editor.
          TTTTeeeexxxxtttt       Call editor.
          OOOOtttthhhheeeerrrr      Selection fails.

     DDDDIIIIRRRREEEECCCCTTTTOOOORRRRYYYY CCCCOOOOMMMMMMMMAAAANNNNDDDDSSSS
          This is a list of the directory commands.  Before doing
          anything else, you should become familiar with commands
          which allow you to select files and display directories.  In
          directories larger then twenty files, you should be able to
          display each page.

          CCCCoooommmmmmmmaaaannnndddd   AAAAccccttttiiiioooonnnn

          aaaa----tttt       Select associated file or directory.
          1111----9999       Select page 1-9.
          0000         Select page 10.
          ssssppppaaaacccceeee bbbbaaaarrrr Select next page.
          ++++         Select next page.
          ----         Select previous page.
          ::::         Change to parent directory.
          ~~~~         Change to HOME directory.
          ////         Change to root directory.
          !!!!         Escape to shell specified in the SHELL environment
                    variable.
          ^^^^LLLL        Redraw the screen.
          ????         Display help file.
          ^^^^DDDD        Leave _v_s_h.



     Page 2                                         (printed 12/13/90)






     VVVVSSSSHHHH((((1111))))                    UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV                    VVVVSSSSHHHH((((1111))))



          AAAA         Show All directory entries, including those whose
                    names begin with a period (.).  If this is already
                    in effect, this command will revert to not
                    displaying such files.
          CCCC         Create a file or directory.  _V_s_h prompts for a
                    name.  One may also copy, link, or move existing
                    files.
          DDDD         Display Date.
          FFFF         Select file or directory by name.  _V_s_h prompts for
                    a name and then selects the specified file or
                    directory.  If it isn't found and it doesn't start
                    with a /, _v_s_h will look for a matching directory
                    using the CDPATH environment variable, just like
                    _k_s_h(1).  If the name is - and there isn't a -
                    directory, _v_s_h will select the previous directory.
          LLLL         Long format file display in a similar manner to
                    _l_s(1).
          OOOO         Option listing.  The contents of command and
                    parameter tables are displayed.  _V_s_h then prompts
                    for commands which modify parameters and which
                    create, modify, and delete commands.
          PPPP         Display Process status with _p_s(1).
          TTTT         Display file Types in a similar manner to _f_i_l_e(1).
          VVVV         Display files in the viewpath (see VIEWPATH
                    section).
          WWWW         Display Who is logged in.
          XXXX         Call _c_s_c_o_p_e(1) to display a symbol cross-reference
                    of the C source files in this directory.

     RRRREEEEMMMMOOOOVVVVEEEE MMMMOOOODDDDEEEE
          Press RRRR to enter _R_e_m_o_v_e _m_o_d_e.  In _R_e_m_o_v_e _m_o_d_e, selecting a
          file causes it to be marked for removal with two slashes
          (//).  Files selected a second time are unmarked.  Pressing
          RRRR a second time causes all marked files to be removed.  The
          following commands are available in _R_e_m_o_v_e _m_o_d_e:

          CCCCoooommmmmmmmaaaannnndddd   AAAAccccttttiiiioooonnnn

          aaaa----tttt       Select corresponding file for removal.  Selecting
                    a file a second time "undeletes" the file.
          ****         Select all files on current page for removal.
          RRRR         Remove marked files and exit _R_e_m_o_v_e _m_o_d_e.  If _v_s_h
                    cannot remove a file, _v_s_h displays the reason and
                    waits for a response.  Press the RETURN key to
                    continue removing marked files.  Press ^^^^DDDD to
                    immediately exit from _R_e_m_o_v_e _m_o_d_e.
          ????         Display help file.
          ^^^^DDDD        Exit _R_e_m_o_v_e _m_o_d_e with out removing marked files.

          In addition to these commands, all of the directory
          selection commands are available.




     Page 3                                         (printed 12/13/90)






     VVVVSSSSHHHH((((1111))))                    UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV                    VVVVSSSSHHHH((((1111))))



     MMMMAAAAKKKKEEEE,,,, GGGGRRRREEEEPPPP,,,, AAAANNNNDDDD SSSSHHHHOOOOWWWWFFFFIIIILLLLEEEE
          _V_s_h interfaces to _m_a_k_e/_b_u_i_l_d(1) and _g_r_e_p(1).  _V_s_h saves
          output from these programs and allows one to examine the
          results in _S_h_o_w_f_i_l_e _m_o_d_e.  The following directory commands
          control _m_a_k_e/_b_u_i_l_d, _g_r_e_p, and _S_h_o_w_f_i_l_e.

          CCCCoooommmmmmmmaaaannnndddd   AAAAccccttttiiiioooonnnn

          GGGG         _G_r_e_p(1).  _V_s_h prompts for a pattern and file
                    names, and then run _g_r_e_p with these parameters.
                    The file names default to *.[!aotz].  The results
                    are saved in the file _g_r_e_p._o_u_t and displayed in
                    _S_h_o_w_f_i_l_e _m_o_d_e.
          SSSS         Show previous _g_r_e_p.  The output of the last _g_r_e_p
                    is displayed in _S_h_o_w_f_i_l_e _m_o_d_e.
          MMMM         Run _m_a_k_e/_b_u_i_l_d(1) in the foreground using the
                    _m_a_k_e_f_i_l_e, _M_a_k_e_f_i_l_e, or *._m_k file in the current
                    directory.  Output is both displayed on the screen
                    and saved in the file _m_a_k_e._o_u_t.  When _m_a_k_e/_b_u_i_l_d
                    terminates, _v_s_h displays _m_a_k_e._o_u_t in
                    _S_h_o_w_f_i_l_e _m_o_d_e.
          NNNN         Run _m_a_k_e/_b_u_i_l_d(1) in the background.  Output is
                    saved in _m_a_k_e._o_u_t, but is not displayed on the
                    screen.  When _m_a_k_e/_b_u_i_l_d terminates, the bell on
                    your terminal rings twice.  Use the EEEE command to
                    review the output in _m_a_k_e._o_u_t.
          EEEE         Review the results of the last _m_a_k_e/_b_u_i_l_d in
                    _S_h_o_w_f_i_l_e _m_o_d_e.
          YYYY         Run a command in the background.  Output is saved
                    in _u_s_e_r._o_u_t, but is not displayed on the screen.
                    When the command terminates, the bell on your
                    terminal rings twice.  Use the ZZZZ command to review
                    the output in _u_s_e_r._o_u_t.
          ZZZZ         Review the output of the above command in
                    _S_h_o_w_f_i_l_e _m_o_d_e.

     SSSSHHHHOOOOWWWWFFFFIIIILLLLEEEE MMMMOOOODDDDEEEE
          _S_h_o_w_f_i_l_e displays the results of a _m_a_k_e/_b_u_i_l_d or _g_r_e_p.  It
          is called by the EEEE and SSSS commands.  _S_h_o_w_f_i_l_e is called
          automatically in the course of an MMMM or GGGG command.  _S_h_o_w_f_i_l_e
          is essentially a special editor.  It has commands which
          allow one to display a file.  One can also command _S_h_o_w_f_i_l_e
          to examine a line of the file.  _S_h_o_w_f_i_l_e scans this line and
          attempt to extract a file name and line number.  _S_h_o_w_f_i_l_e
          then runs the editor, starting it at the specified line.

          CCCCoooommmmmmmmaaaannnndddd   AAAAccccttttiiiioooonnnn

          ^^^^DDDD        Leave _S_h_o_w_f_i_l_e.
          aaaa----tttt       Examine line for a file name and line number.  If
                    a file name is found, run the editor on this file.
          ssssppppaaaacccceeee bbbbaaaarrrr Select next page.



     Page 4                                         (printed 12/13/90)






     VVVVSSSSHHHH((((1111))))                    UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV                    VVVVSSSSHHHH((((1111))))



          ++++         Select next page.
          ----         Select previous page.
          ????         Display help file.

          All directory commands which might be useful are available
          in _S_h_o_w_f_i_l_e mode with the exception of LLLL and RRRR.
          Particularly useful are MMMM and GGGG which allow new iterations
          of _m_a_k_e/_b_u_i_l_d and _g_r_e_p, the escape to the shell (!), and FFFF,
          which allows one to edit files not found in the file being
          shown.

     CCCCOOOONNNNTTTTRRRROOOOLLLL CCCCOOOOMMMMMMMMAAAANNNNDDDDSSSS
          The operation of _v_s_h is controlled by its parameter and
          command tables.  The contents of these tables can be
          displayed via the OOOO command.  These tables can be modified
          with control commands.  When _v_s_h is invoked, it searches for
          the file ._v_s_h_r_c in your home directory.  Control commands
          are then read from this file, allowing one to create a
          personalized environment.  The OOOO command also prompts for
          control commands, allowing for interactive modification of
          the tables.

          These control commands should be presented in the same
          lexical grammar as shell commands.  Spaces and tabs separate
          tokens.  Unquoted newlines terminate each statement.  A
          character may be quoted by preceding it with a backslash
          (\).  All characters inside single quotes (' ') are quoted
          except the single quote.  Inside double quotes (" "), \\\\
          quotes another double quote and \\\\nnnneeeewwwwlllliiiinnnneeee is ignored.  Grave
          accents (` `) are treated as any other character.  Macros
          (such as $HOME) are not available.

          To change a parameter, use the format:

               Parameter Value

          PPPPaaaarrrraaaammmmeeeetttteeeerrrr can be any of the following:

          PPPPaaaarrrraaaammmmeeeetttteeeerrrr DDDDeeeeffffaaaauuuulllltttt   UUUUssssaaaaggggeeee

          eeeeddddiiiittttoooorrrr    vvvviiii        Preferred editor.
          ddddeeeebbbbuuuuggggggggeeeerrrr  ssssddddbbbb       Preferred debugger.
          mmmmaaaakkkkeeee      mmmmaaaakkkkeeee      Make program.
          bbbbuuuuiiiilllldddd     bbbbuuuuiiiilllldddd     Build program.  You may want to change
                              this to _m_o_d_b_u_i_l_d, for example.
          ggggrrrreeeeppppoooouuuutttt   ggggrrrreeeepppp....oooouuuutttt  File used to save the output of _g_r_e_p.
          mmmmaaaakkkkeeeeoooouuuutttt   mmmmaaaakkkkeeee....oooouuuutttt  File used to save the output of _m_a_k_e.
          uuuusssseeeerrrroooouuuutttt   uuuusssseeeerrrr....oooouuuutttt  File used to save the output of the user
                              command.

          To define a command, use the format:




     Page 5                                         (printed 12/13/90)






     VVVVSSSSHHHH((((1111))))                    UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV                    VVVVSSSSHHHH((((1111))))



               Character Keyword [Parameters]

          CCCChhhhaaaarrrraaaacccctttteeeerrrr is the character which calls the new command.
          Valid characters are !!!! """" #### $$$$ %%%% &&&& '''' (((( )))) :::: **** ==== ^^^^ ~~~~ [[[[ ]]]] {{{{ }}}} <<<< >>>>
          ,,,, .... //// ????  and AAAA----ZZZZ.

          These are the valid keywords:
          ccccrrrreeeeaaaatttteeee      Create a file.
          ddddaaaatttteeee        Display date.
          ddddiiiissssppppllllaaaayyyy     Select a file or directory.  If parameter is
                      present, it is displayed.  Otherwise, _v_s_h will
                      prompt for a path name.
          eeeexxxxeeeecccc        Execute a program directly with the _e_x_e_c_l_p
                      system call.  The first parameter must be the
                      program name.  Any other parameters become
                      parameters to the program.  If it is necessary
                      to redirect files, to expand macros, or to
                      expand file regular expressions, use the sssshhhheeeellllllll
                      keyword instead.
          sssshhhheeeellllllll       If no parameter is present, an interactive shell
                      is spawned.  If one parameter is present, it is
                      passed to the shell and run as a command.  Do
                      not specify more than one parameter.  Instead,
                      enclose the entire shell command in quotes to
                      provide _v_s_h with only one parameter.
          ggggrrrreeeepppp        Run _g_r_e_p.  _V_s_h will prompt for parameters.
          sssshhhhoooowwwwggggrrrreeeepppp    Show output from previous _g_r_e_p.
          nnnnoooowwwwaaaaiiiittttmmmmaaaakkkkeeee  Run _m_a_k_e/_b_u_i_l_d.  Do not wait for termination.
          wwwwaaaaiiiittttmmmmaaaakkkkeeee    Run _m_a_k_e/_b_u_i_l_d.  Wait for termination.
          sssshhhhoooowwwweeeerrrrrrrroooorrrr   Show errors from previous _m_a_k_e/_b_u_i_l_d.
          uuuusssseeeerrrr        Run a command in the background.
          sssshhhhoooowwwwuuuusssseeeerrrr    Show the output from the above command.
          hhhhoooommmmeeee        Change to home directory.
          ooooppppttttiiiioooonnnnssss     Display _v_s_h options (parameter and command
                      tables).  Accept commands which modify
                      parameters and which create, modify, and delete
                      commands.
          rrrreeeemmmmoooovvvveeee      Enter _R_e_m_o_v_e _m_o_d_e.
          sssshhhhoooowwwwaaaallllllll     Show all directory entries, including those
                      whose names begin with a period (.).
          lllloooonnnngggglllliiiisssstttt    Long format display in a similar manner to
                      _l_s(1).
          ttttyyyyppppeeee        Display file types in a similar manner to
                      _f_i_l_e(1).
          vvvviiiieeeewwwwppppaaaatttthhhh    Display files in the viewpath (see below).
          nnnnuuuullllllll        Do nothing.

     VVVVIIIIEEEEWWWWPPPPAAAATTTTHHHH
          As described above, _v_s_h displays the current directory
          entries by default.  When the VPATH environment variable is
          set, _v_s_h displays entries in directories that comprise your
          viewpath.  A viewpath is an ordered list of directories,



     Page 6                                         (printed 12/13/90)






     VVVVSSSSHHHH((((1111))))                    UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV                    VVVVSSSSHHHH((((1111))))



          each of which has the same directory structure below it.

          For example, suppose you are part of a software project.
          There is an official set of source files in directories
          below /_f_s_1/_o_f_c and each user has some matching directories
          under their home directory ($HOME).  If you make changes to
          the software system, you may have copies of just those files
          you are changing in $_H_O_M_E/_s_r_c/_c_m_d/_p_r_o_g_1.  The official
          versions of the entire program can be found in
          /_f_s_1/_o_f_c/_s_r_c/_c_m_d/_p_r_o_g_1.

          Suppose you use _v_s_h to browse through the three files that
          comprise _p_r_o_g_1, namely _f_1._c, _f_2._c, and _f_3._c.  You would set
          VPATH to $_H_O_M_E and /_f_s_1/_o_f_c, and export it:

               VPATH=$HOME:/fs1/ofc
               export VPATH

          You would then make your current directory
          $_H_O_M_E/_s_r_c/_c_m_d/_p_r_o_g_1 and invoke _v_s_h:

               cd $HOME/src/cmd/prog1
               vsh

          _V_s_h will locate all files in the viewpath.  In case
          duplicates are found, _v_s_h displays the file whose parent
          directory appears earlier in VPATH.  Thus if _f_2._c is in your
          directory (and all three files are in the official
          directory), _v_s_h will display _f_2._c from your directory and
          _f_1._c and _f_3._c from the official directory.

          The first directory in VPATH must be a prefix (usually
          $HOME) of the directory you will be working in.  Each
          colon-separated directory in VPATH must be a full path, that
          is, it must start with a slash (/).

     EEEENNNNVVVVIIIIRRRROOOONNNNMMMMEEEENNNNTTTT VVVVAAAARRRRIIIIAAAABBBBLLLLEEEESSSS
          CCCCDDDDPPPPAAAATTTTHHHH    Search path for directory names.  See the _c_d
                    command of _s_h(1).
          EEEEDDDDIIIITTTTOOOORRRR    Your preferred editor, which defaults to _v_i(1).
          HHHHOOOOMMMMEEEE      Your home directory, which is automatically set
                    when you login.
          MMMMOOOOUUUUSSSSEEEE     Set to _m_y_x if that is your 5620 terminal program.
          SSSSHHHHEEEELLLLLLLL     Your preferred shell, which defaults to _s_h(1).
          TTTTEEEERRRRMMMM      The terminal type, which must be a screen
                    terminal.
          TTTTEEEERRRRMMMMCCCCAAAAPPPP   TTTTEEEERRRRMMMMIIIINNNNFFFFOOOO Terminal information directory full path
                    name.  If your terminal is not in the standard
                    _t_e_r_m_i_n_f_o directory, see _c_u_r_s_e_s(3X) and _t_e_r_m_i_n_f_o(4)
                    for how to make your own terminal description.
          VVVVPPPPAAAATTTTHHHH     Viewpath (see VIEWPATH section).




     Page 7                                         (printed 12/13/90)






     VVVVSSSSHHHH((((1111))))                    UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV                    VVVVSSSSHHHH((((1111))))



          To set a variable such as EEEEDDDDIIIITTTTOOOORRRR to a value such as _e_m_a_c_s,
          put this in your ._p_r_o_f_i_l_e:

               export EDITOR
               EDITOR=emacs

     FFFFIIIILLLLEEEESSSS
          $HOME/.vshrc  Initialization file (see CONTROL COMMANDS).
          grep.out      File used to save the output of _g_r_e_p.  _V_s_h
                        tries to first create this file in the current
                        directory.  If unsuccessful, the home
                        directory is tried.
          make.out      File used to save the output of _m_a_k_e/_b_u_i_l_d.
          user.out      File used to save the output of user command.
          makefile      Possible makefile name.
          Makefile      Possible makefile name.
          *.mk          Possible makefile name.

     PPPPRRRROOOOVVVVIIIIDDDDEEEERRRR
          Joe Steffen



































     Page 8                                         (printed 12/13/90)



