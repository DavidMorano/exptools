/*ident	"@(#)C++env:incl-master/proto-headers/stdio.h	1.3" */

#ifndef __STDIO_H
#define __STDIO_H

#ifndef __ERRNO_H
#include <errno.h>
#endif


#define ctermid ______ctermid
#define cuserid ______cuserid
#define fdopen ______fdopen
#define fopen ______fopen
#define freopen ______freopen
#define fgets ______fgets
#define ftell ______ftell
#define gets ______gets
#define popen ______popen
#define rewind ______rewind
#define setbuf ______setbuf
#define tempnam ______tempnam
#define tmpfile ______tmpfile
#define tmpnam ______tmpnam
#define sprintf ______sprintf
#define fclose ______fclose
#define fflush ______fflush
#define fgetc ______fgetc
#define fprintf ______fprintf
#define fputc ______fputc
#define fputs ______fputs
#define fread ______fread
#define fscanf ______fscanf
#define fseek ______fseek
#define fwrite ______fwrite
#define getw ______getw
#define pclose ______pclose
#define printf ______printf
#define puts ______puts
#define putw ______putw
#define scanf ______scanf
#define setvbuf ______setvbuf
#define sscanf ______sscanf
#define system ______system
#define ungetc ______ungetc
#define utmpname ______utmpname
#define vfprintf ______vfprintf
#define vprintf ______vprintf
#define vsprintf ______vsprintf

/* need stddef.h for size_t */
#ifndef __STDDEF_H
#include <stddef.h>
#endif

#ifdef NULL
#undef NULL
#endif

/*	@(#)stdio.h 1.12 88/02/07 SMI; from UCB 1.4 06/30/83	*/

# ifndef FILE
#define	BUFSIZ	1024
#define _SBFSIZ	8
extern	struct	_iobuf {
	int	_cnt;
	unsigned char *_ptr;
	unsigned char *_base;
	int	_bufsiz;
	short	_flag;
	char	_file;		/* should be short */
} _iob[];

#define _IOFBF	0
#define	_IOREAD	01
#define	_IOWRT	02
#define	_IONBF	04
#define	_IOMYBUF	010
#define	_IOEOF	020
#define	_IOERR	040
#define	_IOSTRG	0100
#define	_IOLBF	0200
#define	_IORW	0400
#define	NULL	0
#define	FILE	struct _iobuf
#define	EOF	(-1)

#define	stdin	(&_iob[0])
#define	stdout	(&_iob[1])
#define	stderr	(&_iob[2])

#ifdef lint	/* so that lint likes (void)putc(a,b) */
extern int putc();
extern int getc();
#else
#define	getc(p)		(--(p)->_cnt>=0? ((int)*(p)->_ptr++):_filbuf(p))
#define putc(x, p)	(--(p)->_cnt >= 0 ?\
	(int)(*(p)->_ptr++ = (unsigned char)(x)) :\
	(((p)->_flag & _IOLBF) && -(p)->_cnt < (p)->_bufsiz ?\
		((*(p)->_ptr = (unsigned char)(x)) != '\n' ?\
			(int)(*(p)->_ptr++) :\
			_flsbuf(*(unsigned char *)(p)->_ptr, p)) :\
		_flsbuf((unsigned char)(x), p)))
#endif
#define	getchar()	getc(stdin)
#define	putchar(x)	putc((x),stdout)
#define	feof(p)		(((p)->_flag&_IOEOF)!=0)
#define	ferror(p)	(((p)->_flag&_IOERR)!=0)
#define	fileno(p)	((p)->_file)
#define	clearerr(p)	(void) ((p)->_flag &= ~(_IOERR|_IOEOF))

extern FILE	*fopen();
extern FILE	*fdopen();
extern FILE	*freopen();
extern FILE	*popen();
extern FILE	*tmpfile();
extern long	ftell();
extern char	*fgets();
extern char	*gets();
#ifdef vax
char	*sprintf();		/* too painful to do right */
#endif
extern char	*ctermid();
extern char	*cuserid();
extern char	*tempnam();
extern char	*tmpnam();

#define L_ctermid	9
#define L_cuserid	9
#define P_tmpdir	"/usr/tmp/"
#define L_tmpnam	(sizeof(P_tmpdir) + 15)
# endif
 

#undef freopen
#undef cuserid
#undef tmpnam
#undef tmpfile
#undef tempnam
#undef fwrite
#undef printf
#undef puts
#undef fprintf
#undef fputs
#undef putw
#undef fread
#undef setvbuf
#undef utmpname
#undef fgetc
#undef scanf
#undef sprintf
#undef fscanf
#undef fseek
#undef vprintf
#undef system
#undef vfprintf
#undef gets
#undef ftell
#undef fclose
#undef fopen
#undef fdopen
#undef fgets
#undef sscanf
#undef getw
#undef vsprintf
#undef ctermid
#undef ungetc
#undef pclose
#undef fputc
#undef popen
#undef fflush
#undef setbuf
#undef rewind

extern "C" {
	int _filbuf(FILE *);
	int fclose(FILE *);
	FILE *fdopen(int, const char *);
	int fflush(FILE *);
	int fgetc(FILE *);
	char *fgets(char *, int, FILE *);
	FILE *fopen(const char *, const char *);
	int fprintf(FILE *, const char * ...);
	int fputc(int, FILE *);
	int fputs(const char *, FILE *);
	FILE *freopen(const char *, const char *, FILE *);
	int fscanf(FILE *, const char * ...);
	int fseek(FILE *, long, int);
	long ftell(const FILE *);
	char *gets(char *);
	int getw(FILE *);
	int pclose(FILE *);
	FILE *popen(const char *, const char *);
	int printf(const char * ...);
	int puts(const char *);
	int putw(int, FILE *);
	void rewind(FILE *);
	int scanf(const char * ...);
	void setbuf(FILE *, char *);
	int sscanf(const char *, const char * ...);
	int ungetc(int, FILE *);
	int setvbuf(FILE *, char *, int, size_t);
	FILE *tmpfile();
        int fread(void *, int, int, FILE *);
        int fwrite(const void *, int, int, FILE *);
	int _flsbuf(unsigned char, FILE *);
#ifndef ferror
	int ferror(FILE *);
#endif
#ifndef feof
	int feof(FILE *);
#endif
#ifndef fileno
	int fileno(FILE *);
#endif
#ifndef clearerr
	void clearerr(FILE *);
#endif
 	char *sprintf(char *, const char * ...);
	int setbuffer(FILE *, char *, int);
	int setlinebuf(FILE *);
}

/* ANSI C says tmpnam belongs in stdio.h. It is also declared in stdlib.h */

extern "C" {
	char *tmpnam(char*);  
}

#endif
