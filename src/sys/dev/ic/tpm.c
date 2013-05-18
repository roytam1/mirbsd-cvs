/* $MirOS: src/sys/dev/ic/tpm.c,v 1.4 2010/06/27 15:09:07 tg Exp $ */

/*-
 * Copyright (c) 2009, 2010
 *	Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 2003
 *	Rick Wash <rwash@citi.umich.edu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * TCPA TPM driver, bus independent code
 */

#include <sys/param.h>
#include <sys/device.h>
#include <sys/conf.h>
#include <sys/errno.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/timeout.h>
#include <machine/bus.h>
#include <machine/intr.h>
#include <machine/param.h>
#include <dev/pci/pcivar.h>
#include <dev/pci/pcireg.h>
#include <dev/pci/pcidevs.h>

#include <dev/ic/tpm.h>

/* #define TPM_DEBUG */

/* TPM addresses */
#define TPM_ADDR			0x4E
#define TPM_DATA			0x4F

/* write status bits */
#define STATUS_BIT_ABORT		0x01
#define STATUS_BIT_LASTBYTE		0x04

/* read status bits */
#define STATUS_BIT_BUSY			0x01
#define STATUS_BIT_DATA_AVAIL		0x02
#define STATUS_BIT_REWRITE		0x04

/* Timeout Numbers */
#define TPM_DELAY			50	/* in milliseconds */
#define TPM_TIMEOUT			((2*2*60*60) / TPM_DELAY)
#define TPM_TSLEEP_TIMEOUT		(2*60*hz)
#define TPM_CALLOUT_TIMEOUT		TPM_DELAY

int tpm_init(struct tpm_softc *sc, pci_chipset_tag_t pa_pc, pcitag_t pa_tag);
int tpm_recv(struct tpm_softc *sc, int count);
int tpm_send(struct tpm_softc *sc, int count);

void tpm_intr(void *data);
void tpm_read_data(struct tpm_softc *sc);
void tpm_send_data(struct tpm_softc *sc);

struct cfdriver tpm_cd = {
	NULL, "tpm", DV_DULL
};

struct tpm_softc *tpm_sc;

#ifndef SMALL_KERNEL
/* must match enum tpm_chip_type */
static const char *tpm_chip_names[] = {
	"<invalid>",
	"Intel ICH2 LPC",
	"Intel ICH3 LPC-M",
	"Intel ICH4 LPC",
	"Intel ICH4 LPC-M"
};
#endif


int
tpmopen(dev_t dev, int flag, int mode, struct proc *p)
{
#ifdef TPM_DEBUG
	printf("in tpmopen\n");
#endif /* TPM_DEBUG */

	/* Make sure it has been initialised */
	if (!tpm_sc || !tpm_sc->initialised)
		return (ENODEV);

	/* Only can be opened by one process at a time */
	/* XXX: concurrency hack */
	if (tpm_sc->open != 0)
		return (EBUSY);

	tpm_sc->open = 1;
	return (0);
}

int
tpmclose(dev_t dev, int flag, int mode, struct proc *p)
{
#ifdef TPM_DEBUG
	printf("in tpmclose\n");
#endif /* TPM_DEBUG */

	tpm_sc->open = 0;

	return (0);
}

int
tpmwrite(dev_t dev, struct uio *uio, int flags)
{
	size_t len;
	int rv;

	if (!tpm_sc || !tpm_sc->initialised)
		return (ENODEV);
	else if (!tpm_sc->open)
		return (EPERM);
	else if (tpm_sc->state != TPM_STATE_READY)
		return (EBUSY);

	len = min(uio->uio_resid, TPM_BUFFER_LEN);

	uiomove(tpm_sc->buffer, len, uio);

	tpm_sc->len = len;
	tpm_sc->state = TPM_STATE_WRITE_START;
	timeout_add(&tpm_sc->tmo, 1);
	while ((tpm_sc->state != TPM_STATE_WRITE_DONE) &&
	    (tpm_sc->state != TPM_STATE_ERROR))
		tsleep(tpm_sc->buffer, PRIBIO, "tpmwrite", TPM_TSLEEP_TIMEOUT);

	rv = tpm_sc->retval;
	tpm_sc->retval = 0;

	tpm_sc->state = TPM_STATE_READY;

#ifdef TPM_DEBUG
	printf("in tpmwrite\n");
#endif /* TPM_DEBUG */

	return (rv);
}

