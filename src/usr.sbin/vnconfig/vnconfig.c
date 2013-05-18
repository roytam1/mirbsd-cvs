/**	$MirOS: src/usr.sbin/vnconfig/vnconfig.c,v 1.14 2007/08/08 22:20:17 tg Exp $ */
/*	$OpenBSD: vnconfig.c,v 1.16 2004/09/14 22:35:51 deraadt Exp $	*/
/*
 * Copyright (c) 2006, 2010 Thorsten Glaser
 * Copyright (c) 1993 University of Utah.
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * from: Utah $Hdr: vnconfig.c 1.1 93/12/15$
 *
 *	@(#)vnconfig.c	8.1 (Berkeley) 12/15/93
 */

#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/stat.h>

#include <dev/vndioctl.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <util.h>

#ifndef SMALL
#include <openssl/asn1.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#endif

__RCSID("$MirOS: src/usr.sbin/vnconfig/vnconfig.c,v 1.14 2007/08/08 22:20:17 tg Exp $");

#define DEFAULT_VND	"vnd0"

#define VND_CONFIG	1
#define VND_UNCONFIG	2
#define VND_GET		3
#define VND_MAKEKEY	4

#define BLF_MAX_BYTES	72

int verbose = 0;

__dead void usage(void);
int config(char *, char *, int, char *, size_t, u_int32_t);
int getinfo(const char *);
#ifndef SMALL
static void extract_key(FILE *, char **, int *);
static int make_key(const char *, FILE *, const char *);
#endif

int
main(int argc, char **argv)
{
	int ch, rv, action = VND_CONFIG, flags = 0, keylen = 0;
	char *key = NULL;
#ifndef SMALL
	char *key2 = NULL, *keyfile = NULL, *algo = NULL;
	FILE *keyfp = NULL;
#endif

	while ((ch = getopt(argc, argv, "cf:K:klruv")) != -1) {
		switch (ch) {
		case 'c':
			action = VND_CONFIG;
			break;
#ifndef SMALL
		case 'f':
			keyfile = optarg;
			break;
		case 'K':
			action = VND_MAKEKEY;
			algo = optarg;
			break;
#endif
		case 'l':
			action = VND_GET;
			break;
		case 'u':
			action = VND_UNCONFIG;
			break;
		case 'v':
			verbose = 1;
			break;
		case 'k':
			key = getpass("Encryption key: ");
			if (key == NULL)
				errx(1, "getpass");
			keylen = strlen(key);
			break;
		case 'r':
			flags |= VNDIOC_OPT_RDONLY;
			break;
		default:
			usage();
			/* NOTREACHED */
		}
	}

	argc -= optind;
	argv += optind;

#ifndef SMALL
	if (keyfile) {
		keyfp = fopen(keyfile, (action == VND_MAKEKEY) ? "wb" : "rb");
		if (keyfp == NULL)
			err(1, "fopen");
		if (action != VND_MAKEKEY)
			extract_key(keyfp, &key, &keylen);
	}

	if (key && action == VND_MAKEKEY) {
		key2 = getpass("repeat the key: ");
		if (memcmp(key, key2, 1+keylen))
			errx(1, "keys not identical");
	}
#endif

	if (action == VND_CONFIG && argc == 2)
		rv = config(argv[0], argv[1], action, key, keylen,
		    flags);
	else if (action == VND_UNCONFIG && argc == 1)
		rv = config(argv[0], NULL, action, key, keylen,
		    flags | VNDIOC_OPT_RDONLY);
	else if (action == VND_GET)
		rv = getinfo(argc ? argv[0] : NULL);
#ifndef SMALL
	else if (action == VND_MAKEKEY)
		rv = make_key(algo, keyfp, key2);
#endif
	else
		usage();

#ifndef SMALL
	if (keyfp)
		fclose(keyfp);
#endif
	return (rv);
}

int
getinfo(const char *vname)
{
	int vd, print_all = 0;
	struct vnd_user vnu;
	char *vnamedup;

	if (vname == NULL) {
		vname = DEFAULT_VND;
		print_all = 1;
	}

	if ((vnamedup = strdup(vname)) == NULL)
		err(1, "strdup");
	vd = opendev(vnamedup, O_RDONLY, OPENDEV_PART, NULL);
	free(vnamedup);
	if (vd < 0)
		err(1, "open: %s", vname);

	vnu.vnu_unit = -1;

query:
	if (ioctl(vd, VNDIOCGET, &vnu) == -1) {
		close(vd);
		return (!(errno == ENXIO && print_all));
	}

	fprintf(stdout, "vnd%d: ", vnu.vnu_unit);

	if (!vnu.vnu_ino)
		fprintf(stdout, "not in use\n");
	else
		fprintf(stdout, "covering %s on %s, inode %d\n", vnu.vnu_file,
		    devname(vnu.vnu_dev, S_IFBLK), vnu.vnu_ino);

	if (print_all) {
		vnu.vnu_unit++;
		goto query;
	}

	close(vd);

	return (0);
}

