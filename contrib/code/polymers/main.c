/* $MirOS$
 *-
 * Copyright (c) 2005
 *	Benny Siegert <bsiegert@gmx.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publically perform, modi-
 * fy, merge, distribute, sell, give away or sublicence, provided the
 * above copyright notices, these terms and the disclaimer are retai-
 * ned in all redistributions, or reproduced in accompanying documen-
 * tation or other materials provided with binary redistributions.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of covered work, even if advised of the possibility of such damage.
 *-
 * This program calculates a conformation of a hypothetical polymer chain.
 * It creates an output file with the full conformation data and outputs
 * the length of the end-to-end vector on stdout.
 *
 * vim:se cin sw=8:
 */

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	FILE *outfile;
	int result;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return 1;
	}

	outfile = fopen(argv[1], "w");
	if (!outfile) {
		perror("Cannot open output file");
		return 2;
	}

	result = calc(outfile);
	printf("%d\n", result);
	
	if (fclose(outfile) == EOF) {
		perror("Cannot close output file");
		return 4;
	}
	return 0;
}
