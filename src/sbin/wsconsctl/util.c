/*	$OpenBSD: util.c,v 1.30 2005/05/31 15:33:57 brad Exp $ */
/*	$NetBSD: util.c,v 1.8 2000/03/14 08:11:53 sato Exp $ */

/*-
 * Copyright (c) 1998 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Juergen Hannken-Illjes.
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
 *	This product includes software developed by the NetBSD
 *	Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/time.h>
#include <dev/wscons/wsconsio.h>
#include <dev/wscons/wsksymdef.h>
#include <err.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "wsconsctl.h"

#define TABLEN(t)		(sizeof(t)/sizeof(t[0]))

extern struct wskbd_map_data kbmap;	/* from keyboard.c */
extern struct wskbd_map_data newkbmap;	/* from map_parse.y */

struct nameint {
	int value;
	char *name;
};

static const struct nameint kbtype_tab[] = {
	{ WSKBD_TYPE_LK201,	"lk201" },
	{ WSKBD_TYPE_LK401,	"lk401" },
	{ WSKBD_TYPE_PC_XT,	"pc-xt" },
	{ WSKBD_TYPE_PC_AT,	"pc-at" },
	{ WSKBD_TYPE_USB,	"usb" },
	{ WSKBD_TYPE_NEXT,	"NeXT" },
	{ WSKBD_TYPE_HPC_KBD,	"hpc-kbd" },
	{ WSKBD_TYPE_HPC_BTN,	"hpc-btn" },
	{ WSKBD_TYPE_ADB,	"adb" },
	{ WSKBD_TYPE_SUN,	"sun" },
	{ WSKBD_TYPE_SUN5,	"sun5" },
	{ WSKBD_TYPE_HIL,	"hil" },
	{ WSKBD_TYPE_GSC,	"hp-ps2" },
	{ WSKBD_TYPE_LUNA,	"luna" },
	{ WSKBD_TYPE_ZAURUS,	"zaurus" },
	{ WSKBD_TYPE_DOMAIN,	"domain" }
};

static const struct nameint mstype_tab[] = {
	{ WSMOUSE_TYPE_VSXXX,	"dec-tc" },
	{ WSMOUSE_TYPE_PS2,	"ps2" },
	{ WSMOUSE_TYPE_USB,	"usb" },
	{ WSMOUSE_TYPE_LMS,	"lms" },
	{ WSMOUSE_TYPE_MMS,	"mms" },
	{ WSMOUSE_TYPE_TPANEL,	"touch-panel" },
	{ WSMOUSE_TYPE_NEXT,	"NeXT" },
	{ WSMOUSE_TYPE_ARCHIMEDES, "archimedes" },
	{ WSMOUSE_TYPE_ADB,	"adb" },
	{ WSMOUSE_TYPE_HIL,	"hil" },
	{ WSMOUSE_TYPE_LUNA,	"luna" },
	{ WSMOUSE_TYPE_DOMAIN,	"domain" }
};

static const struct nameint dpytype_tab[] = {
	{ WSDISPLAY_TYPE_UNKNOWN,	"unknown" },
	{ WSDISPLAY_TYPE_PM_MONO,	"dec-pm-mono" },
	{ WSDISPLAY_TYPE_PM_COLOR,	"dec-pm-color" },
	{ WSDISPLAY_TYPE_CFB,		"dec-cfb" },
	{ WSDISPLAY_TYPE_XCFB,		"dec-xcfb" },
	{ WSDISPLAY_TYPE_MFB,		"dec-mfb" },
	{ WSDISPLAY_TYPE_SFB,		"dec-sfb" },
	{ WSDISPLAY_TYPE_ISAVGA,	"vga-isa" },
	{ WSDISPLAY_TYPE_PCIVGA,	"vga-pci" },
	{ WSDISPLAY_TYPE_TGA,		"dec-tga-pci" },
	{ WSDISPLAY_TYPE_SFBP,		"dec-sfb+" },
	{ WSDISPLAY_TYPE_PCIMISC,	"generic-pci" },
	{ WSDISPLAY_TYPE_NEXTMONO,	"next-mono" },
	{ WSDISPLAY_TYPE_PX,		"dex-px" },
	{ WSDISPLAY_TYPE_PXG,		"dex-pxg" },
	{ WSDISPLAY_TYPE_TX,		"dex-tx" },
	{ WSDISPLAY_TYPE_HPCFB,		"generic-hpc" },
	{ WSDISPLAY_TYPE_VIDC,		"arm-vidc" },
	{ WSDISPLAY_TYPE_SPX,		"dec-spx" },
	{ WSDISPLAY_TYPE_GPX,		"dec-gpx" },
	{ WSDISPLAY_TYPE_LCG,		"dec-lcg" },
	{ WSDISPLAY_TYPE_VAX_MONO,	"dec-mono" },
	{ WSDISPLAY_TYPE_SB_P9100,	"p9100" },
	{ WSDISPLAY_TYPE_EGA,		"ega" },
	{ WSDISPLAY_TYPE_DCPVR,		"powervr" },
	{ WSDISPLAY_TYPE_SUN24,		"sun24" },
	{ WSDISPLAY_TYPE_SUNBW,		"sunbw" },
	{ WSDISPLAY_TYPE_STI,		"hp-sti" },
	{ WSDISPLAY_TYPE_SUNCG3,	"suncg3" },
	{ WSDISPLAY_TYPE_SUNCG6,	"suncg6" },
	{ WSDISPLAY_TYPE_SUNFFB,	"sunffb" },
	{ WSDISPLAY_TYPE_SUNCG14,	"suncg14" },
	{ WSDISPLAY_TYPE_SUNCG2,	"suncg2" },
	{ WSDISPLAY_TYPE_SUNCG4,	"suncg4" },
	{ WSDISPLAY_TYPE_SUNCG8,	"suncg8" },
	{ WSDISPLAY_TYPE_SUNTCX,	"suntcx" },
	{ WSDISPLAY_TYPE_AGTEN,		"agten" },
	{ WSDISPLAY_TYPE_XVIDEO,	"xvideo" },
	{ WSDISPLAY_TYPE_SUNCG12,	"suncg12" },
	{ WSDISPLAY_TYPE_MGX,		"mgx" },
	{ WSDISPLAY_TYPE_SB_P9000,	"p9000" },
	{ WSDISPLAY_TYPE_RFLEX,		"rasterflex" },
	{ WSDISPLAY_TYPE_LUNA,		"luna" },
	{ WSDISPLAY_TYPE_DVBOX,		"davinci" },
	{ WSDISPLAY_TYPE_GBOX,		"gatorbox" },
	{ WSDISPLAY_TYPE_RBOX,		"renaissance" },
	{ WSDISPLAY_TYPE_HYPERION,	"hyperion" },
	{ WSDISPLAY_TYPE_TOPCAT,	"topcat" },
	{ WSDISPLAY_TYPE_PXALCD,	"pxalcd" }
};

