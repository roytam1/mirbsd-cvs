/**	$MirOS: src/sys/net/netisr.h,v 1.3 2007/05/29 08:42:31 tg Exp $ */
/*	$OpenBSD: netisr.h,v 1.20 2004/11/28 23:39:45 canacar Exp $	*/
/*	$NetBSD: netisr.h,v 1.12 1995/08/12 23:59:24 mycroft Exp $	*/

/*
 * Copyright (c) 1980, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)netisr.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _NET_NETISR_H_
#define _NET_NETISR_H_
/*
 * The networking code runs off software interrupts.
 *
 * You can switch into the network by doing splsoftnet() and return by splx().
 * The software interrupt level for the network is higher than the software
 * level for the clock (so you can enter the network in routines called
 * at timeout time).
 *
 * The routine to request a network software interrupt, setsoftnet(),
 * is defined in the machine-specific include files.
 */

/*
 * Each ``pup-level-1'' input queue has a bit in a ``netisr'' status
 * word which is used to de-multiplex a single software
 * interrupt used for scheduling the network code to calls
 * on the lowest level routine of each protocol.
 */
#define	NETISR_NOTRND	0		/* virtual */
#define	NETISR_RND	1
#define	NETISR_IP	2		/* same as AF_INET */
#define	NETISR_IMP	3		/* same as AF_IMPLINK */
#define	NETISR_NS	6		/* same as AF_NS */
#define	NETISR_ISO	7		/* same as AF_ISO */
#define	NETISR_CCITT	10		/* same as AF_CCITT */
#define	NETISR_ATALK	16		/* same as AF_APPLETALK */
#define	NETISR_ARP	18		/* same as AF_LINK */
#define	NETISR_IPX	23		/* same as AF_IPX */
#define	NETISR_IPV6	24		/* same as AF_INET6 */
#define	NETISR_ISDN	26		/* same as AF_E164 */
#define	NETISR_NATM	27		/* same as AF_ATM */
#define	NETISR_PPP	28		/* for PPP processing */
#define	NETISR_BRIDGE	29		/* for bridge processing */
#define	NETISR_PLIP	30		/* for PLIP processing */
#define	NETISR_PPPOE	31		/* for pppoe processing */

#ifndef _LOCORE
#ifdef _KERNEL
extern int	netisr;			/* scheduling bits for network */
extern int	netrndintr_v;		/* same bits but for entropy */

void	netrndintr(void);
void	arpintr(void);
void	ipintr(void);
void	ip6intr(void);
void	atintr(void);
void	nsintr(void);
void	ipxintr(void);
void	clnlintr(void);
void	natmintr(void);
void	pppintr(void);
void	ccittintr(void);
void	bridgeintr(void);
void	pppoeintr(void);

#define schednetisr(anisr) do {					\
	netrndintr_v |= 1 << (anisr);				\
	netisr |= (1 << (anisr)) | (1 << NETISR_RND);		\
	setsoftnet();						\
} while (/* CONSTCOND */ 0)
#define schednetisr_virtual(anisr) do {				\
	netrndintr_v |= (1 << (anisr)) | (1 << NETISR_NOTRND);	\
	netisr |= 1 << (anisr);					\
	setsoftnet();						\
} while (/* CONSTCOND */ 0)
#endif
#endif

#endif /* _NET_NETISR_H_ */
