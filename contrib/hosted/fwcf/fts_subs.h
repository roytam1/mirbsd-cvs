/* $MirOS$ */

/*
 * This file is part of the FreeWRT project. FreeWRT is copyrighted
 * material, please see the LICENCE file in the top-level directory
 * or at http://www.freewrt.org/license for details.
 */

#ifndef FTS_SUBS_H
#define FTS_SUBS_H

typedef struct {
	char pathname[MAXPATHLEN];
	struct stat *statp;
	enum {
		FTSF_DIR,
		FTSF_FILE,
		FTSF_SYMLINK,
		FTSF_OTHER
	} etype;
} ftsf_entry;

void ftsf_start(const char *);
/* returns -1 on error, 0 on empty, 1 on okay */
int ftsf_next(ftsf_entry *);
void ftsf_debugent(ftsf_entry *);

#endif
