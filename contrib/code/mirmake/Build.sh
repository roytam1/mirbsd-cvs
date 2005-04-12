#!/bin/sh
# $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $
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
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
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
	echo "development team at miros-discuss@66h.42h.de and"
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
	t="`$s -c 'let a=1; (( a + 1 )) 2>/dev/null && if [[ $KSH_VERSION = *@(MirOS \$Rev|MirOS R)* ]]; then echo yes; else echo no; fi' 2>/dev/null`"
	if [ x"$t" = x"yes" ]; then
		echo "Found mirbsdksh: $s"
		ms=$s
		break
	fi
done

if [ x"$ms" = x"NONE" ]; then
	echo "Error: could not find mirbsdksh compatible shell."
	echo "Please go to http://wiki.mirbsd.de/MirbsdKsh and"
	echo "install the shell before continuing."
	exit 1
fi

echo "Building MirMake on $MOS/$MAC ($MAR)"
echo "for $OSN with $MKS to $PFX/bin/$MKN"
echo "Documentation goes to $PFX/$MPT1/ (user ${BIN:-root:bin})"

exec $ms `dirname $0`/dist/scripts/Build.sh "$OSN" "$PFX" "$MPT" "$MKN" "$MAC" "$MAR" "$MOS" $ms "$BIN"
