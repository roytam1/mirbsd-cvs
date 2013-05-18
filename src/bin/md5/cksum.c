/*	$OpenBSD: md5.c,v 1.32 2004/12/29 17:32:44 millert Exp $	*/
/*	$OpenBSD: crc.c,v 1.2 2004/05/10 19:48:07 deraadt Exp $	*/
/*	$OpenBSD: crc.h,v 1.1 2004/05/02 17:53:29 millert Exp $	*/

/*
 * Copyright (c) 2001, 2003, 2004 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * Sponsored in part by the Defense Advanced Research Projects
 * Agency (DARPA) and Air Force Research Laboratory, Air Force
 * Materiel Command, USAF, under agreement number F39502-99-1-0512.
 */

/*-
 * Copyright (c) 2007, 2009
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
 */

#include <sys/param.h>
#include <sys/time.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <adler32.h>
#include <md4.h>
#include <md5.h>
#include <rmd160.h>
#include <sfv.h>
#include <sha1.h>
#include <sha2.h>
#include <suma.h>
#include <tiger.h>
#include <whirlpool.h>

extern const uint8_t RFC1321_padding[64];

__RCSID("$MirOS: src/bin/md5/cksum.c,v 1.11 2009/11/09 21:36:35 tg Exp $");

#define MAX_DIGEST_LEN			128

#define	CKSUM_DIGEST_LENGTH		4
#define	CKSUM_DIGEST_STRING_LENGTH	(10 + 1 + 19)

typedef struct CKSUMContext {
	u_int32_t crc;
	off_t len;
} CKSUM_CTX;

#define	SUM_DIGEST_LENGTH		4
#define	SUM_DIGEST_STRING_LENGTH	(10 + 1 + 16)

typedef struct SUMContext {
	u_int32_t crc;
	off_t len;
} SUM_CTX;

#define	SYSVSUM_DIGEST_LENGTH		4
#define	SYSVSUM_DIGEST_STRING_LENGTH	(10 + 1 + 16)

typedef struct SYSVSUMContext {
	u_int32_t crc;
	off_t len;
} SYSVSUM_CTX;

typedef uint32_t CDB_CTX;
typedef uint64_t SIZE_CTX;

typedef struct {
	uint32_t h;
	uint64_t s;
} OAATS_CTX;

union ANY_CTX {
	CKSUM_CTX cksum;
	MD4_CTX md4;
	MD5_CTX md5;
	RMD160_CTX rmd160;
	SHA1_CTX sha1;
	SHA256_CTX sha256;
	SHA384_CTX sha384;
	SHA512_CTX sha512;
	SUM_CTX sum;
	SYSVSUM_CTX sysvsum;
	SUMA_CTX suma;
	ADLER32_CTX adler32;
	SFV_CTX sfv;
	TIGER_CTX tiger;
	WHIRLPOOL_CTX whirlpool;
	SIZE_CTX size;
	CDB_CTX cdb;
	OAATS_CTX oaats;
};

void digest_print(const char *, const char *, const char *);
void digest_print_short(const char *, const char *, const char *);
void digest_print_string(const char *, const char *, const char *);
void digest_print_sfv(const char *, const char *, const char *);
void digest_printbin_pad(const char *);
void digest_printbin_string(const char *);
void digest_printbin_stringle(const char *);
void cksum_addpool(const char *) __attribute__((__nonnull__(1)));

void SIZE_Init(SIZE_CTX *);
void SIZE_Update(SIZE_CTX *, const uint8_t *, size_t);
char *SIZE_End(SIZE_CTX *, char *);

void CDB_Init(CDB_CTX *);
void CDB_Update(CDB_CTX *, const uint8_t *, size_t);
char *CDB_End(CDB_CTX *, char *);

void CKSUM_Init(CKSUM_CTX *);
void CKSUM_Update(CKSUM_CTX *, const u_int8_t *, size_t);
void CKSUM_Final(CKSUM_CTX *);
char *CKSUM_End(CKSUM_CTX *, char *);
char *CKSUM_Data(const u_int8_t *, size_t, char *);

void OAAT_Init(OAATS_CTX *);
void OAAT1_Init(OAATS_CTX *);
void OAAT_Update(OAATS_CTX *, const uint8_t *, size_t);
void OAAT_Final(OAATS_CTX *);
char *OAAT_End(OAATS_CTX *, char *);
char *OAAT1S_End(OAATS_CTX *, char *);

void SUM_Init(SUM_CTX *);
void SUM_Update(SUM_CTX *, const u_int8_t *, size_t);
void SUM_Final(SUM_CTX *);
char *SUM_End(SUM_CTX *, char *);
char *SUM_Data(const u_int8_t *, size_t, char *);

void SYSVSUM_Init(SYSVSUM_CTX *);
void SYSVSUM_Update(SYSVSUM_CTX *, const u_int8_t *, size_t);
void SYSVSUM_Final(SYSVSUM_CTX *);
char *SYSVSUM_End(SYSVSUM_CTX *, char *);
char *SYSVSUM_Data(const u_int8_t *, size_t, char *);

/* when adding, change lines with context matching NHASHMOD */

