#ident "@(#) /sable/sdb/ra/rel/s.relation.H"
/*      Copyright (c) 1989,1990,1991 AT&T - All Rights Reserved    */

#ifndef relation_h
#define relation_h

#include <sblib.h>

class AF_Extension;
class AF_Relation;
class Attribute;
class BF_Extension;
class BF_Relation;
class Constraint;
class Domain;
class Dname;
class Extension;
class Form_Relation;
class Intension;
class IntensionValue;
class LockBF;
class Predicate;
class Relation;
class Tuple;
class Tuple_Hash;
class WS_Extension;
class WS_Relation;

include(r_error.dd)
include(dname.dd)
include(domain.dd)
include(constr.dd)
include(attribut.dd)
include(predicat.dd)
include(tuple.dd)
include(intensin.dd)
include(IValue.dd)
include(ext.dd)
include(ws_ext.dd)
include(bf_ext.dd)
include(af_ext.dd)
include(relation.dd)
include(hash.dd)
#if sun
/*
** sunOS 4.1 defines major and minor as macros in sys/sysmacros.h
** The names major & minor are used by the relation library.
** The following undefines them so cpp doesn't get confused.
*/
#undef major
#undef minor
#endif
include(combine.dd)
include(afRel.dd)
include(bfRel.dd)
include(bfLock.dd)
include(wsRel.dd)
include(formRel.dd)
#endif
