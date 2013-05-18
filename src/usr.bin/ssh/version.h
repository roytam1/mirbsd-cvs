/* $MirOS: src/usr.bin/ssh/version.h,v 1.17 2006/06/02 20:50:53 tg Exp $ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.46 2006/02/01 11:27:22 markus Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_4.3"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-09n11"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
