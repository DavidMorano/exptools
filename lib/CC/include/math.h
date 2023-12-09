/*ident	"@(#)C++env:incl-master/proto-headers/math.h	1.1" */

#ifndef __MATH_H
#define __MATH_H

#define isnan ______isnan
#define iszero ______iszero
#define ilogb ______ilogb
#define irint ______irint
#define signbit ______signbit
#define isinf ______isinf
#define isnan ______isnan
#define isnormal ______isnormal
#define issubnormal ______issubnormal
#define nextafter ______nextafter
#define remainder ______remainder
#define significand ______significand
#define scalbn ______scalbn
#define min_subnormal ______min_subnormal
#define max_subnormal ______max_subnormal
#define min_normal ______min_normal
#define max_normal ______max_normal
#define infinity ______infinity
#define quiet_nan ______quiet_nan
#define signaling_nan ______signaling_nan
#define single ______single
#define asinh ______asinh
#define acosh ______acosh
#define atanh ______atanh
#define atof ______atof
#define exp ______exp
#define expm1 ______expm1
#define log ______log
#define log10 ______log10
#define log1p ______log1p
#define pow ______pow
#define hypot ______hypot
#define cabs ______cabs
#define cbrt ______cbrt
#define sqrt ______sqrt
#define lgamma ______lgamma
#define gamma ______gamma
#define matherr ______matherr
#define fabs ______fabs
#define floor ______floor
#define ceil ______ceil
#define rint ______rint
#define copysign ______copysign
#define drem ______drem
#define logb ______logb
#define scalb ______scalb
#define finite ______finite
#define sinh ______sinh
#define cosh ______cosh
#define tanh ______tanh
#define sin ______sin
#define cos ______cos
#define tan ______tan
#define asin ______asin
#define acos ______acos
#define atan ______atan
#define atan2 ______atan2
#define frexp ______frexp
#define ldexp ______ldexp
#define modf ______modf
#define strtod ______strtod
#define erf ______erf
#define erfc ______erfc
#define j0 ______j0
#define j1 ______j1
#define jn ______jn
#define y0 ______y0
#define y1 ______y1
#define yn ______yn

/*	@(#)math.h 1.23 88/03/03 SMI	*/

/*
 * Copyright (c) 1988 by Sun Microsystems, Inc.
 */

/*
			#include <math.h>

defines all the public functions implemented in libm.a.

*/

#ifndef M_SQRT1_2
#include <floatingpoint.h>		/* Contains definitions for types and 
					   functions implemented in libc.a.	*/

/* 	4.3 BSD functions: math.h	4.6	9/11/85	*/

extern int    finite();
extern double fabs(), floor(), ceil(), rint();
extern double hypot();
extern double copysign();
extern double sqrt();
extern double modf(), frexp();
extern double asinh(), acosh(), atanh();
extern double erf(), erfc();
extern double exp(), expm1(), log(), log10(), log1p(), pow();
extern double lgamma();
extern double j0(), j1(), jn(), y0(), y1(), yn();
extern double sin(), cos(), tan(), asin(), acos(), atan(), atan2();
extern double sinh(), cosh(), tanh();
extern double cbrt();

/*      Sun definitions.        */
 
enum fp_pi_type { 		/* Implemented precisions for trigonometric
				   argument reduction. */
	fp_pi_infinite	= 0,	/* Infinite-precision approximation to pi. */
	fp_pi_66	= 1,	/* 66-bit approximation to pi. */
	fp_pi_53	= 2	/* 53-bit approximation to pi. */
	} ;

extern enum fp_pi_type fp_pi ;  /* Pi precision to use for trigonometric 
				   argument reduction. */

/*	Functions callable from C, intended to support IEEE arithmetic.	*/

extern enum fp_class_type fp_class() ;
extern int ilogb(), irint(), signbit() ;
extern int isinf(), isnan(), isnormal(), issubnormal(), iszero() ;
extern double nextafter(), remainder() ;
extern double logb(), significand(), scalb(), scalbn();
extern double min_subnormal(), max_subnormal();
extern double min_normal(), max_normal();
extern double infinity(), quiet_nan(), signaling_nan();

/*	Functions callable from C, intended to support Fortran.		*/

extern double log2(), exp10(), exp2(), aint(), anint() ;
extern int nint() ;
extern void   sincos();

/* 	Sun FUNCTIONS for C Programmers for IEEE floating point. */

extern int ieee_flags ();
extern int ieee_handler ();