static const struct nameint kbdenc_tab[] = {
	KB_ENCTAB
};

static const struct nameint kbdvar_tab[] = {
	KB_VARTAB
};

char *int2name(int, int, const struct nameint *, int);
int name2int(char *, const struct nameint *, int);
void print_kmap(struct wskbd_map_data *);

struct field *
field_by_name(struct field *field_tab, char *name)
{
	const char *p = strchr(name, '.');

	if (!p++)
		errx(1, "%s: illegal variable name", name);

	for (; field_tab->name; field_tab++)
		if (strcmp(field_tab->name, p) == 0)
			return (field_tab);

	errx(1, "%s: not found", name);
}

struct field *
field_by_value(struct field *field_tab, void *addr)
{
	for (; field_tab->name; field_tab++)
		if (field_tab->valp == addr)
			return (field_tab);

	errx(1, "internal error: field_by_value: not found");
}

char *
int2name(int val, int uflag, const struct nameint *tab, int len)
{
	static char tmp[20];
	int i;

	for (i = 0; i < len; i++)
		if (tab[i].value == val)
			return(tab[i].name);

	if (uflag) {
		snprintf(tmp, sizeof(tmp), "unknown_%d", val);
		return(tmp);
	} else
		return(NULL);
}

int
name2int(char *val, const struct nameint *tab, int len)
{
	int i;

	for (i = 0; i < len; i++)
		if (strcmp(tab[i].name, val) == 0)
			return(tab[i].value);
	return(-1);
}

void
pr_field(const char *pre, struct field *f, const char *sep)
{
	struct field_pc *pc;
	u_int flags;
	int i, n;
	char *p;

	if (sep)
		printf("%s.%s%s", pre, f->name, sep);

	switch (f->format) {
	case FMT_UINT:
		printf("%u", *((u_int *) f->valp));
		break;
	case FMT_INT:
		printf("%d", *((int *) f->valp));
		break;
	case FMT_BOOL:
		printf("%s", *((u_int *) f->valp)? "on" : "off");
		break;
	case FMT_PC:
		pc = f->valp;
		i = pc->max - pc->min;
		n = pc->cur - pc->min;
		printf("%u.%02u%%", n * 100 / i, ((n * 100) % i) * 100 / i);
		break;
	case FMT_KBDTYPE:
		p = int2name(*((u_int *) f->valp), 1,
			     kbtype_tab, TABLEN(kbtype_tab));
		printf("%s", p);
		break;
	case FMT_MSTYPE:
		p = int2name(*((u_int *) f->valp), 1,
			     mstype_tab, TABLEN(mstype_tab));
		printf("%s", p);
		break;
	case FMT_DPYTYPE:
		p = int2name(*((u_int *) f->valp), 1,
			     dpytype_tab, TABLEN(dpytype_tab));
		printf("%s", p);
		break;
	case FMT_KBDENC:
		p = int2name(KB_ENCODING(*((u_int *) f->valp)), 1,
			     kbdenc_tab, TABLEN(kbdenc_tab));
		printf("%s", p);

		flags = KB_VARIANT(*((u_int *) f->valp));
		for (i = 0; i < 32; i++) {
			if (!(flags & (1 << i)))
				continue;
			p = int2name(flags & (1 << i), 1,
				     kbdvar_tab, TABLEN(kbdvar_tab));
			printf(".%s", p);
		}
		break;
	case FMT_KBMAP:
		print_kmap((struct wskbd_map_data *) f->valp);
		break;
	default:
		errx(1, "internal error: pr_field: no format %d", f->format);
		break;
	}

	printf("\n");
}

