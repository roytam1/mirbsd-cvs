/* $MirOS: contrib/code/libhaible/wctype.c,v 1.1 2006/05/30 11:34:21 tg Exp $ */

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

#include <wchar.h>

#define mir18n_attributes
#include "mir18n.h"

__RCSID("$MirOS: contrib/code/libhaible/wctype.c,v 1.1 2006/05/30 11:34:21 tg Exp $");

/* this is, admittedly, taken from libutf8 */
struct ctype_property {
	const char *property;
	wctype_t ctype;
};

static int ctype_property_cmp(const void *, const void *);

/*
 * keep this sorted for bsearch, we're not as stupid as the
 * FSF to do a linear search if we can do better ;)
 */
static struct ctype_property all_properties[] = {
	{ "alnum", wctype_alnum },
	{ "alpha", wctype_alpha },
	{ "blank", wctype_blank },
	{ "cntrl", wctype_cntrl },
	{ "digit", wctype_digit },
	{ "graph", wctype_graph },
	{ "lower", wctype_lower },
	{ "print", wctype_print },
	{ "punct", wctype_punct },
	{ "space", wctype_space },
	{ "upper", wctype_upper },
	{ "xdigit", wctype_xdigit }
};

static int
ctype_property_cmp(const void *s1, const void *s2)
{
	return (strcmp(((const struct ctype_property *)s1)->property,
	    ((const struct ctype_property *)s2)->property));
}

wctype_t
wctype(const char *property)
{
	struct ctype_property *rv;

	rv = bsearch(property, all_properties,
	    (sizeof (all_properties) / sizeof (all_properties[0])),
	    sizeof (struct ctype_property), ctype_property_cmp);
	return ((rv == NULL) ? 0 : rv->ctype);
}
