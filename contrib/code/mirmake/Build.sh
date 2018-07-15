#!/usr/bin/env sh
# $MirOS: contrib/code/mirmake/Build.sh,v 1.43 2012/11/30 21:22:53 tg Exp $
#-
# Copyright (c) 2004, 2005, 2006, 2008, 2012
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
# Build MirMake. (Assumes mksh or bash)

LC_ALL=C
export LC_ALL

OSN=$1			# OStype
PFX=${2:-/usr/local}	# Installation prefix (optional)
MPT=${3:-man/cat}	# manpath (cat magic) (optional)
MKN=${4:-bmake}		# name of executable (optional)
MAC=$5			# machine (i386, macppc) (optional)
MAR=$6			# machine_arch (i386, powerpc) (optional)
MOS=$7			# machine_os (BSD, Darwin, GNU, Interix) (optional)
MKS=$8			# mirbsdksh path (optional)
BIN=$9			# binown:bingrp (optional)

OLDMAKE=${MAKE-make}	# system's own make(1) binary
export OLDMAKE		# for bootstrapping

# help
case $OSN in
-*)	OSN= ;;
esac

if [ x"$MAC" = x"" ]; then
	x=`printf 'all:\n\t@echo unknown' | \
	    $OLDMAKE -V MACHINE -f - all 2>/dev/null || echo unknown`
	[ x"$x" != x"" ] && [ x"$x" != x"unknown" ] && MAC=$x
fi

if [ x"$MAR" = x"" ]; then
	x=`printf 'all:\n\t@echo unknown' | \
	    $OLDMAKE -V MACHINE_ARCH -f - all 2>/dev/null || echo unknown`
	[ x"$x" != x"" ] && [ x"$x" != x"unknown" ] && MAR=$x
fi

if [ x"$MAC" = x"" ]; then
	MAC=`machine 2>/dev/null || uname -m 2>/dev/null || echo unknown`
fi

if [ x"$MAR" = x"" ]; then
	MAR=`arch -s 2>/dev/null || arch 2>/dev/null || \
	    uname -p 2>/dev/null || echo unknown`
fi

if [ x"$MOS" = x"" ]; then
	u=`uname`
	case $u in
	*Linux*|*GNU*)	MOS=GNU		;;
	*BSD*)		MOS=BSD		;;
	*Interix*)	MOS=Interix	;;
	*Darwin*)	MOS=Darwin	;;
	esac
fi

case $MOS in
Interix)
	# Okay, we know this MACHINE_OS
	[ x"$MAC" = x"x86" ] && MAC=i386
	[ x"$MAC" = x"i386" ] && MAR=i386
	[ -z "$BIN" ] && BIN=-
	;;
BSD|Darwin)
	# Okay, we know this MACHINE_OS
	;;
GNU|Linux)
	MOS=GNU
	# austriancoder's GNU/Linux has _no_ uname option to
	# display the correct machine architecture, nor some
	# kind of arch(1) utility like OpenBSD; from FreeWRT
	case $MAC in
	i[3456789]86)
		MAR=i386
		;;
	x86_64)
		MAR=amd64
		;;
	esac
	;;
*)
	echo "Error: we cannot continue with this MACHINE_OS"
	echo "value of '$MOS'. Please contact the MirOS"
	echo "development team via http://www.mirbsd.org/rss.htm#lists and"
	echo "submit your operating system information and uname -a"
	echo "output. Currently, the following values are supported:"
	echo "- BSD Darwin GNU Interix"
	echo "Your uname -a output is:"
	uname -a
	OSN=	# fall through
	;;
esac

if [ x"$MAC" = x"unknown" ] || [ x"$MAR" = x"unknown" ] || [ x"$MOS" = x"unknown" ]; then
	echo "Error: cannot guess machine or machine_arch"
	echo "Your uname -a output is:"
	uname -a
	OSN=	# fall through
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
	echo "<machine_os> can currently only be: BSD Darwin GNU Interix"
	echo "If <manpath> contains the string 'cat', a catmanpage is"
	echo "generated and installed, else, an unformatted manpage"
	echo "will be installed. If <mksh> is given, it is searched"
	echo "first when determining the path of the mirbsdksh."
	echo "Default binary owner is root:bin"
	exit 1
fi

mktest=
for f in mksh mirbsdksh ksh; do
	for d in /usr/bin /usr/local/bin /bin /sw/bin; do
		mktest="${mktest}${d}/${f} "
	done
done
ms=NONE
echo "Checking for mirbsdksh..."
for s in $MKS $MKSH $mktest $SHELL; do
	echo "Trying ${s}..."
	t=`$s -c 'let a=1; (( a + 1 )) 2>/dev/null && if [[ $KSH_VERSION = @(\@\(#\)MIRBSD KSH R)@(3[4-9]|[4-9][0-9]|[1-9][0-9]+([0-9]))\ +([0-9])/+([0-9])/+([0-9])?(\ *) ]]; then echo yes; else echo no; fi' 2>/dev/null`
	if [ x"$t" = x"yes" ]; then
		echo "Found mirbsdksh: $s"
		ms=$s
		break
	fi
done

if [ -n "$OVERRIDE_MKSH" ]; then
	if test -x "$OVERRIDE_MKSH"; then
		ms=$OVERRIDE_MKSH
	else
		for s in $MKS $mktest; do
			echo "Trying ${s} again..."
			t=`$s -c 'let a=1; (( a + 1 )) 2>/dev/null && if [[ -n $KSH_VERSION || -n $BASH_VERSION ]]; then echo yes; else echo no; fi' 2>/dev/null`
			if [ x"$t" = x"yes" ]; then
				echo "Found some ksh or bash: $s"
				ms=$s
				break
			fi
		done
	fi
fi

if [ x"$ms" = x"NONE" ]; then
	echo "Error: could not find a mirbsdksh compatible shell."
	echo "Please go to <http://mirbsd.de/mksh> and install it before"
	echo "continuing. At the moment, mksh R34 or higher is required;"
	echo "using a recent one like mksh R37c is strongly recommended."
	exit 1
fi

echo "Building MirMake on $MOS/$MAC ($MAR) for $OSN"
echo "with $ms and ${CC:-gcc} to $PFX/bin/$MKN"
echo "Documentation goes to $PFX/${MPT}1/ (user ${BIN:-root:bin})"

MKSH=$ms; export MKSH
exec $ms `dirname $0`/dist/scripts/Build.sh "$OSN" "$PFX" "$MPT" "$MKN" "$MAC" "$MAR" "$MOS" $ms "$BIN"
