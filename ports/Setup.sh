#!/bin/sh
# $MirOS: ports/Setup.sh,v 1.7 2005/09/12 23:25:55 tg Exp $
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
# This script installs mksh if needed, then calls setup.ksh with it.
# On Interix, nroff is also installed first.

# Constants

test -d ${localbase:-/nonexist} || localbase=/usr/mpkg
test -d ${xfbase:-/nonexist} || xfbase=/usr/X11R6
# ... in case we have XFree86(R) as a port
test -r $localbase/X11/include/X11/X.h && xfbase=$localbase/X11
test -f $localbase/X11/bin/xterm && xfbase=$localbase/X11
export localbase
export xfbase

#mksh_ver=24 # unused
mksh_date="24 2005/08/21"

mirror=$1
case x$1 in
	x-*)	mirror= ;;
	x)	;;
	*)	shift ;;
esac
if test x"$mirror" = x; then
	mirror=http://mirbsd.mirsolutions.de/MirOS/dist/
fi
export mirror

# Are we Interix?
isinterix=no
test -n "$SFUDIR" && isinterix=yes
test -n "$OPENNT_ROOT" && isinterix=yes
export isinterix

# Set the PATHs
#%%BEGIN sync Setup.sh with setup.ksh %% paths
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
#%%END sync Setup.sh with setup.ksh %% paths

# Where are we?
ourpath=`dirname $0`
ourpath=`(cd $ourpath && pwd)`
export ourpath
mkdir -p $ourpath/Distfiles

# Divine a fetching utility
fetch=false
if test $isinterix = yes; then
	# check for Weihenstephan wget
	test -f /dev/fs/C/usr/local/wbin/wget.exe && \
	    fetch="runwin32 c:/usr/local/wbin/wget.exe"
fi
if test x"$fetch" = x"false"; then
	# Check for ftp/wget/fetch
	for dir in /usr/mpkg/bin /usr/local/bin /bin /usr/bin; do
		if test -f $dir/wget; then
			fetch=$dir/wget
			break
		fi
		if test -f $dir/fetch; then
			fetch=$dir/fetch
			break
		fi
		if test -f $dir/ftp; then
			fetch=$dir/ftp
			break
		fi
	done
fi
export fetch

# Divine a C compiler
if test -z "$CC"; then
	if mgcc -v >/dev/null 2>&1; then
		CC=mgcc
	elif gcc -v >/dev/null 2>&1; then
		CC=gcc
	else
		CC=cc
	fi
	export CC
fi

# Divine a temporary directory
if T=$(mktemp -d /tmp/mirports.XXXXXXXXXX); then
	:
else
	# May be Interix without mktemp.sh
	T=/tmp/mirports.$$.$RANDOM
	if test -d $T; then
		echo Cannot generate temporary directory >&2
		exit 1
	fi
	mkdir -p $T || {
		echo Cannot generate temporary directory >&2
		exit 1
	}
