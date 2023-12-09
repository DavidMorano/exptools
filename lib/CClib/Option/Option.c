/*
** C++ command line Option class
** Release 1.0; June 1990
**
** Written using ATT C++ release 2.0.
**  by: Michael C. Block
**      ATT-BL Dept 46243, WH 1A-101
**      (RV: Access Methods Inc)
** ema: att!m.c.block
*/
#include "Option.h"
#include <libc.h>
#include <string.h>
#include <stdio.h>

inline int min(int a, int b) { return (a < b) ? a : b; }

static const char* FloatFormat = "%5.4lf";

static Option* first=0;
static char* arg0=0;
static char single_list[64], sp=0;
static int max_nlen=1;

void
Option_list (Option*)
{
    fprintf (stderr, "Individual options:\n");
    for (Option* x=first; x; x=x->nextp)
      {
	if (x->single_letter_flag ())
	    break;
	x->print ("    ", max_nlen);
      }

    if (x)
      {
	fprintf (stderr, "Combinable options:\n");
	for (; x; x=x->nextp)
	    x->print ("    ", max_nlen);
      }
}

static
Option Help_Me ("?", Option::False, "List known options to stderr", Option_list);

Option*
Option::find_overlap ()
{
    Option* insert_point=NULL;

    for (Option* x=first; x; x=x->nextp)
      {
	int o = ( (type=='B' || x->type=='B')
		&& (*namep=='-' || *namep=='+')
		&& (*x->namep=='-' || *x->namep=='+') ) ? 1 : 0;
	int d = strncmp (x->namep+o, namep+o, min(x->nlen,nlen)-o);
	if (d == 0)
	    fprintf (stderr, "Option: name conflict: %s & %s\n", x->namep, namep);
	if (d < 0  &&  x->single_letter_flag () == single_letter_flag ())
	    insert_point = x;
	if (! x->single_letter_flag () && single_letter_flag ())
	    insert_point = x;
      }
     return insert_point;
}

void
Option::add_option (char* s, char t, char* desc, action* funcp)
{
    nlen = strlen(s);

    if (nlen > max_nlen)
	max_nlen = nlen;

    namep = new char [ nlen+1 ];
    strcpy (namep, s);

    if (desc)
      {
	descp = new char [ strlen(desc) +1 ];
	strcpy (descp, desc);
      }
    else
	descp = 0;

    type = t;
    what_to_do = funcp;

    default_value (Set);

    if ( type=='B' && (*s=='-'||*s=='+') && nlen==2 )
      {
	single_letter_flag (Set);
	single_list[sp++] = s[1];
	single_list[sp] = '\0';
      }
    else
	single_letter_flag (Clear);

    Option* insert_point = find_overlap ();

    if (insert_point != NULL)
      {
	nextp = insert_point->nextp;
	insert_point->nextp = this;
      }
    else
      {
	nextp = first;
	first = this;
      }
}

int
Option::check_single_letter_list (char* argp)
{
    if (*argp != '-'  &&  *argp != '+')
	return 1;

    /* First make sure all letters on list are
    ** single letter on/off switches
    */
    for (char* xc=argp+1; *xc; xc++)
	if ( ! strchr (single_list, *xc) )
	    return 1;

    /* Now set them.
    ** They can start with either - or +.
    ** If the definition of the option (-/+) matches that
    ** given in argp then set the flag to 1 otherwise 0.
    */
    for (; this; this=nextp)
	if ( strchr (argp+1, namep[1]) )
	    set_value (argp, "");

    return 0;
}

int
Option::set_value (char* flag, char* vstr)
{
    int match=1, dummy;
    switch (type)
      {
	case 'B':
		if (*vstr == '\0')
		    val.B = (*flag == *namep) ? True : False;
		else
		    match = sscanf (vstr, "%d%c", &(val.B), &dummy);
		break;
	case 'i':
		match = sscanf (vstr, "%d%c", &(val.i), &dummy);
		break;
	case 'f':
		match = sscanf (vstr, "%f%c", &(val.f), &dummy);
		break;
	case 's':
		if (val.s)
		    delete val.s;
		val.s = new char [ strlen(vstr)+1 ];
		strcpy (val.s, vstr);
		break;
      }
    if (match != 1)
      {
	fprintf (stderr, "%s: bad option value: %s %s\n", arg0, namep, vstr);
	return 1;
      }
    default_value (Clear);

    if (what_to_do)
        (*what_to_do) (this);

    return 0;
}

int
Option::setoption (int argc, char* argv[], int& i)
{
    char* flag = argv[i];

    for (; this; this=nextp)
      {
	if (single_letter_flag ())
	    return check_single_letter_list (flag) ? i : 0;

	if (strncmp (namep, flag, nlen) == 0)
	  {
	    char* vstr = &flag[nlen];

	    if (type != 'B')
	      {
		if (*vstr == '\0')
		    if ((vstr=argv[++i]) == '\0'  ||  i >= argc)
		      {
			i--;
			vstr = &flag[nlen];
		      }
	      }
	    return set_value (flag, vstr) ? i : 0;
	  }
    }
    return i;
}

int
Option_arguments (int argc, char* argv[])
{
    static int i=0;
    if (! arg0)
	arg0 = argv[i=0];

    while (++i < argc)
      {
	if (first->setoption (argc, argv, i) != 0)
	    return i;
      }
    return 0;
}

Option::Option (char* s, Bool value, char* desc, action* funcp)
{
    add_option (s, 'B', desc, funcp);
    val.B = value;
}

