/* $MirOS$ */
/* @(#)ccomdefs.h	1.3 03/06/15 Copyright 2000 J. Schilling */
/*
 *	Various compiler dependant macros.
 *
 *	Copyright (c) 2000 J. Schilling
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

#ifndef _CCOMDEFS_H
#define	_CCOMDEFS_H

/*
 * Do not use printflike - it yields a warning, because
 * dear Mr Schily has decided to enhance printflikes...
 */

#define	__printflike__(fmtarg, firstvararg)
#define	__printf0like__(fmtarg, firstvararg)
#define	__scanflike__(fmtarg, firstvararg) \
		__attribute__((__format__(__scanf__, fmtarg, firstvararg)))

#endif	/* _CCOMDEFS_H */
