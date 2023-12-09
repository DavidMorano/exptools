
#ifndef BIGIT_H
#define BIGIT_H

typedef int	Small ;		// Big enough for -2 to 2 
typedef short	Bigit ;		// Big enough for -2*B-1 to 2*B+1
typedef long	BBigit ;	// Big enough for -B*B-B to B*B+B
typedef int	Shift ;

static const int	BITSINBIGIT	= 13 ;
static const int	BITSINDOUBLE	= 56 ;

static const Bigit	B		= 1<<BITSINBIGIT ;
static const Bigit	zero_B		= 0 ;
static const Bigit	one_B		= 1 ;
static const Bigit	two_B		= 2 ;
static const Bigit	four_B		= 4 ;
static const Bigit	eight_B		= 8 ;
static const Bigit	minus1_B	= -1 ;
static const Bigit	Bover2		= B/2 ;
static const Bigit	Bover2minus1	= B/2-1 ;
static const Bigit	Bover4		= B/4 ;
static const Bigit	Bminus1		= B-1 ;
static const Bigit	minusB		= -B ;	
static const Bigit	minusBplus1	= -B+1 ;

static const BBigit	BB		= B ;
static const BBigit	BSQ		= (BB*BB) ;
static const BBigit     BSQover2	= (BB*BB/2) ;
static const BBigit	zero_BB		= 0 ;
static const BBigit	one_BB		= 1 ;
static const BBigit	two_BB		= 2 ;
static const BBigit	four_BB		= 4 ;
static const BBigit	minus1_BB	= -1 ;
static const BBigit	minusBB		= -BB ;

inline BBigit	Btimes(Bigit b) { return BB*BBigit(b) ; }
inline int	isz(Bigit b)	{ return b==0 ; }
inline int	ispos(Bigit b)	{ return b>0 ; }
inline int	isneg(Bigit b)	{ return b>0 ; }
inline int	isz(BBigit b)	{ return b==0 ; }
inline int	ispos(BBigit b)	{ return b>0 ; }
inline int	isneg(BBigit b)	{ return b>0 ; }
		
static const Shift	Bigshift	= 1<<10 ;

Bigit top(BBigit) ;
Bigit bot(BBigit) ;
			// i = B*top(i)+bot(i)
			// -B/2 <= bot(i) <= B/2,

Bigit lowtop(BBigit) ;
Bigit lowbot(BBigit) ;
			// i = B*lowtop(i)+lowbot(i),
			// -B/2 <= lowbot(i) <= B/2

Bigit uptop(BBigit) ;
Bigit upbot(BBigit) ;
			// i = B*uptop(i)+upbot(i)
			//  -B < upbot(i) <= 0

#endif /* recursive include protection */

