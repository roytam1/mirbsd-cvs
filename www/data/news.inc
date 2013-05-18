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
 <tr><td width="128"><a href="@@RELPATH@@pics/LinuxTag_2007/benz-wrk.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/benz-wrk.png" /></a></td><td>
  Benny bei der Arbeit (benz at work)
 </td></tr>
 <tr><td width="128"><a href="@@RELPATH@@pics/LinuxTag_2007/d-benz.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/d-benz.png" /></a></td><td>
  Dæmonische Bilder: Benny (benz, Developer) – bsiegert@
 </td></tr>
 <tr><td width="128"><a href="@@RELPATH@@pics/LinuxTag_2007/d-mira.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/d-mira.png" /></a></td><td>
  Dæmonische Bilder: Thorsten (mira, Developer) – tg@
 </td></tr>
 <tr><td width="128"><a href="@@RELPATH@@pics/LinuxTag_2007/d-zeno.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/d-zeno.png" /></a></td><td>
  Dæmonische Bilder: Przemysław (zeno, User &amp; Booth Staff) – przemek@
 </td></tr>
 <tr><td width="128"><a href="@@RELPATH@@pics/LinuxTag_2007/groupies.jpg"><img
  src="@@RELPATH@@pics/LinuxTag_2007/groupies.png" /></a></td><td>
  Benny, Przemek, mira and much, whose laptop just got freshly installed…
 </tr></tr>
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
