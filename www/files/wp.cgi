#!/usr/bin/perl -T
my $rcsid = '$MirOS: www/files/wp.cgi,v 1.3 2013/06/23 20:02:48 tg Exp $';
#-
# Copyright © 2013
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

use strict;
use warnings;

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

$query = "" unless $query =~ /^[0-9A-Za-z-]*$/;
$query =~ y/a-z/A-Z/;

if ($query ne "") {
	$query =~		s`\b(N[0-9][0-9A-F]{4}|(G[ACE]|O[BCKPSUXZ]|SH|[TL]C)[0-9A-Z]{1,5}|GD[A-Z]{2}-[A-Z]{4})\b`
					($query = $1) =~ /^GC/ ? "http://www.geocaching.com/seek/cache_details.aspx?wp=$query" :
					$query =~ /^GA/ ? "http://geocaching.com.au/cache/$query" :
					$query =~ /^GD/ ? "http://geodashing.gpsgames.org/cgi-bin/dp.pl?dp=$query" :
					$query =~ /^GE/ ? "http://geocaching.gpsgames.org/cgi-bin/ge.pl?wp=$query" :
					$query =~ /^N[0-9]/ ? sprintf("http://www.navicache.com/cgi-bin/db/displaycache2.pl?CacheID=%d", hex(substr($query, 1))) :
					$query =~ /^OB/ ? "http://www.opencaching.nl/viewcache.php?wp=$query" :
					$query =~ /^OC/ ? "http://www.opencaching.de/viewcache.php?wp=$query" :
					$query =~ /^OK/ ? "http://www.opencaching.org.uk/viewcache.php?wp=$query" :
					$query =~ /^OP/ ? "http://www.opencaching.pl/viewcache.php?wp=$query" :
					$query =~ /^OS/ ? "http://www.opencaching.se/viewcache.php?wp=$query" :
					$query =~ /^OU/ ? "http://www.opencaching.us/viewcache.php?wp=$query" :
					$query =~ /^OZ/ ? "http://www.opencaching.cz/viewcache.php?wp=$query" :
					$query =~ /^OX/ ? "http://www.opencaching.com/#!geocache/$query" :
					$query =~ /^SH/ ? "http://shutterspot.gpsgames.org/cgi-bin/sh.pl?wp=$query" :
					$query =~ /^[TL]C/ ? "http://www.terracaching.com/viewcache.cgi?ID=$query" :
					"";
				`eg;
	$found = 1 if $query =~ /http/;
}

$query = "https://www.mirbsd.org/wp.htm" unless $found;

print("Status: 301\r\nLocation: $query\r\n\r\nRedirect: $query\r\n");
exit(0);
