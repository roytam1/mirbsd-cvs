/* $MirOS$ */
/* $ekkoBSD: menu_item.c,v 1.4 2004/02/27 22:55:51 dave Exp $ */

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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fdialog.h"

__RCSID("$MirOS$");

struct fdl_item *
new_item(char * name, char * description, char * value) {
	struct fdl_item * item;

	DEBUG("new_item: name: %s val: %s descr: %s", name, value, description);

	item = malloc(sizeof(struct fdl_item));
	if (item == NULL) {
		perror("malloc");
		exit(1);
	}

	item->name = name;
	item->description = description;
	item->value = value;

	return item;
}

void
destroy_item (struct fdl_item * item) {
	free(item->name);
	free(item->description);
	free(item->value);
	free(item);
}

/* caller must free the returned string when done with it */
char *
toString_item (struct fdl_item * item) {
	char * str;
	asprintf(&str, "item name: %s description: %s value: %s", 
		item->name, item->description, item->value);
	return str;
}

/* caller must free the returned string when done with it */
char *
menuify_item (struct fdl_item * item) {
	char * str;
	if (item->description != NULL)
		asprintf(&str, "%s %s", item->name, item->description);
	else 
		asprintf(&str, "%s", item->name);
	return str;
}

char *
format_selected_item (struct fdl_item * item) {
	char * str;
	if (item->value == NULL)
		str = strdup(item->name);
	else
		str = strdup(item->value);

	return str;
}
