# $MirOS: contrib/hosted/p5/BSD/arc4random/Makefile.PL,v 1.2 2008/07/08 01:46:35 tg Exp $

use 5.000;
use ExtUtils::MakeMaker;

# configuration, set to auto or manual
my $cfg = 'auto';
# override these values if manual mode
my $libs = '';
my $defs = '-DHAVE_ARC4RANDOM_PUSHB=1';
my $incs = '';
my $objs = '';
# do not override below for auto mode
if ($cfg eq 'auto') {
	if ($^O ne 'mirbsd') {
		$defs = '-DHAVE_ARC4RANDOM_PUSHB=0';
	}
	if ($^O eq 'interix') {
		$libs = '-lcrypt';
	}
	if (($^O eq 'gnu') ||
	    ($^O eq 'gnukfreebsd') ||
	    ($^O eq 'linux')) {
		# Debian GNU/HURD, GNU/kFreeBSD, GNU/Linux
		# use libbsd once in testing?
		#$incs = '-include /usr/include/bsd/bsd.h';
		#$libs = '-lbsd';
		# as of now, libbsd is not enough, need arc4random.c
		# XXX the presence of arc4random.c here is a KLUDGE going away!
		$objs = 'arc4random.o';
		$defs .= ' -DHAVE_SYS_SYSCTL_H=1 -DHAVE_STDINT_H=1';
	}
}

if ($objs eq '') {
	$objs = 'arc4rnd_xs.o';
} else {
	$objs = 'arc4rnd_xs.o ' . $objs;
}

WriteMakefile(
	NAME			=> 'BSD::arc4random',
	VERSION_FROM		=> 'lib/BSD/arc4random.pm',
	PREREQ_PM		=> {},
	($] >= 5.005 ? (
	    ABSTRACT_FROM	=> 'lib/BSD/arc4random.pm',
	    AUTHOR		=> 'Thorsten Glaser <tg@mirbsd.de>'
	) : ()),
	LIBS			=> [''],
	DEFINE			=> $defs,
	INC			=> $incs,
	OBJECT			=> $objs
);
