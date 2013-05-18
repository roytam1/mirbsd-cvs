# $MirOS: src/sbin/Makefile,v 1.6 2005/07/01 12:05:17 tg Exp $

.include <bsd.own.mk>

.if (${MACHINE} == "amd64") || (${MACHINE} == "i386")
  SUBDIR+= ancontrol
.endif
  SUBDIR+= atactl
  SUBDIR+= badsect
# SUBDIR+= bioctl
  SUBDIR+= brconfig
  SUBDIR+= ccdconfig
  SUBDIR+= clri
  SUBDIR+= dhclient
  SUBDIR+= disklabel
  SUBDIR+= dmesg
  SUBDIR+= dump
  SUBDIR+= dumpfs
  SUBDIR+= fdisk
  SUBDIR+= ffsinfo
  SUBDIR+= fsck
  SUBDIR+= fsck_ext2fs
  SUBDIR+= fsck_ffs
  SUBDIR+= fsck_msdos
  SUBDIR+= fsdb
  SUBDIR+= growfs
  SUBDIR+= ifconfig
  SUBDIR+= init
.if (${MACHINE} == "amd64") || (${MACHINE} == "i386")
  SUBDIR+= iopctl
.endif
  SUBDIR+= ipsecadm
  SUBDIR+= ipsecctl
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= isakmpd
.endif
  SUBDIR+= kbd
  SUBDIR+= lmccontrol
  SUBDIR+= mknod
  SUBDIR+= modload
  SUBDIR+= modunload
  SUBDIR+= mount
  SUBDIR+= mount_cd9660
  SUBDIR+= mount_ext2fs
  SUBDIR+= mount_fdesc
  SUBDIR+= mount_ffs
  SUBDIR+= mount_kernfs
  SUBDIR+= mount_msdos
  SUBDIR+= mount_nfs
.if (${MACHINE} == "amd64") || (${MACHINE} == "i386")
  SUBDIR+= mount_ntfs
.endif
  SUBDIR+= mount_portal
  SUBDIR+= mount_procfs
  SUBDIR+= mountd
  SUBDIR+= ncheck_ffs
  SUBDIR+= newfs
  SUBDIR+= newfs_msdos
  SUBDIR+= nfsd
  SUBDIR+= nologin
  SUBDIR+= pfctl
  SUBDIR+= pflogd
  SUBDIR+= ping
  SUBDIR+= ping6
  SUBDIR+= quotacheck
  SUBDIR+= raidctl
  SUBDIR+= reboot
  SUBDIR+= restore
  SUBDIR+= route
  SUBDIR+= routed
  SUBDIR+= rtsol
  SUBDIR+= savecore
  SUBDIR+= scan_ffs
  SUBDIR+= scsi
  SUBDIR+= shutdown
  SUBDIR+= slattach
  SUBDIR+= swapctl
  SUBDIR+= sysctl
  SUBDIR+= ttyflags
  SUBDIR+= tunefs
  SUBDIR+= umount
  SUBDIR+= wicontrol
  SUBDIR+= wsconsctl

.include <bsd.subdir.mk>
