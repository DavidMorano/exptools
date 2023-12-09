#ifndef GDOUBLET_HXX
# define GDOUBLET_HXX

# ifndef STD_H
 typedef short BOOL;	/* Use BOOL for logical variables as a reminder to
						the programmer. */
# endif

PT_names
gdoublet(T) T _doublet
PT_end


PT_define gdoubletdeclare(T)
class gdoublet(T)	{	
	public:				
	T x, y;		
	gdoublet(T)(T xx, T yy)	{x=xx; y=yy;}		
	gdoublet(T)()	{x = y = 0;}		
	};	

inline BOOL operator==(const gdoublet(T)& a, const gdoublet(T)& b)
	{return a.x==b.x && a.y==b.y;}
inline BOOL operator!=(const gdoublet(T)& a, const gdoublet(T)& b)
	{return !(a==b);}
inline gdoublet(T) operator+(const gdoublet(T)& a, const gdoublet(T)& b)	
	{return gdoublet(T)(a.x+b.x, a.y+b.y);}	
inline gdoublet(T) operator*(T a, const gdoublet(T)& b)	
	{return gdoublet(T)(a*b.x, a*b.y);}	
inline gdoublet(T) operator*(const gdoublet(T)& b, T a)	
	{return gdoublet(T)(a*b.x, a*b.y);}	
inline gdoublet(T) operator/(const gdoublet(T)& b, T a)	
	{return gdoublet(T)(b.x/a, b.y/a);}	
PT_end

#endif
