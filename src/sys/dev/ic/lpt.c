/**	$MirOS: src/sys/dev/ic/lpt.c,v 1.2 2005/03/06 21:27:40 tg Exp $	*/
/*	$OpenBSD: lpt.c,v 1.5 2002/03/14 01:26:54 millert Exp $ */
/*	$NetBSD: lpt.c,v 1.42 1996/10/21 22:41:14 thorpej Exp $	*/

/*
 * Copyright (c) 2003, 2005 Thorsten Glaser <tg@MirBSD.org>
 * Copyright (c) 1994 Matthias Pfaller.
 * Copyright (c) 1994 Poul-Henning Kamp.
 * Copyright (c) 1993, 1994 Charles Hannum.
 * Copyright (c) 1990 William F. Jolitz, TeleMuse
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This software is a component of "386BSD" developed by 
 *	William F. Jolitz, TeleMuse.
 * 4. Neither the name of the developer nor the name "386BSD"
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS A COMPONENT OF 386BSD DEVELOPED BY WILLIAM F. JOLITZ 
 * AND IS INTENDED FOR RESEARCH AND EDUCATIONAL PURPOSES ONLY. THIS 
 * SOFTWARE SHOULD NOT BE CONSIDERED TO BE A COMMERCIAL PRODUCT. 
 * THE DEVELOPER URGES THAT USERS WHO REQUIRE A COMMERCIAL PRODUCT 
 * NOT MAKE USE OF THIS WORK.
 *
 * FOR USERS WHO WISH TO UNDERSTAND THE 386BSD SYSTEM DEVELOPED
 * BY WILLIAM F. JOLITZ, WE RECOMMEND THE USER STUDY WRITTEN 
 * REFERENCES SUCH AS THE  "PORTING UNIX TO THE 386" SERIES 
 * (BEGINNING JANUARY 1991 "DR. DOBBS JOURNAL", USA AND BEGINNING 
 * JUNE 1991 "UNIX MAGAZIN", GERMANY) BY WILLIAM F. JOLITZ AND 
 * LYNNE GREER JOLITZ, AS WELL AS OTHER BOOKS ON UNIX AND THE 
 * ON-LINE 386BSD USER MANUAL BEFORE USE. A BOOK DISCUSSING THE INTERNALS 
 * OF 386BSD ENTITLED "386BSD FROM THE INSIDE OUT" WILL BE AVAILABLE LATE 1992.
 *
 * THIS SOFTWARE IS PROVIDED BY THE DEVELOPER ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE DEVELOPER BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Device Driver for AT parallel printer port
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/kernel.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <sys/device.h>
#include <sys/conf.h>
#include <sys/syslog.h>

#include <machine/bus.h>
#include <machine/intr.h>

#if defined(INET) && defined(PLIP)
#include "bpfilter.h"
#include <sys/mbuf.h>
#include <sys/socket.h>

#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#ifdef	__NetBSD__
#include <net/if_ether.h>
#endif
#include <net/netisr.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#ifdef	__NetBSD__
#include <netinet/if_inarp.h>
#else
#include <netinet/if_ether.h>
#endif
#if NBPFILTER > 0
#include <sys/time.h>
#include <net/bpf.h>
#endif
#endif

#include <dev/ic/lptreg.h>
#include <dev/ic/lptvar.h>

#include "lpt.h"

#define	TIMEOUT		hz*16	/* wait up to 16 seconds for a ready */
#define	STEP		hz/4

#define	LPTPRI		(PZERO+8)
#define	LPT_BSIZE	1024

#if !defined(DEBUG) || !defined(notdef)
#define LPRINTF(a)
#else
#define LPRINTF(a)	if (lptdebug) printf a
int lptdebug = 1;
#endif

#if defined(INET) && defined(PLIP)

#define PLIPMTU		ETHERMTU

#ifndef PLIPMXSPIN1		/* DELAY factor for the plip# interfaces */
#define	PLIPMXSPIN1	50000	/* Spinning for remote intr to happen */
#endif

#ifndef PLIPMXSPIN2		/* DELAY factor for the plip# interfaces */
#define	PLIPMXSPIN2	50000	/* Spinning for remote handshake to happen */
#endif

