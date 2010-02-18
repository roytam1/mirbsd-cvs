#!/bin/mksh
# $MirOS$
#-
# Copyright (c) 2010
#	Thorsten Glaser <t.glaser@tarent.de>
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
# The current working directory, or else the directory in which this
# script resides, must be the root directory of a (extracted) Debian
# source package. It will then be renamed to the proper dirname, and
# a source package (*.dsc + others) will be created, then it will be
# renamed back.

echo >&2 "=== trying . = $(pwd)"
if ! dh_testdir >/dev/null 2>&1; then
	cd "$(dirname "$0")"
	echo >&2 "=== trying basedir = $(pwd)"
	if ! dh_testdir >/dev/null 2>&1; then
		echo >&2 "FAILED! Please change to the correct directory."
		exit 1
	fi
fi
mydir=$(pwd)
version=$(dpkg-parsechangelog -n1 | sed -n '/^Version: /s///p')
upstreamversion=${version%%-*([!-])}
upstreamversion=${version#+([0-9]):}
pkgstem=$(dpkg-parsechangelog -n1 | sed -n '/^Source: /s///p')
cd ..
mv "${mydir##*/}" "$pkgstem-$upstreamversion"
cd "$pkgstem-$upstreamversion"
dpkg-buildpackage -rfakeroot -S -I
rv=$?
fakeroot debian/rules clean
cd ..
mv "$pkgstem-$upstreamversion" "${mydir##*/}"

exit $rv
