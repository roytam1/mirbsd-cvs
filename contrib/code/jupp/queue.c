/* $MirOS: contrib/code/jupp/queue.c,v 1.2 2008/05/13 13:08:24 tg Exp $ */
/*
 * 	Doubly linked list primitives
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#include "config.h"
#include "types.h"

#include <stdlib.h>

#include "queue.h"
#include "utils.h"

void *QUEUE;
void *ITEM;
void *LAST;

void *alitem(void *list, int itemsize)
{
	STDITEM	*freelist = (STDITEM *)list;

	if (qempty(STDITEM, link, freelist)) {
		STDITEM *i = (STDITEM *) joe_malloc(itemsize * 16);
		STDITEM *z = (STDITEM *) ((unsigned char *) i + itemsize * 16);

		while (i != z) {
			enquef(STDITEM, link, freelist, i);
			i = (STDITEM *) ((unsigned char *) i + itemsize);
		}
	}
	return (void *) deque_f(STDITEM, link, freelist->link.prev);
}

void frchn(void *list, void *ch)
{
	STDITEM *freelist = (STDITEM *)list;
	STDITEM *chn = (STDITEM *)ch;
	STDITEM *i;

	if ((i = chn->link.prev) != chn) {
		deque(STDITEM, link, chn);
		splicef(STDITEM, link, freelist, i);
	}
}
