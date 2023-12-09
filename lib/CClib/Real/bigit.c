
#include <bigit.h>
#include <assert.h>

Bigit top(register BBigit i)
{
	register Bigit d = i/BB ;
	register BBigit t = d*BB ;

	if ( t < i-BB/2 )	return d+1 ;
	else if ( t > i+BB/2 )	return d-1 ; 
	else			return d ;
	}

Bigit bot(BBigit i)
{
	return i-BB*top(i) ;
	}

Bigit lowtop(BBigit i)
{
	if ( i >= 0 )		return i/BB ;
	else 			return -uptop(-i) ;
	}

Bigit lowbot(BBigit i) 
{
	return i - BB*lowtop(i) ;
	}

Bigit uptop(BBigit i)
{
	if ( i >= 0 ) 		return (i+BB-1)/BB ;
	else			return -lowtop(-i) ;
	}

Bigit upbot(BBigit i)
{
	return i - BB*uptop(i) ;
	}

Bigit approxQ(Bigit n1, Bigit n2)
{
	assert (n2!=0) ;
	if ( n2 < 0 ) {
		n1 = -n1 ;
		n2 = -n2 ;
		}
	if ( n1 >= 0 ) 	return (n1 + n2/2) / n2 ;
	else		return -(-n1 + n2/2) / n2 ;
	}

