/* $MirOS: src/sys/arch/i386/i386/powernow-k7.c,v 1.9 2006/06/15 19:18:51 tg Exp $ */
/* $OpenBSD: powernow-k7.c,v 1.3 2004/08/05 04:56:05 tedu Exp $ */

#ifndef SMALL_KERNEL

/* #define K7PN_DEBUG */

/*-
 * Copyright (c) 2005 Thorsten "mirabilos" Glaser <tg@MirBSD.de>
 * Copyright (c) 2004 Martin "deadbug" Végiard <deadbug@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
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

/* AMD POWERNOW(tm) K7 driver */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/sysctl.h>
#include <sys/device.h>

#include <dev/isa/isareg.h>

#include <machine/cpu.h>
#include <machine/bus.h>

#define BIOS_START		0xC0000
#define	BIOS_LEN		0x40000

#define MSR_K7_CTL		0xC0010041
#define CTL_SET_FID		0x0000000000010000ULL
#define CTL_SET_VID		0x0000000000020000ULL

struct psb_s {
	char signature[10];	/* AMDK7PNOW! */
	uint8_t version;
	uint8_t flags;
	uint16_t ttime;		/* Min Settling time */
	uint8_t reserved;
	uint8_t n_pst;		/* number of PSTs */
};

struct pst_s {
	uint32_t signature;	/* CPU ID */
	uint8_t fsb;		/* Front Side Bus frequency (Mhz) */
	uint8_t fid;		/* Max Frequency code */
	uint8_t vid;		/* Max Voltage code */
	uint8_t n_states;	/* Number of states */
};

struct state_s {
	uint8_t fid;		/* Frequency code */
	uint8_t vid;		/* Voltage code */
};

/* Taken from powernow-k7.c/Linux by Dave Jones */
static int fid_codes[32] = {
	110, 115, 120, 125, 50, 55, 60, 65,
	70, 75, 80, 85, 90, 95, 100, 105,
	30, 190, 40, 200, 130, 135, 140, 210,
	150, 225, 160, 165, 170, 180, -1, -1
};

static unsigned int k7pnow_fsb;
unsigned int k7pnow_ttime;
unsigned int k7pnow_nstates;
int k7pnow_state = -1;
struct k7pnow_freq_table_s {
	unsigned int frequency;
	struct state_s state;
} *k7pnow_freq_table;

static char *k7pnow_biosmem;
static struct psb_s *psb;

static int powernowhack_match(struct device *, void *, void *);
static void powernowhack_attach(struct device *, struct device *, void *);

struct cfattach powernowhack_ca = {
	sizeof(struct device), powernowhack_match, powernowhack_attach
};

struct cfdriver powernowhack_cd = {
	NULL, "powernowhack", DV_DULL
};


void
k7_powernow_init(void)
{
#ifdef K7PN_DEBUG
	printf("k7_powernow_init: called\n");
#endif
	k7pnow_state = -2;
}

static int
powernowhack_match(struct device *parent, void *match, void *aux)
{
	bus_space_handle_t bh;
	const char *ptr;
	unsigned i;

	if (__predict_false(aux == NULL))
		return 0;
	if (__predict_true(strcmp((ptr = *(char **)aux), "powernowhack")))
		return 0;

	if (k7pnow_state == -1) {
#ifdef K7PN_DEBUG
		printf("powernowhack_match: not attaching\n");
#endif
		return 0;
	} else if (k7pnow_state != -2) {
		printf("powernowhack_match: already attached\n");
		return 0;
	}
	k7pnow_state = -3;

	/* Look in the 0xE000 : 0xFFFF range for PST tables */
	if (bus_space_map(I386_BUS_SPACE_MEM, BIOS_START,
	    BIOS_LEN, 0, &bh)) {
		printf("powernowhack_match: couldn't map BIOS\n");
		return 0;
	}
	k7pnow_biosmem = malloc(BIOS_LEN, M_DEVBUF, M_NOWAIT);
	memcpy(k7pnow_biosmem, (void *)bh, BIOS_LEN);
	bus_space_unmap(I386_BUS_SPACE_MEM, bh, BIOS_LEN);

	ptr = k7pnow_biosmem;
	for (i = 0; i < BIOS_LEN; i += 16, ptr += 16)
		if (__predict_false(!memcmp(ptr, "AMDK7PNOW!", 10))) {
			psb = (struct psb_s *)ptr;
			k7pnow_ttime = psb->ttime;

			/* Only this version is supported */
			if (psb->version == 0x12)
				return 1;
		}

	psb = NULL;
	free(k7pnow_biosmem, M_DEVBUF);
	k7pnow_biosmem = NULL;
	return 0;
}

