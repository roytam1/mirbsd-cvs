divert(-1)
#
# Copyright (c) 2010
#	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
# Copyright (c) 1998-2000 Sendmail, Inc. and its suppliers.
#	All rights reserved.
# Copyright (c) 1983 Eric P. Allman.  All rights reserved.
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# By using this file, you agree to the terms and conditions set
# forth in the LICENSE file which can be found at the top level of
# the sendmail distribution.
#
#

divert(0)
VERSIONID(`$MirOS: src/gnu/usr.sbin/sendmail/cf/ostype/openbsd.m4,v 1.5 2008/05/07 13:15:17 tg Exp $')
VERSIONID(`$Id$')
define(`confEBINDIR', `/usr/sbin')
ifdef(`PROCMAIL_MAILER_PATH',,
	define(`PROCMAIL_MAILER_PATH', `/usr/bin/procmail'))
FEATURE(local_procmail, `', `', `SPfhn8')
