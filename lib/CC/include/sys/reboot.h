/*ident	"@(#)C++env:incl-master/proto-headers/sys/reboot.h	1.1" */

#ifndef __REBOOT_H
#define __REBOOT_H

#define reboot ______reboot

/*	@(#)reboot.h 2.10 88/02/08 SMI; from UCB 4.3 82/10/31	*/

/*
 * Arguments to reboot system call and flags to init.
 *
 * On the VAX, these are passed to boot program in r11,
 * and on to init.
 *
 * On the Sun, these are parsed from the boot command line
 * and used to construct the argument list for init.
 */
#define	RB_AUTOBOOT	0	/* flags for system auto-booting itself */

#define	RB_ASKNAME	0x001	/* ask for file name to reboot from */
#define	RB_SINGLE	0x002	/* reboot to single user only */
#define	RB_NOSYNC	0x004	/* dont sync before reboot */
#define	RB_HALT		0x008	/* don't reboot, just halt */
#define	RB_INITNAME	0x010	/* name given for /etc/init */
#define	RB_NOBOOTRC	0x020	/* don't run /etc/rc.boot */
#define	RB_DEBUG	0x040	/* being run under debugger */
#define	RB_DUMP		0x080	/* dump system core */
#define	RB_WRITABLE	0x100	/* mount root read/write */
#define	RB_STRING	0x200	/* pass boot args to prom monitor */
 

#undef reboot

extern "C" {
	int reboot(int, const char *bootargs=0);
}

#endif
