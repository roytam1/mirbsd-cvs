/* $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $ */

/*-
 * Copyright (c) 2010
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 *-
 * The idea of an arc4random(3) stems from David Mazieres for OpenBSD
 */

#ifndef _LIBC_INTERNAL_ARC4RANDOM_H
#define _LIBC_INTERNAL_ARC4RANDOM_H

__BEGIN_DECLS

#include <syskern/libckern.h>

extern struct arc4random_status {
	uint32_t pool[32];
	struct arcfour_status cipher;
	struct {
		uint8_t poolptr_;
		bool initialised_;
		pid_t stir_pid_;
		int count_;
	} otherinfo;
} a4state;

#define a4s_poolptr	otherinfo.poolptr_
#define a4s_initialised	otherinfo.initialised_
#define a4s_stir_pid	otherinfo.stir_pid_
#define a4s_count	otherinfo.count_

void arc4random_atexit(void);
void arc4random_stir_locked(pid_t);

__END_DECLS

#endif
