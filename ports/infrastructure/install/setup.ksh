#!/bin/mksh
# $MirOS: ports/infrastructure/install/setup.ksh,v 1.1.2.12 2005/09/11 15:07:50 tg Exp $
#-
# Copyright (c) 2005
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# All advertising materials mentioning features or use of this soft-
# ware must display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# This script really installs the MirPorts Framework.

me=$(basename $0)

function usage
{
	print -u2 "Syntax: $me [-u|-U user[:group]]] [-e|-E sysconfdir]"
	print -u2 "\t[-l localbase] [-X xfbase]"
	print -u2 "  -e\tset sysconfdir (default /etc; -e: \$localbase/etc)"
	print -u2 "  -u\tinstall as user (default root:bin except on Interix)"
	exit 1
}

if [[ $isinterix != @(yes|no) || -z $mirror \
    || -z $ourpath || -z $tempdir ]]; then
	print -u2 ERROR: Do not call this script directly!
	rm -rf $tempdir
	exit 1
fi
T=$tempdir

trap 'rm -rf $T; exit 1' 1 2 3 13 15
trap 'rm -rf $T; exit 0' 0

[[ -n $localbase ]] || localbase=/usr/mpkg
[[ -n $xfbase ]] || xfbase=/usr/X11R6
if [[ $interix = yes ]]; then
	user=$(id -un | sed 's! !\\ !g'):$(id -gn | sed 's! !\\ !g')
else
	user=root:bin
fi
etc=/etc
iopt=0
d=0
while getopts "DE:ehil:U:uX:" opt; do
	case $opt {
	(D)	d=1 ;;
	(E)	etc=$OPTARG ;;
	(e)	etc=@LOCALBASE@/etc ;;
	(i)	iopt=1 ;;
	(l)	localbase=$OPTARG ;;
	(U)	user=$OPTARG ;;
	(u)	user=$(id -un):$(id -gn) ;;
	(X)	xfbase=$OPTARG ;;
	(*)	usage ;;
	}
done
shift $((OPTIND - 1))

[[ $isinterix = yes ]] && LD_LIBRARY_PATH=$LD_LIBRARY_PATH_ORG
[[ $etc = @LOCALBASE@* ]] && etc=$localbase${etc#@LOCALBASE@}
[[ $d = 1 ]] && set -x

# Divine paths again (copied from Setup.sh)
if test $isinterix = no; then
	p=$localbase/bin
	for a in /usr/local/bin $xfbase/bin /usr/X11R6/bin /usr/bin /bin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	done
	p=$p:$localbase/sbin
	for a in /usr/local/sbin /usr/sbin /sbin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	done
	PATH=$p; export PATH
else
	# On Interix, /usr/bin is /bin; gzip lives in /usr/contrib/bin;
	# gcc has yet its own directory; we have X11R5 as well
	p=$localbase/bin
	for a in /usr/local/bin /opt/gcc.3.3/bin /usr/contrib/bin /bin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	done
	p=$p:$localbase/sbin
	for a in /usr/local/sbin /usr/sbin /sbin $xfbase/bin /usr/X11R6/bin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	done
	test -n "$PATH_WINDOWS" && p=$p:/usr/contrib/win32/bin:$PATH_WINDOWS
	test -d /usr/X11R5/bin && p=$p:/usr/X11R5/bin
	PATH=$p; export PATH

	LD_LIBRARY_PATH_ORG=$LD_LIBRARY_PATH
	case :$LD_LIBRARY_PATH: in
	*:$xfbase/lib:*) ;;
	*)	LD_LIBRARY_PATH=$xfbase/lib:$LD_LIBRARY_PATH ;;
	esac
	case :$LD_LIBRARY_PATH: in
	*:$localbase/lib:*) ;;
	*)	LD_LIBRARY_PATH=$localbase/lib:$LD_LIBRARY_PATH ;;
	esac
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH%%+(:)}
	export LD_LIBRARY_PATH LD_LIBRARY_PATH_ORG
fi

# Check some stuff
myuid=${user%%:*}
mygid=${user##*:}
x=0; print -n >$T/test && chown $myuid $T/test && chgrp $mygid $T/test \
    && chown $myuid:$mygid $T/test && rm $T/test && x=1
if [[ $x = 0 ]]; then
	print -u2 "Error: Cannot use UID '$myuid', GID '$mygid'!"
	exit 1
fi
[[ $myuid = root ]] || export BINOWN=$myuid
[[ $mygid = bin ]] || export BINGRP=$mygid
if [[ $isinterix = no && $myuid != root ]]; then
	# mostly copied from above, except for the export
	case :$LD_LIBRARY_PATH: in
	*:$xfbase/lib:*) ;;
	*)	LD_LIBRARY_PATH=$xfbase/lib:$LD_LIBRARY_PATH ;;
	esac
	case :$LD_LIBRARY_PATH: in
	*:$localbase/lib:*) ;;
	*)	LD_LIBRARY_PATH=$localbase/lib:$LD_LIBRARY_PATH ;;
	esac
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH%%+(:)}
fi
if [[ $isinterix = yes || $myuid != root ]]; then
	need_llp=yes
