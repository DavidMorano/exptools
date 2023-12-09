/*	ctrace - C program debugging tool
 *
 *	run-time package of trace functions
 */

/* RISC machines may need to use varargs */
#if hp9000s800 || sparc
#define	V_CT_
#endif

#ifdef V_CT_
/* still get a syntax error if -P is used on file including varargs.h */
#ifndef va_dcl
#include <varargs.h>
#endif
#endif

#ifndef S_CT_TYPE	/* be compatible with old ctrace */
#define S_CT_TYPE int
#endif

#ifndef isprint
#include <ctype.h>
#endif

#define M_CT_	""	/* mark was " \b" for obsolete tool tlimit */

#ifndef B_CT_

/* signal catching function used by u_ct_ */
static jmp_buf sj_ct_;
static
f_ct_()
{
	longjmp(sj_ct_, 1);
}
#endif

#ifdef LM_CT_
#define I_CT_(x)	((x + LM_CT_) % LM_CT_)

/* global data used by loop detection code */
static	int	ts_ct_;	/* trace state */
#endif

/* global data used by duplicate variable trace code */
static	int	vc_ct_;	/* var trace count within statement */

static	struct	{	/* var values within statement */
	char	*vn_ct_;	/* var name */
	int	vt_ct_;		/* var type (0 is string, > 0 is size) */
	union	{		/* var value */
		char	*vs_ct_;/* string */
		int	vi_ct_;	/* int */
		long	vl_ct_;	/* long */
		double	vd_ct_;	/* double */
	} vv_ct_;
} v_ct_[VM_CT_];

/* trace on/off control */
S_CT_	int	tr_ct_ = 1;

S_CT_
ctron()
{
	tr_ct_ = 1;
	t_ct_("\n    ctron();");	/* suppress "ctron();" in loops */
}

S_CT_
ctroff()
{
	tr_ct_ = 0;
}
/* print the statement text */

S_CT_
t_ct_(text)
register char	*text;
{
#ifdef LM_CT_
	static	int	loop_start;
	static	int	next_stmt;
	static	char	*stmt[LM_CT_];
	static	long	loops;
	register int	i;
	register char	*s;
	register char	c;
	S_CT_TYPE	s_ct_();
#endif

	/* return if tracing is off */
	if (!tr_ct_) {
		return;
	}
#ifdef LM_CT_
	if (ts_ct_ == 2)	/* if not tracing */
		if ((s = stmt[next_stmt]) != (char *) 0 &&
		    strcmp(text, s) == 0) {
			if (strcmp(text, stmt[loop_start]) == 0) {
				++loops;
				if (loops % 1000 == 0)
					PF_CT_"%s\n\r    /* still repeating after %ld times */%s", M_CT_, loops, M_CT_);
				next_stmt = loop_start;
			}
			next_stmt = I_CT_(next_stmt + 1);
			vc_ct_ = 0;	/* reset the var count */
			return;
		}
		else {	/* doesn't match next statement */
			PF_CT_"%s\n\r    /* repeated ", M_CT_);
			if (loops == 0)
				PF_CT_"< 1 time");
			else
				PF_CT_"%ld times", loops);
			PF_CT_" */%s", M_CT_);
			loops = 0;
			PF_CT_"%s%s%s", M_CT_, stmt[I_CT_(next_stmt - 1)], M_CT_); /* print last statement */
			ts_ct_ = 4;	/* force var printing */
			for (i = 0; i < vc_ct_; ++i) { /* print its vars */
				int	j = v_ct_[i].vt_ct_;
				
				if (j == 0) /* string? */
					s_ct_(v_ct_[i].vn_ct_, v_ct_[i].vv_ct_.vs_ct_); /* yes */
				else if (j == sizeof(int))
					u_ct_(v_ct_[i].vn_ct_, j, v_ct_[i].vv_ct_.vi_ct_);
				else if (j == sizeof(long))
					u_ct_(v_ct_[i].vn_ct_, j, v_ct_[i].vv_ct_.vl_ct_);
				else if (j == sizeof(char *))	/* rtcc pointer */
					u_ct_(v_ct_[i].vn_ct_, j, v_ct_[i].vv_ct_.vs_ct_);
				else	/* double */
					u_ct_(v_ct_[i].vn_ct_, j, v_ct_[i].vv_ct_.vd_ct_);
			}
			ts_ct_ = 0;	/* start tracing */
		}
