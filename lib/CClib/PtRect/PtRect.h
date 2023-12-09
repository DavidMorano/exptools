#ifndef GEOMETRY_H
#define GEOMETRY_H

/*
 *     C++ include file for point and rectangle geometry
 *     Version - 7 October 1988
 *
 *     Emden R. Gansner
 *     AT&T Bell Laboratories
 *     ulysses!erg
 *
 */

struct Rect;

struct Point {
	short x, y;

  /* Member functions */
	Point()                   {x = 0; y = 0;}
	Point(int a, int b)       {x = a; y = b;}

	Point& operator+= (Point);
	Point& operator-= (Point);
	Point& operator*= (Point);
	Point& operator*= (int);
};

class Rect {
	Point o;			// Origin.
	Point c;			// Corner.

public:
  /* Member functions */
	Rect ()                  { }
	Rect (Point a, Point b) : o (a.x,a.y), c (b.x,b.y) {}
	Rect (int xo, int yo, int xc, int yc) : o (xo,yo), c (xc,yc)
		{ }

	int		clip (Rect);
	int		intersect (Rect);
	int		contains (Point);
	int		contains (Rect);
	Point	origin ()					{ return o; }
	Point	corner ()					{ return c; }
	void	set_origin (Point p)		{ o = p; }
	void	set_corner (Point p)		{ c = p; }
	Point	size ();
	int		width ();
	int		height ();
	Rect	inset (int);

	Rect& operator+= (Point);
	Rect& operator-= (Point);
	Rect& operator*= (Point);
	Rect& operator*= (int);

  /* Friends. */

};


		/** Arithmetic operators. **/
inline Point operator+ (Point a, Point b)
	{ return (Point(a.x + b.x, a.y + b.y)); }     
inline Point operator- (Point a, Point b)
	{ return (Point(a.x - b.x,a.y - b.y)); }     
inline Point operator* (Point a, int b)
	{ return (Point(a.x*b,a.y*b)); }     
inline Point operator* (int b, Point a)
	{ return (Point(a.x*b,a.y*b)); }     
inline Point operator* (Point a, Point b)
	{ return (Point(a.x * b.x,a.y * b.y)); }     
inline Rect operator+ (Point p, Rect r)
	{ return (Rect(p + r.origin(), p + r.corner())); }
inline Rect operator+ (Rect r, Point p)
	{ return (Rect(r.origin() + p, r.corner() + p)); }
inline Rect operator- (Rect r, Point p)
	{ return (Rect(r.origin() - p, r.corner() - p)); }
inline Rect operator* (Point p, Rect r)
	{ return (Rect(p * r.origin(), p * r.corner())); }
inline Rect operator* (Rect r, Point p)
	{ return (Rect(r.origin() * p, r.corner() * p)); }
inline Rect operator* (Rect r, int i)
	{ return (Rect(r.origin() * i, r.corner() * i)); }
inline Rect operator* (int i, Rect r)
	{ return (Rect(r.origin() * i, r.corner() * i)); }


		/** Comparison operators. **/
inline int operator== (Point a, Point b)
	{ return ((a.x == b.x) && (a.y == b.y)); }
inline int operator!= (Point a, Point b)
	{ return ((a.x != b.x) || (a.y != b.y)); }
inline int operator>= (Point a, Point b)
	{ return ((a.x >= b.x) && (a.y >= b.y)); }
inline int operator<= (Point a, Point b) 
	{ return ((a.x <= b.x) && (a.y <= b.y)); }
inline int operator> (Point a, Point b) 
	{ return ((a >= b) && (a != b)); }
inline int operator< (Point a, Point b) 
	{ return ((a <= b) && (a != b)); }
inline int operator== (Rect r, Rect s)
	{ return ((r.origin() == s.origin()) && (r.corner() == s.corner())); }
inline int operator!= (Rect r, Rect s)
	{ return ((r.origin() != s.origin()) || (r.corner() != s.corner())); }


		/** Point functions. **/
inline Point& Point::operator+= (Point b)
	{ x += b.x; y += b.y; return *this; }
inline Point& Point::operator-= (Point b)
	{ x -= b.x; y -= b.y; return *this; }
inline Point& Point::operator*= (Point b)
	{ x *= b.x; y *= b.y; return *this; }
inline Point& Point::operator*= (int b)
	{ x *= b; y *= b; return *this; }

		/** Miscellaneous functions. **/
/* canon:
 * Create rectangle determined by two points.
 */
inline Rect canon (Point a, Point b)
{
	short	xo, yo, xc, yc;

    xo = (a.x < b.x ? a.x : b.x);	// min(a.x, b.x);
    yo = (a.y < b.y ? a.y : b.y);	// min(a.y, b.y);
    xc = (a.x > b.x ? a.x : b.x);	// max(a.x, b.x);
    yc = (a.x > b.y ? a.y : b.y);	// max(a.y, b.y);

	return Rect (xo, yo, xc, yc);
}
		/** Rectangle functions. **/
/* intersect:
 * Return non-zero if this and r intersect; 0 otherwise.
 */
inline int Rect::intersect (Rect r)
{
	return ((r.o.x<c.x) && (o.x<r.c.x)
	   && (r.o.y<c.y) && (o.y<r.c.y));
}

/* clip:
 * Clip this to fit inside r and return non-zero; if disjoint, return 0;
 */
int Rect::clip (Rect r)
{
	/* If they don't overlap, return 0 */	
	if (intersect(r) == 0) return(0); 

	if (o.x < r.o.x)
		o.x = r.o.x;
	if (o.y < r.o.y)
		o.y = r.o.y;
	if (c.x > r.c.x)
		c.x = r.c.x;
	if (c.y > r.c.y)
		c.y = r.c.y;
	return(1);
}

/* contains:
 * Return non-zero if p is in this; 0 otherwise.
 */
inline int Rect::contains (Point p)
{
	return ((p >= o) && (p.x < c.x) && (p.y < c.y));
}

/* contains:
 * Return non-zero if r is in this; 0 otherwise.
 */
inline int Rect::contains (Rect r)
{
	return ((r.o >= o) && (r.c <= c));
}

/* size:
 * Return point containing the size of the rectangle.
 */
inline Point Rect::size ()
{
	return (Point(c.x - o.x, c.y - o.y));
}

/* width:
 * Return the width of the rectangle.
 */
inline int Rect::width ()
{
	return ((int)(c.x - o.x));
}

/* height:
 * Return the height of the rectangle.
 */
inline int Rect::height ()
{
	return ((int)(c.y - o.y));
}

/*
 * inset:
 * Return rectangle r inset by i.
 */
inline Rect Rect::inset  (int i)
{
	return (Rect(o.x+i,o.y+i,c.x-i,c.y-i));
}

inline Rect& Rect::operator+= (Point p)
	{ o += p; c += p; return *this; }
inline Rect& Rect::operator-= (Point p)
	{ o -= p; c -= p; return *this; }
inline Rect& Rect::operator*= (Point p)
	{ o *= p; c *= p; return *this; }
inline Rect& Rect::operator*= (int i)
	{ o *= i; c *= i; return *this; }

#endif GEOMETRY_H

