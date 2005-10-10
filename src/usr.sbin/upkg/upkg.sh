#!/bin/mksh
# $MirOS: src/usr.sbin/upkg/upkg.sh,v 1.2 2005/08/24 09:59:14 tg Exp $
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

function upkg_get_file
{
	case $1 in
	*://*)
		# try it as a url
		ftp -vo - "$1"
	*)
		cat "$1"
	esac
}
		


function upkg_add
{
	set -e # abort on error

	TMPDIR=$(mktemp -d /tmp/pkg_upgrade.XXXXXXXXXX)
	trap 'rm -rf $TMPDIR ; exit 0' 0
	trap 'rm -rf $TMPDIR ; exit 1' 1 2 3 13 15
	
	upkg_get_file "$1" | (cd $TMPDIR ; tar xf -)
	cd $TMPDIR
	
	pkgname=$(awk '$1=="@name" { print $2 ; exit }' ./+CONTENTS)
	pkgdir=$PKG_DBDIR/$pkgname

	if [[ -f +REQUIRE ]] ; then
		chmod +x +REQUIRE
		if ! ./+REQUIRE $pkgname INSTALL ; then
			print -u2 "Package $pkgname fails requirements!"
			exit 1
		fi
	fi
	if [[ -f +INSTALL ]] ; then
		chmod +x +INSTALL
		if ! ./+INSTALL $pkgname PRE-INSTALL ; then
			print -u2 "Package $pkgname install script returned error status"
			exit 1
		fi
	fi
	
	awk '
	BEGIN {
		copycmd = "cpio -pld "
		mkdir_p = "mkdir -p "
	}

	$1 == "@cwd" {
		prefix = $2
	}
	
	/^[^@].*[^\/]$/ {
		last_file = $0
		if (user)
			user_files = user_files " " $0
		if (group)
			group_files = group_files " " $0
		if (mode)
			mode_files = mode_files " " $0
		print $0 | copycmd prefix
	}

	/^[^@].*\/$/ {
		system(mkdir_p prefix "/" $0)
	}

	$1 == "@user" {
		if (user_files != "") {
			system("chown", user, user_files) 
			user_files = ""
		}
		user = $2
	}

	$1 == "@group" {
		if (group_files != "") {
			system("chgrp", group, group_files) 
			group_files = ""
		}
		group = $2
	}

	$1 == "@mode" {
		if (mode_files != "") {
			system("chmod", mode, user_files) 
			mode_files = ""
		}
		mode = $2
	}
	
	$1 == "@sample" {
		if (substr($2, length($2), 1) == "/")
			system(mkdir_p prefix "/" $2)
	}

	END {
		if (user_files != "")
			system("chown", user, user_files) 
		if (group_files != "")
			system("chgrp", group, group_files) 
		if (mode_files != "")
			system("chmod", mode, user_files) 
	}	
	' +CONTENTS
	
	# Record the installation
	mkdir -p $pkgdir
	chmod a+rx $pkgdir
	cp -- +COMMENT +CONTENTS +DESC $pkgdir
	chmod 644 +COMMENT +CONTENTS +DESC
	for i in +INSTALL +DEINSTALL +REQUIRE +DISPLAY ; do
		if [[ -f $i ]] ; then
			cp $i $pkgdir
			chmod 644 $pkgdir/$i
		fi
	done

	if [[ -f +INSTALL ]] ; then
		chmod +x +INSTALL
		if ! ./+INSTALL $pkgname POST-INSTALL ; then
			print -u2 "Package $pkgname install script returned error status"
			exit 1
		fi
	fi
	if [[ -f +DISPLAY ]] ; then
		cat ./+DISPLAY
	fi
	
}

function usage
{
	print -u2 "Usage:"
	print -u2 " $0 [-L localbase] add [pkgname]"
	exit 1
}

[[ -n $1 ]] || usage

LOCALBASE=/usr/mpkg
while getopts "hL" c; do
	case $c {
	(h)	usage
		;;
	(L)	LOCALBASE=$OPTARG
		;;
	(*)	usage
		;;
	}
done
shift $((OPTIND - 1))

PKG_DBDIR=$localbase/db/pkg
if [[ ! -d $PKG_DBDIR ]] ; then
	mkdir -p $PKG_DBDIR
fi

if [[ "x$1" == "xadd" ]] ; then
	while [[ "x$2" != "x" ]] ; do
		upkg_add "$2"
		shift
	done
else
	usage
fi