#endif
	vc_ct_ = 0;	/* reset the var count */

#ifdef LM_CT_
	if (ts_ct_ == 0) {	/* if looking for the start of a loop */
		/* if statement in list */
		for (i = I_CT_(next_stmt - 2); i != I_CT_(next_stmt - 1); i = I_CT_(i - 1))
			if ((s = stmt[i]) != (char *) 0 &&
			    strcmp(text, s) == 0 &&	/* if text matches */
			    (c = s[strlen(s) - 1]) != '{' && c != '}') { /* and is not a brace */
				ts_ct_ = 1;	/* look for the loop end */
				loop_start = i;
				next_stmt = I_CT_(loop_start + 1);
				goto print_stmt;
			}
	}
	else	/* if looking for the loop end */
		if (strcmp(text, stmt[loop_start]) == 0) { /* if start stmt */
			ts_ct_ = 2;			/* stop tracing */
			PF_CT_"%s\n\r    /* repeating */%s", M_CT_, M_CT_);
			stmt[next_stmt] = text;	/* save as end marker */
			next_stmt = I_CT_(loop_start + 1);
			return;
		}
		/* if not next stmt */
		else if ((s = stmt[next_stmt]) == (char *) 0 || strcmp(text, s) != 0)
			ts_ct_ = 0; /* look for the start of a loop */
	stmt[next_stmt] = text;	/* save this statement */
	next_stmt = I_CT_(next_stmt + 1); /* inc the pointer */
print_stmt:
#endif
	/* goto the beginning of the line even if in raw mode */
	if (text[0] == '\n') {
		PF_CT_"\r");
	}
	PF_CT_"%s%s%s", M_CT_, text, M_CT_); /* print this statement */
#ifndef B_CT_
	fflush(stdout);		/* flush the output buffer */
#endif
}
/* dump a string variable */

S_CT_
S_CT_TYPE
s_ct_(name, value)
char	*name;
char	*value;
{
	/* return if tracing is off */
	if (!tr_ct_) {
		return((S_CT_TYPE) value);
	}
#ifdef LM_CT_
	/* save the var name and value */
	if (ts_ct_ != 4) {	/* if not forcing var printing */
		v_ct_[vc_ct_].vn_ct_ = name;
		v_ct_[vc_ct_].vt_ct_ = 0;	/* var type is string */
		v_ct_[vc_ct_].vv_ct_.vs_ct_ = value;
		++vc_ct_;
	}
	if (ts_ct_ == 2)	/* if not tracing */
		return((S_CT_TYPE) value);
#endif
	/* print the variable name */
	PF_CT_"%s\n\r    %s == ", M_CT_, name);

	/* check for a null value */
	if (value == 0) {
		PF_CT_"0 */%s", M_CT_);
	}
	else {	/* flush before printing the string because it may cause an
		   abort if it is not null terminated */
#ifndef B_CT_
		fflush(stdout);
#endif
		PF_CT_"\"%s\" */%s", value, M_CT_);
	}
#ifndef B_CT_
	fflush(stdout);
#endif
	return((S_CT_TYPE) value);
}
/* dump an integer variable */

S_CT_
i_ct_(name, value)
char	*name;
register int	value;
{
	register int	i;
	register char	c;

	/* return if tracing is off */
	if (!tr_ct_) {
		return(value);
	}
#ifdef LM_CT_
	if (ts_ct_ != 4) {	/* if not forcing var printing */
#endif
		/* don't dump the variable if its value is the same */
		for (i = 0; i < vc_ct_; ++i)
			if (sizeof(int) == v_ct_[i].vt_ct_ && 
			    value == v_ct_[i].vv_ct_.vi_ct_ &&
			    strcmp(name, v_ct_[i].vn_ct_) == 0)
				return(value);
	
		/* save the var name and value */
		v_ct_[vc_ct_].vn_ct_ = name;
		v_ct_[vc_ct_].vt_ct_ = sizeof(int);
		v_ct_[vc_ct_].vv_ct_.vi_ct_ = value;
		++vc_ct_;
#ifdef LM_CT_
	}

	if (ts_ct_ == 2)	/* if not tracing */
		return(value);
#endif
	/* determine the variable type and print it */
	PF_CT_"%s\n\r    %s == ", M_CT_, name);
	PF_CT_"%d", value);	/* decimal */
