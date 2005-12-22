/* @(#)nixwrite.c	1.3 03/06/15 Copyright 1986, 2001-2003 J. Schilling */
/*
 *	Non interruptable extended write
 *
 *	Copyright (c) 1986, 2001-2003 J. Schilling
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

#include "io.h"
#include <errno.h>

EXPORT int
_nixwrite(f, buf, count)
	int	f;
	void	*buf;
	int	count;
{
	register char *p = (char *)buf;
	register int ret;
	register int total = 0;

	while (count > 0) {
		while ((ret = write(f, p, count)) < 0) {
			if (geterrno() == EINTR)
				continue;
			return (ret);	/* Any other error */
		}
		if (ret == 0)		/* EOF */
			break;

		total += ret;
		count -= ret;
		p += ret;
	}
	return (total);
}
