
class ExpSeries : public Series {
	long		k ;
	Real		x ;
	Real		b ;
	Real		term ;

protected:
	Real		next() ;
	Real		bound() ;
	void		step() ;
	
public:
			ExpSeries(Real x) ;
			~ExpSeries() ;
	} ;


class LogSeries : public Series {
	Real		tpow ;
	Real		tsq ;
	Real		term ;
	long		k ;
protected:
	Real		next() ;
	Real		bound() ;
	void		step() ;
	
public:
			LogSeries(Real x) ;
			~LogSeries() ;
	} ;


class Log2 : public Series {
	// A class whose value is specifically log2
	Real 	m ;
	Real	p ;
	long	k ;

protected:
	Real		next() ;
	Real		bound() ;
	void		step() ;
	
public:
			Log2() ;
			~Log2() ;
	} ;
	