/* $MirOS: src/usr.bin/ssh/auth.h,v 1.11 2008/12/16 20:55:18 tg Exp $ */
/* $OpenBSD: auth.h,v 1.63 2009/08/15 18:56:34 fgsch Exp $ */

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
 *
 */

#ifndef AUTH_H
#define AUTH_H

#include <signal.h>

#include <openssl/rsa.h>

#ifdef BSD_AUTH
#include <bsd_auth.h>
#endif

typedef struct Authctxt Authctxt;
typedef struct Authmethod Authmethod;
typedef struct KbdintDevice KbdintDevice;

struct Authctxt {
	sig_atomic_t	 success;
	int		 authenticated;	/* authenticated and alarms cancelled */
	int		 postponed;	/* authentication needs another step */
	int		 valid;		/* user exists and is allowed to login */
	int		 attempt;
	int		 failures;
	int		 force_pwchange;
	char		*user;		/* username sent by the client */
	char		*service;
	struct passwd	*pw;		/* set if 'valid' */
	char		*style;
	void		*kbdintctxt;
	void		*jpake_ctx;
#ifdef BSD_AUTH
	auth_session_t	*as;
#endif
	void		*methoddata;
};
/*
 * Every authentication method has to handle authentication requests for
 * non-existing users, or for users that are not allowed to login. In this
 * case 'valid' is set to 0, but 'user' points to the username requested by
 * the client.
 */

struct Authmethod {
	const char *name;
	int	(*userauth)(Authctxt *authctxt);
	int	*enabled;
};

/*
 * Keyboard interactive device:
 * init_ctx	returns: non NULL upon success
 * query	returns: 0 - success, otherwise failure
 * respond	returns: 0 - success, 1 - need further interaction,
 *		otherwise - failure
 */
struct KbdintDevice
{
	const char *name;
	void*	(*init_ctx)(Authctxt*);
	int	(*query)(void *ctx, char **name, char **infotxt,
		    u_int *numprompts, char ***prompts, u_int **echo_on);
	int	(*respond)(void *ctx, u_int numresp, char **responses);
	void	(*free_ctx)(void *ctx);
};

int      auth_rhosts(struct passwd *, const char *);
int
auth_rhosts2(struct passwd *, const char *, const char *, const char *);

int	 auth_rhosts_rsa(Authctxt *, char *, Key *);
int      auth_password(Authctxt *, const char *);
int      auth_rsa(Authctxt *, BIGNUM *);
int      auth_rsa_challenge_dialog(Key *);
BIGNUM	*auth_rsa_generate_challenge(Key *);
int	 auth_rsa_verify_response(Key *, BIGNUM *, u_char[]);
int	 auth_rsa_key_allowed(struct passwd *, BIGNUM *, Key **);

int	 auth_rhosts_rsa_key_allowed(struct passwd *, char *, char *, Key *);
int	 hostbased_key_allowed(struct passwd *, const char *, char *, Key *);
int	 user_key_allowed(struct passwd *, Key *);

void	do_authentication(Authctxt *);
void	do_authentication2(Authctxt *);

void	auth_log(Authctxt *, int, const char *, const char *);
void	userauth_finish(Authctxt *, int, char *);
int	auth_root_allowed(const char *);

char	*auth2_read_banner(void);

void	privsep_challenge_enable(void);

int	auth2_challenge(Authctxt *, char *);
void	auth2_challenge_stop(Authctxt *);
int	bsdauth_query(void *, char **, char **, u_int *, char ***, u_int **);
int	bsdauth_respond(void *, u_int, char **);
int	skey_query(void *, char **, char **, u_int *, char ***, u_int **);
int	skey_respond(void *, u_int, char **);

void	auth2_jpake_get_pwdata(Authctxt *, BIGNUM **, char **, char **);
void	auth2_jpake_stop(Authctxt *);

int	allowed_user(struct passwd *);
struct passwd * getpwnamallow(const char *user);

char	*get_challenge(Authctxt *);
int	verify_response(Authctxt *, const char *);

char	*authorised_keys_file(struct passwd *);
char	*authorised_keys_file2(struct passwd *);

FILE	*auth_openkeyfile(const char *, struct passwd *, int);

HostStatus
check_key_in_hostfiles(struct passwd *, Key *, const char *,
    const char *, const char *);

/* hostkey handling */
Key	*get_hostkey_by_index(int);
Key	*get_hostkey_by_type(int);
int	 get_hostkey_index(Key *);
int	 ssh1_session_key(BIGNUM *);

/* debug messages during authentication */
void	 auth_debug_add(const char *fmt,...) __attribute__((format(printf, 1, 2)));
void	 auth_debug_send(void);
void	 auth_debug_reset(void);

struct passwd *fakepw(void);

#define AUTH_FAIL_MSG "Too many authentication failures for %.100s"

#endif