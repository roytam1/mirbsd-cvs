#!/bin/mksh
# $MirOS: src/scripts/genhtman.sh,v 1.10 2005/12/22 01:12:34 tg Exp $
#-
# Build the HTML format manual pages. This is part of the MirOS con-
# tribuional and base system release process.

. $BSDSRCDIR/scripts/roff2htm
convert_all $BSDOBJDIR/htman/man $BSDOBJDIR/htman/htm
for s in papers psd smm usd; do
	typeset -u u=$s
	mkdir -p $BSDOBJDIR/htman/htm/man$u
	print DirectoryIndex /dev/null >$BSDOBJDIR/htman/htm/man$u/.htaccess
	[[ -e $BSDOBJDIR/htman/papers/$s/Title.txt ]] && \
	    do_conversion Title $u \
	    <$BSDOBJDIR/htman/papers/$s/Title.txt \
	    >$BSDOBJDIR/htman/htm/man$u/Title.htm
	[[ -e $BSDOBJDIR/htman/papers/$s/contents.txt ]] && \
	    do_conversion Contents $u \
	    <$BSDOBJDIR/htman/papers/$s/contents.txt \
	    >$BSDOBJDIR/htman/htm/man$u/Contents.htm
	for f in $BSDOBJDIR/htman/papers/$s/*/paper.txt; do
		t="${f#$BSDOBJDIR/htman/papers/$s/}"
		t="${t%/paper.txt}"
		do_conversion $t $u <$f >$BSDOBJDIR/htman/htm/man$u/$t.htm
	done
done
exit 0
