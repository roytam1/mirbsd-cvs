/* $MirOS: ports/infrastructure/pkgtools/lib/rcdb.c,v 1.4 2008/05/01 00:52:32 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.de>
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
 * Frontend for Berkeley db (version 1.85 - integrated in libc) mana-
 * ging a database with recno back-end (for easy shell access) saving
 * a (key, value) pair separated by a char (by default, '|'), as well
 * as simple raw data.
 *
 * Specification:
 * The data is saved as "<value><separator><key><newline>", where the
 * numeric value is saved in a format recognizable by strtoll(3), and
 * the key is a plain text in which any character, excluding newline,
 * can appear. The value ranges within a signed 64-bit integer.
 * Transparent operation is only guaranteed for data records as shown
 * above which range in chars from 1 to 126 (ISO_646.irv:1991 compli-
 * ant), and the separator is checked to be in that range. Applicati-
 * ons wanting to encode any Unicode character are urged to use utf-7
 * (mostly because transparent operation on utf-8 strings is not gua-
 * ranteed in all C environments).
 */

#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <limits.h>

#define __DBINTERFACE_PRIVATE
#include "lib.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/rcdb.c,v 1.4 2008/05/01 00:52:32 tg Exp $");

DBT *
rcdb_alloc(void *item, const size_t length)
{
	DBT *res = malloc(sizeof(DBT));

	if (res != NULL) {
		res->data = item;
		res->size = length;
	}
	return res;
}

DBT *
rcdb_string(char *text)
{
	if (text == NULL) {
		errno = EINVAL;
		return NULL;
	}
	return rcdb_alloc(text, strlen(text));
}

int
rcdb_split(RCDB *handle, int64_t *value, char **key)
{
	char sepstr[2];
	char *src, *dst;
	int len;

	if (key != NULL)
		*key = NULL;

	if ((handle == NULL) || (key == NULL)) {
		errno = EINVAL;
		return -1;
	}
	if ((handle->sep < 1) || (handle->sep > 126)) {
		errno = EDOM;
		return -1;
	}
	sepstr[0] = handle->sep;
	sepstr[1] = '\0';

	if ((src = (char *)(handle->dbt_data.data)) == NULL) {
		errno = EINVAL;
		return -1;
	}
	len = handle->dbt_data.size;
	if ((dst = malloc(len + 1)) == NULL)
		return -1;
	memcpy(dst, src, len);	/* don't use strlcpy(), src is no C string */
	dst[len] = '\0';
	src = dst;

	dst = strsep(&src, sepstr);
	if (src == NULL) {
		free(dst);
		errno = EFTYPE;
		return -1;
	}
	*value = strtoll(dst, NULL, 0);
	len = strlen(src) + 1;
	if ((*key = malloc(len)) != NULL)
		strlcpy(*key, src, len);
	free(dst);
	return 0;
}

RCDB *
rcdb_open(const char *const dbfile)
{
#ifndef O_EXLOCK
#define O_EXLOCK 0
#endif
	RECNOINFO dbinfo;
	RCDB *handle = malloc(sizeof(RCDB));

	if ((handle == NULL) || (dbfile == NULL)) {
		free(handle);
		if (dbfile == NULL)
			errno = EINVAL;
		return NULL;
	}
	handle->database = NULL;
	handle->dbt_key.data = &(handle->key);
	handle->dbt_key.size = sizeof(recno_t);
	handle->dbt_data.data = NULL;
	handle->dbt_data.size = 0;
	handle->lastrec = handle->currec = 0;
	handle->sep = '|';

	memset(&dbinfo, 0, sizeof(RECNOINFO));
	dbinfo.flags = R_NOKEY;
	dbinfo.cachesize = 131072;
	dbinfo.bval = '\n';
	dbinfo.bfname = NULL;

	if ((handle->database = dbopen(dbfile,
	    O_RDWR | O_CREAT | O_EXLOCK, 0644,
	    DB_RECNO, (void *)&dbinfo)) == NULL) {
		free(handle);
		handle = NULL;
	}
	return handle;
}

int
rcdb_close(RCDB *handle)
{
	int rv = -1;

	if (handle != NULL) {
		if (handle->database != NULL)
			if (!(handle->database->close(handle->database)))
				rv = 0;
		free(handle);
	}
	return rv;
}

