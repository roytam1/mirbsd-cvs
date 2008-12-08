$rcsid=q<$MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $>;
#-
# Copyright (c) 2008
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.

use BSD::arc4random;
use Fcntl;

print "$rcsid\nusing BSD::arc4random v${BSD::arc4random::VERSION}\n";
if (!BSD::arc4random::have_kintf()) {
	die "kernel pushback interface missing";
}
if ($#ARGV < 0) {
	push @ARGV, "/C/MISC/putty.rnd";
}
foreach $fn (@ARGV) {
	sysopen($fh, $fn, O_RDWR) or die "[$fn] open: $!";
	binmode $fh;
	$ofs = 0;
	$nr = 0;
	$nw = 0;
	print "D: [$fn] beginning\n";
	while (1) {
		$s = "";
		$t = "";
		sysseek($fh, $ofs, 0) or die "[$fn] sysseek $ofs: $!";
		$nr = sysread($fh, $s, 240);
		if (!defined($nr)) {
			die "[$fn] sysread 240 $ofs: $!";
		}
		if ($nr == 0) {
			last;
		}
#		print "D: [$fn] read $nr at $ofs:\n" . pack("u", $s) . "\n";
		$t = BSD::arc4random::arc4random_bytes($nr, $s);
		sysseek($fh, $ofs, 0) or die "[$fn] sysseek $ofs: $!";
		$nw = syswrite($fh, $t, $nr);
		if ($nw != $nr) {
			die "[$fn] syswrite $nr $ofs: $nw $!";
		}
#		print "D: [$fn] write $nw at $ofs:\n" . pack("u", $t) . "\n";
		$ofs += $nr;
	}
	print "D: [$fn] done at $ofs\n";
	close $fh or die "[$fn] close: $!";
}
print "D: all arguments processed\n";