#ifdef O_CT_
	if ((unsigned) value > 7)	/* octal */
		PF_CT_" or 0%o", value);
#endif
#ifdef X_CT_
	if ((unsigned) value > 9)	/* hexadecimal */
		PF_CT_" or 0x%x", value);
#endif
#ifdef U_CT_
	if (value < 0)			/* unsigned */
		PF_CT_" or %u", value);
#endif
	if ((unsigned) value <= 255) /* character */
		if (isprint(value))
			PF_CT_" or '%c'", value);
		else if (iscntrl(value)) {
			switch (value) {
				case '\n': c = 'n'; break;
				case '\t': c = 't'; break;
				case '\b': c = 'b'; break;
				case '\r': c = 'r'; break;
				case '\f': c = 'f'; break;
				case '\v': c = 'v'; break;
				default:   c = '\0';
			}
			if (c != '\0')
				PF_CT_" or '\\%c'", c);
		}
	PF_CT_" */%s", M_CT_);
#ifndef B_CT_
	fflush(stdout);
#endif
	return(value);
}
/* dump a variable of an unknown type (cannot return its value) */

S_CT_
#ifdef V_CT_
u_ct_(va_alist)
va_dcl
#else
u_ct_(name, _size, value)	/* size is a macro in <macros.h> */
char	*name;
register int	_size;
union {
	char	*p;
	int	i;
	long	l;
	double	d;
} value;
#endif
{
	register int	i;
	register char	*s;
	register char	c;
#ifdef V_CT_
	va_list ap;
	char	*name;
	register int	_size;
	union {
		char	*p;
		int	i;
		long	l;
		double	d;
	} value;
#endif
	/* return if tracing is off */
	if (!tr_ct_) {
		return;
	}
#ifdef V_CT_
	va_start(ap);
	name = va_arg(ap, char *);
	_size = va_arg(ap, int);
#endif
	/* normalize the size (pointer and float are the same size as either int or long) */
	if (_size == sizeof(char) || _size == sizeof(short))
		_size = sizeof(int);
	else if (_size != sizeof(int) && _size != sizeof(long) && _size != sizeof(double))
		/* this is an extern pointer (size=0), or array or struct address */
		_size = sizeof(char *);
#ifdef V_CT_
	/* assign the union depending on size */
	if (_size == sizeof(int))
		value.i = va_arg(ap, int);
	else if (_size == sizeof(double))
		value.d = va_arg(ap, double);
	else if (_size == sizeof(long))
		value.l = va_arg(ap, long);
	else if (_size == sizeof(char *))
		value.p = va_arg(ap, char *);
	va_end(ap);
#endif
#ifdef LM_CT_
	if (ts_ct_ != 4) {	/* if not forcing var printing */
#endif
		/* don't dump the variable if its value is the same */
		for (i = 0; i < vc_ct_; ++i)
			if (_size == v_ct_[i].vt_ct_ && strcmp(name, v_ct_[i].vn_ct_) == 0)
				if (_size == sizeof(int)) {
					if (value.i == v_ct_[i].vv_ct_.vi_ct_)
						return;
				}
				else if (_size == sizeof(long)) {
					if (value.l == v_ct_[i].vv_ct_.vl_ct_)
						return;
				}
				else /* double */
					if (value.d == v_ct_[i].vv_ct_.vd_ct_)
						return;
	
		/* save the var name and value */
		v_ct_[vc_ct_].vn_ct_ = name;
		v_ct_[vc_ct_].vt_ct_ = _size;
		/* note: sizeof(char *) != sizeof(int) for run-time checking */
		if (_size == sizeof(char *)) {
			v_ct_[vc_ct_].vv_ct_.vs_ct_ = value.p;
		}
		else if (_size == sizeof(int)) {
			v_ct_[vc_ct_].vv_ct_.vi_ct_ = value.i;
		}
		else if (_size == sizeof(long)) {
			v_ct_[vc_ct_].vv_ct_.vl_ct_ = value.l;
		}
		else /* double */
			v_ct_[vc_ct_].vv_ct_.vd_ct_ = value.d;
		++vc_ct_;
#ifdef LM_CT_
	}
	/* return if not tracing */
	if (ts_ct_ == 2)
		return;
#endif
	/* determine the variable type and print it */
	PF_CT_"%s\n\r    %s == ", M_CT_, name);
	if (_size == sizeof(int)) {
		PF_CT_"%d", value.i);		/* decimal */
