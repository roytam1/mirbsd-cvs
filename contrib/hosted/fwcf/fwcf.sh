#!/bin/sh
# $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $
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
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a defect.
#-
# FreeWRT Configuration Filesytem, Version 0.94

export PATH=/bin:/sbin:/usr/bin:/usr/sbin

case $1 in
setup|commit|erase) ;;
*)	cat >&2 <<EOF
FreeWRT Configuration Filesytem (fwcf), Version 0.94
Copyright (c) 2006 by Thorsten Glaser <tg@freewrt.org>

Syntax:
	$0 [commit | erase | setup]
EOF
	exit 1 ;;
esac

part=/dev/mtd/$(fgrep '"fwcf"' /proc/mtd 2>&- | sed 's/^mtd\([^:]*\):.*$/\1/')ro
if ! test -e "$part"; then
	echo 'fwcf: fatal error: no "fwcf" mtd partition found!' >&2
	exit 1
fi

if test $1 = erase; then
	fwcf.helper -Me | mtd -f write - fwcf
	exit $?
fi

if test $1 = setup; then
	if test -e /tmp/fwcf; then
		echo 'fwcf: error: "fwcf setup" already run!' >&2
		exit 1
	fi
	mkdir /tmp/fwcf
	chown 0:0 /tmp/fwcf
	chmod 700 /tmp/fwcf
	mkdir /tmp/fwcf/{root,temp}
	mount --bind /etc /tmp/fwcf/root
	mount -t mfs swap /tmp/fwcf/temp
	(cd /tmp/fwcf/root; tar cf - .) | (cd /tmp/fwcf/temp; tar xpf -)
	if ! fwcf.helper -U /tmp/fwcf/temp <"$part"; then
		echo 'fwcf: error: cannot extract' >&2
		exit 2
	fi
	rm -f /tmp/fwcf/temp/.fwcf_done
	if test -e /tmp/fwcf/temp/.fwcf_done; then
		echo 'fwcf: fatal: this is not Kansas any more' >&2
		exit 3
	fi
	echo -n >/tmp/fwcf/temp/.fwcf_done
	if test ! -e /tmp/fwcf/temp/.fwcf_done; then
		echo 'fwcf: fatal: cannot write to tmpfs' >&2
		exit 4
	fi
	mount --bind /tmp/fwcf/temp /etc
	if test ! -e /etc/.fwcf_done; then
		umount /etc
		echo 'fwcf: fatal: binding to /etc failed' >&2
		exit 5
	fi
	umount /tmp/fwcf/temp
	exit 0
fi

if test $1 = commit; then
	umount /tmp/fwcf/temp >&- 2>&-
	mount -t tmpfs swap /tmp/fwcf/temp
	(cd /etc; tar cf - .) | (cd /tmp/fwcf/temp; tar xpf -)
	rv=0
	if ! ( fwcf.helper -Mc /tmp/fwcf/temp | mtd -f write - fwcf ); then
		echo 'fwcf: error: cannot write to mtd!' >&2
		rv=6
	fi
	umount /tmp/fwcf/temp
	exit $rv
fi

echo 'fwcf: cannot be reached...' >&2
exit 255
