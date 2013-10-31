/* $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $ */

/*-
 * Copyright (c) 2007, 2013
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
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

#ifndef _LIBINTL_H

#include <locale.h>
#undef gettext

/* we emulate GNU gettext 0.16.1 */

#define LIBINTL_VERSION		0x001000
#define __USE_GNU_GETTEXT	1
#define __GNU_GETTEXT_SUPPORTED_REVISION(major)	\
	    ((major) == 0 || (major) == 1 ? 1 : -1)

#ifndef __BEGIN_DECLS
#if defined(__cplusplus)
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	}
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif
#endif

__BEGIN_DECLS
extern int libintl_version;
__END_DECLS

#endif /* !_LIBINTL_H */

#if !defined(_LIBINTL_H) || defined(LIBINTL_REDEFINE)

__BEGIN_DECLS
extern char *gettext(const char *)
    __attribute__((__format_arg__(1)));
extern char *dgettext(const char *, const char *)
    __attribute__((__format_arg__(2)));
extern char *dcgettext(const char *, const char *, int)
    __attribute__((__format_arg__(2)));
extern char *ngettext(const char *, const char *, unsigned long)
    __attribute__((__format_arg__(1)))
    __attribute__((__format_arg__(2)));
extern char *dngettext(const char *, const char *, const char *, unsigned long)
    __attribute__((__format_arg__(2)))
    __attribute__((__format_arg__(3)));
extern char *dcngettext(const char *, const char *, const char *,
    unsigned long, int)
    __attribute__((__format_arg__(2)))
    __attribute__((__format_arg__(3)));
extern char *dcigettext(const char *, const char *, const char *,
    int, unsigned long, int)
    __attribute__((__format_arg__(2)))
    __attribute__((__format_arg__(3)));
extern char *textdomain(const char *);
extern char *bindtextdomain(const char *, const char *);
extern char *bind_textdomain_codeset(const char *, const char *);

#ifdef LIBINTL_INTERNAL
extern void gettext_free_exp(void *);
extern int gettextparse(void *);
#endif /* LIBINTL_INTERNAL */
__END_DECLS

#endif /* !_LIBINTL_H || LIBINTL_REDEFINE */

#ifndef _LIBINTL_H
#define _LIBINTL_H

#ifdef LIBINTL_INTERNAL
__BEGIN_DECLS
extern void libintl_set_relocation_prefix(const char *, const char *);
extern void libintl_gettext_extract_plural(const char *, void *,
    unsigned long *);
extern unsigned long libintl_hash_string(const char *);
extern int libintl_once_singlethreaded(void *);
extern const char *libintl_relocate(const char *)
    __attribute__((__format_arg__(1)));
extern const char *locale_charset(void);
__END_DECLS
#endif /* LIBINTL_INTERNAL */

/*
 * Macro definitions for the above functions.
 * Since this API breaks const-cleanliness, we are required to unconstify.
 * This sucks, and we only do it for GCC and ICC (for now).
 */
#if defined(__GNUC__)
#define libintl_unconst(x) ({		\
	union {				\
		const void *cptr;	\
		void *vptr;		\
	} __UC_v;			\
					\
	__UC_v.cptr = (x);		\
	(__UC_v.vptr);			\
})
#else
#define libintl_unconst(x) ((char *)(x))
#endif

#define gettext(s)		libintl_unconst(s)
#define dgettext(x,s)		libintl_unconst(s)
#define dcgettext(x,s,n)	libintl_unconst(s)
#define ngettext(s,t,n)		libintl_unconst(s)
#define dngettext(x,s,t,n)	libintl_unconst(s)
#define dcngettext(x,s,t,n,m)	libintl_unconst(s)
#define dcigettext(x,s,t,n,m,p)	libintl_unconst(s)
#define textdomain(x)		libintl_unconst("messages")
#define bindtextdomain(x,y)	libintl_unconst(y)
#define bind_textdomain_codeset(x,y)		libintl_unconst(y)
#define libintl_set_relocation_prefix(x,y)	do { } while(0)

#endif /* !_LIBINTL_H */
