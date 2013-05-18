/* $MirOS: src/usr.bin/ssh/version.h,v 1.18 2006/06/16 23:47:10 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.46 2006/02/01 11:27:22 markus Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.3"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-09r80"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
