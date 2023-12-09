#ifndef NDEBUG
/* version 1.3 2/14/91 Greg Kochanski C++ 2.1 */

# ifndef ASSERT_CPP_H
#  define ASSERT_CPP_H

#  ifndef C
#   define C const
#  endif

#  ifndef STD_H
 typedef short BOOL;	/* Use BOOL for logical variables as a reminder to
						the programmer. */
#  endif

class assert_assert	{
	C char *filename;
	C char *functname;
	int linenum;
	C static char *MARK;
	C static char *EXIT;
	assert_assert();
	void dcheck(C char *) C;
	assert_assert *next, *back;
	static assert_assert *top, *bot;

	public:	/* used by macros */
	int fail(C char *s, int l, C char *f);
	assert_assert(C char *f, int line, C char *funct);
	~assert_assert()	{dcheck(EXIT);top=top->back;top->next=top;}
	void mark(int line) {linenum=line;dcheck(MARK);}

	/* May be called to trace pseudo-stack: */
	static void trace();

	/* Parameters to be set by user: */
	static BOOL desperate;
	static void (*display_msg)(C char *s);
	static void (*terminate)(int);
	};

extern assert_assert assert_tmp_rnmn;
# endif

# undef assert
# undef assert2
# undef ENTER_FCN
# undef MARK_LINE
# if defined(__STDC__)
#  define assert(x) (void)((x) || assert_tmp_rnmn.fail(#x, __LINE__, __FILE__))
#  define assert2(x,y) (void)((x)||((y),assert_tmp_rnmn.fail(#x,__LINE__,__FILE__)))
#  define ENTER_FCN(x)	assert_assert assert_tmp_rnmn(__FILE__, __LINE__, (x))
#  define MARK_LINE	assert_tmp_rnmn.mark(__LINE__)
# else
#  define assert(x) (void)((x) || assert_tmp_rnmn.fail(" x ", __LINE__, __FILE__))
#  define assert2(x,y) (void)((x)||((y),assert_tmp_rnmn.fail(" x ",__LINE__,__FILE__)))
#  define ENTER_FCN(x)	assert_assert assert_tmp_rnmn(__FILE__, __LINE__, (x))
#  define MARK_LINE	assert_tmp_rnmn.mark(__LINE__)
# endif
#else
# undef assert
# undef assert2
# undef ENTER_FCN
# undef MARK_LINE
# define assert(x) /**/
# define assert2(x,y) /**/
# define ENTER_FCN(x)	/**/
# define MARK_LINE	/**/
#endif
