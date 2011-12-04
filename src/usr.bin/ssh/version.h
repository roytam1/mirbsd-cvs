/* $MirOS: src/usr.bin/ssh/version.h,v 1.4 2005/04/20 08:01:08 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.44 2005/03/16 21:17:39 markus Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.1"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-08n28"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
