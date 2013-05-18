#!/bin/mksh
# $MirOS: src/distrib/common/upgrade.sh,v 1.9 2009/12/28 17:26:58 tg Exp $
# $OpenBSD: upgrade.sh,v 1.61 2005/04/02 14:27:08 krw Exp $
# $NetBSD: upgrade.sh,v 1.2.4.5 1996/08/27 18:15:08 gwr Exp $
#
# Copyright (c) 1997-2004 Todd Miller, Theo de Raadt, Ken Westerback
# All rights reserved.
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

# install.sub needs to know the MODE
MODE=upgrade

# include common subroutines and initialization code
. install.sub

# Have the user confirm that $ROOTDEV is the root filesystem.
while :; do
	ask "Root filesystem?" "$ROOTDEV"
	resp=${resp##*/}
	[[ -b /dev/$resp ]] && break

	echo "Sorry, $resp is not a block device."
done
ROOTDEV=$resp

echo -n "Checking root filesystem (fsck -fp /dev/${ROOTDEV}) ... "
if ! fsck -fp /dev/$ROOTDEV >/dev/null 2>&1; then
	echo	"FAILED.\nYou must fsck ${ROOTDEV} manually."
	exit
fi
echo	"OK."

echo -n "Mounting root filesystem..."
if ! mount -o ro /dev/$ROOTDEV /mnt; then
	echo	"ERROR: can't mount root filesystem!"
	exit
fi
echo	"done."

# The fstab, hosts and myname files are required.
for _file in fstab hosts myname; do
	if [ ! -f /mnt/etc/$_file ]; then
		echo "ERROR: no /mnt/etc/${_file}!"
		exit
	fi
	cp /mnt/etc/$_file /tmp/$_file
done
hostname $(</tmp/myname)

if [[ -f /etc/ssh/ssh_host_rsa_key ]]; then
	echo "Since sshd(8) is running, I assume you already have" \
	    "set up the network."
	echo 'I will *not* offer to use the configuration from the root fs!'
else
	ask_yn "Enable network using configuration stored on root filesystem?" yes
	[[ $resp = y ]] && enable_network
fi

# Offer the user the opportunity to tweak, repair, or create the network
# configuration by hand.
manual_net_cfg

cat <<__EOT

The fstab is configured as follows:

$(</tmp/fstab)

For the $MODE, filesystems in the fstab will be automatically mounted if the
'noauto' option is absent, and /sbin/mount_<fstype> is found, and the fstype is
not nfs or mfs. Non-ffs filesystems will be mounted read-only.

You can edit the fstab now, before it is used, but the edited fstab will only
be used during the upgrade. It will not be copied back to disk.
__EOT
edit_tmp_file fstab

# Create /etc/fstab.
munge_fstab

# fsck -p non-root filesystems in /etc/fstab.
check_fs

# Mount filesystems in /etc/fstab.
if ! umount /mnt; then
	echo	"ERROR: can't unmount previously mounted root!"
	exit
fi
mount_fs

# Upgrade helper for pkgutl*.ngz (pre-install part)
rm -f /mnt/usr/mpkg/_{upgrade,flst}
if [[ -d /mnt/usr/mpkg/db/. ]]; then (
	cd /mnt/usr/mpkg
	# fold in /usr/mpkg/db/pkg/{mirmake,pkgtools}-* from the database
	# as well as the contents of the mirmake package (pkgtools is OK)
	for i in db/pkg/mirmake-*; do
		[[ -d $i/. ]] || continue
		print -r -- "$i" >>_flst
		grep -v '^[+@]' $i/+CONTENTS | grep -v '^share/mmake' >>_flst
		print share/mmake >>_flst
	done
	for i in db/pkg/pkgtools-*; do
		[[ -d $i/. ]] && print -r -- "$i" >>_flst
	done
	# XXX no sort here… # sort -uo _flst _flst
	cpio -oC512 -Hnewc -Mset <_flst >_upgrade
	rm -rf $(<_flst)
	rm -f _flst
); fi

# Install sets.
install_sets

# Upgrade helper for pkgutl*.ngz (post-install part)
if [[ -s /mnt/usr/mpkg/_upgrade ]]; then (
	cd /mnt/usr/mpkg
	found=0
	for i in db/pkg/pkgtools-*; do
		[[ -d $i/. ]] || continue
		found=1
		break
	done
	if (( !found )); then
		# restore mirmake and pkgtools from before
		tar xphf _upgrade
	fi
	rm -f _upgrade
); fi

# Little upgrade helpers
[[ -e /mnt/etc/boot.conf && ! -e /mnt/boot.cfg ]] && \
    cp /mnt/etc/boot.conf /mnt/boot.cfg
[[ -e /mnt/etc/boot.cfg && ! -e /mnt/boot.cfg ]] && \
    cp /mnt/etc/boot.cfg /mnt/boot.cfg
[[ -e /mnt/etc/spamd.conf && ! -e /mnt/etc/mail/spamd.conf ]] && \
    cp /mnt/etc/spamd.conf /mnt/etc/mail/spamd.conf
[[ -d /mnt/usr/dbin/. || -d /mnt/usr/dsbin/. ]] && \
    for f in /mnt/usr/dbin/* /mnt/usr/dsbin/*; do
	[[ -f $f ]] || continue
	for d in bin sbin usr/bin usr/sbin; do
		if [[ -e /mnt/$d/${f##*/} ]]; then
			rm -f $f
			ln -sf ../../$d/${f##*/} $f
			break
		fi
	done
done
if [[ -d /mnt/usr/include/gxx/. ]]; then
	found=
	for i in /mnt/usr/lib/gcc/*/3.4.6/include/c++/.; do
		[[ -d $i ]] && found=$i
	done
	[[ -n $found ]] && rm -rf /mnt/usr/include/gxx
fi
if [[ -d /mnt/usr/include/objc/. ]]; then
	found=
	for i in /mnt/usr/lib/gcc/*/3.4.6/include/objc/.; do
		[[ -d $i ]] && found=$i
	done
	[[ -n $found ]] && rm -rf /mnt/usr/include/objc
fi

# Perform final steps common to both an install and an upgrade.
finish_up

( ( dd if=/dev/prandom bs=64 count=1; \
    dd if=/dev/arandom bs=64 count=8; \
    dd if=/dev/urandom bs=64 count=55; \
  ) 2>/dev/wrandom | dd of=/mnt/var/db/host.random; \
    chown 0:0 /mnt/var/db/host.random; \
    chmod 600 /mnt/var/db/host.random) \
    >/dev/wrandom 2>&1
