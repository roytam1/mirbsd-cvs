#!/bin/mksh
# $MirOS: src/distrib/common/install.sh,v 1.28 2013/09/11 18:55:55 tg Exp $
# $OpenBSD: install.sh,v 1.152 2005/04/21 21:41:33 krw Exp $
# $NetBSD: install.sh,v 1.5.2.8 1996/08/27 18:15:05 gwr Exp $
#
# Copyright © 2007, 2008, 2009, 2014
#	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
# Copyright (c) 1997-2004 Todd Miller, Theo de Raadt, Ken Westerback
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
#
# Copyright (c) 1996 The NetBSD Foundation, Inc.
# All rights reserved.
#
# This code is derived from software contributed to The NetBSD Foundation
# by Jason R. Thorpe.
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
#        This product includes software developed by the NetBSD
#        Foundation, Inc. and its contributors.
# 4. Neither the name of The NetBSD Foundation nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

#	OpenBSD installation script.
#	In a perfect world, this would be a nice C program, with a reasonable
#	user interface.

# The name of the file holding the list of configured filesystems.
FILESYSTEMS=/tmp/filesystems

# The name of the file holding the list of non-default configured swap devices.
SWAPLIST=/tmp/swaplist

# install.sub needs to know the MODE
MODE=install

# include common subroutines and initialization code
. install.sub

