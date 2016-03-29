/**	$MirOS: src/sys/dev/isa/spkr.c,v 1.7 2016/03/27 18:52:07 tg Exp $ */
/*	$OpenBSD: spkr.c,v 1.7 2002/03/14 01:26:56 millert Exp $	*/
/*	$NetBSD: spkr.c,v 1.1 1998/04/15 20:26:18 drochner Exp $	*/

/*
 * Copyright (c) 1990 Eric S. Raymond (esr@snark.thyrsus.com)
 * Copyright (c) 1990 Andrew A. Chernov (ache@astral.msk.su)
 * Copyright (c) 1990 Lennart Augustsson (lennart@augustsson.net)
 * Copyright (c) 2002, 2016 mirabilos (m@mirbsd.org)
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
 *	This product includes software developed by Eric S. Raymond
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * spkr.c -- device driver for console speaker on 80386
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/errno.h>
#include <sys/device.h>
#include <sys/malloc.h>
#include <sys/uio.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/conf.h>

#include <dev/isa/pcppivar.h>

#include <dev/isa/spkrio.h>

cdev_decl(spkr);

#define __BROKEN_INDIRECT_CONFIG /* XXX */
#ifdef __BROKEN_INDIRECT_CONFIG
int spkrprobe(struct device *, void *, void *);
#else
int spkrprobe(struct device *, struct cfdata *, void *);
#endif
void spkrattach(struct device *, struct device *, void *);

struct spkr_softc {
	struct device sc_dev;
};

struct cfattach spkr_ca = {
	sizeof(struct spkr_softc), spkrprobe, spkrattach
};

struct cfdriver spkr_cd = {
	NULL, "spkr", DV_DULL
};

static pcppi_tag_t ppicookie;

#define SPKRPRI (PZERO - 1)

static void tone(u_int, u_int);
static void rest(int);
static void playinit(void);
static void playtone(int, int, int);
static void playstring(char *, int);

/* emit tone of frequency hz for given number of ticks */
static void
tone(u_int hz, u_int ticks)
{
	pcppi_bell(ppicookie, hz, ticks, PCPPI_BELL_SLEEP);
}

/* rest for given number of ticks */
static void
rest(int ticks)
{
    /*
     * Set timeout to endrest function, then give up the timeslice.
     * This is so other processes can execute while the rest is being
     * waited out.
     */
#ifdef SPKRDEBUG
    printf("rest: %d\n", ticks);
#endif /* SPKRDEBUG */
    if (ticks > 0)
	    tsleep(rest, SPKRPRI | PCATCH, "rest", ticks);
}

/**************** PLAY STRING INTERPRETER BEGINS HERE **********************
 *
 * Play string interpretation is modelled on IBM BASIC 2.0's PLAY statement;
 * M[LNS] are missing and the ~ synonym and octave-tracking facility is added.
 * Requires tone(), rest(), and endtone(). String play is not interruptible
 * except possibly at physical block boundaries.
 */

typedef int	bool;
#define TRUE	1
#define FALSE	0

#define toupper(c)	((c) - ' ' * (((c) >= 'a') && ((c) <= 'z')))
#define isdigit(c)	(((c) >= '0') && ((c) <= '9'))
#define dtoi(c)		((c) - '0')

static int octave;	/* currently selected octave */
static int whole;	/* whole-note time at current tempo, in ticks */
static int value;	/* whole divisor for note time, quarter note = 1 */
static int fill;	/* controls spacing of notes */
static bool octtrack;	/* octave-tracking on? */
static bool octprefix;	/* override current octave-tracking state? */

/*
 * Magic number avoidance...
 */
#define SECS_PER_MIN	60	/* seconds per minute */
#define WHOLE_NOTE	4	/* quarter notes per whole note */
#define MIN_VALUE	64	/* the most we can divide a note by */
#define DFLT_VALUE	4	/* default value (quarter-note) */
#define FILLTIME	8	/* for articulation, break note in parts */
#define STACCATO	6	/* 6/8 = 3/4 of note is filled */
#define NORMAL		7	/* 7/8ths of note interval is filled */
#define LEGATO		8	/* all of note interval is filled */
#define DFLT_OCTAVE	4	/* default octave */
#define MIN_TEMPO	32	/* minimum tempo */
#define DFLT_TEMPO	120	/* default tempo */
#define MAX_TEMPO	255	/* max tempo */
#define NUM_MULT	3	/* numerator of dot multiplier */
#define DENOM_MULT	2	/* denominator of dot multiplier */

/* letter to half-tone:  A   B  C  D  E  F  G */
static const int notetab[8] = {9, 11, 0, 2, 4, 5, 7};

/*
 * These pitches are constructed from the fixed table in octave 6 by
 * shifting right once per octave, then rounding up (adding the carry);
 * our octave 0 is standard octave 2.
 */
