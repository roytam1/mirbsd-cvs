/*
 * Copyright (c) 2004  Morettoni Luca <luca@morettoni.net>
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id$
 */

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#ifdef _BSD
#include <arpa/nameser_compat.h>
#endif
#include <netdb.h>

#define VERSION "zonenotify 0.01"
#define AUTHOR	"Luca Morettoni <luca@morettoni.net>"

/* alarm timeout (second) */
#define TIMEOUT	120

char *dns_errors[] = {
	"No error",
	"Format error",
	"Server failure",
	"Non-existent domain",
	"Not implemented",
	"Query refused",
	"Name exists when it should not",
	"RR Set exists when it should not",
	"RR Set that should exist does not",
	"Server not authoritative for zone",
	"Name not contained in zone",
	"", "", "", "", "", /* available for assignment */
	"Bad OPT version",
	"TSIG signature failure",
	"Key not recognized",
	"Signature out of time window",
	"Bad TKEY mode",
	"Duplicate key name",
	"Algorithm not supported"
};

/* communication socket */
int s;

/* program functions */
int ns_encode (char *str, char *buff);
int slave_notify (char *domain, const char *server);
void usage ();
int init_connection (const char *server);
void stop_connection (void);
