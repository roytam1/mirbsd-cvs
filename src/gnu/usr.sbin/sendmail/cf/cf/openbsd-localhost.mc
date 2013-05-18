divert(-1)
#
# $MirOS: src/gnu/usr.sbin/sendmail/cf/cf/openbsd-localhost.mc,v 1.7 2007/07/07 23:34:56 tg Exp $
# @(#)openbsd-localhost.mc $Revision$
#
# Copyright (c) 2004, 2005, 2007, 2008
#	Thorsten "mirabilos" Glaser <tg@MirBSD.de>
# Copyright (c) 1998 Sendmail, Inc.  All rights reserved.
# Copyright (c) 1983 Eric P. Allman.  All rights reserved.
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# By using this file, you agree to the terms and conditions set
# forth in the LICENSE file which can be found at the top level of
# the sendmail distribution.
#
#

#
#  This configuration only runs sendmail on the localhost interface.
#  This allows mail on the local host to work without accepting
#  connections from the net at large.
#

divert(0)dnl
VERSIONID(`$MirOS: src/gnu/usr.sbin/sendmail/cf/cf/openbsd-localhost.mc,v 1.7 2007/07/07 23:34:56 tg Exp $')
OSTYPE(openbsd)dnl
FEATURE(nouucp, `reject')dnl
FEATURE(`accept_unresolvable_domains')dnl
FEATURE(`no_default_msa')dnl
MAILER(local)dnl
MAILER(smtp)dnl
DAEMON_OPTIONS(`Family=inet, Address=127.0.0.1, Name=MTA')dnl
DAEMON_OPTIONS(`Family=inet6, Address=::1, Name=MTA6, M=O')dnl
DAEMON_OPTIONS(`Family=inet, Address=127.0.0.1, Port=587, Name=MSA, M=E')dnl
DAEMON_OPTIONS(`Family=inet6, Address=::1, Port=587, Name=MSA6, M=O, M=E')dnl
CLIENT_OPTIONS(`Family=inet6, Address=::')dnl
CLIENT_OPTIONS(`Family=inet, Address=0.0.0.0')dnl
dnl
dnl Some broken nameservers will return SERVFAIL (a temporary failure) 
dnl on T_AAAA (IPv6) lookups.
define(`confBIND_OPTS', `WorkAroundBrokenAAAA')dnl
define(`confSEVEN_BIT_INPUT', `True')dnl
define(`confFORWARD_PATH', `$z/.etc/forward.$w:$z/.etc/forward:$z/.forward.$w:$z/.forward')dnl
dnl
dnl STARTTLS won't correctly verify peer (i.e. server) certificates
dnl without both confCACERT_PATH and confCACERT set and valid and
dnl containing at least one X.509 certificate each.
dnl Maybe we should add confCLIENT_CERT and confCLIENT_KEY (same
dnl values as in openbsd-proto.mc) to present a client certificate
dnl by default? (We're never a server, so confSERVER_CERT and
dnl confSERVER_KEY are never needed/used.) At least, they're set
dnl up in MirOS by default.
define(`confCACERT_PATH',	`/etc/ssl/certs')dnl
define(`confCACERT',		`/etc/ssl/deflt-ca.cer')dnl
define(`confRAND_FILE',		`/dev/arandom')dnl
