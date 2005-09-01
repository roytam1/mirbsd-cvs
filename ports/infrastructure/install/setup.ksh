#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $
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
	print -u2 "Syntax: $me [-u|-U user[:group]]] [-l localbase] [-X xfbase]"
	print -u2 "  -u\tinstall as user (default root:bin except on Interix)"
	exit 1
}

if [[ $isinterix != @(yes|no) || -z $mirror \
    || -z $ourpath || -z $tempdir ]]; then
	print -u2 ERROR: Do not call this script directly!
	exit 1
fi
T=$tempdir

[[ -n $localbase ]] || localbase=/usr/mpkg
[[ -n $xfbase ]] || xfbase=/usr/X11R6
if [[ $interix = yes ]]; then
	user=$(id -un | sed 's! !\\ !g'):$(id -gn | sed 's! !\\ !g')
else
	user=root:bin
fi
iopt=0
while getopts "il:U:uX:" opt; do
	case $opt {
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

# Divine paths again (copied from Setup.sh)
if test $isinterix = no; then
	p=$localbase/bin
	for a in /usr/local/bin $xfbase/bin /usr/X11R6/bin /usr/bin /bin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	fi
	p=$p:$localbase/sbin
	for a in /usr/local/sbin /usr/sbin /sbin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	fi
	PATH=$p; export $PATH
else
	# On Interix, /usr/bin is /bin; gzip lives in /usr/contrib/bin;
	# gcc has yet its own directory; we have X11R5 as well
	p=$localbase/bin
	for a in /usr/local/bin /opt/gcc.3.3/bin /usr/contrib/bin /bin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	fi
	p=$p:$localbase/sbin
	for a in /usr/local/sbin /usr/sbin /sbin $xfbase/bin /usr/X11R6/bin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	fi
	test -n "$PATH_WINDOWS" && p=$p:/usr/contrib/win32/bin:$PATH_WINDOWS
	test -d /usr/X11R5/bin && p=$p:/usr/X11R5/bin
	PATH=$p; export $PATH

	export LD_LIBRARY_PATH_ORG=$LD_LIBRARY_PATH
	case :$LD_LIBRARY_PATH: in
	*:$localbase/lib:*) ;;
	*)	LD_LIBRARY_PATH=$localbase/lib:$LD_LIBRARY_PATH
		LD_LIBRARY_PATH=${LD_LIBRARY_PATH%:}
		export LD_LIBRARY_PATH
		;;
	esac
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

