#!/bin/ksh
# $MirOS: contrib/code/mirmake/dist/scripts/Copy.sh,v 1.5 2005/05/20 22:50:41 tg Exp $
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
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.

cd $(dirname $0)/..
rm -rf src
cvs -Rqd ${CVSROOT:-/cvs} co -PA \
    src/usr.bin/make src/usr.bin/mkdep/mkdep.sh src/lib/libc/ohash \
    src/usr.bin/lorder/lorder.sh src/usr.bin/readlink src/usr.bin/tsort \
    src/include/getopt.h src/include/ohash.h src/include/sysexits.h \
    src/include/md4.h src/include/md5.h src/include/rmd160.h \
    src/include/sha1.h src/include/sha2.h src/lib/libc/hash \
    src/lib/libc/stdlib/getopt_long.c src/lib/libc/string/strlfun.c \
    src/share/mk/bsd.sys.mk src/share/mk/bsd.dep.mk src/share/mk/bsd.lib.mk \
    src/share/mk/bsd.man.mk src/share/mk/bsd.obj.mk src/share/mk/bsd.own.mk \
    src/share/mk/bsd.prog.mk src/share/mk/bsd.subdir.mk src/share/mk/sys.mk
top=$(dirname $(pwd))
topd=$(dirname $top)
topf=$(basename $top)
cd $topd
find $topf -type f ! -path \*CVS\* | sort | cpio -oC512 -Hcpio \
    | gzip -n9 >mirmake-$(date +%Y%m%d).cpio.gz
