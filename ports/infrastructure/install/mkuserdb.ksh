#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $
#-
# Copyright (c) 2004, 2005, 2007
#	Thorsten Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
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
		print '# $MirOS: ports/infrastructure/install/mkuserdb.ksh,v 1.4 2005/12/17 05:46:18 tg Exp $'
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
