
#include <real.h>
#include <bigit.h>

static const int BIGCOUNT = 1<<14 ;

Plimit inf_plimit = plimit(BIGCOUNT/BITSINBIGIT) ;

Plimit divide_plimit ;
Plimit relation_plimit ;
Plimit io_plimit ;	
Plimit split_plimit ;
Plimit round_plimit ;
Plimit underflow_plimit ;

Plimit abs_plimit(int n)
{
	Plimit t ;
	t.absolute = (n+BITSINBIGIT-1)/BITSINBIGIT ;
	t.relative = 0 ;
	return t ;
	}

Plimit rel_plimit(int n)
{
	Plimit t ;
	t.absolute = -BIGCOUNT ;
	t.relative = (n+BITSINBIGIT-1)/BITSINBIGIT ;
	return t ;
	}

Plimit plimit(int n) 
{
	Plimit t ;
	t.relative = t.absolute = (n+BITSINBIGIT-1)/BITSINBIGIT ;
	return t ;
	}

Plimit operator+(Plimit t1, Plimit t2)
{
	Plimit t ;
	t.absolute = (t1.absolute>t2.absolute ? t1.absolute : t2.absolute) ;
	t.relative = (t1.relative>t2.relative ? t1.relative : t2.relative) ;
	return t ;
	}