#ifndef PLIPMXERRS		/* Max errors before !RUNNING */
#define	PLIPMXERRS	50
#endif
#ifndef PLIPMXRETRY
#define PLIPMXRETRY	20	/* Max number of retransmits */
#endif
#ifndef PLIPRETRY
#define PLIPRETRY	hz/50	/* Time between retransmits */
#endif

#define STABILIZE(iot, ioh, io) ({ \
		int v1, v2; \
		v2 = bus_space_read_1(iot, ioh, io); \
		do { \
			v1 = v2; \
			v2 = bus_space_read_1(iot, ioh, io); \
		} while (v1 != v2); \
		v2; \
	})
#endif

#if defined(INET) && defined(PLIP)
/* Functions for the plip# interface */
static void	plipattach(struct lpt_softc *);
static void	plipinput(struct lpt_softc *);
static int	plipioctl(struct ifnet *, u_long, caddr_t);
static void	plipoutput(void *);
static int	plipreceive(struct lpt_softc *, u_char *, int);
static void	pliprxenable(void *);
void		plipsoftint(void);
static void	plipstart(struct ifnet *);
static int	pliptransmit(struct lpt_softc *, u_char *, int);
#endif

/* XXX does not belong here */
cdev_decl(lpt);

struct cfdriver lpt_cd = {
	NULL, "lpt", DV_TTY
};

#define	LPTUNIT(s)	(minor(s) & 0x1f)
#define	LPTFLAGS(s)	(minor(s) & 0xe0)

#define	LPS_INVERT	(LPS_SELECT|LPS_NERR|LPS_NBSY|LPS_NACK)
#define	LPS_MASK	(LPS_SELECT|LPS_NERR|LPS_NBSY|LPS_NACK|LPS_NOPAPER)
#define	NOT_READY() \
    ((bus_space_read_1(iot, ioh, lpt_status) ^ LPS_INVERT) & LPS_MASK)
#define	NOT_READY_ERR() \
    lpt_not_ready(bus_space_read_1(iot, ioh, lpt_status), sc)

int	lpt_not_ready(u_int8_t, struct lpt_softc *);
void	lptwakeup(void *arg);
int	lptpushbytes(struct lpt_softc *);

/*
 * Internal routine to lptprobe to do port tests of one byte value.
 */
int
lpt_port_test(iot, ioh, base, off, data, mask)
	bus_space_tag_t iot;
	bus_space_handle_t ioh;
	bus_addr_t base;
	bus_size_t off;
	u_int8_t data, mask;
{
	int timeout;
	u_int8_t temp;

	data &= mask;
	bus_space_write_1(iot, ioh, off, data);
	timeout = 1000;
	do {
		delay(10);
		temp = bus_space_read_1(iot, ioh, off) & mask;
	} while (temp != data && --timeout);
	LPRINTF(("lpt: port=0x%x out=0x%x in=0x%x timeout=%d\n", base + off,
	    data, temp, timeout));
	return (temp == data);
}

void
lpt_attach_common(sc)
	struct lpt_softc *sc;
{
	printf("\n");

	bus_space_write_1(sc->sc_iot, sc->sc_ioh, lpt_control, LPC_NINIT);

#if defined(INET) && defined(PLIP)
	plipattach(sc);
#endif

	timeout_set(&sc->sc_wakeup_tmo, lptwakeup, sc);
}

/*
 * Reset the printer, then wait until it's selected and not busy.
 */
int
lptopen(dev, flag, mode, p)
	dev_t dev;
	int flag;
	int mode;
	struct proc *p;
{
	int unit = LPTUNIT(dev);
	u_int8_t flags = LPTFLAGS(dev);
	struct lpt_softc *sc;
	bus_space_tag_t iot;
	bus_space_handle_t ioh;
	u_int8_t control;
	int error;
	int spin;

	if (unit >= lpt_cd.cd_ndevs)
		return ENXIO;
	sc = lpt_cd.cd_devs[unit];
	if (!sc)
		return ENXIO;

	sc->sc_flags = (sc->sc_flags & LPT_POLLED) | flags;
	if ((sc->sc_flags & (LPT_POLLED|LPT_NOINTR)) == LPT_POLLED)
		return ENXIO;

#ifdef DIAGNOSTIC
	if (sc->sc_state)
		printf("%s: stat=0x%x not zero\n", sc->sc_dev.dv_xname,
		    sc->sc_state);
#endif

