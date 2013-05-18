/* $MirOS: src/usr.bin/ssh/version.h,v 1.39 2007/09/13 13:52:57 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.53 2008/04/03 09:50:14 djm Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_5.0"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-0AuA0"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
