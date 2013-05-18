#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $
#-
# Copyright (c) 2004, 2006
#	Thorsten Glaser <tg@mirbsd.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a defect.
#-
# call this with the canonical target name as parameter
# install stuff into $CROSSDIR/usr/include first, eg a crosscompiler
# to i386-pc-linux-gnu needs pthread.h and the likes during build...

if [[ $1 = -a ]]; then
	no_Ada=No
	shift
else
	no_Ada=Yes
fi

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
    make obj )

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
	NOPIC=Yes \
	_CROSSBUILD=defined \
	all install )
set +e

cp $CROSSDIR/host-tools/lib/*.o $CROSSDIR/usr/lib/

rm -rf $CROSSDIR/usr/obj/gcc

set +x
print
print done.