fi
echo Notice: Temporary Directory: $T >&2
echo 'ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAoEAy5akQiuw0znRhMD0djgQ7BiUPahG1QHJb9ZNApd6D5OnV98FO8Ofbfm4CF1Cvwr+IPnyKyPglQnaFgHF3LVynKMYSupKXnd0JrBR79TBmIVImBnIaTPcApRdWZEbMW5IdYhrWFHKlzk4vDxBXdcVE6QfiemWsYqkiuoJvLTLHXq7WUCQ5z7KuQetMnnP2bswV8SZuYy0IvzQRBVJbiTQzBvsHfyZUERLBZvjtPE9jTaLdTOkKvCuhuTzQAMmG8aYFt9S0p1K20eCCgWvJ5vu3ir875yBrtVPl2VzdFdo7Wv3kg1HOV+Sy7dQ2bIJ52mV8CnHI1W+ZMEjzQ64m75wH/AGsVb35E0sPJzFNCGj//8/kyKxRR1I0DSDOb+iE48twOrBRrUF5+ApwocqVdIa//Cbe1ArjzrEhwaKY0SitPcFwbVV8XadtsHXfdM5QnFwTsNobk2w+XLt9I5yL/SdE1NVVXBsAN1nejzDo8XTheD6o/m5O29WO3MSS7jt1PCYItVjN4ONK/Ztaa+zQcNK9itMy2tEJ1R/gI+AipOQi0JaHHAjcdYKxDbbJpurJAHvtLvKiJNqNUJPGpqCSfL8YqmDwf3Gs1SntRjgZNeOpAdiHl2qUewcB2vujROmLTQgxJ2HJTK8hKr+2nkZdEMkYYQ/wDtsGYohokU1GOGTjdr5d2vXW8MAWaF5UQDXQzPCT4RGjDLfvod4SM+GHn8t2eDJH8uHvUPU6AXcohM30zw/h9FPf18q7Oo0srwFpc0qjvwDxl9lgilsfaL23K2V5YFeTkO1llxnRdsTmSZ7UMsugBFu5bjGEL4hC/Sml0oH9F8hiV50fXWetsQvNB637Q== Thorsten "mirabile" Glaser <tg@MirBSD.org> SIGN' >$T/signkey
tempdir=$T; export tempdir

# Check for Interix
if test $isinterix = yes; then
	# We know /bin/ksh is sufficient
	# Check for nroff
	test -f /usr/bin/nroff || \
	    OVERRIDE_MKSH=/bin/ksh SHELL=/bin/ksh MKSH=/bin/ksh \
	    /bin/ksh $ourpath/infrastructure/install/setup.ksh -i "$@"
	if test ! -f /usr/bin/nroff; then
		echo Cannot install nroff >&2
		exit 1
	fi
fi

# Look if this is a sufficient mksh, search for one
ms=false
for s in /bin/mksh $MKSH $SHELL; do
	# This is from MirMake; it ensures mksh R24 or higher
	t=`$s -c 'let a=1; (( a + 1 )) 2>/dev/null && if [[ $KSH_VERSION = @(\@\(#\)MIRBSD KSH R)@(2[4-9]|[3-9][0-9]|[1-9][0-9][0-9])\ +([0-9])/+([0-9])/+([0-9]) ]]; then echo yes; else echo no; fi' 2>/dev/null`
	if test x"$t" = x"yes"; then
		ms=$s
		break
	fi
done

# If suitable mksh found, retrieve its version number
if test x"$ms" != x"false"; then
	old=no
#	t=`$ms -c 'x=${KSH_VERSION#*KSH?R}; print ${x%% *}'`
#	# first check version, then date
#	test $t -lt $mksh_ver && old=yes
	# check if date matches
	t=`$ms -c 'print ${KSH_VERSION#*KSH?R}'`
	test x"$t" != x"$mksh_date" && old=yes

	# If old, check if we can upgrade
	test $old = yes && if test x"$UPGRADE" != x"no"; then
		# But use it as build shell
		SHELL=$ms
		# Fake no suitable mksh found
		ms=false
	fi
fi

# If no suitable mksh found, or too old, build one,
# else jump to the "real" set-up script
if test x"$ms" != x"false"; then
	SHELL=$ms; export SHELL
	MKSH=$ms; export MKSH
	case $# in
	0)	exec $ms $ourpath/infrastructure/install/setup.ksh ;;
	*)	exec $ms $ourpath/infrastructure/install/setup.ksh "$@" ;;
	esac
	echo Warning: executing old mksh failed >&2
fi

MKSH=${MKSH:-/bin/mksh}; export MKSH
# Check permissions
rm -rf $MKSH.$$.1
badp=0
if test -d $MKSH.$$.1; then
	badp=1
else
	mkdir $MKSH.$$.1 2>/dev/null
	test -d $MKSH.$$.1 || badp=1
	rmdir $MKSH.$$.1 2>/dev/null
	test -d $MKSH.$$.1 && badp=1
	(echo test >$MKSH.$$.1) 2>/dev/null
	test -r $MKSH.$$.1 || badp=1
