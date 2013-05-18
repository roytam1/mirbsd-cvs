#!/usr/bin/env mksh
# $MirOS: src/distrib/baselive/mklocatedb.sh,v 1.9 2008/10/05 16:26:16 tg Exp $
#-
# Copyright (c) 2006, 2007
#	Thorsten Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.

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
set -e
root=$(realpath .)
set +e
rm -f $root/../locatedb.tmp $root/../locatedb.vnd
[[ -e $root/../locatedb.tmp ]] && exit 1
[[ -e $root/../locatedb.vnd ]] && exit 1
set -e
sync
cp "$1" $root/../locatedb.vnd
sync
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
gzip -dc stand/fsrw.dat | pax -r -pe || cleanup
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
