<small class="rcsid">$MirOS: www/content/Y2xvZy0yMDA1.inc,v 1.2 2005/02/05 22:43:38 tg Exp $</small>
<!--
 Full list of release focuses in freshmeat.net-compatible format:
	N/A
	Initial freshmeat announcement
	Documentation
	Code cleanup
	Minor feature enhancements
	Major feature enhancements
	Minor bugfixes
	Major bugfixes
	Minor security fixes
	Major security fixes
 -->
<h1>2005 snapshots of MirOS-current</h1>
<h3>Infos &ndash; <a href="#eof">bottom</a></h3>

<p id="snap0127">27.01.2005<br />Detailed list of changes from the <a
 href="#snap0122">2005/01/22 snapshot</a> below:</p><ul>
 <li>Compile entire system with <tt>-fno-unit-at-a-time</tt> to prevent
  possible gcc bugs and propolice interactions (still unresolved)</li>
 <li>Re-enable building a FLOPPY ramdisk</li>
 <li>Add back much stuff (ping, netcat, vnconfig, an-/wicontrol, nc
  and even dhclient) to the ramdisk floppy</li>
 <li>Add space at end of in-kernel leap second table, for overriding
  it after build in the binary</li>
 <li>Update ProPolice and gcc stuff with some OpenBSD diffs</li>
 <li>Install Reiser CPP as <tt>/usr/libexec/cpp</tt> (for X11)</li>
 <li>Update ssh, lint, kernel random device from OpenBSD</li>
 <li>Let lint use GNU cpp at <tt>/usr/bin/cpp</tt></li>
</ul><p>This bug-fix release addresses a few shortcomings which
 appeared after heavy-scale testing the 2005/01/22 snapshot as
 well as some bugs we discovered before but were unable to hunt
 down (ssh dumping core). There is a ports checkout in the torrent
 and download directory now, too.</p>

<p id="snap0122">22.01.2005<br />Detailed list of changes from the <a
 href="/?clog-2004#snap1129">2004/11/29 snapshot</a> below:</p><ul>
 <li>Large number of new or updated ports, e.g. bison</li>
 <li>Changed to gcc 3.4.4-20050121 with ProPolice</li>
 <li>Languages available: c proto gcov ada objc c++ java f77</li>
 <li>Runtimes available: c ada objc</li>
 <li>Supplementaries available: objc with boehm-gc; fastjar</li>
 <li>Updated CVS to 1.12.11</li>
 <li>Updated Lynx to 2.8.6dev.10-MirOS</li>
 <li>Updated Perl to 5.8.6</li>
 <li>Updated Sendmail to 8.13.3</li>
 <li>Updated binutils to 20050118</li>
 <li>Updated texinfo to 4.8</li>
 <li>Updated libpng to 1.2.8</li>
 <li>Updated rcs 5.7 to BSD build infrastructure</li>
 <li>Huge number of security and bugfix updates from OpenBSD, for
  example in the kernel (pf, networking, filesystems), ksh, ntpd, libc,
  diff, nc, disklabel, ssh, awk, httpd, bc, dc, libpthread, ld.so, sudo,
  libz, ...</li>
 <li>Added Kernel PPPoE support (with SyncPPP) from OpenBSD
  and ported NetBSD&trade; ifwatchd(8)</li>
 <li>Updated ISDN user-land supplementary utilities</li>
 <li>Prepared macppc port, fixed portability problems in progress</li>
 <li>Greatly unslacked code base</li>
 <li>Reduced diffs to OpenBSD (and other upstream) and XFree86&trade;</li>
 <li>Replaced GNU libreadline with libedit</li>
 <li>Fixed problems with time</li>
 <li>Made Openbsuxulator feature-complete except sysctl enumeration</li>
 <li>Spun out src/games/ to ports/games/bsdgames/</li>
 <li>Fixed bug in evilwm, making QWER work as documented</li>
</ul><p>This feature release focuses on reducing diffs to upstream in
 places where we have upstream releases (the BSDs, FSF, XF86) and
 modernising the upstream versions we use (except OpenBSD core, which
 is still at May 2004 state). There was also a huge number of removals
 for code cleanliness, and bug fixes for gcc 3.4.4 compatibility. This
 snapshot is a feature preview, but the first one worthy to be considered
 MirOS #8 pre-beta stage, leaving alpha stadium.</p>

<p id="eof">That's all for 2005, folks.</p>
