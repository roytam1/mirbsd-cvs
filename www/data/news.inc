Title: Some bad CDs distributed on FOSDEM
Date: 27.03.2006

<p>In case you have acquired a MirOS CD-ROM "FOSDEM 2006"
 edition please verify the checksums of the data on the CD. Some of
 the CDs we distributed at FOSDEM were burned from a bad ISO.</p>
----
Title: MirOS #9 released
Date: 01.04.2006

<p><a href="/?ann-9">MirOS #9</a> is available via our <a
 href="http://f.scarywater.net/miros/">BitTorrent tracker</a>. There is
 also an <a href="@@RELPATH@@MirOS/v9/">HTTP(S)</a> download/netinstall
 option.</p>
<p>Please read the <a href="/?errata">errata</a>.</p>
----
Title: New web server
Date: 05.07.2006

<p>We changed our web server. The former mirsolutions server is no longer.
 gecko2 hosts the box behind www.mirbsd.org now. waldi's
 Zope is still operational and helps a lot.</p>
----
Title: MirPorts heads-up
Date: 25.07.2006

<p>Due to the introduction of a new ld wrapper, you will have to re-do
 "make setup" (or a similar command line) after updating the infrastructure
 from CVS.</p>
----
Title: mksh R28 released
Date: 01.09.2006

<p>The <a href="http://mirbsd.de/mksh">MirBSD Korn Shell</a> R28 has
 been released. An upgrade is highly recommended.</p>
----
Title: MirOS #9-current (i386) snapshot: Security Fix
Date: 04.10.2006

<p>The <a href="http://f.scarywater.net/miros/">BitTorrent
 Tracker</a> offers a Live and Install CD ISO image of the
 current development branch for download. This snapshot contains
 security fixes for at least OpenSSL, OpenSSH, httpd, the kernel,
 as well as bugfixes for ftp, lynx, and many others.</p>
----
Title: mksh R29f released
Date: 26.05.2007

<p>mksh R29f is a bugfix release. It fixes some horizontal scrolling
 bugs discovered by David Ramsey. Thanks a lot!</p>
----
Title: MirOS project at Linuxtag 2007
Date: 01.06.2007

<p>We are present in a joint booth with AllBSD.de on Linuxtag 2007
 in Berlin, Germany. The booth is located right at the entrance. Live
 CDs are out, alas.</p>
----
Title: New look and feel
Date: 03.06.2007
Author: tg@

