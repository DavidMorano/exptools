#ifdef alliant
/* C++ Definitions of FX/C vector library
 *
 * Dec. 15, 1987 By Brent Townshend  (..!alice!bst)
 *
 * - added stride versions of vector routines
 * Oct. 13, 1988 Bob Safranek (..!alice!rjs)
 *
 * - added unsigned char ops Nov 3, 1988 bst
 *
 * Predefine NOTRIOPS to eliminate 3 operand instructions for faster compile
 */

/* Macros to make definitions easier */
#include "veclib.h"

#define MONADIC(OP,COP,SIGN,TYPE,TCHAR)  \
inline void COP(SIGN TYPE *result,const SIGN TYPE *op1,int n)  \
{ \
    vec_/**/TCHAR/**/OP((TYPE *)result,(const TYPE *)op1,n); \
} \
inline void COP(SIGN TYPE *result,const SIGN TYPE *op1,int n,int rs, int ops)  \
{ \
    vec_/**/TCHAR/**/OP/**/_s((TYPE *)result,(const TYPE *)op1,n,rs,ops); \
}


#define MONADICVS(OP,COP,SIGN,TYPE,TCHAR)  \
inline void COP(SIGN TYPE *result,TYPE op1,int n)  \
{ \
    vec_/**/TCHAR/**/OP((TYPE *)result,op1,n); \
} \
inline void COP(SIGN TYPE *result,TYPE op1, int n, int rs)  \
{ \
    vec_/**/TCHAR/**/OP/**/_s((TYPE *)result,op1,n,rs); \
}

#define MONADICRED(OP,COP,SIGN,TYPE,TCHAR)  \
inline TYPE COP(const SIGN TYPE *op1,int n)  \
{ \
    TYPE result; \
    vec_/**/TCHAR/**/OP(result,(const TYPE *)op1,n); \
    return(result); \
} \
inline TYPE COP(const SIGN TYPE *op1, int n, int ops)  \
{ \
    TYPE result; \
    vec_/**/TCHAR/**/OP/**/_s(result,(const TYPE *)op1,n,ops); \
    return(result); \
}

#define DYADICRED(OP,COP,SIGN,TYPE,TCHAR)  \
inline TYPE COP(const SIGN TYPE *op1,const SIGN TYPE *op2,int n)  \
{ \
    TYPE result; \
    vec_/**/TCHAR/**/OP(result,(const TYPE *)op1,(const TYPE *)op2,n); \
    return(result); \
} \
inline TYPE COP(const SIGN TYPE *op1,const SIGN TYPE *op2,int n, int op1s, int op2s)  \
{ \
    TYPE result; \
    vec_/**/TCHAR/**/OP/**/_s(result,(const TYPE *)op1,(const TYPE *)op2,n,op1s,op2s); \
    return(result); \
}

#define DYADIC1(OP,COP,SIGN,TYPE,RSIGN,RTYPE,TCHAR,VECS,T1,T2)  \
inline void COP(RSIGN RTYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2,int n)  \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS((RTYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,n); \
} \
inline void COP(RSIGN RTYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2,int n, \
		int rs, int op1s, int op2s)  \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s((RTYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,n,rs,op1s,op2s); \
}

#define DYADIC2(OP,COP,SIGN,TYPE,RSIGN,RTYPE,TCHAR,VECS,T1,T2)  \
inline void COP(RSIGN RTYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2,int n)  \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS((RTYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,n); \
} \
inline void COP(RSIGN RTYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2, \
	int n, int rs, int ops) \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s((RTYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,n,rs,ops); \
}

#define DYADIC(OP,COP,SIGN,TYPE,TCHAR) \
DYADIC1(OP,COP,SIGN,TYPE,SIGN,TYPE,TCHAR,vv,*,*) \
DYADIC2(OP,COP,SIGN,TYPE,SIGN,TYPE,TCHAR,vs,*,) \
DYADIC2(OP,COP,SIGN,TYPE,SIGN,TYPE,TCHAR,sv,,*)

#define DYADICCOMP(OP,COP,SIGN,TYPE,TCHAR) \
DYADIC1(OP,COP,SIGN,TYPE,,int,TCHAR,vv,*,*) \
DYADIC2(OP,COP,SIGN,TYPE,,int,TCHAR,vs,*,) \
DYADIC2(OP,COP,SIGN,TYPE,,int,TCHAR,sv,,*)

#ifndef NOTRIOPS
#define TRIADIC1(OP,COP,SIGN,TYPE,TCHAR,VECS,T1,T2,T3)  \
inline void COP(SIGN TYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2, \
	const SIGN TYPE T3 op3, int n)  \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS((TYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,(const TYPE T3)op3,n); \
} \
inline void COP(SIGN TYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2, \
	const SIGN TYPE T3 op3, int n, int rs, int op1s, int op2s, int op3s)  \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s((TYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,(const TYPE T3)op3,n,rs,op1s,op2s,op3s); \
}

