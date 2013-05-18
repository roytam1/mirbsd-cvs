/* $MirOS: src/lib/libc/i18n/wctrans.c,v 1.1 2006/06/01 22:17:21 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <wctype.h>

#define mir18n_caseconv
#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/wctrans.c,v 1.1 2006/06/01 22:17:21 tg Exp $");

/* this is, admittedly, taken from libutf8 */
struct trans_property {
	const char *property;
	wctrans_t translation;
};

static int trans_property_cmp(const void *, const void *);

static struct trans_property all_properties[] = {
	{ "tolower", tolower_table },
	{ "toupper", toupper_table }
};

static int
trans_property_cmp(const void *key, const void *item)
{
	return (strcmp((const char *)key,
	    ((const struct trans_property *)item)->property));
}

wctrans_t
wctrans(const char *property)
{
	struct trans_property *rv;

	rv = bsearch(property, all_properties,
	    (sizeof (all_properties) / sizeof (all_properties[0])),
	    sizeof (struct trans_property), trans_property_cmp);
	return ((rv == NULL) ? NULL : rv->translation);
}
