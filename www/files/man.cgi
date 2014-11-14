#!/usr/bin/perl -T
my $rcsid = '$MirOS: www/files/man.cgi,v 1.9 2014/07/15 22:19:19 tg Exp $';
#-
# Copyright © 2012, 2014
#	Thorsten Glaser <tg@mirbsd.org>
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
# CGI to search through MirBSD HTML manpages

use strict;
use warnings;

use File::Glob qw(:globally :nocase);

use File::Basename qw(dirname);
my ($mydir) = (dirname($0) =~ /(.*)/);	# untaint

if (!(
    (chdir($mydir)) &&
    (-r 'man.htm') &&
    (open(TEMPLATE, 'man.htm'))
    )) {
	print "Status: 500 Internal Script Error\r\n";
	print "Content-Type: text/plain\r\n\r\n";
	print "Cannot read template '" . $mydir . "/man.htm'!\r\n";
	exit(1);
}

my $canonical = "";
my @files = ();
my $gotmatch = 0;
my $match = "";
my $output = "";
my $query = "";
my $queryorig = "";
my %results = ();
my $stylesheet = "";

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

sub tohtml {
	local ($_) = @_;

	s/&/&#38;/g;
	s/</&#60;/g;
	s/>/&#62;/g;
	s/\"/&#34;/g;
	return $_;
}

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
		$gotmatch = 1 if $match =~ /\/man([1-9]|3p)\//;
	}
}

# $queryorig = "" ⇒ no search
# $query = "" ⇒ tell invalid query, offer ddg
# @files < 1 ⇒ tell no results, offer ddg
# ‣ display list of matches from %results as links
# $gotmatch = 1 ⇒ pull in $match (relative pathname), change $canonical and $stylesheet

my $ares = 4;				# no search
if ($queryorig ne "") {
	$ares = 1;			# no query
	if ($query ne "") {
		$ares = 2;		# no result
		if (@files > 0) {
			$ares = 3;	# got results
		}
	}
}