/*	Single-precision functions callable from Fortran, Pascal, Modula-2, etc.,
	take float* arguments instead of double and
	return FLOATFUNCTIONTYPE results instead of double.
	RETURNFLOAT is used to return a float function value without conversion to
	double.
	ASSIGNFLOAT is used to get the float value out of a FLOATFUNCTIONTYPE result.
	We don't want you to have to think about -fsingle2. 	*

	Some internal library functions pass float parameters as 32-bit values,
	disguised as FLOATPARAMETER.  FLOATPARAMETERVALUE(x) extracts the
	float value from the FLOATPARAMETER.
*/

/*	mc68000 returns float results in d0, same as int	*/

#ifdef mc68000
#define FLOATFUNCTIONTYPE	int
#define RETURNFLOAT(x) 		return (*(int *)(&(x)))
#define ASSIGNFLOAT(x,y)	*(int *)(&x) = y
#endif

/*	sparc returns float results in %f0, same as top half of double	*/

#ifdef sparc
#define FLOATFUNCTIONTYPE	double
#define RETURNFLOAT(x) 		{ union {double _d ; float _f } _kluge ; _kluge._f = (x) ; return _kluge._d ; }
#define ASSIGNFLOAT(x,y)	{ union {double _d ; float _f } _kluge ; _kluge._d = (y) ; x = _kluge._f ; }
#endif

/*	i386 returns float results on stack as extendeds, same as double */

#ifdef i386
#define FLOATFUNCTIONTYPE	float
#define RETURNFLOAT(x) 		return (x)
#define ASSIGNFLOAT(x,y)	x = y
#endif

/*	So far everybody passes float parameters as 32 bits on stack, same as int.	*/

#define FLOATPARAMETER		int
#define FLOATPARAMETERVALUE(x)	(*(float *)(&(x)))

extern int    ir_finite_();
extern FLOATFUNCTIONTYPE r_fabs_(), r_floor_(), r_ceil_(), r_rint_();
extern FLOATFUNCTIONTYPE r_hypot_();
extern FLOATFUNCTIONTYPE r_copysign_();
extern FLOATFUNCTIONTYPE r_sqrt_();
extern FLOATFUNCTIONTYPE r_asinh_(), r_acosh_(), r_atanh_();
extern FLOATFUNCTIONTYPE r_erf_(), r_erfc_();
extern FLOATFUNCTIONTYPE r_exp_(), r_expm1_(), r_log_(), r_log10_(), r_log1p_();
extern FLOATFUNCTIONTYPE r_pow_();
extern FLOATFUNCTIONTYPE r_lgamma_();
extern FLOATFUNCTIONTYPE r_j0_(), r_j1_(), r_jn_(), r_y0_(), r_y1_(), r_yn_();
extern FLOATFUNCTIONTYPE r_sin_(), r_cos_(), r_tan_(), r_asin_(), r_acos_();
extern FLOATFUNCTIONTYPE r_atan_(), r_atan2_();
extern FLOATFUNCTIONTYPE r_sinh_(), r_cosh_(), r_tanh_();
extern FLOATFUNCTIONTYPE r_cbrt_();
extern int ir_ilogb_(), ir_irint_(), ir_signbit_() ;
extern int ir_isinf_(), ir_isnan_(), 
	   ir_issubnormal_(), ir_isnormal_(), ir_iszero_() ;
extern enum fp_class_type ir_fp_class_();
extern FLOATFUNCTIONTYPE r_nextafter_(), r_remainder_() ;
extern FLOATFUNCTIONTYPE r_log2_(), r_exp10_(), r_exp2_(), r_aint_(), r_anint_() ;
extern int ir_nint_() ;
extern FLOATFUNCTIONTYPE r_fmod_();
extern FLOATFUNCTIONTYPE r_logb_(), r_significand_(), r_scalb_(), r_scalbn_();
extern FLOATFUNCTIONTYPE r_min_subnormal_(), r_max_subnormal_();
extern FLOATFUNCTIONTYPE r_min_normal_(), r_max_normal_();
extern FLOATFUNCTIONTYPE r_infinity_(), r_quiet_nan_(), r_signaling_nan_();
extern void r_sincos_();

/* 	Constants, variables, and functions from System V */

#define _ABS(x) ((x) < 0 ? -(x) : (x))

#define	HUGE_VAL	(infinity())	/* Produces IEEE Infinity. */
#define	HUGE		(infinity())	/* For historical compatibility. */

#define DOMAIN          1
#define SING            2
#define OVERFLOW        3
#define UNDERFLOW       4
#define TLOSS           5
#define PLOSS           6

struct exception {
        int type;
        char *name;
        double arg1;
        double arg2;
        double retval;
};

extern int signgam;

extern double fmod();
extern int matherr();

/* First three have to be defined exactly as in values.h including spacing! */

#define M_LN2	0.69314718055994530942
#define M_PI	3.14159265358979323846
#define M_SQRT2	1.41421356237309504880

