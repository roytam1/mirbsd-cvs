/*-
 * Copyright (c) 2009
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
 * MirOS RANDEX protocol plugin for XChat (Win32, BSD, *nix).
 *
 * Protocol implementation status:
 *	- violation: CTCP CLIENTINFO does not list support for the protocol
 *	- violation: CTCP VERSION will not be amended by " (RANDOM=%d)"
 *	^ these stem from limitation of the XChat Plugin API 2.0
 *	- other than that, the protocol is fully supported
 *	- additional CTCP RANDOM returns plugin status and version
 *
 * On MirBSD (arc4random_pushk) and Win32, the entropy received will be fed
 * back to the operating system; on other OSes, this plugin acts mostly as
 * a pool which can be accessed by the protocol and the /RANDOM command.
 *
 * Additional features over other implementations:
 *	- /RANDOM (output a random number, like /eval print $RANDOM in sirc)
 *	- /RANDEX * (send to the current channel/query, like in sirc)
 *
 * Missing features over other implementations:
 *	- no persistent seed file, no periodic stir (unlike irssi/randex.pl)
 *	- no support for contributing to the pool directly, getting entropy
 *	  from the pool other than /RANDOM, or using EGD or similar methods
 */

static const char __rcsid[] =
    "$MirOS: contrib/hosted/tg/code/xchat-randex/main.c,v 1.5 2009/08/02 14:35:00 tg Exp $";

#include <sys/types.h>
#if defined(HAVE_STDINT_H) && HAVE_STDINT_H
#include <stdint.h>
#elif defined(USE_INTTYPES)
#include <inttypes.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xchat-plugin.h"

#ifdef WIN32
#define u_int32_t	uint32_t
#endif

#ifndef MIN
#define MIN(a,b)	(((a) < (b)) ? (a) : (b))
#endif

#ifndef arc4random_pushk
extern u_int32_t arc4random(void);
extern void arc4random_stir(void);
#if defined(__CYGWIN__) || defined(WIN32)
extern uint32_t arc4random_pushb(const void *, size_t);
#define arc4random_pushk arc4random_pushb
#define RELEASE_PAPI	"Win32"
#else
#define arc4random_pushk(b,n) arc4random_addrandom((void *)(b), (int)(n))
#define RELEASE_PAPI	"none"
#endif
#else
#define RELEASE_PAPI	"pushk"
#endif

static unsigned long adler32(unsigned long, const unsigned char *, unsigned);
extern void arc4random_addrandom(unsigned char *, int);

static xchat_plugin *ph;
static char buf[128];

/* The XChat Plugin API 2.0 is not const clean */
static char randex_name[] = "randex";
static char randex_desc[] = "MirOS RANDomness EXchange protocol support";
static char randex_vers[] = "1.07";
static char null[] = "";

int xchat_plugin_init(xchat_plugin *, char **, char **, char **, char *);
int xchat_plugin_deinit(void);
void xchat_plugin_get_info(char **, char **, char **, void **);

static int hookfn_rawirc(char *[], char *[], void *);
static int cmdfn_randex(char *[], char *[], void *);
static int cmdfn_randstir(char *[], char *[], void *);
static int cmdfn_random(char *[], char *[], void *);

static int do_randex(int, char *, char *, char *);
static void entropyio(void *, size_t);

void
xchat_plugin_get_info(char **name, char **desc, char **vers, void **resv)
{
	*name = randex_name;
	*desc = randex_desc;
	*vers = randex_vers;
	if (resv)
		*resv = NULL;
}

int
xchat_plugin_init(xchat_plugin *handle, char **name, char **desc,
    char **version, char *arg)
{
	unsigned long i;

	ph = handle;
	xchat_plugin_get_info(name, desc, version, NULL);

	i = adler32(arc4random() | 1, (const void *)__rcsid, sizeof(__rcsid));
	arc4random_pushk(&i, sizeof(i));

	xchat_hook_server(ph, "RAW LINE", XCHAT_PRI_HIGHEST,
	    hookfn_rawirc, NULL);
	xchat_hook_command(ph, "RANDEX", XCHAT_PRI_NORM,
	    cmdfn_randex, "Initiate RANDEX protocol with argument", NULL);
	xchat_hook_command(ph, "RANDSTIR", XCHAT_PRI_NORM,
	    cmdfn_randstir, "Stir the entropy pool", NULL);
	xchat_hook_command(ph, "RANDOM", XCHAT_PRI_NORM,
	    cmdfn_random, "Show a random number", NULL);

	/* goes to the current tab */
	xchat_printf(ph, "%sstructed RANDEX plugin v%s\n", "Con", randex_vers);
	return (1);
}

int
xchat_plugin_deinit(void)
{
	arc4random_stir();

	/* goes to the current tab */
	xchat_printf(ph, "%sstructed RANDEX plugin v%s\n", "De", randex_vers);
	return (1);
}

