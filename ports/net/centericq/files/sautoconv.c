#define _ALL_SOURCE
#include <wchar.h>

__RCSID("$MirOS$");

char *sautoconv_c(const char *);

char *
sautoconv_c(const char *ccp)
{
	char *rv;
#ifdef mbsnrtowcsvis
	wchar_t *wcs;
	const char *src = ccp;
	size_t n, len = strlen(src) + 1;

	n = mbsnrtowcsvis(NULL, &src, len, 0, NULL);
	if ((wcs = calloc(n + 1, sizeof (wchar_t))) == NULL)
		goto fail;
	src = ccp;
	mbsnrtowcsvis(wcs, &src, len, n + 1, NULL);
	n = wcstombs(NULL, wcs, 0);
	if ((rv = malloc(n + 1)) == NULL) {
		free(wcs);
		goto fail;
	}
	wcstombs(rv, wcs, n + 1);
	free(wcs);
	return (rv);
 fail:
#endif
	return (strdup(ccp));
}
