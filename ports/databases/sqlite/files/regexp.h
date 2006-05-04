/* $MirOS$ */

#ifndef _SQLITE3_REGEXP_H
#define _SQLITE3_REGEXP_H

void sqlite3_regexp_posixext_func(sqlite3_context *, int, sqlite3_value **);
void sqlite3_regexp_posixext_register(sqlite3 *);

#endif
