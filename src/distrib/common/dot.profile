# $MirOS: src/distrib/common/dot.profile,v 1.62 2013/09/28 19:55:15 tg Exp $
# $OpenBSD: dot.profile,v 1.4 2002/09/13 21:38:47 deraadt Exp $
# $NetBSD: dot.profile,v 1.1 1995/12/18 22:54:43 pk Exp $
#
# Copyright (c) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2013
#	mirabilos <m@mirbsd.org>
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

export HOME=/ LC_CTYPE=en_US.UTF-8 PATH=/sbin:/bin:/usr/sbin:/usr/bin:/ PS1='$PWD # '
umask 022
cd /
ulimit -c 0

if [[ -z $NEED_UNICODE ]]; then
	# 0 = UTF-8; >0 = ISO-8859-1
	chkuterm; export NEED_UNICODE=$?
	# no typescript, login shell
	(( NEED_UNICODE )) && exec script -lns
fi
unset NEED_UNICODE

. /etc/functions
sshd() {
	if grep -q '^root:x:' /etc/master.passwd 2>/dev/null; then
		echo error: you must passwd root first
		return 1
	fi
	if [[ ! -f /etc/ssh/ssh_host_rsa_key ]]; then
		_getrnd skg
		print -n "ssh-keygen: generating new RSA host key... "
		sleep 3
		if ssh-keygen -qt rsa -f /etc/ssh/ssh_host_rsa_key -N ''; then
			echo done.
		else
			echo failed.
			rm -f /etc/ssh/ssh_host_rsa_key
		fi
	fi
	if [[ -f /etc/ssh/ssh_host_rsa_key ]]; then
		ssh-keygen -lf /etc/ssh/ssh_host_rsa_key
		/usr/sbin/sshd "$@"
	fi
}

do_netcfg() {
	local bpf=0 cwd=$(pwd) nic pwhash rootpw='miros'
	: this is extra space to facilitate easy editing of the ISO
	echo Setting up the loopback interface
	ifconfig lo0 inet 127.0.0.1 up
	sysctl -w net.inet6.ip6.accept_rtadv=1
	cd /dev
	for nic in $(ifconfig -l); do
		[[ $nic = @(lo|plip)+([0-9]) ]] && continue
		echo Setting up interface $nic
		ifconfig $nic up
		(rtsol $nic 2>&1 &) 2>/dev/null
		mksh MAKEDEV bpf$((bpf++))
		dhclient $nic
	done
	cd "$cwd"
	echo Configuring the ssh daemon
	pwhash=$(encrypt -b 8 -- "$rootpw")
	print "/^root/s^root:[^:]*:root:${pwhash}:\nwq" | ed -s /etc/master.passwd
	pwd_mkdb -p /etc/master.passwd
	sshd
	echo "All done, you can log in now (root/$rootpw)"
}

alias l='/bin/ls -F'
alias la='l -a'
alias ll='l -l'
alias lo='la -lo'

rootdisk=$(sysctl -n kern.root_device)
rootdisk=/dev/${rootdisk:-rd0a}

if [[ ! -f /.profile.done ]]; then
	# first of all, we need a /tmp - use all memory minus 4 MiB
	integer avmem=$(sysctl -n hw.usermem)
	(( avmem = avmem > 321634304 ? 620000 : avmem / 512 - 8192 ))
	(( avmem < 144 )) || mount_mfs -s $avmem swap /tmp
	unset avmem

	# on sparc, use the nvram to provide some additional entropy
	# also read some stuff from the HDD etc. (doesn't matter if it breaks)
	[[ -x /usr/libexec/tpmrng ]] && /usr/libexec/tpmrng
	( ( (for d in {w,s,rai,c}:128, r:1,32; do b=${d#*,}; d=${d%,*}; dd \
	    if=/dev/r${d%:*}d0c count=${d#*:} ${b:+bs=$b of=/dev/urandom}; \
	    done; eeprom; dmesg; sysctl -a) 2>&1 | cksum -backsum -asha512 \
	    -asuma -atiger -armd160 -aadler32 >/dev/wrandom) &)

	# say hello and legalese
	echo '
Welcome to MirOS #10-current!

Welcome to the MirOS BSD operating system installer.  This work is
licenced open source software; for further information please read
the information at http://mirbsd.de/ and its mirrors.  After setup
the files in /usr/share/doc/legal/ contain additional licences and
other terms used by MirOS or its contributed material.
This work is provided "AS IS" and WITHOUT WARRANTY of any kind.
'

	mount -u $rootdisk / || mount -fuw /dev/rd0a /

	# set up some sane defaults
	echo 'erase ^?, werase ^W, kill ^U, intr ^C, status ^T'
	stty newcrt werase ^W intr ^C kill ^U erase ^? status ^T

	# Extract and save one boot's worth of dmesg
	dmesg | sed -ne '/^MirBSD/h;/^MirBSD/!H;${g;p;}' >/var/run/dmesg.boot

	# Now we can try to access an eKey if there is one
	[[ -x /usr/libexec/ekeyrng ]] && /usr/libexec/ekeyrng

	# Enable mouse, if any, for extra possible entropy and copy/paste
	[[ -x /usr/sbin/wsmoused ]] && /usr/sbin/wsmoused

	# look if we're DHCP/TFTP enabled
	if [[ -e /usr/libexec/tftpd ]]; then
		mkdir /tmp/tftpboot
		cp /usr/mdec/boot /tmp/tftpboot/
	fi

	# reset arandom(4)
	typeset -i1 x=RANDOM; print -n "${x#1#}" >/dev/arandom

	# try to spawn a second shell
	mksh -lT1 >/dev/null 2>&1

	# don't run this twice
	:>/.profile.done

	# Installing or upgrading?
	_forceloop=
	while [[ $_forceloop != [IiUuSsN]* ]]; do
		print -n '(I)nstall'
		[[ -f /upgrade ]] && print -n ', (U)pgrade'
		print -n ' or (S)hell? '
		read _forceloop
		case $_forceloop {
		([Ii]*)	/install ;;
		([Uu]*)	/upgrade ;;
		}
	done
	[[ $_forceloop = N ]] && do_netcfg
	unset _forceloop
else
	stty newcrt werase ^W intr ^C kill ^U erase ^? status ^T
fi
RANDOM=$(dd if=/dev/arandom count=1 bs=4 2>/dev/null | hexdump -e '1/4 "%u"')
export TERM=vt220 IRCUSER=MirBSD_s IRCNICK=MirOS_BSD-$RANDOM
print -n '\nAvailable editor: ed'
[ -x /usr/bin/vi ] && print -n ' (n)vi'
[ -x /usr/bin/e3 ] && print -n ' e3*'
[ -s /ed.hlp ] && print -n ' - help with # less /ed.hlp'
print '\nNetwork interfaces (e.g. for dhclient $if;passwd root;sshd):' $(ifconfig -l)
[ -x /usr/bin/tinyirc ] && echo 'Chat client: tinyirc'
echo
_vbox_check && echo Sorry, WirrtualBox is not supported.
