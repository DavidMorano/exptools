/********************************************************/
/*  Integer Set Package   ... tests                     */
/*  Author: J. E. Grass                                 */
/*          MH 3C- 532C             (201) 582-6905      */
/*          ulysses!jeg                                 */
/*  Date:   Aug. 19, 1988                               */
/********************************************************/

#include <iostream.h>
#include "Int_set.h"

int	buf[] = { 15, 33, -1};
int bl[]={0, 3,5,40,-1};
int al[]={3,5,7,9,40,-1};
int c_list[] = {0, 1,2,5,45,-1};
int d_list[]= {  1 , 2 , 3 , 4 , 5  , 40 , 45 ,-1};
int a_list[] = {30, 15, 0, 27, 33, -1};
int b_list[]={1 , 2 , 3 , 4 , 10  , 15 , 20 , 50, 25 , 30, -1};

main (){
	int i, j;
	Int_set a, e;
	Int_set_iter ai(a), ei(e);

	Int_set b;
	Int_set_iter bi(b);

	Int_set c(Int_set_size(80));
	Int_set_iter ci(c);

	Int_set d(200);
	Int_set_iter di(d);

	Int_set f;
	Int_set g(b_list);
	Int_set h(2, 4, 6, 8, 10, 12, 37, -1);
	Int_set iset(0, 40, -3);
	Int_set jset(0, 15, -3);

	cout<<"Start test \n";
        Int_set s1 = Int_set(0,1,8,9,-1);
cerr<<"S1 is "<<s1<<"\n";
        Int_set s2 = Int_set(0,1,2,8,-1);       /* this triggers the bug! */
cerr<<"S2 is "<<s2<<"\n";

        Int_set_iter aix = Int_set_iter(s1);
cerr<<"aix made, s1 = "<<s1<<"\n";
        cerr << aix.last() << "\n";

	cout<<"Test Initialization.. \n";
	{
		cout<<"set g(1 2 3 4 10 50 15 20 25 30 -1) = " << g << "\n";
		cout<<"set h(2 4 6 8 10 37 12 -1) = "<< h << "\n";
		cout<<"iset (0 40) = "<< iset << "\n";
		cout<<"jset (0 15) = "<< jset << "\n";
	}
	cout<<" test adding members\n";
	{
		cout<<" a = "<< a<< "\n";
	
		a .add(5);
		cout<<" a = "<< a <<"\n";
		a.add(buf);
		cout<<" a = "<< a << "\n";
		i = 65;
		j = 30;
		a .add(i);
		cout<<" a = "<< a <<"\n";
		a.add(j);
	
		cout<<"a.add( 5 15 33 65 30) = "<< a <<"\n";
		cout<<"a iterate: ";
		while ( (i=ai++) >= 0)
			cout<< i <<", ";
		cout<<"\n";
	
		cout<<"a iterate: ";
		while ( (i=ai++) >= 0)
			cout<<i<<", ";
		cout<<"\n";
	
		
	
		f.add(0,5, -1);
		cout<<"f .add(0 5)= "<< f <<"\n";
		a.remove(5,15,0,33,30,65,-1);
		cout<<" a.remove(5,15,0, 33,30,65,-1);= "<<a <<"\n";
		a.add(5,15,33,30,65,-1);
		cout<<"a.add(5,15,33,30,65,-1);= "<<a<<"\n";
	
		cout<<"a.backwards iteration::: ";
		for (i = ai.last(); i >= 0; i = ai--)
			cout<<i<<", ";
		cout<<"\n";
	
		a.remove(30);
		cout<<"a.remove(30);= "<<a<<"\n";
	
		b .add(1,2,3,4,10,15,20,25,30,-1);
		cout<<"b.add(1 2 3 4 10 15 20 25 30)= "<<b<<"\n";
	}

	cout<<"test removing members ";
	{
		a.remove(a_list);
		cout<<"a.remove(30 0 15 27 33) = "<<a<<"\n";
	
		d.add(d_list);
		cout<<"d.add(d_list) = "<<d<<"\n";
	
		c.add(c_list);
		cout<<"c.add(0 1 2 5 45)= "<<c<<"\n";
	}

	cout<<"Test diff. (-) \n";
	{
		d = d - c - a; 
		cout<<"d = d - c - a= "<< d<<"\n";
	}

	cout<<"Test union (|) \n";
	{
		c = a | b;
		cout<<"c =  a | b =>"<< c<<"\n";
	
		d = a | b | c ;
		cout<<"\nd =  a | b | c= "<< d<<"\n";
	}


	cout<<"test intersection (&) \n";
	{
		d = c & a & b;
		cout<<"d =  c & a & b ="<< d<<"\n";
	}


	cout<<"test equality (==) \n";
	{
		cout<<" d == d => "<< (d == d)<<"\n";
	
		cout<<" a == d => "<< ( a == d)<<"\n";
		cout<<" d == a => "<< ( d == a)<<"\n";
		cout<<" c == b => "<< ( c == b)<<"\n";
	
		e = a;
		cout<<"e = a = "<< e<<"\n";
		cout<<" a == e => "<< ( a == e)<<"\n";
		cout<<" e== a => "<< ( e == a)<<"\n";
	}

	cout<<"test inequality (!=) \n";
	{
		cout<<" d != d => "<< (d != d)<<"\n";
	
		cout<<" a != d => "<< ( a != d)<<"\n";
		cout<<" d != a => "<< ( d != a)<<"\n";
		cout<<" c != b => "<< ( c != b)<<"\n";
	
		cout<<" a != e => "<< ( a != e)<<"\n";
		cout<<" e != a => "<< ( e != a)<<"\n";
	}

	cout<<"test is contained in (subset) \n";
	{
		cout<<" a subset a ... "<< a .is_subset_of( a)<<"\n";
		cout<<" b subset a ... "<< b .is_subset_of( a)<<"\n";
		cout<<" a subset b ... "<< a .is_subset_of( b)<<"\n";
	
		cout<<" a.is_empty() = "<< a.is_empty()<<"\n";
		a.make_empty();
		cout<<"a.make_empty == "<< a<<"\n";
		cout<<" a.is_empty() = \n"<< a.is_empty()<<"\n";
	
		cout<<" b.is_empty() = "<< b.is_empty()<<"\n";
		b.make_empty();
		cout<<"b.make_empty == "<< b<<"\n";
		cout<<" b.is_empty() = "<< b.is_empty()<<"\n";
	
		cout<<" d.is_empty() = "<< d.is_empty()<<"\n";
		d.make_empty();
		cout<<"d.make_empty == "<< d<<"\n";
		cout<<" d.is_empty() = "<< d.is_empty()<<"\n";
	
		a.add(al);
		cout<<" a.add(al) "<< a<<"\n";
	
		b.add(bl);
		cout<<" b.add( 0 3 5 40); = "<< b<<"\n";
	
		cout<<" a subset a ... "<< a .is_subset_of( a)<<"\n";
		cout<<" b subset a ... "<< b .is_subset_of( a)<<"\n";
		cout<<" a subset b ... "<< a .is_subset_of( b)<<"\n";
	
		cout<<" a supset a ... "<< a.is_superset_of( a)<<"\n";
		cout<<" b supset a ... "<< b.is_superset_of( a)<<"\n";
		cout<<" a supset b ... "<< a.is_superset_of( b)<<"\n";
		cout<<" c supset b ... "<< c.is_superset_of( b)<<"\n";
		cout<<" c supset d ... "<< c.is_superset_of( d)<<"\n";
	}
 
cout<<"test cardinality\n";
	cout<<"a.cardinality() = "<<a.cardinality()<<"\n";
	cout<<"b.cardinality() = "<<b.cardinality()<<"\n";
	cout<<"c.cardinality() = "<<c.cardinality()<<"\n";
	cout<<"d.cardinality() = "<<d.cardinality()<<"\n";

	cout<<"test includes\n";
	for (i = 0; i < 100; i++){
		if (a.includes(i)) cout<<i<<" is in a\n";
		if (b.includes(i)) cout<<i<<" is in b\n";
		if (c.includes(i)) cout<<i<<" is in c\n";
		if (d.includes(i)) cout<<i <<" is in d\n";
	}
	
	cout<<"test fill_range\n";
	{
		a.fill_range(0,31);
		cout<<" a.fill_range(0,31)= "<< a<<"\n";
	
		b.fill_range(1,12);
		cout<<" b.fill_range(1,12)= "<< b<<"\n";
	
		c.fill_range(1,33);
		cout<<" c.fill_range(1,33)= "<< c<<"\n";
	
		d.fill_range(5,69);
		cout<<" d.fill_range(5,69)= "<< d<<"\n";
	
		a.clear_range(5,51);
		cout<<" a.clear_range(5,51)= "<< a<<"\n";
	
		b.clear_range(3,7);
		cout<<" b.clear_range(3,7)= "<< b<<"\n";
	
		b.clear_range(40,40);
		cout<<" b.clear_range(40,40)= "<< b<<"\n";
	
	
		b.clear_range(9,12);
		cout<<" b.clear_range(9,12)= "<< b<<"\n";
	
		c.clear_range(1,33);
		cout<<" c.clear_range(1,33)= "<< c<<"\n";
	
		d.clear_range(12,65);
		cout<<" d.clear_range(12,65)= "<< d<<"\n";
	
		d .remove(69);
		cout<<"d = d - 69 = "<< d<<"\n";
	}

	cout<<"done\n";
}
