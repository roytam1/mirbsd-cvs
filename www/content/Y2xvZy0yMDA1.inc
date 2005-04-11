<small class="rcsid">$MirOS: www/content/Y2xvZy0yMDA1.inc,v 1.3 2005/03/15 21:49:08 tg Exp $</small>
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

<p id="snap0330">30.03.2005<br />Detailed list of changes from the <a
 href="#snap0127">2005/01/27 snapshot</a> below:</p><ul>
 <li>Major bug-hunting season in *roff macros to improve our
  documentation in both catman and HTML format</li>
 <li>Display fixes regarding links in HTML-format documentation</li>
 <li>Major improvements regarding source integrity and much reduced
  cvs checkout time</li>
 <li>More reliability and flexibility in the overall infrastructure,
  including parts shared with portable MirMake and the new MirCPIO
  and related framework; added support for compiling Objective-C;
  shortcut for building the whole system at once</li>
 <li>Releases are now 100% built under systrace(1) quality control</li>
 <li>Portability improvements in MirMake</li>
 <li>Build RCS, less and sudo using BSD make</li>
 <li>Minor security and reliability fixes in system software (kernel
  and support libraries), some from OpenBSD, some detected by our
  superiour build infrastructure</li>
 <li>sendmail now defaults to ISO-8859-1 in the submission agent</li>
 <li>Update MirLibtool to most recent version of GNU Libtool and
  fix pthreads and relinking related bugs; reduce vendor diff</li>
 <li>Update X11 subsystem to the latest <a
  href="http://www.xfree86.org/">XFree86&reg; 4.5.0</a> release</li>
 <li>Update GCC to 3.4-20050325; binutils mainline-20050328</li>
 <li>Languages available: c proto gcov ada objc c++ java pascal</li>
 <li>Runtimes available: c ada objc pascal c++(broken)</li>
 <li>Supplementaries available: objc with boehm-gc; pascal</li>
 <li>Updated Lynx to 2.8.6dev.11i</li>
 <li>MirPorts now work on MirOS BSD 7 and up, OpenBSD 3.4 and up
  and Mac OSX (most versions; probably also (Open)Darwin)</li>
</ul><p>This release includes major feature enhancements and enables
 users to develop against a system which is very similar to what will
 be released as MirOS #8, already at this time, although C++ support is
 still broken. It also addresses overall stability, security, integrity,
 performance and portability issues and features a lot more subprojects
 and better integration into a common Unix&reg; environment. Users are
 urged to update to this snapshot as soon as possible if they are running
 a 2005/01 snapshot, and as soon as feasible if they are running a 2004/11
 snapshot.<br />The next snapshot will be a major security release, because
 this snapshot concentrated on integrating the whole CVS repository into a
 new, overall better, build system and enabling as many features as we
 could with the existing source code, as well as getting the damn thing out
 of our doors, leaving no time to pick and test the security and bug fixes
 from OpenBSD and other upstream vendors.</p>

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
