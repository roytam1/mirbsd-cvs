#!/bin/mksh
# $MirOS: contrib/code/mirmake/dist/scripts/Build.sh,v 1.76 2006/08/26 22:46:43 tg Exp $
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

function scnfunc
{
	name=$1
	args=$2
	extra_hdrs=$3
	extra_defs=$4

	print ... $name
	typeset -u nameu=$name
	rm -f scn.c
	for header in $extra_hdrs; do
		print "#include <$header>" >>scn.c
	done
	print "int main(int argc, char *argv[]) {" >>scn.c
	print "$extra_defs" >>scn.c
	print "(void)$name($args);" >>scn.c
	print "return (0); }" >>scn.c
	$d_build/bmake -m $d_build/mk PROG=scn -f $d_build/mk/bsd.prog.mk
	if [[ -x scn ]]; then
		local res=yes
		eval HAVE_$nameu=1
	else
		local res=no
		eval HAVE_$nameu=0
	fi
	rm -f scn.c scn.o scn
	print "==> $name... $res"
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

if [ -z "$new_mirksh" ]; then
	echo "Use ../../Build.sh instead!" >&2
	exit 255
fi

export SHELL=$new_mirksh MKSH=$new_mirksh

[[ -n $BASH_VERSION ]] && shopt -s extglob
[[ -z $OLDMAKE ]] && OLDMAKE=make

# Directories
top=$(cd $(dirname $0)/../..; pwd)
mkdir $top/tmpx
export PATH=$top/tmpx:$PATH
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

case $new_machos:$new_machin:$new_macarc in
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
	[[ $new_macarc = i[3456789x]86 ]] && new_macarc=i386
	cp $top/dist/contrib/mktemp.sh $top/tmpx/mktemp
	chmod 755 $top/tmpx/mktemp
	;;
*:*:i[3456789x]86)
	new_macarc=i386
	;;
esac

case $new_machos in
Darwin)
	_obfm=Mach-O
	_rtld=dyld
	;;
*Interix)
	_obfm=PE
	_rtld=GNU
	CPPFLAGS="$CPPFLAGS -D_ALL_SOURCE"
	;;
BSD)
	# MirOS BSD
	_obfm=ELF
	_rtld=BSD

	# OpenBSD
	if fgrep ELF_TOOLCHAIN /usr/share/mk/bsd.own.mk >&- 2>&-; then
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

: ${CC:=gcc} ${NROFF:=nroff}
COPTS=${CFLAGS:--O2 -fno-strength-reduce -fno-strict-aliasing}
CPPFLAGS="$CPPFLAGS -D_MIRMAKE_DEFNS -isystem $d_build/F\
 -include $d_build/F/mirmake.h"
CFLAGS="$COPTS $CPPFLAGS"
echo | $NROFF -v 2>&1 | grep GNU >&- 2>&- && NROFF="$NROFF -c"
LDFLAGS=$(echo " $LDFLAGS "|sed -e 's/ -lmirmake //' -e 's/^ *//' -e 's/ *$//')
export CC COPTS CPPFLAGS CFLAGS LDFLAGS NROFF
unset LDADD DPADD LIBS

. $d_script/Version.sh

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
if [[ $binown = - ]]; then
	ug=
	binown=$(id -un)
	[[ $binown = *@( )* ]] && binown=$(id -u)
	bingrp=$(id -gn)
	[[ $bingrp = *@( )* ]] && bingrp=$(id -g)
else
	ug="\"-o $binown -g $bingrp\""
fi

if ! gnuos=$($MKSH $top/dist/contrib/gnu/config/config.guess); then
	print -u2 Please report also to the MirMake maintainers.
	exit 1
fi

