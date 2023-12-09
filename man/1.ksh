


     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



     NNNNAAAAMMMMEEEE
          ksh, rksh - KornShell, a standard/restricted command and
          programming language

     SSSSYYYYNNNNOOOOPPPPSSSSIIIISSSS
          kkkksssshhhh [ ++++____aaaaeeeeffffhhhhiiiikkkkmmmmnnnnoooopppprrrrssssttttuuuuvvvvxxxx ] [ ++++____oooo option ] ...  [ ----cccc string ] [
          arg ... ]
          rrrrkkkksssshhhh [ ++++____aaaaeeeeffffhhhhiiiikkkkmmmmnnnnoooopppprrrrssssttttuuuuvvvvxxxx ] [ ++++____oooo option ] ...  [ ----cccc string ]
          [ arg ... ]

     DDDDEEEESSSSCCCCRRRRIIIIPPPPTTTTIIIIOOOONNNN
          _K_s_h is a command and programming language that executes
          commands read from a terminal or a file.  _R_k_s_h is a
          restricted version of the command interpreter _k_s_h; it is
          used to set up login names and execution environments whose
          capabilities are more controlled than those of the standard
          shell.  See _I_n_v_o_c_a_t_i_o_n below for the meaning of arguments to
          the shell.

        DDDDeeeeffffiiiinnnniiiittttiiiioooonnnnssss....
          A _m_e_t_a_c_h_a_r_a_c_t_e_r is one of the following characters:

               ;;;;   &&&&   ((((   ))))   ||||   <<<<   >>>>   nnnneeeewwww----lllliiiinnnneeee   ssssppppaaaacccceeee   ttttaaaabbbb

          A _b_l_a_n_k is a ttttaaaabbbb or a ssssppppaaaacccceeee.  An _i_d_e_n_t_i_f_i_e_r is a sequence of
          letters, digits, or underscores starting with a letter or
          underscore.  Identifiers are used as names for _f_u_n_c_t_i_o_n_s and
          _v_a_r_i_a_b_l_e_s.  A _w_o_r_d is a sequence of _c_h_a_r_a_c_t_e_r_s separated by
          one or more non-quoted _m_e_t_a_c_h_a_r_a_c_t_e_r_s.
          A _c_o_m_m_a_n_d is a sequence of characters in the syntax of the
          shell language.  The shell reads each command and carries
          out the desired action either directly or by invoking
          separate utilities.  A special command is a command that is
          carried out by the shell without creating a separate
          process.  Except for documented side effects, most special
          commands can be implemented as separate utilities.

        CCCCoooommmmmmmmaaaannnnddddssss....
          A _s_i_m_p_l_e-_c_o_m_m_a_n_d is a sequence of _b_l_a_n_k separated words
          which may be preceded by a variable assignment list.  (See
          _E_n_v_i_r_o_n_m_e_n_t below.)  The first word specifies the name of
          the command to be executed.  Except as specified below, the
          remaining words are passed as arguments to the invoked
          command.  The command name is passed as argument 0 (see
          _e_x_e_c(2)).  The _v_a_l_u_e of a simple-command is its exit status
          if it terminates normally, or (octal) 200+_s_t_a_t_u_s if it
          terminates abnormally (see _s_i_g_n_a_l(2) for a list of status
          values).

          A _p_i_p_e_l_i_n_e is a sequence of one or more _c_o_m_m_a_n_d_s separated
          by ||||.  The standard output of each command but the last is
          connected by a _p_i_p_e(2) to the standard input of the next



     Page 1                                          (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          command.  Each command is run as a separate process; the
          shell waits for the last command to terminate.  The exit
          status of a pipeline is the exit status of the last command.

          A _l_i_s_t is a sequence of one or more pipelines separated by
          ;;;;, &&&&, &&&&&&&&, or ||||||||, and optionally terminated by ;;;;, &&&&, or ||||&&&&.
          Of these five symbols, ;;;;, &&&&, and ||||&&&& have equal precedence,
          which is lower than that of &&&&&&&& and ||||||||.  The symbols &&&&&&&& and
          |||||||| also have equal precedence.  A semicolon (;;;;) causes
          sequential execution of the preceding pipeline; an ampersand
          (&&&&) causes asynchronous execution of the preceding pipeline
          (i.e., the shell does _n_o_t wait for that pipeline to finish).
          The symbol ||||&&&& causes asynchronous execution of the preceding
          command or pipeline with a two-way pipe established to the
          parent shell.  The standard input and output of the spawned
          command can be written to and read from by the parent Shell
          using the ----pppp option of the special commands rrrreeeeaaaadddd and pppprrrriiiinnnntttt
          described later.  The symbol &&&&&&&& (||||||||) causes the _l_i_s_t
          following it to be executed only if the preceding pipeline
          returns a zero (non-zero) value.  An arbitrary number of
          new-lines may appear in a _l_i_s_t, instead of a semicolon, to
          delimit a command.

          A _c_o_m_m_a_n_d is either a simple-command or one of the
          following.  Unless otherwise stated, the value returned by a
          command is that of the last simple-command executed in the
          command.

          ffffoooorrrr _i_d_e_n_t_i_f_i_e_r [ iiiinnnn _w_o_r_d ... ] ;;;;ddddoooo _l_i_s_t ;;;;ddddoooonnnneeee
               Each time a ffffoooorrrr command is executed, _i_d_e_n_t_i_f_i_e_r is set
               to the next _w_o_r_d taken from the iiiinnnn _w_o_r_d list.  If iiiinnnn
               _w_o_r_d ...  is omitted, then the ffffoooorrrr command executes the
               ddddoooo _l_i_s_t once for each positional parameter that is set
               (see _P_a_r_a_m_e_t_e_r _S_u_b_s_t_i_t_u_t_i_o_n below).  Execution ends
               when there are no more words in the list.

          sssseeeelllleeeecccctttt _i_d_e_n_t_i_f_i_e_r [ iiiinnnn _w_o_r_d ... ] ;;;;ddddoooo _l_i_s_t ;;;;ddddoooonnnneeee
               A sssseeeelllleeeecccctttt command prints on standard error (file
               descriptor 2), the set of _w_o_r_ds, each preceded by a
               number.  If iiiinnnn _w_o_r_d ...  is omitted, then the
               positional parameters are used instead (see _P_a_r_a_m_e_t_e_r
               _S_u_b_s_t_i_t_u_t_i_o_n below).  The PPPPSSSS3333 prompt is printed and a
               line is read from the standard input.  If this line
               consists of the number of one of the listed _w_o_r_ds, then
               the value of the variable _i_d_e_n_t_i_f_i_e_r is set to the _w_o_r_d
               corresponding to this number.  If this line is empty
               the selection list is printed again.  Otherwise the
               value of the variable _i_d_e_n_t_i_f_i_e_r is set to _n_u_l_l.  The
               contents of the line read from standard input is saved
               in the variable RRRREEEEPPPPLLLLYYYY....  The _l_i_s_t is executed for each
               selection until a bbbbrrrreeeeaaaakkkk or _e_n_d-_o_f-_f_i_l_e is encountered.




     Page 2                                          (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          ccccaaaasssseeee _w_o_r_d iiiinnnn [ [((((]_p_a_t_t_e_r_n [ | _p_a_t_t_e_r_n ] ... )))) _l_i_s_t ;;;;;;;; ] ... eeeessssaaaacccc
               A ccccaaaasssseeee command executes the _l_i_s_t associated with the
               first _p_a_t_t_e_r_n that matches _w_o_r_d.  The form of the
               patterns is the same as that used for file-name
               generation (see _F_i_l_e _N_a_m_e _G_e_n_e_r_a_t_i_o_n below).

          iiiiffff _l_i_s_t ;;;;tttthhhheeeennnn _l_i_s_t [ eeeelllliiiiffff _l_i_s_t ;;;;tttthhhheeeennnn _l_i_s_t ] ... [ ;;;;eeeellllsssseeee _l_i_s_t ] ;;;;ffffiiii
               The _l_i_s_t following iiiiffff is executed and, if it returns
               a zero exit status, the _l_i_s_t following the first
               tttthhhheeeennnn is executed.  Otherwise, the _l_i_s_t following
               eeeelllliiiiffff is executed and, if its value is zero, the _l_i_s_t
               following the next tttthhhheeeennnn is executed.  Failing that,
               the eeeellllsssseeee _l_i_s_t is executed.  If no eeeellllsssseeee _l_i_s_t or tttthhhheeeennnn
               _l_i_s_t is executed, then the iiiiffff command returns a zero
               exit status.

          wwwwhhhhiiiilllleeee _l_i_s_t ;;;;ddddoooo _l_i_s_t ;;;;ddddoooonnnneeee
          uuuunnnnttttiiiillll _l_i_s_t ;;;;ddddoooo _l_i_s_t ;;;;ddddoooonnnneeee
               A wwwwhhhhiiiilllleeee command repeatedly executes the wwwwhhhhiiiilllleeee _l_i_s_t and,
               if the exit status of the last command in the list is
               zero, executes the ddddoooo _l_i_s_t; otherwise the loop
               terminates.  If no commands in the ddddoooo _l_i_s_t are
               executed, then the wwwwhhhhiiiilllleeee command returns a zero exit
               status; uuuunnnnttttiiiillll may be used in place of wwwwhhhhiiiilllleeee to negate
               the loop termination test.

          ((((_l_i_s_t))))
               Execute _l_i_s_t in a separate environment.  Note, that if
               two adjacent open parentheses are needed for nesting, a
               space must be inserted to avoid arithmetic evaluation
               as described below.

          {{{{ _l_i_s_t;;;;}}}}
               _l_i_s_t is simply executed.  Note that unlike the
               metacharacters (((( and )))), {{{{ and }}}} are _r_e_s_e_r_v_e_d _w_o_r_ds and
               must occur at the beginning of a line or after a ;;;; in
               order to be recognized.

          [[[[[[[[_e_x_p_r_e_s_s_i_o_n]]]]]]]]
               Evaluates _e_x_p_r_e_s_s_i_o_n and returns a zero exit status
               when _e_x_p_r_e_s_s_i_o_n is true.  See _C_o_n_d_i_t_i_o_n_a_l _E_x_p_r_e_s_s_i_o_n_s
               below, for a description of _e_x_p_r_e_s_s_i_o_n.

          ffffuuuunnnnccccttttiiiioooonnnn _i_d_e_n_t_i_f_i_e_r {{{{ _l_i_s_t ;;;;}}}}
          _i_d_e_n_t_i_f_i_e_r (((()))) {{{{ _l_i_s_t ;;;;}}}}
               Define a function which is referenced by _i_d_e_n_t_i_f_i_e_r.
               The body of the function is the _l_i_s_t of commands
               between {{{{ and }}}}.  (See _F_u_n_c_t_i_o_n_s below).

          ttttiiiimmmmeeee _p_i_p_e_l_i_n_e
               The _p_i_p_e_l_i_n_e is executed and the elapsed time as well
               as the user and system time are printed on standard



     Page 3                                          (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               error.

          The following reserved words are only recognized as the
          first word of a command and when not quoted:

          iiiiffff tttthhhheeeennnn eeeellllsssseeee eeeelllliiiiffff ffffiiii ccccaaaasssseeee eeeessssaaaacccc ffffoooorrrr wwwwhhhhiiiilllleeee uuuunnnnttttiiiillll ddddoooo ddddoooonnnneeee {{{{ }}}}
          ffffuuuunnnnccccttttiiiioooonnnn sssseeeelllleeeecccctttt ttttiiiimmmmeeee [[[[[[[[ ]]]]]]]]

        CCCCoooommmmmmmmeeeennnnttttssss....
          A word beginning with #### causes that word and all the
          following characters up to a new-line to be ignored.

        AAAAlllliiiiaaaassssiiiinnnngggg....
          The first word of each command is replaced by the text of an
          aaaalllliiiiaaaassss if an aaaalllliiiiaaaassss for this word has been defined.  An aaaalllliiiiaaaassss
          name consists of any number of characters excluding
          metacharacters, quoting characters, file expansion
          characters, parameter and command substitution characters,
          and ====.  The replacement string can contain any valid Shell
          script including the metacharacters listed above.  The first
          word of each command in the replaced text, other than any
          that are in the process of being replaced, will be tested
          for aliases.  If the last character of the alias value is a
          _b_l_a_n_k then the word following the alias will also be checked
          for alias substitution.  Aliases can be used to redefine
          special builtin commands but cannot be used to redefine the
          reserved words listed above.  Aliases can be created,
          listed, and exported with the aaaalllliiiiaaaassss command and can be
          removed with the uuuunnnnaaaalllliiiiaaaassss command.  Exported aliases remain
          in effect for scripts invoked by name, but must be
          reinitialized for separate invocations of the Shell (see
          _I_n_v_o_c_a_t_i_o_n below).

          _A_l_i_a_s_i_n_g is performed when scripts are read, not while they
          are executed.  Therefore, for an alias to take effect the
          aaaalllliiiiaaaassss definition command has to be executed before the
          command which references the alias is read.

          Aliases are frequently used as a short hand for full path
          names.  An option to the aliasing facility allows the value
          of the alias to be automatically set to the full pathname of
          the corresponding command.  These aliases are called _t_r_a_c_k_e_d
          aliases.  The value of a _t_r_a_c_k_e_d alias is defined the first
          time the corresponding command is looked up and becomes
          undefined each time the PPPPAAAATTTTHHHH variable is reset.  These
          aliases remain _t_r_a_c_k_e_d so that the next subsequent reference
          will redefine the value.  Several tracked aliases are
          compiled into the shell.  The ----hhhh option of the sssseeeetttt command
          makes each referenced command name into a tracked alias.

          The following _e_x_p_o_r_t_e_d _a_l_i_a_s_e_s are compiled into the shell
          but can be unset or redefined:



     Page 4                                          (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



                              aaaauuuuttttoooollllooooaaaadddd====''''ttttyyyyppppeeeesssseeeetttt ----ffffuuuu''''
                              ffffaaaallllsssseeee====''''lllleeeetttt 0000''''
                              ffffuuuunnnnccccttttiiiioooonnnnssss====''''ttttyyyyppppeeeesssseeeetttt ----ffff''''
                              hhhhaaaasssshhhh====''''aaaalllliiiiaaaassss ----tttt''''
                              hhhhiiiissssttttoooorrrryyyy====''''ffffcccc ----llll''''
                              iiiinnnntttteeeeggggeeeerrrr====''''ttttyyyyppppeeeesssseeeetttt ----iiii''''
                              nnnnoooohhhhuuuupppp====''''nnnnoooohhhhuuuupppp ''''
                              rrrr====''''ffffcccc ----eeee ----''''
                              ttttrrrruuuueeee====''''::::''''
                              ttttyyyyppppeeee====''''wwwwhhhheeeennnncccceeee ----vvvv''''

        TTTTiiiillllddddeeee SSSSuuuubbbbssssttttiiiittttuuuuttttiiiioooonnnn....
          After alias substitution is performed, each word is checked
          to see if it begins with an unquoted 9~~~~8.  If it does, then
          the word up to a //// is checked to see if it matches a user
          name in the ////eeeettttcccc////ppppaaaasssssssswwwwdddd file.  If a match is found, the 9~~~~8
          and the matched login name are replaced by the login
          directory of the matched user.  This is called a _t_i_l_d_e
          substitution.  If no match is found, the original text is
          left unchanged.  A 9~~~~8 by itself, or in front of a ////, is
          replaced by $$$$HHHHOOOOMMMMEEEE.  variable.  A 9~~~~8 followed by a ++++ or ---- is
          replaced by $$$$PPPPWWWWDDDD and $$$$OOOOLLLLDDDDPPPPWWWWDDDD respectively.

          In addition, _t_i_l_d_e substitution is attempted when the value
          of a _v_a_r_i_a_b_l_e _a_s_s_i_g_n_m_e_n_t begins with a 9~~~~8.

        CCCCoooommmmmmmmaaaannnndddd SSSSuuuubbbbssssttttiiiittttuuuuttttiiiioooonnnn....
          The standard output from a command enclosed in parenthesis
          preceded by a dollar sign ( $$$$(((()))) ) or a pair of grave accents
          (````````) may be used as part or all of a word; trailing new-
          lines are removed.  In the second (archaic) form, the string
          between the quotes is processed for special quoting
          characters before the command is executed. (See _Q_u_o_t_i_n_g
          below.)  The command substitution $$$$((((ccccaaaatttt ffffiiiilllleeee)))) can be
          replaced by the equivalent but faster $$$$((((<<<<ffffiiiilllleeee)))).  Command
          substitution of most special commands that do not perform
          input/output redirection are carried out without creating a
          separate process.
          An arithmetic expression enclosed in double parenthesis
          preceded by a dollar sign ( $$$$(((((((()))))))) ) is replaced by the value
          of the arithmetic expression within the double parenthesis.

        PPPPrrrroooocccceeeessssssss SSSSuuuubbbbssssttttiiiittttuuuuttttiiiioooonnnn....
          This feature is only available on versions of the UNIX
          operating system that support the ////ddddeeeevvvv////ffffdddd directory for
          naming open files.  Each command argument of the form
          <<<<((((_l_i_s_t)))) or >>>>((((_l_i_s_t)))) will run process _l_i_s_t asynchronously
          connected to some file in ////ddddeeeevvvv////ffffdddd.  The name of this file
          will become the argument to the command.  If the form with >>>>
          is selected then writing on this file will provide input for
          _l_i_s_t.  If <<<< is used, then the file passed as an argument
          will contain the output of the _l_i_s_t process.  For example,



     Page 5                                          (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               ppppaaaasssstttteeee <<<<((((ccccuuuutttt ----ffff1111 _f_i_l_e_1)))) <<<<((((ccccuuuutttt ----ffff3333 _f_i_l_e_2)))) |||| tttteeeeeeee
               >>>>((((_p_r_o_c_e_s_s_1)))) >>>>((((_p_r_o_c_e_s_s_2))))

          _c_u_t_s fields 1 and 3 from the files _f_i_l_e_1 and _f_i_l_e_2
          respectively, _p_a_s_t_e_s the results together, and sends it to
          the processes _p_r_o_c_e_s_s_1 and _p_r_o_c_e_s_s_2, as well as putting it
          onto the standard output.  Note that the file, which is
          passed as an argument to the command, is a UNIX _p_i_p_e(2) so
          programs that expect to _l_s_e_e_k(2) on the file will not work.

        PPPPaaaarrrraaaammmmeeeetttteeeerrrr SSSSuuuubbbbssssttttiiiittttuuuuttttiiiioooonnnn....
          A _p_a_r_a_m_e_t_e_r is an _i_d_e_n_t_i_f_i_e_r, one or more digits, or any of
          the characters ****, @@@@, ####, ????, ----, $$$$, and !!!!.  A _v_a_r_i_a_b_l_e (a
          parameter denoted by an identifier) has a _v_a_l_u_e and zero or
          more _a_t_t_r_i_b_u_t_e_s.  _V_a_r_i_a_b_e_s can be assigned _v_a_l_u_e_s and
          _a_t_t_r_i_b_u_t_e_s by using the ttttyyyyppppeeeesssseeeetttt special command.  The
          attributes supported by the Shell are described later with
          the ttttyyyyppppeeeesssseeeetttt special command.  Exported variables pass values
          and attributes to the environment.

          The shell supports a one-dimensional array facility.  An
          element of an array variables is referenced by a _s_u_b_s_c_r_i_p_t.
          A _s_u_b_s_c_r_i_p_t is denoted by a [[[[, followed by an _a_r_i_t_h_m_e_t_i_c
          _e_x_p_r_e_s_s_i_o_n (see _A_r_i_t_h_m_e_t_i_c _e_v_a_l_u_a_t_i_o_n below) followed by a
          ]]]].  To assign values to an array, use sssseeeetttt ----AAAA _n_a_m_e  _v_a_l_u_e ...
          .  The value of all subscripts must be in the range of 0
          through 1023.  Arrays need not be declared.  Any reference
          to a variable with a valid subscript is legal and an array
          will be created if necessary.  Referencing an array without
          a subscript is equivalent to referencing the element zero.

          The _v_a_l_u_e of a _v_a_r_i_a_b_l_e may be assigned by writing:

               _n_a_m_e====_v_a_l_u_e [ _n_a_m_e====_v_a_l_u_e ] ...

          If the integer attribute, ----iiii, is set for _n_a_m_e the _v_a_l_u_e is
          subject to arithmetic evaluation as described below.
          Positional parameters, parameters denoted by a number, may
          be assigned values with the sssseeeetttt special command.  Parameter
          $$$$0000 is set from argument zero when the shell is invoked.
          The character $$$$ is used to introduce substitutable
          _p_a_r_a_m_e_t_e_r_s.
          $$$${{{{_p_a_r_a_m_e_t_e_r}}}}
               The shell reads all the characters from $$$${{{{ to the
               matching }}}} as part of the same word even if it contains
               braces or metacharacters.  The value, if any, of the
               parameter is substituted.  The braces are required when
               _p_a_r_a_m_e_t_e_r is followed by a letter, digit, or underscore
               that is not to be interpreted as part of its name or
               when a variable is subscripted.  If _p_a_r_a_m_e_t_e_r is one or
               more digits then it is a positional parameter.  A
               positional parameter of more than one digit must be



     Page 6                                          (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               enclosed in braces.  If _p_a_r_a_m_e_t_e_r is **** or @@@@, then all
               the positional parameters, starting with $$$$1111, are
               substituted (separated by a field separator character).
               If an array _i_d_e_n_t_i_f_i_e_r with subscript **** or @@@@ is used,
               then the value for each of the elements is substituted
               (separated by a field separator character).
          $$$${{{{####_p_a_r_a_m_e_t_e_r}}}}
               If _p_a_r_a_m_e_t_e_r is **** or @@@@, the number of positional
               parameters is substituted.  Otherwise, the length of
               the value of the _p_a_r_a_m_e_t_e_r is substituted.
          $$$${{{{####_i_d_e_n_t_i_f_i_e_r[[[[****]]]]}}}}
               The number of elements in the array _i_d_e_n_t_i_f_i_e_r is
               substituted.
          $$$${{{{_p_a_r_a_m_e_t_e_r::::----_w_o_r_d}}}}
               If _p_a_r_a_m_e_t_e_r is set and is non-null then substitute its
               value; otherwise substitute _w_o_r_d.
          $$$${{{{_p_a_r_a_m_e_t_e_r::::====_w_o_r_d}}}}
               If _p_a_r_a_m_e_t_e_r is not set or is null then set it to _w_o_r_d;
               the value of the parameter is then substituted.
               Positional parameters may not be assigned to in this
               way.
          $$$${{{{_p_a_r_a_m_e_t_e_r::::????_w_o_r_d}}}}
               If _p_a_r_a_m_e_t_e_r is set and is non-null then substitute its
               value; otherwise, print _w_o_r_d and exit from the shell.
               If _w_o_r_d is omitted then a standard message is printed.
          $$$${{{{_p_a_r_a_m_e_t_e_r::::++++_w_o_r_d}}}}
               If _p_a_r_a_m_e_t_e_r is set and is non-null then substitute
               _w_o_r_d; otherwise substitute nothing.
          $$$${{{{_p_a_r_a_m_e_t_e_r####_p_a_t_t_e_r_n}}}}
          $$$${{{{_p_a_r_a_m_e_t_e_r########_p_a_t_t_e_r_n}}}}
               If the Shell _p_a_t_t_e_r_n matches the beginning of the value
               of _p_a_r_a_m_e_t_e_r, then the value of this substitution is
               the value of the _p_a_r_a_m_e_t_e_r with the matched portion
               deleted; otherwise the value of this _p_a_r_a_m_e_t_e_r is
               substituted.  In the first form the smallest matching
               pattern is deleted and in the second form the largest
               matching pattern is deleted.

          $$$${{{{_p_a_r_a_m_e_t_e_r%%%%_p_a_t_t_e_r_n}}}}
          $$$${{{{_p_a_r_a_m_e_t_e_r%%%%%%%%_p_a_t_t_e_r_n}}}}
               If the Shell _p_a_t_t_e_r_n matches the end of the value of
               _p_a_r_a_m_e_t_e_r, then the value of this substitution is the
               value of the _p_a_r_a_m_e_t_e_r with the matched part deleted;
               otherwise substitute the value of _p_a_r_a_m_e_t_e_r.  In the
               first form the smallest matching pattern is deleted and
               in the second form the largest matching pattern is
               deleted.

          In the above, _w_o_r_d is not evaluated unless it is to be used
          as the substituted string, so that, in the following
          example, ppppwwwwdddd is executed only if dddd is not set or is null:




     Page 7                                          (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               echo ${d:-$(pwd)}

          If the colon ( :::: )))) is omitted from the above expressions,
          then the shell only checks whether _p_a_r_a_m_e_t_e_r is set or not.

          The following parameters are automatically set by the shell:
               ####    The number of positional parameters in decimal.
               ----    Flags supplied to the shell on invocation or by
                    the sssseeeetttt command.
               ????    The decimal value returned by the last executed
                    command.
               $$$$    The process number of this shell.
               ____    Initially, the value of ____ is an absolute pathname
                    of the shell or script being executed as passed in
                    the _e_n_v_i_r_o_n_m_e_n_t.  Subsequently it is assigned the
                    last argument of the previous command.  This
                    parameter is not set for commands which are
                    asynchronous.  This parameter is also used to hold
                    the name of the matching MMMMAAAAIIIILLLL file when checking
                    for mail.
               !!!!    The process number of the last background command
                    invoked.
               EEEERRRRRRRRNNNNOOOO
                    The value of _e_r_r_n_o as set by the most recently
                    failed system call.  This value is system
                    dependent and is intended for debugging purposes.
               LLLLIIIINNNNEEEENNNNOOOO
                    The line number of the current line within the
                    script or function being executed.
               OOOOLLLLDDDDPPPPWWWWDDDD
                    The previous working directory set by the ccccdddd
                    command.
               OOOOPPPPTTTTAAAARRRRGGGG
                    The value of the last option argument processed by
                    the ggggeeeettttooooppppttttssss special command.
               OOOOPPPPTTTTIIIINNNNDDDD
                    The index of the last option argument processed by
                    the ggggeeeettttooooppppttttssss special command.
               PPPPPPPPIIIIDDDD The process number of the parent of the shell.
               PPPPWWWWDDDD  The present working directory set by the ccccdddd
                    command.
               RRRRAAAANNNNDDDDOOOOMMMM
                    Each time this variable is referenced, a random
                    integer, uniformly distributed between 0 and
                    32767, is generated.  The sequence of random
                    numbers can be initialized by assigning a numeric
                    value to RRRRAAAANNNNDDDDOOOOMMMM.
               RRRREEEEPPPPLLLLYYYY
                    This variable is set by the sssseeeelllleeeecccctttt statement and
                    by the rrrreeeeaaaadddd special command when no arguments are
                    supplied.
               SSSSEEEECCCCOOOONNNNDDDDSSSS



     Page 8                                          (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



                    Each time this variable is referenced, the number
                    of seconds since shell invocation is returned.  If
                    this variable is assigned a value, then the value
                    returned upon reference will be the value that was
                    assigned plus the number of seconds since the
                    assignment.

          The following variables are used by the shell:
               CCCCDDDDPPPPAAAATTTTHHHH
                    The search path for the ccccdddd command.
               CCCCOOOOLLLLUUUUMMMMNNNNSSSS
                    If this variable is set, the value is used to
                    define the width of the edit window for the shell
                    edit modes and for printing sssseeeelllleeeecccctttt lists.
               EEEEDDDDIIIITTTTOOOORRRR
                    If the value of this variable ends in _e_m_a_c_s,
                    _g_m_a_c_s, or _v_i and the VVVVIIIISSSSUUUUAAAALLLL variable is not set,
                    then the corresponding option (see Special Command
                    sssseeeetttt below) will be turned on.
               EEEENNNNVVVV  If this variable is set, then parameter
                    substitution is performed on the value to generate
                    the pathname of the script that will be executed
                    when the _s_h_e_l_l is invoked.  (See _I_n_v_o_c_a_t_i_o_n
                    below.)  This file is typically used for _a_l_i_a_s and
                    _f_u_n_c_t_i_o_n definitions.
               FFFFCCCCEEEEDDDDIIIITTTT
                    The default editor name for the ffffcccc command.
               FFFFPPPPAAAATTTTHHHH
                    The search path for function definitions.  This
                    path is searched when a function with the ----uuuu
                    attribute is referenced and when a command is not
                    found.  If an executable file is found, then it is
                    read and executed in the current environment.
               IIIIFFFFSSSS  Internal field separators, normally ssssppppaaaacccceeee, ttttaaaabbbb,
                    and nnnneeeewwww----lllliiiinnnneeee that is used to separate command
                    words which result from command or parameter
                    substitution and for separating words with the
                    special command rrrreeeeaaaadddd.  The first character of the
                    IIIIFFFFSSSS variable is used to separate arguments for the
                    """"$$$$****"""" substitution (See _Q_u_o_t_i_n_g below).
               HHHHIIIISSSSTTTTFFFFIIIILLLLEEEE
                    If this variable is set when the shell is invoked,
                    then the value is the pathname of the file that
                    will be used to store the command history.  (See
                    _C_o_m_m_a_n_d _r_e-_e_n_t_r_y below.)
               HHHHIIIISSSSTTTTSSSSIIIIZZZZEEEE
                    If this variable is set when the shell is invoked,
                    then the number of previously entered commands
                    that are accessible by this shell will be greater
                    than or equal to this number.  The default is 128.
               HHHHOOOOMMMMEEEE The default argument (home directory) for the ccccdddd
                    command.



     Page 9                                          (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               LLLLIIIINNNNEEEESSSS
                    If this variable is set, the value is used to
                    determine the column length for printing sssseeeelllleeeecccctttt
                    lists.  Select lists will print vertically until
                    about two-thirds of LLLLIIIINNNNEEEESSSS lines are filled.
               MMMMAAAAIIIILLLL If this variable is set to the name of a mail file
                    _a_n_d the MMMMAAAAIIIILLLLPPPPAAAATTTTHHHH variable is not set, then the
                    shell informs the user of arrival of mail in the
                    specified file.
               MMMMAAAAIIIILLLLCCCCHHHHEEEECCCCKKKK
                    This variable specifies how often (in seconds) the
                    shell will check for changes in the modification
                    time of any of the files specified by the MMMMAAAAIIIILLLLPPPPAAAATTTTHHHH
                    or MMMMAAAAIIIILLLL variables.  The default value is 600
                    seconds.  When the time has elapsed the shell will
                    check before issuing the next prompt.
               MMMMAAAAIIIILLLLPPPPAAAATTTTHHHH
                    A colon ( :::: ) separated list of file names.  If
                    this variable is set then the shell informs the
                    user of any modifications to the specified files
                    that have occurred within the last MMMMAAAAIIIILLLLCCCCHHHHEEEECCCCKKKK
                    seconds.  Each file name can be followed by a ????
                    and a message that will be printed.  The message
                    will undergo parameter substitution with the
                    variable, $$$$____ defined as the name of the file that
                    has changed.  The default message is _y_o_u _h_a_v_e _m_a_i_l
                    _i_n $_.
               PPPPAAAATTTTHHHH The search path for commands (see _E_x_e_c_u_t_i_o_n
                    below).  The user may not change PPPPAAAATTTTHHHH if executing
                    under _r_k_s_h (except in ._p_r_o_f_i_l_e).
               PPPPSSSS1111  The value of this variable is expanded for
                    parameter substitution to define the primary
                    prompt string which by default is ``$$$$ ''.  The
                    character !!!! in the primary prompt string is
                    replaced by the _c_o_m_m_a_n_d number (see _C_o_m_m_a_n_d _R_e-
                    _e_n_t_r_y below).
               PPPPSSSS2222  Secondary prompt string, by default ``>>>> ''.
               PPPPSSSS3333  Selection prompt string used within a sssseeeelllleeeecccctttt loop,
                    by default ``####???? ''.
               PPPPSSSS4444  The value of this variable is expanded for
                    parameter substitution and precedes each line of
                    an execution trace.  If omitted, the execution
                    trace prompt is ``++++ ''.
               SSSSHHHHEEEELLLLLLLL
                    The pathname of the _s_h_e_l_l is kept in the
                    environment.  At invocation, if the basename of
                    this variable matches the pattern ****rrrr****sssshhhh, then the
                    shell becomes restricted.
               TTTTMMMMOOOOUUUUTTTT
                    If set to a value greater than zero, the shell
                    will terminate if a command is not entered within
                    the prescribed number of seconds after issuing the



     Page 10                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



                    PPPPSSSS1111 prompt.  (Note that the shell can be compiled
                    with a maximum bound for this value which cannot
                    be exceeded.)
               VVVVIIIISSSSUUUUAAAALLLL
                    If the value of this variable ends in _e_m_a_c_s,
                    _g_m_a_c_s, or _v_i then the corresponding option (see
                    Special Command sssseeeetttt below) will be turned on.

          The shell gives default values to PPPPAAAATTTTHHHH, PPPPSSSS1111, PPPPSSSS2222, MMMMAAAAIIIILLLLCCCCHHHHEEEECCCCKKKK,
          TTTTMMMMOOOOUUUUTTTT and IIIIFFFFSSSS, while HHHHOOOOMMMMEEEE, SSSSHHHHEEEELLLLLLLL EEEENNNNVVVV and MMMMAAAAIIIILLLL are not set at
          all by the shell (although HHHHOOOOMMMMEEEE _i_s set by _l_o_g_i_n(1)).  On
          some systems MMMMAAAAIIIILLLL and SSSSHHHHEEEELLLLLLLL are also set by _l_o_g_i_n(1).

        BBBBllllaaaannnnkkkk IIIInnnntttteeeerrrrpppprrrreeeettttaaaattttiiiioooonnnn....
          After parameter and command substitution, the results of
          substitutions are scanned for the field separator characters
          (those found in IIIIFFFFSSSS) and split into distinct arguments where
          such characters are found.  Explicit null arguments ("""""""" or
          '''''''') are retained.  Implicit null arguments (those resulting
          from _p_a_r_a_m_e_t_e_r_s that have no values) are removed.

        FFFFiiiilllleeee NNNNaaaammmmeeee GGGGeeeennnneeeerrrraaaattttiiiioooonnnn....
          Following substitution, each command _w_o_r_d is scanned for the
          characters ****, ????, and [[[[ unless the ----ffff option has been sssseeeetttt.
          If one of these characters appears then the word is regarded
          as a _p_a_t_t_e_r_n.  The word is replaced with lexicographically
          sorted file names that match the pattern.  If no file name
          is found that matches the pattern, then the word is left
          unchanged.  When a _p_a_t_t_e_r_n is used for file name generation,
          the character .... at the start of a file name or immediately
          following a ////, as well as the character //// itself, must be
          matched explicitly.  In other instances of pattern matching
          the //// and .... are not treated specially.

               ****    Matches any string, including the null string.
               ????    Matches any single character.
               [[[[...]]]]
                    Matches any one of the enclosed characters.  A
                    pair of characters separated by ---- matches any
                    character lexically between the pair, inclusive.
                    If the first character following the opening "[ "
                    is a "! " then any character not enclosed is
                    matched.  A ---- can be included in the character set
                    by putting it as the first or last character.
          A _p_a_t_t_e_r_n-_l_i_s_t is a list of one or more patterns separated
          from each other with a ||||.  Composite patterns can be formed
          with one or more of the following:
               ????((((_p_a_t_t_e_r_n-_l_i_s_t))))
                    Optionally matches any one of the given patterns.
               ****((((_p_a_t_t_e_r_n-_l_i_s_t))))
                    Matches zero or more occurrences of the given
                    patterns.



     Page 11                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               ++++((((_p_a_t_t_e_r_n-_l_i_s_t))))
                    Matches one or more occurrences of the given
                    patterns.
               @@@@((((_p_a_t_t_e_r_n-_l_i_s_t))))
                    Matches exactly one of the given patterns.
               !!!!((((_p_a_t_t_e_r_n-_l_i_s_t))))
                    Matches anything, except one of the given
                    patterns.

        QQQQuuuuoooottttiiiinnnngggg....
          Each of the _m_e_t_a_c_h_a_r_a_c_t_e_r_s listed above (See _D_e_f_i_n_i_t_i_o_n_s
          above) has a special meaning to the shell and causes
          termination of a word unless quoted.  A character may be
          _q_u_o_t_e_d (i.e., made to stand for itself) by preceding it with
          a \\\\.  The pair \\\\nnnneeeewwww----lllliiiinnnneeee is removed.  All characters
          enclosed between a pair of single quote marks (''''''''), are
          quoted.  A single quote cannot appear within single quotes.
          Inside double quote marks (""""""""), parameter and command
          substitution occur and \\\\ quotes the characters \\\\, ````, """", and
          $$$$.  The meaning of $$$$**** and $$$$@@@@ is identical when not quoted or
          when used as a parameter assignment value or as a file name.
          However, when used as a command argument, """"$$$$****"""" is equivalent
          to """"$$$$1111_d$$$$2222_d..."""", where _d is the first character of the IIIIFFFFSSSS
          variable, whereas """"$$$$@@@@"""" is equivalent to """"$$$$1111"""" """"$$$$2222"""" ....
          Inside grave quote marks (````````) \\\\ quotes the characters \\\\, ````,
          and $$$$.  If the grave quotes occur within double quotes then
          \\\\ also quotes the character """".

          The special meaning of reserved words or aliases can be
          removed by quoting any character of the reserved word.  The
          recognition of function names or special command names
          listed below cannot be altered by quoting them.

        AAAArrrriiiitttthhhhmmmmeeeettttiiiicccc EEEEvvvvaaaalllluuuuaaaattttiiiioooonnnn....
          An ability to perform integer arithmetic is provided with
          the special command lllleeeetttt.  Evaluations are performed using
          _l_o_n_g arithmetic.  Constants are of the form [_b_a_s_e####]_n where
          _b_a_s_e is a decimal number between two and thirty-six
          representing the arithmetic base and _n is a number in that
          base.  If _b_a_s_e is omitted then base 10 is used.

          An arithmetic expression uses the same syntax, precedence,
          and associativity of expression of the C language.  All the
          integral operators, other than ++++++++, --------, ????::::, and ,,,, are
          supported.  Variables can be referenced by name within an
          arithmetic expression without using the parameter
          substitution syntax.  When a variable is referenced, its
          value is evaluated as an arithmetic expression.

          An internal integer representation of a _v_a_r_i_a_b_l_e can be
          specified with the ----iiii option of the ttttyyyyppppeeeesssseeeetttt special command.
          Arithmetic evaluation is performed on the value of each



     Page 12                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          assignment to a variable with the ----iiii attribute.  If you do
          not specify an arithmetic base, the first assignment to the
          variable determines the arithmetic base.  This base is used
          when parameter substitution occurs.

          Since many of the arithmetic operators require quoting, an
          alternative form of the lllleeeetttt command is provided.  For any
          command which begins with a ((((((((, all the characters until a
          matching )))))))) are treated as a quoted expression.  More
          precisely, ((((((((...))))))))  is equivalent to lllleeeetttt """"..."""".

        PPPPrrrroooommmmppppttttiiiinnnngggg....
          When used interactively, the shell prompts with the
          parameter expanded value of PPPPSSSS1111 before reading a command.
          If at any time a new-line is typed and further input is
          needed to complete a command, then the secondary prompt
          (i.e., the value of PPPPSSSS2222) is issued.

        CCCCoooonnnnddddiiiittttiiiioooonnnnaaaallll EEEExxxxpppprrrreeeessssssssiiiioooonnnnssss....
          A _c_o_n_d_i_t_i_o_n_a_l _e_x_p_r_e_s_s_i_o_n is used with the [[[[[[[[ compound
          command to test attributes of files and to compare strings.
          Word splitting and file name generation are not performed on
          the words between [[[[[[[[ and ]]]]]]]].  Each expression can be
          constructed from one or more of the following unary or
          binary expressions:
          ----aaaa _f_i_l_e
               True, if _f_i_l_e exists.
          ----bbbb _f_i_l_e
               True, if _f_i_l_e exists and is a block special file.
          ----cccc _f_i_l_e
               True, if _f_i_l_e exists and is a character special file.
          ----dddd _f_i_l_e
               True, if _f_i_l_e exists and is a directory.
          ----ffff _f_i_l_e
               True, if _f_i_l_e exists and is an ordinary file.
          ----gggg _f_i_l_e
               True, if _f_i_l_e exists and is has its setgid bit set.
          ----kkkk _f_i_l_e
               True, if _f_i_l_e exists and is has its sticky bit set.
          ----nnnn _s_t_r_i_n_g
               True, if length of _s_t_r_i_n_g is non-zero.
          ----oooo _o_p_t_i_o_n
               True, if option named _o_p_t_i_o_n is on.
          ----pppp _f_i_l_e
               True, if _f_i_l_e exists and is a fifo special file or a
               pipe.
          ----rrrr _f_i_l_e
               True, if _f_i_l_e exists and is readable by current
               process.
          ----ssss _f_i_l_e
               True, if _f_i_l_e exists and has size greater than zero.
          ----tttt _f_i_l_d_e_s



     Page 13                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               True, if file descriptor number _f_i_l_d_e_s is open and
               associated with a terminal device.
          ----uuuu _f_i_l_e
               True, if _f_i_l_e exists and is has its setuid bit set.
          ----wwww _f_i_l_e
               True, if _f_i_l_e exists and is writable by current
               process.
          ----xxxx _f_i_l_e
               True, if _f_i_l_e exists and is executable by current
               process.  If _f_i_l_e exists and is a directory, then the
               current process has permission to search in the
               directory.
          ----zzzz _s_t_r_i_n_g
               True, if length of _s_t_r_i_n_g is zero.
          ----LLLL _f_i_l_e
               True, if _f_i_l_e exists and is a symbolic link.
          ----OOOO _f_i_l_e
               True, if _f_i_l_e exists and is owned by the effective user
               id of this process.
          ----GGGG _f_i_l_e
               True, if _f_i_l_e exists and its group matches the
               effective group id of this process.
          ----SSSS _f_i_l_e
               True, if _f_i_l_e exists and is a socket.
          _f_i_l_e_1 ----nnnntttt _f_i_l_e_2
               True, if _f_i_l_e_1 exists and is newer than _f_i_l_e_2.
          _f_i_l_e_1 ----ooootttt _f_i_l_e_2
               True, if _f_i_l_e_1 exists and is older than _f_i_l_e_2.
          _f_i_l_e_1 ----eeeeffff _f_i_l_e_2
               True, if _f_i_l_e_1 and _f_i_l_e_2 exist and refer to the same
               file.
          _s_t_r_i_n_g ==== _p_a_t_t_e_r_n
               True, if _s_t_r_i_n_g matches _p_a_t_t_e_r_n.
          _s_t_r_i_n_g !!!!==== _p_a_t_t_e_r_n
               True, if _s_t_r_i_n_g does not match _p_a_t_t_e_r_n.
          _s_t_r_i_n_g_1 <<<< _s_t_r_i_n_g_2
               True, if _s_t_r_i_n_g_1 comes before _s_t_r_i_n_g_2 based on ASCII
               value of their characters.
          _s_t_r_i_n_g_1 >>>> _s_t_r_i_n_g_2
               True, if _s_t_r_i_n_g_1 comes after _s_t_r_i_n_g_2 based on ASCII
               value of their characters.
          _e_x_p_1 ----eeeeqqqq _e_x_p_2
               True, if _e_x_p_1 is equal to _e_x_p_2.
          _e_x_p_1 ----nnnneeee _e_x_p_2
               True, if _e_x_p_1 is not equal to _e_x_p_2.
          _e_x_p_1 ----lllltttt _e_x_p_2
               True, if _e_x_p_1 is less than _e_x_p_2.
          _e_x_p_1 ----ggggtttt _e_x_p_2
               True, if _e_x_p_1 is greater than _e_x_p_2.
          _e_x_p_1 ----lllleeee _e_x_p_2
               True, if _e_x_p_1 is less than or equal to _e_x_p_2.
          _e_x_p_1 ----ggggeeee _e_x_p_2



     Page 14                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               True, if _e_x_p_1 is greater than or equal to _e_x_p_2.

          In each of the above expressions, if _f_i_l_e is of the form
          ////ddddeeeevvvv////ffffdddd////_n, where _n is an integer, then the test is applied
          to the open file whose descriptor number is _n.

          A compound expression can be constructed from these
          primitives by using any of the following, listed in
          decreasing order of precedence.
          ((((_e_x_p_r_e_s_s_i_o_n))))
               True, if _e_x_p_r_e_s_s_i_o_n is true.  Used to group
               expressions.
          !!!! _e_x_p_r_e_s_s_i_o_n
               True if _e_x_p_r_e_s_s_i_o_n is false.
          _e_x_p_r_e_s_s_i_o_n_1 &&&&&&&& _e_x_p_r_e_s_s_i_o_n_2
               True, if _e_x_p_r_e_s_s_i_o_n_1 and _e_x_p_r_e_s_s_i_o_n_2 are both true.
          _e_x_p_r_e_s_s_i_o_n_1 |||||||| _e_x_p_r_e_s_s_i_o_n_2
               True, if either _e_x_p_r_e_s_s_i_o_n_1 or _e_x_p_r_e_s_s_i_o_n_2 is true.

        IIIInnnnppppuuuutttt////OOOOuuuuttttppppuuuutttt....
          Before a command is executed, its input and output may be
          redirected using a special notation interpreted by the
          shell.  The following may appear anywhere in a simple-
          command or may precede or follow a _c_o_m_m_a_n_d and are _n_o_t
          passed on to the invoked command.  Command and parameter
          substitution occur before _w_o_r_d or _d_i_g_i_t is used except as
          noted below.  File name generation occurs only if the
          pattern matches a single file, and blank interpretation is
          not performed.

          <<<<_w_o_r_d         Use file _w_o_r_d as standard input (file
                        descriptor 0).

          >>>>_w_o_r_d         Use file _w_o_r_d as standard output (file
                        descriptor 1).  If the file does not exist
                        then it is created.  If the file exists, and
                        the nnnnoooocccclllloooobbbbbbbbeeeerrrr option is on, this causes an
                        error; otherwise, it is truncated to zero
                        length.

          >>>>||||_w_o_r_d        Sames as >>>>, except that it overrides the
                        nnnnoooocccclllloooobbbbbbbbeeeerrrr option.

          >>>>>>>>_w_o_r_d        Use file _w_o_r_d as standard output.  If the file
                        exists then output is appended to it (by first
                        seeking to the end-of-file); otherwise, the
                        file is created.

          <<<<>>>>_w_o_r_d        Open file _w_o_r_d for reading and writing as
                        standard input.

          <<<<<<<<[----]_w_o_r_d     The shell input is read up to a line that is



     Page 15                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



                        the same as _w_o_r_d, or to an end-of-file.  No
                        parameter substitution, command substitution
                        or file name generation is performed on _w_o_r_d.
                        The resulting document, called a _h_e_r_e-
                        _d_o_c_u_m_e_n_t, becomes the standard input.  If any
                        character of _w_o_r_d is quoted, then no
                        interpretation is placed upon the characters
                        of the document; otherwise, parameter and
                        command substitution occur, \\\\nnnneeeewwww----lllliiiinnnneeee is
                        ignored, and \\\\ must be used to quote the
                        characters \\\\, $$$$, ````, and the first character of
                        _w_o_r_d.  If ---- is appended to <<<<<<<<, then all
                        leading tabs are stripped from _w_o_r_d and from
                        the document.

          <<<<&&&&_d_i_g_i_t       The standard input is duplicated from file
                        descriptor _d_i_g_i_t (see _d_u_p(2)).  Similarly for
                        the standard output using >>>>&&&& _d_i_g_i_t.

          <<<<&&&&----           The standard input is closed.  Similarly for
                        the standard output using >>>>&&&&----.

          <<<<&&&&pppp           The input from the co-process is moved to
                        standard input.

          >>>>&&&&pppp           The output to the co-process is moved to
                        standard output.

          If one of the above is preceded by a digit, then the file
          descriptor number referred to is that specified by the digit
          (instead of the default 0 or 1).  For example:

               ... 2>&1

          means file descriptor 2 is to be opened for writing as a
          duplicate of file descriptor 1.

          The order in which redirections are specified is
          significant.  The shell evaluates each redirection in terms
          of the (_f_i_l_e _d_e_s_c_r_i_p_t_o_r, _f_i_l_e) association at the time of
          evaluation.  For example:

               ... 1>_f_n_a_m_e 2>&1

          first associates file descriptor 1 with file _f_n_a_m_e.  It then
          associates file descriptor 2 with the file associated with
          file descriptor 1 (i.e.  _f_n_a_m_e).  If the order of
          redirections were reversed, file descriptor 2 would be
          associated with the terminal (assuming file descriptor 1 had
          been) and then file descriptor 1 would be associated with
          file _f_n_a_m_e.




     Page 16                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          If a command is followed by &&&& and job control is not active,
          then the default standard input for the command is the empty
          file ////ddddeeeevvvv////nnnnuuuullllllll.  Otherwise, the environment for the
          execution of a command contains the file descriptors of the
          invoking shell as modified by input/output specifications.

        EEEEnnnnvvvviiiirrrroooonnnnmmmmeeeennnntttt....
          The _e_n_v_i_r_o_n_m_e_n_t (see _e_n_v_i_r_o_n(7)) is a list of name-value
          pairs that is passed to an executed program in the same way
          as a normal argument list.  The names must be _i_d_e_n_t_i_f_i_e_r_s
          and the values are character strings.  The shell interacts
          with the environment in several ways.  On invocation, the
          shell scans the environment and creates a variable for each
          name found, giving it the corresponding value and marking it
          _e_x_p_o_r_t.  Executed commands inherit the environment.  If the
          user modifies the values of these variables or creates new
          ones, using the eeeexxxxppppoooorrrrtttt or ttttyyyyppppeeeesssseeeetttt ----xxxx commands they become
          part of the environment.  The environment seen by any
          executed command is thus composed of any name-value pairs
          originally inherited by the shell, whose values may be
          modified by the current shell, plus any additions which must
          be noted in eeeexxxxppppoooorrrrtttt or ttttyyyyppppeeeesssseeeetttt ----xxxx commands.

          The environment for any _s_i_m_p_l_e-_c_o_m_m_a_n_d or function may be
          augmented by prefixing it with one or more variable
          assignments.  A variable assignment argument is a word of
          the form _i_d_e_n_t_i_f_i_e_r=_v_a_l_u_e.  Thus:

               TERM=450 cmd args                  and
               (export TERM; TERM=450; cmd args)

          are equivalent (as far as the above execution of _c_m_d is
          concerned except for special commands listed below that are
          preceded with a dagger).

          If the ----kkkk flag is set, _a_l_l variable assignment arguments are
          placed in the environment, even if they occur after the
          command name.  The following first prints aaaa====bbbb cccc and then cccc:

               echo a=b c
               set -k
               echo a=b c
          This feature is intended for use with scripts written for
          early versions of the shell and its use in new scripts is
          strongly discouraged.  It is likely to disappear someday.

        FFFFuuuunnnnccccttttiiiioooonnnnssss....
          The ffffuuuunnnnccccttttiiiioooonnnn reserved word, described in the _C_o_m_m_a_n_d_s
          section above, is used to define shell functions.  Shell
          functions are read in and stored internally.  Alias names
          are resolved when the function is read.  Functions are
          executed like commands with the arguments passed as



     Page 17                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          positional parameters.  (See _E_x_e_c_u_t_i_o_n below.)

          Functions execute in the same process as the caller and
          share all files and present working directory with the
          caller.  Traps caught by the caller are reset to their
          default action inside the function.  A trap condition that
          is not caught or ignored by the function causes the function
          to terminate and the condition to be passed on to the
          caller.  A trap on EEEEXXXXIIIITTTT set inside a function is executed
          after the function completes in the environment of the
          caller.  Ordinarily, variables are shared between the
          calling program and the function.  However, the ttttyyyyppppeeeesssseeeetttt
          special command used within a function defines local
          variables whose scope includes the current function and all
          functions it calls.

          The special command rrrreeeettttuuuurrrrnnnn is used to return from function
          calls.  Errors within functions return control to the
          caller.

          Function identifiers can be listed with the ----ffff or ++++ffff option
          of the ttttyyyyppppeeeesssseeeetttt special command.  The text of functions will
          also be listed with ----ffff.  Functions can be undefined with the
          ----ffff option of the uuuunnnnsssseeeetttt special command.

          Ordinarily, functions are unset when the shell executes a
          shell script.  The ----xxxxffff option of the ttttyyyyppppeeeesssseeeetttt command allows
          a function to be exported to scripts that are executed
          without a separate invocation of the shell.  Functions that
          need to be defined across separate invocations of the shell
          should be specified in the EEEENNNNVVVV file with the ----xxxxffff option of
          ttttyyyyppppeeeesssseeeetttt.

        JJJJoooobbbbssss....
          If the mmmmoooonnnniiiittttoooorrrr option of the sssseeeetttt command is turned on, an
          interactive shell associates a _j_o_b with each pipeline.  It
          keeps a table of current jobs, printed by the jjjjoooobbbbssss command,
          and assigns them small integer numbers.  When a job is
          started asynchronously with &&&&, the shell prints a line which
          looks like:

               [1] 1234

          indicating that the job which was started asynchronously was
          job number 1 and had one (top-level) process, whose process
          id was 1234.

          This paragraph and the next require features that are not in
          all versions of UNIX and may not apply.  If you are running
          a job and wish to do something else you may hit the key ^^^^ZZZZ
          (control-Z) which sends a STOP signal to the current job.
          The shell will then normally indicate that the job has been



     Page 18                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          `Stopped', and print another prompt.  You can then
          manipulate the state of this job, putting it in the
          background with the bbbbgggg command, or run some other commands
          and then eventually bring the job back into the foreground
          with the foreground command ffffgggg.  A ^^^^ZZZZ takes effect
          immediately and is like an interrupt in that pending output
          and unread input are discarded when it is typed.

          A job being run in the background will stop if it tries to
          read from the terminal.  Background jobs are normally
          allowed to produce output, but this can be disabled by
          giving the command ``stty tostop''.  If you set this tty
          option, then background jobs will stop when they try to
          produce output like they do when they try to read input.

          There are several ways to refer to jobs in the shell.  A job
          can be referred to by the process id of any process of the
          job or by one of the following:
          %%%%_n_u_m_b_e_r
               The job with the given number.
          %%%%_s_t_r_i_n_g
               Any job whose command line begins with _s_t_r_i_n_g.
          %%%%????_s_t_r_i_n_g
               Any job whose command line contains _s_t_r_i_n_g.
          %%%%%%%%   Current job.
          %%%%++++   Equivalent to %%%%%%%%.
          %%%%----   Previous job.

          The shell learns immediately whenever a process changes
          state.  It normally informs you whenever a job becomes
          blocked so that no further progress is possible, but only
          just before it prints a prompt.  This is done so that it
          does not otherwise disturb your work.

          When the monitor mode is on, each background job that
          completes triggers any trap set for CCCCHHHHLLLLDDDD.

          When you try to leave the shell while jobs are running or
          stopped, you will be warned that `You have stopped(running)
          jobs.'  You may use the jjjjoooobbbbssss command to see what they are.
          If you do this or immediately try to exit again, the shell
          will not warn you a second time, and the stopped jobs will
          be terminated.

        SSSSiiiiggggnnnnaaaallllssss....
          The INT and QUIT signals for an invoked command are ignored
          if the command is followed by &&&& and the mmmmoooonnnniiiittttoooorrrr option is
          not active.  Otherwise, signals have the values inherited by
          the shell from its parent (but see also the ttttrrrraaaapppp special
          command below).

        EEEExxxxeeeeccccuuuuttttiiiioooonnnn....



     PPPPaaaaggggeeee 11119999                                         ((((pppprrrriiiinnnntttteeeedddd 7777////22225555////88889999))))






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          Each time a command is executed, the above substitutions are
          carried out.  If the command name matches one of the _S_p_e_c_i_a_l
          _C_o_m_m_a_n_d_s listed below, it is executed within the current
          shell process.  Next, the command name is checked to see if
          it matches one of the user defined functions.  If it does,
          the positional parameters are saved and then reset to the
          arguments of the _f_u_n_c_t_i_o_n call.  When the _f_u_n_c_t_i_o_n completes
          or issues a rrrreeeettttuuuurrrrnnnn, the positional parameter list is
          restored and any trap set on EEEEXXXXIIIITTTT within the function is
          executed.  The value of a _f_u_n_c_t_i_o_n is the value of the last
          command executed.  A function is also executed in the
          current shell process.  If a command name is not a _s_p_e_c_i_a_l
          _c_o_m_m_a_n_d or a user defined _f_u_n_c_t_i_o_n, a process is created and
          an attempt is made to execute the command via _e_x_e_c(2).

          The shell variable PPPPAAAATTTTHHHH defines the search path for the
          directory containing the command.  Alternative directory
          names are separated by a colon (::::).  The default path is
          ////bbbbiiiinnnn::::////uuuussssrrrr////bbbbiiiinnnn:::: (specifying ////bbbbiiiinnnn, ////uuuussssrrrr////bbbbiiiinnnn, and the current
          directory in that order).  The current directory can be
          specified by two or more adjacent colons, or by a colon at
          the beginning or end of the path list.  If the command name
          contains a //// then the search path is not used.  Otherwise,
          each directory in the path is searched for an executable
          file.  If the file has execute permission but is not a
          directory or an aaaa....oooouuuutttt file, it is assumed to be a file
          containing shell commands.  A sub-shell is spawned to read
          it.  All non-exported aliases, functions, and variables are
          removed in this case.  If the shell command file doesn't
          have read permission, or if the _s_e_t_u_i_d and/or _s_e_t_g_i_d bits
          are set on the file, then the shell executes an agent whose
          job it is to set up the permissions and execute the shell
          with the shell command file passed down as an open file.  A
          parenthesized command is executed in a sub-shell without
          removing non-exported quantities.

        CCCCoooommmmmmmmaaaannnndddd RRRReeee----eeeennnnttttrrrryyyy....
          The text of the last HHHHIIIISSSSTTTTSSSSIIIIZZZZEEEE (default 128) commands entered
          from a terminal device is saved in a _h_i_s_t_o_r_y file.  The file
          $$$$HHHHOOOOMMMMEEEE////....sssshhhh____hhhhiiiissssttttoooorrrryyyy is used if the HHHHIIIISSSSTTTTFFFFIIIILLLLEEEE variable is not
          set or if the file it names is not writable.  A shell can
          access the commands of all _i_n_t_e_r_a_c_t_i_v_e shells which use the
          same named HHHHIIIISSSSTTTTFFFFIIIILLLLEEEE.  The special command ffffcccc is used to list
          or edit a portion of this file.  The portion of the file to
          be edited or listed can be selected by number or by giving
          the first character or characters of the command.  A single
          command or range of commands can be specified.  If you do
          not specify an editor program as an argument to ffffcccc then the
          value of the variable FFFFCCCCEEEEDDDDIIIITTTT is used.  If FFFFCCCCEEEEDDDDIIIITTTT is not
          defined then ////bbbbiiiinnnn////eeeedddd is used.  The edited command(s) is
          printed and re-executed upon leaving the editor.  The editor
          name ---- is used to skip the editing phase and to re-execute



     Page 20                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          the command.  In this case a substitution parameter of the
          form _o_l_d====_n_e_w can be used to modify the command before
          execution.  For example, if rrrr is aliased to ''''ffffcccc ----eeee ----'''' then
          typing `rrrr bbbbaaaadddd====ggggoooooooodddd cccc' will re-execute the most recent
          command which starts with the letter cccc, replacing the first
          occurrence of the string bbbbaaaadddd with the string ggggoooooooodddd.

        IIIInnnn----lllliiiinnnneeee EEEEddddiiiittttiiiinnnngggg OOOOppppttttiiiioooonnnnssss
          Normally, each command line entered from a terminal device
          is simply typed followed by a new-line (`RETURN' or
          `LINE FEED').  If either the eeeemmmmaaaaccccssss, ggggmmmmaaaaccccssss, or vvvviiii option is
          active, the user can edit the command line.  To be in either
          of these edit modes sssseeeetttt the corresponding option.  An
          editing option is automatically selected each time the
          VVVVIIIISSSSUUUUAAAALLLL or EEEEDDDDIIIITTTTOOOORRRR variable is assigned a value ending in
          either of these option names.

          The editing features require that the user's terminal accept
          `RETURN' as carriage return without line feed and that a
          space (` ') must overwrite the current character on the
          screen.  ADM terminal users should set the "space - advance"
          switch to `space'.  Hewlett-Packard series 2621 terminal
          users should set the straps to `bcGHxZ etX'.

          The editing modes implement a concept where the user is
          looking through a window at the current line.  The window
          width is the value of CCCCOOOOLLLLUUUUMMMMNNNNSSSS if it is defined, otherwise
          80.  If the line is longer than the window width minus two,
          a mark is displayed at the end of the window to notify the
          user.  As the cursor moves and reaches the window boundaries
          the window will be centered about the cursor.  The mark is a
          >>>> (<,,,, ****) if the line extends on the right (left, both)
          side(s) of the window.

          The search commands in each edit mode provide access to the
          history file.  Only strings are matched, not patterns,
          although a leading ^^^^ in the string restricts the match to
          begin at the first character in the line.

        EEEEmmmmaaaaccccssss EEEEddddiiiittttiiiinnnngggg MMMMooooddddeeee
          This mode is entered by enabling either the _e_m_a_c_s or _g_m_a_c_s
          option.  The only difference between these two modes is the
          way they handle ^^^^TTTT.  To edit, the user moves the cursor to
          the point needing correction and then inserts or deletes
          characters or words as needed.  All the editing commands are
          control characters or escape sequences.  The notation for
          control characters is caret ( ^^^^ ) followed by the character.
          For example, ^^^^FFFF is the notation for control FFFF.  This is
          entered by depressing `f' while holding down the `CTRL'
          (control) key.  The `SHIFT' key is _n_o_t depressed.  (The
          notation ^^^^???? indicates the DEL (delete) key.)




     Page 21                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          The notation for escape sequences is MMMM---- followed by a
          character.  For example, MMMM----ffff (pronounced Meta f) is entered
          by depressing ESC (ascii 000033333333) followed by `f'.  (MMMM----FFFF would
          be the notation for ESC followed by `SHIFT' (capital) `F'.)

          All edit commands operate from any place on the line (not
          just at the beginning).  Neither the "RETURN" nor the "LINE
          FEED" key is entered after edit commands except when noted.

          ^^^^FFFF        Move cursor forward (right) one character.
          MMMM----ffff       Move cursor forward one word.  (The emacs editor's
                    idea of a word is a string of characters
                    consisting of only letters, digits and
                    underscores.)
          ^^^^BBBB        Move cursor backward (left) one character.
          MMMM----bbbb       Move cursor backward one word.
          ^^^^AAAA        Move cursor to start of line.
          ^^^^EEEE        Move cursor to end of line.
          ^^^^]]]]_c_h_a_r    Move cursor forward to character _c_h_a_r on current
                    line.
          MMMM----^^^^]]]]_c_h_a_r  Move cursor backward to character _c_h_a_r on current
                    line.
          ^^^^XXXX^^^^XXXX      Interchange the cursor and mark.
          _e_r_a_s_e     (User defined erase character as defined by the
                    _s_t_t_y(1) command, usually ^^^^HHHH or ####.)  Delete
                    previous character.
          ^^^^DDDD        Delete current character.
          MMMM----dddd       Delete current word.
          MMMM----^^^^HHHH      (Meta-backspace) Delete previous word.
          MMMM----hhhh       Delete previous word.
          MMMM----^^^^????      (Meta-DEL) Delete previous word (if your interrupt
                    character is ^^^^???? (DEL, the default) then this
                    command will not work).
          ^^^^TTTT        Transpose current character with next character in
                    _e_m_a_c_s mode.  Transpose two previous characters in
                    _g_m_a_c_s mode.
          ^^^^CCCC        Capitalize current character.
          MMMM----cccc       Capitalize current word.
          MMMM----llll       Change the current word to lower case.
          ^^^^KKKK        Delete from the cursor to the end of the line.  If
                    preceded by a numerical parameter whose value is
                    less than the current cursor position, then delete
                    from given position up to the cursor.  If preceded
                    by a numerical parameter whose value is greater
                    than the current cursor position, then delete from
                    cursor up to given cursor position.
          ^^^^WWWW        Kill from the cursor to the mark.
          MMMM----pppp       Push the region from the cursor to the mark on the
                    stack.
          _k_i_l_l      (User defined kill character as defined by the
                    stty command, usually ^^^^GGGG or @@@@.)  Kill the entire
                    current line.  If two _k_i_l_l characters are entered



     Page 22                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



                    in succession, all kill characters from then on
                    cause a line feed (useful when using paper
                    terminals).
          ^^^^YYYY        Restore last item removed from line. (Yank item
                    back to the line.)
          ^^^^LLLL        Line feed and print current line.
          ^^^^@@@@        (Null character) Set mark.
          MMMM----_s_p_a_c_e   (Meta space) Set mark.
          ^^^^JJJJ        (New line) Execute the current line.
          ^^^^MMMM        (Return) Execute the current line.
          _e_o_f       End-of-file character, normally ^^^^DDDD, is processed
                    as an End-of-file only if the current line is
                    null.
          ^^^^PPPP        Fetch previous command.  Each time ^^^^PPPP is entered
                    the previous command back in time is accessed.
                    Moves back one line when not on the first line of
                    a multi-line command.
          MMMM----<<<<       Fetch the least recent (oldest) history line.
          MMMM---->>>>       Fetch the most recent (youngest) history line.
          ^^^^NNNN        Fetch next command line.  Each time ^^^^NNNN is entered
                    the next command line forward in time is accessed.
          ^^^^RRRR_s_t_r_i_n_g  Reverse search history for a previous command line
                    containing _s_t_r_i_n_g.  If a parameter of zero is
                    given, the search is forward.  _S_t_r_i_n_g is
                    terminated by a "RETURN" or "NEW LINE".  If string
                    is preceded by a ^^^^, the matched line must begin
                    with _s_t_r_i_n_g.  If _s_t_r_i_n_g is omitted, then the next
                    command line containing the most recent _s_t_r_i_n_g is
                    accessed.  In this case a parameter of zero
                    reverses the direction of the search.
          ^^^^OOOO        Operate - Execute the current line and fetch the
                    next line relative to current line from the
                    history file.
          MMMM----_d_i_g_i_t_s  (Escape) Define numeric parameter, the digits are
                    taken as a parameter to the next command.  The
                    commands that accept a parameter are ^^^^FFFF, ^^^^BBBB,
                    _e_r_a_s_e, ^^^^CCCC, ^^^^DDDD, ^^^^KKKK, ^^^^RRRR, ^^^^PPPP, ^^^^NNNN, ^^^^]]]], MMMM----...., MMMM----^^^^]]]], MMMM----____,
                    MMMM----bbbb, MMMM----cccc, MMMM----dddd, MMMM----ffff, MMMM----hhhh MMMM----llll and MMMM----^^^^HHHH.
          MMMM----_l_e_t_t_e_r  Soft-key - Your alias list is searched for an
                    alias by the name _____l_e_t_t_e_r and if an alias of this
                    name is defined, its value will be inserted on the
                    input queue.  The _l_e_t_t_e_r must not be one of the
                    above meta-functions.
          MMMM----]]]]_l_e_t_t_e_r Soft-key - Your alias list is searched for an
                    alias by the name _________l_e_t_t_e_r and if an alias of this
                    name is defined, its value will be inserted on the
                    input queue.  The can be used to program functions
                    keys on many terminals.
          MMMM----....       The last word of the previous command is inserted
                    on the line.  If preceded by a numeric parameter,
                    the value of this parameter determines which word
                    to insert rather than the last word.



     Page 23                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          MMMM----____       Same as MMMM----.....
          MMMM----****       Attempt file name generation on the current word.
                    An asterisk is appended if the word doesn't match
                    any file or contain any special pattern
                    characters.
          MMMM----EEEESSSSCCCC     File name completion.  Replaces the current word
                    with the longest common prefix of all filenames
                    matching the current word with an asterisk
                    appended.  If the match is unique, a //// is appended
                    if the file is a directory and a space is appended
                    if the file is not a directory.
          MMMM----====       List files matching current word pattern if an
                    asterisk were appended.
          ^^^^UUUU        Multiply parameter of next command by 4.
          \\\\         Escape next character.  Editing characters, the
                    user's erase, kill and interrupt (normally ^^^^????)
                    characters may be entered in a command line or in
                    a search string if preceded by a \\\\.  The \\\\ removes
                    the next character's editing features (if any).
          ^^^^VVVV        Display version of the shell.
          MMMM----####       Insert a #### at the beginning of the line and
                    execute it.  This causes a comment to be inserted
                    in the history file.

        VVVViiii EEEEddddiiiittttiiiinnnngggg MMMMooooddddeeee
          There are two typing modes.  Initially, when you enter a
          command you are in the _i_n_p_u_t mode.  To edit, the user enters
          _c_o_n_t_r_o_l mode by typing ESC (000033333333) and moves the cursor to the
          point needing correction and then inserts or deletes
          characters or words as needed.  Most control commands accept
          an optional repeat _c_o_u_n_t prior to the command.
          When in vi mode on most systems, canonical processing is
          initially enabled and the command will be echoed again if
          the speed is 1200 baud or greater and it contains any
          control characters or less than one second has elapsed since
          the prompt was printed.  The ESC character terminates
          canonical processing for the remainder of the command and
          the user can then modify the command line.  This scheme has
          the advantages of canonical processing with the type-ahead
          echoing of raw mode.
          If the option vvvviiiirrrraaaawwww is also set, the terminal will always
          have canonical processing disabled.  This mode is implicit
          for systems that do not support two alternate end of line
          delimiters, and may be helpful for certain terminals.

             IIIInnnnppppuuuutttt EEEEddddiiiitttt CCCCoooommmmmmmmaaaannnnddddssss
               By default the editor is in input mode.
               _e_r_a_s_e     (User defined erase character as defined by
                         the stty command, usually ^^^^HHHH or ####.)  Delete
                         previous character.
               ^^^^WWWW        Delete the previous blank separated word.
               ^^^^DDDD        Terminate the shell.



     Page 24                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               ^^^^VVVV        Escape next character.  Editing characters
                         and the user's erase or kill characters may
                         be entered in a command line or in a search
                         string if preceded by a ^^^^VVVV.  The ^^^^VVVV removes
                         the next character's editing features (if
                         any).
               \\\\         Escape the next _e_r_a_s_e or _k_i_l_l character.
             MMMMoooottttiiiioooonnnn EEEEddddiiiitttt CCCCoooommmmmmmmaaaannnnddddssss
               These commands will move the cursor.
               [_c_o_u_n_t]llll  Cursor forward (right) one character.
               [_c_o_u_n_t]wwww  Cursor forward one alpha-numeric word.
               [_c_o_u_n_t]WWWW  Cursor to the beginning of the next word that
                         follows a blank.
               [_c_o_u_n_t]eeee  Cursor to end of word.
               [_c_o_u_n_t]EEEE  Cursor to end of the current blank delimited
                         word.
               [_c_o_u_n_t]hhhh  Cursor backward (left) one character.
               [_c_o_u_n_t]bbbb  Cursor backward one word.
               [_c_o_u_n_t]BBBB  Cursor to preceding blank separated word.
               [_c_o_u_n_t]||||  Cursor to column _c_o_u_n_t.
               [_c_o_u_n_t]ffff_c Find the next character _c in the current
                         line.
               [_c_o_u_n_t]FFFF_c Find the previous character _c in the current
                         line.
               [_c_o_u_n_t]tttt_c Equivalent to ffff followed by hhhh.
               [_c_o_u_n_t]TTTT_c Equivalent to FFFF followed by llll.
               [_c_o_u_n_t];;;;  Repeats _c_o_u_n_t times, the last single
                         character find command, ffff, FFFF, tttt, or TTTT.
               [_c_o_u_n_t],,,,  Reverses the last single character find
                         command _c_o_u_n_t times.
               0000         Cursor to start of line.
               ^^^^         Cursor to first non-blank character in line.
               $$$$         Cursor to end of line.
             SSSSeeeeaaaarrrrcccchhhh EEEEddddiiiitttt CCCCoooommmmmmmmaaaannnnddddssss
               These commands access your command history.
               [_c_o_u_n_t]kkkk  Fetch previous command.  Each time kkkk is
                         entered the previous command back in time is
                         accessed.
               [_c_o_u_n_t]----  Equivalent to kkkk.
               [_c_o_u_n_t]jjjj  Fetch next command.  Each time jjjj is entered
                         the next command forward in time is accessed.
               [_c_o_u_n_t]++++  Equivalent to jjjj.
               [_c_o_u_n_t]GGGG  The command number _c_o_u_n_t is fetched.  The
                         default is the least recent history command.
               ////_s_t_r_i_n_g   Search backward through history for a
                         previous command containing _s_t_r_i_n_g.  _S_t_r_i_n_g
                         is terminated by a "RETURN" or "NEW LINE".
                         If string is preceded by a ^^^^, the matched
                         line must begin with _s_t_r_i_n_g.  If _s_t_r_i_n_g is
                         null the previous string will be used.
               ????_s_t_r_i_n_g   Same as //// except that search will be in the
                         forward direction.



     Page 25                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               nnnn         Search for next match of the last pattern to
                         //// or ???? commands.
               NNNN         Search for next match of the last pattern to
                         //// or ????, but in reverse direction.  Search
                         history for the _s_t_r_i_n_g entered by the
                         previous //// command.
             TTTTeeeexxxxtttt MMMMooooddddiiiiffffiiiiccccaaaattttiiiioooonnnn EEEEddddiiiitttt CCCCoooommmmmmmmaaaannnnddddssss
               These commands will modify the line.
               aaaa         Enter input mode and enter text after the
                         current character.
               AAAA         Append text to the end of the line.
                         Equivalent to $$$$aaaa.
               [_c_o_u_n_t]cccc_m_o_t_i_o_n
               cccc[_c_o_u_n_t]_m_o_t_i_o_n
                         Delete current character through the
                         character that _m_o_t_i_o_n would move the cursor
                         to and enter input mode.  If _m_o_t_i_o_n is cccc, the
                         entire line will be deleted and input mode
                         entered.
               CCCC         Delete the current character through the end
                         of line and enter input mode.  Equivalent to
                         cccc$$$$.
               SSSS         Equivalent to cccccccc.
               DDDD         Delete the current character through the end
                         of line.  Equivalent to dddd$$$$.
               [_c_o_u_n_t]dddd_m_o_t_i_o_n
               dddd[_c_o_u_n_t]_m_o_t_i_o_n
                         Delete current character through the
                         character that _m_o_t_i_o_n would move to.  If
                         _m_o_t_i_o_n is dddd ,,,, the entire line will be
                         deleted.
               iiii         Enter input mode and insert text before the
                         current character.
               IIII         Insert text before the beginning of the line.
                         Equivalent to 0000iiii.
               [_c_o_u_n_t]PPPP  Place the previous text modification before
                         the cursor.
               [_c_o_u_n_t]pppp  Place the previous text modification after
                         the cursor.
               RRRR         Enter input mode and replace characters on
                         the screen with characters you type overlay
                         fashion.
               [_c_o_u_n_t]rrrr_c Replace the _c_o_u_n_t character(s) starting at
                         the current cursor position with _c, and
                         advance the cursor.
               [_c_o_u_n_t]xxxx  Delete current character.
               [_c_o_u_n_t]XXXX  Delete preceding character.
               [_c_o_u_n_t]....  Repeat the previous text modification
                         command.
               [_c_o_u_n_t]9~~~~8  Invert the case of the _c_o_u_n_t character(s)
                         starting at the current cursor position and
                         advance the cursor.



     Page 26                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               [_c_o_u_n_t]____  Causes the _c_o_u_n_t word of the previous command
                         to be appended and input mode entered.  The
                         last word is used if _c_o_u_n_t is omitted.
               ****         Causes an **** to be appended to the current
                         word and file name generation attempted.  If
                         no match is found, it rings the bell.
                         Otherwise, the word is replaced by the
                         matching pattern and input mode is entered.
               \\\\         Filename completion.  Replaces the current
                         word with the longest common prefix of all
                         filenames matching the current word with an
                         asterisk appended.  If the match is unique, a
                         //// is appended if the file is a directory and
                         a space is appended if the file is not a
                         directory.
             OOOOtttthhhheeeerrrr EEEEddddiiiitttt CCCCoooommmmmmmmaaaannnnddddssss
               Miscellaneous commands.
               [_c_o_u_n_t]yyyy_m_o_t_i_o_n
               yyyy[_c_o_u_n_t]_m_o_t_i_o_n
                         Yank current character through character that
                         _m_o_t_i_o_n would move the cursor to and puts them
                         into the delete buffer.  The text and cursor
                         are unchanged.
               YYYY         Yanks from current position to end of line.
                         Equivalent to yyyy$$$$.
               uuuu         Undo the last text modifying command.
               UUUU         Undo all the text modifying commands
                         performed on the line.
               [_c_o_u_n_t]vvvv  Returns the command ffffcccc ----eeee
                         $$$${{{{VVVVIIIISSSSUUUUAAAALLLL::::----$$$${{{{EEEEDDDDIIIITTTTOOOORRRR::::----vvvviiii}}}}}}}} _c_o_u_n_t in the input
                         buffer.  If _c_o_u_n_t is omitted, then the
                         current line is used.
               ^^^^LLLL        Line feed and print current line.  Has effect
                         only in control mode.
               ^^^^JJJJ        (New line) Execute the current line,
                         regardless of mode.
               ^^^^MMMM        (Return) Execute the current line, regardless
                         of mode.
               ####         Sends the line after inserting a #### in front
                         of the line.  Useful for causing the current
                         line to be inserted in the history without
                         being executed.
               ====         List the file names that match the current
                         word if an asterisk were appended it.
               @@@@_l_e_t_t_e_r   Your alias list is searched for an alias by
                         the name _____l_e_t_t_e_r and if an alias of this name
                         is defined, its value will be inserted on the
                         input queue for processing.

        SSSSppppeeeecccciiiiaaaallll CCCCoooommmmmmmmaaaannnnddddssss....
          The following simple-commands are executed in the shell
          process.  Input/Output redirection is permitted.  Unless



     Page 27                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          otherwise indicated, the output is written on file
          descriptor 1 and the exit status, when there is no syntax
          error, is zero.  Commands that are preceded by one or two |-
          are treated specially in the following ways:
          1.   Variable assignment lists preceding the command remain
               in effect when the command completes.
          2.   I/O redirections are processed after variable
               assignments.
          3.   Errors cause a script that contains them to abort.
          4.   Words, following a command preceded by |-|- that are in
               the format of a variable assignment, are expanded with
               the same rules as a variable assignment.  This means
               that tilde substitution is performed after the ==== sign
               and word splitting and file name generation are not
               performed.

          |- :::: [ _a_r_g ... ]
               The command only expands parameters.

          |- .... _f_i_l_e [[[[ _a_r_g ............ ]]]]
               Read the complete _f_i_l_e then execute the commands.  The
               commands are executed in the current Shell environment.
               The search path specified by PPPPAAAATTTTHHHH is used to find the
               directory containing _f_i_l_e.  If any arguments _a_r_g are
               given, they become the positional parameters.
               Otherwise the positional parameters are unchanged.  The
               exit status is the exit status of the last command
               executed.

          |-|- aaaalllliiiiaaaassss [ ----ttttxxxx ]  [ _n_a_m_e[ ====_v_a_l_u_e  ] ] ...
               aaaalllliiiiaaaassss with no arguments prints the list of aliases in
               the form _n_a_m_e=_v_a_l_u_e on standard output.  An _a_l_i_a_s is
               defined for each name whose _v_a_l_u_e is given.  A trailing
               space in _v_a_l_u_e causes the next word to be checked for
               alias substitution.  The ----tttt flag is used to set and
               list tracked aliases.  The value of a tracked alias is
               the full pathname corresponding to the given _n_a_m_e.  The
               value becomes undefined when the value of PPPPAAAATTTTHHHH is reset
               but the aliases remained tracked.  Without the ----tttt flag,
               for each _n_a_m_e in the argument list for which no _v_a_l_u_e
               is given, the name and value of the alias is printed.
               The ----xxxx flag is used to set or print exported aliases.
               An exported alias is defined for scripts invoked by
               name.  The exit status is non-zero if a _n_a_m_e is given,
               but no value, and no alias has been defined for the
               _n_a_m_e.

          bbbbgggg [ _j_o_b... ]
               This command is only on systems that support job
               control.  Puts each specified _j_o_b into the background.
               The current job is put in the background if _j_o_b is not
               specified.  See _J_o_b_s for a description of the format of



     Page 28                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               _j_o_b.

          |- bbbbrrrreeeeaaaakkkk [ _n ]
               Exit from the enclosing ffffoooorrrr, wwwwhhhhiiiilllleeee, uuuunnnnttttiiiillll, or sssseeeelllleeeecccctttt
               loop, if any.  If _n is specified then break _n levels.

          |- ccccoooonnnnttttiiiinnnnuuuueeee [ _n ]
               Resume the next iteration of the enclosing ffffoooorrrr, wwwwhhhhiiiilllleeee,
               uuuunnnnttttiiiillll, or sssseeeelllleeeecccctttt loop.  If _n is specified then resume
               at the _n-th enclosing loop.

          ccccdddd [ _a_r_g ]
          ccccdddd _o_l_d _n_e_w
               This command can be in either of two forms.  In the
               first form it changes the current directory to _a_r_g.  If
               _a_r_g is ---- the directory is changed to the previous
               directory.  The shell variable HHHHOOOOMMMMEEEE is the default _a_r_g.
               The variable PPPPWWWWDDDD is set to the current directory.  The
               shell variable CCCCDDDDPPPPAAAATTTTHHHH defines the search path for the
               directory containing _a_r_g.  Alternative directory names
               are separated by a colon (::::).  The default path is
               <<<<nnnnuuuullllllll>>>> (specifying the current directory).  Note that
               the current directory is specified by a null path name,
               which can appear immediately after the equal sign or
               between the colon delimiters anywhere else in the path
               list.  If _a_r_g begins with a //// then the search path is
               not used.  Otherwise, each directory in the path is
               searched for _a_r_g.
               The second form of ccccdddd substitutes the string _n_e_w for
               the string _o_l_d in the current directory name, PPPPWWWWDDDD and
               tries to change to this new directory.
               The ccccdddd command may not be executed by _r_k_s_h.

          eeeecccchhhhoooo [ _a_r_g ... ]
               See _e_c_h_o(1) for usage and description.

          |- eeeevvvvaaaallll [ _a_r_g ... ]
               The arguments are read as input to the shell and the
               resulting command(s) executed.

          |- eeeexxxxeeeecccc [ _a_r_g ... ]
               If _a_r_g is given, the command specified by the arguments
               is executed in place of this shell without creating a
               new process.  Input/output arguments may appear and
               affect the current process.  If no arguments are given
               the effect of this command is to modify file
               descriptors as prescribed by the input/output
               redirection list.  In this case, any file descriptor
               numbers greater than 2 that are opened with this
               mechanism are closed when invoking another program.

          |- eeeexxxxiiiitttt [ _n ]



     Page 29                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               Causes the shell to exit with the exit status specified
               by _n.  If _n is omitted then the exit status is that of
               the last command executed.  An end-of-file will also
               cause the shell to exit except for a shell which has
               the _i_g_n_o_r_e_e_o_f option (See sssseeeetttt below) turned on.

          |-|- eeeexxxxppppoooorrrrtttt [ _n_a_m_e[====_v_a_l_u_e] ] ...
               The given _n_a_m_es are marked for automatic export to the
               _e_n_v_i_r_o_n_m_e_n_t of subsequently-executed commands.

          ffffcccc [ ----eeee _e_n_a_m_e  ] [ ----nnnnllllrrrr ] [ _f_i_r_s_t [ _l_a_s_t ] ]
          ffffcccc ----eeee ---- [ _o_l_d====_n_e_w ] [ _c_o_m_m_a_n_d ]
               In the first form, a range of commands from _f_i_r_s_t to
               _l_a_s_t is selected from the last HHHHIIIISSSSTTTTSSSSIIIIZZZZEEEE commands that
               were typed at the terminal.  The arguments _f_i_r_s_t and
               _l_a_s_t may be specified as a number or as a string.  A
               string is used to locate the most recent command
               starting with the given string.  A negative number is
               used as an offset to the current command number.  If
               the ----llll flag is selected, the commands are listed on
               standard output.  Otherwise, the editor program _e_n_a_m_e
               is invoked on a file containing these keyboard
               commands.  If _e_n_a_m_e is not supplied, then the value of
               the variable FFFFCCCCEEEEDDDDIIIITTTT (default ////bbbbiiiinnnn////eeeedddd) is used as the
               editor.  When editing is complete, the edited
               command(s) is executed.  If _l_a_s_t is not specified then
               it will be set to _f_i_r_s_t.  If _f_i_r_s_t is not specified the
               default is the previous command for editing and -16 for
               listing.  The flag ----rrrr reverses the order of the
               commands and the flag ----nnnn suppresses command numbers
               when listing.  In the second form the _c_o_m_m_a_n_d is re-
               executed after the substitution _o_l_d====_n_e_w is performed.

          ffffgggg [ _j_o_b... ]
               This command is only on systems that support job
               control.  Each _j_o_b specified is brought to the
               foreground.  Otherwise, the current job is brought into
               the foreground.  See _J_o_b_s for a description of the
               format of _j_o_b.

          ggggeeeettttooooppppttttssss _o_p_t_s_t_r_i_n_g _n_a_m_e [ _a_r_g ... ]
               Checks _a_r_g for legal options.  If _a_r_g is omitted, the
               positional parameters are used.  An option argument
               begins with a ++++ or a ----.  An option not beginning with ++++
               or ---- or the argument -------- ends the options.  _o_p_t_s_t_r_i_n_g
               contains the letters that _g_e_t_o_p_t_s recognizes.  If a
               letter is followed by a ::::, that option is expected to
               have an argument.  The options can be separated from
               the argument by blanks.
               ggggeeeettttooooppppttttssss places the next option letter it finds inside
               variable _n_a_m_e each time it is invoked with a ++++
               prepended when _a_r_g begins with a ++++.  The index of the



     Page 30                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               next _a_r_g is stored in OOOOPPPPTTTTIIIINNNNDDDD.  The option argument, if
               any, gets stored in OOOOPPPPTTTTAAAARRRRGGGG.
               A leading :::: in _o_p_t_s_t_r_i_n_g causes ggggeeeettttooooppppttttssss to store the
               letter of an invalid option in OOOOPPPPTTTTAAAARRRRGGGG, and to set _n_a_m_e
               to ???? for an unknown option and to :::: when a required
               option is missing.  Otherwise, ggggeeeettttooooppppttttssss prints an error
               message.  The exit status is non-zero when there are no
               more options.

          jjjjoooobbbbssss [ ----llllnnnnpppp ] [ _j_o_b ... ]
               Lists information about each given job; or all active
               jobs if _j_o_b is omitted.  The ----llll flag lists process ids
               in addition to the normal information.  The ----nnnn flag
               only displays jobs that have stopped or exited since
               last notified.  The ----pppp flag causes only the process
               group to be listed.  See _J_o_b_s for a description of the
               format of _j_o_b.

          kkkkiiiillllllll [ ----_s_i_g ] _j_o_b ...
          kkkkiiiillllllll ----llll
               Sends either the TERM (terminate) signal or the
               specified signal to the specified jobs or processes.
               Signals are either given by number or by names (as
               given in ////uuuussssrrrr////iiiinnnncccclllluuuuddddeeee////ssssiiiiggggnnnnaaaallll....hhhh, stripped of the prefix
               ``SIG'').  If the signal being sent is TERM (terminate)
               or HUP (hangup), then the job or process will be sent a
               CONT (continue) signal if it is stopped.  The argument
               _j_o_b can be the process id of a process that is not a
               member of one of the active jobs.  See _J_o_b_s for a
               description of the format of _j_o_b.  In the second form,
               kkkkiiiillllllll ----llll, the signal numbers and names are listed.

          lllleeeetttt _a_r_g ...
               Each _a_r_g is a separate _a_r_i_t_h_m_e_t_i_c _e_x_p_r_e_s_s_i_o_n to be
               evaluated.  See _A_r_i_t_h_m_e_t_i_c _E_v_a_l_u_a_t_i_o_n above, for a
               description of arithmetic expression evaluation.
               The exit status is 0 if the value of the last
               expression is non-zero, and 1 otherwise.

          |- nnnneeeewwwwggggrrrrpppp [ _a_r_g ... ]
               Equivalent to eeeexxxxeeeecccc ////bbbbiiiinnnn////nnnneeeewwwwggggrrrrpppp _a_r_g ....

          pppprrrriiiinnnntttt [ ----RRRRnnnnpppprrrrssssuuuu[_n ] ] [ _a_r_g ... ]
               The shell output mechanism.  With no flags or with flag
               ---- or -------- the arguments are printed on standard output as
               described by _e_c_h_o(1).  In raw mode, ----RRRR or ----rrrr, the
               escape conventions of _e_c_h_o are ignored.  The ----RRRR option
               will print all subsequent arguments and options other
               than ----nnnn.  The ----pppp option causes the arguments to be
               written onto the pipe of the process spawned with ||||&&&&
               instead of standard output.  The ----ssss option causes the
               arguments to be written onto the history file instead



     Page 31                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               of standard output.  The ----uuuu flag can be used to specify
               a one digit file descriptor unit number _n on which the
               output will be placed.  The default is 1.  If the flag
               ----nnnn is used, no nnnneeeewwww----lllliiiinnnneeee is added to the output.

          ppppwwwwdddd  Equivalent to pppprrrriiiinnnntttt ----rrrr ---- $$$$PPPPWWWWDDDD

          rrrreeeeaaaadddd [ ----pppprrrrssssuuuu[ _n ] ] [ _n_a_m_e????_p_r_o_m_p_t ] [ _n_a_m_e ... ]
               The shell input mechanism.  One line is read and is
               broken up into fields using the characters in IIIIFFFFSSSS as
               separators.  In raw mode, ----rrrr,,,, a \\\\ at the end of a line
               does not signify line continuation.  The first field is
               assigned to the first _n_a_m_e, the second field to the
               second _n_a_m_e, etc., with leftover fields assigned to the
               last _n_a_m_e.  The ----pppp option causes the input line to be
               taken from the input pipe of a process spawned by the
               shell using ||||&&&&.  If the ----ssss flag is present, the input
               will be saved as a command in the history file.  The
               flag ----uuuu can be used to specify a one digit file
               descriptor unit _n to read from.  The file descriptor
               can be opened with the eeeexxxxeeeecccc special command.  The
               default value of _n is 0.  If _n_a_m_e is omitted then RRRREEEEPPPPLLLLYYYY
               is used as the default _n_a_m_e.  The exit status is 0
               unless an end-of-file is encountered.  An end-of-file
               with the ----pppp option causes cleanup for this process so
               that another can be spawned.  If the first argument
               contains a ????, the remainder of this word is used as a
               _p_r_o_m_p_t on standard error when the shell is interactive.
               The exit status is 0 unless an end-of-file is
               encountered.

          |-|- rrrreeeeaaaaddddoooonnnnllllyyyy [ _n_a_m_e[====_v_a_l_u_e] ] ...
               The given _n_a_m_e_s are marked readonly and these names
               cannot be changed by subsequent assignment.

          |- rrrreeeettttuuuurrrrnnnn [ _n ]
               Causes a shell _f_u_n_c_t_i_o_n to return to the invoking
               script with the return status specified by _n.  If _n is
               omitted then the return status is that of the last
               command executed.  If rrrreeeettttuuuurrrrnnnn is invoked while not in a
               _f_u_n_c_t_i_o_n or a ssssccccrrrriiiipppptttt,,,, tttthhhheeeennnn iiiitttt iiiissss tttthhhheeee ssssaaaammmmeeee aaaassss aaaannnn eeeexxxxiiiitttt.

          sssseeeetttt [ ++++____aaaaeeeeffffhhhhkkkkmmmmnnnnooooppppssssttttuuuuvvvvxxxx ] [ ++++____oooo _o_p_t_i_o_n ]... [ ++++____AAAA _n_a_m_e ]  [ _a_r_g ... ]
               The flags for this command have meaning as follows:
               ----AAAA      Array assignment.  Unset the variable _n_a_m_e and
                       assign values sequentially from the list _a_r_g.
                       If ++++AAAA is used, the variable _n_a_m_e is not unset
                       first.
               ----aaaa      All subsequent variables that are defined are
                       automatically exported.
               ----eeee      If a command has a non-zero exit status,
                       execute the EEEERRRRRRRR trap, if set, and exit.  This



     Page 32                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



                       mode is disabled while reading profiles.
               ----ffff      Disables file name generation.
               ----hhhh      Each command becomes a tracked alias when first
                       encountered.
               ----kkkk      All variable assignment arguments are placed in
                       the environment for a command, not just those
                       that precede the command name.
               ----mmmm      Background jobs will run in a separate process
                       group and a line will print upon completion.
                       The exit status of background jobs is reported
                       in a completion message.  On systems with job
                       control, this flag is turned on automatically
                       for interactive shells.
               ----nnnn      Read commands and check them for syntax errors,
                       but do not execute them.  Ignored for
                       interactive shells.
               ----oooo      The following argument can be one of the
                       following option names:
                       aaaalllllllleeeexxxxppppoooorrrrtttt
                               Same as ----aaaa.
                       eeeerrrrrrrreeeexxxxiiiitttt Same as ----eeee.
                       bbbbggggnnnniiiicccceeee  All background jobs are run at a lower
                               priority.  This is the default mode.
                       eeeemmmmaaaaccccssss   Puts you in an _e_m_a_c_s style in-line
                               editor for command entry.
                       ggggmmmmaaaaccccssss   Puts you in a _g_m_a_c_s style in-line
                               editor for command entry.
                       iiiiggggnnnnoooorrrreeeeeeeeooooffff
                               The shell will not exit on end-of-file.
                               The command eeeexxxxiiiitttt must be used.
                       kkkkeeeeyyyywwwwoooorrrrdddd Same as ----kkkk.
                       mmmmaaaarrrrkkkkddddiiiirrrrssss
                               All directory names resulting from file
                               name generation have a trailing ////
                               appended.
                       mmmmoooonnnniiiittttoooorrrr Same as ----mmmm.
                       nnnnoooocccclllloooobbbbbbbbeeeerrrr
                               Prevents redirection >>>> from truncating
                               existing files.  Require >>>>|||| to truncate
                               a file when turned on.
                       nnnnooooeeeexxxxeeeecccc  Same as ----nnnn.
                       nnnnoooogggglllloooobbbb  Same as ----ffff.
                       nnnnoooolllloooogggg   Do not save function definitions in
                               history file.
                       nnnnoooouuuunnnnsssseeeetttt Same as ----uuuu.
                       pppprrrriiiivvvviiiilllleeeeggggeeeedddd
                               Same as ----pppp.
                       vvvveeeerrrrbbbboooosssseeee Same as ----vvvv.
                       ttttrrrraaaacccckkkkaaaallllllll
                               Same as ----hhhh.
                       vvvviiii      Puts you in insert mode of a _v_i style
                               in-line editor until you hit escape



     Page 33                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



                               character 000033333333.  This puts you in move
                               mode.  A return sends the line.
                       vvvviiiirrrraaaawwww   Each character is processed as it is
                               typed in _v_i mode.
                       xxxxttttrrrraaaacccceeee  Same as ----xxxx.
                               option settings are printed.
                       If no option name is supplied then the current
               ----pppp      Disables processing of the $$$$HHHHOOOOMMMMEEEE////....pppprrrrooooffffiiiilllleeee file
                       and uses the file ////eeeettttcccc////ssssuuuuiiiidddd____pppprrrrooooffffiiiilllleeee instead of
                       the EEEENNNNVVVV file.  This mode is on whenever the
                       effective uid (gid) is not equal to the real
                       uid (gid).  Turning this off causes the
                       effective uid and gid to be set to the real uid
                       and gid.
               ----ssss      Sort the positional parameters
                       lexicographically.
               ----tttt      Exit after reading and executing one command.
               ----uuuu      Treat unset parameters as an error when
                       substituting.
               ----vvvv      Print shell input lines as they are read.
               ----xxxx      Print commands and their arguments as they are
                       executed.
               ----       Turns off ----xxxx and ----vvvv flags and stops examining
                       arguments for flags.
               --------      Do not change any of the flags; useful in
                       setting $$$$1111 to a value beginning with ----.  If no
                       arguments follow this flag then the positional
                       parameters are unset.

               Using ++++ rather than ---- causes these flags to be turned
               off.  These flags can also be used upon invocation of
               the shell.  The current set of flags may be found in
               $$$$----.  Unless ----AAAA is specified, the remaining arguments
               are positional parameters and are assigned, in order,
               to $$$$1111 $$$$2222 ....  If no arguments are given then the names
               and values of all variables are printed on the standard
               output.

          |- sssshhhhiiiifffftttt [ _n ]
               The positional parameters from $$$$_n++++1111 ...  are renamed $$$$1111
               ...  , default _n is 1.  The parameter _n can be any
               arithmetic expression that evaluates to a non-negative
               number less than or equal to $$$$####.

          |- ttttiiiimmmmeeeessss
               Print the accumulated user and system times for the
               shell and for processes run from the shell.

          |- ttttrrrraaaapppp [ _a_r_g ] [ _s_i_g ] ...
               _a_r_g is a command to be read and executed when the shell
               receives signal(s) _s_i_g.  (Note that _a_r_g is scanned once
               when the trap is set and once when the trap is taken.)



     Page 34                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



               Each _s_i_g can be given as a number or as the name of the
               signal.  Trap commands are executed in order of signal
               number.  Any attempt to set a trap on a signal that was
               ignored on entry to the current shell is ineffective.
               If _a_r_g is omitted or is ----, then the trap(s) for each
               _s_i_g are reset to their original values.  If _a_r_g is the
               null string then this signal is ignored by the shell
               and by the commands it invokes.  If _s_i_g is EEEERRRRRRRR then _a_r_g
               will be executed whenever a command has a non-zero exit
               status.  If _s_i_g is DDDDEEEEBBBBUUUUGGGG then _a_r_g will be executed
               after each command.  If _s_i_g is 0000 or EEEEXXXXIIIITTTT and the ttttrrrraaaapppp
               statement is executed inside the body of a function,
               then the command _a_r_g is executed after the function
               completes.  If _s_i_g is 0000 or EEEEXXXXIIIITTTT for a ttttrrrraaaapppp set outside
               any function then the command _a_r_g is executed on exit
               from the shell.  The ttttrrrraaaapppp command with no arguments
               prints a list of commands associated with each signal
               number.

          |-|- ttttyyyyppppeeeesssseeeetttt [ ++++____HHHHLLLLRRRRZZZZffffiiiillllrrrrttttuuuuxxxx[_n] ]  [ _n_a_m_e[ ====_v_a_l_u_e ]  ] ...
               Sets attributes and values for shell variables and
               functions.  When invoked inside a function, a new
               instance of the variables _n_a_m_e is created.  The
               variables value and type are restored when the function
               completes.  The following list of attributes may be
               specified:
               ----HHHH   This flag provides UNIX to host-name file mapping
                    on non-UNIX machines.
               ----LLLL   Left justify and remove leading blanks from _v_a_l_u_e.
                    If _n is non-zero it defines the width of the
                    field, otherwise it is determined by the width of
                    the value of first assignment.  When the variable
                    is assigned to, it is filled on the right with
                    blanks or truncated, if necessary, to fit into the
                    field.  Leading zeros are removed if the ----ZZZZ flag
                    is also set.  The ----RRRR flag is turned off.
               ----RRRR   Right justify and fill with leading blanks.  If _n
                    is non-zero it defines the width of the field,
                    otherwise it is determined by the width of the
                    value of first assignment.  The field is left
                    filled with blanks or truncated from the end if
                    the variable is reassigned.  The ----LLLL flag is turned
                    off.
               ----ZZZZ   Right justify and fill with leading zeros if the
                    first non-blank character is a digit and the ----LLLL
                    flag has not been set.  If _n is non-zero it
                    defines the width of the field, otherwise it is
                    determined by the width of the value of first
                    assignment.
               ----ffff   The names refer to function names rather than
                    variable names.  No assignments can be made and
                    the only other valid flags are ----tttt, ----uuuu and ----xxxx.  The



     Page 35                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



                    flag ----tttt turns on execution tracing for this
                    function.  The flag ----uuuu causes this function to be
                    marked undefined.  The FFFFPPPPAAAATTTTHHHH variable will be
                    searched to find the function definition when the
                    function is referenced.  The flag ----xxxx allows the
                    function definition to remain in effect across
                    shell procedures invoked by name.
               ----iiii   Parameter is an integer.  This makes arithmetic
                    faster.  If _n is non-zero it defines the output
                    arithmetic base, otherwise the first assignment
                    determines the output base.
               ----llll   All upper-case characters are converted to lower-
                    case.  The upper-case flag, ----uuuu is turned off.
               ----rrrr   The given _n_a_m_e_s are marked readonly and these
                    names cannot be changed by subsequent assignment.
               ----tttt   Tags the variables.  Tags are user definable and
                    have no special meaning to the shell.
               ----uuuu   All lower-case characters are converted to upper-
                    case characters.  The lower-case flag, ----llll is
                    turned off.
               ----xxxx   The given _n_a_m_es are marked for automatic export to
                    the _e_n_v_i_r_o_n_m_e_n_t of subsequently-executed commands.

               Using ++++ rather than ---- causes these flags to be turned
               off.  If no _n_a_m_e arguments are given but flags are
               specified, a list of _n_a_m_e_s (and optionally the _v_a_l_u_e_s)
               of the _v_a_r_i_a_b_l_e_s which have these flags set is printed.
               (Using ++++ rather than ---- keeps the values from being
               printed.)  If no _n_a_m_es and flags are given, the _n_a_m_e_s
               and _a_t_t_r_i_b_u_t_e_s of all _v_a_r_i_a_b_l_e_s are printed.

          uuuulllliiiimmmmiiiitttt [ ----HHHHSSSSaaaaccccddddffffmmmmnnnnppppssssttttvvvv ] [ _l_i_m_i_t ]
               Set or display a resource limit.  The available
               resources limits are listed below.  Many systems do not
               contain one or more of these limits.  The limit for a
               specified resource is set when _l_i_m_i_t is specifed.  The
               value of _l_i_m_i_t can be a number in the unit specifed
               below with each resource, or the value uuuunnnnlllliiiimmmmiiiitttteeeedddd.  The
               HHHH and SSSS flags specify whether the hard limit or the
               soft limit for the given resource is set.  A hard limit
               cannot be increased once it is set.  A soft limit can
               be increased up to the value of the hard limit.  If
               neither the HHHH or SSSS options is specified, the limit
               applies to both.  The current resource limit is printed
               when _l_i_m_i_t is omitted.  In this case the soft limit is
               printed unless HHHH is specified.  When more that one
               resource is specifed, then the limit name and unit is
               printed before the value.
               ----aaaa   Lists all of the current resource limits.
               ----cccc   The number of 512-byte blocks on the size of core
                    dumps.
               ----dddd   The number of K-bytes on the size of the data



     Page 36                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



                    area.
               ----ffff   The number of 512-byte blocks on files written by
                    child processes (files of any size may be read).
               ----mmmm   The number of K-bytes on the size of physical
                    memory.
               ----nnnn   The number of file descriptors plus 1.
               ----pppp   The number of 512-byte blocks for pipe buffering.
               ----ssss   The number of K-bytes on the size of the stack
                    area.
               ----tttt   The number of seconds to be used by each process.
               ----vvvv   The number of K-bytes for virtual memory.

               If no option is given, ----ffff is assumed.

          uuuummmmaaaasssskkkk [ _m_a_s_k ]
               The user file-creation mask is set to _m_a_s_k (see
               _u_m_a_s_k(2)).  _m_a_s_k can either be an octal number or a
               symbolic value as described in _c_h_m_o_d(1).  If a symbolic
               value is given, the new umask value is the complement
               of the result of applying _m_a_s_k to the complement of the
               previous umask value.  If _m_a_s_k is omitted, the current
               value of the mask is printed.

          uuuunnnnaaaalllliiiiaaaassss _n_a_m_e ...
               The  aliases given by the list of _n_a_m_es are removed
               from the _a_l_i_a_s list.

          uuuunnnnsssseeeetttt [ ----ffff ] _n_a_m_e ...
               The variables given by the list of _n_a_m_es are
               unassigned, i.xe., their values and attributes are
               erased.  Readonly variables cannot be unset.  If the
               ----ffff, flag is set, then the names refer to _f_u_n_c_t_i_o_n
               names.  Unsetting EEEERRRRRRRRNNNNOOOO, LLLLIIIINNNNEEEENNNNOOOO, MMMMAAAAIIIILLLLCCCCHHHHEEEECCCCKKKK, OOOOPPPPTTTTAAAARRRRGGGG,
               OOOOPPPPTTTTIIIINNNNDDDD, RRRRAAAANNNNDDDDOOOOMMMM, SSSSEEEECCCCOOOONNNNDDDDSSSS, TTTTMMMMOOOOUUUUTTTT, and ____ removes their
               special meaning even if they are subsequently assigned
               to.

          |- wwwwaaaaiiiitttt [ _j_o_b ]
               Wait for the specified _j_o_b and report its termination
               status.  If _j_o_b is not given then all currently active
               child processes are waited for.  The exit status from
               this command is that of the process waited for.  See
               _J_o_b_s for a description of the format of _j_o_b.

          wwwwhhhheeeennnncccceeee [ ----ppppvvvv ] _n_a_m_e ...
               For each _n_a_m_e, indicate how it would be interpreted if
               used as a command name.
               The ----vvvv flag produces a more verbose report.
               The ----pppp flag does a path search for _n_a_m_e even if name is
               an alias, a function, or a reserved word.

        IIIInnnnvvvvooooccccaaaattttiiiioooonnnn....



     PPPPaaaaggggeeee 33337777                                         ((((pppprrrriiiinnnntttteeeedddd 7777////22225555////88889999))))






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          If the shell is invoked by _e_x_e_c(2), and the first character
          of argument zero ($$$$0000) is ----, then the shell is assumed to be
          a _l_o_g_i_n shell and commands are read from ////eeeettttcccc////pppprrrrooooffffiiiilllleeee and
          then from either ....pppprrrrooooffffiiiilllleeee in the current directory or
          $$$$HHHHOOOOMMMMEEEE////....pppprrrrooooffffiiiilllleeee, if either file exists.  Next, commands are
          read from the file named by performing parameter
          substitution on the value of the environment variable EEEENNNNVVVV if
          the file exists.  If the ----ssss flag is not present and _a_r_g is,
          then a path search is performed on the first _a_r_g to
          determine the name of the script to execute.  The script _a_r_g
          must have read permission and any _s_e_t_u_i_d and _g_e_t_g_i_d settings
          will be ignored.  Commands are then read as described below;
          the following flags are interpreted by the shell when it is
          invoked:

          ----cccc _s_t_r_i_n_g If the ----cccc flag is present then commands are read
                    from _s_t_r_i_n_g.
          ----ssss        If the ----ssss flag is present or if no arguments
                    remain then commands are read from the standard
                    input.  Shell output, except for the output of the
                    _S_p_e_c_i_a_l _c_o_m_m_a_n_d_s listed above, is written to file
                    descriptor 2.
          ----iiii        If the ----iiii flag is present or if the shell input
                    and output are attached to a terminal (as told by
                    _i_o_c_t_l(2)) then this shell is _i_n_t_e_r_a_c_t_i_v_e.  In this
                    case TERM is ignored (so that kkkkiiiillllllll 0000 does not kill
                    an interactive shell) and INTR is caught and
                    ignored (so that wwwwaaaaiiiitttt is interruptible).  In all
                    cases, QUIT is ignored by the shell.
          ----rrrr        If the ----rrrr flag is present the shell is a
                    restricted shell.

          The remaining flags and arguments are described under the
          sssseeeetttt command above.

        RRRRkkkksssshhhh OOOOnnnnllllyyyy....
          _R_k_s_h is used to set up login names and execution
          environments whose capabilities are more controlled than
          those of the standard shell.  The actions of _r_k_s_h are
          identical to those of _s_h, except that the following are
          disallowed:
               changing directory (see _c_d(1)),
               setting the value of SSSSHHHHEEEELLLLLLLL, EEEENNNNVVVV, or PPPPAAAATTTTHHHH,,,,
               specifying path or command names containing ////,
               redirecting output (>>>>, >>>>|||| ,,,, <<<<>>>> ,,,, and >>>>>>>>).

          The restrictions above are enforced after ....pppprrrrooooffffiiiilllleeee and the
          EEEENNNNVVVV files are interpreted.

          When a command to be executed is found to be a shell
          procedure, _r_k_s_h invokes _k_s_h to execute it.  Thus, it is
          possible to provide to the end-user shell procedures that



     Page 38                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          have access to the full power of the standard shell, while
          imposing a limited menu of commands; this scheme assumes
          that the end-user does not have write and execute
          permissions in the same directory.

          The net effect of these rules is that the writer of the
          ....pppprrrrooooffffiiiilllleeee has complete control over user actions, by
          performing guaranteed setup actions and leaving the user in
          an appropriate directory (probably _n_o_t the login directory).

          The system administrator often sets up a directory of
          commands (i.e., ////uuuussssrrrr////rrrrbbbbiiiinnnn) that can be safely invoked by
          _r_k_s_h.

     EEEEXXXXIIIITTTT SSSSTTTTAAAATTTTUUUUSSSS
          Errors detected by the shell, such as syntax errors, cause
          the shell to return a non-zero exit status.  Otherwise, the
          shell returns the exit status of the last command executed
          (see also the eeeexxxxiiiitttt command above).  If the shell is being
          used non-interactively then execution of the shell file is
          abandoned.  Run time errors detected by the shell are
          reported by printing the command or function name and the
          error condition.  If the line number that the error occurred
          on is greater than one, then the line number is also printed
          in square brackets ([[[[]]]]) after the command or function name.

     FFFFIIIILLLLEEEESSSS
          /etc/passwd
          /etc/profile
          /etc/suid_profile
          $HOME/....profile
          /tmp/sh*
          /dev/null

     SSSSEEEEEEEE AAAALLLLSSSSOOOO
          cat(1), cd(1), chmod(1), cut(1), echo(1), emacs(1), env(1),
          gmacs(1), newgrp(1), stty(1), test(1), umask(1), vi(1),
          dup(2), exec(2), fork(2), ioctl(2), lseek(2), paste(1),
          pipe(2), signal(2), umask(2), ulimit(2), wait(2), rand(3),
          a.out(5), profile(5), environ(7).

          Morris I. Bolsky and David G. Korn, _T_h_e _K_o_r_n_S_h_e_l_l _C_o_m_m_a_n_d
          _a_n_d _P_r_o_g_r_a_m_m_i_n_g _L_a_n_g_u_a_g_e, Prentice Hall, 1989.

     CCCCAAAAVVVVEEEEAAAATTTTSSSS
          If a command which is a _t_r_a_c_k_e_d _a_l_i_a_s is executed, and then
          a command with the same name is installed in a directory in
          the search path before the directory where the original
          command was found, the shell will continue to _e_x_e_c the
          original command.  Use the ----tttt option of the aaaalllliiiiaaaassss command to
          correct this situation.




     Page 39                                         (printed 7/25/89)






     KKKKSSSSHHHH((((1111))))                    ((((RRRR&&&&DDDD UUUUNNNNIIIIXXXX SSSSTTTTDDDD))))                   KKKKSSSSHHHH((((1111))))



          Some very old shell scripts contain a ^^^^ as a synonym for the
          pipe character ||||.

          Using the ffffcccc built-in command within a compound command will
          cause the whole command to disappear from the history file.

          The built-in command .... _f_i_l_e reads the whole file before any
          commands are executed.  Therefore, aaaalllliiiiaaaassss and uuuunnnnaaaalllliiiiaaaassss
          commands in the file will not apply to any functions defined
          in the file.

          Traps are not processed while a job is waiting for a
          foreground process.  Thus, a trap on CCCCHHHHLLLLDDDD won't be executed
          until the forground job terminates.









































     Page 40                                         (printed 7/25/89)



