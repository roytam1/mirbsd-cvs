#!/usr/bin/perl
# $MirOS: ports/infrastructure/pkgtools/pkg/pkg.pl,v 1.5 2007/07/09 20:20:15 bsiegert Exp $
# $OpenBSD: pkg.pl,v 1.7 2001/11/17 10:42:11 espie Exp $
#
# Copyright (c) 2001 Marc Espie.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE OPENBSD PROJECT AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OPENBSD
# PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

require 5.6.0;

use strict;
use Getopt::Std;
use File::Spec;

# This is a first implementation of the pkg_* perl replacement.
# We are doing this piecewise, handling larger and larger parts of
# package handling in perl, until the corresponding C code just vanishes.

# This code is going to change a lot in the near future.

# Currently, it's a bare-bones implementation of the new dependency
# handler. Note that even the syntax may change.

my $vardb = $ENV{'PKG_DBDIR'} || '@@dbdir@@/pkg';
my $verbose;

sub compare_pseudo_numbers
{
	my ($n, $m) = @_;

	my ($n1, $m1);

	if ($n =~ m/^\d+/) {
		$n1 = $&;
		$n = $';
	}
	if ($m =~ m/^\d+/) {
		$m1 = $&;
		$m = $';
	}

	if ($n1 == $m1) {
		return $n cmp $m;
	} else {
		return $n1 <=> $m1;
	}
}


sub dewey_compare
{
	my ($a, $b) = @_;
	my ($pa, $pb);

	unless ($b =~ m/-\d+$/) { 		# does the Dewey hold a -<number> ?
		$a =~ s/-\d+$//; 	# No -> strip it from version.
	}

	return 0 if $a =~ /^$b$/; 	# bare equality

	if ($a =~ s/-(\d+)$//) {	# extract patchlevels
		$pa = $1;
	}
	if ($b =~ s/-(\d+)$//) {
		$pb = $1;
	}

	my @a = split(/\./, $a);
	push @a, $pa if defined $pa;	# ... and restore them
	my @b = split(/\\\./, $b);
	push @b, $pb if defined $pb;
	while (@a > 0 && @b > 0) {
		my $va = shift @a;
		my $vb = shift @b;
		next if $va eq $vb;
		return compare_pseudo_numbers($va, $vb);
	}
	if (@a > 0) {
		return 1;
	} else {
		return -1;
	}
}