static int
hookfn_rawirc(char *word[], char *word_eol[], void *user_data)
{
	unsigned long i;
	time_t v;
	char *src, *dst, *cmd, *rest;

	if (!word[1] || !word[1][0])
		return (XCHAT_EAT_NONE);
	if (word[1][0] == ':') {
		src = word[1];
		cmd = word[2];
		dst = word[3];
		rest = word_eol[4];
	} else {
		src = null;
		cmd = word[1];
		if (word_eol[2][0] == ':') {
			dst = null;
			rest = word_eol[2];
		} else {
			dst = word[2];
			rest = word_eol[3];
		}
	}

	if (*src == ':')
		++src;
	if (*dst == ':')
		++dst;
	if (*rest == ':')
		++rest;

	if (*rest == 1) {
		++rest;
		if (!strcasecmp(cmd, "privmsg") &&
		    !strncasecmp(rest, "entropy", 7))
			return (do_randex(1, src, dst, word_eol[1]));
		else if (!strcasecmp(cmd, "privmsg") &&
		    !strncasecmp(rest, "random", 6))
			return (do_randex(2, src, dst, word_eol[1]));
		else if (!strcasecmp(cmd, "notice") &&
		    !strncasecmp(rest, "random", 6))
			return (do_randex(0, src, dst, word_eol[1]));
	}

	v = arc4random();
	i = adler32(adler32(1, (const void *)&v, sizeof(v)),
	    (const void *)word_eol[1], strlen(word_eol[1]));
	v = time(NULL) ^ (time_t)i;
	arc4random_addrandom((void *)&v, sizeof(v));
	return (XCHAT_EAT_NONE);
}

static void
entropyio(void *p, size_t len)
{
	char *cp = buf;
	uint32_t v;
	int i;

	arc4random_pushk(p, len);
	for (i = 0; i < 7; ++i) {
		v = arc4random();
		*cp++ = '!' + (v & 0x3F);
		v >>= 6;
		*cp++ = '!' + (v & 0x3F);
		v >>= 6;
		*cp++ = '!' + (v & 0x3F);
		v >>= 6;
		*cp++ = '!' + (v & 0x3F);
		v >>= 6;
		*cp++ = '!' + (v & 0x3F);
	}
	*cp = 0;
}

static int
cmdfn_randex(char *word[], char *word_eol[], void *user_data)
{
	const char *ichan, *inetw;

	if (xchat_get_info(ph, "server") == NULL) {
		/* goes to the current tab */
		xchat_print(ph, "You are not connected to the server.\n");
		return (XCHAT_EAT_ALL);
	}

	ichan = word[2];
	/* make "/randex *" address the current tab */
	if (ichan && ichan[0] == '*' && (!ichan[1] || ichan[1] == ' ' ||
	    ichan[1] == '\t' || ichan[1] == '\r')) {
		ichan = xchat_get_info(ph, "channel");
		inetw = xchat_get_info(ph, "network");
		if (!ichan || !*ichan || (inetw && !strcmp(ichan, inetw)))
			/* no current talk channel, or server tab active */
			ichan = NULL;
	}

	if (!ichan || !ichan[0]) {
		/* goes to the current tab */
		xchat_print(ph, "You must specify a nick or channel!\n");
		return (XCHAT_EAT_ALL);
	}

	snprintf(buf, sizeof(buf), "to %s for %s", ichan, word_eol[3] ?
	    word_eol[3] : "\001(null)");
	/* goes to the current tab */
	xchat_printf(ph, "Initiating the RANDEX protocol with %s\n", ichan);
	entropyio(buf, sizeof(buf));
	xchat_commandf(ph, "quote PRIVMSG %s :\001ENTROPY %s\001", ichan, buf);

	memset(buf, 0, sizeof(buf));
	return (XCHAT_EAT_XCHAT);
}

static int
cmdfn_randstir(char *word[], char *word_eol[], void *user_data)
{
	arc4random_stir();
	/* goes to the current tab */
	xchat_print(ph, "Entropy pool stirred.\n");
	return (XCHAT_EAT_XCHAT);
}

static int
cmdfn_random(char *word[], char *word_eol[], void *user_data)
{
	unsigned long v;

	v = arc4random();
	/* goes to the current tab */
	xchat_printf(ph, "Random number: 0x%08X (%lu)\n", v, v);
	return (XCHAT_EAT_XCHAT);
}

#define BASE	65521	/* largest prime smaller than 65536 */
#define NMAX	5552	/* largest n: 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

static unsigned long
adler32(unsigned long s1, const unsigned char *bp, unsigned len)
{
	unsigned long s2;
	unsigned n;

	if (bp == NULL)
		return (1UL);

	s2 = (s1 >> 16) & 0xFFFFUL;
	s1 &= 0xFFFFUL;

	while (len) {
		len -= (n = MIN(len, NMAX));
		while (n--) {
			s1 += *bp++;
			s2 += s1;
		}
		s1 %= BASE;
		s2 %= BASE;
	}

	return (s1 | (s2 << 16));
}

static int
do_randex(int is_req, char *rsrc, char *dst, char *line)
{
	int i, j;
	char *cp, *src;

	if ((cp = strchr(rsrc, '!')))
		*cp = 0;
	src = strdup(rsrc);
	if (cp)
		*cp = '!';
	if (!src)
		src = rsrc;
	if ((i = xchat_get_prefs(ph, "rand_quiet", NULL, &j)) != 1 &&
	    i != 2)
		j = 0;
	if (!j)
		/*
		 * should go to the server tab, but there is no way
		 * to do so even with xchat_find_context => doesn't
		 */
		xchat_printf(ph, is_req == 2 ?
		    "%s queried RANDEX protocol information from %s\n" :
		    is_req ?
		    "%s initiated the RANDEX protocol with %s\n" :
		    "RANDEX protocol reply from %s to %s, processing\n",
		    src, dst);
	entropyio(line, strlen(line));
	if (is_req == 2)
		xchat_commandf(ph, "quote PRIVMSG %s :\001ACTION uses the"
		    " RANDEX plugin v%s for XChat, push API: %s\001",
		    src, randex_vers, RELEASE_PAPI);
	else if (is_req)
		xchat_commandf(ph, "quote NOTICE %s :\001RANDOM %s\001",
		    src, buf);
	if (src != rsrc)
		free(src);

	memset(buf, 0, sizeof(buf));
	return (XCHAT_EAT_ALL);
}
