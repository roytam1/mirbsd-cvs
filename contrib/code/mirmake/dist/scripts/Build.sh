#!/bin/mksh
# $MirOS: contrib/code/mirmake/dist/scripts/Build.sh,v 1.90 2006/11/07 00:18:57 tg Exp $
#-
# Copyright (c) 2006
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


# Functions

# Call: testfunc 'proto' 'call' 'opt_include' 'opt_decl;'
# Return: 1 if found, 0 otherwise (inverse logic)
function testfunc {
	rv=0
	mkdir $d_build/testfunc
	cat >$d_build/testfunc/Makefile <<-'EOF'
		PROG=	testfunc
		.include <bsd.prog.mk>
	EOF
	cat >$d_build/testfunc/testfunc.c <<-EOF
		#include <sys/param.h>
		$3
		$1;
		int main() {
			$4
			$2;
			return 0;
		}
	EOF
	( cd $d_build/testfunc && ${d_build}/bmake -m ${d_build}/mk \
	    NOMAN=yes NOOBJ=yes ) 2>&1 | sed 's!^![ !'
	[[ -x $d_build/testfunc/testfunc ]] && rv=1
	rm -rf $d_build/testfunc
	return $rv
}

# Get parameters
new_ostype=$1
new_prefix=$2		# /usr/local
new_manpth=$3		# man/cat
new_exenam=$4		# bmake
new_machin=$5		# MACHINE
new_macarc=$6		# MACHINE_ARCH
new_machos=$7		# MACHINE_OS
new_mirksh=$8
new_binids=$9
[[ -z $OLDMAKE ]] && OLDMAKE=make

if [ -z "$new_mirksh" ]; then
	echo "Use ../../Build.sh instead!" >&2
	exit 255
fi

export SHELL=$new_mirksh

[[ -n $BASH_VERSION ]] && shopt -s extglob

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

case "$new_machos:$new_machin:$new_macarc" in
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
	[[ -z $new_binids ]] && new_binids=-
	CPPFLAGS="$CPPFLAGS -D_ALL_SOURCE"
	[[ $new_macarc = i[3456789x]86 ]] && new_macarc=i386
	/usr/bin/install -c -m 555 $d_script/../contrib/mktemp.sh \
	    /usr/bin/mktemp
	;;
*:*:i[3456789x]86)
	new_macarc=i386
	;;
esac

case $new_machos in
Darwin)
	_obfm=Mach-O
	_rtld=dyld
	CPPFLAGS="$CPPFLAGS -DHAVE_STRLCPY -DHAVE_STRLCAT"
	;;
*Interix)
	_obfm=PE
	_rtld=GNU
	;;
BSD)
	# MirOS BSD
	_obfm=ELF
	_rtld=BSD

	# OpenBSD
	if fgrep ELF_TOOLCHAIN /usr/share/mk/bsd.own.mk >/dev/null 2>&1; then
		if ! T=$(mktemp /tmp/mmake.XXXXXXXXXX); then
			print -u2 Error: cannot mktemp
			exit 1
		fi
		print '.include <bsd.own.mk>' >$T
		print 'all:' >>$T
		print '\t@echo ${ELF_TOOLCHAIN:L}' >>$T
		if X=$($OLDMAKE -f $T all); then
			[[ $X = no ]] && _obfm=a.out
		fi
		rm -f $T
	fi

	# XXX what about NetBSD? They have ELF a.out PE coff ...
	;;
Linux)
	_obfm=ELF
	_rtld=GNU
	# XXX noone sane uses Linux with a.out libc4 these days?
	;;
esac

export CC=${CC:-gcc}
export COPTS="${CFLAGS:--O2 -fno-strict-aliasing}"
export CPPFLAGS="$CPPFLAGS -D_MIRMAKE_DEFNS -isystem $d_build/F -include $d_build/F/mirmake.h"
export CFLAGS="$COPTS $CPPFLAGS"
export NROFF=${NROFF:-nroff}

echo | $NROFF -v 2>&1 | grep GNU >&- 2>&- && NROFF="$NROFF -c"

. $d_script/Version.sh

if [[ -z $new_binids ]]; then
	binown=root
	bingrp=bin
	confgrp=0
