divert(-1)
#
# $MirOS: src/gnu/usr.sbin/sendmail/cf/cf/openbsd-submit.mc,v 1.4 2010/12/19 17:17:57 tg Exp $
# $OpenBSD: openbsd-submit.mc,v 1.1 2008/10/03 16:29:05 millert Exp $
#
# Copyright (c) 2004, 2005, 2006, 2008, 2011
#	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
# Copyright (c) 2001-2003 Sendmail, Inc. and its suppliers.
#	All rights reserved.
#
# By using this file, you agree to the terms and conditions set
# forth in the LICENSE file which can be found at the top level of
# the sendmail distribution.
#
#

#
#  This is the prototype file for a set-group-ID sm-msp sendmail
#  that acts as a initial mail submission program.
#

divert(0)dnl
VERSIONID(`$MirOS: src/gnu/usr.sbin/sendmail/cf/cf/openbsd-submit.mc,v 1.4 2010/12/19 17:17:57 tg Exp $')
define(`confCF_VERSION', `Submit')dnl
OSTYPE(openbsd)dnl
define(`_USE_DECNET_SYNTAX_', `1')dnl support DECnet
define(`confTIME_ZONE', `USE_TZ')dnl
define(`confBIND_OPTS', `WorkAroundBrokenAAAA')dnl
define(`confDONT_INIT_GROUPS', `True')dnl
define(`confEIGHT_BIT_HANDLING', `mimefy')dnl
define(`confDEF_CHAR_SET', `utf-8')dnl
define(`confCACERT_PATH', `/etc/ssl/certs')dnl
define(`_DEF_SMTP_MAILER_FLAGS', `LmDFMuX')dnl
define(`SMTP_MAILER_FLAGS', `67E')dnl
define(`confCT_FILE', `-o MAIL_SETTINGS_DIR`'trusted-users')dnl
FEATURE(`use_ct_file')dnl
FEATURE(`accept_unresolvable_domains')dnl
dnl
dnl First is for IPv4, second is for IPv6
dnl FEATURE(`msp', `[127.0.0.1]')dnl
FEATURE(`msp', `[IPv6:::1]')dnl
dnl
LOCAL_CONFIG
dnl
dnl Parts of these Content-type are never base64-encoded, only QP
dnl
Cqtext/plain
