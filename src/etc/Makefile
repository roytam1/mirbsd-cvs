# $MirOS: src/etc/Makefile,v 1.53 2014/06/09 13:49:36 tg Exp $
# $OpenBSD: Makefile,v 1.226 2005/05/26 23:06:06 mcbride Exp $

TZDIR=		/usr/share/zoneinfo
LOCALTIME?=	UTC
NOOBJ=		yes

.include <bsd.own.mk>

# -rw-r--r--
BINOWN=	root
BIN1=	anacron ccd.conf changelist cronrun csh.login daily dhclient.conf \
	dhcpd.conf dhcpd.interfaces etc.${MACHINE}/disktab exports \
	ftpchroot ftpusers gettytab group hosts hosts.lpd \
	locate.rc login.conf \
	mailer.conf man.conf moduli monthly motd mrouted.conf \
	myname netstart networks newsyslog.conf ntpd.conf \
	pf.os phones printcap profile protocols rbootd.conf \
	rc rc.conf rc.local rc.securelevel rc.shutdown remote \
	rpc security sensorsd.conf services shells weekly wsconsctl.conf

# machine dependent parts
BINMD=	make.cfg sysctl.conf syslog.conf

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
SKIPDIR?=	# empty

all clean cleandir depend etc install lint:

.if !defined(DESTDIR) || empty(DESTDIR)
etc-files:
	@echo setenv DESTDIR before trying this!
	@exit 1
.else
etc-files:
	${INSTALL} -c -o ${BINOWN} -g ${CONFGRP} -m 644 ${BIN1} ${DESTDIR}/etc/
	cat fbtab.head etc.${MACHINE}/fbtab fbtab.tail >${DESTDIR}/etc/fbtab
	${SHELL} ${.CURDIR}/ttys.pty ${MACHINE} >${DESTDIR}/etc/ttys.dist
.  for _i in ${BINMD}
	if [ -e ${.CURDIR}/etc.${MACHINE}/${_i}.md ]; then \
		sed -e '/@@MDPART@@/r${.CURDIR}/etc.${MACHINE}/${_i}.md' \
		    -e '//d' ${.CURDIR}/${_i}; \
	else \
		sed -e '/@@MDPART@@/d' ${.CURDIR}/${_i}; \
	fi >${DESTDIR}/etc/${_i}
.  endfor
	cd ${DESTDIR}/etc && \
	    chown ${BINOWN}:${CONFGRP} fbtab ttys.dist ${BINMD} && \
	    chmod 644 fbtab ttys.dist ${BINMD}
	${INSTALL} -c -o ${BINOWN} -g ${CONFGRP} -m 664 ${BIN2} ${DESTDIR}/etc/
	${INSTALL} -c -o root -g wheel -m 600 hosts.equiv ${DESTDIR}/etc/
	${INSTALL} -c -o root -g wheel -m 600 crontab ${DESTDIR}/var/cron/tabs/root
	${INSTALL} -c -o root -g wheel -m 600 master.passwd ${DESTDIR}/etc/
	pwd_mkdb -p -d ${DESTDIR}/etc /etc/master.passwd
	${INSTALL} -c -o root -g ${CONFGRP} -m 640 inetd.conf ${DESTDIR}/etc/
	${INSTALL} -c -o root -g wheel -m 640 pf.conf ${DESTDIR}/etc/
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m 555 \
	    etc.${MACHINE}/MAKEDEV ${DESTDIR}/dev/
	${INSTALL} -c -o root -g wheel -m 600 root.profile ${DESTDIR}/.profile
	cd skel; \
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
	${INSTALL} -c -o ${BINOWN} -g wheel -m 640 /dev/null \
		${DESTDIR}/var/log/sendmail.st
	${INSTALL} -c -o ${BINOWN} -g wheel -m 640 /dev/null \
		${DESTDIR}/var/log/wtmp
	${INSTALL} -c -o daemon -g staff -m 664 /dev/null \
		${DESTDIR}/var/msgs/bounds
	${INSTALL} -c -o ${BINOWN} -g utmp -m 664 /dev/null \
		${DESTDIR}/var/run/utmp
.  if ${SKIPDIR:Mgnu/usr.sbin/sendmail}
	@echo "Warning: skipping sendmail"
.  else
	cd ../gnu/usr.sbin/sendmail/cf/cf && exec ${MAKE} distribution
.  endif
.  for _i in lib/libssl bin/mksh usr.bin/indent usr.bin/mail usr.bin/ssh
	cd ../${_i} && exec ${MAKE} distribution
.  endfor
.  if ${CROSS_MODE:L} != "yes"
.    for _i in usr.sbin/httpd gnu/usr.bin/anoncvs gnu/usr.bin/lynx
.      if ${SKIPDIR:M${_i}}
	@echo "Warning: skipping ${_i}"
.      else
	cd ../${_i}; f=Makefile.bsd-wrapper; [[ -e $$f ]] || f=Makefile; \
	    exec ${MAKE} -f $$f distribution
.      endif
.    endfor
.  endif
	${INSTALL} -c -o root -g wheel -m 440 ../usr.bin/sudo/sudoers \
	    ${DESTDIR}/etc/sudoers
	cd ${DESTDIR}/etc/ssl/certs && ${SHELL} ${.CURDIR}/ssl.certs.shar && \
	    chown ${BINOWN}:${CONFGRP} * && chmod 444 * && \
	    ${SHELL} ${.CURDIR}/ssl.links.shar
	${INSTALL} -c -o ${BINOWN} -g ${CONFGRP} -m 644 spamd.conf \
	    ${DESTDIR}/etc/mail/
	${INSTALL} -c -o ${BINOWN} -g ${CONFGRP} -m 644 ssh_known_hosts \
	    ${DESTDIR}/etc/ssh/
	${INSTALL} -c -o 0 -g 0 -m 644 ssh_root_config \
	    ${DESTDIR}/etc/ssh/root:config
.endif # destdir

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
	${INSTALL} -c -o ${BINOWN} -g ${CONFGRP} -m 644 \
	    ${_i}.generated ${DESTDIR}/etc/${_i}
.  endfor
.else
install-generated:
	@echo "Set DESTDIR before trying this!"; false
.endif

DHSIZE=	2048 3072 4096 5120 6144
update-moduli:
	{ \
		echo '# $$MirSecuCron$$'; \
		echo '# $$MirOS: src/etc/Makefile,v 1.53 2014/06/09 13:49:36 tg Exp $$'; \
		echo '#-'; \
		echo '# Time Type Tests Tries Size Generator Modulus'; \
		for i in ${DHSIZE}; do \
			ssh-keygen -b $$i -G /dev/stdout; \
		done | ssh-keygen -T /dev/stdout; \
	} >moduli

.PHONY: all clean cleandir depend etc install lint etc-files \
	clean cleandir m4 man allarchs make-generated clean-generated \
	install-generated update-moduli

.include <bsd.prog.mk>
