# $MirOS: src/etc/Makefile,v 1.20 2006/04/12 11:59:20 tg Exp $
# $OpenBSD: Makefile,v 1.226 2005/05/26 23:06:06 mcbride Exp $

TZDIR=		/usr/share/zoneinfo
LOCALTIME?=	UTC
NOOBJ=		yes

.if exists(etc.${MACHINE}/Makefile.inc)
.  include "etc.${MACHINE}/Makefile.inc"
.endif

.include <bsd.own.mk>

# -rw-r--r--
BINOWN=	root
BINGRP=	wheel
BIN1=	ccd.conf changelist daily dhclient.conf dhcpd.conf \
	dhcpd.interfaces etc.${MACHINE}/disktab exports \
	ftpchroot ftpusers gettytab group hosts hosts.lpd \
	ifstated.conf inetd.conf locate.rc login.conf \
	mailer.conf man.conf moduli monthly motd mrouted.conf \
	myname netstart networks newsyslog.conf ntpd.conf \
	pf.os phones printcap profile protocols rbootd.conf \
	rc rc.conf rc.local rc.securelevel rc.shutdown remote \
	rpc security sensorsd.conf services shells spamd.conf \
	weekly wsconsctl.conf

# machine dependent parts
BINMD=	make.cfg syslog.conf

# -rw-rw-r--
BIN2=	motd

# Use NOGZIP on architectures where the gzip'ing would take too much time
# (pmax or slower :-)).  This way you get only tar'ed snap files and you can
# gzip them on a faster machine
.ifndef NOGZIP
GZIP?=		gzip
GZIPFLAGS?=	-9
GZIPEXT?=	.gz
.else
GZIP=		cat
GZIPFLAGS=
GZIPEXT=
.endif

all clean cleandir depend etc install lint:

.if !defined(DESTDIR) || empty(DESTDIR)
etc-files:
	@echo setenv DESTDIR before trying this!
	@exit 1
.else
etc-files:
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m 644 ${BIN1} ${DESTDIR}/etc/
	chmod 640 ${DESTDIR}/etc/inetd.conf
	${SHELL} ttys.pty | cat etc.${MACHINE}/ttys - >${DESTDIR}/etc/ttys && \
	    chown ${BINOWN} ${DESTDIR}/etc/ttys && \
	    chgrp ${BINGRP} ${DESTDIR}/etc/ttys && \
	    chmod 644 ${DESTDIR}/etc/ttys
	cat sysctl.conf etc.${MACHINE}/sysctl.conf >${DESTDIR}/etc/sysctl.conf && \
	    chown ${BINOWN} ${DESTDIR}/etc/sysctl.conf && \
	    chgrp ${BINGRP} ${DESTDIR}/etc/sysctl.conf && \
	    chmod 644 ${DESTDIR}/etc/sysctl.conf
	cat fbtab.head etc.${MACHINE}/fbtab fbtab.tail >${DESTDIR}/etc/fbtab && \
	    chown ${BINOWN} ${DESTDIR}/etc/fbtab && \
	    chgrp ${BINGRP} ${DESTDIR}/etc/fbtab && \
	    chmod 644 ${DESTDIR}/etc/fbtab
.  for _i in ${BINMD}
	if [ -e ${.CURDIR}/etc.${MACHINE}/${_i}.md ]; then \
		sed -e '/@@MDPART@@/r${.CURDIR}/etc.${MACHINE}/${_i}.md' \
		    -e '//d' ${.CURDIR}/${_i}; \
	    else \
		sed -e '/@@MDPART@@/d' ${.CURDIR}/${_i}; \
	  fi >${DESTDIR}/etc/${_i}; \
	    chown ${BINOWN} ${DESTDIR}/etc/${_i} && \
	    chgrp ${BINGRP} ${DESTDIR}/etc/${_i} && \
	    chmod 644 ${DESTDIR}/etc/${_i}
