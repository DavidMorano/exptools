#ifndef OBJECTXXXH
#define OBJECTXXXH

typedef int Objection_action(const char*);

class Objection {
    Objection_action* action;
    Objection_action* def_action;

    static int Default(const char*);
    static int Ignore(const char*);
public:
    Objection() { 
        action = Objection::Default;
        def_action = Objection::Default;
    }
    Objection(Objection_action* f) { 
        action = Objection::Default;
        def_action = f;
    }
    int raise(const char* s = "") { 
        int i = (*action)(s);
        if( i == 0 ) {
           if( def_action ) (*def_action)(s);
           return 0;
        }
        else return i;
    }
    Objection_action* appoint(Objection_action *f = 0) {
        Objection_action* old_action = action;
        action = f ? f : Objection::Default;
        return old_action;
    }
    Objection_action* ignore() {
        return appoint(Objection::Ignore);
    }
};

#endif
