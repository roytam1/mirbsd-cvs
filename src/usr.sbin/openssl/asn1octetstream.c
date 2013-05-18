/* $MirOS: src/share/misc/licence.template,v 1.8 2006/06/16 23:03:39 tg Rel $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "apps.h"
#include <openssl/asn1.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

__RCSID("$MirOS$");

#undef PROG
#define PROG	asn1octetstream_main

int MAIN(int, char **);

int
MAIN(int argc, char **argv)
{
	ASN1_OCTET_STRING *aos = NULL;
	BIO *in = NULL, *out = NULL;
	char *infile = NULL, *outfile = NULL;
	char *passargin = NULL, *passargout = NULL;
	char *passin = NULL, *passout = NULL;
	char *prog;
	int inplain = 0, outplain = 0;
	const EVP_CIPHER *enc = NULL;
	int rv = 1;

	apps_startup();

	if (bio_err == NULL)
		if ((bio_err=BIO_new(BIO_s_file())) != NULL)
			BIO_set_fp(bio_err, stderr, BIO_NOCLOSE | BIO_FP_TEXT);

	ERR_load_crypto_strings();
	OpenSSL_add_all_ciphers();

	if (!load_config(bio_err, NULL))
		goto end;

	prog = argv[0];
	--argc;
	++argv;
	while (argc > 0) {
		if (!strcmp(*argv, "-in")) {
			if (--argc < 1)
				goto bad;
			infile = *(++argv);
		} else if (!strcmp(*argv, "-out")) {
			if (--argc < 1)
				goto bad;
			outfile = *(++argv);
		} else if (!strcmp(*argv, "-passin")) {
			if (--argc < 1)
				goto bad;
			passargin = *(++argv);
		} else if (!strcmp(*argv, "-passout")) {
			if (--argc < 1)
				goto bad;
			passargout = *(++argv);
		} else if (!strcmp(*argv, "-e")) {
			inplain = 1;
		} else if (!strcmp(*argv, "-d")) {
			outplain = 1;
		} else if ((enc = EVP_get_cipherbyname((*argv) + 1)) == NULL) {
			BIO_printf(bio_err, "unknown option %s\n", *argv);
 bad:
			BIO_printf(bio_err,"%s [options] <infile >outfile\n", prog);
			BIO_printf(bio_err,"where options are\n");
			BIO_printf(bio_err," -in arg         input file\n");
			BIO_printf(bio_err," -passin arg     input file pass phrase source\n");
			BIO_printf(bio_err," -out arg        output file\n");
			BIO_printf(bio_err," -passout arg    output file pass phrase source\n");
			BIO_printf(bio_err," -e              encrypt plain-text input to PEM\n");
			BIO_printf(bio_err," -d              decrypt PEM input to plain text\n");
			BIO_printf(bio_err," -<algo>         encrypt PEM output with <algo>\n");
			goto end;
		}
		--argc;
		++argv;
	}

	if (!app_passwd(bio_err, passargin, passargout, &passin, &passout)) {
		BIO_printf(bio_err, "Error getting passwords\n");
		goto end;
	}

	in = BIO_new(BIO_s_file());

	if (infile == NULL) {
		setvbuf(stdin, NULL, _IONBF, 0);
		BIO_set_fp(in, stdin, BIO_NOCLOSE);
	} else if (BIO_read_filename(in, infile) <= 0) {
		BIO_printf(bio_err, "Error opening input %s\n", infile);
		ERR_print_errors(bio_err);
		goto end;
	}

	if (inplain) {
		char *buf;
		int buflen = 0, bufsiz;

		if ((buf = malloc(1048576)) == NULL) {
			BIO_printf(bio_err, "cannot malloc\n");
			goto end;
		}
		bufsiz = 1048576;

		while (!BIO_eof(in)) {
			int i;

			if ((buflen - bufsiz) < 32768) {
				char *t;

				if ((i = bufsiz + 1048576) < 0) {
					BIO_printf(bio_err, "file too large\n");
					free(buf);
					goto end;
				}

				if ((t = realloc(buf, i)) == NULL) {
					free(buf);
					BIO_printf(bio_err, "cannot realloc\n");
					goto end;
				}
				buf = t;
				bufsiz = i;
			}

			if ((i = bufsiz - buflen) > 32768)
				i = 32768;

			i = BIO_read(in, buf + buflen, i);
			if (i <= 0)
				break;
			buflen += i;
		}

		if ((aos = ASN1_OCTET_STRING_new()) == NULL) {
			BIO_printf(bio_err, "cannot create ASN.1 octet string\n");
			ERR_print_errors(bio_err);
			free(buf);
			goto end;
		}

		if (!ASN1_STRING_set(aos, buf, buflen)) {
			BIO_printf(bio_err, "Error creating ASN.1 octet string\n");
			ERR_print_errors(bio_err);
			free(buf);
			goto end;
		}

		free(buf);
	} else if ((aos = PEM_read_bio_ASN1_OCTET_STRING(in, NULL, NULL,
	    (passargin == NULL) ? NULL : passin)) == NULL) {
		BIO_printf(bio_err, "Error reading PEM input\n");
		ERR_print_errors(bio_err);
		goto end;
	}

	out = BIO_new(BIO_s_file());

	if (outfile == NULL)
		BIO_set_fp(out, stdout, BIO_NOCLOSE);
	else if (BIO_write_filename(out, outfile) <= 0) {
		BIO_printf(bio_err, "Error opening output %s\n", outfile);
		ERR_print_errors(bio_err);
		goto end;
	}

	if (outplain) {
		char *buf;
		int len;

		if ((buf = ASN1_STRING_data(aos)) == NULL) {
			BIO_printf(bio_err, "Error decoding ASN.1 octet string\n");
			ERR_print_errors(bio_err);
			goto end;
		}
		if ((len = ASN1_STRING_length(aos)) < 0) {
			BIO_printf(bio_err, "Error sizing ASN.1 octet string\n");
			ERR_print_errors(bio_err);
			goto end;
		}
		if (BIO_write(out, buf, len) != len) {
			BIO_printf(bio_err, "Error writing plain text output\n");
			ERR_print_errors(bio_err);
			goto end;
		}
	} else if (!PEM_write_bio_ASN1_OCTET_STRING(out, aos, enc, NULL, 0,
	    NULL, (passargout == NULL) ? NULL : passout)) {
		BIO_printf(bio_err, "Error writing PEM output\n");
		ERR_print_errors(bio_err);
		goto end;
	}

	rv = 0;

 end:
	if (in != NULL)
		BIO_free_all(in);
	if (out != NULL)
		BIO_free_all(out);
	if (passin != NULL)
		OPENSSL_free(passin);
	if (passout != NULL)
		OPENSSL_free(passout);
	if (aos != NULL)
		ASN1_STRING_free(aos);
	apps_shutdown();
	OPENSSL_EXIT(rv);
}
