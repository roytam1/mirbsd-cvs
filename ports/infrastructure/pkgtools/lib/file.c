/* $MirOS: ports/infrastructure/pkgtools/lib/file.c,v 1.8 2006/02/25 15:49:55 bsiegert Exp $ */
/* $OpenBSD: file.c,v 1.26 2003/08/21 20:24:57 espie Exp $	*/

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
 * 18 July 1993
 *
 * Miscellaneous file access utilities.
 */

#include "lib.h"

#include <sys/wait.h>

#include <assert.h>
#include <err.h>
#include <netdb.h>
#include <pwd.h>
#include <time.h>
#include <glob.h>
#include <libgen.h>
#include <unistd.h>

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/file.c,v 1.8 2006/02/25 15:49:55 bsiegert Exp $");

/* Try to find the log dir for an incomplete package specification.
 * Used in pkg_info and pkg_delete. Returns the number of matches,
 * or -1 on error.
 */
int
glob_package(char *log_dir, size_t len, const char *pkg)
{
	const char *tmp;
	glob_t pglob;
	int matches;

	if (!(tmp = getenv(PKG_DBDIR)))
		tmp = DEF_LOG_DIR;

	if (strchr(pkg, '/')) {
		if (strncmp(pkg, tmp, strlen(tmp))) {
			pwarnx("package name contains a / and is not under the '%s' directory!", tmp);
			return -1;
		}
		(void) snprintf(log_dir, len, "%s", pkg);
	} else
		(void) snprintf(log_dir, len, "%s/%s", tmp, pkg);

	if (fexists(log_dir))
		return 1;
	if (trim_end(log_dir) && fexists(log_dir))
		return 1;

	/* if all else fails, do the glob */
	memset(&pglob, 0, sizeof(pglob));
	(void) snprintf(log_dir, len, "%s/%s-[0-9]*", tmp, pkg);
	glob(log_dir, 0, NULL, &pglob);
	matches = pglob.gl_pathc;
	if (matches > 0)
		(void) snprintf(log_dir, len, "%s",
				pglob.gl_pathv[0]);
	else
		*log_dir = '\0';
	if (matches > 1) {
		int i;
		printf("Hint: The following versions of this package are installed:\n");
		for (i = 0; i < matches; i++) 
			printf(" %s\n", basename(pglob.gl_pathv[i]));
	}

	globfree(&pglob);
	return matches;
}

/* Try to remove the extension from a package name */
int
trim_end(char *name)
{
	size_t n, m;
	n = strlen(name);
	m = strlen(".tgz");
	if (n > m && strcmp(name+n-m, ".tgz") == 0) {
		name[n-m] = 0;
		return 1;
	}
	m = strlen(".tar.gz");
	if (n > m && strcmp(name+n-m, ".tar.gz") == 0) {
		name[n-m] = 0;
		return 1;
	}
	m = strlen(".cgz");
	if (n > m && strcmp(name+n-m, ".cgz") == 0) {
		name[n-m] = 0;
		return 1;
	}
	m = strlen(".tar");
	if (n > m && strcmp(name+n-m, ".tar") == 0) {
		name[n-m] = 0;
		return 1;
	}
	return 0;
}


/* This fixes errant package names so they end up in .tgz/.cgz.
   XXX returns static storage, so beware! Consume the result
	before reusing the function.
 */
#define	CHK_NAME(name,len,ext)	((len >= strlen(ext)) && \
				 !strcmp(name + len - strlen(ext), ext))
char *
ensure_tgz(char *name)
{
	static char buffer[FILENAME_MAX];
	size_t len;

	len = strlen(name);
	if ( (strcmp (name, "-") == 0 )
	     || CHK_NAME(name,len,".cgz")
	     || CHK_NAME(name,len,".tgz")
	     || CHK_NAME(name,len,".tar.gz")
	     || CHK_NAME(name,len,".tar"))
		return name;
	  else {
		snprintf(buffer, sizeof(buffer), "%s.cgz", name);
		return buffer;
	}
}

/* This is as ftpGetURL from FreeBSDs ftpio.c, except that it uses
 * OpenBSDs ftp command to do all FTP.
 */
