# $MirOS: src/distrib/common/dot.profile,v 1.2 2006/08/18 20:48:46 tg Exp $
# $OpenBSD: dot.profile,v 1.4 2002/09/13 21:38:47 deraadt Exp $
# $NetBSD: dot.profile,v 1.1 1995/12/18 22:54:43 pk Exp $
#
# Copyright (c) 2003, 2004, 2005, 2006
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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

sshd() {
	if [[ ! -f /etc/ssh/ssh_host_rsa_key ]]; then
		echo -n "ssh-keygen: generating new RSA host key... "
		if /usr/bin/ssh-keygen -q -t rsa \
		    -f /etc/ssh/ssh_host_rsa_key -N ''; then
			echo done.
		  else
			echo failed.
			rm -f /etc/ssh/ssh_host_rsa_key
		fi
	fi
	if [[ -f /etc/ssh/ssh_host_rsa_key ]]; then
		/usr/bin/ssh-keygen -l -f /etc/ssh/ssh_host_rsa_key
		/usr/sbin/sshd "$@"
	fi
}

export PATH=/sbin:/bin:/usr/bin:/usr/sbin:/
umask 022

alias ls='/bin/ls -F'
alias la='ls -a '
alias l=la
alias ll='l -l '
alias lo='ll -o '

rootdisk=$(sysctl -n kern.root_device)
rootdisk=/dev/${rootdisk:-rd0a}

if [ ! -f /.profile.done ]; then
	# first of all, we need a /tmp - use all memory minus 4 MiB
	mount_mfs -s $(($(sysctl -n hw.usermem)/512-8192)) swap /tmp

	# on sparc, use the nvram to provide some additional entropy
	[ -x /usr/sbin/eeprom ] && eeprom 2>&1 | cksum -ba sha512 >/dev/prandom
	# basic HD randomness reads (doesn't matter if they break)
	( ( (dd if=/dev/rwd0c count=126; dd if=/dev/rsd0c count=126; dd \
	    if=/var/db/host.random) 2>&1 | cksum -ba sha512 >/dev/arandom) &)

	# say hello and legalese
	echo '
Welcome to MirOS #9-stable!
This is the old installer, expect it to be replaced really soon.

Welcome to the MirOS BSD operating system installer.  This work is
licenced open source software; for further information please read
the information at http://mirbsd.de/ and its mirrors.  After setup
the files in /usr/share/doc/legal/ contain additional licences and
other terms used by MirOS or its contributed material.
This work is provided "AS IS" and WITHOUT WARRANTY of any kind.\n'

	mount -u $rootdisk / || mount -fuw /dev/rd0a /
	rm -f /var/db/host.random

	# set up some sane defaults
	echo 'erase ^?, werase ^W, kill ^U, intr ^C, status ^T'
	stty newcrt werase ^W intr ^C kill ^U erase ^? status ^T

	# look if we're DHCP/TFTP enabled
	if [ -e /usr/mdec/pxeboot ]; then
		mkdir /tmp/tftpboot
		cp /usr/mdec/pxeboot /tmp/tftpboot/
	fi

	# don't run this twice
	echo -n >/.profile.done

	# spawn a second shell if desired
	[[ -e /dev/ttyC1 ]] && mksh -lT1 >/dev/null 2>&1

	# Installing or upgrading?
	_forceloop=
	while [[ -z $_forceloop ]]; do
		echo -n '(I)nstall'
		[ -f upgrade ] && echo -n ', (U)pgrade'
		echo -n ' or (S)hell? '
		read _forceloop
		case $_forceloop {
		[Ii]*)	/install
			;;
		[Uu]*)	/upgrade
			;;
		[Ss]*)	;;
		*)	_forceloop=
			;;
		}
	done
fi
export TERM=vt220
echo -n '\nAvailable editor: ed'
[ -s /ed.hlp ] && echo -n ' - help with # less /ed.hlp'
echo '\n'
