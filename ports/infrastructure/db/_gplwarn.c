/* $MirOS: contrib/gnu/aux/_gplwarn.c,v 1.3 2005/04/19 16:05:38 tg Exp $ */
/* _MirOS: contrib/gnu/aux/_gplwarn.c,v 1.3 2005/04/19 16:05:38 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 *
 * The author hereby permits this work to be distributed according to
 * the GNU General Public License, Version 1 or any later version di-
 * stributed by the Free Software Foundation Europe, and in accordan-
 * ce with the terms of the GPL.
 */

#ifdef GPLVER
#define MYGPLVER ", Version " GPLVER
#define SGPLVER  "v" GPLVER
#endif

#ifndef MYGPLVER
#define MYGPLVER ""
#endif

#ifndef SGPLVER
#define SGPLVER ""
#endif


#ifdef lint
#define	__SECTSTRING(section, prefix, string)			\
	const char __ ## prefix [] = (string)
#elif defined(__ELF__) && defined(__GNUC__)
#define	__SECTSTRING(section, prefix, string)			\
	__asm__(".section " section				\
	"\n	.asciz	\"" string "\""				\
	"\n	.previous")
#else
#define	__SECTSTRING(section, prefix, string)			\
	static const char __ ## prefix []			\
	    __attribute__((__unused__)) = (string)
#endif

#if defined(lint) || !defined(__aout__) || !defined(__GNUC__)
#define	__TEXTSTRING(prefix, string)				\
	__SECTSTRING(".text", prefix, string)
#else
#define	__TEXTSTRING(prefix, string)				\
	static const char __ ## prefix []			\
	    __attribute__((__unused__,__section__(".text")))	\
	    = (string)
#endif


__SECTSTRING(".comment", rcsid,
    "$MirOS: contrib/gnu/aux/_gplwarn.c,v 1.3 2005/04/19 16:05:38 tg Exp $");

__SECTSTRING(".gnu.warning.*main", warntext,
    "Linking with " MYNAME " infects the result\\n\\t"
    "with the GNU General Public License" MYGPLVER "!");

__TEXTSTRING(auditor, "\\n\\t@(#)warning: Licence = GPL" SGPLVER "!\\n");
