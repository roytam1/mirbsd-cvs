/* $MirOS: ports/sysutils/pxegrub/files/openbsd.c,v 1.1.7.1 2005/03/18 15:52:19 tg Exp $
 *
 * Hack to make GRUB boot OpenBSD from the network
 * Booting from the hard drive will require a slightly
 * different boot vector
 *
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
 *
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 1999, 2000, 2001, 2002  Free Software Foundation, Inc.
 *  Copyright (c) 2001, 2002, 2003        Cedric Berger
 *  Copyright (c) 2002, 2003              Thorsten Glaser
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */


/**************************
 * From sys/stand/boot/bootarg.h
 */
#define	BOOTARG_APIVER	(BAPIV_VECTOR|BAPIV_ENV|BAPIV_BMEMMAP)
#define	BAPIV_ANCIENT	0x00000000	/* MD old i386 bootblocks */
#define	BAPIV_VARS	0x00000001	/* MD structure w/ add info passed */
#define	BAPIV_VECTOR	0x00000002	/* MI vector of MD structures passed */
#define	BAPIV_ENV	0x00000004	/* MI environment vars vector */
#define	BAPIV_BMEMMAP	0x00000008	/* MI memory map passed is in bytes */
typedef struct _boot_args {
	int ba_type;
	long ba_size;
	struct _boot_args *_dummy;
//	int ba_arg[1];
} bootarg_t;
#define	BOOTARG_END	-1


/**************************
 * From sys/arch/i386/include/biosvar.h
 */

/*
 * BIOS memory info
 */
#define	BOOTARG_MEMMAP 0
#define	BIOS_MAP_END	0x00	/* End of array XXX - special */
#define	BIOS_MAP_FREE	0x01	/* Usable memory */
#define	BIOS_MAP_RES	0x02	/* Reserved memory */
#define	BIOS_MAP_ACPI	0x03	/* ACPI Reclaim memory */
#define	BIOS_MAP_NVS	0x04	/* ACPI NVS memory */
typedef struct _bios_memmap {
    unsigned long long addr;	/* Beginning of block */
    unsigned long long size;	/* Size of block */
    unsigned long type;		/* Type of block */
} bios_memmap_t;

/*
 * console info
 * tty00 is major=8/minor=0
 */
#define BOOTARG_CONSDEV 5
typedef struct _bios_consdev {
        int     consdev;
        int     conspeed;
} bios_consdev_t;

/*
 * diskless info
 */
#define BOOTARG_IP4INFO 6
typedef struct _bios_ip4info {
    unsigned long ip4_myaddr;	/* if != 0, my IP address, as used by boot */
    unsigned long ip4_mymask;	/* if != 0, my IP netmask, as used by boot */
    unsigned long ip4_mybcast;	/* if != 0, my IP broadcast address */
} bios_ip4info_t;

#define BOOTARG_LINKADDR 7
typedef struct _bios_linkaddr {
    unsigned char la_type;      /* IFT_ETHER = 6 */
    unsigned char la_alen;      /* 6 */
    unsigned char la_addr[6];   /* the ethernet boot MAC address */
} bios_linkaddr_t;


/**************************
 * my bad hack --berger
 */

/*
 * our custom block
 */
struct diskless_bootinfo_s {
    bootarg_t memarg;
    bios_memmap_t memmap[3];
    bootarg_t ttyarg;
    bios_consdev_t ttyinfo;
#ifdef GRUB_OPENBSD_NETWORKED
    bootarg_t ip4arg;
    bios_ip4info_t ip4info;
    bootarg_t laarg;
    bios_linkaddr_t lainfo;
#endif
    bootarg_t endarg;
};

#include "../netboot/etherboot.h"
#include "term.h"
#if defined(GRUB_OPENBSD_NETWORKED)
extern struct arptable_t arptable[];
extern unsigned long netmask;
#elif !defined(GRUB_OPENBSD_LOCAL)
#error mismatching Makefile
#endif
extern long boot_serial_unit;
extern long boot_serial_speed;

/*
 *  All "*_boot" commands depend on the images being loaded into memory
 *  correctly, the variables in this file being set up correctly, and
 *  the root partition being set in the 'saved_drive' and 'saved_partition'
 *  variables.
 */