#define OCTAVE_NOTES	12	/* semitones per octave */
static const int pitchtab[] =
{
/*        C     C#    D     D#    E     F     F#    G     G#    A     A#    B*/
/* 0 */   65,   69,   73,   78,   82,   87,   93,   98,  104,  110,  117,  123,
/* 1 */  131,  139,  147,  156,  165,  175,  185,  196,  208,  220,  233,  247,
/* 2 */  262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494,
/* 3 */  523,  554,  587,  622,  659,  699,  740,  784,  831,  880,  932,  988,
/* 4 */ 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
/* 5 */ 2093, 2218, 2350, 2489, 2637, 2794, 2960, 3136, 3323, 3520, 3730, 3951,
/* 6 */ 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902,
};
#define NNOTES   (sizeof(pitchtab) / sizeof(pitchtab[0]))	/* 84 */
#define NOCTAVES (NNOTES / OCTAVE_NOTES)			/* 7 */

static void
playinit(void)
{
    octave = DFLT_OCTAVE;
    whole = (hz * SECS_PER_MIN * WHOLE_NOTE) / DFLT_TEMPO;
    fill = NORMAL;
    value = DFLT_VALUE;
    octtrack = FALSE;
    octprefix = TRUE;	/* act as though there was an initial O(n) */
}

/* play tone of proper duration for current rhythm signature */
static void
playtone(int pitch, int value, int sustain)
{
    int sound, silence, snum = 1, sdenom = 1;

    if (!value) return;

    /* this weirdness avoids floating-point arithmetic */
    while (sustain--) {
	snum *= NUM_MULT;
	sdenom *= DENOM_MULT;
    }

    if (pitch == -1)
	rest(whole * snum / (value * sdenom));
    else if ((pitch >= 0) && (pitch < NNOTES)) {
	silence = whole * (FILLTIME - fill) * snum /
	    (value * FILLTIME * sdenom);
	sound = whole * snum / (value * sdenom) - silence;

#ifdef SPKRDEBUG
	printf("playtone: pitch %d for %d ticks, rest for %d ticks\n",
	    pitch, sound, silence);
#endif /* SPKRDEBUG */

	tone(pitchtab[pitch], sound);
	if (fill != LEGATO)
	    rest(silence);
    }
}

/* interpret and play an item from a notation string */
static void
playstring(char *cp, int slen)
{
    int pitch, lastpitch = OCTAVE_NOTES * DFLT_OCTAVE;

#define GETNUM(cp, v)	for(v=0; slen > 0 && isdigit(cp[1]); slen--) \
				v = v * 10 + (*++cp - '0');
    for (; slen--; cp++) {
	int sustain, timeval, tempo;
	char c = toupper(*cp);

#ifdef SPKRDEBUG
	printf("playstring: %c (%x)\n", c, c);
#endif /* SPKRDEBUG */

	switch (c) {
	  case 'A':  case 'B':  case 'C':  case 'D':
	  case 'E':  case 'F':  case 'G':

	    /* compute pitch */
	    pitch = notetab[c - 'A'] + octave * OCTAVE_NOTES;

	    /* this may be followed by an accidental sign */
	    if (slen > 0 && (cp[1] == '#' || cp[1] == '+')) {
		if (pitch < (NNOTES - 1))
			++pitch;
		++cp;
		slen--;
	    } else if (slen > 0 && cp[1] == '-') {
		if (pitch > 0)
			--pitch;
		++cp;
		slen--;
	    }

	    /*
	     * If octave-tracking mode is on, and there has been no octave-
	     * setting prefix, find the version of the current letter note
	     * closest to the last regardless of octave.
	     */
	    if (octtrack && !octprefix) {
		if (abs(pitch-lastpitch) > abs(pitch+OCTAVE_NOTES-lastpitch)) {
		    ++octave;
		    pitch += OCTAVE_NOTES;
		}

		if (abs(pitch-lastpitch) > abs((pitch-OCTAVE_NOTES)-lastpitch)) {
		    --octave;
		    pitch -= OCTAVE_NOTES;
		}
	    }
	    octprefix = FALSE;
	    lastpitch = pitch;

	    /* ...which may in turn be followed by an override time value */
	    GETNUM(cp, timeval)
	    if (timeval <= 0 || timeval > MIN_VALUE)
		timeval = value;

	    /* ...and/or sustain dots */
	    for (sustain = 0; slen > 0 && cp[1] == '.'; cp++) {
		slen--;
		sustain++;
	    }

	    /* time to emit the actual tone */
	    playtone(pitch, timeval, sustain);
	    break;

	case 'O':
	    if (slen > 0 && (cp[1] == 'N' || cp[1] == 'n')) {
		octprefix = octtrack = FALSE;
		++cp;
		slen--;
	    } else if (slen > 0 && (cp[1] == 'L' || cp[1] == 'l')) {
		octtrack = TRUE;
		++cp;
		slen--;
	    } else if (slen > 0) {
		GETNUM(cp, octave)
		if (octave >= NOCTAVES)
		    octave = DFLT_OCTAVE;
		octprefix = TRUE;
	    }
	    break;

	case '>':
	    if (octave < NOCTAVES - 1)
		octave++;
	    octprefix = TRUE;
	    break;

	case '<':
	    if (octave > 0)
		octave--;
	    octprefix = TRUE;
	    break;

	case 'N':
	    GETNUM(cp, pitch)
	    for (sustain = 0; slen > 0 && cp[1] == '.'; cp++) {
		slen--;
		sustain++;
	    }
	    playtone(pitch - 1, value, sustain);
	    break;

	case 'L':
	    GETNUM(cp, value)
	    if (!value || value > MIN_VALUE)
		value = DFLT_VALUE;
	    break;

	case 'P':  case '~':
	    /* this may be followed by an override time value */
	    GETNUM(cp, timeval)
	    if (!timeval || timeval > MIN_VALUE)
		timeval = value;
	    for (sustain = 0; slen > 0 && cp[1] == '.'; cp++) {
		slen--;
		sustain++;
	    }
	    playtone(-1, timeval, sustain);
	    break;

	case 'T':
	    GETNUM(cp, tempo)
	    if (tempo < MIN_TEMPO || tempo > MAX_TEMPO)
		tempo = DFLT_TEMPO;
	    whole = (hz * SECS_PER_MIN * WHOLE_NOTE) / tempo;
	    break;

	case 'M':
	    if (slen > 0 && (cp[1] == 'N' || cp[1] == 'n')) {
		fill = NORMAL;
	    } else if (slen > 0 && (cp[1] == 'L' || cp[1] == 'l')) {
		fill = LEGATO;
	    } else if (slen > 0 && (cp[1] == 'S' || cp[1] == 's')) {
		fill = STACCATO;
	    }
	    if (slen > 0) {
		++cp;
		slen--;
	    }
	    /* intentionally no support for MF/MB (Foreground/Background) */
	    break;

	case 'X':
	    /* intentionally no support; skip till end of character */
	    while (slen > 0 && cp[1] != ';') {
		++cp;
		slen--;
	    }
	    break;
	}
    }
}