	if (sc->sc_state)
		return EBUSY;

#if defined(INET) && defined(PLIP)
#ifdef	__NetBSD__
	if (sc->sc_ethercom.ec_if.if_flags & IFF_UP)
#else
	if (sc->sc_arpcom.ac_if.if_flags & IFF_UP)
#endif
	    return EBUSY;
#endif

	sc->sc_state = LPT_INIT;
	LPRINTF(("%s: open: flags=0x%x\n", sc->sc_dev.dv_xname, flags));
	iot = sc->sc_iot;
	ioh = sc->sc_ioh;

	if ((flags & LPT_NOPRIME) == 0) {
		/* assert INIT for 100 usec to start up printer */
		bus_space_write_1(iot, ioh, lpt_control, LPC_SELECT);
		delay(100);
	}

	control = LPC_SELECT | LPC_NINIT;
	bus_space_write_1(iot, ioh, lpt_control, control);

	/* wait till ready (printer running diagnostics) */
	for (spin = 0; NOT_READY_ERR(); spin += STEP) {
		if (spin >= TIMEOUT) {
			sc->sc_state = 0;
			return EBUSY;
		}

		/* wait 1/4 second, give up if we get a signal */
		error = tsleep((caddr_t)sc, LPTPRI | PCATCH, "lptopen", STEP);
		if (error != EWOULDBLOCK) {
			sc->sc_state = 0;
			return error;
		}
	}

	if ((flags & LPT_NOINTR) == 0)
		control |= LPC_IENABLE;
	if (flags & LPT_AUTOLF)
		control |= LPC_AUTOLF;
	sc->sc_control = control;
	bus_space_write_1(iot, ioh, lpt_control, control);

	sc->sc_inbuf = geteblk(LPT_BSIZE);
	sc->sc_count = 0;
	sc->sc_state = LPT_OPEN;

	if ((sc->sc_flags & LPT_NOINTR) == 0)
		lptwakeup(sc);

	LPRINTF(("%s: opened\n", sc->sc_dev.dv_xname));
	return 0;
}

int
lpt_not_ready(status, sc)
	u_int8_t status;
	struct lpt_softc *sc;
{
	u_int8_t new;

	status = (status ^ LPS_INVERT) & LPS_MASK;
	new = status & ~sc->sc_laststatus;
	sc->sc_laststatus = status;

	if (new & LPS_SELECT)
		log(LOG_NOTICE, "%s: offline\n", sc->sc_dev.dv_xname);
	else if (new & LPS_NOPAPER)
		log(LOG_NOTICE, "%s: out of paper\n", sc->sc_dev.dv_xname);
	else if (new & LPS_NERR)
		log(LOG_NOTICE, "%s: output error\n", sc->sc_dev.dv_xname);

	return status;
}

void
lptwakeup(arg)
	void *arg;
{
	struct lpt_softc *sc = arg;
	int s;

	s = spltty();
	lptintr(sc);
	splx(s);

	timeout_add(&sc->sc_wakeup_tmo, STEP);
}

/*
 * Close the device, and free the local line buffer.
 */
int
lptclose(dev, flag, mode, p)
	dev_t dev;
	int flag;
	int mode;
	struct proc *p;
{
	int unit = LPTUNIT(dev);
	struct lpt_softc *sc = lpt_cd.cd_devs[unit];
	bus_space_tag_t iot = sc->sc_iot;
	bus_space_handle_t ioh = sc->sc_ioh;

	if (sc->sc_count)
		(void) lptpushbytes(sc);

	if ((sc->sc_flags & LPT_NOINTR) == 0)
		timeout_del(&sc->sc_wakeup_tmo);

	bus_space_write_1(iot, ioh, lpt_control, LPC_NINIT);
	sc->sc_state = 0;
	bus_space_write_1(iot, ioh, lpt_control, LPC_NINIT);
	brelse(sc->sc_inbuf);

	LPRINTF(("%s: closed\n", sc->sc_dev.dv_xname));
	return 0;
}

int
lptpushbytes(sc)
	struct lpt_softc *sc;
{
	bus_space_tag_t iot = sc->sc_iot;
	bus_space_handle_t ioh = sc->sc_ioh;
	int error;

