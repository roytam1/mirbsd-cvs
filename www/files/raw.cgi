#!/usr/bin/perl -T
# $MirOS: www/files/raw.cgi,v 1.11 2015/12/27 02:25:09 tg Exp $
#-
# Copyright © 2012, 2014, 2015
#	mirabilos <m@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.
#-
# CGI to search through MirBSD HTML manpages and acronyms, for bots.

use strict;
use warnings;

use File::Glob qw(:globally :nocase);

use File::Basename qw(dirname);
my ($mydir) = (dirname($0) =~ /(.*)/);	# untaint

use File::Spec::Functions qw(catfile);
my $db = catfile($mydir, 'acronyms');

if ((-r $db) && (open(ACRONYMS, $db))) {
	undef $mydir;
} else {
	print "Status: 500 Internal Script Error\r\n";
	print "Content-Type: text/plain\r\n\r\n";
	print "Cannot read acronyms database '" . $db . "'!\r\n";
	exit(1);
}

my @files = ();
my $match = "";
my $query = "";
my $queryorig = "";
my %results = ();
my @wtfresults = ();

if (defined($ENV{QUERY_STRING})) {
	for my $p (split(/[;&]+/, $ENV{QUERY_STRING})) {
		next unless $p;
		$p =~ y/+/ /;
		my ($key, $val) = split(/=/, $p, 2);
		next unless defined($key);

		next unless ($key eq "q");
		next unless defined($val);
		$val =~ s/%([0-9A-Fa-f][0-9A-Fa-f])/chr(hex($1))/eg;
		$queryorig = $val;
	}
	if ($queryorig eq "") {
		my $p = $ENV{QUERY_STRING};
		$p =~ y/+/ /;
		$p =~ s/%([0-9A-Fa-f][0-9A-Fa-f])/chr(hex($1))/eg;
		$queryorig = $p unless $p =~ /^(.*[;&])?q=([;&].*)?$/;
	}

	# ltrim and rtrim
	$queryorig =~ s/^\s+//;
	$queryorig =~ s/\s+$//;

	$query = $queryorig unless $queryorig =~ /[^0-9A-Za-z+.:_-]/;
}

if ($queryorig ne "") {
	$queryorig =~ y/a-z/A-Z/;
	$queryorig =~ y/.//d if $queryorig =~ /[A-Z]\./;
	$queryorig =~ s/à/À/g;
	$queryorig =~ s/á/Á/g;
	$queryorig =~ s/ä/Ä/g;
	$queryorig =~ s/å/Å/g;
	$queryorig =~ s/æ/Æ/g;
	$queryorig =~ s/ç/Ç/g;
	$queryorig =~ s/è/È/g;
	$queryorig =~ s/é/É/g;
	$queryorig =~ s/í/Í/g;
	$queryorig =~ s/ð/Ð/g;
	$queryorig =~ s/ñ/Ñ/g;
	$queryorig =~ s/ó/Ó/g;
	$queryorig =~ s/ö/Ö/g;
	$queryorig =~ s/ø/Ø/g;
	$queryorig =~ s/ü/Ü/g;
	$queryorig =~ s/þ/Þ/g;
	$queryorig =~ s/ą/Ą/g;
	$queryorig =~ s/ć/Ć/g;
	$queryorig =~ s/ĉ/Ĉ/g;
	$queryorig =~ s/č/Č/g;
	$queryorig =~ s/đ/Đ/g;
	$queryorig =~ s/ę/Ę/g;
	$queryorig =~ s/ĝ/Ĝ/g;
	$queryorig =~ s/ĥ/Ĥ/g;
	$queryorig =~ s/ĵ/Ĵ/g;
	$queryorig =~ s/ł/Ł/g;
	$queryorig =~ s/ń/Ń/g;
	$queryorig =~ s/ś/Ś/g;
	$queryorig =~ s/ŝ/Ŝ/g;
	$queryorig =~ s/š/Š/g;
	$queryorig =~ s/ŭ/Ŭ/g;
	$queryorig =~ s/ź/Ź/g;
	$queryorig =~ s/ż/Ż/g;
	$queryorig =~ s/ž/Ž/g;
	$queryorig =~ s/ε/Ε/g;
	$queryorig =~ s/λ/Λ/g;
	$queryorig =~ s/ο/Ο/g;
	$queryorig =~ s/ς/Σ/g;
	$queryorig =~ s/σ/Σ/g;
	$queryorig =~ s/а/А/g;
	$queryorig =~ s/б/Б/g;
	$queryorig =~ s/г/Г/g;
	$queryorig =~ s/д/Д/g;
	$queryorig =~ s/е/Е/g;
	$queryorig =~ s/з/З/g;
	$queryorig =~ s/й/Й/g;
	$queryorig =~ s/к/К/g;
	$queryorig =~ s/л/Л/g;
	$queryorig =~ s/м/М/g;
	$queryorig =~ s/н/Н/g;
	$queryorig =~ s/о/О/g;
	$queryorig =~ s/р/Р/g;
	$queryorig =~ s/с/С/g;
	$queryorig =~ s/т/Т/g;
	$queryorig =~ s/у/У/g;
	$queryorig =~ s/ф/Ф/g;
	$queryorig =~ s/қ/Қ/g;
	$queryorig =~ s/ա/Ա/g;
	$queryorig =~ s/հ/Հ/g;
	$queryorig =~ s/յ/Յ/g;

	foreach my $line (<ACRONYMS>) {
		chomp($line);
		if ($line =~ /^\Q$queryorig	\E(.*)$/) {
			push(@wtfresults, $1);
		}
	}
}
close(ACRONYMS);

