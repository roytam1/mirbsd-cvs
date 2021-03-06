divert(-1)dnl
# $MirOS: contrib/gnu/libtool/m4salt.inc,v 1.11 2008/05/02 23:42:41 tg Exp $
# $miros: contrib/gnu/libtool/m4salt.inc,v 1.11 2008/05/02 23:42:41 tg Exp $
#-
# Copyright (c) 2004, 2005, 2006, 2008
#	Free Software Foundation, Inc.
# Contributed under copyright assignment by:
#	Thorsten Glaser <tg@mirbsd.de>
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
# m4salt - include m4sugar (from Autoconf 2.60) for Autoconf 2.13 as
# well as enough magic to make GNU Libtool 1.5 work with Autoconf in
# both the 2.13 and 2.61 version. Provide a way for libtool.m4 later
# on to distinguish whether stuff has been fnordified or not.

define([AC_m4salt_INIT],
[builtin([include], [m4sugar.inc])dnl

dnl Undo some damage
m4_copy_unm4([m4_builtin])
m4_copy_unm4([m4_changequote])
m4_copy_unm4([m4_decr])
m4_copy_unm4([m4_define])
m4_copy_unm4([m4_defn])
m4_copy_unm4([m4_divert])
m4_copy_unm4([m4_divnum])
m4_copy_unm4([m4_errprint])
m4_copy_unm4([m4_esyscmd])
m4_copy_unm4([m4_ifdef])
m4_copy([m4_if], [ifelse])
m4_copy_unm4([m4_incr])
m4_copy_unm4([m4_index])
m4_copy_unm4([m4_indir])
m4_copy_unm4([m4_len])
m4_copy_unm4([m4_patsubst])
m4_copy_unm4([m4_popdef])
m4_copy_unm4([m4_pushdef])
m4_copy_unm4([m4_regexp])
m4_copy_unm4([m4_sinclude])
m4_copy_unm4([m4_syscmd])
m4_copy_unm4([m4_sysval])
m4_copy_unm4([m4_traceoff])
m4_copy_unm4([m4_traceon])
m4_copy_unm4([m4_translit])
m4_copy_unm4([m4_undefine])
m4_copy_unm4([m4_undivert])

m4_ifndef([m4_tmpdir], [m4_define([m4_tmpdir], [/tmp])])dnl

dnl Another identifier
define([m4_PACKAGE_VERSION], [fnord_acsalt])dnl

])dnl # AC_m4salt_INIT

dnl We don't have/want/need aclang.m4
define([AC_LANG_PUSH],
[AC_LANG_SAVE
ifelse([$1],
 [C], AC_LANG_C,
 [Fortran 77], AC_LANG_FORTRAN77,
 [Fortran], AC_LANG_FORTRAN77,
 [C++], AC_LANG_CPLUSPLUS)
])dnl # AC_LANG_PUSH

define([AC_LANG_POP],
[AC_LANG_RESTORE])dnl # AC_LANG_POP

define([AS_MESSAGE_LOG_FD], 5)dnl

dnl Initialisation of m4salt
dnl ------------------------

define([AC_m4salt_SPLIT],
[translit($1, ., [, ])])dnl

define([AC_m4salt_CANON],
[$1, $2])dnl

dnl AC_m4salt_VERIE(MAJOR1, MINOR1, MAJOR2, MINOR2, IFLOWER, IFGREATEROREQUAL)
define([AC_m4salt_VERIE],
[ifelse(builtin([eval], [$2 + $1 * 1000 < $4 + $3 * 1000]), [1],
 [$5], [$6])
])dnl

ifelse(m4_PACKAGE_VERSION, [fnord_acsalt],
[dnl We have already been called
],[
AC_m4salt_VERIE(AC_m4salt_CANON(AC_m4salt_SPLIT(AC_ACVERSION)),
		2, 50,
		[AC_m4salt_INIT
		define(AC_m4salt_OLD, [1])],
		[define(AC_m4salt_OLD, [0])])dnl
])dnl
