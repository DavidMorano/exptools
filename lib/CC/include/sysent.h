/*ident	"@(#)C++env:incl-master/proto-headers/sysent.h	1.3" */

#ifndef __SYSENT_H
#define __SYSENT_H

#ifndef __TYPES_H
#include <sys/types.h>
#endif

#ifndef __WAIT_H
#include <sys/wait.h>
#endif

#ifndef __PTRACE_H
#include <sys/ptrace.h>
#endif

extern "C" {
	void _exit(int);
	int access(const char*, int);
	int acct(const char*);
	int chdir(const char*);
	int chroot(const char*);
	int close(int);
	int dup(int);
	void exit(int);
	int ioctl(int, int ...);
	int link(const char*, const char*);
	int nice(int);
	void pause();
	int pipe(int*);
	void sync();
	int unlink(const char*);
	int system(const char*);
	int execl(const char*, const char* ...);
	int execle(const char*, const char* ...);
	int execlp(const char*, const char* ...);
	int execv(const char*, const char*[]);
	int execve(const char*, const char*[], const char*[]);
	int execvp(const char*, const char*[]);

	int chmod(const char*, int);
	int chown(const char*, int, int);
	int creat(const char*, int);
	int fork();
	int getpid();
	int getppid();
	int kill(int, int);
	int open(const char*, int, int mode=0666);
	long ulimit(int, long);
	int umask(int);
	int lockf(int, int, long);
	int mknod(const char*, int, int);
	int dup2(int, int);
	int mkdir(const char*, int);
	int rmdir(const char*);
	int rename(const char*, const char*);
	int async_daemon();
	int getdirentries(int, char*, int, long*);
	int fchmod(int, int);
	int fchown(int, int, int);
	int fsync(int);
	int getdomainname(char*, int);
	int getgroups(int, int*);
	int gethostname(char*, int);
	void profil(const char*, int, int, int);
	int readlink(const char*, char*, int);
	int setdomainname(const char*, int);
	int setgroups(int, const int*);
	int sethostname(const char*, int);
	int shutdown(int, int);
	int swapon(const char*);
	int symlink(const char*, const char*);
	int vfork();
	int write(int, const void*, int);
	int read(int, void*, int);
	off_t lseek(int, off_t, int);
	int ftruncate(int, off_t);
	int truncate(const char*, off_t);
	int getdtablesize();
	int flock(int, int);
	long gethostid();
	int getpagesize();
	int killpg(int, int);
	int syscall(int ...);
	int vadvise(int);
	int brk(caddr_t);
	int fchdir(int);
	int fchroot(int);
	int setuid(int);
	int setgid(int);
	int getegid();
	int geteuid();
	int getgid();
	int getuid();
	int mount(const char*, const char*, int, caddr_t);
	int unmount(const char*);
	int nfssvc(int);
	int sleep(unsigned);
	unsigned alarm(unsigned);
	int getpgrp(int);
	caddr_t sbrk(int);
	int setegid(int);
	int seteuid(int);
	int setpgrp(int, int);
	int setreuid(int, int);
	int setregid(int, int);
	int setrgid(int);
	int setruid(int);
	void vhangup();
}

#endif