int
tpmread(dev_t dev, struct uio *uio, int flags)
{
	size_t len;
	int rv;

	if (!tpm_sc || !tpm_sc->initialised)
		return (ENODEV);
	else if (!tpm_sc->open)
		return (EPERM);
	else if (tpm_sc->state != TPM_STATE_READY)
		return (EBUSY);

#ifdef TPM_DEBUG
	printf("in tpmread\n");
#endif /* TPM_DEBUG */

	len = min(uio->uio_resid, TPM_BUFFER_LEN);

	if (len < 6)
		return (EIO);

	tpm_sc->len = len;
	tpm_sc->state = TPM_STATE_READ_START;
	timeout_add(&tpm_sc->tmo, 1);
	while ((tpm_sc->state != TPM_STATE_READ_DONE) &&
	    (tpm_sc->state != TPM_STATE_ERROR))
		tsleep(tpm_sc->buffer, PRIBIO, "tpmread", TPM_TSLEEP_TIMEOUT);

	rv = tpm_sc->retval;
	tpm_sc->retval = 0;

	if (tpm_sc->len > 0)
		uiomove(tpm_sc->buffer, tpm_sc->len, uio);

	tpm_sc->state = TPM_STATE_READY;

	return (rv);
}

int
tpmioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p)
{
	return (ENODEV);
}


int
tpm_match(struct device *parent, void *match, void *aux)
{
	struct tpm_attach_args *ta = aux;

	if (ta == NULL || strcmp(ta->busname, "tpm") ||
	    ta->chiptype == TPM_INVALID_CHIP)
		return (0);
	if (tpm_sc && tpm_sc->initialised) {
		printf("tpm: second %sch ignored\n", "mat");
		return (0);
	}
	return (1);
}

void
tpm_attach(struct device *parent, struct device *self, void *aux)
{
	struct tpm_attach_args *ta = aux;
	int notattach;

	if (tpm_sc && tpm_sc->initialised) {
		printf("tpm: second %sch ignored\n", "atta");
		return;
	}

	tpm_sc = (void *)self;
	tpm_sc->type = ta->chiptype;

	outb(TPM_ADDR, 0x08);		/* base addr lo */
	tpm_sc->base = inb(TPM_DATA);
	outb(TPM_ADDR, 0x09);		/* base addr hi */
	tpm_sc->base |= inb(TPM_DATA) << 8;

	/* Query the chip for its version */
	outb(TPM_ADDR, 0x00);
	tpm_sc->version[0] = inb(TPM_DATA);
	outb(TPM_ADDR, 0x01);
	tpm_sc->version[1] = inb(TPM_DATA);
	outb(TPM_ADDR, 0x02);
	tpm_sc->version[2] = inb(TPM_DATA);
	outb(TPM_ADDR, 0x03);
	tpm_sc->version[3] = inb(TPM_DATA);

	/* Query the chip for its vendor */
	outb(TPM_ADDR, 0x04);
	tpm_sc->vendor[0] = inb(TPM_DATA);
	outb(TPM_ADDR, 0x05);
	tpm_sc->vendor[1] = inb(TPM_DATA);
	outb(TPM_ADDR, 0x06);
	tpm_sc->vendor[2] = inb(TPM_DATA);
	outb(TPM_ADDR, 0x07);
	tpm_sc->vendor[3] = inb(TPM_DATA);
	tpm_sc->vendor[4] = '\0';

	notattach = (tpm_sc->vendor[0] == 0xFF) ? 1 : 0;
	printf(" port 0x%X (%s), version ", tpm_sc->base,
	    tpm_chip_names[tpm_sc->type]);
	if (tpm_sc->version[0] == 0xFF) {
		notattach |= 2;
		printf("failed");
	} else
		printf("%d.%d.%d.%d", tpm_sc->version[0], tpm_sc->version[1],
		    tpm_sc->version[2], tpm_sc->version[3]);
	printf(", vendor %s, %sattached\n",
	    (notattach & 1) ? "failed" : (const char *)tpm_sc->vendor,
	    notattach ? "not " : "");

	if (notattach)
		return;

	timeout_set(&tpm_sc->tmo, tpm_intr, tpm_sc);
	timeout_add(&tpm_sc->tmo, 1);

	tpm_sc->initialised = 1;
}

