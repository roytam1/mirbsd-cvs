/*-
 * Copyright (c) 2008
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

#include <err.h>
#include "lib.h"

__RCSID("$MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $");

void *
xcalloc(size_t nmemb, size_t membsz)
{
	void *rv;

	if (nmemb == 0 || membsz == 0)
		errx(1, "xcalloc(%zu, %zu): zero space", nmemb, membsz);
	if (SIZE_MAX / nmemb < membsz)
		errx(1, "xcalloc(%zu, %zu): integer overflow", nmemb, membsz);
	if ((rv = calloc(nmemb, membsz)) == NULL)
		err(1, "xcalloc(%zu, %zu): out of memory allocating %zu bytes",
		    nmemb, membsz, nmemb * membsz);
	return (rv);
}

void *
xrealloc(void *ptr, size_t nmemb, size_t membsz)
{
	void *rv;

	if (ptr == NULL)
		return (xcalloc(nmemb, membsz));
	if (nmemb == 0 || membsz == 0)
		errx(1, "xrealloc(%zu, %zu): zero space", nmemb, membsz);
	if (SIZE_MAX / nmemb < membsz)
		errx(1, "xrealloc(%zu, %zu): integer overflow", nmemb, membsz);
	if ((rv = realloc(ptr, nmemb * membsz)) == NULL)
		err(1, "xrealloc(%zu, %zu): out of memory allocating %zu bytes",
		    nmemb, membsz, nmemb * membsz);
	return (rv);
}

void
xfree(void *ptr)
{
	if (ptr == NULL)
		warnx("xfree: NULL pointer given");
	else
		free(ptr);
}

int
xasprintf(char **ret, const char *fmt, ...)
{
	va_list ap;
	int rv;

	va_start(ap, fmt);
	rv = xvasprintf(ret, fmt, ap);
	va_end(ap);

	return (rv);
}

int
xvasprintf(char **ret, const char *fmt, va_list ap)
{
	int rv;

	if (ret == NULL)
		errx(1, "xvasprintf: NULL pointer given");
	if ((rv = vasprintf(ret, fmt, ap)) < 0 || *ret == NULL)
		err(1, "xvasprintf: out of memory");

	return (rv);
}

void *
xstrdup(const void *s)
{
	void *rv;
	size_t n;

	if (s == NULL)
		s = (const void *)"";
	rv = xcalloc(1, (n = strlen((const char *)s) + 1));
	memcpy(rv, s, n);
	return (rv);
}