static int
k7pnow_dump(int i, struct pst_s *pst)
{
	printf("PST #%03X: CPUID %08X, FSB %d MHz, Max Freq %d MHz\n", i,
	    pst->signature, pst->fsb, pst->fsb * fid_codes[pst->fid] / 10);
	return 0;
}

static int
k7pnow_cpuid(int i, struct pst_s *pst)
{
	extern int cpu_id;

	return (pst->signature == cpu_id);
}

static int
k7pnow_bynumber(int i, struct pst_s *pst)
{
	return (i == k7pnow_state);
}

static struct state_s *
k7pnow_iter(int (*fn)(int, struct pst_s *))
{
	char *ptr = (char *)psb;
	struct pst_s *pst;
	int num;

	ptr += sizeof(struct psb_s);
	/* Find the right PST */
	for (num = 1; num <= psb->n_pst; ++num) {
		pst = (struct pst_s *)ptr;
		ptr += sizeof(struct pst_s);

		if ((*fn)(num, pst)) {
			k7pnow_fsb = pst->fsb;
			k7pnow_nstates = pst->n_states;
			return (struct state_s *)ptr;
		}
		ptr += sizeof(struct state_s) * pst->n_states;
	}
	return NULL;
}

static void
powernowhack_attach(struct device *parent, struct device *self, void *aux)
{
	extern int cpu_id;
	struct state_s *s;
	unsigned i, j;

	printf("\n");
	if (k7pnow_state != -3) {
		printf("powernowhack_attach: not matched %d\n", k7pnow_state);
		goto out;
	}

	if ((self->dv_cfdata->cf_flags & 0x4000) == 0x4000) {
		printf("powernowhack0: these PSTs are known\n");
		k7pnow_iter(k7pnow_dump);
		if ((self->dv_cfdata->cf_flags & 0x0FFF) == 0x0FFF)
			printf("powernowhack0: need PST matching"
			    " CPUID %08X\n", cpu_id);
	}

	if ((self->dv_cfdata->cf_flags & 0x8000) == 0)
		if ((s = k7pnow_iter(k7pnow_cpuid)) != NULL)
			goto found;

	if ((self->dv_cfdata->cf_flags & 0x0FFF) == 0)
		printf("powernowhack0: cannot find PST matching"
		    " CPUID %08X\n", cpu_id);

	if ((self->dv_cfdata->cf_flags & 0x0FFF) == 0x0FFF) {
		printf("powernowhack0: manual mode disabled by user"
		    " (flags 0xnFFF)\n");
		goto out;
	}

	if ((self->dv_cfdata->cf_flags & 0x4FFF) == 0) {
		printf("powernowhack0: tried these PSTs\n");
		k7pnow_iter(k7pnow_dump);
	}

	k7pnow_state = self->dv_cfdata->cf_flags & 0x0FFF;
	if (k7pnow_state == 0) {
		printf("powernowhack0: use flags 0x0nnn to select"
		    " correct PST, trying to use #001\n");
		k7pnow_state = 1;
	}

	if ((s = k7pnow_iter(k7pnow_bynumber)) != NULL)
		goto found;
	printf("powernowhack0: PST #%03X unavailable\n", k7pnow_state);
	goto out;

found:
	/* poor C has no push/pop */
	{
		register struct state_s *s2 = s;
		for (i = 0, j = 0; i < k7pnow_nstates; ++i, ++s2)
			if (__predict_true((s2->fid != 0) && (s2->vid != 0)))
				++j;
	}

	if (j == 0) {
		printf("powernowhack0: %d states, none available\n", i);
		goto out;
	}
	printf("cpu0: AMD K7 POWERNOW: %d states, %d available\n", i, j);
	k7pnow_nstates = j;

	k7pnow_freq_table = malloc(sizeof(struct k7pnow_freq_table_s) * j,
	    M_DEVBUF, M_WAITOK);

	for (i = 0; i < j; ++i) {
		while (__predict_false((s->fid == 0) || (s->vid == 0)))
			++s;
		k7pnow_freq_table[i].frequency = k7pnow_fsb
		    * fid_codes[s->fid] / 10;
		k7pnow_freq_table[i].state.fid = s->fid;
		k7pnow_freq_table[i].state.vid = s->vid;
		++s;
	}

	/* On bootup the frequency should be at its maximum */
	k7pnow_state = j - 1;

#ifdef K7PN_DEBUG
	for (i = 0; i < j; i++) {
		printf("\tstate %d\tFrequency %d\tFID %d, VID %d\n", i,
		    k7pnow_freq_table[i].frequency,
		    k7pnow_freq_table[i].state.fid,
		    k7pnow_freq_table[i].state.vid);
	}
#else
	j = 0;
	for (i = 0; i < k7pnow_nstates; i++) {
		if (j) {
			printf(", ");
		} else {
			printf("powernowhack0: frequencies available: ");
			++j;
		}
		printf("%d", k7pnow_freq_table[i].frequency);
	}
	printf(".\n");
#endif
	cpu_setperf = k7_powernow_setperf;

out:
	k7pnow_state = -4;
	free(k7pnow_biosmem, M_DEVBUF);
	k7pnow_biosmem = NULL;
	return;
}