	if (sc->sc_flags & LPT_NOINTR) {
		int spin, tic;
		u_int8_t control = sc->sc_control;

		while (sc->sc_count > 0) {
			spin = 0;
			while (NOT_READY()) {
				if (++spin < sc->sc_spinmax)
					continue;
				tic = 0;
				/* adapt busy-wait algorithm */
				sc->sc_spinmax++;
				while (NOT_READY_ERR()) {
					/* exponential backoff */
					tic = tic + tic + 1;
					if (tic > TIMEOUT)
						tic = TIMEOUT;
					error = tsleep((caddr_t)sc,
					    LPTPRI | PCATCH, "lptpsh", tic);
					if (error != EWOULDBLOCK)
						return error;
				}
				break;
			}

			bus_space_write_1(iot, ioh, lpt_data, *sc->sc_cp++);
			bus_space_write_1(iot, ioh, lpt_control,
			    control | LPC_STROBE);
			sc->sc_count--;
			bus_space_write_1(iot, ioh, lpt_control, control);

			/* adapt busy-wait algorithm */
			if (spin*2 + 16 < sc->sc_spinmax)
				sc->sc_spinmax--;
		}
	} else {
		int s;

		while (sc->sc_count > 0) {
			/* if the printer is ready for a char, give it one */
			if ((sc->sc_state & LPT_OBUSY) == 0) {
				LPRINTF(("%s: write %d\n", sc->sc_dev.dv_xname,
				    sc->sc_count));
				s = spltty();
				(void) lptintr(sc);
				splx(s);
			}
			error = tsleep((caddr_t)sc, LPTPRI | PCATCH,
			    "lptwrite2", 0);
			if (error)
				return error;
		}
	}
	return 0;
}

/*
 * Copy a line from user space to a local buffer, then call putc to get the
 * chars moved to the output queue.
 */
int
lptwrite(dev, uio, flags)
	dev_t dev;
	struct uio *uio;
	int flags;
{
	struct lpt_softc *sc = lpt_cd.cd_devs[LPTUNIT(dev)];
	size_t n;
	int error = 0;

	while ((n = min(LPT_BSIZE, uio->uio_resid)) != 0) {
		uiomove(sc->sc_cp = sc->sc_inbuf->b_data, n, uio);
		sc->sc_count = n;
		error = lptpushbytes(sc);
		if (error) {
			/*
			 * Return accurate residual if interrupted or timed
			 * out.
			 */
			uio->uio_resid += sc->sc_count;
			sc->sc_count = 0;
			return error;
		}
	}
	return 0;
}

/*
 * Handle printer interrupts which occur when the printer is ready to accept
 * another char.
 */
