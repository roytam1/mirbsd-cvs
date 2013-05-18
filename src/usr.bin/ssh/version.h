/* $MirOS: src/usr.bin/ssh/version.h,v 1.9 2005/11/23 18:04:23 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.45 2005/08/31 09:28:42 markus Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.2"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-08n3A"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
