/**	$MirOS: src/sys/crypto/rijndael.h,v 1.3 2008/03/27 22:39:07 tg Exp $ */
/*	$OpenBSD: rijndael.h,v 1.11 2005/05/25 05:47:53 markus Exp $ */

/*-
 * Adaptions for VIA C3 hardware cryptography and integration is
 * Copyright © 2008, 2013
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 */

/**
 * rijndael-alg-fst.h
 *
 * @version 3.0 (December 2000)
 *
 * Optimised ANSI C code for the Rijndael cipher (now AES)
 *
 * @author Vincent Rijmen <vincent.rijmen@esat.kuleuven.ac.be>
 * @author Antoon Bosselaers <antoon.bosselaers@esat.kuleuven.ac.be>
 * @author Paulo Barreto <paulo.barreto@terra.com.br>
 *
 * This code is hereby placed in the public domain.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ''AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __RIJNDAEL_H
#define __RIJNDAEL_H

#if !defined(SMALL_KERNEL) || (defined(i386) && defined(CRYPTO))
#define __RIJNDAEL_ALIGNED	__attribute__((__aligned__(16)))
#else
#define __RIJNDAEL_ALIGNED	__attribute__((__aligned__(4)))
#endif

#define MAXKC	(256/32)
#define MAXKB	(256/8)
#define MAXNR	14

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

/*  VIA C3 additional information */
struct viac3_rijndael_ctx {
	uint32_t cw0;			/* control word */
};

/*  The structure for key information */
typedef struct {
	u32	ek[4*(MAXNR + 1) + 4]	/* encrypt key schedule */
	    __RIJNDAEL_ALIGNED;
	u32	dk[4*(MAXNR + 1) + 4]	/* decrypt key schedule */
	    __RIJNDAEL_ALIGNED;
	union {
		struct viac3_rijndael_ctx via;
	} hwcr_info;
	u8	enc_only;		/* context contains only encrypt schedule */
	u8	Nr;			/* key-length-dependent number of rounds */
#define RIJNDAEL_HWCR_SOFTWARE	0
#define RIJNDAEL_HWCR_VIA	1
	u8	hwcr_id;		/* which crypto processor is used */
} rijndael_ctx __RIJNDAEL_ALIGNED;

typedef int (*rijndael_setkey_t)(rijndael_ctx *, u_char *, int);
typedef void (*rijndael_do_cbc_t)(rijndael_ctx *, u_char *, u_char *, u_char *,
    int);

int	 rijndael_set_key(rijndael_ctx *, u_char *, int);
int	 rijndael_set_key_enc_only(rijndael_ctx *, u_char *, int);
void	 rijndael_decrypt(rijndael_ctx *, u_char *, u_char *);
void	 rijndael_encrypt(rijndael_ctx *, u_char *, u_char *);
void	 rijndael_cbc_decrypt(rijndael_ctx *, u_char *, u_char *, u_char *,
	    int);
void	 rijndael_cbc_encrypt(rijndael_ctx *, u_char *, u_char *, u_char *,
	    int);

extern rijndael_setkey_t rijndael_set_key_fast;
extern rijndael_setkey_t rijndael_set_key_enc_only_fast;
extern rijndael_do_cbc_t rijndael_cbc_decrypt_fast;
extern rijndael_do_cbc_t rijndael_cbc_encrypt_fast;

int	rijndaelKeySetupEnc(unsigned int [], const unsigned char [], int);
int	rijndaelKeySetupDec(unsigned int [], const unsigned char [], int);
void	rijndaelEncrypt(const unsigned int [], int, const unsigned char [],
	    unsigned char []);

#endif /* __RIJNDAEL_H */
