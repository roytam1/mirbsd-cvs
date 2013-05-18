/**	$MirOS: src/lib/libc/gen/getpwent.c,v 1.2 2005/03/06 20:28:40 tg Exp $ */
/*	$OpenBSD: getpwent.c,v 1.34 2005/08/08 08:05:34 espie Exp $ */
/*
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 * Portions Copyright (c) 1994, 1995, 1996, Jason Downs.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <fcntl.h>
#include <db.h>
#include <syslog.h>
#include <pwd.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <netgroup.h>

__RCSID("$MirOS: src/lib/libc/gen/getpwent.c,v 1.2 2005/03/06 20:28:40 tg Exp $");

static struct passwd _pw_passwd;	/* password structure */
static DB *_pw_db;			/* password database */
static int _pw_keynum;			/* key counter */
static int _pw_stayopen;		/* keep fd's open */
static int _pw_flags;			/* password flags */
static int __hashpw(DBT *);
static int __initdb(void);

struct passwd *
getpwent(void)
{
	DBT key;
	char bf[sizeof(_pw_keynum) + 1];

	if (!_pw_db && !__initdb())
		return ((struct passwd *)NULL);

	++_pw_keynum;
	bf[0] = _PW_KEYBYNUM;
	memmove(bf + 1, (char *)&_pw_keynum, sizeof(_pw_keynum));
	key.data = (u_char *)bf;
	key.size = sizeof(_pw_keynum) + 1;
	if (__hashpw(&key)) {
		return &_pw_passwd;
	}
	return (struct passwd *)NULL;
}

struct passwd *
getpwnam(const char *name)
{
	DBT key;
	int len, rval;
	char bf[_PW_NAME_LEN + 1];

	if (!_pw_db && !__initdb())
		return ((struct passwd *)NULL);

	bf[0] = _PW_KEYBYNAME;
	len = strlen(name);
	if (len > _PW_NAME_LEN)
		rval = 0;
	else {
		memmove(bf + 1, name, MIN(len, _PW_NAME_LEN));
		key.data = (u_char *)bf;
		key.size = MIN(len, _PW_NAME_LEN) + 1;
		rval = __hashpw(&key);
	}

	if (!_pw_stayopen) {
		(void)(_pw_db->close)(_pw_db);
		_pw_db = (DB *)NULL;
	}
	return (rval ? &_pw_passwd : (struct passwd *)NULL);
}

struct passwd *
getpwuid(uid_t uid)
{
	DBT key;
	char bf[sizeof(_pw_keynum) + 1];
	uid_t keyuid;
	int rval;

	if (!_pw_db && !__initdb())
		return ((struct passwd *)NULL);

	bf[0] = _PW_KEYBYUID;
	keyuid = uid;
	memmove(bf + 1, &keyuid, sizeof(keyuid));
	key.data = (u_char *)bf;
	key.size = sizeof(keyuid) + 1;
	rval = __hashpw(&key);

	if (!_pw_stayopen) {
		(void)(_pw_db->close)(_pw_db);
		_pw_db = (DB *)NULL;
	}
	return (rval ? &_pw_passwd : (struct passwd *)NULL);
}

int
setpassent(int stayopen)
{
	_pw_keynum = 0;
	_pw_stayopen = stayopen;
	return (1);
}

void
setpwent(void)
{
	(void) setpassent(0);
}

void
endpwent(void)
{
	_pw_keynum = 0;
	if (_pw_db) {
		(void)(_pw_db->close)(_pw_db);
		_pw_db = (DB *)NULL;
	}
}

static int
__initdb(void)
{
	static int warned;

	if ((_pw_db = dbopen(_PATH_SMP_DB, O_RDONLY, 0, DB_HASH, NULL)) ||
	    (_pw_db = dbopen(_PATH_MP_DB, O_RDONLY, 0, DB_HASH, NULL)))
		return (1);
	if (!warned)
		syslog(LOG_ERR, "%s: %m", _PATH_MP_DB);
	warned = 1;
	return (0);
}

static int
__hashpw(DBT *key)
{
	char *p, *t;
	static u_int max;
	static char *line;
	DBT data;

	if ((_pw_db->get)(_pw_db, key, &data, 0))
		return (0);
	p = (char *)data.data;
	if (data.size > max) {
		char *nline;

		max = data.size + 256;
		nline = realloc(line, max);
		if (nline == NULL) {
			if (line)
				free(line);
			line = NULL;
			max = 0;
			return 0;
		}
		line = nline;
	}

	t = line;
#define	EXPAND(e)	e = t; while ((*t++ = *p++));
	EXPAND(_pw_passwd.pw_name);
	EXPAND(_pw_passwd.pw_passwd);
	memmove((char *)&_pw_passwd.pw_uid, p, sizeof(int));
	p += sizeof(int);
	memmove((char *)&_pw_passwd.pw_gid, p, sizeof(int));
	p += sizeof(int);
	memmove((char *)&_pw_passwd.pw_change, p, sizeof(time_t));
	p += sizeof(time_t);
	EXPAND(_pw_passwd.pw_class);
	EXPAND(_pw_passwd.pw_gecos);
	EXPAND(_pw_passwd.pw_dir);
	EXPAND(_pw_passwd.pw_shell);
	memmove((char *)&_pw_passwd.pw_expire, p, sizeof(time_t));
	p += sizeof(time_t);

	/* See if there's any data left.  If so, read in flags. */
	if (data.size > (p - (char *)data.data)) {
		memmove((char *)&_pw_flags, p, sizeof(int));
		p += sizeof(int);
	} else
		_pw_flags = _PASSWORD_NOUID|_PASSWORD_NOGID;	/* default */

	return (1);
}
