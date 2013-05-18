Date: 10.03.2008
Author: tg@

<p>Our kernel now should handle signals wrt the extended i386/amd64
 ABI fine: thanks to the Debian GNU/kFreeBSD developer Aurelien
 “aurel32” Jarno, the direction flag (DF) is now cleared on traps.</p>
----
Date: 12.03.2008
Author: tg@

<p>The new cksum port sets a variable HAS_CKSUM, which will be used
 really soon now in the MirPorts infrastructure to replace all the
 old cruft (_CKSUM_A, _CKSUM_SIZE, _HASHES). From RSN on, you will
 either have our current cksum(1) from MirOS #10 or MirPorts, or
 you won’t, in which case it will only use the “cksum” algorithm
 of the OS’ own cksum programme (which is rather ubiquitous).</p>
<p>We have a new sample file, “portmdoc”, and I’ve converted yet
 another manpage to be fixed with regards to GNU groff, like I did
 with mksh(1) after the R33 release. Expect this to continue.</p>
<p>The FSF is now mistaking that lazy moronic finnish student’s
 excuse for a patch management system for a version control system
 as well… the config.{guess,sub} files are now in git. Yuck!</p>
----
Date: 13.03.2008
Author: tg@

<p>Besides from my TODO on MirPorts (and the portable subprojects)
 and MidnightBSD, and the release engineering process, and my other
 want-to-do hobbies like hercules(4) wsfb(4) support (and an XF86
 module, and emulation support for a HGC in qemu), and a couple of
 other things, Waldemar has made a point:</p>
<p>MirOS definitively needs to shift away from “we want to make
 OpenBSD better, and we do X, Y and Z” towards “we want to do X, Y
 and Z, specialise on W, support V, and while doing all that, we
 are of course as secure as OpenBSD and track their goodies, and by
 the way, we have GNOME and Frozen-Bubble”. This would give the MirOS
 Project an actual face, which could attract users and development
 capability/potential. (And it would imply a re-design of the Flyers’
 and website’s content…) We’ll have to think about it, but he is
 probably right.</p>
----
Date: 14.03.2008
Author: tg@
Title: GPLv3

<p>As written in my earlier entry (still to be ok’d by benz) about <a
 href="@@RELPATH@@permalinks/wlog-9_e20080313-tg-g10002.htm">GPLv3</a>,
 editors/nano is okay (for now). This means that rsync 3 is probably ok
 to go in now too (especially since we have no patches). It’s said to be
 much faster and less RAM-hungry, which is especially nice.</p>
----
Date: 14.03.2008
Author: tg@

<p>The <a href="@@RELPATH@@ports.htm">MirPorts Framework</a> can now be
 used on <a href="http://www.midnightbsd.org/">MidnightBSD</a> out of
 the box, no special patching needed. MirMake, MirCpio, MirCksum and the
 package tools have been updated appropriately.</p>
<p>However, MirLibtool support is still missing. This is trivial, I just
 don’t have the time to do it right now, as I should be doing the release
 at the moment. Still, feel free to play with it.</p>
<p>Yeah. I did port MirLibtool to mnbsd, and found a bug (in upstream,
 even) while doing it. Nicey. Both devel/glib1 (autoconf-2.13) and
 devel/libtool (autoconf-2.61) seem to work (regarding libtool build
 systems, shared library building/naming, etc.) for now. I’m a little
 bit unsure about shared library <em>naming</em> conventions, but you
 can follow FreeBSD’s, even though Todd Vierling and I think they are
 weird and/or not what one wants. (For insiders like Benny: they do not
 use current/age/revision, set the third number to 0.)</p>
<p>We have a new “p5” port module, which must now be referenced by any
 users of ${P5ARCH} which do not include the “perl” module.</p>
<p>pvalchev@obsd replied to my issues with the UMAC64 hash that I might
 want to report the bug in lingcc’s umoddi3 implementation upstream.
 This shall be my TODO, someone please remember me to do it (check how
 to reproduce on $common_os, with $latest_gcc, etc).</p>
