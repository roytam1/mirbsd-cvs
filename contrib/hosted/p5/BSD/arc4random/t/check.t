# $MirOS$

print "1..5\n";

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
