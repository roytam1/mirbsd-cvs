#!/bin/sh
# $MirOS: contrib/code/mirmake/Build.sh,v 1.17 2006/01/13 03:49:29 tg Exp $
#-
# Copyright (c) 2004, 2005
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
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.
#-
# Build MirMake. (Assumes mksh or bash)

OSN="$1"		# OStype
PFX="${2:-/usr/local}"	# Installation prefix (optional)
MPT="${3:-man/cat}"	# manpath (cat magic) (optional)
MKN="${4:-bmake}"	# name of executable (optional)
MAC="$5"		# machine (i386, macppc) (optional)
MAR="$6"		# machine_arch (i386, powerpc) (optional)
MOS="$7"		# machine_os (BSD, Linux) (optional)
MKS="$8"		# mirbsdksh path (optional)
BIN="$9"		# binown:bingrp (optional)

if [ x"$MAC" = x"" ]; then
	MAC="`machine 2>/dev/null || uname -m 2>/dev/null || echo unknown`"
fi

if [ x"$MAR" = x"" ]; then
	MAR="`arch -s 2>/dev/null || arch 2>/dev/null || echo unknown`"
fi

if [ x"$MOS" = x"" ]; then
	u="`uname`"
	case $u in
	*Linux*)	MOS=Linux	;;
	*BSD*)		MOS=BSD		;;
	*Interix*)	MOS=Interix	;;
	*Darwin*)	MOS=Darwin	;;
	esac
fi

case "$MOS" in
Interix)
	# Okay, we know this MACHINE_OS
	[ x"$MAC" = x"x86" ] && MAC=i386
	[ x"$MAC" = x"i386" ] && MAR=i386
	[ -z "$BIN" ] && BIN=-
	;;
BSD|Darwin|Linux)
	# Okay, we know this MACHINE_OS
	;;
*)
	echo "Error: we cannot continue with this MACHINE_OS"
	echo "value of '$MOS'. Please contact the MirOS"
	echo "development team at miros-discuss@mirbsd.org and"
	echo "submit your operating system information and uname -a"
	echo "output. Currently, the following values are supported:"
	echo "- BSD Darwin Interix Linux"
	echo "Your uname -a output is:"
	uname -a
	OSN=""	# fall through
	;;
esac

if [ x"$MAC" = x"unknown" ] || [ x"$MAR" = x"unknown" ] || [ x"$MOS" = x"unknown" ]; then
	echo "Error: cannot guess machine or machine_arch"
	echo "Your uname -a output is:"
	uname -a
	OSN=""	# fall through
fi

if [ x"$OSN" = x"" ]; then
	echo "Syntax:"
	echo " $0 <OStype> [<prefix> [<manpath> [<exename>"
	echo "	[<machine> [<machine_arch> [<machine_os>"
	echo "  [<mksh> [<binown>:<bingrp>]]]]]]]]"
	echo "OStype:  name of OS (eg. Debian)"
	echo "prefix:  installation target (default: /usr/local)"
	echo "manpath: manpath relative to <prefix> (default: man/cat)"
	echo "exename: name of executable to generate (default: bmake)"
	echo "<machine> and <machine_arch> describe the target machine"
	echo "and are guessed from machine='$MAC' and"
	echo "machine_arch='$MAR' respectively."
	echo "Possible values: (i386, i386), (macppc, powerpc), etc."
	echo "<machine_os> can currently only be: BSD Darwin Interix Linux"
	echo "If <manpath> contains the string 'cat', a catmanpage is"
	echo "generated and installed, else, an unformatted manpage"
	echo "will be installed. If <mksh> is given, it is searched"
	echo "first when determining the path of the mirbsdksh."
	echo "Default binary owner is root:bin"
	exit 1
fi

mktest=""
for f in mksh mirbsdksh ksh; do
	for d in /bin /usr/local/bin /bin /sw/bin; do
		mktest="${mktest}${d}/${f} "
	done
done
ms=NONE
echo "Checking for mirbsdksh..."
for s in $MKS $mktest; do
	echo "Trying ${s}..."
	t="`$s -c 'let a=1; (( a + 1 )) 2>/dev/null && if [[ $KSH_VERSION = @(\@\(#\)MIRBSD KSH R)@(2[6-9]|[3-9][0-9]|[1-9][0-9][0-9])\ +([0-9])/+([0-9])/+([0-9]) ]]; then echo yes; else echo no; fi' 2>/dev/null`"
	if [ x"$t" = x"yes" ]; then
		echo "Found mirbsdksh: $s"
		ms=$s
		break
	fi
done

if [ -n "$OVERRIDE_MKSH" ]; then
	if test -x "$OVERRIDE_MKSH"; then
		ms="$OVERRIDE_MKSH"
	else
		for s in $MKS $mktest; do
			echo "Trying ${s} again..."
			t="`$s -c 'let a=1; (( a + 1 )) 2>/dev/null && if [[ -n $KSH_VERSION -o -n $BASH_VERSION ]]; then echo yes; else echo no; fi' 2>/dev/null`"
			if [ x"$t" = x"yes" ]; then
				echo "Found some ksh or bash: $s"
				ms=$s
				break
			fi
		done
	fi
fi

if [ x"$ms" = x"NONE" ]; then
	echo "Error: could not find mirbsdksh compatible shell."
	echo "Please go to: http://mirbsd.de/mksh and install it before"
	echo "continuing. At the moment, mksh R26 or higher is requited."
	exit 1
fi

echo "Building MirMake on $MOS/$MAC ($MAR) for $OSN"
echo "with $ms and ${CC:-gcc} to $PFX/bin/$MKN"
echo "Documentation goes to $PFX/${MPT}1/ (user ${BIN:-root:bin})"

exec $ms `dirname $0`/dist/scripts/Build.sh "$OSN" "$PFX" "$MPT" "$MKN" "$MAC" "$MAR" "$MOS" $ms "$BIN"
