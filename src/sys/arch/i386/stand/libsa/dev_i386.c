/**	$MirOS: src/sys/arch/i386/stand/libsa/dev_i386.c,v 1.14 2009/01/11 00:32:40 tg Exp $	*/
/*	$OpenBSD: dev_i386.c,v 1.30 2007/06/27 20:29:37 mk Exp $	*/

/*
 * Copyright (c) 2009 Thorsten Glaser
 * Copyright (c) 2004 Tom Cosgrove
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
 */

#define USE_PXE

#ifdef SMALL_BOOT
#undef USE_PXE
#endif

#include "libsa.h"
#include "biosdev.h"
#include <sys/param.h>
#include <dev/cons.h>
#include <sys/disklabel.h>
#include "disk.h"

extern int debug;

#ifdef USE_PXE
extern char use_bootmac;
#endif

/* XXX use slot for 'rd' for 'hd' pseudo-device */
const char bdevs[][4] = {
	"wd", "", "fd", "", "sd", "st", "cd", "mcd",
	"", "", "", "", "", "", "", "scd", "", "hd", ""
};
const int nbdevs = NENTS(bdevs);

const char cdevs[][4] = {
	"cn", "", "", "", "", "", "", "",
	"com", "", "", "", "pc"
};
const int ncdevs = NENTS(cdevs);

/* pass dev_t to the open routines */
int
devopen(struct open_file *f, const char *fname, char **file)
{
	char *cp;
	int rc = 1;
	struct devsw_prefix_match *dm;

	*file = cp = (char *)fname;

#ifdef DEBUG
	if (debug)
		printf("devopen(%s):", fname);
#endif

	/* get the colon-separated device prefix */
	while (*cp && *cp != ':')
		++cp;

	/**
	 * (*file) = "pref:rest"
	 * cp ------------^
	 */
#ifdef DEBUG
	if (debug) {
		if (*cp) {
			char *pp = *file;

			printf(" pfx:[");
			while (pp < cp)
				putchar(*pp++);
			putchar(']');
		} else
			printf(" {no prefix}");
	}
#endif
	for (dm = devsw_match; dm->devops; ++dm) {
#ifdef DEBUG
		if (debug)
			printf(" match?[%s%s%s]", dm->devops->dv_name,
			    dm->prefix[0] ? "?" : "", dm->prefix);
#endif
		if (dm->prefix[0])
			/*
			 * want a prefix; loop if the file has none
			 * or it does not match
			 */
			if (!*cp || strncmp(*file, dm->prefix, cp - *file)) {
#ifdef DEBUG
				if (debug)
					printf("=NO");
#endif
				continue;
			}
		/* prefix matches or is not requested */
		f->f_ops = dm->fsops;
		f->f_dev = dm->devops;
		*file = dm->strip && *cp ? cp + 1 : (char *)fname;
		if ((rc = (*f->f_dev->dv_open)(f, file)) == 0) {
#ifdef USE_PXE
			use_bootmac = dm->networked;
#endif
#ifdef DEBUG
			if (debug)
				printf("=OK(%s) net=%d dev=%s fs=%s\n", *file,
				    dm->networked,
				    f->f_dev ? f->f_dev->dv_name : "(NULL)",
				    f->f_ops ? f->f_ops->name : "(NULL)");
#endif
			return (0);
		}
#ifdef DEBUG
		if (debug)
			printf("=%u", rc);
#endif
	}

	*file = (char *)fname;
	f->f_ops = NULL;
	if (f->f_flags & F_NODEV)
		f->f_dev = NULL;
	else
		/* XXX why? and is this correct? */
		f->f_dev = &devsw[0];
#ifdef DEBUG
	if (debug)
		printf(" FAIL %s%s\n", f->f_dev ? "dev=" : "nodev",
		    f->f_dev ? f->f_dev->dv_name : "");
#endif
	return (rc);
}

void
devboot(dev_t bootdev, char *p)
{
	char *cp;
	if (start_dip) {
		cp = start_dip->name;
		while ((*p++ = *cp++))
			;
		--p;
		if (p[-1] >= '0' && p[-1] <= '9')
			*p++ = 'a';
	}
	*p = '\0';
}

int pch_pos = 0;

void
putchar(int c)
{
	switch (c) {
	case '\177':	/* DEL erases */
		cnputc('\b');
		cnputc(' ');
	case '\b':
		cnputc('\b');
		if (pch_pos)
			pch_pos--;
		break;
	case '\t':
		do
			cnputc(' ');
		while (++pch_pos % 8);
		break;
	case '\n':
	case '\r':
		cnputc(c);
		pch_pos=0;
		break;
	default:
		cnputc(c);
		pch_pos++;
		break;
	}
}

int
getchar(void)
{
	register int c = cngetc();

	if (c == '\r')
		c = '\n';

	if ((c < ' ' && c != '\n') || c == '\177')
		return c;

	putchar(c);

	return c;
}

char ttyname_buf[8];

char *
ttyname(int fd)
{
	snprintf(ttyname_buf, sizeof ttyname_buf, "%s%d",
	    cdevs[major(cn_tab->cn_dev)], minor(cn_tab->cn_dev));

	return ttyname_buf;
}

dev_t
ttydev(char *name)
{
	int i, unit = -1;
	char *no = name + strlen(name) - 1;

	while (no >= name && *no >= '0' && *no <= '9')
		unit = (unit < 0 ? 0 : (unit * 10)) + *no-- - '0';
	if (no < name || unit < 0)
		return NODEV;
	for (i = 0; i < ncdevs; i++)
		if (strncmp(name, cdevs[i], no - name + 1) == 0)
			return (makedev(i, unit));
	return NODEV;
}

int
cnspeed(dev_t dev, int sp)
{
	if (major(dev) == 8)	/* comN */
		return (comspeed(dev, sp));

	/* pc0 and anything else */
	return 9600;
}
