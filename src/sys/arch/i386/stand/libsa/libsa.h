/*	$MirOS: src/sys/arch/i386/stand/libsa/libsa.h,v 1.8 2009/08/11 13:23:59 tg Exp $ */
/*	$OpenBSD: libsa.h,v 1.44 2007/04/27 10:08:34 tom Exp $	*/

/*
 * Copyright (c) 1996-1999 Michael Shalayeff
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR OR HIS RELATIVES BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF MIND, USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef	_I386_STAND_LIBSA_H
#define	_I386_STAND_LIBSA_H

#include <lib/libsa/stand.h>
#include <machine/biosvar.h>

#define	EXEC_ELF

#define	DEFAULT_KERNEL_ADDRESS	0

#define VTOPSEG(vaddr)	(((uint32_t)vaddr) >> 4)
#define VTOPOFF(vaddr)	(((uint32_t)vaddr) & 15)
#define PTOV(seg,ofs)	((void *)((((uint32_t)seg) << 4) + ((uint32_t)ofs)))

struct i386_boot_probes {
	char *name;
	void (**probes)(void);
	int count;
};

extern struct devsw_prefix_match {
	struct devsw *devops;
	struct fs_ops *fsops;
	char prefix[5];
	char networked;		/* pass bootmac */
	char strip;		/* strip prefix from file */
} devsw_match[];

extern uint8_t bounce_buf[4096];

extern void (*sa_cleanup)(void);

void gateA20(int);
void gateA20on(void);

void cpuprobe(void);
void smpprobe(void);
void ps2probe(void);
void pciprobe(void);
void memprobe(void);
void diskprobe(void);
void apmprobe(void);
void apmfixmem(void);
void dump_biosmem(bios_memmap_t *);
int mem_add(long long, long long);
int mem_delete(long long, long long);
void mem_pass(void);

void devboot(dev_t, char *);
void machdep(void);

void *getSYSCONFaddr(void);
void *getEBDAaddr(void);

extern const char bdevs[][4];
extern const int nbdevs;
extern u_int cnvmem, extmem; /* XXX global pass memprobe()->machdep_start() */
extern int ps2model;

extern struct {
	uint8_t active;
	uint8_t beg_DH;
	uint8_t beg_CL;
	uint8_t beg_CH;
	uint8_t partyp;
	uint8_t end_DH;
	uint8_t end_CL;
	uint8_t end_CH;
	uint32_t p_ofs;
	uint32_t p_siz;
} bios_bootpte;
extern uint8_t i386_userpt;
extern uint8_t i386_biosdev;
extern uint8_t i386_biosflags;
extern uint8_t i386_dosdev;

extern struct i386_boot_probes probe_list[];
extern int nibprobes;
extern void (*devboot_p)(dev_t, char *);

/* diskprobe.c */
extern bios_diskinfo_t bios_diskinfo[];
extern u_int32_t bios_cksumlen;

#define MACHINE_CMD	cmd_machine /* we have i386-specific commands */

#define CHECK_SKIP_CONF	check_skip_conf	/* we can skip boot.conf with Ctrl */
extern int check_skip_conf(void);

#endif
