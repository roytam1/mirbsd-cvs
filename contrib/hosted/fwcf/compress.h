/* $MirOS: contrib/hosted/fwcf/compress.h,v 1.7 2006/09/16 07:09:49 tg Exp $ */

/*
 * This file is part of the FreeWRT project. FreeWRT is copyrighted
 * material, please see the LICENCE file in the top-level directory
 * or at http://www.freewrt.org/license for details.
 */

#ifndef COMPRESS_H
#define COMPRESS_H

/* BEGIN of plug-in API description - hook yer proprietary modules here */

/* returns 0 on success, -1 on failure */
typedef int (*fwcf_compress_init_func)(void);
/* in: *dst (malloc'd), src, size of source (max. INT_MAX) */
/* returns size of destination on success, -1 on failure */
typedef int (*fwcf_compress_work_func)(char **, char *, size_t)
    __attribute__((bounded (string, 2, 3)));
/* in: dst, max size of dst, src, size of source (max. INT_MAX) */
/* returns size of destination on success, -1 on failure */
typedef int (*fwcf_compress_rev_func)(char *, size_t, char *, size_t)
    __attribute__((bounded (string, 1, 2)))
    __attribute__((bounded (string, 3, 4)));

typedef struct FWCF_COMPRESSOR {
	fwcf_compress_init_func init;
	fwcf_compress_work_func compress;
	fwcf_compress_rev_func decompress;
	const char *name;
	uint8_t code;
} fwcf_compressor;

__BEGIN_DECLS
/* 0=success 1=EINVAL 2=slot already used */
int compress_register(fwcf_compressor *);
__END_DECLS

/* END of plug-in API description, version 1.0 */

__BEGIN_DECLS
/* low-level */
fwcf_compressor *compress_enumerate(void);
int compress_list(void);

/* high-level */
fwcf_compressor *compressor_get(uint8_t);
int list_compressors(void);
__END_DECLS

#endif
