/*-
 * Copyright © 2009, 2010, 2011, 2013
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 * Copyright © 2013
 *	Vutral <vutral@quantentunnel.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 *-
 * MirOS RANDEX protocol plugin for XChat/HexChat (Win32, BSD, *nix).
 *
 * Protocol implementation status:
 *	- violation: CTCP CLIENTINFO does not list support for the protocol
 *	- violation: CTCP VERSION will not be amended by " (RANDOM=%d)"
 *	^ these stem from limitation of the XChat Plugin API 2.0
 *	- other than that, the protocol is fully supported
 *	- additional CTCP RANDOM returns plugin status and version
 *
 * On MirBSD (arc4random_pushb_fast) and Win32, the entropy received will be
 * fed back to the operating system; on other OSes, this plugin acts mostly
 * as a pool which can be accessed by the protocol and the /RANDOM command.
 *
 * Additional features over other implementations:
 *	- /RANDOM (output a random number, like /eval print $RANDOM in sirc)
 *	- /RANDEX * (send to the current channel/query, like in sirc)
 *	- /RANDFILE fn (read content from "fn", add to pool, save some to it)
 *
 * Missing features over other implementations:
 *	- no persistent seed file, no periodic stir (unlike irssi/randex.pl)
 *	- no support for EGD or other methods other than /RANDFILE
 *	- no support for accessing the pool in an automated fashion
 *
 * This implementation is shared between XChat and HexChat and thus
 * cannot use the plugin preferences feature available in the latter.
 */

static const char __rcsid[] =
    "@(#)HEXCHAT "
    "$MirOS: contrib/hosted/tg/code/xchat-randex/main.c,v 1.16 2011/12/16 21:30:58 tg Exp $";

#define RANDEX_PLUGIN_VERSION	"1.26"

#include <sys/types.h>
#if defined(HAVE_STDINT_H) && HAVE_STDINT_H
#include <stdint.h>
#elif defined(USE_INTTYPES)
#include <inttypes.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PLUGIN_HEADER"

#ifdef WIN32
#define u_int32_t	uint32_t
#endif

#ifndef MIN
#define MIN(a,b)	(((a) < (b)) ? (a) : (b))
#endif

#if defined(arc4random_pushb_fast)
#define dopush		arc4random_pushb_fast
#define slowpush	arc4random_pushb_fast
#define RELEASE_PAPI	"pfast"
#elif !defined(arc4random_pushk)
extern u_int32_t arc4random(void);
extern void arc4random_stir(void);
#if defined(__CYGWIN__) || defined(WIN32)
extern uint32_t arc4random_pushb(const void *, size_t);
#define dopush		arc4random_pushb
#define slowpush	arc4random_addrandom
#define RELEASE_PAPI	"Win32"
#else
#define dopush(b,n)	arc4random_addrandom((void *)(b), (int)(n))
#define slowpush	arc4random_addrandom
#define RELEASE_PAPI	"none"
#endif
#else
#define dopush		arc4random_pushk
#define slowpush	arc4random_addrandom
#define RELEASE_PAPI	"pushk"
#endif

#if !defined(__OpenBSD__)
extern void arc4random_addrandom(unsigned char *, int);
#endif

static hexchat_plugin *ph;
static char buf[128];
static struct {
	time_t t;
	uint32_t u;
} g;

/* The XChat Plugin API 2.0 is not const clean */
static char randex_name[] = "randex";
static char randex_desc[] = "MirOS RANDomness EXchange protocol support";
static char randex_vers[] = RANDEX_PLUGIN_VERSION;
static char null[] = "";

int hexchat_plugin_init(hexchat_plugin *, char **, char **, char **, char *);
int hexchat_plugin_deinit(void);
void hexchat_plugin_get_info(char **, char **, char **, void **);

static int hookfn_rawirc(char *[], char *[], void *);
static int cmdfn_randex(char *[], char *[], void *);
static int cmdfn_randfile(char *[], char *[], void *);
static int cmdfn_randstir(char *[], char *[], void *);
static int cmdfn_random(char *[], char *[], void *);

static int do_randex(int, char *, char *, char *);
static void entropyio(void *, size_t);
static void gstring(const void *);
static void msg_condestruct(int);

/* in lieu of -Bsymbolic */
static void hexchat_plugin_get_info_(char **, char **, char **);



#define NZATInit(h) do {					\
	(h) = 0;						\
} while (/* CONSTCOND */ 0)

#define NZATUpdateByte(h,b) do {				\
	(h) += (unsigned char)(b);				\
	++(h);							\
	(h) += (h) << 10;					\
	(h) ^= (h) >> 6;					\
} while (/* CONSTCOND */ 0)

