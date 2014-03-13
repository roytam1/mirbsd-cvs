#ifndef _RANDOM_H_
#define _RANDOM_H_

#if !defined( lint ) && !defined( SABER )
/* #ident	"@(#)random.h	4.14 99/06/17 xlockmore" */

#endif

/*-
 * Random stuff
 *
 * See xlock.c for copying information.
 *
 * Revision History:
 * 17-06-99: Started log. :)
 */

/*** random number generator ***/
#define LRAND()		((long)(arc4random() & 0x7FFFFFFF))
#define NRAND(n)	((int)arc4random_uniform(n))
#define MAXRAND		(2147483648.0)
#define SRAND(n)	/* nothing */
#endif /* _RANDOM_H_ */
