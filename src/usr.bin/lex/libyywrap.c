/*	$OpenBSD: libyywrap.c,v 1.6 2003/07/28 20:38:31 deraadt Exp $	*/

/* libyywrap - flex run-time support library "yywrap" function */

/* $Header$ */

#include <sys/cdefs.h>

int yywrap(void);

int
yywrap(void)
{
	return 1;
}
