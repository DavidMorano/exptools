#ifndef FSMH
#define FSMH

#include <Objection.h>

class ostream;

class Chararray_ATTLC{
public:
    inline Chararray_ATTLC(
	unsigned int i,
	unsigned int j,
	unsigned int k
    );
    Chararray_ATTLC(
	const Chararray_ATTLC& x
    );
    inline ~Chararray_ATTLC();

    const Chararray_ATTLC& operator=(
	const Chararray_ATTLC& c
    );

    inline unsigned char& operator()( // unsigned -- jfi
	unsigned int i,
	unsigned int j,
	unsigned int k
    )const;
    inline unsigned int size(
        unsigned int i
    )const;
private:
    unsigned char* p;     // unsigned -- jfi
    unsigned int   a;
    unsigned int   b;
    unsigned int   c;
    unsigned int   ab;

    inline unsigned int linearize(
	unsigned int i,
	unsigned int j
    )const;
    inline unsigned int linearize(
	unsigned int i,
	unsigned int j,
	unsigned int k
    )const;
};

static const int MAX_ACTIONS=256;

class Fsm;

typedef int (*hptr)(Fsm& f,unsigned int input);
typedef void (*tptr)(const Fsm& f,int source,int input,int target);

typedef int Fsm_action(Fsm&,unsigned);
typedef void Fsm_tracer(const Fsm&,int,int,int);

class Fsm{
public:

    static Objection state_objection;
    static Objection input_objection;
    static Objection size_objection;

    Fsm(
	unsigned int	n, 
	unsigned int	init=0, 
	Fsm_action*	action=0
    );
    Fsm( const Fsm& f );
    inline ~Fsm();

    inline unsigned int nstates()const;

    inline unsigned int nactions()const;

    inline unsigned int state()const;

    inline unsigned int initial_state()const;

    Fsm_action* action(
	unsigned int	state,
	unsigned int	input
    )const;

    unsigned int action_number(
	unsigned int	state,
	unsigned int	input
    )const;

    unsigned int target(
	unsigned int	state,
	unsigned int	input
    )const;

    void trans(
	unsigned int	start,
	unsigned int	input,
	unsigned int	target,
	Fsm_action*	action=0
    );
    void trans(
	unsigned int	start,
	unsigned int	input1,
	unsigned int	input2,
	unsigned int	target,
	Fsm_action*		action=0
    );
    void trans(
	unsigned int	start,
	char*		re,
	unsigned int	target,
	Fsm_action*		action=0
    );
    int fire( unsigned int input );

    inline void reset();

    void go( unsigned int s );

    inline void abort();

    inline void trace( Fsm_tracer* t );

private:

    Chararray_ATTLC       c;
    unsigned int    size;
    unsigned int    current;
    unsigned int    initial;
    Fsm_tracer*     tracer;
    Fsm_action*     actions[MAX_ACTIONS];
    Fsm_action**    action_guard;
    Fsm_action**    point;
    Fsm_action*     last_action;
    int             ignore_input;

    const Fsm& operator=(const Fsm& f); // disable assignment

};

ostream& operator<<(ostream& out,const Fsm& f);

//  Inline function definitions

unsigned int Chararray_ATTLC::linearize(
    unsigned int i,
    unsigned int j
)const{
    return(b*i+j);
}
unsigned int Chararray_ATTLC::linearize(
    unsigned int i,
    unsigned int j,
    unsigned int k
)const{
    return (ab*k + linearize(i,j));
}
Chararray_ATTLC::Chararray_ATTLC(
    unsigned int i,
    unsigned int j,
    unsigned int k
){
    a=i;
    b=j;
    c=k;
    ab=a*b;
    p=new unsigned char[ab*c];    // unsigned -- jfi
}
Chararray_ATTLC::~Chararray_ATTLC(){
    delete[/*  ab*c */] p;
}
unsigned char& Chararray_ATTLC::operator()( // unsigned -- jfi
    unsigned int i,
    unsigned int j,
    unsigned int k
)const{
    return p[linearize(i,j,k)];
}
unsigned int Chararray_ATTLC::size(
    unsigned int i
)const{
    return( i==0? a : (i==1? b : c) );
}
Fsm::~Fsm(){
}
unsigned int Fsm::state()const{
    return current;
}
unsigned int Fsm::nstates()const{
    return size;
}
unsigned int Fsm::nactions()const{
    return action_guard-actions;
}
unsigned int Fsm::initial_state()const{
    return initial;
}
void Fsm::reset(){
    int source=current;
    current=initial;

    if(tracer){
	tracer(*this,source,-1,current);
    }
    ignore_input=1;
}
void Fsm::abort(){
    go(state());
}
void Fsm::trace(Fsm_tracer* t){
    tracer=t;
}

#endif