#define NZATUpdateMem(h,p,z) do {				\
	register const unsigned char *NZATUpdateMem_p;		\
	register size_t NZATUpdateMem_z = (z);			\
								\
	NZATUpdateMem_p = (const void *)(p);			\
	while (NZATUpdateMem_z--)				\
		NZATUpdateByte((h), *NZATUpdateMem_p++);	\
} while (/* CONSTCOND */ 0)

#define NZATUpdateString(h,s) do {				\
	register const char *NZATUpdateString_s;		\
	register unsigned char NZATUpdateString_c;		\
								\
	NZATUpdateString_s = (const void *)(s);			\
	while ((NZATUpdateString_c = *NZATUpdateString_s++))	\
		NZATUpdateByte((h), NZATUpdateString_c);	\
} while (/* CONSTCOND */ 0)

#define NZAATFinish(h) do {					\
	(h) += (h) << 10;					\
	(h) ^= (h) >> 6;					\
	(h) += (h) << 3;					\
	(h) ^= (h) >> 11;					\
	(h) += (h) << 15;					\
} while (/* CONSTCOND */ 0)


static void
hexchat_plugin_get_info_(char **name, char **desc, char **vers)
{
	*name = randex_name;
	*desc = randex_desc;
	*vers = randex_vers;
}

void
hexchat_plugin_get_info(char **name, char **desc, char **vers, void **resv)
{
	hexchat_plugin_get_info_(name, desc, vers);
	if (resv)
		*resv = NULL;
}

static void
gstring(const void *s)
{
	register uint32_t h;

	g.t = time(NULL);
	g.u = arc4random();
	NZATInit(h);
	NZATUpdateMem(h, &g.u, sizeof(g.u));
	NZATUpdateString(h, s);
	NZAATFinish(h);
	g.u = h;
}

static void
msg_condestruct(int con)
{
	/* goes to the current tab */
	hexchat_printf(ph, "%sstructed RANDEX plugin v%s\n",
	    con ? "Con" : "De", randex_vers);
}

int
hexchat_plugin_init(hexchat_plugin *handle, char **name, char **desc,
    char **version, char *arg)
{
	ph = handle;
	hexchat_plugin_get_info_(name, desc, version);

	gstring(__rcsid);
	dopush((void *)&g, sizeof(g));

	hexchat_hook_server(ph, "RAW LINE", HEXCHAT_PRI_HIGHEST,
	    hookfn_rawirc, NULL);
	hexchat_hook_command(ph, "RANDEX", HEXCHAT_PRI_NORM,
	    cmdfn_randex, "Initiate RANDEX protocol with argument", NULL);
	hexchat_hook_command(ph, "RANDFILE", HEXCHAT_PRI_NORM,
	    cmdfn_randfile, "Exchange between pool and file", NULL);
	hexchat_hook_command(ph, "RANDSTIR", HEXCHAT_PRI_NORM,
	    cmdfn_randstir, "Stir the entropy pool", NULL);
	hexchat_hook_command(ph, "RANDOM", HEXCHAT_PRI_NORM,
	    cmdfn_random, "Show a random number", NULL);

	msg_condestruct(1);
	return (1);
}

int
hexchat_plugin_deinit(void)
{
	arc4random_stir();
	arc4random();

	msg_condestruct(0);
	return (1);
}

static int
hookfn_rawirc(char *word[], char *word_eol[], void *user_data)
{
	char *src, *dst, *cmd, *rest;

	if (!word[1] || !word[1][0])
		return (HEXCHAT_EAT_NONE);
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

	if ((*rest == '+' || *rest == '-') && rest[1] == 1)
		/* CAPAB IDENTIFY-MSG or similar */
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

	gstring(word_eol[1]);
	slowpush((void *)&g, sizeof(g));
	return (HEXCHAT_EAT_NONE);
}

static void
entropyio(void *p, size_t len)
{
	char *cp = buf;
	uint32_t v;
	int i;

	dopush(p, len);
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

	if (hexchat_get_info(ph, "server") == NULL) {
		/* goes to the current tab */
		hexchat_print(ph, "You are not connected to the server.\n");
		return (HEXCHAT_EAT_ALL);
	}

	ichan = word[2];
	/* make "/randex *" address the current tab */
	if (ichan && ichan[0] == '*' && (!ichan[1] || ichan[1] == ' ' ||
	    ichan[1] == '\t' || ichan[1] == '\r')) {
		ichan = hexchat_get_info(ph, "channel");
		inetw = hexchat_get_info(ph, "network");
		if (!ichan || !*ichan || (inetw && !strcmp(ichan, inetw)))
			/* no current talk channel, or server tab active */
			ichan = NULL;
	}

	if (!ichan || !ichan[0]) {
		/* goes to the current tab */
		hexchat_print(ph, "You must specify a nick or channel!\n");
		return (HEXCHAT_EAT_ALL);
	}

	snprintf(buf, sizeof(buf), "to %s for %s", ichan, word_eol[3] ?
	    word_eol[3] : "\001(null)");
	/* goes to the current tab */
	hexchat_printf(ph, "Initiating the RANDEX protocol with %s\n", ichan);
	entropyio(buf, sizeof(buf));
	hexchat_commandf(ph, "quote PRIVMSG %s :\001ENTROPY %s\001", ichan, buf);

	memset(buf, 0, sizeof(buf));
	return (HEXCHAT_EAT_HEXCHAT);
}

