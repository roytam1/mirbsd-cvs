#!/bin/mksh
# $MirOS: ports/infrastructure/install/mkuserdb.ksh,v 1.3 2005/12/04 13:57:55 tg Exp $
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
# Updates $path/etc/master.passwd and $path/etc/group from userlist.
# If $2 == -n, *don't* call pwd_mkdb(8) after that.

cd "$(dirname "$0")"/../templates
fflag=0		# Write ftpusers and aliases too
nflag=0		# Don't call pwd_mkdb(8)
while getopts "fhn" option; do
	case $option {
	f)	fflag=1 ;;
	n)	nflag=1 ;;
	*)	print -u2 "Syntax: $0 [-fn] [/chroot]"
		exit 1 ;;
	}
done
shift $((OPTIND - 1))

G_CHANGED=0
P_CHANGED=0
while read uid uname gecos; do
	[[ $uid = @(#)* ]] && continue
	LINE="${uname}:*:${uid}:"
	if ! egrep '^[^:]*:[^:]*:'$uid':' $1/etc/group >/dev/null 2>&1; then
		[[ $gecos = @(NO,)* ]] && LINE="${LINE}${gecos#NO,}"
		if [[ $gecos != @(!)* ]]; then
			print -r -- "${LINE}" >>$1/etc/group
			G_CHANGED=1
		fi
	fi
	[[ $gecos = @(NO|NO,*) ]] && continue
	[[ $gecos = @(!)* ]] && MYLINE="${LINE}${gecos#!}"
	[[ $uid = 0 ]] && MYLINE="root::${MYLINE#@(root:*:)}"
	gecos="MirPorts -- $(print -r -- "$gecos" | sed s/:/!ERROR!/g)"
	if (( uid < 256 || uid > 999 )); then
		# system user, not MirPorts
		gecos=${gecos#@(MirPorts -- )}
		if [[ $uname = @(popa3d|sshd|_*) ]]; then
			hsf="/var/empty:/sbin/nologin"
		elif [[ $uname = www ]]; then
			hsf="/var/www:/sbin/nologin"
		else
			hsf="/nonexistent:/sbin/nologin"
		fi
	else
		hsf="/nonexistent:/sbin/nologin"
	fi
	if ! egrep '^[^:]*:[^:]*:'$uid':' $1/etc/master.passwd \
	    >/dev/null 2>&1; then
		P_CHANGED=1
		LINE="${LINE}${uid}::0:0:${gecos}:${hsf}"
		[[ $gecos = @(!)* ]] && LINE="$MYLINE"
		print -r -- "${LINE}" >>$1/etc/master.passwd
	fi
done <userlist.db
[[ $G_CHANGED = 1 ]] && sort -t: -nk3 -o $1/etc/group $1/etc/group
[[ $P_CHANGED = 0 && $fflag = 0 ]] && exit 0
sort -t: -nk3 -o $1/etc/master.passwd $1/etc/master.passwd
if [[ $fflag = 1 ]]; then
	{
		print '# $MirOS: ports/infrastructure/install/mkuserdb.ksh,v 1.3 2005/12/04 13:57:55 tg Exp $'
		print '#'
		print '# Users who are not allowed to use ftp access; read by ftpd(8)'
		print
		sed -e 's/:.*$//' <$1/etc/master.passwd
	} >$1/etc/ftpusers
	sed -e 's/:.*$//' <$1/etc/master.passwd | while read user; do
		[[ $user = root ]] && continue
		x=/dev/null
		[[ $user = @(daemon|operator|uucp|www) ]] && x=root
		LINE="${user}:"
		(( ${#LINE} < 8 )) && LINE="$LINE	"
		LINE="$LINE	$x"
		print "$LINE"
	done >$1/etc/aliases.xxx
fi
[[ $nflag = 1 ]] || pwd_mkdb -p -d $1/etc master.passwd
