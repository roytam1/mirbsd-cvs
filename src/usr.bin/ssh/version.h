/* $MirOS: src/usr.bin/ssh/version.h,v 1.34 2007/06/27 10:50:43 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.49 2007/03/06 10:13:14 djm Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.6"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-0An1A_PIC"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
