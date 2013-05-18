#!/bin/sh
# $MirOS: contrib/code/mirmake/dist/scripts/Copy.sh,v 1.22 2005/11/24 14:01:26 tg Exp $
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

wd=$(readlink -f $(dirname $0))
version=$(date +%Y%m%d)
echo version=$version >$wd/Version.sh

cd $wd/..
rm -rf src
cvs -Rqd ${CVSROOT:-/cvs} co -PA \
    contrib/gnu/config/config.guess \
    src/usr.bin/make src/usr.bin/mkdep src/usr.bin/lorder \
    src/usr.bin/readlink src/usr.bin/tsort src/usr.bin/xinstall \
    src/include/getopt.h src/include/ohash.h src/include/sysexits.h \
    src/include/md4.h src/include/md5.h src/include/rmd160.h \
    src/include/sha1.h src/include/sha2.h \
    src/lib/libc/hash src/lib/libc/ohash \
    src/lib/libc/stdio/asprintf.c src/lib/libc/stdio/vasprintf.c \
    src/lib/libc/stdio/mktemp.c \
    src/lib/libc/stdlib/getopt_long.c src/lib/libc/stdlib/strtoll.c \
    src/lib/libc/string/strlfun.c \
    src/share/mk/bsd.cfwrap.mk \
    src/share/mk/bsd.sys.mk src/share/mk/bsd.dep.mk src/share/mk/bsd.lib.mk \
    src/share/mk/bsd.man.mk src/share/mk/bsd.obj.mk src/share/mk/bsd.own.mk \
    src/share/mk/bsd.prog.mk src/share/mk/bsd.subdir.mk src/share/mk/sys.mk
top=$(dirname $(pwd))
topd=$(dirname $top)
topf=$(basename $top)
cd $topd
find $topf -type f | xargs chmod 644
find $topf -type f ! -path \*CVS\* | sort | cpio -oHdist \
    | gzip -n9 >mirmake-$version.cpio.gz
[ -n "$DEBUG" ] || rm -rf $wd/../src $wd/Version.sh $wd/../contrib/gnu
