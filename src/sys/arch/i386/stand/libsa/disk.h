/*	$OpenBSD: disk.h,v 1.4 2004/03/09 19:12:13 tom Exp $	*/

/*
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

#ifndef _DISKPROBE_H
#define _DISKPROBE_H

#include <sys/queue.h>

struct fs_ops;

/* All the info on a disk we've found */
struct diskinfo {
	bios_diskinfo_t bios_info;
	struct disklabel disklabel;

	dev_t bsddev, bootdev;

	TAILQ_ENTRY(diskinfo) list;

	struct fs_ops *ops;
	char name[5];
};
TAILQ_HEAD(disklist_lh, diskinfo);

/* Head of this list */
extern struct diskinfo *bootdev_dip;
extern struct disklist_lh disklist;

/* Entry for boot device */
extern struct diskinfo *start_dip;

void dump_diskinfo(void);
int disk_trylabel(struct diskinfo *);

#endif /* _DISKPROBE_H */