/* $MirOS: src/usr.bin/make/fgetln.c,v 1.1 2005/11/24 13:26:56 tg Exp $ */

/*-
 * Copyright (c) 2005 Thorsten Glaser.
 * Copyright (c) 2001 Marc Espie.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *	notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE OPENBSD PROJECT AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OPENBSD
 * PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__RCSID("$MirOS: src/usr.bin/make/fgetln.c,v 1.1 2005/11/24 13:26:56 tg Exp $");

char *fgetln(FILE *, size_t *);

char *
fgetln(FILE *stream, size_t *len)
{
	static char *buffer = NULL;
	static size_t buflen = 0;

	if (buflen == 0) {
		buflen = 512;
		if ((buffer = malloc(buflen+1)) == NULL)
			goto enomem;
	}
	if (fgets(buffer, buflen+1, stream) == NULL)
		return (NULL);
	*len = strlen(buffer);
	while (*len == buflen && buffer[*len-1] != '\n') {
		if ((buffer = realloc(buffer, 2*buflen + 1)) == NULL)
			goto enomem;
		if (fgets(buffer + buflen, buflen + 1, stream) == NULL)
			return (NULL);
		*len += strlen(buffer + buflen);
		buflen *= 2;
	}
	return (buffer);

enomem:
	fputs("fatal: out of memory\n", stderr);
	exit(2);
}
