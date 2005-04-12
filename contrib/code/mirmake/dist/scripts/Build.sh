#!/bin/ksh
# $MirOS: contrib/code/mirmake/dist/scripts/Build.sh,v 1.18 2005/04/12 19:10:37 tg Exp $
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
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# _Really_ build MirMake. Called from mirbsdksh.


# Get parameters
new_ostype="$1"
new_prefix="$2"		# /usr/local
new_manpth="$3"		# man/cat
new_exenam="$4"		# bmake
new_machin="$5"		# MACHINE
new_macarc="$6"		# MACHINE_ARCH
new_machos="$7"		# MACHINE_OS
new_mirksh="$8"
new_binids="$9"

if [ -z "$new_mirksh" ]; then
	echo "Use ../../Build.sh instead!"
	exit 255
fi

export SHELL=$new_mirksh

# Directories
top=$(cd $(dirname $0)/../..; pwd)
d_script=$top/dist/scripts
d_src=$top/dist/src
d_build=$top/build
dt_bin=$new_prefix/bin
dt_man=$new_prefix/${new_manpth}1
dt_mk=$new_prefix/share/${new_exenam}

if [[ $new_manpth = *@(cat)* ]]; then
	is_catman=1
else
	is_catman=0
fi

case "$new_machos:$new_machin:$new_macarc" {
Darwin:*:powerpc)
	;;
Darwin:*:i686)
	new_machin=i686
	new_macarc=i386
	;;
Darwin:*:*)
	new_macarc=$(uname -p)
	[[ $new_macarc = *86 ]] && new_machin=i686
	[[ $new_macarc = *86 ]] && new_macarc=i386
	;;
Interix:*:*)
	CPPFLAGS="$CPPFLAGS -D_ALL_SOURCE"
	[[ $new_macarc = i[3456789x]86 ]] && new_macarc=i386
	;;
*:*:i[3456789x]86)
	new_macarc=i386
	;;
}

export CC="${CC:-gcc}"
export COPTS="${CFLAGS:--O2 -fno-strength-reduce -fno-strict-aliasing}"
export CPPFLAGS="$CPPFLAGS -include $d_script/../contrib/mirmake.h"
export CFLAGS="$COPTS $CPPFLAGS"

if [[ -z $new_binids ]]; then
	binown=root
	bingrp=bin