static FILE *
ftpGetURL(char *url, int *retcode)
{
	FILE *ftp;
	pid_t pid_ftp;
	int p[2];

	*retcode=0;

	if (pipe(p) < 0) {
		*retcode = 1;
		return NULL;
	}

	pid_ftp = fork();
	if (pid_ftp < 0) {
		*retcode = 1;
		return NULL;
	}
	if (pid_ftp == 0) {
		/* child */
		dup2(p[1],1);
		close(p[1]);

		fprintf(stderr, ">>> ftp -o - %s\n",url);
		execlp("ftp", "ftp", "-V", "-o", "-", url, NULL);
		exit(1);
	} else {
		/* parent */
		ftp = fdopen(p[0],"r");

		close(p[1]);

		if (ftp == NULL) {
			*retcode = 1;
			return NULL;
		}
	}
	return ftp;
}

/* Quick check to see if a file exists */
bool
fexists(const char *fname)
{
    struct stat dummy;
    if (!lstat(fname, &dummy))
	return true;
    return false;
}

/* Quick check to see if something is a directory */
bool
isdir(const char *fname)
{
    struct stat sb;

    if (lstat(fname, &sb) != -1 && S_ISDIR(sb.st_mode))
	return true;
    else
	return false;
}

/* Check if something is a symbolic link */
bool
islink(const char *fname)
{
    struct stat sb;

    return (lstat(fname, &sb) != -1 && S_ISLNK(sb.st_mode));
}

/* Check if something is a link to a directory */
bool
islinktodir(const char *fname)
{
    struct stat sb;

    if (islink(fname))
        if (stat(fname, &sb) != -1 && S_ISDIR(sb.st_mode))
	    return true; /* link to dir! */
        else
	    return false; /* link to non-dir */
    else
        return false;  /* non-link */
}

/* Check to see if file is a dir, and is empty */
bool
isemptydir(const char *fname)
{
    if (isdir(fname) || islinktodir(fname)) {
	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(fname);
	if (!dirp)
	    return false;	/* no perms, leave it alone */
	while ((dp = readdir(dirp)) != NULL) {
	    if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
		closedir(dirp);
		return false;
	    }
	}
	(void)closedir(dirp);
	return true;
    }
    return false;
}

bool
isfile(const char *fname)
{
    struct stat sb;
    if (stat(fname, &sb) != -1 && S_ISREG(sb.st_mode))
	return true;
    return false;
}

/* Check to see if file is a file and is empty. If nonexistent or not
   a file, say "it's empty", otherwise return true if zero sized. */
bool
isemptyfile(const char *fname)
{
    struct stat sb;
    if (stat(fname, &sb) != -1 && S_ISREG(sb.st_mode)) {
	if (sb.st_size != 0)
	    return false;
    }
    return true;
}

/* Returns true if file is a URL specification */
bool
isURL(const char *fname)
{
    /*
     * Hardcode url types... not perfect, but working.
     */
    if (!fname)
	return false;
    while (isspace(*fname))
	++fname;
    if (!strncmp(fname, "ftp://", 6))
	return true;
    if (!strncmp(fname, "http://", 7))
	return true;
    return false;
}

/* Returns the host part of a URL */
char *
fileURLHost(char *fname, char *where, int max)
{
    char *ret;

    while (isspace(*fname))
	++fname;
    /* Don't ever call this on a bad URL! */
    if ((fname = strchr(fname, ':')) == NULL)
	return NULL;
    fname += 3;
    /* Do we have a place to stick our work? */
    if ((ret = where) != NULL) {
	while (*fname && *fname != '/' && max--)
	    *where++ = *fname++;
	*where = '\0';
	return ret;
    }
    /* If not, they must really want us to stomp the original string */
    ret = fname;
    while (*fname && *fname != '/')
	++fname;
    *fname = '\0';
    return ret;
}

