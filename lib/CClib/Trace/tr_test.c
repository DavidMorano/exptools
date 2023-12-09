#include <iostream.h>
#include "c_tr_hdrs.h"

class junk {
public:
    junk (int i);
    void try (int i);
private:
    int id;
};

junk::junk (int i) {
    id = i;
}

void junk::try (int i) {
    f_trace trace ("junk::try", "i", i);
    trace.write (MED, __LOC__, "inside function junk::try");
    if (i == id) {
        cout << "matched\n";
    }
    else {
        cout << "not matched\n";
	trace.write (LOW, __LOC__, "i", i, "id", id);
    }
}

void
doit () {
    f_trace trace ("doit");
    trace.write (MED, __LOC__, "inside function doit");
    trace.write (LOW, __LOC__, "doit");
}

void
checkit () {
    f_trace trace ("checkit");
    trace.write (MED, __LOC__, "inside function checkit");
    trace.write (LOW, __LOC__, "checkit");
}

void
stopit () {
    f_trace trace ("stopit");
    trace.write (MED, __LOC__, "inside function stopit");
    trace.write (LOW, __LOC__, "stopit");
}

int CMS_err;

void
main (int argc, char *argv[]) {
    p_trace trace (argv[0], "argc", argc, "argv[1]", argv[1]);
    int i = atoi (argv[1]);
    junk junkie (i);
    doit ();
    for (i = 0; i < 10; i++) {
	junkie.try (i);
    }
    checkit ();
    stopit ();
}
