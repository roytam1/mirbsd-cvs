divert(-1)
#
# $MirOS: src/gnu/usr.sbin/sendmail/cf/ostype/openbsd.m4,v 1.5 2008/05/07 13:15:17 tg Exp $
# $Sendmail: openbsd.m4,v 8.3 1999/04/24 05:37:42 gshapiro Exp $
#
# Copyright (c) 2004, 2005, 2008
#	Thorsten "mirabilos" Glaser <tg@MirBSD.de>
# Copyright (c) 1999 Sendmail, Inc. and its suppliers.
#	All rights reserved.
#
# By using this file, you agree to the terms and conditions set
# forth in the LICENSE file which can be found at the top level of
# the sendmail distribution.
#
#

divert(0)
VERSIONID(`$MirOS: src/gnu/usr.sbin/sendmail/cf/ostype/openbsd.m4,v 1.5 2008/05/07 13:15:17 tg Exp $')
ifdef(`STATUS_FILE',, `define(`STATUS_FILE', `/var/log/sendmail.st')')dnl
ifdef(`LOCAL_MAILER_PATH',, `define(`LOCAL_MAILER_PATH', /usr/libexec/mail.local)')dnl
_DEFIFNOT(`LOCAL_MAILER_FLAGS', `rmn7S')dnl
ifdef(`UUCP_MAILER_ARGS',, `define(`UUCP_MAILER_ARGS', `uux - -r -z -a$g $h!rmail ($u)')')dnl
