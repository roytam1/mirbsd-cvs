#!/bin/mksh
# $MirOS: src/distrib/baselive/munge_it.sh,v 1.49 2013/11/30 13:45:21 tg Exp $
#-
# Copyright (c) 2006, 2007, 2008, 2013, 2014
#	Thorsten “mirabilos” Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
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
myplace=$(realpath "$0/..")

ed -s etc/X11/XF86Config <<-'EOF'
	/FontPath.*local/s/^/#/
	/FontPath.*100dpi.*unscaled/s/^/#/
	/FontPath.*Speedo/s/^/#/
	/FontPath.*Type1/s/^/#/
	/FontPath.*/s/^/#/
	/FontPath.*100dpi/s/^/#/
	/FontPath.*cyrillic/s/^/#/
	/FontPath.*OTF/s/^/#/
	wq
EOF
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
		# $MirOS: src/distrib/baselive/munge_it.sh,v 1.49 2013/11/30 13:45:21 tg Exp $
	.
	/early munge point/d
	i
		mount -fwo async,noatime /dev/rd0a /dev
		cat /dev/.rs >/dev/urandom 2>&-
		# on sparc, use the nvram to provide some additional entropy
		# also read some stuff from the HDD etc. (doesn't matter if it breaks)
		( ( (for d in {w,s,rai,c}:128, f:1, r:1,512; do b=${d#*,}; d=${d%,*};\
		     dd if=/dev/r${d%:*}d0c count=${d#*:} ${b:+bs=$b of=/dev/urandom}\
		     ; done; dd if=/var/db/host.random of=/dev/urandom; dmesg; sysctl\
		     -a; eeprom) 2>&1 | cksum -a cksum -a sha512 -a suma -a tiger -a \
		     rmd160 -a adler32 -b >/dev/wrandom) &)
		(cd /dev; ln -s $(sysctl -n kern.root_device) root; rm -f .rs)
		print \#\\tMirOS BSD Live-CD/DVD/USB/CF/SD/HDD starting up...
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
		wait
		print ' done'

	.
	/dmesg.boot/i

		# try to get some entropy from any attached Simtec EntropyKey
		[[ -x /usr/libexec/ekeyrng ]] && /usr/libexec/ekeyrng
		# try to get some entropy from the network
		(ulimit -T 60; exec /usr/bin/ftp -mvo /dev/urandom \
		    https://call.mirbsd.org/rn.cgi?live"<$(uname -a | sed '
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
		    ')>,seed=$(dd if=/dev/arandom bs=57 count=1 2>&- | \
		    b64encode -r - | tr '+=/' '._-')" >/dev/wrandom 2>&1)
	.
	/openssl genrsa/s/4096/1024/
	wq
EOMD
ed -s etc/rc.securelevel <<-'EOMD'
	/^securelevel/s/1/-1/
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
cp etc/ttys.dist etc/ttys
perl -p -i -e 's/MirOS ftp.1./MirOS LiveCD/' usr/bin/ftp
ed -s var/cron/tabs/root <<-'EOMD'
	/anacron/s/^/#/
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
pwd_mkdb -pd $(realpath etc) master.passwd
( ( dd if=/dev/prandom bs=64 count=7; \
    dd if=/dev/arandom bs=64 count=56; \
    dd if=/dev/urandom bs=64 count=1; \
  ) 2>/dev/wrandom | dd of=var/db/host.random; \
    chown 0:0 var/db/host.random; \
    chmod 600 var/db/host.random) \
    >/dev/wrandom 2>&1

(cd usr/libdata/ldscripts; rm !(*mbsd*))

# sync with src/distrib/common/listend.i386-big
(saveIFS=$IFS
 tail -3 <usr/share/doc/README | grep '^key ' | \
    while IFS="	" read keynr keyfile; do
	IFS=" :"
	set -A keyno -- $keynr
	IFS=$saveIFS
	print -r -- $keyfile >gzsigkey.${keyno[1]}
done)

(cd usr/X11R6/lib/X11/fonts; rm -rf 100dpi OTF Speedo Type1 cyrillic local \
    misc/*-ISO8859-@(1[013456]|[2345789]).* misc/*{KOI8,JISX0201}* \
    75dpi/*-ISO8859-@(1[0345]|[2349]).* misc/{fonts.alias,gb,hang,jis,k14}*)
cp $myplace/misc_fonts.alias usr/X11R6/lib/X11/fonts/misc/fonts.alias
chown 0:0 usr/X11R6/lib/X11/fonts/misc/fonts.alias
chmod 444 usr/X11R6/lib/X11/fonts/misc/fonts.alias
(cd usr/X11R6/lib/X11/fonts/75dpi; mkfontdir)
(cd usr/X11R6/lib/X11/fonts/misc; mkfontdir)
(cd usr/X11R6/lib/X11; fc-cache -v .)

mv usr/X11R6/lib/X11/fonts usr/X11R6/lib/fonts
(cd usr/X11R6/lib/X11; ln -s ../fonts)
# tmp because of perms
find etc tmp usr/X11R6/lib/X11 var | sort | \
    cpio -oC512 -Hsv4crc -Mset | gzip -n9 >stand/fsrw.dat
rm -rf usr/X11R6/lib/X11 var sys
mkdir -p emul usr/X11R6/lib/X11 usr/mpkg usr/ports var
chown 0:0 emul var

exit 0
