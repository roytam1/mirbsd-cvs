# $MirOS$
# $OpenBSD: install.md,v 1.22 2004/03/03 02:19:26 krw Exp $
#
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
#
# machine dependent section of installation/upgrade script.
#

MDFSTYPE=ntfs
MDFSOPTS=ro
MDTERM=wsvtg
MDXAPERTURE=2
ARCH=ARCH

md_set_term() {
    if [ -x /sbin/kbd ]; then
	local _tables

	ask_yn "Do you wish to select a keyboard encoding table?"
	[[ $resp == n ]] && return

	while : ; do
		ask "Select your keyboard type: (P)C-AT/XT, (U)SB or 'done'" P
		case $resp in
		P*|p*)  _tables="be br de dk es fr it jp lt no pt ru sf sg sv ua uk us"
			;;
		U*|u*)	_tables="br de dk es fr it jp no sf sg sv uk us"
			;;
		done)	;;
		*)	echo "'$resp' is not a valid keyboard type."
			resp=
			continue
			;;
		esac
		break;
	done

	[ -z "$_tables" ] && return

	while : ; do
		cat <<__EOT
The available keyboard encoding tables are:

	${_tables}

__EOT
		ask "Table name? (or 'done')" us
		case $resp in
		done)	;;
		*)	if kbd $resp ; then
				echo $resp >/tmp/kbdtype
			else
				echo "'${resp}' is not a valid table name."
				continue
			fi
			;;
		esac
		break;
	done
    fi
}

md_installboot() {
	echo Installing boot block...
	cat /usr/mdec/boot >/mnt/boot
	/usr/mdec/installboot -v /mnt/boot /usr/mdec/ffspbr ${1}
	echo "done."
}

# $1 is the disk to check
md_checkfordisklabel() {
	local rval=0

	disklabel -r $1 >/dev/null 2>/tmp/checkfordisklabel

	if grep "disk label corrupted" /tmp/checkfordisklabel; then
		rval=2
	fi >/dev/null 2>&1

	rm -f /tmp/checkfordisklabel
	return $rval
}

md_prep_fdisk() {
	local _disk=$1

	ask_yn "Do you want to use *all* of $_disk for MirBSD?"
	if [[ $resp == y ]]; then
		echo -n "Putting all of $_disk into an active MirBSD MBR partition (type 27)..."
		fdisk -ef /nonexist ${_disk} <<__EOT >/dev/null
r
u
w
q
__EOT
		echo "done."
		return
	fi

	# Manually configure the MBR.
	cat <<__EOT

You will now create at least a single MBR partition to contain the disklabel.
This *PRIMARY* partition must have an ID of 27 hex (or 0xA9 for compatibility
reasons) and NOT overlap other partitions. You can create other MBR partitions,
primary or extended ones, to contain the filesystems, but these must *NOT* be
of type 27, A6, A5 or A9. It is recommended they be of type DB (CP/M-86), and
they are only used to mark the space as USED for other operating systems that
still need MBR partitions. BSD exclusively uses the data in the disklabel to
determine where filesystems are, and uses the MBR partition exclusively to
determine where on the disk the disklabel is positioned.

The 'manual' command describes all the fdisk commands in detail.

$(fdisk ${_disk})
__EOT
	fdisk -e ${_disk}

	cat <<__EOT
Here is the partition information you chose:

$(fdisk ${_disk})
__EOT
}

md_prep_disklabel() {
	local _disk=$1
	md_prep_fdisk $_disk
	cat <<__EOT

You will now create a MirBSD disklabel inside the MirBSD MBR partition. The
disklabel defines how MirBSD splits up the MBR partition (rather, the whole
disk) into MirBSD slices in which filesystems and swap space are created.

The offsets used in the disklabel are ABSOLUTE, i.e. relative to the
start of the disk, NOT the start of the MirBSD MBR partition.

If you have created a split space, i.e. one partition of type 27 and one or
more partitions of type (e.g.) DB, use the command b<return>0<return>*<return>
to enable using the entire disk for MirBSD. Be sure to create slices mapping
the filesystems of any other operating systems in order to not overwrite them.

__EOT

	md_checkfordisklabel $_disk
	case $? in
	2)	echo "WARNING: Label on disk $_disk is corrupted. You will be repairing it.\n"
		;;
	esac

	disklabel -W $_disk >/dev/null 2>&1
	disklabel -f /tmp/fstab.$_disk -E $_disk
}

md_congrats() {
}