static int
cmdfn_randstir(char *word[], char *word_eol[], void *user_data)
{
	unsigned long v;

	arc4random_stir();
	v = arc4random();
	/* goes to the current tab */
	hexchat_printf(ph, "Entropy pool stirred. RANDOM: 0x%08X (%lu)\n", v, v);
	return (HEXCHAT_EAT_HEXCHAT);
}

static int
cmdfn_random(char *word[], char *word_eol[], void *user_data)
{
	unsigned long v;

	v = arc4random();
	/* goes to the current tab */
	hexchat_printf(ph, "Random number: 0x%08X (%lu)\n", v, v);
	return (HEXCHAT_EAT_HEXCHAT);
}

static int
do_randex(int is_req, char *rsrc, char *dst, char *line)
{
	int i;
	char *cp, *src;

	if ((cp = strchr(rsrc, '!')))
		*cp = 0;
	src = strdup(rsrc);
	if (cp)
		*cp = '!';
	if (!src)
		src = rsrc;
#ifndef BE_QUIET
	/*
	 * should go to the server tab, but there is no way
	 * to do so even with hexchat_find_context => doesn't
	 */
	hexchat_printf(ph,
	    is_req == 2 ? "%s queried RANDEX protocol information from %s\n" :
	    is_req ? "%s initiated the RANDEX protocol with %s\n" :
	    "RANDEX protocol reply from %s to %s, processing\n", src, dst);
#endif
	entropyio(line, strlen(line));
	if (is_req == 2)
		hexchat_commandf(ph, "quote PRIVMSG %s :\001ACTION uses the"
		    " RANDEX plugin v%s for HexChat, push API: %s\001",
		    src, randex_vers, RELEASE_PAPI);
	else if (is_req)
		hexchat_commandf(ph, "quote NOTICE %s :\001RANDOM %s\001",
		    src, buf);
	if (src != rsrc)
		free(src);

	memset(buf, 0, sizeof(buf));
	return (HEXCHAT_EAT_ALL);
}

static int
cmdfn_randfile(char *word[], char *word_eol[], void *user_data)
{
	register uint32_t h;
	const char *fn;
	FILE *f;
	size_t n;
	uint32_t tv;
	char pb[600];

	fn = word[2];
	if (!fn || !fn[0]) {
		/* goes to the current tab */
		hexchat_print(ph, "You must specify a filename!\n");
		return (HEXCHAT_EAT_HEXCHAT);
	}

	g.t = time(NULL);
	g.u = arc4random();
	NZATInit(h);
	NZATUpdateMem(h, &g.u, sizeof(g.u));
	NZATUpdateString(h, fn);

	if ((f = fopen(fn, "rb")) != NULL) {
		do {
			if ((n = fread(pb, 1, sizeof(pb), f))) {
				slowpush((void *)pb, n);
				tv = arc4random();
				NZATUpdateMem(h, &tv, sizeof(tv));
			}
		} while (n);
		fclose(f);
		NZATUpdateMem(h, pb, 16);
		(void)arc4random();
	}

	if ((f = fopen(fn, "wb")) != NULL) {
		for (n = 0; n < sizeof(pb); n += sizeof(tv)) {
			tv = arc4random();
			memcpy(pb + n, &tv, sizeof(tv));
		}
		if ((n = fwrite(pb, 1, sizeof(pb), f)) != sizeof(pb))
			hexchat_printf(ph, "Write error: %u/%u to %s\n",
			    (unsigned)n, (unsigned)sizeof(pb), fn);
		fclose(f);
		(void)arc4random();
	} else
		hexchat_printf(ph, "Could not open %s for writing!\n", fn);

	tv = arc4random();
	NZATUpdateMem(h, &tv, sizeof(tv));
	NZAATFinish(h);
	g.u = h;
	dopush((void *)&g, sizeof(g));

	memset(pb, 0, sizeof(pb));
	return (HEXCHAT_EAT_HEXCHAT);
}
