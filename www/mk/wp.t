# $MirOS: www/mk/wp.t,v 1.1 2018/08/29 01:19:12 tg Exp $
#-
# test cases for ../files/wp.pm

use strict;
use warnings;

# magic to allow including relative to dirname($0)
use FindBin qw/$Bin/;
BEGIN {
	if ($Bin =~ m!([\w\./]+)!) {
		$Bin = $1;
	} else {
		die "Bad directory $Bin\n";
	}
}
use lib "$Bin/../files";
# include wp.pm, hopefully from dirname($0)/../files
use wp;

while (<DATA>) {
	chomp;
	my $q = $_;
	next if $q eq "";
	my ($code, $label, $url) = explwp($q);
	$url =~ s/\'/\'\\\'\'/g;
	print "lynx '$url' # ($code) <$label> {$q}\n"
}

__DATA__
BC2036
EC988
GA12512
GC4M90G
GDCI-JUNU
GE0300
GGACUO
GK9A81
GL12VZCR
N02F79
OB1A74
OC11141
OK00CA
OP8U1S
OR01E2
OU0B34
OZ0277
PR2950G
SH02BF
TB3C1JW
TC1OYX
LC7TL
CCHU
VX76-DIKA
WM5CZY
m/mirabilos/1
2010-01-12_global
2014-10-28_50_7
invalid
