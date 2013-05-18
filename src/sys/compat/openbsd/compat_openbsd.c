/**	$MirOS: src/sys/compat/openbsd/compat_openbsd.c,v 1.2 2006/06/12 20:35:54 tg Exp $ */
/* 	$OpenBSD: compat_aout.c,v 1.1 2003/06/24 22:45:33 espie Exp $ */

/*
 * Copyright (c) 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * Copyright (c) 2003 Marc Espie
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/syscall.h>
#include <sys/signalvar.h>
#include <sys/mount.h>
#include <sys/fcntl.h>
#include <sys/exec.h>
#include <sys/exec_olf.h>
#include <sys/malloc.h>
#include <compat/common/compat_util.h>
#include <compat/openbsd/compat_openbsd.h>
#include <compat/openbsd/openbsd_syscall.h>
#include <compat/openbsd/openbsd_syscallargs.h>

void openbsd_compat_setup(struct exec_package *epp);

extern char sigcode[], esigcode[];
extern struct sysent openbsd_sysent[];
#ifdef SYSCALL_DEBUG
extern char *openbsd_syscallnames[];
#endif

struct emul emul_openbsd_aout = {
	"openbsd",
	NULL,
	sendsig,
	OPENBSD_SYS_syscall,
	OPENBSD_SYS_MAXSYSCALL,
	openbsd_sysent,
#ifdef SYSCALL_DEBUG
	openbsd_syscallnames,
#else
	NULL,
#endif
	0,
	copyargs,
	setregs,
	NULL,
	sigcode,
	esigcode,
};

struct emul emul_openbsd = {
	"openbsd",
	NULL,
	sendsig,
	OPENBSD_SYS_syscall,
	OPENBSD_SYS_MAXSYSCALL,
	openbsd_sysent,
#ifdef SYSCALL_DEBUG
	openbsd_syscallnames,
#else
	NULL,
#endif
	sizeof(AuxInfo) * ELF_AUX_ENTRIES,
	elf32_copyargs,
	setregs,
	exec_elf32_fixup,
	sigcode,
	esigcode,
};

const char openbsd_emul_path[] = "/emul/openbsd";

void
openbsd_compat_setup(struct exec_package *epp)
{
	epp->ep_emul = &emul_openbsd;
}

int
exec_openbsd_elf32_makecmds(struct proc *p, struct exec_package *epp)
{
	if (!(emul_openbsd.e_flags & EMUL_ENABLED))
		return (ENOEXEC);
	return exec_elf32_makecmds(p, epp);
}

int
openbsd_elf_probe(struct proc *p, struct exec_package *epp,
    char *itp, u_long *pos, u_int8_t *os)
{
	char *bp;
	int error;
	size_t len;

	if (!elf32_os_pt_note(p, epp, epp->ep_hdr, "MirOS OpenBSD", 14, 4))
		goto emulated;

	if (!elf32_os_pt_note(p, epp, epp->ep_hdr, "OpenBSD", 8, 4))
		goto emulated;

	return ENOEXEC;

emulated:
	if (itp[0]) {
		if ((error = emul_find(p, NULL, openbsd_emul_path, itp, &bp, 0)))
			return (error);
		if ((error = copystr(bp, itp, MAXPATHLEN, &len)))
			return (error);
		free(bp, M_TEMP);
	}
	epp->ep_emul = &emul_openbsd;
	*pos = ELF32_NO_ADDR;
	if (*os == OOS_NULL)
		*os = OOS_OPENBSD;
	return (0);
}

#include <sys/sysctl.h>

int
openbsd_sys___sysctl(struct proc *p, void *v, register_t *retval)
{
	extern int sys___sysctl(struct proc *, void *, register_t *);
	struct openbsd_sys___sysctl_args /* {
		syscallarg(int *) name;
		syscallarg(u_int) namelen;
		syscallarg(void *) old;
		syscallarg(size_t *) oldlenp;
		syscallarg(void *) new;
		syscallarg(size_t) newlen;
	} */ *uap = v;
	struct sys___sysctl_args {
		syscallarg(int *) name;
		syscallarg(u_int) namelen;
		syscallarg(void *) old;
		syscallarg(size_t *) oldlenp;
		syscallarg(void *) new;
		syscallarg(size_t) newlen;
	} bap;
	int error;
	int name[CTL_MAXNAME], *namep;
	caddr_t sg;

	if (SCARG(uap, new) != NULL &&
	    (error = suser(p, 0)))
		return (error);
	/*
	 * all top-level sysctl names are non-terminal
	 */
	if (SCARG(uap, namelen) > CTL_MAXNAME || SCARG(uap, namelen) < 2)
		return EINVAL;
	if ((error = copyin(SCARG(uap, name), name,
	    SCARG(uap, namelen) * sizeof(int))))
		return error;

	sg = stackgap_init(p->p_emul);
	namep = stackgap_alloc(&sg, sizeof(name));

	/*
	 * XXX Translation OpenBSD -> MirOS sysctl numbers
	 */
	if ((name[0] == CTL_KERN) && (name[1] == KERN_OSTYPE)
	    && (SCARG(uap, new) == NULL)) {
		name[1] = KERN_EMULUNAME;
	}

	if ((error = copyout(name, namep, sizeof(name))))
		return error;

	SCARG(&bap, name) = namep;
	SCARG(&bap, namelen) = SCARG(uap, namelen);
	SCARG(&bap, old) = SCARG(uap, old);
	SCARG(&bap, oldlenp) = SCARG(uap, oldlenp);
	SCARG(&bap, new) = SCARG(uap, new);
	SCARG(&bap, newlen) = SCARG(uap, newlen);

	return sys___sysctl(p, &bap, retval);
}
