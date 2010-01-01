#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include "lib.h"

bool Verbose = true;

void
cleanup(int signo)
{
	/* do nothing */
}

int
main(int argc, char **argv)
{
	if (!cfg_read_config((argc > 1 ? argv[1] : NULL)))
		warnx("Reading config file failed");
	cfg_dump_vars();
	/*printf("\n");*/
	cfg_dump_sources();
	return 0;
}