/* Returns the filename part of a URL */
char *
fileURLFilename(char *fname, char *where, int max)
{
    char *ret;

    while (isspace(*fname))
	++fname;
    /* Don't ever call this on a bad URL! */
    if ((fname = strchr(fname, ':')) == NULL)
	return NULL;
    fname += 3;
    /* Do we have a place to stick our work? */
    if ((ret = where) != NULL) {
	while (*fname && *fname != '/')
	    ++fname;
	if (*fname == '/') {
	    while (*fname && max--)
		*where++ = *fname++;
	}
	*where = '\0';
	return ret;
    }
    /* If not, they must really want us to stomp the original string */
    while (*fname && *fname != '/')
	++fname;
    return fname;
}

/*
 * Try and fetch a file by URL, returning the directory name for where
 * it's unpacked, if successful.
 */
char *
fileGetURL(char *base, char *spec)
{
    char host[MAXHOSTNAMELEN], file[FILENAME_MAX];
    char *cp, *rp;
    char fname[FILENAME_MAX];
    char pen[FILENAME_MAX];
    FILE *ftp;
    pid_t tpid;
    int i, status;
    char *hint;

    rp = NULL;
    /* Special tip that sysinstall left for us */
    hint = getenv("PKG_ADD_BASE");
    if (!isURL(spec)) {
	if (!base && !hint)
	    return NULL;
	/* We've been given an existing URL (that's known-good) and now we need
	   to construct a composite one out of that and the basename we were
	   handed as a dependency. */
	if (base) {
	    strlcpy(fname, base, sizeof(fname));
	    /* OpenBSD packages are currently stored in a flat space, so
	       we don't yet need to backup the category and switch to all.
	     */
	    cp = strrchr(fname, '/');
	    if (cp) {
		*(cp + 1) = '\0';
		strlcat(fname, ensure_tgz(spec), sizeof(fname));
	    }
	    else
		return NULL;
	}
	else {
	    /* Otherwise, we've been given an environment variable hinting at the right location from sysinstall */
	    snprintf(fname, sizeof(fname), "%s%s", hint, spec);
	}
    }
    else
	strlcpy(fname, spec, sizeof(fname));
    cp = fileURLHost(fname, host, sizeof(host));
    if (!*cp) {
	pwarnx("URL '%s' has bad host part!", fname);
	return NULL;
    }

    cp = fileURLFilename(fname, file, sizeof(fname));
    if (!*cp) {
	pwarnx("URL '%s' has bad filename part!", fname);
	return NULL;
    }

    if (Verbose)
	printf("Trying to fetch %s.\n", fname);
    ftp = ftpGetURL(fname, &status);
    if (ftp) {
	pen[0] = '\0';
	if ((rp = make_playpen(pen, sizeof(pen), 0)) != NULL) {
            rp=strdup(pen); /* be safe for nested calls */
	    if (Verbose)
		printf("Extracting from FTP connection into %s\n", pen);
	    tpid = fork();
	    if (!tpid) {
		dup2(fileno(ftp), 0);
		i = execlp("tar",
		    "tar", Verbose ? "-xpzvf" : "-xpzf", "-", NULL);
		exit(i);
	    }
	    else {
		int pstat;

		fclose(ftp);
		tpid = waitpid(tpid, &pstat, 0);
		if (Verbose)
		    printf("tar command returns %d status\n", WEXITSTATUS(pstat));
	    }
	}
	else
	    printf("Error: Unable to construct a new playpen for FTP!\n");
	fclose(ftp);
    }
    else
	printf("Error: FTP Unable to get %s: %s\n",
	       fname,
	       status ? "Error while performing FTP" :
	       hstrerror(h_errno));
    return rp;
}

