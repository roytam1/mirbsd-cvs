#!/bin/mksh
# $MirOS: src/scripts/xbuild-binutils.sh,v 1.13 2006/08/11 13:56:11 tg Exp $
#-
# Copyright (c) 2004, 2005, 2006, 2007
#	Thorsten Glaser <tg@mirbsd.de>
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
[[ -n $2 ]] && EMULATION=$2

[[ -z $CROSSDIR ]] && CROSSDIR=${DESTDIR}/usr/cross/${TARGET}

if [[ ! -s $CROSSDIR/T_BASEENV ]]; then
	print Run xbuild-env.sh first.
	exit 1
fi

. $CROSSDIR/T_BASEENV
export SHELL=$MKSH

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
	ln -f $CROSSDIR/usr/bin/cross-binutil.sh \
	    $CROSSDIR/host-tools/$TARGET/bin/$binutil
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

[[ -n $MKC_DEBG ]] || : ${INSTALL_STRIP=-s}

install -c $INSTALL_STRIP -o $BINOWN -g $BINGRP -m 555 \
    $BSDSRCDIR/gnu/usr.bin/binutils/gas/obj.$MACHINE/as-new \
    $CROSSDIR/host-tools/$TARGET/bin/as

for binutil in ar as ld nm objcopy objdump ranlib size strip; do
	ln -f $CROSSDIR/host-tools/$TARGET/bin/$binutil\
	    $CROSSDIR/host-tools/bin/$TARGET-$binutil
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
