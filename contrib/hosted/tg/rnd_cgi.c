#if 0
#-
# Copyright © 2010, 2013, 2014
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.
#-
# CGI binary exposing arandom(4) as base64, binary or hex-encoded.
# Uses interna of MirBSD libc. Optimised for size and speed.

PROG=		rn.cgi
SRCS=		rnd_cgi.c
NOMAN=		Yes
BINDIR=		/var/www/htdocs
BINMODE=	0111
LINKS=		${BINDIR}/rn.cgi ${BINDIR}/rb.cgi \
		${BINDIR}/rn.cgi ${BINDIR}/rh.cgi \
		${BINDIR}/rn.cgi ${BINDIR}/ln.cgi \
		${BINDIR}/rn.cgi ${BINDIR}/lb.cgi \
		${BINDIR}/rn.cgi ${BINDIR}/lh.cgi

LDSTATIC=	-static
LDFLAGS+=	-nostartfiles -nostdlib ${DESTDIR}/usr/lib/crt0.o
LDADD+=		-lc

.include <bsd.prog.mk>

.if "0" == "1"
#endif

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

__RCSID("$MirOS: contrib/hosted/tg/rnd_cgi.c,v 1.4 2013/10/31 20:05:53 tg Exp $");

extern const char *__progname;
extern const uint8_t mbsd_digits_base64[65];
extern const uint8_t mbsd_digits_HEX[17];

extern void _thread_sys__exit(int) __dead;

static uint8_t buf[4096];

static void w(int, const void *, size_t);

static uint8_t wBuf[4096];
static size_t wBptr;

static inline void
wBF(int fd)
{
	if (wBptr)
		w(fd, wBuf, wBptr);
	wBptr = 0;
}

static inline void
wB(int fd, char c)
{
	if (wBptr == sizeof(wBuf))
		wBF(fd);
	wBuf[wBptr++] = (uint8_t)c;
}

static inline void
wc(int fd, char c)
{
	w(fd, &c, 1);
}

static inline void
ws(int fd, const char *s)
{
	w(fd, s, strlen(s));
}

static void
pn(int fd, register unsigned long num)
{
	register unsigned long numz;

	if ((numz = num / 10))
		pn(fd, numz);
	wc(fd, '0' + (num % 10));
}

static void
lwarn(const char *msg)
{
	static bool recursive = false;

	if (!recursive) {
		int e = errno;

		recursive = true;
		ws(2, __progname);
		w(2, ": ", 2);
		ws(2, msg);
		w(2, ": ", 2);
		if (e < sys_nerr)
			ws(2, sys_errlist[e]);
		else {
			ws(2, "<errno ");
			pn(2, e);
			wc(2, '>');
		}
		wc(2, '\n');
		recursive = false;
	}
}

static void
w(int fd, const void *p, size_t n)
{
	if ((size_t)write(fd, p, n) != n) {
		lwarn("write");
		_thread_sys__exit(1);
	}
}