<p>Some of you might have noticed the new look &amp; feel creeping onto
 a few of these pages. Well, after LinuxTag (it was a success, but not
 like they say in their press announcements, I'm rather laughing at these)
 and <a href="http://www.cul.de/freex.html">FreeX</a>, whose latest issue
 has an interesting article about MirOS BSD, and with mksh(1) getting more
 and more popular, I decided to skip on sleep and fun today and continue
 hacking on what I had already done for the website. Mostly content today.
 The <a href="@@RELPATH@@mksh.htm">MirBSD Korn Shell</a> page got completely rewritten.
 If you find something, tell me. The theme will probably stay similar like
 the current one, not like <a href="/newsite/">Benny's</a>, but the index
 on the left will look totally different in some days. I'm only migrating
 (very) few of the old content. At the moment, “main”, “news”, “mksh” and
 “wlog-9” are converted, and the old CMS has been hacked for transparent
 migration to the new CMS (“mws”) using HTTP 301 redirects. Same goes for
 manual pages (/manN/ -&gt; /cman/manN/) to save space on search engines'
 hard disc drives. Finally, news and wlog now have permalinks (beta).</p>
<p>UPDATE (02.10.2007): Manpages now have better md redirects, and you can
 use various syntaxes, including /man/foo.1 or /man{i386,sparc}/bar.8</p>
<p>&#x60e3;&#x6d41;&#x30fb;&#x30a2;&#x30b9;&#x30ab;&#x30fb;&#x30e9;&#x30f3;&#x30b0;&#x30ec;&#x30fc;
 (well, just call him Soryu) and NetBSD®'s Stefan Schumacher have taken
 photographs of the MirOS team (the Duo Benny and me, Przemysław who run
 the booth as a mere user, and Much, whose new notebook got freshly set
 up, but who already knows how to like MirOS with evilwm); I'll put them
 up here once I get access to all of them.</p>
<p>Because we ran out of CDs, we put the ISO 9660 image on the <a
 href="http://f.scarywater.net/miros/">BitTorrent tracker</a>; please
 only redistribute it on CDs, DVDs or USB Sticks in order to comply with
 the licence of the Opera© browser included. You can, of course, also simply
 do a <a href="http://www.mirbsd.org/MirOS/current/">netinstall</a>.</p>
<p><strong>Update:</strong> the pictures are here!</p>
<table width="100%">
 <tr><td style="width:128px;"><a
  href="@@RELPATH@@pics/LinuxTag_2007/benz-wrk.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/benz-wrk.png" alt="[image]" /></a></td><td>
  Benny bei der Arbeit (benz at work)
 </td></tr>
 <tr><td style="width:128px;"><a
  href="@@RELPATH@@pics/LinuxTag_2007/d-benz.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/d-benz.png" alt="[image]" /></a></td><td>
  Dæmonische Bilder: Benny (benz, Developer) – bsiegert@
 </td></tr>
 <tr><td style="width:128px;"><a
  href="@@RELPATH@@pics/LinuxTag_2007/d-mira.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/d-mira.png" alt="[image]" /></a></td><td>
  Dæmonische Bilder: Thorsten (mira, Developer) – tg@
 </td></tr>
 <tr><td style="width:128px;"><a
  href="@@RELPATH@@pics/LinuxTag_2007/d-zeno.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/d-zeno.png" alt="[image]" /></a></td><td>
  Dæmonische Bilder: Przemysław (zeno, User &amp; Booth Staff) – przemek@
 </td></tr>
 <tr><td style="width:128px;"><a
  href="@@RELPATH@@pics/LinuxTag_2007/groupies.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/groupies.png" alt="[image]" /></a></td><td>
  Benny, Przemek, mira and much, whose laptop just got freshly installed…
 </td></tr>
</table>
<p>The last picture was made by Stefan Schumacher, thanks!</p>
----
Title: mksh improves portability
Date: 05.06.2007

<p>The MirBSD Korn Shell (<a href="@@RELPATH@@mksh.htm">mksh</a>) now can
 not only be built by the GNU Compiler Collection, egcs/gcc 2.95, the GNU
 C Compiler 2.7.2.3, and the (quite gcc-compatible) Sun Studio 12 C Compiler,
 but also by the Sun Studio 5.8 C Compiler on a Solaris 10 installation.
 Adding support for other vendor compilers will be much easier now.</p>
<p>These changes can be tested in the -current branch of mksh (and MirOS BSD)
 and will be released with the next major version, mksh R30. Furthermore, a
 few minor bugs were fixed and mirtoconfiguration is a little faster and more
 reliable now. Some of these changes may be MFC'd to mksh R29g, whose release
 date has not yet been decided upon (reads: when do <em>you</em> need it?).</p>
<p>Update: Intel's C Compiler (Version 9.1.042 and 10.0.023) work as well and
 have unveiled a few minor issues. The code is now smaller due to removal of
 orphaned code and variables GCC didn't spot. (I don't like icc though.) And in
 unrelated news: while we <em>do</em> now support OpenBSD's new CVS keyword
 <tt>$</tt><tt>Mdocdate$</tt>, we will not use it, so that the mksh(1) manual
 page remains usable on other operating systems.</p>
----
Title: First MirOS #10 Release Candidate published
Date: 09.06.2007

<p>The MirOS Project is proud to announce the availability of the first
 release candidate of the upcoming eleventh release of MirBSD, together
 with a stable release of the MirPorts Framework. This snapshot already
 advertises itself as MirOS #10 except for the OS patchlevel number and
 is available for download for the i386 architecture only.</p>
<p>Download, as usual, on the <a href="http://f.scarywater.net/miros/">
 BitTorrent tracker</a> (Live CD), or via a networked installation from
 various mirrors (<a href="http://www.mirbsd.org/MirOS/current/">DE</a>
 <a href="http://pub.allbsd.org/MirOS/current/">JP</a>).</p>
<p>On unrelated news, work on the 32-bit sparc port has started again –
 mostly due to request from users (quite reassuring). Thanks, guys!</p>
----
Title: FrOSCon talk approved
Date: 18.06.2007

<p>bsiegert@ will hold a talk about GNU autotools, libtool, and how to use
 it right at the second <a href="http://www.froscon.org/">FrOSCon</a> in
 St. Augustin near Bonn, Germany.</p>
<p>Of course, there will be a BSD booth with all the usual suspects and
 goodies, so feel free to come over and talk to your favourite BSD's
 developers in person.</p>
----
Title: Fedora GNU/Linux now officially ships mksh
Date: 19.06.2007

