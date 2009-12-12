/* $MirOS$ */

#import <objc/Object.h>
#import <stdio.h>

@interface Foo: Object
- (void)test;
@end

@implementation Foo
- (void)test
{
	puts("Hello, World!");
}
@end

int
main(void)
{
	Foo *f = [[Foo alloc] init];
	[f test];

	return (0);
}
