#!/bin/mksh
# $MirOS: src/scripts/xbuild-binutils.sh,v 1.9 2006/06/11 00:23:55 tg Exp $
#-
# Copyright (c) 2004, 2005, 2006
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

[[ -n $1 ]] && TARGET=$1
[[ -n $2 ]] && EMULATION=$2

[[ -z $CROSSDIR ]] && CROSSDIR=${DESTDIR}/usr/cross/${TARGET}

if [[ ! -s $CROSSDIR/T_BASEENV ]]; then
	print Run xbuild-env.sh first.
	exit 1
fi

. $CROSSDIR/T_BASEENV
export SHELL=$MKSH

if [[ -z $TARGET ]]; then
	print -u2 No target given.
	exit 1
fi

if [[ -z $EMULATION ]]; then
	EMULATION=$( \
	    targ=$TARGET; \
	    . $BSDSRCDIR/gnu/usr.bin/binutils/ld/configure.tgt; \
	    print -r -- $targ_emul)
fi

if ! ld -V 2>&1 | fgrep -w $EMULATION >/dev/null 2>&1; then
	print -ru2 -- Target emulation \"$EMULATION\" not known.
	print -ru2 -- Execute \"ld -V\" to list known targets.
	exit 1
fi

cp="$SHELL $BSDSRCDIR/gnu/share/move-if-change -c"
set -e
set -x

sed -e "s#@@TARGET@@#${TARGET}#" \
    -e "s#@@EMUL@@#${EMULATION}#" \
    <$BSDSRCDIR/scripts/xbuild-tool.sed \
    >$CROSSDIR/usr/bin/cross-binutil.sh
chmod 555 $CROSSDIR/usr/bin/cross-binutil.sh

for binutil in ar ld nm objcopy objdump ranlib size strip; do
	ln -f $CROSSDIR/usr/bin/cross-binutil.sh $CROSSDIR/host-tools/bin/$binutil
done
rm -f $CROSSDIR/usr/bin/cross-binutil.sh

$cp /usr/include/bfd.h /usr/include/bfdver.h /usr/lib/libbfd.la \
    $BSDSRCDIR/gnu/usr.bin/binutils/bfd/obj.$MACHINE/

$cp /usr/lib/libopcodes.la \
    $BSDSRCDIR/gnu/usr.bin/binutils/opcodes/obj.$MACHINE/

( cd $BSDSRCDIR/gnu/usr.bin/binutils/gas; \
    BSDSRCDIR=$BSDSRCDIR \
    BSDOBJDIR=$BSDOBJDIR \
    OStriplet=$HOST \
    MACHINE=$MACHINE \
    MACHINE_ARCH=$MACHINE_ARCH \
    GCCTARGET=$TARGET \
    CFARGS="--with-sysroot=$CROSSDIR" \
    make -f Makefile.bsd-wrapper )

install -c -s -o $BINOWN -g $BINGRP -m 555 \
    $BSDSRCDIR/gnu/usr.bin/binutils/gas/obj.$MACHINE/as-new \
    $CROSSDIR/host-tools/bin/as

for binutil in ar as ld nm objcopy objdump ranlib size strip; do
	ln -f $CROSSDIR/host-tools/bin/$binutil $CROSSDIR/host-tools/bin/$TARGET-$binutil
done

rm -rf $CROSSDIR/usr/obj/gnu/usr.bin/binutils
( cd $BSDSRCDIR/gnu/usr.bin/binutils; \
    BSDSRCDIR=$BSDSRCDIR \
    BSDOBJDIR=$CROSSDIR/usr/obj \
    OStriplet=$HOST \
    MACHINE=$MACHINE \
    MACHINE_ARCH=$MARCH \
    MAKEOBJDIR=obj.$MACHINE \
    make obj )

set +x
print
print done.
