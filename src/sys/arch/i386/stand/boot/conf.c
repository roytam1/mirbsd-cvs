/**	$MirOS: src/sys/arch/i386/stand/boot/conf.c,v 1.14 2009/01/10 13:03:39 tg Exp $ */
/*	$OpenBSD: conf.c,v 1.39 2008/04/19 23:20:22 weingart Exp $	*/

/*
 * Copyright (c) 1996 Michael Shalayeff
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
 */

#ifdef SMALL_BOOT
#undef USE_PXE
#endif

#include <sys/types.h>
#include <netinet/in.h>
#include <libsa.h>
#include <lib/libsa/ufs.h>
#include <lib/libsa/cd9660.h>
#include <tori.h>
#ifndef SMALL_BOOT
#include <lib/libsa/fat.h>
#ifdef USE_PXE
#include <lib/libsa/nfs.h>
#include <lib/libsa/tftp.h>
#include <lib/libsa/netif.h>
#endif
#endif
#include <biosdev.h>
#include <dev/cons.h>
#include "debug.h"
#ifdef USE_PXE
#include "pxeboot.h"
#include "pxe_net.h"

void pxecheck(void);
#endif

const char version[] = __BOOT_VER;
int debug = 1;

void (*sa_cleanup)(void) = NULL;

void (*i386_probe1[])(void) = {
	ps2probe, gateA20on, /* debug_init, */ cninit,
	apmprobe, pciprobe, /* smpprobe, */
#ifdef USE_PXE
	pxeprobe, pxecheck,
#endif
	memprobe
};
void (*i386_probe2[])(void) = {
 	diskprobe
};
#ifdef USE_PXE
void (*i386_probe3[])(void) = {
	pxeinfo
/*	netprobe_pxe, netprobe_mac, netprobe_inet4, netprobe_bootdev */
};
#endif

struct i386_boot_probes probe_list[] = {
	{ "probing", i386_probe1, NENTS(i386_probe1) },
	{ "disk",    i386_probe2, NENTS(i386_probe2) },
#ifdef USE_PXE
	{ "net",     i386_probe3, NENTS(i386_probe3) },
#endif
};
int nibprobes = NENTS(probe_list);

struct fs_ops file_system[] = {
#ifndef SMALL_BOOT
	{ cd9660_open, cd9660_close, cd9660_read, cd9660_write, cd9660_seek,
	  cd9660_stat, cd9660_readdir },
#endif
	{ ufs_open,    ufs_close,    ufs_read,    ufs_write,    ufs_seek,
	  ufs_stat,    ufs_readdir    },
#ifndef SMALL_BOOT
	{ fat_open,    fat_close,    fat_read,    fat_write,    fat_seek,
	  fat_stat,    fat_readdir    },
#endif
#ifdef USE_PXE
	{ nfs_open,    nfs_close,    nfs_read,    nfs_write,    nfs_seek,
	  nfs_stat,    nfs_readdir    },
	{ tftp_open,   tftp_close,   tftp_read,   tftp_write,   tftp_seek,
	  tftp_stat,   tftp_readdir   },
#endif
};
int nfsys = NENTS(file_system);

struct devsw	devsw[] = {
#ifndef SMALL_BOOT
	{ "TORI", toristrategy, toriopen, toriclose, toriioctl },
#endif
	{ "BIOS", biosstrategy, biosopen, biosclose, biosioctl },
#if 0
	{ "TFTP", tftpstrategy, tftpopen, tftpclose, tftpioctl },
#endif
};
int ndevs = NENTS(devsw);

#ifdef USE_PXE
struct devsw	netsw[] = {
	{ "net",  net_strategy, net_open, net_close, net_ioctl },
};

struct netif_driver	*netif_drivers[] = {
};
int n_netif_drivers = NENTS(netif_drivers);
#endif

struct consdev constab[] = {
	{ pc_probe, pc_init, pc_getc, pc_putc },
	{ com_probe, com_init, com_getc, com_putc },
	{ NULL }
};
struct consdev *cn_tab = constab;

#ifdef USE_PXE
void
pxecheck(void)
{
	if (have_pxe > 0) {
		have_pxe = 1;
		sa_cleanup = pxe_shutdown;
	} else {
		have_pxe = 0;
		nibprobes -= 1;
		nfsys -= 2;
#if 0
		ndevs -= 1;
#endif
	}
}
#endif
