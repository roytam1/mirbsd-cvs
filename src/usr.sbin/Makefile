# $MirOS: src/usr.sbin/Makefile,v 1.24 2008/08/05 22:36:05 tg Exp $
# $OpenBSD: Makefile,v 1.110 2004/05/04 23:27:21 deraadt Exp $

.include <bsd.own.mk>

  SUBDIR+= ac
  SUBDIR+= accton
  SUBDIR+= adduser
.if ${MACHINE_ARCH} == "i386"
  SUBDIR+= apm
  SUBDIR+= apmd
.endif
  SUBDIR+= arp
# SUBDIR+= authpf
  SUBDIR+= bad144
# SUBDIR+= bgpctl
# SUBDIR+= bgpd
  SUBDIR+= chroot
  SUBDIR+= config
  SUBDIR+= cron
  SUBDIR+= dev_mkdb
  SUBDIR+= dhcpd
  SUBDIR+= dhcrelay
  SUBDIR+= edquota
.if ${MACHINE_ARCH} == "sparc"
  SUBDIR+= eeprom
.endif
  SUBDIR+= faithd
  SUBDIR+= fdformat
# SUBDIR+= ftp-proxy
  SUBDIR+= getextent_cd9660
# SUBDIR+= gpioctl
# SUBDIR+= hostapd
# SUBDIR+= hotplugd
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= httpd
.endif
  SUBDIR+= installboot
# SUBDIR+= ifstated
  SUBDIR+= ifwatchd
  SUBDIR+= inetd
  SUBDIR+= iostat
.if ${MACHINE_ARCH} == "i386"
  SUBDIR+= isdn
.endif
  SUBDIR+= kvm_mkdb
  SUBDIR+= lpr
  SUBDIR+= mailwrapper
  SUBDIR+= makefs
  SUBDIR+= map-mbone
  SUBDIR+= memconfig
  SUBDIR+= mrinfo
  SUBDIR+= mrouted
  SUBDIR+= mtrace
  SUBDIR+= mtree
  SUBDIR+= ndp
  SUBDIR+= ntpd
  SUBDIR+= openssl
# SUBDIR+= ospfctl
# SUBDIR+= ospfd
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
# SUBDIR+= sasyncd
  SUBDIR+= sensorsd
  SUBDIR+= sliplogin
  SUBDIR+= slstats
  SUBDIR+= spamdb
  SUBDIR+= spppcontrol
  SUBDIR+= spray
  SUBDIR+= syslogc
  SUBDIR+= syslogd
  SUBDIR+= tcpdrop
  SUBDIR+= timed
  SUBDIR+= tokenadm
  SUBDIR+= tokeninit
  SUBDIR+= traceroute
  SUBDIR+= traceroute6
  SUBDIR+= trpt
# SUBDIR+= upkg
  SUBDIR+= usbdevs
  SUBDIR+= vipw
  SUBDIR+= vnconfig
  SUBDIR+= wake
  SUBDIR+= wsconscfg
  SUBDIR+= wsconfig
.if ${MACHINE_ARCH} == "i386"
  SUBDIR+= wsfontload
.endif
  SUBDIR+= wsmoused
.if ${MACHINE_ARCH} == "i386"
  SUBDIR+= wssetfont
.endif
  SUBDIR+= zdump
  SUBDIR+= zic

.include <bsd.subdir.mk>
