#!/bin/mksh
# $MirOS: src/scripts/genhtman.sh,v 1.15 2007/10/21 15:43:49 tg Exp $
#-
# Build the HTML format manual pages. This is part of the MirOS con-
# tribuional and base system release process.

hm=$BSDOBJDIR/htman
hr=$BSDRELDIR/htman
arch=${MACHINE:-$(uname -m)}

. $BSDSRCDIR/scripts/roff2htm
mkdir -p $hm/{man,htm}

if [[ -e $BSDRELDIR/rel/htmi$OSrev.ngz ]]; then
	cd $BSDRELDIR/x11/usr/X11R6/man
	cpio -pdlu $hm/man <$BSDSRCDIR/distrib/lists/htman/list.x11.$arch
	cd $BSDRELDIR/base/usr/share/man
	cpio -pdlu $hm/man <$BSDSRCDIR/distrib/lists/htman/list.base.$arch

	cd $hr; tar xzf $BSDRELDIR/rel/htmi$OSrev.ngz
else
	cd $BSDRELDIR/x11/usr/X11R6/man
	find * -type f -o -type l | cpio -pdlu $hm/man
	cd $BSDRELDIR/base/usr/share/man
	find * -type f -o -type l | cpio -pdlu $hm/man
	cd $hm
	tar xzf $BSDRELDIR/rel/ports$OSrev.ngz usr/ports/Setup.sh.8
	nrcon -mdoc usr/ports/Setup.sh.8 >man/cat8/Setup.sh.0
	tar xzf $BSDRELDIR/rel/pkgutl$OSrev.ngz usr/mpkg/man/cat\?/\*.0
	cd $hm/usr/mpkg/man
	find * -type f -o -type l | cpio -pdlu $hm/man
	for doc in papers psd smm usd; do
		mkdir -p $hm/papers/$doc
		cd $hm/papers/$doc
		lndir $BSDRELDIR/base/usr/share/doc/$doc
	done
	mkdir $hm/texinfo
	cd $BSDSRCDIR
	make do-htinfopapers
	cp $BSDOBJDIR/share/doc/legal/LICENCE-BSD.0 $hm/man/cat7/BSD-Licence.0

	set_conversion_paper
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

	output_htaccess >$hm/H
	mkdir -p $hr/man{DOCS,INFO}
	cd $hm/texinfo; pax -rw *.html $hr/manINFO/
	cd $BSDRELDIR/base/usr/share/doc/html; pax -rw * $hr/manDOCS/
	cd $hr/manDOCS; find . -type f -a ! -name '*.htm' -a ! -name '*.html' \
	    -a ! -name '*.jpg' -print0 | xargs -0 rm -f --
	output_htaccess >$hr/.htaccess
	output_htaccess >$hr/manDOCS/.htaccess
	{
		output_htaccess
		print "AddType 'text/html; charset=iso-8859-1' html"
	} >$hr/manINFO/.htaccess
fi

cd $hm/htm
set_conversion_man
convert_all $hm/man $hm/htm
find * -type f -o -type l | cpio -pdlu $hr
exit 0