int
rcdb_rawread(RCDB *handle, recno_t nr, char **bstr)
{
	int rv;
	size_t len;

	if (bstr != NULL)
		*bstr = NULL;

	if ((handle == NULL) || (!nr)) {
		errno = EINVAL;
		return -1;
	}
	handle->key = nr;
	rv = handle->database->get(handle->database,
	    &(handle->dbt_key), &(handle->dbt_data), 0);

	if (!rv)
		handle->currec = nr;

	if (bstr == NULL)
		return rv;

	if (!rv)
		if ((*bstr = malloc(1 + (len = handle->dbt_data.size)))
		    != NULL) {
			memcpy(*bstr, handle->dbt_data.data, len);
			(*bstr)[len] = '\0';
		}
	return ((*bstr == NULL) ? -1 : rv);
}

int
rcdb_rawrite(RCDB *handle, recno_t nr, char **bstr)
{
	DBT *dbt;
	int rv;

	if ((handle == NULL) || (bstr == NULL)) {
		errno = EINVAL;
		return -1;
	}
	if ((dbt = rcdb_string(*bstr)) == NULL)
		return -1;

	handle->key = nr;
	rv = handle->database->put(handle->database,
	    &(handle->dbt_key), dbt, (nr ? 0 : R_IAFTER));
	free(dbt);
	if (!rv)
		handle->currec = nr;
	return rv;
}

int
rcdb_delete(RCDB *handle, recno_t nr)
{
	if (handle == NULL) {
		errno = EINVAL;
		return -1;
	}
	handle->key = nr;
	handle->lastrec = handle->currec = 0;
	return handle->database->del(handle->database,
	    &(handle->dbt_key), 0);
}

recno_t
rcdb_lookup(RCDB *handle, const char *const searchkey)
{
	int64_t value;
	char *key;
	recno_t curno = 0;
	int rv;

	if ((handle == NULL) || (searchkey == NULL)) {
		errno = EINVAL;
		return (recno_t)-1;
	}
retr:
	rv = handle->database->seq(handle->database,
	    &(handle->dbt_key), &(handle->dbt_data),
	    (curno ? R_NEXT : R_FIRST));
	if (rv == -1)
		goto bad;
	else if (rv == 1) {
		handle->lastrec = curno - 1;
		return (handle->currec = 0);
	}
	++curno;

	if (rcdb_split(handle, &value, &key)) {
		if (errno == EFTYPE)
			goto retr;
		else
			goto bad;
	}
	if (key == NULL)
		goto retr;

	value = strcmp(key, searchkey);
	free(key);
	if (value)
		goto retr;

	return curno;

bad:
	handle->lastrec = handle->currec = 0;
	return (recno_t)-1;
}

int
rcdb_retrieve(RCDB *handle, recno_t nr, int64_t *value, char **key)
{
	int rv = 0;

	if (key != NULL)
		*key = NULL;

	if ((handle == NULL) || (value == NULL) || (key == NULL)) {
		errno = EINVAL;
		rv = -1;
	} else if (rcdb_rawread(handle, nr, NULL)) {
		rv = -1;
	} else if (rcdb_split(handle, value, key)) {
		rv = -1;
	} else if (*key == NULL)
		rv = -1;

	return rv;
}

int
rcdb_read(RCDB *handle, recno_t nr, int64_t *value)
{
	int rv;
	char *buf;

	rv = rcdb_retrieve(handle, nr, value, &buf);
	free(buf);
	return rv;
}

int
rcdb_modify(RCDB *handle, recno_t nr, int64_t value, const char *const key)
{
	size_t len;
	char *buf;
	int rv;

	if ((handle == NULL) || (key == NULL)) {
		errno = EINVAL;
		return -1;
	}
	if ((handle->sep < 1) || (handle->sep > 126)) {
		errno = EDOM;
		return -1;
	}
	len = strlen(key) + 20;
	if ((buf = malloc(len)) == NULL)
		return -1;
	snprintf(buf, len, "0x%llX%c%s", value, handle->sep, key);

	rv = rcdb_rawrite(handle, nr, &buf);
	free(buf);
	return rv;
}

int
rcdb_write(RCDB *handle, recno_t nr, int64_t value)
{
	int rv;
	int64_t tmpv;
	char *tmpk;

	if (rcdb_retrieve(handle, nr, &tmpv, &tmpk))
		rv = -1;
	else
		rv = rcdb_modify(handle, nr, value, tmpk);
	free(tmpk);
	return rv;
}

recno_t
rcdb_store(RCDB *handle, int64_t value, const char *const key)
{
	recno_t nr;

	if ((nr = rcdb_lookup(handle, key)) == (recno_t)-1)
		return (recno_t)-1;
	if (rcdb_modify(handle, nr, value, key))
		return (recno_t)-1;
	return nr;
}
