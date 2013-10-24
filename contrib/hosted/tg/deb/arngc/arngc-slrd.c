#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

static const char __rcsid[] = "$MirOS$";

static const char errmsg[] = "arngc-slrd: I/O failed, first and only message\n";

int
main(void)
{
	size_t sz;
	unsigned int slp;
	bool messaged = false;
	uint8_t buf[32];

 mainloop:
	if (((sz = read(STDIN_FILENO, buf, sizeof(buf))) == (size_t)-1) ||
	    (sz && (size_t)write(STDOUT_FILENO, buf, sz) != sz)) {
		if (!messaged) {
			sz = write(STDERR_FILENO, errmsg, sizeof(errmsg) - 1);
			messaged = sz == sizeof(errmsg) - 1;
		}
	}
	slp = 240;
	while ((slp = sleep(slp)))
		/* nothing */;
	goto mainloop;

	/* NOTREACHED */
	return (255);
}
