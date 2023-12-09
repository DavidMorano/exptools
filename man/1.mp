


     MP(1)                      (EXPTOOLS)                       MP(1)



     NAME
          mp, inimp - MetaPost system for drawing pictures

     SYNOPSIS
          mp [ -T ] [ _f_i_l_e [ .mp ] ]

          mp [ -T ] [ \&_m_e_m-_f_i_l_e ] [ _c_o_m_m_a_n_d_s ]

          inimp [ _f_i_l_e-_o_r-_c_o_m_m_a_n_d_s ]

     DESCRIPTION
          _M_p interprets the MetaPost language and produces _P_o_s_t_S_c_r_i_p_t
          pictures.  The MetaPost language is similar to Knuth's
          _M_E_T_A_F_O_N_T with additional features for including _t_e_x(1) or
          _t_r_o_f_f commands and accessing features of PostScript not
          found in METAFONT.

          The argument given on the command line is normally the name
          of the input file (possibly truncated).  It can also be a
          sequence of MetaPost commands starting with a suitable
          quoted `\' possibly preceeded by a quoted `&' and the name
          of a `.mem' file.  For example, `mp figs' processes the file
          `figs.mp'.  The basename of `figs' becomes the _j_o_b_n_a_m_e, and
          is used in forming output file names.  If no file is named,
          the jobname becomes `mpout' and _m_p reads from standard
          input.  The default `.mp' extension can be overridden by
          specifying an extension explicitly.

          There is normally one output file for each picture gener-
          ated, and the output files are named _j_o_b_n_a_m_e._n_n_n, where _n_n_n
          is a number passed to the `beginfig' macro.

          The output files can be used as figures in a TeX document by
          including
                          \special{psfile=_j_o_b_n_a_m_e._n_n_n}
          in the TeX document.  Alternatively, one can `\input
          epsf.tex' and then use the macro \epsfbox{_j_o_b_n_a_m_e._n_n_n} to
          produce a box of the appropriate size containing the figure.

          On most systems, the output files can also be used in a
          _t_r_o_f_f document.  To do this, use the `-T' flag with _m_p and
          use the `-mpictures' macro package with your _t_r_o_f_f document.
          The _t_r_o_f_f macro
                   .BP _j_o_b_n_a_m_e._n_n_n [height] [width] [xoffset]
          includes the file _j_o_b_n_a_m_e._n_n_n and scales the picture so it
          just fits within the given height and width.

          In order to support _t_r_o_f_f, _m_p needs to be able to find ASCII
          font description files that give font layouts and other
          information.  With the _t_r_o_f_f that comes with Documentor's
          WorkBench (DWB) version 3.1 or later, the necessary files
          have names like _I, _R, _H_I, and can usually be found in



     Page 1                    Tenth Edition         (printed 4/28/92)






     MP(1)                      (EXPTOOLS)                       MP(1)



          /usr/lib/font/devpost or /usr/add-on/dwb/lib/font/devpost.
          If neither directory contains the right information, mp -T
          prints an error message and stops unless the environment
          variable TRFONTS specifies another font directory.

          btex _T_e_X _c_o_m_m_a_n_d_s etex
               This causes _m_p to generate a MetaPost picture expres-
               sion that corresponds to the TeX commands.  If the TeX
               commands generate more than one line of text, it must
               be in a `\vbox' or a minipage environment.  Under the
               `-T' flag, the commands between `btex' and `etex' are
               processed by _t_r_o_f_f instead of TeX.

          verbatimtex _T_e_X _c_o_m_m_a_n_d_s etex
               This is ignored by _m_p except that the TeX commands are
               passed on to TeX.  When using LaTeX instead of TeX the
               input file must start with a `verbatimtex' block that
               gives the `\documentstyle' and `\begin{document}' com-
               mands.  The `-T' flag causes the commands to be pre-
               cessed by _t_r_o_f_f instead of TeX.

          Since most TeX fonts have to be downloaded as bitmaps, the
          `btex' feature works best when the output of `mp' is to be
          included in a TeX document so that _d_v_i_p_s(1) can download the
          fonts.  For self-contained PostScript output that can be
          used directly, start your MetaPost input file with the com-
          mand `prologues:=1' and stick to standard PostScript fonts.
          (The `-T' flag inserts this command automatically).  TeX and
          MetaPost use the names in the third column of the file
          `$TOOLS/lib/mp/trfonts.map'.

          Here is a complete list of the environment variables that
          affect the behavior of _m_p:

          MPINPUTS    Search path for `\input' files.  It should be
                      colon-separated, and start with dot.  Default:
                      `.:$TOOLS/lib/mp/bin'
          MFINPUTS    Auxiliary search path for `\input' files with
                      `.mf' extensions.  Default:
                      `.:$TOOLS/lib/tex/mf'
          TEXFONTS    Search path for font metric files.  Default:
                      `.:$TOOLS/lib/tex/fonts'
          MPXCOMMAND  The name of a shell script that converts embed-
                      ded typesetting commands to a form that _m_p
                      understands.  Default:
                      `$TOOLS/lib/mp/bin/makempx' or
                      `$TOOLS/lib/mp/bin/troffmpx'
          TEX         The version of TeX to use when processing `btex'
                      and `verbatimtex' commands.  Default: `tex'
          TROFF       The _t_r_o_f_f pipeline for `btex' and `verbatimtex'
                      commands.  Default: `eqn -d\$\$ | troff'
          TRFONTS     The directory containing _t_r_o_f_f font description



     Page 2                    Tenth Edition         (printed 4/28/92)






     MP(1)                      (EXPTOOLS)                       MP(1)



                      files.  Default: `/usr/lib/font/devpost' or
                      `/usr/add-on/dwb/lib/font/devpost'
          MPMEMS      Search path for `.mem' files. Default:
                      `.:$TOOLS/lib/mp'
          MPPOOL      Search path for strings.  Default:
                      `.:$TOOLS/lib/mp'
          MPEDITOR    A command for invoking an editor with `%s' in
                      place of the file name and `%d' in place of the
                      line number.  Default: `vi +%d %s'
          TEXVFONTS   Search path for virtual fonts.  Default:
                      `$TOOLS/lib/tex/fonts'

          A `.mem' file is a binary file that permits fast loading of
          fonts and macro packages.  _M_p reads the default plain.mem
          unless another `.mem' file is specified at the beginning of
          the command line.  There is also an mfplain.mem that simu-
          lates plain METAFONT so that _m_p can read `.mf' fonts.
          (Plain METAFONT is described in _T_h_e _M_E_T_A_F_O_N_T_b_o_o_k).  A spe-
          cial version of _m_p called _i_n_i_m_p creates a `.mem' file when
          it interprets a `dump' command.

          The MetaPost language is similar to METAFONT, but the manual
          _A _U_s_e_r'_s _M_a_n_u_a_l _f_o_r _M_e_t_a_P_o_s_t assumes no knowledge of META-
          FONT.  MetaPost does not have bitmap output commands or
          METAFONT's online display mechanism.  The manual can be
          obtained in PostScript form by mailing the one line message
                        send 162 from research/cstr
          to research!netlib.

     FILES
          $TOOLS/lib/mp/lib/*             MetaPost macros, `.mem'
                                          files
          $TOOLS/lib/tex/macros/epsf.tex  The TeX input file where the
                                          `\epsfbox' macro is defined
          $TOOLS/lib/mp/trfonts.map       table of corresponding font
                                          names for _t_r_o_f_f, PostScript,
                                          and TeX
          $TOOLS/lib/mp                   Miscelaneous tables for _m_p
                                          and _i_n_i_m_p
          $TOOLS/lib/mp/charlib           Instructions that _m_p uses
                                          for handling _t_r_o_f_f special
                                          characters
          $TOOLS/lib/mp/bin               Programs used by _m_p and
                                          _i_n_i_m_p

     SEE ALSO
          _t_e_x(1),
          Donald E. Knuth, _T_h_e _M_E_T_A_F_O_N_T_b_o_o_k, Addison Wesley, 1986,
          John D. Hobby, _A _U_s_e_r'_s _M_a_n_u_a_l _f_o_r _M_e_t_a_P_o_s_t 11272-920413-
          15TM





     Page 3                    Tenth Edition         (printed 4/28/92)