int
lptintr(arg)
	void *arg;
{
	struct lpt_softc *sc = arg;
	bus_space_tag_t iot = sc->sc_iot;
	bus_space_handle_t ioh = sc->sc_ioh;

	if (((sc->sc_state & LPT_OPEN) == 0 && sc->sc_count == 0) ||
	    (sc->sc_flags & LPT_NOINTR))
		return 0;

#if defined(INET) && defined(PLIP)
#ifdef	__NetBSD__
	if (sc->sc_ethercom.ec_if.if_flags & IFF_UP) {
#else
	if (sc->sc_arpcom.ac_if.if_flags & IFF_UP) {
#endif
		if ((sc->sc_control & LPC_IENABLE) == 0)
			return 0;	/* dispose spurious interrupt */

		bus_space_write_1(iot, ioh, lpt_control, sc->sc_control &= ~LPC_IENABLE);
		sc->sc_pending |= PLIP_IPENDING;
		/*softintr(sc->sc_ifsoftint);*/
		schednetisr(NETISR_PLIP);
		return 0;
	}
#endif
	/* is printer online and ready for output */
	if (NOT_READY() && NOT_READY_ERR())
		return -1;

	if (sc->sc_count) {
		u_int8_t control = sc->sc_control;
		/* send char */
		bus_space_write_1(iot, ioh, lpt_data, *sc->sc_cp++);
		delay (50);
		bus_space_write_1(iot, ioh, lpt_control, control | LPC_STROBE);
		sc->sc_count--;
		bus_space_write_1(iot, ioh, lpt_control, control);
		sc->sc_state |= LPT_OBUSY;
	} else
		sc->sc_state &= ~LPT_OBUSY;

	if (sc->sc_count == 0) {
		/* none, wake up the top half to get more */
		wakeup((caddr_t)sc);
	}

	return 1;
}

int
lptioctl(dev, cmd, data, flag, p)
	dev_t dev;
	u_long cmd;
	caddr_t data;
	int flag;
	struct proc *p;
{
	int error = 0;

	switch (cmd) {
	default:
		error = ENODEV;
	}

	return error;
}

#if defined(INET) && defined(PLIP)
static void
plipattach(struct lpt_softc *sc)
{
#ifdef	__NetBSD__
	struct ifnet *ifp = &sc->sc_ethercom.ec_if;
#else
	struct ifnet *ifp = &sc->sc_arpcom.ac_if;
#endif
	u_int8_t myaddr[ETHER_ADDR_LEN];

	sc->sc_ifbuf = NULL;
	snprintf(ifp->if_xname, sizeof ifp->if_xname,
	    "plip%d", sc->sc_dev.dv_unit);
	bzero(myaddr, sizeof(myaddr));
	ifp->if_softc = sc;
	ifp->if_start = plipstart;
	ifp->if_ioctl = plipioctl;
	ifp->if_watchdog = 0;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_NOTRAILERS;
	bzero(&sc->sc_pliptimeout, sizeof(struct timeout));

	if_attach(ifp);
	ether_ifattach(ifp);
	ifp->if_mtu = PLIPMTU;

#if NBPFILTER > 0
	bpfattach(&ifp->if_bpf, ifp, DLT_EN10MB, sizeof(struct ether_header));
#endif
	/*
	 * We hope to get Charle's MI softint establish RSN - the
	 * current hack involves patching icu.s and hardcoding
	 * the softinterupts in a complete unrelated peace
	 * of code....
	sc->sc_ifsoftint = isa_intr_establish(SOFTINT, 0, ISA_IPL_NET,
				plipsoftint, sc);
	 */
}

/*
 * Process an ioctl request.
 */
static int
plipioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct proc *p = curproc;
	struct lpt_softc *sc = (struct lpt_softc *) ifp->if_softc;
	u_char control = sc->sc_control;
	struct ifaddr *ifa = (struct ifaddr *)data;
	struct ifreq *ifr = (struct ifreq *)data;
	bus_space_tag_t iot = sc->sc_iot;
	bus_space_handle_t ioh = sc->sc_ioh;
	struct sockaddr_dl *sdl;
	int error = 0;

	switch (cmd) {
	case SIOCSIFFLAGS:
		if (((ifp->if_flags & IFF_UP) == 0) &&
		    (ifp->if_flags & IFF_RUNNING)) {
		        ifp->if_flags &= ~IFF_RUNNING;
			control = LPC_SELECT | LPC_NINIT;
			bus_space_write_1(iot, ioh, lpt_control, control);

			if (sc->sc_ifbuf)
				free(sc->sc_ifbuf, M_DEVBUF);
			sc->sc_ifbuf = NULL;
		}
		if (((ifp->if_flags & IFF_UP)) &&
		    ((ifp->if_flags & IFF_RUNNING) == 0)) {
			if (sc->sc_state) {
				error = EBUSY;
				break;
			}
			if (sc->sc_ih == 0) {
				error = EINVAL;
				break;
			}
			if (!sc->sc_ifbuf)
				sc->sc_ifbuf =
					malloc(ifp->if_mtu + ifp->if_hdrlen,
					       M_DEVBUF, M_WAITOK);
		        ifp->if_flags |= IFF_RUNNING;
			bus_space_write_1(iot, ioh, lpt_control, control & ~LPC_IENABLE);
			bus_space_write_1(iot, ioh, lpt_data, 0);
			bus_space_write_1(iot, ioh, lpt_control, control |= LPC_IENABLE);
		}
		break;

	case SIOCSIFADDR:
		sdl = ifp->if_sadl;
		if (ifa->ifa_addr->sa_family == AF_INET) {
			if (!sc->sc_ifbuf)
				sc->sc_ifbuf =
					malloc(PLIPMTU + ifp->if_hdrlen,
					       M_DEVBUF, M_WAITOK);
			LLADDR(sdl)[0] = 0xfc;
			LLADDR(sdl)[1] = 0xfc;
			bcopy((caddr_t)&IA_SIN(ifa)->sin_addr,
			      (caddr_t)&LLADDR(sdl)[2], 4);
			ifp->if_flags |= IFF_RUNNING | IFF_UP;
			bus_space_write_1(iot, ioh, lpt_control, control & ~LPC_IENABLE);
			bus_space_write_1(iot, ioh, lpt_data, 0);
			bus_space_write_1(iot, ioh, lpt_control, control |= LPC_IENABLE);
			arp_ifinit(&sc->sc_arpcom, ifa);
		} else
			error = EAFNOSUPPORT;
		break;

	case SIOCAIFADDR:
	case SIOCDIFADDR:
	case SIOCSIFDSTADDR:
		if (ifa->ifa_addr->sa_family != AF_INET)
			error = EAFNOSUPPORT;
		break;

	case SIOCSIFMTU:
        	if ((error = suser(p, 0)))
            		return(error);
		if (ifp->if_mtu != ifr->ifr_metric) {
		        ifp->if_mtu = ifr->ifr_metric;
			if (sc->sc_ifbuf) {
				free(sc->sc_ifbuf, M_DEVBUF);
				sc->sc_ifbuf =
					malloc(ifp->if_mtu + ifp->if_hdrlen,
					       M_DEVBUF, M_WAITOK);
			}
		}
		break;

	default:
		error = EINVAL;
	}
	sc->sc_control = control;
	return (error);
}

