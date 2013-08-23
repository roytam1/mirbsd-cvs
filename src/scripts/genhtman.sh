#!/bin/mksh
# $MirOS: src/scripts/genhtman.sh,v 1.19 2013/03/29 19:10:56 tg Exp $
#-
# Copyright © 2005, 2007, 2011, 2012, 2013
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.
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
	nrcon -mdoc bin/mksh/lksh.1 >$hm/man/cat1/lksh.0
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
	{
		output_header sendmail.cf DOCS
		print -n '<pre>'
		set -A convs -- -e 's/&/\&amp;/g' \
		    -e 's/</\&lt;/g' -e 's/>/\&gt;/g' \
		    -e 's#\([0-9A-z][-.,0-9A-z:]*\)(\([1-9]\))#<a href="../man\2/\1.htm">&</a>#g'
		set -A jumps
		<$BSDSRCDIR/gnu/usr.sbin/sendmail/cf/README \
		    tr '\n' '' | \
		    sed 's/+-*+|//g' | \
		    tr '' '\n' | \
		    fgrep '' | \
		    sed -e 's/^ *//g' -e 's/ *|*$//g' |&
		njumps=0
		while IFS= read -pr x; do
			jumps[j = njumps++]=$x
			i=-1
			while (( ++i < j )); do
				[[ -n ${jumps[i]} ]] || continue
				[[ $x = *"${jumps[i]}"* ]] || continue
				jumps[njumps++]=${jumps[i]}
				unset jumps[i]
			done
		done
		set -A jumps -- "${jumps[@]}"
		njumps=${#jumps[*]}
		i=-1
		while (( ++i < njumps )); do
			set -A convs+ -- -e "s!${jumps[i]}!${i}!g"
		done
		i=-1
		while (( ++i < njumps )); do
			set -A convs+ -- -e "s!${i}!<a href=\"#${jumps[i]//[ \?,-]/_}\">${jumps[i]}</a>!g"
		done
		set -A convs+ -- \
		    -e 's#in op\.me)#in <a href="../manSMM/08.sendmailop.htm">op.me</a>)#' \
		    -e 's#doc/op/op\.\*#doc/op/op.me#' \
		    -e 's#in op\.me)#in doc/op/op.me)#' \
		    -e 's#doc/op/op\.me#<a href="../manSMM/08.sendmailop.htm">&</a>#g' \
		    -e 's#doc/op/op\..me,ps,txt.#<a href="../manSMM/08.sendmailop.htm">&</a>#g'
		<$BSDSRCDIR/gnu/usr.sbin/sendmail/cf/README \
		    sed "${convs[@]}" | \
		    tr '\n' '' | \
		    sed -e 's-+| <a href="#\([^<]*\)</a> |+--+| <span id="\1</span> |+-g' | \
		    tr '' '\n'
		print '</pre>'
		output_footer
	} >$hr/manDOCS/sendmail.cf.htm
	mkdir -p $hr/manINFO/gpc/{demos,images}
	cd $BSDSRCDIR/gcc/gcc/p/demos; for x in *; do
		[[ -f $x ]] && cp "$x" $hr/manINFO/gpc/demos/
	done
	cd $BSDSRCDIR/gcc/gcc/p/doc/images; for x in *; do
		[[ $x = README ]] && continue
		[[ -f $x ]] && cp "$x" $hr/manINFO/gpc/images/
	done
	cd $hr/manINFO; for x in gpc{,-*}.*; do
		ed -s "$x" <<-'EOF'
			,g!src="\.\./!s!!src="gpc/!g
			,g!href="\.\./!s!!href="gpc/!g
			wq
		EOF
	done
	output_htaccess >$hr/.htaccess
	output_htaccess >$hr/manDOCS/.htaccess
	{
		output_htaccess
		print "AddType 'text/html; charset=utf-8' html"
	} >$hr/manINFO/.htaccess
fi

cd $hm/htm
set_conversion_man
convert_all $hm/man $hm/htm
find * -type f -o -type l | cpio -pdlu $hr
exit 0
