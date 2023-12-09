/*
** Last modified: Mon Mar 14 16:00:31 EST 1994
** Bill Carpenter, bill@attmail.com
*/
/*
** How to build "md5cbnews":
**
** [1]  Copy md5.c, md5.h, and md5cbnews.c (this file) to a convenient
**      directory.
**
** [2]  cc -o md5cbnews md5cbnews.c md5.c
**
** [3]  Move the resulting executable md5cbnews to some directory on your
**      $PATH.
**
**
** NOTE:  Code in this program is based on code embedded in the
** nntpclient library provided with cbnews NNTP newsreaders.
*/

#include <stdio.h>
#include "md5.h"

extern char *getpass(), *getenv();

main(argc, argv)
int argc;
char *argv[];
{
	char *authfile;
	FILE	*authfp;
	char default_authfile[2000];  /* ick, but who cares */
	char	authtemp[80];
	long	base_time;
	char	*nntppass;
	char	e_nntppass[80];
	int	i;
	MD5_CTX	mdContext;
	authfile = argv[1];
	if (!authfile)
	{
		char *home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "Usage:  %s path-to-authfile\n", argv[0]);
			exit (1);
		}
		sprintf(default_authfile, "%s/.nntpauth", home);
		authfile = default_authfile;
	}
	nntppass = getpass("NNTP Password: ");
	base_time = time((long*)0);
	(void)umask(077);  /* private stuff, no? */
	authfp = fopen(authfile,"w");
	if (authfp == NULL)
	{
		fprintf(stderr, "Couldn't open '%s' for writing\n", authfile);
	}
	fprintf(authfp, "%ld\n", base_time);
/*
 * MD5 encryption stuff done here
 */
	e_nntppass[0] = '\0';
	MD5Init(&mdContext);
	MD5Update(&mdContext, nntppass, strlen(nntppass));
	MD5Final(&mdContext);
	for (i = 0; i < 16; i++)
	{
		sprintf(authtemp,"%02x", mdContext.digest[i]);
		strcat(e_nntppass,authtemp);
	}
/*
 * END MD5 encryption stuff
 */
	fprintf(authfp, "%s", e_nntppass);
	fclose(authfp);
	fprintf(stderr, "Wrote %s\n\nDon't forget your password!\n", authfile);
	exit (0);
}