elif [[ $new_binids = *:* ]]; then
	binown=${new_binids%:*}
	bingrp=${new_binids#*:}
	confgrp=$bingrp
else
	binown=$new_binids
	bingrp=$new_binids
	confgrp=$bingrp
fi
if [[ $binown = - ]]; then
	ug=
else
	ug="\"-o $binown -g $bingrp\""
fi

if ! gnuos=$($SHELL $top/dist/contrib/gnu/config/config.guess); then
	print -u2 Please report also to the MirMake maintainers.
	exit 1
fi

mkdir -p $d_build/mk $d_build/F

sed_exp="-e 's#@@machine@@#${new_machin}#g' \
	 -e 's#@@march@@#${new_macarc}#g' \
	 -e 's#@@machos@@#${new_machos}#g' \
	 -e 's#@@mksh@@#${new_mirksh}#g' \
	 -e 's#@@ostype@@#${new_ostype}#g' \
	 -e 's#@@shmk@@#${dt_mk}#g' \
	 -e 's#@@binmk@@#${dt_bin}#g' \
	 -e 's#@@ccom@@#${CC}#g' \
	 -e 's#@@nroff@@#${NROFF}#g' \
	 -e 's#@@gnuos@@#${gnuos}#g' \
	 -e 's#@@vers@@#${version}#g' \
	 -e 's#@@obfm@@#${_obfm}#g' \
	 -e 's#@@rtld@@#${_rtld}#g' \
	 -e 's#@@bmake@@#${new_exenam}#g'"


# Copy sources
(cd $d_src/usr.bin/make; find . | cpio -pdlu $d_build)
(cd $d_src/lib/libc; find ohash | cpio -pdlu $d_build)
cp $d_src/lib/libc/stdlib/getopt_long.c $d_src/lib/libc/string/strlfun.c \
    $d_src/include/*.h $d_src/usr.bin/mkdep/mkdep.sh $d_build/
cp $d_src/share/mk/*.mk $d_build/mk/
cp $d_src/include/{getopt,md4,md5,rmd160,sha1,sha2,tiger}.h \
    $d_script/../contrib/mirmake.h $d_build/F/

# Patch sources
for ps in make.1 mk/{bsd.own.mk,bsd.prog.mk,bsd.sys.mk,sys.mk} mkdep.sh; do
	mv $d_build/$ps $d_build/$ps.tmp
	ed -s $d_build/$ps.tmp <$d_script/$(basename $ps).ed
	if eval sed $sed_exp <$d_build/$ps.tmp >$d_build/$ps; then
		rm $d_build/$ps.tmp
	else
		echo "Error in $d_build/$ps.tmp" >&2
		exit 1
	fi
done

if [[ $binown = - ]]; then
	binown=$(id -un)
	[[ $binown = *@( )* ]] && binown=$(id -u)
	bingrp=$(id -gn)
	[[ $bingrp = *@( )* ]] && bingrp=$(id -g)
	confgrp=$bingrp
fi
ed -s $d_build/mk/bsd.own.mk <<-EOF
	/^BINOWN/s/root/$binown/p
	/^BINGRP/s/bin/$bingrp/p
	/^CONFGRP/s/bin/$confgrp/p
	wq
EOF

# Build bmake
cd $d_build
if ! $OLDMAKE -f Makefile.boot bmake CC="$CC" MACHINE="${new_machin}" \
    MACHINE_ARCH="${new_macarc}" MACHINE_OS="${new_machos}" \
    MKSH="${new_mirksh}"; then
	echo "Error: build failure" >&2
	exit 1
fi

# Build the paper
cd $d_build
pic <PSD.doc/tutorial.ms >PSD12.make.ms.tbl 2>/dev/null \
    || cp PSD.doc/tutorial.ms PSD12.make.ms.tbl
tbl <PSD12.make.ms.tbl >PSD12.make.ms 2>/dev/null \
    || cp PSD12.make.ms.tbl PSD12.make.ms
$NROFF -ms PSD12.make.ms >PSD12.make.txt 2>/dev/null \
    || rm PSD12.make.txt

# Generate installer
cd $top
cat >Install.sh <<EOF
#!${new_mirksh}

i=\${1:-install}
ug=$ug
set -x
mkdir -p \$DESTDIR$dt_bin \$DESTDIR$dt_man \$DESTDIR$dt_mk
\$i -c -s \$ug -m 555 ${d_build}/make \$DESTDIR${dt_bin}/${new_exenam}
\$i -c \$ug -m 555 ${d_build}/mkdep.sh \$DESTDIR${dt_bin}/mkdep
\$i -c \$ug -m 555 $d_src/usr.bin/lorder/lorder.sh \$DESTDIR${dt_bin}/lorder
\$i -c \$ug -m 444 $d_build/F/*.h \$DESTDIR${dt_mk}/
\$i -c \$ug -m 444 $d_src/include/sysexits.h \$DESTDIR${dt_mk}/
EOF
for f in ${d_build}/mk/*.mk; do
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $f \$DESTDIR${dt_mk}/
EOF
done
# build make manpage
if [[ $is_catman = 1 ]]; then
	cd $d_build
	if ! $NROFF -mandoc make.1 >make.cat1; then
		echo "Warning: manpage build failure." >&2
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
# build mkdep manpage
if [[ $is_catman = 1 ]]; then
	cd $d_build
	if ! $NROFF -mandoc $d_src/usr.bin/mkdep/mkdep.1 >mkdep.cat1; then
		echo "Warning: manpage build failure." >&2
		is_catman=0
	fi
	cd $top
fi
if [[ $is_catman = 0 ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $d_src/usr.bin/mkdep/mkdep.1 \$DESTDIR${dt_man}/mkdep.1
EOF
else
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/mkdep.cat1 \$DESTDIR${dt_man}/mkdep.0
EOF
fi
# build lorder manpage
if [[ $is_catman = 1 ]]; then
	cd $d_build
	if ! $NROFF -mandoc $d_src/usr.bin/lorder/lorder.1 >lorder.cat1; then
		echo "Warning: manpage build failure." >&2
		is_catman=0
	fi
	cd $top
fi
if [[ $is_catman = 0 ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $d_src/usr.bin/lorder/lorder.1 \$DESTDIR${dt_man}/lorder.1
EOF
else
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/lorder.cat1 \$DESTDIR${dt_man}/lorder.0
EOF
fi
# build make documentation
if [[ -e $d_build/PSD12.make.txt ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $d_build/PSD12.make.txt \$DESTDIR${dt_mk}/
EOF
fi

# check for fgetln, strlcpy/strlcat, arc4random, arc4random_pushb
add_fgetln=
if testfunc 'char *fgetln(FILE *, size_t *)' 'fgetln(stdin, &x)' \
    '#include <stdio.h>' 'size_t x;'; then
	add_fgetln=$d_build/fgetln.o
fi
add_strlfun=
if testfunc 'size_t strlcpy(char *, const char *, size_t)' \
    'strlcpy(dst, src, 1)' '' 'char src[3] = "Hi", dst[3];'; then
	add_strlfun=$d_src/lib/libc/string/strlfun.c
fi
add_arcfour=
if testfunc 'uint32_t arc4random_pushb(const void *, size_t)' \
    'return arc4random_pushb(main, 1)'; then
	add_arcfour=$top/dist/contrib/arc4random.c
	if ! testfunc 'int arc4random(void)' \
	    'return arc4random()'; then
		CPPFLAGS="$CPPFLAGS -D_ARC4RANDOM_WRAP"
	fi
fi
add_libohash=
if testfunc 'u_int32_t ohash_interval(const char *, const char **)' \
    'return ohash_interval(NULL, NULL);'; then
	add_libohash=$d_build/ohash/libohash.a
fi

# build readlink
rm -rf $d_build/readlink
cd $d_src/usr.bin; find readlink | cpio -pdlu $d_build
cd $d_build/readlink
${d_build}/bmake -m ${d_build}/mk NOMAN=yes NOOBJ=yes
export PATH=${d_build}/readlink:$PATH
cd $top
cat >>Install.sh <<EOF
\$i -c -s \$ug -m 555 ${d_build}/readlink/readlink \$DESTDIR${dt_bin}/
EOF
if [[ $is_catman = 1 ]]; then
	cd $d_build/readlink
	if ! $NROFF -mandoc readlink.1 >readlink.cat1; then
		echo "Warning: manpage build failure." >&2
		is_catman=0
	fi
	cd $top
fi
if [[ $is_catman = 0 ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/readlink/readlink.1 \$DESTDIR${dt_man}/readlink.1
EOF
else
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/readlink/readlink.cat1 \$DESTDIR${dt_man}/readlink.0
EOF
fi

# build tsort
rm -rf $d_build/tsort
cd $d_src/usr.bin; find tsort | cpio -pdlu $d_build
cd $d_build/tsort
${d_build}/bmake -m ${d_build}/mk NOMAN=yes NOOBJ=yes \
    INCS="-I $d_build" LIBS="$d_build/ohash/libohash.a $add_fgetln"
export PATH=${d_build}/tsort:$PATH
cd $top
cat >>Install.sh <<EOF
\$i -c -s \$ug -m 555 ${d_build}/tsort/tsort \$DESTDIR${dt_bin}/
EOF
if [[ $is_catman = 1 ]]; then
	cd $d_build/tsort
	if ! $NROFF -mandoc tsort.1 >tsort.cat1; then
		echo "Warning: manpage build failure." >&2
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

if [[ $new_machos = Interix ]]; then
	# build xinstall
	rm -rf $d_build/xinstall
	cd $d_src/usr.bin; find xinstall | cpio -pdlu $d_build
	cd $d_build/xinstall
	CPPFLAGS="$CPPFLAGS -I$d_src/include" \
	    ${d_build}/bmake -m ${d_build}/mk NOMAN=yes NOOBJ=yes
	cd $top
	cat >>Install.sh <<EOF
\$i -c -s \$ug -m 555 ${d_build}/xinstall/xinstall \$DESTDIR${dt_bin}/
mv \$DESTDIR${dt_bin}/xinstall \$DESTDIR${dt_bin}/install
EOF
	if [[ $is_catman = 1 ]]; then
		cd $d_build/xinstall
		if ! $NROFF -mandoc install.1 >install.cat1; then
			echo "Warning: manpage build failure." >&2
			is_catman=0
		fi
		cd $top
	fi
	if [[ $is_catman = 0 ]]; then
		cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/xinstall/install.1 \$DESTDIR${dt_man}/install.1
EOF
	else
		cat >>Install.sh <<EOF
\$i -c \$ug -m 444 ${d_build}/xinstall/install.cat1 \$DESTDIR${dt_man}/install.0
EOF
	fi
fi

# build libmirmake (hash stuff and necessities)
rm -rf $d_build/libmirmake
mkdir $d_build/libmirmake
cd $d_build/libmirmake
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
sed -e 's/hashinc/tiger.h/g' -e 's/HASH/TIGER/g' \
    $d_src/lib/libc/hash/helper.c >tigerhl.c
cp  $d_src/lib/libc/hash/{md4,md5,rmd160,sha1,sha2,tiger}.c \
    $d_src/lib/libc/stdlib/{getopt_long,strtoll}.c \
    $d_src/lib/libc/stdio/{{,v}asprintf,mktemp}.c .
SRCS="${add_fgetln%.[co]}.c $add_strlfun $add_arcfour" \
    ${d_build}/bmake -m ${d_build}/mk -f $d_script/Makefile.lib NOOBJ=yes clean
SRCS="${add_fgetln%.[co]}.c $add_strlfun $add_arcfour" \
    ${d_build}/bmake -m ${d_build}/mk -f $d_script/Makefile.lib NOOBJ=yes
cd $top
if [[ -s $d_build/libmirmake/libmirmake.a ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 600 $d_build/libmirmake/libmirmake.a \$DESTDIR${dt_mk}/
ranlib \$DESTDIR${dt_mk}/libmirmake.a
chmod 444 \$DESTDIR${dt_mk}/libmirmake.a
EOF
fi

# re-build bmake
cd ${d_build}
${d_build}/bmake -m ${d_build}/mk NOMAN=yes NOOBJ=yes \
    MAKE_BOOTSTRAP=Yes MKFEATURES=-D_PATH_DEFSYSPATH=\\\"${dt_mk}\\\" \
    LDADD="$add_libohash $d_build/libmirmake/libmirmake.a" clean
${d_build}/bmake -m ${d_build}/mk NOMAN=yes NOOBJ=yes \
    MAKE_BOOTSTRAP=Yes MKFEATURES=-D_PATH_DEFSYSPATH=\\\"${dt_mk}\\\" \
    MKDEP_SH="${new_mirksh} ${d_build}/mkdep.sh" \
    LDADD="$add_libohash $d_build/libmirmake/libmirmake.a" depend
${d_build}/bmake -m ${d_build}/mk NOMAN=yes NOOBJ=yes \
    MAKE_BOOTSTRAP=Yes MKFEATURES=-D_PATH_DEFSYSPATH=\\\"${dt_mk}\\\" \
    LDADD="$add_libohash $d_build/libmirmake/libmirmake.a" make

[[ -e ${d_build}/make ]] || exit 1

chmod 555 $top/Install.sh

echo "Call $top/Install.sh to install ${new_exenam}!"
exit 0
