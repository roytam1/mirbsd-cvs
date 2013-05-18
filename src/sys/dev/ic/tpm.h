/* $MirOS: src/sys/dev/ic/tpm.h,v 1.2 2009/02/22 12:24:25 tg Exp $ */

/*-
 * Copyright (c) 2009 Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 2003 Rick Wash <rwash@citi.umich.edu>
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

#ifndef TPM_H
#define TPM_H

struct timeout;

#define TPM_BUFFER_LEN	2048

struct tpm_softc {
	struct device 	sc_dev;			/* generic device info */
	/* device specific information */
	u_int8_t	buffer[TPM_BUFFER_LEN];	/* memory for requests and replies */
	int		type;			/* chipset type */
	int 		wait_timeout;		/* poll timeout counter */
	int		retval;			/* return value (length or error) */
	int		len;			/* size of data */
	struct timeout	tmo;			/* for polling */
	u_int16_t	base;			/* base address */
	uint8_t		initialised;		/* flag - initialised chip */
	uint8_t		open;			/* exclusive open flag */
	unsigned char	version[4];		/* Version number */
	unsigned char	vendor[5];		/* vendor name */
	enum tpm_poll_state {
		TPM_STATE_READY = 0,
		TPM_STATE_READ_START,
		TPM_STATE_WAIT_FOR_DATA,
		TPM_STATE_READ_DONE,
		TPM_STATE_WRITE_START,
		TPM_STATE_WRITE_BUSY,
		TPM_STATE_WRITE_WORKING,
		TPM_STATE_WRITE_DONE,
		TPM_STATE_ERROR,
		TPM_STATE_MAX
	}		state;			/* interrupt poll state */
};

enum tpm_chip_type {
	TPM_INVALID_CHIP = 0,
	ICH2LPC,
	ICH3LPCM,
	ICH4LPC,
	ICH4LPCM
};

struct tpm_attach_args {
	char *busname;
	enum tpm_chip_type chiptype;
};

int tpm_match(struct device *, void *, void *);
void tpm_attach(struct device *, struct device *, void *);

int tpmopen(dev_t dev, int flag, int mode, struct proc *p);
int tpmclose(dev_t dev, int flag, int mode, struct proc *p);
int tpmwrite(dev_t dev, struct uio *uio, int flags);
int tpmread(dev_t dev, struct uio *uio, int flags);
int tpmioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p);

#endif
