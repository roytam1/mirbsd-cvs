#!/bin/sh
# $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $
#-
# Copyright (c) 2009
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
# Install GRUB2 (using the MirOS self-installing boot blocks) onto a
# FAT12/16/28 filesystem.

if test -z "$1" || test \! -e "$1"; then
	echo >&2 "Usage: $0 /dev/sda1 [bootgrubfat.mksh-options ...]"
	exit 1
fi

targetdev=$1
shift

T=$(mktemp /tmp/bxinst.XXXXXXXXXX) || {
	echo >&2 Cannot create temporary file
	exit 255
}

rv=0
mksh ${BOOTGRUBFAT_SH-bootgrubfat.mksh} "$@" >"$T" || rv=1
if test $rv = 0; then
	dd bs=1 if="$targetdev" skip=3 seek=3 count=87 of="$T" \
	    conv=notrunc || rv=2
fi
if test $rv = 0; then
	dd if="$T" bs=512 count=1 of="$targetdev" conv=notrunc || rv=3
fi
rm -f "$T"
exit $rv
