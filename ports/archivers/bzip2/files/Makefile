# $MirOS: ports/archivers/bzip2/files/Makefile,v 1.1 2005/05/21 12:54:56 bsiegert Exp $

SUBDIR=		lib bzip2 bzip2recover

check test regress:
	@cat words1
	bzip2/bzip2 -1  < sample1.ref > sample1.rb2
	bzip2/bzip2 -2  < sample2.ref > sample2.rb2
	bzip2/bzip2 -3  < sample3.ref > sample3.rb2
	bzip2/bzip2 -d  < sample1.bz2 > sample1.tst
	bzip2/bzip2 -d  < sample2.bz2 > sample2.tst
	bzip2/bzip2 -ds < sample3.bz2 > sample3.tst
	cmp sample1.bz2 sample1.rb2
	cmp sample2.bz2 sample2.rb2
	cmp sample3.bz2 sample3.rb2
	cmp sample1.tst sample1.ref
	cmp sample2.tst sample2.ref
	cmp sample3.tst sample3.ref
	@print
	@print 'If you got this far and the “cmp”s didn’t complain, it looks'
	@print 'like you’re in business.'
	@print

.include <bsd.subdir.mk>
