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

/* This program is called by the regression test test-cfgfile.t.
 * The first argument is the path to the configuration file, the second one
 * is either a variable name, the value of which is printed, or one of the
 * special values "Sources" or "Variables".
 */

int
main(int argc, char **argv)
{
	if (!cfg_read_config((argc > 1 ? argv[1] : NULL)))
		warnx("Reading config file failed");
	if (argc > 2) {
		if (!strcmp(argv[2], "Sources"))
			cfg_dump_sources();
		else if (!strcmp(argv[2], "Variables"))
			cfg_dump_vars();
		else
			cfg_dump_var(argv[2]);
	} else {
		cfg_dump_vars();
		cfg_dump_sources();
	}
	return 0;
}
