/**	$MirOS: src/sys/arch/i386/stand/libsa/cmd_i386.c,v 1.24 2009/01/11 13:36:05 tg Exp $	*/
/*	$OpenBSD: cmd_i386.c,v 1.29 2006/09/18 21:14:15 mpf Exp $	*/

/*
 * Copyright (c) 1997-1999 Michael Shalayeff
 * Copyright (c) 1997 Tobias Weingartner
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
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <sys/param.h>
#include <sys/reboot.h>
#include <machine/biosvar.h>
#include <sys/disklabel.h>
#include "disk.h"
#include "debug.h"
#include "biosdev.h"
#include "libsa.h"
#include <cmd.h>


extern const char version[];
extern int i386_flag_oldbios;

#ifndef SMALL_BOOT
int Xboot(void);
int Xdiskinfo(void);
int Xlabel(void);
int Xmdexec(void);
#endif
int Xmemory(void);
#ifndef SMALL_BOOT
int Xregs(void);
#endif
int Xoldbios(void);

/* From gidt.S */
__dead void bootbuf(void *codebuf, uint32_t codesize, uint32_t code_esdi,
    int dl, uint32_t initial_csip);

const struct cmd_table cmd_machine[] = {
#ifndef SMALL_BOOT
	{ "boot",	CMDT_CMD, Xboot },
	{ "diskinfo",	CMDT_CMD, Xdiskinfo },
	{ "exec",	CMDT_CMD, Xmdexec },
	{ "label",	CMDT_CMD, Xlabel },
#endif
	{ "memory",	CMDT_CMD, Xmemory },
#ifndef SMALL_BOOT
#ifdef DEBUG
	{ "regs",	CMDT_CMD, Xregs },
#endif
#endif
	{ "oldbios",	CMDT_CMD, Xoldbios },
	{ NULL, 0, NULL }
};

#ifndef SMALL_BOOT
int
Xdiskinfo(void)
{
	dump_diskinfo();
	return 0;
}

int
Xlabel(void)
{
	char *dname = cmd.bootdev;
	struct diskinfo *dip;
	int d = 0;

	if (cmd.argc > 2) {
		printf("machine label [{cd,fd,hd}<0123>]\n");
		return (0);
	} else if (cmd.argc == 2)
		dname = cmd.argv[1];

	if ((dname[0] != 'c' && dname[0] != 'f' && dname[0] != 'h') ||
	    dname[1] != 'd' || dname[2] < '0' || dname[2] > '9') {
		printf("Invalid device!\n");
		return (0);
	}

	for (dip = TAILQ_FIRST(&disklist); dip; dip = TAILQ_NEXT(dip, list))
		if (!strncmp(dip->name, dname, 3))
			break;
	if (!dip) {
		printf("Device for %cd%c not found\n", dname[0], dname[2]);
		return (0);
	}
	printf("Disklabel for device %x (%cd%c): ", dip->bios_info.bios_number,
	    dname[0], dname[2]);
	if ((dip->bios_info.flags & BDI_BADLABEL) &&
	    (d = disk_trylabel(dip)))
		return (0);
	putchar('\n');
	for (d = 0; d < dip->disklabel.d_npartitions; ++d)
		if (dip->disklabel.d_partitions[d].p_fstype ||
		    dip->disklabel.d_partitions[d].p_size ||
		    dip->disklabel.d_partitions[d].p_offset)
			printf("%c (%u): %u @ %u\n", 'a' + d,
			    dip->disklabel.d_partitions[d].p_fstype,
			    dip->disklabel.d_partitions[d].p_size,
			    dip->disklabel.d_partitions[d].p_offset);
	return (0);
}

#ifdef DEBUG
int
Xregs(void)
{
	DUMP_REGS;
	return 0;
}
#endif

