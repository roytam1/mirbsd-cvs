/* $MirOS: src/usr.bin/ssh/version.h,v 1.22 2006/09/24 17:48:35 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.47 2006/08/30 00:14:37 djm Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.4"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-09uA2"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