<p>miod@openbsd is helping me with the tvtwo(4) card – unluckily, I’m
 unable to test diffs because my monitor is too small… Doesn’t anyone
 happen to want to give away a TFT that can do 1152x900 for free? ☺</p>
----
Date: 15.03.2008
Author: tg@
Subject: The Unicode Release

<p>MirOS ξ (MirOS xi) is not only our eleventh release (as I started
 counting at zero), it is also the Unicode release. While it finally
 makes sparc a fully supported platform, the real focus is on Unicode,
 and bsiegert@’s girlfriend seems to have realised that better than I
 did.</p>
<p>However, in fact, that was only a start. We need to change the <a
 href="http://article.gmane.org/gmane.os.miros.general/7938">character
 set</a> in order to be able to handle binary files transparently with
 Unicode-enabled applications – col(1) and tr(1) in MirOS #10 – before
 converting more applications to use Unicode.</p>
<p>Please give feedback on the thread linked above, if you can.</p>
<p>MirOS #10 does come with everything needed by <em>applications</em>
 for full Unicode support though, and in contrast to OpenBSD, things
 really do work. This justifies calling the release like this, even
 with a Unicode character in its codename.</p>
<p>For the first time, the “tag line” comes without a “WTF?”. You may
 take this as a sign that we are not confused about ourselves, have
 gotten over the initial cause to make MirOS and now no longer merely
 are a team that wants to improve OpenBSD. We are a small but powerful
 operating system project, with goals (already met or new ones) of our
 own. We still track OpenBSD, but that’s no longer the focus. Benny’s
 girlfriend also got that right. And her mouse did attract the users,
 and stayed topic on the other BSDs’ websites. Wow.</p>
----
Date: 19.03.2008
Author: tg@

<p>In addition to my primary geocaching site, OpenCaching.de, and the
 commercial crap site, GeoCaching.com, which has most users, I now also
 registered at TerraCaching.com, which is a semi-closed site providing
 “high-quality” caches. Stats bar gallery:</p>
<p><img src="http://www.opencaching.de/statpics/106521.jpg"
 alt="OC" /> <img src="http://img.geocaching.com/stats/img.aspx?txt=Hacking+MirBSD+since+2002&amp;uid=d6aaa6ad-797c-419a-91b3-8cf6a5b40658"
 alt="GC" /> <img src="http://www.terracaching.com/statsban/15089.gif"
 alt="TC" /></p>
<p>Of course, I didn’t find any TCxxxxx caches yet. I need to get fully
 registered (“sponsored”) at the site first. This isn’t a big issue tho.</p>
<p>Update: I’m in. Nearest caches are in Blankenheim, Neuwied and België…</p>
----
Date: 19.03.2008
Author: tg@

<p>gecko2@ just called me. He operates <tt>www.mirbsd.org</tt> and got
 a little surprise on his daily traffic report. Summing it up, his server
 and myself, and a friend of mine, together, adding HTTP and BitTorrent
 transfers, have had about 500 GiB traffic in the 3½ days the #10 release
 is now available. Alone the HTTP direct downloads of clients that got the
 ISO in one piece (not HTTP 206) number sits at 861 at the time of this
 writing (850 five minutes ago, 825 ¼h ago).</p>
<p>As an immediate measure protecting his server against being taken
 offline for traffic limit trespassing, I redirected to allbsd.org for
 direct downloads on getting.htm and suggested him to install bandwidth
 throttling/limiting for apache. Don’t be surprised.</p>
<p>Update: half an hour later, it’s at 867, so I think the change of the
 direct link helped. Sorry for the inconvenience at both gecko2 and our
 downloaders – but then, to the latter group: You should’ve used
 <a href="http://f.scarywater.net/miros/">BitTorrent</a> anyway.</p>
<p>Oops. Changed the wrong link. 923 downloads… 927…</p>
----
Date: 19.03.2008
Author: tg@

<p>My primary SPARC build box <tt>demo</tt> now has a HyperSPARC 150 MHz
 ROSS CPU, instead of a SuperSPARC 75 MHz, and 512 MiB RAM instead of a
 mere 128 MiB (and with that, twice the RAM of my primary i386 box).</p>
