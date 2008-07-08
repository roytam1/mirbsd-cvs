# $MirOS: contrib/hosted/p5/BSD/arc4random/Makefile.PL,v 1.1.201.1 2008/07/08 00:44:10 tg Exp $

use 5.000;
use ExtUtils::MakeMaker;
WriteMakefile(
	NAME			=> 'BSD::arc4random',
	VERSION_FROM		=> 'lib/BSD/arc4random.pm',
	PREREQ_PM		=> {},
	($] >= 5.005 ? (
	    ABSTRACT_FROM	=> 'lib/BSD/arc4random.pm',
	    AUTHOR		=> 'Thorsten Glaser <tg@mirbsd.de>'
	) : ()),
	# add -lbsd on Debian, -lcrypt on Interix/SFU/SUA
	LIBS			=> [''],
	# set to 0 if arc4random_pushb(3) is not available
	DEFINE			=> '-DHAVE_ARC4RANDOM_PUSHB=1',
	# set to... -include bsd/bsd.h or whatever on Debian
	INC			=> '',
	OBJECT			=> 'arc4rnd_xs.o'
);