/* NHASHMOD: total number of hash functions */
#define NHASHES	20
struct hash_functions {
	const char *name;
	size_t digestlen;
	void *ctx;	/* XXX - only used by digest_file() */
	void (*init)(void *);
	void (*update)(void *, const unsigned char *, unsigned int);
	char * (*end)(void *, char *);
	void (*printbin)(const char *);
	void (*print)(const char *, const char *, const char *);
	void (*printstr)(const char *, const char *, const char *);
} functions[NHASHES + 1] = {
	{
		"CKSUM",
		CKSUM_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))CKSUM_Init,
		(void (*)(void *, const unsigned char *, unsigned int))CKSUM_Update,
		(char *(*)(void *, char *))CKSUM_End,
		digest_printbin_pad,
		digest_print_short,
		digest_print_short
	}, {
		"SUM",
		SUM_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))SUM_Init,
		(void (*)(void *, const unsigned char *, unsigned int))SUM_Update,
		(char *(*)(void *, char *))SUM_End,
		digest_printbin_pad,
		digest_print_short,
		digest_print_short
	}, {
		"SYSVSUM",
		SYSVSUM_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))SYSVSUM_Init,
		(void (*)(void *, const unsigned char *, unsigned int))SYSVSUM_Update,
		(char *(*)(void *, char *))SYSVSUM_End,
		digest_printbin_pad,
		digest_print_short,
		digest_print_short
	}, {
		"ADLER32",
		ADLER32_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))ADLER32Init,
		(void (*)(void *, const unsigned char *, unsigned int))ADLER32Update,
		(char *(*)(void *, char *))ADLER32End,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		"CDB",
		8,
		NULL,
		(void (*)(void *))CDB_Init,
		(void (*)(void *, const unsigned char *, unsigned int))CDB_Update,
		(char *(*)(void *, char *))CDB_End,
		digest_printbin_stringle,
		digest_print,
		digest_print_string
	}, {
		"OAAT",
		8,
		NULL,
		(void (*)(void *))OAAT_Init,
		(void (*)(void *, const unsigned char *, unsigned int))OAAT_Update,
		(char *(*)(void *, char *))OAAT_End,
		digest_printbin_stringle,
		digest_print,
		digest_print_string
	}, {
		"OAAT1",
		8,
		NULL,
		(void (*)(void *))OAAT1_Init,
		(void (*)(void *, const unsigned char *, unsigned int))OAAT_Update,
		(char *(*)(void *, char *))OAAT_End,
		digest_printbin_stringle,
		digest_print,
		digest_print_string
	}, {
		"OAAT1S",
		8,
		NULL,
		(void (*)(void *))OAAT1_Init,
		(void (*)(void *, const unsigned char *, unsigned int))OAAT_Update,
		(char *(*)(void *, char *))OAAT1S_End,
		digest_printbin_stringle,
		digest_print,
		digest_print_string
	}, {
		"SUMA",
		SUMA_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))SUMAInit,
		(void (*)(void *, const unsigned char *, unsigned int))SUMAUpdate,
		(char *(*)(void *, char *))SUMAEnd,
		digest_printbin_stringle,
		digest_print,
		digest_print_string
	}, {
		"SFV",
		SFV_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))SFVInit,
		(void (*)(void *, const unsigned char *, unsigned int))SFVUpdate,
		(char *(*)(void *, char *))SFVEnd,
		digest_printbin_stringle,
		digest_print_sfv,
		digest_print_sfv
	}, {
		"SIZE",
		16,
		NULL,
		(void (*)(void *))SIZE_Init,
		(void (*)(void *, const unsigned char *, unsigned int))SIZE_Update,
		(char *(*)(void *, char *))SIZE_End,
		digest_printbin_pad,
		digest_print,
		digest_print_string
	},
	/* NHASHMOD: non-GNU functions above, GNU functions below */
	{
		"MD4",
		MD4_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))MD4Init,
		(void (*)(void *, const unsigned char *, unsigned int))MD4Update,
		(char *(*)(void *, char *))MD4End,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		"MD5",
		MD5_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))MD5Init,
		(void (*)(void *, const unsigned char *, unsigned int))MD5Update,
		(char *(*)(void *, char *))MD5End,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		"RMD160",
		RMD160_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))RMD160Init,
		(void (*)(void *, const unsigned char *, unsigned int))RMD160Update,
		(char *(*)(void *, char *))RMD160End,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		"SHA1",
		SHA1_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))SHA1Init,
		(void (*)(void *, const unsigned char *, unsigned int))SHA1Update,
		(char *(*)(void *, char *))SHA1End,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		"SHA256",
		SHA256_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))SHA256_Init,
		(void (*)(void *, const unsigned char *, unsigned int))SHA256_Update,
		(char *(*)(void *, char *))SHA256_End,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		"SHA384",
		SHA384_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))SHA384_Init,
		(void (*)(void *, const unsigned char *, unsigned int))SHA384_Update,
		(char *(*)(void *, char *))SHA384_End,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		"SHA512",
		SHA512_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))SHA512_Init,
		(void (*)(void *, const unsigned char *, unsigned int))SHA512_Update,
		(char *(*)(void *, char *))SHA512_End,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		"TIGER",
		TIGER_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))TIGERInit,
		(void (*)(void *, const unsigned char *, unsigned int))TIGERUpdate,
		(char *(*)(void *, char *))TIGEREnd,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		"WHIRLPOOL",
		WHIRLPOOL_DIGEST_LENGTH * 2,
		NULL,
		(void (*)(void *))WHIRLPOOLInit,
		(void (*)(void *, const unsigned char *, unsigned int))WHIRLPOOLUpdate,
		(char *(*)(void *, char *))WHIRLPOOLEnd,
		digest_printbin_string,
		digest_print,
		digest_print_string
	}, {
		NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL
	},
};

