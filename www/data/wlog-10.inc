RCSID: $MirOS: www/data/wlog-10.inc,v 1.211 2009/07/09 17:18:11 tg Exp $
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
 want to report the bug in libgcc’s umoddi3 implementation upstream.
 This shall be my TODO, someone please remember me to do it (check how
 to reproduce on $common_os, with $latest_gcc, etc).</p>
<p>miod@openbsd is helping me with the tvtwo(4) card – unluckily, I’m
 unable to test diffs because my monitor is too small… Doesn’t anyone
 happen to want to give away a TFT that can do 1152x900 for free? ☺</p>
----
Date: 15.03.2008
Author: tg@
Title: The Unicode Release

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
Tag: geocache

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
<p>We should be at way more than 1500 downloads in total by now… 1405 on the
 Germany 1 mirror, more than 100 on Germany 2, an unknown lot on Japan, more
 than 60 BT downloads from me and friends… that accumulates quite.</p>
----
Date: 24.03.2008
Author: tg@

<p>I seem to have a sort of fan club, mostly related to <a
 href="@@RELPATH@@mksh.htm">mksh</a>, but also to <a
 href="@@RELPATH@@jupp.htm">jupp</a>. Interesting.</p>
<p>Benny has built 1503 binary packages, amounting to about 954 MiB of
 data. Uploading…</p>
<p>We just got an email about Metalinker, which looks interesting enough
 to try, from its primal developer Anthony Bryan. We now have it ☺</p>
----
Date: 28.03.2008
Author: bsiegert@

<p>Wow, my first posting in this new weblog. My laptop, a new MacBook
 Pro, spent about 10 days over easter in order to really do a MirPorts
 bulk build. 1503 binary packages for MirOS #10 have been uploaded to
 the mirrors. This has also been an occasion to review some largely
 untouched parts of the tree. Most of the problems seen are related to
 missing distfiles, changed download URLs, etc. Some packages did not
 build during th bulk build but when run non-recursively, they
 worked.</p>

<p>Some bugs in the resulting packages remain: You must manually install
 the expat package for most of the stuff to work. gtk+ insists on
 writing to /var/db, which makes it unsuitable for AS_USER builds.
 firesomething only when works as <tt>firefox</tt>. Still, this gives
 you a wide variety of pre-built packages for the new release.
 Enjoy!</p>
----
Title: On Firefox Updates
Date: 02.04.2008

<p>When Mozilla Firefox(TM) aka <tt>www/firesomething</tt> version
 1.5.0.10 came out over a year ago, I tried porting it (of course).
 However, not only did the build not finish, it filled the entire
 filesystem before failing. At the time, I was updating from something
 like 1.5.0.4 so I did not know which version exactly caused the
 problem. Thus, I made incremental updates up to 1.5.0.8, where I
 seemingly lost interest. Now, with a faster build machine, I
 continued the updates, discovering that 1.5.0.10 is really the
 version that fails.</p>

<p>A diff between <tt>firefox-1.5.0.9-source.tar.bz2</tt> and
 <tt>firefox-1.5.0.10-source.tar.bz2</tt> is 10 MiB. Most of that is
 in CVS directories, which are included in their fucking releases,
 believe it or not. If you leave out those changes, the diff is still
 5 MiB and 155000 lines, of which 90% are in <tt>security/</tt>.  Mind
 you, the whole source tarball, from calling the directory
 <tt>mozilla</tt> instead of adding a version number to including CVS
 directories to using several different build systems, leaving unused
 configure scripts in the tree, etc., positively REEKS of a flagrant
 disrespect for those that build from source. All this seems to be
 meant to encourage you to use official Mozilla builds&mdash;which is
 fine if you happen to be on one of the few supported platforms:
 Windows, Mac OS X, and Linux i386. We are not.</p>

<p>Anyway: in their infinite wisdom, the Firefox developers chose to
 upgrade the included NSS libraries (Netscape Security) from 3.10.x to
 3.11.4 <em>in a minor security update</em>. This version sports
 extensive internal restructurations&mdash;another nice way of saying
 "fuck you, porters". Thank you, Mozilla project. Of course, the NSS
 update is not explicitly mentioned in the release notes.</p>

<p><a
 href="http://www.mozilla.org/projects/security/pki/nss/tech-notes/tn6.html">This
 tech note</a> says: "The low-level freebl cryptographic code has been
 separated from softoken on all platforms. Even on platforms for which
 there is only one implementation of freebl, there is now a separate
 freebl shared library. The freebl library implements a private
 interface internal to NSS." This new library is the core of the
 problem. After the NSS libraries are built, they are
 cryptographically signed by a program called <tt>shlibsign</tt>
 which, in turn, dumps core, generating a 3 GiB core dump in my
 case!</p>

<p>I had suspected a problem related to our security features,
 especially W^X. The page about <a
 href="http://developer.mozilla.org/en/docs/Building_on_Fedora_Core_5">Building
 on Fedora Core 5</a> says: "For those with SELinux in enforcing mode,
 you are likely to run into problems both with the shlibsign during
 the build process and with the running the final build related to
 SELinux denying execmod permission&nbsp;..." However, with some
 difficulty, I managed to build a debug version of everything for
 analyis with gdb. During the start of shlibsign, one of the init
 procedures loads the native freebl (?) module, which promptly loads
 itself. On and on, until memory exhaustion.</p>

<p>This comment in <tt>security/nss/lib/freebl/Makefile</tt> provided
 a clue to the solution:</p>

<pre># The blapi functions are defined not only in the freebl shared
# libraries but also in the shared libraries linked with loader.c
# (libsoftokn3.so and libssl3.so).  We need to use GNU ld's
# -Bsymbolic option or the equivalent option for other linkers
# to bind the blapi function references in FREEBLVector vector
# (ldvector.c) to the blapi functions defined in the freebl
# shared libraries.
ifeq (,$(filter-out BSD_OS FreeBSD Linux NetBSD, $(OS_TARGET)))
    MKSHLIB += -Wl,-Bsymbolic
endif</pre>

<p>Adding MirBSD to the OS list fixes the build. And it works!</p>

<p>Now, firefox 1.5 is old and unsupported. So why was this update
 important? It makes further updates possible. The same bug was
 holding up my long-finished firesomething-2.0 port. I already have a
 package for firefox 2.0.0.13 but the port needs just a little more
 work. I am also confident I will be able to provide a working port
 for firesomething 3 when released.</p>
----
Date: 10.04.2008
Author: tg@

<p>I haven’t written here for a while, but I just want to get one
 thing said. I might have done what Sun feared <em>first thing</em>
 after I got a Java™ VM (even if it’s only single-threaded Ewe for
 embedded systems) running stably on MirOS… it now has a native
 method arc4random_pushb(3)… yeah!</p>
<p>Entropy is determining a lot of my life these days anyway. For
 example, accidentally sleeping too few, too much or at weird times,
 being phoned by random people, talking with Vutral about further
 possible improvements in our RNGs, being asked by CAcert.org if we
 are suitable OS for their high-security boxen (almost, but we’ll
 fix the missing parts, and some they’ve got to do themselves as
 no off-the-shelf OS does), and reporting in huge masses of entropy
 to <a href="https://www.cacert.at/cgi-bin/rngresults">CAcert.at
 Research Lab</a> – some 128 MiB samples with Firesomething “Bon
 Echo”, as Opera ISE’d out and Lynx just first ate up all CPU then
 none at all any more without monitorable activity…</p>
<p>Ah, and BOINC is running stable on MirBSD. MidnightBSD has some
 issues, mainly due to the fucked-up FreeBSD kernel and brandelf.</p>
----
Date: 12.04.2008 21:59:14
Author: tg@
Title: a few news items
Tag: geocache

<p>As you can <a href="@@RELPATH@@permalinks/news_e20080412-tg.htm">read</a>,
 quite a few new versions of our portable software has been released. Well,
 sort-of-portable, but for nroff I plan on improving, and MirMake 2 will be
 a lot better too, kinda like <a href="@@RELPATH@@mksh.htm">mksh</a>.</p>
<p>Geocacheing continues:
 <img src="http://www.opencaching.de/images/statpics/statpic106521.jpg" alt="OpenCaching.de" />
 <img src="http://img.geocaching.com/stats/img.aspx?txt=Hacking+MirBSD+since+2002&amp;uid=d6aaa6ad-797c-419a-91b3-8cf6a5b40658" alt="The Frog Site" />
 <img src="http://www.terracaching.com/statsban/15089.gif" alt="Rare Jewels" />
 <img src="http://geocaching.gpsgames.org/cgi-bin/sig.pl?user=mirabilos&amp;txt=Proud+OpenCaching.DE+user" alt="Broken Webpages²" />
 <br />
 Even Jonathan got hooked now. We found another (his first) two today.</p>
<p>As we’re sort of a big family, you’ll occasionally find German-language
 postings here. Don’t wonder. We have people who especially read that.</p>
<p>Ah, and while we’re at stats bragging:<br /><img alt="BOINC stats"
 src="http://www.boincstats.com/signature/user_1525395.gif" /><br />These
 were made on gecko2’s Intel Mac (Darwin), my laptop (MirBSD), and a few
 even on hephaistos (GNU/Linux). MidnightBSD needs to use brandelf, thus
 execution of Linux/i386-ELF binaries fails or, after branding, checksum
 verification (which BOINC does) fails. Sucks to be FreeBSD derived.</p>
<p>I’ll be in Switzerland (Cōnfœderatio Helvetica) next week, while Benny
 happens to be on vacation on Mallorca (hopefully not near the war zone
 called Ballermann). Development may slow down a little due to that (no
 more 100+ CVS spa^H^H^Hmails per day, yay!) but will not stall.</p>
----
Date: 12.04.2008 21:26:39
Author: tg@
Title: Willkommen, Schweiz!
Language: de

<p>Da wir ja alle eine große <a href="https://www.symlink.ch/">Familie</a>
 sind, möchte ich hiermit Grüße (Grüsse?) an die Schweizer Leser, die dieses
 Weblog (nein, ist kein Blog) auf <a href="http://planet.symlink.ch/">Planet
 Symlink</a> entdecken, senden.</p>
<p xml:lang="la">Ad auditorēs qui nōn possunt legere linguam germanicam:
 Salvete amici Cōnfœderationis Helveticæ!</p>
<p>Ich bin übrigens Mitte der Woche in Basel zu Besuch, Benny ist leider zur
 Zeit auf Mallorca, Urlaub machen. (Hoffentlich fernab vom Kampfgebiet, äh,
 Ballermann und so.)</p>
----
Date: 13.04.2008 03:10
Author: tg@
Title: current state: annoyed

<p>How can <a href="http://marc.info/?m=120805623420666">a bug like this</a>
 be unnoticed for so long, while the two source code lines in question were
 specifically touched and diffs reviewed by big names such as deraadt?</p>
<p>Of course it’s me who has to fix longstanding bugs from 386BSD, VIA C3 AES
 data corruption bugs in the OpenBSD kernel, LP64 bugs in OpenSSL, etc.</p>
----
Date: 14.04.2008 11:32
Author: tg@
Title: my first advisory

<p>XTaran mentioned that there is a Secunia advisory for mksh: <a
 href="http://secunia.com/advisories/29803/">SA29803</a>. Wow. This would
 then be my first one. But people really cannot read: the advisory states
 it appies to “Secunia Product #18328: MirBSD Korn Shell 3.x” – WTF?
 I mean, version numbering surely is difficult these days, with Linux and
 related software often having four or more decimal points(!) in them…
 but I reported it to them using their web site form.</p>
<p>I don’t know why Secunia made this advisory, but I suppose the Fedora
 person has his hands in there, as he told me yesterday that he needs an
 advisory for marking the update as security fix in their package system.
 I told him that this is not a lack of wanting to document, or even lack
 of communication (skills), but that I merely don’t know how this kind of
 issues is usually handled “out there”. I haven’t dealt with GNU/Linux
 any more since I started using OpenBSD back then in 2.9 times, and then,
 this procedere wasn’t widely used.</p>
<p>Ah, speaking of OpenBSD. They are sometimes not even at fault when <a
 href="https://www.symlink.ch/article.pl?sid=08/04/03/1650241&amp;mode=nested">a
 bug report is mis-communicated</a>, even if some people don’t believe it. And
 they don’t do the major/minor game either. They just still have the decimal
 dot for hysteric raisins.</p>
<p>Actual user feedback matters. My fork (MirEwe, just to annoy Jonathan) of
 the <a href="http://www.ewesoft.com/EweInfo.htm">Ewe VM</a> now has a fix,
 or rather workaround: when opening serial devices, “/dev/” was prepended to
 the device name. Now if users enter “/dev/ttyUSB0” (leenocks) things don’t
 work – but this is hard to debug. MirEwe now warns and does the right thing.
 The warning is in there for portability ☺</p>
<p>Ah, and: I could finally log my first (locationless, though) TerraCaches.
 That makes me an active user of all known platforms. Even if it cost me an
 entire night of re-reading a book I knew from a looong time ago. But actual
 caches will follow, and I’m even already planning to plant some myself.</p>
<p>Basel is getting nearer. I’m still not too happy with the option to move
 away from here. We’ll see – at least I’m going to take a big chance when I
 see one, and peek into how it is over there. Even if Benny is on Malle.</p>
----
Date: 17.04.2008 20:47
Author: tg@
Title: Geocacheing in Basel
Tag: geocache

<p>This time I <em>did</em> find a geocache far away from home…</p>
<p><img src="http://img.geocaching.com/stats/img.aspx?txt=Gr&#xFC;ezi+&#x2F;+Salut+&#x2F;+Bonjour!&amp;uid=d6aaa6ad-797c-419a-91b3-8cf6a5b40658"
 alt="Only two OCs here, sadly…" /></p>
<p>… in contrast to when I was in Bruxelles, as Benny and gecko2 didn’t seem
 to want to have time for that (or walk at all, they coerced me into the
 tram). This time, I went cacheing with Tonnerre, and he kind of lined it.</p>
<p>Time to push opencaching in Switzerland. He said he might even drop some
 caches (although – jokingly I hope/suppose – his first idea was „Finding
 Sandro“, where the cache is a person… or his home appartement). Likewise,
 I’ll push OC (and, a little, TC) whereever I’m going to live or lived.</p>
<p>While here, special greetings to the TGIF@BS meeting which I won’t attend,
 as I’ll take an earlier train back home tomorrow. It was nice here, much more
 so than in, for instance, Berlin.</p>
<p>Perl is evil. But knowing the basics of other programming languages helps.
 I guess I’ll invest some time into learning perl better, so that I can get
 rid of it (in MirPorts, for example), and better understand what others try
 to write in it (so it can be converted to mksh if possible, or at least
 fixed or optimised).</p>
<p>People can be quite annoying at times (mostly in Jabber, but also via
 eMail or IRC). Hey, if I just don’t reply my current location per eMail,
 sending another one asking specifically for it <em>again</em> isn’t going
 to improve my mood. Neither is constantly annoying me with enquiries about
 whether I’m really gonna move („zügeln“) here or not, <em>after</em> I had
 already stated I’ll think over it next weekend (or so), since I have a few
 reasons pro et contra, some of which are <em>orthogonal</em> to what I see
 here. I concentrate on getting a feel right now. Oh, and texting me one
 messager after another in Jabber (or, worse, by SMS to my Natel) even if
 I don’t reply (which, on the other hand, does <em>not</em> imply I’m willing
 to conversate either!) just gets on my nerves. And: go fucking RTFM, and
 don’t fucking bother me with „the XXXXU2B controller doesn’t exist, because
 the vendor website only lists the XXXXU2W“ – if you know <em>any</em> vendor
 websites you should long know better than to trust them.</p>
<p>For what it’s worth: for building MirEwe, you need <em>very current</em>
 MirMake (at least 20080411), g++, GTK+1.2, GTK+2, libjpeg, zlib, and their
 development headers. It should work on GNU/Linux and the BSDs for now. No
 platform other than i386 has been tested yet, but I’ll take on the Zaurus
 running OpenBSD, I guess, as I finally got the uplcom(4) working. Ah, and
 to rebuild the class libraries you need ecj and paxmirabilis/MirCpio – I
 did the ecj part on Debian and the rest on MirBSD.</p>
----
Date: 20.04.2008 02:34
Author: tg@
Title: Back home again
Tag: hardware mksh

<p>Back home… there just ain’t such place as [::1]… (that’s localhost for all
 of you who don’t use BSD). Swinging on the bike and going to the ice dealer,
 the best of them all. It was kind of nice in Switzerland and it’ll be a hard
 decision for me whether I’m going to move there or not. But after arriving
 at home, past the bike tour, I fell into sleep pretty soon. Travelling may
 be interesting, but it sure is tiring.</p>
<p>Too bad I couldn’t find the two geocaches I looked for on the way back.</p>
<p>I hacked some <a href="@@RELPATH@@mksh.htm">mksh</a> on the train, until
 I had no power left in the batteries… the laptop literally just went off
 all suddenly… and continued that until now. We have some quite interesting
 new features in now, only sad point is that we still can’t hexdump NUL.</p>
<p>I should definitively get my new server (tear) running now, for which the
 only dependency left ought to be the updated vnd(4) crypto stuff. This will
 take a while, as I’ll design a new on-disc format as well for improved
 security (think of keys, IVs, and so on). After that’s done I’ll give y’all
 a snapshot of MirOS-current, and update a <em>lot</em> of ports.</p>
<p>Maybe I should work on bringing a regular sparc boot floppy into the tree
 as well – last time, I had to hand-craft one. But it will be lacking.</p>
<p>There’s so much interesting stuff to do. Working on the Zaurus, ALIX, my
 SPARcstations (still no big monitor yet, so I couldn’t test Miod’s patch to
 make tvtwo(4/sparc) work yet), more FreeWRT devices… but I can’t neglect my
 dayjobs either. And I ought to learn to read and fix Perl *sigh*</p>
<p>This sucks: I have network (internet) outages since last night. Sometimes,
 ppp(8) + pppoe(8) still work when pppoe(4) doesn’t, but most of these times,
 both are unusable. The rest of the time, I sometimes have huge lags. My ISP
 (which unfortunately is a telco, but they aren’t completely clueless either)
 wanted to upgrade me from a 4 Mbit/s connection to a 6 Mbit/s connection as
 the old product doesn’t even exist any more (and I’ll save 10 €/month now),
 and the cable length (230m) isn’t an issue either. Testing today (as per the
 salesman I should have it May 1st, per the acknowledgement mail April 15th)
 I’ve got about 6 Mbit/s down, but my upstream speed is even reduced! WTF?</p>
<p>Argh! Later on this night, my network connection is <em>so</em> flakey…</p>
----
Title: pcc sucks
Author: tg@
Date: 20.04.2008 03:52

<p>I probably could compile mksh on <a href="http://pcc.ludd.ltu.se/">pcc</a>
 again… if pcc would compile itself. Hey, this one is about the contrary of
 OpenBSD or lynx, where development versions are stable… pcc should warn
 before cvs upping.</p>
<p>Every time I try to build <a href="@@RELPATH@@mksh.htm">mksh</a> with
 pcc, either it’s totally b0rked or I have to fix it. Today: ragge doesn’t
 understand autotools. (He added a test to configure.ac which ① gives a
 syntax error when failing, ② fails when compiling pcc using pcc as the
 compiler, ③ doesn’t show up if <tt>/lib/cpp</tt> exists (on GNU/Linux, I
 suppose), ④ produces a broken cpp(1) executable if it fails, ⑤ doesn’t
 even test for the thing it is supposed to check.)</p>
<p>Oh, and the charsets of the mails are b0rken. (WTF windows-1252 when I
 send UTF-8?) See all the ugly details here (XXX insert link).</p>
----
Date: 20.04.2008 21:42
Author: tg@
Title: more rants

<p>I already ranted about pcc… well, I got a reply to my <em>first</em> mail
 to the pcc list (where the second one cleared up the five things mentioned
 in the previous posting), a sort of still friendly one-liner, to which I
 replied with that he should probably read my other mail, to which I only
 got an unfriendly comment that “you are wrong”. Hah! (Well, I got my “pcc
 -E” fixed.)</p>
<p>I guess I just cannot recommend to use pcc, and will have to maintain my
 own set of patches. Trying to get them upstream shipwrecks on a barrier of
 incompetence, regarding not only autotools but also how a compiler (cc(1)
 standard interface) must work: at first, on -O (or -O*), pcc did simply an
 <tt>Oflag++;</tt> which I mentioned as wrong (adding a fix)… but <a
 href="http://marc.info/?m=120866404218935">look for yourself</a>. Oh, and
 they reply using weird – OpenBSD (latin1) or Windows (cp1252) – encodings
 on mails properly sent using Unicode (UTF-8), as is the default in sane
 operating systems like MirOS and <a href="http://9fans.net/">Plan 9</a>.
 Incompetence whereever you look. This matches the interesting UCB hack in
 mv(1) I recently found… or OpenBSD’s inability to port GNU tools.</p>
<p>Also, I suppose my ISP/Telco is going to get some angered tg@ tomorrow.
 The <a href="http://www.pool.ntp.org/scores/87.79.237.121">NTP Pool</a>
 scores show that I’m suffering from <em>a lot</em> of network hiccups.
 This LCP fluctuation kind of sucks, as does the current transfer rate.
 Just the latency is still surplus, 11.2ms to heise.de (suckers as well,
 but for totally different reasons) and 18.3ms to google.com (also suckers,
 for a couple of yet another reasons I think I already elaborated).</p>
----
Date: 21.04.2008 11:36
Author: tg@
Title: when ranting helps

<p>Today’s <a href="http://pcc.ludd.ltu.se/">pcc</a> from anoncvs bootstraps
 successfully and builds mksh just fine, and is amazingly fast (almost en
 par with Microsoft’s compiler). Wow, they fixed all the things I ranted
 about in my earlier postings. Congratulations, pcc team.</p>
<p>Now tcc and TenDRA/Ten15 (schizo) are next (mainstream compilers failing).
 And LLVM/clang and ACK deserve testing.</p>
<p>I wish ranting would help with my internet connection… gotta fight with
 the ISP/Telco now.</p>
----
Date: 21.04.2008 19:33
Author: bsiegert@

<p>Just returning from a week in the south, and feeling well. By sheer
 verpeil0ring, I was away the whole time that tg@ spent in Basel, just
 a few kilometers from here. But those holidays were necessary, and I
 enjoyed them very much. @work, there are new <i>stagiaires</i> of
 which I don't even know the name but it does not look as if anything
 had moved during my absence ;).</p>

<p>I am trying to port ttftot42, a nifty utility for converting
 TrueType fonts to PostScript Type 42 (which seems to be
 straightforward) and, more interesting for me, can create AFM files
 for them. Using those fonts in Teχ is only an <tt>afm2tfm</tt> away
 then. The last version is from 1999 and needs freetype 1. The
 author&mdash;very responsive indeed!&mdash;says this is not yet fixed
 but promised to send me a hg snapshot. While here, we now have a
 mercurial (hg) port ;).</p>
----
Date: 21.04.2008 20:13
Author: tg@
Title: more creative uses for ttftot42

<p>The ttftot42 utility I asked bsiegert@ to port was actually mentioned
 in some GNU groff documentation as a possible way to use OpenType fonts
 in ps/pdf manpages. I always liked the Gentium font (which we use for
 the MirOS CI/CD), and starting from when I first saw it, I hated anything
 remotely looking like the Courier font, so I guess this means that the
 PDF version of mksh’s online manpage will soon have a new look.</p>
<p style="margin-bottom:0px;">On an unrelated note:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;">
 <pre>
	Apr 21 20:09:06 herc ppp[28555]: tun0: LCP: deflink: RecvTerminateReq(206) state = Opened
	Apr 21 20:09:06 herc ppp[28555]: tun0: LCP: deflink: LayerDown
	Apr 21 20:09:06 herc ppp[28555]: tun0: LCP: deflink: SendTerminateAck(206) state = Opened
	Apr 21 20:09:06 herc ppp[28555]: tun0: LCP: deflink: State change Opened --> Stopping
	Apr 21 20:09:06 herc ppp[28555]: tun0: CCP: deflink: State change Stopped --> Closed
	Apr 21 20:09:06 herc ppp[28555]: tun0: CCP: deflink: State change Closed --> Initial
	Apr 21 20:09:06 herc ppp[28555]: tun0: Phase: deflink: open -> lcp
 </pre>
</div><p style="margin-top:0px;">(not using pppoe(4), to enable debugging)</p>
<p>For me, this very much looks like my ISP doesn’t like my nose or something
 and wants the ADSL (ppp(8)+pppoe(8)) session to terminate.</p>
<p>Another unrelated side note: MirOS <tt>ports/math/boinc</tt> definitively
 is able to return valid results to some projects (although some of these
 which work require setting the primary platform to Lunox, but I’m trying to
 get that bug on their server-side fixed.</p>
----
Date: 22.04.2008 12:39:14
Author: tg@
Title: sometimes, ranting doesn’t help…

<p>… but calling does. The bad part is that the internet support number starts
 with <tt>0900…</tt>, which means it cost me 1.69 €/min (and the call took me
 about 3‥4 minutes), but on the other hand, they quickly fixed the issue, sent
 me an SMS that they did it (just, sadly, not what it was), and since then, I
 haven’t been forcefully disconnected any more. This is good.</p>
<p>Now I’ve just got to look if this is stable, then re-measure my bandwidth.
 And in May, I’ll get even better upload (736 kbps instead of 608 kbps).</p>
<p>Verpeilungsfaktor stories: in our weblog source, we use RFC822 style header
 lines: “Date”, “Author”, and… “Title”. Not “Subject”. And I wondered why the
 posting headline wasn’t shown… Since we’re on Planet Symlink now, I try hard
 to find a matching one for each posting, because it looks stupid there with
 just the date.</p>
<p>Another one: we use four dashes on a line by themselves for separating log
 entries; the <a href="@@RELPATH@@mksh.htm">mksh</a> regression test uses <a
 href="http://cvs.mirbsd.de/src/bin/mksh/check.t?rev=HEAD">only three</a>, as
 you can see. And yes, I fell for it (gave me a nice Perl error message over
 there, and a nice shell script induced error over here).</p>
<p>A last question (rhetorical: no answer needed, just nudging your brain):
 what do you do with your spare time, if everyone who’d to something together
 with you either moved away, is working or ill? And: if you were to move away
 yourself, would the situation improve, worsen or stay the same?</p>
----
Date: 29.04.2008 22:02
Author: tg@
Title: be careful what you wish for…
Tag: geocache

<p>… as you could get it. This is because gecko2@ asked for some more cvs
 commit eMail “spam” ☺</p>
<p>While on the spam topic: do <strong>not</strong> send an eMail to one of
 the following addresses: <a href="mailto:junk@mirbsd.org">junk@mirbsd.org</a>,
 <a href="mailto:junk@mirbsd.org">junk@mirbsd.org</a>, or <a
 href="mailto:junk@mirbsd.de">junk@mirbsd.de</a>, or, again, <a
 href="mailto:junk@mirbsd.org">&lt;junk@mirbsd.org&gt;</a>, <a
 href="mailto:junk@mirbsd.org">&lt;junk@mirbsd.org&gt;</a>, or <a
 href="mailto:junk@mirbsd.de">&lt;junk@mirbsd.de&gt;</a> (greytrapping)</p>
<p>Luckily, my internet uplink has been stable for more than 4⅓ days now,
 after repeated phoning (an 0800 number then) and resetting the NTBBA.</p>
<p>Some more statistics:</p><!-- RSS stop -->
<p>Geocacheing continues:
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="OpenCaching.de" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="The Frog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 – now I’ve hidden my first two traditional micros (easy series), and
 one of them even is sort of a “<tt>lost+found</tt>” directory virtual
 cache overload.</p>
<p>BOINC continues, I’m in 9 projects now: <img alt="BOINC stats"
 src="http://www.boincstats.com/signature/user_1525395.gif" /><br />
 While only 8 projects show up at the moment, this’ll improve once
 the last project delivers in a result (it were more projects actually,
 but some don’t even work on hephaistos…) – now the first WCG valid WU
 returned from MirBSD! (MidnightBSD can’t, because I can’t run brandelf
 on the signed binaries of the apps… sucks to be FreeBSD derived ☻☺)</p>
<p>Ah, and, by the way: XTaran did not like external links, especially not
 secure links (https) in my wlog entries, so Planet Symlink doesn’t get
 them now (as it pulls via RSS), but you can look at it on the wlog.</p>
----
Date: 04.05.2008 00:10
Author: tg@
Title: MirEwe on MirDarwin?
Tag: geocache

<p>On an unrelated note, <a href="@@RELPATH@@mksh.htm">mksh</a> needs
 people running the current development version, to prevent mishaps like
 the one with the fullwidth characters causing wrong text output. To do
 that, use AnonCVS like this:<br /><tt>% env CVS_RSH=ssh cvs -qz3 -d
 _anoncvs@anoncvs.mirbsd.org:/cvs co -PA mksh</tt><br />Then, as usual,
 <tt>cd mksh &amp;&amp; (sh Build.sh &amp;&amp; ./test.sh -v) 2>&amp;1
 | tee log.txt</tt> to build and test it. Then, especially if it fails,
 <a href="http://nopaste.snit.ch:8001/">send</a> the logs to me.</p>
<p><a href="http://www.ewesoft.com/M2.htm">Ewe</a> is an embedded VM for
 some Java™ 1.1 compatible stuff. I had to fork it to use it on MirBSD
 and to be able to fix it. So well. It now builds on gecko2@’s Macbook.
 Using MirMake, of course *g* It’s even usable… which means that he can
 now use <a href="http://www.cachewolf.de/">CacheWolf</a> and his laptop
 to go geocaching.</p><!-- RSS stop -->
<p>Speaking of geocaching: more stats bragging… although a little different
 this time:<br />
 <img src="https://flyingfish.freewrt.org/fwrtcommitstats/mirabilos.png"
  alt="mirabilos’ commit stats" /><br />
 <img src="https://flyingfish.freewrt.org/fwrtcommitstats/pfeffer.png"
  alt="Dr. Pfeffer’s commit stats" /><br />
 <img src="http://img.geocaching.com/stats/img.aspx?txt=Mac+Fanboy&amp;uid=d57c5767-047b-4aff-a00a-784356b94e9e"
  alt="gecko2@’s founds and hides" /><br />
 Although only the first two are CacheWolf committers…</p>
<p>Ah, damnit. It freezes the usbserial (Prolific) driver when accessing
 the serial port. Well, Apple… they don’t even use GNU as(1) either.</p>
----
Date: 12.05.2008 23:50
Author: tg@
Title: all hardware sucks, all software sucks...

<p>Happy birthday, <a href="http://www.midnightbsd.org/">laffer1</a>!</p>
<p>Whew. We have a new qemu port, but it doesn't boot MirBSD/i386 any more.
 It almost boots MirBSD/sparc now though. Luckily I could backport the new
 port's ability to use kqemu. Thanks to Fabrice Bellard and the OpenBSD ports
 guys for this.</p>
<p>The Zaurus... SL-C3200... it's a neat device, but after I managed to get
 the pl2303 LKM cross-built (bah!), along with the usual tools mksh(1) and <a
 href="@@RELPATH@@jupp.htm">jupp</a> as well as pax(1)mirabilis for the ability
 to extract my CacheWolf profile onto a (FAT) filesystem - did I mention just
 how much busybox sucks? - Ewe doesn't work. Meh. Go to OpenBSD/zaurus, enter
 a SIGBUS in gtk+1.2 - exactly what I want. The gtk+2 version works, but now,
 X.org plus GTK+2 plus Ewe (Java&trade; Ranz!) eat up all of the 64 MiB RAM
 plus initially 4 to 8, later 20 to 40, MiB swap. Not nice. (Some people are
 said to use a CF card for swap due to it being faster than the internal HDD,
 a microdrive. Geez.) If I'm cycling with more than say 5 km/h, the moving map
 hinders parsing the GPS symbols... NMEA 0183 at 4800 bps. But I managed to
 find another cache before going totally crazy.</p>
<p>After Linux (grml, FrOScon edition) has destroyed my NTFS partition, now
 the ext2fs driver has managed to impale quite some of my FFS filesystems
 again. This time, Linux isn't even at fault. (Hm, fsck_ffs(8) and e2fsck seem
 to have a common ancestor.) The downside however is that my encrypted home is
 now gone. Totally gone, as in, fsck deleted the dirent, inode, and allocation
 of blocks.<br />Yeah, I have backups, but only for the most important things,
 not for everything, and quite old ones. I have had to restructure my storage
 use anyway, now's a good time for it. Hah! And that after I chose to use
 ext2fs ipv msdos for a common data xfer partition between BSD and Win2k due
 to msdosfs eating up long filenames when a directory has a lot of them, even
 on OpenBSD 4.3/zaurus FWIW.</p>
