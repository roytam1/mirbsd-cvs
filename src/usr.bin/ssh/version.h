/* $MirOS: src/usr.bin/ssh/version.h,v 1.7 2005/05/05 00:34:28 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.44 2005/03/16 21:17:39 markus Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.1"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-08n32"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
