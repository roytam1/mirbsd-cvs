/* @(#)rename.c	1.3 03/06/15 Copyright 1998-2003 J. Schilling */
#include <sys/cdefs.h>
__SCCSID("@(#)rename.c	1.3 03/06/15 Copyright 1998-2003 J. Schilling");
__RCSID("$MirOS$");
/*
 *	rename() for old systems that don't have it.
 *
 *	Copyright (c) 1998-2003 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#define	rename	__nothing__
#include <mconfig.h>
#include <stdio.h>	/* XXX not OK but needed for js_xx() in schily.h */
#include <unixstd.h>
#include <strdefs.h>
#include <statdefs.h>
#include <maxpath.h>
#include <standard.h>
#include <schily.h>
#undef	rename
#include <libport.h>

#ifndef	MAXPATHNAME
#define	MAXPATHNAME	1024
#endif

#if	MAXPATHNAME < 1024
#undef	MAXPATHNAME
#define	MAXPATHNAME	1024
#endif

#define	MAXNAME	MAXPATHNAME

#define	FILEDESC struct stat

#ifndef	HAVE_RENAME

EXPORT int
rename(old, new)
	const char	*old;
	const char	*new;
{
	char	nname[MAXNAME];
	char	bakname[MAXNAME];
	char	strpid[32];
	int	strplen;
	BOOL	savpresent = FALSE;
	int	serrno;
	FILEDESC xstat;

	strplen = js_snprintf(strpid, sizeof (strpid), ".%d", getpid());

	if (strlen(new) <= (MAXNAME-strplen) ||
	    strchr(&new[MAXNAME-strplen], '/') == NULL) {
		/*
		 * Save old version of file 'new'.
		 */
		strncpy(nname, new, MAXNAME-strplen);
		nname[MAXNAME-strplen] = '\0';
		js_snprintf(bakname, sizeof (bakname), "%s%s", nname, strpid);
		unlink(bakname);
		if (link(new, bakname) >= 0)
			savpresent = TRUE;
	}

	if (stat(new, &xstat) >= 0 && unlink(new) < 0)
		return (-1);

	/*
	 * Now add 'new' name to 'old'.
	 */
	if (link(old, new) < 0) {
		serrno = geterrno();
		/*
		 * Make sure not to loose old version of 'new'.
		 */
		if (savpresent) {
			unlink(new);
			link(bakname, new);
			unlink(bakname);
		}
		seterrno(serrno);
		return (-1);
	}
	if (unlink(old) < 0)
		return (-1);
	unlink(bakname);
	return (0);
}
#endif	/* HAVE_RENAME */
