#!/usr/bin/perl -T
my $rcsid = '$MirOS: www/files/wp.cgi,v 1.18 2015/10/16 18:15:46 tg Exp $';
#-
# Copyright © 2013, 2014, 2015
#	mirabilos <tg@mirbsd.org>
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

use strict;
use warnings;

sub htmlencode($) {
	local ($_) = @_;

	s/&/&amp;/g;
	s/</&lt;/g;
	s/>/&gt;/g;
	s/\"/&#34;/g;

	return $_;
}

sub redirect($) {
	my ($dst) = @_;
	my $enc = htmlencode($dst);

	print("Status: 301\r\nLocation: $dst\r\n");
	print("Content-type: text/html\r\n\r\n");
	print("<html><head><title>Redirection</title></head><body>\n");
	print("<h1>Redirection</h1>\n");
	print("<p>Please visit <a href=\"$enc\">$enc</a> instead!</p>\n");
	print("</body></html>\n");
	exit(0);
}

my $output = "";
my $query = "";
my $found = 0;

if (defined($ENV{QUERY_STRING})) {
	for my $p (split(/[;&]+/, $ENV{QUERY_STRING})) {
		next unless $p;
		$p =~ y/+/ /;
		my ($key, $val) = split(/=/, $p, 2);
		next unless defined($key);

		next unless ($key eq "q");
		next unless defined($val);
		$val =~ s/%([0-9A-Fa-f][0-9A-Fa-f])/chr(hex($1))/eg;
		next if $val =~ /[\t\r\n]/;
		$query = $val;
	}
	if ($query eq "") {
		my $p = $ENV{QUERY_STRING};
		$p =~ y/+/ /;
		$p =~ s/%([0-9A-Fa-f][0-9A-Fa-f])/chr(hex($1))/eg;
		next if $p =~ /[\t\r\n]/;
		$query = $p;
	}
}

# ltrim and rtrim
$query =~ s/^\s+//;
$query =~ s/\s+$//;

if ($query =~ m!^(m/[0-9A-Za-z_-]*/[0-9]+)/?$!) {
	&redirect("https://www.munzee.com/$1/");
}

$query = "" unless $query =~ /^[0-9A-Za-z_-]*$/;
$query =~ y/a-z/A-Z/;

if ($query ne "") {
	$query =~		s@\b(N[0-9][0-9A-F]{4}|(EC|G[ACEGL]|O[BCKPSUXZ]|PR|SH|[TLC]C|WM)[0-9A-Z]{1,6}|(GD|VX)[0-9A-Z]{2}-[A-Z]{4}|2[0-9]{3}-(0[1-9]|1[0-2])-[0-3][0-9]_(-?[0-9]{1,2}_-?[0-9]{1,3}|GLOBAL))\b@
					($query = $1) =~ /^GC/ ? "http://www.geocaching.com/seek/cache_details.aspx?wp=$query" :
					$query =~ /^EC/ ? sprintf("http://extremcaching.com/index.php/output-2/%s", substr($query, 2)) :
					$query =~ /^GA/ ? "http://geocaching.com.au/cache/$query" :
					$query =~ /^GD/ ? "http://geodashing.gpsgames.org/cgi-bin/dp.pl?dp=$query" :
					$query =~ /^GE/ ? "http://geocaching.gpsgames.org/cgi-bin/ge.pl?wp=$query" :
					$query =~ /^GG/ ? "http://golf.gpsgames.org/cgi-bin/golf.pl?course=$query&coursedetails=Go" :
					$query =~ /^(GL|PR)/ ? "http://coord.info/$query" :
					$query =~ /^N[0-9]/ ? sprintf("http://www.navicache.com/cgi-bin/db/displaycache2.pl?CacheID=%d", hex(substr($query, 1))) :
					$query =~ /^OB/ ? "http://www.opencaching.nl/viewcache.php?wp=$query" :
					$query =~ /^OC/ ? "http://www.opencaching.de/viewcache.php?wp=$query" :
					$query =~ /^OK/ ? "http://www.opencaching.org.uk/viewcache.php?wp=$query" :
					$query =~ /^OP/ ? "http://www.opencaching.pl/viewcache.php?wp=$query" :
					$query =~ /^OS/ ? "http://www.opencaching.se/viewcache.php?wp=$query" :
					$query =~ /^OU/ ? "http://www.opencaching.us/viewcache.php?wp=$query" :
					$query =~ /^OZ/ ? "http://www.opencaching.cz/viewcache.php?wp=$query" :
					$query =~ /^SH/ ? "http://shutterspot.gpsgames.org/cgi-bin/sh.pl?wp=$query" :
					$query =~ /^[TLC]C/ ? "http://play.terracaching.com/Cache/$query" :
					$query =~ /^VX/ ? "http://geovexilla.gpsgames.org/cgi-bin/vx.pl?listwaypointlogs=yes&wp=$query" :
					$query =~ /^WM/ ? "http://www.waymarking.com/waymarks/$query" :
					$query =~ /^2/ ? "http://wiki.xkcd.com/geohashing/$query" :
					"";
				@eg;
	$found = 1 if $query =~ /http/;
}

$query = "https://www.mirbsd.org/wp.htm" unless $found;
&redirect($query);
