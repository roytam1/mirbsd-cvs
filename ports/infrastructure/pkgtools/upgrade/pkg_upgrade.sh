#!/usr/bin/env mksh
# $MirOS: ports/infrastructure/pkgtools/upgrade/pkg_upgrade.sh,v 1.19 2006/08/22 20:50:49 bsiegert Exp $
#-
# Copyright (c) 2006
#	Thorsten Glaser <tg@mirbsd.de>
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

me=${0##*/}

function usage
{
	print -u2 Usage:
	print -u2 "\t$me [-afqs] pkgname.cgz"
	exit 1
}

function twiddle_plists
{
	export oldcontents newcontents stubfiles
	awk '
	BEGIN {
		oldcontents = ENVIRON["oldcontents"]
		newcontents = ENVIRON["newcontents"]
		stubfiles = ENVIRON["stubfiles"]
		lib_seen = 0
	}

	function handle_lib(name) {
		if (FILENAME==newcontents) {
			# first mode: collect libraries
			shlibs[name] = "new"
		} else {
			# second mode: distribute them
			if (shlibs[name]=="new") {
				print
			} else {
				print >> stubfiles
				lib_seen = 1
			}
		}
	}

	$1=="@lib"		{ handle_lib($2) ; next }
	/^[^@].*\.dylib$/	{ handle_lib($0) ; next }

	{
		if (FILENAME==oldcontents) {
			if (lib_seen==1 && $1=="@comment" && $2~/^MD5:/)
				print >> stubfiles
			else
				print
		}
		lib_seen = 0
	}' $newcontents $oldcontents > $oldcontents_new
}

function build_stub
{
	print -u2 "$me: building stub package shlibs-$OLDPKGS"
	stubpkgdir=$TMPDIR/shlibs-$OLDPKGS
	oldpkgdir=$PKG_DBDIR/$OLDPKGS
	stubcontents=$stubpkgdir/+CONTENTS
	newcontents=$TMPDIR/+CONTENTS

	mkdir $stubpkgdir
	echo -n "shared libraries stub: " > $stubpkgdir/+COMMENT
	cat $oldpkgdir/+COMMENT >> $stubpkgdir/+COMMENT
	cp $oldpkgdir/+DESC $stubpkgdir
	[[ -f $TMPDIR/+REQUIRED_BY ]] && cp $TMPDIR/+REQUIRED_BY $stubpkgdir

	echo "@name shlibs-$OLDPKGS" > $stubcontents
	echo "@pkgdep $PKGNAME" >> $stubcontents
	# only the first @cwd
	awk '$1=="@cwd" { print ; exit }' $oldcontents >> $stubcontents
	grep '^@option ' $oldcontents >> $stubcontents
	cat $stubfiles >> $stubcontents
	# ldconfig invocations too
	fgrep exec $oldcontents | fgrep ldconfig >> $stubcontents
	echo >> $stubcontents << EOF
@cwd .
@ignore
+COMMENT
@ignore
+DESC
EOF

	# Register the package
	mv -f $stubpkgdir $PKG_DBDIR
	mv -f $oldcontents_new $oldcontents
}


######################################################################

auto=0
force=0
quiet=0
stubs=0
while getopts "afhqs" option; do
	case $option {
	(a)	auto=1 ;;
	(f)	force=1 ;;
	(h)	usage ;;
	(q)	quiet=1 ;;
	(s)	stubs=1 ;;
	(*)	usage ;;
	}
done
shift $((OPTIND - 1))
[[ -n $1 ]] || usage
npkg="$(readlink -nf "$1")"

PKG_DBDIR=@@dbdir@@/pkg
if [[ ! -d $PKG_DBDIR ]] ; then
	print -u2 "$me: package database directory does not exist"
	exit 1
fi

if [[ ! -s $npkg ]]; then
	print -u2 "$me: package file '$1' does not exist"
	exit 1
fi

TMPDIR=$(mktemp -d /tmp/pkg_upgrade.XXXXXXXXXX) || exit 1
trap 'rm -rf $TMPDIR ; exit 0' 0
trap 'rm -rf $TMPDIR ; exit 1' 1 2 3 5 13 15

OLDPWD=$PWD
cd $TMPDIR
tar xfz "$npkg" +CONTENTS
cd $PKG_DBDIR
PKGNAME=$(awk '$1=="@name" { print $2 }' $TMPDIR/+CONTENTS)
OLDPKGS=$(echo ${PKGNAME%%-[0-9]*}-[0-9]*)
[[ $OLDPKGS = ?(${PKGNAME%%-[0-9]*})@(-\[0-9\]\*) ]] && OLDPKGS=
if [[ $auto = 1 && -z $OLDPKGS ]]; then
	[[ $quiet = 1 ]] || print -u2 "$me: ignoring uninstalled package '${1##*/}'"
	exit 0
fi
cd $OLDPWD

grep -q '^@option no-default-conflict' $TMPDIR/+CONTENTS
if [[ $? -eq 0 || -z "$OLDPKGS" ]]; then
	# we can safely go on
	[[ $quiet = 1 ]] || print -u2 "$me: adding previously uninstalled '${1##*/}'"
	rm -rf $TMPDIR
	exec pkg_add "$npkg"
fi

if [[ $OLDPKGS = *\ * ]]; then
	print -u2 "$me: multiple previous versions of this package are"
	print -u2 "installed. This is not supported in this version."
	print -u2 "The packages in question are:"
	print -u2 "$OLDPKGS"
	exit 1
fi

# Check if we try to re-install same-version packages
NEWPKG=${1##*/}
[[ $OLDPKGS = ${NEWPKG%.+([a-zA-Z])} && $force = 0 ]] && exit 0

print -u2 "$me: will remove $OLDPKGS in favour of ${1##*/}"

if [[ -f $PKG_DBDIR/$OLDPKGS/+REQUIRED_BY ]] ; then
	mv -f $PKG_DBDIR/$OLDPKGS/+REQUIRED_BY $TMPDIR
fi

fd=
fa=
if grep -qi '^@comment upgrade-no-scripts' $TMPDIR/+CONTENTS; then
	fd=-D
	fa=-I
fi
if grep -qi '^@comment upgrade-no-install-script' $TMPDIR/+CONTENTS; then
	fa=-I
fi
if grep -qi '^@comment upgrade-no-deinstall-script' $TMPDIR/+CONTENTS; then
	fd=-D
fi

# Check for shared libraries
newcontents=$TMPDIR/+CONTENTS			# package to be installed
oldcontents=$PKG_DBDIR/$OLDPKGS/+CONTENTS	# older, installed version
oldcontents_new=$TMPDIR/+CONTENTS-$OLDPKGS	# new version of oldcontents
stubfiles=$TMPDIR/+STUB				# files to put into shlibs stub

[[ $stubs = 1 ]] && twiddle_plists

if grep -qi '^@option base-package' $TMPDIR/+CONTENTS; then
	print -u2 "$me: '$OLDPKGS' is a base package, unregistering only"
	pkg_delete $fd -U $OLDPKGS && pkg_add $fa -Nq "$npkg"
else
	[[ $stubs = 1 && -s $stubfiles ]] && build_stub
	pkg_delete $fd $OLDPKGS && pkg_add $fa "$npkg"
fi

if [[ -f $TMPDIR/+REQUIRED_BY && -d $PKG_DBDIR/$PKGNAME ]] ; then
	mv $TMPDIR/+REQUIRED_BY $PKG_DBDIR/$PKGNAME
fi
