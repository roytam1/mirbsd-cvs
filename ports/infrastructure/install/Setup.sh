#!/bin/sh
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
# This script installs mksh if needed, then calls setup.ksh with it.
# On Interix, nroff is also installed first.

# Constants
#mksh_ver=24 # unused
mksh_date="24 2005/08/21"
mksh_dist=mksh-R24b.cpio.gz
mksh_path=mir/mksh/$mksh_dist
mksh_md5="MD5 ($mksh_dist) = 48d0df73eba1ef4e9c0758f69262eb66"
mksh_sum="240923212 224290 $mksh_dist"
mksh_md5sum="48d0df73eba1ef4e9c0758f69262eb66  $mksh_dist"
mirror="${1:-http://mirbsd.mirsolutions.de/MirOS/dist/}"

# Divine a fetching utility
fetch=false
if [ -n "$SFUDIR" -o -n "$OPENNT_ROOT" ]; then
	# Interix: check for Weihenstephan wget
	if [ -x /dev/fs/C/usr/local/wbin/wget.exe ]; then
		fetch="runwin32 c:/usr/local/wbin/wget.exe"
	fi
fi
if [ "$fetch" = false ]; then
	# Check for ftp/wget/fetch
	for dir in /usr/mpkg/bin /usr/local/bin /bin /usr/bin; do
		if [ -x $dir/wget ]; then
			fetch=$dir/wget
			break
		fi
		if [ -x $dir/fetch ]; then
			fetch=$dir/fetch
			break
		fi
		if [ -x $dir/ftp ]; then
			fetch=$dir/ftp
			break
		fi
	fi
fi
export fetch mirror

# Check for Interix
if [ -n "$SFUDIR" -o -n "$OPENNT_ROOT" ]; then
	# We know /bin/ksh is sufficient
	# Check for nroff
	if [ ! -x /usr/bin/nroff ]; then
		set -e
		OVERRIDE_MKSH=/bin/ksh SHELL=/bin/ksh \
		    /bin/ksh `dirname $0`/setup.ksh -i
		set +e
	fi
fi

# Look if this is a sufficient mksh, search for one
ms=false
for s in $SHELL /bin/mksh; do
	# This is from MirMake; it ensures mksh R24 or higher
	t="`$s -c 'let a=1; (( a + 1 )) 2>/dev/null && if [[ $KSH_VERSION = @(\@\(#\)MIRBSD KSH R)@(2[4-9]|[3-9][0-9]|[1-9][0-9][0-9])\ +([0-9])/+([0-9])/+([0-9]) ]]; then echo yes; else echo no; fi' 2>/dev/null`"
	if [ x"$t" = x"yes" ]; then
		ms=$s
		break
	fi
done

# If suitable mksh found, retrieve its version number
if [ x"$ms" != x"false" ]; then
	old=no
#	t="`$ms -c 'x=${KSH_VERSION#*KSH?R}; print ${x%% *}'`"
#	# first check version, then date
#	if [ $t -lt $mksh_ver ]; then
#		old=yes
#	fi
	# check if date matches
	t="`$ms -c 'print ${KSH_VERSION#*KSH?R}'`"
	if [ x"$t" != x"$mksh_date" ]; then
		old=yes
	fi
	# If old, check if we can upgrade
	if [ $old = yes -a x"$UPGRADE" != "no" ]; then
		# But use it as build shell
		SHELL="$ms"
		# Fake no suitable mksh found
		ms=false
	fi
fi

# If no suitable mksh found, or too old, build one,
# else jump to the "real" set-up script
if [ x"$ms" != x"false" ]; then
	SHELL="$ms"; export SHELL
	exec $ms `dirname $0`/setup.ksh
	echo Warning: executing old mksh failed! >&2
fi

# Divine a temporary directory
if ! T=$(mktemp -d /tmp/mirports.XXXXXXXXXX); then
	# May be Interix without mktemp.sh
	T=/tmp/mirports.$$
	if [ -d $T ]; then
		echo Cannot generate temporary directory! >&2
		exit 1
	fi
	if ! mkdir -p $T; then
		echo Cannot generate temporary directory! >&2
		exit 1
	fi
fi

