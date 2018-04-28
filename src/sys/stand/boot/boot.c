/**	$MirOS: src/sys/stand/boot/boot.c,v 1.21 2009/10/24 15:39:40 tg Exp $	*/
/*	$OpenBSD: boot.c,v 1.36 2007/06/26 10:34:41 tom Exp $	*/

/*
 * Copyright (c) 2002, 2003, 2004, 2006, 2009, 2018 mirabilos
 * Copyright (c) 2003 Dale Rahn
 * Copyright (c) 1997,1998 Michael Shalayeff
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
#include <sys/stat.h>
#include <libsa.h>
#include <lib/libsa/loadfile.h>
#ifdef IN_PXEBOOT
#include <pxe.h>

extern int have_pxe;
extern BOOTPLAYER bootplayer;
#endif

#include "cmd.h"

#ifndef MBSD_PREFIX
#define MBSD_PREFIX ""
#endif

static const char *const kernels[] = {
	MBSD_PREFIX "/bsd",
#if !defined(SMALL_BOOT)
	MBSD_PREFIX "/bsd.old",
#endif
	NULL
};

char prog_ident[40];
char *progname = "BOOT";

extern const char version[];
extern int doboot;
int bootprompt = 1;
uint32_t hook_value = 0;

void
boot(dev_t bootdev)
{
	const char *bootfile = kernels[0];
	int fd, i = 0, try = 0, st = -1;
	u_long marks[MARK_MAX];
#ifdef IN_PXEBOOT
	uint32_t ip;
#endif
#if defined(IN_PXEBOOT) || !defined(SMALL_BOOT)
	char myconf[64];
#endif

	machdep();

	snprintf(prog_ident, sizeof(prog_ident),
	    "MirBSD boot %s", version);
	printf(">> %s\n>> booting from device %Xh",
	    prog_ident, bootdev);

	devboot(bootdev, cmd.bootdev);
	printf(" = %s\n", cmd.bootdev);
	memcpy(cmd.image, bootfile, strlen(bootfile) + 1);

	cmd.conf = NULL;
	if (strlen(cmd_buf)) {
		/* command line was passed from previous loader */
		cmd.cmd = NULL;
		cmd.timeout = 0;
		doboot = 0;
		if (docmd())
			goto try_boot;
		st = 0;
		bootprompt = 1;
		goto try_cmd;
	}
#ifdef IN_PXEBOOT
	ip = bootplayer.yip;

	/*
	 * Let's be non-intrusive.. We try to get our /$IP/boot.cfg
	 * first, and if that fails, fall back to /boot.cfg, and
	 * if that fails, do no boot.cfg at all.
	 * Pim van Pelt / Paul de Weerd 20040328
	 */
	if (have_pxe > 0) {
		cmd.boothowto = 0;
		snprintf(myconf, sizeof (myconf),
		    MBSD_PREFIX "/%d.%d.%d.%d/boot.cfg",
		    ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, ip >> 24);
		cmd.conf = myconf;
		cmd.addr = (void *)DEFAULT_KERNEL_ADDRESS;
		cmd.timeout = 5;

		st = read_conf();
	} else
#endif
#if !defined(SMALL_BOOT)
	if (hook_value) {
		cmd.boothowto = 0;
		snprintf(myconf, sizeof (myconf), MBSD_PREFIX "/boot.%d",
		    (hook_value % 999));
		cmd.conf = myconf;
		cmd.addr = (void *)DEFAULT_KERNEL_ADDRESS;
		cmd.timeout = 5;

		st = read_conf();
	}
#endif

	if (st < 0) {
#if defined(IN_PXEBOOT) || !defined(SMALL_BOOT)
		if (cmd.conf)
			printf("Attempt to read %s failed.\n", cmd.conf);
#endif
		cmd.boothowto = 0;
		cmd.conf = MBSD_PREFIX "/boot.cfg";
		cmd.addr = (void *)DEFAULT_KERNEL_ADDRESS;
		cmd.timeout = 5;

		st = read_conf();
	}
	if (!bootprompt)
		snprintf(cmd.path, sizeof cmd.path, "%s:%s",
		    cmd.bootdev, cmd.image);

 try_cmd:
	while (1) {
		/* no boot.cfg, or no boot cmd in there */
		if (bootprompt && st <= 0)
			do {
				printf("boot> ");
			} while(!getcmd());
 try_boot:
		st = 0;
		bootprompt = 1;	/* allow reselect should we fail */

		printf("booting %s: ", cmd.path);
		marks[MARK_START] = (u_long)cmd.addr;
		if ((fd = loadfile(cmd.path, marks,
		    (cmd.boothowto & RB_NO_KSYMS) ?
		    (LOAD_ALL & ~LOAD_SYM) : LOAD_ALL)) != -1) {
			close(fd);
			break;
		}

		if (kernels[++i] == NULL) {
			try += 1;
			bootfile = kernels[i = 0];
		} else
			bootfile = kernels[i];
		memcpy(cmd.image, bootfile, strlen(bootfile) + 1);
		printf(" failed(%d).%s%s\n", errno,
		    (cmd.timeout) ? " will try " : "",
		    (cmd.timeout) ? bootfile : "");

		if (cmd.timeout) {
			if (try < 2)
				cmd.timeout++;
			else {
				printf("Turning timeout off.\n");
				cmd.timeout = doboot = 0;
			}
		}
	}

	/* exec */
	run_loadfile(marks, cmd.boothowto);
}
