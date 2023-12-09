#ident "@(#) /sable/sdb/ra/rel/domain/s.dname.C"
/*      Copyright (c) 1989,1991 AT&T - All Rights Reserved */

#include <relation.h>

ostream & operator<<(ostream &stream,const Dname &dname)
{
stream << dname.name;
return stream;
}

Dname & Dname::operator=(const char *const string)
{
name[0] = '\0';
if ( string ) strncpy(name,string,LNAME);
name[LNAME-1] = '\0';
return *this;
}

Dname & Dname::operator=(const Dname &dname)
{
strncpy(name,dname.name,LNAME);
return *this;
}

Boolean_t Dname::operator==(const Dname &dname) const
{
return strncmp(name,dname.name,LNAME) ?FALSE :TRUE;     // 0 means equal
}

Boolean_t Dname::operator!=(const Dname &dname) const
{
return strncmp(name,dname.name,LNAME) ?TRUE :FALSE;
}
