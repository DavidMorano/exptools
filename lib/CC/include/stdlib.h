/*ident	"@(#)C++env:incl-master/proto-headers/stdlib.h	1.8" */

#ifndef __STDLIB_H
#define __STDLIB_H

#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifndef __PWD_H
#include <pwd.h>
#endif

#ifndef __RAND48_H
#include <rand48.h>
#endif

#ifndef __REGCMP_H
#include <regcmp.h>
#endif

#ifndef __ERRNO_H
#include <errno.h>
#endif

extern "C" {
	double atof(const char*);
	int atoi(const char*);
	long atol(const char*);
	const char* crypt(const char*, const char*);
	char *ecvt(double, int, int*, int*);
	void encrypt(char*, int);
	void exit(int);
	double fabs(double);
	char* fcvt(double, int, int*, int*);
	double frexp(double, int*);
	char *gcvt(double, int, char*);
	char *getenv(const char*);
	char *getlogin();
	char *getpass(const char*);
	int getpw(int, char*);
	int isatty(int);
	double ldexp(double, int);
	double modf(double, double*);
	char *mktemp(char*);
	void perror(const char*);
	void qsort(void*, size_t, size_t, int(*)(const void*, const void*));
	void setkey(const char*);
	void swab(const char*, char*, int);
	int system(const char*);
	long time(long*);
	char *tmpnam(char*);
	char *ttyname(int);
	int ttyslot();
	char *ctermid(char*);
	char *cuserid(char*);
	char *tempnam(const char*, const char*);
	int getopt(int, const char* const*, const char*);
	long a64l(const char*);
	char *getcwd(char*, int);
	void l3tol(long*, const char*, int);
	char *l64a(long);
	void ltol3(char*, const long*, int);
	int putenv(const char*);
	long clock();
	int abort(...); /* Args can be examined in dbx */
	unsigned alarm(unsigned);
	int bcmp(const void*, const void*, int);
	void bcopy(const void*, void*, int);
	void bzero(void*, int);
	int execl(const char*, const char* ...);
	int execle(const char*, const char* ...);
	int execlp(const char*, const char* ...);
	int execv(const char*, const char* argv[]);
	int execvp(const char*, const char* argv[]);
	int ffs(int);
	char *getwd(char*);
	char *initstate(unsigned, char*, int);
	int nice(int);
	void pause();
	long random();
	char *setstate(char*);
	int sleep(unsigned);
	void srandom(int);
	int lockf(int, int, long);
	long ulimit(int, long);
	int usleep(unsigned);
	int rand();
	int srand(int);
	double strtod(const char*, char**);
	long strtol(const char*, char**, int);
	void closelog();
	int endnetgrent();
	int getnetgrent(char**, char**, char**);
	int initgroups(char*, int);
	void openlog(const char*, int, int);
	int rnusers(const char*);
	int rresvport(int*);
	int ruserok(const char*, int, const char*, const char*);
	int setnetgrent(char*);
	void syslog(int, const char* ...);
	int rwall(const char*, const char*);
	int setlogmask(int);
}

extern char *optarg;
extern int optind, opterr;
extern char **environ;
extern int end, etext, edata;

#ifndef __MALLOC_H
#include <malloc.h>
#endif

#endif

