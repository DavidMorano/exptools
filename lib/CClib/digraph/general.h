#ifndef	GENERAL_H
#define	GENERAL_H

/*
			AT&T - PROPRIETARY
	THIS DOCUMENT CONTAINS PROPRIETARY INFORMATION OF
	AT&T AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN
	ACCORDANCE WITH APPLICABLE AGREEMENTS.
	
		Copyright (c) 1988 AT&T
		Unpublished & Not for Publication
		All Rights Reserved
*/

#ident	"%M% %I% %G%"
#ident	"%W%"


/**

.File Name
	general.h
.Author
	Joe Eccles
.Date Created
	October, 1988
.Description
	Contains general defines and typedefs.
.Constraints

.Notes

.See Also

.Standards
This file conforms to the Dept. 54141 C Coding Standards.

**/


/*	System Header Files					*/

/*	Project Header Files					*/

/*	Symbolic Constant Definitions				*/

#define SUCCESS	0	/* Normal function return */
#define FAILURE	-1	/* Abnormal function return */
#define ERROR	-1	/* Abnormal Function return (For DCTN compatibility) */

#ifndef TRUE
#define TRUE	1
#endif TRUE

#ifndef FALSE
#define FALSE	0
#endif FALSE

#define NULL 0

/*	Macro Definitions					*/

/*	Typedefs, Structure and Union Declarations		*/

typedef enum { true = 1, false = 0 } Bool;

/*	External Variable Declarations				*/

/*	Function Declarations					*/

#endif
