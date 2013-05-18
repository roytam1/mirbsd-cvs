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
 also an <a href="/MirOS/v9/">HTTP(S)</a> download/netinstall
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
 The <a href="mksh.htm">MirBSD Korn Shell</a> page got completely rewritten.
 If you find something, tell me. The theme will probably stay similar like
 the current one, not like <a href="/newsite/">Benny's</a>, but the index
 on the left will look totally different in some days. I'm only migrating
 (very) few of the old content. At the moment, “main”, “news”, “mksh” and
 “wlog-9” are converted, and the old CMS has been hacked for transparent
 migration to the new CMS (“mws”) using HTTP 301 redirects. Same goes for
 manual pages (/manN/ -&gt; /cman/manN/) to save space on search engines'
 hard disc drives. Finally, news and wlog now have permalinks (beta).</p>
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
<p>To install MirOS BSD, please use a <a href="/MirOS/current/">direct
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
