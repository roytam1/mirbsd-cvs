#!/bin/mksh
# $MirOS: src/scripts/genhtman.sh,v 1.8 2005/06/05 15:22:55 tg Exp $
#-
# Copyright (c) 2005
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
# Build the HTML format manual pages. This is part of the MirOS con-
# tribuional and base system release process.

. $BSDSRCDIR/scripts/roff2htm
convert_all $BSDOBJDIR/htman/man $BSDOBJDIR/htman/htm
for s in papers psd smm usd; do
	typeset -u u=$s
	mkdir -p $BSDOBJDIR/htman/htm/man$u
	[[ -e $BSDOBJDIR/htman/papers/$s/Title.txt ]] && {
		output_header Title $u
		do_convert <$BSDOBJDIR/htman/papers/$s/Title.txt
		output_footer
	} >$BSDOBJDIR/htman/htm/man$u/Title.htm
	[[ -e $BSDOBJDIR/htman/papers/$s/contents.txt ]] && {
		output_header Contents $u
		do_convert <$BSDOBJDIR/htman/papers/$s/contents.txt
		output_footer
	} >$BSDOBJDIR/htman/htm/man$u/contents.htm
	for f in $BSDOBJDIR/htman/papers/$s/*/paper.txt; do
		t="${f#$BSDOBJDIR/htman/papers/$s/}"
		t="${t%/paper.txt}"
		{
			output_header $t $u
			do_convert <$f
			output_footer
		} >$BSDOBJDIR/htman/htm/man$u/$t.htm
	done
done
exit 0
