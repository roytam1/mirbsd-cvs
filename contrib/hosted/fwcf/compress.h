/* $MirOS: contrib/hosted/fwcf/compress.h,v 1.1 2006/09/16 00:52:13 tg Exp $ */

/*
 * This file is part of the FreeWRT project. FreeWRT is copyrighted
 * material, please see the LICENCE file in the top-level directory
 * or at http://www.freewrt.org/license for details.
 */

#ifndef COMPRESS_H
#define COMPRESS_H

/* returns 0 on success, -1 on failure */
typedef int (*fwcf_compress_init_func)(void);
/* in: *dst (malloc'd), src, size of source (max. INT_MAX) */
/* returns size of destination on success, -1 on failure */
typedef int (*fwcf_compress_work_func)(void **, void *, size_t)
    __attribute__((bounded (string, 2, 3)));

typedef struct FWCF_COMPRESSOR {
	fwcf_compress_init_func init;
	fwcf_compress_work_func compress;
	fwcf_compress_work_func decompress;
	const char *name;
	uint8_t code;
} fwcf_compressor;

int compress_register(fwcf_compressor *);
fwcf_compressor *compress_enumerate(void);
/* 0=success 1=EINVAL 2=slot already used */
int compress_list(void);

#endif
