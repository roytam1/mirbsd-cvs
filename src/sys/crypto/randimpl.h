/* $MirOS: src/sys/crypto/randimpl.h,v 1.3 2011/02/19 14:41:39 tg Exp $ */

/*#define RNDEBUG*/

/* contains RNG implementation details, DO NOT include in your code! */

#ifndef __IMPLEMENTATION_OF_RANDOM_H__
#define __IMPLEMENTATION_OF_RANDOM_H__

#include <dev/rndvar.h>

/* there is actually only one of these, globally */
#ifndef IN_RANDOM_CORE
extern
#endif
  struct {
	u_int add_ptr;
	u_int entropy_count;
	u_char input_rotate;
	u_int32_t pool[POOLWORDS];
	u_int asleep;
	u_int tmo;
} /* singleton */ random_state;

/* import from kernel */
extern int hz;

/* import from crypto/arc4random.c */
extern void arc4random_reinit(void *);

/* import from crypto/randcore.c */
extern uint8_t rnd_attached;
extern void rnd_flush(void);

#ifdef RNDEBUG
#define RD_INPUT	0x000F	/* input data */
#define RD_OUTPUT	0x00F0	/* output data */
#define RD_WAIT		0x0100	/* sleep/wakeup for good data */
#define	RD_ARC4RANDOM	0x0200	/* arc4random(9) */
#define RD_ARC4LOPOOL	0x0400	/* lopool collapser */
#define RD_HASHLOPOOL	0x0800	/* lopool hasher */
#define RD_ALWAYS	0x1000	/* always set, for errors */
#define RD_SRANDOM	0x2000	/* srandom() calls */
#define RD_ENQUEUE	0x4000	/* every enqueue (loud!) */
#ifdef IN_RANDOM_CORE
int rnd_debug = RD_ALWAYS;
#else
extern int rnd_debug;
#endif
extern int db_active;
extern void rnd_lopool_addvq(unsigned long);
#undef RNDEBUG
#define RNDEBUG(flag, ...)	do {				\
	if (!db_active && (rnd_debug & (flag)))			\
		printf(__VA_ARGS__);				\
} while (/* CONSTCOND */ 0)
#else
#define RNDEBUG(flag, ...)	/* nothing */
#define rnd_lopool_addvq	rnd_lopool_addv
#endif

/* import from dev/rnd.c */
extern void rndpool_init(void);

#endif