sed_exp="-e 's#@@machine@@#${new_machin}#g' \
	 -e 's#@@march@@#${new_macarc}#g' \
	 -e 's#@@machos@@#${new_machos}#g' \
	 -e 's#@@mksh@@#${MKSH}#g' \
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
rm -rf $d_build
mkdir -p $d_build/{F,mk,libmirmake}
(cd $d_src/usr.bin/make; find . | cpio -pdlu $d_build)
(cd $d_src/lib/libc; find ohash | cpio -pdlu $d_build)
(cd $d_src/usr.bin; find readlink tsort xinstall | cpio -pdlu $d_build)
cp  $d_src/lib/libc/stdlib/getopt_long.c $d_src/lib/libc/string/strlfun.c \
    $d_src/include/*.h $d_src/usr.bin/mkdep/mkdep.sh $d_build/
cp  $d_src/share/mk/*.mk $d_build/mk/
cp  $d_src/include/{getopt,md4,md5,rmd160,sha1,sha2,stdbool,sysexits}.h \
    $top/dist/contrib/mirmake.h $d_build/F/
cp  $d_src/lib/libc/hash/{md4,md5,rmd160,sha1,sha2}.c \
    $d_src/lib/libc/string/strlfun.c \
    $d_src/lib/libc/stdlib/{getopt_long,strtoll}.c \
    $d_src/lib/libc/stdio/{{,v}asprintf,mktemp}.c \
    $top/dist/contrib/*.c $d_build/libmirmake/
for lc in md4 md5 rmd160 sha1; do
	typeset -u uc=$lc
	sed -e "s/hashinc/$lc.h/g" -e "s/HASH/$uc/g" \
	    <$d_src/lib/libc/hash/helper.c >$d_build/libmirmake/${lc}hl.c
done
for lc in sha256 sha384 sha512; do
	typeset -u uc=$lc
	sed -e "s/hashinc/sha2.h/g" -e "s/HASH_\{0,1\}/$uc_/g" \
	    <$d_src/lib/libc/hash/helper.c >$d_build/libmirmake/${lc}hl.c
done
cp $d_script/Makefile.lib $d_build/libmirmake/Makefile
chmod -R u+w $d_build

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
ed -s $d_build/mk/bsd.own.mk <<-EOF
	/^BINOWN/s/root/$binown/p
	/^BINGRP/s/bin/$bingrp/p
	wq
EOF

# Install shell-based helpers in temporary location (in our PATH)
cd $top/tmpx
cp $d_build/mkdep.sh mkdep
cp $d_src/usr.bin/lorder/lorder.sh lorder
chmod 755 mkdep lorder

# Build bmake
cd $d_build
$OLDMAKE -f Makefile.boot bmake CC="$CC" MACHINE="${new_machin}" \
    MACHINE_ARCH="${new_macarc}" MACHINE_OS="${new_machos}" \
    MKSH="$MKSH" && test -x bmake || {
	print -u2 "Error: build failure"
	exit 1
}
rm $d_build/F/stdbool.h

# Build libmirmake
cd $d_build/libmirmake
print Scanning for functions...
scnfunc strlcpy 'dst,src,1' 'stdlib.h' 'char src[] = "test", dst[4];'
scnfunc strlcat 'dst,src,1' 'stdlib.h' 'char src[] = "test", dst[4] = "";'
scnfunc fgetln 'stdin,&x' 'stdio.h' 'size_t x;'
scnfunc arc4random '' 'stdlib.h'
scnfunc arc4random_pushb 'buf,arc4random()' 'stdlib.h' 'char buf[] = "test";'
unset HAVE_EXIT
scnfunc exit 't==false' 'stdbool.h' 'bool t = true;'
if 1 = $HAVE_EXIT; then
	HAS_STDBOOL_H=1
else
	HAS_STDBOOL_H=0
	cp $d_src/include/stdbool.h $d_build/F/
fi
unset HAVE_EXIT
SRCS="md4hl.c md5hl.c rmd160hl.c sha1hl.c sha256hl.c sha384hl.c sha512hl.c"
SRCS="getopt_long.c md4.c md5.c rmd160.c sha1.c sha2.c $SRCS"
[[ $new_machos = Interix ]] && \
    SRCS="$SRCS asprintf.c mktemp.c strtoll.c vasprintf.c"
[[ $HAVE_STRLCPY$HAVE_STRLCAT = 11 ]] || SRCS="$SRCS strlfun.c"
[[ $HAVE_FGETLN = 1 ]] || SRCS="$SRCS fgetln.c"
[[ $HAVE_ARC4RANDOM = 1 ]] || CPPFLAGS="$CPPFLAGS -D_ARC4RANDOM_WRAP"
[[ $HAVE_ARC4RANDOM_PUSHB = 1 ]] || SRCS="$SRCS arc4random.c"
export SRCS NOMAN=yes NOOBJ=yes
print ... done
$d_build/bmake -m $d_build/mk libmirmake.a
rm -f $top/tmpx/libmirmake.a
cp libmirmake.a $top/tmpx/
export LDADD="-L$top/tmpx -lmirmake"
cd $top

# Build helper programmes
for prog in readlink tsort xinstall; do
	cd $d_build/$prog
	CPPFLAGS="$CPPFLAGS -I$d_src/include" $d_build/bmake -m $d_build/mk
	export PATH=$d_build/$prog:$PATH
done

# Rebuild bmake
cd $d_build
$d_build/bmake -m $d_build/mk MAKE_BOOTSTRAP=Yes \
    MKFEATURES=-D_PATH_DEFSYSPATH=\\\"${dt_mk}\\\" clean
$d_build/bmake -m $d_build/mk MAKE_BOOTSTRAP=Yes \
    MKFEATURES=-D_PATH_DEFSYSPATH=\\\"${dt_mk}\\\" depend
$d_build/bmake -m $d_build/mk MAKE_BOOTSTRAP=Yes \
    MKFEATURES=-D_PATH_DEFSYSPATH=\\\"${dt_mk}\\\"

# Rebuild libmirmake (this time shared)
unset LDADD
cd $d_build/libmirmake
$d_build/make -m $d_build/mk clean
$d_build/make -m $d_build/mk depend
$d_build/make -m $d_build/mk

# Build the make(1) paper and a variety of manual pages
cd $d_build
pic <PSD.doc/tutorial.ms >PSD12.make.ms.tbl 2>&- \
    || cp PSD.doc/tutorial.ms PSD12.make.ms.tbl
tbl <PSD12.make.ms.tbl >PSD12.make.ms 2>&- \
    || cp PSD12.make.ms.tbl PSD12.make.ms
$NROFF -ms PSD12.make.ms >PSD12.make.txt 2>&- \
    || rm PSD12.make.txt
for mansrc in make.1 $d_src/usr.bin/mkdep/mkdep.1 \
    $d_src/usr.bin/lorder/lorder.1 $d_src/usr.bin/readlink/readlink.1 \
    $d_src/usr.bin/tsort/tsort.1 $d_src/usr.bin/xinstall/install.1; do
	mandst=$(basename $mansrc | sed 's/\./.cat/')
	[[ $is_catman = 1 ]] && if ! $NROFF -mandoc $mansrc >$mandst; then
		print -u2 Warning: manpage build failure.
		is_catman=0
	fi
done

# Finally, generate the installer
cd $top
cat >Install.sh <<EOF
#!$MKSH

i=\${1:-install}
s=\${INSTALL_STRIP:--s}
ug=$ug
set -x
mkdir -p \$DESTDIR$dt_bin \$DESTDIR$dt_man \$DESTDIR$dt_mk
\$i -c \$s \$ug -m 555 $d_build/make \$DESTDIR$dt_bin/$new_exenam
\$i -c \$ug -m 555 $top/tmpx/mkdep $top/tmpx/lorder \$DESTDIR$dt_bin/
\$i -c \$ug -m 444 $d_build/F/*.h $d_build/mk/*.mk \$DESTDIR$dt_mk/
progs="libmirmake readlink tsort"
sfu=:
EOF
[[ $new_machos = Interix ]] && cat >>Install.sh <<EOF
\$i -c \$ug -m 555 $top/tmpx/mktemp \$DESTDIR$dt_bin/
progs="\$progs xinstall"
sfu=
EOF
[[ -s $d_build/PSD12.make.txt ]] && cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $d_build/PSD12.make.txt \$DESTDIR$dt_mk/
EOF
if [[ $is_catman = 0 ]]; then
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $d_build/make.1 \$DESTDIR$dt_man/$new_exenam.1
\$i -c \$ug -m 444 $d_src/usr.bin/mkdep/mkdep.1 \$DESTDIR$dt_man/mkdep.1
\$i -c \$ug -m 444 $d_src/usr.bin/lorder/lorder.1 \$DESTDIR$dt_man/lorder.1
\$i -c \$ug -m 444 $d_build/readlink/readlink.1 \$DESTDIR$dt_man/readlink.1
\$i -c \$ug -m 444 $d_build/tsort/tsort.1 \$DESTDIR$dt_man/tsort.1
\$sfu \$i -c \$ug -m 444 $d_build/xinstall/install.1 \$DESTDIR$dt_man/install.1
EOF
else
	cat >>Install.sh <<EOF
\$i -c \$ug -m 444 $d_build/make.cat1 \$DESTDIR$dt_man/$new_exenam.0
\$i -c \$ug -m 444 $d_build/mkdep.cat1 \$DESTDIR$dt_man/mkdep.0
\$i -c \$ug -m 444 $d_build/lorder.cat1 \$DESTDIR$dt_man/lorder.0
\$i -c \$ug -m 444 $d_build/readlink.cat1 \$DESTDIR$dt_man/readlink.0
\$i -c \$ug -m 444 $d_build/tsort.cat1 \$DESTDIR$dt_man/tsort.0
\$sfu \$i -c \$ug -m 444 $d_build/install.cat1 \$DESTDIR$dt_man/install.0
EOF
fi
cat >>Install.sh <<EOF
for prog in \$progs; do
	(cd $d_build/\$prog; $d_build/make -m $d_build/mk \\
	    NOOBJ=yes NOMAN=yes INSTALL_STRIP=\$s \\
	    DESTDIR="\$DESTDIR" BINDIR=$dt_bin LIBDIR=$dt_mk install)
done
EOF

chmod 755 Install.sh
echo "Call $top/Install.sh to install ${new_exenam}!"
exit 0
