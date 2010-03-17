#include <err.h>
#include <unistd.h>
#include <wchar.h>

__RCSID("$MirOS$");

int
main(void)
{
	size_t n;
	char ibuf[4096];
	wchar_t wc, *obuf;

	n = read(0, ibuf, 4095);
	printf("read %zd\n", n);
	if (n > 4095)
		return (1);
	ibuf[n] = 0;

	if ((obuf = ambstowcs(ibuf)) == NULL)
		err(1, "ambstowcs");

	n = 0;
	while (obuf[n]) {
		if (!(n & 15))
			printf("%04zX  ", n);
		if ((wc = obuf[n++]), iswoctet(wc))
			printf("0x%02X ", wc & 0xFF);
		else
			printf("%04X ", wc);
		if (!(n & 15))
			putchar('\n');
	}
	if (n & 15)
		putchar('\n');
	printf("%04zX  EOF\n", n);

	return (0);
}
