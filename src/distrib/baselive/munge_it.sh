#!/bin/mksh
# $MirOS: src/distrib/baselive/munge_it.sh,v 1.18 2007/02/20 01:09:34 tg Exp $
#-
# Copyright (c) 2006, 2007
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
# Patch a freshly unpacked MirOS installation into the standard base
# system generated live CD distribution.

set -ex
myplace=$(readlink -nf $(dirname "$0"))

ed -s etc/X11/xdm/Xresources <<-'EOMD'
	/^xlogin.greeting:/s/CLIENTHOST/the MirOS BSD Live CD/
	/-100-100-/s//-75-75-/
	/^Chooser.label.label:/s/CLIENTHOST/Live-CD/
	wq
EOMD
cat >>etc/exports <<-'EOMD'
	/ -ro -maproot=root
EOMD
ed -s etc/group <<-'EOMD'
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
EOMD
ed -s etc/inetd.conf <<-'EOMD'
	%g/^.tftp/s/^.//
	%g!/tftpboot!s!!/var&!
	wq
EOMD
ed -s etc/master.passwd <<-'EOMD'
	/^root:/s!/root!/dev/.root!
	/^nobody:/i
		live:$2a$04$NCMhVFfIg3afYRXLCDGjcOPYJxem4lxSLcthQT5AaejUaAAvIWdCW:32762:32762:staff:0:0:MirOS BSD Live CD User:/home/live:/bin/mksh
	.
	wq
EOMD
ed -s etc/ntpd.conf <<-'EOMD'
	/^.server /d
	i
		server ntp.mirbsd.org
	.
	wq
