# $MirOS: src/usr.sbin/Makefile,v 1.4 2005/04/26 22:35:05 tg Exp $
# $OpenBSD: Makefile,v 1.110 2004/05/04 23:27:21 deraadt Exp $

.include <bsd.own.mk>

  SUBDIR+= ac
  SUBDIR+= accton
  SUBDIR+= adduser
  SUBDIR+= apm
  SUBDIR+= apmd
  SUBDIR+= arp
  SUBDIR+= authpf
  SUBDIR+= bad144
# SUBDIR+= bgpctl
# SUBDIR+= bgpd
  SUBDIR+= chroot
  SUBDIR+= config
  SUBDIR+= cron
  SUBDIR+= ctm
  SUBDIR+= dev_mkdb
  SUBDIR+= dhcpd
  SUBDIR+= dhcrelay
  SUBDIR+= edquota
.if ${MACHINE} == "sparc"
  SUBDIR+= eeprom
.endif
  SUBDIR+= extattrctl
  SUBDIR+= faithd
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= fdformat
.endif
  SUBDIR+= getextattr
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= httpd
.endif
  SUBDIR+= ifwatchd
  SUBDIR+= inetd
  SUBDIR+= iostat
.if ${MACHINE} == "i386"
  SUBDIR+= isdn
.endif
  SUBDIR+= kvm_mkdb
  SUBDIR+= lpr
  SUBDIR+= mailwrapper
  SUBDIR+= map-mbone
  SUBDIR+= memconfig
  SUBDIR+= mrinfo
  SUBDIR+= mrouted
  SUBDIR+= mtrace
  SUBDIR+= mtree
  SUBDIR+= ndp
  SUBDIR+= netgroup_mkdb
  SUBDIR+= ntpd
  SUBDIR+= openssl
  SUBDIR+= popa3d
  SUBDIR+= portmap
  SUBDIR+= ppp
  SUBDIR+= pppd
  SUBDIR+= pppoe
  SUBDIR+= procmap
  SUBDIR+= pstat
  SUBDIR+= pwd_mkdb
  SUBDIR+= quot
  SUBDIR+= quotaon
  SUBDIR+= rarpd
  SUBDIR+= rbootd
  SUBDIR+= rdate
  SUBDIR+= rdconfig
  SUBDIR+= repquota
  SUBDIR+= rip6query
  SUBDIR+= rmt
  SUBDIR+= route6d
  SUBDIR+= rpc.bootparamd
  SUBDIR+= rpc.lockd
  SUBDIR+= rtadvd
  SUBDIR+= rtsold
  SUBDIR+= rwhod
  SUBDIR+= sa
  SUBDIR+= sensorsd
  SUBDIR+= sesd
  SUBDIR+= setextattr
  SUBDIR+= sliplogin
  SUBDIR+= slstats
  SUBDIR+= spamdb
  SUBDIR+= spppcontrol
  SUBDIR+= spray
  SUBDIR+= syslogc
  SUBDIR+= syslogd
  SUBDIR+= tcpdrop
  SUBDIR+= tcpdump
  SUBDIR+= timed
  SUBDIR+= tokenadm
  SUBDIR+= tokeninit
  SUBDIR+= traceroute
  SUBDIR+= traceroute6
  SUBDIR+= trpt
  SUBDIR+= usbdevs
  SUBDIR+= user
  SUBDIR+= vipw
  SUBDIR+= vnconfig
  SUBDIR+= wsconscfg
  SUBDIR+= wsfontload
  SUBDIR+= wsmoused
  SUBDIR+= wssetfont
  SUBDIR+= zdump
  SUBDIR+= zic

.include <bsd.subdir.mk>