<p>While I was quite reluctant to hack anyway recently, or even to idle in
 IRC or, worse, Jabber, I guess this'll throw me back even more. MirBSD isn't
 affected, except in further development becoming delayed.</p>
<p>There will most probably be a snapshot of MirBSD-current really soon. But
 other work (mksh R34, mirmake in Debian, MirEwe, ports, gcc) is postponed;
 I will try to focus on the more important things (AES vnd(4), improvements
 for CAcert, merging OpenBSD-current maybe even, but that not before the
 migration to <tt>tear</tt> is complete). OTOH, for both MirPorts on !MirBSD
 and pkgsrc&reg; on MirBSD, I have laid foundation for others to build upon.
 Maybe they will.</p>
<p>Just a side question: why don't things just work every once in a while?
 And why, oh Murphy, do things go wrong the worst way possible, always?</p>
----
Date: 13.05.2008
Author: tg@
Title: No, I won’t.

<p>We have lived for 25 years with the seekdir bug, and even if it’s now on
 slashdot this does not mean we will immediately patch it. Besides, bringing
 that part of libc in sync with OpenBSD will involve libc and libpthread
 shlib version major bumps, which is a bit overkill for this diff.</p>
<p>It will go anyway with the upcoming merge of more recent OpenBSD base
 code. There are more pressing issues. But I have looked into it.</p>
----
Date: 20.05.2008
Author: tg@
Title: Improving the world, yet again

<p><a href="@@RELPATH@@ports.htm">The MirPorts Framework</a>, which also
 runs on <a href="http://www.midnightbsd.org/">MidnightBSD</a>, is the
 first to bring native firesomething support to said operating system,
 almost effortless thanks to our good portability infrastructure, and
 because bsiegert@ has already done the dirty work porting it to MirBSD.
 Thanks, Benny! And thanks Lucas for the chance to prove the superiourity
 of our infrastructure. And ctriv, don’t take it too hard, just take our
 patches and put them on your mport.</p>
<p>Hardware sucks. The Z doesn’t power on after it has been shut down for
 a while. The CF wi(4) is broken. Software sucks. And we all know it. <a
 href="http://www.DaemonForums.org/">A web forum</a> sucks. They probably
 will never learn it. Yet people support their… attitude. Americans suck,
 but that’s not news. Luckily, there are a few not totally clueless ones.
 Life sucks, and bureaucracy sucks even worse. And there’s no way around
 <em>that</em>. Too bad. (I had an encounter with bureaucrats again… could
 you tell? Hah. They want money back, even though it belongs to me.)</p>
<p><strong>Update 21.05.2008:</strong> Benny has committed an update to
 firesomething-2.0.0.13-0, and I bumped the dash ver and made it work as
 well on MidnightBSD. Sample build:</p>
<pre> $ cd /usr/mirports/www/firesomething
 $ mmake install clean PKG_CONFIG_PATH=$(mmake show=PKG_CONFIG_PATH):/usr/local/libdata/pkgconfig</pre>
