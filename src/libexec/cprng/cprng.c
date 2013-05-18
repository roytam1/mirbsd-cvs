/*-
 * Copyright (c) 2007
 *	Thorsten Glaser <tg@mirbsd.de>
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
 */

/*-
 * This is designed after the “truerand” entropy generator written by
 * Don Mitchell.  The basic idea is to measure the difference between
 * the mainboard clock and the CPU clock then pass the output through
 * whitening.  It's been designed for a SPARCstation 20 (under SunOS)
 * and a Pentium-100 (under BSD/OS), so it should be find with MirOS.
 * This is deliberately written to use as few libc calls as possible.
 *
 * The raw output stream has an entropy of about 7.8 bit/byte (97.5%)
 * if 1024 bytes of raw output are run through ports/math/ent, that's
 * why I chose to let random(9) care about post-processing instead of
 * adding arcfour output compression to this programme.
 *
 * See stathz(9) for more information on the -p flag's timer choice.
 */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#if defined(__OpenBSD__)
#include <dev/rndioctl.h>
#endif
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

__RCSID("$MirOS: src/libexec/cprng/cprng.c,v 1.10 2007/09/28 19:47:52 tg Exp $");

#ifndef MAYPROF
#if defined(SIGPROF) && defined(ITIMER_PROF)
#define MAYPROF	1
#else
#define MAYPROF	0
#endif
#endif

volatile sig_atomic_t glocke;
useconds_t littlesleep = 2000;
uint8_t obuf[1024];
uint64_t intropy = 0;
#if MAYPROF
bool doprof = false;
#endif

static void laeuten(int);
static int getbits(void);
static void getent(uint8_t *, size_t)
    __attribute__((bounded (string, 1, 2)));

#ifdef __MirBSD__
/* to keep us small */
void exit(int);
int atexit(void (*)(void));
#endif

static void
laeuten(int s __attribute__((unused)))
{
	glocke = 1;
}

static int
getbits(void)
{
	unsigned count = 0;
	struct itimerval itv = {
		.it_interval = {
			.tv_sec = 0,
			.tv_usec = 0
		},
		.it_value = {
			.tv_sec = 0,
			.tv_usec = 16667
		}
	};

	glocke = 0;
	setitimer(
#if MAYPROF
	    doprof ? ITIMER_PROF :
#endif
	    ITIMER_REAL, &itv, NULL);
	while (!glocke)
		++count;

	usleep(littlesleep);
	return (count);
}

static void
getent(uint8_t *buf, size_t n)
{
	int value = 0, bits = 0, t1, t2, tb;

	goto getent_entry;

 getent_loop:
	if ((t1 & 1) != (t2 & 1)) {
		value = (value << 1) | (t1 & 1);
		if (++bits == 8) {
			*buf++ = (uint8_t)value;
			if (--n == 0)
				return;
			bits = 0;
		}
	}
	t1 >>= 1;
	t2 >>= 1;
	if (--tb == 0) {
 getent_entry:
		t1 = getbits();
		t2 = getbits();
		tb = 12;
	}
	goto getent_loop;
}

static const char dmsg[] = "Cannot open random device!\n";
static const char emsg[] = "Syntax error!\n";
static const char fmsg[] = "Cannot daemonise!\n";

int
main(int argc, char *argv[])
{
	size_t num;
	int c = 0;
	unsigned u;
	char *cp;

#if MAYPROF
	signal(SIGPROF, laeuten);
#endif
	signal(SIGALRM, laeuten);
	if (argc == 2 && *(cp = argv[1]) == '-') {
		switch (argv[1][1]) {
		case 'r':
			c = 1;
			break;
		case 'p':
			doprof = true;
			break;
		}
		switch (argv[1][2]) {
		case 'r':
			c = 1;
			break;
		case 'p':
			doprof = true;
			break;
		}
		if (c)
			goto out_bytes;
	} else if (argc > 1) {
		write(2, emsg, sizeof (emsg) - 1);
		return (1);
	}

	switch (fork()) {
	case -1:
 edetach:
		write(2, fmsg, sizeof (fmsg) - 1);
		return (3);
	case 0:
		break;
	default:
		return(0);
	}

	if (setsid() == -1)
		goto edetach;

	if (chdir("/") || (c = open("dev/arandom", O_RDWR)) < 0) {
		write(2, dmsg, sizeof (dmsg) - 1);
		return (2);
	}

	close(0);
	close(1);
	close(2);

 main_loop:
	getent(obuf, 12 + 1);
	write(c, obuf, 12);
	u = 94;
	ioctl(c, RNDADDTOENTCNT, &u);
	usleep(littlesleep);
	if (!intropy)
		read(c, &intropy, sizeof (intropy));
	u = intropy & 0x0F;
	intropy >>= 4;
	u = ((u << 4) | u) ^ obuf[12];
	sleep((u & 0x0F) + 7);
	littlesleep = ((u & 0xF0) << 4) + 42000;
	goto main_loop;

 out_bytes:
	while (*cp < '0' || *cp > '9')
		++cp;
	if ((c = cp[0]) > '0' && c <= '9') {
		num = c - '0';
		if ((c = cp[1]) >= '0' && c <= '9') {
			num = num * 10 + c - '0';
			if ((c = cp[2]) >= '0' && c <= '9') {
				num = num * 10 + c - '0';
				if ((c = cp[3]) >= '0' && c <= '9')
					num = num * 10 + c - '0';
			}
		}
		if (num > sizeof (obuf))
			num = sizeof (obuf);
	} else
		num = 16;

	getent(obuf, num);
	write(1, obuf, num);
	return (0);
}

#ifdef __MirBSD__
void
exit(int status)
{
	close(0);
	close(1);
	close(2);
	_exit(status);
}

int
atexit(void (*function)(void) __attribute__((unused)))
{
	return (-1);
}
#endif
