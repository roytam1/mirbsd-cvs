# $MirOS: src/sbin/Makefile,v 1.11 2006/06/16 23:35:36 tg Exp $

.include <bsd.own.mk>

.if ${MACHINE} == "i386"
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
.if ${MACHINE} == "i386"
  SUBDIR+= fdisk
.endif
  SUBDIR+= ffsinfo
  SUBDIR+= fsck
  SUBDIR+= fsck_ext2fs
  SUBDIR+= fsck_ffs
  SUBDIR+= fsck_msdos
  SUBDIR+= fsdb
  SUBDIR+= growfs
  SUBDIR+= ifconfig
  SUBDIR+= init
.if ${MACHINE} == "i386"
  SUBDIR+= iopctl
.endif
# SUBDIR+= ipsecctl
  SUBDIR+= isakmpd
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
.if ${MACHINE} == "i386"
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