# Download mksh
cd $T
case "$mirror" in
/*)	# file
	cp $mirror/$mksh_path .
	;;
*)	# http
	$fetch $mirror$mksh_path
	;;
esac
sum=good
echo 'ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAoEAy5akQiuw0znRhMD0djgQ7BiUPahG1QHJb9ZNApd6D5OnV98FO8Ofbfm4CF1Cvwr+IPnyKyPglQnaFgHF3LVynKMYSupKXnd0JrBR79TBmIVImBnIaTPcApRdWZEbMW5IdYhrWFHKlzk4vDxBXdcVE6QfiemWsYqkiuoJvLTLHXq7WUCQ5z7KuQetMnnP2bswV8SZuYy0IvzQRBVJbiTQzBvsHfyZUERLBZvjtPE9jTaLdTOkKvCuhuTzQAMmG8aYFt9S0p1K20eCCgWvJ5vu3ir875yBrtVPl2VzdFdo7Wv3kg1HOV+Sy7dQ2bIJ52mV8CnHI1W+ZMEjzQ64m75wH/AGsVb35E0sPJzFNCGj//8/kyKxRR1I0DSDOb+iE48twOrBRrUF5+ApwocqVdIa//Cbe1ArjzrEhwaKY0SitPcFwbVV8XadtsHXfdM5QnFwTsNobk2w+XLt9I5yL/SdE1NVVXBsAN1nejzDo8XTheD6o/m5O29WO3MSS7jt1PCYItVjN4ONK/Ztaa+zQcNK9itMy2tEJ1R/gI+AipOQi0JaHHAjcdYKxDbbJpurJAHvtLvKiJNqNUJPGpqCSfL8YqmDwf3Gs1SntRjgZNeOpAdiHl2qUewcB2vujROmLTQgxJ2HJTK8hKr+2nkZdEMkYYQ/wDtsGYohokU1GOGTjdr5d2vXW8MAWaF5UQDXQzPCT4RGjDLfvod4SM+GHn8t2eDJH8uHvUPU6AXcohM30zw/h9FPf18q7Oo0srwFpc0qjvwDxl9lgilsfaL23K2V5YFeTkO1llxnRdsTmSZ7UMsugBFu5bjGEL4hC/Sml0oH9F8hiV50fXWetsQvNB637Q==' >key
if gzsig -q verify key $mksh_dist 2>/dev/null; then
	:
elif s="`md5 $mksh_dist 2>/dev/null`"; then
	[ x"$s" = x"$mksh_md5" ] || sum=bad
elif s="`cksum $mksh_dist 2>/dev/null`"; then
	[ x"$s" = x"$mksh_sum" ] || sum=bad
elif s="`md5sum $mksh_dist 2>/dev/null`"; then
	[ x"$s" = x"$mksh_md5sum" ] || sum=bad
else
	echo Warning: Cannot check sum of $mksh_dist >&2
	echo Please compare the following two lines manually! >&2
	echo ': -r--r--r--  1 tg  miros-cvsall  224290 Aug 21 13:08 mksh-R24b.cpio.gz' >&2
	echo ": `/bin/ls -l $mksh_dist`" >&2
	echo Press RETURN to continue! >&2
	read s
fi

if [ $sum = bad ]; then
	echo Checksum verification failed! >&2
	echo "false: $s" >&2
	cd
	rm -rf $T
	exit 1
fi

# Extract and build mksh
if ! gzip -dc $mksh_dist | cpio -id; then
	echo Build failed! >&2
	cd
	rm -rf $T
	exit 1
fi

cd mksh
if ! SHELL="${SHELL:-/bin/sh}" ${SHELL:-/bin/sh} ./Build.sh; then
	if ! SHELL="${SHELL:-/bin/sh}" ${SHELL:-/bin/sh} ./Build.sh -d -r; then
		echo Build failed! >&2
		cd
		rm -rf $T
		exit 1
	fi
fi

if [ ! -x mksh ]; then
	echo Build failed! >&2
	cd
	rm -rf $T
	exit 1
fi

# Install mksh
set -e
rm -f /bin/mksh.$$.1
install -c -s -m 555 mksh /bin/mksh.$$.1
mv /bin/mksh /bin/mksh.$$.2 && mv /bin/mksh.$$.1 /bin/mksh
set +e
if ! rm /bin/mksh.$$.2; then
	if ! mv /bin/mksh.$$.2 /tmp/deleteme.$$; then
		echo Warning: remove /bin/mksh.$$.2 later! >&2
	else
		echo Don't forget to clean up /tmp/deleteme.$$ >&2
	fi
fi

# Install some kind of man page
s=0
if [ -s mksh.cat1 ]; then
	install -c -m 444 mksh.cat1 /usr/share/man/cat1/mksh.0 \
	    && s=1
fi
if [ $s = 0 ]; then
	install -c -m 444 mksh.1 /usr/share/man/man1/mksh.1
fi

# Clean up
cd
rm -rf $T

# Jump into final script
SHELL=/bin/mksh; export SHELL
SHELL=/bin/mksh exec /bin/mksh `dirname $0`/setup.ksh

# This line is never run
echo Could not call mksh on setup.ksh >&2
exit 2
