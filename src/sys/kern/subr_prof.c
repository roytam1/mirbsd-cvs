/**	$MirOS$ */
/*	$OpenBSD: subr_prof.c,v 1.14 2003/09/01 18:06:03 henning Exp $	*/
/*	$NetBSD: subr_prof.c,v 1.12 1996/04/22 01:38:50 christos Exp $	*/

/*-
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)subr_prof.c	8.3 (Berkeley) 9/23/93
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/mount.h>
#include <sys/syscallargs.h>

#include <machine/cpu.h>

/*
 * Profiling system call.
 *
 * The scale factor is a fixed point number with 16 bits of fraction, so that
 * 1.0 is represented as 0x10000.  A scale factor of 0 turns off profiling.
 */
/* ARGSUSED */
int
sys_profil(p, v, retval)
	struct proc *p;
	void *v;
	register_t *retval;
{
	register struct sys_profil_args /* {
		syscallarg(caddr_t) samples;
		syscallarg(size_t) size;
		syscallarg(u_long) offset;
		syscallarg(u_int) scale;
	} */ *uap = v;
	register struct uprof *upp;
	int s;

	if (SCARG(uap, scale) > (1 << 16))
		return (EINVAL);
	if (SCARG(uap, scale) == 0) {
		stopprofclock(p);
		return (0);
	}
	upp = &p->p_stats->p_prof;

	/* Block profile interrupts while changing state. */
	s = splstatclock();
	upp->pr_off = SCARG(uap, offset);
	upp->pr_scale = SCARG(uap, scale);
	upp->pr_base = (caddr_t)SCARG(uap, samples);
	upp->pr_size = SCARG(uap, size);
	startprofclock(p);
	splx(s);

	return (0);
}

/*
 * Scale is a fixed-point number with the binary point 16 bits
 * into the value, and is <= 1.0.  pc is at most 32 bits, so the
 * intermediate result is at most 48 bits.
 */
#define	PC_TO_INDEX(pc, prof) \
	((int)(((u_quad_t)((pc) - (prof)->pr_off) * \
	    (u_quad_t)((prof)->pr_scale)) >> 16) & ~1)

/*
 * Collect user-level profiling statistics; called on a profiling tick,
 * when a process is running in user-mode.  This routine may be called
 * from an interrupt context. Schedule an AST that will vector us to
 * trap() with a context in which copyin and copyout will work.
 * Trap will then call addupc_task().
 */
void
addupc_intr(struct proc *p, u_long pc)
{
	struct uprof *prof;

	prof = &p->p_stats->p_prof;
	if (pc < prof->pr_off || PC_TO_INDEX(pc, prof) >= prof->pr_size)
		return;			/* out of range; ignore */

	prof->pr_addr = pc;
	need_proftick(p);
}


/*
 * Much like before, but we can afford to take faults here.  If the
 * update fails, we simply turn off profiling.
 */
void
addupc_task(struct proc *p, u_long pc, u_int nticks)
{
	struct uprof *prof;
	caddr_t addr;
	u_int i;
	u_short v;

	/* Testing P_PROFIL may be unnecessary, but is certainly safe. */
	if ((p->p_flag & P_PROFIL) == 0 || nticks == 0)
		return;

	prof = &p->p_stats->p_prof;
	if (pc < prof->pr_off ||
	    (i = PC_TO_INDEX(pc, prof)) >= prof->pr_size)
		return;

	addr = prof->pr_base + i;
	if (copyin(addr, (caddr_t)&v, sizeof(v)) == 0) {
		v += nticks;
		if (copyout((caddr_t)&v, addr, sizeof(v)) == 0)
			return;
	}
	stopprofclock(p);
}
