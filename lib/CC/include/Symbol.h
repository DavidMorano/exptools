#include "string_set.h"

class Symbol_initializer{
    static int inited;
    int local;
    void initialize();
    void cleanup();
public:
    inline Symbol_initializer();
    inline ~Symbol_initializer();
};
Symbol_initializer::Symbol_initializer(){
    if(!inited){
	initialize();
    }
}
Symbol_initializer::~Symbol_initializer(){
    if(local){
	cleanup();
    }
}
static Symbol_initializer symbol_initializer;

class Symbol{
    friend class Symbol_initializer;
public:
    inline Symbol();
    inline Symbol(const String& s);
    inline int operator==(const Symbol& b) const;
    inline int operator!=(const Symbol& b) const;
    inline int operator<(const Symbol& b) const;
    inline int operator<=(const Symbol& b) const;
    inline int operator>(const Symbol& b) const;
    inline int operator>=(const Symbol& b) const;
    inline String the_string() const;
    inline unsigned long hashval() const;
private:
    static Set(String)* table_ptr;
    static const String* nil;
    const String* sp;
};

Symbol::Symbol() : sp(nil) { 
}
Symbol::Symbol(const String& s){
    const String* result = table_ptr->contains(s);
    sp = result?result:table_ptr->insert(s);
}
int Symbol::operator==(const Symbol& b)const{
    return sp == b.sp; 
}
int Symbol::operator!=(const Symbol& b)const{
    return sp != b.sp; 
}
int Symbol::operator<(const Symbol& b)const{
    return sp < b.sp; 
}
int Symbol::operator<=(const Symbol& b)const{
    return sp <= b.sp; 
}
int Symbol::operator>(const Symbol& b)const{
    return sp > b.sp; 
}
int Symbol::operator>=(const Symbol& b)const{
    return sp >= b.sp; 
}
String Symbol::the_string()const{ 
    return *sp;
}
unsigned long Symbol::hashval() const{ 
    return (unsigned long)sp;
}
