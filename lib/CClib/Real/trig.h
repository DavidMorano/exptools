
class AtanSeries : public Series {
	int		n ;
	Real		xsquare ;	// x*x 
	Real		p ; 		// x**n 
	Real		term ; 		// sgn*p/n 
	int		sgn ;  	// plus or minus 1 

	Real		next() ;
	Real		bound() ;
	void		step() ;
	
public:
			AtanSeries(Real x) ;
			~AtanSeries() ;
	
} ;

class SinSeries : public Series {
	int	 	k ;
	Real		term ;
	Real		xsq ;
	int		sgn ;

	Real		next() ;
	Real		bound() ;
	void		step() ;
	
public:
			SinSeries(Real x) ;
			~SinSeries() ;
	
} ;

class CosSeries : public Series {
	int	 	k ;
	Real		term ;
	Real		xsq ;
	int		sgn ;

	Real		next() ;
	Real		bound() ;
	void		step() ;
	
public:
			CosSeries(Real x) ;
			~CosSeries() ;
	
} ;

extern Real pi() ;
