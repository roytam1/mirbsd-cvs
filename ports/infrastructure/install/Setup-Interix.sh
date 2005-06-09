#!/bin/mksh
# $MirOS: ports/infrastructure/install/Setup-Interix.sh,v 1.11 2005/06/08 10:21:18 tg Exp $
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

PATH=/bin:/opt/gcc.3.3/bin:/usr/contrib/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/X11R6/bin
[ -n "$PATH_WINDOWS" ] && PATH=$PATH:/usr/contrib/win32/bin:$PATH_WINDOWS
PATH_ORIG=$PATH:/usr/X11R5:bin
export PATH=$PATH_ORIG

bd=$(cd $(dirname $0); pwd)
td=$(cd $bd/../..; pwd)

#target=${1:-/usr/mpkg}
mirror=$1 # will be $2
ftp=ftp
#ftp="runwin32 .../wget"
[ -z $mirror ] && mirror=http://mirbsd.mirsolutions.de/MirOS/distfiles/

mksh=mksh-R22c.cpio.gz
make=mirmake-20050602.cpio.gz
mtar=paxmirabilis-20050413.cpio.gz
roff=mirnroff-20050413.cpio.gz
mftp=mirftp-20050413.cpio.gz
mtre=mirmtree-20050413.cpio.gz

T=$(mktemp -d /tmp/mirports.XXXXXXXXXX) || {
	echo Cannot generate temp dir >&2
	exit 1
}

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
	echo cp $mirror/$roff .
	cp $mirror/$roff .
#	echo cp $mirror/$mftp .
#	cp $mirror/$mftp .
	echo cp $mirror/$mtre .
	cp $mirror/$mtre .
	;;
*)	# http
	echo $ftp $mirror$mksh
	$ftp $mirror$mksh
	echo $ftp $mirror$make
	$ftp $mirror$make
	echo $ftp $mirror$mtar
	$ftp $mirror$mtar
	echo $ftp $mirror$roff
	$ftp $mirror$roff
#	echo $ftp $mirror$mftp
#	$ftp $mirror$mftp
	echo $ftp $mirror$mtre
	$ftp $mirror$mtre
	;;
esac
echo 'checking CKSUMs... (no comment)'
cksum $mksh >s
cksum $make >>s
cksum $mtar >>s
cksum $roff >>s
#cksum $mftp >>s
cksum $mtre >>s
cat >t <<EOF
4137564449 227585 mksh-R22c.cpio.gz
109949125 292052 mirmake-20050602.cpio.gz
862398610 117237 paxmirabilis-20050413.cpio.gz
2807559264 222049 mirnroff-20050413.cpio.gz
1518604836 17212 mirmtree-20050413.cpio.gz
EOF

if ! cmp -s s t; then
	echo Checksum failure! >&2
	diff -u12 t s | grep '^[+-][^+-]' >&2
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

mkdir -p /usr/share/man/{cat,man}{1,2,3,4,5,6,7,8,9} \
    /usr/share/tmac/m{doc,e,s} /usr/libexec

if [ ! -x /usr/bin/nroff ]; then
	gzip -dc $mksh | cpio -id
	cd mksh
	SHELL=/bin/ksh CFLAGS="$CFLAGS -D_ALL_SOURCE" /bin/ksh ./Build.sh
	install -c -s -m 555 mksh /bin/mksh2
	mv /bin/mksh /bin/mksh1p && mv /bin/mksh2 /bin/mksh
	rm /bin/mksh1p || echo Warning: remove /bin/mksh1p later! >&2
	cd ..
	rm -rf mksh

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
		make NOMAN=yes obj
		make NOMAN=yes depend
		make NOMAN=yes
		make NOMAN=yes install
		cd ../../../..
	done
	rm -rf mirnroff
fi

gzip -dc $mksh | cpio -id
cd mksh
#if [ -e /usr/share/make/libmirmake.a ]; then
#	CFLAGS="$CFLAGS -D_ALL_SOURCE -I/usr/share/make" \
#	LIBS="$LIBS -L/usr/share/make -lmirmake" \
#	ksh ./Build.sh
#else
	CFLAGS="$CFLAGS -D_ALL_SOURCE" /bin/ksh ./Build.sh
#fi
install -c -s -m 555 mksh /bin/mksh2
mv /bin/mksh /bin/mksh1 && mv /bin/mksh2 /bin/mksh
rm /bin/mksh1 || echo Warning: remove /bin/mksh1 later! >&2
install -c -m 444 mksh.cat1 /usr/share/man/cat1/mksh.0
if ! fgrep /bin/mksh /etc/shells >/dev/null 2>&1; then
	echo /bin/mksh >>/etc/shells
fi
cd ..
rm -rf mksh

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
	make obj
	make depend
	make
	make install
	cd ../../../..
done
rm -rf mirnroff

gzip -dc $mtar | cpio -id
cd pax
make obj
make depend
make
make install BINDIR=/bin MANDIR=/usr/share/man/cat
cd ..
rm -rf pax

gzip -dc $mtre | cpio -id
cd mtree
make obj
make depend
make LIBS="-L\${.SYSMK} -lmirmake"
make install BINDIR=/usr/sbin MANDIR=/usr/share/man/cat
cd ..
rm -rf mtree

#gzip -dc $mftp | cpio -id
#cd ftp
#make obj
#make depend
#make
#make install BINDIR=/usr/bin MANDIR=/usr/share/man/cat
#cd ..
#rm -rf ftp

set +e
set -e

cd $td
rm -rf $T

if ! fgrep /usr/mpkg/lib /etc/profile.lcl >/dev/null 2>&1; then
	echo 'export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/mpkg/lib"' \
	    >>/etc/profile.lcl
fi
[[ $LD_LIBRARY_PATH = */usr/mpkg/lib* ]] || \
    export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/mpkg/lib"

exec make setup SHELL=/bin/mksh
