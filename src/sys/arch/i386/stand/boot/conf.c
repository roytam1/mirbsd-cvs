/**	$MirOS: src/sys/arch/i386/stand/boot/conf.c,v 1.17 2009/01/10 22:18:52 tg Exp $ */
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
#ifndef SMALL_BOOT
#include <lib/libsa/fat.h>
#include <lib/libsa/lmbmfs.h>
#ifdef USE_PXE
#include <lib/libsa/nfs.h>
#include <lib/libsa/tftp.h>
#include <lib/libsa/netif.h>
#include <sys/disklabel.h>
#endif
#endif
#include <biosdev.h>
#include <dev/cons.h>
#include "debug.h"
#ifdef USE_PXE
#include "disk.h"
#include "pxeboot.h"
#include "pxe_net.h"
#endif

#ifdef USE_PXE
static void pxecheck(void);
#endif

#ifndef SMALL_BOOT
static void lmbmfs_check(void);
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
#ifndef SMALL_BOOT
	lmbmfs_check,
#endif
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

/* filesystems applying to generic devices, not pseudodevices */
struct fs_ops file_system[] = {
#ifndef SMALL_BOOT
	{ cd9660_open, cd9660_close, cd9660_read, cd9660_write, cd9660_seek,
	  cd9660_stat, cd9660_readdir, "cd9660" },
#endif
	{ ufs_open,    ufs_close,    ufs_read,    ufs_write,    ufs_seek,
	  ufs_stat,    ufs_readdir,    "ufs" },
#ifndef SMALL_BOOT
	{ fat_open,    fat_close,    fat_read,    fat_write,    fat_seek,
	  fat_stat,    fat_readdir,    "fat" },
#endif
};
int nfsys = NENTS(file_system);

struct devsw devsw[] = {
	{ "BIOS", biosstrategy, biosopen, biosclose, biosioctl },
#ifndef SMALL_BOOT
#define DEVSW_LMBM 1
	{ "lmbm", lmbm_strategy, lmbm_open, lmbm_close, lmbm_ioctl },
#ifdef USE_PXE
#define DEVSW_NET 2
	{ "PXE", net_strategy, net_open, net_close, net_ioctl },
#endif
#endif
};

struct consdev constab[] = {
	{ pc_probe, pc_init, pc_getc, pc_putc },
	{ com_probe, com_init, com_getc, com_putc },
	{ NULL }
};
struct consdev *cn_tab = constab;

#ifdef USE_PXE
static struct fs_ops tftp_fs_ops[] = {
	{ tftp_open,   tftp_close,   tftp_read,   tftp_write,   tftp_seek,
	  tftp_stat,   tftp_readdir, "tftp" },
};
static struct fs_ops nfs_fs_ops[] = {
	{ nfs_open,    nfs_close,    nfs_read,    nfs_write,    nfs_seek,
	  nfs_stat,    nfs_readdir,  "nfs" }
};
struct netif_driver *netif_drivers[] = {
};
int n_netif_drivers = NENTS(netif_drivers);

void
pxecheck(void)
{
	if (have_pxe > 0) {
		if (i386_biosflags & 4) {
			start_dip = alloc(sizeof (struct diskinfo));
			bzero(start_dip, sizeof (struct diskinfo));
			memcpy(start_dip->name, "tftp", 5);
			start_dip->ops = tftp_fs_ops;
			start_dip->bios_info.flags = BDI_NOTADISK;
			TAILQ_INSERT_TAIL(&disklist, start_dip, list);
		}

		have_pxe = 1;
		sa_cleanup = pxe_shutdown;
	} else {
		have_pxe = 0;
		nibprobes -= 1;
	}
}
#endif

#ifndef SMALL_BOOT
static struct fs_ops lmbm_fs_ops[] = {
	{ lmbmfs_open, lmbmfs_close, lmbmfs_read, lmbmfs_write, lmbmfs_seek,
	  lmbmfs_stat, lmbmfs_readdir, "lmbmfs" }
};

void
lmbmfs_check(void)
{
	if (lmbmfs_init() == 0) {
		start_dip = alloc(sizeof (struct diskinfo));
		bzero(start_dip, sizeof (struct diskinfo));
		memcpy(start_dip->name, "lmbm", 5);
		start_dip->ops = lmbm_fs_ops;
		start_dip->bios_info.flags = BDI_NOTADISK;
		TAILQ_INSERT_TAIL(&disklist, start_dip, list);
	}
}
#endif

struct devsw_prefix_match devsw_match[] = {
#ifndef SMALL_BOOT
	{ &devsw[DEVSW_LMBM], lmbm_fs_ops, "lmbm", 0, 1 },
#ifdef USE_PXE
	{ &devsw[DEVSW_NET], tftp_fs_ops, "tftp", 1, 1 },
	{ &devsw[DEVSW_NET], nfs_fs_ops, "nfs", 1, 1 },
#endif
#endif
	{ &devsw[0], NULL, "", 0, 0 },
	{ NULL, NULL, "", 0, 0 }
};
