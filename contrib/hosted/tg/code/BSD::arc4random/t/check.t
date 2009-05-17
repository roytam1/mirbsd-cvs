# $MirOS: contrib/hosted/p5/BSD/arc4random/t/check.t,v 1.2 2008/12/11 17:37:57 tg Exp $

print "1..12\n";

use BSD::arc4random qw(:all);

my $enta = $RANDOM;
my $entb = $RANDOM;

# $RANDOM must output numerics
print "not " unless $enta =~ /^[0-9]+$/;
print "ok 1\n";

print "not " unless $entb =~ /^[0-9]+$/;
print "ok 2\n";

# $RANDOM output must be inside [0; 32767]
print "not " if (($enta < 0) || ($enta > 32767));
print "ok 3\n";

print "not " if (($entb < 0) || ($entb > 32767));
print "ok 4\n";

# $RANDOM output should differ each time
print "not " if ($enta == $entb);
print "ok 5\n";

# Check exported variables
my $v = ${BSD::arc4random::VERSION};
my $k = BSD::arc4random::have_kintf();
print "not " unless (($v =~ /^[0-9]+.[0-9]+$/) && (($k == 0) || ($k == 1)));
print "ok 6\n";
print STDERR "DIAG: BSD::arc4random $v with";
print STDERR "out" if $k == 0;
print STDERR " kernel interface\n";

# test storing to the tied variable
$RANDOM = 123;
$enta = $RANDOM;
$RANDOM = 456;
$entb = $RANDOM;
print "not " unless $enta =~ /^[0-9]+$/;
print "ok 7\n";
print "not " unless $entb =~ /^[0-9]+$/;
print "ok 8\n";
print "not " if (($enta < 0) || ($enta > 32767));
print "ok 9\n";
print "not " if (($entb < 0) || ($entb > 32767));
print "ok 10\n";
print "not " if ($enta == $entb);
print "ok 11\n";
print "not " if (($enta == 123) && ($entb == 456));
print "ok 12\n";