int
Xboot(void)
{
	int dev, part, st;
	bios_diskinfo_t *bd = NULL;
	char *buf;
	uint32_t baddr;
	struct diskinfo *dip;

	if (cmd.argc != 2) {
		printf("machine boot {cd,fd,hd}<0123>[abcd]\n");
		printf("Where [0123] is the disk number,"
		    " and [abcd] is the partition.\n");
		return 0;
	}

	/* Check arg */
	if (cmd.argv[1][0] != 'f' && cmd.argv[1][0] != 'h')
		goto bad;
	if (cmd.argv[1][1] != 'd')
		goto bad;
	if (cmd.argv[1][2] < '0' || cmd.argv[1][2] > '3')
		goto bad;
	if ((cmd.argv[1][3] < 'a' || cmd.argv[1][3] > 'd') &&
	    cmd.argv[1][3] != '\0')
		goto bad;

	printf("Booting from %s ", cmd.argv[1]);

	for (dip = TAILQ_FIRST(&disklist); dip; dip = TAILQ_NEXT(dip, list))
		if (!strncmp(cmd.argv[1], dip->name, 3))
			break;
	if (!dip)
		goto bad;

	dev = dip->bios_info.bios_number;
	part = (cmd.argv[1][3] - 'a');

	if (part >= 0)
		printf("[%x,%d]\n", dev, part);
	else
		printf("[%x]\n", dev);

	/* get a paragraph-aligned buffer */
	buf = alloc(DEV_BSIZE + 16);
	baddr = (intptr_t)buf;
	baddr = (baddr + 15) & ~15;
	buf = (void *)((intptr_t)baddr);

	/* Read boot sector from device */
	bd = &dip->bios_info;
	st = biosd_io(F_READ, bd, 0, 1, buf);
	if (st)
		goto bad;

	if (part < 0) {
		/* boot whole sector; just zero bootpart */
		bzero(&bios_bootpte, 16);
	} else {
		memcpy(&bios_bootpte, buf + DOSPARTOFF + part * 16, 16);
		if ((st = biosd_io(F_READ, bd, bios_bootpte.p_ofs, 1, buf)))
			goto bad;
	}

	/* Load %dl, ljmp */
	baddr = 0x00007C00;
	gateA20(0);
	bootbuf(buf, 512, baddr, dev, baddr);

bad:
	printf("Invalid device!\n");
	return 0;
}
#endif

int
Xmemory(void)
{
	if (cmd.argc >= 2) {
		int i;
		/* parse the memory specs */

		for (i = 1; i < cmd.argc; i++) {
			char *p;
			long long addr, size;

			p = cmd.argv[i];

			size = strtoll(p + 1, &p, 0);
			if (*p && *p == '@')
				addr = strtoll(p + 1, NULL, 0);
			else
				addr = 0;
			if (addr == 0 && (*p != '@' || size == 0)) {
				printf("bad language\n");
				return 0;
			} else {
				switch (cmd.argv[i][0]) {
				case '-':
					mem_delete(addr, addr + size);
					break;
				case '+':
					mem_add(addr, addr + size);
					break;
				default :
					printf("bad OP\n");
					return 0;
				}
			}
		}
	}

	dump_biosmem(NULL);

	return 0;
}

int
Xoldbios(void)
{
#ifndef SMALL_BOOT
	printf("Old BIOS / Soekris helper now turned: ");
#endif
	if (i386_flag_oldbios) {
#ifndef SMALL_BOOT
		printf("OFF\n");
#endif
		i386_flag_oldbios = 0;
	} else {
#ifndef SMALL_BOOT
		printf("ON\n");
#endif
		i386_flag_oldbios = 1;
	}
#ifdef SMALL_BOOT
	printf("%d\n", i386_flag_oldbios);
#endif

	return 0;
}

#ifndef SMALL_BOOT
int
Xmdexec(void)
{
	int fd, sz, type = 0;
	char *buf;
	uint32_t baddr, jaddr = 0xF000FFF0;
	struct stat sb;

	if (cmd.argc != 3) {
 synerr:
		printf("machine exec <type> <file>\n");
		printf("	types: grub sector\n");
		return (0);
	}

	if (!strcmp(cmd.argv[1], "sector")) {
		type = 1;
		sz = 65520;
	} else if (!strcmp(cmd.argv[1], "grub")) {
		type = 2;
		sz = 163840;
	} else
		goto synerr;

	if ((fd = open(qualify(cmd.argv[2]), 0)) < 0) {
		printf("open(%s): %s\n", cmd.argv[2], strerror(errno));
		return (0);
	}

	sb.st_size = 0;
	if (fstat(fd, &sb) < 0 || sb.st_size <= 0)
		printf("cannot stat %s, assuming %d bytes\n", cmd.argv[2], sz);
	else {
		printf("allocating %d bytes for %s (fallback was %d bytes)\n",
		    (int)sb.st_size, cmd.argv[2], sz);
		sz = (int)sb.st_size;
	}

	buf = alloc(sz + 15);
	baddr = (intptr_t)buf;
	baddr = (baddr + 15) & ~15;
	buf = (void *)((intptr_t)baddr);

	if ((sz = read(fd, buf, sz)) < 0) {
		printf("read error\n");
		close(fd);
		return(0);
	}

	close(fd);
	printf("Loaded %d bytes for %s %s\n", sz, cmd.argv[1], cmd.argv[2]);

	switch (type) {
	case 1:
		baddr = 0x07C00000;
		jaddr = 0x00007C00;
		break;
	case 2:
		baddr = 0x08000000;
		jaddr = 0x00008200;
		break;
	}

	gateA20(0);
	bootbuf(buf, sz, baddr, i386_biosdev, jaddr);
}
#endif
