#include <sys/cdefs.h>
#include "open.h"
#include "byte.h"
#include "cdb.h"
#include "ip6.h"

__RCSID("$MirOS$");

char clientloc[2];

static int
try_find_client_loc(struct cdb *cp, const char key[], int len)
{
	int r;

	do {
		r = cdb_find(cp, key, len);
	} while (!r && --len >= 3);

	if (r == -1)
		/* read error */
		return (-1);
	if (r && (cdb_datalen(cp) == 2)) {
		if (cdb_read(cp, clientloc, 2, cdb_datapos(cp)) == -1)
			/* read error */
			return (-1);
		/* found */
		return (0);
	}
	/* not found */
	return (1);
}

int
find_client_loc(const char ip[16], struct cdb *cp)
{
	char key[3 + 32];

	byte_zero(clientloc, 2);
	key[0] = 0;
	key[1] = '%';
	if (byte_equal(ip, 12, V4mappedprefix)) {
		key[2] = 'f';
		byte_copy(key + 3, 4, ip + 12);
		switch (try_find_client_loc(cp, key, 3 + 4)) {
		case -1:
			/* read error */
			return (-1);
		case 0:
			/* found */
			return (0);
		}
		/* retry as v4-mapped */
	}
	key[2] = 's';
	ip6_fmt_flat(key + 3, ip);
	switch (try_find_client_loc(cp, key, 3 + 32)) {
	case -1:
		/* read error */
		return (-1);
	default:
		/* no match */
		byte_zero(clientloc, 2);
		/* FALLTHROUGH */
	case 0:
		/* found */
		return (0);
	}
}
