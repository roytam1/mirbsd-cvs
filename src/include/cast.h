/*	$MirOS: src/include/cast.h,v 1.2 2014/11/30 01:43:36 tg Exp $ */
/*      $OpenBSD: cast.h,v 1.2 1998/07/21 22:42:01 provos Exp $       */
/*
 *	CAST-128 in C
 *	Written by Steve Reid <sreid@sea-to-sky.net>
 *	100% Public Domain - no warranty
 *	Released 1997.10.11
 */

#ifndef _CAST_H_
#define _CAST_H_

typedef struct {
	u_int32_t xkey[32];	/* Key, after expansion */
	int rounds;		/* Number of rounds to use, 12 or 16 */
} cast_key;

void cast_setkey(cast_key* key, const u_int8_t* rawkey, int keybytes);
void cast_encrypt(const cast_key* key, u_int8_t* inblock, u_int8_t* outblock);
void cast_decrypt(const cast_key* key, u_int8_t* inblock, u_int8_t* outblock);

void cast_encrypt2(const cast_key* key, u_int32_t *data);
void cast_decrypt2(const cast_key* key, u_int32_t *data);

#endif /* ifndef _CAST_H_ */