void
plipsoftint(void)
{
	/* while the MI softint framework isn't there, we check
	   check all lpt devices */
	struct device *dev;

	for (dev = alldevs.tqh_first; dev; dev = dev->dv_list.tqe_next) {
		if (dev->dv_cfdata->cf_driver == &lpt_cd) {
			int pending;
			struct lpt_softc *sc = (struct lpt_softc*)dev;

			pending = sc->sc_pending;
			while (sc->sc_pending & PLIP_IPENDING) {
				pending |= sc->sc_pending;
				sc->sc_pending = 0;
				plipinput(sc);
			}

			if (pending & PLIP_OPENDING)
				plipoutput(sc);
		}
	}
}

static int
plipreceive(struct lpt_softc *sc, u_char *buf, int len)
{
	bus_space_tag_t iot = sc->sc_iot;
	bus_space_handle_t ioh = sc->sc_ioh;
	int i;
	u_char cksum = 0, cl, ch;

	while (len--) {
		i = PLIPMXSPIN2;
		while (((cl = STABILIZE(iot, ioh, lpt_status)) & LPS_NBSY) != 0)
			if (i-- < 0) return -1;
		cl = (cl >> 3) & 0x0f;
		bus_space_write_1(iot, ioh, lpt_data, 0x11);
		while (((ch = STABILIZE(iot, ioh, lpt_status)) & LPS_NBSY) == 0)
			if (i-- < 0) return -1;
		cl |= (ch << 1) & 0xf0;
		bus_space_write_1(iot, ioh, lpt_data, 0x01);
		cksum += (*buf++ = cl);
	}
	return(cksum);
}

static void
pliprxenable(void *arg)
{
	struct lpt_softc *sc = arg;
	bus_space_tag_t iot = sc->sc_iot;
	bus_space_handle_t ioh = sc->sc_ioh;
	bus_space_write_1(iot, ioh, lpt_control, sc->sc_control |= LPC_IENABLE);
}

