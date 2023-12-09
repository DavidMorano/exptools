.SA 1
.VM 1 2
.TL
Using the C++ Relational Algebra Library
.AF "AT&T Federal Systems"
.AU "T. M. Robb" "tmr" "~~Santa Barbara Laboratory" "" "" "(805)349-UNIX" "sblab!robb"
.AS 0
.ll -0.5i
.in +0.75i
The C++ relational algebra library was developed at
AT&T Santa Barbara Laboratory using C++\*(Rf Release 2.0.
.RS bs
Bjarne Stroustrup. \fIThe C++ Programming Language\fP,
Addison-Wesley, 1986.
.RF
The relational algebra library is not intended as a substitute or replacement
for a database management system (DBMS).  The purpose of the library is to
provide a powerful data manipulation language for operating on and between
a variety of different storage mechanisms such as
internal program data, ASCII files and binary files.
It provides Boolean operations such as set equality and subset
and algebraic operations such as simple predicate select, project,
natural join, union, set difference and transitive closure.
It has a built-in forms interface.  But it does not have transaction logging,
atomic commitment, permanent indices and other support mechanisms that
characterize a DBMS.  The library can be readily extended to include new
storage mechanisms.  By implementing a query interface to a DBMS as a derived
class of relation, it may in the future allow DBMS management of selected
relations.  This would provide a more compact query language for the DBMS than
is usually available, and would allow the DBMS to interact more easily with
data stored outside the data base.
.P
Relations are a natural and effective method for representing the Entities
and Relationships which characterize much of analysis and design.
Relational algebra is as useful and elegant for expressing relationships
between information as Euclidean algebra is for expressing relationships
between numbers.  Incorporated within C++ using operator overloading, relational
algebra makes C++ a very effective specification language for analysis and
design as well as implementation.  Since the relational algebra
allows data to be accessed relationally \fBwhere it lies\fP rather than
requiring it to be incorporated within a database, the library is very useful
for rapid prototyping.  In many cases it may be useful for the final
implementation, but the primary goal of the current library implementation was
expressive power and versatility rather than performance.
The library optimizes naively N-squared
operations like joins but does not currently optimize linear operations
like simple predicate select.
.P
This paper updates and extends information presented at the 1989 C++ at
Work Conference\*(Rf.
.RS mr
Martin Robb.  \fIA Relational Algebra Package for C++\fP, \fBC++ at Work
'89 Conference Proceedings\fP, JPAM, Inc. 1989.
.RF
It is intended as a tutorial on using the relational algebra library as
well as on extending the library by deriving new classes of relations.
.AE
.OK "relation" "object oriented programming" "C++"
.MT 1
.in 0.0i
.po 1.25i
.ll 6.0i
.H 1 "Introduction"
The relational algebra library is a system containing a large number of classes.
The classes correspond closely with the terminology used when describing
relations.  There are Domains, Attributes and Relations, Constraints and Predicates,
Tuples, Intensions and Extensions.  Some of these classes, in particular
Domains, Attributes and Relations, must be named and manipulated directly by
the user and thus are very visible.  Others, like Intensions and Extensions,
are created as the result of operations on the visible objects and are of
less concern to the user.  
A diagram illustrating the relationships between the classes has been attached.
.P
This paper begins with an overview of the classes and the terminology.
It then discusses the use of the classes in building a simple application.
The application transforms the standard UNIX /etc/passwd and /etc/group
files into relations and performs a variety of simple queries on them.
Updates are illustrated by creating (writable) binary file relations,
selecting and assigning Tuples (records) to them and updating the binary relations.
.P
A Relation consists of two parts, an Intension and
an Extension\*(Rf.
.RS cd
C. J. Date. \fIAn Introduction to Database Systems\fP,
Addison-Wesley, 1981.
.RF
The Intension is the structure of the relation.  It consists
of a list of Attributes, or fields.  Each Attribute is of a particular data
type or Domain.
The Extension is the value of the Relation at a given time.  It consists
of Tuples.  Each Tuple contains a value for each Attribute in the Relation.
The non-key Attribute values may be thought of as "belonging to" the key
Attribute values.  Relational algebra operations include select, project,
join, and many others and will be defined later in the paper.
.P
The concepts of
Intension and Extension are familiar.  A variable in a C program has an
Intension that is its declared type and an
Extension that is its value at a given point in time.
Assigning to the variable changes its Extension without changing its Intension.
.P
Relations are perhaps the most powerful of all container classes and provide
some uncommon implementation problems.  Operations such as join can result
in entirely new data structures that
may not correspond to any declared data type in the program.  The
relational algebra treats Relations as a
common class regardless of their Intension.  It "type-checks"
to ensure that Relations have an appropriate Intension at run time
without help from the compiler.  From the compiler's point of view
Tuples and Relations have no internal structure.
.H 1 "Domains"
The Domain of a data item is the set of values that that
item could have.  Domains are somewhat like typedefs in C.
A Domain has a name, a type (integer, float or fixed length string)
and a length.
Here is part of the declaration for the Domain class:
.DS I
.ft CW
class Domain
   {
public:
   Domain(const char *const n,const Dtype t,const Dlength l);
   Domain(const Domain &domain);
   ~Domain();
   };

\#define int_domain(NAME) Domain NAME("NAME",INT,sizeof(Int_t))
\#define float_domain(NAME) Domain NAME("NAME",FLOAT,sizeof(Float_t))
\#define string_domain(NAME,LENGTH) Domain NAME("NAME",STRING,LENGTH)
.ft P
.DE
.P
The macros int_domain, float_domain and string_domain are
provided to make it more convenient to allocate Domains.  They automatically
match the recorded Domain name with the object's variable name and supply the
size information for Int_t and Float_t.
The Int_t and Float_t types are currently typedefed to long and double.
They could be typedefed to long or int and float.
.P
Application routines define Domains but don't operate on them directly.
It is possible to have a single Domain for INT, a single domain for FLOAT
and a single Domain for each size of character array:
.DS I
.ft CW
int_domain(Int);
float_domain(Float);
string_domain(String_5,5);
string_domain(String_20,20);
...
.ft P
.DE
.P
Although this works, the intent of Domains is to indicate whether
Attributes have the same type.  For example, the Attributes salary
and temperature may both be represented as floating point numbers.
If there is a single float domain Float underlying both Attributes,
salary could be renamed to temperature and vice-versa.  Joins could
be performed where salary is equal to temperature.  However, if
salary is of float Domain Dollars and temperature is of float Domain
Celsius the library will reject attempts to join or rename between
the two Attributes. Here are some Domain definitions for /etc/passwd
and /etc/group:
.DS I
.ft CW
int_domain(Id);
string_domain(Uname,9);
string_domain(Pathname,20); // shortened for convenience in printing
string_domain(Password,14);
string_domain(Comment,10);
.ft P
.DE
.H 2 "Constraint Expressions"
You may specify range and pattern limitations for Domains using Constraint
expressions. You can compare Domains to char *, Int_t or Float_t values,
depending on the Domain type, using the ==, !=, <, <=, >, and >= operators.
You can also compare String Domains to Patterns (regular expressions) using
the == and != operators.  These operations are not currently commutative,
so the Domain name should always occur on the left.  They could be made
commutative by creating a large number of friend operations.
.P
The &&, || and ! operators can also be used to build Constraint expressions.
The Constraint still applies to a single Domain so while it is syntactically
correct to write a Constraint expression that mixes Domains, it will result
in a run-time error.  Constraints are remembered until they are replaced by
another Constraint for the same Domain.  When a Tuple is assigned to a Relation,
the Constraints are checked automatically, but Constraints could be applied
before the assignment or even to non-Relational data by using the
Domain::constrain() function.  You can obtain a textual description of the
Constraint for message purposes using the Domain::constraint_string() function.
The Form_Relation class, for example, uses the constraint_string() to format
an error message if a user inserts or updates a data value that violates a
Constraint.  If constraint_string() is called for a Domain with no explicit
Constraint, it will return a string indicating the Domain type (string,
integer or decimal).
.P
Constraint expressions are written stand-alone, e.g.
.DS I
.ft CW
(void) ((Id >= (Int_t)0) && (Id < (Int_t)10000));
// The following pattern corresponds to "typical" path name usage, but
// would reject many legal path names.
Pattern path_pattern("([a-zA-Z0-9_.]{1,14}/)*[a-zA-Z0-9_.]{1,14}");
(void) Pathname == path_pattern;
.ft P
.DE
.H 1 "Attributes"
Attributes are the fields in Relations. Each Attribute is associated with a Domain.
Attributes in a Relation can be renamed to other Attributes as long as the
Attributes share the same Domain.  The relational algebra operators such as
join, set difference and project use Attribute names to determine
those Attributes of the Relation that are participating in the operation.
Here is part of the Attribute class declaration and some example definitions:
.DS I
.ft CW
class Attribute
   {
public:
   Attribute(char *,Domain &);
   };
\#define attribute(NAME,DOMAIN) Attribute NAME("NAME",DOMAIN)

attribute(user,Uname);
attribute(group,Uname);
attribute(user_password,Password);
attribute(group_password,Password);
attribute(uid,Id);
attribute(gid,Id);
attribute(gcos,Comment);
attribute(members,Comment);
attribute(home,Pathname);
attribute(shell,Pathname);
.ft P
.DE
.P
The Attribute name will be listed as a caption when Relations are printed
or Form_Relations are used.  You may prefer to make them all uppercase, or
bypass the attribute macro and make the internal form upper case for printing
and the external C++ identifier lower case for ease in programming.
.H 2 "Predicate Expressions"
You can use Attributes to create simple predicate expressions, which will
be used later for the select (%) and startwalk() operations.  Predicate
expressions are similar to Constraints.  Attribute names are used rather
than Domain names and Attributes can be compared to other Attributes of the
same Domain type as well as to Int_t, Float_t or character pointer.  Unlike
Constraints, Predicates allow different Attribute names to be mixed in the same
Predicate expression.  As the Predicate is applied to a Relation in a select
or startwalk operation, the Attributes of the Predicate are required to be
members of the Relation.
.H 1 "Intensions"
The Intension of a Relation describes its structure.  It contains a list
of Attributes.  The / operator creates Intensions dynamically by
concatenating Attributes.  In theory intensions may contain constraint
information such as entity or referential integrity.  No constraints are
kept currently, although information about the key is recorded so that
entity integrity could be implemented in the future.
Relations may only have one specified key, and that key must be a prefix
of the Attribute list.  In other words, no Attribute may participate
in the key unless all Attributes to its left also participate.
The operator % is used rather than / to separate the key Attributes from
the non-key Attributes.  An unkeyed
Relation is equivalent to a Relation in which the entire Attribute list
is the key.
.P
Intension references can be declared explicitly:
.DS I
Intension & passwd_attrs = user%user_password/uid/gid/gcos/home/shell;
Intension & group_attrs = group%group_password/gid/members;
.ft P
.DE
.P
This can be more efficient when the same Intension is used in several
places.  However, this practice is dangerous unless you understand
the dynamic allocation mechanism used with Intensions.
Domains and Attributes
are typically allocated statically, and none of the routines in the relational
algebra library would delete a Domain or Attribute unless they also
created it.  Intensions are dynamic.  They are created
by concatenating the first two Attributes in the Attribute list.
To avoid the gradual loss of free space, they are deleted when
the last Relation currently referencing them is deleted.
.P
If you use an Intension reference to define several Relations and
the lifetime of the Relations overlap, there is no problem.  If
the lifetimes are sequential so that you define a Relation using
the Intension, then destroy it, then define another Relation re-using the
Intension the Intension will already have been deallocated.
A similar problem occurs
if you are using an Intension reference to project a Relation inside a
loop.  On the second pass through the loop the Intension will be gone.
.P
These problems do not occur if you use Intension expressions directly in
Relation definitions and projections.  They only occur when you share
Intension reference variables.  If you need to share an Intension
reference you can ensure that it remains around by calling the Intension::use()
operation when it is created and the Intension::done() operation when you are
done.  You can avoid the whole problem by \fI#define\fPing the Intension or
simply specifying it explicitly at the point where it is used in a Relation
definition or projection.
.DS I
\#define passwd_attrs user%user_password/uid/gid/gcos/home/shell
\#define group_attrs group%group_password/gid/members
.ft P
.DE
.H 1 "Relations"
Relations provide a simple implementation of each relational algebra operation.
Classes derived from Relations don't have to redefine the relational operations
although they may.  Here is the Relation class declaration:
.DS I
.ft CW
class Relation
   {
public:
   Relation(Intension &i,Extension *e = new WS_Extension);
   Relation(Attribute &a,Extension *e = new WS_Extension);
   virtual ~Relation();
   virtual int degree();
   virtual int cardinality();
   virtual Boolean_t constrain(Tuple_t);
   virtual void startwalk();
   virtual void startwalk(Predicate &);
   virtual Tuple_t const walk();
   virtual Boolean_t operator=(Tuple_t);
   virtual void endwalk();
   virtual Boolean_t operator+=(Tuple_t);
   virtual Boolean_t operator=(Relation &);
   virtual Boolean_t operator+=(Relation &);
   virtual Boolean_t operator-=(Relation &);
   virtual Boolean_t operator==(Relation &);
   virtual Boolean_t operator!=(Relation &);
   virtual Boolean_t operator<(Relation &);
   virtual Boolean_t operator<=(Relation &);
   virtual Boolean_t operator>(Relation &);
   virtual Boolean_t operator>=(Relation &);
   virtual Relation & operator[](Intension &);
   virtual Relation & operator[](Attribute &);
   virtual Relation & operator%(Predicate &);
   virtual Relation & operator&(Relation &);
   virtual Relation & operator^(Relation &);
   virtual Relation & operator*(Intension &);
   virtual Relation & operator-(Relation &);
   virtual Relation & operator+(Relation &);
   };
.ft P
.DE
.P
All the operations are virtual and may be
overloaded in the derived classes.
The current implementation of the relational algebra operations is compact
but not sophisticated.
The select (such that) operator uses a sequential walk and the
other operators use hash tables that are created on the fly.
Permanent indices are not required.  Duplicates will not occur as the
result of the relational algebra but currently there is nothing to prevent
duplicates or key violations as the result of the += and =
Tuple operations.  Permanent indices may be available in the future
with tighter entity integrity (key violation) checking and
more sophisticated algebra operator implementations.
.VL 25 2
.LI "degree()"
Degree returns the number of Attributes of the underlying Intension.
.LI "cardinality()"
Cardinality returns the number of Tuples of the underlying Extension.
.LI "Relation == Relation"
The set equality operator returns true if the relational expressions
are equal.  If neither relational expression is empty (cardinality 0),
they must have the same Intension.  When the cardinality is 0, the
Relation is the Empty Set, and its Intension does not matter.
.LI "Relation != Relation"
The set inequality operator returns true if the relational expressions
aren't equal.  If neither relational expression is empty (cardinality 0),
they must have the same Intension.
.LI "Relation <= Relation"
The subset operator returns true if all Tuples in the left relational
expression are in the right.  If neither relational expression
is empty (cardinality 0), they must have the same Intension.
.LI "Relation < Relation"
The proper subset operator returns true if the left relational expression
is a subset of the right relational expression and has a lower cardinality.
.LI "Relation >= Relation"
The superset operator returns true if all Tuples in the right relational
expression are in the left.  If neither relational expression is empty
(cardinality 0), they must have the same Intension.
.LI "Relation > Relation"
The proper superset operator returns true if the left relational expression
is a superset of the right relational expression and has a higher cardinality.
.LI "Relation[Intension]"
The projection operator returns a "vertical subset" of the relational
expression, containing
those Attributes listed in the Intension.  Attributes can be renamed
within the Intension using new*old, e.g. a1/(x1*a2)/a3.
The new Attribute name must be associated with the same Domain as
the old Attribute name.
.P
All the Tuples in the original relational expression participate
in the result, but any duplicates are eliminated.  The cardinality
of the result is less than or equal to the cardinality of the original.
.LI "Relation % Predicate"
The select operator returns a "horizontal subset" of the
relational expression.  The Predicate is a simple predicate
expression that was described above.
The Predicate, often called a "such that clause,"
is evaluated for each Tuple in the relational expression.
It is a
simple predicate, meaning that no relational information beyond
the Tuple needs to be examined.
If the Predicate is true, the Tuple is included in the result.
.LI "Relation & Relation"
The natural join operator combines two relational expressions based
on common Attributes.  The resulting Intension has all the Attributes
of the left relational expression in the same order, followed
by any Attributes in the right relational expression that weren't in
the left.  In the Extension, each Tuple in the left relational
expression is combined
with each Tuple in the right relational expression that matches every
common Attribute.
Tuples that don't match don't participate in the join.
If there are no common Attributes each Tuple in the left relational
expression
matches every Tuple in the right relational expression (a cross product).
If all Attributes are common the result is an intersection.
.LI "Relation ^ Relation"
The half join operator is a natural join that has been projected
down to the Attributes of the right relational expression.  It is
more efficient than the natural join and is the most commonly needed join.
.P
The generalized theta-join operator is not supported.  It is rarely
used, can't be implemented using hashing, and can't use operator
overloading since it is ternary (relexpr,relexpr,Predicate).  Therefore
it did not seem worth implementing.
The equivalent of a theta-join can be done by walking through one Relation
and using each Tuple to select from the other Relation.
It could be done more efficiently by walking through one Relation
and creating an index using appropriate techniques (e.g. B-tree),
then walking through the other Relation looking for matches.
Since simple predicate expressions support comparison between two
Attributes, a theta-join can be done in a "relationally complete"
fashion by forcing the natural join to a cross product by renaming
common Attributes, then applying the select (such that) operator to
the result.  This is the most inefficient solution and is of
interest only because it does provide relational completeness.
.LI "Relation * (Intension)"
The transitive closure operator is useful for Relations that
represent graphs or networks.  It successively (transitively)
joins the Relation to itself until it stops growing.  The Intension
shows those Attributes that should be paired.  For example
family*(parent*child) joins parent to child.  The resulting
Intension contains all Attributes in the Intension on both the left
and right hand side of the rename (parent/child).  The resulting Extension
gives all descendents of every parent (as well as all ancestors of
every child).
.P
It is possible to have a closure with multiple Attribute pairs.
This is reasonable if the nodes in the
network are identified by a concatenated Attribute list.  For
example, if users were identified by site and user and there was
a Relation connections(from_site/from_user/to_site/to_user), the
closure would be connections*(from_site*to_site/from_user*to_user).
.LI "Relation - Relation"
The set difference operator results in all Tuples
in the left relational expression that are not in the right
relational expression.  In a strict definition both Relations need the
same Intension.
For convenience it has been defined as all Tuples in the left
relational expression that do not join with the right relational
expression.  The right Intension may differ from the
left Intension.  This avoids clumsy expressions like
A-(B^A).  Strict set difference is simply the case
where both relational expressions have the same Intension.
.LI "Relation + Relation"
The union operator results in all Tuples in either Relation.  The
two relational expressions must have the same Intension (the same
Attributes and, as currently implemented, in the same order).
Duplicates are eliminated.
.LI "walk"
Walks through a Relation behave like walks through the underlying
Extension.  In addition, startwalk() may take a Predicate expression
that will limit the walk.
.LI "ostream << Relation"
A friend operator has been defined for relational expressions that
will print them to an output stream.  The Attribute names are used
as the column headers.  This output operator works for derived
classes as well.
.SK
.H 2 "Binary Relations"
Binary Relations are derived from Relations.  The constructor simply
replaces the WS_Extension that is the default for Relations with a
BF_Extension.  Here is the declaration (and definition):
.DS I
.ft CW
class BF_Relation : public Relation
{
public:
   BF_Relation(Intension &i,char *file,Fileperm perm=READWRITE)
      : (i,new BF_Extension(file,perm)) {};
   BF_Relation(Attribute &a,char *file,Fileperm perm=READWRITE)
      : (a,new BF_Extension(file,perm)) {};
};
.ft P
.DE
.H 2 "Ascii Relations"
ASCII Relations use the AF_Extension as the underlying Extension.
Since Extensions don't know the structure of the data they are storing,
the AF_Extension operators don't attempt to convert between ASCII and
binary format.  The Relation operators for walk(), += Tuple and = Tuple
are overloaded by AF_Relation operators that use the underlying AF_Extension
operations and convert between ASCII and binary.  Here is the declaration:
.DS I
.ft CW
class AF_Relation : public Relation
{
public:
   AF_Relation(Intension &i,char *file,
      char delim='\e0',Fileperm perm=READONLY);
   AF_Relation(Attribute &a,char *file,
      char delim='\e0',Fileperm perm=READONLY);
   Tuple_t const walk();
   void endwalk();
   Boolean_t operator=(Tuple_t);
   Boolean_t operator+=(Tuple_t);
};
.ft P
.DE
.P
The ASCII file may be any file that
consists of one record per line and has a single specified field
separator.  Files that use white space (1 or more spaces or tabs) as
the field separator can be used by leaving the default delimiter value.
The class implementation reads and writes records in the
file using printf/scanf style formatting capabilities.
The /etc/passwd and /etc/group files are now Relations.  Using the Domain
and Attribute definitions created previously, here is an example
of a query that can be run on them:
.DS I
.ft CW
AF_Relation etcpasswd(passwd_attrs,"/etc/passwd",':');
AF_Relation etcgroup(group_attrs,"/etc/group",':');
main()
{
cout << "\et\et\etUSER INFORMATION:\en"
     <<  (etcpasswd & etcgroup)[user/group/home/shell] ;
return 0;
}
.ft P
.DE
.H 2 "Form Relations"
A user interface for insertion, update and display has been
implemented as a derived Relation class.  When used as an rvalue the
Form_Relation accepts input from the user.  When used as an lvalue
the Form_Relation displays to the user.  The Extension is not retained
from expression to expression, although the cardinality() operator will
retain the Tuples it obtained as input until the next use as an rvalue.
Updates are available through an additional update() function that takes
a Tuple as input and returns a new Tuple.  Here is the declaration with
an example using input and display:
.DS I
.ft CW
class Form_Relation : public Relation
   {
public:
   Form_Relation(Intension &i,char *heading=(char *)0,
      WINDOW *w=stdscr);
   Form_Relation(Attribute &a,char *heading=(char *)0,
      WINDOW *w=stdscr);
   ~Form_Relation();
   int cardinality();
   void startwalk();
   void endwalk();
   Boolean_t operator+=(Tuple_t t);   // returns FALSE
   Boolean_t operator+=(Relation &r); // returns FALSE
   Boolean_t operator-=(Relation &r); // returns FALSE
   Boolean_t operator=(Tuple_t);
   Boolean_t operator=(Relation &);
   Tuple_t const update(Tuple_t);
   };

Form_Relation user_display(user/uid/home/shell,"USER INFO");
Form_Relation user_entry(user,"ENTER USERS");
user_display = user_entry ^ etcpasswd[user/uid/home/shell];
.ft P
.DE
.H 1 "Future Directions"
.H 2 "SQL_Relations"
SQL_Relations would  allow the relational algebra library to interact
with a commercial database system.  There might be multiple derived
classes to handle various vendors' presentation layers.
.P
A SQL_Extension class would be needed to send the appropriate
query to the DBMS and iterate through the result.
Most DBMS have a SQL interpreter program that could be used and would
be fairly portable.  A faster implementation would interface to the
underlying library routines  of a particular database.
An actual SQL statement could not be sent to the DBMS using the library
routine interface since
embedded SQL statements are pre-processed by most DBMS and the statement
would not be constructed until run-time.
.P
An initial implementation of SQL_Relations could be done with
overloading similar to the BF_Relation implementation.
A complete SQL_Relation class implementation should distinguish
between internal operations between two SQL_Relations and external
operations between a SQL 
Relation and a non-SQL relation so that the internal queries
can be referred to the DBMS.  This can be done by overloading the relational
algebra operations, e.g:
.DS I
.ft CW
SQL_Relation & SQL_Relation::operator&(SQL_Relation &); // internal
Relation & SQL_Relation::operator&(Relation &);         // external
.ft P
.DE
.P
The external form would simply call the corresponding Relation operation.
The internal form would combine the SELECT, FROM and WHERE clauses of the
operands to form a resulting SQL statement.  The statement could continue
to build without going to the DBMS until the expression was assigned to a
SQL_Relation or until it interacted with a non-SQL_Relation.
.SK
.H 2 "Indexing"
Currently the relational algebra library has no permanent indices.  Most
of the relational operations build temporary hash tables on the smaller
of the two operands, then walk through the larger operand searching the
hash table.  This reduces the cost of complex operations
such as joins and does not incur the update overhead of permanent indices.
.P
There are two major reasons to provide permanent indices.  They could enforce
entity integrity, i.e. check for key violations when appending
data.  They could also provide faster retrieval for simple select
operations.
.P
If indices are implemented the initial version will probably use B-trees
or a similar mechanism that supports all the comparison operators.
There will be at most 1 index per Attribute and exactly 1 Attribute per
index.
Extensions will be restricted to provide ordered storage of Tuples and
will provide numerically indexed retrieval and update.  This will allow
the Extension to be represented as a bitmask where 1-bits show
selected Tuples and 0-bits show unselected Tuples.  The Predicate
&&, || and ! operations could then bit-wise &, | and ~ the
bitmasks obtained by the leaf operations to obtain the composite set
of selected Tuples.
.P
Since not all leaf operations will be indexed there is additional
complexity.  The bitmask returned may be the exact set or a superset
of the desired Tuples.  While the && and || operations can be
applied to a superset of the desired Tuples, the ! operation can't.
It would have to specify the entire set as the resulting superset.
Along with the bitmasks an indication of exact set, superset or
entire set would need to be returned.  Unless the set
were exact, the Predicate would have to be reapplied to the selected
Tuples as they were retrieved.
.P
This discussion of a possible implementation illustrates some good
reasons not to provide permanent indices.  The current code
is compact (about 3000 lines) and simple.  Database
management systems often run well over 100,000 lines of code.  Adding
indices plus the code to update all indices whenever insertions and
deletions occur, apply indices to arbitrary predicate expressions,
accumulate results from a series of applications of indices when joining
two relations,
determine when operations should use existing indices and when they should
build their own, etc., could be a large step towards the size and
complexity of a commercial DBMS.  Once an interface to an existing DBMS
is available, it may be easier and preferable to place relations requiring
indexing into the DBMS rather than writing substantial code to provide features
that would still be less complete than those provided by the DBMS.
.H 1 "References"
.AL 1
.LI
Bjarne Stroustrup. \fIThe C++ Programming Language\fP,
Addison-Wesley, 1986.
.LI
C. J. Date. \fIAn Introduction to Database Systems\fP,
Addison-Wesley, 1981.
.LI
Martin Robb.  \fIA Relational Algebra Package for C++\fP, \fBC++ at Work
'89 Conference Proceedings\fP, JPAM, Inc. 1989.
.LE sp
.SK
.DS CB
#include "relation.pic"
.DE
.H 1 "Tuples"
Tuples are the storage representation for individual records.
Although Tuples have associated operations, they are not a class.
This makes it more convenient to use them as data pointers.
.DS I
.ft CW
typedef char *Tuple_t;
Tuple_t tuple_new(long size);
Boolean_t tuple_done(Tuple_t Tuple);
Boolean_t tuple_share(Tuple_t Tuple);
.ft P
.DE
.P
Relational operations use Tuples internally.  Application code
may never need to reference Tuples directly, but it can
use Tuples to exchange information between
Relations and other program data.  Tuples may be shared between Relations,
which is particularly useful for
relational expressions (intermediate Relations created while
evaluating the relational algebra).  Correct use of the Tuple
operations is important to ensure that the sharing is correct.
.P
Application code can create new Tuples to append records from
internal data structures to a Relation.  It could also use new Tuples to
append records read in from a file, but it would be easier to declare
the file as an ASCII or binary file Relation.  No one should alter the contents
of a Tuple after it has been appended to a Relation.  Use tuple_done to
release any Tuple created through tuple_new once you are finished with it.
.P
Application code may also obtain references to a Tuple by walking
through a Relation.  The reference will remain valid until the
next iteration of the walk.  If the reference is required for a
longer period, share the Tuple using tuple_share and
release it using tuple_done once you are finished
with it.
.P
Passing data between Relations and the application requires a structure
definition that resembles the format of the data in the Relation.  This
icon must contain a member for each Attribute in
the same order the Attributes occur in the Relation.  Integer Attributes
are represented by members of type Int_t, float Attributes by members of
type Float_t and string Attributes by members of type char [N] where
N is the length of the Domain.  For example:
.DS I
.ft CW
typedef char Uname_t[9];
typedef char Pathname_t[16];
typedef char Password_t[14];
typedef char Comment_t[10];
typedef Int_t Id_t;
typedef struct {
   Uname_t user;
   Password_t user_password;
   Id_t uid;
   Id_t gid;
   Comment_t gcos;
   Pathname_t home;
   Pathname_t shell;
   } Passwd_struct_t;
typedef union { Tuple_t t; Passwd_struct_t *s; } Passwd_tuple_t;
.ft P
.DE
.SK
.H 1 "Extensions"
Extensions provide the primitive data management operations
for relational algebra.  Extensions are unbounded heaps that you
can add to, walk through or truncate to zero Tuples.  Extensions
track the number of Tuples currently stored (cardinality).
In the future Extension walks may be assumed ordered and an indexed
retrieval operation may be provided.
.DS I
.ft CW
class Extension
   {
public:
   size_t item_size;
   Extension();
   virtual ~Extension();
   virtual int cardinality();
   virtual void startwalk() = 0;
   virtual Tuple_t const walk() = 0;
   virtual Boolean_t operator=(Tuple_t) = 0;
   virtual void endwalk() = 0;
   virtual void truncate() = 0;
   virtual Boolean_t operator+=(Tuple_t) = 0;
   };
.ft P
.DE
.P
The Relation constructor creates an Extension, so they
don't need to be explicitly allocated.
Here are the Extension operations.  They are used internally by the
relational algebra, but you could use them on an externally defined
Extension.
.VL 15 2
.LI "cardinality"
returns the number of Tuples currently stored.
.LI "truncate"
removes any Tuples currently stored.
.LI "+="
stores a new Tuple.  The Tuple must have been allocated using tuple_new.
.LI "walk"
The walk capability is started by startwalk(), loops using walk(), and is ended by endwalk().  Behavior is not guaranteed unless
the walks are properly started and ended.  Items returned by
walk() are guaranteed to be allocated using tuple_new, so they
may be given to other Extensions using +=.
If you need to retain a reference beyond the current iteration of the walk,
tuple_share and tuple_done should be used.
Since the current Tuple may be shared it should not be
modified directly.
If the = operator is used inside a walk, the current Tuple will be
replaced.
The = operator is not valid outside a walk.
.LE sp
.P
Extensions are an abstract class.
The WS_Extension class is an in memory (workspace) implementation of
Extensions.  The BF_Extension is a binary file implementation and the
AF_Extension is a line-oriented ASCII file implementation.
.P
All Tuples input and output to AF_Extensions must end in a newline.
Unlike the other Extensions, AF_Extensions are not suitable for storing
structures directly. AF_Relations convert between formatted lines and
the structure format of the Tuple.
.SK
