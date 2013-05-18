/* $MirOS: src/usr.bin/ssh/version.h,v 1.37 2007/07/07 22:54:31 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.50 2007/08/15 08:16:49 markus Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.7"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-0An80"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