.  endfor
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m 664 ${BIN2} ${DESTDIR}/etc/
	${INSTALL} -c -o root -g wheel -m 600 hosts.equiv ${DESTDIR}/etc/
	${INSTALL} -c -o root -g wheel -m 600 crontab ${DESTDIR}/var/cron/tabs/root
	${INSTALL} -c -o root -g wheel -m 600 master.passwd ${DESTDIR}/etc/
	pwd_mkdb -p -d ${DESTDIR}/etc /etc/master.passwd
	${INSTALL} -c -o root -g wheel -m 600 pf.conf ${DESTDIR}/etc/
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m 555 \
	    etc.${MACHINE}/MAKEDEV ${DESTDIR}/dev/
	cd root; \
		${INSTALL} -c -o root -g wheel -m 644 dot.profile \
		    ${DESTDIR}/root/.profile; \
		rm -f ${DESTDIR}/.profile; \
		ln ${DESTDIR}/root/.profile ${DESTDIR}/.profile
	cd skel; \
		${INSTALL} -c -o root -g wheel -m 644 ssh.known_hosts \
		    ${DESTDIR}/etc/skel/.etc/ssh/known_hosts; \
		${INSTALL} -c -o root -g wheel -m 644 calendar \
		    ${DESTDIR}/etc/skel/.etc/calendar/calendar; \
		${INSTALL} -c -o root -g wheel -m 644 dot.Xresources \
		    ${DESTDIR}/etc/skel/.Xresources; \
		${INSTALL} -c -o root -g wheel -m 644 dot.mailrc \
		    ${DESTDIR}/etc/skel/.mailrc
	cd mtree; \
		${INSTALL} -c -o root -g wheel -m 600 special \
		    ${DESTDIR}/etc/mtree/; \
		${INSTALL} -c -o root -g wheel -m 444 4.4BSD.dist \
		    ${DESTDIR}/etc/mtree/
	cd ppp; \
		${INSTALL} -c -o root -g wheel -m 600 \
		    chap-secrets options.sample pap-secrets \
		    ppp.conf.sample ppp.secret.sample \
			${DESTDIR}/etc/ppp/; \
		${INSTALL} -c -o root -g wheel -m 600 \
		    isp.sample isp.chat.sample \
			${DESTDIR}/etc/ppp/peers/; \
		${INSTALL} -c -o root -g wheel -m 755 \
		    ip-up ip-down ppp.linkup.sample ppp.linkdown.sample \
			${DESTDIR}/etc/ppp/
	cd systrace; \
		${INSTALL} -c -o root -g wheel -m 600 usr_sbin_lpd \
		    ${DESTDIR}/etc/systrace/
	/bin/rm -f ${DESTDIR}/etc/localtime
	ln -s ${TZDIR}/${LOCALTIME} ${DESTDIR}/etc/localtime
	/bin/rm -f ${DESTDIR}/etc/rmt
	ln -s /usr/sbin/rmt ${DESTDIR}/etc/rmt
	${INSTALL} -c -o root -g wheel -m 644 minfree \
		${DESTDIR}/var/crash/
	${INSTALL} -c -o ${BINOWN} -g operator -m 664 /dev/null \
		${DESTDIR}/etc/dumpdates
.  if ${MACHINE} == "i386"
	${INSTALL} -c -o root -g wheel -m 644 isdnd.rc.sample \
		${DESTDIR}/etc/isdn/
	${INSTALL} -c -o root -g wheel -m 644 isdnd.sppp.sample \
		${DESTDIR}/etc/isdn/
.  endif
	${INSTALL} -c -o root -g crontab -m 660 /dev/null \
		${DESTDIR}/var/cron/at.deny
	${INSTALL} -c -o root -g crontab -m 660 /dev/null \
		${DESTDIR}/var/cron/cron.deny
	${INSTALL} -c -o root -g wheel -m 444 /dev/null \
		${DESTDIR}/var/db/locate.database
	${INSTALL} -c -o ${BINOWN} -g wheel -m 640 /dev/null \
		${DESTDIR}/var/log/messages
	${INSTALL} -c -o ${BINOWN} -g wheel -m 664 /dev/null \
		${DESTDIR}/var/log/sendmail.st
	${INSTALL} -c -o ${BINOWN} -g wheel -m 644 /dev/null \
		${DESTDIR}/var/log/wtmp
	${INSTALL} -c -o daemon -g staff -m 664 /dev/null \
		${DESTDIR}/var/msgs/bounds
	${INSTALL} -c -o ${BINOWN} -g utmp -m 664 /dev/null \
		${DESTDIR}/var/run/utmp
.  if defined(SKIPDIR) && ${SKIPDIR:Mgnu/usr.sbin/sendmail}
	@echo "Warning: skipping sendmail"
.  else
	cd ../gnu/usr.sbin/sendmail/cf/cf && exec ${MAKE} distribution
.  endif
	cd ../usr.bin/ssh && exec ${MAKE} distribution
	cd ../lib/libssl && exec ${MAKE} distribution
.  for _i in usr.sbin/httpd gnu/usr.bin/lynx
.    if defined(SKIPDIR) && ${SKIPDIR:M${_i}}
	@echo "Warning: skipping ${_i}"
.    else
	cd ../${_i} && exec ${MAKE} -f Makefile.bsd-wrapper distribution
.    endif
.  endfor
	cd ../usr.bin/mail && exec ${MAKE} distribution
