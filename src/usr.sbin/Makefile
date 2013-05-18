# $MirOS: src/usr.sbin/Makefile,v 1.11 2005/12/20 18:53:48 tg Exp $
# $OpenBSD: Makefile,v 1.110 2004/05/04 23:27:21 deraadt Exp $

.include <bsd.own.mk>

  SUBDIR+= ac
  SUBDIR+= accton
  SUBDIR+= apm
  SUBDIR+= apmd
  SUBDIR+= arp
# SUBDIR+= authpf
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
  SUBDIR+= faithd
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= fdformat
# SUBDIR+= ftp-proxy
# SUBDIR+= gpioctl
# SUBDIR+= hostapd
# SUBDIR+= hotplugd
  SUBDIR+= httpd
.endif
  SUBDIR+= ifstated
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
  SUBDIR+= tcpdump
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
  SUBDIR+= wsconscfg
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