static void
plipinput(struct lpt_softc *sc)
{
#ifdef	__NetBSD__
	struct ifnet *ifp = &sc->sc_ethercom.ec_if;
#else
	struct ifnet *ifp = &sc->sc_arpcom.ac_if;
#endif
	bus_space_tag_t iot = sc->sc_iot;
	bus_space_handle_t ioh = sc->sc_ioh;
	struct mbuf *m;
	struct ether_header *eh;
	u_char *p = sc->sc_ifbuf, minibuf[4];
	int s, len, cksum;

	if (((ifp->if_flags & IFF_LINK2) == 0) &&
	    (!(STABILIZE(iot, ioh, lpt_status) & LPS_NACK))) {
		bus_space_write_1(iot, ioh, lpt_control, sc->sc_control |= LPC_IENABLE);
		ifp->if_collisions++;
		return;
	}

	bus_space_write_1(iot, ioh, lpt_data, 0x01);
	bus_space_write_1(iot, ioh, lpt_control, sc->sc_control &= ~LPC_IENABLE);

	if (sc->sc_ifierrs)
		timeout_del(&sc->sc_pliptimeout);

	if (plipreceive(sc, minibuf, 2) < 0) goto err;
	len = (minibuf[1] << 8) | minibuf[0];
	if (len > (ifp->if_mtu + ifp->if_hdrlen)) {
		log(LOG_NOTICE, "%s: packet > MTU\n", ifp->if_xname);
		goto err;
	}
	if ((cksum = plipreceive(sc, p, len)) < 0) goto err;

	if (plipreceive(sc, minibuf, 1) < 0) goto err;
	if (cksum != minibuf[0]) {
		log(LOG_NOTICE, "%s: checksum error\n", ifp->if_xname);
		goto err;
	}
	bus_space_write_1(iot, ioh, lpt_data, 0x00);

	s = splimp();
	if ((m = m_devget(sc->sc_ifbuf, len, 0, ifp, NULL)) != NULL) {
		/* We assume that the header fit entirely in one mbuf. */
		eh = mtod(m, struct ether_header *);
#if NBPFILTER > 0
		/*
		 * Check if there's a BPF listener on this interface.
		 * If so, hand off the raw packet to bpf.
		 */
		if (ifp->if_bpf) {
			bpf_mtap(ifp->if_bpf, m);
		}
#endif
		/* We assume the header fit entirely in one mbuf. */
		m_adj(m, sizeof(struct ether_header));
		ether_input_mbuf(ifp, m);
	}
	splx(s);
	sc->sc_ifierrs = 0;
	ifp->if_ipackets++;
	bus_space_write_1(iot, ioh, lpt_control, sc->sc_control |= LPC_IENABLE);
	return;

err:
	bus_space_write_1(iot, ioh, lpt_data, 0x00);

	if (sc->sc_ifierrs < PLIPMXERRS) {
		if (sc->sc_ifierrs > 4 && (STABILIZE(iot, ioh, lpt_status) & LPS_NBSY)) {
			/* Avoid interrupt nesting ... */
			sc->sc_ifierrs = PLIPMXERRS - 1;
		}
		bus_space_write_1(iot, ioh, lpt_control, sc->sc_control |= LPC_IENABLE);
	} else {
		/* We are not able to send or receive anything for now,
		 * so stop wasting our time and leave the interrupt
		 * disabled.
		 */
		if (sc->sc_ifierrs == PLIPMXERRS)
			log(LOG_NOTICE, "%s: rx hard error\n", ifp->if_xname);
		/* But we will retry from time to time. */
		timeout_set(&sc->sc_pliptimeout, pliprxenable, sc);
		timeout_add(&sc->sc_pliptimeout, PLIPRETRY * 10);
	}
	ifp->if_ierrors++;
	sc->sc_ifierrs++;
	return;
}

static int
pliptransmit(struct lpt_softc *sc, u_char *buf, int len)
{
	bus_space_tag_t iot = sc->sc_iot;
	bus_space_handle_t ioh = sc->sc_ioh;
	int i;
	u_char cksum = 0, c;

	while (len--) {
		i = PLIPMXSPIN2;
		cksum += (c = *buf++);
		while ((STABILIZE(iot, ioh, lpt_status) & LPS_NBSY) == 0)
			if (i-- < 0) return -1;
		bus_space_write_1(iot, ioh, lpt_data, c & 0x0f);
		bus_space_write_1(iot, ioh, lpt_data, (c & 0x0f) | 0x10);
		c >>= 4;
		while ((STABILIZE(iot, ioh, lpt_status) & LPS_NBSY) != 0)
			if (i-- < 0) return -1;
		bus_space_write_1(iot, ioh, lpt_data, c | 0x10);
		bus_space_write_1(iot, ioh, lpt_data, c);
	}
	return(cksum);
}

/*
 * Setup output on interface.
 */