fi
rm -f $MKSH.$$.1
if test $badp = 1; then
	echo 'You need superuser privilegues to continue installation.' >&2
	echo 'Ask your system operator to install a recent mksh (R24b)' >&2
	cd
	rm -rf $T
	exit 1
fi

# Download mksh
what=mksh
#%%BEGIN ^K. sync Setup.sh with setup.ksh %% getfile
. $ourpath/infrastructure/install/distinfo.sh
cd $ourpath/Distfiles
test -r $f_dist || case "$mirror" in
/*)	# file
	test -r $mirror/$f_path && cp $mirror/$f_path .
	test -r $mirror/$f_dist && cp $mirror/$f_dist .
	;;
*)	# http
	$fetch $mirror$f_path
	;;
esac
sum=unchecked
if s=`md5 $f_dist 2>/dev/null`; then
	if test x"$s" = x"$f_md5"; then
		sum=good
	else
		sum=bad
	fi
fi
test $sum = bad || if s=`cksum $f_dist 2>/dev/null`; then
	if test x"$s" = x"$f_sum"; then
		sum=good
	else
		sum=bad
	fi
fi
test $sum = bad || if s=`md5sum $f_dist 2>/dev/null`; then
	if test x"$s" = x"$f_md5sum"; then
		sum=good
	else
		sum=bad
	fi
fi
test $sum = bad || if gzsig verify -q $T/signkey $f_dist 2>/dev/null; then
	echo Note: cryptographically strong checksum verified successfully for $f_dist >&2
	sum=verygood
fi
if test $sum = unchecked; then
	echo Warning: Cannot check hashes for $f_dist >&2
	echo Please compare the following two lines manually >&2
	echo "$f_lsline" >&2
	echo ": `TZ=UTC /bin/ls -l $f_dist`" >&2
	echo Press RETURN to continue or abort if unsure. >&2
	read s
fi

if test $sum = bad; then
	echo Checksum verification failed >&2
	echo "false: $s" >&2
	cd
	rm -rf $T
	exit 1
fi

# Extract the distfile
if gzip -dc $f_dist | (cd $T && cpio -id); then
	:
else
	echo Build failed >&2
	cd
	rm -rf $T
	exit 1
fi
#%%END sync Setup.sh with setup.ksh %% getfile

# Build mksh
cd $T/mksh
SHELL=${SHELL:-/bin/sh}; export SHELL
if test -f /usr/lib/libc.dylib; then
	# Darwin
	d=-d
else
	d=
fi
$SHELL ./Build.sh $d || rm -f mksh
if test ! -s mksh; then
	echo Build failed >&2
	cd
	rm -rf $T
	exit 1
fi

# Install mksh
set -e
install -c -s -m 555 mksh $MKSH.$$.1
mv $MKSH $MKSH.$$.2 && mv $MKSH.$$.1 $MKSH
set +e
rm -f $MKSH.$$.2
test -f $MKSH.$$.2 && if mv $MKSH.$$.2 /tmp/deleteme.$$.$RANDOM; then
	echo Do not forget to clean up /tmp/deleteme.$$.\* >&2
else
	echo Warning: remove $MKSH.$$.2 later >&2
fi

# Install some kind of man page
s=0
if test -s mksh.cat1; then
	install -c -m 444 mksh.cat1 /usr/share/man/cat1/mksh.0 && s=1
fi
test $s = 0 && install -c -m 444 mksh.1 /usr/share/man/man1/mksh.1

# Clean up
cd $T
rm -rf mksh

# Jump into final script
SHELL=$MKSH; export SHELL
case $# in
0)	exec $MKSH $ourpath/infrastructure/install/setup.ksh ;;
*)	exec $MKSH $ourpath/infrastructure/install/setup.ksh "$@" ;;
esac

# This line is never run
echo Could not call mksh on setup.ksh >&2
cd /
rm -rf $T
exit 2
