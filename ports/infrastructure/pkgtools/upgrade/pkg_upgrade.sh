#!/usr/bin/env mksh
# $MirOS: ports/infrastructure/pkgtools/upgrade/pkg_upgrade.sh,v 1.3 2005/09/12 22:59:56 tg Exp $
#-
# Copyright (c) 2005
#	Benny Siegert <bsiegert@66h.42h.de>
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
#-
# wrapper for pkg_add to upgrade packages
# This is only a "rapid prototype", the final implementation might
# be as a part of pkg_add.

if [[ -z $1 || $1 = -h ]]; then
	echo "Usage:"
	echo " $0 [pkgname]"
	exit 1
fi

PKG_DBDIR=@@dbdir@@/pkg
if [[ ! -d $PKG_DBDIR ]] ; then
	echo "$0: package database directory does not exist" >&2
	exit 1
fi

TMPDIR=$(mktemp -d /tmp/pkg_upgrade.XXXXXXXXXX) || exit 1
trap 'rm -rf $TMPDIR ; exit 0' 0
trap 'rm -rf $TMPDIR ; exit 1' 1 2 3 13 15

OLDPWD=$PWD
cd $TMPDIR
tar xfz $1 +CONTENTS
cd $PKG_DBDIR
PKGNAME=$(awk '$1=="@name" { print $2 }' $TMPDIR/+CONTENTS)
OLDPKGS=$(eval echo ${PKGNAME%%-[0-9]*}-[0-9]*)
cd $OLDPWD

if grep -q '^@option no-default-conflict' $TMPDIR/+CONTENTS || [[ -z "$OLDPKGS" ]] ; then
	# we can safely go on
	pkg_add $1
	exit
fi

if echo $OLDPKGS | grep -q ' ' ; then
	echo "$0: Multiple previous versions of this package are installed."
	echo "This is not supported in this version."
	echo "The packages in question are:"
	echo "$OLDPKGS"
	exit 1
fi

echo "pkg_upgrade: will remove $OLDPKGS in favour of $1"

if [[ -f $PKG_DBDIR/$OLDPKGS/+REQUIRED_BY ]] ; then
	mv -f $PKG_DBDIR/$OLDPKGS/+REQUIRED_BY $TMPDIR
fi

pkg_delete $OLDPKGS
pkg_add $1

if [[ -f $TMPDIR/$OLDPKGS/+REQUIRED_BY && -d $PKG_DBDIR/$PKGNAME ]] ; then
	mv $TMPDIR/$OLDPKGS/+REQUIRED_BY $PKG_DBDIR/$PKGNAME
fi
