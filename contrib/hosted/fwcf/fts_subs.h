/* $MirOS: contrib/hosted/fwcf/fts_subs.h,v 1.5 2006/09/16 07:35:37 tg Exp $ */

/*
 * This file is part of the FreeWRT project. FreeWRT is copyrighted
 * material, please see the LICENCE file in the top-level directory
 * or at http://www.freewrt.org/licence for details.
 */

#ifndef FTS_SUBS_H
#define FTS_SUBS_H

struct FTSF_ENTRY {
	char pathname[MAXPATHLEN];
	struct stat *statp;
	enum {
		FTSF_DIR,
		FTSF_FILE,
		FTSF_SYMLINK,
		FTSF_OTHER
	} etype;
};
#ifndef PACK_H
typedef struct FTSF_ENTRY ftsf_entry;
#endif

#ifndef FTSF_INTERNALS
extern const char ftsf_prefix[];
#endif

__BEGIN_DECLS
void ftsf_start(const char *);
/* returns -1 on error, 0 on empty, 1 on okay */
int ftsf_next(ftsf_entry *);
void ftsf_debugent(ftsf_entry *);
__END_DECLS

#endif