/******************* UNIX DRIVER HOOKS BEGIN HERE **************************
 *
 * This section implements driver hooks to run playstring() and the tone(),
 * endtone(), and rest() functions defined above.
 */

static int spkr_active;	/* exclusion flag */
static void *spkr_inbuf;

static int spkr_attached = 0;

int
#ifdef __BROKEN_INDIRECT_CONFIG
spkrprobe (struct device *parent, void *match, void *aux)
#else
spkrprobe (struct device *parent, struct cfdata *match, void *aux)
#endif
{
	return (!spkr_attached);
}

void
spkrattach(struct device *parent, struct device *self, void *aux)
{
	printf("\n");
	ppicookie = ((struct pcppi_attach_args *)aux)->pa_cookie;
	spkr_attached = 1;
}

int
spkropen(dev_t dev, int flags, int mode, struct proc *p)
{
#ifdef SPKRDEBUG
    printf("spkropen: entering with dev = %x\n", dev);
#endif /* SPKRDEBUG */

    if (minor(dev) != 0 || !spkr_attached)
	return (ENXIO);
    else if (spkr_active)
	return (EBUSY);
    else {
	playinit();
	spkr_inbuf = malloc(DEV_BSIZE, M_DEVBUF, M_WAITOK);
	spkr_active = 1;
    }
    return (0);
}

int
spkrwrite(dev_t dev, struct uio *uio, int flags)
{
    int n;
    int error;
#ifdef SPKRDEBUG
    printf("spkrwrite: entering with dev = %x, count = %d\n",
		dev, uio->uio_resid);
#endif /* SPKRDEBUG */

    if (minor(dev) != 0)
	return (ENXIO);
    else {
	n = min(DEV_BSIZE, uio->uio_resid);
	error = uiomove(spkr_inbuf, n, uio);
	if (!error)
		playstring((char *)spkr_inbuf, n);
	return (error);
    }
}

int spkrclose(dev_t dev, int flags, int mode, struct proc *p)
{
#ifdef SPKRDEBUG
    printf("spkrclose: entering with dev = %x\n", dev);
#endif /* SPKRDEBUG */

    if (minor(dev) != 0)
	return (ENXIO);
    else {
	tone(0, 0);
	free(spkr_inbuf, M_DEVBUF);
	spkr_active = 0;
    }
    return (0);
}

int spkrioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p)
{
#ifdef SPKRDEBUG
    printf("spkrioctl: entering with dev = %x, cmd = %lx\n", dev, cmd);
#endif /* SPKRDEBUG */

    if (minor(dev) != 0)
	return (ENXIO);
    else if (cmd == SPKRTONE) {
	tone_t	*tp = (tone_t *)data;
	if (!tp->frequency)
	    rest(tp->duration);
	else tone(tp->frequency, tp->duration);
    } else if (cmd == SPKRTUNE) {
	tone_t *tp = (tone_t *)(*(caddr_t *)data);
	tone_t ttp;
	int error;

	for (; ; tp++) {
	    error = copyin(tp, &ttp, sizeof(tone_t));
	    if (error)
		    return (error);
	    if (!ttp.duration)
		    break;
	    if (!ttp.frequency)
		rest(ttp.duration);
	    else tone(ttp.frequency, ttp.duration);
	}
    } else
	return (EINVAL);
    return (0);
}