/* Lower half of the device driver.   This does the actual polling of the device
 * Uses NetBSD's callout to delay, so the kernel stays useful while polling
 */
void
tpm_intr(void *data)
{
	struct tpm_softc *sc = data;
	int status;
#ifdef __OpenBSD__
	int s;

	s = splnet();
#endif

	switch (sc->state) {
	case TPM_STATE_READY:
		/* XXX: Should this be here? */
#ifdef TPM_DEBUG
		printf("tpm: state ready\n");
#endif /* TPM_DEBUG */
		timeout_add(&sc->tmo, TPM_CALLOUT_TIMEOUT);
		break;
	case TPM_STATE_READ_START:	/* Wait till the chip is not busy */
#ifdef TPM_DEBUG
		printf("tpm: state read start\n");
#endif /* TPM_DEBUG */
		sc->wait_timeout++;
		if (sc->wait_timeout > TPM_TIMEOUT) {
			printf("tpm: timeout on read\n");
			sc->state = TPM_STATE_ERROR;
			sc->retval = EIO;
			wakeup(sc->buffer);
			break;
		}
		status = inb(sc->base + 1);
		if ((status & STATUS_BIT_BUSY) != 0) {
			timeout_add(&sc->tmo, TPM_CALLOUT_TIMEOUT);
			break;
		}
		sc->state = TPM_STATE_WAIT_FOR_DATA;
		sc->wait_timeout = 0;
		/* fallthrough */
	case TPM_STATE_WAIT_FOR_DATA:	/* Wait till there is data available */
#ifdef TPM_DEBUG
		printf("tpm: state wait for data\n");
#endif /* TPM_DEBUG */
		sc->wait_timeout++;
		if (sc->wait_timeout > TPM_TIMEOUT) {
			printf("tpm: timeout waiting for data\n");
			sc->state = TPM_STATE_ERROR;
			sc->retval = EIO;
			wakeup(sc->buffer);
			break;
		}
		status = inb(sc->base + 1);
		status &= (STATUS_BIT_BUSY | STATUS_BIT_DATA_AVAIL);
		if ( status != STATUS_BIT_DATA_AVAIL ) {
			timeout_add(&sc->tmo, TPM_CALLOUT_TIMEOUT);
			break;
		}

		/* Read Data */
		sc->wait_timeout = 0;
		sc->retval = 0;
		sc->state = TPM_STATE_READ_DONE;
		tpm_read_data(sc);
		wakeup(sc->buffer);
		break;
	case TPM_STATE_WRITE_START:	/* Wait till the chip is not busy */
		outb(sc->base+1, STATUS_BIT_ABORT);
#ifdef TPM_DEBUG
		printf("tpm: state write start\n");
#endif /* TPM_DEBUG */
		sc->state = TPM_STATE_WRITE_BUSY;
	case TPM_STATE_WRITE_BUSY:
		sc->wait_timeout++;
#ifdef TPM_DEBUG
		printf("tpm:state write busy\n");
#endif /* TPM_DEBUG */
		if (sc->wait_timeout > TPM_TIMEOUT) {
			printf("tpm: timeout waiting to write\n");
			sc->state = TPM_STATE_ERROR;
			sc->retval = EIO;
			wakeup(sc->buffer);
			break;
		}
		status = 0;
		status = inb(sc->base + 1);
#ifdef TPM_DEBUG
		printf("tpm: base: %08x, status bit: %08x\n", sc->base, status);
#endif /* TPM_DEBUG */
		if ( (status & STATUS_BIT_BUSY) != 0) {
			timeout_add(&sc->tmo, TPM_CALLOUT_TIMEOUT);
			break;
		}
		sc->wait_timeout = 0;
		sc->retval = 0;
		sc->state = TPM_STATE_WRITE_WORKING;

		/* Send Data */
		tpm_send_data(sc);
		/* fallthrough */
	case TPM_STATE_WRITE_WORKING:	/* Wait till the chip is working, done, or an error */
#ifdef TPM_DEBUG
		printf("tpm: state write working\n");
#endif /* TPM_DEBUG */
		sc->wait_timeout++;
		if (sc->wait_timeout > TPM_TIMEOUT) {
			printf("tpm: timeout after writing\n");
			sc->state = TPM_STATE_ERROR;
			sc->retval = EIO;
			wakeup(sc->buffer);
			break;
		}
		status = inb(sc->base + 1);
		if ( (status & (STATUS_BIT_BUSY | STATUS_BIT_DATA_AVAIL | STATUS_BIT_REWRITE)) == 0) {
			timeout_add(&sc->tmo, TPM_CALLOUT_TIMEOUT);
			break;
		}
		sc->state = TPM_STATE_WRITE_DONE;

		if ( (status & STATUS_BIT_REWRITE) != 0) {
			sc->retval = EIO;
			sc->state = TPM_STATE_ERROR;
		}
		wakeup(sc->buffer);
		break;
	default:
		printf("tpm: error in interrupt\n");
		sc->state = TPM_STATE_ERROR;
		sc->retval = EIO;
		wakeup(sc->buffer);
	}

#ifdef __OpenBSD__
	splx(s);
#endif
}