#ifdef O_CT_
		if ((unsigned) value.i > 7)	/* octal */
			PF_CT_" or 0%o", value.i);
#endif
#ifdef X_CT_
		if ((unsigned) value.i > 9)	/* hexadecimal */
			PF_CT_" or 0x%x", value.i);
#endif
#ifdef U_CT_
		if (value.i < 0)		/* unsigned */
			PF_CT_" or %u", value.i);
#endif
#ifdef E_CT_
		if (_size == sizeof(float))	/* float */
			PF_CT_" or %e", value.i);
#endif
		if ((unsigned) value.i <= 255) /* character */
			if (isprint(value.i))
				PF_CT_" or '%c'", value.i);
			else if (iscntrl(value.i)) {
				switch (value.i) {
					case '\n': c = 'n'; break;
					case '\t': c = 't'; break;
					case '\b': c = 'b'; break;
					case '\r': c = 'r'; break;
					case '\f': c = 'f'; break;
					case '\v': c = 'v'; break;
					default:   c = '\0';
				}
				if (c != '\0')
					PF_CT_" or '\\%c'", c);
			}
	}
	else if (_size == sizeof(long)) {
		PF_CT_"%ld", value.l);		/* decimal */
#ifdef O_CT_
		if ((unsigned) value.l > 7)	/* octal */
			PF_CT_" or 0%lo", value.l);
#endif
#ifdef X_CT_
		if ((unsigned) value.l > 9)	/* hexadecimal */
			PF_CT_" or 0x%lx", value.l);
#endif
#ifdef U_CT_
		if (value.l < 0)		/* unsigned */
			PF_CT_" or %lu", value.l);
#endif
#ifdef E_CT_
		if (_size == sizeof(float))	/* float */
			PF_CT_" or %e", value.l);
#endif
	}
	else if (_size == sizeof(double))	/* double */
		PF_CT_"%e", value.d);

	/* for run-time checking the size of a pointer is 3 times normal size */
	else if (_size == sizeof(char *)) {
		PF_CT_"%u", value.p);		/* unsigned */
#ifdef O_CT_
		if ((unsigned) value.p > 7)	/* octal */
			PF_CT_" or 0%o", value.p);
#endif
#ifdef X_CT_
		if ((unsigned) value.p > 9)	/* hexadecimal */
			PF_CT_" or 0x%x", value.p);
#endif
	}
#ifndef B_CT_
	/* check for a possible non-null pointer */
#if u370 || uts	/* avoid strlen bug that causes printf to print millions of nulls */
	if (_size == sizeof(char *) && value.p != 0 && (unsigned) value.p <= 0xffffff) {
#else
	if (_size == sizeof(char *) && value.p != 0) {
#endif
#if vax || u3b || u370 || uts	/* signal return type changed in SVR3 */
		int	(*signal())(), (*sigbus)(), (*sigsegv)();
#else
		void	(*signal())(), (*sigbus)(), (*sigsegv)();
#endif
		/* see if this is a non-null string */
		if (setjmp(sj_ct_) == 0) {
			sigbus = signal(10, f_ct_);
			sigsegv = signal(11, f_ct_);
			value.p = (char *) (int) value.p;	/* remove rtcc pointer bounds */
			if (*value.p != '\0')
				for (s = value.p; ; ++s) {
					if ((c = *s) == '\0') {
						PF_CT_" or \"%s\"", value.p);
						break;
					}
					/* don't use isspace(3) because \v and others will not print properly */
					if (!isprint(c) && c != '\t' && c != '\n')
						break;	/* not string */
				}
		}
		signal(10, sigbus);
		signal(11, sigsegv);
	}
#endif
	PF_CT_" */%s", M_CT_);
#ifndef B_CT_
	fflush(stdout);
#endif
}
