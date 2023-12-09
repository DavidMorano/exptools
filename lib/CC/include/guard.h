#ifndef GUARDH
#define GUARDH

#ifdef GUARD
#define PT_guard(X) /-*guard X*-/
#define PT_endguard /-*endguard*-/
#else
#define PT_guard(X)
#define PT_endguard
#endif

#endif
