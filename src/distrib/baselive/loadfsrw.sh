#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $
#-
# Copyright (c) 2010
#	Thorsten Glaser <tg@mirbsd.org>
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
#-
# Load MFS directories from /stand/fsrw.dat and offer to work on it,
# store them as /stand/fsrw.new afterwards unless '-c /mnt'.

if (( USER_ID )); then
	print -u2 need root
	exit 1
fi

if [[ $1 = -c ]]; then
	cd "$2"
	mknew=0
	mketc=0
else
	cd "$(dirname "$0")/obj/tmpdata"
	mknew=1
	mketc=1
fi
[[ $1 = -n ]] && mketc=0
if [[ ! -s stand/fsrw.dat ]]; then
	print -u2 need directory
	exit 1
fi
root=$(realpath .)

function cleanup
{
	set -x
	cd $root
	umount $root/var
	umount $root/usr/X11R6/lib/X11
	umount $root/tmp
	umount $root/etc
	(( mketc )) && rmdir etc
	(( mketc )) && mv etcnomfs etc
	exit ${1:-1}
}

cd "$root"
set -x
(( mketc )) && mv etc etcnomfs
(( mketc )) && mkdir etc
mount_mfs -s 20480 swap $root/etc || cleanup
mount_mfs -s 600000 swap $root/tmp || cleanup
mount_mfs -s 20480 swap $root/usr/X11R6/lib/X11 || cleanup
mount_mfs -s 300000 swap $root/var || cleanup
gzip -dc stand/fsrw.dat | pax -r -pe || cleanup

print === WAIT
read foo

(( mknew )) && find etc tmp usr/X11R6/lib/X11 var | sort | \
    cpio -oC512 -Hsv4crc -Mset | gzip -n9 >stand/fsrw.new
cleanup 0
