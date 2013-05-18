/* $MirOS: contrib/gnu/aux/_gplwarn.c,v 1.7 2006/06/02 20:55:28 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 * This acknowledgement does not need to be reprinted if this work is
 * linked into a bigger work whose licence does not allow such clause
 * and the author of this work is given due credit in the bigger work
 * or its documentation. Specifically, re-using this code in any work
 * covered by the GNU General Public License version 1 or Library Ge-
 * neral Public License (any version) is permitted.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
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
    "$MirOS: contrib/gnu/aux/_gplwarn.c,v 1.7 2006/06/02 20:55:28 tg Exp $");

__SECTSTRING(".gnu.warning.*main", warntext,
    "Linking with " MYNAME " infects the result\\n\\t"
    "with the GNU General Public License" MYGPLVER "!");

__TEXTSTRING(auditor, "\\n\\t@(#)warning: Licence = GPL" SGPLVER "!\\n");
