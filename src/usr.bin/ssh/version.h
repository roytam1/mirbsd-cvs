/* $MirOS: src/usr.bin/ssh/version.h,v 1.26 2006/12/11 20:22:10 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.47 2006/08/30 00:14:37 djm Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.5"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-09uAA"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