__dead void usage(void);
void digest_file(const char *, struct hash_functions **, int, int, int);
int digest_filelist(const char *, struct hash_functions *);
void digest_string(char *, struct hash_functions **, int);
void digest_test(struct hash_functions **);
void digest_time(struct hash_functions **);

extern const char *__progname;

int
main(int argc, char **argv)
{
	struct hash_functions *hf = NULL, *hashes[NHASHES + 1];
	int fl, i, error;
	int cflag, pflag, tflag, xflag, bflag, gnuflag;
	char *cp, *input_string;

	input_string = NULL;
	error = cflag = pflag = tflag = xflag = bflag = gnuflag = 0;
	memset(hashes, 0, sizeof(hashes));
	while ((fl = getopt(argc, argv, "a:bcGo:ps:tx")) != -1) {
		switch (fl) {
		case 'a':
			while ((cp = strsep(&optarg, " \t,")) != NULL) {
				if (*cp == '\0')
					continue;
				for (hf = functions; hf->name != NULL; hf++)
					if (strcasecmp(hf->name, cp) == 0)
						break;
				if (hf->name == NULL) {
					warnx("unknown algorithm \"%s\"", cp);
					usage();
				}
				for (i = 0; i < NHASHES && hashes[i] != hf; i++)
					if (hashes[i] == NULL) {
						hashes[i] = hf;
						break;
					}
			}
			break;
		case 'b':
			bflag = 1;
			break;
		case 'c':
			cflag = 1;
			break;
		case 'G':
			gnuflag = 1;
			break;
		case 'o':
			if (strcmp(optarg, "1") == 0)
				hf = &functions[1];
			else if (strcmp(optarg, "2") == 0)
				hf = &functions[2];
			else {
				warnx("illegal argument to -o option");
				usage();
			}
			for (i = 0; i < NHASHES && hashes[i] != hf; i++) {
				if (hashes[i] == NULL) {
					hashes[i] = hf;
					break;
				}
			}
			break;
		case 'p':
			pflag = 1;
			break;
		case 's':
			input_string = optarg;
			break;
		case 't':
			tflag = 1;
			break;
		case 'x':
			xflag = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	/* Most arguments are mutually exclusive */
	fl = pflag + tflag + xflag + cflag + (input_string != NULL) +
	    bflag - (bflag & (pflag || input_string != NULL));
	if (fl > 1 || (fl && argc && cflag == 0 && bflag == 0) ||
	    (gnuflag && fl))
		usage();
	if (cflag != 0 && hashes[1] != NULL)
		errx(1, "only a single algorithm may be specified in -c mode");

	/* No algorithm specified, check the name we were called as. */
	if (hashes[0] == NULL) {
		char *progname2;

		if ((progname2 = strdup(__progname)) == NULL)
			err(1, "out of memory");
		if (strlen(progname2) > 3) {
			cp = progname2 + strlen(progname2) - 3;
			if (strcasecmp(cp, "sum") == 0) {
				gnuflag |= 2;
				*cp = '\0';
			}
		}

		for (hf = functions; hf->name != NULL; hf++) {
			if ((gnuflag & 2) &&
			    strcasecmp(hf->name, __progname) == 0) {
				gnuflag &= ~2;
				hashes[0] = hf;
				break;
			} else if (strcasecmp(hf->name, progname2) == 0) {
				hashes[0] = hf;
				break;
			}
		}
		if (hashes[0] == NULL)
			hashes[0] = &functions[0];	/* default to cksum */
		if (gnuflag & 2) {
			if (cflag || pflag || input_string || xflag) {
				fprintf(stderr,
				    "usage: %s [-b] [-t] [file ...]\n"
				    "note: GNU syntax -c and -w are not supported.\n",
				    __progname);
				__progname = progname2;
				usage();
			}
			bflag = 0;
			tflag = 0;
		}
		free(progname2);
	}

	if (tflag)
		digest_time(hashes);
	else if (xflag)
		digest_test(hashes);
	else if (input_string)
		digest_string(input_string, hashes, bflag);
	else if (cflag) {
		if (argc == 0)
			error = digest_filelist("-", hashes[0]);
		else
			while (argc--)
				error += digest_filelist(*argv++, hashes[0]);
	} else if (pflag || argc == 0)
		digest_file("-", hashes, pflag, bflag, gnuflag);
	else
		while (argc--)
			digest_file(*argv++, hashes, 0, bflag, gnuflag);

	return(error ? EXIT_FAILURE : EXIT_SUCCESS);
}

void
digest_string(char *string, struct hash_functions **hashes, int dobin)
{
	struct hash_functions *hf;
	char digest[MAX_DIGEST_LEN + 1];
	union ANY_CTX context;

	while (*hashes != NULL) {
		hf = *hashes++;
		hf->init(&context);
		hf->update(&context, (const unsigned char *)string,
		    (unsigned int)strlen(string));
		(void)hf->end(&context, digest);
		cksum_addpool(digest);
		if (dobin)
			hf->printbin(digest);
		else
			hf->printstr(hf->name, string, digest);
	}
}

void
digest_print(const char *name, const char *what, const char *digest)
{
	(void)printf("%s (%s) = %s\n", name, what, digest);
}

void
digest_print_string(const char *name, const char *what, const char *digest)
{
	(void)printf("%s (\"%s\") = %s\n", name, what, digest);
}

void
digest_print_short(const char *name __attribute__((unused)),
    const char *what, const char *digest)
{
	(void)printf("%s %s\n", digest, what);
}

void
digest_print_sfv(const char *name __attribute__((unused)),
    const char *what, const char *digest)

{
	(void)printf("%s %s\n", what, digest);
}

void
digest_file(const char *file, struct hash_functions **hashes, int echo,
    int dobin, int dognu)
{
	struct hash_functions **hfp;
	int fd;
	ssize_t nread;
	u_char data[BUFSIZ];
	char digest[MAX_DIGEST_LEN + 1];

	if (strcmp(file, "-") == 0)
		fd = STDIN_FILENO;
	else if ((fd = open(file, O_RDONLY, 0)) == -1) {
		warn("cannot open %s", file);
		return;
	}

	if (echo)
		fflush(stdout);

	for (hfp = hashes; *hfp != NULL; hfp++) {
		if (((*hfp)->ctx = malloc(sizeof(union ANY_CTX))) == NULL)
			err(1, NULL);
		(*hfp)->init((*hfp)->ctx);
	}
	while ((nread = read(fd, data, sizeof(data))) > 0) {
		if (echo)
			write(STDOUT_FILENO, data, (size_t)nread);
		for (hfp = hashes; *hfp != NULL; hfp++)
			(*hfp)->update((*hfp)->ctx, data, (unsigned int)nread);
	}
	if (nread == -1) {
		warn("%s: read error", file);
		if (fd != STDIN_FILENO)
			close(fd);
		return;
	}
	if (fd != STDIN_FILENO)
		close(fd);
	for (hfp = hashes; *hfp != NULL; hfp++) {
		(void)(*hfp)->end((*hfp)->ctx, digest);
		free((*hfp)->ctx);
		cksum_addpool(digest);
		if (dobin)
			(*hfp)->printbin(digest);
		else if (dognu)
			printf("%s  %s\n", digest,
			    fd == STDIN_FILENO ? "-" : file);
		else if (fd == STDIN_FILENO)
			(void)puts(digest);
		else
			(*hfp)->print((*hfp)->name, file, digest);
	}
}

/*
 * Parse through the input file looking for valid lines.
 * If one is found, use this checksum and file as a reference and
 * generate a new checksum against the file on the filesystem.
 * Print out the result of each comparison.
 */
int
digest_filelist(const char *file, struct hash_functions *defhash)
{
	int fd, found, error;
	unsigned int algorithm_max, algorithm_min;
	const char *algorithm;
	char *filename, *checksum, *buf, *p;
	char digest[MAX_DIGEST_LEN + 1];
	char *lbuf = NULL;
	FILE *fp;
	ssize_t nread;
	size_t len;
	u_char data[BUFSIZ];
	union ANY_CTX context;
	struct hash_functions *hf;

	if (strcmp(file, "-") == 0) {
		fp = stdin;
	} else if ((fp = fopen(file, "r")) == NULL) {
		warn("cannot open %s", file);
		return(1);
	}

	/* NHASHMOD: first GNU style function (and list below) */
	if (defhash < &functions[11])
		/*
		 * no GNU format for cksum, sum, sysvsum, adler32,
		 * cdb, oaat, oaat1, oaat1s, suma, sfv, size
		 */
		defhash = NULL;

	algorithm_max = algorithm_min = strlen(functions[0].name);
	for (hf = &functions[1]; hf->name != NULL; hf++) {
		len = strlen(hf->name);
		algorithm_max = MAX(algorithm_max, len);
		algorithm_min = MIN(algorithm_min, len);
	}

	error = found = 0;
	while ((buf = fgetln(fp, &len))) {
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		else {
			if ((lbuf = malloc(len + 1)) == NULL)
				err(1, NULL);

			(void)memcpy(lbuf, buf, len);
			lbuf[len] = '\0';
			buf = lbuf;
		}
		while (isspace(*buf))
			buf++;

		/*
		 * Crack the line into an algorithm, filename, and checksum.
		 * Lines are of the form:
		 *  ALGORITHM (FILENAME) = CHECKSUM
		 *
		 * Fallback on GNU form:
		 *  CHECKSUM  FILENAME
		 */
		p = strchr(buf, ' ');
		if (p != NULL && *(p + 1) == '(') {
			/* BSD form */
			*p = '\0';
			algorithm = buf;
			len = strlen(algorithm);
			if (len > algorithm_max || len < algorithm_min)
				continue;

			filename = p + 2;
			p = strrchr(filename, ')');
			if (p == NULL || strncmp(p + 1, " = ", (size_t)3) != 0)
				continue;
			*p = '\0';

			checksum = p + 4;
			p = strpbrk(checksum, " \t\r");
			if (p != NULL)
				*p = '\0';

			/*
			 * Check that the algorithm is one we recognize.
			 */
			for (hf = functions; hf->name != NULL; hf++) {
				if (strcmp(algorithm, hf->name) == 0)
					break;
			}
			if (hf->name == NULL ||
			    strlen(checksum) != hf->digestlen)
				continue;
		} else {
			/* could be GNU form */
			if ((hf = defhash) == NULL)
				continue;
			algorithm = hf->name;
			checksum = buf;
			if ((p = strchr(checksum, ' ')) == NULL)
				continue;
			*p++ = '\0';
			while (isspace(*p))
				p++;
			if (*p == '\0')
				continue;
			filename = p;
			p = strpbrk(filename, "\t\r");
			if (p != NULL)
				*p = '\0';
		}

		if ((fd = open(filename, O_RDONLY, 0)) == -1) {
			warn("cannot open %s", filename);
			(void)printf("(%s) %s: FAILED\n", algorithm, filename);
			error = 1;
			continue;
		}

		found = 1;
		hf->init(&context);
		while ((nread = read(fd, data, sizeof(data))) > 0)
			hf->update(&context, data, (unsigned int)nread);
		if (nread == -1) {
			warn("%s: read error", file);
			error = 1;
			close(fd);
			continue;
		}
		close(fd);
		(void)hf->end(&context, digest);
		cksum_addpool(digest);

		if (strcmp(checksum, digest) == 0)
			(void)printf("(%s) %s: OK\n", algorithm, filename);
		else
			(void)printf("(%s) %s: FAILED\n", algorithm, filename);
	}
	if (fp != stdin)
		fclose(fp);
	if (!found)
		warnx("%s: no properly formatted checksum lines found", file);
	if (lbuf != NULL)
		free(lbuf);
	return(error || !found);
}

#define TEST_BLOCK_LEN 10000
#define TEST_BLOCK_COUNT 10000

#ifndef timersub
#define timersub(tvp, uvp, vvp)                                         \
        do {                                                            \
                (vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;          \
                (vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;       \
                if ((vvp)->tv_usec < 0) {                               \
                        (vvp)->tv_sec--;                                \
                        (vvp)->tv_usec += 1000000;                      \
                }                                                       \
        } while (0)
#endif

void
digest_time(struct hash_functions **hashes)
{
	struct hash_functions *hf;
	struct timeval start, stop, res;
	union ANY_CTX context;
	unsigned i;
	u_char data[TEST_BLOCK_LEN];
	char digest[MAX_DIGEST_LEN + 1];
	double elapsed;

	while (*hashes != NULL) {
		hf = *hashes++;
		(void)printf("%s time trial.  Processing %d %d-byte blocks...",
		    hf->name, TEST_BLOCK_COUNT, TEST_BLOCK_LEN);
		fflush(stdout);

		/* Initialize data based on block number. */
		for (i = 0; i < TEST_BLOCK_LEN; i++)
			data[i] = (u_char)(i & 0xff);

		gettimeofday(&start, NULL);
		hf->init(&context);
		for (i = 0; i < TEST_BLOCK_COUNT; i++)
			hf->update(&context, data, TEST_BLOCK_LEN);
		(void)hf->end(&context, digest);
		gettimeofday(&stop, NULL);
		timersub(&stop, &start, &res);
		elapsed = res.tv_sec + res.tv_usec / 1000000.0;

		(void)printf("\nDigest = %s\n", digest);
		(void)printf("Time   = %f seconds\n", elapsed);
		(void)printf("Speed  = %f bytes/second\n",
		    TEST_BLOCK_LEN * TEST_BLOCK_COUNT / elapsed);
	}
}

void
digest_test(struct hash_functions **hashes)
{
	struct hash_functions *hf;
	union ANY_CTX context;
	int i;
	char digest[MAX_DIGEST_LEN + 1];
	unsigned char buf[1000];
	const char *test_strings[] = {
		"",
		"a",
		"abc",
		"message digest",
		"abcdefghijklmnopqrstuvwxyz",
		"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
		    "0123456789",
		"12345678901234567890123456789012345678901234567890123456789"
		    "012345678901234567890",
	};

	while (*hashes != NULL) {
		hf = *hashes++;
		(void)printf("%s test suite:\n", hf->name);

		for (i = 0; i < 8; i++) {
			hf->init(&context);
			hf->update((void *)&context,
			    (unsigned const char *)test_strings[i],
			    (unsigned int)strlen(test_strings[i]));
			(void)hf->end(&context, digest);
			hf->printstr(hf->name, test_strings[i], digest);
		}

		/* Now simulate a string of a million 'a' characters. */
		memset(buf, 'a', sizeof(buf));
		hf->init(&context);
		for (i = 0; i < 1000; i++)
			hf->update(&context, buf,
			    (unsigned int)sizeof(buf));
		(void)hf->end(&context, digest);
		hf->print(hf->name, "one million 'a' characters",
		    digest);
	}
}

void
usage(void)
{
	fprintf(stderr, "usage: %s [-[b]p | -t | -x | -c [cklst ...] | "
	    "-[b]s string | [-bG] file ...]\n", __progname);
	if (strcmp(__progname, "cksum") == 0)
		fprintf(stderr, "             [-a algorithms]] [-o 1 | 2]\n");

	exit(EXIT_FAILURE);
}

void
digest_printbin_pad(const char *digest)
{
	uint64_t one, two;
	char *c;

	one = strtoll(digest, &c, 10);
	if (*c) {
		two = strtoll(++c, NULL, 10);
		if (asprintf(&c, "%016llX%016llX", one, two) == -1)
			return;
	} else if (asprintf(&c, "%016llX", one) == -1)
		return;
	digest_printbin_string(c);
	free(c);
}

void
digest_printbin_string(const char *digest)
{
	int i, j, k;

	for (i = 0; i < (ssize_t)(strlen(digest)/2); ++i) {
		j = digest[i * 2] - 0x30;
		k = digest[i * 2 + 1] - 0x30;
		if ((j < 0) || (k < 0))
			break;
		j = (j > 9) ? (((j - 7) > 15) ? (j - 0x27) : (j - 7)) : j;
		k = (k > 9) ? (((k - 7) > 15) ? (k - 0x27) : (k - 7)) : k;
		if ((j < 0) || (k < 0) || (j > 15) || (k > 15))
			break;
		putchar((j << 4) | k);
	}
}

void
digest_printbin_stringle(const char *digest)
{
	uint32_t dgst;
	char *c;

	dgst = strtoul(digest, NULL, 16);
	if (asprintf(&c, "%02X%02X%02X%02X",
	    dgst & 0xff, (dgst >> 8) & 0xff,
	    (dgst >> 16) & 0xff, dgst >> 24) == -1)
		return;
	digest_printbin_string(c);
	free(c);
}

void
SIZE_Init(SIZE_CTX *ctx)
{
	*ctx = 0;
}

void
SIZE_Update(SIZE_CTX *ctx, const uint8_t *buf __attribute__((unused)), size_t n)
{
	*ctx += n;
}

char *
SIZE_End(SIZE_CTX *ctx, char *digest)
{
	if (digest == NULL) {
		if (asprintf(&digest, "%llu", *ctx) == -1)
			return (NULL);
	} else
		snprintf(digest, 21, "%llu", *ctx);

	return (digest);
}

void
CDB_Init(CDB_CTX *ctx)
{
	*ctx = 5381;
}

void
CDB_Update(CDB_CTX *ctx, const uint8_t *buf, size_t n)
{
	register uint32_t h;

	h = *ctx;
	while (n--)
		h = ((h << 5) + h) ^ *buf++;
	*ctx = h;
}

char *
CDB_End(CDB_CTX *ctx, char *digest)
{
	if (digest == NULL) {
		if (asprintf(&digest, "%08X", *ctx) == -1)
			return (NULL);
	} else
		snprintf(digest, 17, "%08X", *ctx);

	return (digest);
}

void
OAAT_Init(OAATS_CTX *ctx)
{
	ctx->h = 0;
	ctx->s = 0;
}

void
OAAT1_Init(OAATS_CTX *ctx)
{
	ctx->h = 0x100;
	ctx->s = 0;
}

void
OAAT_Update(OAATS_CTX *ctx, const uint8_t *buf, size_t n)
{
	register uint32_t h;

	ctx->s += n;
	h = ctx->h;
	while (n--) {
		h += *buf++;
		h += h << 10;
		h ^= h >> 6;
	}
	ctx->h = h;
}

void
OAAT_Final(OAATS_CTX *ctx)
{
	register uint32_t h;

	h = ctx->h;
	h += h << 3;
	h ^= h >> 11;
	h += h << 15;
	ctx->h = h;
}

char *
OAAT1S_End(OAATS_CTX *ctx, char *digest)
{
	uint8_t le_len[8];
	uint64_t bits;

	bits = ctx->s << 3;
	le_len[0] = bits & 0xFF; bits >>= 8;
	le_len[1] = bits & 0xFF; bits >>= 8;
	le_len[2] = bits & 0xFF; bits >>= 8;
	le_len[3] = bits & 0xFF; bits >>= 8;
	le_len[4] = bits & 0xFF; bits >>= 8;
	le_len[5] = bits & 0xFF; bits >>= 8;
	le_len[6] = bits & 0xFF; bits >>= 8;
	le_len[7] = bits;

	/* look, ma! mirabilos can do nicer formulas than Markus Friedl */
	OAAT_Update(ctx, RFC1321_padding, 64 - ((ctx->s + 8) & 63));
	OAAT_Update(ctx, le_len, 8);

	return (OAAT_End(ctx, digest));
}

char *
OAAT_End(OAATS_CTX *ctx, char *digest)
{
	OAAT_Final(ctx);

	if (digest == NULL) {
		if (asprintf(&digest, "%08X", ctx->h) == -1)
			return (NULL);
	} else
		snprintf(digest, 17, "%08X", ctx->h);

	return (digest);
}

/*
 * Table-driven version of the following polynomial from POSIX 1003.2:
 *  G(x) = x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 +
 *	   x^7 + x^5 + x^4 + x^2 + x + 1
 */
static const u_int32_t crc32tab[] = {
	0x00000000U,
	0x04c11db7U, 0x09823b6eU, 0x0d4326d9U, 0x130476dcU, 0x17c56b6bU,
	0x1a864db2U, 0x1e475005U, 0x2608edb8U, 0x22c9f00fU, 0x2f8ad6d6U,
	0x2b4bcb61U, 0x350c9b64U, 0x31cd86d3U, 0x3c8ea00aU, 0x384fbdbdU,
	0x4c11db70U, 0x48d0c6c7U, 0x4593e01eU, 0x4152fda9U, 0x5f15adacU,
	0x5bd4b01bU, 0x569796c2U, 0x52568b75U, 0x6a1936c8U, 0x6ed82b7fU,
	0x639b0da6U, 0x675a1011U, 0x791d4014U, 0x7ddc5da3U, 0x709f7b7aU,
	0x745e66cdU, 0x9823b6e0U, 0x9ce2ab57U, 0x91a18d8eU, 0x95609039U,
	0x8b27c03cU, 0x8fe6dd8bU, 0x82a5fb52U, 0x8664e6e5U, 0xbe2b5b58U,
	0xbaea46efU, 0xb7a96036U, 0xb3687d81U, 0xad2f2d84U, 0xa9ee3033U,
	0xa4ad16eaU, 0xa06c0b5dU, 0xd4326d90U, 0xd0f37027U, 0xddb056feU,
	0xd9714b49U, 0xc7361b4cU, 0xc3f706fbU, 0xceb42022U, 0xca753d95U,
	0xf23a8028U, 0xf6fb9d9fU, 0xfbb8bb46U, 0xff79a6f1U, 0xe13ef6f4U,
	0xe5ffeb43U, 0xe8bccd9aU, 0xec7dd02dU, 0x34867077U, 0x30476dc0U,
	0x3d044b19U, 0x39c556aeU, 0x278206abU, 0x23431b1cU, 0x2e003dc5U,
	0x2ac12072U, 0x128e9dcfU, 0x164f8078U, 0x1b0ca6a1U, 0x1fcdbb16U,
	0x018aeb13U, 0x054bf6a4U, 0x0808d07dU, 0x0cc9cdcaU, 0x7897ab07U,
	0x7c56b6b0U, 0x71159069U, 0x75d48ddeU, 0x6b93dddbU, 0x6f52c06cU,
	0x6211e6b5U, 0x66d0fb02U, 0x5e9f46bfU, 0x5a5e5b08U, 0x571d7dd1U,
	0x53dc6066U, 0x4d9b3063U, 0x495a2dd4U, 0x44190b0dU, 0x40d816baU,
	0xaca5c697U, 0xa864db20U, 0xa527fdf9U, 0xa1e6e04eU, 0xbfa1b04bU,
	0xbb60adfcU, 0xb6238b25U, 0xb2e29692U, 0x8aad2b2fU, 0x8e6c3698U,
	0x832f1041U, 0x87ee0df6U, 0x99a95df3U, 0x9d684044U, 0x902b669dU,
	0x94ea7b2aU, 0xe0b41de7U, 0xe4750050U, 0xe9362689U, 0xedf73b3eU,
	0xf3b06b3bU, 0xf771768cU, 0xfa325055U, 0xfef34de2U, 0xc6bcf05fU,
	0xc27dede8U, 0xcf3ecb31U, 0xcbffd686U, 0xd5b88683U, 0xd1799b34U,
	0xdc3abdedU, 0xd8fba05aU, 0x690ce0eeU, 0x6dcdfd59U, 0x608edb80U,
	0x644fc637U, 0x7a089632U, 0x7ec98b85U, 0x738aad5cU, 0x774bb0ebU,
	0x4f040d56U, 0x4bc510e1U, 0x46863638U, 0x42472b8fU, 0x5c007b8aU,
	0x58c1663dU, 0x558240e4U, 0x51435d53U, 0x251d3b9eU, 0x21dc2629U,
	0x2c9f00f0U, 0x285e1d47U, 0x36194d42U, 0x32d850f5U, 0x3f9b762cU,
	0x3b5a6b9bU, 0x0315d626U, 0x07d4cb91U, 0x0a97ed48U, 0x0e56f0ffU,
	0x1011a0faU, 0x14d0bd4dU, 0x19939b94U, 0x1d528623U, 0xf12f560eU,
	0xf5ee4bb9U, 0xf8ad6d60U, 0xfc6c70d7U, 0xe22b20d2U, 0xe6ea3d65U,
	0xeba91bbcU, 0xef68060bU, 0xd727bbb6U, 0xd3e6a601U, 0xdea580d8U,
	0xda649d6fU, 0xc423cd6aU, 0xc0e2d0ddU, 0xcda1f604U, 0xc960ebb3U,
	0xbd3e8d7eU, 0xb9ff90c9U, 0xb4bcb610U, 0xb07daba7U, 0xae3afba2U,
	0xaafbe615U, 0xa7b8c0ccU, 0xa379dd7bU, 0x9b3660c6U, 0x9ff77d71U,
	0x92b45ba8U, 0x9675461fU, 0x8832161aU, 0x8cf30badU, 0x81b02d74U,
	0x857130c3U, 0x5d8a9099U, 0x594b8d2eU, 0x5408abf7U, 0x50c9b640U,
	0x4e8ee645U, 0x4a4ffbf2U, 0x470cdd2bU, 0x43cdc09cU, 0x7b827d21U,
	0x7f436096U, 0x7200464fU, 0x76c15bf8U, 0x68860bfdU, 0x6c47164aU,
	0x61043093U, 0x65c52d24U, 0x119b4be9U, 0x155a565eU, 0x18197087U,
	0x1cd86d30U, 0x029f3d35U, 0x065e2082U, 0x0b1d065bU, 0x0fdc1becU,
	0x3793a651U, 0x3352bbe6U, 0x3e119d3fU, 0x3ad08088U, 0x2497d08dU,
	0x2056cd3aU, 0x2d15ebe3U, 0x29d4f654U, 0xc5a92679U, 0xc1683bceU,
	0xcc2b1d17U, 0xc8ea00a0U, 0xd6ad50a5U, 0xd26c4d12U, 0xdf2f6bcbU,
	0xdbee767cU, 0xe3a1cbc1U, 0xe760d676U, 0xea23f0afU, 0xeee2ed18U,
	0xf0a5bd1dU, 0xf464a0aaU, 0xf9278673U, 0xfde69bc4U, 0x89b8fd09U,
	0x8d79e0beU, 0x803ac667U, 0x84fbdbd0U, 0x9abc8bd5U, 0x9e7d9662U,
	0x933eb0bbU, 0x97ffad0cU, 0xafb010b1U, 0xab710d06U, 0xa6322bdfU,
	0xa2f33668U, 0xbcb4666dU, 0xb8757bdaU, 0xb5365d03U, 0xb1f740b4U
};

void
CKSUM_Init(CKSUM_CTX *ctx)
{
	ctx->crc = 0;
	ctx->len = 0;
}

#define	UPDATE(crc, byte) do						\
	(crc) = ((crc) << 8) ^ crc32tab[((crc) >> 24) ^ (byte)];	\
while(0)

void
CKSUM_Update(CKSUM_CTX *ctx, const unsigned char *buf, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		UPDATE(ctx->crc, buf[i]);
	ctx->len += len;
}

void
CKSUM_Final(CKSUM_CTX *ctx)
{
	off_t len = ctx->len;

	/* add in number of bytes read and finish */
	while (len != 0) {
		UPDATE(ctx->crc, len & 0xff);
		len >>= 8;
	}
	ctx->crc = ~ctx->crc;
}

char *
CKSUM_End(CKSUM_CTX *ctx, char *outstr)
{
	CKSUM_Final(ctx);

	if (outstr == NULL) {
		if (asprintf(&outstr, "%u %lld", ctx->crc,
		    (int64_t)ctx->len) == -1)
			return (NULL);
	} else {
		(void)snprintf(outstr, (size_t)CKSUM_DIGEST_STRING_LENGTH,
		    "%u %lld", ctx->crc, (int64_t)ctx->len);
	}

	return (outstr);
}

void
SUM_Init(SUM_CTX *ctx)
{
	ctx->crc = 0;
	ctx->len = 0;
}

void
SUM_Update(SUM_CTX *ctx, const unsigned char *buf, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		ctx->crc = ((ctx->crc >> 1) + ((ctx->crc & 1) << 15) + buf[i]);
		ctx->crc &= 0xffff;
	}
	ctx->len += len;
}

void
SUM_Final(SUM_CTX *ctx)
{
	ctx->len = (ctx->len + 1023) / 1024;	/* convert to 1 KiB blocks */
}

char *
SUM_End(SUM_CTX *ctx, char *outstr)
{
	SUM_Final(ctx);

	if (outstr == NULL) {
		if (asprintf(&outstr, "%u %lld", ctx->crc,
		    (int64_t)ctx->len) == -1)
			return (NULL);
	} else {
		(void)snprintf(outstr, (size_t)SUM_DIGEST_STRING_LENGTH,
		    "%u %lld", ctx->crc, (int64_t)ctx->len);
	}

	return (outstr);
}

void
SYSVSUM_Init(SYSVSUM_CTX *ctx)
{
	ctx->crc = 0;
	ctx->len = 0;
}

void
SYSVSUM_Update(SYSVSUM_CTX *ctx, const unsigned char *buf, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		ctx->crc += buf[i];
	ctx->len += len;
}

void
SYSVSUM_Final(SYSVSUM_CTX *ctx)
{
	ctx->crc = (ctx->crc & 0xffff) + (ctx->crc >> 16);
	ctx->crc = (ctx->crc & 0xffff) + (ctx->crc >> 16);
	ctx->len = (ctx->len + 511) / 512;	/* convert to 512 byte blocks */
}

char *
SYSVSUM_End(SYSVSUM_CTX *ctx, char *outstr)
{
	SYSVSUM_Final(ctx);

	if (outstr == NULL) {
		if (asprintf(&outstr, "%u %lld", ctx->crc,
		    (int64_t)ctx->len) == -1)
			return (NULL);
	} else {
		(void)snprintf(outstr, (size_t)SYSVSUM_DIGEST_STRING_LENGTH,
		    "%u %lld", ctx->crc, (int64_t)ctx->len);
	}

	return (outstr);
}

void
cksum_addpool(const char *s)
{
#if defined(arc4random_pushb_fast)
	arc4random_pushb_fast(s, strlen(s) + 1);
#else
	ADLER32_CTX tmp;

	ADLER32Update(&tmp, (const uint8_t *)s, strlen(s));
#if defined(arc4random_pushk)
	arc4random_pushk(&tmp, sizeof (ADLER32_CTX));
#elif defined(MirBSD) && (MirBSD > 0x09A1)
	arc4random_pushb(&tmp, sizeof (ADLER32_CTX));
#endif
#endif
}
