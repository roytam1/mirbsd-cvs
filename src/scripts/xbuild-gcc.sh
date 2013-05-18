#!/bin/mksh
# $MirOS: src/scripts/xbuild-gcc.sh,v 1.19 2007/06/12 22:54:36 tg Exp $
#-
# Copyright (c) 2004, 2006, 2007, 2009
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
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
# call this with the canonical target name as parameter
# install stuff into $CROSSDIR/usr/include first, eg a crosscompiler
# to i386-pc-linux-gnu needs pthread.h and the likes during build...

no_Ada=Yes
nopic=Yes
while getopts "ad" c; do
	case $c {
	(a)	no_Ada=No ;;
	(+a)	no_Ada=Yes ;;
	(+d)	nopic=Yes ;;
	(d)	nopic=No ;;
	}
done
shift $((OPTIND - 1))

[[ -n $1 ]] && TARGET=$1
if [[ -z $TARGET ]]; then
	print -u2 No target given.
	exit 1
fi

if [[ $TARGET != *-* ]]; then
	case $TARGET {
	(alpha|amd64|hppa|i386|m68k|m88k|powerpc|sparc|sparc64|vax)
		;;
	(amiga|hp300|mac68k|mvme68k)
		TARGET=m68k ;;
	(luna88k|mvme88k)
		TARGET=m88k ;;
	(macppc|mvmeppc)
		TARGET=powerpc ;;
	(sgi)
		TARGET=mips ;;
	(*)
		exit 1 ;;
	}
	TARGET=${TARGET}-ecce-mirbsd$(uname -r)
fi
[[ -z $CROSSDIR ]] && CROSSDIR=${DESTDIR}/usr/cross/${TARGET}

if [[ ! -s $CROSSDIR/T_BASEENV ]]; then
	print -u2 Run xbuild-env.sh first.
	exit 1
fi

. $CROSSDIR/T_BASEENV
export NOMAN=yes

set -e
set -x

( cd $BSDSRCDIR/gcc; \
    BSDSRCDIR=$BSDSRCDIR \
    BSDOBJDIR=$CROSSDIR/usr/obj \
    OStriplet=$HOST \
    MACHINE=$MACHINE \
    MACHINE_ARCH=$MARCH \
    MAKEOBJDIR=obj.$MACHINE \
    make \
	NO_ADA=$no_Ada \
	obj )

set -e
( cd $BSDSRCDIR/gcc; \
    BSDSRCDIR=$BSDSRCDIR \
    BSDOBJDIR=$CROSSDIR/usr/obj \
    CROSSCFLAGS=$CROSSCFLAGS \
    OStriplet=$HOST \
    MACHINE=$MACHINE \
    MACHINE_ARCH=$MARCH \
    GCCTARGET=$TARGET \
    make \
	GCC_NATIVE=Yes \
	NO_ADA=$no_Ada \
	NO_CXX=Yes \
	NO_OBJC=Yes \
	NO_JAVA=Yes \
	NO_PASCAL=Yes \
	NO_THREADS=Yes \
	NO_BOEHMGC=Yes \
	COMPILER_ONLY=Yes \
	GCC_PREFIX=$CROSSDIR/host-tools \
	GCC_INFODIR=$CROSSDIR/usr/share/info \
	GCC_MANDIR=$CROSSDIR/usr/share/man \
	NOPIC=$nopic \
	_CROSSBUILD=defined \
	all install )
set +e

cp $CROSSDIR/host-tools/lib/*.o $CROSSDIR/usr/lib/

rm -rf $CROSSDIR/usr/obj/gcc

set +x
print
print done.
