#!/bin/mksh
# $MirOS: src/scripts/xbuild-gcc.sh,v 1.6 2006/03/01 13:28:34 tg Exp $
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
# All advertising materials mentioning features or use of this soft-
# ware must display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.
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

[[ -z $CROSSDIR ]] && CROSSDIR=${DESTDIR}/usr/cross/${TARGET}

if [[ ! -s $CROSSDIR/T_BASEENV ]]; then
	print -u2 Run xbuild-env.sh first.
	exit 1
fi

. $CROSSDIR/T_BASEENV

[[ -n $1 ]] && TARGET=$1
if [[ -z $TARGET ]]; then
	print -u2 No target given.
	exit 1
fi

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

( cd $BSDSRCDIR/gcc; \
    BSDSRCDIR=$BSDSRCDIR \
    BSDOBJDIR=$CROSSDIR/usr/obj \
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
	GCC_PREFIX=$CROSSDIR/usr \
	GCC_INFODIR=$CROSSDIR/usr/share/info \
	GCC_MANDIR=$CROSSDIR/usr/share/man \
	NOPIC=Yes \
	LDSTATIC=-static \
	_CROSSBUILD=defined \
	all install )

ln -f ${CROSSDIR}/usr/bin/$TARGET-gcc ${CROSSDIR}/usr/$TARGET/bin/cc

set +x
print
print done.