char *
fileFindByPath(char *base, char *fname)
{
	static char tmp[FILENAME_MAX];
	char *cp;

	if (ispkgpattern(fname)) {
		if ((cp=findbestmatchingname(".",fname)) != NULL) {
			strlcpy(tmp, cp, sizeof(tmp));
			free(cp);
			return tmp;
		}
	} else {
		strlcpy(tmp, ensure_tgz(fname), sizeof(tmp));
		if (fexists(tmp) && isfile(tmp)) {
			return tmp;
		}
	}

	if (base) {
		strlcpy(tmp, base, sizeof(tmp));

		cp = strrchr(tmp, '/');
		if (cp) {
			*(cp + 1) = '\0';
			strlcat(tmp, ensure_tgz(fname), sizeof(tmp));
			if (ispkgpattern(tmp)) {
				cp=findbestmatchingname(dirname(tmp),
							basename(tmp));
				if (cp) {
					char *s;
					s=strrchr(tmp,'/');
					assert(s != NULL);
					strlcpy(s+1, cp,
					    (size_t)(tmp + sizeof(tmp) - (s+1)));
					free(cp);
					return tmp;
				}
			} else {
				if (fexists(tmp)) {
					return tmp;
				}
			}
		}
	}

	cp = getenv("PKG_PATH");
	/* Check for ftp://... paths */
	if (isURL(cp)) {
		snprintf(tmp, sizeof(tmp), "%s/%s", cp, ensure_tgz(fname));
		return tmp;
	}
	while (cp) {
		char *cp2 = strsep(&cp, ":");

		snprintf(tmp, sizeof(tmp), "%s/%s", cp2, ensure_tgz(fname));
		if (ispkgpattern(tmp)) {
			char *s;
			s = findbestmatchingname(dirname(tmp),
						 basename(tmp));
			if (s){
				char *t;
				t=strrchr(tmp, '/');
				strlcpy(t+1, s, (size_t)(tmp + sizeof(tmp) - (t+1)));
				free(s);
				return tmp;
			}
		} else {
			if (fexists(tmp) && isfile(tmp)) {
				return tmp;
			}
		}
	}

	return NULL;
}

char *
fileGetContents(char *fname)
{
    char *contents;
    struct stat sb;
    int fd;

    if (stat(fname, &sb) == -1) {
	cleanup(0);
	errx(2, "can't stat '%s'", fname);
    }

    contents = (char *)malloc((size_t)(sb.st_size) + 1);
    if ((fd = open(fname, O_RDONLY, 0)) == -1) {
	cleanup(0);
	errx(2, "unable to open '%s' for reading", fname);
    }
    if (read(fd, contents, (size_t) sb.st_size) != (ssize_t) sb.st_size) {
	cleanup(0);
	errx(2, "short read on '%s' - did not get %lld bytes",
			fname, (int64_t)sb.st_size);
    }
    close(fd);
    contents[(size_t)sb.st_size] = '\0';
    return contents;
}

/* Takes a filename and package name, returning (in "try") the canonical "preserve"
 * name for it.
 */
bool
make_preserve_name(char *try, size_t max, char *name, char *file)
{
    char *p;
    size_t i;

    i = strlcpy(try, file, max);
    if (i == 0 || i >= max)
	return false;

    /* Catch trailing slash early */
    i--;
    if (try[i] == '/')
	try[i] = '\0';

    p = strrchr(try, '/');
    if (p == NULL)
	p = try;
    else
	p++;

    i = p - try;
    if (snprintf(p, max - i, ".%s.%s.backup", file + i, name) >= (int)(max - i))
	return false;

    return true;
}

/* Write the contents of "str" to a file */
void
write_file(const char *name, const char *str)
{
	FILE	*fp;
	size_t	len;

	if ((fp = fopen(name, "w")) == NULL) {
		cleanup(0);
		errx(2, "cannot fopen '%s' for writing", name);
	}
	len = strlen(str);
	if (fwrite(str, 1, len, fp) != len) {
		cleanup(0);
		errx(2, "short fwrite on '%s', tried to write %d bytes",
			name, len);
	}
	if (fclose(fp)) {
		cleanup(0);
		errx(2, "failure to fclose '%s'", name);
	}
}

void
copy_file(const char *dir, const char *fname, const char *to)
{
    char cmd[FILENAME_MAX];

    if (fname[0] == '/')
	snprintf(cmd, sizeof(cmd), "cp -p -r %s %s", fname, to);
    else
	snprintf(cmd, sizeof(cmd), "cp -p -r %s/%s %s", dir, fname, to);
    if (vsystem("%s", cmd)) {
	cleanup(0);
	errx(2, "could not perform '%s'", cmd);
    }
}

void
move_file(const char *dir, const char *fname, char *to)
{
    char cmd[FILENAME_MAX];

    drop_privs();
    if (fname[0] == '/')
	snprintf(cmd, sizeof(cmd), "mv -f %s %s", fname, to);
    else
	snprintf(cmd, sizeof(cmd), "mv -f %s/%s %s", dir, fname, to);
    if (vsystem("%s", cmd)) {
	raise_privs();
	cleanup(0);
	errx(2, "could not perform '%s'", cmd);
    }
    raise_privs();
}

