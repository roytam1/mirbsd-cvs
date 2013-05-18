#!/bin/mksh
# $MirOS: src/scripts/xbuild-tool.sed,v 1.6 2006/10/15 00:16:49 tg Exp $
#-
# Copyright (c) 2004, 2006
#	Thorsten Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-
# This script replaces the need to build cross-binutils and cross-ld
# by calling native (--enable-target=all --enable-64-bit-bfd) tools,
# setting the appropriate environment option first.

export GNUTARGET='@@TARGET@@' LDEMULATION='@@EMUL@@'

ME=$0
CALLED=${ME##*/}
CALLED=/usr/bin/${CALLED#${GNUTARGET}-}
if [[ ! -x $CALLED ]]; then
	print -u2 "Cannot execute native tool $CALLED"
	print -u2 "for $ME, exiting."
	exit 255
fi
exec $CALLED "$@"
