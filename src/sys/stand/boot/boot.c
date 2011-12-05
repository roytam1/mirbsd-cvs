/**	$MirOS: src/sys/stand/boot/boot.c,v 1.4 2006/04/06 00:05:33 tg Exp $	*/
/*	$OpenBSD: boot.c,v 1.30 2004/01/29 00:54:08 tom Exp $	*/

/*
 * Copyright (c) 2002, 2003, 2004 Thorsten Glaser
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
#include <lib/libkern/funcs.h>
#ifdef IN_PXEBOOT
#include <pxe.h>

extern BOOTPLAYER bootplayer;
#endif

#include "cmd.h"

static const char *const kernels[] = {
	"/bsd",
	"/bsd.old",
	NULL
};

char prog_ident[40];
char *progname = "BOOT";

extern const char version[];
struct cmd_state cmd;
int bootprompt = 1;
uint32_t hook_value = 0;

void
boot(dev_t bootdev)
{
	const char *bootfile = kernels[0];
	int i = 0, try = 0, st = -1;
	u_long marks[MARK_MAX];
#ifdef IN_PXEBOOT
	uint32_t ip;
#endif
	char myconf[32];

	machdep();

	snprintf(prog_ident, sizeof(prog_ident),
	    "MirBSD boot %s", version);
	printf(">> %s\n>> booting from device %Xh",
	    prog_ident, bootdev);

	devboot(bootdev, cmd.bootdev);
	printf(" = %s\n", cmd.bootdev);
	strlcpy(cmd.image, bootfile, sizeof(cmd.image));

#ifdef IN_PXEBOOT
	ip = bootplayer.yip;

	/*
	 * Let's be non-intrusive.. We try to get our /$IP/boot.cfg
	 * first, and if that fails, fall back to /etc/boot.cfg, and
	 * if that fails, do no boot.cfg at all.
	 * Pim van Pelt / Paul de Weerd 20040328
	 */
	cmd.boothowto = 0;
	snprintf(myconf, sizeof(myconf), "/%d.%d.%d.%d/boot.cfg",
	    ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff);
	cmd.conf = myconf;
	cmd.addr = (void *)DEFAULT_KERNEL_ADDRESS;
	cmd.timeout = 5;

	if ((st = read_conf()))
		printf("Attempt to read %s failed.\n", cmd.conf);
#else
	if (hook_value) {
		cmd.boothowto = 0;
		snprintf(myconf, sizeof (myconf), "/etc/boot.%03x",
		    (hook_value & 0xFFF));
		cmd.conf = myconf;
		cmd.addr = (void *)DEFAULT_KERNEL_ADDRESS;
		cmd.timeout = 5;

		if ((st = read_conf()))
			printf("Attempt to read %s failed.\n", cmd.conf);
	}
#endif

	if (st < 0) {
		cmd.boothowto = 0;
		cmd.conf = "/etc/boot.cfg";
		cmd.addr = (void *)DEFAULT_KERNEL_ADDRESS;
		cmd.timeout = 5;

		st = read_conf();
	}
	if (!bootprompt)
		snprintf(cmd.path, sizeof cmd.path, "%s:%s",
		    cmd.bootdev, cmd.image);

	while (1) {
		/* no boot.conf, or no boot cmd in there */
		if (bootprompt && st <= 0)
			do {
				printf("boot> ");
			} while (!getcmd());
		st = 0;
		bootprompt = 1;	/* allow reselect should we fail */

		printf("booting %s: ", cmd.path);
		marks[MARK_START] = (u_long)cmd.addr;
		if (loadfile(cmd.path, marks, LOAD_ALL) >= 0)
			break;

		if (kernels[++i] == NULL) {
			try += 1;
			bootfile = kernels[i = 0];
		} else
			bootfile = kernels[i];
		strlcpy(cmd.image, bootfile, sizeof(cmd.image));
		printf(" failed(%d).%s%s\n", errno,
		    (cmd.timeout) ? " will try " : "",
		    (cmd.timeout) ? bootfile : "");

		if (cmd.timeout) {
			if (try < 2)
				cmd.timeout++;
			else
				printf("Turning timeout off.\n");
		}
	}

	/* exec */
	run_loadfile(marks, cmd.boothowto);
}

#ifdef _TEST
int
main()
{
	boot(0);
	return 0;
}
#endif