#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN10		2.30258509299404568402
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT1_2	0.70710678118654752440
#define _POLY1(x, c)    ((c)[0] * (x) + (c)[1])
#define _POLY2(x, c)    (_POLY1((x), (c)) * (x) + (c)[2])
#define _POLY3(x, c)    (_POLY2((x), (c)) * (x) + (c)[3])
#define _POLY4(x, c)    (_POLY3((x), (c)) * (x) + (c)[4])
#define _POLY5(x, c)    (_POLY4((x), (c)) * (x) + (c)[5])
#define _POLY6(x, c)    (_POLY5((x), (c)) * (x) + (c)[6])
#define _POLY7(x, c)    (_POLY6((x), (c)) * (x) + (c)[7])
#define _POLY8(x, c)    (_POLY7((x), (c)) * (x) + (c)[8])
#define _POLY9(x, c)    (_POLY8((x), (c)) * (x) + (c)[9])

/* 	
	Deprecated functions for compatibility with past.  
	Changes planned for future.
*/

extern double cabs();	/* Use double hypot(x,y)
			   Traditional cabs usage is confused - 
			   is its argument two doubles or one struct?	*/
extern double drem();	/* Use double remainder(x,y)
			   drem will disappear in a future release.	*/
extern double gamma();	/* Use double lgamma(x)
			   to compute log of gamma function.
			   Name gamma is reserved for true gamma function
			   to appear in a future release.  		*/
extern double ldexp();	/* Use double scalbn(x,n)
			   ldexp may disappear in a future release	*/

#endif
 

#undef max_subnormal
#undef irint
#undef significand
#undef remainder
#undef signbit
#undef j0
#undef j1
#undef matherr
#undef sqrt
#undef cabs
#undef fabs
#undef ceil
#undef hypot
#undef quiet_nan
#undef gamma
#undef jn
#undef erfc
#undef erf
#undef scalb
#undef signaling_nan
#undef min_normal
#undef iszero
#undef y0
#undef log10
#undef isnormal
#undef y1
#undef atan2
#undef atan
#undef logb
#undef max_normal
#undef strtod
#undef modf
#undef acos
#undef log
#undef tan
#undef lgamma
#undef drem
#undef atanh
#undef infinity
#undef cos
#undef ilogb
#undef copysign
#undef atof
#undef acosh
#undef asin
#undef tanh
#undef cbrt
#undef scalbn
#undef nextafter
#undef cosh
#undef sin
#undef yn
#undef asinh
#undef log1p
#undef exp
#undef sinh
#undef isinf
#undef isnan
#undef finite
#undef ldexp
#undef expm1
#undef pow
#undef single
#undef rint
#undef floor
#undef min_subnormal
#undef frexp
#undef issubnormal

extern "C" {
	double acos(double);
	double asin(double);
	double atan(double);
	double atan2(double, double);
	double atof(const char*);
	double ceil(double);
	double cos(double);
	double cosh(double);
	double erf(double);
	double erfc(double);
	double exp(double);
	double fabs(double);
	double floor(double);
	double frexp(double, int*);
	double gamma(double);
	double hypot(double, double);
	double j0(double);
	double j1(double);
	double jn(int, double);
	double ldexp(double, int);
	double log(double);
	double log10(double);
	double modf(double, double*);
	double pow(double, double);
	double sqrt(double);
	double sin(double);
	double sinh(double);
	double tan(double);
	double tanh(double);
	double y0(double);
	double y1(double);
	double yn(int, double);
	double fmod(double, double);
	int matherr(struct exception*);
	int isnan(double);
	int iszero(double);
	double asinh(double);
	double acosh(double);
	double atanh(double);
	int ilogb(double), irint(double), signbit(double);
	int isinf(double), isnormal(double);
	int issubnormal(double);
	double nextafter(double,double), remainder(double,double);
	double significand(), scalbn(double,int);
	double min_subnormal(), max_subnormal();
	double min_normal(), max_normal();
	double infinity(), quiet_nan(long), signaling_nan(long);
	struct ______complex { double x, y;};
	double cabs(______complex);
	double expm1(double);
	double log1p(double);
	double cbrt(double);
	double lgamma(double);
	double rint(double);
	double copysign(double, double);
	double drem(double, double);
	double logb(double);
	double scalb(double, int);
	int finite(double);
	double strtod(const char*, char**);
}

inline int sqr(int x) {return(x*x);}
inline double sqr(double x) {return(x*x);}

inline int abs(int d) { return (d>0)?d:-d; }
inline double abs(double d) { return fabs(d); }

#ifndef M_PI
#define M_PI	3.14159265358979323846
#endif
#ifndef PI
#define PI M_PI
#endif

#endif
