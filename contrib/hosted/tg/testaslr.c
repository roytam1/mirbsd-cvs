#include <stdio.h>
#include <stdlib.h>

extern void *ptrstackarg(int);
extern void *ptrstackvar(void);

int
main(void)
{
	void *m12, *m257, *m8M, *sarg, *sloc;

	m12 = malloc(12);
	m257 = malloc(257);
	m8M = malloc(8 * 1048576);
	sarg = ptrstackarg(1);
	sloc = ptrstackvar();

	printf("%p %p %p %p %p\n", m12, m257, m8M, sarg, sloc);
	return (0);
}

void *
ptrstackarg(int i)
{
	return (&i);
}

void *
ptrstackvar(void)
{
	int i;

	return (&i);
}
