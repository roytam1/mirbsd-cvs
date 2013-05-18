#!/bin/mksh
# $MirOS: src/scripts/xbuild-gcc.sh,v 1.2 2005/06/05 15:22:56 tg Exp $
#-
# Copyright (c) 2004
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
# install stuff into $CROSSDIR/usr/include first, eg a crosscompiler
# to i386-pc-linux-gnu needs pthread.h and the likes during build...

if [[ $1 = -a ]]; then
	Ada=1
	langs=c,ada
	shift
else
	Ada=0
	langs=c
fi

TARGET=$1
if [[ -z $TARGET ]]; then
	print No target given.
	exit 1
fi

CROSSDIR=${DESTDIR}/usr/cross/${TARGET}

if [[ ! -s $CROSSDIR/T_BASEENV ]]; then
	print Run build-cross-env first.
	exit 1
fi

. $CROSSDIR/T_BASEENV

set -e
set -x

cd $BSDSRCDIR/scripts
CFLAGS="$(make ___DISPLAY_MAKEVARS=CFLAGS)"
cd $BSDSRCDIR/gnu/share
GNU_LIBIBERTY_INC="$(make ___DISPLAY_MAKEVARS=GNU_LIBIBERTY_INC)"

cd $CROSSDIR/usr/obj/gnu/gcc/gcc
ln -sf ${CROSSDIR}/usr/bin/as .
PATH=$PATH:${CROSSDIR}/usr/bin BISON=yacc \
    GNUSYSTEM_AUX_DIR=${BSDSRCDIR}/gnu/share \
    CFLAGS="${CFLAGS} -I${GNU_LIBIBERTY_INC}" \
    $SHELL $BSDSRCDIR/gnu/gcc/gcc/configure \
    --prefix ${CROSSDIR}/usr --build $HOST --host $HOST \
    --target $TARGET --with-gnu-as=${CROSSDIR}/usr/bin/as \
    --with-gnu-ld=${CROSSDIR}/usr/bin/ld \
    --enable-languages=$langs --disable-cpp --disable-nls \
    --with-local-prefix=${CROSSDIR}/usr --disable-libtool-lock \
    --enable-sjlj-exceptions --with-system-zlib --disable-shared \
    --with-gxx-include-dir=${CROSSDIR}/usr/include/gxx
PATH=$PATH:${CROSSDIR}/usr/bin make \
    BISON=yacc LANGUAGES=c LDFLAGS="-static" build_infodir=. \
    CFLAGS="${CFLAGS} -I${GNU_LIBIBERTY_INC}" \
    GNUSYSTEM_AUX_DIR="${BSDSRCDIR}/gnu/share" INSTALL_MAN= \
    GCC_FOR_TARGET="./xgcc -B./ -I${CROSSDIR}/usr/include" \
    LIBIBERTY_HDRS="${GNU_LIBIBERTY_INC}"
[[ $ada = 0 ]] || \
PATH=$PATH:${CROSSDIR}/usr/bin make \
    BISON=yacc LANGUAGES=c LDFLAGS="-static" build_infodir=. \
    CFLAGS="${CFLAGS} -I${GNU_LIBIBERTY_INC}" \
    GNUSYSTEM_AUX_DIR="${BSDSRCDIR}/gnu/share" INSTALL_MAN= \
    GCC_FOR_TARGET="./xgcc -B./ -I${CROSSDIR}/usr/include" \
    LIBIBERTY_HDRS="${GNU_LIBIBERTY_INC}" gnat1
[[ $ada = 0 ]] || \
PATH=$PATH:${CROSSDIR}/usr/bin make \
    BISON=yacc LANGUAGES=c LDFLAGS="-static" build_infodir=. \
    CFLAGS="${CFLAGS} -I${GNU_LIBIBERTY_INC}" \
    GNUSYSTEM_AUX_DIR="${BSDSRCDIR}/gnu/share" INSTALL_MAN= \
    GCC_FOR_TARGET="./xgcc -B./ -I${CROSSDIR}/usr/include" \
    LIBIBERTY_HDRS="${GNU_LIBIBERTY_INC}" gnatlib_and_tools
( cd $BSDSRCDIR/gnu/gcc/gcc; make -f Makefile.bsd-wrapper \
    DESTDIR=$CROSSDIR GCCTARGET=$TARGET pre-install )
INST444='install -c -o root -g bin -m 444'
[[ ! -e crtbegin.o ]] || $INST444 crtbegin.o ${CROSSDIR}/usr/lib/crtbegin.o
[[ ! -e crtbeginS.o ]] || $INST444 crtbeginS.o ${CROSSDIR}/usr/lib/crtbeginS.o
[[ ! -e crtend.o ]] || $INST444 crtend.o ${CROSSDIR}/usr/lib/crtend.o
[[ ! -e crtendS.o ]] || $INST444 crtendS.o ${CROSSDIR}/usr/lib/crtendS.o
[[ ! -e fpic/crtbeginS.o ]] || $INST444 fpic/crtbeginS.o ${CROSSDIR}/usr/lib/crtbeginS.o
[[ ! -e fpic/crtendS.o ]] || $INST444 fpic/crtendS.o ${CROSSDIR}/usr/lib/crtendS.o
[[ ! -e crtsavres.o ]] || $INST444 crtsavres.o ${CROSSDIR}/usr/lib/crtsavres.o
[[ ! -e ncrti.o ]] || $INST444 ncrti.o ${CROSSDIR}/usr/lib/ncrti.o
[[ ! -e ncrtn.o ]] || $INST444 ncrtn.o ${CROSSDIR}/usr/lib/ncrtn.o
PATH=$PATH:${CROSSDIR}/usr/bin make \
    BISON=yacc LANGUAGES=c LDFLAGS="-static" build_infodir=. \
    CFLAGS="${CFLAGS} -I${GNU_LIBIBERTY_INC}" \
    GNUSYSTEM_AUX_DIR="${BSDSRCDIR}/gnu/share" INSTALL_MAN= \
    GCC_FOR_TARGET="./xgcc -B./ -I${CROSSDIR}/usr/include" \
    LIBIBERTY_HDRS="${GNU_LIBIBERTY_INC}" \
    INSTALL_TARGET='install-common $$(INSTALL_HEADERS)
    $$(INSTALL_LIBGCC) lang.install-normal install-driver' \
    install

ln -f ${CROSSDIR}/usr/bin/$TARGET-gcc ${CROSSDIR}/usr/bin/cc

install -c -s -o root -g bin -m 555 \
    ${CROSSDIR}/usr/obj/gnu/gcc/gcc/cpp ${CROSSDIR}/usr/libexec/cpp
sed -e 's/@dollaropt@//' -e 's#/usr/include#${CROSSDIR}/usr/include#' \
    -e 's#/usr/libexec/cpp#${CROSSDIR}/usr/libexec/cpp#' \
    $BSDSRCDIR/usr.bin/cpp/cpp.sh >${CROSSDIR}/usr/bin/cpp
chown root:bin ${CROSSDIR}/usr/bin/cpp
chmod 555 ${CROSSDIR}/usr/bin/cpp

set +x
print
print done.