int
config(char *dev, char *file, int action, char *key, size_t klen,
    u_int32_t flags)
{
	struct vnd_ioctl vndio;
	FILE *f;
	char *rdev;
	int rv = 0;

	if (opendev(dev, (flags & VNDIOC_OPT_RDONLY) ? O_RDONLY : O_RDWR,
	    OPENDEV_PART, &rdev) < 0)
		err(4, "%s", rdev);
	f = fopen(rdev, "rw");
	if (f == NULL) {
		warn("%s", rdev);
		rv = -1;
		goto out;
	}
	vndio.vnd_file = file;
	vndio.vnd_key = (u_char *)key;
	vndio.vnd_keylen = klen;
	vndio.vnd_options = flags;

	/*
	 * Clear (un-configure) the device
	 */
	if (action == VND_UNCONFIG) {
		rv = ioctl(fileno(f), VNDIOCCLR, &vndio);
		if (rv)
			warn("VNDIOCCLR");
		else if (verbose)
			printf("%s: cleared\n", dev);
	}
	/*
	 * Configure the device
	 */
	if (action == VND_CONFIG) {
		rv = ioctl(fileno(f), VNDIOCSET, &vndio);
		if (rv)
			warn("VNDIOCSET");
		else if (verbose)
			printf("%s: %llu bytes on %s\n", dev, vndio.vnd_size,
			    file);
	}

	fclose(f);
	fflush(stdout);
 out:
	if (key)
		memset(key, 0, klen);
	return (rv < 0);
}

__dead void
usage(void)
{
	extern const char *__progname;

	(void)fprintf(stderr,
	    "usage: %s [-c] [-krv] [-f keyfile] rawdev regular-file\n"
	    "       %s -u [-v] rawdev\n"
	    "       %s -K algorithm -f keyfile\n"
	    "       %s -l [rawdev]\n",
	    __progname, __progname, __progname, __progname);
	exit(1);
}

#ifndef SMALL
static int
make_key(const char *algo, FILE *fp, const char *key2)
{
	ASN1_OCTET_STRING *aos;
	const EVP_CIPHER *enc = NULL;
#define KBUF_ELEM	(BLF_MAX_BYTES / 4)
	uint32_t kbuf[KBUF_ELEM];
	int i;
	size_t kbuflen = sizeof (kbuf);

	if (algo == NULL || fp == NULL)
		usage();

	ERR_load_crypto_strings();
	OpenSSL_add_all_ciphers();
	if ((aos = ASN1_OCTET_STRING_new()) == NULL)
		errx(2, "cannot create ASN.1 octet string: %s",
		    ERR_error_string(ERR_get_error(), NULL));
	if ((enc = EVP_get_cipherbyname(algo)) == NULL)
		errx(2, "unknown cipher '%s': %s", algo,
		    ERR_error_string(ERR_get_error(), NULL));

	if (key2) {
		if (strlen(key2) < kbuflen)
			kbuflen = strlen(key2);
		else
			fprintf(stderr, "WARNING: truncating from %zu to"
			    " %zu characters!\n", strlen(key2), kbuflen);
		memcpy(kbuf, key2, kbuflen);
		fprintf(stderr, "WARNING: not using random bits as key!\n");
	} else
		arc4random_buf(kbuf, sizeof(kbuf));

	i = ASN1_STRING_set(aos, kbuf, kbuflen);
	bzero(kbuf, sizeof (kbuf));
	if (!i)
		errx(2, "cannot set ASN.1 octet string: %s",
		    ERR_error_string(ERR_get_error(), NULL));

	i = PEM_write_ASN1_OCTET_STRING(fp, aos, enc, NULL, 0, NULL, NULL);
	ASN1_STRING_free(aos);
	if (!i)
		errx(2, "cannot encode svnd keyfile: %s",
		    ERR_error_string(ERR_get_error(), NULL));
	return (0);
}

static void
extract_key(FILE *fp, char **key, int *klen)
{
	ASN1_OCTET_STRING *aos;
	unsigned char *p;

	if (fp == NULL || key == NULL || klen == NULL)
		usage();

	ERR_load_crypto_strings();
	OpenSSL_add_all_ciphers();
	if ((aos = PEM_read_ASN1_OCTET_STRING(fp, NULL, NULL, NULL)) == NULL) {
		ERR_print_errors_fp(stderr);
		errx(2, "cannot decode svnd keyfile");
	}

	*klen = ASN1_STRING_length(aos);
	if (*klen < 1) {
		ASN1_STRING_free(aos);
		ERR_print_errors_fp(stderr);
		errx(2, "svnd keyfile too small: %d", *klen);
	} else if (*klen > BLF_MAX_BYTES)
		*klen = BLF_MAX_BYTES;

	*key = malloc(*klen);
	if (*key == NULL)
		err(1, "malloc of %d bytes", *klen);

	p = ASN1_STRING_data(aos);
	if (p == NULL) {
		ASN1_STRING_free(aos);
		ERR_print_errors_fp(stderr);
		errx(2, "cannot get ASN.1 string");
	}

	memcpy(*key, p, *klen);
	ASN1_STRING_free(aos);
	EVP_cleanup();
	ERR_free_strings();
}
#endif
