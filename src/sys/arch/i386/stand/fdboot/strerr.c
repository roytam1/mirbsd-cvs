#include <sys/types.h>
#include <lib/libsa/stand.h>

char *
strerror(int err)
{
	static char ebuf[10];

	snprintf(ebuf, sizeof (ebuf), "code %X", err);
	return (ebuf);
}
