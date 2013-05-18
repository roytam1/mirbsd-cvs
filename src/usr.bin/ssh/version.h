/* $MirOS: src/usr.bin/ssh/version.h,v 1.45 2010/09/21 21:24:38 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.56 2009/06/30 14:54:40 markus Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_5.3"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-0AuAE"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