void
tpm_read_data(struct tpm_softc *sc)
{
	int i;
	int status;
	char *buffer = sc->buffer;
	u_int32_t size;

	for (i=0; i<6; i++) {
		status = inb(sc->base+1);
		if ( (status & STATUS_BIT_DATA_AVAIL) == 0) {
			printf("tpm: error reading header\n");
			sc->len = 0;
			sc->retval = EIO;
			sc->state = TPM_STATE_ERROR;;
			return;
		}
		*buffer++ = inb(sc->base);
	}

#ifdef __OpenBSD__
	size = betoh32(*(u_int32_t *)(sc->buffer + 2));
#else
	size = be32toh(*(u_int32_t *)(sc->buffer + 2));
#endif
	if (sc->len < size) {
		sc->len = 0;
		sc->retval = EIO;
		sc->state = TPM_STATE_ERROR;
		return;
	}

	for (; i < size; i++) {
		status = inb(sc->base+1);
		if ( (status & STATUS_BIT_DATA_AVAIL) == 0) {
			printf("tpm: error reading data\n");
			sc->len = 0;
			sc->retval = EIO;
			sc->state = TPM_STATE_ERROR;
			return;
		}
		*buffer++ = inb(sc->base);
	}

	/* Make sure data available is gone */
	status = inb(sc->base+1);
	if ( (status & STATUS_BIT_DATA_AVAIL) != 0) {
		printf("tpm: data avail is stuck\n");
		sc->len = 0;
		sc->retval = EIO;
		sc->state = TPM_STATE_ERROR;
		return;
	}

	/* Send an abort */
	outb(sc->base+1, STATUS_BIT_ABORT);

	sc->len = size;
	/* TODO: crc check? */
}

void
tpm_send_data(struct tpm_softc *sc)
{
	int i;

	/* Write everything but the last byte */
	for (i = 0; i < sc->len; i++) {
		outb(sc->base, sc->buffer[i]);
	}

	/* Send last byte */
	outb(sc->base+1, STATUS_BIT_LASTBYTE);

	/* Send last byte */
	outb(sc->base, sc->buffer[i]);
}
