/* $MirOS: contrib/code/polymers/calc2/calc.c,v 1.1 2005/03/20 18:20:16 bsiegert Exp $
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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* degree of polymerization (number of steps) */
#define DP 100

struct point {
	double x, y, z;
};

int
calc(FILE *outfile)
{
	struct point points[DP + 1];
	int i, j;
	double theta, phi;
	bool ok;

	memset(&points, 0, sizeof(points));
	fprintf(outfile, "#x\ty\tz\n0\t0\t0\n");

	for (i = 1; i <= DP; i++) {
		do {
			ok = true;
			theta = (double)arc4random() / RAND_MAX * M_PI;
			phi = (double)arc4random() / RAND_MAX * M_PI;
			points[i].x = points[i - 1].x + sin(theta) * cos(phi);
			points[i].y = points[i - 1].y + sin(theta) * sin(phi);
			points[i].z = points[i - 1].z + cos(theta);

			for (j = 0; j < i - 1; j++) {
				if (hypot(hypot(points[i].x - points[j].x,
				    points[i].y - points[j].y),
				    points[i].z - points[j].z) < 1.0)
					ok = false;
			}
		} while (!ok);

		fprintf(outfile, "%.4f\t%.4f\t%.4f\n", points[i].x,
				points[i].y, points[i].z);
	}
	return hypot(hypot(points[i - 1].x, points[i - 1].y), points[i - 1].z) + 0.5;
}
