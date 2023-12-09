






       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))

       NNNNAAAAMMMMEEEE
            vb, ve - SCCS/ECMS/SABLIME version environment

       SSSSYYYYNNNNOOOOPPPPSSSSIIIISSSS
            vvvveeee [options ...] [file ...]
            vvvvbbbb [options ...] [file ...]

       DDDDEEEESSSSCCCCRRRRIIIIPPPPTTTTIIIIOOOONNNN
            The SCCS/ECMS/SABLIME Version Environment (VE) provides
            a single command interface to activities with Source
            Code Control System (SCCS) maintained files, especially
            in the context of the Extended Change Management System
            (ECMS) and the AT&T Product Administration System
            (SABLIME).  VE is an alternative to eeeeddddggggeeeetttt, ssssggggeeeetttt, vvvviiii or
            eeeemmmmaaaaccccssss, and eeeeddddppppuuuutttt.  Additionally, vvvveeee provides an
            interface to many other ECMS and SABLIME operations,
            including uuuunnnneeeeddddggggeeeetttt, uuuunnnneeeeddddppppuuuutttt, and rrrreeeeppppoooorrrrtttt.  Features of vvvveeee
            also provide alternatives to activities that normally
            would require ccccmmmmsssspppprrrr and qqqquuuueeeerrrryyyy.  Similar capabilites are
            available for SCCS users not in an ECMS or SABLIME
            environment.

            The basic goal of vvvveeee is to make it easy to examine or
            change a file maintained under version control with
            SCCS, ECMS, or SABLIME.  Current conventional scenarios
            extract a "flat" image from SCCS/ECMS/SABLIME for
            editing, but to understand the origin of each line of
            the flat file extracted, expert knowledge of
            SCCS/ECMS/SABLIME and the SCCS file itself is usually
            required.  The distinguishing feature of vvvveeee is that the
            version information used for the extraction from
            SCCS/ECMS/SABLIME is available during the editing or
            browsing session.

            For an ECMS or SABLIME user, viewing a file and having
            the version information available can be as simple as

                 vvvveeee gggg====5555eeee6666____1111kkkk RRRRTTTTmmmmaaaaiiiinnnn....mmmmdddd

            This places the user in the editor, with a view of the
            file that is equivalent to that obtained by

                 ssssggggeeeetttt gggg====5555eeee6666____1111kkkk RRRRTTTTmmmmaaaaiiiinnnn....mmmmdddd

            However, _n_o _f_i_l_e _h_a_d _t_o _b_e _c_r_e_a_t_e_d _i_n _t_h_e _c_u_r_r_e_n_t
            _d_i_r_e_c_t_o_r_y, version information is readily available,
            and the view of the file, equivalent to ssssggggeeeetttt with
            various combinations of parameters, is easily changed
            _w_i_t_h_o_u_t _l_e_a_v_i_n_g _t_h_e _e_d_i_t_o_r.  Version information for



       Page 1                              (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


            the current line is easily displayed with the editor
            command ^^^^GGGG (in vvvviiii mode) or ^^^^XXXX^^^^GGGG (in eeeemmmmaaaaccccssss mode).  The
            version information shows the MR affecting the line,
            who did the change, when it was done, the status of the
            MR, and the abstract of the MR.

            Moreover, editing in the versioned environment is fully
            supported, with special handling for ECMS feature
            constructs.  There are also provisions for the
            automatic detection and merging of other changes to the
            file that might occur if the user is editing without
            having locked the file.

            In the ECMS or SABLIME environment, use of vvvveeee presumes
            some familiarity with ECMS or SABLIME; see the
            appropriate User's Manual.  For the plain SCCS
            environment, see standard UNIX commands aaaaddddmmmmiiiinnnn,,,, ggggeeeetttt, and
            ddddeeeellllttttaaaa.  In particular, to create an SCCS file, vvvveeee has a
            built in aaaaddddmmmmiiiinnnn command.  If you are editing an ordinary
            file (either already existing or that you have yet to
            write out), use the command ::::aaaaddddmmmmiiiinnnn (in vvvviiii mode) or
            ^^^^XXXXeeeeaaaaddddmmmmiiiinnnn (in eeeemmmmaaaaccccssss mode), and an SCCS file will be
            created from the current ordinary file you are editing.
            The activities of reserving and recording deltas for
            SCCS files are also integrated into vvvveeee.

            vvvveeee also operates on ordinary text files, so can provide
            a uniform editor interface when dealing with some files
            under SCCS, ECMS, or SABLIME as well as ordinary files.
            In particular, vvvveeee is suitable to specify as an editor
            to tools like ccccssssccccooooppppeeee, and will seek to treat named
            files as SCCS, ECMS, or SABLIME files if at all
            possible.

            The VE interface is very much the same as the screen
            editor vvvviiii or the screen editor eeeemmmmaaaaccccssss, with a number of
            extensions, and some limitations.

       PPPPAAAARRRRAAAAMMMMEEEETTTTEEEERRRRSSSS
            All parameters are optional; they are grouped into
            several categories and described below.
          GGGGeeeennnneeeerrrraaaallll OOOOppppttttiiiioooonnnnssss
            The following command line options apply to SCCS, ECMS,
            SABLIME, and ordinary file usage.

            ----VVVV      causes the release of the version editor to be
                    printed, and the program exits.

            ++++_n      causes the initial display to have the cursor
                    positioned at line number _n.




       Page 2                              (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


            ++++////_R_E    causes the initial display to have the cursor
                    positioned at the first line containing the
                    regular expression _R_E.
          EEEEddddiiiittttiiiinnnngggg AAAAccccttttiiiivvvviiiittttyyyy OOOOppppttttiiiioooonnnnssss
            The following options control editing activity.  Except
            for the first three, these options apply only to SCCS,
            ECMS, or SABLIME usage.  In addition to being specified
            on the command line, each of these options may also be
            given a new value during the editing session.  In vvvviiii
            mode, this is accomplished with the ::::sssseeeetttt command, e.g.,
            ::::sssseeeetttt mmmmrrrr====rrrrttttaaaa11112222333344445555UUUU.  Boolean options may also be
            specified in typical vvvviiii fashion, e.g., ::::sssseeeetttt nnnnooooeeeeddddggggeeeetttt is
            equivalent to eeeeddddggggeeeetttt====nnnn.  In eeeemmmmaaaaccccssss mode, these options
            may be set by ^^^^XXXX^^^^MMMM, e.g., ^^^^XXXX^^^^MMMMmmmmrrrr====rrrrttttaaaa11112222333344445555UUUU.  Boolean
            options may also be specified in typical eeeemmmmaaaaccccssss fashion,
            e.g., MMMM--------^^^^XXXX^^^^MMMMeeeeddddggggeeeetttt is equivalent to eeeeddddggggeeeetttt====nnnn.

            ffffoooorrrrcccceeeeoooorrrrddddiiiinnnnaaaarrrryyyy====_y causes any file read to be treated as
                           an ordinary file, regardless of the file
                           prefix or existence in the ECMS or
                           SABLIME data base.  The default is
                           ffffoooorrrrcccceeeeoooorrrrddddiiiinnnnaaaarrrryyyy====nnnn.

            vvvviiiieeeewwww====_n         causes the visibility and attribute
                           assignments in the view map menu to be
                           ignored.  The default is vvvviiiieeeewwww====yyyy.  (May
                           also be specified as uuuusssseeeevvvviiiieeeewwwwmmmmaaaapppp instead
                           of vvvviiiieeeewwww.)

            vvvviiiieeeewwwwmmmmaaaapppp====_f_i_l_e   causes the visibility and attribute
                           assignments in the view map menu to be
                           taken from the named file.  The special
                           value of ddddeeeeffffaaaauuuulllltttt will cause the current
                           view map assignments to reset to the
                           default assignments used when
                           initializing a file.  The default value
                           for this option is taken from the
                           environment variable VVVVIIIIEEEEWWWWMMMMAAAAPPPP.

            pppprrrreeeeffffiiiixxxx====_f_i_l_e    specifies the prefix file that points to
                           the ECMS data base.  If the shell
                           variable PPPPRRRREEEEFFFFIIIIXXXX is set, its value is
                           used.  If no prefix file is specified
                           (either explicitly or through the
                           environment), then no ECMS access can be
                           done and no file can be treated as an
                           ECMS file.  [Applies to ECMS files
                           only.]

            ssssaaaabbbbGGGGDDDDBBBB====_d_i_r_e_c_t_o_r_y specifies the SABLIME global data base
                           directory.  If the shell variable ssssaaaabbbbGGGGDDDDBBBB



       Page 3                              (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                           is set, its value is used.  If no
                           directory is specified (either
                           explicitly or through the environment),
                           then no SABLIME access can be done and
                           no file can be treated as a SABLIME
                           file.  [Applies to SABLIME files only.]

            pppprrrroooodddduuuucccctttt====_p_r_o_d_n_a_m_e specifies the SABLIME product
                           constraint.  If the shell variable
                           ssssaaaabbbbPPPPRRRROOOODDDD is set, its value is used.  If
                           no product is specified (either
                           explicitly or through the environment),
                           then no SABLIME access can be done and
                           no file can be treated as a SABLIME
                           file.  [Applies to SABLIME files only.]

            ccccoooommmmmmmmeeeennnntttt====_t_e_x_t   specifies text to be used as a comment
                           for the SCCS delta command.  If non-
                           interactive mode, no prompting will be
                           done for comments when deltas are
                           created.  If interactive mode, prompting
                           will be done to confirm comment choice.
                           This option may also be specified by
                           ----yyyy_t_e_x_t.  This option can only be
                           specified on the command line and cannot
                           be changed during the editing session.

            eeeeddddiiiitttt====_n         inhibits interactive editing, i.e, the
                           VE reads the file, saves a versioned
                           copy, and exits.  This is mainly used
                           with other options that cause actions
                           like reserving the file for editing, or
                           extracting a flat file.  The default is
                           eeeeddddiiiitttt====yyyy.  This option can only be
                           specified on the command line and cannot
                           be changed during the editing session.

            ccccmmmmsssspppprrrr====_y        creates a P.file containing the visible
                           lines of the file annotated by the MRs
                           or deltas that affected the lines.  This
                           option implies eeeeddddiiiitttt====nnnn, i.e., interactive
                           editing is inhibited.  The default is
                           ccccmmmmsssspppprrrr====nnnn.  This option can only be
                           specified on the command line and cannot
                           be changed during the editing session.
                           This option may also be specified by
                           ssssccccccccsssspppprrrr or ssssrrrrccccpppprrrr.

            SSSSffffiiiilllleeee====_n        prevents the creation of the saved
                           versioned file (_S._f_i_l_e) in non-
                           interactive mode.  When combined with



       Page 4                              (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                           eeeeddddiiiitttt====nnnn eeeexxxxttttrrrraaaacccctttt====yyyy the results will be
                           like that produced by ggggeeeetttt////ssssggggeeeetttt for
                           SCCS/ECMS/SABLIME files.  The default is
                           SSSSffffiiiilllleeee====yyyy, so that the saved versioned
                           file is created.  This option has no
                           effect in interactive mode.

            eeeeddddggggeeeetttt====_y        reserves the file for editing when
                           reading; in the case of ECMS or SABLIME,
                           an eeeeddddggggeeeetttt command is executed, and for
                           SCCS files this is equivalent to ggggeeeetttt ----eeee
                           (may also be specified by ----eeee).  eeeeddddggggeeeetttt====pppp
                           may also be specified to indicate that
                           before any attempt to read an
                           SCCS/ECMS/SABLIME file, the user should
                           be prompted as to whether the file
                           should be reserved for editing.  eeeeddddggggeeeetttt====nnnn
                           indicates that the file should not be
                           reserved.

            eeeeddddppppuuuutttt====_y        records the changes as a delta when
                           writing; in the case of ECMS or SABLIME,
                           an eeeeddddppppuuuutttt command is executed, and for
                           SCCS files this is equivalent to ddddeeeellllttttaaaa
                           (may also be specified by ----dddd).  eeeeddddppppuuuutttt====pppp
                           may also be specified to indicate that
                           when writing an SCCS/ECMS/SABLIME file,
                           the user should be prompted as to
                           whether the changes should be recorded
                           as a delta.  eeeeddddppppuuuutttt====nnnn indicates that no
                           delta should be made.

            mmmmrrrr====_m_r          specifies an ECMS or SABLIME MR to
                           associate with any editing activity.
                           This MR must be in the state 'assigned'
                           for the given generic, and is required
                           for eeeeddddggggeeeetttt====yyyy.  If the shell variable MMMMRRRR
                           is set, its value is used.

            nnnneeeewwwwffff====_f oooollllddddffff====_f  specifies old and new features to use
                           for the special "X" MR mode of editing.
                           The presence of these options indicates
                           the X MR editing mode, in which the only
                           type of changes allowed are to switch
                           featuring between the two indicated
                           features.  (The editing command is ^^^^VVVVxxxx
                           in vvvviiii mode and ^^^^XXXXxxxx in eeeemmmmaaaaccccssss mode.)
                           [Applies to ECMS files only.]

            vvvveeeeffffeeeeaaaattttuuuurrrreeee====_f    specifies an ECMS feature to use for
                           editing.  If given, it must be a valid



       Page 5                              (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                           feature changeable by the generic and
                           project.  If not given and only featured
                           changes are allowed, a suitable feature
                           will be chosen by vvvveeee.  If the shell
                           variable VVVVEEEEFFFFEEEEAAAATTTTUUUURRRREEEE is set, its value is
                           used.  [Applies to ECMS files only.]

            aaaauuuuttttooooeeeexxxxttttrrrraaaacccctttt====_y  causes the "flat" file to be produced
                           whenever the editor saves the versioned
                           file, i.e., is similar to the effect of
                           the ECMS or SABLIME command ssssggggeeeetttt or the
                           UNIX command ggggeeeetttt (may also be specified
                           by eeeexxxxttttrrrraaaacccctttt====yyyy or ----qqqq).  The default is
                           aaaauuuuttttooooeeeexxxxttttrrrraaaacccctttt====yyyy for interactive editing,
                           and aaaauuuuttttooooeeeexxxxttttrrrraaaacccctttt====nnnn for non-interactive
                           use.

            aaaauuuuttttooooffffeeeeaaaattttuuuurrrriiiinnnngggg====_n indicates that nnnnoooo interpretation of
                           #_f_e_a_t_u_r_e control lines should be done.
                           Thus, the version of every line will be
                           "featureless", and the control lines
                           themselves will appear as ordinary text
                           lines (may also be specified by ----ffff).
                           The default is aaaauuuuttttooooffffeeeeaaaattttuuuurrrriiiinnnngggg====yyyy.
                           [Applies to ECMS files only.]

            rrrreeeerrrreeeeaaaadddd====_y       causes the file to be read again after
                           an SCCS delta has been made or when an
                           ordinary file is converted to an SCCS
                           file.  If this parameter has not been
                           explicitly set, the user will be
                           prompted for a response.

            rrrrmmmm====_y           forces the "flat" file to be removed
                           when the editor writes a new flat file,
                           or when eeeeddddppppuuuutttt or uuuunnnneeeeddddggggeeeetttt is executed
                           within the editor.  Otherwise, the file
                           will only be removed if the user
                           responds affirmatively when prompted.
                           For uuuunnnneeeeddddggggeeeetttt, the associated saved
                           versioned file (if it exists), is also
                           similarly removed.  If rrrrmmmm====nnnn, the user
                           will not be prompted and the flat file
                           will not be overwritten or removed.

            ppppddddeeeepppp====_p|_q|_l|_s   passed to any eeeeddddppppuuuutttt command executed by
                           the editor, indicates whether to prompt
                           for, quit, log, or log silently any
                           physical dependencies detected during
                           the eeeeddddppppuuuutttt.  The default is ppppddddeeeepppp====pppp.
                           [Applies to ECMS files only.]



       Page 6                              (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


            ssssrrrrcccciiiinnnnffffoooo====_y|_n    passed to any eeeeddddggggeeeetttt command executed by
                           the editor, indicates whether or not to
                           display information about unapproved
                           MRs.  The default is ssssrrrrcccciiiinnnnffffoooo====yyyy.
                           [Applies to ECMS files only.]

            nnnneeeewwwwbbbbrrrraaaannnncccchhhh====_y    passed to any ggggeeeetttt ----eeee command executed by
                           the editor, indicates whether or not to
                           create a new branch (may also be
                           specified by ----bbbb).  The default is
                           nnnneeeewwwwbbbbrrrraaaannnncccchhhh====nnnn.  [Applies to SCCS files
                           only.]
          IIIInnnniiiittttiiiiaaaallll VVVViiiieeeewwww OOOOppppttttiiiioooonnnnssss

            gggg====_g_e_n_e_r_i_c      specifies the ECMS generic; a generic
                           must be given if any ECMS activity is
                           desired.  If the shell variable GGGGEEEENNNNEEEERRRRIIIICCCC
                           or ssssaaaabbbbGGGGEEEENNNN is set, its value is used.
                           [Applies to ECMS and SABLIME files
                           only.]

            pppprrrroooojjjjeeeecccctttt====_p      specifies the ECMS project.  If the
                           shell variable PPPPRRRROOOOJJJJEEEECCCCTTTT is set, its value
                           is used.  [Applies to ECMS files only.]

            ddddiiiirrrr====_d_i_r_e_c_t_o_r_y  specifies the ECMS or SABLIME directory
                           for the file to be accessed.  This is a
                           relative path name known in the ECMS or
                           SABLIME data base for the generic, and
                           if not given, defaults to the relative
                           location of the current directory in the
                           first node listed in the shell variable
                           VVVVPPPPAAAATTTTHHHH, provided that the current
                           directory is a sub-directory of that
                           first node.  [Applies to ECMS and
                           SABLIME files only.]

            bbbbrrrr====_o_f_c|_m_r      specifies which branch of the ECMS or
                           SABLIME file to display.  The default is
                           'ofc', the official branch, containing
                           only approved changes.  However, for
                           eeeeddddggggeeeetttt====yyyy, the default is branch 'mr',
                           containing the most recent view of the
                           file, including unapproved changes.  If
                           the shell variable BBBBRRRR is set, its value
                           is used.  [Applies to ECMS and SABLIME
                           files only.]

            iiiinnnnccccmmmmrrrr====_m_r_s      specifies a comma separated list of MRs
                           or groupnames of MRs to include in the
                           display of the file, in addition to



       Page 7                              (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                           changes selected by the branch.  If the
                           shell variable IIIINNNNCCCCMMMMRRRR is set, its value
                           is used.  This option may also be
                           specified as mmmmrrrrssss====_m_r_s or uuuummmmrrrrssss====_m_r_s.
                           [Applies to ECMS and SABLIME files
                           only.]

            iiiinnnnccccssssttttaaaattttuuuussss====_s_t_a_t specifies a comma separated list of
                           statuses of MRs to include in the
                           display of the file, in addition to
                           changes selected by the branch.  If the
                           shell variable IIIINNNNCCCCSSSSTTTTAAAATTTTUUUUSSSS is set, its
                           value is used.  [Applies to ECMS and
                           SABLIME files only.]

            iiiinnnnttttgggg====_y         specifies if only integrated MRs on the
                           official branch should be included,
                           rather than the default, which is both
                           approved as well as integrated MRs.  The
                           default is iiiinnnnttttgggg====nnnn.  If the shell
                           variable IIIINNNNTTTTGGGG is set, its value is used.
                           [Applies to ECMS files only.]

            bbbbrrrrddddaaaatttteeee====_d_a_t_e    specifies a cutoff date, so that only
                           deltas prior to the cutoff date are
                           included.  If the shell variable BBBBRRRRDDDDAAAATTTTEEEE
                           is set, its value is used.  This option
                           can also be given as bbbbrrrrddddtttt====_d_a_t_e or
                           ----cccc_d_a_t_e.

            ffff====_f_e_a_t_u_r_e_s     specifies a list of ECMS features to
                           include in the display of the file.  If
                           not specified the default included
                           features for the generic and project are
                           used; in any case the required features
                           for the generic and project are always
                           used.  If the shell variable FFFFEEEEAAAATTTTUUUURRRREEEE is
                           set, its value is used.  [Applies to
                           ECMS files only.]

            aaaalllllllloooowwww====_f_e_a_t_u_r_e_s specifies a list of ECMS features to
                           treat as if they have status "allow" for
                           the project and generic - this will only
                           be possible if the features do not have
                           a status defined for the generic and
                           project.  Such features are treated as
                           if they have status "disallow" by
                           default.  [Applies to ECMS files only.]

            wwwwhhhhoooolllleeee====_y        specifies that the ECMS featured file is
                           to be displayed without feature



       Page 8                              (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                           evaluation, i.e, all lines, including
                           feature control lines, are shown.  This
                           is the default for eeeeddddggggeeeetttt====yyyy, but
                           otherwise the default is wwwwhhhhoooolllleeee====nnnn, in
                           which case no feature lines are
                           displayed, and only the lines extracted
                           for the included feature set are shown.
                           If the shell variable WWWWHHHHOOOOLLLLEEEE is set, its
                           value is used.  [Applies to ECMS files
                           only.]

            sssshhhhoooowwwwffffcccc====_y       specifies that feature control lines are
                           to be displayed in the ECMS featured
                           file.  By default, feature control lines
                           are displayed if wwwwhhhhoooolllleeee====yyyy and not
                           displayed if wwwwhhhhoooolllleeee====nnnn; this options
                           allows feature control lines to be
                           displayed, even if intervening text
                           lines are suppressed because they are
                           not extracted for the current project
                           and generic.  [Applies to ECMS files
                           only.]

            ssssccccccccssssddddiiiirrrr====_d_i_r_e_c_t_o_r_y specifies the directory in which SCCS
                           files reside.  If the shell variable
                           SSSSCCCCCCCCSSSSDDDDIIIIRRRR is set, its value is used.
                           [Applies to SCCS files only.]

            vvvveeeerrrrssssiiiioooonnnn====_S_I_D    specifies the version of the file to
                           view by giving an SCCS Identifier (SID).
                           This may also be specified as ----rrrr_S_I_D.
                           The default is the most recent version
                           of the file.  See ggggeeeetttt for more details.
                           [Applies to SCCS files only.]

            iiiinnnnccccddddeeeellllttttaaaa====_l_i_s_t  specifies a list of deltas forced to be
                           included, the list is comma separated
                           and consists of SCCS Identifiers (SIDs).
                           This may also be specified as ----iiii_l_i_s_t.
                           [Applies to SCCS files only.]

            eeeexxxxccccddddeeeellllttttaaaa====_l_i_s_t  specifies a list of deltas forced to be
                           excluded, the list is comma separated
                           and consists of SCCS Identifiers (SIDs).
                           This may also be specified as ----eeee_l_i_s_t.
                           [Applies to SCCS files only.]
          SSSSeeeelllleeeeccccttttiiiioooonnnn ooooffff FFFFiiiilllleeee ttttoooo EEEEddddiiiitttt

            ffffiiiilllleeee   specifies the file or files to be edited.  These
                   names may be full or relative path names.  For
                   ECMS or SABLIME usage, any initial portion of a



       Page 9                              (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                   relative path name is added to the directory as
                   noted in the ddddiiiirrrr option above.  The file name
                   should not contain the prefix "S." or "s.".  If
                   a file with the same name, and the prefix "S."
                   exists, it is assumed to be a saved session of
                   vvvveeee, and it will be used to resume the vvvveeee
                   session.  If a file with the same name, and the
                   prefix "s." exists, it is assumed to be an SCCS
                   file (originally created with aaaaddddmmmmiiiinnnn), and it
                   will be read to obtain a file to display.  If an
                   SCCS directory has been specified, the check for
                   an SCCS file with the "s." prefix will be done
                   in that directory, relative to the directory
                   indicated by the name of the file to be edited.
                   (E.g., if the SCCS directory has been given as
                   "sccs", then the simple file name "xxx" will
                   lead to the SCCS file "sccs/s.xxx", and the file
                   name "ddd/yyy" will lead to "ddd/sccs/s.yyy".)
                   If the ECMS database is available (determined
                   from the prefix file), and a generic has been
                   given, the file will be accessed from ECMS, if
                   it exists there.  If the SABLIME database is
                   available (determined from the sabGDB and
                   product options) and no ECMS environment exists,
                   and a generic has been given, the file will be
                   accessed from SABLIME, if it exists there.
                   Otherwise, ordinary editing occurs.

            If no file name is given, the user is simply in the
            editor with an empty buffer.

       EEEENNNNVVVVIIIIRRRROOOONNNNMMMMEEEENNNNTTTT
            As described in earlier sections, many parameter values
            may be specified through shell environment variables.
            These variables are: BBBBRRRR,,,, BBBBRRRRDDDDAAAATTTTEEEE,,,, FFFFEEEEAAAATTTTUUUURRRREEEE,,,, GGGGEEEENNNNEEEERRRRIIIICCCC,,,,
            IIIINNNNCCCCMMMMRRRR,,,, IIIINNNNCCCCSSSSTTTTAAAATTTTUUUUSSSS,,,, IIIINNNNTTTTGGGG,,,, PPPPRRRREEEEFFFFIIIIXXXX,,,, PPPPRRRROOOOJJJJEEEECCCCTTTT,,,, MMMMRRRR,,,, ssssaaaabbbbGGGGDDDDBBBB,,,,
            ssssaaaabbbbGGGGEEEENNNN,,,, ssssaaaabbbbPPPPRRRROOOODDDD,,,, SSSSCCCCCCCCSSSSDDDDIIIIRRRR,,,, VVVVEEEEFFFFEEEEAAAATTTTUUUURRRREEEE,,,, VVVVIIIIEEEEWWWWMMMMAAAAPPPP,,,, WWWWHHHHOOOOLLLLEEEE.

            In the EEEEddddiiiittttoooorrrr SSSSttttaaaarrrrttttuuuupppp section, the effect of the
            following variables is described: EEEEDDDDIIIITTTTOOOORRRR,,,, EEEEDDDDIIIITTTTOOOORRRR4444VVVVEEEE,,,,
            VVVVEEEEIIIINNNNIIIITTTT.

            Other shell variables used are:

            PPPPAAAAGGGGEEEERRRR     indicates the screen paging program to use to
                      display the output of certain shell commands
                      run from the editor, such as rrrreeeeppppoooorrrrtttt.  This
                      defaults to the standard UNIX command ppppgggg.

            SSSSHHHHEEEELLLLLLLL     indicates the shell to invoke for shell
                      escapes from the editor as well as file name



       Page 10                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                      and variable expansion.  This defaults to
                      ////bbbbiiiinnnn////sssshhhh.

            TTTTEEEERRRRMMMM      indicates the terminal type you are using
                      (used by the ccccuuuurrrrsssseeeessss package).  See the
                      RRRREEEESSSSTTTTRRRRIIIICCCCTTTTIIIIOOOONNNNSSSS section for details about
                      certain special cases.

            VVVVPPPPAAAATTTTHHHH     indicates the search path for resolving ECMS
                      file names.  If your current directory is one
                      of the directories in VVVVPPPPAAAATTTTHHHH, then relative
                      path names imply the portion of the path from
                      the node in VVVVPPPPAAAATTTTHHHH to the current directory.
                      If full path names to files are given, and
                      the initial portion of the name matches any
                      node in VVVVPPPPAAAATTTTHHHH, then the remaining portion of
                      the name is assumed to be the ECMS file
                      desired, if it exists under ECMS.

       RRRREEEESSSSTTTTRRRRIIIICCCCTTTTIIIIOOOONNNNSSSS
          TTTTeeeerrrrmmmmiiiinnnnaaaallllssss
            If you have a 4425 or 5425 terminal, the default
            terminal descriptor does not define all the possible
            video attributes (dim, bold, flashing, reverse, and
            underlined), so set these environment variables in your
            ._p_r_o_f_i_l_e:

                 TERMINFO=$TOOLS/lib/terminfo/terminfo; export TERMINFO
                 TERM=tty5425


            If you have a 5620 or 630 terminal and do not use
            _l_a_y_e_r_s(_1), the display may get scrambled in _e_m_a_c_s mode
            if the terminal cannot keep up with the flow of
            characters.  The following alternate key bindings are
            always accepted so that ^^^^SSSS and ^^^^QQQQ can be used for flow
            control:

                 ^^^^]]]]   for   ^^^^SSSS
                 ^^^^   for   ^^^^QQQQ
                 MMMM----^^^^]]]] for   MMMM----^^^^SSSS
                 ^^^^XXXX^^^^]]]] for   ^^^^XXXX^^^^SSSS

            If any of these alternate bindings are used before the
            normal ones, or if ^^^^SSSS is followed immediately by ^^^^QQQQ
            before ^^^^SSSS is used as a normal command, flow control
            will automatically be enabled (mode _f_l_o_w__l_i_m will be
            set to -_1).  If you must have ^^^^SSSS and ^^^^QQQQ instead of the
            alternate key bindings, disable flow control by setting
            _f_l_o_w__l_i_m to _0.




       Page 11                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


            If you do not currently use _l_a_y_e_r_s(_1), you can easily
            do so by putting the following at the end of your
            ._p_r_o_f_i_l_e:

                 if test "$TERM" = 630 -o "$TERM" = 5620
                 then layers
                 fi

            If you have a 6300 PC with a color monitor, to get
            useful color definitions set these environment
            variables in your ._p_r_o_f_i_l_e:

                 TERMINFO=$TOOLS/lib/terminfo/terminfo; export TERMINFO
                 TERM=6300c

       EEEEXXXXTTTTEEEENNNNDDDDEEEEDDDD DDDDEEEESSSSCCCCRRRRIIIIPPPPTTTTIIIIOOOONNNN
          EEEEddddiiiittttoooorrrr SSSSttttaaaarrrrttttuuuupppp
            When vvvvbbbb or vvvveeee is invoked, its editing mode will be
            either vvvviiii or eeeemmmmaaaaccccssss, depending on the shell environment
            variable EEEEDDDDIIIITTTTOOOORRRR (or EEEEDDDDIIIITTTTOOOORRRR4444VVVVEEEE if EEEEDDDDIIIITTTTOOOORRRR is not
            recognizable as vvvviiii or eeeemmmmaaaaccccssss).  If the tool is invoked
            as vvvvbbbb, then only commands for perusing the text are
            enabled; all commands which change text or write out
            the file are disabled.  More than one file name may be
            specified, allowing the user to work through a list of
            files without exiting the editor between each file.
            (Search expressions and named buffer contents are
            preserved between files.)

            In vvvviiii mode, if the shell environment variable VVVVEEEEIIIINNNNIIIITTTT is
            set and not null, its value will be interpreted as an
            "ex" type of command to be performed before interactive
            editing begins.  Thus, if VVVVEEEEIIIINNNNIIIITTTT is set to
            "se ai showversion", automatic indenting and constant
            version display of the current line will be enabled.

            In eeeemmmmaaaaccccssss mode, the commands in any $$$$HHHHOOOOMMMMEEEE////....vvvveeee____iiiinnnniiiitttt file
            will be executed when vvvveeee is invoked.

            By default, for ECMS featured files, at startup all
            #_f_e_a_t_u_r_e and #_e_n_d_f_e_a_t_u_r_e lines are interpreted, and
            used to assign feature as part of the version of the
            lines they enclose.  The control lines are not
            editable.  Additional control lines are generated as
            required by the editing.  Feature control directives
            that are not included (as indicated by the ssssggggeeeetttt-type
            parameters) are ignored for the purposes of feature
            interpretation, and no feature attribute is assigned to
            text lines that are not included.  If the shell
            environment variable VVVVEEEEFFFFEEEEAAAATTTTUUUURRRREEEE is set and not null, or
            a value is specified on the command line, the current



       Page 12                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


            feature in the editor will be set to its value; this is
            the featuring that will be used throughout the editing
            session.  (See the section on VE specific commands for
            commands to change the current feature.)  If VVVVEEEEFFFFEEEEAAAATTTTUUUURRRREEEE
            is not set, but FFFFEEEEAAAATTTTUUUURRRREEEE is set, then the first
            changeable feature named by FFFFEEEEAAAATTTTUUUURRRREEEE is used for the
            current feature.  If neither of these variables is set,
            and project isolation does not allow non-featured code
            to be changed, then a current feature is chosen, first
            trying for a feature with the same name as the project,
            then looking for a changeable feature of required,
            included, or allowed status (in that order).
          VVVVEEEE SSSSppppeeeecccciiiiffffiiiicccc CCCCoooommmmmmmmaaaannnnddddssss
            The following sections list the version specific
            commands available within vvvveeee.  For a complete list of
            all editing commands, see the VVVVeeeerrrrssssiiiioooonnnn EEEEnnnnvvvviiiirrrroooonnnnmmmmeeeennnntttt UUUUsssseeeerrrr
            GGGGuuuuiiiiddddeeee.
          VVVVEEEE SSSSppppeeeecccciiiiffffiiiicccc CCCCoooommmmmmmmaaaannnnddddssss ((((vvvviiii MMMMooooddddeeee))))

            ^^^^GGGG     Print the current line number and version
                   attributes.

                   To distinguish VE commands in vvvviiii mode that have
                   no common vvvviiii counterpart, the command character
                   ^^^^VVVV is used as a command prefix.  (This character
                   is unused as a command in vvvviiii.)

            ^^^^VVVV////    Search forward for next line matching given
                   version expression.

            ^^^^VVVV????    Search backward for next line matching given
                   version expression.

            ^^^^VVVVnnnn    Repeat expression search, same direction.

            ^^^^VVVVNNNN    Repeat expression search, reverse direction.

            ^^^^VVVVaaaa    Search forward for next line with same video
                   attribute as current line.

            ^^^^VVVVAAAA    Search backward for next line with same video
                   attribute as current line.

            ^^^^VVVV>>>>    Search forward for next line with given video
                   attribute.

            ^^^^VVVV<<<<    Search backward for next line with given video
                   attribute.

            ^^^^VVVVffff    Go to last line of innermost enclosing feature
                   block.



       Page 13                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


            ^^^^VVVVFFFF    Go to first line of innermost enclosing feature
                   block.

            ^^^^VVVV]]]]    Go to last line of enclosing feature block
                   indicated by given feature.

            ^^^^VVVV[[[[    Go to first line of enclosing feature block
                   indicated by given feature.

            ^^^^VVVV%%%%    Go to matching #_f_e_a_t_u_r_e/#_e_n_d_f_e_a_t_u_r_e control
                   line.

            ^^^^VVVVxxxx    This is a special command which is only
                   recognized in a file which is being edited with
                   a cross-project "X" MR.  The command may be
                   given while positioned on a feature control
                   line, and switches the featuring between the old
                   and new features given on the command line.
                   These features may be changed by "set oldf=f" or
                   "set newf=f".

            ^^^^VVVVuuuu    This is a special operator used to "undelete"
                   lines.  Lines can not be undeleted while in
                   autofeaturing mode, and only lines deleted by
                   the current delta can be undeleted.  This
                   operator works like other vvvviiii operators, e.g.,
                   ^^^^VVVVuuuuuuuu undeletes one line, ^^^^VVVVuuuu''''aaaa undeletes from
                   the current line to the one containing mark a.

            ^^^^VVVVvvvv    Search forward for next line with same version
                   as current line.

            ^^^^VVVVVVVV    Search backward for next line with same version
                   as current line.
          VVVVEEEE SSSSppppeeeecccciiiiffffiiiicccc CCCCoooommmmmmmmaaaannnnddddssss ((((eeeexxxx ccccoooommmmmmmmaaaannnnddddssss iiiinnnn vvvviiii MMMMooooddddeeee))))
            Following are version specific eeeexxxx type commands
            available from vvvveeee.  These commands are invoked by
            entering ::::, the command, and then RRRREEEETTTTUUUURRRRNNNN or EEEESSSSCCCC.

            VVVV      Go to the view menu.

            EEEE      Write a flat file, containing just the lines
                   indicated by the current inclusion options.  For
                   ECMS featured files, if aaaauuuuttttooooffffeeeeaaaattttuuuurrrriiiinnnngggg is not on,
                   the whole file with feature control lines will
                   be written (and the file name prefixed with
                   "f."), otherwise just the lines extracted for
                   the current generic and project will be written.

            FFFF      Display the origin and type of the file,
                   indicating SCCS, ECMS, SABLIME, or ordinary, and



       Page 14                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                   the date of the original SCCS file from which
                   the current file was read.  For ECMS and SABLIME
                   files, the generic, sourcefile, and directory
                   name are also displayed.

            PPPP      Produce a printable dump of visible lines of the
                   file.  The result of this command will contain
                   the information needed to produce a paper copy
                   of the visible lines of the buffer, including
                   video attribute information.  An appropriate
                   filter is required to properly print the dump;
                   its format consists of the view map (see
                   description of view map files later) and the
                   text lines.  Text lines consist of 'T', followed
                   by a space, followed by a string representing
                   the video attribute, followed by a space, and
                   finally the text of the line.

            SSSSWWWW     Write out the line range specified (default is
                   all visible lines) to the file specified.  The
                   default name is the original name used on
                   invocation.  This command can be used to save
                   all or a portion of what can be viewed into an
                   ordinary file.

            aaaaddddmmmmiiiinnnn  (Also ssssccccccccssss.)  For ordinary files only, run the
                   command aaaaddddmmmmiiiinnnn to create an SCCS file whose
                   initial contents are the current ordinary file.
                   If the ssssccccccccssssddddiiiirrrr option has a value, this will be
                   used to determine the location of the created
                   SCCS file.  After the SCCS file is created,
                   editing can continue if you choose to re-read
                   the file; it will now be treated as an SCCS file
                   with delta information available.

            ((((uuuunnnn))))eeeeddddggggeeeetttt (Also ggggeeeetttt or uuuunnnnggggeeeetttt.)  For ECMS and SABLIME
                   [SCCS] files, run the command ((((uuuunnnn))))eeeeddddggggeeeetttt
                   [((((uuuunnnn))))ggggeeeetttt] to (un)reserve the file for editing.
                   This does not affect the current contents of the
                   editor buffer.  An MR must have been specified
                   (see "set" options below).  If another change
                   has occurred to the file since vvvveeee initially
                   started up, the eeeeddddggggeeeetttt command will not be
                   attempted, but a message indicating to do a
                   mmmmeeeerrrrggggeeee (see below) will be given.  Once this has
                   been done, eeeeddddggggeeeetttt may be tried again.

            ((((uuuunnnn))))eeeeddddppppuuuutttt (Also ddddeeeellllttttaaaa or rrrrmmmmddddeeeellll.)  For ECMS and SABLIME
                   [SCCS] files, run the command ((((uuuunnnn))))eeeeddddppppuuuutttt
                   [ddddeeeellllttttaaaa////rrrrmmmmddddeeeellll] to (un)record the current changes
                   as a delta.  Upon successful completion of eeeeddddppppuuuutttt



       Page 15                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                   (or ddddeeeellllttttaaaa), the editor's buffer is discarded.
                   Upon successful completion of uuuunnnneeeeddddppppuuuutttt (or
                   rrrrmmmmddddeeeellll), you are prompted as to whether you want
                   the changes for the removed delta retained in
                   the editor's buffer as the current delta;
                   responding yes allows you to rework the change
                   without starting it all over; responding no
                   causes the editor to discard the buffer.  If
                   another change has occurred to the file since vvvveeee
                   initially started up, the eeeeddddppppuuuutttt command will not
                   be attempted, but a message indicating to do a
                   mmmmeeeerrrrggggeeee (see below) will be given.  Once this has
                   been done, eeeeddddppppuuuutttt may be tried again.  Note:
                   SABLIME does not implement uuuunnnneeeeddddppppuuuutttt.

            mmmmeeeerrrrggggeeee  For SCCS, ECMS, or SABLIME files, merge the
                   changes from the current editing session to the
                   original SCCS file.  If the original SCCS file
                   has not changed since initial retrieval for the
                   current changes, nothing is done.  (However, for
                   ECMS and SABLIME files, the MR status
                   information for the current generic is updated
                   since this information affects the view, even
                   though the underlying SCCS file is logically
                   equivalent.)  If it has changed, the current
                   changes are applied to this new base in a
                   reasonable fashion.  A report of the number of
                   lines inserted and deleted will be given, and
                   the view map will be adjusted to give
                   highlighting to lines inserted or deleted since
                   original retrieval, and to lines inserted or
                   deleted by the current session.  These changes
                   should be inspected to insure that the changes
                   are still relevant, correctly placed, and
                   desired before formally recording them under
                   SCCS/ECMS/SABLIME.

            ccccmmmmsssspppprrrr  For ECMS/SABLIME (SCCS) files, write the visible
                   lines of the file to a file named by adding the
                   prefix "P.", and label each line with the MR
                   (delta) that inserted it.  If a visible line is
                   deleted by an MR (delta), show the deleting MR
                   (delta), too.  Include line numbers if they are
                   currently displayed.  This command may also be
                   invoked as ssssccccccccsssspppprrrr or ssssrrrrccccpppprrrr.

            mmmmrrrrddddeeeepppp  For ECMS files only, run the ECMS command mmmmrrrrddddeeeepppp
                   to check for MR dependencies introduced by the
                   current changes.





       Page 16                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


            rrrreeeeppppoooorrrrtttt For ECMS and SABLIME files only, execute the
                   command rrrreeeeppppoooorrrrtttt to produce a report for the MR
                   that inserted the current line.  Other options
                   to rrrreeeeppppoooorrrrtttt may also be given.

            ssssrrrrccccpppprrrr  Alternative name for ccccmmmmsssspppprrrr described above.

            xxxxttttaaaammmm   For featured ECMS files only, run the ECMS
                   command xxxxttttaaaammmm to check for cross project
                   contamination introduced by the current changes.
                   The editor will prevent such contamination from
                   being introduced as long as the user has stayed
                   in aaaauuuuttttooooffffeeeeaaaattttuuuurrrriiiinnnngggg mode, so it is only useful to
                   run this command if manual editing of feature
                   control constructs has been done when
                   aaaauuuuttttooooffffeeeeaaaattttuuuurrrriiiinnnngggg mode has been turned off.

            sssseeeetttt    Sets certain VE specific options.  In addition
                   to all of the options listed in the PPPPAAAARRRRAAAAMMMMEEEETTTTEEEERRRRSSSS
                   section, and the usual vvvviiii options, the following
                   Boolean options may also be specified (options
                   that are on by default are so indicated):


                   mmmmiiiiggggrrrraaaatttteeee      group archived lines together (on)

                   sssshhhhoooowwwwaaaabbbbssssttttrrrraaaacccctttt display MR abstract in version
                                information (on)

                   sssshhhhoooowwwwddddaaaatttteeee     display date delta was made in
                                version information (on)

                   sssshhhhoooowwwwmmmmrrrrddddaaaatttteeee   display date MR status changed in
                                version information

                   sssshhhhoooowwwwmmmmrrrrssssttttaaaattttuuuussss display MR status in version
                                information (on)

                   sssshhhhoooowwwwppppggggmmmmrrrr     display login that made delta in
                                version information (on)

                   sssshhhhoooowwwwvvvveeeerrrrssssiiiioooonnnn  always display version information
                                for current line (as if ^^^^GGGG were
                                given after every command)

                   sssshhhhoooowwwwssssccccccccssssiiiidddd   display SCCS identifier (e.g.,
                                1.1.3.2) in version information

                   sssshhhhoooowwwwvvvvttttiiiimmmmeeee    display time along with date in
                                version information




       Page 17                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                   vvvveeeerrrrbbbboooosssseeee      give messages in response to user
                                errors, rather than just beeping
          VVVVEEEE SSSSppppeeeecccciiiiffffiiiicccc CCCCoooommmmmmmmaaaannnnddddssss ((((eeeemmmmaaaaccccssss MMMMooooddddeeee))))
            All of the options listed in the previous section may
            be set with the eeeemmmmaaaaccccssss ^^^^XXXX^^^^MMMM command.  In addition, the
            following version specific commands are available in
            eeeemmmmaaaaccccssss mode:

            ^^^^XXXX^^^^GGGG   Print the current line number and version
                   attributes.

            ^^^^XXXX^^^^ZZZZ   Go to the view map menu (also may be specified
                   by ^^^^XXXXVVVV).

            ^^^^XXXX////    Search forward for next line matching given
                   version expression.  (With negative argument,
                   searches backward.)

            ^^^^SSSS     Repeat search in forward direction (sub-command
                   for version expression and video attribute
                   searches).

            ^^^^RRRR     Repeat search in backward direction (sub-command
                   for version expression and video attribute
                   searches).

            ^^^^XXXXaaaa    Search for next line with a particular video
                   attribute (no argument, or argument of 1,
                   searches for line with same video attribute as
                   the current line; argument of greater than one
                   prompts for attribute; negative argument
                   searches backward).

            ^^^^XXXXeeee    Execute an SCCS/ECMS/SABLIME command, the
                   command is prompted for, and may be eeeeddddggggeeeetttt or
                   ggggeeeetttt, uuuunnnneeeeddddggggeeeetttt or uuuunnnnggggeeeetttt, eeeeddddppppuuuutttt or ddddeeeellllttttaaaa, uuuunnnneeeeddddppppuuuutttt
                   or rrrrmmmmddddeeeellll.  (The first three may be abbreviated
                   gggg, uuuu, and pppp, respectively.)
                   Other commands that may be specified are ccccmmmmsssspppprrrr,,,,
                   mmmmrrrrddddeeeepppp,,,, mmmmeeeerrrrggggeeee,,,, rrrreeeeppppoooorrrrtttt,,,, xxxxttttaaaammmm.
                   For descriptions of these commands, see the vvvviiii
                   MMMMooooddddeeee sections.

            ^^^^XXXXffff    go to last line of feature block (no argument,
                   or argument of 1, goes to last line of innermost
                   enclosing feature block; argument of greater
                   than one prompts for an enclosing feature;
                   negative argument goes to first line of block)

            ^^^^XXXXiiii    Display the origin and type of the file,
                   indicating SCCS, ECMS, SABLIME, or ordinary, and



       Page 18                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                   the date of the original SCCS file from which
                   the current file was read.  For ECMS and SABLIME
                   files, the generic, sourcefile, and directory
                   name are also displayed.

            ^^^^XXXXuuuu    This is a special command used to "undelete"
                   lines.  Lines can not be undeleted while in
                   autofeaturing mode, and only lines deleted by
                   the current delta can be undeleted.  A count may
                   be given, and that number of lines, beginning
                   with the current line, will be undeleted.

            ^^^^XXXXxxxx    This is a special command which is only
                   recognized in a file which is being edited with
                   a cross-project "X" MR.  The command may be
                   given while positioned on a feature control
                   line, and switches the featuring between the old
                   and new features given on the command line.
                   These features may be changed by ^X^Moldf=f or
                   ^X^Mnewf=f.

            ^^^^XXXXvvvv    Search forward for next line with same version
                   as current line.  (With negative argument,
                   searches backward.)

            ^^^^XXXXPPPP    Produce a P.file containing a printable dump of
                   the visible file lines.

            ^^^^XXXXWWWW    Write the currently visible lines to the named
                   file as an ordinary file.  If an argument is
                   given, append to the file if it exists.

            ^^^^XXXXXXXX    Extract an S.file into a flat file (and if
                   featured, an f.file).  With an argument, it
                   prompts for the file name (and if featured,
                   eeeexxxxttttrrrraaaacccctttt options)
          VVVViiiieeeewwww MMMMaaaapppp CCCCoooommmmmmmmaaaannnnddddssss
            Following are the commands available from the view map
            menu:

            aaaa    Assign an attribute to a version expression, the
                 version expression and attribute will be prompted
                 for; the number of an existing entry may be given
                 if the same version expression is desired; the
                 attribute may be specified as one or more letters
                 from the displayed attribute code list (multiple
                 codes will combine attributes)

            vvvv    Assign visibility to a version expression, the
                 version expression and visibility value will be
                 prompted for; the number of an existing entry may



       Page 19                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                 be given if the same version expression is desired

            mmmm    Modify the visibility or attribute associated with
                 an assigned version expression

            dddd    Delete a single visibility or attribute
                 assignment, or all current assignments

            rrrr    Read visibility and attribute assignments from a
                 file, appending to the current assignments

            wwww    Write out the current visibility and attribute
                 assignments to a file

            iiii    Specify inclusion options.  The options are
                 specified as _o_p_t_i_o_n__n_a_m_e=_v_a_l_u_e, and any of the
                 command line options may be given.  See the
                 descriptions of the command line options, or
                 ECMS/SABLIME ssssggggeeeetttt for more details).

            ^^^^LLLL   Refresh the screen

            qqqq    Quit the view menu, return to edit window
          VVVVeeeerrrrssssiiiioooonnnn EEEExxxxpppprrrreeeessssssssiiiioooonnnnssss
            A version expression is a "primitive" version
            expression, or is formed by combining version
            expressions with expression operators (parentheses, !,
            &&, and ||).  The primitive expressions use the
            keywords ddddeeeellllttttaaaa,,,, pppprrrrooooggggrrrraaaammmmmmmmeeeerrrr,,,, ddddaaaatttteeee,,,, mmmmrrrr,,,, mmmmrrrrssssttttaaaattttuuuussss,,,, mmmmrrrrddddaaaatttteeee,,,,
            ggggeeeennnneeeerrrriiiicccc,,,, rrrreeeelllleeeeaaaasssseeee,,,, lllleeeevvvveeeellll,,,, bbbbrrrraaaannnncccchhhh,,,, sssseeeeqqqquuuueeeennnncccceeee (optionally
            prefixed by iiiinnnnsssseeeerrrrtttteeeeddddbbbbyyyy; ddddeeeelllleeeetttteeeeddddbbbbyyyy or ~~~~; or aaaaffffffffeeeecccctttteeeeddddbbbbyyyy
            or ****), pppprrrroooojjjjeeeecccctttt,,,, eeeexxxxttttrrrraaaacccctttt,,,, oooowwwwnnnneeeerrrr,,,, iiiinnnnnnnneeeerrrr and eeeennnncccclllloooossssiiiinnnngggg and
            the relational operators ========,,,, !!!!====,,,, <<<<,,,, >>>>,,,, <<<<====,,,, >>>>====.  The
            version expression can be regarded as a means of
            selecting versions.  Thus, a version expression is
            considered as true or false with respect to a
            particular version, i.e., the set of version attributes
            of a line of the file being edited.  Or, one may regard
            the version expression as matching or not matching the
            version attributes of a line.  See the VVVVeeeerrrrssssiiiioooonnnn
            EEEEnnnnvvvviiiirrrroooonnnnmmmmeeeennnntttt UUUUsssseeeerrrr GGGGuuuuiiiiddddeeee for more details.
          EEEExxxxaaaammmmpppplllleeeessss ooooffff VVVVeeeerrrrssssiiiioooonnnn EEEExxxxpppprrrreeeessssssssiiiioooonnnnssss

              1.  iiiinnnnsssseeeerrrrtttteeeedddd bbbbyyyy mmmmrrrr ======== rrrrttttaaaa11112222333344445555LLLL

                  Matches lines inserted by Modification Request
                  rta12345L.  The iiiinnnnsssseeeerrrrtttteeeedddd bbbbyyyy prefix is optional,
                  but improves readability.

              2.  ddddeeeelllleeeetttteeeedddd bbbbyyyy mmmmrrrr ======== rrrrttttaaaa11112222333344445555LLLL




       Page 20                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                  Matches lines deleted by Modification Request
                  rta12345L.

              3.  pppprrrrooooggggrrrraaaammmmmmmmeeeerrrr ======== ddddllllaaaa |||||||| pppprrrrooooggggrrrraaaammmmmmmmeeeerrrr ======== ppppaaaallll

                  Matches lines inserted by login dla or pal.

              4.  aaaaffffffffeeeecccctttteeeedddd bbbbyyyy pppprrrrooooggggrrrraaaammmmmmmmeeeerrrr ======== ddddllllaaaa

                  Matches lines inserted or deleted by login dla.

              5.  iiiinnnnsssseeeerrrrtttteeeedddd bbbbyyyy ddddeeeellllttttaaaa ======== 1111....1111....1111....22228888

                  Matches lines inserted by delta 1.1.1.28.

              6.  ddddeeeelllleeeetttteeeedddd bbbbyyyy ddddeeeellllttttaaaa >>>> 0000

                  Matches all deleted lines (i.e., lines which have
                  been deleted by any delta).

              7.  mmmmrrrrssssttttaaaattttuuuussss !!!!==== ooooffffffffiiiicccciiiiaaaallll

                  Matches inserted lines that are not official
                  (i.e., not approved nor integrated nor included
                  when addsrc'ed for this generic).

              8.  ddddaaaatttteeee>>>>88886666////00006666 &&&&&&&& !!!!((((mmmmrrrrssssttttaaaattttuuuussss========aaaapppppppprrrroooovvvveeeedddd |||||||| mmmmrrrrssssttttaaaattttuuuussss========iiiinnnntttteeeeggggrrrraaaatttteeeedddd))))

                  Matches lines inserted during or after June 1986,
                  and not approved or integrated.  Note that for a
                  comparison like this, only a leading portion of
                  the value is given.  Since no date will consist
                  of _j_u_s_t 86/06, all dates beginning with 86/06
                  will be lexicographically strictly greater than
                  86/06.

              9.  ddddaaaatttteeee >>>> 88886666////00006666 &&&&&&&& ddddaaaatttteeee <<<< 88886666////00008888

                  Matches lines inserted during June and July of
                  1986.

             10.  eeeexxxxttttrrrraaaacccctttt ======== 5555EEEE2222____2222GGGG,,,,5555EEEE3333____1111LLLL,,,,5555EEEE4444____2222QQQQ

                  Matches lines extracted in presence of features
                  5E2_2G, 5E3_1L and 5E4_2Q (i.e., as ECMS
                  "extract" would produce).

             11.  !!!!eeeexxxxttttrrrraaaacccctttt ======== 5555EEEE2222____2222GGGG,,,,5555EEEE3333____1111LLLL,,,,5555EEEE4444____2222QQQQ

                  Matches lines not extracted in presence of
                  features 5E2_2G, 5E3_1L and 5E4_2Q, i.e., the



       Page 21                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


                  complementary lines to the preceding example (but
                  not including deleting lines).

             12.  oooowwwwnnnneeeerrrr ======== 5555EEEE3333____1111LLLL

                  Matches all lines "owned" by 5E3_1L.  These are
                  lines that are enclosed within #_f_e_a_t_u_r_e (_5_E_3__1_L),
                  but may also be further nested within negative
                  featuring, e.g., #_f_e_a_t_u_r_e (!_5_E_4__2_Q).

             13.  iiiinnnnnnnneeeerrrr ======== 5555EEEE3333____1111LLLL

                  Matches all lines immediately featured by 5E3_1L,
                  i.e., whose closest feature control lines are
                  #_f_e_a_t_u_r_e (_5_E_3__1_L) and #_e_n_d_f_e_a_t_u_r_e (_5_E_3__1_L).

             14.  iiiinnnnnnnneeeerrrr ======== """"!!!!5555EEEE4444____2222QQQQ""""

                  Matches all lines immediately featured out for
                  5E4_2Q, i.e., whose closest feature control lines
                  are #_f_e_a_t_u_r_e (!_5_E_4__2_Q) and #_e_n_d_f_e_a_t_u_r_e (!_5_E_4__2_Q).
                  Note that the quotation marks are necessary so
                  that "!" is taken as part of the value.

             15.  oooowwwwnnnneeeerrrr ========

                  Matches all lines that do not belong to a
                  feature.  Such lines might not be enclosed within
                  any #_f_e_a_t_u_r_e construct, or may be enclosed in
                  only negative featuring, e.g., #_f_e_a_t_u_r_e (_n_o_t
                  _5_E_2__2_G).

             16.  iiiinnnnnnnneeeerrrr ========

                  Matches all unfeatured lines, i.e., those lines
                  not enclosed within any ####ffffeeeeaaaattttuuuurrrreeee construct, even
                  negative feature control.

             17.  iiiinnnnnnnneeeerrrr !!!!====

                  Matches all featured lines, i.e., those lines
                  enclosed within any ####ffffeeeeaaaattttuuuurrrreeee construct.  Note
                  that this is different from !!!!iiiinnnnnnnneeeerrrr ======== , which
                  matches everything except lines that are
                  unfeatured, and this would include deleted lines.
          UUUUnnnniiiimmmmpppplllleeeemmmmeeeennnntttteeeedddd EEEEddddiiiittttoooorrrr FFFFeeeeaaaattttuuuurrrreeeessss
          UUUUnnnniiiimmmmpppplllleeeemmmmeeeennnntttteeeedddd vvvviiii////eeeexxxx iiiinnnnppppuuuutttt cccchhhhaaaarrrraaaacccctttteeeerrrrssss
            ^@, ^T, and ^W for last insertion, shiftwidth spaces,
            and word erase.
          UUUUnnnniiiimmmmpppplllleeeemmmmeeeennnntttteeeedddd vvvviiii ccccoooommmmmmmmaaaannnnddddssss
            ^R, {, } for redraw, beginning, end of sentences.



       Page 22                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


          UUUUnnnniiiimmmmpppplllleeeemmmmeeeennnntttteeeedddd vvvviiii mmmmooooddddeeeessss////ooooppppttttiiiioooonnnnssss
            autoprint, autowrite, beautify, directory,
            edcompatible, errorbells, hardtabs, lisp, magic, mesg,
            open, optimize, paragraphs, readonly, redraw, remap,
            report, scroll, sections, shell, showmatch, slowopen,
            term, ttytype, window, wrapmargin.
          UUUUnnnniiiimmmmpppplllleeeemmmmeeeennnntttteeeedddd eeeexxxx ccccoooommmmmmmmaaaannnnddddssss
            abbreviate, open, preserve, recover, tag, unabbreviate
          MMMMiiiisssscccceeeellllllllaaaannnneeeeoooouuuussss uuuunnnniiiimmmmpppplllleeeemmmmeeeennnntttteeeedddd vvvviiii ffffeeeeaaaattttuuuurrrreeeessss
            Tags, lisp mode, and related commands.  Vi macros are
            limited to single character macro names.
          UUUUnnnniiiimmmmpppplllleeeemmmmeeeennnntttteeeedddd eeeemmmmaaaaccccssss ccccoooommmmmmmmaaaannnnddddssss

            M-^M    mails the current buffer
            M-^Z    suspends emacs
            M-s     gives EMACS statistics
            M-t     prompts for terminal type
            M-z     files an electronic trouble report
            ^X^G    sends an interrupt signal to a sub-process in the current buffer
            ^X^V    puts the current version on the kill stack.
            ^X'     loads a new character type definition
            ^XL     loads a compressed output file description
            ^Xk     sets the encryption key for file reading and writing

          UUUUnnnniiiimmmmpppplllleeeemmmmeeeennnntttteeeedddd eeeemmmmaaaaccccssss EEEEMMMMLLLL ffffoooorrrrmmmmssss

            M-0M-$  sub-process
            M-0^X^E simulate <bit-map>
            M-2^X^Q current-char-type
            M-3^X^Q current-transition
            M-17^X& wait-process
            M-18^X& send-process
            M-19^X& read-process

          UUUUnnnniiiimmmmpppplllleeeemmmmeeeennnntttteeeedddd eeeemmmmaaaaccccssss mmmmooooddddeeeessss
            7bit_ascii, backup_copy, compressed_output,
            display_percent, eofnl, height, left_margin,
            local_echo, mailtype, nodelete, picture, savelink,
            smoothscroll, time, and tspeed
          MMMMiiiisssscccceeeellllllllaaaannnneeeeoooouuuussss
            -i and .i command line options
            EMACS_MODES setting string in a file
            macro hooks
          DDDDiiiiffffffffeeeerrrreeeennnncccceeeessss FFFFrrrroooommmm tttthhhheeee RRRReeeeaaaallll vvvviiii
            The four bottom screen lines are used for messages,
            unlike the single line in _v_i.

            The uuuu command accepts a count of the number of changes
            to undo/redo.





       Page 23                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


            The _r_e_g_c_m_p(3X) ++++ operator is recognized in regular
            expressions.

            The definition of a word includes the backspace
            character.

            The _i_g_n_o_r_e_c_a_s_e option affects all letters in a regular
            expression unlike _v_i, where it does not affect
            character classes, e.g. [[[[AAAA----ZZZZ]]]].
          DDDDiiiiffffffffeeeerrrreeeennnncccceeeessss FFFFrrrroooommmm tttthhhheeee RRRReeeeaaaallll eeeemmmmaaaaccccssss
            The argument to the MMMM----uuuu command is the number of
            changes to undo/redo.

            MMMM----wwww switches to a ._w_a_l_l_c_h_a_r_t buffer instead of writing
            into the current buffer if the current file is a
            versioned file.

            The pseudo-last-line of the file is not displayed, so
            MMMM---->>>> goes to the end of the last real line.

            Some messages are displayed at the bottom of the screen
            instead of overwriting the top displayed lines.

            When the screen is updated, the middle line is not
            updated first.

            The MMMM----!!!! command does not clear the screen before the
            shell command is executed.

            The |||| operator is not recognized in regular
            expressions.

            The definition of a word does not include the @@@@ and ````
            characters.

            The ^^^^SSSS command cannot search for a newline character.

            The MMMM----rrrr command does not recognize \\\\nnnn as a replacement
            newline character.

            Changing the height, leftmargin, nodelete, picture, and
            width modes has no effect because they were only
            implemented to be read by macros.
          OOOOtttthhhheeeerrrr lllliiiimmmmiiiittttaaaattttiiiioooonnnnssss
            If you use eeeemmmmaaaaccccsssstttteeeerrrrmmmm////vvvviiiitttteeeerrrrmmmm(EXPTOOLS) and double click
            mouse button 1 to mark a word, the word highlighting
            sometimes disappears so that typing character to
            replace the highlighted word does not work.

       SSSSEEEEEEEE AAAALLLLSSSSOOOO
            SDS-ECMS commands:



       Page 24                             (printed 4/19/93)








       VVVVEEEE((((1111))))                    ((((EEEEXXXXPPPPTTTTOOOOOOOOLLLLSSSS))))                    VVVVEEEE((((1111))))


            eeeeddddggggeeeetttt(1), eeeeddddppppuuuutttt(1), eeeexxxxttttrrrraaaacccctttt(1), mmmmrrrrddddeeeepppp(1), rrrreeeeppppoooorrrrtttt(1),
            ssssggggeeeetttt(1), uuuunnnneeeeddddggggeeeetttt(1), uuuunnnneeeeddddppppuuuutttt(1), xxxxttttaaaammmm(1)

            SABLIME commands:
            eeeeddddggggeeeetttt(1), eeeeddddppppuuuutttt(1), rrrreeeeppppoooorrrrtttt(1), ssssggggeeeetttt(1), uuuunnnneeeeddddggggeeeetttt(1)

            Standard UNIX commands:
            aaaaddddmmmmiiiinnnn(1), ddddeeeellllttttaaaa(1), ggggeeeetttt(1)

       RRRREEEEFFFFEEEERRRREEEENNNNCCCCEEEESSSS
            Version Environment User Guide
            (Use ttttoooooooollllmmmmaaaannnn vvvveeee____ddddoooocccc to get this document.)

       PPPPRRRROOOOVVVVIIIIDDDDEEEERRRRSSSS
            David Atkins, att!research!dla







































       Page 25                             (printed 4/19/93)