EOMD
ed -s etc/rc <<-'EOMD'
	1i
		# $MirOS: src/distrib/baselive/munge_it.sh,v 1.18 2007/02/20 01:09:34 tg Exp $
	.
	/shutdown request/ka
	/^fi/a

		mount -fwo async,noatime /dev/rd0a /dev
		cat /dev/.rs >/dev/arandom 2>&-
		( (dd if=/dev/rwd0c count=126; dd if=/dev/rsd0c count=126) \
		    2>&1 | cksum -ba sha512 >/dev/arandom ) &
		(cd /dev; ln -s $(sysctl -n kern.root_device) root; rm -f .rs)
		print \#\\tThis product includes material provided by Thorsten Glaser.
	.
	/^raidctl.*all/s/^/#/
	/^umount/a
		mount -fwo async,noatime /dev/rd0a /dev >/dev/null 2>&1
	.
	/t nonfs/i
		print -n 'extracting mfs contents...'
		gzip -dc /stand/fsrw.dat | pax -r -pe
		print -n ' populating...'
		sleep 1
		cp -r etc/skel home/live
		chown -R 32762:32762 home/live
		[[ -s /stand/locate.database ]] && \
		    cp /stand/locate.database /var/db/locate.database
		print ' done'

	.
	/dmesg.boot/i

		# try to get some entropy from the network
		(ulimit -T 60; exec /usr/bin/ftp -mvo /dev/arandom \
		    https://herc.mirbsd.org/rn.cgi?live"<$(uname -a | sed '
			s/%/%25/g
			s/;/%3b/g
			s,/,%2f,g
			s/?/%3f/g
			s/:/%3a/g
			s/@/%40/g
			s/&/%26/g
			s/=/%3d/g
			s/+/%2b/g
			s/\$/%24/g
			s/,/%2c/g
			s/ /%20/g
		    ')>" >/dev/wrandom 2>&1)
	.
	/parsed console/a
		[[ -e /etc/ttys ]] && if [[ $consdev != nochg ]]; then
			print -n adjusting /etc/ttys ...
			x=$(uname -m)
			if [[ $x = i386 ]]; then
				# clean up if we don't match
				if ! grep "^#AUTOCONS:$consdev,$consspeed." /etc/ttys >&- 2>&-; then
					print -n ' cleanup (i386)'
					ed -s /etc/ttys <<-EOF
						%g/^#AUTOCONS/d
						%g/	#AUTOADD\$/d
						%g/	#AUTODEL\$/s/^#*//
						%g/	#AUTODEL\$/s///
						wq
					EOF
				fi
			fi
			# if consdev=ttyC0: wscons, no change needed
			if [[ $consdev = ttyC0 ]]; then
				print -n ' wscons'
				# wscons, reset to default on sparc, no action on i386
				if [[ $x = sparc ]]; then
					print -n ' (sparc)'
					ed -s /etc/ttys <<-EOF
						/console.*suncons/s/^#*//
						/console.*std/s/^#*/#/
						wq
					EOF
				fi
			else
				# serial console, disable wscons
				print -n " serial ($consspeed bps)"
				if [[ $x = sparc ]]; then
					# we just use /dev/console for both
					# XXX what is this ttyC0 entry?
					print -n ' (sparc)'
					ed -s /etc/ttys <<-EOF
						/console.*suncons/s/^#*/#/
						/console.*std/s/^#*//
						/console.*std/s/std.[0-9]*/std.$consspeed/
						wq
					EOF
				fi
				if [[ $x = i386 ]]; then
					# keep wscons but enable tty0X dev
					print -n ' (i386)'
					if ! grep "^$consdev	.*std.$consspeed\".*	on" \
					    /etc/ttys >&- 2>&-; then
						print -n ' -> adding'
						ed -s /etc/ttys <<-EOF
							%g/^$consdev	/s/^.*\$/#&	#AUTODEL/
							wq
						EOF
						cat >>/etc/ttys <<-EOF
							$consdev	"/usr/libexec/getty std.$consspeed"	vt100	on  secure	#AUTOADD
							#AUTOCONS:$consdev,$consspeed.
						EOF
					fi
				fi
			fi
			print ' done.'
		fi
	.
	/openssl genrsa/s/4096/1024/
	/xdm may be started/i
		(
			cp /usr/bin/ftp /tmp/ftp.bsdstats
			ed -s /tmp/ftp.bsdstats <<-'EOFB'
				%g/MirOS LiveCD/s//MirOS ftp(1)/
				wq
			EOFB
			sed 's!/usr/bin/ftp!/tmp/ftp.bsdstats!g' \
			    </usr/share/misc/bsdstats >/tmp/run.bsdstats
			stats_sysadd=-livecd mksh \
			    /tmp/run.bsdstats <&- 2>&1 | logger -t BSDstats
			rm -f /tmp/ftp.bsdstats /tmp/run.bsdstats
		) &

	.
	wq
EOMD
ed -s etc/rc.securelevel <<-'EOMD'
	/^securelevel/s/1/-1/
	wq
EOMD
ed -s etc/sudoers <<-'EOMD'
	%g/@ROOT@/s//live/
	wq
EOMD
ed -s etc/sysctl.conf <<-'EOMD'
	/accept_rtadv/s/^.//
	/^.ddb.console/s/^.//
	/^.kern.seminfo.semmni/s/^.//
	/^.kern.seminfo.semmns/s/^.//
	/^.kern.seminfo.semmnu/s/^.//
	/^.kern.shminfo.shmall/s/^.//
	wq
EOMD
[[ $MACHINE = i386 ]] && ed -s etc/sysctl.conf <<-'EOMD'
	/^.machdep.allowaperture/s/^.//
	/^.machdep.kbdreset/s/^.//
	/^.kern.emul.linux/s/^.//
	/^.kern.emul.openbsd/s/^.//
	wq
EOMD
ed -s usr/bin/ftp <<-'EOMD'
	%g/MirOS ftp(1)/s//MirOS LiveCD/
	wq
EOMD
ed -s var/cron/tabs/root <<-'EOMD'
	/daily/s/^/#/
	/weekly/s/^/#/
	/monthly/s/^/#/
	/randshuffle/s/^/#/
	/randomnumbers.info/s/^.//
	/fourmilab.ch/s/^.//
	/random.org/s/^.//
	wq
EOMD

install -c -o root -g staff -m 644 \
    $myplace/$MACHINE/XF86Config etc/X11/XF86Config
install -c -o root -g staff -m 644 \
    $myplace/fstab etc/fstab
install -c -o root -g staff -m 644 \
    $myplace/$MACHINE/rc.conf.local etc/rc.conf.local
install -c -o root -g staff -m 644 \
    $myplace/$MACHINE/rc.netselect etc/rc.netselect
install -c -o root -g staff -m 644 \
    $myplace/rc.netselect.common etc/rc.netselect.common
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
    cpio -oC512 -Hsv4crc -Mset | gzip -n9 >stand/fsrw.dat
rm -rf dev/.root usr/X11R6/lib/X11 var sys
mkdir -p emul usr/X11R6/lib/X11 usr/mpkg usr/ports var
chown 0:0 emul var

exit 0
