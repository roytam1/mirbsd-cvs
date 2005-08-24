#!/bin/mksh
# $MirOS: src/usr.sbin/upkg/upkg.sh,v 1.1 2005/08/23 20:57:28 bsiegert Exp $
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
# a minimal version of pkg_add, written in shell. Requires mksh.

function usage
{
	print -u2 "Usage:"
	print -u2 " $0 [-L localbase] install [pkgname]"
	exit 1
}

[[ -n $1 ]] || usage

localbase=/usr/mpkg
while getopts "hL" c; do
	case $c {
	(h)	usage
		;;
	(L)	localbase=$OPTARG
		;;
	(*)	usage
		;;
	}
done
shift $((OPTIND - 1))

PKG_DBDIR=$localbase/pkg
