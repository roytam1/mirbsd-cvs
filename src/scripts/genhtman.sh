#!/bin/mksh
# $MirOS: src/scripts/genhtman.sh,v 1.13 2007/01/25 11:04:42 tg Exp $
#-
# Build the HTML format manual pages. This is part of the MirOS con-
# tribuional and base system release process.

hm=$BSDOBJDIR/htman

. $BSDSRCDIR/scripts/roff2htm
convert_all $hm/man $hm/htm
for s in papers psd smm usd; do
	typeset -u u=$s
	mkdir -p $hm/htm/man$u
	output_htaccess >$hm/htm/man$u/.htaccess
	[[ -e $hm/papers/$s/Title.txt ]] && \
	    do_conversion_verbose Title $u \
	    $hm/papers/$s/Title.txt $hm/htm/man$u/Title.htm
	[[ -e $hm/papers/$s/contents.txt ]] && \
	    do_conversion_verbose Contents $u \
	    $hm/papers/$s/contents.txt $hm/htm/man$u/Contents.htm
	for f in $hm/papers/$s/*/paper.txt; do
		t=${f#$hm/papers/$s/}
		t=${t%/paper.txt}
		do_conversion_verbose $t $u $f $hm/htm/man$u/$t.htm
	done
done
exit 0
