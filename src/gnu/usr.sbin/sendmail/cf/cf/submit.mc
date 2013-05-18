divert(-1)
#
# $MirOS: src/gnu/usr.sbin/sendmail/cf/cf/submit.mc,v 1.3 2005/03/15 21:35:54 tg Exp $
#
# Copyright (c) 2004, 2005
#	Thorsten "mirabile" Glaser <tg@MirBSD.de>
# Copyright (c) 2001-2003 Sendmail, Inc. and its suppliers.
#	All rights reserved.
#
# By using this file, you agree to the terms and conditions set
# forth in the LICENSE file which can be found at the top level of
# the sendmail distribution.
#
#

#
#  This is the prototype file for a set-group-ID sm-msp sendmail that
#  acts as a initial mail submission program.
#

divert(0)dnl
VERSIONID(`$MirOS: src/gnu/usr.sbin/sendmail/cf/cf/submit.mc,v 1.3 2005/03/15 21:35:54 tg Exp $')
VERSIONID(`$Sendmail: submit.mc,v 8.13 2003/09/10 22:12:48 ca Exp $')
define(`confCF_VERSION', `Submit')dnl
define(`__OSTYPE__',`')dnl dirty hack to keep proto.m4 from complaining
define(`_USE_DECNET_SYNTAX_', `1')dnl support DECnet
define(`confTIME_ZONE', `USE_TZ')dnl
define(`confBIND_OPTS', `WorkAroundBrokenAAAA')dnl
define(`confDONT_INIT_GROUPS', `True')dnl
define(`confEIGHT_BIT_HANDLING', `mimefy')dnl
define(`confDEF_CHAR_SET', `iso-8859-1')dnl
define(`_DEF_SMTP_MAILER_FLAGS', `LmDFMuX')dnl
define(`SMTP_MAILER_FLAGS', `67E')dnl
FEATURE(`accept_unresolvable_domains')dnl
FEATURE(`msp', `[IPv6:::1]')dnl
