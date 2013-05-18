#!/bin/mksh
# $MirOS: src/distrib/i386/livecd/munge_it.sh,v 1.3 2006/04/05 23:39:47 tg Exp $
#-
# Copyright (c) 2006
#	Thorsten Glaser <tg@mirbsd.de>
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
# Patch a freshly unpacked MirOS installation into the standard live
# CD distribution.

set -ex
myplace=$(readlink -nf $(dirname "$0"))

ed -s etc/X11/xdm/Xresources <<-'EOF'
	/^xlogin.greeting:/s/CLIENTHOST/the MirOS BSD Live CD/
	/^Chooser.label.label:/s/CLIENTHOST/Live-CD/
	wq
EOF
ed -s etc/group <<-'EOF'
	/^wheel:/s/$/,live/
	/^operator:/s/$/,live/
	/^wsrc:/s/$/live/
	/^staff:/s/$/,live/
	/^www:/s/$/live/
	/^dialer:/s/$/live/
	/^audio:/s/$/live/
	/^nobody:/i
		live:*:32762:
	.
	wq
EOF
ed -s etc/master.passwd <<-'EOF'
	/^nobody:/i
		live:$2a$04$NCMhVFfIg3afYRXLCDGjcOPYJxem4lxSLcthQT5AaejUaAAvIWdCW:32762:32762:staff:0:0:MirOS BSD Live CD User:/home/live:/bin/mksh
	.
	wq
EOF
ed -s etc/ntpd.conf <<-'EOF'
	/^.server /d
	i
		server 81.169.176.177
	.
	wq
EOF
ed -s etc/rc <<-'EOF'
	1i
		# $MirOS: src/distrib/i386/livecd/munge_it.sh,v 1.3 2006/04/05 23:39:47 tg Exp $
	.
	/^rm.*fastboot$/a

		function do_mfsmount
		{
			print -n " $1"
			mount_mfs -s ${2:-262144} swap /$1
		}
		print -n 'initialising memory filesystems...'
		do_mfsmount dev 16384
		do_mfsmount etc 131072
		do_mfsmount root
		do_mfsmount tmp 524288
		do_mfsmount var
		sleep 2
		tar xzphf /home/fsrw.cgz
		sleep 1
		do_mfsmount home
		print ' done'
		(cd /dev; mksh ./MAKEDEV all)
		sleep 1
		cp -r etc/skel home/live
		chown -R 32762:32762 home/live
	.
	wq
EOF
ed -s etc/rc.conf <<-'EOF'
	/^ntpd_flags/s/NO/""/
	/^wsmoused_flags/s/NO/"-2"/
	wq
EOF
ed -s etc/rc.securelevel <<-'EOF'
	/^securelevel/s/1/-1/
	wq
EOF
ed -s etc/sudoers <<-'EOF'
	%g/@ROOT@/s//live/
	wq
EOF
ed -s etc/sysctl.conf <<-'EOF'
	/^.ddb.console/s/^.//
	/^.kern.seminfo.semmni/s/^.//
	/^.kern.seminfo.semmns/s/^.//
	/^.kern.seminfo.semmnu/s/^.//
	/^.kern.shminfo.shmall/s/^.//
	/^.machdep.allowaperture/s/^.//
	/^.machdep.kbdreset/s/^.//
	/^.kern.emul.linux/s/^.//
	/^.kern.emul.openbsd/s/^.//
	wq
EOF
ed -s etc/ttys <<-'EOF'
	/^tty00/s/unknown/vt220/
	s/off/on secure/
	wq
EOF
ed -s var/cron/tabs/root <<-'EOF'
	/daily/s/^/#/
	/weekly/s/^/#/
	/monthly/s/^/#/
	/randshuffle/s/^/#/
	/randomnumbers.info/s/^.//
	/fourmilab.ch/s/^.//
	wq
EOF

install -c -o root -g staff -m 644 $myplace/XF86Config etc/X11/XF86Config
install -c -o root -g staff -m 644 $myplace/fstab etc/fstab
install -c -o root -g staff -m 644 $myplace/rc.netselect etc/rc.netselect

(cd dev; mksh ./MAKEDEV std)
pwd_mkdb -pd $(readlink -nf etc) master.passwd
dd if=/dev/urandom bs=4096 count=1 of=var/db/host.random

# tmp because of perms
find dev etc root tmp var | sort | cpio -oC512 -Hsv4crc -Mset | \
    gzip -n9 >home/fsrw.cgz
rm -rf root var
mkdir root var

exit 0