.  if defined(SKIPDIR) && ${SKIPDIR:Mgnu/usr.bin/anoncvs}
	@echo "Warning: skipping anoncvs"
.  else
	cd ../gnu/usr.bin/anoncvs && exec ${MAKE} distribution
.  endif
	${INSTALL} -c -o root -g wheel -m 600 root/root.mail \
		${DESTDIR}/var/mail/root
	${INSTALL} -c -o root -g wheel -m 440 ../usr.bin/sudo/sudoers \
		${DESTDIR}/etc/sudoers
	cd ${DESTDIR}/etc/ssl/certs && ${SHELL} ${.CURDIR}/ssl.certs.shar && \
		chown ${BINOWN}:${BINGRP} * && chmod 444 *
.endif # destdir

snap_md:
# nothing here -- look in the machine-dependent Makefile.inc

MAKEDEVARCHS+= amd64
MAKEDEVARCHS+= i386
MAKEDEVARCHS+= sparc

clean:
	rm -f etc.${MACHINE}/MAKEDEV

cleandir:
	cd ${.CURDIR}; for m in ${MAKEDEVARCHS}; do \
	    ${MAKE} MACHINE=$$m clean; done

MAKEDEVSRC=	MAKEDEV.mi MAKEDEV.sub MAKEDEV.common
MAKEDEVDOC=	MAKEDEV.man MAKEDEV.mansub MAKEDEV.common
m4: etc.${M}/MAKEDEV
man: ${.CURDIR}/../share/man/man8/man8.${M}/MAKEDEV.8

etc.${M}/MAKEDEV: ${MAKEDEVSRC} etc.${M}/MAKEDEV.md
	@echo "==> etc.${M}/MAKEDEV"
	m4 -DMACHINE=${M} MAKEDEV.mi >etc.${M}/.MAKEDEV.tmp && \
	    mv etc.${M}/.MAKEDEV.tmp etc.${M}/MAKEDEV || \
	    rm etc.${M}/.MAKEDEV.tmp

${.CURDIR}/../share/man/man8/man8.${M}/MAKEDEV.8: ${MAKEDEVDOC} etc.${M}/MAKEDEV.md
	m4 -DMACHINE=${M} MAKEDEV.man >$@

allarchs: ${MAKEDEVSRC} ${MAKEDEVDOC}
	cd ${.CURDIR}; for m in ${MAKEDEVARCHS}; do \
	    ${MAKE} M=$$m m4 man; done
	@echo "================================="
	@echo " Don't forget to update your own"
	@echo " '/dev/MAKEDEV' script manually!"
	@echo "================================="

GENERATED_FILES=

.for _i in ${BINMD}
GENERATED_FILES+= ${_i}.generated

.  for _j in etc.${MACHINE}/${_i}.md etc.${MACHINE_ARCH}/${_i}.md ${_i}
.    if exists(${_j})
${_i}.generated: ${_j}
.    endif
.  endfor

${_i}.generated:
	if [ -e ${.CURDIR}/etc.${MACHINE}/${_i}.md ]; then \
		sed -e '/@@MDPART@@/r${.CURDIR}/etc.${MACHINE}/${_i}.md' \
		    -e '//d'; \
	elif [ -e ${.CURDIR}/etc.${MACHINE_ARCH}/${_i}.md ]; then \
		sed -e '/@@MDPART@@/r${.CURDIR}/etc.${MACHINE_ARCH}/${_i}.md' \
		    -e '//d'; \
	else \
		sed -e '/@@MDPART@@/d'; \
	fi <${.CURDIR}/${_i} >$@
.endfor

make-generated: ${GENERATED_FILES}

clean-generated:
	-rm -f ${GENERATED_FILES}

.ifdef DESTDIR
install-generated: make-generated
.  for _i in ${BINMD}
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m 644 \
	    ${_i}.generated ${DESTDIR}/etc/${_i}
.  endfor
.else
install-generated:
	@echo "Set DESTDIR before trying this!"; false
.endif

DHSIZE=	1024 1536 2048 3072 4096
update-moduli:
	{ \
		echo '# $$MirOS: src/etc/Makefile,v 1.20 2006/04/12 11:59:20 tg Exp $$'; \
		echo '# Time Type Tests Tries Size Generator Modulus'; \
		for i in ${DHSIZE}; do \
			ssh-keygen -b $$i -G /dev/stdout; \
		done | ssh-keygen -T /dev/stdout; \
	} >moduli

.PHONY: all clean cleandir depend etc install lint etc-files snap_md \
	clean cleandir m4 man allarchs make-generated clean-generated \
	install-generated update-moduli

.include <bsd.prog.mk>
