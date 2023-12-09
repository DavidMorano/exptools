#include "assert_cpp.h"
#include <signal.h>
#include <libc.h> /* for abort */

#define FALSE	0
#define TRUE	(!FALSE)

assert_assert assert_tmp_rnmn("During constructors", 0, "GLOBAL SCOPE");
BOOL assert_assert::desperate = FALSE;
C char * assert_assert::MARK = "MARK:";
C char * assert_assert::EXIT = "EXIT:";
assert_assert *assert_assert::top = 0;
assert_assert *assert_assert::bot = 0;

#define BS	20

static void display_int(int n)
{
 char buf[BS];
 int j;
 C BOOL neg = n<0;
 if(neg)	n = -n;

 buf[j=BS-1] = '\0';
 do	{
	buf[--j] = '0' + n%10;
	n /= 10;
	} while(j>0 && n!=0);
if(neg)	buf[--j] = '-';
 (*assert_assert::display_msg)(&buf[j]);
}

static void
sighandler(int n)
{
 (*assert_assert::display_msg)("SIGNAL ");
 display_int(n);
 (*assert_assert::display_msg)(" CAUGHT\n");
 assert_assert::trace();

 int k;
 for(k=0;k<NSIG;k++)
 	signal(k, SIG_DFL);	/* re-instate default action */

 if(assert_assert::terminate) (*assert_assert::terminate)(128+n);
 else abort();
}


assert_assert::assert_assert(C char *f, int line, C char *funct)
	: filename(f), functname(funct)
{
 if(!top)	{
	int i;
	top=this;
	for(i=0;i<NSIG;i++)
#ifdef SIGABRT
		if(i != SIGABRT)
#endif
			{	/* only catch uncaught signals */
			SIG_TYP tmp = signal(i, sighandler);
			if(tmp != SIG_DFL)
				signal(i, tmp);
			}
	}
 if(!bot)	bot=this;
 linenum = line;
 top->next = this;
 back = top;
 next = this;
 top = this;
 dcheck("ENTER:");
}


void assert_assert::trace()
{
 extern assert_assert assert_tmp_rnmn;
 BOOL go = FALSE;
 C assert_assert *p = bot;
 BOOL corrupt = FALSE;
 if(!display_msg)
	abort();
 do	{
	if(!p || !p->next || !p->back || (p->next!=p && p->next->back!=p)
		|| (p->back!=p && p->back->next!=p) || p->linenum<0)	{
		(*display_msg)("ASSERT TRACE: stack corrupted\n");
		corrupt = TRUE;
		if(!p || (p->back!=p && p->back->next!=p))
			break;
		}
	(*display_msg)(p->filename);
	(*display_msg)(":");
	(*display_msg)(p->functname);
	if(p->linenum != 0)	{
		(*display_msg)(":");
		display_int(p->linenum);
		}
	(*display_msg)("\n");
	go = p->next!=p && p->linenum>=0 && p->next && p!=top;
	p = p->next;
	}	while(go);
 if(corrupt)	{
	(*display_msg)("Assert: attempting backwards stack trace\n");
	p = top;
	do	{
		if(!p || !p->next || !p->back || (p->next!=p && p->next->back!=p)
			|| (p->back!=p && p->back->next!=p) || p->linenum<0)	{
			(*display_msg)("ASSERT TRACE: stack corrupted\n");
			abort();
			}
		(*display_msg)(p->filename);
		(*display_msg)(":");
		(*display_msg)(p->functname);
		if(p->linenum != 0)	{
			(*display_msg)(":");
			display_int(p->linenum);
			}
		(*display_msg)("\n");
		go = p->back!=p && p->linenum>=0 && p!=bot && p->back;
		p = p->back;
		} while(go);
	}
}

static void display_indent(unsigned level)
{
 C static char s1[] = " , |";
 for(;level>=sizeof(s1)-1;level -= (unsigned)(sizeof(s1)-1))
	(*assert_assert::display_msg)(s1);
 C char *p;
 for(p=s1;level>0;level--,p++)	{
	char b[2];
	b[1] = '\0';
	b[0] = *p;
	(*assert_assert::display_msg)(b);
	}
}

void assert_assert::dcheck(C char * s) C
{
 if(desperate)	{
 	if(!display_msg)
		abort();
	int level = -1;
	BOOL corrupt = FALSE;
	{
	unsigned lev = 0;
	C assert_assert *t = top;
	do	{
		if(t == this)
			level = lev;
		if((t->back!=t && t->back->next!=t)
			|| (t->next!=t && t->next->back!=t) || t->linenum<0)	{
			(*display_msg)("Stack corrupted, level=");
			display_int(level);
			(*display_msg)(" at:");
			corrupt = TRUE;
			break;
			}
		lev++;
		} while(t->back!=t && (t=t->back)!=0);
	if(t != bot)	{
		(*display_msg)("Bottom corrupted at:");
		corrupt = TRUE;
		}
	if(level == -1)	{
		(*display_msg)("Stack doesn't include *this at:");
		corrupt = TRUE;
		}
	else level = lev-level;
	}

	if(!corrupt) display_indent(level);

	(*display_msg)(s);
	(*display_msg)(filename);
	(*display_msg)(":");
	(*display_msg)(functname);
	if(linenum != 0)	{
		(*display_msg)(":");
		display_int(linenum);
		}
	(*display_msg)("\n");

	if(corrupt)	{
		(*display_msg)("Stack Trace:\n");
		trace();
		}

	if(corrupt && terminate)	(*terminate)(128);
	else if(corrupt)	abort();
	}
}


int assert_assert::fail(C char *s, int l, C char *f)
{
 if(display_msg)	{
 	(*display_msg)("Assertion failed: ");
	(*display_msg)(s);
	if(l != 0)	{
		(*display_msg)(" Line: ");
		display_int(l);
		}
	(*display_msg)(" File: ");
	(*display_msg)(f);
	(*display_msg)("\n\n");
 	trace();
	}
 if(assert_assert::terminate)
	(*assert_assert::terminate)(1);
 else abort();
 return 0;
}