<p>Thanks to a contributor who wishes to remain anonymous, <a
 href="@@RELPATH@@mksh.htm">mksh</a> is now officially shipped for
 Red Hat's GNU/Linux variants:</p><ul>
 <li>Fedora 7 (i386, amd64, ppc, ppc64 using gcc 4.1.2 and glibc 2.6
  at Linux 2.6.21)</li>
 <li>Fedora Core 6 (i386, amd64, ppc using gcc 4.1.1 and glibc 2.5
  at Linux 2.6.20)</li>
 <li>Red Hat Enterprise Linux 5 (i386, amd64, ppc using gcc 4.1.1 and
  glibc 2.5 at Linux 2.6.18)</li>
 <li>Red Hat Enterprise Linux 4 (i386, amd64, ppc using gcc 3.4.3 and
  glibc 2.3.4 at Linux 2.6.9)</li>
</ul><p>We were informed that the all of these pass the testsuite. Fedora 7
 quality assurance is being run on it until approximately this weekend; to
 install mksh, simply type <tt>yum install mksh</tt> (for RHEL, you'll have
 to <a href="http://fedoraproject.org/wiki/EPEL/FAQ#head-fc43191402d7242da15ebb282c1a7dc948f6c852">enable
 the EPEL repository</a> first).</p>
<p>The Fink package manager for Mac OSX now also contains mksh R29f.</p>
----
Title: Most requested compatibility feature implemented in mksh
Date: 22.06.2007

<p>Countless users have requested we do the same as AT&amp;T ksh93 and bow
 to the “be conservative in what you send, be liberal in what you accept”
 approach. Regarding to shell programming, this means we should support some
 of the most widely used extensions from other shells (ksh93, bash, zsh, csh,
 make(1)) as well.</p>
