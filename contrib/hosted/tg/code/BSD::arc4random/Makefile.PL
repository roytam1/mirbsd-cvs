# $MirOS: contrib/hosted/tg/code/BSD::arc4random/Makefile.PL,v 1.1 2009/05/17 13:01:00 tg Exp $

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
	# note order is important
	if ($^O ne 'mirbsd' && $^O ne 'cygwin') {
		$defs = '-DHAVE_ARC4RANDOM_PUSHB=0';
	}
	if ($^O eq 'interix') {
		$libs = '-lcrypt';
	}
	if (($^O eq 'gnu') ||
	    ($^O eq 'gnukfreebsd') ||
	    ($^O eq 'linux')) {
		# Debian GNU/HURD, GNU/kFreeBSD, GNU/Linux
		# either use libbsd (lenny and up):
		#$incs = '-include /usr/include/bsd/bsd.h';
		#$libs = '-lbsd';
		# or use the contributed arc4random.c file
		$objs = 'arc4random.o';
		$defs .= ' -DHAVE_SYS_SYSCTL_H=0 -DHAVE_STDINT_H=1';
		$defs .= ' -DNEED_ARC4RANDOM_DECL';
	}
	if (($^O eq 'cygwin') ||
	    ($^O eq 'solaris')) {
		# Cygwin, Solaris: use arc4random.c contributed file
		# XXX the presence of arc4random.c here is a KLUDGE going away!
		# XXX Solaris 10 has <stdint.h> but Cygwin and Solaris 8 don't.
		$objs = 'arc4random.o';
		$defs .= ' -DNEED_ARC4RANDOM_DECL';
		if ($^O eq 'solaris') {
			$defs .= ' -DHAVE_SYS_SYSCTL_H=0 -DHAVE_STDINT_H=0';
			$defs .= ' -DUSE_INTTYPES -DREDEF_USCORETYPES';
		}
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
	LIBS			=> $libs,
	DEFINE			=> $defs,
	INC			=> $incs,
	OBJECT			=> $objs
);