void
openbsd_boot (kernel_t type, int bootdev, char *arg)
{
  char *str;
  int clval = 0;
  struct diskless_bootinfo_s bv;

  /* call entry point */
  unsigned long end_mark;

#ifdef GRUB_UTIL
  entry_addr = (entry_func) bsd_boot_entry;
#else
  stop_floppy ();
#endif

  while(*(++arg) && *arg != ' ');
  str = arg;
  while(*str) {
      if(*str == '-') {
	  while (*str && *str != ' ') {
	      if (*str == 'C')
		  clval |= RB_CDROM;
	      if (*str == 'a')
		  clval |= RB_ASKNAME;
	      if (*str == 'b')
		  clval |= RB_HALT;
	      if (*str == 'c')
		  clval |= RB_CONFIG;
	      if (*str == 'd')
		  clval |= RB_KDB;
	      if (*str == 'h')
		  clval |= RB_SERIAL;
	      if (*str == 'r')
		  clval |= RB_DFLTROOT;
	      if (*str == 's')
		  clval |= RB_SINGLE;
	      if (*str == 'v')
		  clval |= RB_VERBOSE;
	      str++;
	  }
	  continue;
      }
      str++;
  }
  /*
   *  We now pass the various bootstrap parameters to the loaded
   *  image via the argument list.
   *
   *  This is the unofficial list:
   *
   *  arg0 = '_boothowto' (flags)
   *  arg1 = '_bootdev' boot device - not used
   *  arg2 = '_bootapiver' (boot capabilities/version flags)
   *  arg3 = '_esym' - not used
   *  arg4 = '_extmem' - extended memory - not used
   *  arg5 = '_cnvmem' - standard memory - not used
   *  arg6 = '_bootargc' - size of the boot argument vector (bytes)
   *  arg7 = '_bootargv' - the boot argument vector
   */

  /*
   * I don't know what this stuff is, so I keep it
   */
  if (mbi.flags & MB_INFO_AOUT_SYMS)
      end_mark = (mbi.syms.a.addr + 4
	      + mbi.syms.a.tabsize + mbi.syms.a.strsize);
  else
      /* FIXME: it should be mbi.syms.e.size.  */
      end_mark = 0;

  /* fillup parameter block */
  bv.memarg.ba_type = BOOTARG_MEMMAP;
  bv.memarg.ba_size = sizeof(bv.memarg) + sizeof(bv.memmap);
  bv.memmap[0].addr = 0;
  bv.memmap[0].size = mbi.mem_lower * 1024;
  bv.memmap[0].type = BIOS_MAP_FREE;
  bv.memmap[1].addr = 0x100000;
  bv.memmap[1].size = extended_memory * 1024;
  bv.memmap[1].type = BIOS_MAP_FREE;
  bv.memmap[2].addr = 0;
  bv.memmap[2].size = 0;
  bv.memmap[2].type = BIOS_MAP_END;
  bv.ttyarg.ba_type = BOOTARG_CONSDEV;
  bv.ttyarg.ba_size = sizeof(bv.ttyarg)+sizeof(bv.ttyinfo);
  if(current_term && !grub_strcmp(current_term->name, "serial")) {
    bv.ttyinfo.consdev = 0x800+boot_serial_unit;
    bv.ttyinfo.conspeed = boot_serial_speed;
  } else {
    bv.ttyinfo.consdev = 0;
    bv.ttyinfo.conspeed = 0;
  }
#ifdef GRUB_OPENBSD_NETWORKED
  bv.ip4arg.ba_type = BOOTARG_IP4INFO;
  bv.ip4arg.ba_size = sizeof(bv.ip4arg)+sizeof(bv.ip4info);
  bv.ip4info.ip4_myaddr = arptable[ARP_CLIENT].ipaddr.s_addr;
  bv.ip4info.ip4_mymask = netmask;
  bv.ip4info.ip4_mybcast = (~netmask)+(bv.ip4info.ip4_myaddr & netmask);
  bv.laarg.ba_type = BOOTARG_LINKADDR;
  bv.laarg.ba_size = sizeof(bv.laarg)+sizeof(bv.lainfo);
  bv.lainfo.la_type = 6;
  bv.lainfo.la_alen = 6;
  bv.lainfo.la_addr[0] = arptable[ARP_CLIENT].node[0];
  bv.lainfo.la_addr[1] = arptable[ARP_CLIENT].node[1];
  bv.lainfo.la_addr[2] = arptable[ARP_CLIENT].node[2];
  bv.lainfo.la_addr[3] = arptable[ARP_CLIENT].node[3];
  bv.lainfo.la_addr[4] = arptable[ARP_CLIENT].node[4];
  bv.lainfo.la_addr[5] = arptable[ARP_CLIENT].node[5];
#endif
  bv.endarg.ba_type = BOOTARG_END;
  bv.endarg.ba_size = sizeof(bv.endarg);

  // copy args at 0x2000, and launch the thing with 8 args
  memcpy((long *)0x2000, (long *)&bv, sizeof(bv));
  (*(void (*)(int, int, int, int, int, int, int, int))entry_addr)
      (clval, bootdev, BOOTARG_APIVER, end_mark,
	  extended_memory, mbi.mem_lower, sizeof(bv), 0x2000);
}
