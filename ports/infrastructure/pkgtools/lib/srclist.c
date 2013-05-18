/* $MirOS: ports/infrastructure/pkgtools/lib/srclist.c,v 1.1.2.1 2010/03/04 18:03:39 bsiegert Exp $ */

/*-
 * Copyright (c) 2010
 *	Benny Siegert <bsiegert@gmx.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 *-
 * Configuration file routines
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include "lib.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/srclist.c,v 1.1.2.1 2010/03/04 18:03:39 bsiegert Exp $");

/* A word on memory management:
 * The strings to be entered into "source" above are just the pointers
 * in the srclist -- which is safe as long as the latter is not destroyed
 * before the results are consumed, e.g. by calling cfg_read_config() in
 * the meantime. Don't do that.
 */

/* state for our matchfn */
typedef struct {
	const char *current_src;
	struct matchlist *matches;
} srciter_state;

/* Determine whether a package name has already been seen. Sources are
 * traversed from highest to lowest priority, so when the same pkgname
 * is seen again, it should be ignored, so that the highest-priority
 * entry prevails.
 * Additional checks could be implemented here: for example, you could
 * also remove packages that have a lower version than others already
 * seen. Might also act on "matches" in the future.
 */
static bool
found_in_matches(const char *pkgname, struct matchlist *matches)
{
	struct match *mp;

	TAILQ_FOREACH(mp, matches, entries) {
		if (!strcmp(pkgname, mp->pkgname))
			return true;
	}
	
	return false;
}

/* Our matchfn, which has to conform to the standard prototype. "data" is
 * really a srciter_state*. Evil hack?
 */
static int
srciter_matchfn(const char *found, char *data, int len)
{
	srciter_state *state;
	struct match *mp;

	assert(len == sizeof (srciter_state));
	state = (srciter_state *)data;

	if (!found_in_matches(found, state->matches)) {
		if (!(mp = malloc(sizeof (struct match))))
			err(1, NULL);
		memset(mp, 0, sizeof (struct match));
		
		mp->source = state->current_src;
		if (!(mp->pkgname = strdup(found)))
			err(1, NULL);
		TAILQ_INSERT_TAIL(state->matches, mp, entries);
	}

	return 0;
}

/* Find all the packages in the list of sources matching the given pattern.
 * Calls findmatchingname and findmatchingname_file internally.
 * The returned list must be destroyed after use.
 */
struct matchlist *
findmatchingname_srcs(const struct cfg_sourcelist *sources, const char *pattern)
{
	srciter_state state;
	struct cfg_source *sp;

	state.current_src = NULL;
	if (!(state.matches = malloc(sizeof (struct matchlist))))
		err(1, NULL);
	TAILQ_INIT(state.matches);

	LIST_FOREACH(sp, sources, entries) {
		if (sp->remote)
			findmatchingname_file(src_index_name(sp->source),
					pattern, srciter_matchfn,
					(char *)&state, sizeof (srciter_state));
		else
			findmatchingname(sp->source, pattern, srciter_matchfn,
					(char *)&state, sizeof (srciter_state));
	}

	return state.matches;
}

/* Free all entries of a matchlist, but not the list itself.
 */
void
matchlist_destroy(struct matchlist *matches)
{
	struct match *mp;

	while ((mp = TAILQ_FIRST(matches))) {
		free(mp->pkgname);
		TAILQ_REMOVE(matches, mp, entries);
		free(mp);
	}
}
