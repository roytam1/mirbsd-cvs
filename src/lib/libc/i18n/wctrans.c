/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <wctype.h>

#define mir18n_caseconv
#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/wctrans.c,v 1.3 2006/11/01 20:01:20 tg Exp $");

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