#define TRIADIC2(OP,COP,SIGN,TYPE,TCHAR,VECS,T1,T2,T3)  \
inline void COP(SIGN TYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2, \
	const SIGN TYPE T3 op3, int n)  \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS((TYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,(const TYPE T3)op3,n); \
} \
inline void COP(SIGN TYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2, \
	const SIGN TYPE T3 op3, int n, int rs, int op1s, int op2s)  \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s((TYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,o(const TYPE T3)p3,n,rs,op1s,op2s); \
}

#define TRIADIC3(OP,COP,SIGN,TYPE,TCHAR,VECS,T1,T2,T3)  \
inline void COP(SIGN TYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2, \
	const SIGN TYPE T3 op3, int n)  \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS((TYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,(const TYPE T3)op3,n); \
} \
inline void COP(SIGN TYPE *result,const SIGN TYPE T1 op1,const SIGN TYPE T2 op2, \
	const SIGN TYPE T3 op3, int n, int rs, int ops)  \
{ \
    vec_/**/TCHAR/**/OP/**/_/**/VECS/**/_s((TYPE *)result,(const TYPE T1)op1, \
	(const TYPE T2)op2,(const TYPE T3)op3,n,rs,ops); \
}


#define TRIADIC(OP,COP,SIGN,TYPE,TCHAR) \
TRIADIC1(OP,COP,SIGN,TYPE,TCHAR,vvv,*,*,*) \
TRIADIC2(OP,COP,SIGN,TYPE,TCHAR,vvs,*,*, ) \
TRIADIC2(OP,COP,SIGN,TYPE,TCHAR,vsv,*, ,*) \
TRIADIC2(OP,COP,SIGN,TYPE,TCHAR,svv, ,*,*) \
TRIADIC3(OP,COP,SIGN,TYPE,TCHAR,svs, ,*, ) \
TRIADIC3(OP,COP,SIGN,TYPE,TCHAR,ssv, , ,*)

#define TRIOP(LET1,LET2,CMD1,CMD2) DOALL(TRIADIC,LET1/**/LET2,CMD1/**/_/**/CMD2)

#define TRIOPS(LET,CMD) \
TRIOP(LET,a,CMD,add) \
TRIOP(LET,d,CMD,div) \
TRIOP(LET,m,CMD,mul) \
TRIOP(LET,s,CMD,sub)

#endif NOTRIOPS

#define DOALLINT(TY,OP,COP) \
TY(OP,COP,unsigned,char,b) \
TY(OP,COP,,char,b) \
TY(OP,COP,,short,w) \
TY(OP,COP,,int,l)

#define DOALL(TY,OP,COP) \
DOALLINT(TY,OP,COP) \
TY(OP,COP,,float,s) \
TY(OP,COP,,double,d)

#define DOALLSIGNED(TY,OP,COP) \
TY(OP,COP,,char,b) \
TY(OP,COP,,short,w) \
TY(OP,COP,,int,l) \
TY(OP,COP,,float,s) \
TY(OP,COP,,double,d)

#define DOALLBUTB(TY,OP,COP) \
TY(OP,COP,,short,w) \
TY(OP,COP,,int,l) \
TY(OP,COP,,float,s) \
TY(OP,COP,,double,d)

#define BITOP(TY,CMD) DOALLINT(TY,CMD,CMD)
#define COMP(CMD) DOALLSIGNED(DYADICCOMP,CMD,CMD)
#define UNSIGNEDCOMP(CMD) DOALL(DYADICCOMP,CMD,CMD)

/* Done with macros:  Now the real definitions */

#ifndef NOTRIOPS
TRIOPS(a,add)
TRIOPS(d,div)
TRIOPS(m,mul)
TRIOPS(s,sub)
#endif NOTRIOPS

DOALLBUTB(MONADICRED,maxval,max)
DOALLBUTB(MONADICRED,minval,min)
DOALLBUTB(MONADICRED,prod,prod)
DOALLBUTB(MONADICRED,sum,sum)

DOALLBUTB(MONADIC,abs,abs)
DOALL(MONADIC,mov,mov)
DOALLSIGNED(MONADIC,neg,neg)

DOALLBUTB(DYADICRED,dot,dot)

DOALL(DYADIC,add,add)
DOALL(DYADIC,div,div)
DOALLBUTB(DYADIC,max,max)
DOALLBUTB(DYADIC,min,min)
DOALL(DYADIC,mul,mul)
DOALL(DYADIC,sub,sub)

DOALL(MONADICVS,set,set)

UNSIGNEDCOMP(eq)
COMP(ge)
COMP(gt)
COMP(le)
COMP(lt)
UNSIGNEDCOMP(ne)

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
#undef TRIOP
#undef TRIOPS
#undef BITOP
#undef COMP
#endif alliant