int
k7_powernow_setperf(int level)
{
	unsigned int low, high, freq, i;
	uint32_t sgtc, vid = 0, fid = 0;
	uint64_t ctl;

	high = k7pnow_freq_table[k7pnow_nstates - 1].frequency;
	low = k7pnow_freq_table[0].frequency;
	freq = low + (high - low) * level / 100;

#ifdef K7PN_DEBUG
	printf("powernowhack0: setperf: level=%d, freq=%d\n", level, freq);
#endif

	for (i = 0; i < k7pnow_nstates; i++)
		/* Do we know how to set that frequency? */
		if (__predict_false(k7pnow_freq_table[i].frequency >= freq))
			break;
	fid = k7pnow_freq_table[i].state.fid;
	vid = k7pnow_freq_table[i].state.vid;

#ifdef K7PN_DEBUG
	printf("powernowhack0: found @%d freq %d: fid %d, vid %d\n",
	    i, k7pnow_freq_table[i].frequency, fid, vid);
#endif

	/* Already set? */
	if (k7pnow_state == i) {
#ifdef K7PN_DEBUG
		printf("powernowhack0: leaving state %d unchanged\n", i);
#endif
		return 0;
	}
#ifdef K7PN_DEBUG
	printf("powernowhack0: setting new state %d (old state %d)\n",
	    i, k7pnow_state);
#endif

	/* Get CTL and only modify fid/vid/sgtc */
	ctl = rdmsr(MSR_K7_CTL);

	/* FID */
	ctl &= 0xFFFFFFFFFFFFFF00ULL;
	ctl |= fid;

	/* VID */
	ctl &= 0xFFFFFFFFFFFF00FFULL;
	ctl |= vid << 8;

	/* SGTC */
	if ((sgtc = k7pnow_ttime * 100) < 10000) sgtc = 10000;
	ctl &= 0xFFF00000FFFFFFFFULL;
	ctl |= (uint64_t)sgtc << 32;

	if (k7pnow_freq_table[k7pnow_state].frequency > freq) {
		wrmsr(MSR_K7_CTL, ctl | CTL_SET_FID);
		wrmsr(MSR_K7_CTL, ctl | CTL_SET_VID);
	} else {
		wrmsr(MSR_K7_CTL, ctl | CTL_SET_VID);
		wrmsr(MSR_K7_CTL, ctl | CTL_SET_FID);
	}
	ctl = rdmsr(MSR_K7_CTL);
	k7pnow_state = i;

	return 0;
}
#endif /* !SMALL_KERNEL */