/* $MirOS: src/usr.bin/ssh/version.h,v 1.2 2005/03/13 18:33:33 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.44 2005/03/16 21:17:39 markus Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.1"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-08n26"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
