/* $OpenBSD: auth2-none.c,v 1.15 2008/07/02 12:36:39 djm Exp $ */
/*
 * Copyright (c) 2000 Markus Friedl.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/types.h>

#include "xmalloc.h"
#include "key.h"
#include "hostfile.h"
#include "auth.h"
#include "packet.h"
#include "log.h"
#include "buffer.h"
#include "servconf.h"
#include "compat.h"
#include "ssh2.h"
#include "monitor_wrap.h"

__RCSID("$MirOS: src/usr.bin/ssh/auth2-none.c,v 1.6 2007/09/02 18:53:13 tg Exp $");

/* import */
extern ServerOptions options;

/* "none" is allowed only one time */
static int none_enabled = 1;

static int
userauth_none(Authctxt *authctxt)
{
	none_enabled = 0;
	packet_check_eom();
	if (options.password_authentication)
		return (PRIVSEP(auth_password(authctxt, (char *)"")));
	return (0);
}

Authmethod method_none = {
	"none",
	userauth_none,
	&none_enabled
};
