/* $MirOS$
 *-
 * Copyright (c) 2005
 *	Benny Siegert <bsiegert@gmx.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

#include "objclib.h"

/* A generic list element class. 
 * This is meant to be used in conjunction with the list class. Note: This is
 * an abstract base class. To do anything useful, you have to derive your own
 * element class.
 */

@implementation listElement

- (id)init
{
	self = [super init];
	if (self) {
		prev = nil;
		next = nil;
	}
	return self;
}

- (id)append: (listElement*)anItem
{
	listElement* tmp = next;
	
	if (anItem) {
		next = anItem;
		anItem->next = tmp;
		anItem->prev = self;
		if(tmp)
			tmp->prev = anItem;
	}
	return anItem;
}

- (id)insert: (listElement*)anItem
{
	listElement* tmp = prev;
	
	if (anItem) {
		prev = anItem;
		anItem->next = self;
		anItem->prev = tmp;
		if (tmp)
			tmp->next = anItem;
	}
	return anItem;
}

- (id)prev
{
	return prev;
}

- (id)next
{
	return next;
}

- (id)setPrev: (listElement *)anItem
{
	id old = prev;
	prev = anItem;
	return old;
}

- (id)setNext: (listElement *)anItem
{
	id old = next;
	next = anItem;
	return old;
}

@end
