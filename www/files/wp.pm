my $rcsid = '$MirOS: www/files/wp.pm,v 1.1 2018/08/29 01:19:11 tg Exp $';
#-
# Copyright © 2018
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

use strict;
use warnings;

# generic HTML encode (&<>" but not ')
sub htmlencode($) {
	local ($_) = @_;

	s/&/&amp;/g;
	s/</&lt;/g;
	s/>/&gt;/g;
	s/\"/&#34;/g;

	return $_;
}

# generic HTML and HTTP redirect
sub redirect($) {
	my ($dst) = @_;
	my $enc = htmlencode($dst);

	print("Status: 301\r\nLocation: $dst\r\n");
	print("Content-Type: text/html; charset=UTF-8\r\n\r\n");
	print("<html><head><title>Redirection</title></head><body>\n");
	print("<h1>Redirection</h1>\n");
	print("<p>Please visit <a href=\"$enc\">$enc</a> instead!</p>\n");
	print("</body></html>\n");
	exit(0);
}

# generic Y-M-D date validity checker
sub chkdate($$$) {
	my ($y, $m, $d) = @_;
	my @mdays = (0,31,28,31,30,31,30,31,31,30,31,30,31);

	$mdays[2] = (($y % 4) == 0 && (($y % 100) != 0 || ($y % 400) == 0)) ?
	    29 : 28 if ($m == 2);

	return !($y < 1 || $y > 9999 || $m < 1 || $m > 12 || $d < 1 ||
	    $d > $mdays[$m]);
}

# generic waypoint code exploder (classifyer, label, URL)
sub explwp($) {
	my ($wp) = @_;
	return ("BC", "BesserCacher#$1", "https://bessercacher.de/forum/viewtopic.php?t=$1") if
	    ($wp =~ m!^BC(\d+)$!);
	return ("EC", "$wp", "http://extremcaching.com/index.php/output-2/$1") if
	    ($wp =~ m!^EC(\d+)$!);
	return ("GA", "$wp", "https://geocaching.com.au/cache/$wp") if
	    ($wp =~ m!^GA[0-9A-Z]{1,6}$!);
	return ("GC", "$wp", "https://www.geocaching.com/seek/cache_details.aspx?wp=$wp") if
	    ($wp =~ m!^GC[0-9A-Z]{1,6}$!);
	return ("GD", "$wp", "http://geodashing.gpsgames.org/cgi-bin/dp.pl?dp=$wp") if
	    ($wp =~ m!^GD[0-9A-Z]{2}-[A-Z]{4}$!);
	return ("GE", "$wp", "http://geocaching.gpsgames.org/cgi-bin/ge.pl?wp=$wp") if
	    ($wp =~ m!^GE[0-9A-Z]{1,6}$!);
	return ("GG", "$wp", "http://golf.gpsgames.org/cgi-bin/golf.pl?course=$wp&coursedetails=Go") if
	    ($wp =~ m!^GG[0-9A-Z]{1,6}$!);
	return ("GK", "$wp", "https://geokrety.org/konkret.php?id=" . hex($1)) if
	    ($wp =~ m!^GK([0-9A-F]+)$!);
	return ("GL", "$wp", "http://coord.info/$wp") if
	    ($wp =~ m!^GL[0-9A-Z]{1,6}$!);
	return ("NC", "$wp", "http://www.navicache.com/cgi-bin/db/displaycache2.pl?CacheID=" . hex($1)) if
	    ($wp =~ m!^N([0-9][0-9A-F]{4})$!);
	return ("OB", "$wp", "https://www.opencaching.nl/viewcache.php?wp=$wp") if
	    ($wp =~ m!^OB[0-9A-Z]{1,6}$!);
	return ("OC", "$wp", "https://www.opencaching.de/viewcache.php?wp=$wp") if
	    ($wp =~ m!^OC[0-9A-Z]{1,6}$!);
	return ("OK", "$wp", "https://opencache.uk/viewcache.php?wp=$wp") if
	    ($wp =~ m!^OK[0-9A-Z]{1,6}$!);
	return ("OP", "$wp", "https://opencaching.pl/viewcache.php?wp=$wp") if
	    ($wp =~ m!^OP[0-9A-Z]{1,6}$!);
	return ("OR", "$wp", "https://www.opencaching.ro/viewcache.php?wp=$wp") if
	    ($wp =~ m!^OR[0-9A-Z]{1,6}$!);
	return ("OU", "$wp", "http://www.opencaching.us/viewcache.php?wp=$wp") if
	    ($wp =~ m!^OU[0-9A-Z]{1,6}$!);
	return ("OZ", "$wp", "https://opencaching.cz/viewcache.php?wp=$wp") if
	    ($wp =~ m!^OZ[0-9A-Z]{1,6}$!);
	return ("PR", "$wp", "http://coord.info/$wp") if
	    ($wp =~ m!^PR[0-9A-Z]{1,6}$!);
	return ("SH", "$wp", "http://shutterspot.gpsgames.org/cgi-bin/sh.pl?wp=$wp") if
	    ($wp =~ m!^SH[0-9A-Z]{1,6}$!);
	return ("TB", "$wp", "https://www.geocaching.com/track/details.aspx?tracker=$wp") if
	    ($wp =~ m!^TB[0-9A-Z]{1,6}$!);
	return ("TC", "$wp", "https://play.terracaching.com/Cache/$wp") if
	    ($wp =~ m!^[TLC]C[0-9A-Z]{1,6}$!);
	return ("VX", "$wp", "http://geovexilla.gpsgames.org/cgi-bin/vx.pl?listwaypointlogs=yes&wp=$wp") if
	    ($wp =~ m!^VX[0-9A-Z]{2}-[A-Z]{4}$!);
	return ("WM", "$wp", "http://www.waymarking.com/waymarks/$wp") if
	    ($wp =~ m!^WM[0-9A-Z]{1,6}$!);
	return ("m/", "$1", "https://www.munzee.com/$1/") if
	    ($wp =~ m!^(m/[0-9A-Za-z_-]*/[0-9]+)/?$!);
	return ("gh", "$wp", "http://wiki.xkcd.com/geohashing/$wp") if
	    ($wp =~ m!^(2[0-9]{3})-(0[1-9]|1[0-2])-([0-2][1-9]|[1-3][01])_(-?[0-9]{1,2})_(-?[0-9]{1,3})$! &&
	    chkdate($1, $2, $3) && $4 >= -90 && $4 <= 90 && $5 >= -180 && $5 <= 180);
	return ("Gh", "$wp", "http://wiki.xkcd.com/geohashing/$wp") if
	    ($wp =~ m!^(2[0-9]{3})-(0[1-9]|1[0-2])-([0-2][1-9]|[1-3][01])_global$! &&
	    chkdate($1, $2, $3));
	return ("", "$wp", "");
}

# substitution function; define a “chkwp” function to use this; skips Munzees
sub substwps($) {
	my ($s) = @_;

	$s =~ s@\b([BE]C\d+|(?:G[ACEGL]|O[BCKPRUZ]|PR|SH|TB|[TLC]C|WM)[0-9A-Z]{1,6}|(?:GD|VX)[0-9A-Z]{2}-[A-Z]{4}|(?:GK|N)[0-9A-F]+|2[0-9]{3}-[0-9]{2}-[0-9]{2}_(?:-?[0-9]{1,2}_-?[0-9]{1,3}|global))\b@chkwp($1)@eg;
	return $s;
}

1;
