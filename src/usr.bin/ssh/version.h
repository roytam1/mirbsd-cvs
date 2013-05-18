/* $MirOS: src/usr.bin/ssh/version.h,v 1.42 2008/12/16 22:13:33 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.55 2009/02/23 00:06:15 djm Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_5.2"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-0AuA7"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
