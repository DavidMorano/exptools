#ifndef VBLOCKH
#define VBLOCKH

#include <Block.h>

class Vb_ATTLC{
public:
    Vb_ATTLC(){};
    virtual ~Vb_ATTLC(){};
    virtual unsigned size()=0;
    virtual unsigned size(unsigned)=0;
    virtual void* elem(int i)=0;
    virtual void* beginning()=0;
    virtual void* finish()=0;
};

PT_names
	Vblock(T)     	Vblock_ T
PT_end

PT_define Vblockdeclare(T)
Blockdeclare(T);

class Vblock(T):public Vb_ATTLC{
private:
    Block(T) B;
    void* elem(int i){
	return &(*this)[i];
    }
    void* beginning(){
	return (T*)(*this);
    }
    void* finish(){
	return end();
    }
public:
    Vblock(T)(){}
    Vblock(T)(unsigned k):B(k){}
    Vblock(T)(const Vblock(T)& b):B(b.B){}

    Vblock(T)& operator=(const Vblock(T)& b){
	B=b.B;
	return *this;
    }
    operator T*(){ return B.operator T*(); }
    T* end(){ return B.end(); }
    T& operator[](int i) { return B.operator[](i);}
    unsigned size(){ return B.size(); }
    unsigned size(unsigned k){ return B.size(k); }
    int reserve(unsigned k) { return B.reserve(k); }
    void swap(Vblock(T)& b){B.swap(b.B);}
};
PT_end

PT_define Vblockimplement(T)  
Blockimplement(T)
PT_end

#endif
