#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

static const char __rcsid[] = "$MirOS: contrib/hosted/tg/deb/arngc/arngc-slrd.c,v 1.2 2014/07/08 13:00:19 tg Exp $";

static const char errmsg[] = "arngc-slrd: I/O failed, first and only message\n";

int
main(void)
{
	size_t sz;
	unsigned int slp;
	bool messaged = false;
	uint8_t buf[16];

 mainloop:
	if (((sz = read(STDIN_FILENO, buf, sizeof(buf))) == (size_t)-1) ||
	    (sz && (size_t)write(STDOUT_FILENO, buf, sz) != sz)) {
		if (!messaged) {
			sz = write(STDERR_FILENO, errmsg, sizeof(errmsg) - 1);
			messaged = sz == sizeof(errmsg) - 1;
		}
	}
	/* three keepalives, then our request 10s before the fourth one */
	slp = 150;
	while ((slp = sleep(slp)))
		;	/* nothing */
	goto mainloop;

	/* NOTREACHED */
	return (255);
}