# If /etc/fstab already exists, skip disk initialization.
if [ ! -f /etc/fstab ]; then
	# Install the shadowed disktab file; lets us write to it for temporary
	# purposes without mounting the miniroot read-write.
	[ -f /etc/disktab.shadow ] && cp /etc/disktab.shadow /tmp/disktab.shadow

	DISK=
	_DKDEVS=$DKDEVS

	while :; do
		_DKDEVS=$(rmel "$DISK" $_DKDEVS)

		# Always do ROOTDISK first, and repeat until
		# it is configured acceptably.
		if isin $ROOTDISK $_DKDEVS; then
			resp=$ROOTDISK
			rm -f /tmp/fstab
			# Make sure empty files exist so we don't have to
			# keep checking for their existence before grep'ing.
			: >$FILESYSTEMS
			: >$SWAPLIST
		else
			# Force the user to think and type in a disk name by
			# making 'done' the default choice.
			ask_which "disk" "do you wish to initialise" "$_DKDEVS" done "No more disks to initialise"
			[[ $resp = done ]] && break
		fi

		DISK=$resp
		makedev $DISK || continue

		# Deal with disklabels, including editing the root disklabel
		# and labeling additional disks. This is machine-dependent since
		# some platforms may not be able to provide this functionality.
		# /tmp/fstab.$DISK is created here with 'disklabel -f'.
		rm -f /tmp/*.$DISK
		md_prep_disklabel $DISK

		# Get the lists of BSD and swap partitions.
		unset _partitions _psizes _mount_points
		_i=0
		disklabel $DISK 2>&1 | sed -ne '/^ *[a-p]: /p' >/tmp/disklabel.$DISK
		while read _dev _size _offset _type _rest; do
			_pp=${DISK}${_dev%:}
			_ps=$_size

			if [[ $_pp = $ROOTDEV ]]; then
				echo "$ROOTDEV /" >$FILESYSTEMS
				continue
			elif [[ $_pp = $SWAPDEV || $_type = swap ]]; then
				echo "$_pp" >>$SWAPLIST
				continue
			elif [[ $_type != *BSD ]]; then
				continue
			fi

			_partitions[$_i]=$_pp
			_psizes[$_i]=$_ps

			# Set _mount_points[$_i].
			if [[ -f /tmp/fstab.$DISK ]]; then
				while read _pp _mp _rest; do
					[[ $_pp = "/dev/${_partitions[$_i]}" ]] || continue
					# Ignore mount points that have already been specified.
					[[ -n $(grep " $_mp\$" $FILESYSTEMS) ]] && break
					isin $_mp ${_mount_points[*]} && break
					# Ignore '/' for any partition but ROOTDEV. Check just
					# in case ROOTDEV isn't first partition processed.
					[[ $_mp = '/' ]] && break
					# Otherwise, record user specified mount point.
					_mount_points[$_i]=$_mp
				done </tmp/fstab.$DISK
			fi
			let _i++
		done </tmp/disklabel.$DISK

		if [[ $DISK = $ROOTDISK && -z $(grep "^$ROOTDEV /$" $FILESYSTEMS) ]]; then
			echo "ERROR: No root partition ($ROOTDEV)."
			DISK=
			continue
		fi

		# If there are no BSD partitions go on to next disk.
		(( ${#_partitions[*]} > 0 )) || continue

		# Now prompt the user for the mount points.
		_i=0
		while :; do
			_pp=${_partitions[$_i]}
			_ps=$(( ${_psizes[$_i]} / 2 ))
			_mp=${_mount_points[$_i]}

			# Get the mount point from the user
			ask "Mount point for ${_pp} (size=${_ps}k)? (or 'none' or 'done')" "$_mp"
			case $resp in
			"")	;;
			none)	_mp=
				;;
			done)	break
				;;
			/*)	set -- $(grep " $resp\$" $FILESYSTEMS)
				_pp=$1
				if [[ -z $_pp ]]; then
					# Mount point wasn't specified on a
					# previous disk. Has it been specified
					# on this one?
					_j=0
					for _pp in ${_partitions[*]} ""; do
						if [[ $_i -ne $_j ]]; then
							[[ $resp = ${_mount_points[$_j]} ]] && break
						fi
						let _j++
					done
				fi
				if [[ -n $_pp ]]; then
					echo "Invalid response: $_pp is already being mounted at $resp."
					continue
				fi
				_mp=$resp
				;;
			*)	echo "Invalid response: mount point must be an absolute path!"
				continue
				;;
			esac

			_mount_points[$_i]=$_mp

			(( ++_i < ${#_partitions[*]} )) || _i=0
		done

		# Append mount information to $FILESYSTEMS
		_i=0
		for _pp in ${_partitions[*]}; do
			_mp=${_mount_points[$_i]}
			[ "$_mp" ] && echo "$_pp $_mp" >>$FILESYSTEMS
			let _i++
		done
	done

	cat <<__EOT

MirBSD filesystems:
$(<$FILESYSTEMS)

The next step *DESTROYS* all existing data on these partitions!
__EOT

	ask_yn "Are you really sure that you're ready to proceed?"
	[[ $resp = n ]] && { echo "Ok, try again later." ; exit ; }

	# Read $FILESYSTEMS, creating a new filesystem on each listed
	# partition and saving the partition and mount point information
	# for subsequent sorting by mount point.
	_i=0
	unset _partitions _mount_points
	while read _pp _mp; do
		_OPT=
		[[ $_mp = / ]] && _OPT=$MDROOTFSOPT
		newfs -q $_OPT /dev/r$_pp

		_partitions[$_i]=$_pp
		_mount_points[$_i]=$_mp
		let _i++
	done <$FILESYSTEMS

	# Write fstab entries to /tmp/fstab in mount point alphabetic
	# order to enforce a rational mount order.
	for _mp in $(bsort ${_mount_points[*]}); do
		_i=0
		for _pp in ${_partitions[*]}; do
			if [ "$_mp" = "${_mount_points[$_i]}" ]; then
				echo -n "/dev/$_pp $_mp ffs rw,softdep"
				# Only '/' is neither nodev nor nosuid. i.e.
				# it can obviously *always* contain devices or
				# setuid programs.
				#
				# Every other mounted filesystem is nodev. If
				# the user chooses to mount /dev as a separate
				# filesystem, then on the user's head be it.
				#
				# The only directories that install puts suid
				# binaries into (as of 3.2) are:
				#
				# /sbin
				# /usr/bin
				# /usr/sbin
				# /usr/libexec
				# /usr/libexec/auth
				# /usr/X11R6/bin
				#
				# and ports and users can do who knows what
				# to /usr/local and sub directories thereof.
				#
				# So try to ensure that only filesystems that
				# are mounted at or above these directories
				# can contain suid programs. In the case of
				# /usr/libexec, give blanket permission for
				# subdirectories.
				if [[ $_mp = / ]]; then
					# / can hold devices and suid programs.
					echo " 1 1"
				else
					# No devices anywhere but /.
					echo -n ",nodev"
					case $_mp in
					# A few directories are allowed suid.
					/sbin|/usr)			;;
					/usr/bin|/usr/sbin)		;;
					/usr/libexec|/usr/libexec/*)	;;
					/usr/local|/usr/local/*)	;;
					/usr/X11R6|/usr/X11R6/bin)	;;
					# But all others are not.
					*)	echo -n ",nosuid"	;;
					esac
					echo " 1 2"
				fi
			fi
			let _i++
		done
	done >>/tmp/fstab

	# Append all non-default swap devices to fstab.
	while read _dev; do
		[[ $_dev = $SWAPDEV ]] || \
			echo "/dev/$_dev none swap sw 0 0" >>/tmp/fstab
	done <$SWAPLIST

	munge_fstab
fi

mount_fs "-o async"

# Set hostname.
#
# Use existing hostname (short form) as the default value because we could
# be restarting an install.
#
# Don't ask for, but don't discard, domain information provided by the user.
#
# Only apply the new value if the new short form name differs from the existing
# one. This preserves any existing domain information in the hostname.
ask_until "\nSystem hostname? (short form, e.g. 'foo')" "$(hostname -s)"
[[ ${resp%%.*} != $(hostname -s) ]] && hostname $resp

# If the network is already running, preserve resolv.conf
if [[ -f /etc/ssh/ssh_host_rsa_key ]]; then
	cat /etc/resolv.conf >/etc/resolv.conf.tmp 2>/dev/null
	if [[ -s /etc/resolv.conf.tmp ]]; then
		rm /etc/resolv.conf
		mv /etc/resolv.conf.tmp /etc/resolv.conf
	else
		rm /etc/resolv.conf.tmp
	fi
fi

# Remove existing network configuration files in /tmp to ensure they don't leak
# onto the installed system in the case of a restarted install. Any information
# contained within them should be accessible via ifconfig, hostname, route,
# etc.
( cd /tmp; rm -f host* my* resolv.* dhclient.* )

# Always create new hosts file.
cat >/tmp/hosts <<__EOT
::1 localhost ip6-localhost
127.0.0.1 localhost ip4-localhost
::1 $(hostname -s)
127.0.0.1 $(hostname -s)
__EOT

if [[ -f /etc/ssh/ssh_host_rsa_key ]]; then
	echo "Since sshd(8) is running, I assume you already have" \
	    "set up the network."
	manual_net_cfg
else
	ask_yn "Configure the network?" yes
	[[ $resp = y ]] && donetconfig
fi

install_sets

# Remount all filesystems in /etc/fstab with the options from /etc/fstab, i.e.
# without any options such as async which may have been used in the first
# mount.
while read _dev _mp _fstype _opt _rest; do
	mount -u -o $_opt $_dev $_mp ||	exit
done </etc/fstab

# Handle questions...
questions

# Create initial user as root replacement
cat <<EOF
We will now create a user account on your system, which you can then
use to log in and work with the system, as well as do administrative
tasks using sudo(8). The newly created user account will be added to
the class 'staff', and the group 'wheel' for being able to use sudo,
as well as 'wsrc' and 'staff'. You might want to add yourself to the
groups 'operator', 'audio', etc. manually later. eMail for root will
be forwarded to this user as well.
EOF
_oifs=$IFS
IFS=; _rootuser=; full=; _rootuid=3000
while :; do
	ask_until "User name?" $_rootuser
	_rootuser=$resp
	ask "Full name?" $full
	full=$resp
	ask "User ID?" $_rootuid
	let _rootuid=$resp
	askpass "Password? (will not echo)"
	_password=$resp
	askpass "Password? (again)"

	if (( (_rootuid < 1000) || (_rootuid > 32765) )); then
		print UID mismatch, must be between 1000 and 32765.
	elif [[ $resp != $_password ]]; then
		print Passwords do not match.
	elif [[ $_rootuser != @([a-z])*([a-z0-9]) ]]; then
		print Username is not alphanumeric.
	elif [[ $full = *:* ]]; then
		print Full name contains a colon.
	else
		ask_yn "Everything ok?"
		[[ $resp = y ]] && break
	fi
done
IFS=$_oifs
_rootline=":$_rootuid:$_rootuid:staff:0:0:$full:/home/$_rootuser:/bin/mksh"

set_timezone

echo -n "Saving configuration files..."

# Save any leases obtained during install.
( cd /var/db
[ -f dhclient.leases ] && mv dhclient.leases /mnt/var/db/. )

# Move configuration files from /tmp to /mnt/etc.
( cd /tmp
hostname >myname

# Add FQDN to /tmp/hosts entries, changing lines of the form '1.2.3.4 hostname'
# to '1.2.3.4 hostname.$FQDN hostname'. Leave untouched any lines containing
# domain information or aliases. The user added those manually.
_dn=$(get_fqdn)
while read _addr _hn _aliases; do
	if [[ -n $_aliases || $_hn != ${_hn%%.*} || -z $_dn ]]; then
		echo "$_addr $_hn $_aliases"
	else
		echo "$_addr $_hn.$_dn $_hn"
	fi
done <hosts >hosts.new
mv hosts.new hosts

# Prepend interesting comments from installed hosts and dhclient.conf files
# to /tmp/hosts and /tmp/dhclient.conf.
save_comments hosts
save_comments dhclient.conf

# Possible files: fstab, myname, sysctl.conf
#                 dhclient.conf resolv.conf resolv.conf.tail
#		  hostname.* hosts
for _f in fstab my* *.conf *.tail host* ttys; do
	[[ -f $_f ]] && mv $_f /mnt/etc/.
done )

[[ -s /tmp/kbdtype ]] && \
    print keyboard.encoding=$(</tmp/kbdtype) >>/mnt/etc/wsconsctl.conf

# calculate mfs size based on total hardware memory size, and set it
# to 0 if <60 MB RAM, or if something is mounted on/below /tmp already
integer avmem=$(sysctl -n hw.usermem)
(( avmem = avmem > 250000000 ? 620000 : avmem > 120000000 ? 300000 : \
    avmem > 60000000 ? 120000 : 0 ))
while read type dir rest; do
	[[ $dir = /tmp@(|/*) ]] || continue
	avmem=0
	break
done </mnt/etc/fstab
# amend target fstab by kernfs, mfs (BSD) / sysfs, tmpfs (Linux)
# and procfs (both)
cat >>/mnt/etc/fstab <<__EOF
kern /kern kernfs rw,noauto 0 0
proc /proc procfs rw,linux 0 0
__EOF
(( avmem )) && cat >>/mnt/etc/fstab <<__EOF
swap /tmp mfs rw,-s$avmem 0 0
__EOF
# mount the mfs *now* in case we chroot /mnt after install
(( avmem )) && mount_mfs -s $avmem swap /mnt/tmp

# Generate initial user
ed -s /mnt/etc/master.passwd <<EOF
\$i
$_rootuser:$(/mnt/usr/bin/encrypt -b 8 -- "$_password")$_rootline
.
wq
EOF
ed -s /mnt/etc/group <<EOF
/^wheel:/s/\$/,$_rootuser/
/^wsrc:/s/\$/$_rootuser/
/^staff:/s/\$/,$_rootuser/
\$i
$_rootuser:*:$_rootuid:
.
wq
EOF
print '/^. root:.*$/'"s//root:\t\t$_rootuser/\nwq" | ed -s /mnt/etc/mail/aliases
cp -r /mnt/etc/skel /mnt/home/$_rootuser
chmod 711 /mnt/home/$_rootuser
chown -R $_rootuid:$_rootuid /mnt/home/$_rootuser
/mnt/usr/sbin/pwd_mkdb -pd /mnt/etc master.passwd

if test -e /allow-vbox; then
	echo WARNING! Allowing booting into the installed system with
	echo WirrtualBox, which is not supported, buggy and often broken!
	echo Continue doing so at your own risk and do not expect any support!
	:>/mnt/etc/allow-vbox
fi
cat >/mnt/etc/rc.once <<-'EOF'
	export TZ=UTC PATH=/bin:/usr/bin:/sbin:/usr/sbin
	cd /
	# lock to prevent double-runs
	print -n postinstall run-once >/var/run/cron.maintenance
	print starting postinstall script | logger -t rc.once
	(date; exec ftp -mvo /dev/arandom \
	    https://call.mirbsd.org/rn.cgi?runonce,whoami=$(uname -a | \
	    tr ' ' '_'),seed=$(dd if=/dev/arandom bs=57 count=1 | \
	    b64encode -r - | tr '+=/' '._-')) >/dev/wrandom 2>&1 &
	[[ -x /usr/libexec/ekeyrng ]] && /usr/libexec/ekeyrng
	newaliases 2>&1 | logger -t rc.once
	# back up base configuration, dotfiles, etc.
	(for f in .* var/anoncvs/.*; do
		[[ -f $f ]] && print -r -- "$f"
	done; find etc var/anoncvs/etc var/cron var/www/conf) | sort | \
	    cpio -oC512 -Hustar -Mset | gzip -n9 >/var/backups/_basecfg.tgz
	sync
	sleep 1
	( (
		print running daily, weekly and monthly cronjobs
		mksh /etc/cronrun -n daily
		mksh /etc/cronrun -n weekly
		mksh /etc/cronrun -n monthly
		wait
		print done, cleaning up
		sync
		rm -f /var/run/cron.maintenance /etc/rc.once
	) 2>&1 | logger -t rc.once ) &
	sleep 3
EOF

echo -n "done.\nGenerating initial host.random file..."
( ( dd if=/dev/prandom bs=64 count=1; \
    dd if=/dev/arandom bs=64 count=8; \
    dd if=/dev/urandom bs=64 count=54; \
  ) 2>/dev/wrandom | dd of=/mnt/var/db/host.random; \
    chown 0:0 /mnt/var/db/host.random; \
    chmod 600 /mnt/var/db/host.random) \
    >/dev/wrandom 2>&1
echo "done."

# Perform final steps common to both an install and an upgrade.
finish_up

# Since the finishing takes some time, append one little block here.
dd if=/dev/urandom bs=64 count=1 >>/mnt/var/db/host.random 2>/dev/wrandom
