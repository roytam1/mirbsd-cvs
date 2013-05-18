RCSID: $MirOS: www/data/wlog-10.inc,v 1.81 2008/10/05 01:00:39 tg Exp $
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

<p>… as you could get it. This is because gecko2@ asked for some more cvs
 commit eMail “spam” ☺</p>
<p>While on the spam topic: do <strong>not</strong> send an eMail to one of
 the following addresses: <a href="mailto:junk@mirbsd.org">junk@mirbsd.org</a>,
 <a href="mailto:junk@66h.42h.de">junk@66h.42h.de</a>, or <a
 href="mailto:junk@mirbsd.de">junk@mirbsd.de</a>, or, again, <a
 href="mailto:junk@mirbsd.org">&lt;junk@mirbsd.org&gt;</a>, <a
 href="mailto:junk@66h.42h.de">&lt;junk@66h.42h.de&gt;</a>, or <a
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

<p>On an unrelated note, <a href="@@RELPATH@@mksh.htm">mksh</a> needs
 people running the current development version, to prevent mishaps like
 the one with the fullwidth characters causing wrong text output. To do
 that, use AnonCVS like this:<br /><tt>% env CVS_RSH=ssh cvs -qz3 -d
 anoncvs@anoncvs.mirbsd.org:/cvs co -PA mksh</tt><br />Then, as usual,
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
 href="http://www.mirbsd.org/MirOS/dist/mir/mksh/mksh-R35.cpio.gz">http://www.mirbsd.org/MirOS/dist/mir/mksh/mksh-R35.cpio.gz</a>.</p>
----
Date: 14.07.2008 00:00
Author: tg@
Title: Inclusion of the MirBSD Korn Shell

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

<h3><a href="@@RELPATH@@mksh.htm">mksh</a> – The iShell</h3>
<p style="margin-bottom:0px;">Try this:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;">
 <pre>
	$ cvs -d anoncvs@anoncvs.mirbsd.org:/cvs co -PA mksh
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
 </pre>
</div><p style="margin-top:0px;">Mach-O executable arm</p>
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
