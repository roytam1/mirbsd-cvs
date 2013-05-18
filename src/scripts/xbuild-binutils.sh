#!/bin/mksh
# $MirOS: src/scripts/xbuild-binutils.sh,v 1.2 2005/06/05 15:22:56 tg Exp $
#-
# Copyright (c) 2004, 2005
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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

TARGET=$1
EMULATION=$2

if [[ -z $TARGET ]]; then
	print No target given.
	exit 1
fi

CROSSDIR=${DESTDIR}/usr/cross/${TARGET}

if [[ ! -s $CROSSDIR/T_BASEENV ]]; then
	print Run xbuild-env.sh first.
	exit 1
fi

. $CROSSDIR/T_BASEENV

if [[ -z $EMULATION ]]; then
	EMULATION=$( \
	    targ=$TARGET; \
	    . $BSDSRCDIR/gnu/usr.bin/binutils/ld/configure.tgt; \
	    print $targ_emul)
fi

if ! ld -V 2>&1 | fgrep -w $EMULATION >/dev/null 2>&1; then
	print -- Target emulation \"$EMULATION\" not known.
	print -- Execute \"ld -V\" to list known targets.
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
	ln -f $CROSSDIR/usr/bin/cross-binutil.sh $CROSSDIR/usr/bin/$binutil
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
    make -f Makefile.bsd-wrapper )

install -c -s -o root -g bin -m 555 \
    $BSDSRCDIR/gnu/usr.bin/binutils/gas/obj.$MACHINE/as-new \
    $CROSSDIR/usr/bin/as

for binutil in ar as ld nm objcopy objdump ranlib size strip; do
	ln -f $CROSSDIR/usr/bin/$binutil $CROSSDIR/usr/$TARGET/bin/$binutil
	ln -f $CROSSDIR/usr/bin/$binutil $CROSSDIR/usr/bin/$TARGET-$binutil
done

set +x
print
print done.
