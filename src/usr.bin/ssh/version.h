/* $MirOS$ */
/* $NetBSD: version.h,v 1.28 2003/04/03 06:21:37 itojun Exp $	*/
/* $OpenBSD: version.h,v 1.42 2004/08/16 08:17:01 markus Exp $ */

#define __OPENSSH_VERSION	"OpenSSH_3.9"

#define __MIRBSDSSH_VERSION	"MirBSD_Secure_Shell-08n23"

/*
 * it is important to retain OpenSSH version identification part, it is
 * used for bug compatibility operation.
 * present MirOS SSH version as comment.
 */
#define SSH_VERSION	(__OPENSSH_VERSION " " __MIRBSDSSH_VERSION)
