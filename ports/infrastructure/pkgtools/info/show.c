/* $MirOS: ports/infrastructure/pkgtools/info/show.c,v 1.7 2009/10/20 19:32:49 bsiegert Exp $ */
/* $OpenBSD: show.c,v 1.13 2003/08/21 20:24:56 espie Exp $ */

/*
 * FreeBSD install - a package for the installation and maintainance
 * of non-core utilities.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * Jordan K. Hubbard
 * 23 Aug 1993
 *
 * Various display routines for the info module.
 */

#include <err.h>

#include "lib.h"
#include "info.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/info/show.c,v 1.7 2009/10/20 19:32:49 bsiegert Exp $");

/* structure to define entries for the "show table" */
typedef struct show_t {
	pl_ent_t	sh_type;	/* type of entry */
	const char	*sh_quiet;	/* message when quiet */
	const char	*sh_verbose;	/* message when verbose */
} show_t;

/* the entries in this table must be ordered the same as pl_ent_t constants */
static show_t	showv[] = {
	{	PLIST_FILE,	"%s",		"File: %s" },
	{	PLIST_CWD,	"@cwd %s",	"\tCWD to: %s" },
	{	PLIST_CMD,	"@exec %s",	"\tEXEC '%s'" },
	{	PLIST_CHMOD,	"@chmod %s",	"\tCHMOD to %s" },
	{	PLIST_CHOWN,	"@chown %s",	"\tCHOWN to %s" },
	{	PLIST_CHGRP,	"@chgrp %s",	"\tCHGRP to %s" },
	{	PLIST_COMMENT,	"@comment %s",	"\tComment: %s" },
	{	PLIST_ARCH,	"@arch %s",	"\tComment: @arch %s" },
	{	PLIST_IGNORE,	NULL,	NULL },
	{	PLIST_NAME,	"@name %s",	"\tPackage name: %s" },
	{	PLIST_UNEXEC,	"@unexec %s",	"\tUNEXEC '%s'" },
	{	PLIST_SRC,	"@srcdir: %s",	"\tSRCDIR to: %s" },
	{	PLIST_DISPLAY,	"@display %s",	"\tInstall message file: %s" },
	{	PLIST_PKGDEP,	"@pkgdep %s",	"\tPackage depends on: %s" },
	{	PLIST_MTREE,	"@mtree %s",	"\tPackage mtree file: %s" },
	{	PLIST_DIR_RM,	"@dirrm %s",	"\tDeinstall directory remove: %s" },
	{	PLIST_OPTION,	"@option %s",	"\tPackage has option: %s" },
	{	PLIST_PKGCFL,	"@pkgcfl %s",	"\tPackage conflicts with: %s" },
	{	PLIST_EXTRA,	"@extra %s",	"\tExtra files: %s" },
	{	PLIST_EXTRAUNEXEC,
				"@extraunexec %s",
						"\tExtra UNEXEC: %s" },
	{	PLIST_NEWDEP,	"@newdep %s",	"\tNew package dependency: %s" },
	{	PLIST_LIBDEP,	"@libdep %s",	"\tLibrary dependency: %s" },
	{	PLIST_SAMPLE,	"@sample %s",	"\tInstall configuration file: %s" },
	{	PLIST_LIB,	"@lib %s",	"\tShared library: %s" },
	{	PLIST_SHELL,	"@shell %s",	"\tShell: %s" },
	{	PLIST_ENDFAKE,	"@endfake",	"\tEnd of fake point" },
	{	PLIST_LDCACHE,	"@ldcache %s",	"\tShared libraries enabled: %s" },
	{	PLIST_EMUL,	"@emul %s",	"\tNeeds binary emulation: %s" },
	{	PLIST_NOLIB,	"@nolib %s",	"\tLibtool library (no expansion): %s" },
	{	-1,		NULL,		 NULL }
};

