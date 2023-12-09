#ifndef INLINEH
#define INLINEH

#include "g2mach.h"
#include "g2io.h"

static int gcd(
    int m, 
    int n
){
    int i;

    if(
	m < n
    ){
	return gcd(n,m);
    }
    if(
	i = m %n
    ){
	return gcd(n,i);
    }
    return n;
}
static inline int lcm(
    int m, 
    int n
){ 
    return (m * n)/gcd(m,n);
}
static inline int align(
    int offset, 
    int align
){
    return ((offset)+align-1)/align*align;
}
static inline int alignof(  
    int ival
){
    return(
	ival==LONG_INT_ATTLC ?(
	    LONG_ALIGN_ATTLC
	):(
	    ival==STRING_INT_ATTLC ?(
		STRING_ALIGN_ATTLC
	    ):(
		ival==CHAR_INT_ATTLC ?(
		    CHAR_ALIGN_ATTLC
		):(
		    ival==SHORT_INT_ATTLC ?(
			SHORT_ALIGN_ATTLC
		    ):(
			0
		    )
		)
	    )
	)
    );
}
#endif
