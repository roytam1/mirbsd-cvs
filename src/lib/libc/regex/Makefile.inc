# $MirOS: src/lib/libc/regex/Makefile.inc,v 1.3 2007/02/12 05:51:51 tg Exp $
# $OpenBSD: Makefile.inc,v 1.6 2005/04/15 02:07:04 millert Exp $
# @(#)Makefile.inc	8.1 (Berkeley) 6/4/93

# regex sources
.PATH: ${LIBCSRCDIR}/regex

CPPFLAGS+=	-DPOSIX_MISTAKE

.ifndef _MODSRC_LIB_LIBC_REGEX_NOSRCS
SRCS+=	regcomp.c regerror.c regexec.c regfree.c

MAN+=	regex.3 re_format.7

MLINKS+=regex.3 regcomp.3 regex.3 regexec.3 regex.3 regerror.3 regex.3 regfree.3
.endif