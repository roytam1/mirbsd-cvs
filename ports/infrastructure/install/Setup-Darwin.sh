#!/bin/bash
# $MirOS: ports/infrastructure/install/Setup-Darwin.sh,v 1.8 2005/04/13 21:44:23 tg Exp $
#-
# Copyright (c) 2005
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
# Retrieve prerequisites for running MirPorts on Mac OSX

# DO NOT UNCOMMENT
#testing=1

export PATH=/bin:/sbin:/usr/bin:/usr/sbin

bd=$(cd $(dirname $0); pwd)
td=$(cd $bd/../..; pwd)

#target=${1:-/usr/mpkg}
mirror=$1 # will be $2
binown=$(echo "${2:-root:bin}" | sed 's/:.*$//') # will be $3
bingrp=$(echo "${2:-root:bin}" | sed 's/^.*://') # will be $3
[ -z $mirror ] && mirror=http://mirbsd.mirsolutions.de/MirOS/distfiles/

mksh=mirbsdksh-R20.cpio.gz
make=mirmake-20050521.cpio.gz
mtar=paxmirabilis-20050413.cpio.gz

T=$(mktemp -d /tmp/mirports.XXXXXXXXXX) || { echo Cannot generate temp dir; \
    exit 1; }

echo "===> building in $T"

cd $T
case "$mirror" in
/*)	# file
	echo cp $mirror/$mksh .
	cp $mirror/$mksh .
	echo cp $mirror/$make .
	cp $mirror/$make .
	echo cp $mirror/$mtar .
	cp $mirror/$mtar .
	;;
*)	# http
	echo ftp $mirror$mksh
	ftp $mirror$mksh
	echo ftp $mirror$make
	ftp $mirror$make
	echo ftp $mirror$mtar
	ftp $mirror$mtar
	;;
esac
echo 'checking MD5 sums... (tell Apple to make RMD160 part of the base OS!)'
md5 $mksh >s
md5 $make >>s
md5 $mtar >>s
echo "MD5 ($mksh) = 2267876639a682dd8d43f28aa697241c" >t
echo "MD5 ($make) = 436949ce3f3163e5cb6cbf41a84cdb10" >>t
echo "MD5 ($mtar) = 8f48631579a700b5328025c7dbc7ac7d" >>t

if ! cmp -s s t; then
	echo Checksum failure!
	diff -u12 t s | fgrep MD5
	if [ x"$testing" != x"1" ]; then
		cd $td
		rm -rf $T
		exit 1
	else
		echo WARNING: testing engaged!
	fi
fi


export CC="${CC:-gcc}"
export CFLAGS="${CFLAGS:--O2 -fno-strength-reduce -fno-strict-aliasing}"

set -e # XXX should set up a trap, but...
set -x

gzip -dc $mksh | cpio -id
cd ksh
SHELL=/bin/bash WEIRD_OS=1 bash ./Build.sh
install -c -s -o $binown -g $bingrp -m 555 mksh /bin/mksh
install -c -o $binown -g $bingrp -m 444 mksh.1 /usr/share/man/man1/mksh.1
if ! fgrep /bin/mksh /etc/shells >/dev/null 2>&1; then
	echo /bin/mksh >>/etc/shells
fi
cd ..
rm -rf ksh

gzip -dc $make | cpio -id
cd mirmake
SHELL=/bin/mksh /bin/mksh ./Build.sh \
    Darwin /usr/mpkg man/man mmake \
    "" "" Darwin \
    /bin/mksh $binown:$bingrp
/bin/mksh ./Install.sh
cd ..
export PATH=/usr/mpkg/bin:$PATH
rm -rf mirmake

gzip -dc $mtar | cpio -id
cd pax
SHELL=/bin/mksh mmake obj
SHELL=/bin/mksh mmake depend
SHELL=/bin/mksh mmake
mkdir -p /usr/mpkg/bin /usr/mpkg/man/cat1
SHELL=/bin/mksh mmake install BINDIR=/usr/mpkg/bin MANDIR=/usr/mpkg/man/cat
cd ..
rm -rf pax

cd $td
rm -rf $T
mmake setup SHELL=/bin/mksh
