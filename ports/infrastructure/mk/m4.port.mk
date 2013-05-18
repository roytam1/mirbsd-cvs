# $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $
#-
# Copyright (c) 2009
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-

# one of "any", "bsd" (-g old), "old" (-g new), "new" (-gP), "gnu"
USE_M4?=		any


# at least MirBSD #10, OpenBSD equivalent

.if ${USE_M4:L:Mbsd}
.  ifndef _HAVE_BSD_M4
_HAVE_BSD_M4!=		if [[ $$(${M4} -g \
			    <<<'changequote(","){format("%4s", "foo")}' \
			    2>&-) = '{ foo}' ]]; then echo Yes; else echo No; fi
MAKEFLAGS+=		_HAVE_BSD_M4=${_HAVE_BSD_M4:Q}
.  endif
.  if ${_HAVE_BSD_M4:L} != "yes"
USE_M4+=		gnu
.  endif
.endif


# at least MirBSD/OpenBSD 2008-08

.if ${USE_M4:L:Mold}
.  ifndef _HAVE_OLD_M4
_HAVE_OLD_M4!=		if [[ $$(${M4} -g \
			    <<<'changequote(","){format("%.8s", "foo")}' \
			    2>&-) = '{foo}' ]]; then echo Yes; else echo No; fi
MAKEFLAGS+=		_HAVE_OLD_M4=${_HAVE_OLD_M4:Q}
.  endif
.  if ${_HAVE_OLD_M4:L} != "yes"
USE_M4+=		gnu
.  endif
.endif


# at least MirBSD/OpenBSD 2009-11

.if ${USE_M4:L:Mnew}
.  ifndef _HAVE_NEW_M4
_HAVE_NEW_M4!=		if [[ $$(${M4} -gP \
			    <<<'m4_changequote(","){m4_format("%.8s", "foo")}' \
			    2>&-) = '{foo}' ]]; then echo Yes; else echo No; fi
MAKEFLAGS+=		_HAVE_NEW_M4=${_HAVE_NEW_M4:Q}
.  endif
.  if ${_HAVE_NEW_M4:L} != "yes"
USE_M4+=		gnu
.  endif
.endif


# definitively GNU m4 (gnu) or minimum version (gnu_1.x.y)

.if ${USE_M4:L:Mgnu_*}
USE_M4+=		gnu
.endif
.if ${USE_M4:L:Mgnu}
.  if ${M4} == "${LOCALBASE}/bin/gm4"
_HAVE_GNU_M4=		No
.  elif !defined(_HAVE_GNU_M4)
.    if ${USE_M4:L:Mgnu_*}
_HAVE_GNU_M4!=		${MKSH} ${PORTSDIR}/infrastructure/scripts/check-gm4 \
			    ${M4:Q} ${USE_M4:L:Mgnu_*:S/gnu_//:Q}
.    else
_HAVE_GNU_M4!=		if ${M4} --help >/dev/null 2>&1; then \
				echo Yes; else echo No; fi
.    endif
.  endif
.  if ${_HAVE_GNU_M4:L} != "yes"
.    if ${USE_M4:L:Mgnu_*}
MODM4_DEPENDS+=		:m4->=${USE_M4:L:Mgnu_*:S/gnu_//}:lang/m4
.    else
MODM4_DEPENDS+=		:m4-*:lang/m4
.    endif
M4=			${LOCALBASE}/bin/gm4
.  endif
.endif