elif [[ $new_binids = *:* ]]; then
	binown=${new_binids%:*}
	bingrp=${new_binids#*:}
else
	binown=$new_binids
	bingrp=$new_binids
fi

mkdir -p $d_build/mk

sed_exp="-e 's#@@machine@@#${new_machin}#' \
	 -e 's#@@march@@#${new_macarc}#' \
	 -e 's#@@machos@@#${new_machos}#' \
	 -e 's#@@mksh@@#${new_mirksh}#' \
	 -e 's#@@ostype@@#${new_ostype}#' \
	 -e 's#@@shmk@@#${dt_mk}#' \
	 -e 's#@@ccom@@#${CC}#' \
	 -e 's#@@bmake@@#${new_exenam}#'"


# Copy sources
(cd $d_src/usr.bin/make; tar cf - * ) | (cd $d_build; tar xf - )
cp $d_src/share/mk/*.mk $d_build/mk/
cp $d_src/include/*.h $d_build/
(cd $d_src/lib/libc; tar cf - ohash ) | (cd $d_build; tar xf - )
cp $d_src/lib/libc/stdlib/getopt_long.c $d_build/
cp $d_src/lib/libc/string/strlfun.c $d_build/
cp $d_src/usr.bin/mkdep/mkdep.sh $d_build/

# Patch sources
for ps in Makefile.boot mk/bsd.man.mk mk/bsd.own.mk mk/bsd.prog.mk \
    mk/bsd.sys.mk make.1 mk/sys.mk mkdep.sh; do
	mv $d_build/$ps $d_build/$ps.tmp
	ed -s $d_build/$ps.tmp <$d_script/$(basename $ps).ed
	if eval sed $sed_exp <$d_build/$ps.tmp >$d_build/$ps; then
		rm $d_build/$ps.tmp
	else
		echo "Error in $d_build/$ps.tmp"
		exit 1
	fi
done

# Build bmake
cd $d_build
if ! make -f Makefile.boot bmake CC="$CC"; then
	echo "Error: build failure"
	exit 1
fi

# Build the paper
cd $d_build
pic <PSD.doc/tutorial.ms >PSD12.make.ms.tbl 2>/dev/null \
    || cp PSD.doc/tutorial.ms PSD12.make.ms.tbl
tbl <PSD12.make.ms.tbl >PSD12.make.ms 2>/dev/null \
    || cp PSD12.make.ms.tbl PSD12.make.ms
nroff -ms PSD12.make.ms >PSD12.make.txt 2>/dev/null \
    || rm PSD12.make.txt

# Generate installer
cd $top
cat >Install.sh <<EOF
#!${new_mirksh}

i=\${1:-install}
if [[ $binown = - ]]; then
	ug=
else
	ug="-o $binown -g $bingrp"
fi
set -x
mkdir -p \$DESTDIR$dt_bin \$DESTDIR$dt_man \$DESTDIR$dt_mk
\$i -c -s \$ug -m 555 ${d_build}/bmake \$DESTDIR${dt_bin}/${new_exenam}
\$i -c \$ug -m 555 ${d_build}/mkdep.sh \$DESTDIR${dt_bin}/mkdep
EOF
for f in ${d_build}/mk/*.mk; do
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $f \$DESTDIR${dt_mk}/
EOF
done
if [[ $is_catman = 1 ]]; then
	cd $d_build
	if ! nroff -mandoc make.1 >make.cat1; then
		echo "Warning: manpage build failure."
		is_catman=0
	fi
	cd $top
fi
if [[ $is_catman = 0 ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/make.1 \$DESTDIR${dt_man}/${new_exenam}.1
EOF
else
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/make.cat1 \$DESTDIR${dt_man}/${new_exenam}.0
EOF
fi
if [[ -e $d_build/PSD12.make.txt ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $d_build/PSD12.make.txt \$DESTDIR${dt_mk}/
EOF
fi

cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $d_src/lib/libc/string/strlfun.c \$DESTDIR${dt_mk}/
\$i -c \$ug -m 444 $d_script/../contrib/mirmake.h \$DESTDIR${dt_mk}/
EOF

# build tsort
rm -rf $d_build/tsort
mkdir $d_build/tsort
cd $d_build/tsort
(cd $d_src/usr.bin/tsort; tar cf - * ) | tar xf -
${d_build}/bmake -m ${d_build}/mk NOMAN=yes \
    INCS="-I $d_build" LIBS="$d_build/ohash/libohash.a"
cd $top
cat >>Install.sh <<EOF
\$i -c -s \$ug -m 555 ${d_build}/tsort/tsort \$DESTDIR${dt_bin}/
EOF
if [[ $is_catman = 1 ]]; then
	cd $d_build/tsort
	if ! nroff -mandoc tsort.1 >tsort.cat1; then
		echo "Warning: manpage build failure."
		is_catman=0
	fi
	cd $top
fi
if [[ $is_catman = 0 ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/tsort/tsort.1 \$DESTDIR${dt_man}/tsort.1
EOF
else
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/tsort/tsort.cat1 \$DESTDIR${dt_man}/tsort.0
EOF
fi

# build the hash stuff
rm -rf $d_build/hash
mkdir $d_build/hash
cd $d_build/hash
sed -e 's/hashinc/md4.h/g' -e 's/HASH/MD4/g' \
    $d_src/lib/libc/hash/helper.c >md4hl.c
sed -e 's/hashinc/md5.h/g' -e 's/HASH/MD5/g' \
    $d_src/lib/libc/hash/helper.c >md5hl.c
sed -e 's/hashinc/rmd160.h/g' -e 's/HASH/RMD160/g' \
    $d_src/lib/libc/hash/helper.c >rmd160hl.c
sed -e 's/hashinc/sha1.h/g' -e 's/HASH/SHA1/g' \
    $d_src/lib/libc/hash/helper.c >sha1hl.c
sed -e 's/hashinc/sha2.h/g' -e 's/HASH_\{0,1\}/SHA256_/g' \
    $d_src/lib/libc/hash/helper.c >sha256hl.c
sed -e 's/hashinc/sha2.h/g' -e 's/HASH_\{0,1\}/SHA384_/g' \
    $d_src/lib/libc/hash/helper.c >sha384hl.c
sed -e 's/hashinc/sha2.h/g' -e 's/HASH_\{0,1\}/SHA512_/g' \
    $d_src/lib/libc/hash/helper.c >sha512hl.c
( cd $d_src/lib/libc/hash; \
  cp md4.c md5.c rmd160.c sha1.c sha2.c $d_build/hash/ )
${d_build}/bmake -m ${d_build}/mk -f $d_script/Makefile.hash \
    INCS="-I$d_src/include" libhash.a
cd $top
if [[ -s $d_build/hash/libhash.a ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 600 $d_build/hash/libhash.a \$DESTDIR${dt_mk}/
ranlib \$DESTDIR${dt_mk}/libhash.a
chmod 444 \$DESTDIR${dt_mk}/libhash.a
\$i -c \$ug -m 444 $d_src/include/md4.h \$DESTDIR${dt_mk}/
\$i -c \$ug -m 444 $d_src/include/md5.h \$DESTDIR${dt_mk}/
\$i -c \$ug -m 444 $d_src/include/rmd160.h \$DESTDIR${dt_mk}/
\$i -c \$ug -m 444 $d_src/include/sha1.h \$DESTDIR${dt_mk}/
\$i -c \$ug -m 444 $d_src/include/sha2.h \$DESTDIR${dt_mk}/
EOF
fi

chmod 555 $top/Install.sh

echo "Call $top/Install.sh to install ${new_exenam}!"
exit 0
