#!/bin/ksh
# $MirOS: src/scripts/genhtman.sh,v 1.3 2005/03/29 00:21:33 tg Exp $
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
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# Build the HTML format manual pages. This is part of the MirOS con-
# tribuional and base system release process.

cd $BSDRELDIR
if ! [[ -e base && -e gcc && -e x11 ]]; then
	print Invoke in BSDRELDIR
	exit 1
fi

. /usr/src/scripts/roff2htm
mkdir -p /usr/obj/htman/{man,htm}
for s in x11 gcc base; do
	( cd $s/usr/share/man; find * -type f | cpio -pdlu /usr/obj/htman/man )
done
convert_all /usr/obj/htman/man /usr/obj/htman/htm
for s in papers psd smm usd; do
	typeset -u u=$s
	mkdir -p /usr/obj/htman/papers/$s /usr/obj/htman/htm/man$u
	( cd /usr/obj/htman/papers/$s; lndir base/usr/share/doc/$s; make )
	if [[ -e /usr/obj/htman/papers/$s/Title.txt ]]; then
		( output_header Title $u
		  do_convert </usr/obj/htman/papers/$s/Title.txt
		  output_footer
		) >/usr/obj/htman/htm/man$u/Title.htm
	fi
	if [[ -e /usr/obj/htman/papers/$s/contents.txt ]]; then
		( output_header Contents $u
		  do_convert </usr/obj/htman/papers/$s/contents.txt
		  output_footer
		) >/usr/obj/htman/htm/man$u/contents.htm
	fi
	for f in /usr/obj/htman/papers/$s/*/paper.txt; do
		t="${f#/usr/obj/htman/papers/$s/}"
		t="${t%/paper.txt}"
		( output_header $t $u
		  do_convert <$f
		  output_footer
		) >/usr/obj/htman/htm/man$u/$t.htm
	done
done

$SUDO mkdir -p htman
( cd /usr/obj/htman/htm; find man* -name \*.htm | cpio -o ) \
    | ( cd htman; $SUDO cpio -id )
$SUDO chown -R 0:0 htman
$SUDO chmod -R a=rX htman
rm -rf /usr/obj/htman
exit 0
