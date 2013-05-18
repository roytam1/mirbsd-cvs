<!-- PageID: getting -->
<small class="rcsid">$MirOS: www/content/Z2V0dGluZw__.inc,v 1.9 2006/01/27 00:14:27 tg Exp $</small>
<h1>How to get MirOS</h1>

<h3>Introduction</h3>
<p>MirOS is separated in various parts: the MirBSD base installation,
 the MirLinux base installation (available about 2006), the
 full source tree for MirBSD/MirLinux (including the X-Windowing
 system), and the MirPorts framework.</p>
<p>Historically, these files have all been available for the i386
 architecture only, and been split on two different servers. This
 is the current state of affairs, as described below - however,
 it will change before the end of the year. Read on for more details.</p>
<p>More information about <a href="/?anoncvs">anonCVS</a> and
 anonRSYNC can be found on the <a href="/?mirrors">Mirrors</a> list.</p>

<h3>Buy CDs with MirOS on them</h3>
<p>Usually, on exhibitions such as the <a
 href="http://www.froscon.org/">FROSCON, St. Augustin (near Bonn), .de</a>, <a
 href="http://www.ccc.de/congress/">Chaos Communication Congress, Berlin, .de</a>, <a
 href="http://www.linuxtag.de/">LinuxTag, Karlsruhe, .de</a> (no longer), or the <a
 href="http://www.fosdem.org/">FOSDEM, Bruxelles, .be</a> there is a
 BSD booth which hosts the MirOS people. You can buy CDs
 on these events (to be exact, you can ask for a CD and donate something in
 return so we can pay our expenses - we aren't making money with it. The
 so-called "minimal donations" are negotiatable).
 Usually they are burnt on the fly during the event.</p>
<p>You can also ask <a href="mailto:tg@66h.42h.de">Thorsten</a> for install
 CDs and <a href="mailto:bsiegert@66h.42h.de">Benny</a> for CDs with binary
 packages, distfiles and MirPorts on them. They will ship per snail mail;
 the usual pricing is: at least 15 EUR per CD (25 for both) to Germany.<br />
 We cannot ship to outside the European Union and Swiss/Schweiz/Suisse.</p>

<h3>Get MirOS now, the new way!</h3>
<p>The current version is MirOS BSD #8semel, available for the i386
 architecture, released on December 23rd, 2005, and MirOS #7quater
 for the sparc architecture, based upon code from 2003. You might
 want to read the <a href="/?ann-8">release announcement</a>.</p>
<p>Development snapshots are also available, and usually newer than the
 latest release. In exchange for actuality, bug fixes and a horseload of
 new features, you get some breakage. If you actually find a bug, please
 send us a bugfix instead of a complaint ;-)</p>

<h4>Doing an online installation</h4>
<p>Currently, you must set the installation method to <tt>HTTP</tt>, the
 server to <tt>www.66h.42h.de</tt> and the path to
 <tt>MirOS/v8/i386</tt> <!-- (or <tt>MirOS/v7/bsd/sparc</tt>) -->,
 with neither a slash before nor after the pathname.</p>

<p>All files which belong to a release of MirOS are
 available for download from a single site (and its mirrors). Source code
 will be retrievable using the <a href="/cvs.cgi/">CVSWEB interface</a>.</p>

<h4>MirOS #8semel</h4>
<p>The first release of the MirOS #8 branch, and the only version
 currently supported. Users are strongly suggested to update.
 You can use MirPorts-current with this version.</p>
<!-- p>A scheduled maintenance upgrade of MirOS BSD #7quater. This version
 includes all OpenBSD errata up to end of 2004, as well as various MirOS
 errata. Users <strong>must</strong> now use current MirPorts for this
 system and install the egcs (gcc3) from packages on i386 if they need it.
 Additionally, it is available for the <a
 href="http://www.66h.42h.de/MirOS/v7/bsd/i386/">i386</a>
 architecture only; for <a
 href="http://www.66h.42h.de/MirOS/v7.4/bsd/sparc/">sparc</a>
 support you must start with #7quater and compile yourself.
 You may also want to get the <a
 href="http://www.66h.42h.de/MirOS/v7.3/source.tgz">*OLD* source code</a>
 (this time excluding the MirPorts Framework), or <a
 href="http://benz.mine.nu/MirBSD/packages/">binary packages for MirOS at
 Benny Siegert's site</a> for both architectures; some are <a
 href="http://www.66h.42h.de/MirOS/v7.3/bsd/Pkgs/">available here</a>
 as well.</p -->
<p>You can retrieve the source code for MirOS #8semel
 by using anonCVS with the tag <tt>MIRBSD_8_BASE</tt>.</p>

<h4>MirOS #8-stable</h4>
<p>This is a development branch with only security and runnability fixes
 to #8semel. There are currently no fixes included.</p>
<p>You can retrieve the source code for MirOS #8-stable
 by using anonCVS with the tag <tt>MIRBSD_8</tt>.</p>

<h4>Snapshots of current development</h4>
<p>You can usually find some more or less recent snapshots in the
 <a href="http://www.66h.42h.de/MirOS/current/">&quot;current&quot;
 directory</a>; beware these might be older than the latest release
 or not work at all. The BitTorrent snapshots however are usually newer
 than the latest release which is also made available via BT, usually
 a few weeks after the release.</p>
<h5><tt style="color:#FF0033;">NEW:</tt> BitTorrent</h5>
<p>The greatest Anime tracker found has enabled the MirOS project to host
 Torrents for our snapshots and releases on them. Please refer <a
 href="http://f.scarywater.net/miros/">the tracker page</a> and consider
 donating the MirOS project with a notice that you used BitTorrent, so we
 can donate the tracker admin ourselfes.</p>
<p><tt style="color:#FF0033;">Request:</tt> We are looking for people who
 are willing to help seeding, because we do not have any system with a
 decent upstream yet. Right now, all of us are seeding via ADSL, but the
 accumulated power of 1-4 KiB/sec upstream entities already gives our
 users a decent downstream. <strong>Please leave your downloaders open
 for another 2-3 weeks after downloading MirOS.</strong> Thanks.</p>

<h1>Other ways to retrieve MirOS</h1>
<p>You might want to check out our AnonCVS and CVSweb pages listed in the
 index tab of this website. Soon, we will provide mirrors hosting MirOS
 releases, and probably rsync access to the repository.</p>
