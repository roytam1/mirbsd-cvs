/* $MirOS: src/sys/net/netisr_dispatch.h,v 1.2 2005/03/06 21:28:16 tg Exp $ */
/* $OpenBSD: netisr_dispatch.h,v 1.7 2004/11/28 23:39:45 canacar Exp $	*/
/* $NetBSD: netisr_dispatch.h,v 1.2 2000/07/02 04:40:47 cgd Exp $ */

/*
 * netisr_dispatch: This file is included by the
 *	machine dependant softnet function.  The
 *	DONETISR macro should be set before including
 *	this file.  i.e.:
 *
 * softintr() {
 *	...do setup stuff...
 *	#define DONETISR(bit, fn) do { ... } while (0)
 *	#include <net/netisr_dispatch.h>
 *	#undef DONETISR
 *	...do cleanup stuff.
 * }
 */

#ifndef _NET_NETISR_H_
#error <net/netisr.h> must be included before <net/netisr_dispatch.h>
#endif

#ifndef _NET_NETISR_DISPATCH_H_
#define _NET_NETISR_DISPATCH_H_
#include "ether.h"
#include "ppp.h"
#include "bridge.h"
#include "pppoe.h"
#include "lpt.h"
#endif

/*
 * When adding functions to this list, be sure to add headers to provide
 * their prototypes in <net/netisr.h> (if necessary).
 */

	DONETISR(NETISR_RND,netrndintr);

#ifdef INET
#if NETHER > 0
	DONETISR(NETISR_ARP,arpintr);
#endif
	DONETISR(NETISR_IP,ipintr);
#endif
#ifdef INET6
	DONETISR(NETISR_IPV6,ip6intr);
#endif
#ifdef NETATALK
	DONETISR(NETISR_ATALK,atintr);
#endif
#ifdef IMP
	DONETISR(NETISR_IMP,impintr);
#endif
#ifdef IPX
	DONETISR(NETISR_IPX,ipxintr);
#endif
#ifdef NS
	DONETISR(NETISR_NS,nsintr);
#endif
#ifdef CCITT
	DONETISR(NETISR_CCITT,ccittintr);
#endif
#if NATM > 0
	DONETISR(NETISR_NATM,natmintr);
#endif
#if NPPP > 0
	DONETISR(NETISR_PPP,pppintr);
#endif
#if NBRIDGE > 0
        DONETISR(NETISR_BRIDGE,bridgeintr);
#endif
#if defined(PLIP) && NLPT > 0
	DONETISR(NETISR_PLIP,plipsoftint)
#endif
#if NPPPOE > 0
	DONETISR(NETISR_PPPOE,pppoeintr);
#endif