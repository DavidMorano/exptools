


     CCCCCCCC((((1111))))		     UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV (((( ))))			 CCCCCCCC((((1111))))



     NNNNAAAAMMMMEEEE
	  CC - AT&T C++	translator (cfront)

     SSSSYYYYNNNNOOOOPPPPSSSSIIIISSSS
	  CCCCCCCC [[[[ ----EEEE ]]]] [[[[ ----FFFF||||----FFFFcccc ]]]] [[[[ ----ffffssss ]]]] [[[[ ----...._s_u_f_f_i_x ]]]] [[[[ ++++iiii ]]]] [[[[ ++++LLLL	]]]] [[[[ ++++xxxx
	  _f_i_l_e ]]]] [[[[ ++++eeee0000||||++++eeee1111 ]]]] [[[[ ++++dddd ]]]] [[[[ ++++wwww ]]]] [[[[ ++++pppp	]]]] [[[[ ++++aaaa0000||||++++aaaa1111 ]]]] _f_i_l_e ............

     DDDDEEEESSSSCCCCRRRRIIIIPPPPTTTTIIIIOOOONNNN
	  _C_C (capital CC) is the AT&T C++ compiler.  The command uses
	  _c_p_p(1) for preprocessing, _c_f_r_o_n_t for syntax and type
	  checking, and	_c_c(1) for object code generation.

	  For each C++ source file, _C_C creates a temporary file	in
	  /usr/tmp, _f_i_l_e.c, containing the generated C file for
	  compilation with _c_c. The ++++iiii or -._s_u_f_f_i_x options will save a
	  copy of this file in the current directory, with the name
	  _f_i_l_e..c or _f_i_l_e._s_u_f_f_i_x.

	  _C_C takes arguments ending in ....cccc,,,, ....CCCC or ....iiii to be C++ source
	  programs.  ....iiii	files are presumed to be the output of _c_p_p(1).
	  Both ....ssss and ....oooo files are also	accepted by the	_C_C command and
	  passed to _c_c(1).

	  _C_C interprets	the following options:

	  ----EEEE	    Run	only _c_p_p(1) on the C++ source files and	send
		    the	result to standard output.

	  ----FFFF	    Run	only _c_p_p(1) and	_c_f_r_o_n_t on the C++ source
		    files, and send the	result to standard output.

	  ----ffffssss	    See	_f_s(1).

	  ----FFFFcccc	    Like the ----FFFF	option,	but the	output is C source
		    code suitable as a ....cccc file for _c_c(1).

	  ----...._s_u_f_f_i_x  Instead of using standard output for the ----EEEE	,,,, ----FFFF
		    or ----FFFFcccc options, place the output from each ....cccc file
		    on a file with the corresponding ._s_u_f_f_i_x.

	  ++++iiii	    Produce an intermediate ........cccc	C language file	in the
		    current directory.	All "#line" and	other
		    preprocessor directives are	stripped from the
		    file.

	  ++++LLLL	    Generate source line number	information using the
		    format "#line %d" instead of "# %d".

	  ++++xxxx _f_i_l_e   Read a file	of sizes and alignments.  Each line
		    contains three fields: a type name,	the size (in
		    bytes), and	the alignment (in bytes).  This	option
		    is useful for cross	compilations and for porting



     Page 1					     (printed 5/10/90)






     CCCCCCCC((((1111))))		     UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV (((( ))))			 CCCCCCCC((((1111))))



		    the	translator.  See the _A_T&_T _C++ _L_a_n_g_u_a_g_e _S_y_s_t_e_m
		    _R_e_l_e_a_s_e _2._0	_R_e_l_e_a_s_e	_N_o_t_e_s for more information.

	  ++++eeee[[[[00001111]]]]    In older releases of _C_C(1),	a separate "virtual
		    table" was generated in each file containing the
		    definition of a class with virtual functions.
		    This release of _C_C(1) optimizes space by defining
		    only one virtual table per class across an entire
		    program.

		    There are only two rare cases in which the
		    compiler cannot automatically perform this
		    optimization:  (1) A class contains	one or more
		    non-inherited virtual functions, but does not
		    contain at least one non-inherited non-inline
		    non-abstract virtual function; and (2) A class
		    inherits all its virtual functions,	including a
		    virtual destructor.	 In both (1) and (2), the
		    compiler will, as in older releases, generate a
		    separate virtual table in each file	containing the
		    definition of the offending	class.	If the
		    programmer wishes to optimize space, he should
		    either rewrite his program to remove (1) or	(2)
		    (the preferred solution), or use the ++++eeee[[[[00001111]]]]
		    options.

		    ++++eeee1111	causes all virtual tables for classes
		    satisfying (1) or (2) in the file being compiled
		    to be external and defined;	it should be used to
		    compile one	file containing	the definition of the
		    offending classes.	++++eeee0000 causes all virtual tables
		    for	classes	satisfying (1) or (2) in the file
		    being compiled to be external but only declared;
		    it should be used on all other files containing
		    the	definition of the offending classes.

		    Notice that	the ++++eeee[[[[00001111]]]] options are ignored for any
		    classes other than those satisfying	(1) or (2)
		    (since _C_C(1) can automatically perform the
		    optimization in the	other cases).

	  ++++dddd	    Do not expand inline functions.

	  ++++wwww	    Warn about all questionable	constructs.  Without
		    the	++++wwww option, the translator issues warnings only
		    about constructs that are almost certainly
		    problems.

	  ++++pppp	    Disallow all anachronistic constructs.  Ordinarily
		    the	translator warns about anachronistic
		    constructs;	under ++++pppp (for ``pure''), the
		    translator will not	compile	code containing



     Page 2					     (printed 5/10/90)






     CCCCCCCC((((1111))))		     UUUUNNNNIIIIXXXX SSSSyyyysssstttteeeemmmm VVVV (((( ))))			 CCCCCCCC((((1111))))



		    anachronistic constructs, such as ``assignment to
		    this.''  See the _A_T&_T _C++ _L_a_n_g_u_a_g_e _S_y_s_t_e_m _P_r_o_d_u_c_t
		    _R_e_f_e_r_e_n_c_e _M_a_n_u_a_l for a list	of anachronisms.

	  ++++aaaa[[[[00001111]]]]    The	translator can generate	either ANSI C style or
		    ``Classic C'' (also	known as K&R C)	style
		    declarations.  The ++++aaaa option specifies which style
		    of declarations to produce.	 ++++aaaa0000, the default,
		    causes the translator to produce ``Classic C''
		    style declarations.	 The ++++aaaa1111 option	causes the
		    translator to produce ANSI C style declarations.

	  See _l_d(1) for	loader options,	_a_s(1) for assembler options,
	  _c_c(1)	for code generation options, and _c_p_p(1)	for
	  preprocessor options.

     FFFFIIIILLLLEEEESSSS
	  Most of the default pathnames	listed below can be modified
	  by changing environmental variables in CCCCCCCC.

	  file.[Cc]	      input file
	  file..c	      optional cfront output
	  file.o	      object file
	  a.out		      linked output
	  /lib/cpp	 C preprocessor
	  cfront	      C	front end
	  /bin/cc	      C	compiler
	  /lib/libc.a	      standard C library (see _i_n_t_r_o(3))
	  /lib/libC.a	      standard C++ library
	  /lib/lib++.a	      Liberty Corner library
	  /lib/libtask.a      C++ task library
	  /lib/libcomplex.a   C++ complex library
	  /usr/include/CC     standard directory for ####iiiinnnncccclllluuuuddddeeee files

     SSSSEEEEEEEE AAAALLLLSSSSOOOO
	  _c_c(1), _m_o_n_i_t_o_r(3), _p_r_o_f(1), _l_d(1), _c_p_p(1), _a_s(1).
	  Bjarne Stroustrup.  _T_h_e _C++ _P_r_o_g_r_a_m_m_i_n_g _L_a_n_g_u_a_g_e, Addison-
	  Wesley 1986.
	  B. W.	Kernighan and D. M. Ritchie.  _T_h_e _C _P_r_o_g_r_a_m_m_i_n_g
	  _L_a_n_g_u_a_g_e, Prentice-Hall 1978.

     DDDDIIIIAAAAGGGGNNNNOOOOSSSSTTTTIIIICCCCSSSS
	  The diagnostics produced by _C_C itself	are intended to	be
	  self-explanatory.  Occasional	messages may be	produced by
	  the assembler	or loader.  No messages	should be produced by
	  _c_c(1).

     BBBBUUUUGGGGSSSS
	  Some ``used before set'' warnings are	wrong.






     Page 3					     (printed 5/10/90)