else
	need_llp=no
fi

isopenbsd=no
ismirbsd=no
isdarwin=no

case $(uname -s 2>/dev/null || uname) {
(MirBSD*)
	ismirbsd=yes ;;
(OpenBSD*)
	if uname -M >/dev/null 2>&1; then
		ismirbsd=yes
	else
		isopenbsd=yes
	fi
	;;
(Darwin*)
	let isdarwin=yes ;;
(*)
	print -u2 Cannot determine operating system.
	exit 1
	;;
}

portsdir=$(readlink -nf $ourpath/../.. 2>/dev/null || (cd $ourpath/../.. && pwd -P))

cp $portsdir/infrastructure/templates/fake.mtree $portsdir/infrastructure/db/
if [[ $myuid != root ]]; then
	print 'g/[ug]name=[a-z]*/s///g\n'"/^.set/s/   /" \
	    "uname=$myuid gname=$mygid /\nwq" \
	    | ed -s $portsdir/infrastructure/db/fake.mtree
fi
cat $portsdir/infrastructure/db/fake.mtree >$T/fake.mtree
(print '/@@local/d\ni\n'; IFS=/; s=;
 for pc in $(print "$localbase"); do
	s="$s    "; print "$s$pc"
 done; print '.\nwq') | ed -s $T/fake.mtree
mtree -U -e -d -n -p / -f $T/fake.mtree
mkdir -p $etc

# XXX this is the place to install other stuff
# XXX mmake nroff cpio mtree wget
# XXX install <mirports.sys.mk> with/instead mmake
[[ $ismirbsd = yes ]] || exit 1

cat >$localbase/db/SetEnv.sh <<-EOF
	LOCALBASE='$localbase'
	PORTSDIR='$portsdir'
	SYSCONFDIR='$etc'
	X11BASE='$xfbase'
	MAKECONF='$localbase/db/make.cfg'
	BINOWN='$myuid'
	BINGRP='$mygid'
	PATH='$PATH'
EOF
[[ $need_llp = yes ]] && \
    cat >>$localbase/db/SetEnv.sh <<-EOF
	LD_LIBRARY_PATH='$LD_LIBRARY_PATH'
EOF
cat >>$localbase/db/SetEnv.sh <<-EOF
	export LOCALBASE PORTSDIR SYSCONFDIR X11BASE MAKECONF
	export BINOWN BINGRP PATH LD_LIBRARY_PATH
EOF

cat >$localbase/db/SetEnv.csh <<-EOF
	# unsupported, untested, etc.pp
	setenv LOCALBASE '$localbase'
	setenv PORTSDIR '$portsdir'
	setenv SYSCONFDIR '$etc'
	setenv X11BASE '$xfbase'
	setenv MAKECONF '$localbase/db/make.cfg'
	setenv BINOWN '$myuid'
	setenv BINGRP '$mygid'
	setenv PATH '$PATH'
EOF
[[ $need_llp = yes ]] && \
    cat >>$localbase/db/SetEnv.csh <<-EOF
	setenv LD_LIBRARY_PATH '$LD_LIBRARY_PATH'
EOF

cat >$localbase/db/SetEnv.make <<-EOF
	LOCALBASE=	$localbase
	PORTSDIR?=	$portsdir
	SYSCONFDIR?=	$etc
	X11BASE?=	$xfbase
	MAKECONF=	$localbase/db/make.cfg
	BINOWN?=	$myuid
	BINGRP?=	$mygid
EOF
[[ $need_llp = yes ]] && \
    cat >>$localbase/db/SetEnv.make <<-EOF
	_OUR_LDLIBPATH=	$LD_LIBRARY_PATH
EOF

cat >$localbase/db/make.cfg <<-EOF
	# Default to include system-wide configuration
	.if exists(/etc/\${MAKE:T}.cfg)
	.  include "/etc/\${MAKE:T}.cfg"
	.endif
EOF

cd $portsdir/infrastructure/pkgtools
export LOCALBASE=$localbase
set -e
make cleandir
make obj
make cleandir
make depend
make PORTABLE=Yes PKG_USER="$myuid"
make install
set +e
rm -rf {rtfm,pkg,lib,info,delete,create,add}/obj
unset LOCALBASE

print Should be done now... have fun.
print Source $localbase/db/SetEnv.sh for playing.
exit 0
