/* $MirOS: src/sys/compat/openbsd/compat_openbsd.h,v 1.1.7.1 2005/03/06 16:33:43 tg Exp $ */

/*-
 * Copyright (c) 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#ifndef _COMPAT_OPENBSD_H
#define _COMPAT_OPENBSD_H

#define OPENBSD_CHECK_ALT_EXIST(p, sgp, path) \
    CHECK_ALT_EXIST(p, sgp, openbsd_emul_path, path)

#define  OPENBSD_CHECK_ALT_CREAT(p, sgp, path) \
    CHECK_ALT_CREAT(p, sgp, openbsd_emul_path, path)

extern const char openbsd_emul_path[];

int openbsd_elf_probe(struct proc *, struct exec_package *, char *,
    u_long *, u_int8_t *);
int exec_openbsd_elf32_makecmds(struct proc *, struct exec_package *);

#endif /* ndef _COMPAT_OPENBSD_H */
