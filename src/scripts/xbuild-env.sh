#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.6 2006/01/24 22:24:02 tg Rel $
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
# call this with the machine as first parameter and canonical target
# name as second parameter; optionally the machine arch as third.

MACHINE=$1
TARGET=$2

[[ -z $MACHINE && -n $TARGET ]] && MACHINE=${TARGET%%-*}

if [[ -z $MACHINE ]]; then
	print -u2 No target or machine given.
	exit 1
fi

case $MACHINE {
(alpha|amd64|hppa|i386|m68k|m88k|powerpc|sparc|sparc64|vax)
	MARCH=$MACHINE ;;
(amiga|hp300|mac68k|mvme68k)
	MARCH=m68k ;;
(luna88k|mvme88k)
	MARCH=m88k ;;
(macppc|mvmeppc)
	MARCH=powerpc ;;
(sgi)
	MARCH=mips ;;
(*)
	[[ -n $3 ]] && MARCH=$3
	if [[ -z $MARCH ]]; then
		print -u2 "Cannot guess machine arch for $MACHINE,"
		print -u2 "target $TARGET - please supply."
		exit 1
	fi
	;;
esac

[[ -z $TARGET ]] && TARGET=${MARCH}-unknown-mirbsd$(uname -r)
[[ -z $BSDSRCDIR ]] && BSDSRCDIR=/usr/src
if [[ -z $MKSH ]]; then
	if [[ -x /bin/mksh ]]; then
		MKSH=/bin/mksh
	else
		MKSH="/usr/bin/env mksh"
	fi
fi
SHELL=$MKSH
if ! FOO=$($SHELL $BSDSRCDIR/gnu/share/config.sub "$TARGET" 2>/dev/null); then
	print -u2 "Invalid target $TARGET chosen, exiting."
	exit 1
else
	TARGET=$FOO
fi
[[ -z $CROSSDIR ]] && CROSSDIR=${DESTDIR}/usr/cross/${TARGET}
HOST=$(make -f /dev/null ___DISPLAY_MAKEVARS=OStriplet)
[[ -n $CFLAGS ]] || CFLAGS="$(cd $BSDSRCDIR/etc; make ___DISPLAY_MAKEVARS=CFLAGS)"

set -e
set -x

mkdir -p $CROSSDIR/usr/$TARGET/bin
( cd $CROSSDIR/usr/$TARGET; ln -sf ../include .; ln -sf ../lib . )
( cd $BSDSRCDIR; DESTDIR=$CROSSDIR make distrib-dirs )

print -r -- "$MACHINE" >$CROSSDIR/T_MACHINE
print -r -- "$MARCH" >$CROSSDIR/T_MACHINE_ARCH
print -r -- "$TARGET" >$CROSSDIR/T_CANON
print -r -- "$HOST" >$CROSSDIR/H_CANON

( cd $BSDSRCDIR; \
    BSDSRCDIR=$BSDSRCDIR \
    BSDOBJDIR=$CROSSDIR/usr/obj \
    OStriplet=$HOST \
    MACHINE=$MACHINE \
    MACHINE_ARCH=$MARCH \
    MAKEOBJDIR=obj.$MACHINE \
    make obj )

CROSSCPPFLAGS="$CROSSCPPFLAGS -nostdinc -I${CROSSDIR}/usr/include"
BUILDLDFLAGS="$CROSSLDFLAGS -L${CROSSDIR}/usr/lib -static"
CROSSLDFLAGS="$CROSSLDFLAGS -nostdlib -L${CROSSDIR}/usr/lib -static"
CROSSCFLAGS="-O2 $CROSSCFLAGS $CROSSCPPFLAGS"

cat >$CROSSDIR/T_BASEENV <<-EOF
	BSDSRCDIR='$BSDSRCDIR'
	BSDOBJDIR='$CROSSDIR/usr/obj'
	CROSSDIR='$CROSSDIR'
	HOST='$HOST'
	MACHINE='$MACHINE'
	MACHINE_ARCH='$MARCH'
	MKSH='$MKSH'
EOF

cat >$CROSSDIR/T_ENV <<-EOF
	AR='$CROSSDIR/usr/bin/ar'
	AS='$CROSSDIR/usr/bin/as'
	CC='$CROSSDIR/usr/bin/cc'
	CFLAGS=''$CROSSCFLAGS''
	CPP='$CROSSDIR/usr/bin/cpp'
	CPPFLAGS='$CROSSCPPFLAGS'
	CROSS_MODE=yes
	DESTDIR='$CROSSDIR'
	HOSTCC=/usr/bin/mgcc
	HOSTCFLAGS='$CFLAGS -Wno-error'
	HOSTLDFLAGS='$LDFLAGS'
	LD='$CROSSDIR/usr/bin/ld'
	LDFLAGS='$CROSSLDFLAGS'
	LDSTATIC='-static'
	LORDER='/usr/bin/lorder'
	NM='$CROSSDIR/usr/bin/nm'
	NOMAN=yes
	NOPIC=yes
	OBJCOPY='$CROSSDIR/usr/bin/objcopy'
	OBJDUMP='$CROSSDIR/usr/bin/objdump'
	RANLIB='$CROSSDIR/usr/bin/ranlib'
	SIZE='$CROSSDIR/usr/bin/size'
	STRIP='$CROSSDIR/usr/bin/strip'
EOF

cat >$CROSSDIR/T_MAKE <<-EOF
#!/bin/mksh
exec env \
	CFLAGS='$CROSSCFLAGS' \
	CPPFLAGS='$CROSSCPPFLAGS' \
	HOSTCFLAGS='$CFLAGS -Wno-error' \
	MACHINE='$MACHINE \'
	MACHINE_ARCH='$MARCH \'
	OStriplet='$HOST \'
	GCCHOST='$TARGET \'
	GCCTARGET='$TARGET \'
    make MAKE=\$0 \
	__objdir='obj.$MACHINE \'
	BSDSRCDIR='$BSDSRCDIR \'
	BSDOBJDIR='$CROSSDIR/usr/obj \'
	HOST='$HOST \'
	AR='$CROSSDIR/usr/bin/ar \'
	AS='$CROSSDIR/usr/bin/as \'
	CC='$CROSSDIR/usr/bin/cc \'
	CPP='$CROSSDIR/usr/bin/cpp \'
	CROSS_MODE=yes \
	DESTDIR='$CROSSDIR \'
	HOSTCC=/usr/bin/mgcc \
	HOSTLDFLAGS='$LDFLAGS' \
	LD='$CROSSDIR/usr/bin/ld \'
	LDFLAGS='$BUILDLDFLAGS' \
	LDSTATIC='-static \'
	LORDER='/usr/bin/lorder \'
	NM='$CROSSDIR/usr/bin/nm \'
	NOMAN=yes \
	NOPIC=yes \
	OBJCOPY='$CROSSDIR/usr/bin/objcopy \'
	OBJDUMP='$CROSSDIR/usr/bin/objdump \'
	RANLIB='$CROSSDIR/usr/bin/ranlib \'
	SIZE='$CROSSDIR/usr/bin/size \'
	STRIP='$CROSSDIR/usr/bin/strip \'
    "\$@"
EOF
chmod 755 $CROSSDIR/T_MAKE

set +x
print
print Building on $HOST for $TARGET
exit 0
