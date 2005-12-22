/* $MirOS: contrib/gnu/aux/_gplwarn.c,v 1.6 2005/12/17 05:46:10 tg Exp $ */
/* _MirOS: contrib/gnu/aux/_gplwarn.c,v 1.6 2005/12/17 05:46:10 tg Exp $ */

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
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
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
#define	__SECTSTRING(segment, prefix, string)			\
	static const char __LINTED__ ## segment ## _ ## prefix [] = (string)
#elif defined(__ELF__) && defined(__GNUC__)
#define	__SECTSTRING(segment, prefix, string)			\
	__asm__(".section " segment				\
	"\n	.ascii	\"" #prefix ": \""			\
	"\n	.asciz	\"" string "\""				\
	"\n	.previous")
#else
#define	__SECTSTRING(segment, prefix, string)			\
	static const char __ ## prefix []			\
	    __attribute__((used)) = (string)
#endif

#if defined(lint) || !defined(__aout__) || !defined(__GNUC__)
#define	__TEXTSTRING(prefix, string)				\
	__SECTSTRING(".text", prefix, string)
#else
#define	__TEXTSTRING(prefix, string)				\
	static const char __ ## prefix []			\
	    __attribute__((used,__section__(".text")))		\
	    = (string)
#endif


__SECTSTRING(".comment", rcsid,
    "$MirOS: contrib/gnu/aux/_gplwarn.c,v 1.6 2005/12/17 05:46:10 tg Exp $");

__SECTSTRING(".gnu.warning.*main", warntext,
    "Linking with " MYNAME " infects the result\\n\\t"
    "with the GNU General Public License" MYGPLVER "!");

__TEXTSTRING(auditor, "\\n\\t@(#)warning: Licence = GPL" SGPLVER "!\\n");