void
show_file(const char *title, const char *fname)
{
	FILE *fp;
	char line[1024];
	int n;

	if (!Quiet) {
		printf("%s%s", InfoPrefix, title);
	}
	if ((fp = fopen(fname, "r")) == NULL) {
		printf("ERROR: show_file: Can't open '%s' for reading!\n", fname);
	} else {
		while ((n = fread(line, 1, 1024, fp)) != 0) {
			fwrite(line, 1, n, stdout);
		}
		(void) fclose(fp);
	}
	printf("\n");	/* just in case */
}

void
show_index(const char *title, const char *fname)
{
	FILE *fp;
	char line[MAXINDEXSIZE+2];

	strlcpy(line, "???\n", sizeof(line));

	if (!Quiet) {
		printf("%s%-20s ", InfoPrefix, title);
	}
	if ((fp = fopen(fname, "r")) == NULL) {
		pwarnx("show_file (%s): can't open '%s' for reading", title, fname);
	}
	else {
		if (fgets(line, MAXINDEXSIZE+1, fp)) {
			int  line_length = strlen(line);

			if (line[line_length-1] != '\n') {
				line[line_length] = '\n';
				line[line_length+1] = 0;
			}
		}
		(void) fclose(fp);
	}
        (void) fputs(line, stdout);
}

/* Show a packing list item type.  If type is PLIST_SHOW_ALL, show all */
void
show_plist(const char *title, package_t *plist, pl_ent_t type)
{
    plist_t *p;
    bool ign;
    show_t *showr;

    if (!Quiet) {
	printf("%s%s", InfoPrefix, title);
    }
    for (ign = false, p = plist->head; p ; p = p->next) {
	if (p->type == type || type == PLIST_SHOW_ALL) {
		for (showr = showv; (showr->sh_type != p->type) && (showr->sh_type != -1); showr++);
		switch(p->type) {
		case PLIST_FILE:
			printf(Quiet ? showr->sh_quiet : showr->sh_verbose, p->name);
			if (ign) {
				if (!Quiet) {
					printf(" (ignored)");
				}
				ign = false;
			}
			break;
		case PLIST_CHMOD:
		case PLIST_CHOWN:
		case PLIST_CHGRP:
			printf(Quiet ? showr->sh_quiet : showr->sh_verbose,
				p->name ? p->name : "(clear default)");
			break;
		case PLIST_IGNORE:
			ign = true;
			break;
		case PLIST_CWD:
		case PLIST_CMD:
		case PLIST_SRC:
		case PLIST_UNEXEC:
		case PLIST_COMMENT:
		case PLIST_NAME:
		case PLIST_DISPLAY:
		case PLIST_PKGDEP:
		case PLIST_MTREE:
		case PLIST_DIR_RM:
		case PLIST_OPTION:
		case PLIST_PKGCFL:
		case PLIST_EXTRA:
		case PLIST_EXTRAUNEXEC:
		case PLIST_NEWDEP:
		case PLIST_LIBDEP:
		case PLIST_SAMPLE:
		case PLIST_ARCH:
		case PLIST_LIB:
		case PLIST_SHELL:
		case PLIST_ENDFAKE:
		case PLIST_LDCACHE:
		case PLIST_EMUL:
		case PLIST_NOLIB:
			printf(Quiet ? showr->sh_quiet : showr->sh_verbose, p->name);
			break;
		default:
			pwarnx("unknown command type %d (%s)", p->type, p->name);
		}
		(void) fputc('\n', stdout);
	}
    }
}

/* Show all files in the packing list (except ignored ones) */
void
show_files(const char *title, package_t *plist)
{
	plist_t	*p;
	bool	ign;
	const char *dir = ".";

	if (!Quiet) {
		printf("%s%s", InfoPrefix, title);
	}
	for (ign = false, p = plist->head; p ; p = p->next) {
		switch(p->type) {
		case PLIST_FILE:
		case PLIST_INFO:
		case PLIST_MAN:
		case PLIST_LIB:
			if (!ign) {
				printf("%s/%s\n", dir, p->name);
			}
			ign = false;
			break;
		case PLIST_CWD:
			dir = p->name;
			break;
		case PLIST_IGNORE:
			ign = true;
			break;
		default:
			break;
		}
	}
}
