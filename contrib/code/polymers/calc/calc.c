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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* degree of polymerization (number of steps) */
#define DP 100

int
calc(FILE *outfile)
{
	double x = 0;
	double y = 0;
	int i;
	double angle;

	fprintf(outfile, "#x\ty\n");

	for (i = 0; i <= DP; i++) {
		fprintf(outfile, "%.4f\t%.4f\n", x, y);
		angle = (double)arc4random() / (1 << 31) * M_PI;
		x += sin(angle);
		y += cos(angle);
	}
	return pow(x, 2) + pow(y, 2);
}
