/*	Element.h
	Author: T. C. Weitzen/mozart!tcw
	Version 1.0, July 1990
*/
#ifndef ELEMENT_DOT_H
#define ELEMENT_DOT_H

#include "Symbol.h"



PT_names
	Elem(A) A _elem 
	Element2(A,B)	Element2_ A _ B
	Element3(A,B,C)	Element3_ A _ B _ C
	Element4(A,B,C,D)	Element4_ A _ B _ C _ D
	Element5(A,B,C,D,E)	Element5_ A _ B _ C _ D _ E
PT_end

PT_define Element1declare(A)
class Element1(A) {
	char symbol;
	union {
		A* Elem(A) ;
		};
public:
	inline void put(A* a) {Elem(A) = a; symbol = 'a';}
	inline A* get(A*) { 
		if (symbol=='a') 
			return Elem(A) ;
		else return 0;
		}
	inline int operator==(Element1(A)&) {
		return(1);
		}
	};

PT_end
PT_define Element2declare(A,B)
class Element2(A,B) {
	char symbol;
	union {
		A* Elem(A) ;
		B* Elem(B) ;
		};
public:
	inline void put(A* a) { Elem(A) = a; symbol = 'a';}
	inline void put(B* b) { Elem(B) = b; symbol = 'b';}
	inline A* get(A*) { 
		if (symbol=='a') 
			return Elem(A) ;
		else return 0;
		}
	inline B* get(B*) { 
		if (symbol=='b') 
			return Elem(B) ;
		else return 0;
		}
	inline int operator==(Element2(A,B)&) {
		return(1);
		}
	};

PT_end
PT_define Element3declare(A,B,C)
class Element3(A,B,C) {
	char symbol;
	union {
		A* Elem(A) ;
		B* Elem(B) ;
		C* Elem(C) ;
		};
public:
	inline void put(A* a) { Elem(A) = a; symbol = 'a';}
	inline void put(B* b) { Elem(B) = b; symbol = 'b';}
	inline void put(C* c) { Elem(C) = c; symbol = 'c';}
	inline A* get(A*) { 
		if (symbol=='a') 
			return Elem(A) ;
		else return 0;
		}
	inline B* get(B*) { 
		if (symbol=='b') 
			return Elem(B) ;
		else return 0;
		}
	inline C* get(C*) { 
		if (symbol=='c') 
			return Elem(C) ;
		else return 0;
		}
	inline int operator==(Element3(A,B,C)&) {
		return(1);
		}
	};

PT_end
PT_define Element4declare(A,B,C,D)
class Element4(A,B,C,D) {
	char symbol;
	union {
		A* Elem(A) ;
		B* Elem(B) ;
		C* Elem(C) ;
		D* Elem(D) ;
		};
public:
	inline void put(A* a) { Elem(A) = a; symbol = 'a';}
	inline void put(B* b) { Elem(B) = b; symbol = 'b';}
	inline void put(C* c) { Elem(C) = c; symbol = 'c';}
	inline void put(D* d) { Elem(D) = d; symbol = 'd';}
	inline A* get(A*) { 
		if (symbol=='a') 
			return Elem(A) ;
		else return 0;
		}
	inline B* get(B*) { 
		if (symbol=='b') 
			return Elem(B) ;
		else return 0;
		}
	inline C* get(C*) { 
		if (symbol=='c') 
			return Elem(C) ;
		else return 0;
		}
	inline D* get(D*) { 
		if (symbol=='d') 
			return Elem(D) ;
		else return 0;
		}
	inline int operator==(Element4(A,B,C,D)&) {
		return(1);
		}
	};

PT_end
PT_define Element5declare(A,B,C,D,E)
class Element5(A,B,C,D,E) {
	char symbol;
	union {
		A* Elem(A) ;
		B* Elem(B) ;
		C* Elem(C) ;
		D* Elem(D) ;
		E* Elem(E) ;
		};
public:
	inline A* get(A*) { 
		if (symbol=='a') 
			return Elem(A) ;
		else return 0;
		}
	inline B* get(B*) { 
		if (symbol=='b') 
			return Elem(B) ;
		else return 0;
		}
	inline C* get(C*) { 
		if (symbol=='c') 
			return Elem(C) ;
		else return 0;
		}
	inline D* get(D*) { 
		if (symbol=='d') 
			return Elem(D) ;
		else return 0;
		}
	inline E* get(E*) { 
		if (symbol=='e') 
			return Elem(E) ;
		else return 0;
		}
	inline int operator==(Element5(A,B,C,D,E)&) {
		return(1);
		}
	};

PT_end


#endif