<p>But then, I got three SCSI HDDs from the same stone age, and each of
 them has a different connector. <em>This</em> sucks.</p>
----
Date: 20.03.2008
Author: tg@

<p>I’m impressed – 1377 full downloads from the Germany 1 mirror, add to
 that the partial downloads (<tt>wget -c</tt> or so-called “download
 managers”), these from the Germany 2 and Japan mirrors, BitTorrent (which
 is 36 times from myself, and a couple of dozen times from my friends, and
 even more from the unknown peers) and you won’t think of us as irrelevant
 any more.</p>
<p>I’ve hacked on the crypto improvements branch again. I decided that
 getting <tt>tear</tt> up and running would be my priority target. It
 turned out to be a great way to hone my programming skillz as well:
 I got a lession about pointer aliasing.</p>
<p>Except the actual VIA C7 part, I now tested it quite well on i386-qemu
 and sparc, where the latter took about one third the time compiling… the
 new CPU and RAM pay off.</p>
<p>Oh yeah, and hacking on stuff always points out unrelated bugs… such as
 NO_GZIP=Yes for kernels not working, or &lt;bsd.lkm.mk&gt; being out of
 date (I had to MFC that, even). And that <tt>src/kern/z</tt> needs tender
 care – the transition is still not finished even for zlib.</p>
<p>I hope the discussion about our charset/encoding proposal will find a
 solution… I feel like constructing a bikeshed, as you get about that much
 feedback there too ☺ Benny said he doesn’t grok the SUSv3 functions, like
 mbrtowc(3), enough to follow – and I can totally understand that. Maybe a
 Unicode guru person like Markus Kuhn can help – I asked him.</p>
----
Date: 21.03.2008
Author: tg@

<p>Happy Spring Equinōx to everyone!</p>
<p>I merged the crypto improvements to HEAD: we now have improved Rĳndael
 CBC code for UVM swapencrypt, and this code uses the VIA C3/C7 PadLock™
 ACE if existing – whose code contained a now-fixed data corruption bug.</p>
<p>Next on the TODO list is: make vnd(4)’s encryption use the same code
 if AES is chosen as cipher algorithm. Allow selection of Blowfish (stay
 compatible), AES-128, AES-192, AES-256; other algorithms may follow. We
 will need a new keyfile format <em>and</em> stay backwards-compatible,
 but this is not a problem.</p>
<p>We got a PUA assignment from U+F900‥F97F (tentatively) for our encoding
 proposal, and should use “one of the various non-characters” for the NUL
 encoding. But: “Emoticon U+FDD0 is actually Unicode for the eye of the
 basilisk…” – U+F000‥F7FF are now reserved for Linux’ straight-to-font map
 (and some subranges are used by Windows® and Mac), and F800‥F89F for Mac
 (and possibly, Linux). – Although I got scolded <em>again</em> for chosing
 a 16 bit wide character type, I believe this compromise with all its good
 and bad sides is the right way to go for us at the moment. As for how to
 codify this, I still do not have a final answer, but I think using wrappers
 for SUSv3 functions which cannot fully support the proposal is a good idea.
 Most use cases should work with the SUSv3 functions, anyway.</p>
<p>I still haven’t ported mksh to BSD/OS 3.1, OSF/1 V2.0 and Ultrix V4.5…</p>
----
Date: 22.03.2008
Author: tg@

<p>This night, my internet connection failed every so few minutes (returning
 a PAP failure, despite me being in midst of a session). I took the chance to
 upgrade herc’s software (kernel, userland, a few packages) and spotted that
 sendmail(8) bug. I also took the chance to rebuild the two RAID 1s (one for
 <tt>/</tt>, the other for <tt>/MirOS</tt> and the CVS repositories), which
 took me a while and about a dozen attempts, but finally I succeeded.</p>
<p>Other than that, I didn’t hack much. I walked about 5‥6 km (single way) to
 buy myself a Döner though ☺ bad weather doesn’t have to mean stay inside.</p>
----
