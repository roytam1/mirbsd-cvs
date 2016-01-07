RCSID: $MirOS: www/data/wlog-10.inc,v 1.470 2015/10/12 22:40:48 tg Exp $
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
<p class="boxhead">On an unrelated note:</p>
<div class="boxtext">
 <pre>
	ppp[28555]: tun0: LCP: deflink: RecvTerminateReq(206) state = Opened
	ppp[28555]: tun0: LCP: deflink: LayerDown
	ppp[28555]: tun0: LCP: deflink: SendTerminateAck(206) state = Opened
	ppp[28555]: tun0: LCP: deflink: State change Opened --> Stopping
	ppp[28555]: tun0: CCP: deflink: State change Stopped --> Closed
	ppp[28555]: tun0: CCP: deflink: State change Closed --> Initial
	ppp[28555]: tun0: Phase: deflink: open -> lcp
 </pre>
</div><p class="boxfoot">(not using pppoe(4), to enable debugging)</p>
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
 〔fwrtcommitstats removed due to FreeWRT archival〕
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
 $ mmake install clean PKG_CONFIG_PATH=$(mmake \
    show=PKG_CONFIG_PATH):/usr/local/libdata/pkgconfig</pre>
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
<p class="boxhead">Part of <tt>httpd.conf</tt> is:</p>
<div class="boxtext">
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
</div><p class="boxfoot">(using documentation addresses)</p>
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
<p>mksh is also the default shell, including <tt>/bin/sh</tt>, on
 FreeWRT Embedded GNU/Linux.</p>
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
<p class="boxhead">Try this:</p>
<div class="boxtext"><pre>
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
</pre></div><p class="boxfoot">Mach-O executable arm</p>
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
<p>If you have an idea how I get the OSF/1 V2.0 cc(﻿1) to correctly
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
 href="@@RELPATH@@cvs.cgi/src/sys/arch/i386/include/exec.h">except with a
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
 &lt;sys.mk&gt; mir﻿make(1) file, to <tt>${CC} -E -</tt> (which is not
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
<pre class="dowrap">14:46⎜«benz» Nov 23 16:40:29 mirbulk firesomething-bin: stack overflow in function virtual nsresult nsCryptoHash::Finish(PRBool, nsACString_internal&amp;)</pre>
<p>And if he wouldn’t document this in a wlog entry, I do ☻☺</p>
<p>But then, I don’t believe him totally unaware:</p>
<pre>14:09⎜«benz» The name "Minefield" is strangely appropriate</pre>
----
Date: 25.11.2008 17:57
Author: tg@
Title: pcc and Win32
Tag: pcc snippet unicode

<p class="boxhead">I think I’m quite finished with the Unicode
 stuff. You can now do really weird things like this:</p>
<div class="boxtext">
 <pre>void
今日は(const struct person *$kunde)
{
        printf("Γεια σου %ls!", $kunde->имя);
}</pre></div><p class="boxfoot">ISO C99 permits it.</p>
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
Title: Laptops – IBM X40 vs MiTAC 4023
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
 MirBSD #8-current single-user-only mostly-﻿crunchgen(1)d installation).</p>
<p>Tom "nwt" Kohnen, einer der beiden Luxemburger, von denen ich viel
 halte, wenn Du wüßtest, wie oft Dein alter Laptop, den Du für wertloser
 als den Nike-Sticker, mit dem er beklebt ist, gehalten hast, mir schon
 den Arsch gerettet hat... Leider bist Du nicht mehr im IRC, aber falls
 Du dies liest, fühl Dir gedankt!</p>
----
Date: 27.11.2008 7:00
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
 they have booted a Windows® – maybe its “driver” has fixed the graphics
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

<p><a href="@@RELPATH@@cvs.cgi/contrib/hosted/tg/svn2cvs.sh">svn2cvs.sh</a>
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
 exect(2). Since o﻿malloc(3) needs arc4random(3) anyway, it
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
<p class="boxhead">cnuke@ pointed me to a nice IRC quote:</p>
<div class="boxtext"><pre>
17:57 &lt; jtsn&gt; Der 25C3 ist lustig. Deutsche Vortragende brechen
        sich vor deutschen Zuhörern auf Englisch einen ab. ;-)
18:01 &lt; jtsn&gt; Adolfs Werk war sehr nachhaltig. ;-)
18:01 &lt; jtsn&gt; Das gab's nichtmal in der DDR, das<i>[sic!]</i> Deutsche
        mit Deutschen auf Russisch reden. ;-)
</pre></div><p class="boxfoot">This’ll be my <tt>~/.etc/sig</tt> for
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
</p><p class="boxhead">Snippet from the config:</p>
<div class="boxtext"><pre>
O CACertPath=/etc/ssl/certs
O CACertFile=/etc/ssl/deflt-ca.cer
</pre></div><p class="boxfoot">Here, <tt>CACertPath</tt> is the name of a
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
 needed (or can apt-get it), including jupp_3.1.10-1, mksh_36.2-1?buntu1
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
 so we will also be using FreeWRT Embedded GNU/Linux.</p>
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
 two who are going to Bruxelles with us. I’m in the process of
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
</p>
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
Title: k?buntu cheats (remember cheaterinterview.mp3? think Shuttleworth)
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
 wir – Fabian Köster und der Vortragende Robert
 Schuster, gecko2@ und ich – beim Beer Event, später auch mit
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
 die Mengen und Verhältnisse sind echt nicht planbar.
</p>
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
 that code on MirBSD™ can assume wrapping semantics and 8/16/32/64 bit
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

<p class="boxhead">How about this:</p>
<div class="boxtext"><pre>
	tg@herc:~ $ /bin/sh -c 'echo "0=($0) 1=($1) 2=($2) 3=($3)"' -- a "b c"
	0=(--) 1=(a) 2=(b c) 3=()
	tg@herc:~ $ nbsh -c 'echo "0=($0) 1=($1) 2=($2) 3=($3)"' -- a "b c"
	0=(--) 1=(a) 2=(b c) 3=()
</pre></div><p class="boxfoot">Heck, not just NetBSD® ash, and almost
 any shell Debian can dig out (bash pdksh ksh93 zsh dash posh) behaves
 the same as mksh.</p>
<p class="boxhead">MidnightBSD (DragonFly and FreeBSD too):</p>
<div class="boxtext"><pre>
	tg@mnbsd:~ $ /bin/sh -c 'echo "0=($0) 1=($1) 2=($2) 3=($3)"' -- a "b c"
	0=(a) 1=(b c) 2=() 3=()
</pre></div><p class="boxfoot">And the best thing of all: I am to "fix"
 this in mksh, as the old FreeBSD® ash is documented to have that weird
 behaviour. (Well, there's always <tt>-DMKSH_BINSHREDUCED</tt>...)</p>
<p>This is not a fault of MidnightBSD (except they could fix mports to
 behave more POSIXish; after all, I had to do that to MirBSD and MirPorts
 often enough), don't get me wrong. It just surprised me, and since I'm
 glad <a href="@@RELPATH@@permalinks/news_e20090329-tg-g10003.htm">they
 switched to mksh as <tt>/bin/sh</tt></a> I basically had to debug it.</p>
<p>I don't remember any more what NetBSD® 1.5 did that its <tt>/bin/sh</tt>
 could not be replaced by mksh, but they fixed it in 1.6 &ndash; K?buntu
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

<p class="boxhead">I don’t even know perl(1), I just can RTFM…</p>
<div class="boxtext"><pre>
<em>tg@bleu:~ $</em> echo 'xyzz�€y' | perl -C -pe \
    's/([\x{7f}-\x{ffff}])/"&amp;#".unpack("U",$1).";"/eg'
<em>xyzz&amp;#65533;&amp;#8364;y</em>
<em>tg@bleu:~ $</em> echo 'xyzz�€y' | perl -C -pe \
    's/([\x{7f}-\x{ffff}])/sprintf "&amp;#x%X;",unpack("U",$1)/eg'
<em>xyzz&amp;#xFFFD;&amp;#x20AC;y</em>
</pre></div><p class="boxfoot">Just hacked it for Natureshadow.</p>
----
Date: 22.04.2009 17:26
Author: tg@
Title: perl and quoted-printable
Tag: snippet

<p class="boxhead">While here anyway…</p>
<div class="boxtext"><pre>
<em>$</em> perl -pe 's/=(\n|[a-fA-F0-9]{2})/$1 eq "\n" ? "" : pack("C",hex($1))/eg'
</pre></div><p class="boxfoot">Needed it once for SyGroup.</p>
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
<p class="boxhead">To say it with Mika Prokop himself:</p>
<div class="boxtext"><pre>
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
</pre></div><p class="boxfoot" xml:lang="de">Ich glaube, Mika mag meinen
 Bootloader ;)</p>
<p>For simplicity, getextent_cd9660(1) will also be added to the grml-live
 ISO build process, as its output is easier to parse than J&#xFFFD;rg's
 isoinfo. (I definitively should add subdir support there, just haven't
 gotten around to do it yet...) It uses a UCB and a TNF header file and
 otherwise available under the <a href="@@RELPATH@@MirOS-Licence">MirOS
 Licence</a> (of course), as are the bootblocks.</p>
----
Date: 27.05.2009 15:32
Author: tg@
Title: GNU GRUB2 and BSD – state of affairs

<p>The “openbsd” option (<tt>bsd.mod</tt>) is unable to boot 4.4OpenBSD,
 MirOS #10, bsd4grml 2009.05rc1.</p>
<p>It appears that the kernel gets a page fault trying to access its own
 <tt>.bss</tt> – but I didn’t really look into it. Any takers?</p>
<p class="boxhead">This is bad, I wanted to add this…</p>
<div class="boxtext"><pre>
menuentry "bsd4grml from harddisk (ISO = grml_2009.05-rc1.iso)" {
        loopback        loop (hd0,1)/grml/grml_2009.05-rc1.iso
        openbsd         (loop)/boot/addons/bsd4grml/bsd.rd
}
</pre></div><p class="boxfoot">… to the solution using GRUB2 for <a
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
<p class="boxhead">This basically means you will be able to</p>
<div class="boxtext"><pre>
# dd if=grml-daily.iso of=/dev/sda [bs=…]
# dd if=/dev/cdrom of=/dev/sda [bs=…]
</pre></div><p class="boxfoot">to create a bootable USB stick (or a
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
 A ready
 made DLL for Win32 is available for direct download from us as is
 the <a href="@@ABSPATH@@/MirOS/dist/hosted/tg/xchat-randex_1.05.orig.tar.gz">source
 code</a>. It is, of course, <a href="@@RELPATH@@MirOS-Licence">MirOS
 licenced</a>.</p>
<p><a href="@@RELPATH@@cvs.cgi/ports/net/irssi/files/randex.pl">irssi
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

<p>About 30°C in the bureau don't make working easy.
 It was still too hot to work, and <tt>apt</tt>
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
 a single person, "the mksh team" (as seen on Debian derivate from Canonical that cannot be named forums, out of all
 places!), a.k.a. me, myself and I. Sometimes, actual users report bugs
 or even send in patches. I keep track of oksh's development as well, of
 course. But there are times I would like to get feedback on <a
 href="http://marc.info/?m=124689308408723">issues</a> from other people
 working on pdksh or its descendants. I mailed, for that specific issue
 in question, the Debian developer who created the original patch which
 addressed the scenario except for a corner case (interestingly, as the
 world is small, discovered in a Debian(!) init script from a package
 maintained by aforementioned formorer, on a DomU running Lenny
 - don't underestimate the effect
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
 KDE Wallet and
 would like public feedback, before releasing an 1.00 version, both on <a
 href="@@RELPATH@@cvs.cgi/contrib/hosted/tg/code/kwalletcli/">the source
 code</a> and <a href="https://eurynome.mirbsd.org/debs/dists/hardy/wtf/pkgs/kwalletcli/kwalletcli_0.94-1.dsc">an
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
  href="@@RELPATH@@MirOS-Licence">licence</a></li>
</ul>
<p>Any feedback welcome! Direct it to the miros-discuss mailing list.</p>
<p><strong>Update</strong> 09.07. – version 0.90 -> 0.91-1<br />I also crafted
 a <a href="http://trac.gajim.org/ticket/5153">patch for gajim to use
 kwalletcli</a>, let's see if it gets in. More to follow.</p>
<p><strong>Update</strong> 09.07. – version 0.91-1 -> 0.92-1<br />People who
 port this to KDE 4 (create a <tt>kwif4.cc</tt> file) welcome!</p>
<p><strong>Update</strong> 12.07. – version 0.92-1 -> 0.93-1</p>
<p><strong>Update</strong> 27.07. – version 0.93-1 -> 0.94-1</p>
----
Title: mksh change announcement: support future POSIX standard
Date: 09.07.2009 18:54
Author: tg@
Tag: mksh

<p>mksh(1)'s "set -u" handling will change RSN to match what POSIX will
 mandate in the next version, matching similar changes in GNU bash 4 and
 AT&amp;T ksh93.</p>
<p>Most of the thread can be seen on the miros-discuss@ mailing list
 archives (although both MARC and GMane seem to not have all related
 eMails... weird).</p>
----
Title: vacation
Date: 13.07.2009 18:32
Author: tg@
Language: de

<p>Ich bin jetzt bei gecko2@ für ’ne Woche, mal entspannen. ObRecovery:
 für zirka 2 € mehr habe ich durch IC-Nutzung eine Stunde Fahrt eingespart.
 Vive le Deutsche Bahn :þ</p>
<p>Pläne: viel offline sein. Ansonsten vielleicht ein wenig mksh(1)-Hacking
 (siehe letztes Posting) oder so.</p>
<p>Gestern mußte ich noch einen Fipptehler bei kwalletcli fixen ☹ dafür
 sollte™ heute auf Arbeit alles gut gelaufen sein.</p>
----
Title: Bremsen nerven!
Date: 14.07.2009 16:29
Author: tg@
Language: de
Tag: geocache

<p>Irgendwie… ist’s warm, ich bin müde, satt, und hab grad <em>keine</em>
 Lust, an mksh(1), BSD::arc4random, oder gar vnd(4) zu arbeiten ☺</p>
<p>Ist aber denk ich mal erlaubt. Dafür waren wir heute beim Einkaufen
 wieder geocachen (Statistiken siehe unten, <em>irgendwann</em> einmal
 „inventarisiere“ ich die aber mal richtig, Duplikate und so, denn das
 erste Hundert sollte ich vollhaben bald). Nervig ist, wenn man wegen
 Bremsen (der Viecher, die ich eigentlich so nur vom Bodansee kenne)
 die Suche abbricht, bevor sie richtig begonnen hat. Immerhin, einige
 haben wir gefunden, mit Lust auf mehr.</p>
<p>Fahrradmitnahme bei der DB ist auch so ’ne Sache, sicher, es ginge,
 irgendwie. Aber spontan wars mir dann doch zu aufwendig. Auch wenn ich
 es jetzt gerne hier hätte ☻</p>
<p>Ich hab <tt>nocd</tt> bei mir, und eine ganze Pixelreihe (horizontal)
 ist kaputt. Noch einer. Das nervt, nur <tt>nwt</tt> bleibt seinem Nutzer
 seit 1993 treu ☹</p>
<p>gecko2@ hat lustige Musik da, ganz gut, mal was Anderes. Wie die aber
 alle heißen muß er selber ins wlog schreiben :þ</p><!-- RSS stop -->
<p>Hier nun (nicht im RSS) die Statpix (:<br />
 <img src="https://call.mirbsd.org/sp.cgi?oc" alt="OpenCaching.de" />
 <img src="https://call.mirbsd.org/sp.cgi?gc" alt="The Frog Site" />
 <img src="https://call.mirbsd.org/sp.cgi?tc" alt="Rare Jewels" />
 <img src="https://call.mirbsd.org/sp.cgi?nc" alt="Broken Webpages²" />
 <br />Leider fast keine OCs hier in der Gegend.</p>
----
Title: iPhone Navigation
Date: 16.07.2009 15:09
Author: tg@
Language: de
Tag: geocache

<p>Leute, nehmt euer iPhone gerne dazu, auf dem Weg zum Schwimmbad Queen
 (Masters of the Universe) zu hören, aber bitteschön nicht zum Navigieren.
 Beim Versuch, das entfernte Ziel zu erreichen, sind wir an lustigen Stellen
 (Acker und so) gelandet; die mobile Suche war irgendwie von der Adresse
 <em>leicht</em> verwirrt. Die geocaching.com-Anwendung ist auch bescheiden,
 die kommt mir vor als wär ich aufm PocketPC und hätte vergessen, <em
 xml:lang="en">static navigation</em> auszuschalten.</p>
----
Title: mksh R39 coming soon to a /bin near you
Date: 16.07.2009 15:12
Author: tg@
Tag: mksh

<p><a href="@@RELPATH@@mksh.htm">mksh</a> has just been adjusted to behave
 as future POSIX will demand, after a lengthy discussion (on the bug-bash
 and miros-discuss mailing lists as well as the Debian bug tracker), for
 “set -u” (<tt>-o nounset</tt>). This, as well as the “stop () {…}” fix,
 <strong>must</strong> be tested extensively.</p>
<p class="boxhead">Therefore I urge all of you to</p>
<div class="boxtext"><pre>
 % CVS_RSH=ssh; export CVS_RSH
 % cvs -d :ext:_anoncvs@anoncvs.mirbsd.org:/cvs co -PA mksh
 % cd mksh
 % (sh Build.sh -r &amp;&amp; ./test.sh -v) 2&gt;&amp;1 | tee log
</pre></div><p class="boxfoot">and possibly send me the log. See <a
 href="@@RELPATH@@permalinks/wlog-10_e20081013-tg.htm">an earlier post</a>
 for more information about testing mksh(1) snapshots, as well.</p>
<p>Tests for better standards compliance and bugs, especially in corner
 cases, are also welcome. Known are: all but the first command of a pipeline
 are run in subprocesses (made to be an mksh feature, not a bug); the lexer
 is not recursive (issues with parenthesēs and comments in COMSUBs); some
 IFS/whitespace issues. Fixes for these bugs, and maybe for the regression
 tests (they may or may not be correct) are desirable… as well as <a
 href="@@RELPATH@@permalinks/wlog-10_e20090707-tg-g10031.htm">development
 related communication</a>.</p>
<p>On an unrelated side note, aptituz told me that Debian etch already had
 Debhelper v5, and as such, the mksh package has been converted over from
 Debhelper v4 (yay, RCS IDs in debhelper configuration files! but what about
 changelog (no-no) and menu? dunno…).</p>
----
Title: new netinstall snapshot for i386 online
Date: 17.07.2009 15:04
Author: tg@
Tag: news snapshot

<p>The <a href="@@ABSPATH@@/MirOS/current/i386/">NetInstall</a> directory
 contains a new intermediate snapshot of MirOS BSD/i386 built last night.
 I also brought the <a href="@@ABSPATH@@/MirOS/current/older/">fixes for
 older snapshots</a> a little more up to date. Enjoy!</p>
----
Title: jupp – the editor which sucks less
Date: 18.07.2009 19:02
Author: tg@
Tag: news

<p><a href="@@RELPATH@@jupp.htm">jupp</a> development has been split
 into <em>two</em> <strong>active</strong> development lines: jupp for
 DOS (based on joe 2.8) and jupp for Unix (based on joe 3.x).</p>
<p>There are binaries for both DOS (jupp for DOS) and Win32 (jupp for
 Unix, via Cygwin) available.</p>
<p>The jupp for DOS development line incorporates only minor patches
 relative to the original source code (it wasn’t <em>that</em> buggy
 as the sourceforge development made the code later…) and a jupprc
 file tuned for it but feature-complete with joe-3.1jupp10’s one.</p>
<p>The jupp for Unix development line incorporates all of the very
 extensive patches to the binary, and an enriched jupprc with, due to
 popular demand, <strong>syntax highlighting</strong> <em>enabled</em>
 by default – even though I still loathe it personally, and feel with
 Rob Pike when he questions the use of pretty printers. It will also
 try to correctly guess CR-LF vs LF-only line endings, indentation,
 and terminal colour. Furthermore, the language selection of the jupp
 flavour is now en par with that of the joe flavour, and the Python
 variants honour the standard coding style of theirs (needed that by
 the third quarter of last year, remember?). Autoindent is still off,
 by default, though – with reason.</p>
<p>Now give it a try. Hint: <tt>^J</tt> (Ctrl-J) invokes the help.</p>
----
Title: Deutſcher, kauf nicht bei Apple!
Date: 30.07.2009 19:56
Author: tg@
Tag: rant

<p>My <a href="https://eurynome.mirbsd.org/debs/debidx.htm">play <tt>*.deb</tt>
 repository</a> no longer carries binaries for <tt>iPhoneOS 2.2</tt>, or any
 other version for that matter. Apple prides themselves in DRM (Digital
 Restrictions Management) in a way that makes them look <a
 href="http://www.theregister.co.uk/2009/07/29/apple_jailbreaking_patent_office_response/">totally
 ridiculous</a> to anyone with only the tiniest amount of technical knowledge
 or political empathy. Gah. I don't see why I should support that with free
 software. Besides, it's not a good tool for geocaching, either.</p>
<p>Some years ago, this would not have surprised me, but these days it's rare
 to find a company doing similar stunts. While the iPhone may help them through
 the current economical crisis, I dare suggest they build more variants of the
 iMer instead :þ At least these have hack value.</p>
----
Title: KDE 4 – inakzeptabel
Date: 02.08.2009 19:12
Author: tg@
Language: de
Tag: rant

<p>Vor ein paar Tagen im IRC…</p><ul>
 <li><a href="http://techbase.kde.org/Projects/PIM/Akonadi#Do_I_need_a_running_MySQL_server.3F">KDE4PIM
  FAQ 5.9 Do I need a running MySQL server?</a> (Nein, wir bringen einen mit,
  vergessen aber, dessen Sicherheitslücken zu patchen.)</li>
 <li><a href="http://techbase.kde.org/Projects/PIM/Akonadi#Can_Akonadi_use_a_normal_MySQL_server_running_on_my_system.3F">KDE4PIM
  FAQ 5.10 Can Akonadi use a normal MySQL server running on my system?</a>
  (Wer zur Hölle benutzt MySQL, wenn er eine Datenbank (SQLite, MS-SQL,
  PostgreSQL) haben kann? Außerdem ist es recht diffizil, eine Datenbank
  oder ein Datengrab aufzusetzen, zu konfigurieren und abzusichern… auch
  wenn der obige Punkt sagt, sie bringen eine mit.)</li>
 <li><a href="http://techbase.kde.org/Projects/PIM/Akonadi#Which_DBMS_does_Akonadi_use.3F">KDE4PIM
  FAQ 5.6 Which DBMS does Akonadi use?</a> (Ein Wort: Ｗａｒｕｍ？)</li>
 <li><a href="http://techbase.kde.org/Projects/PIM/Akonadi#Why_not_use_sqlite.3F">KDE4PIM
  FAQ 5.7 Why not use sqlite?</a> (Auf Deutsch: wir sind zu blöd, Code
  zu schreiben, der funktioniert. Daß es mit MySQL tut ist nur Zufall,
  weil das genau so ein Haufen Scheiße ist, aber das haben wir noch
  nicht gemerkt.)</li>
 <li><a href="http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=513382">Debian
  #513382 – akonadi-server: depends on mysql-server</a> (Wir nutzen zwar den
  Datengrabserver der Distribution, aber ändern trotzdem nix an der Sache.
  Aber auch wir finden’s „toll“, daß ein MySQL-Server via /etc/init.d ｐｌｕｓ
  einer pro eingeloggter KDE4-Luser gestartet wird.)</li>
</ul>
<p class="boxhead">Zu Datenbank vs. Datengrab hatten wir ja:</p>
<div class="boxtext"><pre>
 “mysql is about as much database as ms access” – “MSSQL at least descends
 from a database” “it's a rebranded SyBase” “MySQL however was born from a
 flatfile and went downhill from there” – “at least jetDB doesn’t claim to
 be a database”	-- myself, Tonnerre and psychoschlumpf in #nosec
</pre></div><p class="boxfoot">Kleine Randbemerkung: mediawiki_*.deb
 dependet auch auf MySQL… obschon das FusionForge-Paket es für PostgreSQL
 konfiguriert und das so auch ganz gut tut. Echt ’ne Krankheit…</p>
----
Title: a whole lot of new releases
Date: 02.08.2009 19:13
Author: tg@
Tag: mksh news

<p>I took the weekend to release a couple of things… MirBSD™ base code
 stuff and base releases (printf.c for mksh in Debian; arc4random.c for
 Win32 and other non-BSD OSes, now with a HKCU key used in addition to
 the HKLM seed key which may not be writable; MirMake; MirPorts Package
 Tools; mirdate – rdate(8)), <a href="@@RELPATH@@jupp.htm">jupp</a>,
 <a href="@@RELPATH@@mksh.htm">mksh</a> including a new PDF manpage, <a
 href="@@RELPATH@@kwalletcli.htm">KWalletCLI</a>, and the RANDEX plugin
 for XChat (Win32, BSD and *nix). I also prepared for the inclusion of
 more Debian source packages in my CVS “home subtree” and creation of
 SRPMs for more software (not in CVS though). I cleaned up the mess that
 were the X11 dist sets in base, cleaned up compiler warnings on half a
 dozen or more platforms in several parts of the code, fixed bugs in a
 lot of subprojects, integrated things better, updated the BSD::arc4random
 MirPort as well as TinyIRC, MirSirc, the irssi and XChat RANDEX plugins
 to include better version reporting and, for XChat, seedfile support and
 better responsibility. Now all I need to do is build more binaries and
 ports (DEB RPM OpenBSD FreeWRT etc.) of the subprojects, update <a
 href="http://lynx.invisible-island.net/">Lynx</a> in base and ports (there is
 a new major release out, even), update MirGRML, fix the HDD in my sparc,
 compile stuff, … you see I’m busy.</p>
<p>Here’s a “checksum and link collection” for today’s finest:</p><ul>
 <li style="list-style:none;">Simple CVS file drops</li>
 <li>RMD160 (printf.c.1.10) = 8e8b88401a04474db973be07540a79b129919ff5</li>
 <li>TIGER (printf.c.1.10) = 3cec4bc24074e88c7889143d19f7659ced17482115ea5afb</li>
 <li>3098389975 10575 /MirOS/dist/hosted/other/printf.c.1.10</li>
 <li>MD5 (printf.c.1.10) = d09ae97aebac104f834d3d3ddd1702ca</li>
 <li>RMD160 (arc4random.c.1.16) = b0caa3509d2cade6d86cb2c13e6b8817ced2d9a9</li>
 <li>TIGER (arc4random.c.1.16) = ef6d7a281d451e28434b0e003990eebb47edd0cd4d899fd1</li>
 <li>2199066621 12558 <a href="@@ABSPATH@@/MirOS/dist/hosted/other/arc4random.c.1.16">/MirOS/dist/hosted/other/arc4random.c.1.16</a></li>
 <li>MD5 (arc4random.c.1.16) = e8376a9b51c0ce08f5ed20722b05cad3</li>
 <li style="list-style:none;">Simple subproject checkouts</li>
 <li>RMD160 (mirmake-20090801.cpio.gz) = 79e0d15aab4c7a05690e66769c12dbeb3d99daa1</li>
 <li>TIGER (mirmake-20090801.cpio.gz) = 2c6642b9515f38e736386945e72c06f402134ebf898613de</li>
 <li>788720631 372063 <a href="@@ABSPATH@@/MirOS/dist/mir/make/mirmake-20090801.cpio.gz">/MirOS/dist/mir/make/mirmake-20090801.cpio.gz</a></li>
 <li>MD5 (mirmake-20090801.cpio.gz) = 47c63503210054d86db80040474f1f71</li>
 <li>RMD160 (pkgtools-20090801.mcz) = 482dcf4b915a10bb6b76859f0c1755b67d6343bb</li>
 <li>TIGER (pkgtools-20090801.mcz) = 3a622ac3c895c4af9df719dd30cfd3fe45e6d719cc34db5e</li>
 <li>2864495035 180188 <a href="@@ABSPATH@@/MirOS/dist/mir/pkgtools/pkgtools-20090801.mcz">/MirOS/dist/mir/pkgtools/pkgtools-20090801.mcz</a></li>
 <li>MD5 (pkgtools-20090801.mcz) = 87378c95bde1c219d4a09e6bb8ccb897</li>
 <li>RMD160 (rdate-20090802.tar.gz) = abac9ae8a08ac566d6c0396d39cd5d2cd724f7b0</li>
 <li>TIGER (rdate-20090802.tar.gz) = f38a164e9d77412203349f79e8033c413335dd6f43a5cbf5</li>
 <li>3840714105 11987 <a href="@@ABSPATH@@/MirOS/dist/mir/rdate/rdate-20090802.tar.gz">/MirOS/dist/mir/rdate/rdate-20090802.tar.gz</a></li>
 <li>MD5 (rdate-20090802.tar.gz) = a8fa4550b5a77cff6db1ed0a9d8aa357</li>
 <li style="list-style:none;">JUPP (including Win32 binary)</li>
 <li><a href="@@ABSPATH@@/MirOS/dist/jupp/joe.pdf">PDF manpage</a></li>
 <li><a href="@@ABSPATH@@/MirOS/dist/jupp/joe.htm">HTML manpage</a></li>
 <li>RMD160 (joe-3.1jupp11.cpio.gz) = 7ade55cb8511600b3a9d77f37bc581b2d09ab2aa</li>
 <li>TIGER (joe-3.1jupp11.cpio.gz) = b7bb4aa464b705e697ab2a52ad75fc8755a5817bfb83e09a</li>
 <li>805235529 419484 <a href="@@ABSPATH@@/MirOS/dist/jupp/joe-3.1jupp11.cpio.gz">/MirOS/dist/jupp/joe-3.1jupp11.cpio.gz</a></li>
 <li>MD5 (joe-3.1jupp11.cpio.gz) = 1e2f21a6fdebe678b125e96806267f33</li>
 <li>RMD160 (JWIN31B.EXE) = f9eb9f6b3bd2a1bb5874e36d2dcc6dbdaabf75cc</li>
 <li>TIGER (JWIN31B.EXE) = 771461b752114978ed64f67c01e3ef22a9a9cdf76fda6b11</li>
 <li>674256238 948176 <a href="@@ABSPATH@@/MirOS/dist/jupp/JWIN31B.EXE">/MirOS/dist/jupp/JWIN31B.EXE</a></li>
 <li>MD5 (JWIN31B.EXE) = b2d3f1044221fdea76f15621e94e1ae4</li>
 <li style="list-style:none;">mksh (including Cygwin package)</li>
 <li><a href="@@ABSPATH@@/MirOS/dist/mir/mksh/mksh.pdf">PDF manpage</a></li>
 <li>RMD160 (mksh-R39.cpio.gz) = 5a5bcbe288e722f9772e27d2fdc36eee174bbb7b</li>
 <li>TIGER (mksh-R39.cpio.gz) = 2a2c08ccf5e27365aa652663629789ade93b3d30c0d1d51f</li>
 <li>4103085544 278476 <a href="@@ABSPATH@@/MirOS/dist/mir/mksh/mksh-R39.cpio.gz">/MirOS/dist/mir/mksh/mksh-R39.cpio.gz</a></li>
 <li>MD5 (mksh-R39.cpio.gz) = b2eeb4fe4ccac2704e1440e53cd2672c</li>
 <li>RMD160 (mksh-39.1-cygwin.tgz) = 0cecd4ffb72f2d51a5c935da58e67350fab10e81</li>
 <li>TIGER (mksh-39.1-cygwin.tgz) = 3157abadc40696bcb8df1d3574df571b728bef3d4d2ac2f2</li>
 <li>2818578374 144625 <a href="https://eurynome.mirbsd.org/~tg/pub/mksh-39.1-cygwin.tgz">mksh R39 for Cygwin</a></li>
 <li>MD5 (mksh-39.1-cygwin.tgz) = ca949841e39721be666e6a82803e7769</li>
 <li style="list-style:none;">KWalletCLI</li>
 <li>RMD160 (kwalletcli-1.00.tar.gz) = f04ebd39e9714212a915b6d7d4524c8cc2daaee7</li>
 <li>TIGER (kwalletcli-1.00.tar.gz) = 0fc673c0c813608f0f0d863dfd924a6d62a8507c7bdf361b</li>
 <li>2355082724 11524 <a href="@@ABSPATH@@/MirOS/dist/hosted/kwalletcli/kwalletcli-1.00.tar.gz">/MirOS/dist/hosted/kwalletcli/kwalletcli-1.00.tar.gz</a></li>
 <li>MD5 (kwalletcli-1.00.tar.gz) = 76ef3c1d611a11ea13dc805d67d82208</li>
 <li style="list-style:none;">RANDEX plugin for XChar (including Win32 binary)</li>
 <li>RMD160 (xchat-randex-1.10.tar.gz) = fd61babbf4e5189f69dae8eb664ee2780433bf4b</li>
 <li>TIGER (xchat-randex-1.10.tar.gz) = 6bd888b157fcd931e54b71e9778950cbfa675ae6b784ddd5</li>
 <li>2651117045 8702 <a href="@@ABSPATH@@/MirOS/dist/hosted/xchat-randex/xchat-randex-1.10.tar.gz">/MirOS/dist/hosted/xchat-randex/xchat-randex-1.10.tar.gz</a></li>
 <li>MD5 (xchat-randex-1.10.tar.gz) = d1585c5fae3ee531deeffc8314910553</li>
 <li>RMD160 (randex.dll.gz.1.10) = a4aaa67cfdad1f9a1bcdc3eea797aff3a30703c4</li>
 <li>TIGER (randex.dll.gz.1.10) = 55b2dcd7d790d28944d7424121cf5c6d4d386a99751fb556</li>
 <li>972086546 23998 /MirOS/dist/hosted/xchat-randex/randex.dll.gz.1.10</li>
 <li>MD5 (randex.dll.gz.1.10) = 793ce548256efc6a23f7a37dde9215a2</li>
</ul>
<p>An observation… mksh “print $RANDOM” on Cygwin is very slow, and the
 HKCU seed changes each time. This should be debugged, it shan’t unless
 <tt>RANDOM</tt> is being written to or 400k calls are done.</p>
----
Title: updates regarding the upcoming new snapshots
Date: 10.08.2009 15:48
Author: tg@
Tag: bug

<p>While the <a href="@@RELPATH@@permalinks/news_e20090809-tg.htm">ext2fs
 fix</a> is good, we have a new lynx(1) version, and boot(8/i386) has
 vastly improved, trying to fix boot_sparc(8) didn't help much, I either
 get esp(4/sparc) problems or panic(9)s in uvm_fork(9). *sigh*</p>
<p>This means that the FrOSCon edition will contain a brand-new i386
 snapshot and a merely polished sparc snapshot largely based upon the
 as-of-now current 20090425 snapshot with hand-tweaking applied.</p>
<p>Thusly no new sparc binary packages for -current will be built.</p>
<p>Even if I did get the hardware issues solved (or move from <tt>demo</tt>
 to <tt>ss20</tt>, I <em>now</em> couldn't get things done in time.</p>
----
Title: finally, a new snapshot
Date: 11.08.2009 21:17
Author: tg@
Tag: bug snapshot

<p>Woohoo, MirOS #10-current (20090811) i386;sparc is out, and with
 only a glurpzillion problems that arose during its compilation…</p>
----
Title: Manche Sachen übersetzt man einfach nicht!
Date: 12.08.2009 14:33
Author: tg@
Language: de

<p>NLS, I18N (Internationalisierung), L&lt;Zahl&gt;N (Lokalisierung)
 und so mögen ja alle schön und gut sein… (gcc verwendet immerhin bei
 LC_MESSAGES=en_GB.UTF-8 „<span xml:lang="en">the Queen’s English</span>“
 (so halbwegs) und statt U+0060 (‘`’, muß sterben) typographisch korrekte
 Anführungszeichen (‘’). Aber… man kann sich bei „<span xml:lang="en">tab
 completion</span>“ <em>leicht</em> auf „Tab-Vervollständigung“ einigen,
 alles muß man jedoch nicht übersetzen. Auf der Webseite (nicht im RSS)
 gibt’s ein Bild dazu.</p><!-- RSS stop -->
<p><img src="https://serverop.de/~tek/images/nlssucks.jpg"
 alt="NLS sucks" /><br />(danke an &lt;teK_:#grml&gt;, der sich zu
 erinnern meint, daß das SuSE verbrochen habe)</p>
----
Title: finally, a new snapshot – Episode 2: the b0rken
Date: 12.08.2009 14:34
Author: tg@
Tag: bug snapshot

<p>Yeah, a new snapshot. I wanted to update MirOS bsd4grml in the <a
 href="http://git.grml.org/?p=grml-live.git;a=summary">grml-live</a>
 repository too. Like a good developer, I read my “git diff” before
 “git commit -a”ing. What do I see, the ‘-’ in the manpage is missing.
 Search. Search more. Curse. I mean, fuck. The whole 20090811 “David”
 snapshot has broken manpages because of a faulty merge-from-OpenBSD,
 who decided, in their infinite wisdom, to use “\(en”, a GNU groff
 extension. While Kristaps Džonsons (ha, jmc, <strong>I</strong> can
 spell that right!) is correct in that an en dash should be used at
 that position (separating name from short description), nroff(1) only
 has “\(em” in that place. Luckily, we already define “\*(en” in our
 compatibility stuff (and mircvs://contrib/samples/portmdoc), so we
 can use that instead.</p>
<p>The only annoying thing is that I have to rebuild the i386 part
 of the snapshot again. Anyway, as soon as it’s up (probably tomorrow
 afternoon, as it has to be uploaded from here first), have fun.
 I’ll change the <a href="@@RELPATH@@irc.htm">channel</a> topic.</p>
----
Title: more about the FrOSCon ISO
Date: 13.08.2009 15:00
Author: tg@

<p>I’m ill. I’ve not kissed a porc though, so I think it’s some kind
 of the common cold. Today, the headaches are killing me; I guess that
 when I finished the snapshot for the first time on 2009/08/11 night,
 my body decided it could relax now and let things out. Damn. Anyway,
 I’ll be finishing the FrOSCon DuaLive™/Triforce ISO this weekend, and
 there will be <em>no</em> binary packages on it thusly. Better that
 than untested or uninstallable ones. Users will, however, be able to
 get a variety of them from our download area (large variety for i386
 built by bsiegert@ and small variety I’ll be baking for sparc). There
 also won’t be a new MirGRML (but the grml-FrOSCon edition ISO will
 contain a new MirOS bsd4grml, since that was made at approximately
 zero cost, since it “fell out” of the snapshot building anyway – and
 had me discover the manpage bug) this time, due to lack of that.</p>
<p>I’m hoping the headaches and other symptoms will leave me ASAP, so
 that I can go back to work tomorrow – as today is the second day, I’d
 need to see a doctor otherwise, which sucks even more (as it involves
 quite some money and a 1½hr-per-direction bus+tram+train ride), and
 it’s not <em>that</em> bad. I just cannot concentrate. – Retrospectively,
 I think I’ve been ill last week already, considering how badly I could
 concentrate back then (might also had to do with the huge number of
 small things we has to take care of) and the bodily condition… (The
 weather also has been killing me, fluctuating between 12°C and 24°C
 at night, 18°C and 30°C at day, cold/dry, cold/raining, hot/dry and
 hot/humid (extremely), with a few warm/humid/raining in between.)</p>
<p>Ah, if someone didn’t get it: the netinstall area now contains the
 i386=20090812 sparc=20090811* (tweaked) snapshot, which is what will
 be on CD, on <tt>/MirOS/current/</tt> and everyone is invited to test
 that – especially on sparc, the floppies (all five of them), and maybe
 the separate five arch-specific ISOs too not just the larger combined
 one. And there will be buttons again. (Sorry if I made nōn sequitur –
 I <em>do</em> have a rather heavy headache right now, but just could
 not go back to sleep two hours ago.)</p>
<p>PS: <a href="http://www.froscon.org/">go here</a></p>
----
Title: It sucks! I want no more!
Date: 15.08.2009 21:07
Author: tg@
Tag: bug event hardware rant snapshot

<p>You all know that the sparc (demo) freezed on me. Well, the VT420
 only emitted “Keyboard Error 4”, I tried the other sparc (ss20/marc).
 Also equipped with one of these 36G LVD/SE U160 SCA HDDs, it exploded.
 Literally. Something – I still don’t know what (smells in the area of
 the tvtwo(4/sparc) and le(4/sparc) but…) as this happened during the
 installation, which continued as if nothing had happened, except that,
 a minute after the explosive sound, it begun to smell. *sigh*</p>
<p>Me then go back to <tt>demo</tt>, even put in the tvtwo(4/sparc) for
 monitor/keyboard console (sucky German keyboard, but after installing
 kbd(8) works), use the <tt>Stop-N</tt> trick (hold it down and power
 on) to erase the PROM (thanks NetBSD® FAQ, no thanks to the people in
 #sparc in IRC who suggested <tt>Stop-A</tt>) to switch from serial to
 k/m console, then it installed… and froze.</p>
<p>To add insult to injury (luckily not mine), the VT420 works again.</p>
<p>I tried hard to get you at least a minimal set of binary packages –
 gmake (so it’s self-hosted), lzma (for *.clz binary package support),
 screen (because people need it), jupp (vi(1) is in base, but no editor
 other than ed(1)…), rsync (even though it’s now GPLv3, we depend on it
 heavily) – but just <strong>could not</strong>, no matter how hard.</p>
<p>On the other front, after re-doing the installer a few times due to
 some fuckup in <tt>install.sub</tt> (don’t ask, but I really extracted
 the image from the symbol-less kernel and put it back afterwards…), a
 number of core packages for i386 were built, and bsiegert@ is supplying
 another few hundred. Yay!</p>
<p>I’ll still follow the plan to create the FrOSCon ISO tomorrow, will
 add a minimal set of i386 packages plus their distfiles where licences
 require it, and refer people to the online repository. I cannot add any
 “real” sparc packages, so there will be none. I’m tempted to modify the
 sparc installer by image extraction too, since the mount_mfs(8) fails
 when the box has too much RAM (more than about 300 MiB), but don’t want
 to power on one of these boxen and lose even more time (if not body or
 possession).</p>
<p>qemu is getting better at emulating a sparc, but we still cannot go
 to user space. ☹</p>
<hr style="width:66%" />
<p>If someone is really interested in getting MirOS working on boxen
 compatible to the SheevaPlug (ARM 1.2 GHz), despite our rather old gcc
 and binutils, <em>please</em> contact us. I’d drop sparc support over
 it once working.</p>
<hr style="width:66%" />
<p>See you all kissing the <a href="http://www.froscon.org/">blue
 frog</a>, but remember, don’t kiss a porc. You can read the <a
 href="@@ABSPATH@@/MirOS/PR/advertisement.pdf">advertisement</a> or
 the flyers (<a href="@@ABSPATH@@/MirOS/PR/flyer_de.pdf">German</a>,
 <a href="@@ABSPATH@@/MirOS/PR/flyer_en.pdf">English</a> or <a
 href="@@ABSPATH@@/MirOS/PR/flyer_fr.pdf">French</a>) meanwhile.</p>
----
Title: I complain, rant and give up, then it works…
Date: 16.08.2009 15:48
Author: tg@
Tag: hardware

<p class="boxhead">The subject line says it all…</p>
<div class="boxtext"><pre>
tg@ss5:~ $ uname -a
MirBSD ss5.mirbsd.org 10 Kv#10uAA-20090810 GENERIC#146 sparc
tg@ss5:~ $ dmesg
MirBSD#10uAA (GENERIC) #146: Mon Aug 10 17:57:16 UTC 2009
        tg@demo.mirbsd.org:/usr/src/distrib/generic/obj/build/GENERIC
real mem = 33165312
avail mem = 24928256
[…]
sd0 at scsibus0 targ 3 lun 0: &lt;IBM, DORS32160SUN2.1G, WA7A&gt; SCSI2 0/direct fixed
sd0: 2063MB, 6703 cyl, 5 head, 126 sec, 512 bytes/sec, 4226725 sec total
[…]
cgsix0 at sbus0 slot 3 offset 0x0: SUNW,501-2325, 1152x900, rev 11
wsdisplay0 at cgsix0: console (std, vt100 emulation), using wskbd0
[…]
tg@ss5:~ $ sysctl hw machdep
hw.machine=sparc
hw.model=SUNW,SPARCstation-5, MB86907 @ 170 MHz, on-chip FPU
[…]
machdep.cputype=2
machdep.v8mul=1
[…]
tg@ss5:~ $ top
[…]
Memory: Real: 17M/26M act/tot  Free: 1444K  Swap: 2640K/133M used/tot
[…]
</pre></div><p class="boxfoot">It may only be a SPARCstation 5,
 with a rather fast CPU though (the SS20en only have 125 MHz and 150 MHz
 ROSS CPUs), with a small, slow and lout hard disc and <em>very</em> few
 RAM, but hey, it installs, the cgsix(4/sparc) scrolls quickly (as the
 tvtwo(4/sparc) currently is unaccelerated), and builds packages like a
 charm. Yay! I even have mc (Midnight Commander) now…</p>
----
Title: First three issues of BSDmagazine – for free!
Date: 19.08.2009 16:30
Author: tg@
Tag: news

<p>Karolina Lesińska writes: “We have placed the first 3 issue of
 BSDmagazine on our website as free downloads. The issues are:</p><ol>
 <li>FreeBSD Ins &amp; Outs</li>
 <li>OpenBSD in the Limelight</li>
 <li>Explore NetBSD</li>
</ol><p>“The link is: <a href="http://bsdmag.org/prt/view/pdf-articles.html">http://bsdmag.org/prt/view/pdf-articles.html</a>”</p>
<p>My comment: The <a href="http://www.bsdmag.org/">BSD magazine</a> is a
 rather interesting piece of print, which already carried a small article
 about MirBSD. We have, I admit, been offered to write more which would get
 published, but, I am ashamed, haven’t quite gotten around to doing so.</p>
<!-- RSS stop --><p>Today, it's only been 29°C, and I died. What will I do
 tomorrow, where it is supposed to climb up to 35°C over today's 32°C?</p>
----
Title: Hot!
Date: 20.08.2009 15:18
Author: tg@
Tag: rant snapshot

<p>It’s <strong>hot</strong>! The weather forecast said 35°C, one of the
 apothecaries’ thermometres says 40°C, and my body says I’m ill. I also
 nurse quite some headaches again. So I won’t do/write much. It was hard
 enough to go outside to buy breakfast.</p>
<p>On the other hand, the SS5 built a mock-snapshot (QUICK_DIST2, so only
 base+gcc, no X11/ports/htman/…) just fine (with some fixes). Does anybody
 have any RAM suitable for a SPARCstation 5 for me? I cannot use that from
 the SS20s because they use different kinds of RAM. I won’t publish this,
 but instead use it to build another one for real, possibly combined with
 another i386 snapshot, with all the /etc/* changes after 20090812, and
 maybe fixing what we will have learned to be broken in the meantime. And
 Benny’s ports fixes (he got GNOME except nautilus – which has unsafe code
 in signal handlers – working, part of (or all?) Xfce too, etc).</p>
<p>Luckily, tomorrow is more like 22°C</p>
----
Title: MirOS bsd4me – Sane OS on netboot.me ☺
Date: 30.08.2009 22:30
Author: tg@
Tag: news snapshot

<p>Christian Hofstaedtler «ch:#grml» pointed me to an <a
 href="http://www.heise.de/newsticker/meldung/144502">article</a>
 about <a href="http://www.netboot.me/">netboot.me</a>, a service
 providing bootable Live and Install variants of some OSes over
 the Internet (via gPXE and HTTP transport, mostly). They offer
 a bootable floppy/disc, USB stick, and El Torito ISO image. One
 gets a graphical menu if not careful, out of which there is no
 escape, and which isn’t compatible with most graphics cards, but
 if ^B is pressed quickly enough, there will be a usable <a
 href="http://www.netboot.me/help#chainload">command line</a>.</p>
<p class="boxhead">An experimental MirOS bsd4me bootable
 image is available as well:</p>
<div class="boxtext"><pre>
gPXE&gt; <span class="u">autoboot</span>
gPXE&gt; <span class="u">chain http://netboot.me/2032</span>
</pre></div><p class="boxfoot">This will be loaded via plain,
 unencrypted HTTP from our main webserver. It’s the usual &lt;5 MiB
 Mini-ISO for the i386 architecture and contains a full installer,
 as well as e3 and tinyirc known from MirOS bsd4grml. Source code of
 the GPL’d parts and overall licencing information is also included
 inside the ISO image. <em>Please remember this is for beta testing
 only.</em> We do not support MEMDISK boot methods with our second
 stage boot(8/i386) loader, as these are not reliable.</p>
<p>On an unrelated side note: dutch Windows XP Professional is weird.
 Translations were laughed at by several dutch-speaking people in the
 mksh IRC channel, but I was able to disable Blåtand on “blau” (the
 new IBM X40, successor of “bleu”). And it works!</p>
<p>A more related side note: when virtualising MirBSD, do <em>not</em>
 use VirtualBox. If you <em>do</em> have Vanderpool/Pacifica available
 and enabled, both the OSE and the full edition may be viable, but kvm
 is the better option. If VT-x/HVM is not used, it does not emulate the
 i386 architecture properly. Use qemu, kqemu, kvm, bochs, VMware Server
 2 (not 1 – timekeeping is broken in there), Microsoft® VirtualPC 2004,
 Parallels Desktop, VMware Fusion for Macintosh, … instead.</p>
<p>Tonight and the last few days have seen several releases of things
 like MirMake, the package tools, etc. You might want to upgrade your
 MirPorts Framework checkout. (We now have enough Lua tools to access
 the <a href="http://marc.info/?m=125058382706316">Simtec eKey</a>, I
 just need to order one. We’re currently at 2¾ interested people, not
 quite enough to make sense.)</p>
----
Title: mksh feature weeks
Date: 07.09.2009 17:27
Author: tg@
Tag: mksh

<p>It's feature weeks for mksh(1). You almost certainly want to follow the <a
 href="@@RELPATH@@mksh.htm#clog">mksh-current changelog</a>. Please test all
 the new features, as well as make sure that nothing breaks nor I introduced
 other regressions, such as making resource usage worse (disc, CPU, memory).
 Please be reminded that many more deep-reaching changes will follow in the
 next few hacking days.</p>
<p>Thanks to David Korn (the Korn in AT&amp;T Korn Shell, ksh88/ksh93) for
 discussing features and helping with finding syntax and semantic of some
 of the more complicated language pecularities.</p><!-- RSS stop -->
<p>On an unrelated note, cvs(1), lynx(1), ncurses(3), some other things,
 and a lot of ports have also been worked on. The next snapshot is planned
 for mid to end of September, bi-arch. Stay tuned!</p>
----
Title: It's this time of the year again
Date: 09.09.2009 19:41
Author: tg@
Tag: bug debian event geocache rant

<p>Due to heavy load at work, as well as some minor things, I'm either
 taking back interest altogether, involvement altogether, time spent on
 projects, or any of these on aspects/particulars of projects.</p>
<p>Sometimes, when you're burnt out, it's best to concentrate on living
 and on core projects. <a href="@@RELPATH@@mksh.htm">mksh</a> is one of
 these for me, as is keeping MirBSD userland and MirPorts infrastructure
 working well, with small, evolving improvements (no big jumps). Other
 things, no matter how nice, interesting or useful (to me as well as to
 others) they are, need to stay back. I poured most of the last seven
 years of my life into MirBSD.</p>
<p>Sometimes, you want to give back, but it's too much effort, or you
 cannot afford to spend more time on it. I'll close one of my Debian
 ITP bugs for this reason. (I also rarely send in patches from ports
 for this reason, but sometimes point upstream to our CVSweb.)</p>
<p>Sometimes, people like Ulrich Drepper, Marco d'Itri, Gerrit Pape
 let you realise that every project has its Theo de Raadt-alikes.
 I've still not ported <a href="@@RELPATH@@jupp.htm">jupp</a>'s latest
 release to Debian (but an OpenSuSE Buildservice SRPM exists), nor
 uploaded the current mksh(1) version even to my own <tt>wtf</tt> repo.
 I will do so, when I feel like spending private time with Debian again,
 at least for the etch and lenny (and hardy &ndash; for work) branches,
 as dash and mksh in sid have... issues I predicted ages ago. (For one,
 I'm still waiting for Gerrit to contact me. Maybe our eMail systems
 don't like each other? Waldi or formorer will probably pass on any
 messages, as will the trusty BTS.) I'll probably not open any ITP
 bugs again and send in much less of the bugs I notice, simply because
 I don't like being ignored (or flamed, but sometimes, being ignored
 is worse &ndash; which is why Benny works on MirPorts, btw). Maybe,
 if I feel the need to, my <tt>wtf</tt> repo will grow instead; DDs
 or DMs are free to take from there if they like.</p>
<p>Sometimes, one realises that he just doesn't fit in. While <a
 href="http://www.cachewolf.de/">Cachewolf</a> is a useful project,
 working together with Java&trade; developers that communicate over
 web fora <em>only</em> and don't even see the need for compatibility
 with Unix or proper processes most of the time (<tt>svn:eol-style</tt>
 comes to mind, and switching the source code to UTF-8 is something
 I've given up to dream of &ndash; I would even have fixed bugs where
 Ewe wouldn't do UTF-8 right, but I run into a wall of bliss ignorance
 there) proved impossible for me. I won't budge either: web fora are
 simply not for me to use. Period. This is my fault (for not fitting
 in) as well as the fault of some of the rest of the team (for ignoring
 years of experience, or for simply <span xml:lang="de-DE-1901">nicht
 über den eigenen Tellerrand schauen</span> (however one says this in
 English, I don't know) and not caring of these who do; for supporting
 the commercial gc.com site over the three alternatives too). I will
 continue to use it, maybe the iPAQ H3600 a colleague gave me proves
 useful, otherwise, MirBSD will do just fine.</p>
<p>So, when I leave or pull back a little, no prejudices. Sometimes
 with reason, but mostly due to lack of available resources on my
 part. I hope nobody who has been or will be noticing me ceasing to
 contribute as much as usual thinks ill that's why.</p>
----
Title: 8 Useful and Interesting Bash^Wmksh Prompts
Date: 10.09.2009 18:54
Author: tg@
Tag: mksh snippet

<p>smultron, <a href="http://www.midnightbsd.org/">MidnightBSD</a>
 developer and project member, and graphician / art master for the <a
 href="@@RELPATH@@mksh.htm">MidnightBSD Korn Shell</a> (among other
 things), has pointed me to a blog article: <a
 href="http://maketecheasier.com/8-useful-and-interesting-bash-prompts/2009/09/04">8
 Useful and Interesting Bash Prompts</a> and asked for an mksh(1)
 translation. These will <em>not</em> be minimalistic (I can do quite
 some things), but focus on containing no control characters or other
 things not easily cut-and-past'able. Made more readable, too.</p>
<p class="boxhead">Small note: <em>all</em> mksh examples assume
 the following "setup code" in front of the PS1=... line. Yes, PS1 is set
 twice (makes the code more readable and perform better). Most of this is
 from the mksh(1) manpage or <tt>dot.mkshrc</tt> and relatively portable,
 which is why some things seem more complicated than needed. They do,
 however, use some rather recent mksh features; if there's real interest
 in making it work with, say, Debian etch mksh R28, eMail me. Note: that
 → character is a literal Tab (the "[→·]" Tab-Space occurs often).</p>
<div class="boxtext"><pre>
	ca=$(print -n '\001'); ce=$(print -n '\033'); cm=$(print -n '\r')
	: ${HOSTNAME:=$(ulimit -c 0; hostname -s 2&gt;&amp;-)}
	[[ $HOSTNAME = @(localhost|*([→·])) ]] &amp;&amp; \
	    HOSTNAME=$(ulimit -c 0; hostname 2&gt;&amp;-)
	: ${USER:=$(ulimit -c 0; id -un 2&gt;&amp;- || print \?)}
	if (( USER_ID )); then PS1='$'; else PS1='#'; fi

	function twd {
		typeset d=${PWD:-?} p=~

		[[ $p = ?(*/) ]] || d=${d/#$p/~}
		print -nr -- "$d"
	}
</pre></div><p class="boxfoot">If you do not need exactly the effect
 of "\w" (tilde unexpansion), use <tt>$PWD</tt> ipv <tt>$(twd)</tt> below.
 Note that $USER and $HOSTNAME are usually evaluated only once; escape them
 if you need it evaluated every time.</p>
<ol>
 <li>Show Happy face upon successful execution
<div class="boxtext"><pre>
	bash$ PS1="\`if [ \$? = 0 ]; then
		echo \[\e[33m\]^_^\[\e[0m\]
	else
		echo \[\e[31m\]O_O\[\e[0m\]
	fi\`[\u@\h:\w]\$ "

	mksh$ PS1="$ca$cm"'$(if (( $? )); then
		print "'"$ca$ce[31m$caO_O$ca$ce[0m$ca"'"
	else
		print "'"$ca$ce[33m$ca^_^$ca$ce[0m$ca"'"
	fi)'"[$USER@$HOSTNAME:\$(twd)]$PS1 "
</pre></div>
 <br />I do think Unicode makes things more fun though:
<div class="boxtext"><pre>
	mksh$ PS1="$ca$cm$ca$ce["'$(if (( $? )); then
		print "'"31m$ca☹"'"
	else
		print "'"33m$ca☺"'"
	fi)'"$ca$ce[0m$ca[$USER@$HOSTNAME:\$(twd)]$PS1 "
</pre></div>
 </li>
 <li>Change color on bad command
  <br />Coming soon... colour changes are okay, but I wonder why anyone
  would want the history number. I've got to discuss this a little, and
  think about ways to use such information with mksh, and if I really
  want to transcribe the prompts 1:1 (it's possible by just incrementing
  a counter, but, hey, you don't want that). This is actually a csh
  feature, and who'd really use csh? I'm on my 80486DLC notebook right
  now, so my debugging methods are a little limited, but I promise a
  larger article later. I just needed to get started.</li>
</ol>
<p>This article will be updated in-place.</p>
----
Title: Getting closer: new snapshots soon
Date: 13.09.2009 16:57
Author: tg@
Tag: snapshot

<p>I'm closer to getting a new bi-arch snapshot ISO done: i386 is in a
 pretty shape, and the sparc looks good, will be compiling this night,
 and a few subsequent ones... so both architectures are on the same
 level. I'll need to do clean installation builds for the snapshots of
 course. There will probably be a ISO like the Easter 2009 snapshot on
 BitTorrent again (no TPB, mind you), including the (admittedly slightly
 dusty) MirGRML.</p>
<p>Since we have over 1 GiB worth of binary packages, mostly compiled by
 bsiegert@, some of which depend on libgcc_s.so.1.1, while the snapshots
 will have libgcc_s.so.2.0, <tt>fixes10.ngz</tt> will contain a binary
 plug of the older one (built just before the ABI change) for convenience
 in using the binary packages. Be advised to install it.</p>
<p>mksh(1) is currently being actively developed; the snapshot may come
 before mksh R40 will be released, but contain a <em>lot</em> of changes
 from R39 (see <a href="@@RELPATH@@mksh.htm#clog">the changelog</a>).</p>
<!-- RSS stop --><p>I feel like I'm going ill again, bed day for me. This
 sucks. And I even don't know why.</p>
----
Title: Improved CSS and Font Embedding
Date: 25.09.2009 19:10
Author: tg@

<p>I tried to improve the Font Embedding as well as the CSS on this
 website again. The fonts actually used should be Gentium Regular,
 Gentium Italic, Gentium Basic Bold, Gentium Basic Bold Italic. If
 you have only the Book variants installed, they are fallback. Both
 CSS3 and IE/EOT embedding styles should work. (Bolding seems to be
 broken in my Opera-Linux 9.27 though…)</p>
<ul>
 <li><b>b bold</b></li>
 <li><strong>strong bold</strong></li>
 <li><i>i italic</i></li>
 <li><em>em italic</em></li>
 <li><b><i>bold italic</i></b></li>
</ul>
<p>Please do report any bugs (possibly with patches) again ☺ Things
 still look great in Lynx, so I̲ am content in any case…</p>
----
Title: mkshdroid, brother of the iShell [updated]
Date: 02.10.2009 17:38
Author: tg@
Tag: mksh

<p>As <a href="http://thread.gmane.org/gmane.os.miros.general/8946">sent to
 the mailing list</a> I had a chance to compile mksh for Android today,
 thanks to Waldemar confirming that it works (with OpenADK's eglibc linked
 in statically) and CeKay's help in mastering the SDK and NDK. The posting
 contains all relevant information; it is virtually impossible to write an
 <tt>Android.mk</tt> file though.</p>
<p>On the other hand, I <em>did</em> submit a patch for Bionic (the libc)
 to have <tt>sys_signame[]</tt> like real BSDs, so that we could simply
 hard-code the appropriate CFLAGS and CPPFLAGS and let the NDK compile the
 mksh source *.c files (signames.inc would no longer be needed).</p>
<p>Maybe we'll submit <a href="@@RELPATH@@mksh.htm">mksh</a> for
 inclusion somewhere, as this would be the first <em>really</em> usable
 shell. For this reason, I have uploaded a binary (gunzip(1) first) at <a
 href="https://www.mirbsd.org/MirOS/dist/mir/mksh/ports/mksh-39.9.20090929-android15.tgz">ports/mksh-39.9.20090929-android15.tgz</a>
 (MD5 <tt>64ee103453d65e947f2beb1aeb6450d2</tt>) which you can place in, for
 instance, <tt>/data/mksh</tt> then put a (modified, as the ls(1) and id(1)
 and possibly other utilities are more than reduced) <tt>dot.mkshrc</tt> from
 the source (<a href="@@RELPATH@@cvs.cgi/mksh/dot.mkshrc?rev=1.49">CVSweb</a>)
 as <tt>/data/.mkshrc</tt> and run it from adb (which, by the way, is the one
 responsible for some cursor keys etc. not working, as Android and mksh(1) do
 both fine in that regard) with <tt># HOME=/data /data/mksh</tt> in the shell.
 I may post an Android specific patch for <tt>dot.mkshrc</tt> some day.</p>
<p><strong>Update</strong> 10.10. – .gz → .tgz and Cygwin binary now too!</p>
----
Title: more mksh (Android and others), new jupp, …
Date: 18.10.2009 18:33
Author: tg@
Tag: mksh

<p><a href="@@RELPATH@@mksh.htm">mksh</a>’s <tt>Build.sh</tt> can now
 generate <tt>Makefrag.inc</tt> snippets that reflect its environment
 and can be used like <tt>Rebuild.sh</tt> or integrated in, for example,
 the <tt>Android.mk</tt> files.</p>
<p>mksh(1) also is a great compiler testsuite: it <em>regularily(!)</em>
 points out bugs in gcc’s <tt>-fwhole-program --combine</tt> and helped
 to find (and fix) bugs in huge things like SunStudio, old things made
 modern like <a href="http://pcc.ludd.ltu.se/">pcc</a>, as well as one-man
 projects such as <a href="http://nwcc.sourceforge.net/">nwcc</a> ☺<br />
 I wish compiler authors would just use mksh as testsuite regularily.</p>
<p>I released a new version of <a href="@@RELPATH@@jupp.htm">jupp</a> for
 Unix® today: joe-3.1jupp12 (including a backported hex editing mode, as
 a late birthday present for waga (from IRC) who asked for it, a plethora
 of bug fixes, raw octet support in UTF-8 mode, UTF-8 support in the 8-bit
 modes, and <a href="@@RELPATH@@jupp.htm#r3_1j12">more changes</a>. If you
 already use it, update please. If not, give it a try! It’s included in at
 least FreeWRT already, and I build
 Debian packages (link on the jupp website) in my “play repository”, as well
 as packages for Univention Corporate Server at work (from these packages).
 I’m also using it on Solaris 8, Solaris 10 and AIX 5.3 ☻ (and many more)</p>
<p>There are currently quite a lot more things I would like to do but can’t
 seem to find the time for. I had originally planned a new MirBSD snapshot,
 including ISO, for mid→end of September – now, end of October seems more
 likely (if I can get a few days off work and some RAM for the SPARCstation
 5). Several things, like the mksh prompt wlog entry and webpages for a few
 subprojects (BSD::arc4random; arc4random.c; the RANDEX protocol, plugins,
 implementations, proxies; kwalletcli; keystash) are lacking too, and the <a
 href="http://grml.org/">Grml</a> project is also expecting code from me.
 Sorry. I am, after all, human too…</p>
----
Title: My stance on GNU and its Coding Style
Date: 28.10.2009 12:33
Author: tg@
Tag: mksh rant

<p>The GNU Project is famous for its coding style – Linus Torvalds even
 suggests to print them out, but not read them; burning them is a great
 symbolic gesture. Legibility issues aside (Linus’ own are interestingly
 similar to style(9) aka KNF, the BSD coding styles), why is that so?</p>
<p><a href="@@RELPATH@@mksh.htm">mksh</a>-current (R40+) now supports
 pathnames in arbitrary lengths on Debian GNU/Hurd (I think; I only could
 test on <tt>gnubber.bddebian.org</tt> that it compiles, seeing that all
 existing installations set sysconf(_PC_PATH_MAX) to 1024 to be consistent
 with POSIX <tt>PATH_MAX</tt>) by using some glibc-only functions. This
 is because Hurd does not have <tt>PATH_MAX</tt> (some older systems also
 don’t have it, but there, we just define it to POSIX 1024 and good is).
 Now, why? Simple: because the GNU coding style says to have “no arbitrary
 limits” in your code.</p>
<p>I would like to call that ridiculous, but it’s actually dangerous:
 if you are on a 32-bit machine and have a pathname of 512 MiB, you’re
 in danger of freezing your system or at least crashing mksh, even if
 you have the full 4 GiB worth of RAM, due to the amount of copying and
 carrying around pathnames. This is a security relevant issue, in my
 eyes.<br />Now on to the ridicule part: This is Open Source, people!
 Change the limit (as it’s a – only one – constant in a header file)
 and recompile everything! Simple as that! The BSDs do it all the time!
 In GNU, it’s even simpler because you <strong>force</strong> developers,
 redistributors and some users to actually give up freedom and require
 them to put the source code alongside. Now, why doesn’t anybody see this?
 I can’t be the only one, can I? (I actually think that changeable limits
 would suffice the horrid GNU coding style, but find myself reluctant to
 read it again due to its sheer size – similar to their licences…)</p>
<p>On an unrelated note, I hope to have a bi-arch ISO format snapshot on
 BitTorrent by end of the month. Mika is also trying to put a new <a
 href="http://grml.org/">Grml</a> release out by then, of course with
 an up-to-date <tt>MirOS bsd4grml</tt> ☺</p>
----
Title: Bittorrent trackers, …
Date: 31.10.2009 22:24
Author: tg@
Tag: rant
Pictures: 0
Picture0: wtf ist hallowe’en

<p>TPB has never been a viable tracker for us… h33t lost my login data…
 I hope Scarywater still holds up, we’ll be adding Openbittorrent to
 the mix… oh yikes, Demonoid is down. How great… NOT!</p>
<p>At least I finally managed to release things in time, and during the
 night, both ISO and CVS tarball, forming the torrent, will be available
 to the general public. I also already know of some interested parties,
 from remote areas like Romania and Mauritius.</p>
<h3 class="revbox">@!PICTURE0!@</h3>
<p>The <a href="@@RELPATH@@permalinks/news_e20091031-tg.htm">explanation</a>
 is on the front page, of course. This link is for the benefit of RSS or
 aggregator (like <a href="http://planet.symlink.ch/">Plänet Sümlink</a>)
 readers.</p>
<p>The files <em>will</em> take some time until they are up. I do have an
 ADSL internet connection only and they’re huge.</p>
----
Title: GRUB sucks! • More snapshot fallout.
Date: 01.11.2009 16:47
Author: tg@
Tag: bug rant snapshot

<p>The GRUB2 「memtest86+」 bootmenu option in both 「wtf ist hallowe’en」
 and Grml “Hello-Wien” does not work as-is (note that Grml uses ISOLINUX,
 unless you either select GRUB2 from the boot menu or dd(1) it onto a USB
 stick, CF/SD card, etc. for manifold-boot) because nobody told the Grml
 team that it must now be booted with 「linux16」 ipv 「linux」 – fix is
 to type ‘e’ to edit the entry, move right, type the “16” and hit ^X to
 boot. Just great… I’ve updated <a href="@@RELPATH@@permalinks/news_e20091031-tg.htm">the
 article</a> accordingly.</p>
<p><a href="http://www.symlink.ch/article.pl?sid=09/11/01/156220&amp;mode=nested">We
 are on Sümlink</a>. <a href="http://www.symlink.ch/article.pl?sid=09/10/31/196234&amp;mode=nested">Both
 of us</a>. Sweet. Remember that this could’ve been MirOS #11-RELEASE,
 and should be treated by everyone except us as such ☺</p>
<p>On the bonus side, I’ve tested the <tt>netboot.me</tt> 17001 boot, as
 well as the ISO (both file – in qemu – and CD-R on real hardware) on a
 SPARCstation 20, Setup (i386) on a VIA C7, grml and Live (i386) on an
 IBM X40 and in qemu… so I’d say it works. Oh, and memtest86+ on X40.</p>
<p>Netboot instructions: boot, e.g. via “qemu -m 256 -fda netbootme.dsk”,
 do not hit Ctrl-B, but hit the Anykey when it asks, “boot a configuration
 directly”, type 17001 and hit Enter; wait for the “boot&gt; ” boot(8/i386)
 prompt, type “b bsd.rd” and hit Return. Voilà! (Or, select MirOS bsd4me,
 which loads a memdisk-ISO, either via the number 2038 or via “Live OSes”
 → BSD → “MirOS bsd4me current” and just press Enter on the prompt. The <a
 href="http://static.netboot.me/gpxe/netbootme.dsk">gPXE image</a> can be
 dd(1)d onto a floppy disc.</p>
<p>Benny finally made ports/print/ttftot42 – thanks!</p>
----
Title: Subversion 1.6 and other stuff
Author: bsiegert@
Date: 03.11.2009 14:11

<p>For compatibility reasons, the current version of Subversion in
 MirPorts is still 1.5. I tried to remedy the situation a few days ago
 and committed subversion-1.6.6-0 into a branch a few days ago. It is
 not yet in the trunk because it has some nasty bugs. For example this
 gem:</p>

<pre>% perl -MSVN::Core -e 1
Bus error
</pre>

<p>This, of course, makes svk unusable, as it is written in Perl using
 the SVN perl bindings. svk is my way of making Subversion bearable,
 with easy replication, offline commits, and more.</p>

<p>I think I found the reason now: The SVN people managed to screw up
 the Perl module build so that the modules link against stuff in
 /usr/lib instead of <tt>$PREFIX</tt>. Incidentally, Darwin includes
 svn-1.4.4 in the base system. Sigh.</p>

<p>Wow, it seems that I have not written anything here in the last four
 months. Between my thesis and Real Life(TM), there is just not enough
 time for everything.</p>

<p>One more thing though: I have been attending a course on "Scientific
 Writing" at the Universit&eacute; de Haute Alsace, with excellent hints
 on article styles, writing readable scientific prose, and more. I can
 recommend such a course to every scientist, but also to all those who
 regularly publish things&mdash;including articles in CS journals, Free
 software project posters or announcements. There are also some
 excellent articles on how <em>not</em> to write. I especially recommend
 Martin W. Gregory, The infectiousness of pompous prose, <i>Nature</i>
 <b>360</b> 11&ndash;12 (1992). Unfortunately, you will need a
 subscription to read it.</p>
----
Title: this snapshot CDs, next snapshot codename
Author: tg@
Date: 06.11.2009 19:24
Tag: bug event security snapshot

<p><a href="http://www.openrheinruhr.de/aussteller.html">OpenRheinRuhr</a>
 will see <a href="@@RELPATH@@permalinks/news_e20091031-tg.htm">our latest
 snapshot</a> on CDs (although we seem to be short of flyers ☹). Complete,
 with MirOS BSD (i386, sparc; i386 Live) and MirGRML (i386).</p>
<p>The next snapshot’s codename has been decided upon angrily today: “wtf
 is with <a href="http://www.openbsd.org/errata44.html">all</a> <a
 href="http://article.gmane.org/gmane.comp.web.lynx.devel/6570">these</a>
 <a href="http://www.securityfocus.com/bid/36935">bugs</a>?”<br />Expect
 a fix for the latter sometime soon, it does in fact have more effect than
 most sites say, to avoid <span xml:lang="de-DE-1901">Panikmache</span>
 (unlike that <span xml:lang="de-DE-1901">Schweinegrippe</span> stuff);
 I’m lucky my online banking stuff keeps SIDs in the URI ipv Cookie, but
 still… very bad. Switching renegotiation off as a quick würgaround also
 is evil, for example, my SMTP setup (using X.509v3 SSL certificate auth
 for relaying) might break. But we are said to expect an amended SSL/TLS
 protocol soon, hopefully with OpenSSL patch.</p>
<p><a href="@@RELPATH@@cvs.cgi/src/distrib/common/ekeyrng">ekeyrng</a> is
 a very rough draft (shell prototype) currently driving, together with a
 small USB backport, a <a href="http://www.entropykey.co.uk/">Simtec
 EntropyKey</a> in <tt>herc</tt> into wrandom(4) (for now). Really, the
 Lua tools should be used, but this is good for the installer, although
 the <a href="@@RELPATH@@cvs.cgi/contrib/hosted/tg/tpmrx">TPM</a>, eKey
 and truerand – cprng(8) – functionality should be combined into one small,
 efficient, C dæmon doing so (but without the hacks to keep cprng(8) within
 one memory page to cease swapping). Still, it’s great!</p><!-- RSS stop -->
<p>bsiegert@ will be offline for a week.</p>
----
Title: got home
Author: tg@
Date: 08.11.2009 19:43
Tag: bug event snapshot

<p><a href="@@RELPATH@@permalinks/news_e20091031-tg.htm">The snapshot</a>
 has another bug I discovered after converting my laptop to a showcase:
 lynx(1) charset defaults, after disabling auto-detection, to the wrong
 one (the news item has been updated, again).</p>
<p>I came back from <a href="http://www.openrheinruhr.de/">OpenRheinRuhr</a>,
 and (apparently in contrast to many others) liked it, save for the (a)social
 event, which some organisers admit hasn't been what was promised to them. My
 hotel was actually some kind of <span xml:lang="de-DE-1901">Vereinshaus</span>
 and Billard club, so I had to eat supper (after fleeing the Casino, I had
 wanted to eat with some others deciding to split/fork, but formorer couldn't
 decide, so I walked the 3km, but didn't find anything appealing on the way,
 since I walked towards the outside of the city) in a smokey bar. So 2007,
 that. But I watched some kind of Billard competition during that, the meal
 was good and much, and the beer good and rather affordable. (I even took a
 <span xml:lang="de-DE-1901">Krug</span> to my room with me to flee smoke.)
 Breakfast was included, the quality much more than I had expected at that
 price (I paid almost twice that in Basel, where I didn't even have a private
 loo adjourning the room, much less a proper bathroom with douche). The city,
 despite confusing it with other <span xml:lang="de-DE-1901">Ruhrpott</span>
 cities beginning with <b>BO</b>, was nice and quiet (although the visitor
 count suggests that it was too remote, I rather prefer this to the usual
 rush and street mob, and it was still lively).</p>
<p>I think you'll find more coverage, photographies (hopefully not of me,
 as I wore a pullover forbidding it) and opinions on the 'net soonish, even
 dissing if I may harbour a guess (not without reason, from what I've been
 told privately), and, as I still have a headache (as usual...) I refrain
 from writing more. The MirBSD<tt>^H^H^H</tt>GRML CDs will be distributed
 at 26C3 by formorer from the Grml team <i>*grins</i> and I wonder if the
 celebrities equipeed with a MirCD or MirUSB stick, like Werner Koch, will
 make good use of it ;-)</p>
----
Title: I am happy with my eKey
Author: tg@
Date: 12.11.2009 19:16
Tag: debian

<p><a href="http://blog.halon.org.uk/2009/11/12#ekey-02">Neil</a>, I am
 happy with my <a href="http://www.entropykey.co.uk/">eKey</a>, and I
 would blog it if I had a blog ☺ (And yours doesn’t allow comments. But
 then, <a href="http://blog.digital-scurf.org/">Daniel’s</a> doesn’t,
 either.) I’d have liked proper (C flute / piano / voice) notes, though…
 never got the hang of string instruments.</p>
<p>Of course I still have to make a MirPort for that Lua dæmon, but for
 now, things work quite well. (I do have a rather large TODO and woke up
 with headaches and slight cold today.)</p>
----
Title: Yes, I am happy with my eKey ☺
Author: tg@
Date: 15.11.2009 01:49

<p><a href="@@RELPATH@@permalinks/wlog-10_e20091112-tg.htm">I am, indeed,
 happy</a> with my <a href="http://www.entropykey.co.uk/">eKey</a>. I’ve
 <a href="@@RELPATH@@cvs.cgi/ports/security/ekeyd/">ported</a> the ekeyd
 support software (but could not get ekey-ulusbd to work), created a real
 lot of patches, and discussed with «rjek» in IRC happily.</p>
<p>I now get about 4 KiB/sec on large streams (such as 64 KiB) reads from
 srandom(4), with 8 KiB/sec initially, in contrast to the less-than-100
 Bytes per second (300 Bytes per second initially) without the eKey.</p>
<p>Of course, there’s still room for improvement – I fixed the ioctl(2)
 calls, removed strcpy(3) and sprintf(3) calls, and added arc4random_buf(3)
 calls for generating the nonce (which can now be made much larger than
 the 12 conservative bytes the original code reads from urandom(4)), and
 made it work <em>at all</em> on our platform (and, possible, OpenBSD).
 But I get statistics now, even if told that my <tt>ekeyrng</tt> mksh(1)
 script is “Cute”.</p>
<p>Make sure you update to at least <tt>luasocket-2.0.1-1</tt> for some
 bugfix (pkg_info(1) has <a href="http://marc.info/?m=125823720030423">a
 bug</a> preventing it from seeing that – what worries me even more are
 some outputs not sent with the mail), and that you have a recent kernel
 (post the “wtf ist hallowe’en” snapshot!) since lsusb (even when ported)
 doesn’t output anything, and nobody knows what arguments to ekey-ulusbd
 are needed to make it find the eKey.</p>
<p>ObInfo: new CA bundles are out too, and more binary packages.</p>
----
Title: New MirBSD/i386 snapshots
Author: tg@
Date: 15.11.2009 14:54
Tag: news security snapshot

<p>I have compiled a new snapshot (i386 only) and uploaded the following
 flavours: <a href="http://git.grml.org/?p=grml-live.git;a=commit;h=6efcb236c9b1df3bc4323e0e6c625ea25115e26a">MirOS
 bsd4grml</a>, <a href="http://www.netboot.me/2038">MirOS bsd4me</a>-current
 (Live OS), <a href="http://www.netboot.me/17001">MirBSD-current</a> netboot
 (<a href="@@ABSPATH@@/MirOS/current/i386/">NetInstall for i386</a>), the <a
 href="@@ABSPATH@@/MirOS/current/cdrom10.iso">Midi-ISO</a> (bi-arch manifold
 NetInstall), and the checksums.</p>
<p>The <tt>/MirOS/current/older/</tt> subdirectory containing partial and
 incremental upgrades for older MirBSD-current snapshots is gone for now.
 The 20091115 (i386) snapshot is a security upgrade (contains the OpenSSL
 panic patch in its second version), bugfix (all errata mentioned in the <a
 href="@@RELPATH@@permalinks/news_e20091031-tg.htm">“wtf ist hallowe’en”</a>
 announcement are fixed if applicable), and feature upgrade: the installer
 and first boot recognise a <a href="http://www.entropykey.co.uk/">Simtec
 Entropy Key</a> if plugged in (for the installer, break into a shell and
 run <tt>/usr/libexec/ekeyrng</tt> if plugging it in later) for increased
 entropy generation; after first-time installation and reboot, the user is
 supposed to install <tt>ports/security/ekeyd</tt> and use that (for which
 there are <a href="@@ABSPATH@@/MirOS/Pkgs/current/i386/">binary packages</a>
 as well).</p>
<p>The MirOS Project’s servers are or will be upgraded as well; please bear
 in mind this implies short outages of service. Furthermore, due to the <a
 href="http://extendedsubset.com/?p=8">TLS protocol design error</a>, some
 things may not work any more, since we applied the OpenSSL “panic patch”,
 which disables all renegotiation, but allows applications to re-enable it,
 if they knew about that possibility at compile time, by setting a run-time
 flag before initiating the connection. (None we know of does, though.)</p>
----
Title: Still happy with the eKey
Author: tg@
Date: 25.11.2009 09:11
Tag: debian

<p>As I <a href="@@RELPATH@@permalinks/wlog-10_e20091112-tg.htm">wrote</a>,
 I asked for flute notes. Well, piano notes are ok too, although I don’t
 have my electric organ any longer, they can easily be transposed, even
 if I don’t know the software (could do it by hand though). And I might
 give midiplay(1) a shot (I bet it’ll sound like PC-Speaker emulation…).
 <a href="http://vincentsanders.blogspot.com/2009/11/getting-things-done.html">Vincent</a>
 kindly provides more input (apparently one more of these Simtec people,
 but that’s just my guess).</p>
<p>Since <tt>ports/security/ekeyd</tt> runs happily on <tt>herc</tt> and
 most of my patches were not just applied but even appreciated, thanks
 Daniel, and <a href="@@RELPATH@@permalinks/wlog-10_e20091115-tg.htm">the
 results</a> speak for themselves (I even get stats from daily.local mailed
 to me every night), and we had some fun discussions, I like it. I think
 these whom I ordered additional ones for are, too. (I wonder if I should
 invest into a ten-pack bulk ones and re-sell them at conferences, but the
 <a href="http://www.fosdem.org/">next one</a> is so close to the UK they
 probably will be there by themselves.)</p>
<p>I must admit I also have the context switching problem (but hey, that’s
 what you get for being a sysadmin, and our
 <a href="http://www.gepa3.de/shop/index.php">coffee</a> (GEPA, <span
 xml:lang="de-DE-1901">ganze Bohne, im Eimer, fair gehandelt</span>),
 even if not <a href="@@RELPATH@@anargeek.htm#koffie">Café Libertad</a>,
 who, incidentally, are Debian Wine distributors, is good), but since I’m
 usually not working for customer projects, I’m rarely time bound, and
 quite some good ideas have come from distraction (or timeouts, such as
 personal needs or getting coffee/food/…).</p>
<p>Now I still wish I could split myself in half to get more time for all
 the projects I have…</p>
----
Title: more mkshdroid and other OSS project stuff
Author: tg@
Date: 02.12.2009 17:21
Tag: android debian mksh

<p>I managed to create an avd "Android 2.0-current", with stuff completely
 built by myself. Now I "just" need to get project/external/mksh.git to be
 created and writable by me. Or, even better, nuke that NetBSD® ash they're
 currently using and replace it with a sensible shell, at least mksh-small.
 Then adb can be built with<em>out</em> <tt>-DSH_HISTORY</tt> (which, with
 <a href="@@RELPATH@@mksh.htm">mksh</a>, is required for usability).</p>
<p>I wonder if I could take over Mæmo as well... *grins*</p>
<p>On unrelated side notes, I'm trying to get the "debian" tagged entries
 aggregated on Plänet Debian, and I'm &ndash; again &ndash; in the NM
 process trying to become a DD, with slightly different goals this time.
 (But I'd also
 like these porting machines... 'sides, there's still an mksh+dietlibc on
 hppa bug open...)</p>
<p>I also got HP-UX back at HP PvP (not player versus player though ;) for
 mksh(1) porting/testing. Sadly, Itanic only, no humppa machines.</p>
<p>In case someone ever needs it, a collection of scripts called <a
 href="https://evolvis.org/projects/bw2mw/">BitWeaver → MediaWiki</a>
 does exactly that and has been released under GNU GPLv2 (only). Cheers!</p>
----
Title: Happy Benzday!
Author: tg@
Date: 07.12.2009 20:41

<p>Since I don't reach you via IRC, phone or Natel&trade; let me wish
 you a happy benzday here. ☺☻</p>
<p>I think it's perfectly okay for libobjc to depend on libgcc_s like
 libstdc++ does. So let's not disable gobjc from base. Rather, make
 everything except C version-dependent. (Bump base vsn afterwards, the
 gcc vsn has been already.) I think we'd also best rename the clang
 executable and make a wrapper using <tt>-L</tt>, <tt>-rpath</tt> and
 <tt>-I</tt> flags from its <tt>CCLD</tt> instead of always using
 these from the system compiler. (I wonder if it's worth the effort
 to make the C++ header files version dependent as well. Probably.)</p>
<p>We somehow need a way to differentiate ABIs in MirPorts, as there
 will be several compilers. On MirBSD: base-gcc3.4.6, port-gcc4.4.2,
 port-llvm-gcc4.2.1, port-pcc, port-nwcc (this list is for i386).</p>
<p>Benny, may I encourage you to hack on pkgtools the next Muttenzday?
 Especially I'd like to have that file extension retaining/cycling for
 auto-dependent packages in, it's basically a showstopper for LZMA
 compressed binary packages. (Will still be LZMA1 for some time, as
 there is not yet a stable xz release.)</p>
<p>The <a href="https://eurynome.mirbsd.org/debs/dists/hardy/wtf/pkgs/kwalletcli/">hardy
 at MirDebian "WTF" Repository</a> section contains a KDE 3 source and
 binary package of <a href="@@RELPATH@@kwalletcli.htm">KWalletCLI</a>
 2.00 (built for Debian Lenny and K?buntu Hardy). A KDE 4 package (for
 Debian squeeze/sid, newer *bunti and ones with KDE4-backport) will be
 worked upon as soon as I can get into the pkg-kde Alioth group.</p>
----
Title: BASE – schlimmere Verbrecher als Debiltel
Author: tg@
Date: 11.12.2009 17:37
Tag: rant
Language: de-DE-1901

<p>Bei VIAG Interkom einen Händivertrag (Händi, schwäbisches Fremdwort,
 von "Jo hän di denn do koa Kabel dran?") kündigt, geht das relativ gut,
 man bekommt nur zwei Monate später eine Rechnung über 0,00 €. Den T-D1
 Mitarbeitervertrag (Azubi...) wird man auch gut wieder los, obschon er
 über die Laufzeit hinweg funktioniert (wohl ein Abschiedsgeschenk des
 Ausbildungskonzerns). Bei Debitel hingegen wird der postalische Eingang
 der schriftlichen Kündigung um ein paar Tage verzögert, und dann hat
 man den Vertrag noch knapp 15 Monate lang am Hals. Die Frechheit ist
 aber BASE: die Karte funktioniert, nach meiner Kündigung gegen Anfang
 des 2. Quartales 2008(!), immer noch. Auf Anfrage teilt man mir mit,
 daß "leider" in ihrem System keine Kündigung ersichtlich sei, und ich
 noch bis zum 5. Dezember 2010(!) damit leben müsse.</p>
<p>Hoffen wir, daß Netcologne, falls ich denn den dortigen Mobilfunkteil
 meines Kombipaketes mal loswerden will, angenehmer ist. Immerhin ist das
 die einzige Telko, die auch mal Bestandskundenaktionen macht, mit denen
 ich seit 2001 ununterbrochen extrem zufrieden bin, und die nur ein Mal
 größere Störungen hatten (November 2001, wohl noch neu) und einem für
 einen halben Monat öfters gestörten DSLs einen ganzen Monat Telephon- und
 DSL-Grundpreis erstattet haben; die defekte Splitter und Leihmodems (NTBBA)
 innert Stunden ohne große Fragen austauschen; die einem alle paar Jahre
 mal <em>sowohl</em> den Grundpreis reduzieren <em>als auch</em> der DSL
 Geschwindigkeit erhöhen...</p>
<p>Also, Leute, kauft nicht bei BASE! (ciruZ ist mit blau.de zufrieden,
 die sind aber Prepaid, das heißt zwar keine Knebelverträge, aber auch
 keine unlimitierten Telephonate im Ausland, z.B. um gecko2 auf belgischen
 Autobahnen zu helfen.) Daß es auch anders geht zeigt die Deutsche Bahn in
 <a href="@@RELPATH@@permalinks/wlog-10_e20090204-tg-g10020.htm">einer
 anderen Kaufempfehlung</a> (diese hier ist allerdings eher eine leicht
 frustrierte <strong>Ver</strong>fehlung). Mein Brüderchen fand, ich sollte
 das hier dokumentieren/ablassen; keine Bange, das hier wird nicht wie bei
 Fefe eine Produktbashingseite werden (dafür sind einfach alle Sachen in
 Existenz zu... kaputt, das ist mir meine Zeit nicht wert).</p>
<p>Naja, mal die Kündigungsbestätigung aus den Altunterlagen raussuchen,
 um deren Zusendung ich letztes Jahr gebeten hatte. Warum wohl?</p>
----
Title: I smell an antitrust case coming up
Author: tg@
Date: 12.12.2009 21:03
Tag: mksh rant security

<p>Oh the joy…</p>
<p>20:54⎜«smultron» <i>mira</i>: i just upgraded the big server from 10.5
 to 10.6... and apparently the upgrade script removed /bin/mksh... now I
 don't have a shell and quits immediately... any ideas?</p>
<p>My suggestion – <tt>ssh -t servername /bin/bash --login</tt> – doesn’t
 seem to help:</p>
<p>20:59⎜«smultron» oh great<br />
   20:59⎜«smultron» ssh just keeps asking for the password<br />
   20:59⎜«smultron» then gives this:<br />
   20:59⎜«smultron» Permission denied
 (publickey,gssapi-keyex,gssapi-with-mic,keyboard-interactive).</p>
<p>Maybe gecko2@ can help… or bsiegert@… who knows.</p>
<p>In other news, no reaction <em>at all</em> on the Android front on <a
 href="http://groups.google.com/group/android-platform/browse_thread/thread/413d8e10ec68b9fa">my
 proposal</a> to get <a href="@@RELPATH@@mksh.htm">mksh</a> either to
 replace NetBSD® 0.x ash, or, at least, add it for developers.</p>
----
Title: RFC: New pkgtools features
Author: bsiegert@
Date: 13.12.2009 17:26

<p>Yesterday, I posted the following proposal to the mailing list. I am
 putting it here, too, for future reference.</p>

<p>I have been thinking about how we can improve the pkgtools with some
 new and useful features. There are two that would be easy to implement
 and would give us some kind of "poor man's apt":</p>

<p>Replace <tt>PKG_PATH</tt>, which at the moment is either a single URL
 or a colon-separated list of local paths, by a simple config file. It
 could also include a few other directives, like the default pager for
 MESSAGE files. I am thinking of the following:</p>

<pre>Pager=less
Source=1,/usr/ports/Packages
Source=255,https://www.mirbsd.org/MirOS/Packages/i386/</pre>

<p>The "source" lines are just local paths or URLs with a priority
 value, where 0 is the highest one.</p>

<p>For http, we have the problem of getting the file names. I propose to
 put an <tt>index.txt</tt> file, with just one filename per line, into
 each "repository". The indices might be cached so that we know what
 files are where. For http, we could even automatically update by using
 an "If-Changed-Since" header, or have something akin to "apt-get
 update".</p>

<p>It would be very easy to just search the repos in order of priority
 and take the first match for the pkgspec given. Or we could use
 <tt>findbestmatchingname()</tt> to decide which package to take.</p>

<p>These changes can be implemented in a reasonable amount of time, I
 think. Maybe during the CCC?</p>
----
Title: Stehen, Warten, Beten
Author: tg@
Date: 17.12.2009 14:52
Tag: rant
Language: de-DE-1901

<p>SWB. Stehen, Warten, Beten.</p><!-- RSS stop -->
<p>Am Dienstag Abend waren wir mit <a
 href="http://www.gnurandal.com/">Roland</a> in der Bonner Innenstadt.
 Hiernach wollte ich gerne nach Hause fahren, aber die StadtWerke Bonn
 machten mir, wie so oft, einen Strich durch die Rechnung.</p>
<p>Das ist eigentlich gar nicht so schlimm, denn wäre ich zu Fuß gegangen
 hätte ich sicherlich nicht mehr als eine Dreiviertelstunde benötigt.
 Aber wir haben ja das tolle Informationssystem, das uns allerdings nur
 anzeigte: „Betriebsstörung. Unregelmäßigkeiten im Fahrplan
 <em>möglich</em>.“</p>
<p>Bei „möglich“ wäre ich hellhörig geworden, aber das stand schon den
 ganzen Tag da, und morgens auf dem Weg zur Arbeit war eigentlich nichts
 los und wurde nichts durchgesagt. Also warte ich auf die nächste Bahn.
 Eine ganze Viertelstunde lang – anscheinend ist (gestern Abend nach der
 Arbeit übrigens auch) <em>mal wieder</em> eine Bahn ausgefallen, ohne
 daß dies angezeigt oder durchgesagt wurde, trotz moderner Technik. (Die
 Deutsch Bahn schafft dies zumindest auf ihrer Webseite, und Durchsagen
 gibts auch öfters, Anzeigetafeln sind dort ja etwas unflexibler.)</p>
<p>Dann kam die Bahn, ich frag’ was denn los sei. „Ja, ich fahre auch
 nur (1 Haltestelle), von da aus müssen Sie zu Fuß (2 Haltestellen)
 laufen, da fahren wieder Bahnen, wir haben da ein Riesenloch in der
 Straße.“ (Kurzum ein ganzer Streckenabschnitt abgeschlossen, ohne eine
 Möglichkeit, dort weitere Verkehrsmittel reinzubringen.)</p>
<p>Ich laufe also, frustriert, und stehe mir an der Zielhaltestelle –
 wohlgemerkt bei Minusgraden – wieder die Füße in den Bauch. Die gerade
 gewendet habende Bahn eine knappe Viertelstunde lang gut sichtbar für
 uns auf dem Stumpfgleis, Lichter an, tätigkeitslos.</p>
<p>Alles in allem habe ich annähernd eineinviertel Stunden nach Hause
 benötigt, und das ist bei einem monatlichen <strong>reduzierten</strong>
 Abonnementpreis von 66.50 € einfach inakzeptabel, zudem die tollen neuen
 Anzeigetafeln intakt waren. Hätte ich das gewußt wäre ich gelaufen oder
 hätte mir ein Taxi genommen, aber nein, die StadtWerke Bonn machen ihrem
 Namen „Stehen, Warten, Beten“ alle Ehre. Wenn ich nicht mein Abonnement
 <a href="@@RELPATH@@permalinks/wlog-10_e20090204-tg-g10020.htm">eh’</a>
 schon bei der Deutschen Bahn hätte würde ich es sofort kündigen.</p>
<p><span xml:lang="en">To add insult to injury</span>, die Anzeigetafeln
 waren mit einem teils statischen teils durchlaufenden Text so dermaßen
 „voll“ belegt, daß man es nicht für nötig hielt, die normalerweise dort
 verfügbare Uhr (man sieht schön, daß alle Bahnen an den Endhaltestellen
 immer eine Minute zu spät abfahren – aber von einem Ex-1€-Mitarbeiter
 weiß ich ja, daß die SWB drei(!) unterschiedliche Fahrpläne haben…)
 anzuzeigen. Dann hätte man ja entscheiden können zu laufen – insbesondere
 wenn man informiert gewesen wäre. (Oder zumindest dann drei statt zwei
 Haltestellen laufen und eine Bahn früher nehmen. Oder zwei, je nachdem.)
 <br />Ich meine, für den Wasserrohrbruch zwischen Straßen- und U-Bahn
 können die ja nix, aber informieren können hätte man mich wenigstens,
 denn am nächsten Tage (gestern) mußte ich <em>sehr</em> früh ’raus.</p>
----
Title: Disappointed
Author: tg@
Date: 26.12.2009 16:35
Tag: snapshot

<p>I somewhat had hoped the TLS extension would be finished this month.
 Too bad. I will still wait for an OpenSSL patch, and maybe options for
 clients to control behaviour (on connections to servers that don’t have
 it implemented yet), such as lynx(1).</p>
<p>Alas, we need a snapshot by January, to put on AllBSD.de USB sticks,
 so I’m compiling one. Other than that, recovering a little over the
 weekend, will need to work next week as well. Taking things slower.
 I think I caught a slight cold+stomach ache last weekend, when it was
 freezing pretty hard.</p>
<p>Benny is at 26C3, but there’s probably no official MirOS presence.
 You’re still cordially invited to talk to him and gecko2@ who’s there
 as well.</p>
----
Title: Just another Office suite
Author: tg@
Date: 26.12.2009 17:14

<p>In addition to <a href="http://www.openoffice.org/">OpenOffice</a>
 2.0 (Linux-i386 on MirBSD) and the Lotus SmartSuite Millennium, I
 downloaded <a href="http://www.loadandhelp.de/">SoftMaker Office 2008</a>
 for Linux-i386 (on MirBSD) and Windows® (free serial numbers until end
 of 2009, since SoftMaker Office 2010 (for Windows®) is out). This was
 pretty easy: extract tarball, throw away installer, extract the second
 tarball in <tt>/opt/SMo</tt> (along with <tt>/opt/OOo</tt>), and it
 Just Works™ (with <tt>ports/emulators/fedora</tt> installed).</p>
<p>So now I have three choices for creating documents (although I won’t
 use OOo for it, I think it’s unreadable), and three for reading files
 in MS Office format, and two (OOo and SMo) for reading documents in
 some weird .ZIP-like format (OASIS or something), if they get sent to
 me. I’ll toy around with SoftMaker Office 2008 on both platforms and
 will see how it compares to Lotus WordPro.</p>
<p>So this is basically positive press to show another Linux-i386 blob
 that works as-is on MirBSD/i386 with compat_linux(8) – thanks! Others
 make this much more difficult.</p>
----
Title: 26C3, day 0 and 1
Author: bsiegert@
Date: 27.12.2009 17:40
Tag: event

<p>I finally have a wristband for 26C3. The wristband is what is
 controlled on the entrance. I had preordered the ticket and paid by
 bank transfer, and the receipt with the barcode only arrived on
 december 25. In earlier years, you came on the 26th, crashed in the
 hackcenter, and at some point, when there were only ten people in the
 queue at the cash desk, you got your ticket easily.</p>

<p>Well, this year, things were a little different. First, there was a
 semi-public ticket presale. What's more, rumors about a very limited
 number of tickets were floating around. And finally, while the cash
 desk was said to open at 2000, the software was not ready by then (!)
 and the opening was deferred to 2130. The "fast line" cash desk for
 people with presale tickets was only opened around midnight, when I had
 already given up hope and joined the <em>huge</em> queue of several
 hundred desperate hackers. (Thanks, btw, to ScottyTM for pointing out
 that the "fast line" had been opened.) Finally, I was told that my
 ticket "did not exist in the system", that I was an evil cracker for
 trying to enter with a fake ticket, and that I should check back on the
 27th. Great.</p>

<p>The end was happy and somewhat anticlimactic: I checked back this
 morning, there was no queue, and my presale ticket was accepted without
 any problem. Most of the talks I saw today were about network
 neutrality, censorship and related topics. I found the <a
 href="http://events.ccc.de/congress/2009/Fahrplan/events/3501.en.html">talk
 by J&eacute;r&eacute;my Zimmermann</a> from <a
 href="http://www.laquadrature.net/"><i>La Quadrature du Net</i></a>
 especially interesting. Part of the talk was an introduction to
 lobbying: calling your EuroParl representative, sending e-mails and
 insisting on your point "raises the political cost of certain
 decisions".</p>
----
Title: speling[sic!]
Author: tg@
Date: 27.12.2009 19:07
Tag: debian

<p>With <a href="http://www.eyrie.org/~eagle/journal/2009-12/012.html">the
 Lintian 2.3.0</a> saturday-after-christmas release (by the way, over here
 if it’s done twice it’ll really become tradition) I’ve run its spelling
 tests over all of MirOS CVS repository. The result: 293 kinds of typos in
 35857 souce files. (Although there are the case things too. Without them,
 I have 51 typos in 7206 files. Asides from false positives (I used fgrep
 <tt>-rwl</tt>[<tt>i</tt>], and <tt>-i</tt> and <tt>-w</tt> don’t play well
 together, and <tt>-w</tt> mis-catches “GTK+” as “GTK”) I probably can’t
 (API, source code) or won’t fix all of them though.)</p>
<p>However, I have some rather hot asia-style food to eat right now, and
 will need to get up early tomorrow for work, so I am not applying/fixing
 them right now. (bsiegert@ and gecko2@ however are enjoying themselves at
 26C3, see their wlog entries.)</p>
<p>Note that all of today’s fixes will not make it into the next MirBSD
 snapshot already, since it’s built (i386) and building X11 already (sparc).
 On the other hand, the next bunch of WTF *.deb files <em>will</em> have
 them. I also need to fix <strong>makefs</strong> upstream for Hurd… and
 continue the T&amp;S questionnaire… *sigh*</p>
<p><strong>Update</strong>: I suppose this is my “Hello, Plänet Debian!”
 posting (thanks aptituz!)… well, my packages in the archive were already
 lintian clean, in case someone wonders (I did recheck with 2.3.0 though).
 My point was, why not use checking tools from one “universe” for another
 one, viceque versa? (Similar to synergy effects from knowledge.)</p>
----
Title: new snapshot upcoming
Author: tg@
Date: 29.12.2009 20:51
Tag: snapshot

<p>I’m almost there: i386 and sparc have compiled complete. Now I “just”
 need to do some release engineering (consider whether to re-roll the
 <tt>ports10.ngz</tt> dist set; creating the combined manifold Midi-ISO,
 various things with checksums and signatures, announce and upload) then
 we’ll have a new snapshot. Finally, I also plan to create a big ISO to
 replace the “wtf ist hallowe’en” edition. No new MirGRML but nevertheless
 bugfixes for <tt>grub.cfg</tt> (memtest and vga modes).</p>
<p>The other side is that I didn’t have to do much for this, luckily; I
 was still suffering from some kind of cold+stomach ache. I hate that. I
 bought vitamines etc. for $alot € yesterday to fight it better though.</p>
<p>OpenBSD can build the kernel with pcc now, nice. I thought ÆrieBSD was
 the one with switching to a GNU-free toolchain goal though…</p>
----
Title: RCBD #1
Author: tg@
Date: 01.01.2010 14:17
Tag: debian

<p>My first RC Bug-squashing Day (or rather night):</p><ul>
 <li><a href="http://bugs.debian.org/552791">bug #552791</a> – acorn-fdisk –
  Copyright file does not contain verbatim copy of the license or a pointer
  to one</li>
 <li><a href="http://bugs.debian.org/562647">bug #562647</a> – gidentd –
  Does not work with ipv4 after recent change in netbase</li>
 <li><a href="http://bugs.debian.org/558812">bug #558812</a> – dietlibc –
  incorrect license in debian/copyright</li>
 <li><a href="http://bugs.debian.org/531937">bug #531937</a> – autossh –
  FTBFS on mipsel due to missing -fPIC</li>
</ul>
<p>I picked all of them mostly randomly from the <a
 href="http://bugs.debian.org/release-critical/debian/all.html">list</a>
 Zack gave me, and except dietlibc they are packages I had not even heard
 of before. The first one begun easily (track down licencing information,
 pimp <tt>debian/copyright</tt>, but I ended up fixing compiler and lintian
 warnings and even wrote a manpage for it while there (but for this one, I
 didn’t bump the Standards-Version). The second one was only the second one
 to complete because the others took longer; it’s basically a change of a
 dæmon to use two instead of one listening socket, to work with a “doble
 stack” OS instead of just a “dual stack” OS by not using v4-mapped IPv6
 addresses (I considered if to use select(2) or poll(2), or to just fork
 and have two dæmons running, but that seemed too ressource-consuming to
 me so I chose the less-complicated poll(2) method, looking at popa3d(8)’s
 source code (inherited from OpenBSD) in the MirBSD tree since I could not
 find my network programming book. The third one was basically communicating
 with upstream; the bug can be blosed with no change to the package. The
 fourth one took me a while; luckily I have qemu 0.11.0 on MirBSD, and <a
 href="http://people.debian.org/~aurel32/qemu/mipsel/">aurel32’s mipsel qemu
 images</a> helped a great deal; however, <tt>cowbuilder --create</tt> failed
 for me, so I ended up waiting almost the entire night for a-g d-u to finish;
 in the end, it was simply a bug in upstream’s <tt>configure.ac</tt> which is
 only exposed due to a <a href="http://bugs.debian.org/519006">toolchain bug
 on mips(el)</a>.</p>
<p>To do: my AM Zack needs to upload the NMUs (after checking, of course);
 I need to communicate some of the fixes upstream (the gidentd upstream is
 NXDOMAIN ☹), produce a very small testcase for the mipsel toolchain bug,
 maybe fix some more mipsel FTBFSen as I have a working qemu instance now,
 but maybe I’ll do that at the BSP when I can’t find IPv6 bugs or so that
 I feel I can fix (I also want to do an <a href="@@RELPATH@@mksh.htm">mksh</a>
 release which has to be prepared first RSN, and there’s still the need to
 formally publish the MirBSD-current bi-arch snapshot and make another ISO
 out of it for BT and prepare the multi-BSD USB stick for allbsd.de…).</p>
<p>Annoyances: a-g d-u could ask me things at the start before working for
 some four+ hours instead of in the middle, and the same questions several
 times (PAM restart). The sid kernel doesn’t boot today but did yesterday,
 the lenny kernel produces this:<br /><tt class="dowrap">Starting the hotplug events
 dispatcher: udevdudevd[320]: udev: missing sysfs features; please update
 the kernel or disable the kernel's CONFIG_SYSFS_DEPRECATED option; udev
 may fail to work correctly</tt><br />(I hate udev.) And, worst of all,
 these annoying fireworks (some sounded like originating from inside our
 staircase, I pity the neighbour’s cats) when one wants to hack… Finally,
 I *loathe* CDBS. Debhelper <a
 href="http://xana.scru.org/xana2/parabola/carhelper/">v5</a> rules!</p>
<p>Oh, and I also was under the impression that “Firstname LASTNAME” was
 a French thing, and to a much lesser extent Asian. (@bubulle)</p>
----
Title: catching up the TODO
Author: tg@
Date: 01.01.2010 20:46

<p>Wow. Cleaned up <a href="@@RELPATH@@mksh.htm">mksh</a>, did NMUs for <a
 href="https://nm.debian.org/nmstatus.php?email=tg%40mirbsd.org">T&amp;S
 1</a>, tested nwcc, validated mksh-current (what will be the base of R39b)
 on HP-UX, but there’s still a lot of things I need to do. A new MirBSD
 snapshot awaits, more ports fixes, new LLVM, I’ve got to fix the typos I
 <a href="@@RELPATH@@permalinks/wlog-10_e20091227-tg.htm">found</a>, and
 much more. And it’s already this late. At least I feel like I’ve achieved
 somewhat much ☺ I somehow need to put an order or priorities to tasks.</p>
<p>The 26C3 gang has also returned, with delays that seem funny to those
 not involved… and tonight snow came back as well. Benny still works on
 the pkgtools configuration stuff. I wonder how much effort it would be
 to patch both pkgtools and apt to play together optionally… we wouldn’t
 lose that what pkgtools already have as high-level functionality, gain
 some of dpkg’s low-level functionality (must be reimplemented though),
 and for these who want, a (GPL’d…) high-level tool for binary package
 management.</p>
<p>FreeWRT is also slowly gaining
 a little more traction, even from its founder (who asserts that FreeWRT
 1.0-stable is the only OS for WRT-like devices that does WDS correctly,
 and feeds us patches). I still think we need MirWRT ☺ with a ports-like
 instead of buildroot-based system, but will never have enough time and
 interest to do that…</p>
<p>And: our <a href="@@RELPATH@@cvs.cgi/www/">website source code</a> is
 in fact superiour to many others ☻ and quite extensible and flexible…</p>
----
Title: new MirBSD-current snapshot; more TODO done
Author: tg@
Date: 03.01.2010 19:42
Tag: debian snapshot

<p>The MirBSD <a href="@@ABSPATH@@/MirOS/current/cdrom10.iso">Midi-ISO</a>
 (bi-arch manifold boot) and NetInstall for both i386 and sparc have been
 upgraded to the 20091226 snapshot (sorry for the delay). A separate news
 announcement will be done when a full ISO (MirBSD + MirGRML) is done.</p>
<p>Other than that, I have fixed a couple of things all over the place, <a
 href="@@RELPATH@@jupp.htm">jupp</a> for example. The planned release of <a
 href="@@RELPATH@@mksh.htm">mksh</a> R39b is still not done though, as I’m
 only human as well, and too much hacking isn’t something one can do without
 relaxing some in between.</p>
<p>On the Debian front, my RCBD #1 was continued, here’s #1½ results:</p><ul>
  <li style="list-style:none;">Carry over from day #1</li>
 <li><a href="http://bugs.debian.org/552791">bug #552791</a> – acorn-fdisk –
  Copyright file does not contain verbatim copy of the license or a pointer
  to one</li>
 <li><a href="http://bugs.debian.org/562647">bug #562647</a> – gidentd –
  Does not work with ipv4 after recent change in netbase</li>
 <li><a href="http://bugs.debian.org/558812">bug #558812</a> – dietlibc –
  incorrect license in debian/copyright</li>
 <li><a href="http://bugs.debian.org/531937">bug #531937</a> – autossh –
  FTBFS on mipsel due to missing -fPIC</li>
  <li style="list-style:none;">New ones</li>
 <li><a href="http://bugs.debian.org/563522">bug #563522</a> – acorn-fdisk –
  cleanup patches</li>
 <li><a href="http://bugs.debian.org/563525">bug #563525</a> – gidentd –
  cleanup patches</li>
</ul>
<p>Explanations: I did go overboard during the first patching session, but
 I suppose this is what the NM learning period is for too. The autossh
 maintainer said thanks and will probably integrate my patches, so I don’t
 need to NMU. I could close the dietlibc bug. The other two didn’t look as
 good, I had to separate the fix for the RC bug (and other required fixes,
 such as ftp-master rejects – there were none though) and my other fixes;
 I submit the former as NMU diffs again and pointed Zack to the .dsc files,
 and opened the aforementioned two new bugs with the rest of the diffs, so
 the proper maintainers can take and apply them.</p>
<p>There’s questioning if gidentd should be removed (see the PR for more);
 the acorn-fdisk upstream (arm-fdisk it’s called there) is not actively
 developing but will receive patches; the autossh maintainer said thanks
 but I didn’t yet hear back from upstream.</p>
<p>The <a href="http://bugs.debian.org/541535">binutils as intel_mode bug</a>
 was fixed upstream and in experimental for my case, but I had to reopen
 things because the variant documented in binutils-current still doesn’t
 work, so others (who use the new, more intel-like, syntax) don’t run into
 it.</p>
<p>Luk sent me a request to do more mipsel-FTBFS-due-to-toolchain-bugs
 workarounds. Will do (but can’t promise to do so before the upcoming <a
 href="http://wiki.debian.org/BSP2010/Moenchengladbach">BSP</a>.</p>
<p>Robert Millan incorporated something like manifold-boot into GRUB 2,
 after I described it to him (the debian-bsd@ people are currently sorting
 out some heisenbugs with it, though). Now there’s three variants (but then,
 this helps spotting bugs that don’t appear in all implementations).</p>
<p><a href="http://marc.info/?m=111197460604448">sendmail 8.13.4 is out</a>,
 I wonder when OgreBSD will upgrade… I could do it myself again, but this
 time it’s not <em>that</em> urgent. Still waiting for the TLS extension,
 though…</p>
----
Title: Various topics, and, at least *some* people think!
Author: tg@
Date: 20.01.2010 17:31
Tag: debian event mksh rant snapshot

<p><a href="http://www.pro-linux.de/NB3/news/1/15197/">Marc Fleury, JBoss
 founder</a> joins the ranks of <a href="http://nosec.ch">Tonnerre</a>,
 me, and other people requesting that MySQL (and MariaDB!) <em>please</em>
 finally die. Everyone, don't even fork it. Use <a
 href="http://www.microsoft.com/sql">a</a> <a
 href="http://ingres.com/">real</a> <a
 href="http://www.postgresql.org/">database</a> instead. Or, at least, <a
 href="http://sqlite.org/">SQLite</a>. Really.</p>
<p>We're going to <a href="http://www.fosdem.org/">FOSDEM</a> 2010 (of
 course &ndash; I've been at every FOSDEM that was not just an OSDEM,
 Benny and gecko2 are regular attendees as well, as are other projects
 of mine such as FreeWRT and Debian GNU/kFreeBSD, by proxy). There will
 be a recent MirBSD snapshot I've yet got to build, with the new floppy
 format ustarfs (idea, but no single line of their stinking ridiculously
 huge code, stolen from NetBSD®) and other improvements (albeit less than
 I wanted to get done by then). The days before, I'll attend the first <a
 href="http://roland.entierement.nu/blog/2010/01/15/fusionforge-developersusers-meeting-coming-up.html">FusionForge
 meeting</a> to break up the French Cabal, with my work hat on. That is
 also my first time in France (outside of the Elsaß). People, make a good
 impression on me to overcome the classic prejudices ;-)</p>
<p><a href="http://wiki.debian.org/BSP2010/Moenchengladbach">This
 weekend</a> I'm going to meet my Debian Application Manager zack, have
 some good beer (ugh... first this, then Paris, then good belgian beer...)
 and fix some bugs, all while learning even more. Sounds like fun, but I
 almost feel overwhelmed, in contrast to the years of much less travelling
 from my past. I've also started sort-of mentoring Simon, one of our
 apprentices at work, into the Debian processes. (On an unrelated side
 note, formorer recently said bpo will become bp.d.o soon. Great!)</p>
<p>Please don't laugh at <a href="@@RELPATH@@kwalletcli.htm">this excuse
 for a webpage</a>, as I've yet to fill it in, but my CLI for the KDE
 Wallet is hereby deemed ready for public consumption, with a bug-fix
 release <tt>2.01</tt> (bugs actually found during preparation of a
 port to Debian sid and KDE 4, which is much much worse than KDE 3, plus
 it looks so absolutely disgusting I'm not even sure Windows® Mistda is
 worse). I hope the package will end up in NEW soon (and once progressed
 to testing I may be able to make the KDE 3 variant official via lenny
 backports; <a href="https://eurynome.mirbsd.org/debs/debidx.htm">my WTF
 <tt>*.deb</tt> repo</a> will hold them until then.</p>
<p style="font-size:small">There are more webpages I need to fill in...
 mksh's TaC, arc4random (which needs some major redesign as well) and
 BSD::arc4random, the RANDEX protocol (entropy exchange over IRC) and
 its plugins and patches, ...</p>
<p>Not just <a href="@@RELPATH@@permalinks/wlog-10_e20080712-bsiegert.htm">Mac
 OSX</a> (and, I hope, iPhoneOS) will soon come with mksh(1), but also
 Android (I prepared patches to make it <tt>/bin/sh</tt>, which works
 quite well &ndash; although I need to find out how to make a hardlink
 so that <tt>#!/bin/mksh</tt> scripts will run) and Maemo, for which I
 wrote an <a href="@@RELPATH@@mksh.htm">mksh</a> package in a <a
 href="https://garage.maemo.org/projects/mksh/">garage project</a>,
 which also needs some love w.r.t. testing on actual devices, menu
 integration, etc. (Please contact me if you can help with either of
 the three.) We also have <tt>«lewellyn:#ksh»</tt> making a package
 for the new OpenSolaris system (thanks again). People persuading
 Apple to put it on the jesusPhone are also welcome. (This does not
 mean I endorse any of these &ndash; right now, I'd probably get the
 most of a WinCE PDA with built-in GPSr, WLAN and maybe GSM/GPRS.)</p>
<p>English and French native speakers, please review, and Dutch native
 speakers may contribute a translation of, our <a
 href="@@ABSPATH@@/MirOS/PR/">flyers</a>. (Source code for these is
 <em>not</em> available, sorry. Benny makes them in Quark on System 7
 in Basilisk II, used to be Classic until Apple yanked it. But still,
 they use only free fonts, free imagery or such the MirOS Project is
 allowed to use, and beat every single other FOSS project flyer I've
 ever seen by far!)</p>
<p>There's probably more I could write, I bet I forgot half of it
 anyway, but I'll leave it at that for now. Get yourself a nice cup
 of hot chocolate, pour an Espresso into it, and enjoy the mix with
 a piece of cake (I'd say strawberry or mousse-pear but all they had
 was cassis-créme) and pity me for not knowing any French next month.</p>
----
Title: To do.
Author: tg@
Date: 28.01.2010 21:20
Tag: debian event mksh

<p><a href="http://www.fosdem.org/"><img alt="I’m going to FOSDEM, as usual"
 src="http://www.fosdem.org/promo/going-to" /></a></p>
<p>The MirOS Project will have a booth at FOSDEM 2010, business as usual.
 If you thought otherwise, you’re crazy ☺</p>
<p>I know I should write a wlog entry about the BSP, write more, release <a
 href="@@RELPATH@@mksh.htm">mksh</a> R40, fix the TaC of it and the <a
 href="@@RELPATH@@kwalletcli.htm">kwalletcli</a> webpage (thanks again, it’s
 now in Debian sid!) etc.pp but I also need to prepare an ISO for FOSDEM, etc.
 Heck, I should prepare a talk for FOSDEM, but I’m not going to. If I need to
 stand there and talk, I’ll talk, not hold a presentation. I’ll just see what
 people are interested in, talk about The MirOS Project, and improvise.</p>
<p>I’m busy, and there’s only so much computing you can do in a day. This
 does include the dayjob. At least, my NMUs are in Debian now and probably
 can help people (and I submitted info about other bugs too).</p>
<p>Anyway, watch the news in the months to follow… can’t talk about everything
 now.</p>
----
Title: new snapshot (netinstall) uploaded
Author: tg@
Date: 30.01.2010 22:39
Tag: snapshot

<p>The 2010-01-30 snapshot was uploaded to <tt>/MirOS/current/</tt> with
 i386 (actually had to restart due to cid 1004B6372DA2A612787, then manually
 incorporate cid 1004B6448D51D101C96 and re-do the floppy, and then, cid
 1004B64C58E652566A6+1004B64C5FC627C5254 and especially 1004B64D0994DA8A990
 are still not honoured), sparc (built 2010-01-25 though), MirOS bsd4grml
 and MirOS bsd4me (with another number of commits). If I had more time,
 I'd probably rebuild them both. As things are, I consider pimping all
 four of {i386,sparc}/{,x}etc10.ngz before making the FOSDEM Live-ISO.
 Maybe even put the re-built boot.fd into base10.ngz and re-do all of the
 ramdisk kernels, floppies and CDs. Ugh.</p>
----
Title: Hello, Debian!
Author: tg@
Date: 31.01.2010 02:05
Tag: debian

<p>I got an eMail tonight. I guess <a
 href="http://bzr.debian.org/loggerhead/keyring/debian-keyring/revision?start_revid=385&amp;filter_file_id=keyids-20091117093835-z3pjruc5aae10oh7-1">this</a>
 means I can say hello officially now. (Everything else is details, waiting
 and fixing some bugs and technicalities, or so.) Thanks to everyone involved,
 I learned a lot already. Oh, and I had a look into madduck's book (the old
 sarge edition, which I got for free recently) and found a nice graphic
 explaining what non-native English speakers (I even had Latin first, and 3
 programming languages!) don't, from the Debian constitution.</p>
<p>Congratulations <a href="http://fsinfo.cs.uni-sb.de/~abe/Links/">XTaran</a>
 for making it as well, even visible on the website already!</p>
<p>Please don't file an "Please package mksh R39b" bug again, I am aware
 there's a new version ;-) as I'm upstream too. I'm just short of time at
 the moment, and I'd like to put out high-quality packages. Besides, the
 webpage needs fixing first (while the checksums and the changelog for the
 release are there, no proper announcement is yet, and I'd like, for this
 version, to add a "upgrading caveats" section, since due to bugfixes and
 better standards compliance some scripts need to be updated; some of the
 pdksh behaviour favoured Bourne over POSIX even!</p>
----
Title: FOSDEM 2010, day #0
Author: tg@
Date: 05.02.2010 13:37
Tag: debian event

<p>Yesterday, I arrived in Bruxelles, coming from the Issy/Paris <a
 href="https://fusionforge.org/mediawiki/index.php/2_days_Hackers/users_meeting_in_Paris%2C_2010-02-03_and_04">FusionForge
 meeting</a> which will be described more later by Roland on <a
 href="http://www.planetforge.org/planet/">Plänet Forge</a>. Please <a
 href="http://www.ohloh.net/p/fusionforge">tell Ohlol if you use it</a>,
 for more visibility.
</p>
<p>There is a new inter-forge mailing list as well, see the <a
 href="http://lists.planetforge.org/cgi-bin/mailman/listinfo/discussions">info
 page</a>. People from Coclico and the various *forges may want to
 subscribe there (forge developers, not so much users (hosters) or
 end-users (hosted project developers/users) though).</p>
<p>At FOSDEM, Benny and I (and maybe gecko2) will be running the <a
 href="@@RELPATH@@main.htm">MirBSD</a> booth, so no Debian staffing
 for me, sorry. But I will be there. Also please do ask me about <a
 href="@@RELPATH@@mksh.htm">mksh – the MirBSD Korn Shell</a> etc.</p>
<p>There are flyers in <a
 href="@@ABSPATH@@/MirOS/PR/flyer_de.pdf">German</a> (not updated), <a
 href="@@ABSPATH@@/MirOS/PR/flyer_en.pdf">English</a> and <a
 href="@@ABSPATH@@/MirOS/PR/flyer_fr.pdf">French</a> too! (One of
 the *forge guys did install mksh(1) after reading it, in fact.)</p>
<p>Don't you people dare miss the two talks: from Benny about <a
 href="http://fosdem.org/2010/schedule/events/bsd_autotools">how to
 package with autotools and libtool correctly</a> and from <a
 href="http://fsinfo.cs.uni-sb.de/~abe/Links/">XTaran</a> explaining <a
 href="http://noone.org/blog/English/Computer/Debian/abe%2540debian.org.html">Debian
 GNU/kFreeBSD</a>. Benny's also famous for his talk about <a
 href="http://www.slideshare.net/bsiegert/painless-perl-ports-with-cpan2port">Painless
 Perl Ports</a> with cpan2port; XTaran's famous for a whole bunch
 of other <a href="http://www.symlink.ch/">things</a>.</p>
<p>I still have some catching up (wlog entries, keysigning, webpages,
 etc.) to do, please bear with me. I don't really have a proper work
 environment with me.</p>
<p>There's a chance I will not be attending the Beer Event in the
 Delirium Tremens café (last year's still remembered). Benny will
 certainly be there, though.</p>
<p>Could someone please order nice weather? I still need to eat some
 lunch and find a supermarket to shop for the weekend!</p>
----
Title: FOSDEM 2010, day #2
Author: tg@
Date: 07.02.2010 14:06
Tag: event
Language: de-DE-1901

<p>Ich glaube, das Essen gestern (war eh’ scheiße, heh… anyway, der
 Couscous-Laden hatte zu, und Benny und gecko2@ und Anhäne haben mich
 zum Inder geschleppt) ist schuld, daß es mitr im Moment scheiße (heh…)
 geht. Mist.</p>
<p>Ich freue mich schon auf das Essen gleich, hoffe, daß es frischen
 Minztee in großen Mengen geben wird. Und daß ich die Reise nach Hause
 unbeschadet überstehen werde. Immerhin haben wir gut, aber zu wenig ☺
 wie immer… geschlafen.</p>
<p>XTaran hält gerade seinen Vortrag. Dem Benz seiner war gut.</p>
----
Title: After FOSDEM 2010
Author: bsiegert@
Date: 08.02.2010 17:39
Tag: event

<p>FOSDEM was a great success. Once more, thanks to Daniel Seuffert,
 Marius N&uuml;nnerich and the others from <a
 href="http://www.allbsd.de/en/">the AllBSD project</a>. We distributed
 400 CDs with the latest snapshots, of which about 350 were distributed
 on Saturday alone. There was a stronger demand for French flyers
 compared to the last years; I think that more locals (i.e. Belgians)
 attended the conference. Many of these people were only there on one of
 the two days.</p>

<p>Kudos also to the people from the Debian booth (especially Axel
 “XTaran” Beckert) for lending us a screen for the showcase computer.
 Due to communication problems, the others had not brought a spare
 screen as usual, and I could not bring one on the plane.</p>

<p>I held my talk about <i>Build Systems with autoconf, automake and
 libtool</i> on Sunday at noon, with a very interested public who posed
 some very concrete question. I conclude that there is a real need for
 this kind of “HOWTO”. I will write a bit more on the subject of
 autotools, in the meantime the slides are <a
 href="http://www.slideshare.net/bsiegert/build-systems-with-autoconf-automake-and-libtool">available
 at SlideShare</a>, where you can view the presentation online (Flash
 required) or <a
 href="http://www.slideshare.net/bsiegert/build-systems-with-autoconf-automake-and-libtool/download">download
 a PDF</a>.</p>

<p>Oh, and contrary to “popular” belief, the food at the Pakistani (!)
 restaurant on Saturday was excellent :).</p>
----
Title: the day after FOSDEM
Author: tg@
Date: 08.02.2010 17:10
Tag: event
Language: de-DE-1901

<p>Bauch wieder OK, dafür nen recht wehtuënden Frosch im Hals,
 Hammerkopfschmerzen, Rückenschmerzen und bißchen Gliederschmerzen.
 Grml. Ich mach' im Moment erst mal nix.</p>
----
Title: Rant about PGP keysigning problems
Author: tg@
Date: 23.02.2010 22:29
Tag: debian mksh rant

<p><strong>Update</strong>: This wlog entry uses aggressive tone
 because I somehow needed to vent frustration from using some of
 the tools. I should probably provide some constructive critics,
 too... but this is a rant. Be warned.</p>
<p>Keysigning is useless. I boot up <a href="http://grml.org/">a
 suitable live GNU/Linux system</a>, install signing-party, take
 the trouble that is to set up caff, transfer my secret key from
 the <a href="@@RELPATH@@main.htm">secure box</a>, sign. I think
 caff providing the keys in a different order than they're given
 on the command line sucks and just run caff once per key. I did
 even start Postwreck. But no, people just don't accept any mail
 from "EHLO grml" systems, and I still cannot control my reverse
 DNS despite having a static IPv4 address (and IPv6, which looks
 to be unused). People also pretend I'm on dial-up. Great!</p>
<p>I will no longer participate in any (mass) PGP keysigning but
 will continue to do so on a per-person basis. Probably sign but
 one <tt>uid</tt>, either apply common sense and upload it to <a
 href="http://blackhole.pca.dfn.de:11371/">t̲h̲e̲ keyserver</a>, or
 mail the entire signed key to one address.</p>
<p>By the way, how crazy is it that I need to use the deprecated
 <tt>$CONFIG{'mailer-send'}</tt> to pass an envelope-from to the
 mailer? It also suffers from the same delusion as e.g. nmudiff,
 namely that my Debian box is a fully set up workstation able to
 send out eMail and configured correctly. At least, it, unlike a
 number of others, does not assume I use mud (Mutt). grml…</p>
<p>Oh, and caff does a protocol violation (by always sending out
 GnuPG/MIME and not offering the standardised Inline OpenPGP), I
 think people just don't   care about such. (There is a notation
 people can use to signal they want PGP/MIME, Inline PGP – which
 is called "partitioned" – or both (and which order of priority)
 but, alas, despite Inline PGP being the only one useful for the
 MUAs without integratin, and being more widely spread than that
 PGP/MIME crap, the followers of the latter do some (FSF-style?)
 kind of vendor lockin by not speaking anything else.</p>
<p>Anyway. I'm all for X.509 except there seems to be no sane CA
 (Startcom is... trouble, even with Opera; CAcert.org is dying).
 I'll just buy a certificate (not from Verisign though) for www,
 and roll <a href="@@RELPATH@@ca.htm">my own</a> again (I can do
 it, I have experience with that actually).</p>
<p>On an unrelated side note, still waiting for an OpenSSL patch
 for that recent TLS extension...</p>
<p>ObRant: password policies, be they required characters or any
 kind of length restrictions, suck. People I will eventually end
 up with <strong>less secure passwords</strong> on such systems,
 because even if some of mine may appear to be derived from some
 kind of dictionary (what language that is I'd be interested in,
 though...) they aren't, and I have my scheme<em>s</em>. You got
 to have them with a gazillion of passwords used. And I probably
 will forget them more often (and sending them via eMail is also
 not a solution).</p>
<p>Unrelated notice: <a href="@@RELPATH@@mksh.htm">mksh</a> R39c
 with bug fixes coming RSN.</p>
<p>(Updated 24.02. because I was, rightfully, told the language,
 and the title, were too strong. I also would like to excuse for
 going so low as to write an ad-hominem attack, which I've since
 redacted.</p>
----
Title: CLI for the KDE Wallet • 2.02
Date: 03.03.2010 11:43
Author: tg@
Tag: debian news

<p>The <a href="@@RELPATH@@kwalletcli.htm">Command-Line Interface
 for the KDE Wallet</a>, Version 2.02, has been released and dput
 into Debian unstable. (The lenny-backports version will follow.)
 It took me quite a while to reproduce, then track down, the bug;
 having unrelated problems at the same time didn’t help either…</p>
----
Title: On ranting...
Date: 04.03.2010 17:55
Author: tg@
Tag: debian

<p>Yes, my rant was more against the things I encountered during
 keysigning, not keysigning itself. However, I still feel X.509
 doesn't have these problems, and nothing I can think of will
 persuade me to think PGP/MIME better than Inline PGP. (Especially
 when the recipient's key contains a notation that he wants the
 latter, but not the former.)</p>
<p>Jonathan does have some good points about the (PGP) Web of Trust.</p>
<p>Again, that wlog entry of mine was a rant; I had let the topic
 stew over night, trying to get the anger out, but on the next
 day it just wanted to get out of me, I merely wanted a good old
 rant. I think I'll not include Planet Debian next time I <em>do</em>
 rant, though (it's not the place to do so).</p>
----
Title: RCBD #2
Author: tg@
Date: 04.03.2010 19:55
Tag: debian

<p>My ex-AM now sort-of mentor Zack asked for help of an Autoconf/Libtool
 guru with an RC bug... well, <a href="@@RELPATH@@ports.htm">The MirPorts
 Framework</a> taught benz and me, under consumption of a bottle of wine,
 how to deal with that stuff. So I've fixed <a
 href="http://bugs.debian.org/559822">#559822</a> (CVE-2009-3736, another
 of them...) and NMU'd.</p>
<p>Sort of a PITA, considering gettextize runs interactively, and there's
 a lot of files to remove in debian/rules:clean for a double-build to not
 add nonsensical files to the .diff.gz; but I did it in the end.</p>
----
Title: CLT 2010
Author: tg@
Date: 07.03.2010 01:01
Tag: debian event news

<p>Quite surprisingly, I’ll attend the Chemnitzer Linuxtage 2010 in Eastern
 Germany. This is a happenstance, I managed to get fast transportation (via
 my boss) and accomodation (in a hotel). I will try to help staffing the <a
 href="http://wiki.debian.org/DebianEventsChemnitzerLinuxTage2010">booth of
 Debian</a> this time (so I cannot be called Traitor any longer). Schedule,
 due to the spontaneousness of this, no, though. I may not even be there on
 Sunday, dunno…</p>
<p>No RCBD (or night) though, some real life and a new release (with fix of
 an FTBFS-on-hurd-i386 bug) though:<br />
 RMD160 (<a href="@@ABSPATH@@/MirOS/dist/mir/makefs/makefs-20100306.tar.gz">/MirOS/dist/mir/makefs/makefs-20100306.tar.gz</a>)
 = f65bd8ef5cf3306a9112587dd4915b6255e479fe<br />
 This version pulls in NetBSD® changes (Acorn Archimedes support, for one),
 but I’ve also coded support for boot-info-table (J�rg compatible), as well
 as setting the PVD dates (used by GNU GRUB 2 for “UUID”s).</p>
<p>On MirBSD, cdio(1) can now be used to burn (TAO) and blank (quick) CD-RW
 media (I backported some OpenBSD changes) too.</p>
----
Title: Go
Author: bsiegert@
Date: 02.04.2010 19:05

<p>Today was a fine day, which I spent at the excellent <a
 href="http://www.zoo-mulhouse.com/">Zoo de Mulhouse</a>. Alas, most of
 the plants there are still in “winter mode”.</p>

<p>Recently, i mentioned in a thread on reddit that Limbo (under
 Inferno) is “my favorite obscure programming language”. Someone else
 replied that “it is now called Go”. This led me to take a look at the
 <a href="http://golang.org">Go programming language</a> made by Google.
 Sure enough, there are big names behind it: Rob Pike and Ken Thompson,
 of Unix (and Plan9) fame, and also Russ Cox, one of the most prolific
 Plan 9 fans.</p>

<p>When you compile Go, the first thing that is built is a lib9, which
 contains Plan 9 code, such as the rune routines for UTF-8. The Go
 compiler is derived from kencc. For the 386 architecture (the one I
 tested), you get <tt>8g</tt> (Go), <tt>8c</tt> (C), <tt>8l</tt>
 (linker) and <tt>8a</tt> (assembler). For the record, there is also a
 Go compiler using gcc, which is able to call C code.</p>

<p>Leaving obvious syntax differences aside, Go indeed resembles Limbo
 quite closely. There is no first-class list data type however, and
 there exists a curious difference between arrays and slices. Slices are
 some sort of pointer to (part of) an array. Arrays are passed by-value
 to functions while slices are passed by reference, it seems. There is
 also an associative array type that maps one data type of your choice
 to another, for example a string to an int. Other Limbo niceties, such
 as easy string manipulations, are also present.</p>

<p>The first thing I tried was porting a scientific program I had
 written in Limbo before. The math module looks almost like its
 counterpart in Inferno but is missing the gemm() function (generic
 matrix multiplication) from BLAS3. Thus, I ported it from the Inferno
 sources, where gemm() is written in C. (By the way, that code looks like
 it has been ported from Fortran 77.) Porting from C just involves
 removing a few parentheses (in if and for clauses) and semicolons (just
 about everywhere).</p>

<p>I have not explored it much further yet. But it does look very
 interesting for system programming and similar things. The only thing
 missing now is a MirPort ...</p>
----
Title: Upcoming migrations
Author: tg@
Date: 03.04.2010 17:27

<p>I finally managed to move my arse and buy a new Socket 7 CPU fan
 for <tt>herc</tt>, two new 160 GB IDE HDDs for <tt>tear</tt>, and
 plan a number of other migrations. Within the next time, the SSL
 certificates will be renewed (changed away from CAcert to some as
 of yet undefined CA for the main (web)server and to ca.mirbsd.org
 for the secondary services), <tt>www</tt> will possible move to a
 dedicated box, <tt>cvs</tt> from <tt>herc</tt> to <tt>tear</tt>
 for sure though. I’m at gecko2@’s place right now though, so it’ll
 take a while more (obviously). I’ll take the chance to re-design
 a number of things during the process and clean up old, no longer
 used things, as well.</p>
<p>I know I should probably have written something about CLT (it
 was great, except for the social event, which confused everyone
 about the who where etc. and I had a headache and the sounds they
 provided (no music…) didn’t help either, but it was planned and
 exercised very well and much cleaner than ULB too ☺) and that I
 managed to do two geocaches in East Germany… and a plethora of
 other things (I did staff the Debian booth, there were neither a
 MirBSD nor FreeWRT booth after all; there is interest in makefs(8)
 but the 31/32-bit limit must go; etc). I’ve had a demanding three
 weeks at work though, and I’ll probably not write much content for
 the website anyway any more, but I’ll try to get more hacking done.
 <a href="@@RELPATH@@mksh.htm">mksh</a> got more POSIX compliance,
 and we’re discussing about the things on the Austin Group mailing
 list. I’ll be writing a bootloaderloader for mika and Grml, with
 special consideration for a blind user. I need to get screws, RAM,
 a hard disc and a PSU for my new Cobalt Qube2 and put Debian on it
 to debug things. I plan to buy the upgrade kit (to 20 MiB RAM) and
 a new battery for <tt>nwt</tt> (and use glue to put the broken-off
 edge back there) just like I started renovating my hardware pool.
 OpenSSH needs an import, others may need work. So, I’ve got a TODO
 longer than a lifetime, so I get to pick my things ;-)</p>
<p>There will not be a MirBSD booth at LinuxTag in Berlin. If I’m
 going (even that’s not sure), I join a shared AllBSD booth, which
 seems to not happen, or… bsiegert@ will be at some conference for his
 Chemistry stuff again, and it’s too far for gecko2@ to attend, so
 I would’ve been alone anyway. At FrOSCon, though, we’ll be sure to
 happen (I’m even trying to cobble together a FreeWRT booth again,
 but there are not enough volunteers coming who aren’t expected as
 another booths’ staff).</p>
<p>gecko2@ upgraded ports/editors/nano and desired documentation,
 possibly in the form of a tutorial, on how to do it. And I hope
 bsiegert@ will remember that Google’s “Go” is the second one of
 that name and use something like ports/lang/google-go (on second
 thought, a company name in a directory is bad too). And there’s
 kencc in ports already so I’d like an Inferno port first.</p>
<p>ciruZ said that Syllable is pretty much dead… sad, since mksh
 now works on <a href="http://www.haiku-os.org/">Haiku</a> and
 both Syllable and Plan 9 had similar issues with it, so I was
 hoping we could get them fixed… (bsiegert@ is our resident Plan 9
 expert, so I need to push him into looking at it.) Speaking of
 MirWorldDomination, <tt>/system/bin/sh</tt> on Android-x86 is an
 mksh(1) already ☺</p>
----
Title: New pkgtools stuff
Author: bsiegert@
Date: 13.05.2010 18:42

<p>The <i>bsiegert-cfgfile</i> branch of the MirPorts package tools is
 coming along nicely. Today I committed a patch to info/perform.c that
 puts its logic from the head on its feet, making the function more
 readable and, incidentally, getting rid of two gotos. The header of the
 information has become a little more informative. Watch:</p>

<pre><code>% pkg_info foo
pkg_info(foo): cannot find package 'foo' installed or in a file!

% pkg_info tiff | head -4
Information for tiff-3.7.4-1 (installed):

Comment:
library routines for working with TIFF images
</code></pre>

<p>Something new that I got working is support for giving the name of an
 uninstalled package in a repository mentioned in the new
 <tt>/etc/pkgtools/pkgtools.conf</tt> file. This works for both local
 and remote repos:</p>

<pre><code>% pkg_info tiff-cxx | head -4
Information for /usr/ports/Packages/tiff-cxx-3.7.4-1.cgz:

Comment:
C++ API for working with TIFF images

% pkg_info mc | head -4
>>> ftp -o - http://www.mirbsd.org/MirOS/Pkgs/current/i386//mc-4.6.1-16.cgz
Information for /var/folders/Xk/XkVpSyd8F0WZnoK9NwgsWU+++TI/-Tmp-//instmp.4OV2INPVOK:

Comment:
free Norton Commander clone with many useful features
</code></pre>

<p>Actually, in the last case, the output could be improved some more
 :). You can also give it a package specification such as "tiff->=3.0".
 If more than one package matches the specification given, then a menu
 is displayed from which you choose one. This happens, for instance, if
 you have an older version built locally and a newer version of the
 same package in a remote repo, or if several flavours of the package
 are available.</p>

<p>The changes are not in the HEAD branch yet, I will merge them when I
 consider it "done".</p>
----
Title: Hello, World!
Author: tg@
Date: 22.05.2010 14:37
Tag: mksh

<p>Just a random status update: I’ve been too busy with the dayjob,
 now ill for about two weeks already. There have been some minor <a
 href="@@RELPATH@@mksh.htm">mksh</a> fixes but I’d still like to
 catch up on the Austin ML postings before releasing R39d; Android
 discussion is live. The base system has some issues found, but I
 will take a while (no hacking mood, even when not ill).</p>
<p><a href="https://eurynome.mirbsd.org/~tg/pub/qr.htm">Scan this!</a>
 and Google’s playable logo is just weird (at least no sound in
 Opera) but at least it’s not Fläsh. I played it but there’s no
 second level. Tonnerre likes «Forth op de Fiets» (as a pun on
 Ruby on Rails), which lets me remember the Forth Glockenspiel.</p>
<p>Sorry for the lack of updates, but MirBSD is still pretty much
 a fun project, and Benny is working on his Doctor thesis too.</p>
<p>FWIW: <a href="http://www.golem.de/1005/75291.html">Patents</a>
 on <a href="http://www.golem.de/1005/75277.html">software</a> are
 <a href="http://www.golem.de/1004/74727.html">evil</a> and times
 <a href="http://www.golem.de/0703/50844.html">are worsening</a>.
 I suppose, if we’ll be able to continue MirBSD at all, I need to
 disable FAT LFN support. Sucks.</p>
----
Title: Cancelling bash, retrieving a command, mksh rules :þ
Author: tg@
Date: 23.05.2010 15:08
Tag: debian mksh

<p>In response to a <a href="http://planet.debian.org/">planet.d.o</a>
 series (mentioned in <tt>#grml</tt> on IRC) of <a
 href="http://womble.decadent.org.uk/blog/cancelling-a-command-in-bash">posting</a>s:
 In a sensible shell, <tt>Esc+#</tt> not only pushes it back but also
 re-enables the command. Try it out: <tt>l</tt> <tt>s</tt> <tt>Esc</tt>
 <tt>#</tt> <tt>Cursor-Up</tt> <tt>Esc</tt> <tt>#</tt></p>
<pre>
tg@blau:~ $ #ls
tg@blau:~ $ <span class="u">l</span>s
</pre>
<p>The command sticks in the history, and is not immediately shown in
 the next interactive input line, which I consider a plus in most use
 cases. Anyway, try <a href="@@RELPATH@@mksh.htm">mksh</a> (just a-g
 i it), there are a lot of goodies. I found out about Ctrl-O only a
 year or so ago myself…</p>
<p>I wonder why schizo didn’t write about how to do it in posh tho ☺</p>
----
Title: odem is dead
Author: tg@
Date: 17.06.2010 19:58

<p>My laptop <tt>odem</tt> has a somewhat split personality… half of
 it ended up in the waste bin, the other half will probably end up
 being sold under price to someone who may then sell the parts separately
 from each other (I’m not in the mood to do packaging and shipping).
 Salvaged parts: some PC133 SO-SDRAM (probably 512 and 256 MiB), an
 Athlon XP 1400+ CPU, an Acer Aspire 1300XC(?) BIOS, floppy drive,
 DVD-ROM/CD-RW drive, complete display (panel, inverter and chassis),
 CMOS battery, a lot of screws, the fan, some cables, the upper half
 of the chassis, the keyboard, and probably other things.</p><!-- RSS stop -->
<p>In case someone noticed: the <a href="@@RELPATH@@mksh.htm">mksh
 web page</a> now looks nicer, and it’s even mentioned in some <a
 href="http://forums.freebsd.org/showthread.php?p=88087">forum
 thread</a> as the “popular” shell ☺</p>
<p>Mojito tastes good… we had a soldering social evening at $orkplace
 followed by an ad-hōc visit to the cocktail bar due to missing the
 tram (caught the next one). Summer’s gone again though… rain really
 is imminent now ☹</p>
<p>This wlog entry is presented you by gecko2@’s nagging… we’re
 really working though, so don’t expect many… I’m even doing the
 Debian stuff only at ork at the moment.</p>
----
Title: LSM/RMLL; mksh R40, R41 plans
Author: tg@
Date: 05.07.2010 20:54
Tag: bug debian event mksh

<p>The current version of <a href="@@RELPATH@@mksh.htm#clog">mksh</a>
 had use of arc4random(3) removed, including “set -o arc4random”, to
 speed it up (on some architectures, a lot) – this <em>will</em> break
 some existing scripts (such as <tt>/etc/rc</tt> *cough* on MirBSD…).
 Hence I decided to publish the next version of mksh(1) as R40 based
 upon current development, and defer plans for associative arrays (and
 multidimensional arrays) for mksh R41. There’s also already the change
 to <tt>Build.sh</tt> arguments, so this suits me quite fine.</p>
<p>(Read: if running MirBSD, don’t upgrade mksh at the moment.) There
 will be a new MirBSD snapshot once this is fixed, maybe a few more
 changes to the shell for better POSuX compliance, and the recently <a
 href="@@RELPATH@@permalinks/wlog-10_e20100522-tg.htm">mentioned</a>
 patent on LFNs (long filename) in FAT will be taken into account with
 a patch to msdosfs.</p>
<p>I’ll travel to <a href="http://2010.rmll.info/">LSM/RMLL 2010</a>,
 the Libre Software Meeting (<span xml:lang="fr">Rencontres Mondiales
 du Logiciel Libre</span>) tomorrow until the weekend, to hack some on
 FusionForge (this <em>is</em> worktime for me), visit XTaran, Uriel,
 and maybe a couple of other “usual people”.</p>
<p>Thundersday, between 10:00 UTC and 12:00 UTC, <tt>eurynome</tt> will
 be shut down by gecko2@ due to power supply maintenance on the host
 system data centre.</p>
<p>We have a new mirror in the Americas, thanks a lot to Mike 'Fuzzy'
 Partin! Benny will mention it on the webpages once it’s working.</p>
----
Title: Back home
Author: tg@
Date: 11.07.2010 12:18
Tag: bug debian event geocache mksh news release snapshot

<p><a href="http://2010.rmll.info/">Bordeaux</a> was very nice (and
 towards the end much cooler… it’s actually hotter here at more than
 50½° north – too warm to think, or do anything) but the LSM/RMLL was
 very french. They’ll be in Straßburg and Lüttich the next two years
 so we can probably be expected to attend. I don’t think I can eat
 duck (which, in south-west france, is a vegetable) or like all that
 classic french multi-course food so much, but I had enough Couscous
 Merguez and Thé à la menthe fraîche… and similar good stuff. Many
 people spoke English and actually asked me whether I do (probably
 they couldn’t bear me trying to spea^W^W^Wbutchering the language
 of the Grande Nation) and in general were a friendly bunch. I did
 see some people with machine guns in the city on the last day,
 though. No idea what/why… didn’t dare asking ☻</p>
<p>Just another reason to boycott flying: Mario Lang (one of the
 speakers) was apparently held on the airport and treated as a
 terrorist due to his Braille line… they thought it was a bomb or
 somesuch thing.</p>
<p style="font-size:small">Read on for more…</p><!-- RSS stop -->
<p>Travelling with the Thalys and TGV was nice (but I loathe the
 Métro parisienne… they should build a ring train like the Berlin
 S-Bahn and just put another stop before Paris Nord and Montparnasse
 for people who just want to switch trains to take the ring train to
 the other line). And I want air conditioned trams in Germany too!</p>
<p>I met Uriel (invited him for some food and talked lengthy with
 him and some 9grid guy), XTaran (who was rather busy organising
 things), and a number of other people. Did some PGP keysigning as
 well. There’s now an experimental MirOS presence at Launchpad, not
 sure what exactly we’re going to do with it but, as Canonical does
 not care (as Jonathan said in his talk – <em>great</em> slides, by
 the way, really impressive), there’s no harm in having it. Some Perl
 guy from America (USA… just to make sure ☺) wanted a photograph of
 me with a sign “I love CVS” just so people back at home would believe
 him he’s met such a person *grins* of course I plugged in a little
 advertising but cvs(GNU) is honestly good. The forge hacking session
 was a little under-visited (but still a success in terms of getting
 more communication and maybe collaboration underways, especially
 thinking of common interfaces, DC, semantic web, OSLC-CM) and since
 the room was (in contrast to my hotel room and the trams!) not air
 conditioned we didn’t get much hacking done. The Debian booth was
 about 40% of one FOSDEM style table wide… and subsequently crowded.
 There were more people (of course, I was trying to get <a
 href="@@RELPATH@@mksh.htm">mksh</a> into Haikuports, Mandriva, and
 other things; talked about KDE 3.5.11 (Trinity), Qt 3 vs Qt 4, and
 <a href="@@RELPATH@@kwalletcli.htm">kwalletcli</a>, and in general
 to a not-so-usual bunch of suspects – like I said, LSM/RMLL really
 is pretty french-only).</p>
<p>It <em>is</em> too hot, but I still committed <tt>src/etc/rc,v</tt>
 version 1.110 which you <strong>want to upgrade your <tt>/etc/rc</tt>
 to</strong> before upgrading mksh(1) in MirBSD. (All in the name of
 better performance on platforms such as Debian/m68k and not raiding
 Linux’ inferior RNG… but it does simplify things.)</p>
<p>I could probably write more but at the moment just want to lie
 down and die until it gets cooler… even the rain didn’t help. My
 feet hurt (Montparnasse-Bienvenue didn’t help) too.</p>
----
Title: On ASLR (Address Space Layout Randomisation)
Author: tg@
Date: 12.07.2010 20:28
Tag: debian mksh

<p>I’ve got some interesting results using r1.1 of an example <a
 href="@@RELPATH@@cvs.cgi/contrib/hosted/tg/testaslr.c">test
 programme</a> (r1.2 got cleaned up and more output) on various
 systems, regarding ASLR. The 1.1 revision tests everything <a
 href="@@RELPATH@@mksh.htm#clog">mksh</a> R40+ will use (except
 there will probably no larger than page sized allocations) for
 its LCG PRNG. On OpenBSD (MirBSD, ÆrieBSD) malloc(3) uses <a
 href="http://www.openbsd.org/papers/auug04/mgp00005.html">in
 fact</a> mmap(2), which is randomised. (Though <tt>-pie</tt>
 doesn’t yet work as it’s supposed to.) Some OSes are better
 than others… but look for yourself. (Read on to continue, not
 part of the RSS for size reasons. This wlog entry may be updated
 – with bumped date – unperiodically.)</p><!-- RSS stop -->

<h3>MirBSD-current/i386</h3>
<pre>tg@blau:~ $ mgcc -static x.c
x.c:0: note: someone does not honour COPTS correctly, passed 0 times
x.c: In function `foo':
x.c:27: warning: function returns address of local variable
tg@blau:~ $ ./a.out
0xa9332000 0xaba65000 0xa0ae7000 0xcfbed990 0xcfbed994
tg@blau:~ $ ./a.out
0xa91b4000 0xa02b1000 0xa1602000 0xcfbf8680 0xcfbf8684
tg@blau:~ $ ./a.out
0x9f731000 0x9cb2a000 0xa94ca000 0xcfbf5840 0xcfbf5844
tg@blau:~ $ ./a.out
0x9c2af000 0xa6a0b000 0xa4ce1000 0xcfbefac0 0xcfbefac4
tg@blau:~ $ ./a.out
0xa3b61000 0xa96de000 0xa96df000 0xcfbedcc0 0xcfbedcc4</pre>

<h3>Debian Ätsch/i386</h3>
<pre>tg@frozenfish:~ $ gcc -static x.c
x.c: In function ‘foo’:
x.c:27: warning: function returns address of local variable
x.c: In function ‘bar’:
x.c:33: warning: function returns address of local variable
tg@frozenfish:~ $ ./a.out
0x80b2a20 0x80b2a30 0xb7745008 0xbf985ce0 0xbf985cd4
tg@frozenfish:~ $ ./a.out
0x80b2a20 0x80b2a30 0xb7726008 0xbfb911b0 0xbfb911a4
tg@frozenfish:~ $ ./a.out
0x80b2a20 0x80b2a30 0xb7784008 0xbf83d040 0xbf83d034
tg@frozenfish:~ $ ./a.out
0x80b2a20 0x80b2a30 0xb77e8008 0xbfc0f840 0xbfc0f834

tg@frozenfish:~ $ sid
I: [sid chroot] Running command: “mksh -l”
tg@frozenfish:~ $ gcc -static x.c
x.c: In function ‘foo’:
x.c:27: warning: function returns address of local variable
x.c: In function ‘bar’:
x.c:33: warning: function returns address of local variable
tg@frozenfish:~ $ ./a.out
0x80c86a8 0x80c86b8 0xb77c3008 0xbfaa1900 0xbfaa18f4
tg@frozenfish:~ $ ./a.out
0x80c86a8 0x80c86b8 0xb77d2008 0xbfcc0260 0xbfcc0254
tg@frozenfish:~ $ ./a.out
0x80c86a8 0x80c86b8 0xb77c1008 0xbfbe2120 0xbfbe2114</pre>
<p>uname: Linux frozenfish 2.6.18-6-686 #1 SMP Fri Feb 19 23:40:03 UTC 2010 i686 GNU/Linux</p>

<h3>Solaris 8/sparc64</h3>
<pre>tg@stinky:~ $ gcc -static x.c
x.c: In function `foo':
x.c:27: warning: function returns address of local variable
tg@stinky:~ $ ./a.out
595f0 59bf0 59d00 ffbefbb4 ffbefb5c
tg@stinky:~ $ ./a.out
595f0 59bf0 59d00 ffbefbb4 ffbefb5c
tg@stinky:~ $ ./a.out
595f0 59bf0 59d00 ffbefbb4 ffbefb5c
tg@stinky:~ $ gcc x.c
x.c: In function `foo':
x.c:27: warning: function returns address of local variable
tg@stinky:~ $ ./a.out
20950 20f50 21060 ffbefb3c ffbefae4
tg@stinky:~ $ ./a.out
20950 20f50 21060 ffbefb3c ffbefae4</pre>

<h3>MidnightBSD/amd64</h3>
<pre>mirabilos@stargazer:~ $ gcc -static x.c
x.c: In function 'foo':
x.c:27: warning: function returns address of local variable
x.c: In function 'bar':
x.c:33: warning: function returns address of local variable
mirabilos@stargazer:~ $ ./a.out
0x800603080 0x800605040 0x800700000 0x7fffffffe62c 0x7fffffffe62c
mirabilos@stargazer:~ $ ./a.out
0x800603080 0x800605040 0x800700000 0x7fffffffe63c 0x7fffffffe63c
mirabilos@stargazer:~ $ ./a.out
0x800603080 0x800605040 0x800700000 0x7fffffffe62c 0x7fffffffe62c</pre>
<p>uname: MidnightBSD stargazer.midnightbsd.org 0.3-CURRENT MidnightBSD 0.3-CURRENT #1: Thu May 27
22:13:45 EDT 2010     root@stargazer.midnightbsd.org:/usr/obj/usr/src/sys/GENERIC  amd64</p>

<h3>Debian sid/mipsel</h3>
<p>(QEMU, thanks to Aurélien! Debian unstable from approx. Jan 2010)</p>
<pre>root@debian-mipsel:~ # gcc-4.4 -static x.c
x.c: In function 'foo':
x.c:27: warning: function returns address of local variable
x.c: In function 'bar':
x.c:33: warning: function returns address of local variable
root@debian-mipsel:~ # ./a.out
0x4aa740 0x4aa750 0x2aaa8008 0x7fa417e8 0x7fa417d8
root@debian-mipsel:~ # ./a.out
0x4aa740 0x4aa750 0x2aaa8008 0x7fc67708 0x7fc676f8
root@debian-mipsel:~ # ./a.out
0x4aa740 0x4aa750 0x2aaa8008 0x7fb68238 0x7fb68228
root@debian-mipsel:~ # ./a.out
0x4aa740 0x4aa750 0x2aaa8008 0x7fc586c8 0x7fc586b8</pre>
<p>uname: Linux debian-mipsel 2.6.32-trunk-4kc-malta #1 Mon Jan 11 03:45:08 UTC 2010 mips GNU/Linux</p>

<h3>Gentoo GNU/Linux on amd64</h3>
<p>gcc-4.4.4, glibc-2.11.2-r0, 2.6.35-rc4 x86_64</p>
<pre>0x20cc010 0x20cc030 0x7fef0c497010 0x7fff32148fec 0x7fff32148fec
 0xa35010  0xa35030 0x7f575d0e4010 0x7fff0dd7220c 0x7fff0dd7220c
0x1f90010 0x1f90030 0x7f8657107010 0x7fff6116813c 0x7fff6116813c
 0x9dd010  0x9dd030 0x7f1eab0a6010 0x7fff3dcc638c 0x7fff3dcc638c</pre>

<h3>Conclusion</h3>
<p>Not everyone does ASLR… but there’s enough variety (and with
 eglibc’s AT_RANDOM even proper entropy) inside for our purposes.
 On OpenBSD and MirBSD, we’ll still use KERN_ARND as it’s extremely
 cheap entropy (code paths checked on both) but not for every call
 of <tt>$RANDOM</tt>. On things like Debian/m68k mksh(1) ought to
 have gained a possibly noticeable speed-up.</p>
----
Title: What’s with mksh bugs at the moment?
Author: tg@
Date: 21.07.2010 11:39
Tag: debian mksh

<p>Well, I suppose I should be happy that <a
 href="@@RELPATH@@mksh.htm">mksh</a> is actually used…</p>
<ul>
 <li>[tg] Correct shf buffer I/O routines to avoid a memory corruption bug
  discovered by Waldemar Brodkorb and other bad effects</li>
 <li>[tg] Fix NULL pointer dereference during iteration loop when checking
  for alias recursion; discovered by Michal Hlavinka</li>
</ul>
<p>That’s OpenADK (Waldemar’s fork of FreeWRT, which is Waldemar’s fork of
 OpenWrt), and Red Hat Enterprise Linux, respectively. Popcon in Debian and
 its derivates is also pleasant.</p>
<p>I could use some help bugfixing this though:</p>
<pre>
	(sleep 3; exit 12) &amp;
	bgprocpid=$!
	sleep 6
	# background process is done by now
	wait $bgprocpid
	# POSIX mandates that, since $! was asked
	# for, wait is to reply its errorlevel
</pre>
<p>Somehow, JF_KNOWN is never set – and I can’t debug this with gdb(1).</p>
<p>(There’s also a dashism in some *buntu start scripts that does pretty
 much the same except it uses “wait %1” there. In fact it doesn’t even
 seem to use $! – no idea whether we can support that at all in a POSIX
 shell – which dash clearly isn’t… – without keeping track of background
 processes forever.)</p>
----
Title: FrOSCon 2010 (“Birthday FrOSCon”) approaching
Author: tg@
Date: 25.07.2010 11:39
Tag: debian event geocache grml

<p><a href="http://froscon.de/">FrOSCon 5 - 21./22. August 2010</a> is
 approaching rapidly. I’m a bit envious at some of the tracks (I mean,
 really, geocaching (ok, I did the surrounging caches over the last
 years but still), learning python by means of game programming, etc.
 really sounds interesting – and I know people who could benefit from
 a non-kids version of that as well) but this year’s FrOSCon is nothing
 for me to curse about either: I managed to get <strong>both</strong> a
 booth for <a href="@@RELPATH@@main.htm">The MirOS Project</a> (MirBSD,
 mksh and other subprojects) as well as one for Waldemar’s
 FreeWRT (although wbx@ – if he
 comes – won’t join there since he forked his own fork since its
 conception). Booth staff are, currently: tg@ and bsiegert@ (Developer),
 gecko2@ (Staff) for MirOS, tg@ and “XTaran” abe@ (Developer), kimnotyze
 (Hacker) for FreeWRT. (XTaran will probably be helping Debian/Grml too.)
 This year, it’ll be my job (after 2 years of aptituz) to keep the <span
 xml:lang="de-DE-1901">Altbier-Fraktion</span> watered, I’m thinking one
 crate of Schlösser Alt and one crate of Hannen Alt?</p>
<p>Have a look at <a href="http://www.froscon.de/programm/uebersicht.html">the
 Program</a> and don’t tell me you won’t come! It will rock! (Except there
 won’t be Formorer’s Chilli, but that’s no reason, there’s enough other stuff
 in manageable distance.)</p>
<p>Besides interesting booths and talks, FrOSCon is still looking for helpers
 who will not only get free entrance but also catering during operation.</p>
----
Title: FrOSCon 2010 and other sundries
Author: tg@
Date: 06.08.2010 14:42
Tag: debian event grml

<p class="boxhead">The <a href="http://froscon.de/">FrOSCon 5 - 21./22.
 August 2010</a> booth plans have finalised, I am rather content:</p>
<div class="boxtext">
 <pre>
	┌──┐              I ❦ STANDPLAN FROSCON 2010
	│ F│reeWRT
	├──┤
	│ <a style="border:none;" href="https://www.mirbsd.org/">M</a>│<a style="border:none;" href="https://www.mirbsd.org/">irBSD</a>
	│  │
	├──┤
	│ <a style="border:none;" href="http://www.debian.org/">D</a>│<a style="border:none;" href="http://www.debian.org/">ebian</a>
	│  │                 C = Collectd
	├──┼────┐
	│C │   <a style="border:none;" href="http://grml.org/">G</a>│<a style="border:none;" href="http://grml.org/">rml</a>
	└──┴────┘
 </pre>
</div><p class="boxfoot">This is especially good, as XTaran will be
 shared among (at least) Debian, Grml, FreeWRT; same for me plus of
 course MirBSD; kimnotyze is FreeWRT but may help with MirBSD; benz
 and gecko2 probably are MirBSD but gecko2 could help with FreeWRT,
 tokkee was interested in FreeWRT too… anyway.</p>
<p class="boxhead">Some days, you just love software.</p><div class="boxtext">
 <pre>
	Aug  6 13:55:01 blau firesomething-bin: stack overflow
	    in function VFY_EndWithSignature
	Aug  6 13:55:01 blau /bsd: signal 6 received by
	    (firesomething-bi:1146) UID(2999) EUID(2999),
	    parent (sh:9059) UID(2999) EUID(2999)
 </pre>
</div><p class="boxfoot">Thus, let me reïterate it for all of you:
 <br /><img src="@@RELPATH@@pics/wlog/firemoo.gif" alt="firesomething" /></p>
<p>Well, now that the Debian Release Managers have sent their freezing
 bits around… *shudder*… Squeeze is frozen. Well, at least everything
 I have my hands in has migrated. I’m still… not persuaded. I also can’t
 decide which looks worse (KDE 4 or Win 7), tending towards KDE 4…</p>
<p>Why does all the horrid software (Solaris, Java™, OpenSSO, MySQL,
 etc.) tend to end up at Oracle at the moment? Let me quote from some
 Debian mailing list:<br />&gt;&gt;What happened to the Unix philosophy?
 <br />&gt;Modern Solaris engineers<br />Is that similar to high-speed
 horse carriages?</p><!-- RSS stop -->
<p>My <a href="http://download.opensuse.org/repositories/home:/mirabile/">RPM
 repository</a> has been pimped a bit – I ported some stuff from my <a
 href="https://eurynome.mirbsd.org/debs/debidx.htm">DEB repository</a>
 and updated them in both (rdate(8) and ntpd(8), specifically). Still
 ought to work more on them, but currently MirBSD base is most important,
 although I’m dying for <a href="@@RELPATH@@mksh.htm">mksh</a> associative
 and multi-dimensional arrays, as well as more sh(1) conformance <a
 href="@@RELPATH@@permalinks/wlog-10_e20100721-tg.htm">assorted bug
 fixes</a>.</p>
<p>Well, there’s a life besides the computer. I’ve taken today off, wanting
 to hack on MirBSD’s most urgent problems (but probably end up doing that
 tomorrow), slept long, and will meet with cnuke@ and gecko2@ for Greek
 style dinner. The latter will almost certainly end up with a long-time
 work contract at the same place where I run a lot of things already, so
 congratulations. In the meanwhile, bsiegert@ has almost become a Doctor of
 Chemistry, and my brother’s finished his Maths and Economics diploma.</p>
<p>Also, I’ve put up the logo of the company where my new dedicated server
 is hosted; they reduce the monthly fee in exchange for this, so humour me
 and pay them a visit. They’re IPv6 pioneers, actually. (The server is now
 installed but not completely set up yet, and I have yet to begin moving
 services; it’ll be better than the VM <tt>eurynome</tt> is, but the clock
 could use the new timekeeping subsystem in the kernel as well as socket
 send (ÆrieBSD) and receive timestamps as it’s off by 0-1000 ms.)</p>
<p>Speaking of kernel stuff, yesterday I considered moving wscons(4) to
 UTF-8 again (since everything is CESU-8, we need to take raw octets into
 account also). I’ve seen OpenBSD begun importing Citrus… *shudder*
 Anyway, that’s my part, but I’d like volunteers for backporting things
 like the timekeeping stuff (and possibly more hardware support), and
 writing a pivot_root like thing (explained on some mailing list already)
 so we can use ramdisc root to do loopback root.</p>
----
Title: New snapshot 2010-08-15 (i386), sparc reloaded
Author: tg@
Date: 15.08.2010 12:59
Tag: snapshot

<p>I’m currently putting the finishing touches on a new MirBSD snapshot
 for i386, targetting FrOSCon. Due to German patent 69429378 (EP0618540)
 I had to update the sparc kernel (GENERIC and RAMDISK) as well though.
 For now, mount_msdos(8) LFN support is <em>disabled entirely</em>, but
 a code rewrite to support LFNs in FAT in a non-infringing way (although
 for a file with LFN, no SFN will be generated any more then) is planned
 already (just not done before FrOSCon). This situation, in general, <a
 href="@@RELPATH@@permalinks/wlog-10_e20100522-tg.htm">sucks</a>.</p>
<p>The HTML manpages have also been updated, and the <a
 href="@@ABSPATH@@/MirOS/dist/mir/mksh/mksh.pdf">PDF</a> manpage for <a
 href="@@RELPATH@@mksh.htm">mksh</a> is now PDF 1.4 – something closely
 resembling, if not, PDF/A actually.</p>
<p>The snapshot will, as usual, end up on the mirrors, i.e.</p><ul>
 <li><a href="https://www.mirbsd.org/MirOS/current/">Germany main</a>
  (Strato) secure HTTP</li>
 <li><a href="http://pub.allbsd.org/MirOS/current/">Japan</a>
  (AllBSD.org) insecure HTTP</li>
 <li><a href="http://mirror.bsdprison.com/MirOS/current/">USA</a> insecure
  HTTP and <a href="ftp://ftp.bsdprison.com/pub/MirOS/current/">FTP</a></li>
</ul>
----
Title: FrOSCon 2010 and today’s resumée
Author: tg@
Date: 24.08.2010 14:43
Tag: debian event mksh snapshot

<p>FrOSCon was a blast. I had two booths of my own – MirBSD and FreeWRT – as
 well as shares of Debian and Grml. Well, MirBSD was run by Benny and gecko2
 because I just didn’t have any time for it, despite XTaran’s help with the
 FreeWRT booth. All I did was the initial setup of both booths, while at the
 same time answering about three questions regarding FreeWRT in parallel.
 Wow. What a little small, open hardware can do to you. XTaran and I had fun
 and we’ll do FreeWRT booths again; I managed to flash my two FON2100 devices
 (“La Fonera” – the FON2200 can use the same image, says nbd of OpenWrt) and
 will fix the port’s remaining few bugs I found; XTaran will try to push the
 WL-500gPv2 development. The social part was nice as well, although I think
 the greek restaurant in the city will not be visited by me again. Anyway,
 if you didn’t attend FrOSCon, your own fault…</p>
<p>Since the BitTorrent tracker used by MirOS is down, here’s the link to
 the [updated 2010-08-28] [deleted 2014-05013]
 current (FrOSCon 2010 Edition) snapshot’s torrent, Triforce as usual.
 We’ll probably rewrite torrent files for all our ISOs and publish them on
 the MirBSD website. I’m currently considering OpenBitTorrent plus one or
 two DHT seed nodes with no statistics. Maybe with webseed. (Need to update
 the libtorrent/rtorrent MirPorts first, though…) Other options would be
 different trackers or running one of our own. I will announce the outcome
 as news entry, once done.</p>
<p>On the plus side, the review process of mksh(1) in Android continues,
 and I fixed the realpath builtin to behave even more POSIX-ish.</p>
----
Title: mksh, encodings, MirBSD, BitTorrent, WinCE
Author: tg@
Date: 28.08.2010 20:31
Tag: android debian geocache hardware mksh news release snapshot

<p><a href="@@RELPATH@@mksh.htm">mksh</a> was merged into Android (both
 AOSP and Google’s internal master tree) in the night 24/25th August,
 and is expected to be the one shell to rule them all, for Gingerbread.</p>
<p>mksh(1) now also has a <tt>cat</tt> builtin, for here documents
 mostly. It calls the cat(1) command if it receives any options. The
 shell is nevertheless smaller than yesterday because of improved
 string pooling.</p>
<p>There’s another reason to use the MirOS OPTU-16 encoding instead of <a
 href="http://thread.gmane.org/gmane.os.miros.general/8899">PEP 383</a>,
 on which I already wrote: try passing a wide-char filename to a function
 such as MessageBoxW, or create a filename on a system using wide chars,
 such as FAT’s LFN or ISO 9660’s Joliet, or one that only allows Unicode
 (canonically decomposed – ü → ü – out of all things) like HFS+. OPTU-8
 at least maps to somewhat reserved codepoints (would, of course, be
 better to get an official 128 codepoint block, but the chance’s small
 of getting that in the BMP). Still.</p>
<p>Oh well, the torrents. I’ve remade them all, using one DHT seed node
 and <a href="http://openbittorrent.com/">OpenBitTorrent</a> as tracker
 and put them on a very rudimentary <a href="@@RELPATH@@bt.htm">BT</a>
 page that will be completely redone soonish. Please re-download them.
 I currently do not believe <tt>f.scarywater.net</tt> will return.</p>
<p>Finally, I fell victim to a selling-out and may have just bought a
 Windows Mobile 6 based phone (Glofiish X650) and an SDHC card and an
 extra battery with double capacity. Well, at least it’s said to run <a
 href="http://www.cachewolf.de/">CacheWolf</a> well. I still would like
 to have something like Interix, Cygwin, UWIN, coLinux, or maybe some
 qemu-for-WinCE variant that runs Android, Maemo, Debian/armhf (or armel
 or arm) at near-native speed (and is usable – the device sadly doesn’t
 have a hardware keyboard, but it comes with SiRFstar Ⅲ GPSr). It only
 has 64 MiB RAM, like the Zaurus SL-C3200 and the jesusPhone, though.
 ☹ Any chance to get <a href="@@RELPATH@@mksh.htm">MirWorldDomination</a>
 onto that device as well?</p><!-- RSS stop -->
<p>Tomorrow, eight years ago, is the date we now use as birthing point
 for <a href="@@RELPATH@@main.htm">MirOS</a>. The thing is, we did not
 really want to create a BSD of our own, fork, or whatnot. We were mostly
 happy OpenBSD users (really happy before the first eMail exchange with
 its developers, where Theo de Raadt did indeed stand out but was not
 the only one – just the one with the authority to deny us), improved it
 locally and submitted patches and ports. We were flamed for that or,
 worse, ignored. I begun putting up my “OpenBSD patchkit” on my homepage
 (back then, at Tripod) and still tried to feed things to upstream and
 OpenBSD. Then, at some point, Theo de Raadt made it clear he did not
 want me and the patch kit had grown (from one 4M file into several of
 them), so I ended up doing a “cvs -d /cvs init” and went from there.
 Benny’s story is similar – he laughed at me while trying to get ports
 added to OpenBSD, then discovered his ports were added to the MirPorts
 Framework and getting commit access there was easier than getting some
 random developer to commit something of his to OpenBSD. (This trend
 ended there though… <em>every single</em> person I approached since
 has become OpenBSD ports committer – I wonder whether they used my
 invitation letter to blackmail Theo?) It’s often thought that there
 was a clash of opinions between Theo and me. I think while we might
 disagree in certain aspects or priorities things should have, in the
 end we both wanted the same thing, I just was promised to never become
 a member of the OpenBSD project, so it’s really just “them” being
 uncooperative. (They (Henning and others) did burn the T-Shirt I gave
 Theo as a gift some day for making OpenBSD what it was. I won’t comment
 on that, again, now.)</p>
----
Title: Don’t use HEAD right now, working on RNG and CVS
Author: tg@
Date: 16.09.2010 21:24
Tag: snapshot

<p>I’m currently working on two very important subsystems to MirBSD:
 the entropy subsystem arc4random(3), arandom(4), arc4random(9);
 the cvs(GNU) implementation. That’s why it’s extremely encouraged to
 <strong>not</strong> update to -rHEAD right now.</p>
<p>The entropy subsystem receives completely – except arc4random_uniform(3) –
 rewritten arcfour and arc4random* code (userspace already done) including
 quite a speedup, and a new structure of the kernel pools and how they
 interact (also for speedup, but better hashing as well).</p>
<p>Our GNU CVS implementation has received a number of patches from Debian’s,
 and not only did I synchronise the port with base again, but also created
 I an (unofficial) “WTF” *.deb package from it, since Debian’s has, as we
 discovered years ago, some broken (but hey, ISO compliant!) date format.</p>
<p>I’d suggest let me finish doing, unbreaking ;-) and testing it.</p>
----
Title: Minor annoyances, BitTorrent trackers; construction work finished
Author: tg@
Date: 26.09.2010 16:32
Tag: news rant release security snapshot

<p><tt>openbittorrent.com</tt> has, apparently, bitten the dust as well.
 Oh the joy. DHT to the rescue, over the last few days, for those who
 could do it. I’m now running <tt>bttrack.py</tt>, yes the original, on
 <tt>eurynome</tt> and have (<strong>again</strong>) reannounced this
 project’s torrents. <strong>Please <a href="@@RELPATH@@bt.htm">download
 the *.torrent files</a> again.</strong> And don’t bother asking, I’m not
 running a public tracker. <strong>Clarification:</strong> The content is
 unchanged, <em>only the torrent metafile</em> has changed!</p>
<p>The updated CVS and new RNG code seem to behave well; I also fixed old
 bugs in the process. I will probably update our main server within some
 foreseeable future (this would be the ideal time to push out a snapshot
 again as well, even if it’s “just” netinstall).</p>
<p>People have shown interest in my djbdns patches. Consider forking,
 even putting it into the base system. I need to solve the problem of
 the remaining non-v4-transport-capable v6-transport binaries though,
 I think only dnscachet6 is remaining, so we’ll get only one set of
 binaries again. Also look for SRV RR patches. I wonder whether someone
 will code DNSSEC support…</p>
<p>The msdosfs LFN code is also still on my TODO, as are some other
 things. But hey, at least there’s movement; even Benny, despite being
 offline, unreachable by phone, etc. commits Google-Goo code. (Hi!)</p>
<p><a href="@@RELPATH@@mksh.htm">mksh</a> currently is being reviewed
 by the Android Security team, who like it on a first look. I’ve already
 addresses the first concerns even. I might release R39d soonish, also
 because I’d like a stable release before going on to associative, and
 since it’s easier to do than prohibit, multidimensional arrays – which
 have been welcomed in <tt>#ksh</tt> already…</p>
<p>You might want to update src/sys/net/netisr.h if running #10-stable,
 or upgrade to the latest kernel. I ran dieharder, and the results look
 good. The latest RNG subsystem pulls from many more sources and mixes
 better; I’ll summarise it later probably.</p>
----
Title: Debian/m68k re-bootstrapping
Author: tg@
Date: 16.10.2010 19:55
Tag: debian

<p>I’m currently working on something which will eventually amount to a
 re-bootstrapping of sorts of the Debian/m68k (Linux) port – patches to
 the Linux kernel, gcc, etc. are prepared (some have been accepted into
 upstream or the packages already). I will probably have more, once the
 compile processes finish, anyway (even emulated, it’s slow).</p>
<p>I think that, once I get past that TLS (thread-local storage, needed
 by eglibc) migration, I will try to find out a list of packages needed
 for debootstrap (AFAICT: all packages marked Essential, or of priority
 important, and all marked Build-Essential (for the *-builder variant),
 and their dependencies (although I’ll substitute sysv-rc with file-rc,
 which is better and needs less deps)) and pull arch:all from sid, then
 build the rest myself using a consistent snapshot of sid possibly with
 patches going to unreleased. Then I can use cowbuilder to make cleaner
 packages, which can eventually be uploaded (once I get enough to get a
 buildd running – kernel, bootloader, etc) – binNMUs are way to go here
 I suppose. I will only upload once it’s self-hosted, installable (seen
 by edos-debcheck), clean, etc. (i.e. I’ll rebuild <strong>all</strong>
 binaries) and probably keep a bootstrap repo around (until m68k caught
 up) so that unstable (possibly amended by unreleased for a while) will
 not again become uninstallable, e.g. if arch:all packages change their
 dependencies (Python, gcc-defaults are some I’ve seen). That bootstrap
 repository is needed anyway because debootstrap can’t install from two
 separate repositories (unstable+unreleased for example).</p>
<p>Progress is slow because I try to keep as close to official packages
 as possible, refuse to cross-compile, and try to produce uploadable if
 possible packages all the time. Getting patches into packages, so that
 I can build from unstable, instead of debian-ports.org unreleased, has
 proven time-consuming and occasionally frustrating as well. Although I
 would like to thank the people who helped me on the way already. (I am
 not naming any in fear of forgetting some, but you know who you are ☺)
 They are among the Debian (gcc, kernel, m68k) and Linux-68k crowd.</p>
<p>(Why does genattrtab in gcc-4.4 take 3½ hours when it took less than
 half an hour in gcc-4.3 anyway?)</p>
<p>I’m also still working on <a href="@@RELPATH@@mksh.htm">mksh</a> and
 some Python ISO hacks for <a href="http://grml.org/">mika</a> and some
 minor stuff, and further cleaning up MirBSD.</p><!-- RSS stop -->
<p>Well, did I mention dentists are sadists?</p>
----
Title: Debian/m68k progress, MirBSD notes
Author: tg@
Date: 06.11.2010 15:10
Tag: debian event mksh

<p>I’m almost finished with “sort of re-bootstrapping” Debian/m68k (I
 can use etch-m68k as well as what was in unstable at the moment as
 dependencies, so it was not <em>that</em> much, still, 305 binary
 packages build from 84 source packages, most for unstable (very few
 for unreleased, with very responsive maintainers, thanks all, who
 will include the patches in their next uploads) is a bit… including
 rebuilds with newer versions, more patches, more testing or newer
 dependencies installed. I’ll probably upload on Sunday evening, as
 I’ll be off for 2-4 days at least from then (see below). Ingo tried
 to test on real hardware, but as Murphy wants a hard disc failed…
 we’ll still try to get something done over the weekend. If you want
 to have a
 look, see my repository index (<tt>sources.txt</tt> contains a
 sample sources.list file, <tt>0-NOTE.txt</tt> some hints, including
 the right debootstrap/cowbuilder magic and speed tricks). I’ll need
 to learn how to use LVM and set up a buildd now…</p>
<p>I’ve not been in much of a hacking mood recently – all these visits
 to the dentist leave me in unrest and disturb my equilibrium. Hence,
 not much activity even in <a href="@@RELPATH@@mksh.htm">mksh</a> even
 if there was need, almost none in MirBSD. This is only temporary, but
 I won’t attend <a href="http://openrheinruhr.de/">OpenRheinRuhr</a>,
 or, if I come at all, it’ll be for socialising only and probably only
 one day. Benny’s done with his Doctor (in France, no idea whether it’s
 one in Germany as well) of Chemistry and has returned to hacking some
 (World of) Google-Go(o) code. I expect MirBSD activity to slowly raise
 once we can come back. Please accept our apologies.</p>
----
Title: Sorry for accidentally spamming ~60 people/lists
Author: tg@
Date: 07.11.2010 14:18
Tag: debian

<p>When doing porter uploads, one must not forget to pass
 <tt>-m"My Name &lt;my@email.addr&gt;"</tt> to dpkg-buildpackage,
 e.g. with <tt>--debbuildopts</tt> for cowbuilder. Thanks Aurélien
 and sorry to everyone who got the upload mails.</p>
<p>(How are the rules for sponsored uploads? I get conflicting info
 on these, and indeed, the one I sponsored never showed up on my QA
 DDPO page…)</p>
----
Title: pkgsrc on MirOS
Author: bsiegert@
Date: 11.12.2010 14:10

<p>Like we decided on FrOSCon this august, I restarted work on getting
 pkgsrc working again and then, on adding support for MirOS BSD to
 pkgsrc upstream. The thing is, while our MirPorts infrastructure is,
 in my opinion, outstanding, many of the ports themselves are highly
 out of date. Having pkgsrc would free us from the burden of maintaining
 thousands of ports ourselves. Many of the technical arguments that
 had originally been brought up against pkgsrc (such as missing support
 for "faking") have been addressed in the last few years.</p>

<p>As a first step, I applied Thorsten's old diff against the
 pkgsrc-2006Q4 stable branch, which was created shortly after the diff
 had been made. Next, I am porting these changes to a current pkgsrc
 branch in order to get them integrated. However, this will involve
 porting libtool 2 to MirOS, as newer pkgsrc versions only use this
 version. Wish me luck :).</p>

<p>I will be on 27C3 in Berlin from December 27 to 30, even though tg@
 will not.</p>
----
Title: pkgsrc Mini-Howto
Author: bsiegert@
Date: 31.12.2010 12:50

<p>27C3 brought significant advancements in pkgsrc support for MirOS
 BSD. I am in contact with a NetBSD developer, who is favourable to
 including the patch upstream in pkgsrc. For them, there are two parts
 for this: (a) the mere addition of a "MirBSD" stanza, which is
 unproblematic, and (b) other code changes, which need more review. Note
 that pkgsrc is currently frozen before the 2010Q4 release, so our
 patches will likely be deferred until after the freeze.</p>

<p>If you would like the current patches, which are still in a bit of a
 rough shape, here is how to use it:</p>

<ol>
 <li>Make sure there are no mentions of MirPorts in your current
  environment. Most importantly, remove /usr/mpkg/bin and /usr/mpkg/sbin
  from your PATH. This is needed when building or installing packages;
  the reason is that the package tools from MirPorts and pkgsrc have the
  same name but are incompatible with each other.</li>
 <li>Check out pkgsrc, for example to /usr/pkgsrc:<br />
  <tt>cvs -qd anoncvs@anoncvs.netbsd.org:/cvsroot co -P pkgsrc</tt></li>
 <li>To be sure that the patches will apply, downgrade the patched
  directories:<br />
  <tt>cd pkgsrc</tt><br />
  <tt>cvs -q up -Pd -D2010-12-27 bootstrap devel/{bmake,libtool*}
   lang/perl5 mk</tt></li>
 <li>Apply <a
  href="http://dl.dropbox.com/u/17617299/MirOS/pkgsrc-bootstrap.diff">pkgsrc-bootstrap.diff</a>,
  then <a
  href="http://dl.dropbox.com/u/17617299/MirOS/pkgsrc-libtool-miros.diff">pkgsrc-libtool-miros.diff</a>:<br
  /><tt>cat pkgsrc-bootstrap.diff pkgsrc-libtool-miros.diff | patch
  -p0</tt></li>
 <li>Check that there are no rejected patches:<br />
  <tt>find . -name "*.rej"</tt><br />
  should give no results.</li>
 <li>Bootstrap pkgsrc. In this example, we install (using sudo) into
  /usr/pkg. The dbdir should be inside the prefix to avoid conflicts
  with MirPorts.<br />
  <tt>cd bootstrap</tt><br />
  <tt>./bootstrap --prefix /usr/pkg --pkgdbdir /usr/pkg/db</tt></li>
 <li>Add /usr/pkg/bin and /usr/pkg/sbin to your path:<br />
  <tt>export PATH=/usr/pkg/bin:${PATH}:/usr/pkg/sbin</tt></li>
 <li>I recommend to install perl first because it is needed by many
  other packages and because it needs a workaround at the moment:<br />
  <tt>cd ../lang/perl5</tt><br />
  <tt>bmake install &amp;&amp; cd /usr/pkg/lib
  &amp;&amp; ln perl5/5.12.0/*/CORE/libperl.so.* .</tt></li>
</ol>

<p>You can now use pkgsrc to build whatever you like. Please test this
 procedure and report whether it works for you.</p>
----
Date: 15.01.2011 22:07
Author: tg@
Title: FOSDEM 2011 – Let the beards grow!
Tag: debian event mksh rant

<p><a href="http://www.fosdem.org/"><img
 alt="FOSDEM, the Free and Open Source Software Developers' European Meeting"
 src="http://www.fosdem.org/promo/fosdem/static" /></a></p>
<p style="font-size:big;">❧ Who’s not? ☺ Same procedure as every year.</p>
<p style="font-size:small;">(okay, lolando prefers skiïng but…)</p>
<p>Anyway. A cow‐orker told me that Belgium again/still has no gouvernment,
 and they have been asked to grow out their beards until they do. I found
 “evidence” on the ’net but won’t link it here, also it’s on German… anyway.
 Let’s all join in. (Besides, I now have an excuse to not shave, maybe even
 my grandmother will accept this one…)</p>
<p>RT said on IRC that <a href="@@RELPATH@@mksh.htm">mksh</a> will probably
 work on <a href="http://oldwiki.mingw.org/index.php/MsysShell">MSYS</a>.</p>
<p>My Debian/m68k stuff is coming around nicely, but I <em>still</em> haven’t
 gotten around to do everything planned, plus I need to grow a new kernel and
 eglibc, after the latest uploads, and the 2.6.37 based one panics. Also I’ve
 got to take care to not overwork myself. (And make a MirBSD ISO for FOSDEM.)
 But hey, it’s been not working for some time and better now. And slow anyway
 ☺ yet we’re progressing. Does anyone know how to debug that a C programme
 only calling res_init(3) segfaults?</p>
<p>Benny is apparently not just working on making NetBSD® pkgsrc® available
 on MirOS BSD (picking up my work from 4+ years ago) but also replacing
 The MirPorts Framework with it. Sad, as I got a request for a gajim MirPort
 over a cocktail just this evening…</p>
----
Date: 23.01.2011 21:30
Author: tg@
Title: FOSDEM snapshot; next mksh release
Tag: event mksh

<p>I’ve just prepared an ISO for <a href="http://fosdem.org/">FOSDEM Ⅺ</a>
 which we might export on <a href="@@RELPATH@@bt.htm">BitTorrent</a> soon.
 Benny has provided an upgraded desktop background image, thanks.</p>
<p>The next <a href="@@RELPATH@@mksh.htm">mksh</a> release… well I’ll bite
 the sour apple and will release it without associative arrays but hope I
 get around to hack a few things (especially the read and sleep builtins)
 before releasing. One lession learned, don’t brag with oh-so-big plans
 when you haven’t got a deliverable yet. Real Life <em>will</em> interfere.
 Oh, and Murphy, of course. (mksh R41 might have the associative arrays
 then. But mksh-current has <tt>${foo@#}</tt> which is <tt>hash($foo)</tt>.</p>
----
Date: 13.02.2011 00:07
Author: tg@
Title: FOSDEM was a blast!
Tag: debian event mksh

<p>I just need to work more on bilocality. While I did find two geocaches,
 one at the South/Noon Train Station (taalverwarringen…), one in the buurt
 of the University, I did manage to miss the AW building completely and
 utterly. Wow. Except, that Haiku guy came over to talk for a bit (nice).
 And I drew. An Atari logo with swirl, for that weird stuff I recently have
 been <a href="https://wiki.debian.org/M68k/Cowbuilder">found doing</a>.</p>
<p>More <a href="@@RELPATH@@mksh.htm#clog">mksh-current</a> news coming soon,
 stay tuned. In the meanwhile, I met bonsaikitten IRL (at FOSDEM, yes, too)
 who kindly made a “live ebuild”, i.e. a source package building -current.</p>
<p>Finally let’s say a big thank you to the person mostly manning our booth,
 gecko2, and to Benny for talking to people, getting That Other Packaging
 Thingy working, and pimping the website a bit.</p>
----
Date: 19.02.2011 18:01
Author: tg@
Title: Where in the world is Carmen Sanbuggo?
Tag: debian mksh

<p>Eh. Why does <a href="@@RELPATH@@mksh.htm">mksh</a> built with (a patched:
 mkstemp(3) added) <a href="http://en.wikipedia.org/wiki/Klibc">klibc</a> work
 suddenly, unexpectedly?</p>
<p>To reproduce, I just uploaded <tt>mksh_39.3.20110218-1.dsc</tt> and you can
 run <tt>DEB_BUILD_OPTIONS=mksh-static=klibc,dietlibc,eglibc dpkg-buildpackage
 -rfakeroot</tt> to verify it, once you have mkstemp(3). (I will probably send
 a smaller implementation of that in, later.) I have that and the open fix and
 the m68k patch applied, nothing else… where did my bug go?</p>
<p>ObQuestion: what’s the legal (copyright/trademark) status of the Atari logo
 (the one in rainbow colours, with three things going up, right and left “leg”
 looking like an umbrella stand’s)?</p>
----
Date: 03.03.2011 16:24
Author: tg@
Title: (Free)BSD vs. Linux
Tag: debian event ill mksh rant

<p>Warning: this is a rant against BSD (specifically FreeBSD®, but don’t let
 me get started on DragonFly, who think it’s wise to drop all shells except
 ash from the base system and rely on pkgsrc® – yay let’s compile a dozen
 packages just to get a shell with tab completion, not to mention boxen with
 no network access – for the task – although others seem to go into that
 direction too…; you know, there’s BSD, and then there’s FreeBSD…) – don’t
 like, don’t read.</p>
<p>If you want to change something in the BSD world, you gotta fork your
 own BSD – no other way around the thickheads. Ok, back then, I ran into
 a particularily thick one, but others tend to not be much better. Users
 share the thickness. If you want to change something in the GNU/Linux
 world, just make a package, have someone upload it, prod (or pay, Hanno
 got a Radler) people to do it, or just upload it yourself.</p>
<p>At the BSD booth at FOSDEM, despite me bringing the Windows® Mobile
 6 Professional devive, strictly for Geocaching mind you, Macintosh boxen
 had a share of more than 50% – I didn’t manage to tip the scale. At the
 Debian booth, almost everyone had a “I want to buy a new laptop some day,
 but it just keeps on working and doesn’t break” pre-Lenovo IBM laptop.
 No hyping of Google either. (Last year’s CLT saw BSD people advocating
 pro-Schily – the guy with the broken encoding in his name – shockingly.)</p>
<p>Honestly, tcsh, FreeBSD® people? Sorry. While I agree that there is
 merit on having the same script and interactive shell, as someone has
 pointed out (copy-paste examples into the command line), there’s those
 zsh users who use <a href="@@RELPATH@@mksh.htm">mksh</a> or GNU bash
 for scripting. Or just POSIX shell. And that’s with an interactive shell
 which <a href="http://git.grml.org/">can</a> be used for scripting. On
 the other hand, <a href="http://www.debian.org/doc/debian-policy/ch-files.html#s-scripts">the
 C shell</a> (both csh and tcsh) can<em>not</em>.</p>
<p>And what’s with pretending the <a
 href="http://www.cl.cam.ac.uk/~mgk25/ucs/apostrophe.html">accent
 gravis</a> is non-combining, called “backtick” (such a thing does not
 exist); and advocating it? Sorry, if your csh/tcsh doesn’t handle the
 POSIX <tt>$(…)</tt> you should just drop it. (By the way, there <em>is</em>
 a convention that example command lines are prefixed with <tt>% </tt> for
 csh and <tt>$ </tt> for sh (or <tt># </tt> but we write <tt>$ sudo </tt>
 instead, these days). Use it. Or leave it. If you have examples that
 substitute another process’ output, be specific.) It’s funny to see how
 one person tries to defuse my arguments against csh by telling me “it’s
 just an interactive shell”, while the other argues that people copy-paste
 between them, to which that was my response. Read the thread!</p>
<p>And please, get your facts right. “I would prefer that the standard shell
 be at least Bourne-compatible.” You don’t want Bourne (“^” instead of “|”
 for pipes), you want POSIX. That GNU bash is called the Bourne-Again Shell
 in one of their usual semi-bad puns doesn’t help the global perception of
 such things any. Also, the root shell and <tt>/bin/sh</tt> are disjunct.</p>
<p>(Plus, why change the root shell, use sudo(8), plain and simple.)</p>
<p>ObNote: in <a href="@@RELPATH@@jupp.htm">jupp</a> (should I package that
 for Debian, btw? rather upload, packages are ready…) the ‘`’ key is used
 as præfix for Ctrl-X (<tt>`X</tt>) or to directly enter numerical (decimal,
 octal, sedecimal/hexadecadic) ASCII, 8-bit or Unicode codepoints. Yay!<br />
 And even the FSF has seen the light; for a few releases already, GCC uses
 “'…'” instead of “`…'” for quoting in messages, even without locales. Great
 job there! (<tt>LC_MESSAGES=en_GB.UTF-8</tt> usually works, too, though.)</p>
<p>ObDisclaimer: I have an (yes, Google…) Alert on the word “mksh”, so I know
 when it’s being discussed. This obviously includes certain fora. Also, I’m a
 shell implementer and bound to know a certain amount of details. Plus, mksh’s
 build script runs with pretty much any Bourne/POSIX/Z Shell which has
 functions and not too many bugs. I wrote it. Go figure. No lowly trolling.</p>
<p>FWIW, mksh(1) has the cat(1) builtin both because Android has no cat(1),
 and as speed hack. Almost all other shells have worse speed hacks, like a
 printf(1) builtin. And recently, builtins have become direct-callable, so
 this actually reduces the overall system footprint. (Its inclusion also
 provides for some other possibilities, internally.) And as two final side
 notes, if you haven’t seen this: determine which shell we are run under <a
 href="@@RELPATH@@cvs.cgi/contrib/code/Snippets/getshver?rev=HEAD">(CVS)</a>
 and I still offer a prompt conversion service (send me any GNU bash or oksh
 <tt>$PS1</tt> and I’ll send that to you in mksh(1) syntax – optionally with
 adjustments/improvements, like cwd uses only up to 1/3 of screen width).</p>
----
Date: 06.03.2011 02:06
Author: tg@
Title: mksh gains recursive parser for command substitutions – $(…)
Tag: debian mksh news

<p><a href="@@RELPATH@@mksh.htm#clog">mksh-current</a> has just gained an
 <em>experimental</em> recursive parser for command substitutions, fixing
 <a href="https://bugzilla.redhat.com/show_bug.cgi?id=496791">RedHat
 BZ#496791</a> and decades-old complaints about the pdksh codebase,
 compared to AT&amp;T ksh93. (GNU bash could also do the example, but not
 some other things mksh(1) parses fine now.)</p>
<p class="boxhead">This means that things like the following work now.</p>
 <div class="boxtext"><pre>
	# POSIX, should “always” work
	echo $(case 1 in (1) echo yes;; (2) echo no;; esac)
	# POSIX optional, works now in mksh, works in GNU bash
	echo $(case 1 in 1) echo yes;; 2) echo no;; esac)
	# GNU bash seems to choke on comments ending with backslash
	# a comment with " ' \
	x=$(
	echo yes
	# a comment with " ' \
	)
	# No non-recursive COMSUB parser can pass all of the above
	# tests and these below at the same time (some extensions)
	echo $(typeset -i10 x=16#20; echo $x)
	echo $(typeset -Uui16 x=16#$(id -u)
	) .
	echo $(c=1; d=1
	typeset -Uui16 a=36#foo; c=2
	typeset -Uui16 b=36 #foo; d=2
	echo $a $b $c $d)
	# the ‘#’ is especially tricky, that’s why the above cases
 </pre>
</div><p class="boxfoot">Next on my TODO is the complete rewrite of the
 read built-in command, as well as its documentation. I think that the
 (reduced) goals for mksh R40 will have been met by then, except porting
 to LynxOS and MPE, but we’re working on it, and re-testing Syllable and
 Plan 9). Of course, a release implies testing on <em>a lot</em> of the
 supposedly supported platforms, so it won’t be out “immediately”. Though,
 associative arrays have been removed from the R40 goals, so that I can
 at least get a new release out. Note that Debian and OpenSuSE Buildservice
 users have been provided with somewhat well-tested mksh-current snapshots
 for a while already, and Gentoo users can use the “live ebuild”; there’s
 always compiling from source too…</p>
----
Title: I am now a NetBSD developer!
Date: 11.03.2011 18:40
Tag: pkgsrc
Author: bsiegert@

<p>Since 2011-03-09, I am now a NetBSD developer. My allocated work area
 is <b>MirBSD support for pkgsrc</b>. This is now much simpler, as I have
 direct commit access to the repo.</p>

<p>My sponsors are Guillaume Lasmayous (glc) and Alistair G. Crooks (agc).
 The whole thing would never have happened if Marc Ballmer had not started
 the new-developer process during FOSDEM 2011. A big “Thank you” goes out
 to these three persons in particular as well as to all those that warmly
 welcomed me on the NetBSD developer mailing list.</p>
----
Title: Impressions of the Go programming language
Date: 12.03.2011 15:10
Tag: golang
Author: bsiegert@

<p><em>A few days ago, somebody sent me an e-mail with a few questions
 about the Go programming language, of which I am a coauthor and
 contributor. The questions concerned my general impression, the
 experience I had in it, the future and some good areas of application.
 Here is my reply.</em></p>

<p>In my experience, when people try Go, there are two phases: On a
 first glance, it does not seem very special. However, many that do try
 it quickly become hooked.</p>

<p>I myself was primarily programming in C when I started using Go. I
 had written some code in Limbo, which an be seen as the antecessor of
 Go, so trying it seemed natural. I quickly discovered that it is a very
 well-designed language, whose constructs make perfect sense and are
 easy to grasp. The standard library is also very well done and makes
 many common programming jobs easy.</p>

<p>I decided to write a project I did for work in Go. However, the target
 was a Windows system, so I became involved in the Windows port. My
 first contributions were to the path package. It is a nice experience
 working with such bright and professional people as the Go developers.
 While they can be sometimes a bit terse in code reviews, they are very
 talented people. I found myself thinking a long time about a single
 sentence in a review before finally “getting it”.</p>

<p>Speaking of which, the code review process is very efficient for the
 development of the language.</p>

<p>In the future, I think Go will get a much wider adoption, and be
 usable also for writing “native” graphical user interface programs.
 There is a WinAPI port for creating Windows GUIs, and there is a very
 good Gtk+ adapter for Unix-like systems. I can also see it being used a
 lot for network servers, such as HTTP application servers and so
 on.</p>

<p>In these two areas, parallelism is a key point. In a GUI application,
 you want the interface to remain reactive during calculations and I/O,
 which is very easy to do with multiple goroutines. In a network
 application, you also have to process many requests in parallel. Go has
 the potential to scale significantly better than other languages.
 Maybe will even be one of the answers to the problem of programming for
 ever more parallel machines, as almost all new computers have multiple
 CPU cores.</p>

<p>I also think that there will be more optimization so the language
 will get much faster in the future. It is already faster than Python in
 most cases (easy, since it is a compiled language) but just as easy for
 many.</p>
----
Date: 16.03.2011 21:21
Author: tg@
Title: HOWTO OpenID Delegate with Launchpad Login Service
Tag: debian grml tip

<p>Rhonda suggested I document how to use the LLS (Launchpad Login
 Service – their implementation of an OpenID provider) as Delegate,
 which basically means, you can put something up on your webpage,
 which can be a simple static (X)HTML page like mine (a /index.htm
 is especially nice, a <tt>/~<i>user</i>/index.htm</tt> works too),
 and use its URI and not <tt>https://launchpad.net/~<i>me</i></tt>
 to login. For example, this often hides the LLS from view e.g. in
 blog comments, such as those where Canonical is being criticised
 ☺ – but it’s also <strong>yours</strong>, easier to type and to
 change if you switch service providers.</p>
<p>The basic idea is to go to your Launchpad user page and view its
 page source. Look for openid relation links in the header – on <a
 href="https://launchpad.net/~rhonda">Rhonda’s</a> the value we’re
 looking for is “cyLQbcp”, and you see it several times.</p>
<p class="boxhead">Now you put this on your web page:</p><div class="boxtext">
 <pre>
	&lt;!-- begin: OpenID delegation to LP --&gt;
	 &lt;link rel="openid.server" href="https://login.launchpad.net/+openid" /&gt;
	 &lt;link rel="openid.delegate" href="https://login.launchpad.net/+id/<i>cyLQbcp</i>" /&gt;
	 &lt;link rel="openid2.provider" href="https://login.launchpad.net/+openid" /&gt;
	 &lt;link rel="openid2.local_id" href="https://login.launchpad.net/+id/<i>cyLQbcp</i>" /&gt;
	&lt;!-- end: OpenID delegation --&gt;
 </pre>
</div><p class="boxfoot">Of course, insert your, not Rhonda’s, ID.
 Do note that we <em>don’t</em> copy the <tt>X-XRDS-Location</tt>
 tag (that breaks things for some unknown reason), but otherwise,
 what we insert on our page is pretty much a copy of the info on
 the user page (maybe it’s a Delegate page, too?).</p>
<p>As usual, try at your own risk, bug Canonical if it breaks. It
 works with <a href="http://archiveofourown.org/">AO3</a>, Gerrit
 Code Review, and others though (interestingly enough, better in
 <a href="http://lynx.invisible-island.net/">Lynx</a> than GUI browsers because
 I stay logged in across Lynx sessions (and just have to confirm
 sending “my information” to the accessing site), whereas I have
 to re-login to the LLS in every GUI browser session).</p>
<p>As with the LLS generally, “to access a site which is <i>not</i>
 recognised” is <a
 href="https://answers.launchpad.net/canonical-identity-provider/+question/147960">expected</a>
 and worked on with low urgency (mostly cosmetical, I think).</p>
----
Date: 19.03.2011 04:45
Author: tg@
Title: Yawn.
Tag: debian event geocache grml

<p>Will drive to <a href="http://www.google.com/webhp?hl=la&amp;q=Chemnitzer+Linuxtage">Chemnitz</a>
 now. Maybe meet me there. No booth, just visiting to meet everyone
 again, rather spontaneous.</p>
----
Date: 21.03.2011 15:50
Author: tg@
Title: ’M back.
Tag: debian event geocache

<p>Two DNF out of four geocaches, well… one was too muggled, the other was
 no longer there, judging from the previous visitors’ log entries. Cached
 with natureshadow and bought his book on how not to cycle across Germany.</p>
<p>CLT was a blast, and it’s refreshing to attend an event without having
 to drive a booth of our own. Talked to <em>lots</em> of people. Since the
 boss was paying, even did some mingling in that area.</p>
<p>My ADSL line has been hiccupping ☹</p>
----
Date: 24.03.2011 18:39
Author: tg@
Title: Debugging PPPoE

<p class="boxhead">⸘Did you know…</p><div class="boxtext">
 <pre>
	sudo tail -f /var/log/messages &amp;
	sudo tcpdump -ovvlns1500 -eine3 &amp;
	sudo ifconfig pppoe0 debug up
 </pre>
</div><p class="boxfoot">… still no network ☹ but at least
 I got some more information, and the L-Technicians will
 have a look at it tomorrow as well.</p>
----
Date: 26.03.2011 10:58
Author: tg@
Title: Various joys
Tag: debian

<p>I’m online again. (In case you didn’t notice, duh…) Seems as if we
 (the Telco/ISP guy and me) just needed to look at it hard enough for
 it to go away – first he could dial in, using my account data, which
 I probably should change now, then herc with ppp(8) and pppoe(8) was
 working (although at about 50 KiB/s down, he showed me 508 KiB/s – a
 rate I had never achieved – with his WiXP), then I took my notebook,
 which worked with pppoe(4). Now herc’s working again. (Maybe altq(9)
 can explain the slowdown? Hm, from debian.netcologne.de I get 500 so
 it looks okay.)<br />But eurynome isn’t, oh the joy. Luckily, gecko2
 who administers its host system just woke up.</p>
<p>Things we do want to see: the Telco/ISP guy accepting that I run
 MirBSD on a P-233MMX box with Hercules graphics card and a 9″ monitor
 with no comment other than considering its age (and that it usually
 runs 24/7) as partial cause for the bug. Thanks, Netcologne!</p>
<p>Things we don’t want to see:<br /><tt style="white-space:normal;">Mar
 26 10:40:02 blau /bsd: signal 11 received by (screen:16857) UID(2999)
 EUID(2999), parent (screen:19111) UID(2999) EUID(2999)</tt><br
 />“Suddenly the Dungeon collapses!! - You die...” (luckily, I get it
 about once a year only)</p>
<p>ObCoffeeSpices: Marrakech (Cumin, Allspice, Cumin Aroma) – though,
 due to its relative strength compared to the others, the only coffee
 spice I have left. And another hint: pre-warming the <a
 href="http://bts.grml.org/grml/issue914">coffee cup</a> with hot
 water, so it doesn’t cool down too fast with the amounts of milk I
 put in, rocks.</p>
<p>I just wore the Squeeze Release (FOSDEM, Spacefun) T-Shirt to the
 bakery and got asked by a neighbour: “Oh, a Debian fan?” “Developer,
 even” – now imagine the typical “informed interested guy” talk for a
 conference booth of your OS of choice here. How proud he was to get
 his wife and himself Windows®-free at home; how he likes to tinker a
 bit (if he’s got any time left), which has become harder with Windows;
 how his time constraints have him at OpenSuSE currently but asked how
 squeeze is; and the usual complaints at places like $ork where they
 have to use Windows® and MSIE (apparently you can’t centrally manage
 Firefox, eh, good someone tells me, because that’s what we do…). Wow.
 Anyway, it’s spring, so people, wear your shirts. (Hrm, what do I make
 of the fact that this is my only Debian shirt – although I’m thinking
 how to get Tartan Trousers if money were no issue – and nobody had ever
 commented on my various BSD, FOSDEM, FrOSCon, etc. wear…)</p>
----
Date: 19.05.2011 20:29
Author: bsiegert@
Title: :(

<p>I hope I will never again have to attend a funeral for a friend who
 committed suicide.</p>

<p>That is all.</p>
----
Date: 19.05.2011 20:47
Author: bsiegert@
Title: Progress with pkgsrc
Tag: pkgsrc

<p>The MirOS support for pkgsrc is progressing, albeit very slowly. This
 is because I spend more time traveling for work than in the office.
 After a long day of meetings and conferences, I am no longer motivated
 to code in my free time. What’s more, several different projects at
 work have tight deadlines.</p>

<p>Having said this, I committed MirOS support for libtool-2.2.6b in
 pkgsrc the other day, after a positive review by agc. As for the bmake
 patch, which is still available from
 <a href="@@RELPATH@@pkgsrc.htm">our pkgsrc page</a>, I was told to
 redo the patch, this time for <tt>src/usr.bin/make</tt> directly. When
 this patch will have gone in, somebody else (joerg?) will sync
 <tt>pkgsrc/devel/bmake</tt>, and MirOS will be able to bootstrap pkgsrc
 without patches. Let’s try to get to this point before the 2011Q2
 branch.</p>

<p>The new “showcase” machine that I bought a while ago, does not have
 working network connectivity and SATA under MirOS. tg@ recommended an
 installation into an HVM guest under Xen. I am currently trying to set
 this up, however I must first succeed to get a stable NetBSD Dom0
 system. I am using NetBSD-current because it has the right network
 driver and a custom kernel, however the console seems flakey, and
 accessing <tt>/kern/xen</tt> (even just ls!) leaves the process hanging
 in the “tstile” state. pkgsrc has four versions of Xen, so I should
 just test them all until I find one that works.</p>

<p>PS: My Go package,
 <a href="http://golang.org/pkg/image/tiff">image/tiff</a> is now part
 of the standard library. Yay!</p>
----
Date: 21.05.2011 15:56
Author: tg@
Title: Progress with other things

<p>I’m still working on <a href="@@RELPATH@@mksh.htm">mksh</a> and
 doing some MirBSD core and ports work in between. On the other hand,
 since a lot of things suck so much, and other things become <a
 href="http://git.kernel.org/?p=libs/klibc/klibc.git;a=commitdiff;h=e90552b6d78dd4d090d014024da00723e179df30">unacceptable</a>,
 I’m seriously considering writing things like a libc (probably not
 complete, not totally from scratch – no way I’m going to code sunrpc –
 and not fast but at least correct. I’ve written quite some code for
 the MirBSD libc already, as well as kernel and bootloader. Most of
 it is shared between these, and I’ve digged in enough others (klibc,
 dietlibc, µClibc, musl, glibc) to have seen more. I was thinking of
 static linkage only at first, mostly for bootloader and compiler
 support code and, later, to link mksh statically against it on some
 OSes. But cnuke@ wanted a “correct” libc with dynamic linkage. Hmm…
 (On the other hand, we all know that these are dreams and a RL job
 can be time and will consuming.)</p>
<p>Roland Mas is hacking on Alioth this weekend, which runs code from
 me and some coworkers via FusionForge – more coverage ☺ I’m also
 doing okay with Debian/m68k (still slowly of course, but then, as
 BSD developer, I’m used to that <i>*g*</i>) and one of the old m68k
 buildds may very well be resurrected soonish. (Still need to port
 elfutils…) By the way, XHTML sucks, some things are hard to get right,
 and writing <a href="https://evolvis.org/DTD/xhtml10t-rdfa10.dtd">a
 DTD</a> should be obsolete…</p>
<p>I took over cvs(1) in Debian and replaced it with my previously
 private package of MirPorts’ cvs. Way to go! (Thanks to Steve for
 handing over maintainership.) Now, everyone, please test it and
 recheck whether your old bugs still apply. Oh, and send patches.
 But pserver, PAM etc. are gone for good, don’t bother.</p>
<p>PS: It’s still Google Go, Benny. (World of Google’s goo?)</p>
----
Date: 06.06.2011 21:36
Author: tg@
Title: synchronise environment between two shells
Tag: debian mksh pcli

<p>(First posting to Plänet Commandline! <tt>Tag: pcli</tt>)</p>
<p>Vutral asked in IRC how to synchronise two shells’ environment
 while they’re running. As you may know, POSIX systems cannot change
 a process’ environment vector after it has been started, only the
 process itself can. Well, <a href="@@RELPATH@@mksh.htm">the shell</a>
 can, and we’ll use a variety of things for this.</p>
<p>This trick assumes you have <tt>$HISTFILE</tt> set to the same
 pathname in both shells (obviously, they run under the same user).
 It uses <tt>export -p</tt> to render the current list of exported
 variables, then transforms the list from newline-separated to a
 single big one-line export statement.<br />Then it transforms all
 remaining newlines (which will be part of a single-quoted string,
 since that’s mksh(1)’s export format) into the sequence
 <tt>'$'\n''</tt> which means: terminate current single-quoted
 string, append <tt>$'\n'</tt> and open up a new single-quoted
 string immediately; concatenate these three.<br />Now, <tt>$'\n'</tt>
 is just a fancy way of saying newline, and part of mksh because
 David Korn (yes, the Korn in Korn Shell) strongly suggested to
 me that this functionality be included – but, as we can see here,
 it pays off.<br />Finally, the so transformed string is prepended
 by <tt>unset \$(export);</tt> which, when executed, will cause the
 shell to unset (and unexport) all currently exported variables.
 The shell parameters that are not exported, i.e. not in the
 environment, are not affected by this code (except for <tt>$x</tt>
 and <tt>$nl</tt>, but… whatever).<br />This string is then passed
 to <tt>read -s</tt> (plus <tt>-r</tt> and clearing <tt>IFS</tt> to
 enable raw mode), which means, read into the parameter <tt>$REPLY</tt>
 (which we conveniently don’t use – but it’s trashed too, thus) but
 store into history at the same time.</p>
<p>Ah hah! Now, the persistent history feature comes into effect!
 After running the below statement in the “source” shell, switch
 into the terminal running the “destination” shell, press Enter
 once on the empty line (Ctrl-U to empty it if it wasn’t), then
 Cursor-Up (↑) to recall… voilà, an insanely large line with the
 previously created string sorta expanded… and press Enter again
 to run it. Now your set of exported parameters is the exact same
 (minus if you exported <tt>IFS</tt>, <tt>nl</tt>, <tt>x</tt> or
 <tt>REPLY</tt>) as in the “source” shell.</p>
<p class="boxhead">I’ve added extra spaces and a linewrap below,
 this is really just one big line:</p><div class="boxtext">
  <tt>nl=$'\n'; x=$(export -p); x=${x//${nl}export/};</tt>
  <tt>IFS= read -rs &lt;&lt;&lt;"unset \\\$(export);${x//$nl/\'\$\'\\\\n\'\'}"</tt>
</div><p class="boxfoot">Of course, this makes a nice function,
 for your <tt>~/.mkshrc</tt> or somesuch.</p>
----
Date: 11.07.2011 20:21
Author: tg@
Title: Yugoslawia, I’ll be back
Tag: debian event

<ul>
 <li>√ Agreement to pay from company</li>
 <li>√ Going to drive with some apparently speed-loving brits</li>
 <li>√ Registration accepted</li>
 <li>√ Dienstreiseantrag prepared</li>
 <li>√ Sent that beast to the office ticket queue</li>
</ul><p>So yes, this means I’m <img alt="going to DebConf 11"
 src="http://kitenet.net/~joey/blog/pics/debconf11_banner.png" />
 to what used to be Yugoslawia when I was there the last time,
 although in the Poreč region of Istria, Hrvatska.</p>
----
Date: 11.07.2011 20:37
Author: tg@
Title: New releases
Tag: debian mksh

<p>You might have noticed the release of <a
 href="@@RELPATH@@mksh.htm#r40">mksh R40</a> recently, after
 more than a year of development. Well, stay tuned for both
 R40b (with accumulated fixes) and R41 (intent to speed up
 array handling a lot and prepare for what we postponed to
 mksh R42 now – associative, multi-dimensional arrays).</p>
<p>You should also upgrade, if you have not yet done so, to <a
 href="@@RELPATH@@kwalletcli.htm#r2_11">kwalletcli 2.11</a>.</p>
<p>Finally, <a href="@@RELPATH@@jupp.htm#r3_1j15">jupp 3.1.15</a>
 was left out to the world, including Minix 3 users this time,
 by special request of one of these on our mailing list. In
 addition to the MidnightBSD mport – which has been there in
 like forever – and the MirPort and the FreeWRT package, in
 December 2011 a user submitted it to FreeBSD® ports, and Benny
 is going to add it to NetBSD® pkgsrc® soon, he said. (He also
 updated their mksh source package. Thanks!) I’ve been asked by
 two people, independent from each other, when I’ll upload it to
 Debian proper, instead of the private-repo packaging. Maybe I
 should indeed do that, comments?</p>
----
Deleted: 1
Date: 11.07.2011 20:42
Author: tg@

-
----
Deleted: 1
Date: 11.07.2011 20:49
Author: tg@

-
----
Date: 17.07.2011 00:40
Author: tg@
Title: mksh R40b; joe 3.1jupp16 and 2.8jupp2 released
Tag: debian mksh news pcli release

<p><a href="@@RELPATH@@mksh.htm#r40b">mksh R40b</a> (nowadays with filled
 in <a href="@@RELPATH@@mksh.htm#c40b">user’s caveats</a> (for R40, too!)
 and <a href="@@RELPATH@@mksh.htm#p40b">packager’s upgrade hints</a>) has
 just been released. This is a should-have upgrade, fixing a number of –
 admittedly some obscure – bugs, changing things begun in R40, improving
 upon others. Thanks to the PLD Linux guys for spotting all these errors;
 thanks to them and phpnet.org both for adopting mksh so well.</p>
<p>I have also fixed a bug in nroff(1) which will lead to an <em>even</em>
 nicer looking HTML manpage mksh(1) (after the next rebuild and upload of
 a MirBSD snapshot – scheduled RSN).</p>
<p><a href="@@RELPATH@@jupp.htm#r3_1j16">jupp 3.1.16</a> took on the task
 of merging Debian joe changes (aiming at an upload). I also split the
 jupprc file into three versions (2.8 generic/DOS, 3.1+jupp and 3.7/Unix)
 because of the differences in the baseline executables making rc files
 partially mutually incompatible (think Insert key), annoyingly warning
 (think syntax, hmsg), or less usable (joe’s new menu system).</p>
<p><a href="@@RELPATH@@jupp.htm#r2_8j2">jupp 2.8.2</a> is a companion to
 jupp 3.1.16 – mostly because of the new help window “character map” ☺</p>
<p>Binaries for jupp should be updated RSN too.</p>
<p>Considering Banja Luka is arriving quickly, the “r” in RSN should be
 taken with a few grains of salt. I’ve also scheduled working on the pcc
 Debian package for the next future; updating lynx and maybe others like
 OpenSSH in MirBSD is also due; cvs(1) will receive more of my time, but
 before the next Upload I’d like to fix LP#12230 once verified.</p>
<p>Builds for Debian/m68k are also still running. I note I did in fact
 <em>not</em> manage to make a new base image, yet (but 2.6.39 kernels
 miss a patch, anyway, so waiting for 3.0 is ok). It’s still using gcc-4.4
 because nobody tests gcc-4.6 and gcj-4.6 FTBFS due to SIGSEGV, but that’s
 ok in my books. rsyslog is broken but sysklogd works.</p>
<p>The <a href="@@RELPATH@@ksh-chan.htm">#ksh|Freenode</a> page finally
 got a well-deserved link to Planet Commandline. Throw more my way!</p>
<p><a href="@@RELPATH@@cvs.cgi/src/share/misc/acronyms">Acronyms</a> and <a
 href="https://evolvis.org/scm/viewvc.php/evolvis/trunk/gforge_base/evolvisforge/gforge/www/js/datepicker.js?view=markup">translations</a>,
 too. (Got Norwegian and Rumanian covered in the meantime. No idea whether any
 RTL languages will work in that beast. But I’m young and need the money)</p>
<p>Since I’m writing a wlog entry anyway… let me thank Gunnar for a <a
 href="http://gwolf.org/blog/free-software-must-migrate-become-free-culture">nice
 summary on the current Free Culture discussion</a>; my comments on Nina’s site
 seem to be eaten, but let me support it fully, although, of course, I normally
 use a <a href="@@RELPATH@@MirOS-Licence">copycenter style licence</a>, which
 is specifically written for general works of authorship under copyright law,
 not limited to software. I did in fact have that in mind. Maybe some people
 will like it (it’s less than one Kibibyte long) either generally or just for
 their everyday random musings (they can then keep CC-BY-SA for the “big works”
 if they so desire).</p>
<p>Wouter, grass background makes green headlines illegible. I’ve never liked,
 and never installed manually, cups either. (Benny tells me that Apple’s new
 version refuses to talk with a non-Apple cups, kinda defeating the whole idea
 I think.) Port 9100 is JetDirect (probably with an HP in front and some subset
 of ©®™ trailing) and just nice. (Being able to talk ESC/P with your printer
 like <tt>print '\033K\x07\0\x3E\x81\x99\xA5\xA5\x81\x3E' &gt;/dev/lpa</tt> too
 rocks though, IMHO. Yes, mine can, and I still can. /dev/lpa is BSD.)</p>
<p class="boxhead">Kai, thanks for your vimrc lines:</p><div class="boxtext">
 <pre>
	:highlight TrailWhitespace ctermbg=red guibg=red
	:match TrailWhitespace /\s\+$\| \+\ze\t/
 </pre>
</div><p class="boxfoot">Automatic removal is harmful, though – I just fell
 into the trap since jupprc contains needed whitespace at EOL… but manual
 removal (bound to ^K] in jupp) rocks. And I like that your solution uses
 such strong a colour – vim users are the <strong>single most represented
 offender group</strong> for actually leaving the redundant whitespace at
 EOL there, and it should <em>hurt their eyes</em>. (Sadly there is some
 vehement disagreement preventing them from inclusion in grml-etc-core –
 but that’s why I re-post them here.) Ah, and jupp can of course display
 whitespace visibly (although it uses ‘·’/‘→’, replacing the arrow with ‘¬’
 if no UTF-8, not ‘»’), accessible with ^Ov.</p>
<p>Steve, want to put up a checklist for sites? We can “crowdsource” the…
 testing… to maybe get some interesting results…</p>
<p>Some other people would get more comments if they were idling in IRC
 (Freenode) <span style="font-size:small;">or allow comments on their blog,
 specifically without too high an entrance barrier – OpenID is ok, but many
 other things, and ECMAscript, are not; but I can’t really say that loud
 because our wlog is static HTML compiled from a flat plaintext data source
 so it doesn’t allow such either</span>. I often forget what I wanted to
 add if I can’t get it out quickly enough (especially at work). Sowwy…</p>
<p>Me like the cat picture postings (Amayita, Tiago, ¡Gracias!).</p>
----
Date: 19.07.2011 07:32
Author: bsiegert@
Title: Progress with pkgsrc and other things
Tag: pkgsrc

<p>pkgsrc-2011Q2 has been released. This is the first release which is
 really usable on MirOS. Bootstrapping works without applying patches
 before; I updated the <a href="@@RELPATH@@pkgsrc.htm">pkgsrc
 instructions</a> accordingly. During the freeze, there were two
 last-minute fixes to important base packages (gmake and glib2) which
 did not go in before the branch was cut off. One of them (gmake) has
 been pulled up on my request after Alistair G. Crooks encouraged to do
 so.</p>

<p>I finally managed to get a MirOS instance running on Xen with HVM
 using NetBSD-current as the Domain-0. I had to compile my own DOM0
 kernel to include support for the alc ethernet driver&mdash;yes, the
 one where I did not manage to fix the driver under MirOS. The first
 impression: Compilation and other CPU-intensive tasks are very fast,
 while I/O is quite slow. The qemu-dm process, which provides hard disk
 and network drivers to the DomU, seems to get congested quite rapidly.
 Btw, emulating an Intel Gigabit network card works very well with our
 em(4) driver.</p>


<p>To profit from the VM, I set up a bulk build with a fresh
 pkgsrc-2011Q2 checkout, using the pbulk framework. Technically, it
 looks very nice and more sane overall than a simple recursive make:
 there is a scan phase at the start, where a dependency tree of all
 packages is constructed. Then, a master process decides which package
 to build next. It can optionally distribute the builds over several
 machines at once. However, I found the documentation to be severely
 lacking; what’s more, the pkgsrc guide and the <tt>doc/HOWTO-pbulk</tt>
 file have obviously been written by persons with different approaches
 w.r.t. suggested directory layout etc.</p>

<p>I created a NetBSD slice of 55 GiB, mounted in MirOS under /pbulk,
 for all data relative to the bulk build and added it as a physical
 device in the VM configuration. However, the I/O congestion becomes
 worse after some time building things. The ssh connection becomes more
 or less unresponsive, and qemu-dm takes 100% of the Dom0 cpu. Even
 after stopping the build with ^Z, the hard disk is thrashing for
 several minutes with qemu-dm at 100% cpu, before slowly going back to
 normal after a few minutes. WTF? For what it is worth, the VM has 1 GiB
 of RAM allocated and no swap. More tuning required&nbsp;…</p>
----
Date: 25.07.2011 16:01
Author: tg@
Title: DebConf
Tag: debian event

<p>Sitting in <span xml:lang="sr-Cyrl">Бања Лука, Република Српска,
 Босна и Херцеговина</span> (<span xml:lang="sr-Latn">Banja Luka,
 Republika Srpska, Bosna i Hercegovina</span>) let’s just say the
 country is pretty nice. People are okay, the beer is not called
 “Nektar” by accident, and the <span xml:lang="sr-Latn">Mark</span>
 (subunit <span xml:lang="sr-Latn">Fennig</span>, funnily enough)
 is worth 1 DM. Price niveau is below Germany (even when we had
 the DM) in some things, below or at modern European in others.
 In short, very affordable. They don’t accept paper money though,
 it’s really hard to get coins in most places, and they only want
 those. The food is okay, and my hotel is very luxurious. It’s
 also got LAN.</p>
<p>The weather is not so nice at the moment though: raining a lot,
 and expecting 30°C too-hot sun in two days. And there are still
 no Geocaches in the area.</p>
<p>Anyway, DebConf is going on, I’m acclimating and trying to get
 people, faces, nicknames and realnames connected. And accents.
 (And pronunciation of names – for example, Ian differs totally
 from what I’d use.) We even have working wire network (LAN) most
 of the time ;-)</p>
<p>We’re indeed still working on resurrecting m68k, but that’s no
 news. More on that later, I’d say.</p>
----
Date: 27.07.2011 20:16
Author: tg@
Title: Бања Лука (Banja Luka)
Tag: debian event

<p>Been hot and dry today (although the sky is now back full of
 dark clouds), so I had a headache most of the morning until way
 past noon. Better now though, and I found a place where I could
 get Cevapi, which are really some sort of quick imbiss / fast
 food here (no Đuveč pirinač though, and she didn’t have any
 Ajvar nor did she speak any language other than the local, but
 that wasn’t a problem, only a bit dry because I didn’t give in
 and took the offered Ketchup). Bought a 1ℓ bottle of Kruškovac
 (from Hrvatska, though) and some small plastic glasses, then.</p>
<p>I wonder how many people would, now, be willing to give Bosna
 i Hercegovina a try as holiday region (which might have been the
 intent of having a Balkan DebConf). I’m sure I do.</p>
<p>To all attendees: the hotel will give you some kind of stamped
 hardpaper card which states where you stayed on the trip, and for
 how long – give that to the border guards when exiting Bosnia.</p>
----
Date: 27.07.2011 20:21
Author: tg@
Title: jupp: new release, new distro package
Tag: debian news

<p><a href="@@RELPATH@@jupp.htm#r3_1j17">jupp 3.1.17</a> uploaded
 today, mostly thanks to user input suggesting I improve things,
 especially the syntax highlighting. (Maybe more to come.) I like
 users who don’t complain but give helpful comments and send in
 patches even.</p>
<p>Since the Debian FTP masters complain that the NEW queue is
 empty for the first time in ages, I also uploaded jupp to Debian
 proper (got requests, several, from actual users – independent
 of each other). I originally thought I were the only user, it’s
 not worth it, maybe too close to joe (which segfaults a lot more
 and has some ugly things, so I cherry-picked the better features
 of it instead of rebasing jupp), but it’s had a package in mports
 (MidnightBSD ports) for ages, users submitted one to FreeBSD® last
 year and keep it updated, there’s even a WIP package in pkgsrc®,
 and who knows where else or how many people are using my OpenSuSE
 Buildservice package or have had installed the previous DEB package
 I uploaded to my play repo. So now I feel it worth to upload.</p>
<p>I even invested some <em>major</em> packaging rework, such as
 splitting the build-arch and build-indep parts from each other,
 and importing the upstream source into the packaging VCS, as I
 have learned in the “packaging with git” talk here at DebConf.
 (No guys, I will stick to CVS as git doesn’t give me anything.)</p>
----
Date: 11.04.2011
Author: tg@
Title: in-target: E: Kaputte Pakete
Tag: bug debian rant
Language: de-DE-1901

<p><a href="https://bugs.launchpad.net/ubuntu/+bug/757338">*buntu Hardy</a>
 kann zur Zeit nicht installiert werden (der Kernel (in main) dependet auf
 Pakete aus restrictet, das ist aber zum Installationszeitpunkt nicht aktiv
 und sowieso unfrei; und wieso ist eigentlich das hardy-updates Repo im d-i
 eingeschaltet und nicht erst hinterher?).</p>
<p>Lustiger aber: „Einige Pakete konnten nicht installiert werden. Das kann
 bedeuten, dass[sic!] Sie eine unmögliche Situation angefordert haben oder
 dass[sic!], wenn Sie die Unstable-Distribution verwenden, […]“</p>
<p><tt>gecko2</tt>s Kommentar dazu nur, daß unstable bei *buntu stable heiße.
 Ich habs dann auf LTS korrigiert (ist nicht das erste Mal – und sowieso,
 wieso tauschen die in einer stabilen Version PostgreSQL-Majorversionen aus?)
 und dabei haben wir’s belassen: Debian unstable = *buntu LTS.</p>
<p>Naja, wie wir das letztens Simon gesagt haben (Upgrade innerhalb einer
 Version von *buntu auf einem Server hat grub durch grub2 ausgetauscht):
 <em>Mit Debian wär’ das nicht passiert!</em></p>
----
Date: 18.08.2011 16:53:01
Author: tg@
Title: 「??? ???」 • or • mira meets d-i
Tag: bug debian fun

<p style="font-size:small;">(originally published on 2011-01-26, but
 reposting so the people on Plänet Debian can have some fun)</p>
<p>While helping a cow-orker setting up an encrypted hard disc
 (basically, putting <tt>/</tt> and <i>swap</i> into LVM inside
 cryptsetup, and <tt>/boot</tt> outside), <tt>mirabilos</tt> managed
 to discover an entirely new side of K?buntu 10.10 on his voyage…</p>
<p><img src="@@RELPATH@@pics/wlog/cryptsetup.jpg" alt="Warped" /><br />
 <span xml:lang="de-DE-1901">… wo noch nie ein Debian Developer zuvor
 gewesen ist… oder?</span></p>
<p>(Only a reboot helped at that point. Earlier, the dialogue box was
 shown only once, but upon re-entry of the partitioning <span
 xml:lang="de-DE-1901">clickibunti</span> d-i tool, neither button did
 anything save redrawing this… interesting, informative and intuitive
 error message.)</p>
----
Date: 25.01.2011
Author: tg@
Title: On SecureAPT
Tag: debian rant

<p>Dear Opera Software A.S.A.</p>
<p>It’s nice that you employ SecureAPT for your <a
 href="http://deb.opera.com/">package repository</a>, however, the effect
 is slightly lost by you replacing the key each year, never signing any of
 them, and putting them up on an http but not https site.</p>
<p><strong>Update</strong> 18.08.2011 – please refrain from putting a file
 <tt>/etc/apt/sources.d/opera.list</tt> inside your binary DEB packages, as
 well. As a system administrator, we may very well have mirrored the binary
 packages, and do <strong>not</strong> want accesses to external APT repos,
 for a shitload of reasons. Honestly. (Lintian could warn about it…)</p>
<p>If you don’t get the message, please contact me. Or any of my fellow
 Debian Developers. Thank you very much.</p>
----
Date: 09.05.2010
Author: tg@
Title: How to upgrade SKS Berkeley DB (bdb) etch→lenny
Tag: debian pcli

<p>Some things are ugly.</p><!-- The HTML of this entry too, I copy-pasted it from Wordpress… -->
<p>Waldi’s suggestion fails.</p>
<blockquote><p>db4.6_upgrade: Program version 4.6 doesn&#8217;t match environment version 4.4<br />
db4.6_upgrade: DB_ENV-&gt;open: DB_VERSION_MISMATCH: Database environment version mismatch</p></blockquote>
<p>Can’t start it manually.</p>
<blockquote><p>debian-sks@dev:~$ /usr/sbin/sks recon<br />
Fatal error: exception Bdb.DBError(&#8220;Program version 4.6 doesn&#8217;t match environment version 4.4&#8243;)</p></blockquote>
<p>The log only shows:</p>
<blockquote><p>2010-05-09 16:59:29 Opening log<br />
2010-05-09 16:59:29 sks_db, SKS version 1.1.0<br />
2010-05-09 16:59:29 Copyright Yaron Minsky 2002, 2003, 2004<br />
2010-05-09 16:59:29 Licensed under GPL.  See COPYING file for details<br />
2010-05-09 16:59:29 http port: 11371<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Malformed entry<br />
2010-05-09 16:59:29 Opening KeyDB database<br />
2010-05-09 16:59:29 Shutting down database
</p></blockquote>
<p>The solution is ugly as hell, too:</p>
<blockquote><p>root@dev:/ # su &#8211; debian-sks<br />
debian-sks@dev:~$ cd DB<br />
debian-sks@dev:~/DB$ db4.4_checkpoint -1<br />
debian-sks@dev:~/DB$ db4.4_recover<br />
debian-sks@dev:~/DB$ db4.4_archive<br />
log.0000002839<br />
log.0000002840<br />
log.0000002841<br />
log.0000002842<br />
log.0000002843<br />
log.0000002844<br />
log.0000002845<br />
debian-sks@dev:~/DB$ db4.6_archive -d<br />
debian-sks@dev:~/dump$ cd ../PTree/<br />
debian-sks@dev:~/PTree$ db4.4_checkpoint -1<br />
debian-sks@dev:~/PTree$ db4.4_recover<br />
debian-sks@dev:~/PTree$ db4.4_archive<br />
debian-sks@dev:~/PTree$ db4.6_archive -d<br />
debian-sks@dev:~/PTree$ logout<br />
root@dev:/ # /etc/init.d/sks start<br />
Starting sks daemons: sksdb.. sksrecon.. done.
</p></blockquote>
<p>Wow, our internal keyserver works again. Thank you, Debian…</p>
<p>This solution courtesy of <a href="http://www.hermann-uwe.de/blog/migrating-bdb-svn-repositories-from-one-version-to-another-and-to-fsfs">Uwe Hermann</a>, although it was for Suckwürstchen.</p>
----
Date: 18.08.2011 16:53:02
Author: tg@
Title: Not a good idea…
Tag: debian fun

<p>Sometimes, when you develop WUIs (Web UI), you really have to
 test them against a variety of browsers, not all of which are
 available for the operating system installed on peoples’ desktop
 PCs, or working in Wine. (For theming QA, Wine is also a #FAIL,
 but for technical QA, MSIE 1.5, 3.0, 5.02, 5.5, 6.0 work fine,
 and MSIE 7.0 can be used under rare circumstances.) In these
 cases, you use VMs running certain operating systems. One VM had
 an interesting idea of which hardware you can “safely remove”
 a couple of days ago when I was hacking it anyway: <img
 src="@@RELPATH@@pics/wlog/notagoodidea.png"
 alt="Safely Remove… the RAM controller?" /></p>
----
Date: 18.08.2011 16:53:03
Author: tg@
Title: FrOSCon 2011
Tag: debian event grml news

<p>This year without our friends from Grml, but The MirOS Project
 (all two active developers and our Booth Babe gecko2@) will of
 course attend <a href="http://froscon.de/">FrOSCon</a>, nicknamed
 Froschkon, again.</p>
<p>We’ll have a pre-event meal time at my favourite Jugoslawian
 Restaurant on Friday (20:00 CEST) – contact me privately for the
 coördinates if interested. On Saturday and Sunday we’ll staff a
 booth and answer questions about the many projects we have (more
 or less) running, including but not limited to paxmirabilis (aka
 MirCPIO), <a href="@@RELPATH@@mksh.htm">The MirBSD Korn Shell</a>
 aka mksh(1), <a href="@@RELPATH@@jupp.htm">jupp</a> the editor,
 and developers’ private projects such as slowly undermining Debian
 or Google-Go. While slow we are still working on World Domination.
 And <a href="https://evolvis.org/projects/shellsnippets/">teaching
 people good shell programming</a> by example code.</p>
<p>We might even bring CDs, but I’m still working on the ISO… last
 night’s build aborted because the OS grew a bit making the floppy
 image not fit any more. (Solution, drop ping(8) and rtsol(8), but
 re-add sf(4) and bce(4) now that they fit again.)</p>
----
Date: 09.06.2010
Author: tg@
Title: SPARCstation 20 (75 MHz)
Tag: debian rant
Language: de-DE-1901

<p>Wenn Du denkst, MirBSD wäre langsam und sein Installer in irgendeiner
 Art und Weise doof, dann installiere mal Debian (etch, neuere Versionen
 können nur noch sun4u und sun4v, kein sun4m mehr) auf einer SPARCstation
 20.</p>
<p>Lahm wie Sau, das Teil. Und der Installer ist schwarz auf weiß – was
 nicht so schlimm wäre, wenn der Cursor (und die dialog-Markierungen)
 nicht ebenfalls schwarz auf weiß wären…</p>
<p>Ich bin ja mal gespannt, ob das durchläuft.</p>
----
Date: 18.08.2011 16:53:04
Author: tg@
Title: How not to create DEB files
Tag: debian

<p class="boxhead">Once upon a time, there was Deb and Ian. That
 was about exactly 18 years ago. We don’t talk about the 0.939000
 format any more, but they eventually settled on:</p><div class="boxtext">
 <pre>
	<b>$</b> ar rc pkg_1.0_all.deb debian-binary control.tar.gz data.tar.gz
	<b>$</b> hexdump -C pkg_1.0_all.deb | head
	00000000  21 3c 61 72 63 68 3e 0a  64 65 62 69 61 6e 2d 62  |!&lt;arch&gt;.debian-b|
	00000010  69 6e 61 72 79 20 20 20  31 33 31 33 36 38 33 35  |inary   13136835|
	00000020  32 39 20 20 31 30 30 36  20 20 32 30 30 20 20 20  |29  1006  200   |
	00000030  31 30 30 36 34 34 20 20  34 20 20 20 20 20 20 20  |100644  4       |
	00000040  20 20 60 0a 32 2e 30 0a  63 6f 6e 74 72 6f 6c 2e  |  `.2.0.control.|
	00000050  74 61 72 2e 67 7a 20 20  31 33 31 33 36 38 33 35  |tar.gz  13136835|
	00000060  32 39 20 20 31 30 30 36  20 20 32 30 30 20 20 20  |29  1006  200   |
	00000070  31 30 30 36 34 34 20 20  31 33 39 31 20 20 20 20  |100644  1391    |
	00000080  20 20 60 0a 1f 8b 08 00  00 00 00 00 00 03 ed 59  |  `............Y|
	00000090  eb 6f db 36 10 f7 d7 f0  af b8 3a 5e 9b 74 b1 f5  |.o.6......:^.t..|
 </pre>
</div><p class="boxfoot">By then, systems were a.out(5), and everything
 was good. <span style="font-size:x-small;">(Of course, if you look at
 the mtimes, you’ll notice I faked this. But it’s really equivalent to
 the real thing.</span></p>
<p class="boxhead">But oh horror! GNU binutils, not always everyone’s
 friend, switched from using BSD style “Unix Archiver” libraries in
 ar(1) to SYSV style libraries on elf(5) systems:</p><div class="boxtext">
 <pre>
	<b>$</b> ar rc on-elf debian-binary control.tar.gz data.tar.gz
	<b>$</b> hexdump -C on-elf | head
	00000000  21 3c 61 72 63 68 3e 0a  64 65 62 69 61 6e 2d 62  |!&lt;arch&gt;.debian-b|
	00000010  69 6e 61 72 79 2f 20 20  31 33 31 33 36 38 33 35  |inary/  13136835|
	00000020  32 39 20 20 31 30 30 36  20 20 32 30 30 20 20 20  |29  1006  200   |
	00000030  31 30 30 36 34 34 20 20  34 20 20 20 20 20 20 20  |100644  4       |
	00000040  20 20 60 0a 32 2e 30 0a  63 6f 6e 74 72 6f 6c 2e  |  `.2.0.control.|
	00000050  74 61 72 2e 67 7a 2f 20  31 33 31 33 36 38 33 35  |tar.gz/ 13136835|
	00000060  32 39 20 20 31 30 30 36  20 20 32 30 30 20 20 20  |29  1006  200   |
	00000070  31 30 30 36 34 34 20 20  31 33 39 31 20 20 20 20  |100644  1391    |
	00000080  20 20 60 0a 1f 8b 08 00  00 00 00 00 00 03 ed 59  |  `............Y|
	00000090  eb 6f db 36 10 f7 d7 f0  af b8 3a 5e 9b 74 b1 f5  |.o.6......:^.t..|
 </pre>
</div><p class="boxfoot">Can you spot the difference?</p>
<p class="boxhead">Of course, ELF is what you want™, so there is
 little choice. Unix Archiver libraries are system dependent, and
 no format has ever been normed, but DEB files use it as format…
 so what is one to do?</p><div class="boxtext">
 <pre>
	<b>$</b> GNUTARGET=a.out-i386-linux ar rc with-aout \
	<b>&gt;</b> debian-binary control.tar.gz data.tar.gz
	<b>$</b> md5sum pkg_1.0_all.deb with-aout on-elf
	248f78d42f8ca8f2a3560f9800b2bf01  pkg_1.0_all.deb
	248f78d42f8ca8f2a3560f9800b2bf01  with-aout
	09eca70c9b11b6b55bbadcab5c3201fb  on-elf
 </pre>
</div><p class="boxfoot">“OK, and what do I do on my Debian/m68k system?”</p>
<p class="boxhead">ar(1) uses bfd, and GNU binutils can not only forcibly
 set the target emulation but also show them:</p><div class="boxtext">
 <code>
	<tt style="font-weight:bold;">debian_m68k$</tt> ar -h 2&gt;&amp;1 | grep '^ar: supported targets'<br />
	ar: supported targets: elf32-m68k a.out-m68k-linux elf32-little elf32-big plugin srec symbolsrec verilog tekhex binary ihex trad-core<br />
	<tt style="font-weight:bold;">debian_i386$</tt> ar -h 2&gt;&amp;1 | grep '^ar: supported targets'<br />
	ar: supported targets: elf32-i386 a.out-i386-linux pei-i386 elf32-little elf32-big elf64-x86-64 elf32-x86-64 pei-x86-64 elf64-l1om elf64-k1om elf64-little elf64-big plugin srec symbolsrec verilog tekhex binary ihex trad-core<br />
	<tt style="font-weight:bold;">debian_i386$</tt> ar -h 2&gt;&amp;1 | grep '^ar: supported targets' <tt style="font-weight:bold;"># binutils-multiarch</tt><br />
	ar: supported targets: elf32-i386 a.out-i386-linux pei-i386 elf32-little elf32-big elf64-alpha ecoff-littlealpha elf64-little elf64-big elf32-littlearm elf32-bigarm elf32-hppa-linux elf32-hppa elf64-x86-64 elf32-x86-64 elf64-l1om elf64-k1om elf64-ia64-little elf64-ia64-big pei-ia64 elf32-m68k a.out-m68k-linux coff-m68k versados ieee a.out-zero-big elf32-tradbigmips elf32-tradlittlemips ecoff-bigmips ecoff-littlemips elf32-ntradbigmips elf64-tradbigmips elf32-ntradlittlemips elf64-tradlittlemips elf32-powerpc aixcoff-rs6000 elf32-powerpcle ppcboot elf64-powerpc elf64-powerpcle aixcoff64-rs6000 aix5coff64-rs6000 elf32-s390 elf64-s390 elf32-shbig-linux elf32-sh-linux elf32-sh64-linux elf32-sh64big-linux elf64-sh64-linux elf64-sh64big-linux elf32-sparc a.out-sparc-linux elf64-sparc a.out-sunos-big pei-x86-64 elf32-m32r-linux elf32-m32rle-linux elf32-spu plugin srec symbolsrec verilog tekhex binary ihex trad-core<br />
	<tt style="font-weight:bold;">mirbsd_i386$</tt> ar -h 2&gt;&amp;1 | grep '^ar: supported targets'<br />
	ar: supported targets: elf32-i386 coff-a29k-big a.out.adobe aix5coff64-rs6000 a.out-zero-big a.out-mips-little epoc-pe-arm-big epoc-pe-arm-little epoc-pei-arm-big epoc-pei-arm-little coff-arm-big coff-arm-little a.out-arm-netbsd pe-arm-big pe-arm-little pei-arm-big pei-arm-little b.out.big b.out.little efi-app-ia32 efi-app-ia64 elf32-avr elf32-big elf32-bigarc elf32-bigarm elf32-bigarm-symbian elf32-bigarm-vxworks elf32-bigmips elf32-cr16c elf32-cris elf32-crx elf32-d10v elf32-d30v elf32-dlx elf32-fr30 elf32-frv elf32-frvfdpic elf32-h8300 elf32-hppa-linux elf32-hppa-netbsd elf32-hppa elf32-i370 elf32-i386-freebsd elf32-i386-vxworks elf32-i860-little elf32-i860 elf32-i960 elf32-ia64-hpux-big elf32-ip2k elf32-iq2000 elf32-little elf32-littlearc elf32-littlearm elf32-littlearm-symbian elf32-littlearm-vxworks elf32-littlemips elf32-m32r elf32-m32rle elf32-m32r-linux elf32-m32rle-linux elf32-m68hc11 elf32-m68hc12 elf32-m68k elf32-m88k elf32-mcore-big elf32-mcore-little elf32-mn10200 elf32-mn10300 elf32-msp430 elf32-nbigmips elf32-nlittlemips elf32-ntradbigmips elf32-ntradlittlemips elf32-openrisc elf32-or32 elf32-pj elf32-pjl elf32-powerpc elf32-powerpc-vxworks elf32-powerpcle elf32-s390 elf32-sh elf32-shbig-linux elf32-shl elf32-shl-symbian elf32-sh-linux elf32-shl-nbsd elf32-sh-nbsd elf32-sh64 elf32-sh64l elf32-sh64l-nbsd elf32-sh64-nbsd elf32-sh64-linux elf32-sh64big-linux elf32-sparc elf32-tradbigmips elf32-tradlittlemips elf32-us-cris elf32-v850 elf32-vax elf32-xstormy16 elf32-xtensa-be elf32-xtensa-le elf64-alpha-freebsd elf64-alpha elf64-big elf64-bigmips elf64-hppa-linux elf64-hppa elf64-ia64-big elf64-ia64-hpux-big elf64-ia64-little elf64-little elf64-littlemips elf64-mmix elf64-powerpc elf64-powerpcle elf64-s390 elf64-sh64 elf64-sh64l elf64-sh64l-nbsd elf64-sh64-nbsd elf64-sh64-linux elf64-sh64big-linux elf64-sparc elf64-tradbigmips elf64-tradlittlemips elf64-x86-64 mmo pe-powerpc pei-powerpc pe-powerpcle pei-powerpcle a.out-cris demo64 ecoff-bigmips ecoff-biglittlemips ecoff-littlemips ecoff-littlealpha coff-go32 coff-go32-exe coff-h8300 coff-h8500 a.out-hp300hpux a.out-i386 a.out-i386-bsd coff-i386 a.out-i386-freebsd a.out-i386-lynx coff-i386-lynx msdos a.out-i386-netbsd i386os9k pe-i386 pei-i386 coff-i860 coff-Intel-big coff-Intel-little ieee coff-m68k coff-m68k-un a.out-m68k-lynx coff-m68k-lynx a.out-m68k-netbsd coff-m68k-sysv coff-m88kbcs a.out-m88k-mach3 a.out-m88k-openbsd mach-o-be mach-o-le mach-o-fat coff-maxq pe-mcore-big pe-mcore-little pei-mcore-big pei-mcore-little pe-mips pei-mips a.out-newsos3 nlm32-alpha nlm32-i386 nlm32-powerpc nlm32-sparc coff-or32-big a.out-pc532-mach a.out-ns32k-netbsd a.out-pdp11 pef pef-xlib ppcboot aixcoff64-rs6000 aixcoff-rs6000 coff-sh-small coff-sh coff-shl-small coff-shl pe-shl pei-shl coff-sparc a.out-sparc-little a.out-sparc-linux a.out-sparc-lynx coff-sparc-lynx a.out-sparc-netbsd a.out-sunos-big sym a.out-tic30 coff-tic30 coff0-beh-c54x coff0-c54x coff1-beh-c54x coff1-c54x coff2-beh-c54x coff2-c54x coff-tic80 a.out-vax-bsd a.out-vax-netbsd a.out-vax1k-netbsd versados vms-alpha vms-vax coff-w65 coff-we32k coff-z8k elf32-am33lin elf32-ms1 srec symbolsrec tekhex binary ihex netbsd-core<br />
 </code>
</div><p class="boxfoot">Wow. While binutils share no single supported
 <em>working</em> target, they can be built multiarch, or (on MirBSD)
 with <tt>--enable-targets=all --enable-64-bit-bfd</tt>. Doesn’t help
 if you want to stay portable: <tt>GNUTARGET=srec</tt> is common on
 all Debian (sid) binutils versions (single or multiarch), but errors
 out on older binutils. The <tt>a.out-*</tt> targets are not common.
 Sure, you could hack around things, but… this is tedious. If you <a
 href="http://grep.be/blog/en/computer/debian/m68k/revival">follow
 things</a> or know me a little, you might <em>already have guessed</em>
 that I wouldn’t let that stand.</p>
<p class="boxhead">pax(1) to the rescue. On MirBSD, we use paxtar,
 which has cpio(1) and tar(1) front-ends and supports multiple formats
 (4 cpio and 2 tar variants) and has already been extended a lot and
 is lovingly called <tt>paxmirabilis</tt> (mirabilos’ peace in Latin)
 – it has options to anonymise archives: set uid and gid to zero, set
 mtime to zero, (for ustar) only write the numeric uid and gid to the
 archive, (for cpio formats) serialise inodes and device information,
 write content of hardlinked files only once (breaks partial extraction
 but saves <em>a lot</em> of space, e.g. 2 MiB off the Grml initrd.gz).
 And, recently, the ability to append a trailing slash to pathnames of
 ustar members which are directories (GNU tar does it – and I thought
 some Debian utilities check for it). So why not… (the <tt>-M dist</tt>
 and <tt>fakeroot</tt> set the uid/gid to 0)</p><div class="boxtext">
 <pre>
	<b>$</b> find debian-binary control.tar.gz data.tar.gz | \
	<b>&gt;</b> mircpio -oHar -Mdist &gt;with-mircpio
	<b>$</b> mirpax -w -M dist -f with-mirpax -x ar \
	<b>&gt;</b> debian-binary control.tar.gz data.tar.gz
	<b>$</b> mirtar -M dist -A -cf with-mirtar \
	<b>&gt;</b> debian-binary control.tar.gz data.tar.gz
	<b>$</b> GNUTARGET=a.out-i386-linux fakeroot ar rc with-aout-ar \
	<b>&gt;</b> debian-binary control.tar.gz data.tar.gz
	<b>$</b> md5sum with-*
	a466e2fd57cdee141fe585a43245548f  with-aout-ar
	a466e2fd57cdee141fe585a43245548f  with-mircpio
	a466e2fd57cdee141fe585a43245548f  with-mirpax
	a466e2fd57cdee141fe585a43245548f  with-mirtar
 </pre>
</div><p class="boxfoot"><span xml:lang="fr">Voilà.</span> I got it,
 and even appending is possible. It supports the BSD format with special
 focus on DEB files, and deals with long filenames, but not symbol or
 filename tables (used by ranlib(1) or strange formats, respectively,
 but since we don’t create <tt>*.a</tt> files to use with some native
 linker/binder/loader, we don’t need that anyway).</p>
<p class="boxhead">On extraction (oh, and listing!) it deals with SYSV
 style filenames as well.</p><div class="boxtext">
 <pre>
	<b>$</b> mirtar tvf on-elf
	-rw-r--r--  1 tg       tg          4 Aug 18 16:05 debian-binary
	-rw-r--r--  1 tg       tg       1391 Aug 18 16:05 control.tar.gz
	-rw-r--r--  1 tg       tg      18135 Aug 18 16:05 data.tar.gz
	<b>$</b> mirtar tvf with-aout
	-rw-r--r--  1 tg       tg          4 Aug 18 16:05 debian-binary
	-rw-r--r--  1 tg       tg       1391 Aug 18 16:05 control.tar.gz
	-rw-r--r--  1 tg       tg      18135 Aug 18 16:05 data.tar.gz
 </pre>
</div><p class="boxfoot">One of the real benefits is that you can use
 the front-ends interchangably – for example, “mirtar tzf foo.cpio.gz”
 would work (which GNU tar can’t do), and mircpio’s ustar implementation,
 unlike GNU cpio’s, is not horribly broken.</p>
<p>Of course, there are some drawbacks: it’s not GNU tar or GNU cpio,
 so there are absolutely zero <tt>--long-options</tt>. Some of their
 features are missing (but tar’s <tt>-O</tt> is implemented now), so
 it’s no replacement (but very well usable alongside it). The format
 called <tt>pax</tt>, committee-designed to replace ustar, isn’t yet
 supported ironically, but that’s on the TODO.</p>
<p class="boxhead">So, what do you think?</p><div class="boxtext">
 <pre>
	<b>tg@frozenfish:~/Debs/dists/sid/wtf/Pkgs/mircpio $</b> ll *.deb
	-rw-r--r-- 2 tg freewrt 78140 Aug 17 11:04 mircpio_20110817-0wtf2_amd64.deb
	-rw-r--r-- 3 tg freewrt 72262 Aug 17 11:00 mircpio_20110817-0wtf2_i386.deb
	-rw-r--r-- 1 tg freewrt 67446 Aug 17 18:21 mircpio_20110817-0wtf2_m68k.deb
 </pre>
</div><p class="boxfoot">Should I upload this to Debian proper?</p>
<p>As for the licence: 3-clause UCB (and 2-clause BSD, which is a
 subset of it), so no problem. I’m asking because the other package
 which I had been using for a <em>long</em> time and not uploaded,
 <a href="http://packages.debian.org/jupp">jupp</a>, got uploaded <a
 href="@@RELPATH@@permalinks/wlog-10_e20110727-tg-g10043.htm">recently</a>
 (during DebConf) on user input (people wondered why it did not yet
 exist in Debian proper). I guess the old saying “if it’s not in Debian,
 it doesn’t exist” holds true in many parts of the OSS world.</p>
<p>It’s up to date wrt. standards btw, and lintian-clean save for two
 pedantic-class warnings (no upstream changelog file, no homepage link)
 which aren’t fulfillable (could link this wlog entry as homepage).</p>
<p>If you know <a href="https://alioth.debian.org/">Alioth</a> you’re
 familiar with the software formerly known as SourceForge, formerly
 known as GForge, currently known as FusionForge. My employer both
 uses it and contributes to it, we run an adapted (mostly themed,
 prototyping new functions that often end up in FusionForge itself,
 and backporting functions from FF to our “production codebase”)
 version.</p><p class="boxhead">I’ve backported the extratabs plugin
 to appease project managers and other non-technical people while we
 move our codebase to FF 5.1, and I did so on an installed version of
 the plugin rather than the source because the latter was tightly
 integrated with rather heavy packaging style changes.</p><div class="boxtext">
 <pre>
	[…]
	dh_builddeb
	# create fusionforge-plugin-extratabs binary package
	toplev=$$(pwd); cd plugins/fusionforge-plugin-extratabs; \
	p=$$(print -r -- $$(sed -n '/^Package: /s///p' C/control | head -1)); \
	v=$$(print -r -- $$(sed -n '/^Version: /s///p' C/control | head -1)); \
	a=$$(print -r -- $$(sed -n '/^Architecture: /s///p' C/control | head -1)); \
	d=$${p}_$${v}_$${a}.deb; \
	rm -f $$toplev/../$$d control.tar.gz data.tar.gz; \
	(cd control; find . | fgrep -v /.svn | sort | \
	    mircpio -oC512 -Hustar -M0x0B -Mgslash) | gzip -n9 &gt;control.tar.gz; \
	(cd data; find . | fgrep -v /.svn | sort | \
	    mircpio -oC512 -Hustar -M0x0B -Mgslash) | gzip -n9 &gt;data.tar.gz; \
	mirtar -M dist -Acf $$toplev/../$$d debian-binary cont*gz dat*gz; \
	rm -f control.tar.gz data.tar.gz; \
	cd $$toplev; dpkg-distaddfile $$d non-free/devel optional
 </pre>
</div><p class="boxfoot">The hardest part of extending debian/rules
 with that was to get the autobuild and dpkg-distaddfile call right.
 This works, even though I’d call it a temporary kludge. (No need to
 tell me I should have used &amp;&amp; – I know. And I only shell out
 to mksh(1) because the “inner” part was already there from before,
 when I still used ar(1). This was slightly edited for the wlog.)</p>
<p>In the meanwhile, apt-extracttemplates can deal with SYSV style
 filenames in DEB files – on Debian sid, but not on K?buntu hardy,
 which some people are using as Desktop OS still…</p>
<p><strong>Update</strong> 03.03.2012 – Jonathan Nieder replied
 quickly with a suggestion to instead take over the “pax” package
 in Debian. Eventually, I uploaded pax (1:20120211-1) from the
 former “mircpio” package to Debian, after I managed to talk to
 its previous maintainer Bdale Garbee (thanks for handing over).
 It is now present in Debian wheezy and Zubunt! precise as /bin/pax
 with /bin/paxcpio and /bin/paxtar offering the other interfaces.</p>
----
Date: 18.08.2011 22:00
Author: tg@
Title: New MirBSD/i386 NetInstall snapshot
Tag: news snapshot

<p>Almost ☺ in time for FrOSCon there’s a new binary snapshot of
 MirBSD-current (10uAF-20110818) compiled, right now waiting for
 me to do the usual post-compilation work of preparing the cdrom
 and floppy images for serial console, signing and uploading. Of
 course, the online manpages will be updated then as well.</p>
<p>The snapshot will, as usual, end up on the mirrors, i.e.</p><ul>
 <li><a href="https://www.mirbsd.org/MirOS/current/">Germany main</a>
  (Strato) secure HTTP</li>
 <li><a href="http://pub.allbsd.org/MirOS/current/">Japan</a>
  (AllBSD.org) insecure HTTP</li>
</ul>
<p>We’ll also have it with us at FrOSCon. Maybe on CDs, but on a
 laptop ready for netboot and netinstall is a promise.</p>
<p><strong>Update</strong> 20.08.2011 – we’ve got an ISO:</p><ul>
 <li>MD5 (MIRB0818.ISO) = 805c4a34bae523ef5d838e79ecdcdad8</li>
 <li>RMD160 (MIRB0818.ISO) = 93df98d24b2d877502e7be8af580907311d2d8cc</li>
 <li>SHA1 (MIRB0818.ISO) = 6dacb045675184c06a00401357a0a510dd3e6edb</li>
 <li>SIZE (MIRB0818.ISO) = 727711744</li>
 <li>TIGER (MIRB0818.ISO) = ff0c145b93988c306530963fd881ad7972d5eb2d2e0ce298</li>
 <li style="list-style:none;"><a href="@@RELPATH@@bt.htm#s110818">BitTorrent
  download</a> is [no longer, 2014-05-13] available</li>
</ul>
----
Date: 20.08.2011 21:01
Author: tg@
Title: FrOSCon 2011, Day 1
Tag: debian event geocache

<p>Built the ISO [torrent link deleted 2014-05-13] in the
 morning, today. Finally. Whew. It was much too warm in the mēnsa,
 and why did I have to get up so early anyway? Real Conferences™
 don’t start before 10 o’clock, and there are no sensible activities
 before 11 o’clock anyway…</p>
<p>Talked to a lot of people, introduced my favourite Fedora Packager
 to Geocaching. Now my throat is sore and I’m tired. Social Event was
 not my case, as usual. (And even the vegetarian food now costs money
 as opposed to, I think, two years ago.) At least dry and not too
 loud. Still, best thing of FrOSCon is the Friday Evening Jugoslawian
 Food Mealtime ;-)</p>
----
Date: 26.08.2011 14:44
Author: tg@
Title: Netsplit – so let’s answer in the wlog
Tag: debian pcli security

<pre>
	14:31⎜*<b>&lt;</b>* Signoff: XTaran (*.net *.split)</pre>
<p>… doesn’t prevent me from telling him…</p>
<pre xml:lang="de-DE-1901">
	14:39⎜&lt;mira|AO&gt; XTaran: n̲i̲e̲ n̲i̲e̲ n̲i̲e̲ n̲i̲e̲ n̲i̲e̲ n̲i̲e̲ n̲i̲e̲
	     ⎜empfiehlt man k̶i̶l̶l̶a̶l̶l̶, i̲m̲m̲e̲r̲ nur p̲k̲i̲l̲l̲!</pre>
<p>“Now playing: Monzy — kill dash” ⇒ good idea… ☺</p>
<hr />
<p class="boxhead">By the way, you were probably
 looking for this…</p><div class="boxtext">
 <pre>
     -x      Require an exact match of the process name, or argument list if
             -f is given. The default is to match any substring.
 </pre>
</div><p class="boxfoot">… excerpt from the pkill(1) manual page,
 where you can see it stems from grep(1) clearly.</p>
<hr />
<p>Yes, this website (and thus the RSS export) is Lynx on uxterm
 -fn -misc-fixed-medium-r-normal--18-120-100-100-c-90-iso10646-1
 -fw -misc-fixed-medium-r-normal-ko-18-120-100-100-c-180-iso10646-1
 on XFree86® optimised. Your browser might not do combining.</p>
----
Date: 27.08.2011 19:24
Author: tg@
Title: FrOSCon 2011, Day 0 and 2
Tag: debian event geocache

<p>On Day 0, we were at my favourite Jugoslawian restaurant, and
 during eating and <i>verpeiling</i>, Andi took some pictures:<br /><a
 href="@@RELPATH@@pics/FrOSCon_2011/fc11-jj.jpg"><img
 alt="Jana und Jupp “ich habe die Macht” cnuke@"
 src="@@RELPATH@@pics/FrOSCon_2011/fc11_jj.jpg" /></a> <a
 href="@@RELPATH@@pics/FrOSCon_2011/fc11-hc.jpg"><img
 alt="Henni und ciruZ (Jonathan)"
 src="@@RELPATH@@pics/FrOSCon_2011/fc11_hc.jpg" /></a> <a
 href="@@RELPATH@@pics/FrOSCon_2011/fc11-gb.jpg"><img
 alt="gecko2@ “geh weg” und bsiegert@ “waaah!” deer in the headlights"
 src="@@RELPATH@@pics/FrOSCon_2011/fc11_gb.jpg" /></a><br />
 Take special note of the fun expressions everyone has…</p>
<p>Day 2, nothing of note at the conference itself – according to
 Jana, the only interesting talk (that tcpdump(8) GUI) was cancelled,
 and everything else was PHP and Web 2.0 crap. The food also was
 different, at least what I got, from Day 1. But it wasn’t <em>as</em>
 hot as on the previous day, and we did more socialising. I also
 managed to get the MirBSD ISO distributed some more.</p>
<p>Then I took my fellow DDs Enrico and madamezou geocaching for
 their first time, together with benz; they then took a Travelbug
 I found on Day 1 (with rsc) to Italy so it’ll end up in Rome, a
 next step on its mission.</p>
<p>Other rarely-seen people, such as Dr. Pfeffer, made an appearance,
 but overall the second day was quite relaxed. Ah, and Benny is a
 Doctor in Germany now as well.</p>
<p>On Monday, I slept quite a bit ☺</p>
----
Date: 01.09.2011 21:36
Author: tg@
Title: Subversion for Dummies (or visitors of the #cvs IRC channel)
Tag: debian fun rant

<p>Oh well – someone came into the <tt>#cvs</tt> channel on <a
 href="@@RELPATH@@irc.htm">IRC</a> without a clue, again. I’ve
 made a nice picture to show “the competition” (rival, whatever)
 to newbies (<em>warning</em>, sarcasm ahead)…</p><!-- RSS stop -->
<p><img src="@@RELPATH@@pics/wlog/svn43cvs.jpg"
 alt="Subversion (svn, Suckwürstchen) for Dummies – or #cvs
 channel visitors • branches tags trunk" /></p>
<p>SCNR.</p>
<p>But trying to “cvs co” a websvn repository view… honestly!</p>
<p>Yes, I’m biased. And known to be proud of the things I use.</p>
----
Date: 03.09.2011 17:20
Author: tg@
Title: MirOS BSD users portrait – polarhome, Sweden
Tag: news

<p>Zoltan Arpadffy has let us know that he has set up a MirBSD
 installation at <a href="http://polarhome.com/">polarhome</a>
 in Stockholm, to aid its “purpose [to] serve the healthy part
 of the already, rather badly MS infected Universe - and MirOS
 is definetevly on that part”. He wrote that “MirBSD is a very
 nice easy to use BSD system”, thanking us with “gratitude and
 respect for developing a such a nice OS”. He also sent a list
 of things he ran into while installing (although we can guess
 some of them are related to using VirtualBox, which is not at
 all supported, as base) so we can fix them, and offered help,
 e.g. in adding ports of software they use.<br />Well, Zoltan,
 you’re definitively welcome ☺</p>
<p>polarhome.com is non commercial, educational effort for
 popularization of shell enabled operating systems and Internet
 services, offering shell accounts, mail and other online
 services on all available systems (currently on Linux, OpenVMS,
 Solaris, OpenIndiana, AIX, QNX, IRIX, HP-UX, Tru64, SCO OpenUnix,
 UnixWare, FreeBSD, OpenBSD, NetBSD, DragonFly BSD, MirBSD, Ultrix
 and OPENSTEP).</p>
<p>Well guys, talk to us – we know we have one to several hundred
 users world-wide but don’t really get a lot of feedback (so we
 assume you like it).</p>
----
Date: 29.07.2011
Author: tg@
Title: Photos from the (inofficial) DC11 Booth Party ☺
Tag: debian event fun

<p>The pictures are hypertext references to large versions. Of
 course, your photographer (me, although Samuel helped to set
 up the PocketPC’s camera application correctly, 10x) also had
 some Kruškovac ☺ (imported from Croatia into Bosnia)…</p>
<p><a href="@@RELPATH@@pics/wlog/dc11-bp1.jpg"><img
 alt="spontaneous late night meeting at Front Desk"
 src="@@RELPATH@@pics/wlog/dc11_bp1.jpg" /></a></p>
<p>Of course we were not above closing Front Desk either ☻☺</p>
<p><a href="@@RELPATH@@pics/wlog/dc11-bp2.jpg"><img
 alt="Best Friends" src="@@RELPATH@@pics/wlog/dc11_bp2.jpg" /></a></p>
----
Date: 03.09.2011 17:34
Author: tg@
Title: Saturday Noon Cat wlog-entry-writing
Tag: debian fun geocache

<p>As <a href="@@RELPATH@@permalinks/wlog-10_e20080725-tg.htm">written
 about here earlier</a>, cats have a nice life. I walked into my home
 seeing three cats in a row, all black: two lazing around, the third
 (with white spots, and belonging to a different neighbour from the
 other two) ambulating. I went up and got my PocketPC with the already
 mentioned camera application to take a shoot. Sadly, the more shy cat
 went away, but I got some pictures of the other two – here they are,
 internet photo stars ☺ follow the hyperlink to get a large version.</p>
<p><a href="@@RELPATH@@pics/wlog/cats-1.jpg"><img
 alt="two of three black cats I met today… in a row!"
 src="@@RELPATH@@pics/wlog/cats_1.jpg" /></a></p>
<p>Later I came back from geocaching (2 GC.COM-only, 1 OC-only *yay!*
 found, one not found due to not taking <em>any</em> hardware with me)
 the bigger guy lazed around in the bush next to where I usually park
 my bike. Lucky…</p>
----
Date: 04.09.2011 11:44
Author: tg@
Title: Cat weather
Tag: debian fun

<p class="mirbsdwebsitehidefromnonrss">Another cat posting,
 about 100 KiB worth of images embedded so follow to the
 main article to read it, I don’t want Planet readers to
 suffer from traffic overuse.</p><!-- RSS stop -->
<p>Hot and humid (it’s rained a bit overnight, but has almost dried
 up quickly) seems to be cat weather. I went to buy breakfast at the
 local bakery when three cats lay around the house door in a half
 circle – my two black friends from the last posting and their human
 can opener’s third owner. When I came back I wondered whether the
 small guy wanted to travel:<br /><img
 alt="cat car" src="@@RELPATH@@pics/wlog/cats-2.jpg" /><br /><img
 alt="what could that human possibly want from me? (focus follows eyes)"
 src="@@RELPATH@@pics/wlog/cats-3.jpg" /></p>
<p>The big guy has hidden indoors, but needed only very little coaxing
 to head back outside in a measured speed:<br /><a
 href="@@RELPATH@@pics/wlog/cats-4.jpg"><img
 alt="can you see me?" src="@@RELPATH@@pics/wlog/cats_4.jpg" /></a></p>
<p>The car’s owner arrived when I closed the door behind that cat,
 and not only did the little guy jump off… but also did the third
 cat… get out from <em>under</em> the car. Huh…</p>
----
Date: 14.09.2011 20:54
Author: tg@
Title: MirBSD online manpages major facelift
Tag: debian news pcli snapshot

<p>Our <a href="@@RELPATH@@htman/i386/">MirBSD online manual pages and
 other assorted BSD documentation</a> (except of course the merely copied
 ncurses, lynx etc. documentation and the texinfo generated HTML pages)
 has just gained a major facelift. They look alike in lynx(1) – best web
 browser ever – and less(1)/man(1) now, and remind of a DEC VT420 on a
 CSS capable Buntbrause.</p>
<p>Thanks to our contributor XTaran for aid with the colour scheme!</p>
<p>Since these are generated from catmanpages, heuristics are used for
 things like where should bold/underline begin/end (since nroff(1) is
 not always the brightest… but working on that), and hyperlinks can only
 be generated for other manpage references (whose targets may or may not
 exist, for example if they aren’t part of MirOS base/XFree86®). But on
 the other hand, Valid XHTML/1.1 and CSS speaks for itself ☻☺</p>
----
Date: 20.09.2011 22:36
Author: bsiegert@
Title: pkgsrc frozen
Tag: pkgsrc

<p>So the pkgsrc tree has been frozen in preparation for the 2011Q3
 release. I managed to sneak in a few interesting commits just after the
 deadline *cough*. Firstly, Python 2.6 and 2.7 now build fine. The
 corresponding <a href="http://bugs.python.org/issue12976">Python
 bug</a> was marked wontfix though&mdash;even though it only touches six
 lines or so. Apparently they have a policy not to support what they
 call “marginal platforms” even when people submit them patches. Compare
 to perl, where more changes were required, but they were all committed
 upstream, and all new releases support MirBSD out of the box.</p>

<p>The second change concerns X11. Many new packages want to have X11R7
 and/or xcb libraries, which our X11 does not provide. Thus, after a
 some discussion on tech-pkg, I switched the MirBSD platform to modular
 X libraries. This means that libX11 etc. are built as packages inside
 pkgsrc instead of relying on <tt>/usr/X11R6</tt>. If you already use
 pkgsrc, you might need to recompile X11-using packages after this
 change, or use <tt>pkg_rolling-replace</tt>. Incidentally, I had to fix
 a few bugs in libX11 ;).</p>

<p>The final thing concerns the texlive packages, which should all be
 working now. They were using <tt>pax -rw</tt> to copy files around
 without creating the destination directory first. This is an error
 condition in paxmirabilis, and it should also be elsewhere. For
 example, pax in Darwin accepts it although the manpage says
 otherwise. Strange.</p>
----
Date: 30.09.2011 16:07:21
Author: tg@
Title: Improvements welcome
Tag: debian tip
Comment: the mtime of this item is not by accident…

<p>No I don’t really know any SQL. In fact, even at vocational
 school, where we focussed on database normalisation anyway, I
 tried hard to avoid the topic. Feel free to access here my <a
 href="http://www.postgresql.org/docs/8.4/interactive/">entire
 knowledge about SQL</a> ☺ (I did use Amaya, Arena and Arachne
 though. Liked only Arachne out of these three, and then, only
 under DOS, not its Unix version. Maybe the WWW could be named
 AAA instead? But then, lynx(1) is the one true browser…)</p>
<p>Ah, well. While at it… the entirety of my Perl knowledge is
 here: perltoc(1) with quick links to perlfunc(1).</p>
<p>The entirety of my (X)HTML and ECMAscript knowledge, DE: <a
 href="http://de.selfhtml.org/">SELFHTML</a>; although, the <a
 href="http://www.w3.org/TR/xhtml11/">spec and DTD</a> helped;
 and to write my notes on JSON, I took a peek at the formal <a
 href="http://www.ecma-international.org/publications/files/ECMA-ST/Ecma-262.pdf">ECMAscript spec</a>
 as well… à propos, does anyone know a (good enough) indent(1)
 equivalent for ECMAscript, as I am trying to strip down some,
 inherited (GPL, yes) code for a hobby project, but Geo-people
 seem to produce illegible code?</p>
----
Date: 06.10.2011 22:42
Author: tg@
Title: eMail
Tag: debian pcli rant tip

<p>Would MTAs <strong>please</strong> stop sending hi-bit7 messages
 to other MTAs which do not advertise <tt>8BITMIME</tt>! Recode it
 to QP or BASE64, damnit! The receiving MTA is entitled to strip the
 set bit7, which kinda makes things hard to read (while I <a
 href="http://fsinfo.noone.org/~abe/typing-8bit.html">know</a> how
 to deal with <tt>blvde Stra_e</tt>, the advent of UTF-8 makes that
 <tt>blC6de StraC?e</tt>, introduces C0 control characters and makes
 typographic quotation marks into NUL-containing octet sequences (as
 their UTF-8 representation contains 0x80 octets) which let every
 sensible MDA terminate the line there). I even filed in the Debian
 BTS against the BTS (might be Drexim's fault, though).</p>
<p>Would MUAs <em>please</em> default to Quoted-Printable!</p>
<p>And mail hosters should use the same server when retrying delivery,
 to benefit greylisting. Or at least publish a list of outgoing IPv4
 addresses they use for sending. Or use IPv6. Oh, and <tt>STARTTLS</tt>,
 while we are on my wishlist.</p>
<p>It's a sad day when the percentage of correctly encoded eMail
 messages in my INBOX is smaller than that of my Spambox...</p>
----
Date: 24.10.2011 20:18
Author: tg@
Title: benz’ wedding, fun before
Tag: debian event fun

<p>My dear MirBSD co-developer Benny did not only get his Doctor title
 but also recently married. There will be another post detailing this,
 including better photos of the two Doctors and the cake (with a Dæmon
 she made herself) on the wlog, but this is some fun beforehand:</p>
<p><a href="@@RELPATH@@pics/wlog/NoGPLcar.jpg"><img alt="No GPL cars!"
 src="@@RELPATH@@pics/wlog/NoGPLcar.png" /></a></p>
<p>Apparently, it is forbidden in France to drive GPL cars. (Without
 safety valve – but you have to admit the picture was fun. And we were
 like ＷＴＦ？ since the thing actually meant is LPG in German. Just
 like UTC is CUT (Coordinated Universal Time) in English, TUC (Temps
 Universel Coordonné) in French…)</p><!-- RSS stop -->
<p>I’m also working on improving our xterm(1) and GNU screen config,
 and other things. Explaining acronyms on our webpages is also coming
 some time. Benny is importing weird stuff from TNF for better pkgsrc®
 support, so there <em>is</em> activity. Just we’ve got dayjobs and a
 life… and mksh(1) still rocks (pdksh got orphaned in Debian today).</p>
----
Date: 29.10.2011 20:57
Author: tg@
Title: Geocaching-Literaturverlosung in Franken
Tag: geocache
Language: de-DE-1901

<p>Es gibt eine Literaturverlosung im Themengebiet Geocaching auf <a
 href="http://www.geocaching-franken.de/twitter-news/verlosung-es-gibt-was-zu-gewinnen-2x-outlife-geocaching-2x-geocaching-fachbuch/">dieser
 Geocaching Franken Seite</a>. Man kann dort zwei Fachbücher „Geocaching –
 GPS-Freizeitspaß für Abenteurer” und zwei Exemplare der Zeitschrift
 „Out<i>life</i>“ zu ebendiesem Thema gewinnen.</p>
<p>Nun hoffe ich natürlich, einen Gewinn zu reißen, gerade weil ich der
 Meinung bin, dies als <strong>stolzer Opencacher</strong> (und damit
 meine ich das <a href="http://opencaching.eu/">echte OpenCaching-Netzwerk</a>
 und nicht den billigen, ungepflegten Garmin-Ripoff (OC.COM alias OXnnnnn),
 der vor einiger Zeit eine feindliche Übernahme des guten Namens versucht
 hat). Stets im Kampf gegen diese, die unseren Sport zu kommerzialisieren
 versuchen mit Premiummitgliedschaften bei GC.COM; gekauften Anwendungen für
 Windows®, um ihr Profi-Navi besser bedienen zu können; und dergleichen.
 Außerdem hoffe ich, hierduch einen besseren Einstieg in die Rätselcaches,
 die mir bisher, durch Mangel an Kontakten in der Geocacher-Stammtischrunde
 (fühle mich dort ein wenig wie ein Windows®-Nutzer beim Linuxstammtisch…),
 sich nicht erschlossen.</p>
<p>Außerdem bin ich gerade, auf Basis der OC.de-Karte, an einer „MirKarte“
 am basteln, die einfach nur eine Google-und-OSM-Karte, die auch in älteren
 Browsern wie Opera 9 funktioniert, ist (relativ statisch, aber mit einigen
 Features wie der supergenialen Anzeige der Koordinaten unterm Mauszeiger).
 Bin noch nicht fertig, da ich mein ECMAscript erst auffrischen muß und auch
 die Maps-API-Dokumentation nochmal lesen will, aber immerhin. (Außerdem mag
 ich minimalen Code, und was ich bisher habe ist bloated. Und buggy.)</p>
<p>Vielleicht weiß man auch meine Beiträge zu den ganzen Open Source Projekten
 zu schätzen?</p>
<p>(<tt>maps.geocaching.de</tt> scheint down zu sein, und weder die neue neue
 noch die neue alte GC.COM-Karte tun im Opera… somit <em>kann</em> ich im
 Moment sowieso, von <a href="http://www.cachewolf.de/">CacheWolf</a> und
 Umkreissuche mal abgesehen, nur nach OC-Caches Ausschau halten.)</p>
<p>So, dann mal Gruß nach Franken aus der Eifel. Ich werde auch den Franken,
 die ich kenne, den GAV-Button nahelegen.</p>
----
Date: 22.11.2011 19:10
Author: tg@
Title: Those small nice tools we all write
Tag: debian mksh news pcli release

<p>This is both a release announcement for the next installment of The
 MirBSD Korn Shell, <a href="@@RELPATH@@mksh.htm#r40c">mksh R40b</a>,
 and a follow-up to <a href="http://pusling.com/blog/?p=230">Sune’s
 article about small tools of various degrees of usefulness</a>.</p>
<p>I hope I don’t need to say too much about the first part; mksh(1)
 is packaged in a gazillion of operating environments (dear Planet
 readers, that <em>of course</em> includes Debian, which occasionally
 gets a development snapshot; I’ll wait uploading R40c until that <a
 href="http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=633479">two
 month fixed gcc bug</a> will <em>finally</em> find its way into the
 packages for armel and armhf). Ah, we’re getting Arch Linux (after
 years) to include mksh now. (Probably because they couldn’t stand
 the teasing that Arch Hurd included it <em>one</em> day after having
 been told about its existence, wondering why it built without needing
 patches on Hurd…) MSYS is a supposedly supported target now, people
 are working on WinAPI and DJGPP in their spare time, and Cygwin and
 Debian packagers have deprecated pdksh in favour of mksh (thanks!).
 So, everything looking well on that front.</p>
<p>I’ve started <a href="https://evolvis.org/projects/shellsnippets/">a
 collection of shell snippets</a> some time ago, where most of “those
 small things” of mine ends up. Even stuff I write at work – we’re an
 Open Source company and can generally publish under (currently) AGPLv3
 or (if extending existing code) that code’s licence. I chose git as
 SCM in that FusionForge instance so that people would hopefully use it
 and contribute to it without fear, as it’s hosted on my current money
 source’s servers. (Can just clone it.) Feel free to register and ask
 for membership, to extend it (only if your shell-fu is up to the task,
 KNOPPIX-style scripts would be a bad style(9) example as the primary
 goal of the project is to give good examples to people who learn shell
 coding by looking at other peoples’ code).</p>
<p>Maybe you like <a href="@@RELPATH@@jupp.htm">my editor</a>, too? At
 OpenRheinRuhr, the Atari people sure liked it as it uses WordStar®
 like key combinations, standardised across a lot of platforms and
 vendors (DR DOS Editor, Turbo Pascal, Borland C++ for Windows, …)</p>
<p>ObPromise: a posting to raise the level of <em>ferrophility</em>
 on the Planet aggregators this wlog reaches (got pix)</p>
----
Date: 18.12.2011
Author: bsiegert@
Title: pkgsrc-2011Q3 binary packages for MirBSD-current
Tag: pkgsrc news

<p>This is a very late announcement. Binary packages for pkgsrc-2011Q3
 are now available on <a
 href="ftp://ftp.netbsd.org/pub/pkgsrc/packages/MirBSD/i386/10uAE_2011Q3/">ftp://ftp.netbsd.org/pub/pkgsrc/packages/MirBSD/i386/10uAE_2011Q3/</a>.
 The repository contains 5330 packages built on MirOS-current. Any MirOS
 BSD version from 2011 should work.</p>

<p>The packages are self-contained in <tt>/usr/pkg</tt>: The VARBASE has
 been set to <tt>/usr/pkg/var</tt>, and the package database is in
 <tt>/usr/pkg/db</tt>. This matches the MirPorts defaults and
 facilitates using pkgsrc and MirPorts side by side.</p>

<p>In this quarterly release, the new default for MirBSD is to use
 “modular” X11, i.e. install Xorg libraries and programs as packages
 instead of using the system X libs. This improves the compatibility
 with many newer programs, which expect for example that the X libraries
 have pkg-config files. This should not change anything for the user,
 however.</p>

<p>For more information on how to use these packages, consult the
 <a href="@@RELPATH@@pkgsrc.htm">pkgsrc page on mirbsd.org</a>
 or the
 <a href="http://www.netbsd.org/docs/pkgsrc/using.html#using-pkg">relevant
 section of the pkgsrc guide</a>.
</p>
----
Date: 28.12.2011 23:06
Author: tg@
Title: MirBSD-current snapshot uploaded, some things gone
Tag: news snapshot

<p>What’s going on in MirOS Project land? Other than all developers
 being buried in dayjob work, of course… (sorry for that, guys; even
 tg@ has now succumbed to an ever-growing backlog but <em>will</em>
 be back, some time)</p>
<p>tg@ uploaded a new MirBSD-current/i386 snapshot (20111228) plus
 a full set of HTML manpages for all architectures (so they all are
 in the new amber style), and redid the usual combined i386+sparc
 <tt>cdrom10.iso</tt> Midi-ISO as well as the netboot.me kit. Older
 binary packages may no longer be supported: the old libgcc_s DLL
 is no longer provided in <tt>fixes10.ngz</tt>, and it may be time
 to reduce the amount of packages in MirPorts to concentrate on
 those worth the effort and receiving enough care.</p>
<p>Thanks to bsiegert@’s amazing work, the pkgsrc® kit of anno 2007
 could finally be deleted. <a href="@@RELPATH@@pkgsrc.htm">The page
 about pkgsrc® on MirOS</a> describes instructions to use instead.
 At some point, we may release a binary bootstrap kit along with
 the snapshots as set ready for pickup by the installer.</p>
<p>No MirGRML based on the latest Grml 2011.12 release will be made.
 We’ll be investigating a possible solution for a flavour of the
 popular GNU/Linux OS to accompany full Triforce Live CDs in the
 future (for now, we’ll keep the old MirGRML 2009.10 on them).</p>
<p>We hope to be able to return to investing more spare (heh…) time
 into development some time. For now, we apologise for the slowed
 down development and reaction even in important subprojects such
 as <a href="@@RELPATH@@mksh.htm">mksh</a>. Occasionally, they do
 have updates, e.g. <a href="@@RELPATH@@jupp.htm#bins">the latest
 Jupp/Win32 release</a>, or fixes in CVS.</p>
----
Date: 04.01.2012 14:23
Author: bsiegert@
Title: Quick! A webserver!
Tag: golang tip

<p class="boxhead">If, like me, you occasionally want to transfer some
 files via
 http&mdash;like the sets for a MirOS installation&mdash;but are much
 too lazy to set up apache, here is a simple web server in nine lines of
 Go:</p><div class="boxtext">
<pre>
	package main

	import (
		"log"
		. "net/http"
	)

	func main() {
		Handle("/", FileServer(Dir(".")))
		log.Fatal(ListenAndServe(":8080", nil))
	}
</pre>
</div><p class="boxfoot">It simply exports the current directory
 via http on port 8080. Neat!</p>
----
Date: 05.01.2012 21:41
Author: tg@
Title: Clone a disc with progress indicator
Tag: debian pcli tip

<p>On <a href="@@RELPATH@@main.htm">MirBSD</a> and other sane OSes,
 you can just press <tt>^T</tt> (Ctrl-T) when dd(1) runs; this sends
 it a <tt>SIGINFO</tt> (cf. sigaction(2)) which asks it to display
 (progress) information to the tty. This includes kFreeBSD, btw.</p>
<p><strong>Update</strong> 07.01.2012 – this also works on Hurd.
 Linux neither has SIGINFO nor (cooked mode tty) support for it.</p>
<p class="boxhead">There’s also pv:</p><div class="boxtext">
 <pre>
	dd if=/dev/mapper/vg01-${customername}--hudson bs=1048576 | \
	    pv -pter -B 1048576 -s 85899345920 | \
	    xz -0 &gt;/mnt/ci-${customername}-snap-20120105-lenny.img.xz
 </pre>
</div><p class="boxfoot">I used this At wOrk today to back up a Jenkins VM
 before upgrading its underlying operating system for evaluation. Here, the
 <tt>-s</tt> flag is the total size (in bytes; don’t forget to multiply by
 1024 when reading from Linux’ /proc/partitions) so pv can calculate a total
 and an ETA; <tt>-B</tt> is the same as <tt>bs</tt>; and xz is the currently
 best compressor to use, in any situation, unless you must stay compatible to
 gzip(1)-only systems. (Except that it’s not under an Open Source licence.)</p>
<p><a href="http://sourceforge.net/projects/clpbar/">clpbar</a> might also
 be worth looking into. XTaran points out sid has this as bar.</p>
<p>PSA: Last of June, 2012, will be a leap second.</p>
----
Date: 22.01.2012 12:58
Author: bsiegert@
Title: Today's piece of Unix history

<p>Courtesy of <a
 href="https://plus.google.com/101960720994009339267/posts/3WDmR2RTTrv">Rob
 Pike on Google+</a> and Richard Kettlewell in the comments:</p>

<p>In Plan 9 and Research Unix, rm(1) also removes empty directories.
 Why doesn't it in Unix? In V7 Unix, only privileged users could
 unlink() a directory. Thus, rmdir(1) was a setuid executable. rm(1)
 actually called rmdir(1) via fork()+exec() in its recursive mode. Of
 course, there were some bugs in rmdir ...</p>
----
Date: 05.02.2012 20:46
Author: bsiegert@
Title: FOSDEM 2012: “pkgsrc on MirBSD”
Tag: event pkgsrc

<p>This weekend, the <a href="http://fosdem.org/2012">FOSDEM 2012</a>
 took place in Brussels. We gave away DVDs with the latest MirOS BSD
 snapshot and <a
 href="http://ftp.netbsd.org/pub/pkgsrc/packages/MirBSD/i386/10uAE_2011Q3/All/">about
 3&nbsp;GiB of binary packages for pkgsrc</a>.</p>

<p>I gave a talk entitled <b>“pkgsrc on MirBSD”</b>. It gives a short
 introduction to both MirBSD and pkgsrc and details how we managed to
 get MirBSD supported as a platform, including some details on the
 new-developer process at the NetBSD foundation. The slides are now
 available <a href="http://slideshare.net/bsiegert/pkgsrc-on-mirbsd">on
 slideshare</a> or <a href="/MirOS/PR/pkgsrc-on-MirBSD.pdf">as a PDF for
 download</a>.&nbsp;&mdash;</p>

<p>The showcase is doing strange things. The NetBSD-current kernel
 panics reproducibly when the network card, an alc, does not have a
 link. Thus, I put it on a switch with no other connection to “fix” the
 problem. Furthermore, I have a half-finished pkg_rolling-replace on the
 NetBSD side; various things now give Memory Errors, including running
 xfce4-session. Oh well. WindowMaker to the rescue … I am planning on
 redoing the setup on this machine anyway, once NetBSD-6-alpha will have
 been branched. I would also like to use LVM to set up the partitions
 for the Xen domains, to avoid going through a vnd(4) device.</p>
----
Date: 20.03.2012 21:49
Author: bsiegert@
Title: blog @ TNF

<p>
 So now I am even
 <a href="http://blog.NetBSD.org/tnf/entry/new_netbsd_flyers_available">posting
  over at TNF</a>
 on <a href="http://blog.NetBSD.org/">blog.NetBSD.org</a>. Julian Fagir
 made new NetBSD flyers, and I committed them to the TNF website.
</p>

<p>I know that I should write more here but there is not much new on the
 MirBSD front.
</p>

<p>
 I updated the showcase to NetBSD-6_BETA on the Dom0, and now X refuses
 to start. Oh well. X does start when using a GENERIC kernel. This is
 very bad for showcase use, of course :(. pkgsrc is going into freeze
 very soon, and I did not do a whole lot of MirBSD fixes this time
 around. This is due to illness, searching for a new job, and working on
 <a href="http://golang.org/">the Go programming language</a>, which is
 expected to hit version 1.0 Real Soon Now(TM).
</p>

<p>
 I brushed up my Algorithms and Data Structures a bit by reading the
 third volume of TAOCP. Fantastic book.
</p>

<!-- tg: DON'T change the link above. Don't even think about it. -->
----
Date: 19.05.2012 23:07
Author: tg@
Title: MirBSD goes webservice – manpages and WTF‽
Tag: debian mksh news pcli tip

<p>While wtf(1) always has been a bit central to <a
 href="@@RELPATH@@main.htm">MirBSD</a>, and the <a
 href="@@RELPATH@@acronyms" type="text/plain; charset=utf-8"
 title="MirBSD WTF acronym database">acronym database</a>
 has been accessible by <a href="@@RELPATH@@cvs.cgi">CVSweb</a>,
 what we never had was a DAU compatible (and <a
 href="https://evolvis.org/projects/shellsnippets/">shellsnippets</a>
 compatible) lookup. This has now changed: the above link to
 the acronyms file is a persistent link to its latest version
 (well, latest when the website was last recompiled), tooltips
 may very well follow soon, and we’ve got an <a
 href="@@RELPATH@@wtf.htm">online WTF lookup service</a>.<br />
 Contributions to the acronym database are welcome, of course;
 just eMail them to <tt>tg＠mirbsd．org</tt>.</p>
<p>Not to stop there, our <a href="@@RELPATH@@man.htm">online
 HTML manpage search</a> is also new, shiny, and should replace
 the “<tt>!mbsdman</tt>” DuckDuckGo hash-bang shortly. (Both of
 these services offer a DDG search as fallback. Note that DDG is
 an external service included herein by linking, under their
 request to spread it, and not affiliated with The MirOS Project.
 They do, however, donate some advertising money to Debian.)<br />
 For all those who didn’t know: only manpages for software in the
 MirOS BSD base system and for the MirPorts Framework package tools
 are listed, not for third-party applications installable using <a
 href="@@RELPATH@@ports.htm">ports</a> or, recently, <a
 href="@@RELPATH@@pkgsrc.htm">pkgsrc®</a>. Still, if you want to have
 a peek at a modern classic BSD’s documentation, you’re welcome. (Not
 to mention content like re_format(7) and style(9) and that some of
 our documentation is much more legible than others.)</p>
<p>And because writing all that perl(1) made me ill, not to
 mention I don’t even <em>know</em> that language, I’ve hacked
 a bit more in the mir﻿make(1) and mksh(1) parts of the
 MirWebsite, finally implementing pointing out where in the
 navigation sidebar the visitor currently is.</p>
<p>We also have exciting <a href="@@RELPATH@@mksh.htm">mksh</a>
 porting news involving RT trying a larger number of ancient
 platforms than I dare count, me fixing bugs in Linux klibc and
 diving into other things, learning more about why I consider me
 lucky for hacking a BSD operating system… sorry, I want to keep
 this short as it’s mostly an announcement.</p>
<p>The <a href="@@RELPATH@@cvs.cgi/www/">MirWebsite source code</a>
 is, of course, also available. Improvements welcome. Except for
 these three CGIs, our website is fully statically precompiled,
 and that’s a good thing. Please help in making the CGIs secure.</p>
----
Date: 15.06.2012 07:37
Author: tg@
Title: Tricks for dealing with modern-day X.org
Tag: debian pcli tip

<p><a href="http://blog.mraw.org/2012/06/15/Fixed/">KiBi is my hero
 of the day.</a> I’ve long wondered why I couldn’t select fixed-misc
 as font on my workstation at the dayjob, which is running K?buntu
 Hardon Heroin. (Luckily, I managed to avoid upgrading to Prolonged Pain.)
 Now I guess that’ll work again.</p>
<p>My work laptop (running testing) also has got this X.org thingy. <a
 href="@@RELPATH@@cvs.cgi/contrib/samples/dot.Xmodmap">My keyboard
 layout</a> now has got a <tt>grml</tt> branch (named after the person
 who first cursed about the insane idea of those toy-breaking boys to
 rearrange the keycodes) that works with it. Since Debian is marginally
 more sane than K?buntu, in contrast to the <tt>gnu</tt> branch I use
 on my orkstation, the <tt>grml</tt> branch still has Meta on the left
 Alt key, not Mode_switch, as it still works in uxterm, which reduces
 the diff between the <tt>MAIN</tt> branch (<tt>HEAD</tt>) on XFree86®
 and this beast.</p>
<p class="boxhead">And finally: X.org defaults to a black screen and
 disabled mouse pointer until an application first requests it.
 Totally unacceptable for evilwm(1) users, and letting people think
 it crashed, to boot. The Arch Linux guys found this, among others;
 the fix is: startx(1) users edit <tt>/etc/X11/xinit/xserverrc</tt>
 to add <tt>-retro</tt> behind the <tt>X</tt>, or copy the file to
 <tt>~/.xserverrc</tt> and change it there:</p><div class="boxtext">
 <pre>
	#!/bin/sh

	exec /usr/bin/X -retro -nolisten tcp "$@"
 </pre>
</div><p class="boxfoot">For display managers, similar files exist in
 <tt>/etc/kde4/kdm</tt> and related places.</p>
<p><strong>Update:</strong> Also, newer xterm(1) justify <a
 href="https://www.mirbsd.org/cvs.cgi/contrib/samples/dot.Xresources?rev=HEAD">an
 update to <tt>~/.Xresources</tt></a> for we can finally get rid of
 cut buffers, and get a blinking underline cursor to boot!</p>
<!-- RSS stop -->
<p>On the other front, worked on Debian packaging, and upstream on
 pax(1) and <a href="@@RELPATH@@jupp.htm">jupp</a>, with more things
 to follow (especially in <a href="@@RELPATH@@mksh.htm">mksh</a>).
 Also fixed about ⅔ Linux klibc architectures and learned why I’m a
 BSD developer despite all the bad parts of it ☺ and fixed fakeroot
 with pax(1) on Hurd… incidentally in code originally designed to
 support the Linux pax. My dayjob’s keeping me busy, but I’ve got
 plans to run mksh(1) through Sonar, in addition to the static code
 analysēs done by (once again, thanks!) Coverity (commits to mksh
 pending) and Clang/LLVM scan-build. Uhm, what can I say more, grab
 me in IRC if you need it. Ah, and some other mksh things coming up
 that may be of interest to people needing to support legacy scripts.</p>
----
Date: 14.07.2012 22:17:01
Author: tg@
Title: bubulle’s Cool prompt for git users with mksh
Tag: debian mksh pcli tip

<p class="boxhead">Originally <a
 href="http://www.perrier.eu.org/weblog/2012/07/15#cool-prompt">posted
 by bubulle</a> on Planet Debian, a shell prompt that displays the
 current git branch, in colour on some terminals, after the current
 working directory. The following snippet does similar things for
 <a href="@@RELPATH@@mksh.htm">mksh</a> users, except it doesn’t
 redefine your prompt but amend it – just throw it at the bottom of
 your <tt>~/.mkshrc</tt> before that last line beginning with a colon
 (copy from <a href="@@RELPATH@@cvs.cgi/contrib/hosted/tg/deb/mksh/debian/.mkshrc?rev=HEAD"><tt>/etc/skel/.mkshrc</tt></a>
 if you haven’t done that yet):</p><div class="boxtext">
 <pre>
	function parse_git_branch {
		git branch 2&gt;/dev/null | sed -n '/^\* \(.*\)/s//(\1)/p'
	}

	function amend_prompt_with_git {
		local p q='$(parse_git_branch)' r

		if [[ $TERM = @(xterm-color|xterm|screen*) ]]; then
			if [[ ${PS1:1:1} = $'\r' ]]; then
				p=${PS1:0:1}
			else
				p=$'\001'
				PS1=$p$'\r'$PS1
			fi
			q=$p$'\e[1;33m'$p$q$p$'\e[0m'$p
		fi

		p=${PS1%%*( )[#$]*( )}
		if [[ $p != "$PS1" ]]; then
			# prompt ends with space + #-or-$ + space, we can amend
			r=${PS1: ${#p}}
			PS1=$p$q$r
		fi
	}
	amend_prompt_with_git
	unset -f amend_prompt_with_git
 </pre>
</div><p class="boxfoot">The indirection by use of a function is not
 strictly necessary but allows the use of locals. I took the liberty
 of adding an asterisk after “screen” to match the GNU/Linux nonsense
 of having <tt>TERM=screen.xterm</tt> or somesuch.</p>
----
Date: 16.07.2012 15:31 +0200
Author: tg@
Title: Apache 2, https clients linked against GnuTLS, connection errors
Tag: debian tip work

<p>I’ve been debugging a weird problem at work – after upgrading a
 complex system from lenny to wheezy, <em>some</em> https clients
 failed to connect: GNU wget and Debian’s version of lynx(1) which
 is linked against libgnutls26 fail. NSS applications continue to
 work, as does cURL; wget and lynx on MirBSD (linked with OpenSSL
 of course) work. Even Debian’s gnutls-cli tools from both gnutls26
 and gnutls28 work. Huh. The error_log shows renegotiation problems,
 yet setting the new Apache 2 configuration option to “use insecure
 renegotiation” doesn’t help either. (The option is a total #FAIL:
 its only other value is “use secure TLSv1.x renegotiation”, but I
 don’t want/need SSL renegortiation at all, anyway.) Natureshadow
 told me this was a hot issue on Debianforum at the moment, yet,
 nobody had a clue or enough information to file a formal bugreport
 against (initially) apache2, as that’s what changed. I tracked it
 down on a new VM with no configuration otherwise, and here are my
 findings so others don’t run into it.</p>
<p class="boxhead">Tracking down the problem, this can be reduced
 to the following configuration (minimised, to show the problem)
 in <tt>/etc/apache2/sites-enabled/1one</tt>:</p><div class="boxtext">
 <pre>
	&lt;VirtualHost *:443&gt;
		ServerName wiki-70.lan.tarent.de
		RedirectMatch permanent . https://evolvis-70.lan.tarent.de/
		SSLEngine on
		SSLCertificateFile /etc/ssl/W_lan_tarent_de.cer
		SSLCertificateKeyFile /etc/ssl/private/W_lan_tarent_de.key
		SSLCertificateChainFile /etc/ssl/godaddy.ca
	&lt;/VirtualHost&gt;
 </pre>
</div><p class="boxfoot">Do not mind the actual content, this is a
 very stripped-down demo on a not-actually-set-up-yet box.</p>
<p class="boxhead">Same is valid for the companion configuration file
 <tt>/etc/apache2/sites-enabled/2two</tt>:</p><div class="boxtext">
 <pre>
	NameVirtualHost *:443

	&lt;VirtualHost *:443&gt;
		ServerName evolvis-70.lan.tarent.de
		SSLEngine on
		# workaround for BEAST (CVE-2011-3389), short-term
		SSLCipherSuite RC4-SHA
		SSLCertificateFile /etc/ssl/W_lan_tarent_de.cer
		SSLCertificateKeyFile /etc/ssl/private/W_lan_tarent_de.key
		SSLCertificateChainFile /etc/ssl/godaddy.ca
		SSLProtocol TLSv1
	&lt;/VirtualHost&gt;
 </pre>
</div><p class="boxfoot">Turns out the BEAST workaround was at fault here:
 the differing <tt>SSLCipherSuite</tt>s between the vhosts (on the same
 Legacy IP / TCP Port tuple, as we use Wildcard SSL Certificates) made
 Apache 2 want to renegotiate, so either commenting it on <tt>2two</tt>
 or, better, adding it to <tt>1one</tt> helped. Interestingly enough,
 the <tt>SSLProtocol</tt> directive did not matter (in my tests).</p>
<p>So, keep SSL settings synchronised between vhosts. In fact, those
 <em>were</em> already from include files, but <tt>2two</tt> was from
 the “Evolvis 5” generation, whereas we added to <tt>1one</tt> an
 <tt>Include</tt> of the <tt>httpd.ssl1.inc</tt> file generated by
 the previous releases of EvolvisForge and had not switched those
 legacy vhosts to the new configuration, as everything worked on lenny.</p>
<p>This wlog entry brought to you by the system administrators of <a
 href="https://www.tarent.de/">tarent solutions GmbH</a> and the <a
 href="https://evolvis.org/projects/shellsnippets/">Evolvis Project</a>,
 based on <a href="https://fusionforge.org/">FusionForge</a>.</p>
<hr />
<p><strong>Update</strong> 17.05.2013 – Absolutely <strong>do not
 use <tt>RC4-SHA</tt> for SSL/TLS (https)!</strong> It can leak
 over 200 initial plaintext bytes easily. (arc4random(3) is not
 affected from this, especially on MirBSD, nor arc4random(9).)</p>
----
Date: 10.08.2012 19:45 +0200
Author: bsiegert@
Title: Interview about MirOS
Tag: news

<p>I (bsiegert@) have been interviewed by
 <a href="http://www.OSworld.pl/">OSWorld</a>,
 a Polish news site about open source software. The interview took place
 at FOSDEM 2012. I talk about the project, about the community and about
 some of the great things when using open source.
 <a href="http://youtu.be/ASi5aTRPof0">Check out the video.</a></p>

<p>Read the
 <a href="http://osworld.pl/wywiad-z-benny-siegert-deweloperem-mirbsd/">original
 article (in Polish)</a>
 over at OSWorld. Thanks guys!</p>

<p>(Update: Corrected the HTML. Again.</p>
----
Date: 12.08.2012 22:41 +0200
Author: bsiegert@
Title: Latest MirOS developments
Tag: kernel jupp pkgsrc

<p>There have been some interesting recent developments in MirBSD. As
 always, there has been development on mksh but tg@ is more qualified to
 write about this.</p>

<p>The kernel has also seen some improvements: bge(4) is now again
 included in the GENERIC kernel, and it supports some newer chips – for
 example the BCM5751 Gigabit Ethernet. This chip is the one in the
 machine graciously donated by Marc Balmer. The umsm(4) driver has been
 added, supporting certain 3G “surf sticks”.</p>

<p>There has been a new
 <a href="@@RELPATH@@jupp.htm">release of jupp</a>,
 joe-3_1jupp21, containing several critical fixes regarding the use of
 uninitialized memory. It also contains a bugfix for syntax
 highlighting.</p>

<p>In pkgsrc, have been attacking the list of broken packages breaking
 the highest number others. The three versions of Ruby in the tree
 (1.8.x, 1.9.2 and 1.9.3) now build fine, as do ilmbase, blas and a few
 others. Fixing blas meant introducing a weird special case in libtool:
 Usually, MirBSD has no Fortran compiler; however, pkgsrc has f2c, which
 it uses as <tt>f77</tt>, confusing libtool. It actually needed a
 special-case entry to treat it like gcc (which it uses internally).
 There is also a weird failure in policykit, where an XSLT processor
 segfaults during the creation of one of the manpages. Maybe it hits an
 ulimit, I am not sure. Anyway, these fixes are now in pkgsrc-current.
</p>
----
Date: 12.08.2012 23:11 +0200
Author: bsiegert@
Title: pkgsrc-2012Q2 binary packages available
Tag: news pkgsrc

<p>Packages for pkgsrc-2012Q2 are now available on ftp.NetBSD.org. They
 have been built for MirBSD-current on i386. This time, there is notably
 a much larger selection of software for X11, due to a successful build
 of gtk+2. All in all, there are about 6300 packages available.</p>
----
Date: 12.10.2012 15:56 +0200
Author: bsiegert@
Title: Source Code Pro

<p>There are a lot of monospaced fonts or “programmer’s fonts” available
 these days. Personally, I like neither the default “sans” that is
 generally used in Gtk applications nor the default monospace font in
 Mac&nbsp;OS&nbsp;X, Menlo. Both fonts are very similar, as Menlo is
 based on Bitstream Vera Sans.</p>

<p>Now, Adobe has just released an excellent monospaced OpenType font,
 called
 <a href="http://blogs.adobe.com/typblography/2012/09/source-code-pro.html"><i>Source
 Code Pro</i></a>,
 as open source. The fonts can be directly downloaded from
 <a href="http://sourceforge.net/projects/sourcecodepro.adobe/">their
 SourceForge page</a>.</p>

<p>(Of course, if you are into non-antialiased fonts, nothing beats the
 “fixed” font included with X.)</p>
----
Date: 12.10.2012 16:04 +0200
Author: bsiegert@
Title: Go on NetBSD
Tag: golang

<p>Starting today, I am running continuous builders for Go on NetBSD/386
 and NetBSD/amd64. Both are running fine, so Go is now (semi-officially)
 supported on NetBSD. You need at least version 5.99.51 or, even better,
 a NetBSD-6.0 release candidate. In addition, the latest Go release
 (1.0.3) does not have the NetBSD support, so you must build from source
 on tip.</p>

<p>Go 1.1, which is expected for January 2013, will support NetBSD on
 x86 officially.</p>
----
Date: 01.12.2012 21:24
Author: tg@
Title: Proposed extensions to the JSON specification
Tag: debian

<p>The following proposal extends the JSON specification, with the idea
 of using JSON as an information interchange format, rather than just a
 way of writing certain ECMAscript values. They do not add anything but
 only restrict valid JSON content and encoders with some rationale.</p>
<p>First of, I’d like to remind everyone, including JSON’s author, that
 JSON <em>is</em> case-sensitive, <em>except</em> in the four hexdigits
 after a backslash-u sequence in a String.</p>
<p>Second, I’d like to remind everyone that JSON is not binary-safe. No
 way around that, it implements Unicode (actually, 16-bit UCS-2, and it
 doesn’t guarantee that UTF-16 surrogates are correctly paired) text. I
 also consider only UTF-{8,{16,32}{B,L}E} valid encodings for JSON. (No
 PDP endian, either. Sorry, guys.)</p>
<p>For my first proposal, I’d like to point out CVE-2011-4815 which was
 about overflowing hashtables. The obvious fix is to randomise the hash
 per hashtable; to ensure this doesn’t leak, we sort ASCIIbetically the
 keys of an Object in the encoder. (Using Unicode is good here – we can
 just sort the keys as UTF-8 strings by their <tt>uint8_t</tt> value or
 as Unicode (UCS-2 or even UCS-4 or UTF-16) strings by the codepoints.)
 JSON was never preserving the order of elements in an Object anyway so
 we make it standardised (we still accept any order, and, when parsing,
 in collision cases, the later value wins). This also helps diffs.</p>
<p>For my second proposal, I’d like to forbid \u0000, \uFFFE, \uFFFF in
 strings. The first because many implementations use C strings, and for
 an information interchange format this is better; it also has security
 implications to allow NUL in a string. The other two, but not unpaired
 UTF-16 surrogates (as ECMAscript uses UCS-2 and got UTF-16 only later)
 because they’re not valid Unicode; JSON was not binary-safe already so
 why bother. Among other benefits, this also helps implementations.</p>
<p>For my third proposal, I’d like to agree that implementations should
 impose a nesting depth limit that may be user-defined, and in the face
 of which, cyclic checking may be ignored by an encoder. I emit nesting
 depth overflows as literalnull; might also throw an error. Since I was
 asked, the common “standard” value is to restrict nesting depth is 32,
 unless the user specified one. (I also saw 8, but 32 WFM pretty well.)
 Most seem to use it even if it may seem low at first. Only specialised
 applications probably need more, and they can always pass a value.</p>
<p>For my forth proposal, backslash-escape U+007F‥U+009F always. It may
 upset humans, editors, databases, etc. (This paragraph is newly added,
 after some <a href="@@RELPATH@@irc.htm">IRC</a> discussion.)</p>
<p>All these do not permit anything that wasn’t accepted to be accepted
 afterwards. I’ve got a fifth proposal which changes acceptance rules –
 but only for a subset of parsers: formally JSON is defined in ECMA-262
 as industry standard that, in contrast to RFC 4627, always allowed any
 Value as top-level element of a JSON text. I’d like to make it so, and
 ignore the RFC’s requirement for it to be an Object or Array. Even so,
 the first two characters (after the BOM, if any) of a JSON text always
 are in the non-NUL 7-bit ASCII range, allowing for encoding detection.
 (This is done by the NUL octet pattern in the first four octets.)</p>
<p>JSON has only taken off because it’s a tightly defined simple format
 that can be used “everywhere” and isn’t too awful for humans (escaping
 not needed for U+0020‥U+D7FF and U+E000‥U+FFFD after all, although I’d
 also take the C1 control characters out, see my forth proposal above).
 I’ve started to use a trailing comma in indexed and associative arrays
 in code I write at work, when the array values are one a line, to help
 version control systems to do their diffs, but refrain from asking for
 a JSON extension to permit that in order to not endanger compatibility
 any (no comment needed, it’s just not worth it), but I’d like my above
 proposals to be followed by implementators (and I’m one of them).</p>
<p>Some more discussion with Jonathan pointed out that JSON5 allows for
 trailing commata in Object and Array; IMHO the only feature of it that
 is not bad or outright harmful. I’ll probably keep from accepting them
 because, on their own, they’re not <em>that</em> useful, and I usually
 would run JSON texts, even configs, through a parser/encoder roundtrip
 to pretty-print them which would lose them anyway.</p>
<p>As for binary-safeness: probably best to just use base64 and let the
 outer layers worry about compression. The data is usually unrelated to
 the JSON-encoded structure, and even if it’s related to other data the
 base64 representation is usually similar (unless misaligned).</p>
<p><strong>Update</strong> 02.12.2012 – Wrong I was about the first two
 characters: “"€"” is a valid JSON text. Still possible to peek at four
 octets and determine the encoding by ordering the tests; updated my <a
 href="@@RELPATH@@cvs.cgi/contrib/hosted/tg/code/MirJSON/json.txt?rev=HEAD">notes</a>.</p>
----
Date: 07.12.2012 22:40
Author: tg@
Title: Collision resolution in open addressing hashtables
Tag: debian

<p>Before we begin, everyone should read up on hashtables and what open
 addressing / closed hashing is. The context is lines 111‥190 of <a
 href="http://hg.python.org/cpython/file/026b9f5dd97f/Objects/dictobject.c">Python’s
 Objects/dictobject.c as of today</a> (so we get the line numbers straight).</p>
<p>(I’ve reworded this wlog entry a bit; I originally wrote it too late at
 night for it to read coherent.) Basically, I’ve got an application where
 I’d like to use a hashtable for a number of things – not as generic as
 Python, and with focus on small footprint. I’d like to offer associative
 arrays in a scripting language, where the keys are always arbitrary byte
 strings excluding NUL. Also, I’d like to use the hashtable as backend for
 indexed arrays, where the keys are <tt>uint32_t</tt> and the usual use
 case is sequential. Finally, I’m using it for several internal tables,
 such as a list of keywords, one of builtins, one of special variables,
 etc. which is a reason for me to not use a self-balancing binary tree
 as data structure (reading further below might suggest that, but getting
 a sorted list of hashtable keys is not the focus, though not unimportant).
 <br />My questions on this are:</p>
<p class="boxhead">① Why is the shift on perturb done after its first use?
 In my experiments (using 32-bit width everywhere), for the pathological
 case of an 8-element (i = 3) table with three entries 0, 0x40000000 and
 0x800000000, the “second round” yields 1 for all three, so it cannot have
 to do with the upper bits. My lookup looks like:</p><div class="boxtext">
 <pre>
	mask = 2ⁱ - 1;
	j = perturb = hash(key);
	goto find_first_slot;

	 find_next_slot:
	j = (j &lt;&lt; 2) + j + perturb + 1;
	perturb &gt;&gt;= PERTURB_SHIFT;
	/* FALLTHROUGH */

	 find_first_slot:
	entry = table[j &amp; mask];
	if (!match(entry)) goto find_next_empty_slot;
 </pre>
</div><p class="boxfoot">This means that my first check is always the bare
 hash (so “only do it if needed” is no reason) and, since I’m using gotos,
 I could just move the <tt>perturb &gt;&gt;= PERTURB_SHIFT;</tt> line before
 the line recalculating the next <tt>j</tt> to use. This seems to make more
 sense, even in the face of Python. (I actually looked at the Python file’s
 comments again today because I thought to use a different resolution, but
 they have a good rationale for using the multiplication by 5.)</p>
<p>② Why can’t we just use <tt>i</tt> as the <tt>PERTURB_SHIFT</tt>? Sure,
 this changes a shift-right by a constant, which can possibly be encoded
 as immediate value in assembly (unless you’re on a pre-80186, which can
 only do <tt>SHR AX,1</tt> and <tt>SHR AX,CL</tt> but not <tt>SHR AX,4</tt>,
 but that’s outside of <a href="@@RELPATH@@mksh.htm">mksh</a>’s scope) into
 a right-shift by a variable, but <tt>i</tt> is already known, and I think
 the behaviour is better (it wouldn’t eat any bits; assume the same 8-entry
 hashtable and pathologic keys 0, 8 and 16). Again: who do I think I am to
 go against the wisdom of the Python people, who seem to have shed more
 thought on this than everyone else I saw, asked, read about (including <a
 href="http://pics.nase-bohren.de/jimmywales-begging.jpg">Spammipedia</a>).
 That’s why I’m asking here. <span style="font-size:small;">On that reference:
 I don’t support spammers or people nagging for donations or premium accounts,
 like Xing and Groundspeak/Geocaching.COM, at all. In fact, I urge others to
 do the same, so it really hurts them; it may be their business model, but not
 if they spam me. Besides, OpenCaching.DE exists.</span></p>
<p>Another thing is: to avoid CVE-2011-4815, I’m randomising the hash used,
 with one “seed” value per hashtable, changed before a resize operation.
 I originally thought to seed it with nonzero, but then I have to rehash
 on hashtable resize, so I’ll be XORing the final hash value instead (thanks
 ciruZ for the idea). I’m thinking of omitting that for indexed arrays, as
 an attacker almost certainly cannot determine the keys there. (To directly
 use the indexed array keys, which are already <tt>uint32_t</tt>, as hashes
 makes using <tt>i</tt> from ② even more important.) The hash I’m using is
 a modified Jenkins one-at-a-time called NZAAT: it’s my new generic standard
 nōn-cryptographic hash, and the changes are thus: while adding a byte,
 another increment of the hash is done (so NUL counts), and the finaliser
 got prefixed with the shift-left-add+shift-right-xor sequence of the
 adder (but not adding any value or the +1), to get best avalanche for
 all bytes. I actually compiled several versions of <tt>Hash.cs</tt> on
 a Windows® VM at work to analyse the original one-at-a-time and all of my
 modifications; these turned out to be the simplest ones (I originally had
 added 0x100 instead of 1, but the effect was the same, and +1 is usually
 cheaper on most CPUs).</p>
<p>Also, to avoid people being able to get to the seed, a user will always
 get only a sorted list of hashtable keys (numeric for indexed arrays,
 ASCIIbetically otherwise; see also my thoughts on JSON from the previous
 wlog entry). What algorithm do I use? For strings, comparisons are much
 more expensive, so I’d like to keep them low. Memory use is also a factor;
 allocating one large(r) block is better than many small ones due to the
 pool allocator overhead and due to portability to ancient Unicēs (which
 is another reason for me to use a hashtable which is a small struct plus
 an array of pointers, and then pass the list of keys as array of string
 pointers, instead of a tree). For both reasons, I’m thinking a relatively
 simple MergeSort: I need to allocate the result array anyway, so I can
 just get two and free the one that isn’t the end result, and it’s AFAICT
 the cheapest on comparisons other than Tree Sort (which nobody really seems
 to use, and which would effect to using a balanced binary tree again).
 Since keys are unique, stability and duplicate handling is never an issue.
 I’d like to use only one algorithm and one data structure, not a combination,
 as compactness <em>is</em> a design goal.</p>
<p>Please drop your thoughts on <a href="@@RELPATH@@irc.htm">Freenode</a>,
 e.g. by <tt>/msg MemoServ send mirabilos <i>your text here</i></tt> or per
 eMail to the domains debian, freewrt or mirbsd, which are organisations, with
 the localpart <tt>tg</tt>. Or just contact me as usual, if you’re already
 acquainted. Or lookup 0xE99007E0. Thanks in advance! (Especially, Python
 Developers’ thoughts are welcome.)</p>
----
Date: 10.12.2012 17:28
Author: bsiegert@
Title: Call for Participation: BSD developers’ room at FOSDEM 2013
Tag: news

<p>There is one week left to submit your talk proposals for the BSD
 devroom at FOSDEM 2013. We still have quite a few slots open, so do not
 be shy! See the original announcement below:</p>

<blockquote>
 <p>FOSDEM 2013 will take place on February 2-3, 2013, in Brussels,
  Belgium. Just like in the last years, there will be both a BSD booth
  and a developer's room (on Sunday).</p>

 <p>The topics of the devroom include all BSD operating systems. Every
  talk is welcome, from internal hacker discussion to real-world
  examples and presentations about new and shiny features. The talks
  will be 45 minutes including discussion. Feel free to ask if you want
  to have a longer or shorter slot.</p>

 <p>If you want to do a talk, please submit your proposal to</p>

 <p style="text-align: center">bsiegert at google.com</p>

 <p>and include the following information:</p>

 <ul>
  <li>Your name</li>
  <li>The title of your talk (please be descriptive, as titles will be
     listed with ~400 from other projects)</li>
  <li>A short abstract of one to two paragraphs</li>
  <li>A short biography introducing yourself</li>
  <li>Links to related websites/blogs etc.</li>
 </ul>
</blockquote>

<p>The deadline for submissions is December 17, 2012. The talk committee,
 consisting of Daniel Seuffert, Marius Nünnerich and Benny Siegert,
 will consider the proposals. If yours has been accepted, you will be
 informed by e-mail within one week of the submission deadline.</p>
----
Date: 15.12.2012 13:23
Author: tg@
Title: Der heilige… Frieden?
Tag: debian politics

<p style="font-size:small;">(Apologies for putting this on Planet Debian,
 but it says the one or other non-English post is okay as long as it’s an
 exception. I feel I need to reach more people with this, but don’t feel
 like translating this into English right now.)<br />Update: Tanguy asked
 for a short English summary: it’s me ranting against the rioting against
 muslims and the call for more CCTV surveillance after a <em>possible</em>
 bomb was found at the train station.</p>
<p>In Bonn herrscht immer noch „Bombenstimmung“, wenn man z.B. auf die
 Webseite der Lokalzeitung schaut – von dem Amoklauf in Connecticut, über
 den sich im IRC gewunder wird, ist immer noch nichts zu sehen, dafür wird
 fleißig wider „Islamisten“ gehetzt.</p>
<p>Ich finde das besorgniserregend, muß doch jetzt jeder Angehörige des
 Islams fürchten, verfolgt oder benachteiligt zu werden. Das reizt doch
 erst recht zum Gegenschlag, bei dem dann auch Menschen, die absolut
 <strong>nicht</strong> mit der hier vorherrschenden Meinung und Politik
 übereinstimmen, getroffen werden können.</p>
<p>Ich persönlich habe kein Problem mit Menschen anderen Glaubens oder
 anderer Weltanschauung, solange wir friedlich miteinander leben können.
 Ich teile eure Unzufriedenheit mit dem herrschenden Staat, der immer
 weitergehenden Überwachung, Unterdrückung von Leuten, die nicht dem
 vorherrschenden Menschenbild entsprechen (egal an welchen Kategoriën),
 und bitte die, die dies lesen, nochmal nachzudenken, bevor sie etwas
 tun, was hinterher Unschuldige trifft oder gar in „friendly fire“
 ausartet.</p>
<p>Hat eigentlich wer die in Bad Godesberg ausgegebenen Koran-Bücher
 sich mal angeschaut? Als ich davon las, war ich ja zugegebenermaßen
 neugierig, weil ich vom Koran leider eher wenig kenne, weiß aber nicht,
 wie neutral oder eben nicht die Übersetzung gehalten ist. Anhand dessen,
 <em>was</em> ich bereits mitbekam, sollte das eher friedlicher sein als
 was durch spätere Theologen festgelegt wurde – wie ja auch zum Beispiel
 im Christentum, aber über die Horrorepisoden der christlichen Kirche will
 ich jetzt auch nicht mich auslassen, in der Hoffnung, daß auch diese sich
 mit den Jahren gebessert hat. (Ist nur halt das Problem mit den Leuten,
 die die „alten Hetzparolen“ jetzt noch verbreiten. Ist wie im Netz mit
 den Groupies von Theo de Raadt, die noch asiger zu Leuten sind als er
 selber.) (Außerdem muß man ja befürchten, durch Besitz eines Korans schon
 vorverurteilt zu werden heutzutage *seufz*… ich finde das nicht gut!)</p>
<p>Update (ich vergaß): auch der Ruf nach mehr Videoüberwachung ist nur
 Panikmache. Das geht nur zu Lasten des Normalbürgers. Vielleicht lassen
 sich noch Kleinstdelikte wie Taschendiebstahl damit abschrecken, aber
 gerade diese Bomben und dergleichen sind doch oft von Leuten, die vor
 Konsequenzen keine Angst haben, organisiert. Die werden dann maximal
 Märtyrer. Ich wiederhole nochmal für die Politiker und die ganz langsamen
 unter den Lesern: Überwachung verhindert <em>keine</em> Straftat.</p>
<p><strong>Update 11.01.2013</strong>: Mittlerweile hat auch <a
 href="http://blog.fefe.de/?ts=ae2a54c2">Fefe</a> was dazu.</p>
----
Date: 31.12.2012 22:36
Author: tg@
Title: Not just Amigas, editors and errnos
Tag: debian mksh

<p><a href="@@RELPATH@@mksh.htm">mksh</a> made <a
 href="http://phoronix.com/forums/showthread.php?76247-Debian-Brought-Back-To-Life-On-M68K-Based-Amigas">quite</a> <a
 href="http://linux.slashdot.org/story/12/12/26/163222/debian-m68k-port-resurrected">some</a> <a
 href="http://www.solidot.org/story?sid=32869">waves</a> (machine <a
 href="http://sprunge.us/UPGA">translation</a> of the third article) recently.
 Let’s state it’s not just Amigas – ara5 is a buildd running the Atari kernel,
 an emulated though. On the other hand, the bare-metal Ataris used to be the
 fastest buildds, so I expect we get them back online soonish. I’m currently
 fighting with some buildd software bugfixes, but once they’re in, we will
 make more of them. Oh, and porterboxen! Does anyone want to host a VM with a
 porterbox? Requirements: wheezy host system (can be emulated), 1 GiB RAM, one
 CPU core with about 6500 BogoMIPS or more (so the emulated system has decent
 speed; an AMD Phenom II X4 3.2 GHz does just fine). Oh, and mksh is <a
 href="@@RELPATH@@mksh_bld.htm">ported</a> to more and more platforms, like
 386BSD 0.0 with GCC 1.39, and QNX 4 with Watcom… and more bugfixes are also
 being worked on. And let’s not forget features!</p>
<p><a href="@@RELPATH@@jupp.htm">jupp</a> got refreshed: it’s got a bracketed
 paste mode, which is even auto-enabled on <tt>xterm-xfree86</tt> (though the
 xterm(1) in MirBSD’s a tad too old to know it; will update that later, just
 imported sendmail(8) 8.14.6 and lynx(1) 2.8.8dev.15 into base, more to come)
 and will be enhanced later (should disable auto-indent, wordwrap, status line
 updates, and possibly more), lots of new functions and bindings, now uses
 mkstemp(3) to create backup files race-free, and more (read the NEWS file).</p>
<p>In MirBSD, Benny and I just added a number of <tt>errno</tt>s, mostly for
 SUSv4 compliance and being able to compile more software from pkgsrc® without
 needing to patch. This is being tested right now (although I should probably
 go out and watch fireworks in less than a half-hour), together with the new
 imports and the bunch of small fixes we accumulate (even though <em>most</em>
 development in MirBSD is currently in mksh(1) and similar doesn’t mean that
 <em>all</em> is, or worse, we were dead, which we aren’t). I’ll publish a
 new snapshot some time in January. The Grml 2012.12 also contains a pretty
 up-to-date MirBSD, with a boot(8/i386)loader that now ignores GUID partition
 table entries when deciding what to use for the ‘a’ slice.</p>
<p>If you haven’t already done so, read <a href="http://mako.cc/">Benjamin
 Mako Hill</a>’s writings!</p>
----
Date: 04.01.2013 17:32
Author: tg@
Title: on the linguistic gender of hosts, with an xz reminder
Tag: debian

<p>Let’s start a convention: bare-metal machines have the linguistic male
 gender (<span xml:lang="de-DE-1901">„der Computer“</span>, he needs to be
 rebooted), whereas VMs have the linguistic female gender (<span
 xml:lang="de-DE-1901">„die virtuelle Maschine“</span>, she runs better
 since the last upgrade of Linux-KVM), and neutral linguistic gender is
 used when you cannot or do not want or need to make such distinction.<br />
 This is, of course, entirely unrelated to human gender, but not unrelated
 to <tt>#debian-68k</tt> (on OFTC) discussions ;-)</p>
<p>ObRant: <strong>DO NOT USE xz COMPRESSION LEVELS ABOVE 6!</strong> (For
 <tt>-7</tt> we can make exceptions, for example in Debian *<tt>-dbg</tt>
 or *<tt>-source</tt> packages.) You <em>may</em> use <tt>-e</tt> if you
 absolutely need the better compression, but please think of the poor sods
 who have to create the archives. You <em>must not</em> use the highest
 compression levels <tt>-8</tt> or <tt>-9</tt> since they have absolutely
 insane memory requirements on compression and will still hinder machines
 with less RAM on decompression. (Using <tt>-e</tt> only affects CPU usage
 at compression time; decompression is exactly as fast and memory-consuming
 as without.) Furthermore, <strong>DO NOT CHOOSE A COMPRESSION LEVEL WITH
 A DICTIONARY SIZE MUCH LARGER THAN THE DATA TO COMPRESS</strong>, as that
 makes absolutely no sense and will rather worsen than improve compression.
 As a reminder, xz uses the following dictionary sizes:</p><ul>
  <li>256 KiB at <tt>-0</tt> (compresses better than gzip(1) and faster
   than either gzip(1) or bzip2)</li>
  <li>1 MiB at <tt>-1</tt></li>
  <li>2 MiB at <tt>-2</tt> (compresses better than gzip(1) and bzip2
   without losing much speed)</li>
  <li>4 MiB at <tt>-3</tt> and <tt>-4</tt> (the difference is in the
   match finder between these two levels)</li>
  <li>8 MiB at <tt>-5</tt> and <tt>-6</tt></li>
  <li>16 MiB at <tt>-7</tt> (186 MiB RAM used to compress a file)</li>
  <li>32 MiB at <tt>-8</tt> (370 MiB RAM used to compress a file)</li>
  <li>64 MiB at <tt>-9</tt> (674 MiB RAM used to compress a file)</li>
</ul>
<p>Decompression uses less than 1 MiB more than the dictionary size,
 but the dictionary must always be allocated wholly. (You’re fine to
 use custom presets, but mind the RAM usage!) As a general rule, if
 you have something of up to 20 MiB to compress, <tt>-4</tt> is fine,
 and <tt>-5</tt> will only be better if you have similar data spread
 across the whole of the file instead of close to each other. When I
 make <a href="@@RELPATH@@mksh.htm">mksh</a> distfiles, I instead put
 files close to each other that have related content, which improves
 compression much more nicely without penalising low-memory systems;
 for example, you could put documentation, Makefiles, scripts, m4(1)
 files, and C source code into groups before archiving, instead of
 doing it alphabetically.</p>
<p>Another note on bzip2: its decompression <strong>is slow</strong>.
 I see no reason to use it any more, <em>at all</em>. Use gzip(1) if
 you care for compatibility or have an issue with xz not having a free
 copyright licence, and xz otherwise.</p>
----
Date: 13.01.2013 15:24
Author: tg@
Title: PSA: Unicode codepoints, referring to
Tag: debian rant

<p><a href="@@RELPATH@@wtf.cgi?PSA">PSA</a>: Referring to Unicode
 codepoints.</p>
<p>If your Unicode codepoint is, numerically, between 0 and 65533,
 inclusive, convert it to hexadecimal and zero-pad it to four nibbles.
 For example, the Euro sign € is Unicode codepoint #8364 which is 20AC
 hex; the Eszett ß is 223 which is DF hex, padded 00DF.<br />
 Then write an uppercase ‘U’, a plus sign ‘+’, and the four nibbles:
 U+20AC U+00DF<br />In <a href="@@RELPATH@@mksh.htm">mksh</a>, <a
 href="@@RELPATH@@cvs.cgi/contrib/hosted/tg/code/MirJSON/json.txt?rev=HEAD">JSON</a>,
 etc. it’s a backslash ‘\’, a lower-case ‘u’ and four nibbles.</p>
<p>Otherwise, your Unicode codepoint will be, numerically, between
 65536 and 1114111, inclusive, that is hex 10000 to 10FFFF. (There’s
 nothing on 65534 and 65535, nor above these figures.) In this case,
 convert it to hex, zero-pad it <strong>to eight nibbles</strong> and
 write it as an uppercase ‘U’, <strong>a hyphen-minus ‘-’</strong> and
 the <strong>eight</strong> nibbles. In C-like escapes for environments
 supporting the Unicode SMP, that’s a backslash ‘\’, an upper-case ‘U’
 and eight nibbles. <em>Do not, in either case, use less (or more) hex
 digits than specified here.</em> For example, there’s a famous Unicode
 codepoint U-0001F4A9 “PILE OF POO”. <strong>That’s not the same as
 U+1F4A9</strong>. The latter reads as U+1F4A “GREEK CAPITAL LETTER
 OMICRON WITH PSILI AND VARIA” and a digit 9 (Ὂ9). Be educated.</p>
<!-- RSS stop --><p>Since this wlog runs on MirBSD, which limits itself
 to the Unicode BMP voluntarily, and as nōn-BMP is not widespread anyway,
 I cannot reproduce the “PILE OF POO” here, but you can <a
 href="https://duckduckgo.com/?kp=-1&amp;kl=wt-wt&amp;kb=t&amp;kh=1&amp;kj=g2&amp;km=l&amp;ka=monospace&amp;ku=1&amp;ko=s&amp;k1=-1&amp;kv=1&amp;t=debian&amp;q=unicode+pile+of+poo">just
 duckduckgo it</a>.</p>
----
Date: 20.02.2013 08:28:20
Author: tg@
Title: GNU autotools generated files
Tag: debian rant

<p class="boxhead">On Planet Debian, Vincent Bernat <a
 href="http://vincent.bernat.im/en/blog/2013-lldpd-0.7.1.html">wrote</a>:</p>
<div class="boxtext">
 The drawback of this approach is that if you rebuild configure from
 the released tarball, you don’t have the git tree and the version will
 be a date. Just don’t do that.
</div><p class="boxfoot">Excuse me‽</p>
<p>This is totally inacceptable. Regenerating files like aclocal.m4 and
 Makefile.in (for automake), configure (for autoconf), and the likes is
 one of the absolute <strong>duties</strong> of a software package.
 Things <strong>will</strong> break sooner or later if people do not do
 that. Additionally, generated files <strong>must</strong> be remakable
 from the distfile, so <strong>do not break this!</strong></p>
<p>May I suggest, constructively, an alternative? (People – rightfully,
 I must admit – complain I’m “just” ranting too much.)<br />When making
 a release from git, write the “git describe” output into a file. Then,
 use that file instead of trying to run the git executable if .git/. is
 not a directory (“<tt>test -d .git/.</tt>”). Do not call git, because,
 in packages, it’s either not installed or/and also undesired.</p>
<p>Couldn’t comment on your blog, but felt strongly enough about this I
 took the effort of writing a full post of my own.</p>
<p>(But thanks for the book recommendation.)</p>
----
Date: 23.02.2013 20:27
Author: tg@
Title: Too much
Tag: personal

<p>I’ve been doing too much lately, which has led to reduced performance
 and enjoyment. Also I’ve not been able to work the full hours of my
 dayjob, reducing what I had on my overtime account. I’ll be taking a
 step back and try to un-load. This is my notice, I’m not explicit on
 where, and I’m not cancelling anything special (not even those mentioned
 in the next paragraphs).</p>
<p>I’m disappointed with Google/Nianticproject Ingress. It’s frustrating
 (nothing lasts; also read <a
 href="https://plus.google.com/+KristianK%C3%B6hntopp/posts/gyV1wRnuwyo">this
 posting</a>), buggy, battery-draining, sometimes too time-consuming
 (especially with only GPRS) and I don’t get warm with the Android 2.3
 based Cyanogenmod on the borrowed device. Using it without a <em>big</em>
 screen device having the Intel map next to you is futile. I could go into
 detail but won’t. I won’t stop playing, as it’s a good excuse to go outside
 and combines somewhat with geocaching (unless you’re trying to actually
 play Ingress, in which case you’ll just be walking/cycling/driving between
 portals at maximum speed). And there’s that connection with Liferay…</p>
<p>Fun is important in securing volunteer work; bugs and <a
 href="http://article.gmane.org/gmane.linux.debian.ports.68k/10993">other
 random happenings</a> (example) can drain the fun.</p>
<p>To end on a positive note, I’m absolutely, totally happy with <a
 href="@@RELPATH@@mksh.htm">mksh</a> user and distributor feedback,
 including the bug reports and feature requests, how well almost all
 people deal with feature rejection, and the speed of integration of
 mksh(1) updates lately. The only thing I’m unhappy wrt. mksh is my
 own lack of speed regarding implementing the cool new things I’ve
 been, as an mksh <em>user</em>, waiting for because I want and even
 <em>need</em> them for some cool programs written in mksh I would
 love to write, so I can use them.</p>
<p>I’ve got roughly 350 mails in my INBOX (all read, but most of them
 being action items; some due… before this weekend, evilly enough, the
 one I’m thinking of is GnuPG/MIME encrypted, which means extra effort
 to read it). Just so you know. (And a couple of other things that
 really could use some fixing, which I can, in theory, do. And lots of
 requests for spending real life time with.)</p>
<p>I’m still reachable via eMail and IRC (mostly), will respond, will
 try to persuade my employer to send me to CLT 2013 next month… just,
 don’t deadline me right now. I’m not taking a VACation either (though
 I probably should, had I money).</p>
----
Date: 04.03.2013 18:55
Author: tg@
Title: Himbeerichüechli!
Tag: twitxr

<p><a href="@@RELPATH@@pics/wlog/Himbeerquarkschnitte.JPG"><img
 src="@@RELPATH@@pics/wlog/Himbeerquarkschnitte.jpg"
 alt="Himbeerquarkschnitte" /></a> <i>*winkt Ventilator*</i></p>
<p>Natürlich mit MirKaffee (enthält Milch, Kakao, Kaffee, Rohrzucker)!</p>
----
Title: pkgsrccon 2013
Author: bsiegert@
Date: 24.03.2013 17:06
Tag: pkgsrc

<p>On Saturday March 23, this year's pkgsrc conference (pkgsrccon 2013)
 took place in Berlin. Julian Fagir organized it with unending energy,
 even though pkgsrc is not the primary focus of his NetBSD work. He just
 took matters in his hands because no one else stepped forward. A big
 thanks for that!</p>

<p>The flight from Zurich to Berlin was uneventful. It was my first
 flight to TXL airport (I normally arrive at SXF), and arriving there is
 incredibly quick and convenient compared to the latter. The terminal is
 very small, and it takes just five minutes to go from the plane to a
 bus to the city.</p>

<p>Now for the conference itself: we started at 12pm on Saturday with a
 program of talks but no fixed schedule. Due to this, the conference
 took a long time (we finished only at 9pm or so) but on the other hand,
 it allowed for lots of interesting and fruitful discussion. At no point
 did we have to cut a question short because of a lack of time. Overall,
 I think that this was an excellent choice and made the conference more
 useful and productive.</p>

<p>We were about 21 people &ndash; mostly pkgsrc developers (of course)
 but also a Debian Developer (Ralf Treinen, who presented his work on
 Mancoosi), a FreeBSD dev and some interested users. I won't give an
 exhaustive recollection of all talks here but simply comment on a few
 ones that I found particularly interesting.</p>

<p>The most important theme of the conference was virtualization and
 cloud computing. Jonathan Perkin and Filip Hajny gave a talk about
 their company's product, SmartOS, and how it uses pkgsrc. SmartOS is a
 "cloud OS" based on OpenSolaris. It boots from a read-only medium (such
 as a CD) into a lean system that only does the administration of all
 the zones that it runs. All useful work happens in zones, which are a
 sort of lightweight VM solution specific to OpenSolaris. The zone
 images include access to a very complete set of pkgsrc packages for
 things such as a compiler. They can also run other OSes (NetBSD!) by
 setting up a zone that runs KVM. Joyent runs a large public cloud with
 SmartOS, where customers purchase virtual machines by the hour. This is
 similar to Amazon EC2 but with a focus on high performance.</p>

<p>Hubert Feyrer gave another talk about a similar theme. He described
 the use of Ansible for provisioning and setting up VMs. Ansible can
 automatically create VMs on EC2, gather the necessary information (such
 as the IP address) and do various setup tasks without further user
 interaction. This was all very impressive, even though the live demo
 failed. This was for two reasons: Somebody deleted the sudo package for
 amd64 from the NetBSD ftp server (boo), and the i386 VM failed to come
 up, the kernel paniced on startup. Joerg speculated that this was due
 to _some_ machines in their DC not having PAE enabled, while the i386
 kernel uses PAE. This was interesting, as I had noticed the very same
 problem when I set up the netbsd-386-bsiegert continuous builder for
 Go.</p>

<p>Amitai Schlair alias Schmonz came out in a passionate defense of the
 venerable pkglint. <a href="https://github.com/schmonz/pkglint">He put
 the source on github</a> and started refactoring the code
 and adding tests. He calls this approach TED for "Test Eventually
 Development" ;) and advocated a similar approach for the pkgsrc
 infrastructure: Every time a developer takes five minutes to understand
 a part of the infrastructure (when making a change, for instance), he
 or she should write a test for it. This is a very pragmatic and doable
 approach, in my opinion, and we should all do this.</p>

<p>I gave a slightly amended version of the "Go on NetBSD" talk I had
 given at FOSDEM 2013. There were a lot of valuable questions and
 discussion, both about the language and about how to package software
 written in it.</p>

<p>Aleksej Saushev ended the day with a talk that was not in the program
 about the Google Code-In and the problems that developers and
 particularly new contributors face. If pkgsrc can get more contributors,
 it gets more fixes, which in turn makes it more useful to users. More
 usefulness leads to more users, leading to more contributors. We should
 do more to get into this virtuous circle. There are about five
 different mechanisms to build and/or deploy packages in pkgsrc: build
 directly with "make package", pkg_chk, pkg_comp, the old bulk build
 scripts and pbulk. The basic frustration that should be overcome is the
 following: you want to upgrade a set of packages, the old ones are
 removed, new ones are rebuilt, and the build fails. Rolling back is
 difficult in general. pbulk could be a valuable solution to this, but
 its standard config is heavily tailored for a different use case, and
 its _two_ separate pieces of documentation are contradictory,
 incomplete and confusing. So the talk contained a call for action to
 fix those minor annoyances and generally document things better, which
 makes it easier for everybody.</p>

<p>My take-home message – and my next project idea – is the following:
 each time that I do a MirBSD bulk build using pbulk, I have to do a lot
 of painful steps to set up the right build environment on all my
 machines. This time, I will try to automate this process with Ansible,
 making up the recipes as I go along, and then (more importantly)
 publish these recipes for others to use and to share.</p>
----
Date: 24.03.2013 21:39
Author: tg@
Title: Earthcache Master (Bronze)
Tag: debian geocache

<p>Since a while…</p><table>
<tr><td align="center">I am a proud</td></tr>
<tr><td align="center"><a href="http://www.earthcache.org/"><img
 src="http://img.geocaching.com/user/1847de56-1d37-4def-b22b-97b71bd2f1fd.jpg"
 style="border:0;" alt="EarthCache Master" /></a></td></tr>
</table>
<p>On the other hand… I should probably put up my own, local, list
 of found caches, considering what happened to me on “Open”caching.
 And maybe write intros for people new to geocaching, since it’d be
 virtually no work now had I done it initially. (And for fanfiction
 readers! I wish I’d kept a list of <em>read</em> fics, not just of
 these I currently read and/or are currently unfinished.)</p>
----
Date: 13.04.2013 17:05
Author: bsiegert@
Title: pkgsrc-2013Q1 binary packages available
Tag: news pkgsrc

<p>I uploaded a full bulk build of binary packages for MirBSD/i386
 corresponding to the pkgsrc-2013Q1 release. About 7,000 binary packages
 are available in this build, including the <b>pkgin</b> package manager
 that makes installing binary packages as easy as apt.</p>

<p>See the <a href="@@RELPATH@@pkgsrc.htm">pkgsrc page</a> for
 instructions on how to install pkgsrc for MirBSD.
 <a href="http://miros.s3.amazonaws.com/pbulk/20130329.2011/meta/report.html">Build
 logs</a> are available on S3.</p>
----
Title: mksh R45 released
Date: 26.04.2013 22:24
Author: tg@
Tag: debian mksh news

<p>The <a href="@@RELPATH@@mksh.htm">MirBSD Korn Shell</a> R45 has been
 released today, and R44 has been named the new stable/bugfix-only series.
 (That’s version 45.1, not 0.45, dear Homebrew/MacOSX packagers.)</p>
<p>Packagers rejoice: the <tt>-DMKSH_GCC55009</tt> dance is no longer needed,
 and even the run-time check for integer division is gone. Why? Because I
 realised one cannot use signed integers in C, at all, and rewrote the mksh(1)
 arithmetics code to use unsigned integers only. Special thanks to the people
 from <a href="http://www.musl-libc.org/">musl libc</a> and, to some lesser
 amount, Natureshadow for providing me with ideas what algorithms to replace
 some functionality with (signed shell arithmetic is, of course, still usable,
 it is just emulated using unsigned C integers now).</p>
<p class="boxhead">The following entertainment…</p><div class="boxtext">
 <pre>
	tg@blau:~ $ echo foo &gt;/bar\ baz
	/bin/mksh: can't create /bar baz: Permission denied
	1|tg@blau:~ $ doch
	tg@blau:~ $ cat /bar\ baz
	foo
 </pre>
</div><p class="boxfoot">… was provided by Tonnerre Lombard; like <a
 href="http://www.thelocal.se/39784/20120320/">Swedish</a>, German has
 got a number of words that cannot be expressed in English so I feel
 not up to the task of explaining this to people who don’t know the
 German word “doch”, just rest assured it calls the last input line
 (be careful, this is literally a line, so don’t use backslash-newline
 sequences) using sudo(8).</p>
----
Title: DynDNS
Date: 20.05.2013 15:27
Author: tg@
Tag: archaeology debian

<p><a href="http://www.die-welt.net/2013/05/powerdyn-a-dynamic-dns-service-for-powerdns-users/">Apparently
 (hi Zhenech, found on Plänet Debian)</a>, a Man does not only need
 to fork a child, plant a tree, etc. in their life but also write a
 DynDNS service. Perfect for opening a new tag in the wlog called
 archæology (<a href="http://www.pagetable.com/">pagetable.com –
 Some Assembly Required</a> is also a nice example for these).</p>
<p>Once upon a time, I used SixXS’ heartbeat protocol client for
 updating the Legacy IP (known as “IPv4” earlier) endpoint address
 of my tunnel at home (<a href="http://www.netcologne.de/">My ISP</a>
 offers static v4 for some payment now, luckily). Their client sucked,
 so I wrote on in <a href="@@RELPATH@@mksh.htm">ksh</a>, naturally.</p>
<p>And because mksh(1) is such nice a language to program in (although,
 I only really begun becoming proficient in Korn Shell in 2005-2006 or
 so, thus please take those scripts with a grain of salt, I’d do them
 <em>much</em> differently nowadays) I also wrote a heartbeat server
 implementation. In Shell.</p>
<p>The heartbeat server supports different backends (per client), and
 to date I’ve run backends providing DynDNS (automatically disabling
 the RR if the client goes offline), an IP (IPv6) tunnel of my own
 (basically the same setup SixXS has, without knowing theirs), rdate(8)
 based time offset monitoring for ntpd(8), and an eMail forwarding
 service (as one <strong>must not run an MTA on dynamic IP</strong>)
 with it; some of these even in parallel.</p>
<p>Not all of it is documented, but I’ve written up most things in <a
 href="@@RELPATH@@cvs.cgi/contrib/code/heartbeat/">CVS</a>. There also
 were some issues (mostly to do with killing sleep(1)ing subprocesses
 not working right), so it occasionally hung, but very rarely. Running
 it under the supervise of DJB dæmontools was nice, as I was already
 using djbdns, since I do not understand the BIND zone file format and
 do not consider MySQL a database (and did not even like databases at
 all, back then). For DynDNS, the heartbeat server’s backend simply
 updated the zone file (by either adding or updating or deleting the
 line for the client) then running tinydns-data, then rsync’ing it
 to the djbdns server primary and secondaries, then running zonenotify
 so the BIND secondaries get a NOTIFY to update their zones (so I never
 had to bother much with the SOA values, only allow AXFR). That’s a
 really <a href="@@RELPATH@@wtf.cgi?kiss">KISS</a> setup ☺</p>
<p>Anyway. This is archæology. The scripts are there, feel free to
 use them, hack on them, take them as examples… even submit back
 patches if you want. I’ll even answer questions, to some degree,
 in <a href="@@RELPATH@@irc.htm">IRC</a>. But that’s it. I urge
 people to go use a decent ISP, even if the bandwidth is smaller.
 To paraphrase a coworker after he cancelled his cable based internet
 access (I think at Un*tym*dia) before the 2-week trial period was
 even over: rather have slow but reliable internet at Netc*logne
 than “that”. People, vote with your purse!</p>
----
Date: 08.06.2013 17:38
Author: tg@
Title: Waypoint Statistics
Tag: debian geocache

<p class="cr"><a href="@@RELPATH@@WPtg.htm" style="border:0;"><img
 class="fr" style="border:0;" alt="mirabilos’ found waypoints"
 src="@@RELPATH@@WPtg.png" /></a></p>
<p>I’ve finally gotten around to listing all Waypoints (Geocaches,
 Opencaches, Closedcaches, Earthcaches, Terracaches including
 Locationless, Navicaches, etc.) I’ve found a box, enjoyful,
 educating, a good place to hide one myself, etc. and putting up
 a <a href="@@RELPATH@@WPtg.htm">list</a> and, of course, generate
 my own statpic.</p>
<p class="cr">I’ll put them up for the other project members, too
 (already made a picture for gecko2@ but bsiegert@ still needs one;
 we also need to collect offline lists of found, owned and attended
 waypoints)…</p>
<p>A bit of background story: I decided, years ago, to have an offline
 list of cache finds in case something would happen. Just, I had found
 way too many already, so this was a huge bit of work. Oh well… I of
 course procrastinated, and then something did happen (Opencaching
 wanting to force a <a href="http://freeculture.org/blog/2012/08/27/stop-the-inclusion-of-proprietary-licenses-in-creative-commons-4-0/">Restricted
 Commons</a> licence; me disagreeing and suggesting a change; some
 trigger-happy person immediately deleting my account without waiting
 for the discussion <em>or</em> the decision period to end; weeks of
 forum discussions; Opencaching allowing dual-licencing; them telling
 me they can’t restore my data – probably never heard of databa…sorry,
 MySQL backups). And I still didn’t have the list. Now I do; recreated
 even the OC information from what was still accessible and with help
 from one OC supporter (“<tt>mic@</tt>”, thanks); merged caches that
 are co-listed on several platforms, etc. (still need to put in the
 FTF/STF/TTF/4TF/LTF and voting/favourites information) and a statpic,
 all in Open Source and Open Data, in cvs(1) with mksh(1) and… a…
 frontend for libgd2 I admit, but we had been using that for the
 MirWebsite for a while already.</p>
<p>I suggest every geocacher keep an offline or local record of all
 their finds (and hides and attended logs) for things like this, in
 case some platform decides to… let’s say, “put your data into the
 cloud… where it is? I don’t know”.</p>
----
Date: 26.06.2013 20:27
Author: tg@
Title: Current slow period

<p>Just in case someone wonders… I haven’t found any time and “head
 capacity” to hack recently; $dayjob leaving me sucked dry, with the
 weather also playing in, etc. but neither did I disappear nor do I
 intend to drop anything planned.</p>
<p>Sorry for keeping even medium and more severe bugs open for such
 a long time (several weeks by now, for some); recently I was assured
 my response time – especially for an Open Source volunteer – is very
 <em>good</em> still, even if I find it lacking sometimes.</p>
<p><a href="@@RELPATH@@mksh.htm">mksh</a>, as one specific thing to
 mention here, will get an R47 release RSN™ (i.e. as soon as I get
 around to do it) which could be labelled R46b too (except I like
 integer version numbers more), it <em>will</em> (that’s a promise)
 be bugfix-only and <em>ought to</em> be dropped into any place
 that’s currently shipping R45 or R46, at the very least (and maybe
 R44 too, and no older versions should be around at all anyway).</p>
<p>Note that me beginning to catch up the TODO list, like today’s
 cvs(1) upload to Debian, shall not be taken as a sign of me being
 back (just that I found myself to tackle something). It did take
 way too long, it’s 22:15 localtime already again, and I had planned
 to catch up on my leisure reading a bit this evening (damn…) but,
 well. At least I managed to put in some outdoor fun (to be exact, <a
 href="@@RELPATH@@permalinks/wlog-10_e20130608-tg.htm">visiting some
 more waypoints</a>) too (though I expect this weekend to be scary
 <em>and</em> it’s definitely <em>under</em>planned ☹ – but who knows,
 maybe it’ll be great fun, and wbx@ and my biggest little brother are
 both a backup plan each.)</p><!-- RSS stop -->
<p class="cr"><img class="fr" alt="Combined BOINC stats for mirabilos"
 src="http://boincstats.com/signature/-1/user/388444/sig.png" /></p>
<p>Also toying a bit with BOINC again (MirBSD of course, and, this time,
 some spare CPU capacity at work, which <em>did</em> lead to detecting
 a hardware/system bug/malconfiguration, even!) prodded by the second
 (found!) and third (not found… yet) installment of a WCG LC.</p>
----
Date: 07.07.2013 15:39
Author: tg@
Title: MirWarm
Tag: debian fun

<p><a href="@@RELPATH@@pics/wlog/cats-5.jpg"><img
 alt="zz̼̐z" src="@@RELPATH@@pics/wlog/cats_5.jpg" /></a></p>
<p>Time for more neighbours’ <a
 href="@@RELPATH@@permalinks/wlog-10_e20110903-tg-g10048.htm">cat</a> <a
 href="@@RELPATH@@permalinks/wlog-10_e20110904-tg.htm">posts</a>, apparently.
 It’s warm, so the cat’s sleeping outside. Not disturbed by much.</p>
<p>Me envious. Too warm to go to the ice salon (bike’s in repair,
 car’s hot enough to boil eggs on it, public transport not better).</p>
----
Date: 18.07.2013 21:57
Author: tg@
Title: mksh/Win32
Tag: debian mksh news pcli

<p>Michael Langguth and Scalaris AG asked me to publish <a
 href="https://www.mirbsd.org/MirOS/dist/mir/mksh/ports/mksh-w32-beta14.zip">the
 mksh/Win32 Beta 14</a> source and binary archive, and it is with joy
 I’m doing this.</p>
<h3>Checksums and Hashes</h3><ul>
  <li>RMD160 (ports/mksh-w32-beta14.zip) = 0dc8ef6e95592bd132f701ca77c4e0a3afe46f24</li>
  <li>TIGER (ports/mksh-w32-beta14.zip) = 966e548f9e9c1d5b137ae3ec48e60db4a57c9a0ed15720fb</li>
  <li>1181543005 517402 /MirOS/dist/mir/mksh/ports/mksh-w32-beta14.zip</li>
  <li>MD5 (ports/mksh-w32-beta14.zip) = b57367b0710bf76a972b493562e2b6b5</li>
</ul>
<p>Just a few words on it (more in the README.1st file included): this is
 a port of <a href="@@RELPATH@@mksh.htm">The MirBSD Korn Shell</a> R39 to
 the native WinAPI; it’s not quite got the full Unix feel (especially as
 it targets the Weihenstephan unxutils instead of a full Interix or Cygwin
 environment) but doesn’t need a full POSIX emulation layer either. It’s
 intended to replace MKS ksh and the MKS Toolkit. Source for the compatibility
 library is also included under <a href="@@RELPATH@@MirOS-Licence.htm">The
 MirOS Licence</a>; we aim at publishing it as OSI Certified Open Source
 Software like mksh itself. (There is a situation with dlmalloc/nedmalloc
 being resolved, and the icon is derived from the BSD dæmon which is a
 protected unregistered trademark, but we’re not Mozilla and allow distro
 packages to keep using it ☺) Rebasing it on a newer mksh(1) followed by
 (partial) integration into the main source code is a goal.</p>
<p>Have fun trying it out and hacking on it. It’s currently built with
 <tt>-DMKSH_NOPROSPECTOFWORK</tt> (so coprocesses and a few other minor
 things won’t work), but a <tt>SIGCHLD</tt> emulation is being worked
 on – but if you want to help out, I’m sure it’s welcome, just come on
 <a href="@@RELPATH@@irc.htm">IRC</a> or post on the mailing list, and
 I’ll forward things to Michael as needed. Reports on testing with other
 toolchain and OS versions are also welcome.</p>
----
Date: 23.08.2013 23:37
Author: tg@
Title: FrOSCon 2013, or, why is there no MirBSD exhibit?
Tag: debian event geocache mksh

<p><a href="http://www.froscon.org/">FrOSCon</a> is approaching, and
 all MirBSD developers will attend… but why’s there no MirBSD exhibit?
 The answer to that is a bit complex. First let’s state that of course
 we will participate in the event as well as the Open Source world.
 We’ll also be <a href="@@RELPATH@@permalinks/wlog-10_e20130608-tg.htm"
 title="Waypoint Statistics">geocaching</a> around the campus with other
 interested (mostly OSS) people (including those we won for this sport)
 and helping out other OSS projects we’ve become attached to.</p>
<p>MirOS BSD, the operating system, is a niche system. The conference
 on the other hand got “younger” and more mainstream. This means that
 almost all conference visitors do not belong to the target group of
 MirOS BSD which somewhat is an “ancient solution”: the most classical
 BSD around (NetBSD® loses because they have rc.d and PAM and lack
 sendmail(8), sorry guys, your attempt at being not reformable doesn’t
 count) and running on restricted hardware (such as my 486SLC with 12
 MiB RAM) and exots (SPARCstation). It’s viable even as developer
 workstation (if your hardware is supported… otherwise just virtualise
 it) but its strength lies with SPARC support and “embedded x86”. And
 being run as virtual machine: we’re reportedly more stable and more
 performant than OpenBSD. MirBSD is not cut off from modern development
 and occasionally takes a questionable but justified choice (such as
 using 16-bit Unicode internally) or a weird-looking but beneficial
 one (such as OPTU encoding saving us locale(1) hassles) or even acts
 as technological pioneer (64-bit <tt>time_t</tt> on ILP32 platforms)
 or, at least, is faster than OpenBSD (newer GNU toolchain, things
 like that), but usually more conservatively, and yes, this is by
 design, not by lack of manpower, most of the time.</p>
<p>The MirPorts Framework, while technically superiour in enough
 places, is something that just cannot happen without manpower.
 I (tg@) am still using it exclusively, continuing to update ports
 I use and occasionally creating new ones (mupdf is in the works!),
 but it’s not something I’d recommend someone (other than an Mac OSX
 user) to use on a nōn-MirBSD system (Interix is not exactly thriving
 either, and the Interix support was only begun; other OSes are not
 widely tested).</p>
<p><a href="@@RELPATH@@mksh.htm">The MirBSD Korn Shell</a> is probably
 the one thing I will be remembered for. But I have absolutely no idea
 how one would present it on a booth at such an exhibition. A talk is
 much more likely. So no on that front too.</p>
<p><a href="@@RELPATH@@jupp.htm">jupp, the editor which sucks less</a>,
 is probably something that does deserve mainstream interest (especially
 considering Natureshadow is using it while teaching computing to kids)
 but probably more in a workshop setting. And booth space is precious
 enough in the FH so I think that’d be unfair.</p>
<p>All the other subprojects and side projects Benny and I have, such
 as mirₘᵢₙcⒺ,
 josef stalin, FreeWRT, Lunix Ewe, Shellsnippets, the fonts, etc. are
 interesting but share few, if any, common ground. Again, this does not
 match the vast majority of visitors. While we probably should push a
 number of these more, but a booth isn’t “it” here, either.</p>
<p>MirOS Linux (“MirLinux”) and MirOS Windows are, despite otherwise-saying
 rumours called W*k*p*d*a, only premature ideas that will not really be
 worked on (though MirLinux concepts are found in mirₘᵢₙcⒺ and stalin).</p>
<p>As you can see, despite all developers having full-time dayjobs,
 The MirOS Project is far from being obsolete. We hope that our website
 visitors understand our reasons to not have an exhibition booth of our
 own (even if the SPARCstation makes for a way cool one, it’s too heavy
 to lift all the time), and would like to point out that there are several
 other booths (commercial ones, as well as OSS ones such as AllBSD, Debian
 and (talking to) others) and other itineries we participate in. This year
 both Benny and I have been roped into helping out the conference itself,
 too (not exactly unvoluntarily though).</p>
<p>The best way to talk to us is <a href="@@RELPATH@@irc.htm">IRC</a>
 during regular European “geek” hours (i.e. until way too late into the
 night – which Americans should benefit from), semi-synchronously, or <a
 href="@@RELPATH@@rss.htm#lists">mailing lists</a>. We sort of expect you
 to not be afraid to <a href="@@RELPATH@@man.htm">RTFM</a> and <a
 href="@@RELPATH@@wtf.htm">look up acronyms</a> you don’t understand;
 The MirOS Project is not unfriendly but definitely not suited for your
 proverbial Aunt Tilly, newbies, “desktop” users, and people who aren’t
 at least somewhat capable of using written English (this is by design).</p>
----
Date: 24.11.2013 23:42
Author: tg@
Title: MirBSD in jslinux

<p>Bochs is not the only emulator. But Fabrice Bellard wrote more
 than just qemu, either – tonight I did a quick hack and <a
 href="http://oi43.tinypic.com/30aw6xv.jpg">started booting MirBSD
 in jslinux</a>. Unmodified. Of course, there are still things to
 change before this goes into userspace, and the bootloader wants
 to be ported to ECMAscript as well, but… I got some dmesg(8)!</p>
<p>Feel free to call me crazy now. Anyway, more on this as time
 and legalese permits. This was a can-do test in about 2 hours of
 work, only.</p>
----
Date: 02.12.2013 19:41
Author: tg@
Title: Neo900
Tag: debian

<p>I’ve did something I surely will (financially) regret, next year,
 and designated the <a href="http://neo900.org/">Neo900</a> to be the
 successor to my PocketPC, due to the latter having only 64 MiB RAM
 and Geocaching applications being quite hungry. It’s got a lovely
 hardware keyboard, a “pen” display like the PocketPC (as opposed to
 the “wishy-washy” displays that Android and iPhone have), not only
 GPS but also GLONASS, fully free software with mostly free firmware
 (I’m okay with that, mostly), a Ctrl key (useful in ssh and locally
 and <a href="@@RELPATH@@jupp.htm">my text editor</a>; <tt>^I</tt>
 is Tab, so it’s useful in <a href="@@RELPATH@@mksh.htm">shell</a>,
 too), WLAN, UMTS (I don’t think I need LTE and would rather it have
 the more RAM), USB host (OTG), and lots of other nice features.</p>
<p>In short, it’s a tinkerable device: one I can not only hack at,
 but also hack <em>on</em>.</p>
<p>Since I use a “dumbphone” for mobile phone anyway (pro: separate
 battery from the “toy” PocketPC/Smartphone – we’re talking two+
 <strong>weeks</strong> of battery time <em>when using it</em> here,
 and easier use and less bugs, and a reliable fallback when I tinker
 “too much”), this is perfect for me.</p>
<p>I’m reposting this in the wlog mostly because it’s an interesting
 technical and OSS project, and because if 1000 people want one it
 will get less expensive for all of us (while here… shameless plug…
 any sponsors willing to contribute some EUR so I don’t ruin myself
 with this, in exchange for services of some kind?). I’ll probably
 run Debian on it (unless it goes systemd), maybe in a chroot – if
 the native OS has functionality needed that I can’t simply put into
 packages; they say Maemo has <em>much</em> better power management,
 but considering most use will have GPS, GLONASS and backlight on,
 battery isn’t going to last long anyway… – or maybe even native…
 I’ve been wanting to know what this “freesmartphone” stuff my m68k
 (Atari VM) buildd has been happily compiling, anyway… and some sort
 of Geocaching application (ideally a cross between something online,
 <a href="http://www.cachewolf.de/">CacheWolf</a> and an offline OSM
 (with most of Europe, but uninteresting tags stripped) and possibly
 access to the GS Live API but nevertheless supporting TC, NC, OC,
 gpsgames too), and my usual mksh(1), GNU screen, jupp(1), lynx(1),
 ssh(1) toolchain.)</p>
<p>Delivery is expected for mid to end of 2014, but once it’s there
 I’ll keep you informed ☺</p><!-- RSS stop -->
<p>On that matter… I’ve got my PocketPC (currently in production use)
 and another WinCE device and wonder about tinkering with them, too.
 It appears to be a rather open platform (compared to Android, anyway)
 but most official documentation is tied to Windows® host systems, and
 most utilities have been taken offline after the abomination called
 Windows Phone has taken over. Hm I’ve got PocketPython and some sort
 of cross GCC but nothing to tinker with the core OS / ROM image…</p>
----
Date: 02.01.2014 14:35
Author: bsiegert@
Title: On modern VCSes

<p>There has been an ongoing discussion in the NetBSD community about
 migrating away from CVS (something that is not in question here, I know
 I know)&mdash;to the point that the
 <a href="http://mail-index.netbsd.org/tech-repository/">tech-repository
  mailing list</a>
 has been set up specifically for this discussion.</p>

<p>Eric S. Raymond recently posted an article titled
 <a href="https://lists.gnu.org/archive/html/emacs-devel/2014-01/msg00005.html">"bzr is dying; Emacs needs to move"</a>
 on emacs-devel. Thomas Klausner remarked that if you apply
 <tt>sed -e "s/emacs/NetBSD/g" -e "s/bzr/CVS/g"</tt> to the post, then
 the same applies, frighteningly accurate in fact:</p>

<blockquote>
 <p>In practice, I judge that sticking with CVS would have social and
  signaling effects damaging to NetBSD's prospects. Sticking to a
  moribund version-control system will compound and exacerbate the
  project's difficulty in attracting new talent.</p>

 <p>The uncomfortable truth is that many younger hackers already think
  CVS is a dinosaur &ndash; difficult, bulky, armor-plated, and generally
  stuck in the last century. If we're going to fight off that image, we
  cannot afford to make or adhere to choices that further cast the
  project as crusty, insular, and backward-looking.</p>
</blockquote>

<p>This is what I wrote in reply:</p>

<blockquote>
 <p>Scary how spot-on this is after the above substitution. I fully agree.</p>

 <p>I know that this may spawn another centithread but: how about we use a
  "canary" for a VCS migration? For example, moving pkgsrc-wip to git
  would probably be trivial, considering that it's sourceforge that
  hosts it. Last time I checked, sourceforge supports hosted git
  repositories.</p>

 <p>As a new data point, I did some hacking on pkgsrc on MirBSD during
  30c3 using a clone of
  <a href="https://github.com/jsonn/pkgsrc/">github.com/jsonn/pkgsrc</a>.
  This was in part to work around the freeze, in part to see how git copes with
  the typical pkgsrc workflows. I was positively surprised, I must say. Some
  observations:</p>

 <ul>
  <li>you want distfiles/ and packages/ in gitignore.</li>
  <li>not ignoring work directories is actually a convenient way to find
   stale work directories quickly.</li>
  <li>downgrading a single package (in my case, to get autoconf-2.61 for
   some configure script) is easy to do, using
   <tt>git checkout $revision devel/autoconf</tt>
   This set the working copy back to the given revision and put the changes to
   HEAD into the index.</li>
  <li>branch/rebase/merge is a good workflow for upgrading single packages.</li>
 </ul>

 <p>Thus, even if the NetBSD project is not prepared to move to git
  outright, we could do a move for pkgsrc-git, then pkgsrc. src could
  come later.</p>
</blockquote>
----
Date: 04.01.2014 20:09
Author: tg@
Title: jupp, coming to a Fedora near you soon!
Tag: jupp news pcli

<p>Thanks to Robert Scheck, <a href="@@RELPATH@@jupp.htm">jupp – the
 Editor which sucks less</a> (a WordStar™-compatible Unix editor
 with lots of features, including a hex editor) is currently <a
 href="https://admin.fedoraproject.org/updates/search/jupp">on its
 way to Fedora</a> and EPEL (RHEL/CentOS 5 and 6).</p>
<p>Depending on your distribution, you will have it available within
 one to two weeks, I’m being told.</p>
<p>This adds another distribution to the list; jupp has been available
 in Debian and its derivates (some of which may not be named) for some
 time (due to user request), and the webpage contains Win32 binaries
 (made with Cygwin, an oldish version to be compatible to Win9x).</p>
<p>jupp is especially useful as programmers’ editor, but also used in
 teaching school-aged kids the joys of IT; Natureshadow has prepared
 a cheat sheet, which we will internationalise and localise, then link
 from the jupp homepage – so stay tuned! (I guess we’ll also need a
 concise list of jupp features, in lieu of advertising.)</p>
----
Date: 20.01.2014 21:49
Author: tg@
Title: FOSDEM preparations… done.
Tag: debian event fun grml mksh twitxr work

<p>I’ve produced several pin-on buttons to take with me to <a
 href="https://fosdem.org/">FOSDEM</a> for giving away (as
 long as there are any left):</p>
<p><img alt="Several pin-on buttons I made"
 src="@@RELPATH@@pics/wlog/btn14a20.jpg" /></p>
<p>First row (nice projects), from left to right: <a
 href="http://www.midnightbsd.org/">MidnightBSD</a>; <a
 href="http://plan9.bell-labs.com/plan9/glenda.html">Glenda</a>, the
 <a href="http://9fans.net/">Plan 9</a> bunny; <a
 href="https://www.teckids.org/ad.cgi">Teckids e.V.</a></p>
<p>Second row (<a href="@@RELPATH@@main.htm">The MirOS Project</a>):
 <a href="@@RELPATH@@mksh.htm">mksh</a>; the Shilouette Dæmon; the
 “Triforce” (Live+Install CDs for i386 and sparc, with Mir<a
 href="http://grml.org/">Grml</a>); “the m” (alternative logo, vector)</p>
<p>Third row (things originating from tarent): <a
 href="http://freedroidz.org/">Freedroidz</a> (now a Teckids project);
 <a href="https://www.osiam.org/">OSIAM</a> (Identity and Access Management);
 <a href="https://www.tarent.de/">tarent</a> (tarent AG, tarent GmbH),
 who sponsored production of these buttons</p>
<p>Hm… <a href="@@RELPATH@@jupp.htm">jupp</a> needs a button’able logo!</p>
<hr />
<p><a href="http://coord.info/GC4V7ZQ">FOSDEM meetup</a></p>
----
Date: 22.01.2014 20:02
Author: tg@
Title: Lacking hacking time. Puppet stinks.
Tag: personal rant work

<p>Meh. I announced a tree breaker. Would be nice if I actually found
 enough spare time to hack on it before, I think, end of March (which
 is roughly when I’m planning to decommission both <tt>eurynome</tt>
 and, for monetary reasons (not going to do an OpenBSD here and cry
 about needing funds, as those who know me know this is a constant),
 the manitu server).</p>
<p>Took me 62 minutes to write a functioning OSIAM installer in mksh(1)
 after getting annoyed that the Puppet-lovers are either ill, not able
 to work on the project I have to finish by Friday, or not yet skilled
 enough to help. Got the entire thing working (but this week sees way
 too many overlong days at the workplace), estimate finishing with full
 success by tomorrow afternoon, with zero puppet but lots of <a
 href="@@RELPATH@@mksh.htm">mksh</a>. Maintainable, too.</p>
----
Date: 26.01.2014 20:29
Author: tg@
Title: mksh build problem workaround
Tag: mksh

<p class="boxhead">As a workaround to the build problem of <a
 href="@@RELPATH@@mksh.htm">mksh</a> R49 with some host shells,
 you can try removing every sequence of backslash + newline in
 <tt>rlimits.opt</tt> and <tt>sh_flags.opt</tt>, for example with
 the following sequence:</p><div class="boxtext">
 <pre>
	cd /path/to/mksh
	for f in *.opt; do
		tr '\n' '`' &lt;"$f" | \
		    sed 's/\\`//g' | \
		    tr '`' '\n' &gt;"$f.out"
		mv "$f.out" "$f"
	done
 </pre>
</div><p class="boxfoot">This will apply to every upcoming
 mksh(1) release until such time as this code has been
 rewritten in (host) C. Another thing that could be done is
 to add <tt>-r</tt> to both <tt>IFS= read line</tt> occurences
 in <tt>Build.sh</tt>, function <tt>do_genopt</tt>.</p>
----
Date: 06.02.2014 14:28
Author: tg@
Title: KISS
Tag: archaeology debian fun jupp pcli

<p class="boxhead">Just saw this in my INBOX:</p><div class="boxtext">
 <pre>
    B. The default init system for jessie will be a single /etc/rc script
 </pre>
</div><p class="boxfoot">I’d certainly vote that❣</p>
<hr />
<p>In unrelated news, <a href="@@RELPATH@@jupp.htm#bdos">jupp 2.8 for DOS</a>
 runs on <a href="http://ioccc.org/2013/cable3/hint.html">cable3</a>, which
 means it’ll still run on an original 8088/8086 ☻</p>
<p><strong>Update 10.02.2014</strong>: The unobfuscated version of cable3 is
 called <a href="http://www.megalith.co.uk/8086tiny/">8086tiny</a> under the
 MIT licence. Thanks to the author for doing that (and not just dumping the
 IOCCC code) and to RT from the mksh(1) <a href="@@RELPATH@@ksh-chan.htm">IRC
 channel</a> for finding it on the ’net!</p>
----
Date: 30.03.2014 14:30
Author: tg@
Title: FreeWRT Archive
Tag: archaeology freewrt news pcli snapshot

<p>As <a href="http://article.gmane.org/gmane.comp.embedded.freewrt.announce/10">previously
 announced</a>, the FreeWRT Project has been archived. You can access the
 content at the <a href="@@RELPATH@@FreeWRT.htm">FreeWRT Archive Site</a>
 on the MirWebseite.</p>
<p>ObRant: <a href="@@RELPATH@@wtf.cgi?DST">DST</a> (Sommerzeit) sucks!</p>
----
Date: 01.04.2014 12:24
Author: tg@
Title: Sorry about the MediaWiki-related breakage in wheezy
Tag: debian work

<p>I would like to publicly apologise for the inconvenience caused by my
 recent updates to the <tt>mediawiki</tt> and <tt>mediawiki-extensions</tt>
 source packages in Debian wheezy (stable-security).</p>
<p>As for reasons… I’m doing Mediawiki-related work at my dayjob, as part
 of <a href="https://fusionforge.org/">FusionForge</a>/Evolvis development,
 and try to upstream as much as I can. Our production environment is a
 Debian wheezy-based system with a selection of newer packages, including
 MediaWiki from sid (although I also have a test system running sid, so my
 uploads to Debian are generally better tested). I haven’t had experience
 with stable-security uploads before, and made small oversights (and did
 not run the full series of tests on the “final”, permitted-to-upload,
 version, only beforehand) which led to the problems. The situation was
 a bit complicated by the need to update the two packages in lockstep,
 to fight an RC bug file/symlink conflict, which was hard enough to do
 in sid already, plus the desire to fix other possibly-RC bugs at the
 same time. I also got no external review, although I cannot blame anyone
 since I never asked anyone explicitly, so I accept this as my fault.</p>
<p>The issues with the updates are:</p><ul>
 <li>mediawiki 1.19.5-1+deb7u1 (the previous stable-security update) was
  not made by me but by Jonathan Wiltshire</li>
 <li>mediawiki 1.19.11+dfsg-0+deb7u1 (made by me) was fine, fixed the
  bugs it was supposed to, but was delayed after being uploaded to
  security-master-unembargoed</li>
 <li>mediawiki 1.19.14+dfsg-0+deb7u1 was supposed to be a mostly
  upstream update, but I decided to add changes to fix issues pointed
  out by lintian (not trivial ones), and mistakenly forgot to remove
  two lines that should not have crept in from sid</li>
 <li>mediawiki 1.19.14+dfsg-0+deb7u2 was quickly uploaded to fix
  this issue but took about half a day to be ACCEPTed</li>
 <li>mediawiki-extensions 3.5~deb7u1 should have be named 2.12 but
  could not, due to the aforementioned lockstep update requirement
  and version checks in maintainer scripts; it fixes the issues but
  does not add other changes from 3.5 in sid… unfortunately, the
  packaging uses <tt>cdbs</tt> (which I dislike quite a lot, but as
  the newcomer in the team I decided to accept it and go on; changing
  the existing packaging would be quite some effort anyway) and wants
  <tt>debian/control</tt> to be regenerated from <tt>control.in</tt>…
  which I <em>thought</em> I had done, and normally do…</li>
 <li>mediawiki-extensions 3.6 (in sid) fixes another dir/symlink
  conflict shown up after 3.5 was made. I’ve requested upload
  permission for regenerating <tt>debian/control</tt> and asked
  whether I am allowed to include this fix as well</li>
</ul>
<p>My unfamiliarity with some of the packaging concepts used here,
 combined with this being something I do during $dayjob (which can
 limit the time I can invest, although I’m doing much more work on
 Mediawiki in Debian than I <i>thought</i> I could do on the job),
 can cause some of those oversights. I guess I also should install
 a vanilla wheezy environment somewhere for testing… I do not
 normally do stable uploads (jmw did them before), so I was not
 prepared for that.</p>
<p>And, while here: thanks to the Debian Security Team for putting
 up with me (also in <a href="http://lists.fusionforge.org/pipermail/fusionforge-general/2014-March/002645.html">this
 week’s FusionForge issue</a>), and thanks to Mediawiki upstream for
 agreeing to support releases shipped in Debian stable for longer
 support, so we can easily do stable-security updates.</p>
----
Date: 09.04.2014 19:51
Author: tg@
Title: Heartbleed vs. Startcom / StartSSL
Tag: bug debian news rant security work

<p>First of all, good news, MirBSD is <em>not</em> vulnerable to <a
 href="http://heartbleed.com/">The Heartbleed Bug</a> due to my
 deliberate choice to stick to an older OpenSSL version. My inquiry
 (in various places) as to what <em>precisely</em> could leak when
 a vulnerable client connected to a nōn-vulnerable server has yet
 to be answered, though we can assume private key material is safe.</p>
<p>Now the bad news: while <a href="http://www.godaddy.com/">the CA
 I use</a>¹ and <a href="http://www.cacert.org/">a CA I don’t use</a>
 offer free rekeying (in general), <a href="http://www.startssl.com/">a
 CA I also use occasionally²</a> refuses to do that. The ugly: they
 will not even revoke the certificates, so any attacker who gained
 your key, for example when you have been using a certificate of
 theirs on a Debian system, will be able to use it (e.g. to MITM your
 visitors traffic) unless you shell over lots of unreasonable money
 per certificate. (Someone wrote they got the fee waived, but <a
 href="https://cv.exbit.io/emails/startssl_heartbeat.txt">others</a> don’t, <a
 href="https://bugzilla.mozilla.org/show_bug.cgi?id=994033#c20">nor do
 I</a>. (There’s also a great Twitter discussion-thingy about this
 involving Zugschlus, but I won’t link Twitter because they are not
 accessible to <a href="http://lynx.invisible-island.net/">Lynx</a> users
 like me and other Planet Debian authors.)</p>
<div style="font-size:90%;">
<p>① I’ve been using GoDaddy privately for a while, paid for a wildcard
 certificate for <tt>*.mirbsd.org</tt>, and later also at work. I’ve
 stopped using it privately due to current lack of money.</p>
<p>② Occasionally, for nōn-wildcard gratis SSL certificates for HTTP servers.
 <a href="http://forum.startcom.org/viewtopic.php?f=15&amp;t=2328">Startcom’s
 StartSSL certificates are unusable for real SSL as used in SMTP STARTTLS</a>
 anyway, so usage isn’t much.</p>
</div>
<p>Now I’ve got a dilemma here. I’ve created a CA myself, to use with
 MirBSD infrastructure and things like that – X.509 certificates for
 my hosts (especially so I can use them for SMTP) and possibly personal
 friends (whose PGP key I’ve signed with maximum trust after the usual
 verification) but am using a StartSSL certificate for <tt>www.mirbsd.org</tt>
 as my GoDaddy wildcard certificate expires in a week or so (due to the
 aforementioned monetary issues), and I’d rather not pay for a limited
 certificate only supporting a single vhost. There is absolutely no issue
 with that certificate and key (only ever generated and used on MirBSD,
 only using it in Apache mod_ssl). Then, there’s this soon-to-be tax-exempt
 non-profit society of public utility I’m working with, whose server runs
 Debian, and which is affected, but has been using a StartSSL certificate
 for a while. Neither the society nor I can afford to pay for revocation,
 and we do not see any possible justification for this especially in the
 face of CVE-2014-0160. I expect a rekey keeping the current validity end
 date, and would accept a revocation even if I were unable to get a new
 certificate, since even were we to get a certificate for the society’s
 domain from someplace else, an attacker could still MITM us with the
 previous one from Startcom.</p>
<p>The problem here is: I’d really love to see (all of!) Startcom dropped
 from the global list of trustworthy CAs, but then I’d not know from where
 to get a cert for MirBSD; Globalsign is not an option because I will not
 limit SSL compatibility to a level needed to pass their “quality” test…
 possibly GoDaddy, ISTR they offer a free year to Open Source projects…
 no idea about one for the society… but it would solve the problem of not
 getting the certificates revoked. For everyone.</p>
<p>I am giving Startcom time until Friday after $dayjob (for me); after
 that, I’ll be kicking them off MirBSD’s CA bundle and will be lobbying
 for Debian and Mozilla to do the same.</p>
<p>Any other ideas of how to deal with that? I’d probably pay 5 € for a
 usable certificate accepted by people (including old systems, such as
 MSIE 5.0 on Win2k and the likes) without questioning… most of the time,
 I only serve public content anyway and just use SSL to make the NSA’s
 job more difficult (and even when not I’m not dealing with any payment
 information, just the occasional login protected area).</p>
<p>By the way, is there <em>any</em> way to access the information that
 is behind a current-day link to <tt>groups.google.com</tt> with Lynx or
 Pine? I can’t help but praise GMane for their NNTP interface.</p>
<p>ObFunfact: just when I was finished writing this wlog entry, I got a
 new eMail “Special offer just for you.” from GoDaddy. Sadly, no offer
 for a 5 € SSL certificate, just the usual 20-35% off coupon code.</p>
----
Date: 18.04.2014 22:45
Author: tg@
Title: Stay off my computer, puppet!
Tag: bug debian fun geocache pcli rant tip work

<p>I was out, seeing something that wasn’t there yet when I was at
 school (the “web” was not ubiquitous, back then), and decided to
 have a look:</p>
<pre>pageok</pre>
<p class="boxhead">Ugh. Oh well, PocketIE doesn’t provide a “View
 Source” thingy, so I asked Natureshadow (who got the same result
 on his Android, and had no “View Source” either apparently, so he
 used cURL to see it). We saw (here, re-enacted using ftp(1)):</p>
<div class="boxtext">
 <pre>
	tg@blau:~ $ ftp -Vo - http://www.draitschbrunnen.de/
	&lt;!-- pageok --&gt;
	&lt;!-- managed by puppet --&gt;
	&lt;html&gt;
	&lt;pre&gt;pageok&lt;/pre&gt;
	&lt;/html&gt;
 </pre>
</div><p class="boxfoot">This is the final straw… after puppet
 managed to trash a sudoers(5) at work (I warned people to not
 introduce it) now it breaks websites. ☺</p>
<p style="font-size:small;">(Of course, tools are useful, but
 at best to the skill of their users. Merely dumbly copying
 recipes from “the ’net” without any understanding just makes
 debugging harder for those of us <em>with</em> skills.)</p>
<p>ObQuestion: Does anyone have ⓐ a transcript (into UTF-8)
 and ⓑ a translation for the <em>other</em> half of the <a
 href="http://www.openbsd.org/images/poster4.jpg">OpenBSD
 2.8 poster</a>? (I get asked this regularily.)<br
 /><strong>Update:</strong> One person sent me the Kanji
 and Kana for it in UTF-8 「俺のマシンに手を出すな！」,
 and they and one more person told me it’s “Hands off my
 machine!” or “Don’t lay a hand on my machine!”. Now I’m
 not studying Japanese, but it LGTM in FixedMisc [MirOS],
 and JMdict from MirPorts says: ore no mashin ni te (w)o
 dasu na (roughly: my machine; particle; hands; particle;
 put out; prohibition) ☺ Thanks all, now I know what to
 tell visitors who wonder about that poster on my wall.</p>
<p>ObTip: I can install a few hundred Debian VMs at work
 manually before the effort needed to automate d-i would
 amortise. So I decided not to. Coworkers are shocked. I
 keep flexibility (can decide to have machines differ),
 and the boss accepts my explanations. Think before doing
 automation just for the sake of automation!</p>
----
Date: 20.05.2014 11:37
Author: bsiegert@
Title: Tip of the Day (Vim)

<p>Today I learned something about file encodings in vim. When your
 terminal is UTF-8 but Vim insists on treating the file you are opening
 as latin-1, here is what to do: Setting <tt>fileencoding</tt> on the
 already opened file will not work, it will only try to convert the file
 (i.e. the wrongly interpreted UTF-8 sequences) to UTF-8. Don't do
 this!</p>

<p>The solution is to reopen the file using</p>
<p><tt>:e ++enc=utf8</tt></p>
<p>or specify the <tt>++enc</tt> parameter when opening the file from
 inside vim. The more you know.</p>
----
Date: 20.05.2014 11:37:01
Author: tg@
Title: More on the Vim thing
Tag: tip

<p>As an update to the issue with Vim not treating a file as UTF-8 <a
 href="@@RELPATH@@permalinks/wlog-10_e20140520-bsiegert.htm">Benny
 wrote about</a> earlier, there’s more to note:</p>
<ul>
 <li>The <a href="@@RELPATH@@cvs.cgi/src/share/misc/acronyms">file in
  question</a> contained two lines that were copied from the Other BSD,
  which were not UTF-8. This probably led to Vim not wanting to treat
  the entire file as UTF-8. (This is not normally a problem in vi(1),
  AFAIK (but in nvi in Debian, which truncates the file on write, with
  no way to recover), and <a href="@@RELPATH@@jupp.htm">jupp</a> even
  has mixed-encoding files as a primary use case.)</li>
 <li>When treating the file as UTF-8 forcefully, which Benny used, the
  file was saved with the offending bytes replaced by question marks
  (which was discovered by me in cvs(1) diff(1), leading to a fix and
  this post-mortem analysis)</li>
</ul>
<p>This is apparently something every editor user should know about.
 Another lesson learned: run <tt>$VCS diff</tt> before committing!</p>
<p>And something for me to take from this: check file encodings when
 importing from poorer OSes, and in general.</p>
----
Title: mksh R50, jupp 27 released
Date: 29.06.2014 13:20
Author: tg@
Tag: jupp mksh news pcli

<p>Both the <a href="@@RELPATH@@mksh.htm">MirBSD Korn Shell</a> and
 <a href="@@RELPATH@@jupp.htm">jupp – the editor which sucks less</a>
 have seen new releases today. Please test them, report all bugs,
 and otherwise enjoy all the bugfixes.</p>
<p>Other subprojects will also have new releases… once I get around
 doing so after hacking them…</p>
<p><strong>Update 03.07.2014</strong>: New release for MirCPIO, that
 is, cpio(1) and pax(1) and tar(1) in a somewhat portable package.</p>
<tt class="dowrap">-r--r--r--  4 tg  miros-cvssrc  141973 Jul  3 19:56 /MirOS/dist/mir/cpio/paxmirabilis-20140703.cpio.gz</tt>
----
Title: mksh R50b released
Date: 03.09.2014 19:54
Author: tg@
Tag: mksh news pcli

<p>The <a href="@@RELPATH@@mksh.htm">MirBSD Korn Shell</a> has got
 a new bugfix release. Thought you’d want to know ☺</p>
----
Title: mksh R50c released, security fix
Date: 03.10.2014 18:12
Author: tg@
Tag: android bug debian mksh news pcli release security

<p>The <a href="@@RELPATH@@mksh.htm">MirBSD Korn Shell</a> has got
 a new <strong>security</strong> and maintenance release.</p>
<p>This release fixes one mksh(1)-specific issue when importing
 values from the environment. The issue has been detected by the
 main developer during careful code review, looking at whether
 the shell is affected by the recent “shellshock” bugs in GNU bash,
 many of which also affect AT&amp;T ksh93. (The answer is: no, none
 of these bugs affects mksh.) Stephane Chanzelas kindly provided me
 with an in-depth look at how this can be exploited. The issue has
 not got a CVE identifier because it was identified as low-risk.
 The problem here is that the environment import filter mistakenly
 accepted variables named “FOO+” (for any <i>FOO</i>), which are,
 by general environ(7) syntax, distinct from “FOO”, and treated
 them as appending to the value of “FOO”. An attacker who already
 had access to the environment could so append values to parameters
 passed through programs (including sudo(8) or setuid) to shell
 scripts, including indirectly, after those programs intended to
 sanitise the environment, e.g. invalidating the last <tt>$PATH</tt>
 component. It could also be used to circumvent sudo’s environment
 filter which protected against the vulnerability of an unpatched
 GNU bash being exploited.</p>
<p><strong>tl;dr:</strong> <a href="@@RELPATH@@mksh.htm">mksh</a>
 not affected by any shellshock bugs, but we found a bug of our
 own, with low impact, which does not affect any other shell, during
 careful code review. Please do update to mksh R50c quickly.</p>
----
Title: mksh R50d released
Date: 07.10.2014 15:54
Author: tg@
Tag: bug debian mksh news pcli

<p>The last <a href="@@RELPATH@@mksh.htm">MirBSD Korn Shell</a> update
 broke <tt>update-initramfs</tt> because I accidentally introduced a
 regression in field splitting while fixing other bugs – sorry!</p>
<p>mksh R50d was just released to fix that, and a small NULL pointer
 dereference found by Goodbox on IRC. Thanks to my employer <a
 href="http://www.tarent.de/">tarent</a> for a bit of time to work on it.</p>
----
Title: The colon in the shell: corrigenda
Date: 09.12.2014 10:40
Author: tg@
Tag: debian mksh pcli

<p>Bernhard’s <a href="http://blog.brlink.eu/index.html#i70">article</a>
 on Plänet Debian about the “colon” command in the shell could use a
 clarification and a <em>security-relevant</em> correcture.</p>
<p>There is, indeed, no difference between the <tt>:</tt> and <tt>true</tt>
 built-in commands.</p>
<p><a href="http://unix.stackexchange.com/q/171346/43720">Stéphane Chazelas
 points out</a> that writing <tt style="color:red;">: ${VARNAME:=default}</tt>
 is <strong>bad</strong>, <tt style="color:green;">: "${VARNAME:=default}"</tt>
 is correct. Reason: someone could preset <tt>$VARNAME</tt> with, for
 example, <tt>/*/*/*/*/../../../../*/*/*/*/../../../../*/*/*/*</tt> which
 will exhaust during globbing.</p>
<p>Besides that, the article is good. Thanks Bernhard for posting it!</p>
<p>PS: I sometimes use the colon as comment leader in the last line of a
 script or function, because it, unlike the <a
 href="http://fsinfo.noone.org/~abe/Bloedsinn/Teppich.html##">octothorpe</a>,
 sets <tt>$?</tt> to 0, which can be useful.</p>
<p><strong>Update:</strong> As jilles pointed out in IRC, “colon” (‘:’) is <a
 href="http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_14">a
 POSIX special built-in</a> (most importantly, it keeps assignments), whereas
 “true” is a regular built-in utility.</p>
----
Title: mksh R50f coming soon
Date: 11.04.2015 23:39
Author: tg@
Tag: mksh pcli

<p>Please test <a href="@@RELPATH@@mksh.htm">mksh</a>-current from CVS (or
 the <a href="https://github.com/MirBSD/mksh">inofficial git mirror</a>)!
 There are security-related fixes I’ll MFC in a few days, for which I’d
 prefer for them (and the other changes) to not introduce any regressions.
 Thanks!</p>
----
Title: portable shebang for mksh on Unix and Android
Date: 27.06.2015 21:50
Author: tg@
Tag: mksh pcli

<p><tt>carstenh</tt> asked in <a href="@@RELPATH@@irc.htm">IRC</a> how
 to make a shebang for mksh(1) scripts that works on both regular Unix
 and Android.</p>
<p>This is not as easy as it looks, though. Most Unicēs will have <a
 href="@@RELPATH@@mksh.htm">mksh</a> installed, either manually or by
 means of the native package system, as <tt>/bin/mksh</tt>. Some put it
 into package manager-specific directories; I saw <tt>/sw/bin/mksh</tt>,
 <tt>/usr/local/bin/mksh</tt> and <tt>/usr/pkg/bin/mksh</tt> so far.
 Some systems have it as <tt>/usr/bin/mksh</tt> but these are usually
 those who got poettering’d and have <tt>/bin</tt> a symlink anyway.
 Most of these systems also have env(1) as <tt>/usr/bin/env</tt>.</p>
<p>Android, on the contrary, ships with precisely one shell. This has
 been mksh for a while, thankfully. There is, however, <em>neither</em>
 a <tt>/bin</tt> nor a <tt>/usr</tt> directory. mksh usually lives as
 <tt>/system/bin/mksh</tt>, with <tt>/system/bin/sh</tt> a symlink(7)
 to the former location. Some broken Android versions ship the binary
 in the latter location instead and do not ship anything that matches
 mksh on the <tt>$PATH</tt>, but I hope they merge my AOSP patch to
 revert this bad change (especially as some third-party Android toolkits
 overwrite <tt>/system/bin/sh</tt> with busybox sh or GNU bash and you’d
 lose mksh in the progress). However, on all official Android systems,
 mksh is the system shell. This will be important later.</p>
<p>The obvious and correct fix is, of course, to <tt>chmod -x</tt> the
 scripts and call them explicitly as <tt>mksh scriptname</tt>. This is
 not always possible or desirable; sometimes, people will wish it to be
 in the <tt>$PATH</tt> and executable, so we need a different solution.</p>
<p>There’s a neat trick with shebangs – the absence of one is handled
 specifically by <em>most</em> systems in various ways. I remember reading
 about it, but don’t remember where; I can’t find it on Sven Mascheck’s
 excellent pages… but: the C shell variants run a script with the Bourne
 Shell if its first line is a sole colon (‘:’), the Bourne family shells
 run it with themselves or <tt>${EXECSHELL:-/bin/sh}</tt> in those cases,
 and the kernel with the system shell, AFAIK. So we have a way to get most
 things that could call the script to interpret it as Bourne/POSIX shell
 script on most systems. Then we just have to add a Bourne shell scriptlet
 that switches to mksh iff the current shell isn’t it (lksh, or something
 totally different). On Android, there is only ever one shell (or the
 toolkit installer better preserve mksh as mksh), so this doesn’t do
 anything (I hope – but did not test – that the kernel invokes the system
 shell correctly despite it not lying under <tt>/bin/sh</tt>) nor does
 it need to.</p>
<p class="boxhead">This leaves us with the following “shebang”:</p>
<div class="boxtext">
 <pre>
	:
	case ${KSH_VERSION-} in
	*MIRBSD\ KSH*) ;;
	*)	# re-run with The MirBSD Korn Shell, this is an mksh-specific script
		test "${ZSH_VERSION+set}" = set &amp;&amp; alias -g '${1+"$@"}'='"$@"'
		exec mksh "$0" ${1+"$@"}
		echo &gt;&amp;2 E: mksh re-exec failed, should not happen
		exit 127 ;;
	esac
 </pre>
</div><p class="boxfoot">The case argument not only does not need to,
 but actually should not be quoted; the expansion is a <tt>set -u</tt>
 guard; the entire scriptlet is <tt>set -e</tt> safe as well; comments
 and expansions are safe. <tt>exec</tt> shall not return, but if it
 does (GNU bash violates POSIX that way, for example), we use POSIX’
 appropriate errorlevel. zsh is funny with the Bourne shell’s way of
 using <tt>"$@"</tt> properly. But this should really be portable.
 The snippet is both too short and too obvious (“only way to do it”)
 to be protected by copyright law.</p>
<p>Thanks to <tt>carstenh</tt> and <tt>Ypnose</tt> for discussing things
 like this with us in <a href="@@RELPATH@@irc.htm">IRC</a>, sending in
 bugfixes (and changes we decline, with reason), etc. – it feels like we
 have a real community, not just consuments ☺</p>
----
Date: 07.01.2016 01:24
Author: tg@
Title: “git find” published; test, review, fix it please
Tag: debian fun mksh pcli tip

<p>I just published the first version of <tt>git find</tt> on <a
 href="https://github.com/mirabilos/git-find">gh/mirabilos/git-find</a>
 for easy collaboration. The repository deliberately only contains the
 script and the manual page so it can easily be merged into git.git with
 complete history later, should they accept it. <tt>git find</tt> is <a
 href="@@RELPATH@@MirOS-Licence.htm">MirOS licenced</a>. It does require
 a recent <a href="@@RELPATH@@mksh.htm">mksh</a> and some common utility
 extensions to deal with NUL-separated lines (<tt>sort -z</tt>, <tt>grep
 -z</tt>, <tt>git ls-tree -z</tt>); also, support for <tt>'\0'</tt> in
 tr(1) and a comm(1) that does not choke on embedded NULs in lines.</p>
<p class="boxhead">To install or uninstall it, run…</p>
<div class="boxtext"><pre>
	$ git clone git@github.com:mirabilos/git-find.git
	$ cd git-find
	$ sudo ln -sf $PWD/git-find /usr/lib/git-core/
	$ sudo cp git-find.1 /usr/local/share/man/man1/
	… hack …
	$ sudo rm /usr/lib/git-core/git-find \
	    /usr/local/share/man/man1/git-find.1
</pre></div><p class="boxfoot">… then you can call it as “git find”
 and look at the documentation with “git help find”, as is customary.</p>
<p>The idea behind this utility is to have a tool like “git grep” that
 acts on the list of files known to git (and not e.g. ignored files)
 to quickly search for, say, all PNG files in the repository (but not
 the generated ones). “git find” acts on the index for the HEAD, i.e.
 whatever commit is currently checked-out (unlike “git grep” which also
 knows about “git add”ed files; fix welcome) and then offers a filter
 syntax similar to find(1) to follow up: parenthesēs, <tt>!</tt> for
 negation, <tt>-a</tt> and <tt>-o</tt> for boolean are supported, as
 well as <tt>-name</tt>, <tt>-regex</tt> and <tt>-wholename</tt> and
 their case-insensitive variants, although regex uses grep(1) without
 (or, if the global option <tt>-E</tt> is given, with) <tt>-E</tt>,
 and the pattern matches use mksh(1)’s, which ignores the locale and
 doesn’t do <tt>[[:alpha:]]</tt> character classes yet. On the plus
 side, the output is guaranteed to be sorted; on the minus side, it
 is rather wastefully using temporary files (under <tt>$TMPDIR</tt>
 of course, so use of tmpfs is recommended). <tt>-print0</tt> is the
 only output option (<tt>-print</tt> being the default).</p>
<p>Another mode “forwards” the file list to the system <tt>find</tt>;
 since it doesn’t support DOS-style response files, this only works
 if the amount of files is smaller than the operating system’s limit;
 this mode supports the full range (except <tt>-maxdepth</tt>) of the
 system find(1) filters, e.g. <tt>-mmin -1</tt> and <tt>-ls</tt>, but
 it occurs filesystem access penalty for the entire tree and doesn’t
 sort the output, but can do <tt>-ls</tt> or even <tt>-exec</tt>.</p>
<p>The idea here is that it can collaboratively be improved, reviewed,
 fixed, etc. and then, should they agree, with the entire history, <a
 href="https://www.kernel.org/pub/software/scm/git/docs/howto/using-merge-subtree.html"
 >subtree-merge</a>d into <tt>git.git</tt> and shipped to the world.</p>
<p>Part of the development was sponsored by tarent solutions GmbH, the
 rest and the entire manual page were done in my vacation.</p>
----