int
main(int argc __unused, char *argv[], char *envp[]) {
	size_t n;
	bool has_post = false, has_http11 = false, is_long = false;
	enum { NUM, HEX, BIN } mode = NUM;

	if (__progname == NULL)
		__progname = "<unknown>";
	else switch (__progname[0]) {
	case 'l':
		is_long = true;
		/* FALLTHROUGH */
	case 'r':
		switch (__progname[1]) {
		case 'b': mode = BIN; break;
		case 'h': mode = HEX; break;
		}
	}

	while (*argv) {
		arc4random_pushb_fast(*argv, strlen(*argv) + 1);
		++argv;
	}

	if (envp != NULL) {
		while (*envp != NULL) {
			if (!strcmp(*envp, "REQUEST_METHOD=POST"))
				has_post = true;
			if (!strcmp(*envp, "SERVER_PROTOCOL=HTTP/1.1"))
				has_http11 = true;
			/* hash, then feed to pool */
			arc4random_pushb_fast(*envp, strlen(*envp) + 1);
			++envp;
		}
	}

	ws(1, has_http11 ? "Cache-Control: no-store\r\nConnection: close" :
	    "Pragma: no-cache");
	ws(1, "\r\nContent-Type: ");
	ws(1, mode == BIN ? "application/octet-stream" : "text/plain");
	ws(1, "\r\nContent-Length: ");
	pn(1, is_long ? (mode == BIN ? 4096 : mode == HEX ? 8194 : 5462) :
	    (mode == BIN ? 32 : mode == HEX ? 66 : 78));
	ws(1, "\r\nEntropy: ");
	pn(1, arc4random() & 0x7FFF);
	ws(1, "\r\nExpires: -1\r\n\r\n");

	while (has_post && (n = read(0, buf, 4096)) && (n <= 4096))
		arc4random_pushb_fast(buf, n);

	arc4random_buf(buf, is_long ? 4096 : mode == NUM ? 57 : 32);

	switch (mode) {
	case BIN:
		w(1, buf, is_long ? 4096 : 32);
		break;
	case HEX:
		n = is_long ? 4096 : 32;
		while (n--) {
			wB(1, mbsd_digits_HEX[buf[n] >> 4]);
			wB(1, mbsd_digits_HEX[buf[n] & 0x0F]);
		}
		wBF(1);
		w(1, "\r\n", 2);
		break;
	case NUM:
		n = is_long ? 4095 : 57;
		while (n) {
			n -= 3;
#define pb(x) wB(1, mbsd_digits_base64[x])
			pb(buf[n + 0] >> 2);
			pb(((buf[n + 0] & 0x03) << 4) + (buf[n + 1] >> 4));
			pb(((buf[n + 1] & 0x0F) << 2) + (buf[n + 2] >> 6));
			pb(buf[n + 2] & 0x3F);
#undef pb
		}
		wBF(1);
		w(1, "\r\n", 2);
		break;
	}

	return (0);
}

#ifdef lint
#define	CONSTRUCTOR
#elif defined(__PCC__)
#define	CONSTRUCTOR	_Pragma("init")
int __stack_chk_guard;				/* pcc */
#else
#define	CONSTRUCTOR	static __attribute__((__constructor__))
long __guard[8] = {0, 0, 0, 0, 0, 0, 0, 0};	/* gcc */
#endif

CONSTRUCTOR void __guard_setup(void);
__dead void __stack_smash_handler(const char func[], int damaged);

static long __guardinit[8];
CONSTRUCTOR void
__guard_setup(void)
{
	if (__guard[0] != 0)
		return;
	arc4random_buf(__guardinit, sizeof(__guardinit));
#if defined(__PCC__)
	memcpy(&__stack_chk_guard, __guardinit, sizeof(__stack_chk_guard));
#else
	memcpy(__guard, __guardinit, sizeof(__guard));
#endif
}

void
__stack_smash_handler(const char func[], __unused int damaged)
{
	ws(2, "stack overflow in function ");
	ws(2, func);
	w(1, "\r\n", 2);
	_thread_sys__exit(128+6);
}

#if defined(__PCC__)
__dead void __stack_chk_fail(void);
void
__stack_chk_fail(void)
{
	__stack_smash_handler("unknown (pcc)", 0);
}
#endif

__dead void
exit(int rv)
{
	_thread_sys__exit(rv);
}

int
atexit(void (*function)(void) __unused)
{
	errno = ENOSYS;
	return (-1);
}

void _init(void); void _init(void) { }
void _fini(void); void _fini(void) { }

__asm__(".section .note.miros.ident,\"a\",@progbits"
"\n	.p2align 2"
"\n	.long	2f-1f"			/* name size */
"\n	.long	4f-3f"			/* desc size */
"\n	.long	1"			/* type (OS version note) */
"\n1:	.asciz	\"MirOS BSD\""		/* name */
"\n2:	.p2align 2"
"\n3:	.long	0"			/* desc */
"\n4:	.p2align 2");

#if 0
.endif
#endif
