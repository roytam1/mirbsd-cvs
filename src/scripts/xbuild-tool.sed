#!/bin/ksh
# $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $
#-
# Copyright (c) 2004
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# All advertising materials mentioning features or use of this soft-
# ware must display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# This script replaces the need to build cross-binutils and cross-ld
# by calling native (--enable-target=all --enable-64-bit-bfd) tools,
# setting the appropriate environment option first.

ME=$0
GNUTARGET=@@TARGET@@
LDEMULATION=@@EMUL@@
CALLED=${ME##*/}
CALLED=/usr/bin/${CALLED#${GNUTARGET}-}

if [[ ! -x $CALLED ]]; then
	print Cannot execute native tool $CALLED
	print for $ME, exiting.
	exit 255
fi

export GNUTARGET LDEMULATION
exec $CALLED "$@"
