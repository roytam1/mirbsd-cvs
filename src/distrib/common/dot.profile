# $MirOS: src/distrib/common/dot.profile,v 1.33 2008/10/20 19:29:20 tg Exp $
# $OpenBSD: dot.profile,v 1.4 2002/09/13 21:38:47 deraadt Exp $
# $NetBSD: dot.profile,v 1.1 1995/12/18 22:54:43 pk Exp $
#
# Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008
#	Thorsten “mirabilos” Glaser <tg@66h.42h.de>
# Copyright (c) 1995 Jason R. Thorpe
# Copyright (c) 1994 Christopher G. Demetriou
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#	This product includes software developed by Christopher G. Demetriou.
# 4. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

export HOME=/ LC_CTYPE=en_US.UTF-8 PATH=/sbin:/bin:/usr/sbin:/usr/bin:/ \
    PS1='$PWD # '
umask 022
cd /
ulimit -c 0

_getrnd() {
	(ulimit -T 60; exec ftp -mvo /dev/arandom \
	    https://call.mirbsd.org/rn.cgi?bsdrdskg,$(dd \
	    if=/dev/arandom bs=57 count=1 | \
	    b64encode -r - | tr '+=/' '._-')) >/dev/wrandom 2>&1
}

sshd() {
	if grep -q '^root:x:' /etc/master.passwd 2>/dev/null; then
		print -u2 error: you must passwd root first
		return 1
	fi
	if [[ ! -f /etc/ssh/ssh_host_rsa_key ]]; then
		_getrnd
		print -n "ssh-keygen: generating new RSA host key... "
		sleep 3
		if ssh-keygen -qt rsa -f /etc/ssh/ssh_host_rsa_key -N ''; then
			print done.
		else
			print failed.
			rm -f /etc/ssh/ssh_host_rsa_key
		fi
	fi
	if [[ -f /etc/ssh/ssh_host_rsa_key ]]; then
		ssh-keygen -lf /etc/ssh/ssh_host_rsa_key
		/usr/sbin/sshd "$@"
	fi
}

if [[ -z $NEED_UNICODE ]]; then
	chkuterm; export NEED_UNICODE=$?	# 0 = UTF-8; >0 = ISO-8859-1
	(( NEED_UNICODE )) && exec script -lns	# no typescript, login shell
fi
unset NEED_UNICODE

alias l='/bin/ls -F'
alias la='l -a'
alias ll='l -l'
alias lo='la -lo'

rootdisk=$(sysctl -n kern.root_device)
rootdisk=/dev/${rootdisk:-rd0a}

if [ ! -f /.profile.done ]; then
	# first of all, we need a /tmp - use all memory minus 4 MiB
	integer avmem="$(sysctl -n hw.usermem) / 512"
	(( avmem < 8200 )) || mount_mfs -s $((avmem - 8192)) swap /tmp
	unset avmem

	# on sparc, use the nvram to provide some additional entropy
	# also read some stuff from the HDD etc. (doesn't matter if it breaks)
	[[ -x /usr/libexec/cprng ]] && /usr/libexec/cprng -p
	( ( (for d in {w,s,rai,c}:128, r:1,128; do b=${d#*,}; d=${d%,*}; dd \
	     if=/dev/r${d%:*}d0c count=${d#*:} ${b:+bs=$b of=/dev/urandom}; \
	     done; eeprom; dmesg; sysctl -a) 2>&1 | cksum -backsum -asha512 \
	     -asuma -atiger -armd160 -aadler32 >/dev/wrandom) &)

	# say hello and legalese
	print '
Welcome to MirOS #10-current!

Welcome to the MirOS BSD operating system installer.  This work is
licenced open source software; for further information please read
the information at http://mirbsd.de/ and its mirrors.  After setup
the files in /usr/share/doc/legal/ contain additional licences and
other terms used by MirOS or its contributed material.
This work is provided "AS IS" and WITHOUT WARRANTY of any kind.\n'

	mount -u $rootdisk / || mount -fuw /dev/rd0a /

	# set up some sane defaults
	print 'erase ^?, werase ^W, kill ^U, intr ^C, status ^T'
	stty newcrt werase ^W intr ^C kill ^U erase ^? status ^T

	# Extract and save one boot's worth of dmesg
	dmesg | sed -ne '/^MirBSD /h;/^MirBSD /!H;${g;p;}' >/var/run/dmesg.boot

	# look if we're DHCP/TFTP enabled
	if [ -e /usr/mdec/pxeboot ]; then
		mkdir /tmp/tftpboot
		cp /usr/mdec/pxeboot /tmp/tftpboot/
	fi

	# don't run this twice
	print -n >/.profile.done

	# reset arandom(4) – in a subshell for arc4_stir_pid
	(typeset -i1 x=RANDOM; print -n "${x#1#}" >/dev/arandom)

	# try to spawn a second shell
	mksh -lT1 >/dev/null 2>&1

	# Installing or upgrading?
	_forceloop=
	while [[ -z $_forceloop ]]; do
		print -n '(I)nstall'
		[ -f upgrade ] && print -n ', (U)pgrade'
		print -n ' or (S)hell? '
		read _forceloop
		case $_forceloop {
		([Ii]*)	/install ;;
		([Uu]*)	/upgrade ;;
		([Ss]*)	;;
		(*)	_forceloop= ;;
		}
	done
else
	stty newcrt werase ^W intr ^C kill ^U erase ^? status ^T
fi
export TERM=vt220
print -n '\nAvailable editor: ed'
[ -s /ed.hlp ] && print -n ' - help with # less /ed.hlp'
print '\n'
