#!/bin/sh
# $MirOS: contrib/code/mirmake/dist/scripts/Copy.sh,v 1.35 2014/11/16 12:16:25 tg Exp $

wd=$(realpath "$0/..")
version=$(date +%Y%m%d)
echo version=$version >$wd/Version.sh

cd $wd/..
rm -rf src
cvs -Rqd ${CVSROOT:-/cvs} co -PA \
    contrib/code/Snippets/arc4random.c \
    contrib/gnu/config/config.guess \
    src/kern/include/md5.h \
    src/usr.bin/lndir src/usr.bin/xinstall \
    src/usr.bin/make src/usr.bin/mkdep src/usr.bin/lorder \
    src/usr.bin/tsort \
    src/include/getopt.h src/include/ohash.h src/include/sysexits.h \
    src/include/stdbool.h \
    src/include/adler32.h src/include/md4.h \
    src/include/rmd160.h src/include/sfv.h src/include/sha1.h \
    src/include/sha2.h src/include/suma.h src/include/tiger.h \
    src/include/whirlpool.h src/kern/include/libckern.h \
    src/kern/c/strlfun.c \
    src/lib/libc/hash src/lib/libc/ohash \
    src/lib/libc/stdio/asprintf.c src/lib/libc/stdio/vasprintf.c \
    src/lib/libc/stdio/mktemp.c \
    src/lib/libc/stdlib/getopt_long.c src/lib/libc/stdlib/strtoll.c \
    src/share/mk/bsd.cfwrap.mk src/share/mk/bsd.dep.mk \
    src/share/mk/bsd.doc.mk src/share/mk/bsd.lib.mk \
    src/share/mk/bsd.lt.mk src/share/mk/bsd.man.mk \
    src/share/mk/bsd.obj.mk src/share/mk/bsd.own.mk \
    src/share/mk/bsd.prog.mk src/share/mk/bsd.subdir.mk \
    src/share/mk/bsd.sys.mk src/share/mk/sys.mk
mv src/kern/include/md5.h src/include/
rm -r src/kern
cvs -Rqd ${CVSROOT:-/cvs} co -r1.15 src/bin/mksh/setmode.c
top=$(dirname $(pwd))
topd=$(dirname $top)
topf=$(basename $top)
cd $topd
find $topf -type f | xargs chmod 644
find $topf -type f ! -path \*CVS\* | sort | cpio -oHdist \
    | gzip -n9 >mirmake-$version.cpio.gz
[ -n "$DEBUG" ] || rm -rf $wd/../src $wd/Version.sh $wd/../contrib/gnu
