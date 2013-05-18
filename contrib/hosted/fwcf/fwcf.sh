#!/bin/sh
# $MirOS: contrib/hosted/fwcf/fwcf.sh,v 1.18 2007/02/20 21:06:02 tg Exp $
#-
# Copyright (c) 2006, 2007
#	Thorsten Glaser <tg@mirbsd.de>
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
# Possible return values:
# 0 - everything ok
# 1 - syntax error
# 1 - no 'fwcf' mtd partition found
# 1 - fwcf erase: failed
# 1 - fwcf setup: already run
# 3 - fwcf setup: mount --bind problems
# 4 - fwcf setup: can't create or write to temporary filesystem
# 5 - fwcf setup: can't bind the tmpfs to /etc
# 6 - fwcf commit: cannot write to mtd
# 7 - fwcf commit: won't write to flash because of unclean setup
# 8 - fwcf status: differences found
# 9 - fwcf status: old status file not found
# 255 - fwcf erase: failed
# 255 - internal error

export PATH=/bin:/sbin:/usr/bin:/usr/sbin

case $1 in
commit|erase|setup|status) ;;
*)	cat >&2 <<EOF
FreeWRT Configuration Filesytem (fwcf), Version 1.02
Copyright (c) 2006, 2007
	Thorsten Glaser <tg@freewrt.org>

Syntax:
	$0 [commit | erase | setup | status [-rq]]
EOF
	exit 1 ;;
esac

part=/dev/mtd/$(fgrep '"fwcf"' /proc/mtd 2>&- | sed 's/^mtd\([^:]*\):.*$/\1/')ro
if ! test -e "$part"; then
	echo 'fwcf: fatal error: no "fwcf" mtd partition found!' >&2
	exit 1
fi

if test $1 = erase; then
	fwcf.helper -Me | mtd -F write - fwcf
	exit $?
fi

if test $1 = setup; then
	if test -e /tmp/.fwcf; then
		echo 'fwcf: error: "fwcf setup" already run!' >&2
		exit 1
	fi
	mkdir /tmp/.fwcf
	if test ! -d /tmp/.fwcf; then
		echo 'fwcf: error: cannot create temporary directory!' >&2
		exit 4
	fi
	chown 0:0 /tmp/.fwcf
	chmod 700 /tmp/.fwcf
	mkdir /tmp/.fwcf/root
	mount --bind /etc /tmp/.fwcf/root
	mkdir /tmp/.fwcf/temp
	mount -t tmpfs fwcf /tmp/.fwcf/temp
	(cd /tmp/.fwcf/root; tar cf - .) | (cd /tmp/.fwcf/temp; tar xpf -)
	x=$(dd if="$part" bs=4 count=1 2>&-)
	test x"$x" = x"FWCF" || fwcf.helper -Me | mtd -F write - fwcf
	if ! fwcf.helper -U /tmp/.fwcf/temp <"$part"; then
		echo 'fwcf: error: cannot extract' >&2
		echo -n >/tmp/.fwcf/temp/.fwcf_unclean
		echo unclean startup | logger -t 'fwcf setup'
	fi
	if test -e /tmp/.fwcf/temp/.fwcf_deleted; then
		# this is safe even in ash (I hope)
		while IFS= read -r file; do
			rm -f "/tmp/.fwcf/temp/$file"
		done </tmp/.fwcf/temp/.fwcf_deleted
		rm -f /tmp/.fwcf/temp/.fwcf_deleted
	fi
	rm -f /tmp/.fwcf/temp/.fwcf_done
	if test -e /tmp/.fwcf/temp/.fwcf_done; then
		echo 'fwcf: fatal: this is not Kansas any more' >&2
		umount /tmp/.fwcf/temp
		umount /tmp/.fwcf/root
		rm -rf /tmp/.fwcf
		exit 3
	fi
	echo -n >/tmp/.fwcf/temp/.fwcf_done
	if test ! -e /tmp/.fwcf/temp/.fwcf_done; then
		echo 'fwcf: fatal: cannot write to tmpfs' >&2
		umount /tmp/.fwcf/temp
		umount /tmp/.fwcf/root
		rm -rf /tmp/.fwcf
		exit 4
	fi
	mount --bind /tmp/.fwcf/temp /etc
	if test ! -e /etc/.fwcf_done; then
		umount /etc
		echo 'fwcf: fatal: binding to /etc failed' >&2
		if test -e /tmp/.fwcf/temp/.fwcf_unclean; then
			umount /tmp/.fwcf/temp
		else
			echo 'fwcf: configuration is preserved' \
			    'in /tmp/.fwcf/temp' >&2
		fi
		exit 5
	fi
	umount /tmp/.fwcf/temp
	echo complete | logger -t 'fwcf setup'
	cd /etc
	find . -type f | grep -v -e '^./.fwcf' -e '^./.rnd$' | sort | \
	    xargs md5sum | sed 's!  ./! !' | gzip -9 >/tmp/.fwcf/status.gz
	exit 0