static void
plipstart(struct ifnet *ifp)
{
	struct lpt_softc *sc = (struct lpt_softc *) ifp->if_softc;
	sc->sc_pending |= PLIP_OPENDING;
	/*softintr(sc->sc_ifsoftint);*/
	schednetisr(NETISR_PLIP);
}

static void
plipoutput(void *arg)
{
	struct lpt_softc *sc = arg;
#ifdef	__NetBSD__
	struct ifnet *ifp = &sc->sc_ethercom.ec_if;
#else
	struct ifnet *ifp = &sc->sc_arpcom.ac_if;
#endif
	bus_space_tag_t iot = sc->sc_iot;
	bus_space_handle_t ioh = sc->sc_ioh;
	struct mbuf *m0, *m;
	u_char minibuf[4], cksum;
	int len, i, s;

	if (ifp->if_flags & IFF_OACTIVE)
		return;
	ifp->if_flags |= IFF_OACTIVE;

	if (sc->sc_ifoerrs)
		timeout_del(&sc->sc_pliptimeout);

	for (;;) {
		s = splnet();
		IF_DEQUEUE(&ifp->if_snd, m0);
		splx(s);
		if (!m0)
			break;

#if NBPFILTER > 0
		if (ifp->if_bpf)
			bpf_mtap(ifp->if_bpf, m0);
#endif

		len = m0->m_pkthdr.len;
		minibuf[0] = 2;
		minibuf[1] = len;
		minibuf[2] = len >> 8;

		/* Trigger remote interrupt */
		i = PLIPMXSPIN1;
		do {
			if (sc->sc_pending & PLIP_IPENDING) {
				bus_space_write_1(iot, ioh, lpt_data, 0x00);
				sc->sc_pending = 0;
				plipinput(sc);
				i = PLIPMXSPIN1;
			} else if (i-- < 0)
				goto retry;
			/* Retrigger remote interrupt */
			bus_space_write_1(iot, ioh, lpt_data, 0x08);
		} while ((STABILIZE(iot, ioh, lpt_status) & LPS_NERR) == 0);
		bus_space_write_1(iot, ioh, lpt_control, sc->sc_control &= ~LPC_IENABLE);
		if (pliptransmit(sc, minibuf + 1, minibuf[0]) < 0) goto retry;
		for (cksum = 0, m = m0; m; m = m->m_next) {
			i = pliptransmit(sc, mtod(m, u_char *), m->m_len);
			if (i < 0) goto retry;
			cksum += i;
		}
		if (pliptransmit(sc, &cksum, 1) < 0) goto retry;
		i = PLIPMXSPIN2;
		while ((STABILIZE(iot, ioh, lpt_status) & LPS_NBSY) == 0)
			if (i-- < 0) goto retry;
		sc->sc_pending = 0;
		bus_space_write_1(iot, ioh, lpt_data, 0x00);

		ifp->if_opackets++;
		ifp->if_obytes += len + 4;
		sc->sc_ifoerrs = 0;
		m_freem(m0);
		bus_space_write_1(iot, ioh, lpt_control, sc->sc_control |= LPC_IENABLE);
	}
	ifp->if_flags &= ~IFF_OACTIVE;
	return;

retry:
	if (STABILIZE(iot, ioh, lpt_status) & LPS_NACK)
		ifp->if_collisions++;
	else
		ifp->if_oerrors++;

	ifp->if_flags &= ~IFF_OACTIVE;
	bus_space_write_1(iot, ioh, lpt_data, 0x00);

	if ((ifp->if_flags & (IFF_RUNNING | IFF_UP)) == (IFF_RUNNING | IFF_UP)
	    && sc->sc_ifoerrs < PLIPMXRETRY) {
		s = splnet();
		IF_PREPEND(&ifp->if_snd, m0);
		splx(s);
		timeout_set(&sc->sc_pliptimeout, plipoutput, sc);
		timeout_add(&sc->sc_pliptimeout, PLIPRETRY);
	} else {
		/* we are not able to send this... give up for now */
		if (sc->sc_ifoerrs == PLIPMXRETRY) {
			log(LOG_NOTICE, "%s: tx hard error\n", ifp->if_xname);
		}
		m_freem(m0);
	}
	bus_space_write_1(iot, ioh, lpt_control, sc->sc_control |= LPC_IENABLE);
	sc->sc_ifoerrs++;
}
#endif	/* PLIP and INET */