if ($query ne "") {
	if (length($query) < 3) {
		@files = <htman/*/man[1-9]/{,.}${query}*.htm>;
		my @f;
		@f = <htman/*/man{3p,PSD,SMM,USD,PAPERS}/${query}*.htm>;
		push @files, @f if (@f > 0);
		@f = <htman/*/man{PSD,SMM,USD,PAPERS}/*.${query}*.htm>;
		push @files, @f if (@f > 0);
		@f = <htman/*/manINFO/${query}*.html>;
		push @files, @f if (@f > 0);
	} else {
		@files = <htman/*/man[1-9]/{,.}*${query}*.htm>;
		my @f;
		@f = <htman/*/man{3p,PSD,SMM,USD,PAPERS}/*${query}*.htm>;
		push @files, @f if (@f > 0);
		@f = <htman/*/manINFO/*${query}*.html>;
		push @files, @f if (@f > 0);
	}
}

if (@files > 0) {
	my @filesort = ();

	foreach my $a (qw( i386 sparc )) {
		# from MirOS: src/etc/man.conf,v 1.5 2009/07/18 14:09:03 tg Exp $
		foreach my $o (qw( 1 8 6 2 3 5 7 4 9 3p
		    PSD SMM USD PAPERS INFO )) {
			my @filtered = grep /^htman\/\Q$a\E\/man\Q$o\E\//,
			    @files;
			if (@filtered > 0) {
				push @filesort, @filtered;
			}
		}
	}

	my %pnino = ();
	my %inoseen = ();
	@files = ();

	foreach my $fn (@filesort) {
		my $ino = (stat($fn))[1];

		next unless (-r _ && -f _ && -s _);

		my ($a, $k) = $fn =~
		    /^htman\/([^\/]*)\/man([^\/]*\/.*)[.]html?$/;
		$results{$k} .= $a . ' ';

		if ($ino) {
			if ($inoseen{$ino}) {
				my $bn = $fn;
				$bn =~ s/^.*\///g;
				my @inomatches = grep {
					$pnino{$_} == $ino
				    } keys %pnino;
				s/^.*\///g for @inomatches;
				my $inomatched = grep {
					$_ eq $bn
				    } @inomatches;
				next if ($inomatched > 0);
			} else {
				$inoseen{$ino} = 1;
			}
			$pnino{$fn} = $ino;
		}
		push @files, $fn;
	}

	foreach my $k (keys %results) {
		$_ = $results{$k};
		my @a = split;
		if (@a < 1) {
			# should not happen
			$results{$k} = '-';
			next;
		}
		if (@a < 2) {
			$results{$k} = $a[0];
			next;
		}
		# both i386 and sparc: duplicates or no?
		@a = grep /man\Q$k\E[.]html?$/, @files;
		if (@a < 2) {
			$results{$k} = '-';
		} else {
			$results{$k} = 'i386 sparc';
		}
	}

	my @goodmatches;
	@goodmatches = grep /\/\Q$query\E[.]htm$/, @files;
	if (@goodmatches < 1) {
		@goodmatches = grep /\/\Q$query\E[.]htm$/i, @files;
	}
	if (@goodmatches > 0) {
		$match = $goodmatches[0];
	}
}

if (@files > 0) {
	my @res = sort keys %results;
	foreach my $k (grep(!/^INFO/, @res)) {
		my $a = $results{$k};
		my ($s, $n) = split /\//, $k, 2;
		my $x = $k . ".htm";
		if ($a eq '-') {
			push(@wtfresults, "http://www.mirbsd.org/man" . $x);
			next;
		}
		$_ = $a;
		my @aa = split;
		foreach my $r (@aa) {
			push(@wtfresults, "http://www.mirbsd.org/htman/" . $r . "/man" . $x);
		}
	}
	foreach my $k (grep(/^INFO/, @res)) {
		my $a = $results{$k};
		my ($s, $n) = split /\//, $k, 2;
		$s = "GNU";
		my $x = $k . ".html";
		if ($a eq '-') {
			push(@wtfresults, "http://www.mirbsd.org/man" . $x);
			next;
		}
		$_ = $a;
		my @aa = split;
		foreach my $r (@aa) {
			push(@wtfresults, "http://www.mirbsd.org/htman/" . $r . "/man" . $x);
		}
	}
}

print "Content-Type: text/plain; charset=utf-8\r\n\r\n";

foreach my $line (@wtfresults) {
	print $line . "\r\n";
}

exit(0);