void
rd_field(struct field *f, char *val, int merge)
{
	struct wscons_keymap *mp;
	struct field_pc *pc;
	u_int u, r, fr;
	char *p;
	int i;

	switch (f->format) {
	case FMT_UINT:
		if (sscanf(val, "%u", &u) != 1)
			errx(1, "%s: not a number", val);
		if (merge)
			*((u_int *) f->valp) += u;
		else
			*((u_int *) f->valp) = u;
		break;
	case FMT_INT:
		if (sscanf(val, "%d", &i) != 1)
			errx(1, "%s: not a number", val);
		if (merge)
			*((int *) f->valp) += i;
		else
			*((int *) f->valp) = i;
		break;
	case FMT_BOOL:
		if (*val != 'o' || (val[1] != 'n' &&
		    (val[1] != 'f' || val[2] != 'f')))
			errx(1, "%s: invalid value (on/off)", val);
		*((u_int *) f->valp) = val[1] == 'n'? 1 : 0;
		break;
	case FMT_PC:
		fr = 0;
		if ((i = sscanf(val, "%u.%u%%", &u, &fr)) != 2 && i != 1)
			errx(1, "%s: not a valid number", val);
		pc = f->valp;
		r = pc->max - pc->min;
		i = pc->min + (r * u) / 100 + (r * fr) / 100 / 100;
		if (merge == '+')
			pc->cur += i;
		else if (merge == '-')
			pc->cur -= i;
		else
			pc->cur = i;
		if (pc->cur > pc->max)
			pc->cur = pc->max;
		if (pc->cur < pc->min)
			pc->cur = pc->min;
		break;
	case FMT_KBDENC:
		p = strchr(val, '.');
		if (p != NULL)
			*p++ = '\0';

		i = name2int(val, kbdenc_tab, TABLEN(kbdenc_tab));
		if (i == -1)
			errx(1, "%s: not a valid encoding", val);
		*((u_int *) f->valp) = i;

		while (p) {
			val = p;
			p = strchr(p, '.');
			if (p != NULL)
				*p++ = '\0';
			i = name2int(val, kbdvar_tab, TABLEN(kbdvar_tab));
			if (i == -1)
				errx(1, "%s: not a valid variant", val);
			*((u_int *) f->valp) |= i;
		}
		break;
	case FMT_KBMAP:
		if (! merge)
			kbmap.maplen = 0;
		map_scan_setinput(val);
		yyparse();
		if (merge) {
			if (newkbmap.maplen < kbmap.maplen)
				newkbmap.maplen = kbmap.maplen;
			for (i = 0; i < kbmap.maplen; i++) {
				mp = newkbmap.map + i;
				if (mp->command == KS_voidSymbol &&
				    mp->group1[0] == KS_voidSymbol &&
				    mp->group1[1] == KS_voidSymbol &&
				    mp->group2[0] == KS_voidSymbol &&
				    mp->group2[1] == KS_voidSymbol)
					*mp = kbmap.map[i];
			}
		}
		kbmap.maplen = newkbmap.maplen;
		memmove(kbmap.map, newkbmap.map,
		      kbmap.maplen*sizeof(struct wscons_keymap));
		break;
	default:
		errx(1, "internal error: rd_field: no format %d", f->format);
		break;
	}
}

void
print_kmap(struct wskbd_map_data *map)
{
	struct wscons_keymap *mp;
	int i;

	for (i = 0; i < map->maplen; i++) {
		mp = map->map + i;

		if (mp->command == KS_voidSymbol &&
		    mp->group1[0] == KS_voidSymbol &&
		    mp->group1[1] == KS_voidSymbol &&
		    mp->group2[0] == KS_voidSymbol &&
		    mp->group2[1] == KS_voidSymbol)
			continue;
		printf("\n");
		printf("keycode %u =", i);
		if (mp->command != KS_voidSymbol)
			printf(" %s", ksym2name(mp->command));
		printf(" %s", ksym2name(mp->group1[0]));
		if (mp->group1[0] != mp->group1[1] ||
		    mp->group1[0] != mp->group2[0] ||
		    mp->group1[0] != mp->group2[1]) {
			printf(" %s", ksym2name(mp->group1[1]));
			if (mp->group1[0] != mp->group2[0] ||
			    mp->group1[1] != mp->group2[1]) {
				printf(" %s", ksym2name(mp->group2[0]));
				printf(" %s", ksym2name(mp->group2[1]));
			}
		}
	}
}
