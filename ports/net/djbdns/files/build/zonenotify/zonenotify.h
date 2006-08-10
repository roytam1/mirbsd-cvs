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
 * $MirOS: ports/net/djbdns/files/build/zonenotify/zonenotify.h,v 1.3 2006/07/27 00:58:16 tg Exp $
 * $Id$
 */

#ifndef ZONENOTIFY_H
#define ZONENOTIFY_H

#ifdef _DJBDNS_PORT_V
#define VERSION	"zonenotify " _DJBDNS_PORT_V
#define AUTHOR	"MirPorts Framework"
#else
#define VERSION "zonenotify 0.01"
#define AUTHOR	"Luca Morettoni <luca@morettoni.net>"
#endif

/* alarm timeout (second) */
#define TIMEOUT	120

__BEGIN_DECLS
const char *dns_errors[] = {
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
__dead void usage(void);
int init_connection(const char *, const char *);
int ns_encode(const char *, char *);
int slave_notify(const char *, const char *);
__END_DECLS

#endif
