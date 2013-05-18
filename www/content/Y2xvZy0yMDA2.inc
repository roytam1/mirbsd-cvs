<small class="rcsid">$MirOS: www/content/Y2xvZy0yMDA2.inc,v 1.3 2006/01/13 04:04:43 tg Exp $</small>
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
<h1>2006 snapshots of MirOS-current</h1>
<h3>Infos &ndash; <a href="#eof">bottom</a></h3>

<!--
 <li>base: sample ssh/known_hosts aliases sync with reality</li>
 <li>build: roff2man now generates correct manual pages again</li>
 <li>cvs: correct handling of backslash escapes in log messages</li>
 <li>cvs: save space in commit messages with unexpand(1)</li>
-->

<p id="snap0113">13.01.2006<br />Changes relative to the <a
 href="#snap0103">2006-01-03 snapshot</a> below:</p><ul>
 <li>base: acronym database additions for wtf(1)</li>
 <li>base: anoncvssh standardise on mirror</li>
 <li>base: fixes for mtree database</li>
 <li>base: installboot(8) output fix</li>
 <li>base: mount_msdos(8) USA patents by Microsoft</li>
 <li>base: randshuffle no longer complains in chroot</li>
 <li>base: sample entry in crontab fix</li>
 <li>base: sample ssh/known_hosts addition</li>
 <li>build: ISO generation fixes</li>
 <li>build: fixes for mtree database</li>
 <li>build: roff2man more fixes (final one past snapshot tho)</li>
 <li>installer: default sudo(8) password prompt to no timeout</li>
 <li>kernel: binary compatibility for pre-#8 MirOS was removed</li>
 <li>ports: add -g1 to CFLAGS if DEBUGLIBS</li>
 <li>ports: document some of the new features</li>
 <li>ports: new qt3; several updates and fixes (bash daemontools
  djbdns e2fsprogs lcms libmng ...)</li>
 <li>www: fix URIs, update content</li>
</ul><p>This snapshot also cleans up the codebase even more, but
 its primary focus is to wipe out even more bugs in the infrastructure,
 single programmes and ports. It has been developed for and with
 and while initialising the new dedicated server. There are still
 some known issues (and that securelevel bug I have no idea <em>what</em>
 is a correct fix anyway), but it's quite good. This one also comes
 with a ports set which has been used for upgrading #8 as well.</p>

<p id="snap0103">03.01.2006<br />Announcement relative to the <a
 href="/?ann-8">MirOS #8semel</a> release, not to the MirOS #8-beta <a
 href="/?clog-2005#snap1207">2005-12-07 snapshot</a>:</p><ul>
 <li>base: <tt>/etc/profile</tt> now works nicely on sh(1); better
  legible examples and code</li>
 <li>base: <tt>bsd.rd</tt> is now always gzip'd</li>
 <li>base: fix mtree(8) definitions delivered</li>
 <li>base: fix pax(1) bug in cpio(1) -M option parsing</li>
 <li>base: fix pax(1) build on Macintosh: no strtonum(3)</li>
 <li>base: fix wtmp log rotating default; proper monthly login accounting</li>
 <li>base: remove perl/C-based user management tools</li>
 <li>base: small format string bug fixes</li>
 <li>build: roff2man bugfix for trespassing &quot;&gt; barriers</li>
 <li>installer: allow alphanumeric user names; add to groups staff, wsrc</li>
 <li>kernel: compat_linux(8) now does ptrace(2), from NetBSD&reg;</li>
 <li>mirmake: Libraries built contain debugging information</li>
 <li>mirmake: add -g1 to CFLAGS if DEBUGLIBS (bsd.cfwrap.mk)</li>
 <li>mirmake: add DT_RPATH to shared libraries built (ELF, PE)</li>
 <li>ports: MirLibtool insertion workaround for Debian brokenness</li>
 <li>ports: add +COMMENT to faked packages</li>
 <li>ports: check package names for correctness</li>
 <li>ports: package tools bugfix regarding conflicting packages</li>
 <li>ports: set XAPPLRESDIR to the correct value</li>
 <li>ports: unbreak libtoolise with SED_PLIST</li>
 <li>ports: updates and fixes to lots of ports</li>
 <li>sirc: nicer output, timestamps</li>
 <li>toolchain: fix "could not read symbols: File truncated" problem,
  from OpenBSD</li>
 <li>toolchain: ld(1) no longer dumps core in certain dependent library
  path search cases</li>
 <li>x11: set UseRpath to Yes on ELF systems</li>
</ul><p>This quick follow-up snapshot focuses on cleaning up the code after
 the release was out of the door and got broader exposure. It also, as a
 result of the Hackathon at the 22C3, corresponds to a much better working
 ports framework. The ld(1) bug fix, together with DT_RPATH (-Wl,-rpath and
 -Wl,-rpath-link usage), should allow shared libraries to depend on each
 other (not a good thing if you have static arches, but we don't). Some old
 support code and legacy tools (like useradd) were removed for cleanliness.
 After all, the release and this snapshot are something to be content with.</p>

<p id="eof">That's all for 2006, folks.</p>