<p>You must have installed fontconfig from mports (and, of course, perl,
 for MirPorts to work at all.</p>
<p>This beast now works on MirBSD/i386 and MidnightBSD/i386, should work
 on OpenBSD/i386, OpenBSD/amd64, OpenBSD/alpha, OpenBSD/powerpc,
 OpenBSD/sparc, OpenBSD/sparc64, and possibly MidnightBSD/amd64 and
 MirBSD/sparc (not yet on MidnightBSD/sparc64, but they’ll want to test
 and fix that). No idea about Darwin and Interix. Benny is going to bump
 to the latest upstream version now, whereas Jonathan recommended us to
 go to 3.0b2 for increased speed and decreased resource use. We’ll see.
 The mports maintainers can now take our patches and get rid of their
 linuxulated firesomething binary port ☺</p>
----
Date: 24.05.2008 01:00
Author: tg@
Title: kqemu

<p>Last time I had tried qemu+kqemu (on GNU/Linux), it made BSD segfault,
 kinda like VirtualBox nowadays. But things seem to have changed: I ran
 the Linuxtag 2008 Live CD Edition inside it (on MirBSD) with no problems
 at all. Nice, and shows that BSDs can have LKMs.</p>
<p>Now missing: vmxnet source code… or evil BLOB? I suppose the latter.</p>
<p>Unrelated side note: Netcologne is cool, but they suck: you can only
 change the PTR for your static IP, which you pay 4.90 € per month for, if
 you’re a business customer. No IPv6 anyway (but SixXS has a new PoP, out
 of all places in Düsseldorf *evil grin*). And Strato gives gecko2@ two IPs,
 but only allows the MAC of the built-in NIC (so no bridging to domU or VMs).
 Why can’t they ever do something not totally clueless? (Okay, I could ask
 the support… Netcologne support even phoned me back after my eMail enquiry
 apparently went through their entire house until they could figure out what
 I need (to mail Fefe, who blocks PTRs like foo-www-xxx-yyy-zzz.ISP), but
 rejected; Strato support is, from my past experience, hopeless.)</p>
----
Date: 27.05.2008
Author: tg@
Title: Linuxtag 2008, Berlin, .de
Tag: event

<p>This year's <a href="http://www.linuxtag.org/">LinuxTag</a> will not go
 by without the BSD projects exhibiting their fine software. Of course, we
 will attend &ndash; the usual gang (Benny and me, gecko2 and Przemek will
 help out). New is that we'll also be distributing a couple of MidnightBSD
 CDs and flyers I had a helping hand in creating, as they are US based and
 won't be able to make it to Germany for this event. This all would not be
 possible without the help of allbsd.de, again. Thanks, Daniel!</p>
<p>The MirBSD CDs distributed contain a Live + Install CD, as usual, of an
 unnamed #10-stable snapshot, plus a couple of packages, including Benny's
 new firesomething port instead of opera-linux. The MidnightBSD CDs aren't
 as big and miss the install part, but are a relatively new and especially
 stable 0.2-CURRENT snapshot (including <a href="@@RELPATH@@mksh.htm">mksh</a>
 of course).</p>
<p>We'll attend Tuesday (probably late) till Saturday.</p>
----
Date: 13.06.2008
Author: tg@
Title: Getting things done… slowly
Tag: hardware

<p>While “the swiss are laggards, and the people from Bern are the slow
 motion of switzerland”, other things take their time as well. However,
 vnd(4) updates have started, and other encryption schemes (including a
 hardware-accelerated AES variant for Columbo0815 from #IceWM) will end
 up in the code very soon, as promised.</p>
<p>During hacking, I spot other things – bugs in the random(4) code, as
 well as improvements to the kernel and XFree86® possibly leading to my
 pcengines.ch ALIX.1c board to be supported (thanks to undeadly.org for
 keeping me informed). And Benny fixed ports bugs again, as well as put
 security updates for Freetype2 et al. into the tree. Thanks!</p>
<p>FWIW: Opera 9.50 segfaults on me. It can’t be updated thusly.</p>
----
Date: 25.06.2008
Author: tg@
Title: U+1E9E… and where innovation resides

<p>So the uppercase eszett – ‘ẞ’ (or <tt>‘ẞ’</tt> if your monospace font
 has it) – is <a href="http://www.golem.de/0806/60622.html">now an ISO
 10646 standard</a>. Your favourite BSD has been one of the first to add
 support for it to libc, a (contributed) keyboard layout, and even Markus
 Kuhn’s fixed-misc Unicode fonts, after the proposal with a real codepoint
 assignment came out. Not all Germans, nor typographers, but historicians,
 might like it, the discussion has been flamewar-like. But we <a
 href="http://blogs.msdn.com/michkap/archive/2008/05/15/8506679.aspx">knew
 this</a> all along.</p>
<p>Ah, by the way. No, we aren’t dead. Websites are irrelevant, but if you
 end up here, please read about <a href="@@RELPATH@@mksh.htm">mksh</a>
 anyway. Real questions are asked on <a href="@@RELPATH@@rss.htm#lists">the
 mailing lists</a> or in <a href="@@RELPATH@@irc.htm">IRC</a>. And we don’t
 have a handbook (yet), because with two developers, nobody has yet had
 enough spare time to write one, plus you’d need a couple of handbooks – one
 for people coming from Open/NetBSD (Lite-based), one for people coming from
 Free/DragonFly/MidnightBSD (386BSD-based), one for people coming from Unix®,
 one for the Apple followers, one for the GNU/Leenocksers, etc. You see?</p>
<p>And while here: Xcode 3.1 (on gecko2@’s Macbook) comes with llvm-gcc… but
 not in <tt>/usr/bin/</tt> but in <tt>/Developer/usr/bin/</tt>. It compiles
 quickly, produces fast and small code… kind of nice. If Apple brings <a
 href="http://llvm.org/">LLVM</a>+<a href="http://clang.llvm.org/">clang</a>
 into a usable shape to replace our gcc 3.4.6 (gcc4 has unsafe optimisations
 that cannot be turned off, and all other compilers produce bigger code,
 which breaks the installation media (especially floppies) and SPARC
 kernels), in a form usable as compact command-line compilers (and not just
 libraries for Xcode integration), I’ll be happy. (They’d just need to add
 mksh to Mac OSX then to make me even happier, but I guess I’m sort of late
 with that request. Even if it’s fully free – in contrast to GNU bash – and,
 in its most recent incarnations, even advertising clause free.)</p>
----
Date: 09.07.2008 22:40
Author: tg@
Title: Configuring name-based apache vhosts with SSL and IPv6…

<p>Configuring name-based apache vhosts with SSL and IPv6… is hard. Really.
 This is probably due to it being “a patchy webserver”. Here is a quick cut
 and paste solution, well, sort of.</p>
<p>Scenario: I have a web server running name-based vhosts on the SSL port.
 I get a either wildcard certificate, or – in my case – a certificate with
 some subjectAltName extensions set; <a href="https://cacert.org/">CAcert</a>
 supports these now. All vhosts I wish to serve must be included, and the
 primary commonName (as part of the distinguishedName) ought to be the host’s
 primary FQDN, and it <em>must</em> be duplicated as subjectAltName.</p>
<p>I wish to serve a default page (just the standard <tt>index.htm</tt> from
 <tt>/var/www/htdocs/</tt>) to everyone who does not provide a proper host
 name (e.g. speaking HTTP/1.0 without <tt>Host:</tt> header, or just probing
 my IP addresses), and a couple of vhosts to everyone else. I use one IPv4
 and one IPv6 address. The vhost configuration is placed in several files in
 <tt>/var/www/conf/vhosts/</tt> called <tt>«vhostname».«port»</tt>; if some
 information is to be shared (e.g. vhost on both port 80 and 443), these are
 placed in <tt>«vhostname».common</tt> and included by the port configs.</p>
<p>Important: Do not use wildcard vhosts, they won’t work and give errors. Do
 not use the <tt>_default_</tt> vhost in any form, it silently won’t work.</p>
<p>You might want to place directory information in the vhost configuration
 file instead of in the main configuration file.</p>
<p style="margin-bottom:0px;">Part of <tt>httpd.conf</tt> is:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;">
 <pre>
	ServerAdmin «mail address for the server itself»
	ServerName «main FQDN»

	NameVirtualHost 192.0.2.1 443
	NameVirtualHost 2001:db8:1234:1::1 443

	&lt;IfDefine SSL&gt;

	&lt;VirtualHost 192.0.2.1:443&gt;
	Include /var/www/conf/vhosts/eurynome.443
	&lt;/VirtualHost&gt;

	&lt;VirtualHost [2001:db8:1234:1::1]:443&gt;
	Include /var/www/conf/vhosts/eurynome.443
	&lt;/VirtualHost&gt;

	&lt;VirtualHost 192.0.2.1:443&gt;
	Include /var/www/conf/vhosts/call.443
	&lt;/VirtualHost&gt;

	&lt;VirtualHost [2001:db8:1234:1::1]:443&gt;
	Include /var/www/conf/vhosts/call.443
	&lt;/VirtualHost&gt;

	&lt;VirtualHost 192.0.2.1:443&gt;
	Include /var/www/conf/vhosts/default.443
	&lt;/VirtualHost&gt;

	&lt;VirtualHost [2001:db8:1234:1::1]:443&gt;
	Include /var/www/conf/vhosts/default.443
	&lt;/VirtualHost&gt;

	&lt;/IfDefine&gt;
 </pre>
</div><p style="margin-top:0px;">(using documentation addresses)</p>
<p>Make sure every vhost <em>except</em> the default one sets ServerName
 (and ServerAdmin if it differs), and DocumentRoot etc. as usual. The
 default vhost does <em>not need</em> to set ServerName, but the line<br />
 <tt>ServerAlias *</tt><br /> <em>must</em> be present <em>and</em> it
 <strong>must</strong> be the <em>last</em> vhost in the list, as above.</p>
<p>If you still have questions – especially now that even OpenBSD has <a
 href="http://undeadly.org/cgi?action=article&amp;sid=20080519151435&amp;mode=expanded">seen
 the light</a> and applied the IPv6 patch I not only applied to MirBSD some
 four years ago but also suggested to them some two or three times – come
 to <a href="@@RELPATH@@irc.htm">IRC</a> or drop us an eMail, and we’ll try
 to fix things. Apache is definitively historic ballast, but still common
 enough on todays Unices.</p>
----
Date: 09.07.2008 23:31
Author: tg@
Title: continuity

<p>Since quite a while I’ve had anger about BSDstats – their ports reporting
 stopped including ours (MirPorts Framework, NetBSD® pkgsrc®, OpenBSD ports
 tree, Debian dpkg), the maintainer was rarely reachable, at most by eMail,
 and the entire system had issues. Now, the site no longer exists, apparently
 nobody knows why, and our systems error out. Well, I have disabled BSDstats,
 this will probably make MirOS appeal more to privacy-conscious geeks again,
 and save us from getting more errors in our logfiles, especially the Live CD
 reporting was already totally broken due to weird User-Agent tricks.</p>
<p>I’ll now count on people just using <a href="@@RELPATH@@irc.htm">IRC</a>
 or so to say hi to us if they’re using MirOS, are happy or tell us things we
 could improve. Or meet us at <a href="http://www.froscon.de/">conferences</a>
 and pay for our beer ☺ and other beverages (we’re not BeerFSD after all).</p>
----
Date: 12.07.2008 21:15
Author: bsiegert@
Title: "Requesting inclusion of mksh (shell) into Mac OS X"

<p>This is the title of the bug report I filed with the Apple Bug Report Tool
 yesterday. The problem ID is 6069931; I think you can only see your own bug
 reports in the tracker though, so you may not be able to see my report. FWIW,
 I filed it against Mac OS X 10.5.4 (the current version), with "Feature (new)"
 as a severity. For reference, the full text of the bug report follows:</p>

<p>11-Jul-2008 11:58 AM Benny Siegert:</p>

<p>I would like to kindly request the inclusion of mksh as an alternative shell
 into future versions of Mac OS X.</p>

<p>mksh (the MirOS Korn Shell) is a Korn Shell derivative under a
 BSD-like licence. It includes the features from the OpenBSD ksh as well
 as additional bash compatibility. Almost all bash scripts run under
 mksh, however with a speedup of about a factor 2. The code was checked
 for security problems by Coverity, Inc. UTF-8 support is fully
 integrated. With all these features, it is still very small, just 240
 KiB as an i386 binary. The build process is done by a script called
 Build.sh, Mac OS is already a fully supported and maintained
 platform.</p>

<p>This could potentially replace the ksh93 included now as /bin/ksh or
 be installed side by side as /bin/mksh. In short, it can be regarded a
 more modern replacement for older ksh releases.</p>

<p>The homepage of mksh is located at <a
 href="http://mirbsd.de/mksh">http://mirbsd.de/mksh</a>. The current
 version is available from <a
 href="@@ABSPATH@@/MirOS/dist/mir/mksh/mksh-R35.cpio.gz">https://www.mirbsd.org/MirOS/dist/mir/mksh/mksh-R35.cpio.gz</a>.</p>
----
Date: 14.07.2008 00:00
Author: tg@
Title: Inclusion of the MirBSD Korn Shell
Tag: geocache

<p>As <a href="http://marc.info/?m=121469556601834">requested</a>, <a
 href="@@RELPATH@@permalinks/wlog-10_e20080712-bsiegert.htm">Benny</a>
 has written to Apple, Inc. about inclusion of mksh. Lucas “laffer1” Holt
 of MidnightBSD has said to follow, as has Andreas “gecko2” Gockel, the
 Fink maintainer for <a href="@@RELPATH@@mksh.htm">mksh</a>. Link to <a
 href="@@RELPATH@@permalinks/wlog-10_e20080714-tg.htm">this entry</a>.</p>
<p>Lucas actually said he would care more about and use mksh(1) if it
 were integrated in Mac OSX, as most MidnightBSD developers (like Benny)
 do most of their work on a Macintosh. He has integrated mksh in his
 operating system quite some time ago.</p>
<p>mksh is also the default shell, including <tt>/bin/sh</tt>, on <a
 href="https://www.freewrt.org/trac">FreeWRT</a> Embedded GNU/Linux.</p>
<p>Andreas already has run tests for using mksh(1) as <tt>/bin/sh</tt>
 on Darwin, although I did not request that personally, and brought up
 the question of <tt>/etc/profile</tt> adjustments and <tt>~/.mkshrc</tt>
 integration. (FreeWRT has a changed system-wide profile including a
 system-wide copy of the mkshrc file; other possible ways would involve
 setting <tt>$ENV</tt> or (preferred) placing <tt>.mkshrc</tt> in the
 New User’s Skeleton and in root’s home directory, if existent.</p>
<p>Strong points of <a href="@@RELPATH@@mksh.htm">mksh</a>: free (as in BSD,
 now even without advertising clause), small, fast, portable, easy to use,
 can run many ksh93 and bash scripts, is actively developed, and benefits
 from the BSD development style (central development, security focus).</p>
<p>To everyone with an Apple ID: please suggest to Apple to include mksh(1),
 write to them how good it is despite lacking popularity, how compatible it
 is, and just how much you like to use it. Even if you do not use it yourself,
 if you can follow our reasons, write to them. If you have access to other
 operating systems, do the same, especially with mere porting frameworks, as
 the OpenBSD ports tree still does not include our port, which was ready-made
 for committing by me to reduce workload for them.</p>
<p>Some unrelated side notes… Geocacheing continues:
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="OpenCaching.de" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="The Frog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 – Dr. Pfeffer especially liked mine<tt>^W</tt>Waldemar’s Zaurus SL-C3200 with
 CacheWolf running on Ewe… even if I still think it’s dead slow. Interestingly,
 porting Ewe to the iPhone G3 would not violate the clause preventing you from
 creating “instant messaging or real time navigation software”, and CacheWolf
 itself would not have to be ported. I’d like to have more RAM on the Z though
 – maybe via the SD Card slot?<br />SCSI sucks. And mksh gets better… IRIX,
 and a bug fix. Just still no SunOS 5.5 (missing <tt>/usr</tt> on the HDD).</p>
----
Date: 16.07.2008 23:42
Author: tg@
Title: mksh on… platforms

<p>Okay, so I installed Windows® 2000 and Interix again. And UWIN. And the
 Microsoft, Digital Mars, and Borland command-line compilers. And <a
 href="@@RELPATH@@mksh.htm">mksh</a> worked, of course.</p>
<p>Then I tried DJGPP. Yeah, mksh(1) for MS-DOS®. *sigh* GNU bash, the only
 shell available, SIGSEGVs on me trying to build anything nōn-trivial, even
 worse with gcc 4.2.3 than with gcc 3.2.3… but even pdksh could not be made,
 due to SIGCHLD missing. Too bad, no mksh for you, Mr “I don’t accept bug
 report mails from your IP, nor in the webinterface” Delorie.</p>
<p>The iPhone… will have to wait. We can install the BSD Subsystem and the
 Terminal application in gecko2’s SDK’s ARM emulator, then build and test
 for that. I just gave him the link to the BSD package, but he went to bed
 shortly before, so maybe tomorrow.</p>
<p>And then, mksh R35b can go out, we fixed some bugs and tested on more
 platforms (fixing testsuite shortcomings during that time, even).</p>
----
Date: 17.07.2008 21:43
Author: tg@
Title: mksh – The iShell [updated 2 times]
Tag: geocache mksh

<h3><a href="@@RELPATH@@mksh.htm">mksh</a> – The iShell</h3>
<p style="margin-bottom:0px;">Try this:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
	$ cvs -d _anoncvs@anoncvs.mirbsd.org:/cvs co -PA mksh
	$ cd mksh
	$ cat &gt;iBuild.sh &lt;&lt;-'EOF'
		DEV=/Developer/Platforms/iPhoneOS.platform/Developer
		SDK=${DEV}/SDKs/iPhoneOS2.0.sdk
		CC="${DEV}/usr/bin/gcc-4.0 -arch arm"
		CPPFLAGS="-I${SDK}/usr/include"
		CPPFLAGS="$CPPFLAGS -I${DEV}/usr/lib/gcc/arm-apple-darwin9/4.0.1/include"
		CPPFLAGS="$CPPFLAGS -F${SDK}/System/library/Frameworks"
		CPPFLAGS="$CPPFLAGS -F${SDK}/System/library/PrivateFrameworks"
		CPPFLAGS="$CPPFLAGS -F/System/library/Frameworks"
		LDFLAGS="-L${SDK}/usr/lib -L${DEV}/usr/lib/gcc/arm-apple-darwin9/4.0.1/lib"

		export CC CPPFLAGS LDFLAGS
		exec "$@"
	EOF
	$ mksh iBuild.sh mksh Build.sh -r
	$ file mksh
</pre></div><p style="margin-top:0px;">Mach-O executable arm</p>
<p>Of course, you need the iPhone 2.0 SDK on your Mac for this (and,
 presumably, an installed native mksh… otherwise just change the above
 instructions a little.</p>
<p>We haven't tested it yet, but if gecko2@ can figure out how to run
 mobileterminal.app inside the emulator, he will… and possibly jailbreak
 his iPhone G3.</p>
<p>Maybe this fact (availability of mksh) strengthens <a
 href="@@RELPATH@@permalinks/wlog-10_e20080714-tg.htm">our point</a>.</p>
<p>In the meanwhile, gecko2@ has found the geocaches I placed.</p>
<p><strong>Update 18.07.2008 12:42</strong> – we have a fat binary with
 five architectures (amd64 arm i386 powerpc ppc64) now. This is the <a
 href="https://eurynome.mirbsd.org/pub/iShell.tgz">iShell</a>, indeed.</p>
----
Date: 19.07.2008 22:17
Author: tg@
Title: plans for the immediate future

<p>My plans are as follows: after squishing out all remaining bugs, I’ll
 publish another MirOS-current snapshot (i386 baselive, i386 installer,
 sparc installer, some selected few binary packages for both arches),
 announce that on the website, and make a CVS repository tarball.</p>
<p>After that, I’ll concentrate on setting up the new servers (tear and
 euynome) fully, and dispose of rant-featuring-herc. Features I wanted,
 such as full AES vnd(4) encryption, DJBDNS with no split v4/v6 transport
 binaries, etc. will have to wait.</p>
<p>With the infrastructure in place, we can start hacking again. We had
 planned on bringing out MirOS #10bis in time for FOSDEM, but it looks
 more like just another -stable snapshot, and maybe another month for
 the second release of -stable; Benny will have to work some on the branch
 prior to its tagging (I’ll concentrate on -current), especially because
 we want to use X11 (and gcc) from HEAD, since these are not branched.</p>
----
Date: 20.07.2008 18:27:42
Author: tg@
Title: mksh – The iShell, Episode Ⅱ

<h3><a href="@@RELPATH@@mksh.htm">mksh</a> – The iShell</h3>
<p>Thanks to help from people in the various IRC channels, and gecko2@
 jailbreaking his iPhone 3G (not G3…), I was able to run (albeit not
 test – there is no Perl for the iPhone yet) two mksh(1) binaries on
 it: a normal one and a fat binary (aka universal binary – this one,
 containing code for 5 (five) architectures, can truly be called an
 universal binary ☺).</p>
<p>I packaged the modified build script, an extra ldid binary (built
 for OSX86) provided by <em>someone else</em>, and the output of the
 build process, together with a readme, as a gzsig(1)ned <a
 href="https://eurynome.mirbsd.org/pub/iShell.tgz">tarball</a> on our
 server again – note that the cryptographic signature is only for time
 stamping (and download integrity checking) and does <strong>not</strong>
 imply any warranties, especially for the third-party software involved.</p>
<p>While here, we would be pleased if the reader supports our <a
 href="@@RELPATH@@permalinks/wlog-10_e20080714-tg.htm">proposal</a> and
 requests Apple to include <a href="@@RELPATH@@mksh.htm">mksh</a> in the
 default installations. We would also be pleased if the mksh-iPhone binary
 were to make it into one of the Cydia repositories, contact us via <a
 href="@@RELPATH@@irc.htm">IRC</a> or mailing lists for assistance.</p>
<p>If someone were to package Perl 5.8 or so, that’d be great too.</p>
<p>To the readers from ##iphone-hackers on the one and #iphone-dev on
 the other IRC network: *waves a friendly hello*</p>
----
Date: 22.07.2008 20:54
Author: tg@
Title: MirEwe requiescas in pacem

<p>Since <a href="http://www.cachewolf.de/">CacheWolf</a> was the only
 use case, I decided to remove MirEwe from the repository entirely, as
 CacheWolf will be rewritten to use the Eve VM, inevitably.</p>
<p>Not only have I removed a last source tarball (distfile) of <a
 href="@@ABSPATH@@/MirOS/dist/hosted/other/ewe-1.49mb4.tar.gz">Lunix Ewe 1.49mb4</a>,
 with <tt>CompileEwe.zip</tt>, <tt>JavaEwe.zip</tt>, and <tt>ewe.jar</tt>
 pregenerated, but the comma-v rcsfile(5)s are also archived in a <a
 href="@@ABSPATH@@/MirOS/dist/hosted/other/ewe-rcsfiles.cgz">gzipped sv4crc</a> file,
 gzsig(1)ned, as usual.</p>
<p><strong>Update 06.11.2008</strong>: We now have an <object width="128"
 height="96" data="@@RELPATH@@pics/ewe.svg" type="image/svg+xml"><img
 src="@@RELPATH@@pics/ewe128x128.png" alt="Ewe icon" /></object> Icon,
 thanks to smultron.</p>
<p>And, also as usual, one more unrelated thing: <tt>config(8) -ef /bsd</tt>
 should not only be able to handle gzip(1)ped kernels, but also personalise
 them by rewriting the <tt>initial_entropy</tt> array. TODO. The snapshot,
 dualive ISO 9660 image, is almost complete and will be uploaded later.</p>
<p><strong>Update 26.07.2008</strong>: personalising done, snapshot broken.</p>
----
Date: 23.07.2008 01:47
Author: tg@
Title: Trumping OpenBSD, once again ☺

<p>With the latest edition of MirOS #10-current’s snapshot (read the <a
 href="@@RELPATH@@permalinks/news_e20080722-tg.htm">announcement</a> for
 more details), we have trumped OpenBSD once more. While being dual-arch
 is nothing new (to them), and being runnable as Live-HDD, Live-CF-Card,
 etc. is nothing new (to us), we haven’t yet had a dual-arch Live-CD/DVD
 (or HDD or CF/SD/MMC/… Card or USB stick) yet. Well, only one of the two
 architectures has Live CD capability, but we neither have baselive image
 capability for sparc yet (though that would be possible, even if somewhat
 kludgy) nor would it have fit on the ISO 9660 image within the boundaries
 of a CD-R. And DVDs don’t match well with SPARCstation 20s ☻</p>
<p>Coming to that, I recently recherched if gcc 3.4.6, which we currently
 use as system compiler, can be used to build gcc 4.3 (with special care
 on the Ada part). Looks like you can even use gcc 2.95 for that, lucky us.
 This means I should somehow discover the Ada patch for gdb 6.3, which –
 again, luckily – we use, and apply it. I had talked with Benny about the
 compiler issue… originally I wanted to strip down the system compiler to
 the bare minimum once a more recent gcc (and possibly, LLVM, SUNWcc, pcc,
 etc.) are in ports and usable, but with the proposals to rewrite gcc in
 dreaded C++, C++ API issues, licencing issues, Ada bootstrapping, etc. we
 will probably continue to require GNU make for building the base compiler
 (the bad part) and be able to announce we’re good for developing (the good
 part of keeping the full-featured gcc near base). Just the Java™ part will
 not be re-enabled in near future, as it isn’t used for bootstrapping Iced
 Tea anyway. (It <em>can</em> be used for simple things though.)</p>
<p>With all the friendly fire, OpenBSD bashing, etc. aside, I would like to
 use this place to thank a few OpenBSD developers for helping me out with a
 bug in <a href="@@RELPATH@@mksh.htm">mksh</a> as well as the issue with
 sshd(8) on sparc (and probably i386 even if it didn’t show up) I had (which
 even was my own fault). While you guys still don’t have an mksh port in
 your tree, some of you are really helpful (also hi Miod) sometimes, and
 I hope we can drink a few beer together at the next FOSDEM etc. and <a
 href="@@RELPATH@@permalinks/news_e20080722-tg-g10001.htm">FrOSCon</a> of
 course. (Which I hope we will also be able to use to discuss the state of
 our X11 tree.) To Linus: while OpenBSD developers may be masturbating
 monkeys, at least they’re able to design stable APIs, drink beer, and use
 sane version control systems with central quality control <strong>while
 being annoyed by humppa</strong>.</p>
<p>The usual unrelated news: Basel, ich komme! Schon mal GRÜẞE im Voraus
 an die Schweizer, die dies lesen.</p>
<p>mksh side notes: some older versions of SunC 5.9 fail on <tt>({</tt>
 stuff in acomp, use <tt>env HAVE_EXPSTMT=0</tt> to build then. <a
 href="http://nwcc.sourceforge.net/">nwcc</a> also has issues.</p>
<p>MirBSD side notes: We build for V8 CPUs on sparc, but still only V7 are
 emulated by <a href="http://people.csail.mit.edu/fredette/tme/">tme</a>.
 And while V9 CPUs in V8+ mode shouldn’t be a problem, there’s no interest
 from the OpenBSD camp to run the sparc (not sparc64) port on sun4u or even
 sun4v machines, so no fast build machines yet… *snief*</p>
----
Date: 25.07.2008 16:22:34
Author: tg@
Title: Katze müßte man sein…

<p>… oder: de vitae felidae</p>
<hr />
<p>Katze müßte man sein, oder Kater halt, je nachdem. Den ganzen Tag sich
 faul in der Sonne räkeln, unter dem Heck eines Autos liegen und ab und
 zu den an ihr vorbeiradelnden Zweibeinern zuzwinkern und sie mit dem Kopf
 verfolgen; wenn man Hunger hat, reicht es, den Dosenöffner auf zwei Beinen
 mitleiderregend anzuschauen und/oder zu -miauen… manche haben sogar ein <a
 href="http://henrythecat.livejournal.com/">eigenes Blog</a> oder gar ein <a
 href="http://justjournal.com/users/midnight">BSD nach einem benannt</a>; wem
 das nicht reicht hält sich den Nachbar des eigenen Dosenöffners, nämlich
 <em>homsn</em>, als zusätzlichen Hausmensch (quasi wie wir uns Haustiere, z.B.
 Hunde, halten)… der krault einen dann, und man muß nichtmals hingehen.</p>
<hr />
<p>I just coined a new term: IMACS. The connotation is: I’ll hack the ukbd(4)
 driver to allow inmetaaltctrlshifting entropy into the kernel too, soon.</p>
<p><strong>Update 26.07.2008</strong>: sadly, USB keyboards don’t seem to
 generate any interrupt requests on modifier key presses or releases. This
 means you’re stuck to DIN or PS/2 pckbd(4) or Sun (&amp;c.) zskbd(4/sparc)
 for entropy collection via IMACSing. Can’t be helped…</p>
----
Date: 30.07.2008 00:16
Author: tg@
Title: Get me some beer, Wine sucks

<p>… I still <a href="@@RELPATH@@permalinks/wlog-10_e20080725-tg.htm">wish
 I were a cat</a>, sometimes. Just have to stay clear of <a
 href="http://partmaps.org/era/unix/award.html">cat abusers</a>.</p>
<p>Tonight, I managed to port Wine 1.0 from pkgsrc®, with thanks to <a
 href="http://www.feyrer.de/NetBSD/blog.html/nb_20080728_1037.html">Hubert
 Feyrer</a> for mentioning, except it seems to stumble about W^X and
 memory allocation/mapping in general. I guess we need some help from
 OpenBSD toolchain experts and possibly both FreeBSD® and pkgsrc® porters
 dealing with this. I can’t, but I tried a lot.</p>
<p>My other project for tonight failed, once because it has just too many
 unported dependencies, second because one of them requires gcc4, namely <a
 href="http://undeadly.org/cgi?action=article&amp;sid=20080728142422">webkit
 (non-Qt)</a>. Okay, they say webkit-Qt can be built with gcc 3.4.6, but it
 seems to be not recommended. Thus no midori for us ☹ (yet).</p>
<p>The third thing was getting rid of J�rg Schilling… but due to the heat I
 slept bad and could not get up early. Really! (Yeah yeah…)</p>
<p>You all should read Tonnerre’s wonderful blog posting about how he got <a
 href="http://blog.pas-un-geek-en-tant-que-tel.ch/archives/2008/07/23/Subversion_-_tales_from_a_failed_migration/">rid
 of Subversion</a>, luckily. (I wonder about said “new” developer’s preference
 as I’d rather use CVS for everything…)</p>
----
Date: 02.08.2008 00:12
Author: tg@
Title: HEAD may be broken, but improvements coming, OPTU-8 charset
Tag: unicode

<p>I started hacking on the bootloader issue, decided to move out the
 various libraries into <tt>src/kern/</tt> first, and completed that
 for zlib, began it for the rest. The other places – <tt>src/lib/libc/</tt>
 <tt>src/sys/lib/</tt> <tt>src/sys/arch/*/stand/lib*</tt> – now look much
 cleaner already, and in fact can do some better. I also merged bootloader
 and other improvements from OpenBSD before beginning the file move dance,
 but it still worked for me in qemu for testing, so I didn’t expect much
 breakage.</p>
<p>Furthermore, MirOS now officially has OPTU-8 locale (no more CESU-8),
 even if masqueraded as “en_US.UTF-8” for better application support. The
 CSUR had already, as posted about quite a few times, allocated us a PUA
 range, which <a href="@@RELPATH@@mksh.htm">mksh</a> was already using,
 and now the base system and libc are beginning to catch up. Thanks to a
 pen and paper “game” I have sort of a defined finite machine modelling
 the conversion states, and found out I can get by with the mbstate_t we
 already were using. tr(1) already doesn’t wreck ISO-8859-1 accents any
 more (nor binary files), although that definitively needs some testing.</p>
<p>I’d just like to warn people that HEAD (MirOS-current) is a pretty
 moving target at the moment.</p>
----
Date: 08.08.2008 22:18
Author: bsiegert@
Title: Improving MirPorts by porting stuff

<p>I have just finished porting the aqua version of LyX (which I need
 for @work), which is going to become <tt>aqua/lyx-mac</tt>. Version
 1.5.x needs Qt4, which we do not have on MirOS just yet, and the Mac
 version installs into an application bundle, so it is a completely
 separate port.</p>

<p>First of all, I discovered TWO bugs in Qt's build system. Not only
 are the generated .la files wrong, but the .pc files are broken, too.
 My first bug report contained lots of detail but what finally landed in
 their bad joke of a bug tracking system is <a
 href="http://trolltech.com/developer/task-tracker/index_html?method=entry&amp;id=218261">a
 one-liner</a>. That should teach me not to write bug reports longer
 than one line ... Seriously, WTF?</p>

<p>Next, our pkg-config (both actually, pkgconfig-bsd is not better)
 does not grok frameworks. In order to get a correct result, I had to
 port pkg-config-0.23. It is not in the trunk yet because I was told
 that newer versions "make bad things happen" on MirOS. What I will do
 is try to build some stuff using this newer version of pkgconfig and
 try to find out if it works. So, if you are feeling lucky: Install this
 and try to build some software on MirOS.</p>
----
Date: 08.08.2008 21:03
Author: tg@
Title: Cats, Rivella, other nice things, and… yuck

<p>Still <a href="@@RELPATH@@permalinks/wlog-10_e20080725-tg.htm">cats
 have less sorrows</a>. Now it’s proven that feline specimen <a
 href="http://incredimazing.com/static/media/2007/12/09/915d7ec0e067ac2/i_question.jpg">can
 actually spell</a>. Poor “lolcats” who are abused by many.</p>
<p>Discovering <a href="http://www.rivella.ch/">Rivella</a> and Tonnerre
 mentioning that swiss chocolate exported into the EU is artificially
 made more sweet than inland production (yuck, sweet chocolate) are some
 promising points voting for working in Switzerland. It’s still expensive
 and a major change though. But the payment is good, too.</p>
<p>While mkisofs is finally gone, I had to fix lots of bugs and port a
 new language, <tt>lang/pawn</tt>, actually better than others, but the
 interna still look more than very fragile. Same problem as with Ewe:
 written for Win32-only at first, made portable later by persons who
 don’t know how to code for Unix. Ugh, and… I’ve got to learn Python.</p>
<p>Either my VPN, gecko2s Server, or the network (at home, Strato, or
 here) sucks. Hm… maybe it’s the backup Tonnerre makes.</p>
<p>I should search for some more geocaces, but now that I have some more
 time than at the beginning of the week, the weather is worsening, and
 we still have the duties. *grml* I need tear set up, too…</p>
----
Date: 16.08.2008 22:19
Author: tg@
Title: X11, etc.
Tag: geocache

<p>Don’t wonder if I appear online less often these days and commit weird
 and plain ugly things. I’m young and need the money&lt;/asr&gt;</p>
<p>Uh, EXPN? Sure. I’m currently working for a company and a customer who
 both originally were basically the local CCC meet cast into a company. I
 need to learn a lot of things, and my view of the world has been utterly
 turned upside down.</p>
<p>At least, I was able to spot some geocaches in the more obscure parts…
 some would call it primitif… of the world. And in the Elsaß.</p>
<p>Ah, X11… the input is passed as keycode, not as keysym… it’s not easy,
 trying to write a thing for entering unicode hex chars (damn US keyboard
 missing the “&lt;&gt;|” key). IME won’t go. Maybe fake a selection and a
 paste event. Compose works, but only in xterm, which grows from 8 MiB to
 34 MiB size and 1 minute startup time, each, when expanding composure. I
 don’t think that’s worth it, even if unicode <em>is</em> big.</p>
<p>As a new “standard”, we’ll <tt>#define</tt> all functions we introduce
 to themselves, like arc4random_pushk(3), to rid autohell.</p>
----
Date: 24.08.2008 10:28
Author: bsiegert@
Title: pkg-config woes, FrOSCon
Tag: event

<p>In my recent entry, I already talked a bit about pkg-config and its
 framework support. It turns out that there is another problem. The
 <tt>--libs</tt> parameter can be "split" into its parts by using
 <tt>--libs-only-L</tt>, <tt>--libs-only-l</tt>, and
 <tt>--libs-only-other</tt>. The LyX configure script, however, did not
 care about the latter, only the first two. Which brings me to the mail
 I wrote to the pkg-config mailing list:</p>

<p>"Hi,</p>

<p>"while compiling LyX/Mac the other day, I came across a problem in the way
 frameworks are handled. On Mac OS, frameworks are a different way to pack a
 library together with its headers. Framework-related options are put in
 --libs-only-other, while the configure script was only checking for
 --libs-only-l and --libs-only-L. While I agree that this is broken behavior,
 it brings me to my question:</p>

<p>"The way I see it, -Fpath (framework search path) is equivalent to -Lpath for
 libraries. Thus, -F should maybe be included in the output of "pkg-config
 --libs-only-L". The same thing goes for the "-framework name" linker option,
 which is more or less the same thing as "-lname", namely linking against a
 certain library/framework. Thus, the -framework option (with argument)
 should be added to the output of --libs-only-l.</p>

<p>"Opinions?"</p>

<p>In other news, FrOSCon has it second and last day today. I am
 currently in the train on the way. The party ("social event") yesterday
 was quite good, even though the weather was not as good as last
 year&mdash;it was cold and humid.</p>
----
Date: 25.08.2008 13:02
Author: tg@
Title: FrOSCon redux
Tag: event geocache grml

<p>Hum. This year’s FrOSCon… sucks. At least the catering, which was
 so much better last year (remembering the Chili con Carne, as well
 as the Chili non (sin) Carne, fondly… these were produced by wbx@’s
 family members, which haven’t been included in this year’s planning
 so some other persons did the catering). And being waked up at 04:00
 in the morning due to a call on the mobile phone, for taking care of
 some drunken booth slave *grml…*, didn’t help either.</p>
<p>The evening’s social event also sucked totally. Since it had been
 raining until shortly before, they decided to have it inside, except
 the barbecue of course, but didn’t adjust the volume of the music
 played to the environment, which caused me to leave the MirOS/XF86
 booth in favour of the Debian/grml booth, talking to Mika and Joey…
 who, like me, didn’t quite like being LITERALLY punched into our
 stomach by the basses. I left relatively early then, especially as
 the cocktails (Vutral brought me one, since I couldn’t go near the
 counter due to the volume of the… whatever they call music) tasted
 pretty bad and had a (too?) high percentage of alcohol. But talking
 to the various people, not just Mika and Joey, was good, even though
 just being at the FH (university) during the social event was really
 unbearable and physically endangering one’s health.</p>
<p>Other than that, we had quite a lot of fun at the conference, as
 usual. I still think it has chances to close up to FOSDEM, but they
 will have to make sure the catering does not get even worse. While
 FOSDEM does not have <em>any</em> catering, FrOSCon 2006 and 2007
 had good food, and regressions count as malus.<br /> Once I found
 Marc Aurele La France at the train station (which was quite a task),
 things went well – he even fixed a bug in our xdm configuration at
 the conference. The bug was inherited from OpenBSD, as usual ☺<br />
 Marc also said he enjoyed himself.</p>
<p>I hacked an Asus EeePC… MirOS mostly works (no NIC though), and the
 graphics card runs at 640x480 VESA… with the new 915resolution port of
 today, it might do the 800x480, but I can’t test now.</p>
<p>I took the chance to discover a geocache in St. Augustin yesterday,
 but, while Benny suggested we (him, me and gecko2) go caching in Bonn
 today, they seem to prefer hacking on the laptops (considering the
 weather, this is not the worst idea though), so I got time to write a
 wlog entry (too). I still have some things on my TODO, like fixing the
 ports with unfetchable distfiles, but hey.<br /> Taking the day before
 and the day after the conference off is A Good Thing™.<br /> Next one
 will be the <a href="http://softwarefreedomday.eu/">Software Freedom
 Day</a> in Baarn, Nederland – where not even Wim will go ☺ But I need
 a car… parents don’t help even if you ask them <em>once</em> a year,
 but maybe Jonathan from (near) Aachen will join me, he has a car.</p>
<p>My Thinkpad X40 will probably arrive today or tomorrow. Sadly, I
 didn’t invest any time in evaluating the products before… I learned
 that the ‘T’ series has 2.5" HDDs instead of the sucky 1.6" HDDs, and
 a much more solid lid chassis, at FrOSCon. My decision to buy an X40
 was based <em>solely</em> on the observation that it was “in” at most
 OpenBSD developers some years ago (and thusly would most certainly
 work well with MirOS). Don’t do that then…</p>
<p>Once it’s there, I got to set it up and continue working. It’s bad
 <tt>odem</tt> broke so badly, especially as my current contractor
 (employer, except not quite so) would rather have me working full-time
 on the project, which is not entirely possible since I still have a
 life here. But upon setting it up, I might upgrade and/or fix some of
 the ports, since I’m at it anyway. Plus I get <tt>/home</tt> encryption.</p>
<p>Marc agreed to merging as much of our <tt>X11</tt> changes (both these
 inherited from OpenBSD’s <tt>XF4</tt> module and our own patches) into
 the XFree86® main tree, some ifdef’d, and helping us migrate to the new
 4.7 or upcoming 4.8 release (or probably, 4.8.99.01, since I don’t think
 the merge will be there in time for 4.8 proper). He was a fun guy and
 well understanding our issues. The most funny part however was Thomas
 from <a href="http://sourcemage.org/">Sourcemage</a> (SMGL), who also
 maintains the <a href="@@RELPATH@@mksh.htm">mksh</a> spell in their
 grimoire, considering to retain supporting XFree86® (and modular X.org,
 but not the buggy monolithic X.org) iff it’s still actively developed,
 which Marc assured me it is.</p>
<p>Benny agrees that the “Kaiser’s BIO-Kaffee” is decent, despite its
 pricing of only 3.99 €/£ (may be my high quality milk too, though).</p>
<p>Update: looks like I’ve got a package to fetch from the post station.</p>
----
Date: 29.08.2008
Author: tg@
Title: Six Years of MirBSD
Tag: release mksh

<p>Six years ago, I started collecting patches against OpenBSD, a bunch
 of 4.4 elitist snobs since the 1980s (or so they say). Said patchkit
 should eventually become MirOS BSD and the MirPorts Framework, along
 with a couple of more or less well-known and successful subprojects.
 Time to celebrate (TGIF)!</p>
<p>IOW, I hacked a Debian package of mirmake, depending on latest <a
 href="@@RELPATH@@mksh.htm">mksh</a> of course. It needs more upstream
 work to be useful and pretty, though.</p>
<p>Let me plug here an animated GIF found somewhere in the net, which
 shows my opinion about Netscape/Mozilla/Fire…tapir quite well:<br />
 <img src="@@RELPATH@@pics/wlog/firemoo.gif" alt="firesomething" /></p>
<p>And, even more unrelated, MirOS is (of course) continuously improving.
 We now use Fedora Core 4 libraries for the linuxulator, by suggestion
 of the MidnightBSD people, which should improve some things (it already
 has opened the door for Opera-linux plugins such as AcroRead-linux).</p>
<p>(The best browser of all is still lynx(1) though.)</p>
----
Date: 05.09.2008 15:04
Author: bsiegert@
Title: cairo regressions
Tag: bug

<p>It seems that everytime I update cairo, another annoying bug pops up.
 This one is actually a regression: the exact same bug had been fixed in
 cairo-0.9.3, and now they reintroduced it. It seems that their code is
 only ever tested on GNU/Linux with all the latest libraries. Solaris
 and BSD systems are especially likely to blow up.</p>

<p>I have submitted the following text as fd.o <a
 href="https://bugs.freedesktop.org/show_bug.cgi?id=17450">bug
 17450</a>. Sorry if this wlog is becoming just a dump for upstream
 bugreports.</p>

<p>"I am trying to compile cairo 1.6.4 on MirOS BSD (an OpenBSD
 variant). The fontconfig included in the base system does not have the
 FcFini() function. As I gathered from searching the mailing list
 archives, this function is optional.  However, on systems without
 FcFini(), the freetype backend is completely disabled.</p>

<p>"From reading the source code, I do not think that FcFini is really
 essential, and any calls to it are protected by <tt>#ifdef
 HAVE_FCFINI</tt> anyway. Thus, I made a small patch for the configure
 script to make a missing FcFini non-fatal for the freetype font
 backend.</p>

<p>"What's ironic is that this bug had already existed as <a
 href="https://bugs.freedesktop.org/show_bug.cgi?id=3951">bug
 3951</a>. It was fixed in 0.9.3."</p>
----
Date: 09.09.2008 18:50
Author: tg@
Title: Aus gegebenem Anlaß^Hss
Tag: event geocache

<p>Wir haben jetzt ein Blumenkohl-Icon fürs iPhone, Dank an die RUBIs.</p>
<p>Google ist definitiv evil. Ich vermeide sie auch so wie es eben geht,
 aber bei zwei Sachen habe ich keine Alternative, da sie entweder einfach
 nicht existieren oder saugen: Suchmaschine (ja ich hab sie alle durch)
 und Karten (bin halt Geocacher).</p>
<p>Während ich die 2⁶ Caches locker voll habe, siehe die diversen…
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="Open, Free, Cool" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="CommerceFrog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 …Statistiken, fängt Benny erst an, immerhin 2³ hat er schon:
 <img src="http://img.geocaching.com/stats/img.aspx?txt=MirPorts+Developer&amp;uid=a1e7bb35-ff5a-48dd-b435-91f822b3f8c1" alt="Required in CH/F" />
 Kimnotyze macht nicht wirklich weiter…
 <img src="http://img.geocaching.com/stats/img.aspx?txt=Wilder+Kerl&amp;uid=3d6a47db-c0f0-4c02-b037-e1fe43b1dbce" alt="Lost in Luzern" />
 … gecko2 kommt selten zum Cachen, aber hatte letztens sein Vélo mit,
 sodaß er sich mit Kabelaffe und mir auf Tour begeben konnte:
 <img src="http://img.geocaching.com/stats/img.aspx?txt=Apple+Fanboy&amp;uid=d57c5767-047b-4aff-a00a-784356b94e9e" alt="Janz Weit Draußen" />
 Und der Dr. Pfeffer findet in Bremen nichts mehr… wär er bloß mal
 nicht umgezogen, jaja… gibt halt nur in Bonn schön viele Dinger:
 <img src="http://img.geocaching.com/stats/img.aspx?txt=Lazy+Academic&amp;uid=49c2ffb9-b3cf-4ce9-af7d-b1076dd451f4" alt="Wallapampa" />
 <br />Aber Benny hat echt fieses Anfängerglück, und ich bin fachblind.
</p>
<p>Bruscetta sind superlecker, aber füllen, zusammen mit der warmen Mahlzeit,
 den Bauch sehr an… und wenn man dann vorher noch einen Mojito hatte, hat man
 gar keine Lust zu hacken, ist ziemlich platt… erst bsiegert@ dann auch mir
 aufgefallen. Wir sitzen gerade bei N 47° 31.936′ E 007° 38.043′ im Chaostreff
 Bāsel… und sind ziemlich platt. Aber irgendwas kommt trotzdem bei rum.</p>
<p>Kommt wer mit nach <a href="http://marc.info/?m=122098732430813">Baarn</a>
 und ggf. trifft sich mit uns $sonstwo?</p>
----
Date: 14.09.2008 15:26
Author: tg@
Title: SoftwareFreedomDay aftrap (of niet…)
Tag: event

<p>Zaterdag 13 September, Baarn, Nederland. Iedereen wacht op me. Spijtig
 dat ik niet kan komen. Ik wilde met een vriend die een auto heeft naar
 Baarn gaan, maar die komt op 10:30 ipv 09:00 CEST, en dan ben ik ook nog
 niet klaar met wakker worden, koffie drinken, zaken samenzoeken, voor’t
 weekend inkopen, enzo. Op 12:00 zitten wij in zijn auto… maar dat zijn
 nog 2½ uren (of meer) tot dat wij aankomen kunnen, dus wordt besloten,
 er niet meer te gaan. SFD was vanaf 12:00 tot 17:00… voor 2 or 2½ uren
 moeten wij 5+ uren in’t auto zitten, en dan is nog niet zeker of wij
 het Brandpunt vinden. Slechte planing. In het duits is er een expressie
 voor dat: “Verpeilungsfaktor” – Wij zijn dan in’t zwembad geweest.</p>
<p>Groeten an iedereen die daar was… volgende keer dan. Echt jammer dat
 het niks wordt. Ik geloof ik had te weinig geslapen verleden week, door
 mijn nieuwe baan in zwitserland.</p>
<p>Wij zatten dan gisteren nog in mijn favoriet kroaats restaurant, er
 wordt besloten dat ik de volgende tijd minder aan mirbsd zelfs werk,
 maar het nieuwe server klaar maak en de VM zo installeer dat ze een
 takeover van de oude www.mirbsd.org vhost kan maken. Ik doe mss eerst
 nog een snapshot, maar die komt dan zonder Live CD (die moet ik opnieuw
 maken doordat wij geen mkisofs met al zijn fouten meer gebruiken).
 Benny doet in de tussentijd meer met ports, bv. fixes voor ccache en
 distcc (zodat mijn SPARCstation cluster packages kan bouwen ☺) en enige
 Qt4 ports. Nadat de twee server’s klaar zijn kunnen wij dan verder met
 mksh, mirmake en zo doen, wanneer het werk nog arbeidsvermogen overig
 laat (da’s soms moeilijk). gecko2@ doet goeie werk met het opzetten van
 VMware voor eurynome, ter gebruik stellen van een IPv4, enzo.</p>
----
Title: PHP is dead!
Date: 17.09.2008 21:58
Author: tg@
Tag: security

<p>The MirBSD website now runs without PHP even for legacy content. All HTML
 files are statically generated using <a href="@@RELPATH@@mksh.htm">mksh</a>
 and <a href="@@RELPATH@@htman/i386/man1/make.htm">MirMake</a>. Pretty much
 unbreakable, we think.</p>
<p>While here, I’d like to invite you to try out mksh-current from CVS, as
 several (minor) bugs have been fixed. There are still some new features
 pending for another release.</p>
----
Title: code age
Date: 20.09.2008 19:19
Author: tg@

<p>Today, I hacked some more on <a href="@@RELPATH@@mksh.htm">mksh</a>’s
 command line editing modi. They were probably written independently, so
 Benny’s request for vi mode cursor keys is unfulfillable reasonablily.
 I’m not quite done, there are some more patches to create, including one
 to the mksh(1) manual page, but that will come. It’s a hard job, and on
 a headache-clouded november day like this (no pun, look at the weather!)
 getting a hacking mood, as well as anything else done, is difficult. I
 did manage to catch a few sun rays, but… not much. Besides, sitting in
 front of a monitor all day makes you wish you had learned something else,
 even if everthing else goes smoothly – which it usually doesn’t…</p>
<p>I tried to make pax(1) compile without the -DLONG_OFF_T define… turns
 out that all the quad_t types and defines are not existant on Debian.
 Autoconfiguration and <tt>#ifdef</tt>s suck if you can do it without,
 but this will take some more time.</p>
<p>I had an interesting discussion about light bulbs with the MidnightBSD
 people yesternight. Mine mostly changed to power saving ones I got for
 free for switching to online invoices from our local provider. Neat. I
 do keep traditional bulbs in the places where light is needed only for
 very short times, like the entrance area, and frequently at that.<br />
 We often have interesting topics to discuss, e.g. languages, chocolate,
 things that suck… not only computing things, mind you ;)</p>
<p>I just use <a href="@@RELPATH@@wlog.htm">…/wlog.htm</a> as my “blog”
 URI now if someone asks, <strong>even though this is <em>not</em> a
 blog</strong>. Symlinks rock.</p>
----
Date: 05.10.2008 00:47
Author: tg@
Title: I agree with RMS

<p>This may come shocking to you, but, yes, I indeed agree with <a
 href="http://www.stallman.org/">Richard M. “FSF” Stallman</a>. While
 I respect him quite a lot, similar to Bill Gates, I usually do not.
 But this time, there’s something which makes me, wholeheartedly:</p>
<p>At Chaostreff on Tuesday I learned that RMS protests against <a
 href="http://blogs.computerworld.com/rms_hates_cloud_computing_says_you_should_too">cloud
 computing</a> (via OSnews). I actually had to learn this new term
 first, but after I did, I can only join the fun, despite so many
 voices against it. It’s really bad having few people control a lot
 of users, and everybody using it without a second thought¹². The
 Terms of Service³ on these “Web 2.0” thingies, as I called them for
 myself until now, are usually quite problematic as well. You should
 not trust everybody, even without being paranoid.</p>
<p>① Yeah, I know I’m still using Google’s search engine and Maps
 service. But that’s a voluntary choice, plus there is no (usable)
 alternative, so I’ve got no way around it due to my requirements.
 However, I do not have a Google account.</p>
<p>② Interestingly enough, Benny said on the phone that he agrees
 with me on this one, despite using a GMail account. Pardon, for my
 German readers (this wlog entry was drafted in Switzerland), that’s
 Google Mail, just to make this clear.</p>
<p>③ Ever tried to take back information, cancel an account, get rid
 of their spam, read through the EULA, get someone to change things
 which suck, get some knowledgeable support person, etc.?</p>
<p>Of course, RMS’ arguments are also all valid. While I do not like
 the “sort of communistic” licencing approach of the FSF, and how
 they use the GNU FDL to restrict people while claiming that really
 all information should be free (I wouldn’t want that either, but
 that’s mostly for personal reasons or privacy), I’m positive that
 we should think twice about the code we use and the data we give.</p>
<p>I still am amazed at why people use so many kludgy web browser
 applications in favour of local applications. We should probably
 improve the situation regarding local backups… BoxBackup has an
 interesting approach, encrypting them. And, gosh, someone wrote
 a cloud shell… using $favourite_name (SOAP, XML, XMLRPC, AJAX, insert
 whatever disgusting technology is used at the moment) instead of Unix
 IPC via Pipes to connect “applications”. Gah! *shudder*</p>
----
Date: 13.10.2008 22:29
Author: tg@
Title: mksh – please test release candidate
Tag: mksh

<p>Hi everyone, <a href="@@RELPATH@@mksh.htm">mksh</a>’s current
 development version should be tested on as many platforms as
 possible before a new release. This mostly means:</p>
<pre> $ CVS_RSH=ssh; export CVS_RSH
 $ cvs -d :ext:_anoncvs@anoncvs.mirbsd.org:/cvs co -PA mksh
 $ cd mksh
 $ (sh Build.sh -r &amp;&amp; ./test.sh -v) 2&gt;&amp;1 | tee build.log</pre>
<p>Afterwards, please mail me (<tt>tg@</tt>) the <tt>build.log</tt>
 file, play around a little with mksh(1), see if it works. You can
 use a relative path to the source directory for repeated builds and
 also pass different compilers or flags as shown below, but please
 remember that passing CFLAGS or LIBS overrides the defaults, which
 you thusly should include:</p>
<ul>
 <li><tt>CC=gcc ksh93 ../mksh/Build.sh -r &amp;&amp; ./test.sh -v</tt></li>
 <li><tt>CFLAGS="-q64 -O3 -qstrict" bash ../mksh/Build.sh -r &amp;&amp; ./test.sh -v</tt></li>
 <li><tt>CFLAGS="-xO2 -m64" /usr/xpg4/bin/sh Build.sh -r &amp;&amp; ./test.sh -v</tt></li>
 <li>…</li>
</ul>
<p>You are, of course, invited to join the mailing list discussions
 regarding features, bugs, and behaviour, or even send in patches for
 missing items or architectures. I’d especially be happy if someone
 made Minix 3 work… pdksh runs there, mksh didn’t last time I tried
 (with gcc, but once that’s up ACK should be easy). Or Plan 9.</p>
<p>If you’re on Ohloh, please add mksh to one of your stacks.</p>
----
Date: 19.10.2008 20:20
Author: tg@
Title: Getting closer
Tag: bug geocache

<p>I’ve built i386 and sparc intermediate snapshots. We’ve been fixing
 things lately, so that another combined DuaLive CD is not so far off,
 before the more weird things (such as the 4.4OpenBSD merge) start to
 happen. On an unrelated side note, my SPARCstation 20 is crunching for
 BOINC at the moment, at about 75 MIPS only though…</p>
<p>Maybe LLVM 2.4 and llvm-gcc 4.2 will hit the MirPorts Framework now,
 because we need a recent compiler for some things (Objective-C, or to
 compile Webkit), and it’s better in terms of licencing (BSD + GPLv2),
 quality and portability than FSF GCC. Maybe someone ports Iced Tea so
 that comrad will be happy. I don’t know. It’s all our spare time.</p>
<p>There are a few things in libpng that need to be taken care of
 first though, but the other recent security issues (ftpd(8) must die
 anyway, IPv6 ndp, …) were handled. Maybe others, let’s see.</p>
<p>Ah, and of course I need to get the Live CD functionality fixed and
 switched to use NetBSD® makefs(8) instead of J�rg’s mkisofs first.</p>
<p>I still don’t believe in Web 2.0, Communities, etc. For example, on
 Ohloh (I still need to take care to not write oh lol!) there are quite
 some projects, but “nobody” (well, almost) uses them. CacheWolf, the
 geocaching software of choice, starts a conversion from the Ewe VM to
 the supposedly superiour Eve VM, but I yet fail to see success, still
 people want to already switch over the svn trunk, and only bugfix in
 the 1.0 branch… as if anything were usable before next spring, and a
 full replacement before end of next year or so, guesstimated………</p>
<p>Jonathan complains about the brokenness of software, libobjfw is
 suffering from GNU libobjc runtime bugs (a layer deeper, that is).
 I so feel with him, I know the feeling so well… sometimes it would
 really be better to be a cat. I also quite met with Azraël, Florian’s
 (my best friend) animal half – with approximately 13 kg much more of
 a beast than the neighbour’s cat I nicknamed “Mir” (just to name it
 after a BSD) and behaving much more “cool”, but very nice.</p>
----
Date: 21.10.2008 21:54
Author: tg@
Title: Closer, but no game
Tag: bug

<p>On a somewhat unrelated topic, I would like to remind the readers
 of this wlog that next weekend, winter time will enact, i.e. you’ve
 got to add only one instead of two hours to the current UTC time to
 be able to talk to your “nōn-CS” neighbours. I’m adding it here since
 I know <em>I</em> would forget it otherwise, and I just saw it in a
 newspaper I read at the imbiss.</p>
<p>Well, I got closer. So close that dual-boot CDs are possible with
 the new system. So close that I got everything in place to make both
 baselive and dualive CDs. But makefs(8) let me down and threw an
 assertion on – how gdb(1) helped me to find out – a deep directory,
 <tt>usr/libdata/perl5/i386-mirbsd/5.8.8/auto/B/C</tt>, thinking it
 adds the same directory a second time to its node tree (aborting
 thusly to not end up in an endless loop later). However, adding the
 <tt>allow-deep-trees</tt> mount option did not help. So I’m stuck.</p>
<p>There are some alternatives. The one which I like the most would
 be to further change the Sun disklabel to not only look like an i386
 MBR to the BIOS, but also contain a “partition table” with only one
 partition of type <tt>0x27 (MirBSD)</tt>, starting at the chain sector
 (24, in our case) and being two sectors in size. The second one would
 then contain an i386 disklabel. A 4.2BSD FFS filesystem (created with
 makefs(8) which should work better there) would just be added after
 the ISO 9660 filesystem containing the boot stuff (and possibly, the
 <tt>/v10</tt> directory, i.e. nothing less and nothing more than the
 contents of a normal dual-arch install-only CD, plus the Live kernel,
 which is just a GENERIC with root set to <tt>cd0f</tt>… since we’ll
 be using UFS then, we don’t even need <tt>/dev</tt> on a ramdisk any
 more). However, I do not exactly know how this would behave if we mix
 a filesystem using 2048-byte sectors with a filesystem using 512-byte
 sectors on the same medium and expect it to work both when burnt on a
 CD using 2048-byte sectors <em>for the entire medium</em> and when put
 on a CF card / USB stick / HDD / etc. using 512-byte sectors <em>for
 all of the two filesystems</em>. The Sun disklabel would also have to
 be adapted, unless we want to hide the i386-live part from it (or are
 too lazy to show it… but we’re perfectionists, sometimes).</p>
<p>I know from others that they put <tt>/usr</tt> on an FFS inside a
 vnd(4) file instead, but this has not only heavy performance issues,
 I also know our vnd(4) to behave slightly buggy on media with sector
 sizes other than 512, with OpenBSD having fixed some of that. I would
 thusly like to avoid it.</p>
<p>Just putting FFS on the CD is not an option either. Oh, there are
 endianness issues as well, so there’s probably no point in having the
 i386 FFS slice being accessible by sparc, since people in all of the
 BSD camps still haven’t understood how uncool they are (our rewritten
 elf2aout(1) being a prime example that it is not only possible but also
 highly useful to have such tools do internal endianness conversions as
 needed).</p>
<p>Now I either need an OpenBSD guru telling me how to accomplish it,
 or have to experiment. *sigh*</p>
<p>Does anyone succeed in running MirBSD on qemu 0.9.1? No matter if with
 or without kqemu, it freezes for me after the pciide(4) probe. The <a
 href="http://thread.gmane.org/gmane.os.miros.general/8057">sparc issue</a>
 also has yet to be resolved.</p>
----
Date: 21.10.2008 22:21
Author: tg@
Title: mksh porting
Tag: mksh

<p>If you read the <tt>comp.os.minix</tt> newsgroup, please have a look at
 Message-Id &lt;Pine.BSM.4.64L.0810202029070.28869@herc.mirbsd.org&gt; and
 help us porting <a href="@@RELPATH@@mksh.htm">mksh</a> to Minix 3. (Yes I
 know I replied to a different thread, but this is just because Pine did
 not want to let me post using a simple ‘C’ompose in the gabeln.)</p>
<p>If you have an idea how I get the OSF/1 V2.0 cc(‌1) to correctly
 fail if it cannot resolve functions, or how we can fix Plan 9 or even
 Syllable Desktop (which is said to have fixed their signal handling in
 the kernel, however an actual user would have to <em>test</em> it), also
 feel free to contact me, you can probably help.</p>
----
Date: 22.10.2008 21:08
Author: tg@
Title: All software sucks…
Tag: bug

<p>I did not get much further. While I had the brilliant idea to embed a
 native little-endian BSD disklabel inside the first 512 bytes of the
 first-stage sparc bootloader (as the code searches for it anywhere in
 sector #1 inside the partition – or disc, if no MBR partition found –
 aligned to a long boundary), because an MBR partition would fake about
 two slices in the Sun disklabel which… could cause issues, the software
 I wanted to use to create a testcase has… bugs.</p>
<p>I ended up creating an install-only ISO and wanted to put the rest of
 the files into a 4.2FFS filesystem with makefs(8). However, that one <a
 href="http://www.NetBSD.org/cgi-bin/query-pr-single.pl?number=33925">did
 not want as I do</a>, and that for quite a while. Cheers to TNF! grml…</p>
<p>The update of Opera to 9.61 also failed for reasons outlined in the <a
 href="http://cvs.mirbsd.de/ports/www/opera/Makefile">commit message</a>.
 So we’re still stuck with Opera 9.27…</p>
<p>I did get libpng updated, but had “fun” with that as well. So long.</p>
----
Date: 24.10.2008 21:42
Author: tg@
Title: Giving up far-away aims to achieve the nearest ones at all
Tag: bug

<p>While I could use newfs(8)+vnd(4)+mount(8) or makefs(8) with a fixed
 block size for a live CD, or a ports version of mkisofs, or create the
 image on Darwin, I do not think so. The next snapshot will just not be
 a Live CD at all. Later, guys. Maybe TNF helps fixing it.</p>
<p><a href="@@RELPATH@@mksh.htm">mksh</a> also did not have the newest
 nifty features, such as <tt>&lt;(cmd)</tt>, applied, due to my ongoing
 illness feeling and added headaches all of this evening. However, I did
 finish the OSF/1 V2.0 (MIPS) port, and tomorrow there will be a proper
 announcement of R36, including ports, source RPMs, etc.</p>
<p>Many thanks to DEChengst from the <tt>#!/bin/mksh</tt> IRC channel
 again for giving me access to such machines.</p>
<p>I built LLVM+clang on Debian Lenny, just to make it crash *grin* due
 to an internal assertion… in mksh(1)’s source code. Gah. Anyway, got
 the problem reported. I wonder if I should remove Objective-C from the
 base gcc since it’s not just almost but really unusable anyway (same
 for Ada unless it can be used to build llvm-gnat-4.2). Jonathan gave
 up on the GNU runtime for good, or so he told me.</p>
<p>Today I also tried to get a neighbour’s fax-scan-print-copy combo
 running. Ends up that both the <strong>new</strong> phone line he bought
 for it was faulty (I gave him a replacement from my Attic), the AVM
 Fritzbox has… issues, and when I finally got my own fax from anno 1985 to
 work, and his Officejet not, we belive that either the ISDN voltage (it
 was accidentally plugged next to the NTBA first) or, much more likely, a
 recent thunderstorm b0rked it. So much for high-tech. My low-tech works.</p>
----
Date: 26.10.2008 22:20
Author: tg@
Title: new developer

<p>Adam “replaced” Hoka, who has advertised and bug-spotted (and fixed)
 in the past, begun a Haiku port of <a href="@@RELPATH@@mksh.htm">mksh</a>.
 He has been given CVS commit access for that purpose (possibly extended
 later), and as such, is now the 8th developer (counting both active and
 passive ones) to The MirOS Project.</p>
<p>Apparently, the Haiku port now compiles but does not run. Possibly
 another buggy operating system to add to the list.</p>
<p>I somehow end up fixing <a href="http://pcc.ludd.ltu.se/">pcc</a> each
 time I try to build it. But code size on i386 has <em>much</em> improved
 recently, although still nowhere near gcc ‘-Os’ already much better than
 its ‘-O2’ counterpart, both gcc3 and gcc4. I’m still waiting for more bug
 fixes, and more of my fixes integrated into upstream, before updating the
 pcc mirport though.</p>
<p>While I removed the use of <tt>__typeof__</tt> from the mksh(1) source,
 SUNWcc still explodes on it unless we use <tt>HAVE_EXPSTMT=0</tt> *sigh*</p>
<p>There are new “hosted” subprojects in our CVS repository. These are for
 each committer to place his/her stuff into, which, in contrast to other
 stuff in the <tt>contrib</tt> module, does not necessarily need to have
 something to do with BSD, Unix, shell, etc. However, existing mismatched
 code (the .exe files of my keyboard layout and Benny’s polymers code) will
 not be moved, because that doesn’t make sense with cvs(1).</p>
<p>Today, my health has been somewhat better, but I still feel as if I had
 a cold but hidden, so it does not impact me that much but I cannot lose it
 either. Headaches started at about 20³⁰, which I consider good, even though
 I now cannot comply with Jonathan’s wish of having a look at llvm-gcc for
 spotting a bug in libobjfw.</p>
----
Date: 01.11.2008 00:36
Author: tg@
Title: WTF we have a symlink
Tag: bug snapshot

<p>Much closer to a new DuaLive CD. Reading Ecma 119 (ISO 9660), El Torito,
 and IEEE P1282 (Rock Ridge). Fixing bugs in makefs(8) as if there were no
 tomorrow. Even ifdef’d MirBSD deps, so that they™ can take everything back.
 Finding bugs in the kernel (one harmless, one deadly), and amusing myself
 over certain students. (Bit 0 == 2⁰ == 0x01 not 0x00…)</p>
<p>What’s left? Actual testing (qemu, real hardware), and I suspect that
 the RR_MOVED creation code does not split the directory correctly at 2048
 byte sector boundaries, like all the others. (How many damn academics did
 work on this part of the code, anyway? Modularisation sucks, major arse.)
 Being paranoid and using calloc(3) has saved me from most other illnesses
 since.</p>
<p>Leider mußte ich den Federroten heute alleine trinken, aber immerhin
 konnte ich wbx@ überzeugen, sich zur <a href="@@RELPATH@@mksh.htm">mksh</a>
 zu bekennen – sie kann UTF-8 und überhaupt Umlaute in der Shell, schön mit
 nur einmal Rücktaste drücken und so. Und seinen GNU screen hab ich ihm auch
 noch gefixt. Dafür bin ich den Sharp Zaurus SL-C3200 (und somit auch meine
 einzige OpenBSD-Testkiste) wieder los… eventuell nutzt er ja MirPorts, denn
 <em>unser</em> screen weiß, obs in einem Unicode- oder 8-Bit-Terminal rennt,
 wsconfig/chkuterm sei dank.</p>
<p>Warum sagt mir eigentlich niemand, daß mor…^Wheute die Geschäfte zuhaben?
 Ich bin ja mal <strong>voll</strong> für
 <tt>src/usr.bin/calendar/calendars/de_DE/calendar.ladenöffnungszeiten.<i>$bundesland</i></tt>
 (das geht ja sonst mal gar nicht)!</p>
<p>I discovered that the CD drive in my docking station – namely a
 <tt>cd0 at scsibus0 targ 0 lun 0: &lt;HL-DT-ST, DVD-ROM GDR8083N, 0K04&gt; SCSI0 5/cdrom removable</tt>
 – neither is removable (the docking station is not exactly hot-pluggable)
 nor can it write. It can read various kinds of DVDs, CD-ROM, CD-R, CD-RW,
 but not burn any ☹ And since the lid seems to be custom-fit, I probably
 cannot simply take odem’s DVD-ROM/CD-RW slim drive either. That said, the
 sparc still cannot read CD-RW either… must discover some CD-R media…</p>
<p>I had a good laugh at J�rg “schily” Schilling learning English:
 <tt>&amp;dp[14] /* Hunreds of a Seconds */</tt> – That he doesn’t grok
 licencing is already well-known, so no need to bash that again.</p>
----
Date: 09.11.2008 02:36
Author: tg@
Title: website fun
Tag: security

<p>Now that the website is running on MirOS httpd(8), we can have some
 fun… SSL and such. The following picture may not be displayed if you
 use a nōn-rsync’d mirror, but can be worth the fun:</p>
<p><img src="@@ABSPATH@@/connimg.cgi" alt="connection info" /></p>
<p>An <a href="@@ABSPATH@@/conninfo.cgi">ASCII connection info</a>
 version is, of course, available as well, but images can be embedded
 more easily. For example, if you were to read <a
 href="https://www.mirbsd.org/permalinks/wlog-10_e20081109-tg.htm">this
 wlog entry via SSL</a> (link provided courtesy to readers using Planet
 Symlink), the information would differ.</p>
<p>And if you <em>still</em> get warnings about an unknown certificate
 authority, <a href="http://www.cacert.org/index.php?id=3">CAcert</a>
 provides them for downloading into browsers such as M*zilla Firef*x
 whose idiotic development team opposes against them. For what it’s
 worth, unchecked SSL is still better than no SSL at all (especially
 for entropy ☺) unless you think encrypted = authentic identify.</p>
----
Date: 10.11.2008 21:39
Author: tg@
Title: compilers

<p>First off, <a href="@@ABSPATH@@/MirOS/gzsigkey.cer">the X.509v3
 certificate</a> for gzsig(1) has been renewed. While, strictly spoken,
 this is not necessary, it eases validation.</p>
<p>MirPorts now not only contain ports for various compilers such as <a
 href="http://pcc.ludd.ltu.se/">pcc</a> (which does not suck anymore), <a
 href="http://clang.llvm.org/">LLVM+Clang</a> (which does suck, because
 it’s written in ugly CFrustFrust) and <a href="http://llvm.org/">llvm-gcc
 4.2</a>, it can also peruse them to compile packages:</p><ul>
<li><tt>$ mmake <i>USE_COMPILER=system</i></tt> # mgcc (C, C++), Default</li>
<li><tt>$ mmake USE_COMPILER=pcc</tt> # pcc (C only)</li>
<li><tt>$ mmake USE_COMPILER=llvm</tt> # llvm-gcc (C, C++, Fortran 77/9x)</li>
</ul><p>While clang cannot yet be used there really, the <tt>Build.sh</tt>
 script of <a href="@@RELPATH@@mksh.htm">mksh</a> can use its “ccc” compiler
 driver (which however is experimental) as well as llvm-gcc to build mksh(1)…
 to native code, or to intermediate bytecode (with link-time intra-module
 optimisation and final assembly into native code).</p>
<p>The LLVM Interpreter lli also, surprisingly, works. No patch required.</p>
<p>This (LLVM) is for MirOS-current i386 only; Darwin probably just needs to
 be tested, whereas MidnightBSD and OpenBSD require some more work.</p>
<p>TODO: there is an LGPL’d lzmadec binary, C only even; do something with
 it, possibly to ease use of <tt>.clz</tt> binary packages. Recent storage
 needs have become utterly ridiculous.</p>
----
Date: 12.11.2008 23:55
Author: tg@
Title: small updates
Tag: security

<p><tt>/MirOS/current/i386/fixes10.ngz</tt> holds a new libm, with which
 you can use the three new binary packages (lzma, llvm, llvm-gcc4.2) I’ve
 just placed in <tt>/Pkgs/current/i386/</tt> for your fun. These all have
 been compiled using mgcc-10uA3, as llvm-gcc4.2 is not up to the task.</p>
<p>The new “aalloc” area-based omalloc-employing pool allocator is still
 unfinished; I need to make cookies work and perhaps add more ifdefs to
 make it smaller for MKSH_SMALL users (installer, FreeWRT, …). However,
 feel free to read it and send me comments. I admit it might want to be
 cleaned up a little, but first it’s got to be finished. Do not use it
 yet; it’s intended for both mksh and libobjfw though. Also, I’d like to
 hear of possible optimisations or more security stuff one can throw in;
 the current scheme is the compromise looking best to me. Remember that
 it was written with mmap malloc (and omalloc – Otto Moerbeek zĳn malloc)
 and malloc.conf(5) MALLOC_OPTIONS guard/junk/protection in mind.</p>
----
Date: 17.11.2008 01:17
Author: tg@
Title: aalloc and COFF
Tag: mksh

<p>I got (E)COFF executables to work, even though I cannot produce them <a
 href="@@ABSPATH@@/cvs.cgi/src/sys/arch/i386/include/exec.h">except with a
 hand-crafted binary</a> yet. Maybe these produced by kencc work now.</p>
<p>I didn’t get the time or nerve to continue hacking on aalloc today… the
 whole pointers thing in C is so useless. If I could use assembly, it were
 so trivial. Anyway, the <tt>TPtr</tt> data type will probably have to get
 lost, and I plan on using more temporary local variables for overview.</p>
<p>Besides a beer discussion, <a href="@@RELPATH@@irc.htm">IRC</a> channel
 today featured plans on getting a temporary setup of fast enough machines
 for crossbuilding OpenJDK; replaced confirmed that someone had success in
 doing what I planned, although the nōn-free JDK 1.5 only. We’ll see…</p>
----
Date: 22.11.2008 14:22
Author: tg@
Title: galloc and OPTU
Tag: unicode mksh

<p>aalloc was a failure and prone to mis-type; I’ve started on galloc,
 which is supposed to be even more type-safe and flexible, yet still
 segfaults on me as well.</p>
<p>In the meanwhile, to not stay bored, I enhanced the Unicode (MirOS
 OPTU-8/OPTU-16) function suite in MirBSD and hacked an implementation
 of Plan 9’s Rune functions – dubbed <tt>p9¾_*.c</tt> due to usage of
 our “internationalisation like Plan 9, just on the next layer, and
 within the confines of UNIX®” approach to internationalisation. These
 (as well as some well-known ones like wcsrtombs(3)) should be OPTU
 safe, and we now have a macro telling us if a wide character is part
 of the OPTU Raw Octet codepoint range (in the CSUR PUA assignment).</p>
<p>I’ve contacted Bruno Haible again because his libutf8 misses the
 Unicode Title case (complementing Upper and Lower case)… I’ve got an
 idea how to implement it but would like to double-check with him to
 ensure nothing breaks. The Plan 9 functions need it (these two are
 currently implemented as stubs that just throw <tt>ENOCOFFEE</tt>).</p>
<p>The number of manual pages also raised…</p>
<p>I built XFree86® with a (slightly beefed up) Reiser CCCP in use as
 sole C Præprocessor now… and have yet to notice failures in operation.
 Now we’ll have to find out what else stuff is there depending on the
 existence of <tt>/usr/bin/cpp</tt>, possibly switching it, like the
 &lt;sys.mk&gt; mir‍make(1) file, to <tt>${CC} -E -</tt> (which is not
 100% compatible, because cpp can also read from stdin without the
 dash, whereas, with the dash, neither can read from only a file).
 X11 etc. can be switched to <tt>/usr/libexec/cpp</tt> then.</p>
----
Date: 23.11.2008 17:26
Author: tg@
Title: pcc and OPTU – and just how much Mirzilla Firetapir sucks
Tag: pcc unicode bug

<p>Today, I was sort of bored, so I enhanced something other than our
 libc, namely <a href="http://pcc.ludd.ltu.se/">pcc</a>, with support
 for Unicode/UTF and wide character literals and strings. Kind of fun
 it was.</p>
<p>Still missing is support for <tt>\uXXXX</tt> literals in multibyte
 strings (need ucs2utf function for that, which can be taken from our
 libc again), and, maybe, automatic UTF-16/CESU-8 conversions, if the
 target has UCS-2 (MirBSD, Windows) and the host doesn’t, or so.</p>
<p>Every single time Benny works on <tt>ports/www/firesomething</tt>,
 it sinks in my esteem. Generating crypto keys during fake install is
 <em>not</em> how things should be done (use a post-pkg_add script!).
 And I still think it’s only rumours that it had been rewritten after
 the Netscape® code was opened – it would be better than before then,
 not worse. I’d rather shoot myself than publish such filth, if, like
 Benny says, the code had indeed been rewritten. Well, at least it is
 aware how insecure it is and kills itself:</p>
<pre>14:46⎜«benz» Nov 23 16:40:29 mirbulk firesomething-bin: stack overflow in function virtual nsresult nsCryptoHash::Finish(PRBool, nsACString_internal&amp;)</pre>
<p>And if he wouldn’t document this in a wlog entry, I do ☻☺</p>
<p>But then, I don’t believe him totally unaware:</p>
<pre>14:09⎜«benz» The name "Minefield" is strangely appropriate</pre>
----
Date: 25.11.2008 17:57
Author: tg@
Title: pcc and Win32
Tag: pcc snippet unicode

<p style="margin-bottom:0px;">I think I’m quite finished with the Unicode
 stuff. You can now do really weird things like this:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;">
 <pre>void
今日は(const struct person *$kunde)
{
        printf("Γεια σου %ls!", $kunde->имя);
}</pre></div><p style="margin-top:0px;">ISO C99 permits it.</p>
<p>On the other hand, pcc on Win32 appears broken, cannot be compiled
 either natively (e.g. due to use of “long long” and other bogus things
 which may be C99 but not MS-C90) nor cross from GNU/Cygwin32 (because
 the Win32 port seems to be orphaned and, even if I try to fix these
 things, it doesn’t work for me). So I couldn't get it to build a simple
 MessageBoxW() hello world programme.</p>
<p>I wonder what the reception of my patch will be. I wish support for
 wchar_t were a release goal, then I could try to tap into that BSD func
 *smile* but anyway, I was just bored, and we need wchar_t support in
 pcc anyway, and better I do it than some ISO-2022-JP fanboy. And that
 above example… well, three more lines of code, so that you can actually
 write “int blöd;” ipv “int bl\u00F6d;” ☻☺ I think it’s worth it, even
 if such can confuse the hell out of people trying to read your code.</p>
<p><a href="http://thread.gmane.org/gmane.comp.compilers.pcc/1220">This
 thread</a> contains the patches (three versions, until now… use today’s
 please), in case you want to help testing.</p>
----
Date: 26.11.2008 17:40
Author: tg@
Title: Laptops &ndash; IBM X40 vs MiTAC 4023
Tag: hardware bug

<p>Today, I intended to do some hacking too, maybe on that new allocator
 for <a href="@@RELPATH@@mksh.htm">mksh</a> again. However, I never came
 that far.</p>
<p>Michael "tazz" Kristensen decided he'd try MirBSD. He wanted to boot
 from a USB stick, before he found out his computer couldn't (now what
 a surprise, if you ask me...). Since he has a GNU/Linux and GNU grub
 running, I'd thought we could use memdisk (from SYSLINUX) to boot off
 the ISO as if it were a hard disc. I ended up making him a hard disc
 image with a small FAT12 partition (just IO.SYS, MSDOS.SYS, COMMAND.COM
 and BOOT.COM &ndash; a.k.a. <tt>/usr/mdec/boot</tt>) and a small 4.2FFS
 MirBSD partition (just bsd.rd), which worked. However, I first needed
 to produce a test hard disc (image) into which I could place GNU grub,
 memdisk and the fake disc image. For that, I booted Knoppix 4.0.2, and
 from then on (co&iuml;ncidentally or not) strange things started to
 happen...</p>
<p>My shiny new IBM ThinkPad X40 started to blank the screen while I was
 typing (so it wasn't a screen saver issue). Fn-F7, waiting for half a
 minute or so, and Fn-F7 again brought back the screen. It did not come
 from moving, and it's not the inverter (I checked with a flashlight,
 the TFT is really out). Anyway, it continued to work for quite a while.
 Sadly, the intervals it would work eventually got as short as a few
 seconds. I found out that unplugging the AC power supply helped... for
 a while. The intervals eventually got down there as well. Cleaning the
 fan I tried, but it does not seem like a heat issue either.</p>
<p style="font-size:xx-large"><strong>HELP</strong>!!!</p>
<p>I cannot simply afford another laptop. I bought this one because it
 was popular with the OpenBSD people... while the hardware is working
 nicely, the TFT is a tad small, the keyboard is an absolute shame,
 and the "mouse" buttons... well, let's just not talk about any IBM
 laptops, okay? &mdash; Nevertheless, I need it for work, development,
 and other (private or not) things. Fuck.</p>
<p>This wlog entry has been written on a MiTAC 4023 laptop. While it
 only has a DSTN (or STN?) LCD, 12 MiB RAM, a Cyrix 486DLC CPU with,
 I believe, 33 MHz, it <strong>works</strong> (despite the aged custom
 MirBSD #8-current single-user-only mostly-‍crunchgen(1)d installation).</p>
<p>Tom "nwt" Kohnen, einer der beiden Luxemburger, von denen ich viel
 halte, wenn Du wüßtest, wie oft Dein alter Laptop, den Du für wertloser
 als den Nike-Sticker, mit dem er beklebt ist, gehalten hast, mir schon
 den Arsch gerettet hat... Leider bist Du nicht mehr im IRC, aber falls
 Du dies liest, fühl Dir gedankt!</p>
----
Date: 27.11.2008 7
Author: tg@
Title: Netcraft confirms: my IBM X40 is dying
Tag: hardware

<p>Well, maybe not Netcraft. But I couldn't resist the joke, having been
 a regular Slashdot reader for years, seeing its quality sink, until I
 suddenly could not login any more with lynx(1), best browser ever.</p>
<p>This morning, I tried to power it on from cold state, and could not
 even see that password (machine + IDE) prompt. After I typed blindly,
 I was able to use Fn-F7 (seems as if it's not enabled that early in
 the boot process), but only for less than one second each try, despite
 unplugging the AC power supply again. Well, I made it through the boot
 and shut down the box cleanly again, but it confirms that it's not a
 heat issue. But what else could it have been? At first I thought that
 maybe the PSU sent too much current or something, but that's also not
 it. Perhaps Tonnerre is right and it's all Knoppix' fault ;)</p>
<p>Looks like I'm going to do some hacking on <tt>nwt</tt> today...</p>
----
Date: 04.12.2008
Author: tg@
Title: website updates

<p>If you look carefully, you might notice small changes to the
 website, both HTML and RSS versions. Enjoy!</p>
----
Date: 10.12.2008 18:45
Author: tg@
Title: wb bleu (X40)
Tag: hardware

<p>Yay, the IBM X40 is back. No explanatory letter, just an invoice over
 0 € (funny), but it works. The BIOS clock was off by an hour, I suppose
 they have booted a Windowd® – maybe its “driver” has fixed the graphics
 chip. So I can go back trying to build a working snapshot again.</p>
<p>And never boot a GNU/Linux, especially not KNOPPIX!</p>
<p>PACKSTATION rules! Even though I yet have to figure out how to use it
 for <em>sending out</em> a snail mail package.</p>
<p>Maybe I should just go and get stuff for soldering <tt>odem</tt> back
 to life, though. Anyone want to buy an otherwise perfectly fine working
 IBM X40 with docking station and laptop bag? It’s not used much even by
 the previous owner (french company) and in good state.</p>
<p>We have Mirzilla Firetapir now, but I need to figure out how to get a
 cleanly separated xorg-reachover port for MidnightBSD done… unless I’ll
 be porting XFree86® (client part only) over.</p>
<p>I’ll still be using <tt>nwt</tt> this evening for recreation. And the
 win2k box <tt>nocd</tt> has RANDEX in Cygwin, using tinyirc, irssi, and
 mirsirc. I should <strong>definitively</strong> create a webpage on the
 site here for randex. Maybe make a tinyirc port – once it can deal with
 SIGWINCH…</p><!-- RSS stop -->
<p>Some search engine bait: Tom Kohnen, thanks for your old <tt>nwt</tt>
 laptop. The MirOS OPTU-8 encoding does UTF-8 (WTF-8?) and CESU-8, while
 OPTU-16 can do UTF-16 in pcc. Mirzilla Firetapir is the Vutral name for
 Mozilla Firefox, <tt>ports/www/firesomething</tt>. Vutral too helped to
 invent the MirOS RANDEX protocol (entropy exchange over IRC), which has
 nothing to do with the Win32 worm, just random numbers. My graphician –
 smultron – needs to expand <a href="@@RELPATH@@mksh.htm">mksh</a> and I
 suggested, besides letter spelling (em ka es ha, or for the English, em
 kay es aytch), or the “polish/klingon variant” (m’ksh), or the official
 expansion “MirBSD Korn Shell”, he call it “MidnightBSD Korn Shell”. The
 invalid ones were “make shell” or em kay shell, this is something else.
 On a side note, we’ll be having a logo for mksh(1) soonish.</p>
----
Date: 14.12.2008 00:01
Author: tg@
Title: mksh R36b
Tag: mksh

<p><a href="@@RELPATH@@mksh.htm#r36b">mksh R36b</a> is out, grab it while
 it’s still hot ☺ There’s an impressive change list for a mere bug-fix
 version, and this is the first one where ahoka@ has contributed directly.
 Upgrade is recommended for <strong>all</strong> users. The new memory
 allocator has been backed out for stability.</p>
<p>MirOS-current has mksh R36b plus some changes from mksh-current, mostly
 renaming <tt>set -o utf8-hack</tt> to <tt>set -o utf8-mode</tt> denoting
 said technology is solid after ages of testing. MirOS-stable has R36b.</p>
----
Date: 17.12.2008 00:25
Author: tg@
Title: Updates

<p>Today I updated a couple of things (Perl, OpenSSL, OpenSSH, libpng,
 Lynx, Sendmail) in MirOS-current. Should be pretty much all needed,
 and stuff should still be working.</p>
<p>XFree86® 4.8.0 is out, we’ll update once we have human resources
 to do it.</p>
<p>The next snapshot may not contain the newer X11 unless stable. If
 imported <em>and</em> stable before the #11 release (whose criteria
 include OpenBSD merge), it’ll be used there.</p><!-- RSS stop -->
<p>Today I’ve got an interview at a potential new employer. *crosses
 fingers* Wish me luck. Or employ me. (Donations to be used for travel
 and accomodation for “events” are still desired for all of us
 developers.)</p>
----
Date: 17.12.2008 23:20
Author: tg@
Title: svn2cvs.sh – convert Subversion to RCS/CVS Repositories
Tag: mksh

<p><a href="@@ABSPATH@@/cvs.cgi/contrib/hosted/tg/svn2cvs.sh">svn2cvs.sh</a>
 is an mksh(1) shell script able to convert from Subversion repositories
 (remote access via URLs, needs installed svn client) to RCS/CVS repositories
 (local access via pathnames, needs installed rcs(1) ci(1) co(1) GNU RCS, as
 well as cvs(1) GNU CVS, for rcsfile(5) handling). For more information, see
 the included help as well as the commit message.</p>
<p>If you have any improvements or requests regarding this script, please
 contact me or the <tt>miros-discuss@</tt> mailing list. There is a <a
 href="http://thread.gmane.org/gmane.os.miros.general/8673">discussion
 thread</a> for it.</p>
<p>In case you didn’t, read cvs(GNU) a.k.a. The Cederqvist! Another source
 of <a href="http://www.stremler.net/Code/cvs_tricks/">CVS tricks</a> is
 courtesy of «ThunderChicken:#cvs» and includes some from myself.</p>
<p>The 13.rcs(PSD) documentation and rcsintro(1) are online as well!</p>
----
Date: 24.12.2008 11:49
Author: tg@
Title: Chaos Communication Congress upcoming
Tag: event

<p>I have just placed a couple of MirOS CDs and flyers (English and
 French only though ☺) in the hands of a friend while helping him to
 move to Berlin. Either him or Benny (bsiegert@) or Andreas (gecko2@)
 will distribute them at 25C3, or we’ll place them somewhere. I (tg@)
 will not attend, replaced (ahoka@) probably neither. You might be
 able to track down Benny in between some of the talks if you have
 any questions regarding MirPorts and MirOS, though.</p>
<p>To these who do, happy celebrating!</p>
----
Date: 25.12.2008 18:33
Author: tg@
Title: MirOS @ 25C3 Updates
Tag: event

<p>Word has reached me that Benny and Przemek are both suffering from
 illness (nothing bad, just a cold, don't worry) and thusly will not
 be attending the congress either.</p>
<p>As gecko2@ is currently preparing his machines, we believe he will
 uphold our representation at the event. Please join the <a
 href="@@RELPATH@@irc.htm">IRC channel</a> or the <a
 href="@@RELPATH@@rss.htm#lists">mailing list</a> if you have any
 questions.</p>
<p>To these who do: happy celebrating!</p>
----
Date: 27.12.2008 22:17
Author: tg@

<p>Today, we gained arc4random_buf(3), arc4random_uniform(3) in
 libc and arc4random_atexit(), which is undocumented, but called
 from _exit(2) and all exec-style functions via execve(2) and
 exect(2). Since o‍malloc(3) needs arc4random(3) anyway, it
 is no real overhead, but a great way to make modelling the pool
 stuff even more difficult. Thusly, arc4random_pushk(3) retires
 in favour of arc4random_pushb(3) but stays as cpp(1) define.</p>
<p>Riding on the minor bump, mempcpy(3) stpcpy(3) stpncpy(3) GNU
 style were added as well.</p>
<p>Next plans are: rewrite src/lib/csu for pcc, make a port of
 uw-imapd with libc-client.so (maybe LTMIRMAKE?), make the pine
 and alpine ports use it, make the php-imap extension work with
 it again, further improve src/kern/ stuff and maybe www/mk/</p>
<p>More deep changes are however still postponed until OpenBSD
 is merged better.</p>
<p>I also fixed makefs(8) again ☺</p>
----
Date: 28.12.2008 20:54
Author: tg@
Title: light bulbs

<p>Yesternight, not only my server crashed in the softupdates
 code again (*sigh* two RAID 1 rebuilds and a lot of fsck(8)),
 but also one of these energy saving light bulbs (13W). This
 proves that they do not have a longer lifetime than regular
 bulbs.</p>
<p>I oppose the planned ban of regular light bulbs, because,
 although almost(!) all of mine are energy saving ones, some
 of the propaganda apparently is wrong, plus they are not good
 in situations where the light switch is used very often, or
 when the light is only on for very short amounts, such as in
 the entrance area of an appartement (say 1½ m²).</p>
<p>What did I do? Meh, just some <a
 href="@@RELPATH@@permalinks/news_e20081228-tg.htm">bootloader
 hacking</a>.</p>
----
Date: 30.12.2008 21:34
Author: tg@
Title: MD5 attack lead to faking an X.509v3 Intermediate CA [updated]
Tag: security

<p>I’ve updated <tt>src/etc/ssl.certs.shar</tt>, read <a
 href="http://www.win.tue.nl/hashclash/rogue-ca/">about
 the procedure</a>. Someone might want to update the nss
 <tt>certdata.txt</tt> file (to mark them as untrusted);
 for OpenSSL it’s enough to have them renamed. Luckily,
 the CAs agree wanting to switch to SHA-1 (yuck, broken as
 well). Only, do they get a new root certificate (probably
 not), and where does an OS vendor get such news?</p>
<p><strong>Update:</strong> This appears to be not needed, as per <a
 href="http://broadcast.oreilly.com/2009/01/new-pki-problem-resolved.html">this
 comment</a>. However, how credible is this person? Where is proof?
 I’d recommend everyone who has not yet read it to look at <a
 href="http://cm.bell-labs.com/who/ken/trust.html">On Trusting
 Trust</a>. Anyway, the CA certificates are now trusted again;
 let’s just hope the <em>backdated</em> demo intermediate CA was
 the only one generated in the meantime. We really need my <a
 href="http://thread.gmane.org/gmane.comp.web.lynx.devel/6096">SSL
 known_certs proposal</a>, I think. What’s with these MD2 certs
 anyway? <small>(end of update)</small></p>
<!-- RSS stop --><p>On other notes, we have a new logo for <a
 href="@@RELPATH@@mksh.htm">mksh</a>, thanks smultron.
 Hand-editing SVG is so much fun ☺ no really, in <a
 href="@@RELPATH@@jupp.htm">jupp</a> it works very well.</p>
<p>I also ported the e3 editor to MirBSD, it’s 17 KiB i386
 statically linked (stand-alone) binary. GNU GPL, but good
 for custom-made (hehe…) install/rescue system <tt>bsd.rd</tt>
 kernels. I would like to add TinyIRC-MirOS as well, but need
 to get an exception licence for crunchgen(1) use.</p>
<p>Both tinyirc and mksh(1) now use TIOCGWINSZ more properly
 and aggressively. The shell, in particular, now <em>always</em>
 has <tt>COLUMNS</tt> and <tt>LINES</tt> set.</p>
----
Date: 31.12.2008 00:30
Author: tg@
Title: mksh-current GNU/Cygwin32 binaries (snapshot)
Tag: mksh

<p>An <a href="@@RELPATH@@mksh.htm">mksh</a>-current <a
 href="https://eurynome.mirbsd.org/~tg/pub/mksh-36.9.20081229-cygwin.tgz">cygwin
 snapshot</a> I just built for smultron, our graphical artist
 friend from MidnightBSD (which, by the way, also packages
 mksh(1)). He just did this:</p>
<object data="@@RELPATH@@pics/mksh.svg"
 type="image/svg+xml" width="256" height="200"><img alt="mksh Logo"
 src="@@RELPATH@@pics/mksh128x100.png" /></object>
<p>We’ll see what we do with that “m”…</p>
----
Date: 31.12.2008 16:47
Author: tg@
Title: 25C3 redux
Tag: event

<p>Did you all read my <a href="@@RELPATH@@permalinks/wlog-10_e20081230-tg.htm">comment
 on the MD5 CA thing</a>?</p>
<p>25C3 is over, gecko2@ arrived today, and both he and bogus are just
 too <strong>verpeilt</strong> – they forgot to distribute the MirOS
 flyers and CDs at first, then bogus (who had them) got really ill.</p>
<p>We all somehow are, at the moment. Get better, everyone. (replaced
 couldn’t get to the BSD@Wien pre-christmas party either…)</p>
<p style="margin-bottom:0px;">cnuke@ pointed me to a nice IRC quote:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
17:57 &lt; jtsn&gt; Der 25C3 ist lustig. Deutsche Vortragende brechen sich vor deutschen Zuhörern auf Englisch einen ab. ;-)
18:01 &lt; jtsn&gt; Adolfs Werk war sehr nachhaltig. ;-)
18:01 &lt; jtsn&gt; Das gab's nichtmal in der DDR, das<i>[sic!]</i> Deutsche mit Deutschen auf Russisch reden. ;-)
</pre></div><p style="margin-top:0px;">This’ll be my <tt>~/.etc/sig</tt> for
 a while… it does hold some truth. *looks at this wlog*</p>
<p>Benny is still alive, yet a little offline, hacking on perl stuff for
 MirPorts. Good riddance.</p>
<p>By the way: does anyone know of a way to use a web browser or engine,
 for instance Webkit, from a shell script to produce a rendered version
 of a HTML source file (preferably to PostScript® or PDF)?</p>
----
Date: 31.12.2008 16:56
Author: tg@
Title: IBM X40 – USB stick boot (mission impossible) [updated]
Tag: hardware bug

<p>It’s simply amazing. I wanted to show gecko2@ a USB stick with both
 grml(-small) and MirBSD on it, using SYSLINUX, but this fscking laptop
 does not boot from USB stick. So, the ALIX.1c it is, or the VIA C7.</p>
<p>Update: the VIA C7 doesn’t, either. Phoenix/Award BIOS v6.00PG it is,
 <tt>09/26/2006-ID-PCM7E-6A7L6EIIC-00</tt> apparently (I learned today
 from gecko2@ that you can indeed use the “Pause” key on the IBM PS/2
 keyboard to hold the output during BIOS POST). And I suspect the X40
 just has USB Legacy support disabled, but won’t reboot now.</p>
----
Date: 31.12.2008 17:51
Author: tg@
Title: Best bash tip ever! Use mksh!
Tag: mksh

<p><a href="http://www.nardol.org/2008/12/31/best-bash-tip-ever">Best
 Bash tip ever!</a> is a little… interesting. Of course, mksh(1) can do
 it as well:</p>
<pre>tg@bleu:~ $ head -2 /var/run/dmesg.boot
MirBSD#10uA4 (GENERIC) #1161: Fri Dec 26 21:05:59 UTC 2008
        tg@bleu.mirbsd.org:/usr/src/distrib/generic/obj/build/GENERIC
tg@bleu:~ $ r 2=3
head -3 /var/run/dmesg.boot
MirBSD#10uA4 (GENERIC) #1161: Fri Dec 26 21:05:59 UTC 2008
        tg@bleu.mirbsd.org:/usr/src/distrib/generic/obj/build/GENERIC
cpu0: Intel(R) Pentium(R) M processor 1.40GHz ("GenuineIntel" 686-class) 598 MHz
tg@bleu:~ $ fc -l
1       head -2 /var/run/dmesg.boot
2       head -3 /var/run/dmesg.boot</pre>
<p>What’s best, the <em>modified commands</em> are written into the
 history, not the modificator itself.</p>
<p>Some of the commentaries are rather clueless too, not <tt>$!</tt>
 but <tt>$_</tt> is the last word of the last command, in this case:</p>
<pre>tg@bleu:~ $ head -2 /var/run/dmesg.boot
MirBSD#10uA4 (GENERIC) #1161: Fri Dec 26 21:05:59 UTC 2008
        tg@bleu.mirbsd.org:/usr/src/distrib/generic/obj/build/GENERIC
tg@bleu:~ $ print $_
/var/run/dmesg.boot</pre>
<p>Instead of “<tt>^-s</tt>” you would use “<tt>r -- -s=</tt>” (the two
 dashes are needed as the “r” built-in alias parses its arguments).</p>
<hr />
<p>More on Planet Debian (read via Planet Symlink): how many times do I
 have to tell you it’s “CAs” not “CA’s” again? Please do the world a
 favour and read <a href="http://linuxwiki.de/ApoStrophen">Apostrophen
 und andere Katastrophen</a> with rules for German and English: never
 in German except the word ends with s or similar: „Jens’, Max’ und
 Joes CDs“ and for genitives only in both languages, but with apostrophe
 in English: “Jens’, Max’ and Joe’s CDs”</p>
<p>ciruZ now has a blog too… with two ruby scripts. I prefer mine in
 <a href="@@RELPATH@@mksh.htm">mksh</a> very much, thank you :þ</p>
----
Date: 01.01.2009 17:26
Author: tg@
Title: USB stick boot (mission impossible Ⅱ)
Tag: bug grml hardware

<p>After my earlier escapades, which you might have <a
 href="@@RELPATH@@permalinks/wlog-10_e20081231-tg-g10011.htm">read</a>
 about, here’s some news regarding USB sticks:</p><ul>
<li>The IBM X40 can boot, but always uses a geometry of LBA translated
 into 255 heads, 63 sectors per track, contrary to the “USB ZIP” one
 which demands 64 heads, 32 sectors per track.</li>
<li>The ALIX.1c does recognise the stick’s physical or USB ZIP geometry,
 since they match each other and what the BSD kernel thinks:<br />
 <tt>sd0: 241MB, 241 cyl, 64 head, 32 sec, 512 bytes/sec, 495607 sec total</tt><br />
 However, it still cannot boot MS-DOS® 7.10 from the stick. WTF?</li>
<li>The VIA C7 can still not boot from the stick. It doesn’t even
 appear in the boot menu. Interestingly enough, it does try to boot
 from SCSI even if unlisted (disabling the AHA-2940U2B BIOS helps
 to disable it, but I don’t even <em>know</em> where that MBR code
 which it did boot came from…)</li>
<li>I still hate ATX. I fragged a K6-2 mainboard when trying to
 power it on due to a flash(?) (German: Überschlagsblitz). Also,
 I definitively have a lack of hardware with an ISA slot, a floppy
 drive, and USB.</li>
<li>The (old) <tt>herc</tt> hardware might work, but its keyboard
 controller is damaged, ISTR I wrote about it ages ago. Some day,
 I’ll either solder in a new one or use a USB keyboard to bring it
 back working (to hack a hercules framebugger).</li>
</ul>
<p>So the way out of this misére is a “machine sector &lt;type&gt;
 &lt;filename&gt;” command for boot(8/i386). It should be able, at
 least, to load: an MBR/PBR, a GNU GRUB stage2, stage2_eltorito
 (with boot-info-table emulation), SYSLINUX, ISOLINUX, EXTLINUX,
 an MS-DOS® 7.x IO.SYS. But at the beginning, I’m content with less.
 Because it seems to be impossible to boot DOS from a USB stick,
 due to the varying CHS geometries, MEMDISK might be the way to
 go for a triple-boot stick. A combined grml+MirBSD thing would
 not be hindered by it because both SYSLINUX and boot(8/i386) use
 the LBA access method if available.</p>
<p>Benny beat me, he did the first commit this year. Congrats!
 Oh, and the second and the third. But I’ll write the first wlog
 entry, hahaha, and <strong>the Developers’ Weblog is <em>not</em>
 a blog!</strong> Oh, and the fourth.</p>
----
Date: 01.01.2009 17:30
Author: tg@
Title: Useful GSM tricks

<p style="font-size:small;">Ich guck’ ja keinen an…</p>
<ul>
 <li><tt>##002#</tt> (and press the green/dial button afterwards):
  disable all call redirections (alle)</li>
 <li><tt>##21#</tt>: disable unconditional redirection (immer)</li>
 <li><tt>##61#</tt>: disable redirections if no answer (geht nicht ran)</li>
 <li><tt>##62#</tt>: disable redirections if unreachable (Akku leer, …)</li>
 <li><tt>##67#</tt>: disable redirections if busy (besetzt)</li>
</ul>
----
Date: 02.01.2009 00:16
Author: tg@
Title: SYSLINUX, the horrors

<p style="font-size:small;">Hmm… where is bsiegert@’s promised entry?</p>
<p>SYSLINUX creates an <tt>ldlinux.bin</tt> file from source code which
 is composed of two parts: a bootsector (FAT PBR) and the rest of the
 code, later written to <tt>A:LDLINUX.SYS</tt>. However, the later code
 not only makes assumptions about which bootsector loads it, but also
 jumps into it at will for unimportant things like loading more sectors
 (like the configuration file) from the disc. Bah! Impossible to do, as
 the bootsector is cut off before ldlinux.sys is written. Worse than even
 Microsoft®, who at least don’t go back to the bootsector once the first
 2048 bytes of IO.SYS in DOS 7.10 are loaded.</p>
----
Date: 02.01.2009 03:07
Author: tg@
Title: GNU GRUB, the horrors [updated 3 times]

<p>We can use “machine exec grub /boot/grub/stage2” as well as “machine
 exec grub /boot/grub/core.img” to chain into GNU GRUB-Legacy or GRUB2
 now. GRUB2 is in rescue mode, though, but catting files works, as does
 chaining from GRUB 0.9x (mirports/sysutils/pxegrub) to GRUB2.</p>
<p>Also, “machine exec grub /stage2_eltorito” works, because they are
 actually the same (it doesn’t care if it’s a CD or not; we might use
 that in the future too instead of the <tt>tori_bootflag</tt> hack).
 <strong>However</strong>, while GRUB 0.9x can deal with filesystems
 created by “mkisofs”, “makefs”, “mkisofs -R”, it cannot deal with one
 created by “makefs -o rockridge”, neither the old makefs(8) we had 3
 months ago, nor stock TNF one, nor our new one with my patches. Since
 GRUB2 just says unknown filesystem, it’s fine… but <b>useless</b>.</p>
<p>Anyway, I now have a way to boot MS-DOS® from a USB stick (bootbsd
 → grub → memdisk → DOS) in order to install SYSLINUX on the very same
 stick… gaaaaaaaaaaaah!</p>
<hr />
<p><strong>Update:</strong> Yay! Our bootloader <em>is</em> now multiboot
 compliant, detects El Torito in a better way without the patch-the-code
 kludge, and can thusly survive boot ↔ grub cycles.</p>
<p><strong>2. Update:</strong> It can also chain to itself, and can still
 be used from MS-DOS® or as SYSLINUX (et al.) COMBOOT module. It just can’t
 load SYSLINUX because you usually only have LDLINUX.SYS not LDLINUX.BIN,
 see my earlier post. And it can’t load an MS-DOS® boot sector, however,
 chaining to GRUB then from there to DOS works. (So much for my plans to
 directly load an IO.SYS file.)</p>
<p><strong>3. Update</strong> 18.01.2009: Even GRUB2 could operate on the
 filesystem. As could various OSes and tools (from Schily and others). Just
 grub-legacy can’t. What was it? Padding was missing…</p>
----
Date: 06.01.2009 19:55
Author: tg@
Title: delaying

<p>It's official, I've got a new job (some adminning). However, this means,
 whereas Benny has been committing like crazy, I've got to step back some.
 I somehow broke DOS operation of boot(8/i386) during some of the last
 changes, which means I need to investigate. And probably rewrite all of
 the asm part of it to get rid of the LINKSEG vs LOADSEG problems, since
 I confuse them all the time, and OpenBSD only introduced them because
 they didn't know how to use 32 bit relocations in 16 bit code segments.</p>
<p>This means my mikap project will be delayed a little. Sorry.</p>
----
Date: 12.01.2009 21:26
Author: tg@
Title: bootloader… good so far

<p>After a full three days (well, today I worked – rather interesting stuff
 actually; OpenBSD-based spamfilter, we’ll make most of the setup public, I
 get to set up the backup on MirBSD, Xen HVM DomU, and got lauded – but the
 evening and night it did cost) of continuous bug squashing, they are here.
 The new bootloaders work okay on everything I throw them at.</p>
<p>They’re even smaller ☺ except the new commands, such as “machine label”,
 “cat”, paginating in “cat” and “ls”, support for FAT12, FAT16, FAT28, etc.
 cost a little:</p><ul>
 <li><tt>-r--r--r--  1 tg  tg  - 41456 Jan 12 21:28 boot.old.disc-only</tt></li>
 <li><tt>-r--r--r--  1 tg  tg  - 46736 Jan 12 21:25 boot.new.disc-only</tt></li>
 <li><tt>-r--r--r--  1 tg  tg  - 48892 Jan 12 21:28 boot.old.pxe-only</tt></li>
 <li><tt>-r--r--r--  1 tg  tg  - 57864 Jan 12 21:29 boot.new.disc+pxe</tt></li>
</ul>
<p>As already mentioned, you can load it from DOS (limited: DOS=LOW must be
 in CONFIG.SYS, DOS=HIGH conflicts with the kernel, and chaining breaks) as
 well as SYSLINUX &amp; Co. and any Multiboot loader (GNU grub-legacy, GRUB
 2). You can chain to GNU GRUB (both versions), boot sectors and flat image
 files like ourselves. It does 4.2FFS, CD9660 (no “ls”) and FAT. It also is
 usable as PXE loader, doing TFTP (and supposedly NFS) as well as any local
 filesystem listed earlier – although the boot device seems to be passed to
 the kernel incorrectly if it’s a local drive.</p>
<p>Now we just need more testing and a manpage polish… and some more (minor
 though) fixes like the boot drive.</p>
<p>I plan on bringing out a new snapshot any time soon, now that this works
 and security stuff is in, although Lynx might get updated again first. And
 I still write HTML source code in <em>Blocksatz</em>… old dasr habit.</p>
----
Date: 14.01.2009 07:30
Author: tg@
Title: NetBSD® _also_ switches to 64 bit time_t; sendmail and SSL/TLS certificates; danGerOOus uGLy web2.0 Email; random musings [updated]
Tag: grml snippet

<p>We got reminded that NetBSD® switched to a 64 bit <tt>time_t</tt> by <a
 href="http://www.feyrer.de/NetBSD/bx/blosxom.cgi/nb_20090114_0121.html">Hubert
 Feyrer</a> <strong>as well</strong>. However, one should mention that MirOS
 BSD has been using this since past the MirOS #7 release, i.e. for more than
 four years. Including fixing format string bugs (i386 is not LP64 so a long
 doesn’t contain a time_t) in a plethora of ports. Some kernel parts however
 are Y2100 but not (yet) Y2200 safe (such as 4.2FFS aka UFS1).</p>
<p>Still nice to see others <em>do</em> follow our lead ;-) *wink*</p>
<hr />
<p><a href="http://www.outflux.net/blog/archives/2009/01/13/etoomanycerts/">A
 Debian person</a> wonders about sendmail… but the answer is relatively easy.
</p><p style="margin-bottom:0px;">Snippet from the config:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
O CACertPath=/etc/ssl/certs
O CACertFile=/etc/ssl/deflt-ca.cer
</pre></div><p style="margin-top:0px;">Here, <tt>CACertPath</tt> is the name of a
 <em>directory</em> containing files named <i>xxxxxxxx.y</i> where <i>x</i>
 is the hash of the certificate and <i>y</i> is a number starting at 0 that
 is used to avoid collision if two CA certificates have the same hash. They
 are used for <strong>peer certificate verification</strong> alone.<br />
 <tt>CACertFile</tt>, on the other hand, contains the certificates that are
 <strong>sent to the SSL peer</strong>, in a <em>single file</em>, but
 <strong>excluding our own one</strong>. For instance, it would contain TWO
 certificates in my case (CAcert.org Root CA Certificate, plus CAcert.org
 Class 3 Intermediate CA Certificate), once they switch to the new roots;
 I’m currently still using an older Class 1 one which needs only one there.
 I hope this clears things up. However, sendmail(8) on Debian <em>is</em>
 not funny (I succeeded with it only once I disabled <em>all</em> of their
 scripts, including the sysvinit one, and scp(1)ing <tt>sendmail.cf</tt>
 from my MirBSD system…).</p>
<hr />
<p>Looking at <a href="http://www.klein2.de/?p=48">someone using Google
 Mail for all of his traffic</a>, I can only stress again that Google is
 just plain evil. Especially the company offer. I mean, they can do anything
 with the stored data. They make deletion hard (BTDT, when I cancelled
 <strong>all</strong> of my Google accounts), and you never know if they
 don’t use anything of yours despite that. (And they owe me US$ ~130.)</p>
<hr />
<p>Meh. No “Hello Planet Debian, I’m now a DM (not DD)” post for me. But I
 still work on the “wtf” repository from time to time. I need a package for
 our rdate(8), compress(1), and the <a href="@@RELPATH@@mksh.htm">mksh</a>
 one could need updates.</p>
<p>Our company’s new MXens will run OpenBSD and MirBSD, respectively, with
 pf(4), spamd(8), sendmail(8), mksh(1), <tt>ports/mailnews/bmf</tt>, and
 OpenLDAP interconnection (slave slurping Univention UCS)… hard but nice.
 No SASL, it sucks (the UCS does that for the MUAs, and smarthosts off to
 our sendmail(8) plus spamlogd(8) instead). TLS Certificate Authentification
 is just so much more nice… or IP based, both are Xen DomU on the same box,
 the two BSDs (one offsite though) via HVM (replace Realtek with e1000).</p>
<p>Sometimes, OpenBSD does nice things: /var/backups/pkglist I will take.</p>
<p>VMware Server 2 is okay (MirBSD works fine) but the WUI is most annoying.
 And it eats lots of RAM. But hey, YGWYPF. And it’s better than no MirBSD
 (entropy collection rulez!!!!11!1einself), plus, the host has all the stuff
 needed (or can apt-get it), including jupp_3.1.10-1, mksh_36.2-1ubuntu1
 (from my “wtf” repo), satanic-wallpapers_666.4 (oO). The latter only on my
 workstation though, not the other vmws2 box, and only for the looks.</p>
<p>I switched my 22" (or so, dunno) widescreen reflexive TFT LCD with a 17"
 nōn-wide one that does 1280x1024 (we have a 15" one, but it has the same
 native resolution, so I took the one with bigger pixels as I do <em>not</em>
 run any LCDs in anything scaled instead of the native resolution). Now I at
 least see everything happening on my display ☺ and got brownie points with
 our HR lead (who got my old monitor in exchange for her 15" LCD).</p>
<p>Inactive MirOS Developer and FreeWRT Founder wbx@ (Waldemar Brodkorb) has
 also helped with setting up WDS and procuring some Asus WL-500gP routers,
 so we will also be using FreeWRT Embedded GNU/Linux at tarent.</p>
<p>Nathan Laredo (GNU member and author of tinyirc) and I have reached a
 consensus (compromise?) which enables me to include it on the special grml
 edition of our <tt>bsd.rd</tt> kernel (rescue system mode). That and e3
 will make it; the bootloader needs macros (for calling grub), but that’s
 it probably. And I’ll try to get a MirGRML too. Maybe for FOSDEM.</p>
----
Date: 15.01.2009 21:15
Author: tg@
Tag: mksh
Title: positive feedback

<p>iMil of <a href="http://beastiebox.sourceforge.net/">Beastiebox</a> has
 apparently lauded me for <a href="@@RELPATH@@mksh.htm">mksh</a> – someone
 came into our IRC channel <tt>#!/bin/mksh</tt> by means of it. Thanks, it
 is not often that people give feedback on things. According to them, code
 quality is very good. While many things are inherited this shows that the
 cleanup both OpenBSD and I did <em>did</em> pay off.</p>
<p>Tonnerre thanked for a script of mine he put to good production use: <a
 href="@@RELPATH@@permalinks/wlog-10_e20081217-tg-g10009.htm">svn2cvs</a>,
 which I already talked about. Glad to be helpful!</p>
<p>Sadly, at work we’d probably need cvs2svn. Not going to do. Besides, it
 won’t work that easily – their CVS doesn’t use commit IDs, and svn has no
 tools like rcs(1), ci(1), co(1) which are immensely useful.</p>
----
Date: 15.01.2009 21:22
Author: tg@
Tag: grml

<p>Whew. A long day at work. FreeWRT, OpenNTPD… and that other NTP dæmon.
 For sarge (first got to create a working <tt>sources.list</tt>…) and UCS
 (Univention). No wonder I’m not doing much any more.</p>
<p>Bootloader: cd9660 has no “ls”, ffs and fat (and maybe nfs) do, tftp’s
 excused. But looking at the code… while adding it would not even add any
 but just reshuffle it, it’s advertising clause infested and slightly odd
 so a full rewrite based upon fat and getextent_cd9660(1) will do. Though
 that not before the next snapshot.</p>
<p>This leaves me with the new manpage for boot(8/i386) and the update to
 lynx(1) and regenerating <tt>ports/INDEX</tt> (again).</p>
<p>I also hacked some more wtf-debs and FreeWRT 1.0-stable packages (ARGH
 THIS IS JUST SO… EVIL, but WDS doesn’t work in trunk sez wbx@).</p>
<p>Mika says I’m going to get my MirGRML. I say he’s going to get his BSD
 for grml. My colleagues say I’ll probably get some time off for FOSDEM –
 a few hours of Friday and all of Monday (as a weekend shift is scheduled
 soonish anyway). Just gecko2@ can’t get off early ☹ Daniel says we could
 go for DVDs, but I estimate we won’t make it in time this time.</p>
----
Date: 17.01.2009 23:42
Author: tg@
Title: mumble entropy, moving randomness

<p>I seem to recall that IBM Thinkpads have a movement sensor. We may use
 it as entropy source – not for normal on-the-desk use cases, but still –
 every bit counts. This is probably a Vutral-worthy idea. Someone should,
 really, look into that. Kabelaffe says it has few states, but both level
 and edge (timing) values.</p>
<p>Another thing <a href="http://mumble.sourceforge.net/Main_Page">Mumble
 and Murmur</a>, which he showed me, could do is to collect entropy too –
 Mumble (the client) continuously records anyway (to intelligently try to
 find out when we talk loudly – it works surprisingly well), which hashed
 can contribute entropy (even with hardware mute it’ll get electric noise
 or somesuch); it could also hash the current channel conversation a.k.a.
 input from the network. Now I need to persuade gecko2@ to set up Murmur,
 the server, on thetis, and get bsiegert@ to port qt4-x11, as well as all
 the other prerequisites of Mumble, the client, to MirBSD. May as well be
 he ports both Mumble and Murmur, that latter I could set up on eurynome.
 At least it has more bandwidth than Kabelaffe’s home ADSL.</p>
----
Date: 18.01.2009 20:23
Author: tg@
Title: So much for a weekend
Tag: grml snapshot

<p><a href="@@RELPATH@@permalinks/wlog-10_e20090102-tg-g10014.htm">I seem
 to have written</a> about it already. Damn. Cost me nearly the entire of
 this weekend day (yesterday it was more lashing the alliance with mika),
 and then I still had to fix it – turns out makefs(8) was at fault again.
 Now who’d have expected this?</p>
<p>Owkay. We have a working bootloader (sans the scheduled rewrite of the
 cd9660 filesystem, see my last wlog entry), a cleaned up system for both
 creating the baselive (and DuaLive™ and Triforce™) CDs, stuff for making
 the <tt>bsd.rd</tt> for grml, a working <tt>ports/sysutils/pxegrub</tt>,
 the legal issues cleaned up, the makefs(8) bug fixed, lynx(1) updated as
 well as bugfixed (UTF-8 was broken), the MBR source code portable to not
 include &lt;machine/asm.h&gt;, and the worst problem with the OpenLDAP’s
 port MESSAGE fixed (discovered at work).</p>
<p>Now it’s later than intended again, but I’ll regenerate the port index
 later tonight, head to bed then work, and will set up tear tomorrow, for
 building the snapshot-to-be-uploaded, while writing a new bootloader man
 page. That should about be it.</p>
<p>I wonder if we should rename MirOS #11 to #12 and issue a release from
 what we have in -current now (pretty stable it is, plus #10 isn’t really
 maintained) like I did in the early years, when I start breaking HEAD to
 merge OpenBSD changes into it. Mh, talk with Benny and replaced.</p>
<p>This 40 work hours per week scheme is annoying. But I guess if all had
 34 work hours per week, they’d need additional personnell which has high
 cost overhead. Damn! If I divided my salary by 40/34, I could still make
 a living (not much worse than now; still can’t afford much).</p>
<p>Woohoo. replaced commits, n0-1 (FreeWRT) joins the RANDEX contributors
 club and joins <tt>##/dev/arandom</tt>. Just Benny was on vacation, and,
 again, I didn’t know of it ☺</p>
----
Date: 20.01.2009 18:03
Author: tg@
Title: SCSI-induzierter Rückschlag
Tag: bug event grml hardware snapshot

<p>Heute hat mein Rückschlag, wenn man von den leichten Kopfschmerzen und
 der arbeitsinduzierten Müdigkeit absieht, einen Namen: SCSI. Ich wollte,
 damit wir mit dem neuen Snapshot endlich mal weiterkommen, <tt>tear</tt>
 aufsetzen (hey, ich schreib ja immer noch im Blocksatz im HTML-Quelltext
 ohne Mühe oder es zu wollen oder zu schummeln, wow) und dann kompilieren
 (quasi als Abnahmemessung). Dummerweise habe ich, auch dank gecko2@, nun
 eine Idee, woher die SCSI-Fehler kommen könnten, denn die Plattenprüfung
 im BIOS zeigt keine Fehler an. Ich fürchte, daß das LVD-Kabel kaputt ist
 (i386-Hardware ist eh doof, ein Kabel, ein Terminator und fünf Konverter
 von SCA auf UW-SCSI sind nötig, wo meine SPARCstation 20 das bereits als
 Backplane hat).</p>
<p>Es läuft vermutlich darauf hinaus, daß ich <tt>odem</tt>s 2.5″ 80G IDE
 Platte nehme. Bonus: ältere cvs und Distfiles sind schon drauf, sodaß es
 mit einem schnellen rsync sowie einem erneuten Checkout (da ich / ja eh’
 plattmache mit dem letzten Zwischensnapshot) gehen sollte, und ich sogar
 ein paar Pakete (zumindest IceWM) für den LiveCD-Teil backen könnte.</p>
<p>Toll. Ich habe sogar schon ein vorläufiges ISO zum MirGRML testen, bin
 aber irgendwie platt und auch von Technik mal wieder angenervt. So komme
 ich nie zu was… ich glaube, ich fang morgen mal so früh wie geht an, und
 bin dann ausnahmsweise schon wo’s hell ist zu Hause.</p>
<p>Also: Am Snapshot wird gearbeitet; mbsd4grml kommt direkt im Anschluß;
 grml-mir muß noch getuned (Konfigs), aktualisiert (lynx-cur UTF-8 Bug wo
 ich vorgestern drüber schrieb) und getestet werden; den sparc-Teil nehme
 ich vom letzten Snapshot; für DuaLive™ haben wir somit alles, Extrazeugs
 mache ich nur wenig und nur für i386, und für Triforce™ siehts gut aus –
 eine offizielle Ankündigung kommt auch irgendwann, wenn für beide Seiten
 alles funktioniert und integriert ist. Die <tt>tear</tt>-Migration ist –
 leider – hingegen auf unbestimmte Zeit verschoben. (Damn!)</p>
<p>Bißchen malen müßte ich noch, damit die FOSDEM Edition CDs auch sowohl
 das grml-Logo (habe ein OK von mika), den Shilouetten-Dæmon (altbekannt,
 mit OK von rcollette und mckusick), und ein Triforce haben. Es paßt mir,
 ausnahmsweise, auf Arbeit einen KDE-Desktop mit gimp und Inkscape nutzen
 zu „dürfen“ (peu à peu krieg ich den weniger nervig konfiguriert, und ㈠
 kenn ich KDE 1 schon auf ecce!GNU/Linux 1.0 und ㈡ mag ich kmahjongg eh’
 und konqueror besser als M*zilla Schrott, also ruhe da!, auch wenn ciruZ
 mir GNOME verkaufen will). Mal sehen, was ich da so hinbekomme. Wobei, à
 propos Bildchen: wann lernen die Leute eigentlich, daß man keine Formate
 wie JPEG ob ihrer verlustbehafteten Kompressionsverfahren herumschickt –
 zumindest zum Bearbeiten? *seufz*… Zumindest denke ich, daß ich das ganz
 gut hinkriegen werde, hab da was im Kopf, sogar ohne smultron, lediglich
 die Schrift könnte knapp werden, kA ob der schwarze Hintergrund in dünne
 Linien reinläuft. Mal Daniel fragen…</p>
<p>Ha! Laufend mehr Leute krieg ich vom RANDEX-Protokoll und den Vorzügen
 des Entropieaustauschs, Zufall allgemein, usw. überzeugt. Way to go! Nun
 bin ich gespannt, ob Vutral mal was zu APS findet und was man mit Mumble
 und <i>randomness</i> so machen kann.</p>
----
Date: 21.01.2009 09:45
Author: tg@
Title: We are going to FOSDEM 2009, have been for years!
Tag: event

<p><a href="http://www.fosdem.org/"><img
 alt="FOSDEM, the Free and Open Source Software Developers' European Meeting"
 src="http://www.fosdem.org/promo/fosdem/static" /></a></p>
<p style="font-size:big;">Who’s not? ☺</p>
<p>My boss approached me just this morning… looks as if gecko2@ and I can
 use the bigger company car from here, expense paid, and take the other
 two employees who are going to Bruxelles with us. I’m in the process of
 organising them a hotel now though – maybe bsiegert@ the francophile can
 help with that. gecko2@ is going for a youth hostel though, as usual, as
 he has a membership anyway. Benny and I are already hotel’d.</p>
<p style="font-size:small;">Now if I were on Plänet Debilian…</p>
----
Tag: geocache
Author: tg@
Title: Cachers Sättigungsbeilage
Date: 21.01.2009 13:08

<p>Heute mit einem Kollegen in der Mittagspause aufm Weg zum Chinesen:<br />
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="OpenCaching.de" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="The Frog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 <br />Incr(Caches);</p>
----
Author: tg@
Title: Sponsor for FOSDEM
Date: 21.01.2009 20:02
Tag: event

<p>My employer, <a href="http://www.tarent.com/">tarent Gesellschaft
 für Software-Entwicklung und IT-Beratung mbH</a>, is sponsoring the
 entirety of the attending MirOS Project representatives – which are
 bsiegert@ and gecko2@ as well as me – for FOSDEM, covering the Bonn
 to Bruxelles travel of gecko2@ and me (and two colleagues, where <a
 href="http://rschuster.blogs.evolvis.org/2008/12/21/serving-cross-compiled-openjdk-with-icedtea/">one
 of them</a> had already been mentioned before I entered the company
 ☺) and hotel costs of all three of us. Thank you!</p>
<p><img width="341" height="71" alt="Logo der tarent GmbH (FrOSCon)"
 src="http://www.froscon.de/uploads/pics/tarent-logo.jpg" /></p>
<p>tarent GmbH develops IT solutions and supports open source and <a
 href="http://evolvis.org/">evolvis</a> hosts almost three dozen OSS
 projects, mostly written in Java™, for various fields of endeavour.
 The <a href="http://wiki.evolvis.org/freedroidz/index.php/LinuxTag_2008">Freedroidz</a>
 robots are well known on the “house” events. Jalimo is a Java™ 2 SE
 platform targetting mobile devices. And this is just the beginning.
 We are also internally using a lot of open source projects’ work; I
 already mentioned the FreeWRT, MirBSD and OpenBSD boxen…</p>
<hr />
<p>Sponsors make it possible for us to attend popular events, paying
 for travel and accomodation (we do not necessarily require a hotel,
 though, but it should be a clean place to sleep) cost. We are still
 looking for more sponsors making it possible to travel to even more
 events (Linuxtage Chemnitz, Essen, Graz, Luxembourg, for example) –
 flyers and CDs are already covered by AllBSD.de or ourselves, so it
 would just be that and, if you have money to spare, food and drink.
 Come and <a href="@@RELPATH@@irc.htm">talk</a> if you’re interested
 (in return, like here, we will publicly thank you or provide custom
 MirOS editions, possibly Live DVDs with binary packages, etc).</p>
----
Date: 24.01.2009 13:12
Author: tg@
Title: miscellany

<p>My <a href="http://thread.gmane.org/gmane.comp.compilers.pcc/1220">pcc
 <tt>wchar_t</tt> patch</a> thread gets attention again. Yay!</p>
<p>Good I just installed MirOS on soon-to-be-<tt>tear</tt> (althouh on
 <tt>odem</tt>’s old 2.5″ HDD. I cou^H^Haught an error due to /dev/MAKEDEV
 using the installer’s user and group databases, which were missing some.
 And good I compiled a kernel beforehand… bzero(3) is optimised in locore,
 memset(3) isn’t. Lession learned? Maybe. I bet I’ll do quite some of these
 “Flüchtigkeitsfehler” again in the future, I always used to do so, even
 at school.</p>
<p>Damn. SCSI is expensive, and SSDs are available only for SATAn.</p>
<p>Whew, finally weekend. I slept what appears to be 10 hours and dazed
 for some more. Now I’m unwilling to do any work, but I’ll do what I’m
 owing y’all. (Yes, <em>normally</em> I try to write British English.)
 I estimate we’ll have a new i386 snapshot, and mika his special edition,
 by tomorrow evening. Too bad I delayed testing the MirGRML due to the
 dayjob workload and general… unwillingness. Anyway, FOSDEM is coming,
 we’ll shine.</p>
<p>Lucas “laffer1” Holt from <a href="http://www.midnightbsd.org/">our
 other ally</a> MidnightBSD will also do a special ISO for FOSDEM, which
 we’ll distribute among people. I wonder if Debian GNU/kFreeBSD does some,
 maybe an updated GING CD, but I guess that’s up to the Debian people,
 not for us BSDers.</p>
<p>Since I started working, I can’t bring myself to eat anything in the
 morning, nor really in the evening. I wonder why that is… I still have
 a package of black bread here I bought when gecko2@ visited me, that
 would be 31 Dec I guess. I probably have to throw it away by now, but
 that sucks. I hope I don’t get even more ill… my colleagues and I have
 not been feeling all that well for days.</p>
<p>On building a cross-compiler package: I wish I could bring myself to
 get it done by FOSDEM, maybe Robert Schuster would help baking the JDK.
 I just don’t see me doing it during working hours, however much tarent
 endorses OSS work, because they’re already helping with FOSDEM…</p>
<p>Anyway, I’d better stop concocting some text here, and instead bring
 the mock-<tt>tear</tt> installation into working state and get it to
 start rsynching, cvs(1) co(1)ing, and compiling…</p>
----
Author: tg@
Title: 2009-01-24 snapshot uploaded, pending validation
ID: e20090125-tg
Date: 25.01.2009 20:48
Tag: grml snapshot

<p>Yesternight, I built an i386 snapshot (including a bsd4grml). This
 is already uploaded on <tt>/MirOS/current/i386/</tt> but beware, it
 is pending validation, and some things (like the serial console or
 combined i386+sparc ISOs) are missing. Note that there will be, due
 to time constraints, no new sparc snapshot, we’ll just use the last
 one I built.</p>
<p>If <strong>people who actually use MirOS/sparc</strong> were to
 <em>talk</em> to us, this situation might improve.</p>
<p>It’s still a couple of days until the Triforce™ ISO and CD label
 are due, but we’d appreciate independent test results, as usual.</p>
<p>Plans for the FOSDEM Edition Triforce™ (MirOS DuaLive™ + MirGRML)
 CD-ROM are to add a few packages to the usual baseLive image: IceWM,
 screen, rsync(GPLv2), mc; possibly ent, lzmadec</p>
<p>Watch the <a href="@@RELPATH@@main.htm">news</a> for announcements
 about usability of the 2009-01-24 snapshot.</p>
<p>Update: the three serial console floppies and the five ISOs are
 there and should arrive at the public mirrors tonight. They are in
 fact bootable and quite probably usable, but bsiegert@ still has to
 do the validation by doing a full install and some port builds.</p>
----
Author: tg@
Title: Das Wetter bessert sich
Date: 25.01.2009 15:02
Tag: geocache

<p>Heute mal wieder das Vélo aus- und mich gut eingepackt:<br />
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="OpenCaching.de" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="The Frog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 <br />        inc     dword ptr ds:[caches]</p>
<p>Diesen hatte ich auch schon länger auf’m Kieker, allerdings nie die
 Muße, dort hinzufahren, bei dem Wetter, und der FTF lockte auch nicht,
 weil er – mal wieder – auf der Kommerzseite <em>Tage</em> bevor er auf
 der freien Seite zu finden war geloggt wurde. *grml*…</p>
<p>Liebe <a href="http://planet.symlink.ch/">Plänet Sümlink</a> Leser,
 weil so viele von euch zu &lt;zensiert /&gt; sind, sich das <a
 href="http://www.cacert.org/index.php?id=3&amp;lang=de_DE">CAcert.org
 Root CA Certificate</a> zu installieren, und die Bloatzilla-Leute ihren
 A^H^H^H^H Hinterteil auch nicht bewegt kriegen, editiert der XTaran das
 https in ein http. Zu dumm, daß ich auf vielen Seiten nur noch SSL
 erlaube. Nutzt also den „Mehr...“-Hyperlink, um die Statistikbildchen zu
 sehen, und hofft, daß die neue CAcert-Root bald live <em>und</em> in die
 Brauser geht. MirPorts Framework Nutzer habens natürlich einfacher…</p>
<p>Gleich geht’s erst mal zu meinem Stammrestaurant, einem Jugoslawen,
 ääh Kroaten (Primošten oder auch Dalmatien Grill) mit bogus…</p>
----
Author: tg@
Title: more bootloaders *grml*
Date: 31.01.2009 22:07
Tag: bug event mksh snapshot unicode

<p>To counter the bug in Parallels Desktop, I rewrote all of our Master
 Boot Record (mbrldr, mbrmgr), Partition Boot Record (bootxx), and BIOS
 disc detection code in boot(8/i386). I've also changed the magics, API
 etc. a little between these, rewriting or removing quite some parts of
 both installboot(8/i386) and <tt>bootxx.sh</tt> a.k.a. self-installing
 bootblocks. Oh, and MBR and PBR are smaller, or rather, have more room
 for informatory texts and data block storage now.</p>
<p>Lucas “laffer1” Holt from <a href="http://www.midnightbsd.org/">that
 cat's BSD</a> helped me testing, qemu and bare metal IBM X40 works, so
 I suppose it's good. Can't test on VMware Server 2 right now.</p>
<p>On the other front, I'm writing this wlog entry on MirGRML, which is
 finally sort-of finished (which is why it has much less Unicode than a
 regular posting from my laptop). lynx-cur in sid is broken though, due
 to it using GnuTLS. Gah! Anyway, I see a sid “wtf” repo coming, and it
 was workarounded; next time I'll just do things differently.</p>
<p>Lukas “smultron”      , the graphician of our partner project mnbsd,
 helped a little with the label (while I'm not versed in that field, if
 I had gotten the right material to work with I could've managed it all
 alone <em>this time</em>), and all that's left now is the Live-CD part
 and baking (and testing! even on sparc...) the ISO 9660 image.</p>
<p>There will be 297 MirBSD Triforce™ DuaLive™-CDs (two will go to Kiwi
 land to swishy, one is already reserved for XTaran) and 50 MidnightBSD
 Live DVDs at <a href="http://www.fosdem.org/">FOSDEM</a>.</p>
<!-- RSS stop -->
<p>gecko2@ and bsiegert@ were not too helpful today, although I have to
 admit that real life often has precedence. I merely read some and went
 to sleep early yesterday too (and disabled both POTS and cell phone so
 that I couldn't be waked, haha!) instead of hacking late. Luckily, the
 deadline is not that dead, and I'll almost certainly make it tomorrow,
 in time. Thanks again, Daniel Seuffert from AllBSD.de, for all support
 you and others give to the smaller BSDs. Heh, and laffer1 is not quite
 done yet with his ISO (or UDF?) either.</p>
----
Author: tg@
Title: ext2fs damage
Date: 01.02.2009 00:42
Tag: bug

<p>Fun: MirBSD #8, #10 and #10-current can’t edit or create symlink(7)s
 on ext2fs, MirBSD #7quater could. They hang the filesystem, as well as
 the parent of the mount point, on access, and damage the filesystem. I
 have <em>no</em> idea… (msdos is damaging long filenames, btw.)</p>
<p>4.4OpenBSD can… oO</p>
<p>Benny has done more work on ext2fs, maybe he’ll fix it.</p>
----
Author: tg@
Title: more bugs – bootloader and mksh
Date: 01.02.2009 14:42
Tag: bug event grml mksh snapshot

<p>Again. I almost have a MirGRML+bsd4grml ISO ready (exactly 72 MiB),
 just for the fun of it, and so that people can toy with it – and test
 the integration. But nooo, I even hacked a disklabel, yet it wouldn’t
 access the filesystem. The “machine label” command shows what’s wrong
 (and hints how to fix it), and I missed a corner case in disc I/O due
 to adding two not-so-independent-from-each-other scenarios during the
 El Torito merge.</p>
<p>mksh has funny behaviour with <tt>${foo/@(%)/x}</tt> failing – only
 in Unicode mode though.</p>
----
Author: tg@
Title: MirGRML and FOSDEM DuaLive™ Triforce™ CDs
Date: 03.02.2009 00:54
Tag: bug event grml security snapshot

<p>Uh-oh, 03.02. already. I <em>think</em>, after the switch to GRUB 2
 and another couple of bootlooter fixes, that we’re there yet. Funnily
 I only noticed how BSD cannot access labelled disks when the device’s
 sector size mismatches the one in the label. <strong>There is also an
 embarassing (for upstream) local DoS exploit</strong> possibility, by
 setting a sector size of 0, the kernel traps division by zero. Thanks
 for all the blowfish, yeah.</p>
<p><a href="https://eurynome.mirbsd.org/~tg/pub/mirgrml200901.sum">The
 checksum file</a> for MirGRML 2009.01 (experimental, but probably, by
 now, complete). You’ll probably figure out the ISO link.</p>
<p>The full MirOS CD should be done soonish as well. Just have to test
 it, then I can go to bed. Wish me luck.</p>
<p>GNU grub-legacy cannot access ISO 9660 on devices with sector sizes
 other than 2048 bytes… and, according to mika, has other quirks, with
 recent mke2fs’ inode defaults making it hiccup. Heh.</p>
----
Author: tg@
Title: kubuntu cheats (remember cheaterinterview.mp3? think Shuttleworth)
Date: 04.02.2009 13:20

<p>kdm starts while (Ctrl-Alt-F8) the system is still booting. I only
 noticed it because we log in against LDAP (UCS), and since I have two
 NICs in there now (due to FreeWRT stuff), the Network Manager takes
 more time in bringing the network up. Gah. I do not even <em>want</em>
 to log in before <tt>/etc/rc.local</tt> has run, because it contains
 calls to rdate and starts an egd (entropy gathering dæmon), among other
 things… these cheaters are worse than Microsoft®!</p>
<p>Oh, and when I wanted to unlock it to write about it, it hung (as if
 it didn’t like me). Alt-SysRq to the rescue (we need it in MirBSD too).
 Crapware.</p>
----
Author: tg@
Date: 04.02.2009 19:36
Title: Deutsche Bahn verschenkt BahnCard 25

<p>Leute, kauft euer Nahverkehrsfahrkartenabonnement bei der Deutschen
 Bahn. Nicht nur nerven sie täglich weniger, sind ihre Züge in der
 Regel pünktlicher, sondern sie überfahren einen auch nicht fast… wie
 bei gewissen Stadtwerken vorkommt. Und in der Regel halten sie sogar
 da, wo sie sollen.</p>
<p>Auf jeden Fall habe ich meine innerstädtische Monatskarte bei der
 DB gekauft und hatte heute einen Gutschein für ein Jahr BahnCard 25
 im Briefkasten. Nett…</p>
----
Author: tg@
Date: 04.02.2009 19:38
Title: MirOS heartbeat protocol implementation: abuse as NTP monitoring

<p>I’ve started trying to use the mircvs://contrib/code/heartbeat/
 stuff to monitor NTP timedeltas between my boxen and a reference box
 (some random Stratum 2 pool server I do not use as server in any of
 the boxen, otherwise I might have used the PTB servers). Add rrdtool
 and rrdgraph output. Maybe mail when the boxen are down, until we
 have company monitoring set up?</p>
<p>I wonder if I should do it the “right” way instead of the “little
 effort” way, then commit it? Including cleaning up the age-old code.
 Is there any interest?</p>
<p>On a side note, we need a monitoring and management system, either
 one tool or integrating a few. It should have a command line interface
 and a WUI, different web pages for admins and (read-only) users who
 can look there for the general system state before complaining. Also,
 we need configuration management. A few keywords: nagios, cacti, puppet,
 cfengine. These were thrown into the room. Does anyone have a complete
 solution, possibly with VM management (how much does OpenCRM do?), for
 which we currently use a homegrown Jabber bot (don’t ask…) which does
 the template cloning (zfs, iSCSI) and other setup. Other suggestions,
 tools to avoid, success stories, links, documentation welcome.</p>
----
Author: tg@
Date: 07.02.2009 15:35
Title: FOSDEM Tag 0
Tag: event

<p>Gestern, Freitag Abend, war der Tag 0 der FOSDEM. Natürlich waren
 wir – die anderen beiden tarentler Fabian Köster und der Vortragende <a
 href="http://rschuster.blogs.evolvis.org/2008/12/21/serving-cross-compiled-openjdk-with-icedtea/">Robert
 Schuster</a>, gecko2@ und ich – beim Beer Event, später auch mit
 bsiegert@. Das Bier war lecker, allerdings habe ich zwar nicht zu
 viel aber wohl zu varietätenreich getrunken, sodaß es mir in der
 Nacht nicht so wirklich gut ging und ich noch Bauchschmerzen habe.
 Also keinen mit dem Debian Projektleiter trinken.</p>
<p>Benny hat lustige Sympathiën von Leuten aus anderen Projekten
 bekommen, aber ich darf leider nicht drüber schreiben.</p>
----
Author: tg@
Date: 07.02.2009 15:38
Title: FOSDEM Tag 1
Tag: event

<p>Das Aufbauen verpaßt, aber wir haben ein „m“ (Bild wird später
 nachgereicht, sollte smultron freuen), viele Kontakte, und die
 englischen Flyer sind <em>jetzt schon</em> alle, die CDs runter
 auf ¼ oder so.</p>
<p>Der Unicode-syscons-Vortrag war für mich leider nicht so
 ertragreich; dadurch, daß wir vt100 wscons(4) haben, und durch
 meinen script(1) <tt>-lns</tt> Hack, haben wir schon mehr Probleme
 gelöst und Wissen angebaut als er. Ed Schouten ist aber anscheinend
 ein vielversprechender talentierter Jungentwickler.</p>
<p>Cool, ich habe ein bißchen WLAN! Mal schnell ein bißchen wlog
 Einträge verfassen, Benny und gecko2 wollen ja nicht.</p>
<p>Jetzt nur noch den NetBSD®-Kollegen neben uns zum Installieren
 des RANDEX-Plugins verlassen…</p>
<p>Wer setzt uns eigentlich direkt neben OpenBSD? Zum Glück gibts
 eine große Barriere, daher ist bislang, außer Laserpointerattacken
 (sogar direkt in Bennys Auge) noch nichts passiert…</p>
----
Author: tg@
Date: 08.02.2009 14:52
Title: FOSDEM Tag 2
Tag: event

<p>Alle englischen Flyer weg, alle CDs heute Vormittag weg. Die
 (alten) deutschen sowie die französischen Flyer gehen okay, aber
 die Mengen und Verhältnisse sind echt nicht planbar. Die Flyer
 von der tarent (<a href="https://wiki.evolvis.org/jalimo/index.php/Main_Page">Jalimo</a>
 und <a href="https://wiki.evolvis.org/freedroidz/index.php/Main_Page">Freedroidz</a>)
 gehen auch okay weg, aber die Baumwolltaschen waren schneller weg.
 Die Roboter haben aber das ein oder andere "Oooh!" oder reinen
 Wiedererkennungswert gehabt.</p>
<p>Die Vorträge sind okay, aber leider für mich nichts dabei zum
 rausziehen. Pläne schmieden geht aber.</p>
<p><a href="@@RELPATH@@mksh.htm">mksh</a> hingegen ist mehr als
 nur ein Erfolg, auch wenn mir gruselt, wenn Leute eine ohne den
 emacs-Modus haben wollen.</p>
<p>Hm, irgendwie läßt sich das Event nicht gut in Worte fassen.
 Es hat sich auf jeden Fall für uns alle gelohnt. Das Hotel war
 spaßig (insbesondere der Versuch, eine Rechnung zu erhalten);
 gestern Abend gabs Couscous Merguez + Lamm in einer verdammt
 kleinen aber gemütlichen Bude (mit Couch!), wo wir frischen
 Minztee getrunken haben (fünf Kannen; ich alleine zwei oder so).</p>
----
Author: tg@
Date: 09.02.2009 11:32
Title: FOSDEM is over
Tag: event

<p><a href="https://bilder.bsdgroup.de/images/FOSDEM2009/big/853.jpg"><img
 src="@@RELPATH@@pics/FOSDEM_2009.jpg" alt="CDs and the “m” at FOSDEM 2009"
 /></a><br />(picture courtesy of Christian “taleon” Ruesch from #pcc)</p>
<p>FOSDEM 2009 is over, we are all sober again (I hope), any spotted <a
 href="@@RELPATH@@permalinks/news_e20090208-tg.htm">bugs</a> are getting
 fixed. I tended to the disklabel sector size issue, although that has yet
 to be tested, and we might want to see what upstream does about it. <a
 href="@@RELPATH@@mksh.htm">mksh</a> changes will be coded when I get to
 it, and we’re looking forward towards the next event(s).</p>
<p>Is there anyone interested in making a Virtual Appliance (for qemu,
 VMware, Parallels, you name it) out of MirOS? I could, of course, do a
 standard install one, maybe add some packages, like with the live CDs,
 but I’m not good for desktop style ones. Maybe we want a server and a
 desktop appliance. Benny could bake a GNOME version, just to show off
 (note that I still quite dislike it… and expressed it with one of these
 yellow stickers at the “GNOME HATE” side at FOSDEM ☺).</p>
<p>MirOS/sparc users, show yourselves, if you want snapshots to be built
 and provided more often. Talk to us, so we see the effort to support a
 second platform is not in vain.</p>
----
Author: tg@
Date: 16.02.2009 21:21
Title: still recovering

<p>I admit I hacked a little for leisure tonight, but I’m still
 recovering from a rather bad case of the “common cold” (grippaler
 Infekt) so I’ll yet have to do some catch-up on my duties, read
 and respond to mails and other communiques, etc. So don’t get
 your hopes up <em>too</em> soon. But I could go to my dayjob
 again today, which my doctor gave me a permit to not do for the
 end of last week. Paid about 50 € for remedies and the health
 insurance *grml…*</p>
<p>Not exactly sure where my priorities lie at the moment. The
 computer related things will come a little short in the next
 while; I’ll probably hack some more entropy and bootloader
 related stuff for fun, do another snapshot, while trying to
 get <tt>tear</tt> <em>finally</em> done, but that’s about it.
 The debs are postponed, no matter how much a decent lynx-secure
 package (linked against OpenSSL!) is needed; other MirOS work
 probably too. (Except little things here and there; helping the
 users which give actual feedback, especially for mksh; maybe,
 once we have enough Qs, put up a FAQ.)</p>
<p>I guess I have some catching up on sleep, life duties, and
 non-computer-related activities to do, considering how much
 the new job and the FOSDEM preparations strained.</p>
----
Author: tg@
Date: 21.02.2009 14:01
Title: mksh new memory allocator: postponed
Tag: mksh

<p>The MirOS Project News in the upcoming February issue of the <a
 href="http://www.bsdmag.org/">BSD magazine</a> contains a mention
 of mksh R37 with a new memory allocator. This will, however, be
 postponed, because I could not get it right in time (even though
 I learned from the first tries – and wish I could write it in i386
 assembly) and lost interest for now, as the current one still does
 work. I may revisit that at a later date.</p>
<p>Fixing the PS1 bug, maybe changing the echo builtin to SUSv3 (and
 nothing more), maybe porting, are on the list, besides continuing
 the <a href="http://scan.coverity.com/">Coverity Scan</a> fixes.</p>
----
Author: bsiegert@
Date: 21.02.2009 19:39
Title: History lesson

<p>Today I read <a
 href="http://archive.salon.com/tech/feature/2000/05/17/386bsd/">“The
 unknown hackers”</a>, a piece about Bill and Lynne Jolitz, the creators
 of the 386BSD operating system.</p>

<p>On exhibitions and conferences, we are often asked by visitors why
 the hell we forked form OpenBSD. The same argument, namely that we
 should have been content with submitting patches instead of forking, is
 sometimes brought forward by OpenBSD devs. But here is the thing: We
 did this at the beginning but nobody wanted them&mdash;not even a
 reply to the mail in most cases. What is funny is that according to the
 article, the situation was very similar in the early 1990s, when
 FreeBSD and later NetBSD forked from 386BSD:</p>

<blockquote><p>“The Jolitzes [...] seem to have tried to control quality by
 doing most of the work themselves. This inevitably made their release
 cycle slow, but it was also an implied snub to would-be collaborators
 &ndash; who took their contributions elsewhere. [...] By the time 1.0
 was released, the x86BSD user community had fragmented. Some developers
 had moved to the more active and open NetBSD and FreeBSD teams.
 [The Jolitzes] were criticized for their autocratic style. The
 strength of their convictions did not endear them to people who wanted
 to do things differently.”</p></blockquote>

<p>Funny how history repeats itself, isn't it?</p>
----
Author: tg@
Date: 23.02.2009 15:40
Title: one (lonely) day at work
Tag: bug grml

<p>Today is Rosenmontag, so we were only four people in total today.
 Anyway, we tried to use Mondo to back up and, subsequently, clone a
 Gemeinschaft system with CentOS/amd64.</p>
<p>We learned a few lessions:</p><ul>
 <li>a <a href="http://grml.org/">grml</a> CD is handy, even if it’s
  just a grml-mir</li>
 <li>CentOS sucks, RPM sucks, YUM sucks</li>
 <li>Very few software is available for CentOS</li>
 <li>Upstream software sucks (RPM and DEB versions differ)</li>
 <li>Mondo sucks, it can’t deliver what it promises, has a shitload
  of bugs and is very hard to use</li>
 <li>You’ll have to install a bootloader yourself after a rescue</li>
 <li>The GNU GRUB-legacy from CentOS cannot access (even read-only!)
  a filesystem created with <tt>mke2fs -j /dev/sda1</tt> on grml-mir.
  Neither can <tt>ports/sysutils/pxegrub</tt> from MirBSD.</li>
 <li>Debian Lenny/amd64 comes with a working GRUB1, but not with a
  pxegrub image… anyway, copy ldbsd.com to pxebsd.0 on the netboot
  server we already have, enter it into <tt>pxelinux.cfg/default</tt>
  and use <tt>boot&gt; machine exec grub tftp:/stage2</tt> to chain
  to it. Then copy all the stuff from /usr/lib/grub/… and the binary
  /usr/sbin/grub to it, <strong>remove</strong> /boot/grub/stage*
  first, copy the Debian stuff over, and install (./grub). Voilá.</li>
 <li>GNU bash sucks. Especially with a foreign keyboard layout where
  the ‘-’ key produces a ‘ß’, which inserts a multibyte UTF-8 character.
  Of course, “yum install mksh” worked, thanks to rsc.</li>
 <li>Any kind of vi(1) sucks. Just some, like vim, suck more.</li>
</ul>
<p>In the end, we got what we wanted, with a combination of the MirGRML
 ISO, stock Debian packages, a call to rsync after mondorestore, and
 my cool bootloader. By the way, this means that both using boot(8/i386)
 as direct boot image and as “pxebsd.0” image chained(!) from PXELINUX
 are tested now. (Do not chain to “ldbsd.com” as PXELINUX will unload
 the PXE/UNDI stack before calling it, possibly. It insists that PXE boot
 images¹ are called *.0…)</p>
<p>① which, according to hpa’s FOSDEM talk, must be smaller than 32 KiB…
 the hell… but if such a situation should ever arise, PXELINUX is, in
 fact, smaller. I haven’t yet such a pedantic NIC yet, though.</p>
<p>Too bad that cost me almost the entire afternoon, since I had planned
 on beginning to cross-compile Java™ 6 to MirBSD™ using Robert’s IcedTea
 patches, and hack some more on FreeWRT. But at least, we have achieved
 something (the second server is running just fine now) and learned a lot
 in the progress.</p>
<p>In unrelated news, mikap has integrated bsd4grml into the <a
 href="http://ml.grml.org/pipermail/grml-testing-changes/2009-February/000354.html">new
 grml-live version</a>. Although a few commits to the bootloader (cd9660),
 getextent_cd9660(1), kernel, installer, tpmrng(8) are still pending; he
 will be provided with a new version of bsd4grml then.</p>
----
Author: bsiegert@
Date: 24.02.2009 19:45
Title: Bulk builds revisited

<p>Even though I had added a “mmake bulk-build” target to MirPorts’
 top-level Makefile some time ago, one thing has always been broken: if
 one port in a bulk build fails to build, we do not want to abort the
 whole thing. Using mmake -k however leads to 0-byte packages and
 corresponding bulk cookies being created erroneously. This seems to be
 a consequence of the “indirect” inter-target dependencies used by
 MirPorts.</p>

<p>The fix turned out easier than I thought: there is a
 <tt>REPORT_PROBLEM</tt> variable that can be set to a command run when
 mmake fails. The default is <tt>exit 1</tt>. For bulk builds (i.e. when
 <tt>BULK</tt> is set), we now default to a new <tt>failedport</tt>
 script, which records the directory and flavour in
 <tt>${PORTSDIR}/Failed</tt> and exits with status 0. Thus, the build
 continues at the next port, as is should.</p>

<p>The next thing I want to do is a HTML report of a finished bulk build
 with links to all build reports. I saw this in Rodrigo Osorio's
 “Porting applications in FreeBSD” talk on <a
 href="http://www.fosdem.org/2009/">FOSDEM 2009</a>, and thought it was
 quite nice.</p>
----
Author: tg@
Date: 24.02.2009 20:41
Title: Compiling for MirBSD™ on Debian

<p>Uhm, Benny… times in the web source are supposed to be in UTC…</p>
<p>I just created i386-mirbsd-toolchain and sparc-mirbsd-toolchain
 Debian packages (for my own use, mostly). Because we can.</p>
<p>Maybe I can cross-compile IcedTea with it, to be used to natively
 compile OpenJDK?</p>
<p>Dr. Pfeffer (happy birthday btw) thinks it’s cool. Comrad is also
 interested.</p>
----
Author: tg@
Date: 02.03.2009 18:00
Title: getting closer, slowly
Tag: bug geocache

<p>We’re slowly getting closer to spring! It was about 12°C even in
 the late afternoon of the weekend, and I took out my bike on Sunday
 (helped a friend with cleaning up after moving on Saturday). Sadly,
 three DNFs (one search aborted due to the law enforcement approaching,
 one not even attempted due to too many muggles – although I already
 had logged another cache with almost the same name in exactly the same
 location –, and the third one not done because a certain institution’s
 garden has different opening times during winter period and I didn’t
 quite want to risk using the fire fighters’ entrance, like some other
 logger. Not even for a coin.</p>
<p>Anyway, the tpm driver bugs me a little (it’s possible to hang it
 from user space), and I can’t make <tt>-fwrapv</tt> default because
 <tt>-ftrapv</tt> wouldn’t disable it then. Unless I look more into
 gcc’s source again. But I hereby <strong>officially announce</strong>
 that code on MirBSD® can assume wrapping semantics and 8/16/32/64 bit
 wide integral types, big or little endian. No 9 bit bytes, 36 bit PDP
 endian integers, saturation arithmetics. Ever. It’s a promise.</p>
<p>The IcedTea cross-compile patch and the OpenJDK BSD patchkit are
 not build system compatible. I probably need to go the route of using
 compat_openbsd(8) for it. Kurt Miller said if I sigh Sun’s agreement
 chances are good MirBSD support making it upstream (into the patchkit,
 for now, but maybe eventually into OpenJDK 7). MirUsers will just have
 to use a binary package I provide for bootstrap.</p>
<p>More… some other time. Still wish humans would hibernate too…</p>
----
Author: tg@
Title: GUUG FFG Redux – Geocacheing in Karlsruhe
Date: 14.03.2009 18:19:37
Tag: bug event geocache hardware

<p>Es ging also zum GUUG Frühjahrsfachgespräch nach Karlsruhe. Nun,
 die Stadt kannte ich ja schon vom LinuxTag (meines Erachtens auch
 der beste Austragungsort für jene), aber diesmal eine neue Ecke.
 Hotel, Einzelzimmer, bezahlt vom Arbeitgeber; Event auch. Tutorium
 okay, lehrreich (auch was man nicht will), die Vorträge wechselnd
 gut aber in der Regel es auch wert. Aber wie auf jedem Event lernt
 man viele neue Leute kennen, oder auch Gesichter zu den (Nick)namen.
 Das fand ich gut. Das „social event“ entsprach dem auch, wir waren
 im lokalen Brauhaus, und das Buffet… nunja, ich bin kein Freund von
 Buffets und „kompliziertem“ Essen, aber bin gut sattgeworden, nur
 die „Mousse“ war eher… interessant im Biolekschen Sinne.</p>
<p>Natürlich war ich auch zwischendurch Couscous Merguez essen,
 frischen Minztee trinken, und beim Geocachen meinen Laptop schrotten.
 Hmpf. Immerhin laufen die Flüssigkristalle nicht aus. Drückt mir die
 Daumen, daß der Händler meinen X40 auf Kulanz repariert, da innerhalb
 der Garantiezeit (1 Jahr; ist knapp unter 6 Monate her, daß ich das
 Teil brauchte). Immerhin 3 gefunden, einige nicht gefunden (dafür aber
 ne hiesige Cacherin) oder nicht angegangen (zB da nicht so lebensmüde,
 auf ein >4m hohes Verkehrsschild zu klettern, oder da die Koords zu
 weit weg vom Startpunkt waren).</p>
<p>Dummerweise werde ich also jetzt eher an <tt>nocd</tt> (win2k) und
 <tt>nwt</tt> (80486er Kiste) hängen und nicht weiter entwickeln.</p>
<p>Ich denke, ich sollte mal selber meine Founds durchnumerieren und
 in eine Liste packen, da die meisten eben nicht in allen Datenbanken
 gelistet sind.</p><!-- RSS stop -->
<p>Hier dann die aktuellen „Statistiken“:<br />
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="OpenCaching.de" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="The Frog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 <br />Drei mehr dabei, aber leider kaum auf OC</p>
<p><strong>Unterstützt <i>JamesDoe</i> nicht, boykottiert seine Caches,
 schreibt die Logeinträge bei ihm ausschließlich auf OC.de hin, sodaß
 er die Listings dort wieder pflegen möge, oder schreibt ihm, was ihr <a
 href="http://www.opencaching.de/viewlogs.php?cacheid=111936">von seiner
 Aktion</a> haltet, die Listings auf OC.de zu orphanen!</strong></p>
----
Author: bsiegert@
Title: Short LaTeX hint: correct tables for scientific documents
Date: 15.03.2009 12:24
Tag: latex snippet

<p>One of the things you should pay attention to when writing a
 scientific paper is the layout of the tables. Never, I repeat never,
 use vertical lines or even a “grid” with lines between all cells.
 Instead, use only horizontal lines&mdash;one at the top, one between
 the column headings, and one at the bottom. <a
 href="http://www.ctan.org/get/macros/latex/contrib/booktabs/booktabs.pdf">The
 documentation for the booktab package [pdf]</a>, which is appropriately
 written by a Swiss, explains this nicely. Two more things: the table
 should be in a smaller font than the text (about 10%) and span the
 whole width of the text. As scientific papers are always typeset in
 two-column mode, you may have tables one column or two columns wide.
 The latter is done like this in LaTeX:</p>

<pre>\begin{table*}
\centering\small%
\begin{tabular*}{\textwidth}{@{\extracolsep{\fill}}lll}
\toprule
First column &amp; Temperature (°C) &amp; $D$ (nm)\\
\midrule
Foo &amp; 210 &amp; 10\\
Bar &amp; 300 &amp; 15\\
\bottomrule
\end{tabular*}
\caption{\label{tbl:mylabel} This is the table caption, where you
should explain what identifiers like $D$ above mean.}
\end{table*}</pre>

<p>Units go into the header, or into a separate header line (which is
 IIRC recommended by DIN). The amount of <tt>l</tt> at the end of the
 third line is equivalent to the number of columns. That means you
 should exclusively use left-aligned columns. Also, don’t be afraid to
 make tables wider than high, or with only one line of data. I have seen
 this in Wiley-VCH journals, and it comes out alright.</p>

<p>To make the table only one column wide, replace <tt>table*</tt> by
 <tt>table</tt> and <tt>\textwidth</tt> by <tt>\columnwidth</tt> in the
 example above. Do however leave the asterisk in <tt>tabular*</tt>.</p>
----
Author: tg@
Title: Die erste Frühlingsluft
Date: 21.03.2009 00:59
Language: de

<p>Kurz nach Mitternacht (oder genauer, 23:31:56 UTC). Ich stehe am
 Fenster und atme die frische Frühlingsluft. Gleich in zweierlei
 Bedeutungen, denn es friert nachts; dies ändert jedoch nichts daran,
 daß es die letzten und nächsten Tage wunderbares Wetter hat.</p>
<p>Diese Nacht hatte ich keine Kerze an wie sonst. Ich las und
 unterhielt mich ein wenig, primär via IRC. Auch nicht habe ich
 produktiv gehackt oder dergleichen (für alle, die noch nicht
 lange hier mitlesen: hacken bedeutet nicht cracken). Ich frage
 mich, ob dies zum nächsten Fest anders sein wird. Das Leben gut
 zu verwalten ist definitiv nicht einfach, insbesondere mit einem
 Achtstundenjob, dem inneren Schweinehund, und einfach <em>zu</em>
 vielen guten Ideën (zum Beispiel mksh(1) betreffend).</p>
<p>Nichtsdestoweniger gilt es, aus den paar guten, paar schlechten,
 und vielen mittelmäßigen Impressionen das Beste zu machen. Einen
 Kompromiß zu nehmen, damit man zum Beispiel mit dem Zwischenprodukt
 bereits arbeiten kann (gutes Fallbeispiel, wann es in die Hose
 geht, wenn man das nicht macht, ist "FreeWRT 1.1", more like 3.0).</p>
<p>Dummerweise habe ich die meisten guten Ideën afk oder doch
 zumindest im Zug oder dergleichen; außerdem ist es oft diffizil,
 beim Tippen nicht alles wieder zu vergessen, bedingt durch die
 langsamere Verarbeitungsgeschwindigkeit sowohl von Worten als
 auch der physischen Mittel, sowie dadurch, daß das in-Worte-gießen
 ebenfalls den Geist beansprucht. So manches Mal wünsche ich mir,
 nur für mich zu hacken und es nicht zu publizieren, neue Versionen
 zu produzieren "müssen" (selbstauferlegter Druck), so nehmt es mir
 nicht übel. Keine Angst, weiter geht's immer.</p>
<p>Veränderungen sind auch nichts Feines. Im Großen (in was für
 einer Welt wachsen unsere Kinder eigentlich auf?) wie im Kleinen
 (die Java&trade;-Fuzzis machen meinen Cachewolf kaputt). *seufz*
 Vielleicht muß man echt alles selber machen. Aber ein portables
 GUI-Toolkit für X11 und WinCE, das nicht Qt heißt oder sonstwie
 was komisches Objektorientiertes (außer TP) braucht? Naja, packen
 wir an, was wir können, und machen weiter, in der Hoffnung, es
 werde nicht zu schlimm, und daß auch andere anpacken. (Ist das
 eigentlich typisch deutsch? Jedenfalls bin ich Eifler genug, um
 da keinen großen Aufschrei mehr zu machen. Oder einfach von der
 harten Realität abgestumpft.)</p>
<p>Rückblicke sind kraß. Da merkt man echt, wie alt man ist/wird.</p>
----
Author: tg@
Title: Die erste Frühlingsluft (contd.)
Date: 22.03.2009 12:23
Language: de

<p>Ja, und sie war schön!</p>
<p>Jetzt erstmal Kaffee, bißchen Geocachen, dann weiter hacken,
 und mit Benny zu kommunizieren versuchen ;)</p>
----
Author: tg@
Title: mksh improvements
Date: 22.03.2009 18:51
Tag: mksh

<p>Today's commits should fix Debian #518359 (not tried yet, as looking
 at a 14" Belinea 10 40 40 CRT makes my eyes and head hurt), as well as
 improve a lot of more things.</p>
<p>The mksh(1) echo builtin now behaves more POSIXly in "set -o posix"
 mode (or when called as "sh", if that feature was set at compile time).
 The exact feature set is negotiable, if certain parties, say pkgsrc®,
 are interested.</p>
<p>Thanks to the OpenBSD developers for improving their ksh as well.</p>
<p>The ;&amp; and ;;&amp; features are delayed for now though, sorry.</p>
<p>We're in a feature freeze; people <strong>please test</strong> <a
 href="@@RELPATH@@permalinks/wlog-10_e20081013-tg.htm">mksh-current</a>
 on your system to make <em>R37</em> rock!</p>
----
Author: tg@
Title: Fixes, current and upcoming
Date: 28.03.2009 21:56
Tag: security

<p>Benny has upgraded Mirzilla Firetapir (ports/www/firesomething).</p>
<p>Some time ago I already upgraded libpng (base and port).</p>
<p>Pending fixes: libc (fts), and probably some subset of the recent
 OpenSSL things.</p>
<p>mksh R37 is scheduled to be released RSN.</p>
----
Author: tg@
Title: Mein erster FTF
Date: 29.03.2009 17:43
Language: de
Tag: geocache

<p>Anläßlich meines ersten FTF (ein OC-Only natürlich, weil, sonst
 kriegt man die Benachrichtigung ja nie pünktlich von der drecks
 Kommerzseite) habe ich <tt>src/share/misc/acronyms</tt> für wtf(1)
 mal um entsprechenden Jargon erweitert.</p><!-- RSS stop -->
<p>Hier dann die aktuellen „Statistiken“:<br />
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="OpenCaching.de" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="The Frog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 <br />Zwei mehr, auch wenn ich für einen was länger brauchte…</p>
----
Author: tg@
Title: [rant] FreeBSD® sucks!
Date: 29.03.2009 22:28
Tag: bug mksh snippet

<p style="margin-bottom:0px;">How about this:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
	tg@herc:~ $ /bin/sh -c 'echo "0=($0) 1=($1) 2=($2) 3=($3)"' -- a "b c"
	0=(--) 1=(a) 2=(b c) 3=()
	tg@herc:~ $ nbsh -c 'echo "0=($0) 1=($1) 2=($2) 3=($3)"' -- a "b c"
	0=(--) 1=(a) 2=(b c) 3=()
</pre></div><p style="margin-top:0px;">Heck, not just NetBSD® ash, and almost
 any shell Debian can dig out (bash pdksh ksh93 zsh dash posh) behaves
 the same as mksh.</p>
<p style="margin-bottom:0px;">MidnightBSD (DragonFly and FreeBSD too):</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
	tg@mnbsd:~ $ /bin/sh -c 'echo "0=($0) 1=($1) 2=($2) 3=($3)"' -- a "b c"
	0=(a) 1=(b c) 2=() 3=()
</pre></div><p style="margin-top:0px;">And the best thing of all: I am to "fix"
 this in mksh, as the old FreeBSD® ash is documented to have that weird
 behaviour. (Well, there's always <tt>-DMKSH_BINSHREDUCED</tt>...)</p>
<p>This is not a fault of MidnightBSD (except they could fix mports to
 behave more POSIXish; after all, I had to do that to MirBSD and MirPorts
 often enough), don't get me wrong. It just surprised me, and since I'm
 glad <a href="@@RELPATH@@permalinks/news_e20090329-tg-g10003.htm">they
 switched to mksh as <tt>/bin/sh</tt></a> I basically had to debug it.</p>
<p>I don't remember any more what NetBSD® 1.5 did that its <tt>/bin/sh</tt>
 could not be replaced by mksh, but they fixed it in 1.6 &ndash; Kubuntu
 (the LTS version) fscks up similarily...</p>
----
Date: 05.04.2009 12:16
Author: tg@
Title: mksh at Apple again
Tag: mksh

<p><a href="http://www.midnightbsd.org/">laffer1</a> remembered me of <a
 href="@@RELPATH@@permalinks/wlog-10_e20080712-bsiegert.htm">Benny’s</a>
 Apple bug report about <a href="@@RELPATH@@mksh.htm">mksh</a> inclusion
 into their base system. He also did it back then, as requested, and the
 bug #6735470 would be the result. Unfortunately, one still cannot get a
 publicly accessible version of them.</p>
<p>By the way, <a href="@@RELPATH@@permalinks/news_e20090405-tg.htm">the
 R37b version</a> is out.</p>
----
Date: 08.04.2009 18:31
Author: tg@
Title: Not an mksh bug
Tag: bug debian mksh

<p>When <a href="@@RELPATH@@permalinks/news_e20090407-tg.htm">R37c</a>
 was brought out, I fixed a bug on (among others) IA64. The simple
 memory allocator added a pointer (or two, in Espie's) to the storage,
 placed before what the user got. Of course, gcc wanted to align the
 struct not taking this into account, failing evilly. Luckily, another
 FTBFS was not my fault, but sigsetjmp(3) was merely broken on S/390
 with dietlibc; waldi fixed it in the meanwhile, but I uploaded another
 version of mksh to Debian for now whose mksh-static binary links against
 glibc instead and added me a TODO bug.</p>
<p>All the testsuite failures are certainly interesting though; the hppa
 one looks like a bug in ed(1) there; as to the others, either Perl, or
 binfmt_misc was configured to accept or drop (but not reject) shebangs
 præfixed with a BOM. Whatever.</p>
<p>Maybe I can now finally go back to working on MirBSD instead? :D<br />
 After all, we want a new snapshot (for NetInstall, at least).</p>
----
Date: 11.04.2009 18:23
Author: tg@
Title: Building a snapshot; herc on HGC again
Tag: grml hardware snapshot

<p><a href="@@RELPATH@@permalinks/news_e20090411-tg.htm">Today’s snapshot</a>
 has been built cleanly again, after quite some time without one. Also, a
 CVS snapshot was packaged, again, after a very long time. This allowed me,
 although I didn’t quite plan for it yesternight, to move <tt>herc</tt> back
 to the P-233MMX hardware with the Hercules Graphics Card. Its pckbc(4) is
 still broken, and the ukbd(4) doesn’t attach – but works fine with the BIOS
 or on <tt>bleu</tt>. Damn early USB controllers; I know it’s cheap crap.</p>
<p><tt>demo</tt>’s building too, maybe I do a combined ISO. I also created a
 new <a href="http://grml.org/">bsd4grml</a> to go with it.</p>
<p>Now I can basically order another 8-plug SCSI U320 LVD cable (or wait for
 the one I ordered six weeks ago… NOT) and move everything to <tt>tear</tt>…
 ok I’ve been telling that for one year and a half. But it <em>is</em> time.
 Just hard to buy these cables… on the bright side, it’s much more quiet in
 here now, even with the SPARCstation 20 running. Sometimes, its serial port
 even works, so venerable <tt>nwt</tt> now plays console.</p>
<p>Benny said he’ll probably be going to do a ports bulk build with the new
 snapshot. Let’s cross fingers and hope for the best.</p>
<p>Note that the <a href="@@RELPATH@@permalinks/news_e20090208-tg.htm">FOSDEM
 ISO problems</a> posting was updated with a new path to <tt>fixes10.ngz</tt>
 since a new snapshot got uploaded.</p>
----
Date: 16.04.2009 14:20
Author: tg@
Title: life, sparc and everything
Language: de

<p>Habe „nur“ noch ein paar kleine Bugs fixen müssen, auch im Bootloader auf
 sparc (oO), aber jetzt tut alles, wie es soll. Damit kann ich also noch nen
 Snapshot bauen… ich überlege gerade, auch i386 nochenz durchrennen zu lassen,
 wegen der anderen kleinen Änderungen. Ob ich dann das Easteregg (hm…) wieder
 einfüge? gecko2@ spielt dieweil Musik. Jetzt ist mal RL angesagt.</p>
<!-- RSS stop --><p>Hier dann noch die aktuellen „Statistiken“:<br />
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="OpenCaching.de" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="The Frog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 <br />Paar mehr, schön nach Feierabend oder so.</p>
----
Date: 17.04.2009 15:03
Author: tg@
Title: Gibts eigentlich keinen tuënden Compiler?
Tag: bug pcc rant
Language: de

<p>pcc ist mal wieder kaputt – -O ist gebrochen, tat aber mal. nwcc ist auch
 ein Haufen Scheiße, so kaputte Makefiles, hartkodiertes Fehlverhalten sowie
 unmögliche Annahmen sieht man selten. Selbst die Linux Kernel-Makefiles (in
 FreeWRT gesehen) sind mittlerweile besser. *seufz…*</p>
<p>Ich hab mal unseren nwcc-Port updatet, allerdings krieg ich das Ding weil
 es keinen cpp findet („gcc -E” gibts natürlich nicht, welcher Idiot kodiert
 sowas bitte hart? – und nwcpp baut er dank kaputtem Makefile net enz) nicht
 ans Laufen und habs daher als BROKEN markiert.</p>
<p>pcc hab ich nicht updatet, wir haben einen, der tut, aber Upstream – wenn
 auch nur mit YACC=yacc konfiguriert – baut mit -O2 ne kaputt mksh… -O0 aber
 funktioniert.</p>
<p>Ich weiß ja gar nicht, ob ich die <i xml:lang="en">inner workings</i> vom
 SUNWcc sehen will… außerdem wollte ich ja mal nen Ausflug nach ARM machen –
 dann unterstützte SunPRO nicht mehr alle unsere Plattformen.</p>
<p>TenDRA ist mit Ten15 schizophren und tut auch irgendwie nur so halbwegs –
 auf Debian krieg ich damit immerhin manchmal eine mksh(1) gebaut, aber…</p>
<p>Fabrice Bellards tcc ist ja ein schlechter Witz, der tut <em>net enz</em>
 auf Debian… was aber wohl an glibc liegt.</p>
<p>Von OpenWatcom, den MIPSpro-Ergüssen und so hört man auch nichts. Aber da
 ich die Vendor-Compiler wie Digital Mars, Borland C++ Builder, usw. bereits
 unter Cygwin, Interix, PW32 und UWIN „genießen“ durfte, hege ich kein allzu
 großes Verlangen danach. MIPSpro ist eh’ seltsam.</p>
<p>gcc4 ist ja erwiesenermaßen absolut selbstdisqualifizierend, LLVM ekliges
 CFrustFrust, also bleibt wohl nur noch gcc3 übrig… ☹</p>
----
Date: 18.04.2009 19:57
Author: tg@
Title: mksh world domination via Cydia

<p>I amended my WTF *.deb repository (link to the WTF repository <a
 href="https://eurynome.mirbsd.org/debs/debidx.htm">overview page</a>),
 which carried Debian packages I needed, and later packages for their
 derivates used at $workplace as well, by iPhoneOS 2.2 packages, after
 gecko2@ nagged me enough.</p>
<p>Let’s see if it makes. Requests for packaging welcome, but also if
 someone has already attempted to have dget, dpkg-source &amp; al. on
 the jesusPhone. Oh, and I’d like to have swap over NFS (or something
 similarily useful), as I refuse to cross-build, other than exclusively
 for bootstrapping – a lession learned from OpenBSD (and myself).</p>
----
Date: 22.04.2009 16:47
Author: tg@
Title: Mehr über kaputte Compiler
Tag: bug rant
Language: de

<p>Als ich <a href="@@RELPATH@@permalinks/wlog-10_e20090417-tg.htm">über
 Compiler</a> fluchte hatte ich eigentlich nur im Sinn, festzustellen,
 daß wir wohl weiterhin mit gcc3 „stuck“ sind. Zugegeben, ich habe den
 Autor von nwcc als Idioten bezeichnet in einem „rant“, aber die Antwort,
 die ich per privater eMail erhielt – daher nicht hier wiedergegeben –
 überraschte mich doch etwas. Ich habe nichtmals alles von ihr gelesen,
 aber… naja. nwcc baut mksh nicht korrekt, selbst wenn er korrekt tut,
 weil er zum Beispiel 「void **」 mit 「void *」 verwechselt. Ich schrieb
 von Warnungen, aber der Autor von nwcc zieht es vor, nicht zwischen
 gcc-Warnungen beim Bauen von nwcc und nwcc-Warnungen beim Bauen von <a
 href="@@RELPATH@@mksh.htm">mksh</a> zu unterscheiden. Weiterhin wagt er
 es, meinen rant-Idioten als ad-hominem-Attacke zu bezeichnen, selber
 jedoch erst recht eine derselben zu lancieren.</p>
<p>Nunja. Ich denke, ich habe durch das entfernen des ohnehin defekten
 nwcc-Ports seinem Wunsch genüge getan. Hiermit weise ich darauf hin,
 daß der erwähnte Idiot keinesfalls wider seine Person gerichtet war,
 sondern sich auf die Tätigkeit des Hartkodierens falscher bzw. nicht
 portabler Annahmen bezog. Damit ist das Kapitel für mich geschlossen.
 Achja: in einem Makefile eine Regel wie ein Verzeichnis nennen tut
 nicht – das mußte ich lernen (bei install(1) zum Beispiel), und selbst
 wenn es funktioniert tut sie nicht das, was Nils Weller gerne hätte,
 nämlich automatisch in das Verzeichnis hinabsteigen und dort weiter
 make(1)n.</p>
<p><strong>Update</strong> 18:40 – Wir haben uns geëinigt, daß wir
 keine gegenseitigen Kriegserklärungen wollen, also halte ich mich
 jetzt an „shut up and hack“ und vergesse das Ganze.</p>
----
Date: 22.04.2009 16:53
Author: tg@
Title: HW RNG, Geocaching und so
Tag: geocache
Language: de

<p>Bei <a href="http://www.naturalnik.de/wordpress/">Natureshadow</a>
 seinem Blog findet man bisweilen lustige Sachen, zum Beispiel den
 unten eingebetteten T5-Cacher (nicht im RSS).</p>
<p><a href="http://blog.rheinlandcacher.de/">Geocachen im Rheinland</a>
 ist auch nett, hat öfters Tips und so. Schade ist, daß man die Coins
 nicht als Nichtmitglied in einem Klub bestellen kann. Bei Bertelsmann
 bin ich ja auch raus.</p><!-- RSS stop -->
<p><img src="http://www.naturalnik.de/photosharing/t5cacher.jpg"
 alt="T5-Cacher ☺ geocaching, spontane Gedanken" /></p>
----
Date: 22.04.2009 16:58
Author: tg@
Title: mksh $(…) evaluation bug
Tag: bug mksh

<p><a href="https://bugzilla.redhat.com/show_bug.cgi?id=496791">RedHat
 BZ#496791</a> is another example of a bug I documented better in the
 commitids 10049EF448F5F89A278 and 10049EF493039137B14 in mksh(1).</p>
<p>The gist is: $(…) are not parsed recursively but by a lexer hack,
 namely merely looking at matching parenthesēs; this needs to go away.
 Until then, this bug cannot be fixed.</p>
<p>And while at it, ((foo); bar) subshells need to be fixed so that
 they are not parsed as ((…)) arithmetic expression with a failure
 upon encountering a sole closing parenthesis.</p>
<p>The <a href="@@RELPATH@@mksh.htm#plans">mksh plans</a> list this.</p>
----
Date: 22.04.2009 16:07
Author: tg@
Title: perl and HTML entities
Tag: snippet

<p style="margin-bottom:0px;">I don’t even know perl(1), I just can RTFM…</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
<em>tg@bleu:~ $</em> echo 'xyzz�€y' | perl -C -pe \
    's/([\x{7f}-\x{ffff}])/"&amp;#".unpack("U",$1).";"/eg'
<em>xyzz&amp;#65533;&amp;#8364;y</em>
<em>tg@bleu:~ $</em> echo 'xyzz�€y' | perl -C -pe \
    's/([\x{7f}-\x{ffff}])/sprintf "&amp;#x%X;",unpack("U",$1)/eg'
<em>xyzz&amp;#xFFFD;&amp;#x20AC;y</em>
</pre></div><p style="margin-top:0px;">Just hacked it for Natureshadow.</p>
----
Date: 22.04.2009 17:26
Author: tg@
Title: perl and quoted-printable
Tag: snippet

<p style="margin-bottom:0px;">While here anyway…</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
<em>$</em> perl -pe 's/=(\n|[a-fA-F0-9]{2})/$1 eq "\n" ? "" : pack("C",hex($1))/eg'
</pre></div><p style="margin-top:0px;">Needed it once for SyGroup.</p>
----
Date: 23.04.2009 18:14
Author: tg@
Title: current snapshot delaying poll
Tag: snapshot

<p>As I built a 2009-04-17 snapshot but haven't yet come to publish it,
 or especially create a DuaLive&trade; CD again, mostly due to real life
 jumping in or immense (more than usual) headaches, I wonder if I should
 build another one with the changes done afterwards in it. Comments?</p>
----
Date: 26.04.2009 18:09
Author: tg@
Title: MirOS-current Triforce snapshot on BT
Tag: news snapshot

<p>The <a href="@@RELPATH@@bt.htm#s90425">Ostara 2009</a> snapshot of
 MirOS BSD #10-current (DuaLive™ technology and MirGRML 2009.01 making
 a Triforce™ CD) is available on a couple of BitTorrent trackers, <a
 href="http://f.scarywater.net/miros/">our usual tracker</a> and a few
 others for diversity (and so that they do have some legal content).</p>
<p>It's also available for <a href="@@ABSPATH@@/MirOS/current/">NetInstall</a> on both
 architectures.</p>
----
Date: 27.04.2009 13:04
Author: tg@
Title: WTF *.deb repo now has (emulated) m68k too

<p>As <a href="@@RELPATH@@permalinks/wlog-10_e20090418-tg.htm">before</a>,
 I amended my WTF *.deb repository (link to the WTF repository <a
 href="https://eurynome.mirbsd.org/debs/debidx.htm">overview page</a>),
 this time by <a href="http://wiki.debian.org/Aranym/Quick">emulated
 m68k</a> packages.</p>
<p>The mirmake package definitively needs upstream work, but I don’t
 even know off-hand what MACHINE and MACHINE_ARCH are correct for the
 Atari Falcon on m68k… need to peek at the other BSDs for that.</p>
<p><strong>Rant:</strong> the Debian sendmail package <em>sucks</em>,
 I wonder how anyone can use it… I’ll go by scp(1)ing the configuration
 from MirBSD again…</p>
----
Date: 16.05.2009 17:02
Author: tg@
Title: Solución al reto del script
Tag: mksh
Language: es

<p><a href="http://mononeurona.org/entries/view/asarch/1805">asarch</a>
 ha escrito un artículo acerca de cómo se usa la función isatty(3) de
 para verificar si un script tiene
 datos en stdin, quizas en <tt>"$@"</tt>, o para imprimir su uso.</p>
<p>Para el soporte oficial del mksh eres bienvenido en su canal (en inglés,
 ya que no todos hablan el castellano) en <tt>#!/bin/mksh</tt> (sí, sí es
 un nombre válido XD) del <a href="@@RELPATH@@irc.htm">Freenode PDPC</a>
 (<tt>irc.freenode.net:6667</tt>).</p>
<p>Update: asarch ha corregido mi español... ¡gracias!</p>
----
Date: 26.05.2009 20:55
Author: tg@
Title: grml to use MirOS manifold-boot CD technology
Tag: grml

<p><a href="http://grml.org/">grml GNU/Linux</a>, our recently-partner
 project from Austria (not Australia), will gain ISO images bootable by
 dd(1)ing to a USB stick (or CF/SD card, hard disc, ...) via the MirOS
 manifold-boot technology, in use since 10/2007 and developed for the
 self-installing boot blocks. With only a couple of ifdefs, the MirOS
 BSD/i386 <tt>bootxx.sh</tt> was made into a <tt>bootgrub.sh</tt> which
 runs fine on GNU/Linux (with <a href="@@RELPATH@@mksh.htm">mksh</a>,
 of course!) and produces a first stage boot sector capable of loading
 a GNU GRUB2 <tt>core.img</tt> image the same as boot(8/i386) has been
 able to for a while. (GNU GRUB-legacy <tt>stage2</tt> images cannot be
 loaded that way because <tt>bootxx</tt> is limited to 65280 bytes of
 second stage loader &ndash; mostly because the bootloader itself is,
 too, and this enabled me to squeeze out a few more bytes there.)</p>
<p style="margin-bottom:0px;">To say it with Mika Prokop himself:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
23:22⎜«mikap:#grml» mirabilos: und dein bootloader ist geil :)
23:29⎜«mikap:#grml» und ich finds saugeil dass ich ein bsd zum booten mit
     ⎜  grml hab, das muss ich dann gleich mal auf usb-stick installieren

&lt;mika:#grml&gt; mirabilos: because: per default i still want to use isolinux
   (unless grub2 is working better, and: i'm missing the f2, f3,... splashes
   from isolunux)
&lt;mirabilos:#grml&gt; yep, nimm isolinux
&lt;mirabilos:#grml&gt; mkisofs -b hat damit gar nix zu tun
&lt;mirabilos:#grml&gt; das ISO bootet grub, wenns von USB gebootet wird, isolinux,
   wenns von CD gebootet wird
&lt;mika:#grml&gt; mirabilos: and the *same* ISO boots isolinux by default then but
   can be 'dd if=grml.iso of=/dev/sdb'-ed?!
&lt;mirabilos:#grml&gt; yep
&lt;mirabilos:#grml&gt; MirBSD doing that for a couple of years
&lt;mika:#grml&gt; mirabilos: awesome, i still don't get it but this sounds awfull
   rocking
&lt;mirabilos:#grml&gt; mika: ours can even be booted on i386 via both methods *and*
   on a sparc
&lt;mika:#grml&gt; mirabilos: WTF?
&lt;mirabilos:#grml&gt; yep
&lt;mirabilos:#grml&gt; before MirGRML was added, our live CDs were already DuaLive?
&lt;mika:#grml&gt; awesome
&lt;mirabilos:#grml&gt; i386 boot (from cd, hdd, usb, compactflash, sd) into either
   live or install mode + sparc boot (voa OpenBOOT) into install mode
&lt;mika:#grml&gt; mirabilos: pfuh *verbeuge_again* :)
</pre></div><p style="margin-top:0px;" xml:lang="de">Ich glaube, Mika mag meinen
 Bootloader ;)</p>
<p>For simplicity, getextent_cd9660(1) will also be added to the grml-live
 ISO build process, as its output is easier to parse than J&#xFFFD;rg's
 isoinfo. (I definitively should add subdir support there, just haven't
 gotten around to do it yet...) It uses a UCB and a TNF header file and
 otherwise available under the <a href="@@ABSPATH@@/MirOS-Licence">MirOS
 Licence</a> (of course), as are the bootblocks.</p>
----
Date: 27.05.2009 15:32
Author: tg@
Title: GNU GRUB2 and BSD – state of affairs

<p>The “openbsd” option (<tt>bsd.mod</tt>) is unable to boot 4.4OpenBSD,
 MirOS #10, bsd4grml 2009.05rc1.</p>
<p>It appears that the kernel gets a page fault trying to access its own
 <tt>.bss</tt> – but I didn’t really look into it. Any takers?</p>
<p style="margin-bottom:0px;">This is bad, I wanted to add this…</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
menuentry "bsd4grml from harddisk (ISO = grml_2009.05-rc1.iso)" {
        loopback        loop (hd0,1)/grml/grml_2009.05-rc1.iso
        openbsd         (loop)/boot/addons/bsd4grml/bsd.rd
}
</pre></div><p style="margin-top:0px;">… to the solution using GRUB2 for <a
 href="http://michael-prokop.at/blog/2009/05/25/boot-an-iso-via-grub2/">ISO
 loopback boot</a>, which <a href="http://blog.zugschlus.de/archives/825-grml-als-eigenes-Rescuesystem.html"
 xml:lang="de">Zugschlus</a> brought into practical use.</p>
----
Date: 30.05.2009 00:14
Author: tg@
Title: mksh user feedback appreciated
Tag: mksh

<p>With another <a href="@@RELPATH@@mksh.htm">mksh</a> release out, and
 the first feedback (actually a patch with explanation &ndash; naaina
 ported it to the newly released QNX 6.4, 10x) already in, I would like
 to request user feedback if mksh compiles okay for them, the regression
 test suite results, and if it does its job &ndash; especially on the
 more obscure platforms. Current plans for R36b are mere portability and
 bug fixes, and maybe some more of the Syllable, Plan 9 or Haiku issues
 touched if someone does it.</p>
<p>On the other hand, I'm really glad I get feedback, even patches from
 people I've never heard of beforehand, which even touch documentation
 as it should be. One had the luck of adding a feature that had been,
 independently, requested in <a href="@@RELPATH@@irc.htm">IRC</a> mere
 days beforehand. You're welcome ;)</p>
<p>Let me plug a link to the fine manual page mksh(1) or its <a
 href="@@ABSPATH@@/MirOS/dist/mir/mksh/mksh.pdf">PDF</a> version.</p>
<p>Thanks to all users as well, we cracked the 100 in Debian popcon a
 few days ago (102), even though it's down a tad right now, to 94.</p>
<p>Plans are to get promoted to Arch Linux Community from AUR, included
 into Mac OSX, Minix, pkgsrc® (as bootstrap shell) and QNX by default,
 and the usual world domination in general. Hey, I'm fixing dietlibc
 bugs on Launchpad now, so low I've sunk, so gimme some rest.</p>
----
Date: 31.05.2009 12:54
Author: tg@
Title: On BSD derivates and ports frameworks

<p>Random musings, devised on the best place ever to think (the one
 in the house where there will be no computer, at most a telephone;
 insiders know where it is, afk): I wonder what <a
 href="http://www.aeriebsd.org/">ÆrieBSD</a> will do regarding ports.
 Sure, granted as long as they don’t change their uname(1) away from
 <tt>OpenBSD</tt> (and retain Perl, gcc and the obsd perl espietools)
 they can continue using OpenBSD ports. But as soon as… we (bsiegert@
 and I) know the pain, the autotools tricks, have an infrastructure in
 place to deal with it, etc. Of course, there is also pkgsrc®, but they
 aren’t exactly easy to deal with, and pretty over-engineered in most
 parts while lacking in others (even though they catch up in a few of
 these). I wonder…</p>
<p>Okay, The MirPorts Framework assumes Perl, most individual ports
 haven’t been tested with pcc, I have yet to see a constantly working
 <a href="http://pcc.ludd.ltu.se/">pcc</a> as well, and XFree86® (or
 Xenocara in /usr/X11R6, should work too) is depended upon for X11.
 But it should be easier, even if mksh and mirmake are required, than
 starting from scratch. Heck, even MidnightBSD would probably have
 jumped on the MirPorts wagon if they had not had such success with
 mports at that time already.</p>
----
Title: mksh R38 released
Date: 31.05.2009 19:01
Author: tg@
Tag: bug mksh

<p>The <a href="@@RELPATH@@mksh.htm">MirBSD Korn Shell R38b</a> has been
 released. It adds portability to QNX 6.4, a built-in base64 decoder and
 encoder written in mksh itself, and most importantly fixes a regression
 introduced in R38 causing memory corruption.</p><!-- RSS stop -->
<p>This – and a lot more bugs – were discovered while porting Git (resp.
 running its test suite) for Michael Gebetsroither (grml).</p>
----
Title: grml.org manifold-boot™ ISOs
Date: 06.06.2009 14:00
Author: tg@
Tag: grml

<p>The official <a href="http://grml.org/">grml GNU/Linux</a> ISOs will
 use the manifold-boot™ technology from The MirOS Project – development
 builds have already done so for a couple of days – starting at 2009.08
 (the next scheduled formal release).</p>
<p style="margin-bottom:0px;">This basically means you will be able to</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;"><pre>
# dd if=grml-daily.iso of=/dev/sda [bs=…]
# dd if=/dev/cdrom of=/dev/sda [bs=…]
</pre></div><p style="margin-top:0px;">to create a bootable USB stick (or a
 Live HDD, CF/SD/MMC card, etc). MirOS CDs have been using this since
 approximately October 2007. Support for loading GNU GRUB2 instead of
 boot(8/i386) was a dozen-line patch adding some ifdefs to our source
 (upstream; the grml Git repo only contains the generated bootblocks)
 hacked on a lone evening. (Knowledge how to boot GNU GRUB was there,
 from boot(8/i386) “machine exec” support, already.)</p>
<p><a href="http://michael-prokop.at/blog/">Mikas Blog</a> appears to
 contain more documentation on GRUB2 than the FSF’s pages…</p>
----
Title: RANDEX plugin for XChat
Date: 06.06.2009 14:05
Author: tg@

<p>The already mentioned RANDEX protocol (entropy exchange via IRC) is
 now supported, by means of a plugin, on XChat as well. Of course, the
 whole feeding entropy back to the kernel thing can only work on Win32
 (thanks to my earlier changes to <tt>arc4random.c</tt> and MirOS BSD,
 although I thought our XChat port is stuck at 1.8.11-1 and only now I
 see we have an XChat2 port (with a bzip2 distfile, yuck).</p>
<p>This plugin is therefore tested to compile (by myself), with strict
 warnings on MirOS BSD/i386, Debian Lenny/i386, Mac OSX/i386, Cygwin32
 (for MinGW); it works on Lenny, Win2k (myself) and Mac OSX (gecko2@).
 A <a href="@@ABSPATH@@/MirOS/dist/hosted/tg/randex.dll.gz.1.05">ready
 made DLL</a> for Win32 is available for direct download from us as is
 the <a href="@@ABSPATH@@/MirOS/dist/hosted/tg/xchat-randex_1.05.orig.tar.gz">source
 code</a>. It is, of course, <a href="@@ABSPATH@@/MirOS-Licence">MirOS
 licenced</a>.</p>
<p><a href="@@ABSPATH@@/cvs.cgi/ports/net/irssi/files/randex.pl">irssi
 plugin</a> is available from CVSweb or AnonCVS; the MirPorts versions
 of sirc and tinyirc, as well as tinyirc on bsd4grml and the Live CDs,
 also support the RANDEX protocol.</p><!-- RSS stop -->
<p>While it does not feed back entropy to the kernel on e.g. Mac OSX –
 due to a hypothetical arc4random_pushk(3) function needing root privs
 – it can still be used to access the pool by typing <tt>/RANDOM</tt>,
 or simply participate in the distribution (one can get back some from
 the pool from <a href="https://call.mirbsd.org/rn.cgi?from=wlog">call
 MirBSD</a>), thus gecko2@ offered to push it into Fink.</p>
<p>I hope “Biertier” comrad now joins the fun set up by Vutral and me,
 especially since he operates an SSL-only private IRC server.</p>
----
Title: Website: now with “Corporate” Identity
Date: 21.06.2009 11:25
Author: tg@

<p>Thanks to smultron and quite some bugfixing and hacking of yours
 truly, the titles of the pages on our website are now pregenerated
 PNG images, depicting the headline text in <em>Gentium Italic</em>
 (the font in which our flyers have always been set, as well as the
 <a href="@@ABSPATH@@/MirOS/dist/mir/mksh/mksh.pdf">PDF</a> version
 of the <a href="@@RELPATH@@mksh.htm">mksh</a> manual page (since a
 few weeks, once I found out how to use it with groff).</p>
<p>Of course, it <strong>still</strong> looks superb in Lynx, using
 &lt;img alt="…" /&gt; tags, and is valid XHTML/1.1 still.</p>
----
Title: Website: “Corporate” Identity II.
Date: 22.06.2009 12:21
Author: tg@

<p>We’re now doing Font Embedding (MSIE4+ and CSS3 styles) with the
 already mentioned Gentium font, using Gentium Basic for the styles
 it doesn’t support (bold; bold italic). Sadly, if the browser does
 not yet support it, the bold formatting is lost in its entirety if
 Gentium is installed locally. I also tried putting “Gentium Basic”
 first in the font-family list, but it doesn’t fall back to Gentium
 upon encountering Greek or Cyrillic characters then, but uses some
 totally random fonts instead (something illegible for Greek), that
 Opera 9 stuff on MirBSD, that is.</p>
<p>bsiegert@ has tested it with Safari 4 from 北京 and says that it
 works, although his screenshot looks like browser emboldened to me
 (no idea… but trying to combine Gentium + Gentium Italic + Gentium
 Basic Bold + Gentium Basic Bold Italic into one font is hard.</p>
<p>And the Ⅱ U+2161 ROMAN NUMERAL TWO is missing… ☹</p>
----
Author: bsiegert@
Date: 07.07.2009 10:02
Title: Carbon 2009, Biarritz, France

<p>I spent the past week in Biarritz for the <em>Carbon 2009</em>
 conference. Biarritz is located in the Basque country on the shores of
 the Atlantic ocean. It used to be a resort for the rich ones (Napoleon,
 for instance, had a summer residence there), and the town still has
 that kind of feeling to it. The conference took place in the Casino,
 right on the beachfront, and in a former Casino transformed to a
 convention center, with a nice view over the ocean. We had only a few
 hours of sun here and there; we did take a bath in the ocean but it was
 quite cold.</p>

<p>I did an oral presentation about the "Structure and Reactivity of
 Carbon Nanotube/Manganese Oxide Nanocomposites", which was well
 received, I think. There were some interesting questions, and
 everything went well&mdash;except for the fact that the "moderator
 monitor" in Keynote stopped responding at about the third slide. On the
 big screen however, everything continued smoothly. Other talks were
 very interesting, too: Kazu Suenaga from AIST in Japan showed
 atomic-resolution electron microscopy images and even videos of
 reactions taking place inside the microscope. Wow.</p>

<p>For the people presenting posters, the situation was less rosy
 though: all the poster sessions were in parallel to a buffet, so you
 had to choose between eating and looking at the posters.</p>
----
Title: krank ‣ ziek ‣ ill
Date: 29.06.2009 21:04
Author: tg@
Tag: geocache

<p>I got ill during the night from Thundersday to Friday last week,
 damn Berlin weather (hot, humid, chilly wind especially indoors in
 the exhibition halls), so you’ve got to wait a little longer for a
 report about LinuxTag.</p>
<p>I will also need to take care of roff2htm better, as some of the
 pages produce invalid XML (overstrike my arse, we use WTF-8), plus
 it’s probably better to cease using a chain of sed(1) exprs…</p>
<p>Mika is awaiting more bootloader hacking. A 4.1 GiB grml DVD did
 not work for boot(8/i386) either… shux…</p><!-- RSS stop -->
<p>I however did get to geocache, especially today, as I discovered
 one in almost spit distance from my home. Too bad it was listed on
 the .COMmercial site only, so I hadn’t noticed. Anyway…<br />
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="OpenCaching.de" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="The Frog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 <br />I still plan on inventarising them…</p>
----
Title: hot
Date: 03.07.2009 19:21
Author: tg@

<p>About 30°C in the bureau don't make working easy. At least, <a
 href="http://www.tarent.com/">my employer</a> saw the need and
 bought ventilators for every office room which did not yet have
 one. Within approximately three hours after being told of the
 need. <em>Nice!</em> It was still too hot to work, and <tt>apt</tt>
 is a buggy pile of... whatever. Maybe I should search for my own
 ventilator, so it doesn't get that hot at home. I actually was ill
 again yesterday due to the heat (and it got worse instead of better
 over the late morning, when I thought I could sleep it out).</p>
<p>NetBSD® makefs(8) overwrote meaningful data with padding if you
 told it to not pad (fixed), and one of its header files comes with
 CR-LF (DOS) line endings. Nice, eh?</p>
----
Title: don't procrastinate!
Date: 07.07.2009 19:00
Author: tg@
Tag: event

<p>Hell yeah. I promised a wlog entry about the Linuxtag 2009 visit.
 I planned on making it somewhat detailed, enumerating a couple of
 things I did other than catching a few geocaches with a company's
 EeePC and MirBSD and CacheWolf on a USB stick, and getting ill.</p>
<p>Alas, things often are not as desired, and I had to work last week,
 while still slightly ill, and I just never came around doing it. I
 arguably could write up something now, but I forgot most(!) of it
 already, don't want to publish incomplete things out of fear from
 (accidental) omissions, sit on nwt (my dear 80486DLC laptop) and...
 well, procrastinated too much. And I had a long work day and am very
 much enjoying my AfriCola+SchlösserAlt beer, thank you very much.</p>
<p>So, without further ado (why the fuck do Amis tend to have trouble
 with homophones, by the way?), comrad's pictures:<br /><a
 href="@@RELPATH@@pics/LinuxTag_2009/booth.jpg"><img
 alt="The BSD booth setting (overview picture; mira says hello"
 src="@@RELPATH@@pics/LinuxTag_2009/booth_s.jpg" /></a> <a
 href="@@RELPATH@@pics/LinuxTag_2009/merchandise.jpg"><img
 alt="MirOS merchandise, grml and fun buttons, etc."
 src="@@RELPATH@@pics/LinuxTag_2009/merchandise_s.jpg" /></a></p>
<p>It definitively wasn't as technical an event as FOSDEM, and much
 less people asked about <a href="@@RELPATH@@mksh.htm">mksh</a>, but
 at least now I got my OpenPGP signed by two more Debian Developers
 who <em>do not</em> intend on switching keys in the next couple of
 months... *sigh* Anyway, world domination coming, this is required
 for I am still a DM, but wouldn't say no to DD status either. Why,
 à propos, do I have <tt>&lt;tg@d.o&gt;</tt> and only realise that
 because of spam mails sent there? Anyway, met formorer from grml
 in real life, quite nice too. We got some donations for the buttons
 and grml CDs, but the money got distributed among many people.</p>
<p>Hah! These CentOS guys! They made me promise to say CentOS rocks
 if it included mksh; they were going to file a bug at RHEL for its
 inclusion. I looked today, they didn't. So I won't say it rocks. It
 rather annoys, truth be told. Especially since it comes without a <a
 href="@@RELPATH@@mksh.htm">decent shell</a>, and I had to make an RPM
 of OpenNTPD myself! Imagine that!</p>
----
Title: RFH: mksh development
Date: 07.07.2009 20:29
Author: tg@
Tag: mksh

<p><a href="@@RELPATH@@mksh.htm">mksh</a> development is mostly done by
 a single person, "the mksh team" (as seen on Ubuntu forums, out of all
 places!), a.k.a. me, myself and I. Sometimes, actual users report bugs
 or even send in patches. I keep track of oksh's development as well, of
 course. But there are times I would like to get feedback on <a
 href="http://marc.info/?m=124689308408723">issues</a> from other people
 working on pdksh or its descendants. I mailed, for that specific issue
 in question, the Debian developer who created the original patch which
 addressed the scenario except for a corner case (interestingly, as the
 world is small, discovered in a Debian(!) init script from a package
 maintained by aforementioned formorer, on a DomU running Lenny at <a
 href="http://www.tarent.com/">work</a> - don't underestimate the effect
 of synergy) but would really like to talk to some of the OpenBSD devs
 about it; they mostly know what they're doing, even if I worked on ksh
 for longer than most of them, many eyes do help, and most of the time
 I do <strong>not</strong> know what I'm doing XD</p>
<p>[Update] There's also the issue of inter-(POSIX-compatible)-shell
 discussion. For instance, "set -u" vs "$@", which has come up in <a
 href="http://bugs.debian.org/522255">Debian #522255</a> because GNU
 bash4 decided to switch to the behaviour used by the Bourne shell
 (from V7 to SVR4.2), all Korn shells, ash and its descendents (like
 posh) except dash, to not treat it specially. (Funny too how they
 suggest 「${@:-}」 or 「${@:+}」 instead of 「${1+"$@"}」 (from the
 GNU(!) autoconf texinfo documentation) as replacements.) Oh well,
 zsh also behaves like bash2/3 and dash, but then, it's not even a
 POSIX compatible shell. *sigh* Now I wonder what AT&amp;T ksh93 will
 do and <a href="http://article.gmane.org/gmane.os.miros.general/8846">a
 confirmation</a> if it's indeed being forcibly changed by POSIX (IMHO,
 they could at least "agree to disagree", like they usually do, and make
 it vendor defined, so that scripts could not depend on it - "set -u" is
 something I don't use anyway).</p>
<p>So if you're interested in the further development of MirBSD, The
 MirOS Project, one of its subprojects, such as The MirPorts Framework,
 mksh(1), MirMake, even jupp-2.8 or jupp-3.x, please talk to me.</p>
<p>[Update] Do the same for POSIX compatible shell discussion, if you
 are going to take mksh, its goals, needs and history seriously. (Yes,
 it also has bugs, like a non-recursive parser troubling COMSUBs, but
 they may be fixed long-term, especially if people contribute. Ideas,
 at the very least.)</p>
<p>Thanks in advance.</p>
----
Title: kwalletcli Public Beta Test
Date: 08.07.2009 15:54
Author: tg@

<p>I have developed <tt>kwalletcli</tt>, a command-line interface to the
 KDE Wallet, for <a href="http://www.tarent.com/">tarent GmbH</a>, and
 would like public feedback, before releasing an 1.00 version, both on <a
 href="@@ABSPATH@@/cvs.cgi/contrib/hosted/tg/code/kwalletcli/">the source
 code</a> and <a href="https://eurynome.mirbsd.org/debs/dists/hardy/wtf/pkgs/kwalletcli/kwalletcli_0.91-1.dsc">an
 experimental Debian package</a> of it.</p>
<p>Nice things it can do:</p><ul>
 <li>get and set password stanzas in the KWallet via CLI</li>
 <li>contains a CLI wrapper around pinentry’s Aegypten protocol</li>
 <li>contains an Aegypten protocol server, <tt>pinentry-kwallet</tt>, which
  checks the KWallet before deferring to another pinentry of your choice</li>
 <li>contains an ssh-askpass(1) alike kwalletaskpass tool</li>
 <li>can be used in gajim and pidgin to store Jabber passwords in the KDE
  Wallet (not included; patches for these will be made separately)</li>
 <li>plugins for other tools do not introduce dependencies due to separation
  via CLI API</li>
 <li>nice, (hopefully) consistent shell CLI API</li>
 <li>low dependencies: KDE 3 (for kwalletcli itself – KDE 4 might even work,
  with minor Makefile changes, but that was not tested), another pinentry
  (x11, qt, gtk-2, curses – all tested) if needed, gpg-agent if needed, <a
  href="@@RELPATH@@mksh.htm">mksh</a> to run the scripts, ssh-add(1) to make
  use of kwalletaskpass</li>
 <li>with appropriate agents, GnuPG 2 and SSH keys can be made available to
  pure CLI sessions as well, if one has logged in via KDE first (we do this
  at work on our standard desktops, courtesy by me)</li>
 <li>OSI certified Open Source™ Software under a free, very unrestrictive, <a
  href="@@ABSPATH@@/MirOS-Licence">licence</a></li>
</ul>
<p>Any <a href="mailto:t.glaser@tarent.de">feedback</a> welcome!</p>
<p><strong>Update</strong> 09.07. – version 0.90 -> 0.91-1</p>
----
