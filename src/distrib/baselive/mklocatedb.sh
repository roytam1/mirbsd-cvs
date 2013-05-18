#!/bin/mksh
# $MirOS: src/distrib/baselive/mklocatedb.sh,v 1.3 2006/08/19 01:28:51 tg Exp $
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

function cleanup
{
	set -x
	cd $root
	set +e
	umount $root/var
	umount $root/usr/X11R6/lib/X11
	umount $root/tmp
	umount $root/home
	umount $root/etc
	umount $root/dev
	vnconfig -u svnd0
	rm -f $root/../locatedb.tmp $root/../locatedb.vnd
	exit ${1:-1}
}

set -x
rm -f $root/../locatedb.tmp $root/../locatedb.vnd
[[ -e $root/../locatedb.tmp ]] && exit 1
[[ -e $root/../locatedb.vnd ]] && exit 1
set -e
root=$(readlink -nf .)
cp "$1" $root/../locatedb.vnd
vnconfig svnd0 $root/../locatedb.vnd
set +e
cd $root
mount /dev/svnd0a dev || cleanup
rm -f dev/.rs
ln -s rd0a dev/root
mount_mfs -s 20480 swap $root/etc || cleanup
mount_mfs -s 300000 swap $root/home || cleanup
mount_mfs -s 600000 swap $root/tmp || cleanup
mount_mfs -s 20480 swap $root/usr/X11R6/lib/X11 || cleanup
mount_mfs -s 300000 swap $root/var || cleanup
pax -r -pe -f stand/fsrw.dat || cleanup
cp -r etc/skel home/live || cleanup
chown -R 32762:32762 home/live || cleanup
chroot $root /usr/libexec/locate.updatedb --fcodes=- --tmpdir=/var/tmp \
    --filesystems='ffs ufs mfs' >$root/../locatedb.tmp
if [[ -s $root/../locatedb.tmp ]]; then
	cp $root/../locatedb.tmp $root/stand/locate.database
	chmod 444 $root/stand/locate.database
	chown root:wheel $root/stand/locate.database
	rv=0
else
	rv=1
fi
rm -f $root/../locatedb.tmp
cleanup $rv
