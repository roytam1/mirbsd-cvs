# $MirOS: src/libexec/Makefile,v 1.7 2007/07/07 20:32:05 tg Exp $

.include <bsd.own.mk>

  SUBDIR+= anoncvssh
  SUBDIR+= cpp
  SUBDIR+= fingerd
  SUBDIR+= ftpd
  SUBDIR+= getty
  SUBDIR+= identd
.if (${OBJECT_FMT:U} == "ELF") && !(defined(NOPIC) && ${NOPIC:L} != "no")
  SUBDIR+= ld.so
.endif
  SUBDIR+= lockspool
  SUBDIR+= login_chpass
  SUBDIR+= login_lchpass
  SUBDIR+= login_passwd
  SUBDIR+= login_radius
  SUBDIR+= login_reject
  SUBDIR+= login_skey
  SUBDIR+= login_token
  SUBDIR+= mail.local
  SUBDIR+= makewhatis
  SUBDIR+= randshuffle
  SUBDIR+= rpc.rquotad
  SUBDIR+= rpc.rstatd
  SUBDIR+= rpc.rusersd
  SUBDIR+= rpc.rwalld
  SUBDIR+= rpc.sprayd
  SUBDIR+= spamd
  SUBDIR+= spamd-setup
  SUBDIR+= spamlogd
  SUBDIR+= talkd
  SUBDIR+= tftpd

.include <bsd.subdir.mk>
