#include <libckern.h>

void
bzero(void *b, size_t len)
{
	((char *)b)[len] = 0;
}