<p>Some hours of continuous cursing later, it's done. The current development
 version of <a href="@@RELPATH@@mksh.htm">mksh</a> R30β now supports GNU bash
 style array initialisations – and better than they, I might add:</p><ul>
 <li>OpenBSD ksh (from OpenBSD 4.1-current, 17 May 2007):<pre>
	$ x=(a b c)
	/bin/ksh: syntax error: `(' unexpected</pre></li>
 <li>GNU bash (from MirPorts Framework, 2.05b-1):<pre>
	$ v="d e"; x=('$a' "$v" c "(d)"); echo "${#x[*]}/${x[0]}/${x[1]}/${x[2]}/${x[3]}/"
	4/$a/d e/c/(d)/
	$ v="d e"; x=('$a' "$v" c (d)); echo "${#x[*]}/${x[0]}/${x[1]}/${x[2]}/${x[3]}/"
	bash: syntax error near unexpected token `('
	Segmentation fault
	$ v="d e"; x=('$a' "$v" c "(d)"; echo "${#x[*]}/${x[0]}/${x[1]}/${x[2]}/${x[3]}/"
	bash: syntax error near unexpected token `;'
	Segmentation fault
	$ bash -c 'v="d e"; x=('\''$a'\'' "$v" c "(d)"'
	bash: -c: line 1: unexpected EOF while looking for matching `)'
	Segmentation fault
	$ bash -c 'v="d e"; x=('\''$a'\'' "$v" c "(d)"; echo "${#x[*]}/${x[0]}/${x[1]}/${x[2]}/${x[3]}/"'
	bash: -c: line 1: syntax error near unexpected token `;'
	bash: -c: line 1: `v="d e"; x=('$a' "$v" c "(d)"; echo "${#x[*]}/${x[0]}/${x[1]}/${x[2]}/${x[3]}/"'
	Segmentation fault</pre></li>
 <li>mksh (-current as of tonight):<pre>
	$ v="d e"; x=('$a' "$v" c "(d)"); echo "${#x[*]}/${x[0]}/${x[1]}/${x[2]}/${x[3]}/"
	4/$a/d e/c/(d)/
	$ v="d e"; x=('$a' "$v" c (d)); echo "${#x[*]}/${x[0]}/${x[1]}/${x[2]}/${x[3]}/"
	mksh: syntax error: '(' unexpected
	$ mksh -c 'v="d e"; x=('\''$a'\'' "$v" c "(d)"'
	mksh: syntax error: ')' missing
	$ mksh -c 'v="d e"; x=('\''$a'\'' "$v" c "(d)"; echo "${#x[*]}/${x[0]}/${x[1]}/${x[2]}/${x[3]}/"'
	mksh: syntax error: ')' missing</pre></li>
</ul>
<p>As you can see, we're continuing our not only tradition but also mission
 to provide working, reliable software. (If you try interactively typing one
 of the last two examples, mksh just waits for the closing parenthesis.)</p>
<p>Furthermore, <a href="@@RELPATH@@permalinks/news_e20070605-nn.htm">our
 portability promise</a> is kept – mksh now also compiles fine with the vendor
 tools on HP-UX, which even have found a little shortcoming in the code I only
 can shake my head about… no idea who coded <em>that</em> ugly thing…</p>
<p>On unrelated news, bsiegert@ has continued his work on bringing the GNOME
 ports into shape for the impending release of MirOS #10.</p>
----
Title: More mksh features, Download issues
Date: 06.07.2007

<p>We've finally implemented another bash-compatible feature in <a
 href="@@RELPATH@@mksh.htm">mksh</a>, namely variable substitution
 with substrings. Try <tt>print ${var:2:3}</tt>. The first character
 after the (first) colon must be numeric, an opening parenthesis, a
 dollar sign or a space right now; use <tt>${var: n: m}</tt> for the
 bash <tt>${var:n:m}</tt> (or <tt>${var:$n:m}</tt> or even
 <tt>${var:(n):m}</tt>). All of these are bash-compatible. This doesn't
 nest in either mksh or bash.</p>
<p>More features are to follow ☺</p>
<p>To install MirOS BSD, please use a <a href="@@RELPATH@@MirOS/current/">direct
 download</a> (or even netinstall from the same place) at the moment.
 We will provide MirOS #10RC2 as a Live+Install ISO image again at some
 time in the future (give us 1-2 weeks); MirOS #10RC1 contained a bug
 regarding the live CD part which went for a few days undetected; the
 creation of the ISO fell into that timeframe.</p>
<p>On a side note, the series of GNOME port updates is continuing.</p>
----
Title: mksh R29g released; impact of German law on MirOS base
Date: 09.07.2007

<p><a href="@@RELPATH@@mksh.htm">mksh R29g</a> has been released mostly
 to fix large file support in some operating systems (mostly GNU), which
 was tested for correctly, but the test result was not used during the
 actual compilation. Found by hondza, thanks! This stable version update
 also contains some other minor changes from mksh-current that don't
 affect existing behaviour (so none of the nice features shown earlier)
 which aren't that noteworthy though. <small>There's still an issue in
 that <tt>-D_LARGE_FILES=1</tt> is defined even if it's not required
 sometimes, which is fixed in mksh-current, but it doesn't hurt.</small></p>
<p>German penal and crime code, Article 202c, forbids us from “retrieving,
 making available” (and some other things) tools that can be used to gain
 illegal access to data or access codes. While we do not approve of this law
 at all, we will be forced to abide by it in a few weeks (once it's been
 published in the print version of the parliament's papers), so tcpdump(8)
 was removed from the base system. We do not believe providing MirPorts
 makes us liable for the actions of the end user, and hope no other tool
 in the base system is affected by this law. We will try to make politicians
 realise how bad that is, as they are effectively preventing sysadmins as
 well as researchers, teachers and students from securing systems. (Maybe
 they just want to make us affected by the Federal Trojan?)</p>
----
Title: mksh now the default shell in FreeWRT
Date: 16.07.2007

<p><a href="https://www.freewrt.org/">FreeWRT</a>, an embedded applicance
 development kit, has adopted <a href="@@RELPATH@@mksh.htm">mksh</a> as its
 default shell and <tt>/bin/sh</tt> for the upcoming 1.1 release.</p>
<p>We would like to thank everyone for their support and feedback, hope that
 the upcoming mksh R30 will please even more, and suggest other projects,
 such as NetBSD®, to switch at least their native ksh to mksh.</p>
----
Title: sparc32 no longer in Debian; mksh with xlC
Date: 23.07.2007
Author: tg@

<p>With apologies to every Debian user who is still on sparc32, XTaran of
 <a href="http://www.symlink.ch/">Symlink</a> fame has provided us with
 the idea: We aim to produce an operating system for 32-bit sparc boxen
 that is small, fast, stable, reliable and secure. MirOS/sparc is its name,
 and while it's currently being dormant, I promise it will be polished and
 shining in a short while. (I hope to get the issues I had some weeks ago
 solved, even at the cost of Ada support should that be necessary.)</p>
<p>I could use some parts for my SPARCstation 20 though: it only has a 75
 MHz supersparc CPU and 128 MiB RAM; if someone has a 233 MHz hypersparc
 CPU (I think Ross built these) I'd be delighted to upgrade, and more RAM
 never is bad. I've got some SCSI discs from tyler, so that's not urgent.</p>
<p><a href="@@RELPATH@@mksh.htm">mksh</a> now builds with IBM XL C/C++ on
 AIX – Linux/POWER and Mac OSX shall follow once I'm able to test. Thanks
 to the person who wishes to remain anonymous for providing us the ability
 to do this porting work.</p>
----
Date: 27.06.2007
Title: fixed some annoying kernel bug

<p>On boot, if the kernel were to drop into ddb(4), it would panic again,
 rebooting over and over, due to an uninitialised timeout(9) in random(9);
 this was fixed today.</p>
----
Title: mksh R30 released
Date: 28.06.2007

<p><a href="@@RELPATH@@mksh.htm">mksh R30</a> has been released; read the
 <a href="@@RELPATH@@mksh.htm#clog">ChangeLog</a> for details. FreeWRT,
 Debian, FreeBSD Ports, MidnightBSD mports, MirPorts, RedHat/Fedora, the
 OpenSuSE Buildservice all have it already; we expect others to follow.</p>
<p>This release is dedicated to everyone who helped with portability.</p>
----
Title: MirOS #10 RC3 available
Date: 01.08.2007

<p>The <a href="http://f.scarywater.net/miros/">BitTorrent tracker</a> now
 has a torrent for the MirOS #10 RC3 Live+Install CD; of course, the <a
 href="@@RELPATH@@MirOS/current/">netinstall location</a> has been upgraded with the
 new dist sets as well. You can now select a keyboard layout during livecd
 boot, and it's been made more user friendly; many small bugs have been
 plugged; <a href="@@RELPATH@@mksh.htm">everyone's favourite shell</a> is
 at R30-current with support for TenDRA and maybe tcc, and several ports,
 most notably GNOME, are in good shape.</p>
<p><em>Please</em> <strong>report</strong> errors back to us; we don't plan
 on making any further changes to the codebase save bugfixes and maybe some
 more changes to ports.</p>
----
Title: mksh integrated into MidnightBSD
Date: 18.08.2007

<p>After <a href="@@RELPATH@@permalinks/news_e20070716-nn.htm">FreeWRT</a>,
 <a href="http://www.midnightbsd.org/">MidnightBSD</a>, a FreeBSD-based
 operating system, has adopted <a href="@@RELPATH@@mksh.htm">mksh</a> as its
 default Korn shell, that is, <tt>/bin/mksh</tt> and <tt>/bin/ksh</tt> (but
 not as <tt>/bin/sh</tt>). While the current <a
 href="http://www.midnightbsd.org/cgi-bin/cvsweb.cgi/src/bin/mksh/">state
 of integration</a> uses mksh R30, the upcoming R31 release with features
 requested by MidnightBSD developers will be integrated soon.</p>
<p>We would like to thank the developers of MidnightBSD for considering this
 and congratulate their users to gain a usable-by-default shell. We would
 also like to encourage other operating system developers to follow this
 example and integrate mksh (or, like OpenSolaris, AT&amp;T ksh93).</p>
----
Title: Hardware problems
Date: 21.08.2007

<p>Our main cvs and mailing list server, <tt>herc.mirbsd.org</tt>, has some
 hardware problems at the moment. This means that the mailing lists
 are down until further notice. Anonymous CVS access (not from allbsd.org),
 this website, and BitTorrent are working fine though.</p>

<p>Read/write CVS access to CVS for developers will be restored in one
 or two days, making tg@’s SPARCstation the temporary CVS master.</p>

<p>Waldemar Brodkorb (wbx@) has donated hardware to act as a supplemental
 AnonCVS/AnonRSYNC server, which is being initialised and tested right
 now, as the hosting site only accepts boxen that have passed a typical
 stress test. Eventually, this box will act as a secondary mail server
 as well.</p>

<p>For now, please use <a href="irc://irc.freenode.net/MirBSD">IRC</a>
 for bug reports, feature requests, feedback, etc.</p>

<p><strong>Update</strong> (2007-08-24): We’re almost back to normal,
 the server hardware has changed a little until proper replacement can
 be used (with proper, I mean replacing the IDE crap with SCSI, etc.
 while we’re at replacing anyway, and actually investing some – well, a
 lot of – money and effort). Mailing lists work again, and commits will
 be enabled for developers during short timeframes a few times per day,
 with immediate rsync actions being taken afterwards just to be on the
 safe side. This however means: FrOSCon CDs will contain older versions
 of MirOS, big financial loss for us, and MirOS #10 will be delayed for
 a yet unknown amount of time (but sparc is finally ready since 23rd).</p>
----
Title: MirOS #10-rc4 (i386) released, with a known bug
Date: 22.08.2007

<p>MirOS BSD #10 is coming near. The fourth release candidate for i386
 has been released. Grab it via HTTP for the <a
 href="http://www.mirbsd.org/MirOS/current/i386/">i386</a> or <a
 href="http://www.mirbsd.org/MirOS/current/sparc/">sparc</a> platform,
 or do a network installation.</p>

<p><strong>Caveat</strong>: There is a bug in some of the <tt>fonts.alias</tt>
 files from the xbase set. If X fails to start, enter the following
 commands to fix the problem:</p>

<pre>$ sudo ed /usr/X11R6/lib/X11/fonts/misc/fonts.alias
%s/iso8859-1$/iso10646-1/
wq</pre>

<p>Note: this affects both the i386 and sparc snapshots!</p>
----
Title: FrOSCon 2007
Date: 24.08.2007

<p>This weekend, the project will be present at the <a
 href="http://www.froscon.org/">FrOSCon 2007</a> at the FH
 Bonn-Rhein-Sieg near Bonn, Germany. There is going to be a booth where
 you can meet the developers, and bsiegert@ will hold a talk about
 <i>autoconf, automake, and libtool&mdash;an introduction to the GNU
 build system</i> on Sunday at 16:30, room 5.</p>

<p>Note the <a href="@@RELPATH@@permalinks/wlog-9_e20070824-tg.htm">wlog
 entry</a> about FrOSCon – more entries will follow, stay tuned.</p>

<p>The CDs to distribute are <em>still</em> not done, sorry… it’ll be an
 adjusted LinuxTag edition, no more, not even more recent dist sets, due
 to all the trouble we had.</p>

<p>tg@ and bsiegert@ are appearing at the FH site later this evening and
 are open for food’n’beer suggestions from donators ☻</p>
----
Title: MirOS #10 RC6 (i386, sparc)
Date: 30.08.2007

<table width="100%"><tr>
 <td style="width:160px;"><a
  href="@@RELPATH@@pics/XTaranStation.jpg"><img
  src="@@RELPATH@@pics/XTaranStation.png" alt="XTaran no SPARCstation"
  /></a></td>
 <td>XTaran of symlink.ch fame has finally helped us to test the latest,
  greatest and ultimately vt100, grey-on-blue / grey-on-black snapshot –
  as you can see, it boots up quite nicely. First, the text is still all
  black on white, but as soon as the framebuffer is initialised, that is
  switched to lightgrey on black, and further kernel messages are in our
  well-known, famous lightgrey on blue colour composition.<br />WARNING:
  The linked image is more than 1 MiB in size.</td>
</tr></table>
<p>Furthermore, this very snapshot has been uploaded (for both the sparc
 and i386 architectures, with a readme for the former) to /MirOS/current
 and waits for your test results. We would be glad if someone could help
 us to fix the remaining bugs especially in the sparc port (nroff, issue
 with the bootloader and bsd.rd, etc).</p>
<p>The aforementioned XFree86 font issues have been solved provisionally
 by putting back the cropped and charset-reduced font sets; we will look
 into this issue after the release sometime.</p>
----
Title: mksh R31 released
Date: 07.09.2007

<p><a href="@@RELPATH@@mksh.htm">mksh R31</a> has been released; read the
 <a href="@@RELPATH@@mksh.htm#clog">ChangeLog</a> for details.</p>
<p>This release is dedicated to Bob “maradong” Hentges, Symlink Lëtzebuerg.</p>
----
Title: mksh R31b released, mksh R31c followup
Date: 09.09.2007

<p><a href="@@RELPATH@@mksh.htm">mksh R31b</a> has been released; read the
 <a href="@@RELPATH@@mksh.htm#clog">ChangeLog</a> for details. This quick
 follow-up release is because it fixes several important bugs etc.</p>
<p>OSF/1 support thanks to the <a href="http://www.icewm.org/">IceWM</a>
 coffee pot maintainer, Josef “Jupp” Schugt.</p>
<p>Update: On 09/11, mksh R31c was released, thanks to Josef “Jupp” Söntgen
 (aka cnuke@)’s very late bug report, which was done IRL instead of via IRC
 or eMail, which are the usual channels. This release fixes arc4random.c on
 SunOS due to them bad OpenBSD guys using non-standard types in an API.</p>
<p>Update 2: Everyone should upgrade to mksh R31b or later, due to the bug
 fixes and their relevance.</p>
----
Title: mksh R31d released
Date: 14.10.2007

<p><a href="@@RELPATH@@mksh.htm">mksh R31d</a> has been released; read the
 <a href="@@RELPATH@@mksh.htm#clog">ChangeLog</a> for details. Basically,
 another busy loop spinning bug was fixed and everyone should upgrade.
 This release features <a href="http://pcc.ludd.ltu.se/">PCC</a> support.</p>
----
Title: bootblocks now machine-independent, HTML manual pages split
Date: 21.10.2007

<p>The first-stage bootblocks (bootxx) of both the i386 and sparc architecture
 are now self-installing shell scripts that take an extent list (block spans)
 on standard input. This now allows to create, for example, bootable ISO9660
 images for MirBSD/i386 and MirBSD/sparc (or even both at the same time) on
 a MirBSD/i386 (or even GNU/Linux/i386) box. This is another milestone in the
 progress of making sparc a full-blown, supported, architecture.</p>
<p>The HTML manual pages have now been split into a machine-independent and a
 machine-dependent part (or rather, two of them) as well. This allows a much
 faster release generation on sparc. Furthermore, related manual pages, such
 as uuencode(1), uudecode(1), b64encode(1) and b64decode(1), now list all of
 their aliases in the title and are hard linked to save space and generation
 time (and hopefully search engine traffic, who knows).</p>
----
Title: mksh R32 released, plans for R33
Date: 25.10.2007

<p><a href="@@RELPATH@@mksh.htm">mksh R32</a> has been released; read the
 <a href="@@RELPATH@@mksh.htm#clog">ChangeLog</a> for details. In short, an
 internal error when using pipelines as co-processes was fixed, array index
 bounds expanded, the build system improved, and everything cleaned up.</p>
<p>mksh R33 will address the namespace conflict between aliases and shell
 functions in a way Debian patched their pdksh package to go. This implies
 that FSH invocations will be able to define all common aliases again.</p>
----
Title: herc down, mirbsd.org mail unavailable
Date: 22.11.2007

<p>Due to a technical problem, mail service for <tt>mirbsd.org</tt> is
 not available. tg@ is also absent but you can reach a MirOS developer
 at <tt>bsiegert at gmail.com</tt> (replace " at " by @).</p>

<p>Most notably, this means that the mailing lists, miros-discuss and
 miros-cvs, are not working. To keep up with recent commits, look at the
 <a href="http://www.mirbsd.org/clogs/ChangeLog">Changelog</a>. anoncvs
 and cvsweb do work.</p>
----
Title: Security updates
Date: 26.11.2007

<p>A security update for perl in the base system has been committed.
 To install it, update <tt>src/gnu/usr.bin/perl</tt> via cvs and
 rebuild perl. A <a
 href="@@RELPATH@@MirOS/current/i386/perl-CVE-2007-5116.cpio.gz">binary
 upgrade</a> for newer MirOS #10-beta versions (Linuxtag 2007 and
 newer) is also available. To install the latter, use</p>

<pre>cd / ; sudo tar xvfz /path/to/perl-CVE-2007-5116.cpio.gz</pre>

<p>The following ports also had security updates: <tt>print/cups</tt>
 (fixed in 1.2.11-1), <tt>devel/pcre</tt> (fixed in 7.4-0). Please
 upgrade those if you have them installed.</p>

<p><b>Update 20071221:</b> cups-1.2.11-3 is out with more fixes.</p>
----
Title: MirOS at 24C3
Date: 26.12.2007

<p>The project will be present (albeit without tg@) at the 24th Chaos
 Communication Congress at Berlin, Germany. We will have (maybe) a table
 in the hackcenter. There will be many interesting talks about hacking,
 society and similar topics.</p>
----
Title: New website design
Date: 28.12.2007

<p>As you surely see, this page sports a brand-new design based on the old
 <a href="http://www.mirbsd.org/newsite/">/newsite</a> CSS and the old one
 for www.mirbsd.org. The colors have been inverted (i.e. dark text on light
 background) and the header has changed. If you happen to notice any problems,
 contact us.</p>

<p>The design was tested on Camino (Mozilla), Firefox, Safari, IE6, Opera,
 and lynx. I hope that covers the ususal suspects.</p>
----
Title: RSS feeds
Date: 21.01.2008

<p>RSS feeds (in RSS 2.0 format) are now available (again). The available
 feeds are <a href="@@RELPATH@@news.rss">news</a> and <a
 href="@@RELPATH@@wlog-9.rss">wlog-9</a>. <tt>link</tt> tags have also been
 placed, so your browser should be able to auto-detect them. If you have
 any problem, do not hesitate to contact me.</p>
----
Title: MirOS at FOSDEM 2008
Date: 07.02.2008

<p>The MirOS project will be present at <a
 href="http://www.fosdem.org/2008/">FOSDEM 2008</a> in Bruxelles,
 Belgium. We will have a booth and distribute the usual CDs and
 flyers. The BSD projects share a developer room with PostgreSQL. <b>I
 will hold a talk about "Build systems with autoconf, automake, and
 libtool" at Sunday, Feb 24, from 2pm to 3pm.</b></p>

<p>Update: the schedule for the developer room is <a
 href="http://fosdem.org/2008/schedule/rooms/aw1.124">available on the
 FOSDEM web site</a>.</p>
----
Title: mirmake 20080218 released
Date: 20.02.2008

<p><a href="@@RELPATH@@MirOS/dist/mir/make/">mirmake-20080218</a> has been
 released. Read the <a
 href="@@RELPATH@@permalinks/wlog-9_e20080219-bsiegert.htm">release notes
 here</a>.</p>
----
Title: MirOS @ FOSDEM 2008
Date: 22.02.2008

<p>bsiegert@ currently sits at the Early Bird beer event in Bruxelles,
 tg@ and gecko2@ will follow tomorrow and man the MirOS booth ☻</p>
----
Title: FOSDEM follow-up
Date: 24.02.2008

<p><a href="@@RELPATH@@MirOS/dist/mir/make/">mirmake-20080224</a> and
 assorted commits in the MirPorts Framework fix all known Mac OSX Leopard
 issues.</p>
<p>There are two BSD booths at FOSDEM: one with OpenBSD and FreeBSD (with
 DesktopBSD and PC-BSD CDs) at the usual place in the main building, and
 one with OpenBSD, NetBSD and MirOS in the AW building, near the shared
 PostgreSQL/BSD developer room. Meet us at the latter! CDs are out though
 (MirOS, FreeSBIE, etc. – only some of the other BSDs left).</p>
<p>Despite the crappy WLAN and no LAN availability even for booths, Benny
 and I managed to hack on stuff (e.g., mksh). We also made plans for a
 very short-term follow-up #10semel release; mostly, security updates for
 XFree86® and a lot of ports. (FOSDEM was great as usual, though.)</p>
<p>The &lt;link rel=…&gt; tags for RSS have been fixed. After removing and
 re-adding, they should work with Opera now, and the pages are XHTML/1.1
 compliant again now.</p>
<p>Currently, pcc cannot compile anything with &lt;stdio.h&gt;.</p>
----
Title: mksh R33 released
Date: 01.03.2008

<p><a href="@@RELPATH@@mksh.htm">mksh R33</a> has been released; read the
 <a href="@@RELPATH@@mksh.htm#clog">ChangeLog</a> for details. (Happy
 Birthday to everyone who has on this day.)</p>
<p>The news in short and human-readable:</p><ul>
 <li>Improved build system, once again; better error tracking; better
  portability with regards to tools in /usr/bin at build and compilers</li>
 <li>Integrate all changes from OpenBSD ksh</li>
 <li>Integrate some changes from Debian: the “dot” command needs an
  argument; prevent namespace conflict between (built-in) aliases and
  (POSIX, not Korn) shell functions</li>
 <li>Add <tt>\uXXXX</tt> and <tt>\xXX</tt> escapes to the print builtin</li>
 <li>No longer check if we are called as “sh” for special handling</li>
 <li>Implement here strings: you can now replace <tt>print -r -- "$foo" |
  command</tt> with <tt>command &lt;&lt;&lt;"$foo"</tt> – like ksh93, zsh;
  GNU bash behaves differently if and only if $foo is not quoted</li>
 <li>Implement string replacement <tt>${var/pattern/string}</tt></li>
</ul>
<p>Especially cool feature: replace <tt>x=$(print -r -- "$x" | sed -e
 's/foo.*bar/baz/g')</tt> with <tt>x=${x//foo*bar/baz}</tt> ☺</p>
<p>Note: the distfile is not here yet, it’ll take a while to be released.
 Once it’s uploaded, the <a href="@@RELPATH@@mksh.htm">mksh homepage</a>
 will be updated with appropriate information. UPDATE: It’s out now.</p>
----