/*
 * Copy a hierarchy (possibly from dir) to the current directory, or
 * if "to" is true, from the current directory to a location someplace
 * else.
 *
 * Though slower, using tar to copy preserves symlinks and everything
 * without me having to write some big hairy routine to do it.
 */
void
copy_hierarchy(const char *dir, char *fname, bool to)
{
    char cmd[FILENAME_MAX * 3];

    if (!to) {
	/* If absolute path, use it */
	if (*fname == '/')
	    dir = "/";
	snprintf(cmd, sizeof(cmd), "tar cf - -C %s %s | tar xpf -",
 		 dir, fname);
    }
    else
	snprintf(cmd, sizeof(cmd), "tar cf - %s | tar xpf - -C %s",
 		 fname, dir);
#ifdef DEBUG
    printf("Using '%s' to copy trees.\n", cmd);
#endif
    if (system(cmd)) {
	cleanup(0);
	errx(2, "copy_file: could not perform '%s'", cmd);
    }
}

/* Unpack a tar file */
int
unpack(char *pkg, const char *flist)
{
    char args[10], suff[80], *cp;

    args[0] = '\0';
    /*
     * Figure out by a crude heuristic whether this or not this is probably
     * compressed.
     */
    if (strcmp(pkg, "-")) {
	cp = strrchr(pkg, '.');
	if (cp) {
	    strlcpy(suff, cp + 1, sizeof(suff));
	    if (strchr(suff, 'z') || strchr(suff, 'Z'))
		strlcpy(args, "-z", sizeof(args));
	}
    }
    else
	strlcpy(args, "z", sizeof(args));
    strlcat(args, "xpf", sizeof(args));
    if (vsystem("tar %s %s %s", args, pkg, flist ? flist : "")) {
	pwarnx("tar extract of %s failed!", pkg);
	return 1;
    }
    return 0;
}

/*
 * Using fmt, replace all instances of:
 *
 * %F	With the parameter "name"
 * %D	With the parameter "dir"
 * %B	Return the directory part ("base") of %D/%F
 * %f	Return the filename part of %D/%F
 *
 */
int
format_cmd(char *buf, size_t size, const char *fmt,
	const char *dir, const char *name)
{
	char *pos;
	size_t len;

	while (*fmt != 0 && size != 0) {
		if (*fmt == '%') {
			switch(fmt[1]) {
			case 'f':
				if (name == NULL)
					return 0;
				pos = strrchr(name, '/');
				if (pos != NULL) {
					pos++;
					len = strlen(name) - (pos-name);
					if (len >= size)
						return 0;
					memcpy(buf, pos, len);
					buf += len;
					size -= len;
					fmt += 2;
					continue;
				}
				/* FALLTHRU */
			case 'F':
				if (name == NULL)
					return 0;
				len = strlen(name);
				if (len >= size)
					return 0;
				memcpy(buf, name, len);
				buf += len;
				size -= len;
				fmt += 2;
				continue;
			case 'D':
				if (dir == NULL)
					return 0;
				len = strlen(dir);
				if (len >= size)
					return 0;
				memcpy(buf, dir, len);
				buf += len;
				size -= len;
				fmt += 2;
				continue;
			case 'B':
				if (dir == NULL || name == NULL)
					return 0;
				len = strlen(dir);
				if (len >= size)
					return 0;
				memcpy(buf, dir, len);
				buf += len;
				size -= len;
				if ((pos = strrchr(name, '/')) != NULL) {
					*buf++ = '/';
					size--;
					if ((size_t)(pos - name) >= size)
						return 0;
					memcpy(buf, name, (size_t)(pos - name));
					buf += pos-name;
					size -= pos-name;
				}
				fmt += 2;
				continue;
			case '%':
				fmt++;
			default:
				break;

			}
		}
		*buf++ = *fmt++;
		size--;
	}
	if (size == 0)
		return 0;
	else
	    *buf = '\0';
	return 1;
}
