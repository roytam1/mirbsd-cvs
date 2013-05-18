#!@SHELL@
# $MirOS: ports/mailnews/bmf/files/mbmf.sh,v 1.2 2005/10/01 19:06:56 tg Exp $
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
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.
#-
# bmf filter tool front-end
#
# Syntax:
#  mbmf {0|1|c}
#  mbmf filter	# don't invoke directly

export PATH=/bin:/usr/bin:@PREFIX@/bin
typeset -l MODE="$1"
shift

BMFP=0
[[ $MODE = 0 ]] && BMFP=N
[[ $MODE = 1 ]] && BMFP=S
[[ $MODE = c ]] && BMFP=p
[[ $MODE = filter ]] && BMFP=p

if [[ $BMFP != 0 ]]; then
	if [ ! -x @PREFIX@/bin/bmf ]; then
		echo BMF not found; aborting
		exit 241
	fi
	bmf -${BMFP} -d $HOME/.etc/bmf
	BMFR=$?
	[[ $BMFP = p ]] || print "Command returned errorlevel ${BMFR}."
	[[ $BMFP = N && $BMFR = 1 ]] && print Command executed successfully. Message registered as legal.
	[[ $BMFP = S && $BMFR = 0 ]] && print Command executed successfully. Message registered as spam.
	exit 0
fi

print Syntax error.
exit 1
