/* $MirOS$
 *-
 * Stubbed out version of idea.c for pgp-2.6.3i
 * This makes the result uncovered by patents!
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "idea.h"
#include "randpool.h"

#ifdef IDEA32			/* Use >16-bit temporaries */
#define low16(x) ((x) & 0xFFFF)
typedef unsigned int uint16;	/* at LEAST 16 bits, maybe more */
#else
#define low16(x) (x)		/* this is only ever applied to uint16's */
typedef word16 uint16;
#endif

#ifdef _GNUC_
#define CONST __const__
#else
#define CONST
#endif

#ifndef	__dead
#define	__dead
#endif

__dead void
ideaFail(void)
{
	fprintf(stderr, "ERROR: no IDEA cipher included!\n");
	_exit(1);
}

CONST static uint16
 mulInv(uint16 x)
{
	ideaFail();
}

static void ideaExpandKey(byte const *userkey, word16 * EK)
{
	ideaFail();
}

static void ideaInvertKey(word16 const *EK, word16 DK[IDEAKEYLEN])
{
	ideaFail();
}

static void ideaCipher(byte const inbuf[8], byte outbuf[8],
		       word16 const *key)
{
	ideaFail();
}

void ideaCfbReinit(struct IdeaCfbContext *context, byte const *iv)
{
	ideaFail();
}

void ideaCfbInit(struct IdeaCfbContext *context, byte const key[16])
{
	ideaFail();
}

void ideaCfbDestroy(struct IdeaCfbContext *context)
{
	ideaFail();
}

void ideaCfbSync(struct IdeaCfbContext *context)
{
	ideaFail();
}

void ideaCfbEncrypt(struct IdeaCfbContext *context, byte const *src,
		    byte * dest, int count)
{
	ideaFail();
}

void ideaCfbDecrypt(struct IdeaCfbContext *context, byte const *src,
		    byte * dest, int count)
{
	ideaFail();
}

void ideaRandInit(struct IdeaRandContext *context, byte const key[16],
		  byte const seed[8])
{
	ideaFail();
}


void ideaRandState(struct IdeaRandContext *context, byte key[16], byte seed[8])
{
	ideaFail();
}

void ideaRandWash(struct IdeaRandContext *context, struct IdeaCfbContext *cfb)
{
	ideaFail();
}

byte
ideaRandByte(struct IdeaRandContext *c)
{
	ideaFail();
}
