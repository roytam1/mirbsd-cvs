#!@SHELL@
# $MirOS: ports/mailnews/bmf/files/mbmf-sm.sh,v 1.2 2005/10/01 19:06:56 tg Exp $
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
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# Called via
# echo '|@PREFIX@/libexec/mbmf-sm' >.forward

eval export HOME=~$(id -un)
@SHELL@ @PREFIX@/bin/mbmf filter | @PREFIX@/libexec/dmail
