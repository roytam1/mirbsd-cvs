#!/bin/ksh
# $MirOS: ports/infrastructure/install/Setup-Interix.sh,v 1.1 2005/04/13 16:16:42 tg Exp $
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
testing=1

# Since we're on NT, we can't exchange running binaries.
[ x"$SHELL" = x"/bin/mksh" ] && exec /bin/ksh $0 "$@"

PATH=/bin:/opt/gcc.3.3/bin:/usr/contrib/bin:/usr/local/bin:/usr/X11R6/bin
[ -n "$PATH_WINDOWS" ] && PATH=$PATH:/usr/contrib/win32/bin:$PATH_WINDOWS
PATH_ORIG=$PATH:/usr/X11R5:bin
export PATH=$PATH_ORIG

if [ -e mktemp.sh ]; then
	rm -f /bin/mktemp
	install -c -m 555 mktemp.sh /bin/mktemp
fi

bd=$(cd $(dirname $0); pwd)
td=$(cd $bd/../..; pwd)

#target=${1:-/usr/mpkg}
mirror=$1 # will be $2
[ -z $mirror ] && mirror=http://mirbsd.mirsolutions.de/MirOS/distfiles/

mksh=mirbsdksh-R20.cpio.gz
make=mirmake-20050412.cpio.gz
mtar=paxmirabilis-20050228.cpio.gz
roff=mirnroff-20050412.cpio.gz
mftp=mirftp-20050413.cpio.gz

T=$(mktemp -d /tmp/mirports.XXXXXXXXXX) || { echo Cannot generate temp dir; \
    exit 1; }

cd $T
case "$mirror" in
/*)	# file
	echo cp $mirror/$mksh .
	cp $mirror/$mksh .
	echo cp $mirror/$make .
	cp $mirror/$make .
	echo cp $mirror/$mtar .
	cp $mirror/$mtar .
	echo cp $mirror/$roff .
	cp $mirror/$roff .
	echo cp $mirror/$mftp .
	cp $mirror/$mftp .
	;;
*)	# http
	echo ftp $mirror$mksh
	ftp $mirror$mksh
	echo ftp $mirror$make
	ftp $mirror$make
	echo ftp $mirror$mtar
	ftp $mirror$mtar
	echo ftp $mirror$roff
	ftp $mirror$roff
	echo ftp $mirror$mftp
	ftp $mirror$mftp
	;;
esac
echo 'checking CKSUMs... (no comment)'
cksum $mksh >s
cksum $make >>s
cksum $mtar >>s
cksum $roff >>s
cksum $mftp >>s
echo "62583208 292816 mirbsdksh-R20.cpio.gz" >t
echo "1984996926 279003 mirmake-20050412.cpio.gz" >>t
echo "3380377454 117013 paxmirabilis-20050228.cpio.gz" >>t
echo "2584789426 221690 mirnroff-20050412.cpio.gz" >>t
echo "3462097166 62625 mirftp-20050413.cpio.gz" >>t

if ! cmp -s s t; then
	echo Checksum failure!
	diff -u12 t s | grep '^[+-][^+-]'
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

mkdir -p /usr/share/man/{cat,man}1 /usr/share/tmac/m{doc,e,s}

if [ ! -x /usr/bin/nroff ]; then
	gzip -dc $mksh | cpio -id
	cd ksh
	SHELL=/bin/ksh CFLAGS="$CFLAGS -D_ALL_SOURCE" ksh ./Build.sh
	install -c -s -m 555 mksh /bin/mksh
	cd ..
	rm -rf ksh

	gzip -dc $make | cpio -id
	cd mirmake
	/bin/mksh ./Build.sh \
	    Interix /usr share/man/man make \
	    "" "" "" /bin/mksh -
	/bin/mksh ./Install.sh
	rm -f /usr/share/man/man1/make.1
	cd ..
	rm -rf mirmake

	gzip -dc $roff | cpio -id
	for subdir in mirnroff/src/{usr.bin/oldroff,share/tmac}; do
		cd $subdir
		SHELL=/bin/mksh make NOMAN=yes obj
		SHELL=/bin/mksh make NOMAN=yes depend
		SHELL=/bin/mksh make NOMAN=yes
		SHELL=/bin/mksh make NOMAN=yes install
		cd ../../../..
	done
	cd ..
	rm -rf pax
fi

gzip -dc $mksh | cpio -id
cd ksh
CFLAGS="$CFLAGS -D_ALL_SOURCE" ksh ./Build.sh
install -c -s -m 555 mksh /bin/mksh
install -c -m 444 mksh.0 /usr/share/man/cat1/mksh.1
if ! fgrep /bin/mksh /etc/shells >/dev/null 2>&1; then
	echo /bin/mksh >>/etc/shells
fi
cd ..
rm -rf ksh

gzip -dc $make | cpio -id
cd mirmake
ksh ./Build.sh \
    Interix /usr share/man/cat make \
    "" "" "" /bin/mksh -
/bin/mksh ./Install.sh
cd ..
rm -rf mirmake

gzip -dc $roff | cpio -id
for subdir in mirnroff/src/{usr.bin/oldroff,share/tmac,usr.bin/soelim}; do
	cd $subdir
	SHELL=/bin/mksh make obj
	SHELL=/bin/mksh make depend
	SHELL=/bin/mksh make
	SHELL=/bin/mksh make install
	cd ../../../..
done
cd ..
rm -rf pax

gzip -dc $mtar | cpio -id
cd pax
SHELL=/bin/mksh make obj
SHELL=/bin/mksh make depend
SHELL=/bin/mksh make
SHELL=/bin/mksh make install BINDIR=/bin MANDIR=/usr/share/man/cat
cd ..
rm -rf pax

gzip -dc $mftp | cpio -id
cd ftp
SHELL=/bin/mksh make obj
SHELL=/bin/mksh make NO_INET6=1 depend
SHELL=/bin/mksh make NO_INET6=1
SHELL=/bin/mksh make install BINDIR=/usr/bin MANDIR=/usr/share/man/cat
cd ..
rm -rf ftp

set +e
for page in make pax tar cpio; do
	mv /usr/share/man/cat1/$page.0 /usr/share/man/cat1/$page.1
done
set -e

cd $td
rm -rf $T
make setup SHELL=/bin/mksh
