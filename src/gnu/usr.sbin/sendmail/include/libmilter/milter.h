/*
 * Copyright (c) 1999-2003, 2006 Proofpoint, Inc. and its suppliers.
 *	All rights reserved.
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the sendmail distribution.
 *
 *
 *	$Id$
 */

/*
**  MILTER.H -- Global definitions for mail filter.
*/

#ifndef _LIBMILTER_MILTER_H
# define _LIBMILTER_MILTER_H	1

#include "sendmail.h"
#include "libmilter/mfapi.h"

/* socket and thread portability */
# include <pthread.h>
typedef pthread_t	sthread_t;
typedef int		socket_t;

#endif /* ! _LIBMILTER_MILTER_H */
