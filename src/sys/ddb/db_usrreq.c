/**	$MirOS: src/sys/ddb/db_usrreq.c,v 1.3 2006/10/18 00:52:26 tg Exp $ */
/*	$OpenBSD: db_usrreq.c,v 1.9 2004/02/06 22:19:21 tedu Exp $	*/

/*
 * Copyright © 2006, 2013
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 * Copyright (c) 1996 Michael Shalayeff.  All rights reserved.
 * Copyright (c) 1986, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/types.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <uvm/uvm_extern.h>
#include <sys/sysctl.h>

#include <ddb/db_output.h>
#include <ddb/db_var.h>

static void paniK(const char *, ...)
    __attribute__((__format__(__kprintf__, 1, 2)));

int	db_log = 1;
int	db_allowcrash = 0;

int
ddb_sysctl(name, namelen, oldp, oldlenp, newp, newlen, p)
	int	*name;
	u_int	namelen;
	void	*oldp;
	size_t	*oldlenp;
	void	*newp;
	size_t	newlen;
	struct proc *p;
{
	int error, ctlval;

	/* All sysctl names at this level are terminal. */
	if (namelen != 1)
		return (ENOTDIR);

	switch (name[0]) {

	case DBCTL_RADIX:
		return sysctl_int(oldp, oldlenp, newp, newlen, &db_radix);
	case DBCTL_MAXWIDTH:
		return sysctl_int(oldp, oldlenp, newp, newlen, &db_max_width);
	case DBCTL_TABSTOP:
		return sysctl_int(oldp, oldlenp, newp, newlen, &db_tab_stop_width);
	case DBCTL_MAXLINE:
		return sysctl_int(oldp, oldlenp, newp, newlen, &db_max_line);
	case DBCTL_PANIC:
		ctlval = db_panic;
		if ((error = sysctl_int(oldp, oldlenp, newp, newlen, &ctlval)) ||
		    newp == NULL)
			return (error);
		if (ctlval != 1 && ctlval != 0)
			return (EINVAL);
		if (ctlval > db_panic && securelevel > 1)
			return (EPERM);
		db_panic = ctlval;
		return (0);
	case DBCTL_CONSOLE:
		ctlval = db_console;
		if ((error = sysctl_int(oldp, oldlenp, newp, newlen, &ctlval)) ||
		    newp == NULL)
			return (error);
		if (ctlval != 1 && ctlval != 0)
			return (EINVAL);
		if (ctlval > db_console && securelevel > 1)
			return (EPERM);
		db_console = ctlval;
		return (0);
	case DBCTL_LOG:
		return (sysctl_int(oldp, oldlenp, newp, newlen, &db_log));
	case DBCTL_CRASH:
		ctlval = db_allowcrash;
		if ((error = sysctl_int(oldp, oldlenp, newp, newlen, &ctlval)) ||
		    newp == NULL)
			return (error);
		switch (ctlval) {
		case 0:
			db_allowcrash = 0;
			break;
		case 1:
			if (securelevel > 0)
				return (EPERM);
			db_allowcrash = 1;
			break;
		default:
			if (!db_allowcrash)
				return (EPERM);
			paniK("ddb user requested panic: sysctl ddb.crash=%d",
			    ctlval);
			printf("db_usrreq.c: recovering sysop after panik\n");
		}
		return (0);
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
}

/* this comes from panic() in kern/subr_prf.c - keep it in sync */
static void
paniK(const char *fmt, ...)
{
	va_list ap;
	void (*tmp_panic_hook)(void) = panic_hook;

	if (panic_hook) {
		panic_hook = NULL;
		tmp_panic_hook();
	}

	printf("panic: ");
	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);

#ifdef KGDB
	kgdb_panic();
#endif
#ifdef KADB
	if (boothowto & RB_KDB)
		kdbpanic();
#endif
#ifdef DDB
	if (db_panic)
		Debugger();
	else
		db_stack_dump();
#endif

	panic_hook = tmp_panic_hook;
}
