# $MirOS: src/distrib/special/mksh/Makefile,v 1.87 2015/10/05 17:58:55 tg Exp $
#-
# Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010,
#		2011, 2012, 2013, 2014, 2015, 2016
#	mirabilos <m@mirbsd.org>
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
# use CPPFLAGS=-DDEBUG __CRAZY=Yes to check for certain more stuff

.include <bsd.own.mk>

SRCDIR=		${BSDSRCDIR}/bin/mksh
.PATH: ${SRCDIR}

PROG=		mksh
SRCS=		edit.c eval.c exec.c expr.c funcs.c histrap.c jobs.c \
		lalloc.c lex.c main.c misc.c shf.c syn.c tree.c var.c
# env: HAVE_MKNOD=x
CPPFLAGS+=	-DMKSH_ASSUME_UTF8 -DMKSH_DISABLE_DEPRECATED -DMKSH_SMALL \
		-DHAVE_ATTRIBUTE_BOUNDED=1 -DHAVE_ATTRIBUTE_FORMAT=1 \
		-DHAVE_ATTRIBUTE_NORETURN=1 -DHAVE_ATTRIBUTE_PURE=1 \
		-DHAVE_ATTRIBUTE_UNUSED=1 -DHAVE_ATTRIBUTE_USED=1 \
		-DHAVE_SYS_TIME_H=1 -DHAVE_TIME_H=1 -DHAVE_BOTH_TIME_H=1 \
		-DHAVE_SYS_BSDTYPES_H=0 -DHAVE_SYS_FILE_H=1 \
		-DHAVE_SYS_MKDEV_H=0 -DHAVE_SYS_MMAN_H=1 -DHAVE_SYS_PARAM_H=1 \
		-DHAVE_SYS_RESOURCE_H=1 -DHAVE_SYS_SELECT_H=1 \
		-DHAVE_SYS_SYSMACROS_H=0 -DHAVE_BSTRING_H=0 -DHAVE_GRP_H=1 \
		-DHAVE_IO_H=0 -DHAVE_LIBGEN_H=1 -DHAVE_LIBUTIL_H=0 \
		-DHAVE_PATHS_H=1 -DHAVE_STDINT_H=1 -DHAVE_STRINGS_H=1 \
		-DHAVE_TERMIOS_H=1 -DHAVE_ULIMIT_H=0 -DHAVE_VALUES_H=0 \
		-DHAVE_CAN_INTTYPES=1 -DHAVE_CAN_UCBINTS=1 \
		-DHAVE_CAN_INT8TYPE=1 -DHAVE_CAN_UCBINT8=1 -DHAVE_RLIM_T=1 \
		-DHAVE_SIG_T=1 -DHAVE_SYS_ERRLIST=1 -DHAVE_SYS_SIGNAME=1 \
		-DHAVE_SYS_SIGLIST=1 -DHAVE_FLOCK=1 -DHAVE_LOCK_FCNTL=1 \
		-DHAVE_GETRUSAGE=1 -DHAVE_GETSID=1 -DHAVE_GETTIMEOFDAY=1 \
		-DHAVE_KILLPG=1 -DHAVE_MEMMOVE=1 -DHAVE_MKNOD=1 -DHAVE_MMAP=1 \
		-DHAVE_NICE=0 -DHAVE_REVOKE=1 -DHAVE_SETLOCALE_CTYPE=0 \
		-DHAVE_LANGINFO_CODESET=0 -DHAVE_SELECT=1 -DHAVE_SETRESUGID=1 \
		-DHAVE_SETGROUPS=1 -DHAVE_STRERROR=0 -DHAVE_STRSIGNAL=0 \
		-DHAVE_STRLCPY=1 -DHAVE_FLOCK_DECL=1 -DHAVE_REVOKE_DECL=1 \
		-DHAVE_SYS_ERRLIST_DECL=1 -DHAVE_SYS_SIGLIST_DECL=1 \
		-DHAVE_PERSISTENT_HISTORY=0 -DMKSH_BUILD_R=523
CPPFLAGS+=	-D${${PROG:L}_tf:C/(Mir${MAN:E}{0,1}){2}/4/:S/x/mksh_BUILD/:U}
CPPFLAGS+=	-I.
CPPFLAGS+=	-DMIRBSD_BOOTFLOPPY
COPTS+=		-std=c89 -Wall

DEBUGFILE?=	No
.if ${DEBUGFILE:L} == "yes"
CPPFLAGS+=	-DDF=mksh_debugtofile
.endif

OPTGENS!=	cd ${SRCDIR:Q} && echo *.opt
.for _i in ${OPTGENS}
GENERATED+=	${_i:R}.gen
${_i:R}.gen: ${_i} ${SRCDIR}/Build.sh
	/bin/sh ${SRCDIR:Q}/Build.sh -G ${SRCDIR:Q}/${_i:Q}
.endfor
CLEANFILES+=	${GENERATED}

${PROG} beforedepend: ${GENERATED}

regress: ${PROG} check.pl check.t
	-rm -rf regress-dir
	mkdir -p regress-dir
	echo export FNORD=666 >regress-dir/.mkshrc
	HOME=$$(realpath regress-dir) perl ${SRCDIR}/check.pl \
	    -s ${SRCDIR}/check.t -v -p ./${PROG} \
	    -C shell:legacy-no,int:32,smksh,convfds,no-histfile,fastbox

cleandir: clean-extra

clean-extra: .PHONY
	-rm -rf regress-dir

mksh_tf=xMakefile${OStype:S/${MACHINE_OS}/1/1g}${OSNAME}
.include <bsd.prog.mk>
