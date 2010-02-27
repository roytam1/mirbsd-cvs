#!/usr/bin/env perl -W

use Test::More tests => 11;
use File::Temp qw( tempfile );


my $PROG = "./test-cfgfile";
my ($fh, $tempfile);

ok( -e $PROG , "Testing program exists");

BAIL_OUT("Testing program does not exist") if (! -e $PROG);

($fh, $tempfile) = tempfile();

print $fh "VAR=value\n";
is( `$PROG $tempfile`, "VAR = value\n", "One variable");

is( `$PROG $tempfile UNDEF_VAR`, "UNDEF_VAR is undefined\n", "Undefined variable");

print $fh "FOO=\${VAR}2\n";
is( `$PROG $tempfile FOO`, "FOO = value2\n", "Simple variable expansion");

print $fh "_\${VAR}=This is a test.\n";
is( `$PROG $tempfile _value`, "_value = This is a test.\n", "Expansion in a variable name");

print $fh "FOO=redefined\n";
is( `$PROG $tempfile FOO`, "FOO = redefined\n", "Redefine a variable, second definition takes precedence");

print $fh "#UNDEF=test\n";
is( `$PROG $tempfile UNDEF`, "UNDEF is undefined\n", "Comments");

print $fh "WS=hello   \n";
is( `$PROG $tempfile WS`, "WS = hello\n", "Trailing whitespace");

print $fh "WS2=hello # world\n";
is( `$PROG $tempfile WS2`, "WS2 = hello\n", "Trailing whitespace before comment start");

print $fh "  WS3=hello\n";
is( `$PROG $tempfile WS3`, "WS3 = hello\n", "Leading whitespace");

print $fh "\tWS4=hello\t\n";
is( `$PROG $tempfile WS4`, "WS4 = hello\n", "Leading and trailing tab characters");