Option::Option (char* s, long value, char* desc, action* funcp)
{
    add_option (s, 'i', desc, funcp);
    val.i = value;
}

Option::Option (char* s, float value, char* desc, action* funcp)
{
    add_option (s, 'f', desc, funcp);
    val.f = value;
}

Option::Option (char* s, char* value, char* desc, action* funcp)
{
    add_option (s, 's', desc, funcp);
    if (value)
      {
	val.s = new char [ strlen(value)+1 ];
	strcpy (val.s, value);
      }
    else
	val.s = 0;
}

	/* These next three constructors should not exist.
	** But C++ seems to have trouble promoting
	** (int|char)-=>long and float-=>double
	** without Option::Bool getting in the way.
	*/
Option::Option (char* s, char value, char* desc, action* funcp)
{   add_option (s, 'i', desc, funcp);   val.i = value;   }
Option::Option (char* s, int value, char* desc, action* funcp)
{   add_option (s, 'i', desc, funcp);   val.i = value;   }
Option::Option (char* s, double value, char* desc, action* funcp)
{   add_option (s, 'f', desc, funcp);   val.f = value;   }

Option::~Option ()
{
    if (this != first)
	for (Option* x = first; x; x = x->nextp)
	    if ( x->nextp == this )
	      {
		x->nextp = nextp;
		break;
	      }
    else
	first = nextp;

    delete namep;
    if (descp)
	delete descp;
    if (type == 's' && val.s)
	delete val.s;
}

int
Option::Bvalue ()
{
    if (type == 'B')
	return val.B;

    return given ();
}

int
Option::Bvalue (int i)
{
    int old = Bvalue ();
    switch (type)
      {
	case 'i':
	    val.i = i;
	    break;

	case 'B':
	    val.B = i ? True : False;
	    break;

	case 'f':
	    val.f = i;
	    break;

	case 's':
	    if (val.s)
		delete val.s;
	    val.s = new char[ 8 ];
	    strcpy (val.s, i ? "True" : "False");
	    break;
      }
    default_value (Clear);
    return old;
}

long
Option::ivalue ()
{
    switch (type)
      {
	case 'i': return val.i;
	case 'B': return long (val.B);
	case 'f': return long (val.f);
	case 's': return atoi (val.s);
      }
    return 0;
}

long
Option::ivalue (long i)
{
    char buf[32];
    long old = ivalue ();

    switch (type)
      {
	case 'i':
	    val.i = i;
	    break;

	case 'B':
	    val.B = i ? True : False;
	    break;

	case 'f':
	    val.f = i;
	    break;

	case 's':
	    if (val.s)
		delete val.s;
	    sprintf (buf, "%ld", i);
	    val.s = new char[ strlen(buf)+1 ];
	    strcpy (val.s, buf);
	    break;
      }
    default_value (Clear);
    return old;
}

double
Option::fvalue ()
{
    switch (type)
      {
	case 'i': return double (val.i);
	case 'B': return double (val.B);
	case 'f': return val.f;
	case 's': return atof (val.s);
      }
    return 0;
}

double
Option::fvalue (double f)
{
    char buf[32];
    double old = fvalue ();

    switch (type)
      {
	case 'i':
	    val.i = long(f);
	    break;

	case 'B':
	    val.B = f ? True : False;
	    break;

	case 'f':
	    val.f = f;
	    break;

	case 's':
	    if (val.s)
		delete val.s;
	    sprintf (buf, FloatFormat, f);
	    val.s = new char[ strlen(buf)+1 ];
	    strcpy (val.s, buf);
	    break;
      }
    default_value (Clear);
    return old;
}

char*
Option::svalue ()
{
    static char buf[64];

    switch (type)
      {
	case 'i':
	    sprintf (buf, "%ld", val.i);
	    break;

	case 'B':
	    sprintf (buf, val.i ? "True" : "False");
	    break;

	case 'f':
	    sprintf (buf, FloatFormat, val.f);
	    break;

	case 's':
	    return val.s;
      }
    return buf;
}

char*
Option::svalue (char* s)
{
    static char old [128];
    strcpy (old, svalue ());

    switch (type)
      {
	case 'i':
	    val.i = 0;
	    sscanf (s, "%d", &val.i);
	    break;

	case 'B':
	    val.B = ( (*s == 'T') || (*s == 't') ) ? True : False;
	    break;

	case 'f':
	    val.i = 0;
	    sscanf (s, FloatFormat, &val.f);
	    break;

	case 's':
	    if (val.s)
		delete val.s;
	    val.s = new char[ strlen(s)+1 ];
	    strcpy (val.s, s);
	    break;
    }
    default_value (Clear);
    return old;
}

void
Option::print (char* tag, int len)
{
    char fmt[16];

    sprintf (fmt, "%%s%%%ds ", len);
    fprintf (stderr, fmt, tag, namep);

    switch (type)
      {
	case 'i':
	    fprintf (stderr, "(integer) %s [%d]", description (), val.i);
	    break;

	case 'B':
	    fprintf (stderr, "(Boolean) %s [%s]", description (), val.B?"True":"False");
	    break;

	case 'f':
	    fprintf (stderr, "(float) %s [%f]", description (), val.f);
	    break;

	case 's':
	    fprintf (stderr, "(string) %s [%s]", description (), val.s?val.s:"<nil>");
	    break;
      }
    fprintf (stderr, "\n");
}
