#!/usr/bin/env perl -W

use Test::More tests => 3;
use File::Temp qw( tempfile );


my $PROG = "./test-cfgfile";
my ($fh, $tempfile);

ok( -e $PROG , "Testing program exists");

BAIL_OUT("Testing program does not exist") if (! -e $PROG);

($fh, $tempfile) = tempfile();

print $fh "VAR=value\n";

is( `$PROG $tempfile`, "VAR = value\n", "One variable");

print $fh 'FOO=${VAR}2';

is( `$PROG $tempfile`, "FOO = value2\nVAR = value", "Simple variable expansion");