sub check_version
{
	my ($v, $spec) = @_;
	local $_;

	# any version spec
	return 1 if $spec eq '.*';

	my @specs = split(/,/, $spec);
	for (grep /^\d/, @specs) { 		# exact number: check match
		return 1 if $v =~ /^$_$/;
		return 1 if $v =~ /^${_}-\d+$/; # allows for recent patches
	}

	# Last chance: dewey specs ?
	my @deweys = grep !/^\d/, @specs;
	for (@deweys) {
		if (m/^\<\=|\>\=|\<|\>/) {
			my ($op, $dewey) = ($&, $');
			my $compare = dewey_compare($v, $dewey);
			return 0 if $op eq '<' && $compare >= 0;
			return 0 if $op eq '<=' && $compare > 0;
			return 0 if $op eq '>' && $compare <= 0;
			return 0 if $op eq '>=' && $compare < 0;
		} else {
			return 0;	# unknown spec type
		}
	}
	return @deweys == 0 ? 0 : 1;
}

sub check_1flavour
{
	my ($f, $spec) = @_;
	local $_;

	for (split /-/, $spec) {
		# must not be here
		if (m/^\!/) {
			return 0 if $f->{$'};
		# must be here
		} else {
			return 0 unless $f->{$_};
		}
	}
	return 1;
}

sub check_flavour
{
	my ($f, $spec) = @_;
	local $_;
	# no flavour constraints
	return 1 if $spec eq '';

	$spec =~ s/^-//;
	# retrieve all flavours
	my %f = map +($_, 1), split /\-/, $f;

	# check each flavour constraint
	for (split /,/, $spec) {
		if (check_1flavour(\%f, $_)) {
			return 1;
		}
	}
	return 0;
}

sub subpattern_match
{
	my ($p, $list) = @_;
	local $_;

	my ($stemspec, $vspec, $flavourspec);

	# first, handle special characters (shell -> perl)
	$p =~ s/\./\\\./g;
	$p =~ s/\+/\\\+/g;
	$p =~ s/\*/\.\*/g;
	$p =~ s/\?/\./g;

	# then, guess at where the version number is if any,

	# this finds patterns like -<=2.3,>=3.4-1-
	# the only constraint is that the actual number
	# - must start with a digit,
	# - not contain - or ,
	if ($p =~ m/\-((?:\>|\>\=|\<|\<\=)?\d[^-]*(-\d+)?)/) {
		($stemspec, $vspec, $flavourspec) = ($`, $1, $');
	# `any version' matcher
	} elsif ($p =~ m/\-(\.\*)/) {
		($stemspec, $vspec, $flavourspec) = ($`, $1, $');
	# okay, so no version marker. Assume no flavour spec.
	} else {
		($stemspec, $vspec, $flavourspec) = ($p, '', '');
	}

	$p = "$stemspec-\.\*" if $vspec ne '';

	# First trim down the list
	my @l = grep {/^$p$/} @$list;

	my @result = ();
	# Now, have to extract the version number, and the flavour...
	for (@l) {
		my ($stem, $v, $flavour);
		if (m/\-(\d[^-]*(-\d+)?)/) {
			($stem, $v, $flavour) = ($`, $1, $');
			if ($stem =~ m/^$stemspec$/ &&
			    check_version($v, $vspec) &&
			    check_flavour($flavour, $flavourspec)) {
			    	push(@result, $_);
			}
	    	}
	}

	return @result;
}

sub pattern_match
{
	my ($pattern, $list) = @_;
	my @l;

	for my $subpattern (split /\|/, $pattern) {
		@l = subpattern_match($subpattern, $list);
		if (@l > 0) {
			return $l[0];
		}
	}
	return 0;
}

sub check_dependencies
{
	my $pattern = shift;
	unless (chdir $vardb) {
		die "Directory $vardb absent\n";
	}
	my @list = glob '*';
	# Try subpatterns in sequence
	return pattern_match($pattern, \@list) ? 1 : 0;
}

sub check_lib_specs
{
	my $base = shift;
	my $dir;
	for my $spec (split(/,/, shift)) {
		print "  libspec $spec: " if $verbose;
		if ($spec =~ m|.*/|) {
			$dir = "$base/$&";
			$spec = $';
		} else {
			$dir = "$base/lib";
		}
		if ($spec =~ m/^(.*)\.(\d+)\.(\d+)$/) {
			my ($libname, $major, $minor) = ($1, $2, $3);
			unless (opendir(DIRECTORY, $dir)) {
				print "base directory not found\n" if $verbose;
				return undef;
			}
			my @candidates =
			    grep { (/^lib\Q$libname\E\.so\.$major\.(\d+)$/
			    	&& $1 >= $minor) ||
				(/^lib\Q$libname\E.$major\.(\d+)\.\d+\.dylib$/
				&& $1 >= $minor) }
			    readdir(DIRECTORY);
			close(DIRECTORY);
			if (@candidates == 0) {
				print "not found\n" if $verbose;
				return undef;
			} else {
				print "found ", $candidates[0], "\n" if $verbose;
			}
		} elsif ($spec =~ m/^(.*)\.la$/) {
			my $libname = $1;
			if (-f File::Spec->catfile($dir, "lib$libname.la")) {
				print "found $dir/lib$libname.la\n" if $verbose;
				return 1;
			}
			# if no .la, we accept _any_ .so version
			my @candidates = 
				(glob(File::Spec->catfile($dir, "lib$libname.so.*")),
				 glob(File::Spec->catfile($dir, "lib$libname.*dylib")));
			if (@candidates == 0) {
				print "not found\n" if $verbose;
				return undef;
			} else {
				print "found ", $candidates[0], "\n" if $verbose;
			}
		} else {
			print "bad spec\n" if $verbose;
			return undef;
		}
	}
	return 1;
}

sub solve_dependencies
{
	my $file = shift;
	my $pkgname;
	my %verify;
	my @lines;
	my $prefix;

	if (defined $ENV{'PKG_PREFIX'}) {
		$prefix = $ENV{'PKG_PREFIX'};
	}
	open(FILE, '<', $file);
	# Parse the old plist, scanning for what we want to handle only.
	while (<FILE>) {
		chomp;
		if (m/^\@name\s+/) {
			$pkgname=$';
		}
		elsif (m/^\@newdepend\s+/) {
			my ($name, $pattern, $def) = split(/\:/, $');
			unless (defined $verify{$name}) {
				$verify{$name} = [];
			}
			push(@{$verify{$name}}, [$pattern, $def]);
			push(@lines, "\@comment newdepend $name:$pattern:$def");
		} elsif (m/^\@libdepend\s+/) {
			my ($name, $libspec, $pattern, $def) = split(/\:/, $');
			unless (defined $verify{$name}) {
				$verify{$name} = [];
			}
			push(@{$verify{$name}}, [$pattern, $def, $libspec]);
			push(@lines, "\@comment libdepend $libspec:$name:$pattern:$def");
		} else {
			if (m/^\@cwd\s+/ && !defined $prefix) {
				$prefix = $';
			}
			push(@lines, $_);
		}
	}
	close(FILE);

	open FILE, '>', "$file";
	print FILE "\@name $pkgname\n";
	my @todo = ($pkgname);
	my %done = ();

	unless (chdir $vardb) {
		die "Directory $vardb absent\n";
	}
	my @list = glob '*';

	# create all the new pkgdep stuff

	for my $check (@todo) {
		print "pkg: Handling dependencies for $check\n" if $verbose;
		for my $dep (@{$verify{$check}}) {
			print " dependency on ", $dep->[0], " (default ",
			    $dep->[1], ") -> " if $verbose;
			my $r = pattern_match($dep->[0], \@list);
			if ($r) {
			    print "$r\n" if $verbose;
			} else {
			    print "Not found\n" if $verbose;
		    	}
			# library dependency check: if the libraries don't
			# match, the package found is bad. Revert to
			# the default package
			if (@{$dep} > 2) {
				unless (check_lib_specs($prefix, $dep->[2])) {
					print "  reverting to default -- this is bound to fail\n" if $verbose;
					$r = '';
				}
			}
			# unshift so that base dependencies happen first.
			if ($r) {
				unshift @lines, "\@pkgdep $r";
			} else {
				unshift @lines, "\@pkgdep ".$dep->[1];
				push @todo, $dep->[1] unless $done{$dep->[1]};
			}
		}
		$done{$check} = 1;
	}
	for my $l (@lines) {
		print FILE $l, "\n";
	}
	close FILE;
}

sub resolve_version
{
	return $_ if -d $_;
	my @l = glob("$_-[0-9]*");
	if (@l > 0) {
		return $l[0];
	} else {
		return undef;
	}
}

sub show_forward_dependencies
{
	my @l = @_;

	local $_;

	unless (chdir $vardb) {
		die "Directory $vardb absent\n";
	}

	@l = map(resolve_version, @l);

	my %known = map +($_,1), @l;

	open(OUT, "|tsort -f -r|tr '\012' '\040';echo");
	for my $p (@l) {
		print OUT "$p $p\n";
		if (open(DEPS, "$p/+REQUIRED_BY")) {
			while (<DEPS>) {
				chomp;
				print OUT "$p $_\n";
				unless ($known{$_}) {
				    push(@l, $_);
				    $known{$_} = 1;
				}
			}
			close DEPS;
		}
	}
	close OUT;
}

# Pass this off to the old package commands
my %legacy = map +($_, 1), qw{add info delete create};
my %opts;

getopts('v', \%opts);

$verbose = 1 if defined($opts{'v'});

if (@ARGV == 0) {
	die "needs arguments\n";
}

my $cmd = shift;

if (defined $legacy{$cmd}) {
	if (defined $opts{'v'}) {
		unshift(@ARGV, '-v');
	}
	exec { "pkg_$cmd"} ("pkg_$cmd", @ARGV);
} elsif ($cmd eq 'dependencies') {
	my $sub = shift;
	if ($sub eq 'check') {
		print "Warning: 'pkg dependencies check' is deprecated. ";
		print "Update bsd.port.mk.\n";
		if (check_dependencies(shift)) {
			exit(0);
		} else {
			exit(1);
		}
	} elsif ($sub eq 'solve') {
		solve_dependencies(shift);
		exit(0);
	} elsif ($sub eq 'show') {
		show_forward_dependencies(@ARGV);
		exit(0);
	}
	die "Bad dependency subcommand $sub\n";
}
die "Bad command $cmd\n";
