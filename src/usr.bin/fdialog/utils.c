/* $MirOS$ */
/* $ekkoBSD: utils.c,v 1.3 2004/02/19 00:38:37 dave Exp $ */

/*-
 * Copyright (c) 2003 David Steinberg <dave@redterror.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF MIND, USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/queue.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "fdialog.h"

__RCSID("$MirOS$");

struct fdl_str *
itemq_to_str (struct itemq_head * headp) {
	int size = 0;
	struct fdl_item * itemp;
	struct fdl_str * str;

	/* get the size first */
	TAILQ_FOREACH(itemp, headp, items)
		size++;

	str = str_new(size);

	TAILQ_FOREACH(itemp, headp, items) {
		str_append(str, menuify_item(itemp));
	}

	return str;
}

/* basic new and delete functions */
struct fdl_str *
str_new (unsigned int size) {
	struct fdl_str * str;

	if ((str = malloc(sizeof(struct fdl_str))) == NULL) {
		perror("malloc");
		fdl_exit(1);
	}

	str->free = str->size = size;

	if (size > 0) {
		if ((str->str = malloc(sizeof(char *) * size)) == NULL) {
			perror("malloc");
			fdl_exit(1);
		}
	}

	return str;
}

/* free all of our strings and then ourself */
void
str_destroy (struct fdl_str * str) {
	int i=0;
	for (i=0; i < str->size ; i++)
		free(str->str[i]);
	free(str);
}

/* append a string in the subsequent free slot */
int
str_append (struct fdl_str * str, const char * new) {
	int free_slot;

	if (new == NULL)
		return 0;
	if (str == NULL)
		abort();

	if (str->free == 0)
		return FDL_NOROOM;

	free_slot = str->size - str->free;
	str->str[free_slot] = strdup(new);
	str->free--;
	return 0;
}
