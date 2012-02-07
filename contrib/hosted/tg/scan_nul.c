#if 0
.if "0" == "1"
#endif

/*-
 * Copyright © 2012
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 */

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <err.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

extern const char *__progname;

int
main(int argc, char *argv[])
{
	int fd;
	char *cp;
	struct stat sb;
	char rv = 0, sep = '\n';

	if (argc > 1 && !strcmp(argv[1], "-0")) {
		sep = '\0';
		--argc;
		++argv;
	}

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file [...]\n", __progname);
		return (2);
	}
	--argc;

	while (argc--) {
		++argv;
		if ((fd = open(*argv, O_RDONLY)) == -1)
			err(3, "open: %s", *argv);
		if (fstat(fd, &sb))
			err(3, "stat: %s", *argv);
		if (sb.st_size >= (off_t)SSIZE_MAX)
			errx(4, "too big (%llu): %s",
			    (unsigned long long)sb.st_size, *argv);
		if ((cp = mmap(NULL, (size_t)sb.st_size, PROT_READ,
		    MAP_FILE | MAP_SHARED, fd, (off_t)0)) == MAP_FAILED)
			err(3, "mmap: %s", *argv);
		if (madvise(cp, (size_t)sb.st_size, MADV_SEQUENTIAL))
			err(3, "madvise: %zu, %s", (size_t)sb.st_size, *argv);
		if (memchr(cp, '\0', (size_t)sb.st_size) != NULL) {
			rv = 1;
			printf("%s%c", *argv, sep);
		}
		if (munmap(cp, (size_t)sb.st_size))
			err(3, "munmap: %s", *argv);
		if (close(fd))
			err(3, "close: %s", *argv);
	}

	return (rv);
}

#if 0
.endif

PROG=		scan_nul
NOMAN=		Yes

.include <bsd.prog.mk>
#endif
