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

@implementation list

- (id)init
{
	self = [super init];
	if (self) {
		head = nil;
		tail = nil;
	}
	return self;
}

- (void)release
{
	listElement *tmp;
	listEnumerator *en;
	if (!head)
		return;
	
	en = [[listEnumerator alloc] initWithList: self];
	while ((tmp = [en nextObject]))
		[tmp release];
	[en release];
}

- (id)head
{
	return head;
}

- (id)tail
{
	return tail;
}

- (id)append: (listElement *)anItem
{
	if (!anItem)
		return nil;
	if (!tail) {
		tail = anItem;
		if (!head)
			head = tail;
	} else 
		tail = [tail append: anItem];
	return tail;
}

- (id)insert: (listElement*)anItem
{
	if (!anItem)
		return nil;
	if (!head) {
		head = anItem;
		if (!tail)
			tail = head;
	} else
		head = [head insert: anItem];
	return head;
}

@end
