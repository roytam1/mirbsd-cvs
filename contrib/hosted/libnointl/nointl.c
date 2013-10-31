/*-
 * Copyright (c) 2007, 2013
 *	Thorsten Glaser <tg@mirbsd.de>
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

#undef __unused		/* just in case this is built on GNU/Linux */
#include <sys/types.h>
#include <langinfo.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#define LIBINTL_INTERNAL
#include "libintl.h"

static const char __rcsid_intl[] __attribute__((__used__)) =
    "$MirOS: contrib/hosted/libnointl/nointl.c,v 1.8 2009/11/17 19:26:15 tg Exp $";

#undef __unused
#define __unused	__attribute__((__unused__))

/* hidden data symbols */
const char _nl_default_default_domain__[] = "messages";
const char _nl_default_dirname__[] = "/usr/share/locale";
const char *_nl_current_default_domain__ = _nl_default_default_domain__;
const char _nl_default_default_domain[] = "messages";
const char _nl_default_dirname[] = "/usr/share/locale";
const char *_nl_current_default_domain = _nl_default_default_domain__;
const char libintl_nl_default_default_domain[] = "messages";
const char libintl_nl_default_dirname[] = "/usr/share/locale";
const char *libintl_nl_current_default_domain = _nl_default_default_domain__;
int libintl_version = LIBINTL_VERSION;
char _nl_state_lock[/* arbitrary value */ 64] = "";
char libintl_gettext_germanic_plural[/* arbitrary value */ 64] = "";
void *_nl_domain_bindings__;
void *_nl_domain_bindings;
void *libintl_nl_domain_bindings;
int _nl_msg_cat_cntr;

/* hidden functions */
/*
 * luckily, for a C function, it doesn't matter how many arguments
 * we have, we can just return NULL/0 in all cases
 */
#define hiddenfunc(x)		\
	void *x(void);		\
				\
	void *			\
	x(void)			\
	{			\
		return (NULL);	\
	}
hiddenfunc(_nl_expand_alias)
hiddenfunc(_nl_explode_name)
hiddenfunc(_nl_find_domain)
hiddenfunc(_nl_find_language)
hiddenfunc(_nl_find_msg)
hiddenfunc(_nl_free_domain_conv)
hiddenfunc(_nl_init_domain_conv)
hiddenfunc(_nl_language_preferences_default)
hiddenfunc(_nl_load_domain)
hiddenfunc(_nl_locale_name)
hiddenfunc(_nl_locale_name_default)
hiddenfunc(_nl_locale_name_posix)
hiddenfunc(_nl_log_untranslated)
hiddenfunc(_nl_make_l10nflist)
hiddenfunc(_nl_normalize_codeset)
#undef hiddenfunc

/* public and semi-public functions */

void
libintl_gettext_extract_plural(const char *x __unused,
    void *y __unused, unsigned long *z __unused)
{
	return;
}

unsigned long
libintl_hash_string(const char *s)
{
	/*
	 * An adaptation of Peter Weinberger's (PJW) generic hashing
	 * algorithm based on Allen Holub's version. Assumes 32-bit
	 * output values to be compatible to GNU libintl.
	 * Source: Doctor Dobb's Journal
	 */
	unsigned long hash_value = 0, i;
	const unsigned char *datum = (const unsigned char *)s;

#define HIGH_BITS	(~((unsigned int)(~0) >> 8))
	while (*datum) {
		hash_value = (hash_value << 8) + *datum++;
		if ((i = hash_value & HIGH_BITS) != 0)
			hash_value = (hash_value ^ (i >> 24)) & ~HIGH_BITS;
	}
#undef HIGH_BITS
	return (hash_value);
}

int
libintl_once_singlethreaded(void *dummy __unused)
{
	return (1);
}

const char *
libintl_relocate(const char *s)
{
	return (s);
}

#undef locale_charset
const char *
locale_charset(void)
{
	return (nl_langinfo(CODESET));
}

#undef libintl_set_relocation_prefix
void
libintl_set_relocation_prefix(const char *a __unused, const char *b __unused)
{
	return;
}

/* repeat functions */
#undef gettext
#undef dgettext
#undef dcgettext
#undef ngettext
#undef dngettext
#undef dcngettext
#undef dcigettext
#undef textdomain
#undef bindtextdomain
#undef bind_textdomain_codeset
#include "meat.c"

#define gettext libintl_gettext
#define dgettext libintl_dgettext
#define dcgettext libintl_dcgettext
#define ngettext libintl_ngettext
#define dngettext libintl_dngettext
#define dcngettext libintl_dcngettext
#define dcigettext libintl_dcigettext
#define textdomain libintl_textdomain
#define bindtextdomain libintl_bindtextdomain
#define bind_textdomain_codeset libintl_bind_textdomain_codeset
#define gettext_free_exp libintl_gettext_free_exp
#define gettextparse libintl_gettextparse
#define LIBINTL_REDEFINE
#include "libintl.h"
#include "meat.c"

#undef gettext
#undef dgettext
#undef dcgettext
#undef ngettext
#undef dngettext
#undef dcngettext
#undef dcigettext
#undef textdomain
#undef bindtextdomain
#undef bind_textdomain_codeset
#undef gettext_free_exp
#undef gettextparse

#define gettext gettext__
#define dgettext dgettext__
#define dcgettext dcgettext__
#define ngettext ngettext__
#define dngettext dngettext__
#define dcngettext dcngettext__
#define dcigettext dcigettext__
#define textdomain textdomain__
#define bindtextdomain bindtextdomain__
#define bind_textdomain_codeset bind_textdomain_codeset__
#define gettext_free_exp gettext_free_exp__
#define gettextparse gettextparse__
#include "libintl.h"
#include "meat.c"
