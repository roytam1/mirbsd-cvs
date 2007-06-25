/*-
 * Copyright (c) 2007
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
 * This acknowledgement does not need to be reprinted if this work is
 * linked into a bigger work whose licence does not allow such clause
 * and the author of this work is given due credit in the bigger work
 * or its accompanying documents, where such information is generally
 * kept, provided that said credits are retained.
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

/* this is not a stand-alone file */
#ifndef LIBINTL_REDEFINE /* first time only */
static const char __rcsid_meat[] __attribute__((used)) =
    "$MirOS$";
#endif

char *
gettext(const char *s)
{
	return (libintl_unconst(s));
}

char *
dgettext(const char *x __unused, const char *s)
{
	return (libintl_unconst(s));
}

char *
dcgettext(const char *x __unused, const char *s, int n __unused)
{
	return (libintl_unconst(s));
}

char *
ngettext(const char *s, const char *t __unused, unsigned long n __unused)
{
	return (libintl_unconst(s));
}

char *
dngettext(const char *x __unused, const char *s, const char *t __unused,
    unsigned long n __unused)
{
	return (libintl_unconst(s));
}

char *
dcngettext(const char *x __unused, const char *s, const char *t __unused,
    unsigned long n __unused, int m __unused)
{
	return (libintl_unconst(s));
}

#ifdef LIBINTL_REDEFINE /* second+ time only */
char *
dcigettext(const char *x __unused, const char *s, const char *t __unused,
    int n __unused, unsigned long m __unused, int p __unused)
{
	return (libintl_unconst(s));
}
#endif

char *
textdomain(const char *x __unused)
{
	return (libintl_unconst(_nl_current_default_domain__));
}

char *
bindtextdomain(const char *x __unused, const char *y)
{
	return (libintl_unconst(y));
}

char *
bind_textdomain_codeset(const char *x __unused, const char *y)
{
	return (libintl_unconst(y));
}

#ifdef LIBINTL_REDEFINE /* second+ time only */
void
gettext_free_exp(void *x __unused)
{
	return;
}

int
gettextparse(void *x __unused)
{
	return (0);
}
#endif
