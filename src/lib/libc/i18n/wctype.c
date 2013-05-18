/*-
 * Copyright (c) 2006, 2008
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
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

#include <wchar.h>

#define mir18n_attributes
#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/wctype.c,v 1.4 2007/02/02 21:06:23 tg Exp $");

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
	{ "title", wctype_title },
	{ "upper", wctype_upper },
	{ "xdigit", wctype_xdigit }
};

static int
ctype_property_cmp(const void *key, const void *item)
{
	return (strcmp((const char *)key,
	    ((const struct ctype_property *)item)->property));
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