if ($ares == 1) {
	$output = "<h2>Invalid search query</h2>\n<p>Sorry, the query " .
	    "string “" . tohtml($queryorig) . "” contained invalid " .
	    "characters that cannot match a manpage name.</p>\n";
}
if ($ares == 2) {
	$output = "<h2>No results</h2>\n<p>Sorry, there were no results " .
	    "for “" . tohtml($query) . "” in our manual pages.</p>\n";
}
if ($ares < 3) {
	$output .= '<form accept-charset="utf-8" action="https://duckduckgo.com/?kp=-1&#38;kl=wt-wt&#38;kb=t&#38;kh=1&#38;kj=g2&#38;km=l&#38;ka=monospace&#38;ku=1&#38;ko=s&#38;k1=-1&#38;kv=1&#38;t=debian" method="post">';
	$output .= "<p>\n <input type=\"hidden\" name=\"q\" value=\"" .
	    "site:www.mirbsd.org/htman/ " . tohtml($queryorig) .
	    "\" /><input type=\"submit\" value=\"Search again for: " .
	    tohtml($queryorig) . "\" />\n</p></form>\n";
	$output .= "<p>DuckDuckGo is a search engine that protects privacy " .
	    "and has lots of\n features. This search is external content, " .
	    "not part of MirOS, although it searches through our pages.</p>\n";
}
if ($ares == 3) {
	$output = "<h2>Results for " . tohtml($query) . "</h2>\n";
	if ($gotmatch) {
		$output .= "<p>Jump to the <a href=\"#direct\">direct " .
		    "match for " . tohtml($query) . "</a></p>\n";
	}
	$output .= "<ul>\n";
	my @res = sort keys %results;
	foreach my $k (grep(!/^INFO/, @res)) {
		my $a = $results{$k};
		my ($s, $n) = split /\//, $k, 2;
		my $x = $k . ".htm";
		if ($a eq '-') {
			$output .= " <li><a href=\"htman/i386/man" . $x .
			    "\">" . $n . "(" . $s . ")</a></li>\n";
			next;
		}
		$_ = $a;
		my @aa = split;
		foreach my $r (@aa) {
			$output .= " <li><a href=\"htman/" . $r . "/man" . $x .
			    "\">" . $n . "(" . $s . "/" . $r . ")</a></li>\n";
		}
	}
	foreach my $k (grep(/^INFO/, @res)) {
		my $a = $results{$k};
		my ($s, $n) = split /\//, $k, 2;
		$s = "GNU";
		my $x = $k . ".html";
		if ($a eq '-') {
			$output .= " <li><a href=\"htman/i386/man" . $x .
			    "\">" . $n . "(" . $s . ")</a></li>\n";
			next;
		}
		$_ = $a;
		my @aa = split;
		foreach my $r (@aa) {
			$output .= " <li><a href=\"htman/" . $r . "/man" . $x .
			    "\">" . $n . "(" . $s . "/" . $r . ")</a></li>\n";
		}
	}
	$output .= "</ul>\n";
}
if ($gotmatch && !open(MATCHPAGE, $match)) {
	$output .= "<p id=\"direct\">Matching manual page “" . $match .
	    "” found, but cannot be opened. ☹</p>\n";
	$gotmatch = 0;
}
if ($gotmatch) {
	$output .= "<h2 id=\"direct\">Matching manual page</h2>\n<div " .
	    "class=\"manbody\" style=\"padding:6px; line-height:100%;\">\n\n";
	my $state = 0;
	my $matchparentdir = dirname(dirname($match));
	# drop next line once roff2htm,v 1.74 was used globally
	my $matchdir = dirname($match);
	foreach my $line (<MATCHPAGE>) {
		chomp($line);
		if ($state == 0) {
			if ($line eq '</head><body>') {
				$state = 1;
				next;
			}
			if ($line =~ /<link rel=["]canonical["]/) {
				$canonical = $line;
				next;
			}
			if ($line =~ /<style[\s>]/) {
				$state = 2;
			}
		}
		if ($state == 1) {
			if ($line eq '</body></html>') {
				$state = 9;
				next;
			}
			$line =~ s/(<\/?)h1\b/$1h6/g;
			$line =~ s# href="\.\./# href="$matchparentdir/#g;
			# drop next line once roff2htm,v 1.74 was used globally
			$line =~ s# href="([^/"]+)"# href="$matchdir/$1"#g;
			$output .= $line . "\n";
		}
		if ($state == 2) {
			if ($line =~ /\bbody\b.*[{]/) { #}
				$line =~ s/\bbody\b/.manbody/;
			}
			if ($line =~ /\b(a|a:[a-z]+|h[23])\b.*[{]/) { #}
				$line =~ s/\b(a|a:[a-z]+|h[23])\b/.manbody $&/;
			}
			if ($line =~ /\bh1\b.*[{]/) { #}
				$line =~ s/\bh1\b/.manbody h6/;
				$line .= "\n\tmargin:12px 0px;";
				$line .= "\n\tline-height:132%;";
			}
			$stylesheet .= $line . "\n";
			if ($line =~ /<\/style>/) {
				$state = 0;
			}
		}
	}
	close(MATCHPAGE);
	$output .= "\n</div><!-- .manbody -->\n";
}

print "Content-Type: text/html; charset=utf-8\r\n\r\n";
foreach my $line (<TEMPLATE>) {
	chomp($line);

	if ($gotmatch) {
		if (($canonical ne '') &&
		    ($line =~ /<link rel=["]canonical["]/)) {
			$line = $canonical;
		}
		if (($stylesheet ne '') &&
		    ($line eq '</head><body>')) {
			print $stylesheet;
		}
	}

	if ($line eq '<!-- man-result -->') {
		print $output;
		next;
	}

	if ($line =~ /rcsdiv.*rcsid/) {
		$line =~ s!\Q</p>\E! by <span class=\"rcsid\">$rcsid</span>$&!;
	}
	print $line . "\n";
}
close(TEMPLATE);
exit(0);
