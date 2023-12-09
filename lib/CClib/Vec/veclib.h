#ifdef alliant
/* C++ Definitions of FX/C vector library
 *
 * Dec. 15, 1987 By Brent Townshend  (..!alice!bst)
 *
 * - added declarations for stride versions of vector routines
 * Oct. 13, 1988 Bob Safranek (..!alice!rjs)
 *
 * Predefine NOTRIOPS to eliminate 3 operand instructions for faster compile
 */

/* Macros to make definitions easier */

extern "C" {
#define MONADIC(OP,COP,TYPE,TCHAR)  \
    extern void vec_/**/TCHAR/**/OP/**/_s(TYPE*,const TYPE*,int, int, int); \
    extern void vec_/**/TCHAR/**/OP(TYPE*,const TYPE*,int);

#define MONADICVS(OP,COP,TYPE,TCHAR)  \
    extern void vec_/**/TCHAR/**/OP/**/_s(TYPE*,TYPE, int, int); \
    extern void vec_/**/TCHAR/**/OP(TYPE*,TYPE, int);

#define MONADICRED(OP,COP,TYPE,TCHAR)  \
    extern void vec_/**/TCHAR/**/OP/**/_s(TYPE&,const TYPE*,int, int); \
    extern void vec_/**/TCHAR/**/OP(TYPE&,const TYPE*,int);


#define DYADICRED(OP,COP,TYPE,TCHAR)  \
    extern void vec_/**/TCHAR/**/OP/**/_s(TYPE&,const TYPE*,const TYPE *, int, int, int);\
    extern void vec_/**/TCHAR/**/OP(TYPE&,const TYPE*,const TYPE *, int);


/* declarations for "vv" operations */
#define DYADIC1(OP,COP,TYPE,RTYPE,TCHAR,VECS,T1,T2)  \
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s(RTYPE*,\
		const TYPE T1,const TYPE T2, int, int, int, int);\
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS(RTYPE*,const TYPE T1, \
		const TYPE T2, int);

/* declarations for "vs" and "sv" operations -- can have only 2 strides */
#define DYADIC2(OP,COP,TYPE,RTYPE,TCHAR,VECS,T1,T2)  \
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s(RTYPE*, \
		const TYPE T1,const TYPE T2, int, int, int);\
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS(RTYPE*, \
		const TYPE T1,const TYPE T2, int);

#define DYADIC(OP,COP,TYPE,TCHAR) \
DYADIC1(OP,COP,TYPE,TYPE,TCHAR,vv,*,*) \
DYADIC2(OP,COP,TYPE,TYPE,TCHAR,vs,*,) \
DYADIC2(OP,COP,TYPE,TYPE,TCHAR,sv,,*)

#define DYADICCOMP(OP,COP,TYPE,TCHAR) \
DYADIC1(OP,COP,TYPE,int,TCHAR,vv,*,*) \
DYADIC2(OP,COP,TYPE,int,TCHAR,vs,*,) \
DYADIC2(OP,COP,TYPE,int,TCHAR,sv,,*)

#ifndef NOTRIOPS
/* "vvv" routines */
#define TRIADIC1(OP,COP,TYPE,TCHAR,VECS,T1,T2,T3)  \
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s(TYPE*, const TYPE T1, \
		const TYPE T2, const TYPE T3, int, int, int, int, int);\
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS(TYPE*,const TYPE T1, \
		const TYPE T2, const TYPE T3, int);

/* "vvs," "vsv," and "svv" routines */
#define TRIADIC2(OP,COP,TYPE,TCHAR,VECS,T1,T2,T3)  \
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s(TYPE*,const TYPE T1, \
		const TYPE T2, const TYPE T3, int, int, int, int);\
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS(TYPE*,const TYPE T1, \
		const TYPE T2, const TYPE T3, int);

/* "svs," and "ssv" routines */
#define TRIADIC3(OP,COP,TYPE,TCHAR,VECS,T1,T2,T3)  \
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s(TYPE*,const TYPE T1, \
		const TYPE T2, const TYPE T3, int, int, int);\
    extern void vec_/**/TCHAR/**/OP/**/_/**/VECS(TYPE*,const TYPE T1, \
		const TYPE T2, const TYPE T3, int);

#define TRIADIC(OP,COP,TYPE,TCHAR) \
TRIADIC1(OP,COP,TYPE,TCHAR,vvv,*,*,*) \
TRIADIC2(OP,COP,TYPE,TCHAR,vvs,*,*, ) \
TRIADIC2(OP,COP,TYPE,TCHAR,vsv,*, ,*) \
TRIADIC2(OP,COP,TYPE,TCHAR,svv, ,*,*) \
TRIADIC3(OP,COP,TYPE,TCHAR,svs, ,*, ) \
TRIADIC3(OP,COP,TYPE,TCHAR,ssv, , ,*)

#define TRIOP(LET1,LET2,CMD1,CMD2) DOALL(TRIADIC,LET1/**/LET2,CMD1/**/_/**/CMD2)

#define TRIOPS(LET,CMD) \
TRIOP(LET,a,CMD,add) \
TRIOP(LET,d,CMD,div) \
TRIOP(LET,m,CMD,mul) \
TRIOP(LET,s,CMD,sub)

#endif NOTRIOPS

#define DOALLINT(TY,OP,COP) \
TY(OP,COP,char,b) \
TY(OP,COP,short,w) \
TY(OP,COP,int,l)

#define DOALL(TY,OP,COP) \
DOALLINT(TY,OP,COP) \
TY(OP,COP,float,s) \
TY(OP,COP,double,d)

#define DOALLBUTB(TY,OP,COP) \
TY(OP,COP,short,w) \
TY(OP,COP,int,l) \
TY(OP,COP,float,s) \
TY(OP,COP,double,d)

#define BITOP(TY,CMD) DOALLINT(TY,CMD,CMD)
#define COMP(CMD) DOALL(DYADICCOMP,CMD,CMD)

/* Done with macros:  Now the real definitions */

#ifndef NOTRIOPS
TRIOPS(a,add)
TRIOPS(d,div)
TRIOPS(m,mul)
TRIOPS(s,sub)
#endif NOTRIOPS

DOALLBUTB(MONADICRED,maxval,max)
DOALLBUTB(MONADICRED,minval,min)
DOALL(MONADICRED,prod,prod)
DOALL(MONADICRED,sum,sum)

DOALLBUTB(MONADIC,abs,abs)
DOALL(MONADIC,mov,mov)
DOALL(MONADIC,neg,neg)

DOALLBUTB(DYADICRED,dot,dot)

DOALL(DYADIC,add,add)
DOALL(DYADIC,div,div)
DOALLBUTB(DYADIC,max,max)
DOALLBUTB(DYADIC,min,min)
DOALL(DYADIC,mul,mul)
DOALL(DYADIC,sub,sub)

DOALL(MONADICVS,set,set)

COMP(eq)
COMP(ge)
COMP(gt)
COMP(le)
COMP(lt)
COMP(ne)

BITOP(DYADIC,and)
BITOP(DYADIC,eor)
BITOP(DYADIC,eqv)
BITOP(MONADIC,not)
BITOP(DYADIC,or)

#undef MONADIC
#undef MONADICVS
#undef MONADICRED
#undef DYADICRED
#undef DYADICCOMP
#undef DYADIC1
#undef DYADIC2
#undef DYADIC
#undef TRIADIC1
#undef TRIADIC2
#undef TRIADIC3
#undef TRIADIC
#undef DOALLINT
#undef DOALL
#undef DOALLBUTB
#undef TRIOP
#undef TRIOPS
#undef BITOP
#undef COMP
}
#endif alliant