fi

if test $1 = commit; then
	umount /tmp/.fwcf/temp >&- 2>&-
	if test -e /etc/.fwcf_unclean; then
		cat >&2 <<-EOF
			fwcf: error: unclean startup!
			explanation: during boot, the FWCF filesystem could not
			    be extracted; saving the current /etc to flash will
			    result in data loss; to override this check, remove
			    the file /etc/.fwcf_unclean and try again.
		EOF
		exit 7
	fi
	mount -t tmpfs swap /tmp/.fwcf/temp
	(cd /etc; tar cf - .) | (cd /tmp/.fwcf/temp; tar xpf -)
	cd /tmp/.fwcf/temp
	find . -type f | grep -v -e '^./.fwcf' -e '^./.rnd$' | sort | \
	    xargs md5sum | sed 's!  ./! !' | gzip -9 >/tmp/.fwcf/status.gz
	cd /tmp/.fwcf/root
	rm -f /tmp/.fwcf/temp/.fwcf_deleted
	find . -type f | while read f; do
		f=${f#./}
		if ! test -e "/tmp/.fwcf/temp/$f"; then
			printf '%s\n' "$f" >>/tmp/.fwcf/temp/.fwcf_deleted
			continue
		fi
		x=$(md5sum "$f" 2>&-)
		y=$(cd ../temp; md5sum "$f" 2>&-)
		test x"$x" = x"$y" && rm "../temp/$f"
	done
	rv=0
	if ! ( fwcf.helper -M /tmp/.fwcf/temp | mtd -F write - fwcf ); then
		echo 'fwcf: error: cannot write to mtd!' >&2
		rv=6
	fi
	umount /tmp/.fwcf/temp
	exit $rv
fi

if test $1 = status; then
	rm -f /tmp/.fwcf/*_status /tmp/.fwcf/*_files
	rflag=0
	q=printf	# or : (true) if -q
	# XXX if we had mksh 'getopts' this would look nicer
	shift
	for arg in "$@"; do
		case $arg in
		-*r*)	rflag=1 ;;
		esac
		case $arg in
		-*q*)	q=: ;;
		esac
	done
	if test $rflag = 1; then
		f=/tmp/.fwcf/rom_status
		cd /tmp/.fwcf/root
		find . -type f | grep -v -e '^./.fwcf' -e '^./.rnd$' | sort | \
		    xargs md5sum | sed 's!  ./! !' >$f
	else
		f=/tmp/.fwcf/status
		gzip -d <$f.gz >$f || rm -f $f
	fi
	if ! test -e $f; then
		echo 'fwcf: error: old status file not found' >&2
		exit 9
	fi
	cd /etc
	find . -type f | grep -v -e '^./.fwcf' -e '^./.rnd$' | sort | \
	    xargs md5sum | sed 's!  ./! !' >/tmp/.fwcf/cur_status || exit 255
	cd /tmp/.fwcf
	sed 's/^[0-9a-f]* //' <$f >old_files
	sed 's/^[0-9a-f]* //' <cur_status >cur_files
	# make *_status be of exactly the same length, for benefit of the
	# while ... read <old, read <new loop below, and sort it
	comm -23 old_files cur_files | while read name; do
		echo "<NULL> $name" >>cur_status
	done
	comm -13 old_files cur_files | while read name; do
		echo "<NULL> $name" >>$f
	done
	# this implementation of sort -o sucks: doesn't do in-place edits
	sort -k2 -o sold_status $f
	sort -k2 -o snew_status cur_status
	gotany=0
	while :; do
		IFS=' ' read oldsum oldname <&3 || break
		IFS=' ' read newsum newname <&4 || exit 255
		test x"$oldname" = x"$newname" || exit 255
		test x"$oldsum" = x"$newsum" && continue
		test $gotany = 0 && $q '%32s %32s %s\n' \
		    'MD5 hash of old file' 'MD5 hash of new file' 'filename'
		gotany=8
		test $q = : && break
		$q '%32s %32s %s\n' "$oldsum" "$newsum" "$oldname"
	done 3<sold_status 4<snew_status
	rm -f /tmp/.fwcf/*_status /tmp/.fwcf/*_files
	exit $gotany
fi

echo 'fwcf: cannot be reached...' >&2
exit 255
