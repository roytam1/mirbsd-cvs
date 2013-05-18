#!/bin/mksh
# $MirOS: src/distrib/baselive/munge_it.sh,v 1.6 2006/08/22 21:51:40 tg Exp $
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
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a defect.
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
cat >>etc/exports <<-'EOF'
	/ -ro -maproot=root
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
ed -s etc/inetd.conf <<-'EOF'
	%g/^.tftp/s/^.//
	%g!/tftpboot!s!!/var&!
	wq
EOF
ed -s etc/master.passwd <<-'EOF'
	/^root:/s!/root!/dev/.root!
	/^nobody:/i
		live:$2a$04$NCMhVFfIg3afYRXLCDGjcOPYJxem4lxSLcthQT5AaejUaAAvIWdCW:32762:32762:staff:0:0:MirOS BSD Live CD User:/home/live:/bin/mksh
	.
	wq
EOF
ed -s etc/ntpd.conf <<-'EOF'
	/^.server /d
	i
		server ntp.mirbsd.org
	.
	wq
EOF
ed -s etc/rc <<-'EOF'
	1i
		# $MirOS: src/distrib/baselive/munge_it.sh,v 1.6 2006/08/22 21:51:40 tg Exp $
	.
	/shutdown request/ka
	/^fi/a

		mount /dev/rd0a /dev
		cat /dev/.rs >/dev/arandom 2>&-
		( (dd if=/dev/rwd0c count=126; dd if=/dev/rsd0c count=126) \
		    2>&1 | cksum -ba sha512 >/dev/arandom ) &
		(cd /dev; ln -s $(sysctl -n kern.root_device) root)
		rm -f /dev/.rs
		print \#\\tThis product includes material provided by Thorsten Glaser.
	.
	/^raidctl.*all/s/^/#/
	/^rm.*fastboot$/a

		function do_mfsmount
		{
			print -n " $1"
			mount_mfs -s ${2:-300000} swap /$1
		}
		print -n 'initialising memory filesystems...'
		do_mfsmount etc 20480
		do_mfsmount home
		do_mfsmount tmp 600000
		do_mfsmount usr/X11R6/lib/X11 20480
		do_mfsmount var
		print '... done'
		sleep 2
		print -n 'extracting mfs contents...'
		pax -r -pe -f /stand/fsrw.dat
		print ' done'
		sleep 1
		cp -r etc/skel home/live
		chown -R 32762:32762 home/live
		[[ -s /stand/locate.database ]] && \
		    cp /stand/locate.database /var/db/locate.database
	.
	/openssl genrsa/s/4096/1024/
	%g!/etc/ttys\.gen!s!!/etc/ttys!g
	/^#	print -n adjusting/s/^#//
	/for now/d
	/xdm may be started/i
		(stats_sysadd=-livecd mksh \
		    /usr/share/misc/bsdstats <&- 2>&1 | logger -t BSDstats) &

	.
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
	/accept_rtadv/s/^.//
	/^.ddb.console/s/^.//
	/^.kern.seminfo.semmni/s/^.//
	/^.kern.seminfo.semmns/s/^.//
	/^.kern.seminfo.semmnu/s/^.//
	/^.kern.shminfo.shmall/s/^.//
	wq
EOF
[[ $MACHINE = i386 ]] && ed -s etc/sysctl.conf <<-'EOF'
	/^.machdep.allowaperture/s/^.//
	/^.machdep.kbdreset/s/^.//
	/^.kern.emul.linux/s/^.//
	/^.kern.emul.openbsd/s/^.//
	wq
EOF
ed -s usr/bin/ftp <<-'EOF'
	%g/MirOS ftp(1)/s//MirOS LiveCD/
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

install -c -o root -g staff -m 644 \
    $myplace/$MACHINE/XF86Config etc/X11/XF86Config
install -c -o root -g staff -m 644 \
    $myplace/fstab etc/fstab
install -c -o root -g staff -m 644 \
    $myplace/$MACHINE/rc.conf.local etc/rc.conf.local
install -c -o root -g staff -m 644 \
    $myplace/$MACHINE/rc.netselect etc/rc.netselect
install -c -o root -g staff -m 644 \
    $myplace/dot.xsession etc/skel/.xsession
install -c -o root -g bin -m 555 \
    $myplace/evilwm-session usr/local/bin/evilwm-session

(cd dev; mksh ./MAKEDEV std rd0a)
pwd_mkdb -pd $(readlink -nf etc) master.passwd
dd if=/dev/arandom count=4 of=var/db/host.random

mv root dev/.root
rm -rf usr/X11R6/lib/X11/fonts/{100dpi,OTF,Speedo,Type1,cyrillic,local}
mv usr/X11R6/lib/X11/fonts usr/X11R6/lib/fonts
(cd usr/X11R6/lib/X11; ln -s ../fonts)
# tmp because of perms
find dev/.root etc tmp usr/X11R6/lib/X11 var | sort | \
    cpio -oC512 -Hsv4crc -Mset >stand/fsrw.dat
rm -rf dev/.root usr/X11R6/lib/X11 var sys
mkdir -p usr/X11R6/lib/X11 var

exit 0
