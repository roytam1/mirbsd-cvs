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

#ifndef OBJCLIB_H_INCLUDED
#define OBJCLIB_H_INCLUDED

#import <Foundation/NSObject.h>

@interface listElement : NSObject
{
	listElement *next, *prev;
}

- (id)init;

- (id)append: (listElement*)anItem;
- (id)insert: (listElement*)anItem;

- (id)prev;
- (id)next;

- (id)setPrev: (listElement *)anItem;
- (id)setNext: (listElement *)anItem;

@end

@interface list : NSObject
{
	listElement *head, *tail;
}

- (id)init;
- (void)release;

- (id)head;
- (id)tail;
- (id)append: (listElement *)anItem;
- (id)insert: (listElement*)anItem;

@end

@interface enumerator : NSObject
{
	listElement *obj;
}

- (id)initWithList: (list *)aList;
- (id)nextObject;

@end

@interface listEnumerator : enumerator
{
}

- (id)initWithList: (list *)aList;
- (id)nextObject;

@end

@interface listReverseEnumerator : enumerator
{
}

- (id)initWithList: (list *)aList;
- (id)nextObject;

@end

@interface plistElement: listElement
{
	char *name;
}

- (id)init;
- (id)initWithName: (const char *)aName;
- (char *)toString;

@end

@interface plistFile: plistElement
{
}

- (char *)toString;

@end

@interface plistDir: plistElement
{
}

- (char *)toString;

@end

@interface plistCwd: plistElement
{
}

- (char *)toString;

@end

@interface plistMan: plistFile
{
}

- (char *)toString;

@end

#endif /* defined(OBJCLIB_H_INCLUDED) */
