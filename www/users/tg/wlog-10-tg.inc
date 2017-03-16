RCSID: $MirOS: www/users/tg/wlog-10-tg.inc,v 1.42 2017/03/08 21:00:32 tg Exp $
Date: 14.04.2014 19:22
Author: tg@
Title: Enough of IT…
Tag: geocache rant

<p>I’ve been only sleeping, cooking and geocaching this weekend.
 Rather productive. Better than being angry at idiots, slowpokes
 (StartCom and Mozilla in particular), etc.</p>
<p><a href="http://fish.mirbsd.org/wptg.htm#banners" style="border:0;"><img
 style="border:0;" alt="mirabilos’ Waypoints"
 src="@@RELPATH@@WPtg.png" /></a></p>
<p>Food was rather tasty, although I held back and put only ten
 pieces of garlic into it; gecko2 added some Pul Biber to his…</p>
----
Date: 04.05.2014 00:36
Author: tg@
Title: Maibaum für Ada
Tag: debian fun twitxr

<p>While taking the tram to our favourite Croatian restaurant,
 I spotted something dedicated to Ada. We’ll never know which
 one… the language, the famous programmer, or someone else. <a
 href="https://de.wikipedia.org/wiki/Maibrauchtum_(Rheinland)#Maibaum">A
 “<span xml:lang="de-DE-1901">Maibaum</span>”</a> (may pole, one of its
 many meanings). Click on
 the picture to get a slightly different one which has the text
 better legible.</p>
<p><a href="@@RELPATH@@pics/wlog/Ada-Maibaum.jpg"><img
 alt="Ada-Maibaum" src="@@RELPATH@@pics/wlog/Ada_Maibaum.jpg" /></a></p>
----
Date: 13.05.2014 16:25
Author: tg@
Title: Lügen haben lange Leitern
Tag: debian fun politics rant twitxr
Language: de-DE-1901

<p><a href="@@RELPATH@@pics/wlog/anti-nrw.jpg"><img
 style="float:right; margin-left:1em; margin-bottom:3px;"
 alt="Photo von Laternenmast mit Wahlplakaten, oben Pro NRW, unten…"
 src="@@RELPATH@@pics/wlog/anti_nrw.jpg" /></a></p>
<p>Endlich tut mal jemand was gegen <a
 href="https://de.wikipedia.org/wiki/B%C3%BCrgerbewegung_pro_NRW">die
 rechte Hetzpartei</a>! – Ein Arbeitskollege fragt, ob man die nicht
 einfach mit einem langen Heckenschneider abmachen kann… aber sie so
 lächerlich zu machen hat auch was ☺</p>
<p xml:lang="en">Finally, someone is doing something against <a
 href="https://en.wikipedia.org/wiki/Pro_NRW">this Nazi party</a>!
 A coworker wondered whether it’s legal to cut them off with a long
 tool, but making them ridiculous like this is also funny ☻</p>
<p xml:lang="en">(Explanation: the “Pro NRW” people put their campaign
 thingies (sorry, I don’t speak English well) up on lamp posts very high,
 because they are taken down by other citizens immediately otherwise,
 so there’s now people making fun of them for using long ladders (to
 put them up there, so the offended citizens need equally long ladders
 or tools with long arms) in leaning on the saying that lies have long
 legs ⇒ here: ladders.)</p>
<div style="clear:right; height:1px;"> </div>
----
Date: 15.05.2014 15:05
Author: tg@
Title: Debian packaging example: PHP5 webapp with dbconfig-common and Apache 2.2/2.4 support
Tag: debian snippet tip work

<p>I’m holding a Debian packaging workshop for our trainees at <a
 href="http://www.tarent.de/">work</a> tomorrow, and have prepared
 a sample package for a simple PHP web application (just a handful
 of files) with DB connection (PostgreSQL of course), automatic setup
 via <tt>dbconfig-common</tt>, and with support for both Apache 2.2
 (wheezy, precise) and Apache 2.4 (jessie/sid), configuration-wise.
 (It is possible to install this without Apache, just it does not
 configure the webserver then.) Schema updates on software updates
 are also tested (there is neither Flyway nor Liquibase – which are
 the tools we use at work for this, other than Roland Mas’ wonderful
 scripts for FusionForge – in Debian, but to my delight I discovered
 that dbconfig-common can also do this).</p>
<ul>
 <li><a href="https://evolvis.org/plugins/scmgit/cgi-bin/gitweb.cgi?p=shellsnippets/hello-php-world.git">VCS-Browser</a></li>
 <li><a href="https://evolvis.org/anonscm/git/shellsnippets/hello-php-world.git">VCS-git</a></li>
</ul>
<p>Comments, suggestions, flames, etc. welcome. I know that this
 should not be a native package, and will address this tomorrow,
 but I wanted something that serves as decent example for how to
 do this easily, Policy conformant and using modern techniques
 (even those <a href="https://launchpad.net/~dh7-haters">I dislike
 myself</a> – for the sake of simplicity).</p>
<p>Permission was granted by the business administration to reproduce
 this all under <a href="@@RELPATH@@MirOS-Licence.htm">a BSD-style
 licence</a>, so, enjoy sharing!</p>
<p>Thanks to Roland Mas, for making FusionForge such a nice project,
 and Arno Töll for some instant IRC help on the Apache side of this.</p>
<p>This is my first time using <tt>dbconfig-common</tt>, and now, I
 finally feel I know enough to finish the packaging of <a
 href="http://www.kivitendo.de/">Kivitendo</a> which I’ve <a
 href="http://anonscm.debian.org/gitweb/?p=collab-maint/kivitendo.git">started
 earlier</a>. Beta testers for <em>that</em> welcome, too.</p>
<p>(And next week or so, I’ll need this for a Maven thingy. I’ll
 probably opt out on the DB side, there, though. Never did anything
 with that, either, not being a Java™ guy. I guess something web
 to go with tomcat7… anyone got this already?)</p>
----
Date: 17.05.2014 10:05
Author: tg@
Title: Quotes of the day – SWB Engrish
Tag: fun

<p>Stadtwerke Bonn conduct track works on the third<br />
 weekend of May 23-25th on several sections of the<br />
 line 61. <b>The orbits</b> of lines 61, 62 and 65 <b>drive from</b><br />
 Friday 23 May to Sunday 25 May <b>not on their usual<br />
 line paths</b>. Due the track works a train replacement<br />
 service by busses will be established.</p>
<p>Please note: <b>The travel time</b> of the shuttle busses<br />
 <b>takes longer</b>. It is recommend to adjust the traveling<br />
 plan.</p>
<p>We apologise for any inconvenience!</p>
<p>(Emphasis mine. Inconvenience, such as almost <tt>C|N&gt;K</tt>…)</p>
----
Date: 21.05.2014 18:28
Author: tg@
Title: Friseure!
Tag: personal rant
Language: de-DE-1901

<p>Mein Friseur hat zugemacht. Jetzt versuche ich seit Wochen, einen
 neuen zu finden. Der sollte aufhaben, wenn ich von der Arbeit komme.
 Technisch beëinflußt suche ich zunächst im Netz… aber liebe Leute,
 ich will keine 20 € und mehr ausgeben und dafür beim Friseur Kaffee
 aus einer Saeco trinken (das mache ich auf Arbeit kostenlos), oder
 für 36 € das 40-Minuten-Wellness-Paket mit irgendwelchen abgedrehten
 Pflegen haben oder von Promi-Friseuren beackert werden.</p>
<p>Ich will einfach nur nen verdammten normalen sommerlichen Kurzhaarschnitt,
 für ein Dutzend Quakes, ggfs. ein paar mehr, gern auch mit Rasur.
 Und zwar abends so zwischen 18 und 19 Uhr, oder samstags am späten
 (lies: 14 Uhr) Vormittag, wenn ich halbwegs wach bin.<br />
 Ist das denn <em>so</em> schwer?</p>
<p>(Okay, die meisten haben vermutlich keine Webseite. Aber wie
 findet man die? Und die zwei mit einer Facebook- aber keiner
 Webseite kommen, habe ich extra von der Arbeit aus nachgesehen,
 auch nicht in Frage.)</p>
<p>&lt;/rant&gt;</p>
----
Date: 05.06.2014 08:42
Author: tg@
Title: Dear FSF, stop recommending Enigmail.
Tag: debian pcli rant security tip work

<p>Dear FSF, stop <a href="https://emailselfdefense.fsf.org/">recommending</a>
 Enigmail, please. It <a href="http://apebox.org/wordpress/rants/589/">is
 broken</a>, simple as that. Even if you <a
 href="news://news.gmane.org/53859C5C.1020306@debian.org">switch everything
 HTML-related off</a>, it still defaults to the latin9 (ISO-8859-15) encoding
 instead of UTF-8, and possibly some other nasties. Worse, it’s based upon
 obsolete Thunderbird/Icedove technology, which is dead since the release of
 Firefox® 17 and will only degrate over time.</p>
<p>Side note: I was asked recently how much entropy is used while generating
 a PGP key using GnuPG on Windows®, after having done the same for <a
 href="https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=742145">OpenSSL on
 Debian</a> (and possibly almost all other OSes). I had to try to find out
 which was the actual code (GnuPG 2 with libgcrypt, it turns out), and it
 was <em>not pretty</em>. (You are hereby adviced to create a 600-byte file
 <tt>${GNUPGHOME:-~/.gnupg}/random_seed</tt> from a good source before even
 attempting to use GnuPG 2 for the first time. OK, you can run <tt>gpg -k</tt>
 once, to create the GNUPGHOME directory from a skeleton.)</p>
----
Date: 09.10.2014 00:50
Author: tg@
Title: Debian is a bit like a school class…
Tag: personal rant

<p>… which has never quite taken you as-is, bordering bullying maybe,
 and has now made up rules to include some new kids, using these as
 excuse to bully you around even more. You stay the outsider, having
 tried to struggle along for a while, except of course when they want
 to copy off your homework. Or, as happened to me, during a Maths test,
 with carbon paper. Then you're thanked for a short while, and after
 some time, you're alone again.</p>
<p>… except, it all happened in the city, not in the internet, which
 happily multiplies negative voices and likes to take things out of
 context, especially if part of the context was in private mail or
 other threads or long buried (closed as ignored/WONTFIX) bugreports.</p>
<p>Of course, some sorts of misbehaviour are okay, as long as those
 who do toe the party line ‒ and aren't outcast, to start with.</p>
<p>I still pride myself as independent thinker and <em>like</em> to
 play the devil's advocate rule (heh, double entendree, being a BSD
 person). Critically looking at something new has led to lots of <a
 href="@@RELPATH@@wtf.cgi?tys">tys</a> moments. If people listened
 to my criticism in the first place, effort could have been saved.</p>
<p>It seems to be an anglo-american-australian thing, putting political
 correctness in expressions over real niceness. And the opinion about
 cursing, in general. And this <a href="@@RELPATH@@wtf.cgi?sjw">SJW</a>
 thing. You know, a good friend is someone who you can be silent with,
 while being happy together. One whom you can insult, be it in jest or
 in anger, and still stay friends.</p>
<p>And look at those newcomers! Shiny, with makeup that promises faster
 boot times (eh? I fail to see how this is relevant in a Unix…) and
 all that. But these superficial people, always jumping from one thing
 (HAL, consolekit) to the next, giving up their own projects which they
 forced upon others the minute before ‒ no consistency.</p>
<p>I'm too old for this shit. Ignore my rambling. Couldn't sleep.</p>
----
Date: 19.11.2014 12:44
Author: tg@
Title: Debian init system freedom of choice GR worst possible outcome
Tag: debian rant work

<p><a href="http://blog.venthur.de/index.php/2014/11/general-resolution-is-not-required/">Apparently</a>
 (the actual results have not yet been published by the Secretary),
 the GR is over, and the <strong>worst possible option</strong> has
 won. This is an <strong>absolutely ambiguous result</strong>, while
 at the same time <strong>sending a clear signal that Debian is not
 to be trusted</strong> wrt. investing anything into it, right now.</p>
<p>Why is this? Simply: “GR not required” means that “whatever people
 do is probably right”. Besides this, we have one statement from the
 CTTE (“systemd is default init system for jessie. Period.”) and
 nothing else. This means that runit, or upstart, or file-rc, or
 uselessd, can be the default init system for zurg^H^H^H^Hstretch,
 or even the only one. It also means that the vast majority of Debian
 Developers are sheeple, neither clearly voting to preserve freedom
 of choice between init systems for its users, nor clearly voting to
 unambiguously support systemd and progress over compatibility and
 choice, nor clearly stating that systemd is important but supporting
 other init systems is still recommended. (I’ll not go into detail on
 how the proposer of the apparently winning choice recommends others
 to ignore ftpmaster constraints and licences, and even suggests to
 run a GR to soften up the DFSG interpretation.) I’d have voted this
 as “no, absolutely not” if it was possible to do so more strongly.</p>
<p>Judging from the statistics, the only thing I voted above NOTA/FD
 is the one least accepted by DDs, although the only other proposal
 I considered is the first-rated of them: support for other init
 systems is recommended but not required. What made me vote it below
 NOTA/FD was: “The Debian Project makes no statement at this time on
 sysvinit support beyond the jessie release.” This sentence made even
 this proposal unbearable, unacceptable, for people wanting to invest
 (time, money, etc.) into Debian.</p>
<p><strong>Update:</strong> Formal result announced. So 358 out of 483
 voting DDs decided to be sheeple (if I understand the eMail correctly).
 We had 1006 DDs with voting rights, which is a bit ashaming as well.
 That’s 48.01% only. I wonder what’s worse.</p>
<p>This opens up a very hard problem: I’m absolutely stunned by this
 and wondering what to do now. While there is no real alternative to
 Debian at $dayjob I can always create customised packages in <a
 href="http://users.unixforge.de/~tglaser/debs/debidx.htm">my own
 APT repository</a>, and – while it was great when those were <a
 href="http://metadata.ftp-master.debian.org/changelogs/main/j/jupp/unstable_changelog">eventually</a>
 (3.1.17-1) accepted <a
 href="https://packages.qa.debian.org/c/cvs/news/20110507T011726Z.html">into
 Debian</a>, even <a
 href="https://packages.qa.debian.org/p/pax/news/20120212T030643Z.html">replacing</a>
 the previous packages completely – it is simpler and quicker to not do so. <a
 href="http://article.gmane.org/gmane.org.wikimedia.mediawiki.distributors/56">While
 $dayjob benefits</a> from having packages I work on inside Debian itself,
 even though I cannot always test all scenarios Debian users would need, <a
 href="https://packages.qa.debian.org/m/mediawiki/news/20141007T191941Z.html">some
 work reduction</a> due to… reactions… already led to Debian <a
 href="http://lists.alioth.debian.org/pipermail/pkg-mediawiki-devel/2014-November/003081.html">losing
 out on Mediawiki for jessie</a> and some additional <a
 href="https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=764400">suffering</a>.
 With my own package repository, I can – modulo installing/debootstrap – serve
 my needs for $dayjob much quicker, easily, etc. and only miss out on <a
 href="https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=763842">absolutely
 delightful user feedback</a>. But then, others could always package software
 I’m upstream of for Debian. Or, if I do <em>not</em> leave the project,
 continue doing so via QA uploads.</p>
<p>I’m also disappointed because I have invested quite some effort into
 trying to make Debian better (my idea to join as DD was “if I’ve got to
 use it, it better be damn good!”), into packaging software and convincing
 people at work that developing software as Debian packages instead of (or
 not) thinking of packaging later was good. I’ve converted our versions of
 FusionForge and d-push to Debian packages, and it works pretty damn well.
 Sometimes it needs backports of my own, but that’s the corportate world,
 and no problem to an experienced DD. (I just feel bad we ($orkplace) lost
 some people, an FTP master along them, before this really gained traction.)</p>
<p>I’d convert to OpenBSD because, despite MirBSD’s history with them,
 they’re the only technically sound alternative, but apparently tedu (whom
 I respect technically, and who used to offer good advice to even me when
 asked, and who I think wouldn’t choose systemd himself) still (allying
 with the systemd “side” (I’m not against people being able to choose
 systemd, for the record, I just don’t want to be forced into it myself!))
 has some sort of grudge against me. Plus, it’d be hard to get customers
 to follow. So, no alternative right now. But I’m used to managing my own
 forks of software; I’m doomed to basically hack and fix anything I use
 (I recently got someone who owns a licence to an old-enough Visual Studio
 version to transfer that to me, so I can hack on the Windows Mobile 6
 version of Cachebox, to fix bugs in one of the geocaching applications
 I use. Now I “just” need to learn C# and the .NET Compact Framework.
 So I’m also used to some amount of pain.)</p>
<p>I’m still unresolved wrt. the attitude I should show the Debian project
 now. I had decided to just continue to live on, and work on the things I
 need done, but that was before this GR non-result. I absolutely cannot
 recommend anyone to “invest” into Debian (without sounding hypocriet), but
 I cannot recommend anything else <em>either</em>. I cannot justify leaving
 but don’t know if I want to stay. I think I should sleep over it.</p>
<p>One thing I promised, and thus will do, is to organise a meeting of the
 Debian/m68k people soonish. But then, major and important and powerful
 forces inside Debian still insist that Debian-Ports are not part of it…
 [Update: yes, DSA is moving it closer, thanks for that by the way, but
 that doesn’t mean anything to certain maintainers or the Release Team,
 although, the latter is actually understandable and probably sensible.]
 yet, <strong>all forks of Debian now suffer from the systemd adoption in
 it</strong> instead of having a freedom-of-choice upstream. I’ve said, and
 <strong>I still feel that systemd adoption should have done in a Debian
 downstream / (pure?) blend</strong>, and maybe (parts of) GNOME removed
 from Debian itself for it. (Adding cgroups support to the m68k kernel to
 support systemd was done. I adviced against it, on the grounds of memory
 and code size. But no downstream can remove it now.)</p><!-- RSS stop -->
<p>On a closing note: an Ewok told me I should not be surprised because
 of my communication style on the mailing lists. I just got private mails
 telling me that, indeed, I’ve been more civilised recently, plus I’ve
 not started out as aggressively as it became in the end of the heated
 systemd debate (with this GR result, I precisely lost what I had feared),
 plus I’ve hung on Usenet for too long… and I’m sometimes terse when I
 don’t want to repeat the, for me, same topic once <em>again</em> (I’ve
 usually looked at the things before and decided they’re just another
 hype, and know from experience to avoid them). So I feel this should
 not be held against me. Listen to advice, please. (I’m also somewhat
 shocked by certain people asserting systemd is “unavoidable”, now.)</p>
----
Date: 25.11.2014 17:00
Author: tg@
Title: d-i preseeding is not the answer
Tag: debian rant work

<p><a href="http://www.vitavonni.de/blog/201411/2014112501-installing-debian-with-sysvinit.html">This
 post</a> details what the d-i team currently shows as the only way.</p>
<p>It has several shortcomings and one missing documentation part.</p>
<p>Shortcoming: <tt>--purge</tt> is missing from the <tt>apt-get</tt>
 invocation. This leaves packages in “rc” state (requiring a manual
 <tt>dpkg --purge</tt> to completely remove them later, as they are
 then invisible to apt).</p>
<p>Worse shortcoming: this still leaves all dependencies pulled in by
 systemd around on the system, because packages installed by debootstrap
 are not eligible for “apt-get --purge autoremove”. Additionally, it does
 not influence debootstrap’s (nōn-existent, see #557322, #668001, #768062)
 dependency resolver, leading to possibly pessimistic package selections.</p>
<p class="boxhead">Missing: you can just hit Alt-F2 and enter the command…</p>
<div class="boxtext">
 <pre>
	in-target apt-get --purge -y install sysvinit-core
 </pre>
</div><p class="boxfoot">… there, no need to preseed. But this does not
 eliminate the aforementioned shortcomings, of course.</p>
----
Date: 29.11.2014 15:11
Author: tg@
Title: RNG for MirBSD and subprojects
Tag: plan

<p>Feel free to ignore those semi-unsorted ramblings of mine, they are
 unfinished, not binding, notes of plans that may come if I ever learn
 影分身の術 (Kage Bunshin no Jutsu) or bilocality…</p><!-- RSS stop -->
<p>We currently have arc4random(9) in the kernel and arc4random(3) in
 userspace. We also have the urandom(4) stuff, but nobody should use
 them really. OpenBSD simplified theirs, but lost functionality like
 arc4random_addrandom(3) during that. I complicated ours, to get e.g.
 arc4random_pushb_fast(3), and for using userspace as additional pools,
 but that grew complex too, and few applications really add to their
 state other than using it anyway.</p>
<p>My idea thus far is to begin with those applications. That would
 be mksh(1) and ntpd(8) only, AFAICT. On the basis of the recently <a
 href="http://article.gmane.org/gmane.os.miros.mksh/482"><span
 style="font-variant:small-caps">Spritz</span></a>, an aRC4 successor
 with great sponge properties, I plan on creating <tt>s4random</tt>,
 which could serve their specific needs: an output state <span
 style="font-variant:small-caps">Spritz</span> (like arc4random has);
 an input <span style="font-variant:small-caps">Spritz</span> (which
 corresponds to the arc4random_roundhash) tweaked to have, every time
 <span style="font-variant:small-caps">Shuffle()</span> is called by
 the absorption functions, four bytes sent to a BAFH state from <span
 style="font-variant:small-caps">Drip()</span>; that 32-bit state is
 then used to randomly drop from the output state (in addition to a
 value from the output state itself like arc4random uses) for faster
 feedback (think state recovery attacks). The output state can then
 be seeded less often but in larger blocks, taking from the input
 state as well as arc4random(3) or sysctl(3) <tt>KERN_ARND</tt> or
 OpenBSD getentropy() or Linux getrandom() or <tt>/dev/urandom</tt>,
 with the usual pushback. It could also need only 16 bytes instead
 of 128/256 bytes from the kernel on such calls (possibly lowering
 the a4s_count equivalent for the first two trips). It would also
 need to work on lesser operating systems, so it can probably have
 a function to determine seed status (2 = third trip, kernel entropy;
 1 = first or second trip, or Win32 CryptGenRandom; 0 = untrusted).
 Also consider skipping initialisation by hardcoding one at compile
 time, facilitated through Mirtoconf v2. (Also, reducing the maximum
 <span style="font-variant:small-caps">Squeeze()</span> parameter to
 64 before random dropping engages, instead of 256, makes sense. The
 BAFH state also needs feedback from the output state…)</p>
<p>Then, I could simplify MirBSD libc arc4random(3) as all other
 applications than those mentioned above (and maybe libcrypto, but
 that’s a special case anyway) don’t need this sort of fast feedback
 loop. I’ve not yet planned that part out. – Finally, the kernel may
 or may not adopt <span style="font-variant:small-caps">Spritz</span>
 but I’ve got ideas wrt. that, faster feedback loops, less overhead
 for interrupt handlers, etc. as well. This can wait a bit, as <span
 style="font-variant:small-caps">Spritz</span> is still very new, so
 I’d prefer to not lower the security level accidentally, but it can
 be prototyped for something eventually ending up in ntpd(8) where it
 has low impact, and <a href="@@RELPATH@@mksh.htm">mksh</a>, where the
 MirJSON and Mirkev code will need it.</p>
<p>OpenSSL’s libcrypto is another case. Just using arc4random(3) now
 has effectively reduced its state size from about 8184 bit to about
 1700 bit of aRC4 state while a Spritz state has about 1476‒1604 bit.
 Of course, it reads from the kernel, which doesn’t offer more anyway,
 and people say about security levels, but there’s still always EGD
 and, more importantly, <tt>~/.rnd</tt> (or <tt>RANDFILE</tt> to be
 exact). So, an upscaling solution is needed, too, but I can construct
 one, similar to how arc4random_roundhash is comprised of 32 32-bit
 BAFH states with appropriate (but slow) mixing. But that’s specific
 to MirBSD anyway, and can take time.</p>
<p>Meh. Reminds me, I probably should add getentropy() before upgrading
 OpenSSH to a version doing the sandboxing. And let arc4random(3) use
 the new <tt>MAP_INHERIT_ZERO</tt> stuff; at least minherit(2) throws
 <tt>EINVAL</tt> as safe fallback but it still requires updating the
 kernel first. But then it has been there for months already.</p>
----
Date: 30.11.2014 20:06
Author: gecko2@
Title: Wegeskreuzungen, Pöller und Erkennbarkeit
Tag: geocache
Language: de-DE-1901

<p>Wußtest Du schon, daß eine Abzweigung (eine andere Straße oder sogar
 auch nur ein Feldweg) dadurch markiert wird, daß sie zwischen Pöllern
 mit orangefarbenen statt weißen Reflektoren steht?</p>
<p><i xml:lang="en">(tg@ continuing…)</i> Nein, wußte ich nicht, aber
 jetzt wo Du’s sagst… danke! Hilfreich! Daß die Pöller links wie ein
 Doppelpunkt und rechts wie ein senkrechter Strich geformt sind wußte
 ich immerhin schon. Ja, kann mir vorstellen, daß es bei der Navigation
 im Schnee hilft. Nein, in der Fahrschule hörte ich dies, und so manches
 anderes, nicht… komme mir im Nachhinein betrogen vor…</p>
----
Date: 03.12.2014 02:05
Author: tg@
Title: Munzee-Plazierungen
Tag: geocache
Language: de-DE-1901

<p>Wenn ich meine Geocaches so „genau“ ausmessen würde wie die Munzees
 hier in der Ecke sind, würden mir wütende Finder die Bude einrennen…</p>
<p>Und wieso überhaupt kann ich in der Ähpp ein DNF als Logtyp auswählen,
 aber beim Sync sagt er dann, ginge nicht? (NM geht. Note sollte auch.)</p>
<p>Alles in allem: besser als Ingress (nicht schwer…), aber ähnlich
 stromfressend; nerviger als Geocaching (die Ähpp ist auch furchtbar lahm).
 Und: <span xml:lang="en">it’s all about the numbers</span>, aber teilt
 sich bei mir nunmal mit anderen GPS-Spielen die Statistik…</p>
----
Date: 12.12.2014 23:56
Author: tg@
Title: WTF is Jessie; PA4 paper size
Tag: debian pcli rant

<p><a href="https://www.mirbsd.org/~tg/Debs/debidx.htm">My personal APT
 repository</a> now has a <tt>jessie</tt> suite – currently just a clone
 of the <tt>sid</tt> suite, but so, people can get on the correct “upgrade
 channel” already.</p>
<p>Besides that, the usual small updates to my metapackages, bugfixes, etc.
 – You might have noticed that it’s now on a (hopefully permanent) location.
 I’ve put a donated eee-pc from my father to good use and am now running a
 Debian system at home. (Fun, as I’m emeritus now, officially, and haven’t
 had one during my time as active uploading DD.) I’ve created a couple of
 cowbuilder chroots (<tt>pbuilderrc</tt> to achieve that included in the
 repo) and can build packages, but for i386 only (amd64 is still done on
 the x32 desktop at work), but, more importantly, I can build, sign and
 publish the repo, so it may grow. (popcon data is interesting. More than
 double the amount of machines I have installed that stuff on.)</p>
<p><strong>Update:</strong> I’ve started writing a <tt>NEWS</tt> file and
 cobbled together an <a href="https://www.mirbsd.org/~tg/Debs/NEWS.rss">RSS
 2.0 feed</a> from that… still plaintext content, but at least signalling
 in feedreaders upon updates.</p>
<hr />
<p>Installing gimp and inkscape, I’m asked for a default paper size by
 libpaper1. <a href="@@RELPATH@@wtf.cgi?pa4">PA4</a> is still not an
 option, I wonder why. I also haven’t managed to get MirPorts GNU groff
 and Artifex Ghostscript to use that paper size, so the various PDF
 manpages I produce are still using <a href="@@RELPATH@@wtf.cgi?a4">DIN
 ISO A4</a>, rendering e.g. Mexicans unable to print them. Help welcome.</p>
<!-- RSS stop --><hr />
<p>Note, for <tt>arngc</tt>, you need a server component (MirBSD-current,
 of course; we’re rolling release nowadays). Config included, but I’m
 willing to open my firewall to people I know, provided they won’t use
 “too much” traffic (running a couple of arngc instances is fine, according
 to what I estimated).</p>
<p>A largish article about how to use some other packages in the repo,
 such as <tt>dash-mksh</tt>, is yet to come. In the meantime, I wrote
 a bit more in <tt>README.Debian</tt> in <tt>mirabilos-support</tt>.</p>
----
Date: 07.04.2015 22:02
Author: tg@
Title: exciting news, or so
Tag: debian event fun geocache mksh news personal pkgsrc plan rant security work

<p>I implemented <tt>&lt;?</tt> support (including <tt>&lt;?php</tt>…)
 script embedding support for <tt>*.inc</tt> in MirWebseite today; the
 specific syntax was explicitely requested by <a
 href="https://www.teckids.org/people.htm#nik">Natureshadow</a>. Ugh.</p>
<p>My own hacking activities are progressing, even if slowly. I do some
 other interesting, funny, social, beneficial, etc. stuff in between, though.
 I’ll even have to get some of my DD buddies to sponsor me some QA uploads
 of packages I formerly maintained, whereever changes are queued up… such as
 better old-format repo compatibility in cvs(GNU) ☺ Though some of the stuff
 I do at work is currently done only there… sorry.</p>
<p>Also: prepare to be fully enlightened about just <a
 href="https://blog.abevoelker.com/why-i-dont-use-docker-much-anymore/">what
 evil</a> (nice picture) <a href="http://iops.io/blog/docker-hype/">Docker</a>
 is. I especially liked the comparison of containers to a herd of cattle,
 mere numbers, replaceable, whereas VMs are cats, each with their individual
 name, lovely petted each day, etc.</p>
<p>ObHint: Some may have noticed I do have a Twitter account now. I do not
 really use it much. I got it because I wanted to rant at someone who only
 gave Twitter as means to contact them (a European company running a lottery
 for USA citizens only). But I found one nice thing: @HourlyCats (though
 @FacesPics and @BahnAnsagen are funny too, and the Postillon anyway).
 The internet is there for cat content, anyway.<br />Ahem. Do not contact
 me there, use <a href="@@RELPATH@@irc.htm">IRC, more specifically, the
 Freenode network, and possibly <tt>memoserv</tt> to <tt>mirabilos</tt></a>
 instead, I can’t fit things into 140 chars, that’s just ridiculous. Also,
 don’t follow me. It may contain rants, it’s NSFW, and I’m not censoring
 there. As I said: I do not use it. So should you. (But kudos for having a
 mostly functional “fallback” site (the “mobile” one), which even works in
 PocketIE (Windows Mobile) and Opera 9, though not so much lynx(1)…)</p>
<p>odc (from <tt>#!/bin/mksh</tt> on IRC) is hacking support to use <a
 href="@@RELPATH@@mksh.htm">mksh</a> instead of GNU bash for bootstrapping
 pkgsrc® (e.g. on Solaris). Nice! Good luck!</p>
<p>… à propos mksh(1), dear Debian <tt>armel</tt> and <tt>armhf</tt> buildd
 maintainer colleagues, pretty please with strawberries and chocolate ice
 on top (I just had that on waffles at my favourite ice salon, so I may be
 biased), do like s390x and update your chroots and wanna-build give-back <a
 href="https://buildd.debian.org/status/package.php?p=mksh">mksh</a>, as we
 requested, so the privacy fix makes it into jessie. Thanks in advance!</p>
<p>Oh, and Y_Plentyn and I both have been putting more and updated packages into
 <a href="http://www.mirbsd.org/~tg/Debs/debidx.htm">my APT repository</a>.
 XTaran held a talk at CLT 2015 mentioning it… maybe I should write up some
 docs about how to use it for which purposes (e.g. how to avoid systemd but
 not get the other packages from it, or how to use it with systemd (trivial
 but has to be stated, it’s freedom of choice after all), etc.)?</p>
<p>Besides decent fanfiction (the stories in the Uzumaki Naruto universe
 seem, on average, to be much longer than those in the Harry Potter one), the
 weather is becoming good, so I’ve already been enjoying going out for some
 geocaching and will have the bike fixed at the shop RSN (it suffers a bit
 each winter, as it stands outside, since our basement is mouldy, which is
 worse than a bit of rust IMHO) to get more activity in. Also planning to
 head to the GPS Maze in Mainz and, besides what time FrOSCon (including
 preparation) allows, heading to DebConf for a while.</p>
<p><a href="http://fish.mirbsd.org/wptg.htm#banners" style="border:0;"><img
 style="border:0;" alt="mirabilos’ Waypoints"
 src="@@RELPATH@@WPtg.png" /></a></p><!-- RSS stop -->
<p>… to my shame I must admit I fucked up, and we <em>still</em> do not have
 support in libssl for SHA2-signed X.509 certificates. Also, StartSSL fucked
 up, so currently https for <tt>www.mirbsd.org</tt> is toast.</p>
<p>Also more on the rant side, services offered by web-based platforms, be
 they web (e.g. Groundspeak’s GC.COM) or not (Googlemail, which $orkplace
 switched to against my express veto some time ago) are getting worse and
 worse over time. I had hoped they realise that and improve, especially
 when seeing small signs (such as GC.COM pages shrinking to 20% of the
 formerly served bloat) but… no.</p>
----
Date: 18.04.2015 22:12
Author: tg@
Title: Pannekōche
Tag: food fun tip twitxr
Language: de-DE-1901

<p>Dies ist ein Rezept für polnische <span
 xml:lang="de-PL">Hefepfannkuchen</span> (<span
 xml:lang="pl">Racuchy drożdżowe</span>) mit Äpfeln (<span
 xml:lang="pl">z jabłkami</span>). Bei uns zu Hause gab es
 allerdings auch immer diese Pfannkuchen, nur mit Backpulver
 statt Hefe. Hefe ist allerdings besser. Das, was man sonst
 in Deutschland (außer Berlin, da heißen Berliner so, obschon
 die nicht in der Pfanne zubereitet werden) als Pfannkuchen
 (oder Eier(pfann)kuchen) kennt heißt bei uns <span
 xml:lang="fr">Crêpe</span>s (oder Eierkuchen). (Natureshadow
 und ich haben und jetzt drauf geëinigt, daß der Begriff
 „Pfannkuchen“ zu überladen ist, und zwischen Pannekōche (wie
 diese hier, nur mit Backpulver), Hefepfannkuchen (diese hier),
 Eierkuchen (pfannengroß, ½cm dick, mit Zeug eingebacken),
 Crêpes (beinahe selber Teig wie Eierkuchen, pfannengroß,
 deutlich dünner, um Zeug gewickelt) und Berlinern zu
 unterscheiden.<br />
 Die Hefepfannkuchen werden etwas mehr als handtellergroß,
 sind wunderbar luftig und prall und weich in der Mitte.</p>
<p><a href="@@RELPATH@@pics/wlog/Pfannkuchen.JPG"><img
 src="@@RELPATH@@pics/wlog/Pfannkuchen.jpg"
 alt="Pfannkuchen • Pannekōche • Hefepfannkuchen" /></a></p>
<p>Man kann die nicht nur als Apfelpfannkuchen zubereiten,
 sondern sie schmecken auch mit Erdbeeren total lecker, was
 allerdings recht matschig ist. Blaubeeren oder Pfirsische
 bieten sich auch an.</p>
<p>Die Mengenangaben sind für eine Standardfamilie gedacht;
 auf Arbeit doppeln wir alles, um die halbe Firma satt zu
 kriegen, und beim Firmenfest haben wir alles vervierfacht;
 das Rezept skaliert linear sehr gut.</p>
<p>Zutaten:</p><ul>
 <li>1 Pfund Weizenmehl (½ kg)</li>
 <li>1 Prise Salz</li>
 <li>50g frische Hefe</li>
 <li>3 Eßlöffel Zucker</li>
 <li>1½ Tassen Milch auf Zimmertemperatur(!)</li>
 <li>1 Ei</li>
 <li>3–4 Äpfel (am besten „Topaz“)</li>
</ul>
<p>Zubereitung: Das Mehl in eine große(!) Schüssel geben (der
 Teig steigt enorm hoch), das Salz hinzumischen. In die Mitte
 eine kleine Kuhle machen und dort die Hefe hineingeben und
 mit dem Zucker überhäufen, danach mit einer halben Tasse Milch
 übergießen und eine Viertelstunde gehen lassen. Dann das Ei
 und eine ganze Tasse Milch zugeben, kneten und zugedeckt etwa
 ein bis zwei Stunden gehen lassen.</p>
<p>Die Äpfel schälen, vierteln und in dünne Scheiben (etwa 2–3
 mm dick) schneiden. (Für 16 Äpfel muß man hier über eine Stunde
 Arbeitszeit einkalkulieren!) Diese nach dem Ziehen dem Teig
 zugeben und nochmals durchmischen und eine weitere Stunde (im
 polnischsprachigen Rezept stand 15–20 Minuten, aber wir gehen
 hier von Erfahrungswerten von Paweł und mir auf Arbeit aus)
 zugedeckt gehen lassen.</p>
<p>In einer Pfanne (bei doppelter oder gar vierfacher Menge
 besser in drei Pfannen zu zweit gleichzeitig) Öl mit einem
 Klecks Butter heißwerden lassen und dann mit einem großen
 Eßlöffel oder, besser, einem Salatbestecklöffel, drei bis
 vier Kleckse des Teigs (separat) in die Pfanne geben; nach
 kurzer Zeit (wenn der Boden und die Ränder schon etwas fest
 sind) mit einem Pfannenwender umdrehen und leicht obendrauf
 drücken, dann braten lassen und noch 3–4 Mal wenden, bis sie
 auf beiden Seiten goldbraun (oft auch etwas mehr als das…)
 und in der Mitte durch sind, dann auf einen Teller geben,
 der mit zwei Lagen Zewa ausgelegt wurde, um das überschüssige
 Fett aufzusaugen. Dann die nächsten Pfannkuchen machen und
 auf den Teller (oder einen neuen) stapeln. Zielgröße ist
 etwas mehr als handtellergroß und mehrere Zentimeter dick.</p>
<p>Heiß servieren. Kann man so (sind mir süß genug) oder mit
 Puderzucker bestreut (mag Paweł lieber) oder mit Marmelade
 essen. (Wenn man die vierfache Menge für die ganze Firma
 macht sollte man bereits während des Bratens ab und zu selber
 einen essen, weil man sonst nix mehr bekommt, weil das so
 lecker riecht, daß die Kollegen einen belagern…)</p>
<p>Update: Photo. Diesmal mit Vollkornmehl – eher mehr Milch
 nehmen hierbei, sonst fallen die Äpfel raus. Stevia geht auch,
 aber ein bißchen Zucker muß zum Gären sein.</p>
----
Date: 28.04.2015 20:54
Author: tg@
Title: さくら – Kirschblüte
Tag: fun twitxr

<p>I took some photos of the cherry blossoms fading today.
 As usual, small versions (about five à 100K) inline,
 linking to bigger versions (over 1 MiB each).</p>
<p><a href="http://mirsolutions.de/pub/sakura-1.jpg"><img
 alt="桜一" src="http://mirsolutions.de/pub/sakura_1.jpg" /></a></p>
<p><a href="http://mirsolutions.de/pub/sakura-2.jpg"><img
 alt="桜二" src="http://mirsolutions.de/pub/sakura_2.jpg" /></a></p>
<p><a href="http://mirsolutions.de/pub/sakura-3.jpg"><img
 alt="桜三" src="http://mirsolutions.de/pub/sakura_3.jpg" /></a></p>
<p><a href="http://mirsolutions.de/pub/sakura-4.jpg"><img
 alt="桜四" src="http://mirsolutions.de/pub/sakura_4.jpg" /></a></p>
<p><a href="http://mirsolutions.de/pub/sakura-5.jpg"><img
 alt="桜五" src="http://mirsolutions.de/pub/sakura_5.jpg" /></a></p>
<p>They are published under the terms and conditions of <a
 href="@@RELPATH@@MirOS-Licence.htm">The MirOS Licence</a>. Enjoy.</p>
<p>(I am aware that I missed the <span xml:lang="de">Kirschblütenfest</span>.
 This is a deliberate shot, well five, of the blossoms waning. There is <a
 href="http://coord.info/GLH9GE47">another shot</a> of cherry and apple trees
 in fuller bloom, though I did not take it and thus cannot licence it.)</p>
<p>Update: <a href="@@RELPATH@@permalinks/wlog-10-tg_e20151027-tg.htm">follow-up
 post</a> during Autumn.</p>
----
ID: evo-3
Date: 01.03.2010 15:21:07
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: EvolvisForge blog created
Tag: work

<p>It took us a while, but we’ll be participating at Plänet Forge soon as well. We, that is the Evolvis team at tarent GmbH:</p>
<ul>
<li>Thorsten Glaser (that’s me), a sysadmin at tarent and an Evolvis developer</li>
<li>Sven Frommeyer, an apprentice sysadmin at tarent</li>
<li>Stefan Walenda, our project manager</li>
<li>… and potentially others</li>
</ul>

<p>To clean up the nomenclature…</p>
<ul>
<li>Evolvis is the platform consisting of EvolvisForge and others, such as a Continuum or Hudson build server, an Alfresco DMS, a MediaWiki, …</li>
<li>EvolvisForge shall be the name of the customised installation (not fork) of FusionForge (formerly gforge-*.deb) that is used by Evolvis</li>
<li>evolvis.org is the public platform where tarent GmbH is presenting their open-sourced projects</li>
<li>There are other Evolvis installations at *.tarent.de domains, which are private.</li>
</ul>

<p>EvolvisForge customisations mostly consist of: take a stable FusionForge version plus bugfixes, sometimes backports (such as the FF 5.0 MediaWiki integration), change some defaults, and add Evolvis branding such as our theme. Also, some integration with the other Evolvis components, Univention/LDAP, etc.</p>

<p>This is a welcoming posting, so I better keep it short. We’ve been in Issy-les-Moulineaux (I hope I spelt that correctly) breaking up the French cabal, but they’re all nice people. Let’s try and improve all the forges!</p>
----
ID: evo-5
Date: 23.03.2010 17:02:09
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Just deployed evolvisforge 4.8.3+evolvis2
Tag: work

<p>tl;dr: EvolvisForge 4.8.3+evolvis2 deployed, almost all systems converted; FusionForge 5.0 coming Really Soon Now, faster if YOU help!</p><!-- RSS stop -->

<p><em>I’m happy.</em> I just was able to deploy a new version with many improvements on almost all of our systems (save the two which are not yet on 4.8 but stuck on 4.5 codebase).</p>

<p>For example, Roland has provided code to set the roles’ default permissions in a new forum, tasks or tracker subproject to some (sane) default value, instead of Read – now that they’re suddenly honoured, the bug (of them not being set to e.g. Tech) surprised many people.</p>

<p>I’ve written a CAPTCHA for user self-registration, in the hope of fooling automated login bots to fight spam accounts like we see at evolvis.org quite often these days (maybe spammers have special bot codes for *forge?).</p>

<p>The automated creation of ~user/.forward to enable mail forwarding for «user»@«forge» the same way «user»@users.«forge» is already handled now also works well. Other nifty things include bug fixes and more features in our theme (which should not be considered public) and the mediawiki plugin (allowing better control over importing, editing the Sidebar, logos, etc) and better XHTML/CSS compliance and browser compatibility.</p>

<p>Admins will love this: one can now set the password of any user if one is a Site Admin! (Before, this involved quite some database fiddling after calling <a href="http://www.mirbsd.org/man1/md5">md5(1)</a> and <a href="http://www.mirbsd.org/man1/encrypt">encrypt(1)</a> manually.)</p>

<p>The only sad things I see are that we cannot yet upgrade all instances we run to gforge-plugin-mediawiki, so they keep running the old-style separate wikis, which run on the same database though, preventing it from being upgraded from PostgreSQL 8.1 to 8.3 (due to the age of the mediawiki engine being used), and that our internal forge and the public one, evolvis.org, cannot yet be upgraded (especially as I’ll be on vacation RSN).</p>

<p>Still, we hope our cow-orkers enjoy the new release.</p>

<p>On the other track, we’re already running towards a stable 5.0 release, which will rock. One of my colleagues is helping with translating the strings into German upstream, and the branch is created; the code is being stabilised now and short of a release (also, thanks to the speedy help of the Debian FTP masters, with a detailed and correct debian/copyright file and a DFSG free distfile). Some tarent/evolvis extensions have found their way in there already; FusionForge 5.1 will have more, we guess.</p>

<p>Keep up the great work, FusionForge people!</p>

<p><strong>FAQ</strong>: When will FusionForge 5.0 be released? ⇒ As soon as it’s ready. Faster if you help.</p>

<p>EvolvisForge will migrate to a 5.0-based code some time after, taking care of possible regressions and merging our changes, some of which will then wander into FusionForge trunk, hopefully ☺</p>
----
ID: evo-7
Date: 09.05.2010 15:29:23
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Migration successful!
Tag: work

<p>tl;dr: EvolvisForge 4.8 deployed on *all* tarent systems now. Let’s party! Stay tuned for even more cool features.</p><!-- RSS stop -->

<p>I just installed EvolvisForge 4.8.3+evolvis12 (after quite some bugfixing) on <a href="https://evolvis.org/">evolvis.org</a> and the last remaining internal instance.</p>

<p>This means that tarent is no longer running GForge 4.5 so let’s celebrate!</p>

<p>You’re hereby cordially invited to check out the public <a href="https://evolvis.org/">Evolvis</a> and what makes it so good (FusionForge based) and then even better (our hard work ☺). This is the latest and greatest, but still work in progress, we have a lot of further improvements planned, so stay tuned!</p>
----
ID: evo-9
Date: 10.06.2010 09:49:41
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Configuration simplification
Tag: work

<p>With <a href="https://evolvis.org/">EvolvisForge 4.8.3+evolvis20</a>, we have <a href="http://lists.fusionforge.org/pipermail/fusionforge-general/2010-June/001074.html">a new configuration system for Apache 2</a> (being prepared for merging into FusionForge) which greatly simplifies things.</p>

<p>The most common tasks can now be easily solved:</p>
<ul>
	<li>/etc/gforge/templates/httpd.ssl0.inc: uncomment two lines, and all forge vhosts redirect to https unconditionally</li>
	<li>/etc/gforge/templates/httpd.auth.forge.inc: uncomment a bunch of lines, and you get HTTP Basic Auth with PAM backend accessing nss_pgsql2, which means you must login with your forge username and password to display the site</li>
	<li>/etc/gforge/templates/httpd.auth.projects.inc: copy the same lines here, and the project homepages (*.forge vhosts) are protected in the same manner</li>
	<li>/etc/gforge/httpd.d/*: change 02namevhost, 06maindirhttp, 20list, 40virtualhost if you want not *:80 and *:443 vhosts but per-IPv4-address vhosts</li>
	<li>/etc/gforge/gforge.conf: insert lines like 「sys_sslcrt=/etc/ssl/my.cer」, 「sys_sslkey=/etc/ssl/private/my.key」, 「sys_ssl_apache_extra_cmd=SSLCertificateChainFile /etc/ssl/chain.pem」 to configure HTTPS properly and easily</li>
</ul>

<p>Of course, there’s more to that: If you have more vhosts, just 「Include /etc/gforge/httpd.security.inc」 to <a href="http://www.cgisecurity.com/questions/httptrace.shtml">disable a potential security hole / information leak</a>, 「Include /etc/gforge/httpd.log.inc」 to log into the same files, 「Include /etc/gforge/httpd.ssl0.inc」 (SSL off) and  「Include /etc/gforge/httpd.ssl1.inc」 (SSL on) to use the same SSL configuration as the forge. The latter is especially important if you have more than one 〈VirtualHost *:443〉 container, as Apache 2 uses the configuration from the ASCIIbetically first one.</p>

<p>I was able to completely switch from the old, hand-edited configuration to a generated one with little, if any, changes on all our installations now. Some legacy or useful vhosts have been split out, for example a redirect for the old-style Wiki URIs, the Maven 2 repository vhosts, and Alfresco/Domisol (which was already separate but now got split port-80/443 configuration and the above-mentioned Include directives).</p>

<p>Furthermore, eMails from forge users to the FOO-commits@ mailing lists are always allowed by default for newly created lists, and users added to a group with SVN commit rights will be automatically subscribed to that list. We now issue the <a href="http://home.gna.org/forgeplucker/forge-identification.html">Forge Identification Header</a> and display the version on the webpage. There was, of course, your usual round of bugfixes and infrastructure improvements, including preparations for more things to come (so stay tuned).</p>

<p>Roland will, as usual, take the best out of EvolvisForge and put it into <a href="https://fusionforge.org/">FusionForge</a> (et vice versa).</p>

<p>There’s also news on the not-so-forge front of Evolvis: our Hudson installations talk Jabber now, and the integration is becoming more tight. We can drive both old-style wikis and gforge-plugin-mediawiki at the same time. We’ve begun adding a bunch of mediawiki plugins (more to follow as needed); if there are people packaging those for Debian already, cooperation is desired.</p>

<p>Until 12th of June, the “Fairtrade Software” booth at <a href="http://www.linuxtag.org/2010/de/aussteller/aussteller-2010.html">LinuxTag 2010</a> in Berlin, Germany, will present Evolvis and FusionForge to the public. Visit us in Hall 7.2a, Booth 123, and check out the <a href="https://evolvis.org/projects/freedroidz/">other exciting</a> tarent projects!</p>
----
ID: evo-11
Date: 01.07.2010 15:15:30
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: 21
Tag: work

<p>No, it’s not just half the answer. I think we’re much farther down the way than that ☺ while there are still improvements planned, under development, and to come, we’ve gone a long ways from 4.5 based Evolvis platform releases.</p>

<p>I have just upgraded all tarent-internal instances of Evolvis, as well as the public <a href="https://evolvis.org/">evolvis.org</a> forge, to a new version of the <a href="https://fusionforge.org/">FusionForge</a> based <a href="https://evolvis.org/projects/evolvis/">EvolvisForge</a> as well as <a href="http://www.mediawiki.org/wiki/Extension:NewestPages">MediaWiki and its extensions</a>.</p>

<p>There are several new extensions, almost all of them enabled by default. You can see a tech demo of these at <a href="https://evolvis.org/plugins/mediawiki/wiki/evolvis/index.php/PluginDemo">https://evolvis.org/plugins/mediawiki/wiki/evolvis/index.php/PluginDemo</a> (which will automatically show you an English- or German language version depending on your web browser’s preferences). The extensions are:</p>
<ul>
	<li>Math</li>
	<li>Cite</li>
	<li>Collection</li>
	<li>CreateBox</li>
	<li>Footnote</li>
	<li>GraphViz</li>
	<li>ImageMap</li>
	<li>InputBox</li>
	<li>LanguageSelector</li>
	<li>NewestPages</li>
	<li>News</li>
	<li>PageCSS</li>
	<li>ParserFunctions</li>
	<li>Polyglot</li>
	<li>RSS_Reader</li>
	<li>SpecialCite</li>
	<li>SyntaxHighlight_GeSHi</li>
</ul>

<p>The MediaWiki extensions are “driven” (configured) by the forge semi-automatically, for example RSS_Reader uses a per-project (forge group) cache directory instead of disabling the cache (which needed to be done for the Debian package, since the default installation does not have the luxury of a directory writable for the Apache user). The configuration closely matches the “old-style” (JH) Wiki integration that has been done for Evolvis 4.5 previously.</p>

<p>Further changes include a fair number of bugfixes to the code, theme, wiki, extensions (fed upstream), and XHTML compliance. We know there are still enough bugs to keep us busy for a while, but you might notice some improvements; others are hidden but shorten the Apache error_log noticeably ☺</p>

<p>To further summarise from the <a href="https://evolvis.org/scm/viewvc.php/trunk/gforge_base/evolvisforge/gforge/debian/changelog?root=evolvis&amp;view=markup">developer/package management system changelog</a> the (non-bugfix) changes from the last version include:</p><ul>
<li>reduced space requirements by using the <a href="http://packages.debian.org/lenny-backports/xz-utils">xz</a> compressor instead of gzip for nightly Subversion backups</li>
<li>give forge (group/project and site) admins more permissions in the Wiki by default</li>
<li>Konqueror users have clickable <tt>sftp://</tt> links in the places where SFTP/manual file upload can be used</li>
<li>displaying filenames of uploaded files, including rules for them, has been improved</li>
<li>there are now two automatic mailing lists (for newly created groups/projects): <i>unixname</i>-commits (where every member with commit rights will be added automatically) and <i>unixname</i>-discuss (where every member will be added automatically); of course there’s still the option to unsubscribe or, for non-members, to subscribe (a <a href="https://code.launchpad.net/~melanie-lebail/mailman/coclico">new Mailman integration</a> is being worked on)</li>
<li><a href="http://www.list.org/">Mailman</a> list administrator passwords can now be (re-)set from the forge (by group/project or site admins); be careful to tell your co-admins the new password though…</li>
<li>new values for PM (Tasks) status fields</li>
<li>the ability to copy a task to another subproject</li>
<li>customisable display for the Tasks area</li>
</ul>

<p>Notable bugfixes:</p><ul>
<li>the SCM URLs now always use the correct hostname</li>
<li>help window pop-ups are working again</li>
<li>Evolvis can now almost fully be used with PHP 5.3 on Debian unstable (although we are still formally targetting Debian Lenny (with select backports and custom packages) specifically)</li>
<li>font sizes (in the forge and the wiki) are finally consistent</li>
<li>slight performance improvements</li>
</ul>

<p>The time tracking area in Tasks has been disabled, since there is a company-internal tool doing the same, with an Evolvis integration being developed.</p>

<p>We hope you enjoy the latest installment of the Evolvis platform!</p>

<p> -- Thorsten Glaser, for the <a href="http://www.tarent.de/">tarent</a> Evolvis task forge, FusionForge and Mediawiki</p>
----
ID: evo-14
Date: 14.09.2010 15:21:33
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: 25 ☺
Tag: work

<p>tl;dr: EvolvisForge 4.8.3+25 with Permalinks and unique IDs for Task and Tracker items, automatic links for RFC conformant hrefs and [#123] style texts in comments and commits, better Task manipulation, improved Mediawiki integration and SOAP functionality, automatic mailing lists and greylisting, better debugging and less PHP and XHTML errors has been released.</p><!-- RSS stop -->

<p>And again, with a plethora of bugfixes, improvements and new features, EvolvisForge 4.8.3+evolvis25 was released and deployed. Read on for more details!<!--more--></p>

<p>The probably most amazing things have been done in the Tasks and Tracker areas again. You can now write “[#123]” in a Task or Tracker comment, and it will automatically be converted into a link to the respective task/tracker item IFF the latter was created today or later (to be exact, while EvolvisForge 4.8.3+evolvis25 or later was installed); this stipulation is valid for all such references. When you write “[#123]” in an SVN commit message, the same applies in both directions – links to the task/tracker item from SCM → ViewVC (web-based Subversion browser) and links to the changeset from the task/tracker item as Related Commit (similar to how Related Tasks work). Similar to the t_follow.php based Permalinks for Tasks, Trackers now also have permalinks that are displayed. In both Tasks and Tracker, the ID column in the subproject browse view links to them for easy grabbing. The browse views also have configurable paging for logged-in users now, the setting of which is stored as a global preference.</p>

<p>In task/tracker item comments (as well as the initial comment, named “detailed description”), hyperlinks are made “clickable” automatically as well, using RFC-compliant matching (i.e. http://foo/möp is not a valid link – to be exact, it’ll link to http://foo/m – but http://foo/m%C3%B6p is).</p>

<p>It is now possible to change the “percent complete” column of Tasks in a bulk update. The Copy+Closed functionality now works almost correctly (a minor detail for better tarent-Activity usability will be changed later). The comments are now displayed in chronological order, instead of antichronological, for better human readability.</p>

<p>The state and percent complete of linked tasks are shown in the detail view of a Tracker item (bug, feature request, …), and related tasks can be unlinked there as well, instead of just in the tasks’ detail view.</p>

<p>The search now ignores double quotes and searches for the combination of all words by default.</p>

<p>The MediaWiki plugin sees Interwiki capability: the Interwiki table is global (per-forge) instead of per-wiki and filled with all præficēs automatically, using the Project’s unix name. It can also be edited with the new Special:Interwiki MediaWiki extension. The mw-wrapper.php script works correctly again, and nightly XML dumps of every Wiki are available, for example for backups. It is now possible to use both English (File:foo.jpg, #REDIRECT, Special:Weird) and German (Datei:foo.jpg, #WEITERLEITUNG, Spezial:Seltsam) syntax in the Wikis. Pages like Login/Logout, Create Account and Lost Password, that have no value in the MediaWiki plugin, redirect to the Forge’s equivalent functionality.</p>

<p>The SOAP WSDL now compiles cleanly and sees a few bugfixes as well as a new API “addUploadedFile” which works with the File Release System and manual (SFTP) uploads, to facilitate automatic deployment, e.g. from a Hudson running Maven.</p>

<p>The Document Manager has received some fixes and the ability to use manual (SFTP) upload like the FRS.</p>

<p>All projects will have a -commits and a -discuss mailing list; all members with SCM commit access will be added to the former, all proect members no matter what to the latter automatically upon joining the project (you can, of course, unsubscribe). Postings to the -commits list bear the -discuss list as followup. The Postfix MTA will be configured to use Postgrey for greylisting to reduce spam income.</p>

<p>There’s now a suggestion list for project tags. In most places where a history was kept (project, task, tracker), not only the old but also the new value are stored and shown now, and the sort order has been reversed to chronological as well.</p>

<p>EvolvisForge will now work better with Python 2.6 and PHP 5.3 on Debian unstable, although Debian Lenny (with backports) is still the only supported platform; *.deb files are available on request, we’ll allow others to install EvolvisForge and related software by and for themselves now (although most of the functionality is supposed to be achievable by using <a href="https://fusionforge.org/">FusionForge</a>, our upstream Open Source project). (In fact, in between writing this Release Announcement for the <a href="https://evolvis.org/projects/evolvis/">Evolvis Project</a> and formatting it for the Blog, Roland Mas has begun merging improvements into FusionForge trunk. Nevertheless, contact <b>evolvistodo <i>{klammeraffe}</i> tarent <i>{punkt}</i> de</b> if you want to set up an EvolvisForge instance yourself. Remember that Evolvis is more than just the Forge, it’s also Wikis (now included in the Forge though), Blogs, Planet, Continuous Integration (soon to be integrated in the Forge), Domisol, and more.)</p>

<p>Some minor things have been fixed too, for example, there was a tremendous effort to fix all PHP warnings found and make all pages XHTML 1.0/Transitional compliant (if one isn’t, it can now be considered a bug), which led to the redesign of some pages, such as the Task “Select Columns” facility and the project Admin page. Wrong output, texts and translations in some places have been fixed. Developers of EvolvisForge now have better help in debugging: the “pink pop-up” can display calls to db_query{,_params} and backtraces when PHP warnings/errors occur. The licence information of a project will not be shown, as it currently cannot be set (we’re working on that). Several theme issues have been corrected, and to Mozilla™ Firefox® users (and users of other Gecko-based browsers),  fields’  elements will now appear white-on-black by default with black-on-white (instead of white-on-blue) for selected items, due to a bug in that browser series. And, of course, the bugfixes from our upstream, <a href="https://fusionforge.org/">FusionForge</a>, have been merged when applicable as well.</p>

<p>The <a href="https://evolvis.org/scm/viewvc.php/trunk/gforge_base/evolvisforge/gforge/debian/changelog?root=evolvis&amp;view=markup">complete changelog</a> and our <a href="https://evolvis.org/plugins/mediawiki/wiki/evolvis/index.php/PluginDemo">MediaWiki Plugin demonstration page</a> are still available for your convenience.</p>

<p>We wish you a pleasant experience using the new, improved EvolvisForge, as well as the rest of our Evolvis platform! -- The Evolvis team</p>

<p>PS: Sorry for the very long posting, but I’ve already tried to go down on detail and only mention the important things, mostly from a user’s PoV, and condensed… it’s just a lot happened and some co-workers are really excited about those features yet.</p>
----
ID: evo-21
Date: 21.01.2011 16:19:06
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Evolvis: git and scm, SOAP WSDL, Jenkins, …
Tag: debian work

<p>tl;dr: New Evolvis release, scmgit plugin, bidirectional merge with FusionForge 5.1; committing tarent features back to Mediawiki and Mailman packaging in Debian; Fairtrade Software</p><!-- RSS stop -->

<p><a href="http://www.tarent.de/">tarent GmbH</a> now offers both git and Subversion as Source Code Management systems in their <a href="https://evolvis.org/">Evolvis</a> platform.</p>

<p>The scmsvn plugin of EvolvisForge was amended with the scmgit plugin, backported from a newer <a href="https://fusionforge.org/">FusionForge</a> release, while work to upgrade the main forge code to the soon-to-be-released FusionForge is ongoing in parallel. Of course, most features, such as commit mails (in git, they’re really sent out after a “git push” from the developer), are already available for both; others will follow after the code base upgrade for simplicity. Already, git repositories can be used for all regular tasks – although it’s currently not possible to have both git and svn repositories in a project.</p>

<p>During the migration (as well as regular development), many features of Evolvis will show up in regular FusionForge to benefit the broad community of Forge users, courtesy of the Open Source policy of tarent GmbH, who has contracted the FusionForge project leader to improve both projects, following the mantra of “Fairtrade Software”.</p>

<p>Among other changes, the SOAP WSDL has been corrected and is now versioned, and other areas (especially the Tasks and Tracker) have been improved.</p>

<p>There’s a <a href="https://evolvis.org/forum/forum.php?forum_id=379">release announcement</a> of the new version at Evolvis, in case you want to know the details.</p>

<p>Finally, an Evolvis developer has set foot not only in the Mediawiki packaging team at Debian but also the Mailman packaging team. Expect many, if not all, improvements to show up there within some time.</p>

<p>Did you know that Hudson is now called <a href="http://jenkins-ci.org/">Jenkins</a>? This is a change in name only, due to trademark concerns, but rest assured the Evolvis platform will continue to offer Continuous Integration in a usable fashion, no matter the technology behind (there was Continuum, now <a href="http://hudson-labs.org/">Hudson</a>, soon Jenkins).</p>

<p>In our evergoing quest to improve the Evolvis platform, we wish you a pleasant user and developer experience!<br />
//The Evolvis team</p>
----
ID: evo-24
Date: 13.04.2011 16:16:25
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Administrativa (Evolvis Blogs)
Tag: work

<p>The blogs have been moved from *.blogs.evolvis.org to *.blog.tarent.de to provide proper SSL certificates. This also means that the use of blogs for people who are not employees of tarent GmbH, tarent AG or one of its subsidiaries is currently not available. (If that should become necessary, please <a href="mailto:evolvistodo@tarent.de">contact us</a>.</p>

<p>The feed has moved to http://evolvisforge.blog.tarent.de/feed/ for this blog (similarily to the others), but just in case, you’ll get redirected (although only to the https version, which Planetplanet doesn’t seem to like).</p>

<p>Planet Evolvis will be set up anew using Planet Venus software shortly.</p>

<p>All in all, the Greater Evolvis Platform is undergoing updates and improvements.</p>
----
ID: evo-26
Date: 13.04.2011 16:22:38
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: JSON
Tag: work debian

<p>tl;dr: Full JSON encoder/emitter and decoder/parser in Pure PHP now available as part of FusionForge/Evolvis under GPLv2. Do not use PHP’s built-in code, it’s broken. Read on for details and links.</p><!-- RSS stop -->

<p>I’ve pimped the <a href="https://evolvis.org/scm/viewvc.php/trunk/gforge_base/evolvisforge-5.1/src/common/include/minijson.php?root=evolvis&amp;view=markup">minijson</a> code in EvolvisForge to be a full-blown JSON encoder and decoder (lexer/parser) now. You wouldn’t believe just how much is broken in PHP (its own json_encode handles floats wrong in most locales, and mb_check_encoding doesn’t check the encoding of a multibyte string… at least, unlike Python, PHP manages to get 8bit okay though).</p>
<p>Anyway, thought you want to know. If you ever need a Pure PHP JSON encoder/decoder, you know where to look. It’s 100% my code (although written during dayjob, so the exploitation rights are with tarent GmbH). Current licence is GPLv2+ or AGPLv3+. If you spot any bugs, you know <a href="https://evolvis.org/projects/evolvis-platfrm/">where to report</a> them. I think it should be good though. (Do note that JSON is case-sensitive, so “NULL”, “True” and “\N” or “\U20AC” are not valid, “null”, “true”, “\n” and “\u20AC” or “\u20ac” are.)</p>
<p>I plan to store the “art_cust<em>123</em>” information in the user_prefs table in JSON now, instead of ‘|’-separated values, to avoid problems like these we had with broken database format and subsequent corruption of values, by using a dictionary (JSON Object) instead.</p>
<p>The <a href="http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-262.pdf">ECMA 262</a> standard (ECMAscript and JSON) is freely available, though. JSON is also additionally specified in <a href="http://www.ietf.org/rfc/rfc4627.txt">RFC 4627</a> which differs slightly (see <a href="https://www.mirbsd.org/cvs.cgi/contrib/hosted/tg/code/MirJSON/json.txt?rev=HEAD">my notes</a> for details, mostly the goal element).</p>

<p>Update: fixed links</p>
----
ID: evo-31
Date: 26.05.2011 12:36:08
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: How (not to) encode MIME headers
Tag: work debian

<p>I was just tracking down why some mails seem to have garbled Subjects.</p>

<p>It looked like this in Alpine:<br />
<code>Subject: [BOFH commits] r2040:  fix directory struct =?UTF-8?Q?ure=E2=86=B5=20unix?=/mirror/=?UTF-8?Q?=20=E2=86=92=20mirror?=. bonn</code></p>

<p>The raw header sight was this:<br />
<code>Subject: [BOFH commits] =?utf-8?q?r2040=3A__fix_directory_struct__=3D=3FUT?=<br />
 =?utf-8?b?Ri04P1E/dXJlPUUyPTg2PUI1PTIwdW5peD89L21pcnJvci89P1VURi04P1E/?=<br />
 =?utf-8?b?PTIwPUUyPTg2PTkyPTIwbWlycm9yPz0uIGJvbm4=?=</code></p>

<p><em>Ein Schelm, wer Böses dabei denkt…</em> First suspect was, of course, Mailman – after decoding, this showed the classical signs of a double-encode. (After ruling out general header brokenness, but no, 76 chars is ok.) I thus hand-crafted an eMail with the correct header line and sent that out:<br />
<code>Subject: [BOFH commits] =?utf-8?q?r2040=3A_fix_directory_structure?=<br />
 =?utf-8?b?4oa1IHVuaXgvbWlycm9yLyDihpIgbWlycm9yLmJvbm4=?=</code></p>

<p>Huh? Mailman and Python weren’t the culprit, thus – this is correct mangling. Okay, let’s dive into the Perl code that actually sends out the eMails. To make a long story short, have a look at this, then <a href="http://tools.ietf.org/html/rfc2047">RFC 2047</a>:<br />
<code>tglase@tglase:~ $ perl -MEncode -e '$subject = "r2040: fix directory structure↵ unix/mirror/ → mirror.bonn"; Encode::from_to($subject, "UTF-8", "MIME-Q"); print "{Subject: ".$subject."}\n";'<br />
{Subject: r2040:=?UTF-8?Q?=20fix=20directory=20struct?=<br />
 =?UTF-8?Q?ure=E2=86=B5=20unix?=/mirror/=?UTF-8?Q?=20=E2=86=92=20mirror?=.<br />
 bonn}</code></p>

<p>Amazingly enough, PHP’s <strong>mb_encode_mimeheader</strong>, despite being talked to trash in the comments on its online documentation, <strong>does</strong> manage to get it right:<br />
<code>tglase@tglase:~ $ php -r 'mb_internal_encoding("UTF-8");echo "{".mb_encode_mimeheader("Subject: r2040: fix directory structure↵ unix/mirror/ → mirror.bonn", "UTF-8", "Q")."}\n";'<br />
{Subject: r2040: fix directory =?UTF-8?Q?structure=E2=86=B5=20unix/mirror/?=<br />
 =?UTF-8?Q?=20=E2=86=92=20mirror=2Ebonn?=}</code></p>

<p>Wow. Now, the Perl guys I know told me to use Perl’s Mail tools… which are much too high-level though, for all I have and want is the subject string and an RFC 822 header line. I told them I’m not above doing <a href="https://evolvis.org/scm/viewvc.php/evolvis/trunk/gforge_base/evolvisforge/gforge/plugins/scmsvn/etc/plugins/scmsvn/commit-email.pl?r1=17270&amp;r2=17277&amp;diff_format=u">this</a>, and so I did. The 3P languages can really be annoying.</p>

<p>Why’s Perl’s output wrong anyway? I don’t know for sure, but I think the atoms must be separated, so unquoting <code>/mirror/</code> in the middle, with no spaces around it, are wrong. (Besides, <strong>Encode::from_to</strong> can’t do the job right anyway, as it misses the <em>name</em> of the header, which is included in the 76 chars allowed for the first line. BAD • Broken As Desdigned.)</p>

<p>Disclaimer: I don’t really know any Perl, I fight my way through PHP and, barely, Python. (But I can code.)</p>
----
ID: evo-34
Date: 14.06.2011 12:02:33
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: mksh R40 is out, so what now?
Tag: work debian

<p><a href="https://www.mirbsd.org/mksh.htm#r40">mksh R40</a> has been released Sunday 12nd June. So, what can you do with <a href="https://www.mirbsd.org/man1/mksh">The MirBSD Korn Shell</a>?</p>

<p>Have a look at the <a href="https://evolvis.org/plugins/scmgit/cgi-bin/gitweb.cgi?p=shellsnippets/shellsnippets.git">collection of shell snippets</a>, which admittedly is only the beginning – most scripts don’t make use of the <a href="http://freshmeat.net/projects/mksh">cool new features</a> yet. But they eventually will. The <a href="https://evolvis.org/projects/shellsnippets/">Shell-Toolkit</a> project is definitely worth a visit! (Admittedly not using <a href="http://packages.qa.debian.org/c/cvs.html">my most ❦ dear SCM</a>, but with a DVCS, every checkout is a clone, i.e. a backup, and none of the contributors must fear a central repo being taken down, which, for such a loose collection, is desirable.)</p>
----
ID: evo-36
Date: 20.07.2011 09:12:02
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: 35, a.k.a. it’s time for a blog posting again ☺
Tag: work

<p><a href="https://evolvis.org/projects/evolvis/">Evolvis 4.8.35</a> has been released this week. This is an amazing upgrade within the 4.8 series of development, to bridge the time gap until such time as the 5.1 series can be used.</p>

<p>As <a href="https://evolvis.org/forum/forum.php?forum_id=408">announced earlier</a>, our <a href="https://evolvis.evolvis.org/debidx.htm">APT Repository</a> contains packages targetting Debian Lenny (amd64, i386), including side packages and backports needed for a standard EvolvisForge installation, add <a href="https://evolvis.evolvis.org/sources.txt">one of these lines</a> to your <code>/etc/apt/sources.list</code> to use it. These packages might work on Debian squeeze, maybe even *buntu, but will probably have issues with multiarch on Debian unstable.</p>

<p>First the big caveat: support for old-style (Jutta Horstmann) external Wiki instances has been removed, since we migrated all Evolvis installations to use gforge-plugin-mediawiki a while ago already.</p>

<p>Now the big news: bug trackers (old and new) contain several <a href="https://evolvis.org/plugins/mediawiki/wiki/evolvis/index.php/Tracker_StandardSuche">predefined search queries</a> useful for Software Engineering and Quality Assurance. There’s a new standard tracker type called “Funktionsreferenz” (functionality specification) on every newly created project. The <a href="https://evolvis.org/plugins/mediawiki/wiki/evolvis/index.php/Extratabs">Extratabs plugin</a>, backported from 5.1 then enhanced, allows adding arbitrary tabs as link or IFRAME (embedding content) to any project. And the <a href="https://evolvis.org/plugins/mediawiki/wiki/evolvis/index.php/Datumsformate">DatePicker component</a> allows easily entering a date, or a date plus time-of-day, using an ECMAscript pop-up while also accepting simple strings, for instance from Lynx users. The format used for displaying dates can be configured in “My Account” between d.m.y, y-m-d and m/d/y; the software accepts all three formats, always, nevertheless. Furthermore, the ECMAscript DatePicker widget is available in a number of languages for all three formats – English, German (Deutsch), Spanish (Español), French (Français), Italian (Italiano), Dutch (Nederlands), Polish (Polsku), Portuguese (Portugues), Romanian (Românesc), Bulgarian (Български), Russian (Русский), Hungarian (Magyar), Norwegian (but I’m not sure if it’s Nynorsk or Bokmål).</p>

<p>Now the small improvements: a robots.txt file is present by default, allowing wget and asking all crawlers to slow down; system administrators may configure it (in gforge.conf) to switch to one disallowing search engine spiders. Newly created Tasks have a default duration of two weeks (standard Scrum timeframe), not one week. /usr/share/gforge/bin/scm-newsubrepo.php supports easily adding new git repositories to a project already using them.</p>

<p>And finally, the most important / visible bug fixes: Sorting tables in Tasks works again, and the search drop-down boxen in Tracker are now sorted. The modify task/tracker forms have more “Submit” buttons and have been slightly rearranged to improve User Experience. “Copy+Close” a task works again. Some links, labels and translations (German only) have been corrected. Project members are now added to the default mailing lists correctly, i.e. to the -discuss group always, to the -commits group if they have SCM Write permissions. Custom Tracker fields of type Checkbox no longer have the “100 None” option. Tasks do not show up on “My Page” several times now, once is enough ;-)</p>

<p>Last but not least, a look at the future: we’re working on our Jenkins Plugin, which we might provide for Evolvis 4.8 if it’s functioning quickly enough. We’re also working on getting Evolvis 5.1 into a usable shape, and porting all Evolvis 4.8 functionality to it. Much has been integrated in the recently released <a href="https://fusionforge.org/">FusionForge</a> 5.1 already. A new functionality to mark bugs as duplicate, followup or having a simple, nontyped relationship to another tracker item is being worked on, as are improvements (new items, better look’n’feel) to the “My Page”. And that’s just the big news.</p>

<p>A <a href="https://evolvis.org/plugins/mediawiki/wiki/evolvis/index.php/Category:Handbuch">German language User’s Guide / Handbook</a> is also being worked on. It’s a Wiki, so feel free to help ☺ (although the licence is CC-BY-NC-SA and thus non-free, sorry for that, but the software itself is GPLv2+). And as usual, there’s a <a href="https://evolvis.org/scm/viewvc.php/evolvis/trunk/gforge_base/evolvisforge/gforge/debian/changelog?view=markup">full changelog</a> and you can look at the <a href="https://evolvis.org/scm/viewvc.php/evolvis/trunk/gforge_base/evolvisforge?view=log">svn revision log</a>.</p>

<p>We wish you an enjoyable software development and lifecycle management, <i>your tarent solutions GmbH Evolvis Project Team</i></p>
----
ID: evo-40
Date: 11.08.2011 12:29:05
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Jenkins und die APT-Repositories
Tag: debian work

<p>(Dieses Posting wurde ursprünglich im internen Blog veröffentlicht, ist jedoch hierhin umgezogen. Es sind keine sensitiven Informationen enthalten, allerdings können die Links nur im Firmennetz angesteuert werden.)</p>

<p>Neues aus der Adminstube (und vom Evolvis-Team) für unsere Entwickler, die wir, nachdem wir die Projektmanager schon bedient haben, auch nicht zu kurz kommen lassen wollen:</p>

<p>Wenn ihr einen Jenkins-Job habt, der Debian-Pakete (oder für Derivate) erstellt, könnt ihr ab sofort (mindestens) ein Repository pro Job haben, in dem ihr die Pakete „veröffentlichen“ könnt. Diese Repositories werden automatisch signiert, und durch tarent-keyring werden die Signaturen bereits seit Dienstag verteilt, sodaß auch SecureAPT funktioniert.</p>

<p>Im folgenden wird die Arbeitsweise am Beispiel von Saschas WIP-Portalinstaller erklärt.</p>

<p>Ausgangspunkt ist ein Jenkins-Job, in diesem Fall auf dem test-hudson, hier mit dem Namen „portal-setup“, der unter „Build“ den Punkt „Execute shell“ aktiv hat. Hier wird durch diverse Kommandos ein Debian-Paket (Source und Binary) gebaut, das wirklich wichtige hierbei ist folgender Ausschnitt:</p>

<pre>
	cd portal-setup-$pv
	dpkg-buildpackage -rfakeroot -us -uc
	cd ..
	#rm -rf portal-setup-$pv
</pre>

<p>Der Befehl dpkg-buildpackage übernimmt das Bauen und schmeißt die erstellten Pakete (Source *.dsc und Binaries *.deb) und, ganz wichtig, die *.changes-Datei, ins Elternverzeichnis (daher die cd-Aufrufe). Nun möchte Sascha, daß diese Pakete einfach von Kollegen getestet werden, und ändert daher den Codeschnipsel so ab:</p>

<pre>
	cd portal-setup-$pv
	dpkg-buildpackage -rfakeroot -us -uc
	cd ..
	#rm -rf portal-setup-$uv portal-setup-$pv

	/opt/mvn-debs/mvndput.sh portal-setup squeeze main *.changes
</pre>

<p>Im ersten Teil bleibt alles beim alten, aber ein neuer Befehl ist am Schluß hinzugekommen. Was macht der?</p>

<p>Nun, <code>/opt/mvn-debs/mvndput.sh</code> ist die <a href="https://www.mirbsd.org/mksh.htm">Magie</a>, die unterhalb des Pfades <code>/opt/mvn-debs</code> ein Debian-Repository mit dem Jobnamen <code>portal-setup</code> anlegt. Wir publizieren Pakete in die „dist“ <code>squeeze</code>, und darin in die „suite“ <code>main</code>. Das ist hier lediglich eine Konvention; normalerweise heißt die <em>dist</em> so wie die Debian-Version (sarge, dapper, etch, hardy, lenny, squeeze, …), für die das Paket gedacht ist, und die <em>suite</em> ist eine Unterkategorie – also zum Beispiel main/contrib/non-free oder main/restricted/universe/multiverse oder wtf/tarent/evolvis (in unserem Adminrepo). Man kann die aber auch frei Schnauze nennen (ich hab zum Beispiel im m68k-Repo eine <em>dist</em> namens „cross“, unterhalb derer eine Cross-Toolchain liegt).</p>

<p>Das letzte Argument ist <code>*.changes</code>, was <a href="https://www.mirbsd.org/man1/mksh">die Shell</a> für uns expandiert: alle Dateien, die auf „.changes“ enden, werden dort (ASCIIbetisch sortiert) der Reihe nach aufgelistet.</p>

<p>Das Skript prüft nun zunächst die Namen und Dateien auf Plausibilität (es sind schließlich immer nur gewisse Zeichen erlaubt) und schiebt dann vermittels dput ein Release (also eine *.changes + alle drin enthaltenen *.deb + dazugehörige *.dsc, *.diff.gz/*.debian.tgz, *.orig.tar.gz, oder *.tar.gz bei <em>native packages</em>) ins APT-Repository und läßt danach den Index regenerieren und PGP-signieren. <code>dput</code> ist ein schlaues Tool, es schreibt nämlich nach getaner Arbeit eine *.upload-Datei, in welcher dieser Fakt verzeichnet wird, sodaß Pakete auch wenn man den <em>workspace</em> nicht jedes Mal wegschmeißt nur einmalig hochgeladen werden. (Es existiert allerdings hier kein Schutz davor, den <em>workspace</em> zu leeren und ein Paket mit derselben Version aber anderem Inhalt ein zweites Mal hochzuladen. Nur die Systeme, die das installieren wollen, mögen einen dann ggf. nicht mehr so gerne.)</p>

<p><code>mvndput.sh</code> ruft nun also <code>mvndebri.sh</code> auf, was allerdings mehr macht als nur das Äquivalent von Debians dak oder CentOS’ createrepo. Es erstellt nämlich auch einen Index.</p>

<p><a href="http://test-hudson-debs.bonn.tarent.de/portal-setup/debidx.htm">http://test-hudson-debs.bonn.tarent.de/portal-setup/debidx.htm</a> heißt der Gute, und ist eine Auflistung aller Pakete nach <em>dist</em>, <em>suite</em>, <code>Source</code> und <code>Binary</code> im Repository. Weiterhin steht oben nochmal, um welches Repository es sich handelt, und welche <em>dist</em>s und <em>suite</em>s verfügbar sind. Der Name bildet sich aus „http://“ + Jenkins-Systemname + „-debs.bonn.tarent.de/“ + Jenkins-Jobname + „/debidx.htm“ – wenn man den Dateinamen wegläßt kann man das auch direkt als Verzeichnisstruktur anschauen.</p>

<p>Der Clou: die passende <code>sources.list</code>-Zeile steht auch schon da! (Allerdings muß man die <em>suite</em>n ggf. auf die, die wirklich benötigt werden, reduzieren.)</p>

<p><code>deb http://test-hudson-debs.bonn.tarent.de/portal-setup squeeze main</code></p>

<p>Das funktioniert auf allen acht Jenkins-Systemen, allerdings natürlich nur aus dem tarent-Netz heraus – dafür ohne https oder aufwendige Authentifizierung. Einfach so.</p>

<p>Bitte achtet darauf, den Namen des Jenkins-Jobs als erstes Argument zu <code>mvndput.sh</code> zu verwenden, ggf. gefolgt von einer Kennzeichnung, falls ihr mehr als ein Repo pro Job braucht (warum, weiß ich nicht, aber es geht). Da alles als maven-User läuft findet keine Abgrenzung statt.</p>

<p>Wenn ihr Pakete aufräumen möchtet, so loggt euch (als User maven) auf dem entsprechenden Jenkins ein und schaut auf der Verzeichnisebene nach; einen direkten Link gibt’s auch, wenn man das <code>[dir]</code> im tabellarischen Index anklickt, zum Beispiel <a href="http://test-hudson-debs.bonn.tarent.de/portal-setup/dists/squeeze/main/Pkgs/portal-setup/">http://test-hudson-debs.bonn.tarent.de/portal-setup/dists/squeeze/main/Pkgs/portal-setup/</a>, was im Dateisystem dem Verzeichnis <code>/opt/mvn-debs/portal-setup/dists/squeeze/main/Pkgs/portal-setup/</code> entspricht.</p>

<p>Nachdem ihr händisch Änderungen dort vorgenommen habt, müßt ihr natürlich den Index neu generieren lassen, das geht dann so:</p>

<p><code>mksh /opt/mvn-debs/mvndebri.sh /opt/mvn-debs portal-setup squeeze</code></p>

<p>Wenn ihr nicht nur eine <em>dist</em> angefaßt habt, könnt ihr die auch auflisten:</p>

<p><code>mksh /opt/mvn-debs/mvndebri.sh /opt/mvn-debs portal-setup hardy squeeze</code></p>

<p>Oder einfach weglassen, dann macht er alle:</p>

<p><code>mksh /opt/mvn-debs/mvndebri.sh /opt/mvn-debs portal-setup</code></p>

<p>Das ist dann auch der Unterschied zwischen <em>dist</em>s und <em>suite</em>s: letztere teilen sich ein Release-File, erstere nicht, nur den XHTML-Index.</p>

<p>So, ich hoffe, ihr findet das so nützlich wie Sascha und so arbeits- und zeitersparend wie ich ☺</p>

<p>PS: Der <a href="https://evolvis.org/plugins/scmgit/cgi-bin/gitweb.cgi?p=shellsnippets/shellsnippets.git;a=commit;h=5c31b62ca4a6607347c29aa2c85220e241cfcc0f">Code</a> ist mittlerweile auch publiziert. Wer solch ein Szenario noch woanders aufsetzen möchte ist uns herzlich willkommen.</p>
----
ID: evo-42
Date: 11.08.2011 12:29:44
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Evolvis-Wikis und die Suchmaschine
Tag: work

<p>(Dieses Posting wurde ursprünglich im internen Blog veröffentlicht, ist jetzt jedoch hierhin umgezogen. Firmeninterne Information wurde gekürzt, ist aber für Mitarbeiter im <a href="https://lists.tarent.de/cgi-bin/mailman/private/blog-intern/2011-June/000206.html">Mailinglistenarchiv</a> ersichtlich.)</p>

<p>Neues aus der Adminstube (und vom Evolvis-Team) für unsere Projektmanager:</p>

<p>Im Rahmen der tarent-Suche werden die Wikis indiziert; dies ist natürlich nicht immer gewünscht, auch wenn die Suche nur Mitarbeitern zugänglich ist. Darum gibt es jetzt eine Möglichkeit, <a href="https://evolvis.org/plugins/mediawiki/wiki/evolvis/index.php/Mediawiki-Plugin,_Wiki_%C3%B6ffentlich_oder_privat_setzen">pro Projekt das Wiki öffentlich oder privat zu setzen</a>. Im Moment werden nur die Wikis auf evolvis.org und dev.tarent.de indiziert, <strong>ab dem 20.06.2011</strong> aber auch auf den Kundenevolvinēs – daher stellt eure Wikis bitte ein!</p>

<p>Wir werden jedes Wochenende den Suchindex leeren und neu aufbauen, das heißt, zukünftige Änderungen von öffentlich auf privat werden <i>erst in der Folgewoche</i> aktiv!</p>

<p>Die Einstellung betrifft den XML-Export, die tarent-Suche und die Sichtbarkeit für nicht eingeloggte Besucher. Wenn ihr die Einsicht eines Wiki vor Mitarbeitern, die keine Projektmitglieder sind, verstecken wollt, müssen wir weiterhin die Rechtefreigaben von Hand anpassen.</p>

<p>Die aktuelle Konfiguration ist wie folgt: [… gekürzt …]</p>
----
ID: evo-44
Date: 29.11.2011 15:46:37
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Jenkins und die APT-Repositories Ⅱ
Tag: work debian

<p>As reported earlier (in “Jenkins und die APT-Repositories” part 1) we’ve got some kind of Jenkins/APT integration, with automatically generating as many repositories as a job desires.</p>

<p>News are that the builds host has moved, so the URIs to the repositories have changed. The new syntax is https://ci-something.lan.tarent.de/ for the Jenkins ⇒ “deb https://ci-something-debs.lan.tarent.de/jobname/ distribution suite …” and currently only usable in the company-internal network.</p>

<p>We’ve also got <a href="https://evolvis.org/plugins/scmgit/cgi-bin/gitweb.cgi?p=shellsnippets/shellsnippets.git;a=blob;f=mksh/sysadmin/vcs2deb;h=c2db67e82027e04ca17da37500765c3fc89b214f;hb=HEAD">some more magic mksh code</a> to automate the entire process – check the code out from SCM (required, as Jenkins’ svn checkouts are <em>broken</em>), build a Debian source package, <strong>NEW!</strong> ask cowbuilder to compile it in a clean chroot environment, and call <code>mvndput.sh</code> for APT repository publication. Sample projects are ci-evolvis/virtualscreen (git) and ci-dev/portal-setup (svn). Talk to me if you have any questions.</p>

<p>This allows for a one-line “run a shell command” build step!</p>

<p>Everybody else is, of course, invited to take and re-use our code, and maybe even improve upon it and submit that back. It’s all Open Source, after all.</p>

<hr />

<p><b>tl;dr</b> Jenkins Jobs now have integration with cowbuilder. There’s a new script to automate the whole build pipeline. The APT repositories have moved with the <a href="https://blog-intern.tarent.de/admins/2011/11/18/jenkins-server-sind-umgezogen/">recent move</a>.</p>
----
ID: evo-54
Date: 31.10.2012 14:18:58
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: PostgreSQL #FAIL – Handarbeit nötig!
Tag: debian work

<p>PostgreSQL hatte vor kurzem ein <a href="http://wiki.postgresql.org/wiki/20120924updaterelease">Problem</a>, und zwar in der Version <b>9.1.5</b>, welches zu Datenkorruption führen kann. Ist in der Version 9.1.6 (und 9.2.1) gefixt. Dummerweise <i>muß aber jede Datenbank, die auch nur einmal mit 9.1.5 gestartet wurde, gefixt werden</i>, weil es sonst zu <b>Datenkorruption</b> kommen kann.</p>

<p>Schlimmer: <b>die kaputte Version 9.1.5 wird aktuell mit precise-security in Ubuntu ausgeliefert und war für ca. ein Dutzend Tage in wheezy!</b></p>

<p>Nach dem Upgrade auf 9.1.6 gestaltet sich das Fixen wie folgt, als Superuser:</p><ul>
<li>Die <code>/etc/postgresql/9.1/main/postgresql.conf</code> editieren: die Konfigurationseinstellungen (ggfs. erst hinzufügen) <code>vacuum_freeze_table_age = 0</code> und <code>vacuum_cost_delay = 50</code> setzen</li>
<li>Die Datenbank stoppen: <code>/etc/init.d/postgresql stop</code></li>
<li>Prüfen, ob <code>ps ax | fgrep postgres</code> wirklich nix mehr zurückliefert</li>
<li>Die Datenbank starten: <code>cleanenv - /etc/init.d/postgresql start</code></li>
<li>Ggfs. alle Anwendungen, die PostgreSQL (dauerhaft) benutzen, wie apache2 (Evolvis) und tomcat6 (Domisol) neu starten</li>
<li>Zum Systemuser wechseln – <code>su - postgres</code> – und vernünftige Sprache auswählen: Debian <code>export LC_ALL=C.UTF-8</code> Ubuntu <code>export LC_ALL=C</code></li>
<li>Alle Indicēs regenerieren: <code>reindexdb -a</code></li>
<li>Staubsaugen: <code>vacuumdb -F -z -a</code> (optional noch mit <code>-v</code> zum mehr (zu viel) sehen)</li>
<li>Den PostgreSQL-User wieder verlassen: <code>exit</code></li>
<li>Die beiden Konfigurationsänderungen von oben wieder rückgängig machen</li>
<li>Falls gewünscht, die Änderungen aktivieren: <code>cleanenv - /etc/init.d/postgresql reload</code></li>
</ul>

<p>Ich hab’ das mal für alle EvolvisForge- und tarent-activity-Maschinen gemacht, aber eure Desktops und so aktualisiert ihr bitte selber, wenn auch nur <i>die Chance besteht, daß mal ein 9.1.5 oder 9.2.0 installiert war</i>!</p>
----
ID: evo-57
Date: 15.01.2013 12:28:35
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: How to find out when to a git repository was last committed?
Tag: work debian

<pre>git log -n 1 --all --full-history --pretty=format:'%cD'</pre>

<p>This should™ scan all branches, take the chronologically last commit and output its committer date. Still doesn’t take into account git-receive-pack times, but we can just look at the mtime of the <i>projectname</i><tt>-commits@lists.</tt><i>forgename</i> mailing list for that.</p>
----
ID: evo-58
Date: 05.07.2013 13:09:12
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Send Alt-SysRq-* to virt-manager guest using virsh
Tag: work debian

<p><code>virsh send-key guestname KEY_LEFTALT KEY_SYSRQ KEY_H</code></p>

<p>This doesn’t work in virt-manager, but the virsh CLI tool is just fine.</p>

<p>PS: <a href="http://packages.debian.org/zerofree">zerofree</a> rocks! And can be installed in <a href="http://grml.org/">Grml</a> 2011.05 just finely.</p>
----
ID: evo-66
Date: 04.07.2013 09:15:09
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Fun with ssh pubkey auth
Tag: work debian

<p>Okay, so imagine this: you just generated an SSH RSA key and threw its public part on system B into ~foo/.ssh/authorized_keys and its private part on system A into ~bar/.ssh/id_rsa but can’t login. Why?</p>

<p>Automated processes (Jenkins *cough*) often need you to ssh(1) manually once, to accept the remote host’s server key. Do that.</p>

<p>The id_rsa file on system A must be owned by the user bar and chmod 0600 or 0400 (similarily, the .ssh directory has strict permission checks, and everything in the path until there). Check those.</p>

<p>And, the most surprising one of the day: if there’s an id_rsa.pub it <i>will</i> be used for offering a key to the remote host (B) <b>even if it does not match the secret key</b>. Deleting A:~bar/.ssh/id_rsa.pub apparently makes OpenSSH generate the public part from the secret key each time (or just put the correct pubkey there), but if one’s there, it seems to like to use them. (That was the only part of this post that was news to even me, of course ☺)</p>

<p>And, as bottom line: hello to Planet Debian from “mirabilos at work”, too. I’ll occasionally tag posts so they show up here, if I think they’re of interest, since I’m doing Debian work at the dayjob, too.</p>
----
ID: evo-68
Date: 29.07.2013 12:51:14
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: SSD
Tag: work debian

<p>Following <a href="https://wiki.debian.org/SSDOptimization">the Wiki</a> I put “discard” entries into my fstab(5) for swap (but not / as it’s suggested to use fstrim instead, and I had noatime for /boot and relatime for / already) and changed the scheduler. What wasn’t written there was to set vm.swappiness=0 in sysctl.d/local.conf *shrug* but it helps.</p>

<p>What they also didn't mention:</p>

<p><code>mount -t tmpfs swap /var/cache/apt/archives</code></p>

<p>And in sid, which my dayjob-laptop is running, APT _finally_ creates the missing “partial/” subdirectory itself. Thanks!</p>

<p>I had the filesystems already created, so I changed the ext options with tune2fs:</p>

<pre>tune2fs -E stride=1024,stripe_width=1024 /dev/sda2 # 1 KiB blocks: /boot
tune2fs -E stride=256,stripe_width=256 /dev/sda4   # 4 KiB blocks: /</pre>

<p>I wonder how well that works. I also did _not_ manage to find out my device’s flash block size (search engine fodder: erase block size), so I assumed 1 MiB (also used for partition alignment already) as worst-case scenario. Input welcome on how to find *that* out.</p>
----
ID: evo-77
Date: 03.08.2013 21:10:39
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Nicht Hardlink, sondern…?
Tag: work debian

<p><a href="https://www.mirbsd.org/wtf.cgi?TANSTA">TANSTA</a> “softlink”. <a href="https://www.mirbsd.org/wtf.cgi?ITYM">ITYM</a>: <a href="https://www.mirbsd.org/man7/symlink">symlink(7)</a></p>

<p>Actually, there’s “link” (also “hardlink”) and “symbolic link” (short “symlink”). (Oh, and reparse points, but let’s not get there, lest we mention *.lnk files…)</p>

<p>Inspired by a posting on the <a href="http://packages.debian.org/source/sid/klibc">klibc</a> mailing list.</p>
----
ID: evo-80
Date: 12.08.2014 11:55:07
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: iCalender and timezones
Tag: work debian

<p>Okay. I just created three events at tomorrow 10:00 CEST (08:00 UTC), on three different accounts on the very same Debian Lenny machine. All three use nxclient to log into KDE 3, with Kontact/KDEPIM Version 1.2.9 (enterprise35 20131030.a834355).</p>

<p>Then, I looked at the event invitations (METHOD:REQUEST BEGIN:VEVENT) in a simple eMail program (alpine). What I got made me beg to differ:</p>

<p><code>$ fgrep -e DTSTAMP -e CREATED -e UID -e LAST-MODIFIED -e SUMMARY -e DTSTART -e DTEND s?</code></p>

<p>s2:DTSTAMP:20140812T<b style="color:green">11</b>4542<b style="color:green">Z</b><br />
s2:CREATED:20140812T<b style="color:green">11</b>4541<b style="color:green">Z</b><br />
s2:UID:libkcal-1345193151.365<br />
s2:LAST-MODIFIED:20140812T<b style="color:green">11</b>4541<b style="color:green">Z</b><br />
s2:SUMMARY:sk2<br />
s2:DTSTART:20140813T<b style="color:green">080000Z</b><br />
s2:DTEND:20140813T<b style="color:green">100000Z</b></p>

<p>s3:DTSTAMP:20140812T<b style="color:red">13</b>4551<b style="color:red">Z</b><br />
s3:CREATED:20140812T<b style="color:red">13</b>4550<b style="color:red">Z</b><br />
s3:UID:libkcal-579827798.725<br />
s3:LAST-MODIFIED:20140812T<b style="color:red">13</b>4550<b style="color:red">Z</b><br />
s3:SUMMARY:sk3<br />
s3:DTSTART:20140813T<b style="color:red">100000Z</b><br />
s3:DTEND:20140813T<b style="color:red">120000Z</b></p>

<p>s4:DTSTAMP:20140812T<b style="color:red">13</b>4559<b style="color:red">Z</b><br />
s4:CREATED:20140812T<b style="color:red">13</b>4558<b style="color:red">Z</b><br />
s4:UID:libkcal-743876151.470<br />
s4:LAST-MODIFIED:20140812T<b style="color:red">13</b>4558<b style="color:red">Z</b><br />
s4:SUMMARY:sk4<br />
s4:DTSTART:20140813T<b style="color:red">100000Z</b><br />
s4:DTEND:20140813T<b style="color:red">120000Z</b></p>

<p>I should mention that I created the events at roughly 13:45 CEST today (11:45 UTC), and the system timezone on the box as well as the “Time &amp; Date” zone in the Kontact settings are all “Europe/Berlin”.</p>

<p>To add insult to injury: the calendar view on the accounts that created the event all <i>do</i> show it for tomorrow, 10:00 local time.</p>

<p>I cannot possibly imagine how this could go wrong, seeing as those are all on the same machine…</p>

<p>WTF is going on here?</p>

<hr />

<p>Update: <code>.kde/share/config/korganizerrc</code> had <code>TimeZoneId</code> wrong. I had to change a <em>different</em> timezone (such as Europe/Bratislava), hit the OK button, confirm to “Keep Times”, <em>then</em> re-open the settings dialogue and change back to Europe/Berlin, for it to work.</p>
----
ID: evo-90
Date: 04.09.2014 08:17:43
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: git rebasing considered harmful
Tag: work debian

<p><code>git rebase</code> is problematic (from a version control system user point of view) because it rewrites history. We all knew that.</p>

<p>But did you know that <code>git pull --rebase</code>, commonly used before a <code>git push</code>, can also be harmful, destroy history, and surprise users in a negative way?</p>

<pre>10:08⎜&lt;Beuc:#fusionforge&gt; Lo-lan-do, we must have committed at the same time :)  First time I rebase and my commit disappear ;)
10:11⎜«Lo-lan-do:#fusionforge» So who won?
10:11⎜«Lo-lan-do:#fusionforge» Aha, I did :-)</pre>

<p>This does fit git’s model of managing patches and tracking content, but is just irresponsible for a version control system. (Also, imagine incensed contributors whose commits just vanish.) So, danger, beware of using git rebasing when you use git as distributed version control system!</p>

<p>In a related way: merge commits are <strong>good</strong>. Especially when merging between, into or from feature branches. (A friend had his <code>.gitconfig</code> set up to default to rebasing… ugh.) So there should have been <em>one</em> place where you used rebase: to avoid merge commits when people work on the same repository at the same time (but, ideally, on different files). Those were mostly annoying. But, as you can see above, the alternatives are even worse…</p>
----
ID: evo-93
Date: 08.10.2014 13:57:43
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: PSA: #shellshock still unfixed except in Debian unstable, testing, *buntu LTS
Tag: work debian

<p>I just installed, for <a href="http://www.tarent.de/">work</a>, Hanno Böck’s <a href="https://github.com/hannob/bashcheck">bashcheck</a> utility on our monitoring system, and watched all¹ systems go blue.</p>

<p>① All but two. One is not executing remote scripts from the monitoring for security reasons, the other is my desktop which runs Debian “sid” (unstable).</p>

<p>(Update, 2014-10-20: jessie, precise, trusty are also green now.)</p>

<p>This means that all those distributions still have unfixed #shellshock bugs.</p>

<ul>
 <li style="color:maroon">lenny (with Md’s packages): bash (<b>3.2-4.2</b>) = 3.2.53(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:maroon">squeeze (LTS): bash (<b>4.1-3+deb6u2</b>) = 4.1.5(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:maroon">wheezy (stable-security): bash (<b>4.2+dfsg-0.1+deb7u3</b>) = 4.2.37(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li>
  <li>CVE-2014-6278 (lcamtuf bug #2)</li></ul></li>
 <li style="color:maroon">jessie (testing): bash (<b>4.3-10</b>) = 4.3.27(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li>
  <li>CVE-2014-6278 (lcamtuf bug #2)</li></ul></li>
 <li style="color:green">sid (unstable): bash (<b>4.3-11</b>) = 4.3.30(1)-release<ul>
  <li>none</li></ul></li>
 <li style="color:red">CentOS 5.5: bash-<b>3.2-24.el5</b> = 3.2.25(1)-release<ul>
  <li>extra-vulnerable (function import active)</li>
  <li>CVE-2014-6271 (original shellshock)</li>
  <li>CVE-2014-7169 (taviso bug)</li>
  <li>CVE-2014-7186 (redir_stack bug)</li>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:red">CentOS 5.6: bash-<b>3.2-24.el5</b> = 3.2.25(1)-release<ul>
  <li>extra-vulnerable (function import active)</li>
  <li>CVE-2014-6271 (original shellshock)</li>
  <li>CVE-2014-7169 (taviso bug)</li>
  <li>CVE-2014-7186 (redir_stack bug)</li>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:maroon">CentOS 5.8: bash-<b>3.2-33.el5_10.4</b> = 3.2.25(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:maroon">CentOS 5.9: bash-<b>3.2-33.el5_10.4</b> = 3.2.25(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:maroon">CentOS 5.10: bash-<b>3.2-33.el5_10.4</b> = 3.2.25(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:maroon">CentOS 6.4: bash-<b>4.1.2-15.el6_5.2.x86_64</b> = 4.1.2(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:maroon">CentOS 6.5: bash-<b>4.1.2-15.el6_5.2.x86_64</b> = 4.1.2(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:maroon">lucid (10.04): bash (<b>4.1-2ubuntu3.4</b>) = 4.1.5(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li></ul></li>
 <li style="color:maroon">precise (12.04): bash (<b>4.2-2ubuntu2.5</b>) = 4.2.25(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li>
  <li>CVE-2014-6278 (lcamtuf bug #2)</li></ul></li>
 <li style="color:red">quantal (12.10): bash (<b>4.2-5ubuntu1</b>) = 4.2.37(1)-release<ul>
  <li>extra-vulnerable (function import active)</li>
  <li>CVE-2014-6271 (original shellshock)</li>
  <li>CVE-2014-7169 (taviso bug)</li>
  <li>CVE-2014-7186 (redir_stack bug)</li>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li>
  <li>CVE-2014-6278 (lcamtuf bug #2)</li></ul></li>
 <li style="color:maroon">trusty (14.04): bash (<b>4.3-7ubuntu1.4</b>) = 4.3.11(1)-release<ul>
  <li>CVE-2014-6277 (lcamtuf bug #1)</li>
  <li>CVE-2014-6278 (lcamtuf bug #2)</li></ul></li>
</ul>

<p>I don’t know if/when all distributions will have patched their packages ☹ but thought you’d want to know the hysteria isn’t over yet…</p>

<p>… however, I hope you were not stupid enough to follow the advice of <a href="https://shellshocker.net/">this site</a> which suggests you to download some random file over the ’net and execute it with superuser permissions, unchecked. (I think the Ruby people were the first to spread this extremely insecure, stupid and reprehensible technique.)</p>

<p><b>Updates:</b></p><ul>
 <li style="color:blue">rsc points out that CentOS only supports 5.«latest» and 6.«latest», and paying RHEL get 5.«x».«y» but only occasionally. We updated one of the two systems in question and shut the other down due to lack of use.</li>
 <li style="color:green">trusty (14.04): bash (<b>4.3-7ubuntu1.5</b>) = 4.3.11(1)-release<ul>
  <li>none</li></ul></li>
 <li>Yes, comments on this blog are disabled; mail ｔ．ｇｌａｓｅｒ＠ｔａｒｅｎｔ．ｄｅ for feedback.</li>
 <li style="color:blue">Since I was asked (twice): the namespace patches by Florian Weimer protect from <strong>most</strong> exploits. The bugs are, nevertheless, present:<pre>
root@debian-wheezy:~ # env 'BASH_FUNC_foo()=() { x() { _; }; x() { _; } &lt;&lt;'"$(perl -e '{print "A"x1000}'); }" bash -c :
Segmentation fault
139|root@debian-wheezy:~ # dmesg | tail -1
[3121102.362274] bash[1699]: segfault at dfdfdfdf ip 00000000f766df36 sp 00000000ffe90b34 error 4 in libc-2.13.so[f75ee000+15d000]
 </pre></li>
 <li>To one eMail sender: If you do not understand why a CGI or something else could invoke a shell, or what a segmentation fault trap is, <strong>do not bother me</strong>. Especially not in <em>that</em> tone.</li>
 <li style="color:blue">To another eMail sender: Yes, quantal is end of life. It’s also upgraded. First and last time I ever used *buntu’s “do-release-upgrade”. Broke kernel and GRUB, and upgraded to saucy. I manually “apt-get --purge dist-upgrade”d to trusty (went surprisingly well).</li>
 <li style="color:green">precise (12.04): bash (<b>4.2-2ubuntu2.6</b>) = 4.2.25(1)-release<ul>
  <li>none</li></ul></li>
 <li style="color:green">jessie (testing): bash (<b>4.3-11</b>) = 4.3.30(1)-release<ul>
  <li>none</li></ul></li>
 <li><b>Update 27.10.2014:</b> Clearly, distributions are not fixing the lcamtuf bug series (Debian stable, CentOS), believing that the affix patch makes them invulnerable, while it just removes the most common/popular/exposed attack vector. Sad story.</li>
</ul>

<p>Thanks to <span style="color:#CC0000;border:1px solid #CC0000;padding:1px">↳ tarent</span> for letting me do this work during $dayjob time!</p>
----
ID: evo-113
Date: 30.10.2014 14:17:11
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Tip of the day: bind tomcat7 to loopback i/f only
Tag: work debian

<p>We already edit <code>/etc/tomcat7/server.xml</code> after installing the <code>tomcat7</code> Debian package, to get it to talk AJP instead of HTTP (so we can use <code>libapache2-mod-jk</code> to put it behind an Apache 2 httpd, which also terminates SSL):</p>

<p>We already comment out the block…</p>
<pre>    &lt;Connector port="8080" protocol="HTTP/1.1"
               connectionTimeout="20000"
               URIEncoding="UTF-8"
               redirectPort="8443" /&gt;</pre>
<p>… and remove the comment chars around the line…</p>
<pre>    &lt;Connector port="8009" protocol="AJP/1.3" redirectPort="8443" /&gt;</pre>
<p>… so all we need to do is edit that line to make it look like…</p>
<pre>    &lt;Connector <span style="color:green">address="127.0.0.1" </span>port="8009" protocol="AJP/1.3" redirectPort="8443" /&gt;</pre>
<p>… and we’re all set.</p>

<p>(Your apache2 vhost needs a line <tt>JkMount /?* ajp13_worker</tt> and everything Just Works™ with the default configuration.)</p>

<p>Now, tomcat7 is only accessible from localhost (Legacy IP), and we don’t need to firewall the AJP (or HTTP/8080) port. Do make sure your Apache 2 access configuration works, though ☺</p>
----
ID: evo-119
Date: 19.11.2014 14:18:13
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Valid UTF-8 but invalid XML
Tag: work debian

<p>Another PSA: something surprising about XML.</p>

<p>As you might all know, XML must be valid UTF-8 (or UTF-16 (or another encoding supported by the parser, but one which yields valid Unicode codepoints when read and converted)). Some characters, such as the ampersand ‘&amp;’, must be escaped (“&amp;&#035;38;” or “&amp;&#035;x26;”, although “&amp;amp;” may also work, depending on the domain) or put into a CDATA section (“&lt;![CDATA[&amp;]]&gt;”).</p>

<p>A bit surprisingly, a literal backspace character (ASCII 08h, Unicode U+0008) is not allowed in the text. I <a href="https://bugzilla.gnome.org/show_bug.cgi?id=739574">filed a bugreport against libxml2</a>, asking it to please encode these characters.</p>

<p>A bit <a href="http://stackoverflow.com/a/5742563/2171120">more research</a> followed. Surprisingly, there are <a href="http://www.w3.org/TR/2000/REC-xml-20001006#NT-Char">characters</a> that are not valid in XML “documents” in any way, not even as entities or in CDATA sections. (xmlstarlet, by the way, errors out somewhat nicely for an unescaped literal or entity-escaped backspace, but behaves absolutely hilarious for a literal backspace in a CDATA section.) Basically, XML contains a whitelist for the following Unicode codepoints:</p><ul>
 <li>U+0009</li>
 <li>U+000A</li>
 <li>U+000D</li>
 <li>U+0020‥U+D7FF</li>
 <li>U+E000‥U+FFFD</li>
 <li>U-00010000‥U-0010FFFF</li>
</ul><p>Additionally, a certain number of codepoints is discouraged: U+007F‥U+0084 (IMHO wise), U+0086‥U+009F (also wise, but why allow U+0085?), U+FDD0‥U+FDEF (a bit surprisingly, but consistent with disallowing the backspace character), and the last two codepoints of every plane (U+FFFE and U+FFFF were already disallowed, but U-0001FFFE, U-0001FFFF, …, U-0010FFFF weren’t; this is extremely wise).</p>

<p>The <a href="http://blog.mark-mclaren.info/2007/02/invalid-xml-characters-when-valid-utf8_5873.html">suggestion</a> seems to be to just strip these characters silently from the XML “document”.</p>

<p>I’m a bit miffed about this, as I don’t even use XML directly (I’m extending a PHP “webapplication” that is a SOAP client and talks to a Java™ SOAP-WS) and would expect this to preserve my strings, but, oh my. I’ve forwarded the suggestion to just strip them silently to the libxml2 maintainers in the aforementioned bug report, for now, and may even hack that myself (on customer-paid time). More robust than hacking the PHP thingy to strip them first, anyway – I’ve got no control over the XML after all.</p>

<p>Sharing this so that more people know that not all UTF-8 is valid in XML. Maybe it saves someone else some time. (Now wondering whether to address this in my <tt>xhtml_escape</tt> shell function. Probably should. Meh.)</p>
----
ID: evo-122
Date: 12.12.2014 09:04:27
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Tip of the day: don’t use --purge when cross-grading
Tag: work debian

<p>A surprise to see my box booting up with the default GRUB 2.x menu, followed by “cannot find a working init”.</p>

<p>What happened?</p>

<p>Well, grub:i386 and grub:x32 are distinct packages, so APT helpfully decided to purge the GRUB config. OK. Manual boot menu entry editing later, re-adding “GRUB_DISABLE_SUBMENU=y” and “GRUB_CMDLINE_LINUX="syscall.x32=y"” to /etc/default/grub, removing “quiet” again from GRUB_CMDLINE_LINUX_DEFAULT, and uncommenting “GRUB_TERMINAL=console”… and don’t forget to “sudo update-grub”. There. This should work.</p>

<p>On the plus side, nvidia-driver:i386 seems to work… but not with boinc-client:x32 (why, again? I swear, its GPU detection has been driving me nuts on &gt;¾ of all systems I installed it on, already!).</p>

<p>On the minus side, I now have to figure out why…</p>

<pre>tglase@tglase:~ $ sudo ifup -v tap1
Configuring interface tap1=tap1 (inet)
run-parts --exit-on-error --verbose /etc/network/if-pre-up.d
run-parts: executing /etc/network/if-pre-up.d/bridge
run-parts: executing /etc/network/if-pre-up.d/ethtool
ip addr add 192.168.0.3/255.255.255.255 broadcast 192.168.0.3   peer 192.168.0.4  dev tap1 label tap1
Cannot find device "tap1"
Failed to bring up tap1.</pre>

<p>… this happens. This used to work before the cktN kernels.</p>
----
ID: evo-124
Date: 05.01.2015 12:56:48
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Tip of the day: prevent iceweasel from mkdir ~/Desktop
Tag: work debian

<p>If you’re a Unix person instead of e.g. a Microsoft® Windows® person, you’ve probably been annoyed by Iceweasel (or Mozilla™ Firefox®) creating a <tt>~/Desktop</tt> directory, among others (things like <tt>~/Downloads</tt>).</p>

<p>Here’s a quick fix I found somewhere in the ’net:</p>

<pre>
mkdir -p -m0700 ~/.config
cat &gt;~/.config/user-dirs.dirs &lt;&lt;&#039;EOF&#039;
XDG_DESKTOP_DIR=&quot;$HOME/&quot;
XDG_DOCUMENTS_DIR=&quot;$HOME/&quot;
XDG_DOWNLOAD_DIR=&quot;$HOME/&quot;
XDG_MUSIC_DIR=&quot;$HOME/&quot;
XDG_PICTURES_DIR=&quot;$HOME/&quot;
XDG_PUBLICSHARE_DIR=&quot;$HOME/&quot;
XDG_TEMPLATES_DIR=&quot;$HOME/&quot;
XDG_VIDEOS_DIR=&quot;$HOME/&quot;
EOF
</pre>

<p>Upon next start, Iceweasel (and other XDG-compliant applications) will throw stuff into <tt>~/</tt> instead.</p>
----
ID: evo-127
Date: 16.01.2015 14:26:37
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Debian/m68k hacking weekend commencing soonish
Tag: work debian

<p>As I said, I did not certain events that begun with “lea” and end with “ing” prevent me from organising a Debian/m68k hack weekend. Well, that weekend is now.</p>

<p>I’m too unorganised, and I spent too much time in the last few evenings to organise things so I built up a sleep deficit already ☹ and the feedback was slow. (But so are the computers.) And someone I’d have loved to come was hurt and can’t come.</p>

<p>On the plus side, several people I’ve long wanted to meet IRL are coming, either already today or tomorrow. I hope we all will have a lot of fun.</p>

<p style="font-size:x-small">Legal disclaimer: “Debian/m68k” is a port of Debian™ to m68k. It used to be official, but now isn’t. It belongs to debian-ports.org, which may run on DSA hardware, but is not acknowledged by Debian at large, unfortunately. <i>Debian</i> is a registered trademark owned by Software in the Public Interest, Inc.</p>
----
ID: evo-131
Date: 18.01.2015 16:16:51
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Debian/m68k hacking weekend cleanup
Tag: work debian

<p>OK, time to clean up <a href="http://www.tarent.de/" style="text-decoration:none"><span style="color:#CC0000;background-color:#FFFFF;border:1px solid #CC0000;padding:1px">↳ tarent</span></a>  so people can work again tomorrow.</p>

<p>Not much to clean though (the participants were nice and cleaned up after themselves ☺), so it’s mostly putting stuff back to where it belongs. Oh, and drinking more of the cool Belgian beer Geert (Linux upstream) brought ☻</p>

<p>We were productive, reporting and fixing kernel bugs, fixing hardware, swapping and partitioning discs, upgrading software, getting buildds (mostly Amiga) back to work, trying X11 (kdrive) on a bare metal Atari Falcon (and finding a window manager that works with it), etc. – I hope someone else writes a report; for now we have a photo and a screenshot (made with trusty <a href="https://www.mirbsd.org/man1/xwd">xwd</a>). Watch the <tt>debian-68k</tt> mailing list archives for things to come.</p>

<p>I think that, issues with electric cars aside, everyone liked the food places too ;-)</p>
----
ID: evo-133
Date: 24.02.2015 16:02:14
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Java™, logging and the locale
Tag: work debian

<p>A coworker and I debugged a fascinating problem today.</p>

<p>They had a tomcat7 installation with a couple of webapps, and one of the bundled libraries was logging in German. Everything else was logging in English (the webapps themselves, and the things the other bundled libraries did).</p>

<p>We searched around a bit, and eventually found that the wrongly-logging library (something jaxb/jax-ws) was using, after unravelling another few layers of “library bundling another library as convenience copy” (gah, Java!), <code>com.sun.xml.ws.resources.WsservletMessages</code> which contains quite a few <code>com.sun.istack.localization.Localizable</code> members. Looking at the other classes in that package, in particular <code>Localizer</code>, showed that it defaults to the <code>java.util.Locale.getDefault()</code> value for the language.</p>

<p>Which is set from the environment.</p>

<p>Looking at <code>/proc/</code><i>pid-of-JVM-running-tomcat7</i><code>/environ</code> showed nothing, “of course”. The system locale was, properly, set to English. (We mostly use <code>en_GB.UTF-8</code> for better paper sizes and the metric system (unless the person requesting the machine, or the admin creating it, still likes the system to speak German *shudder*), but that one still had <code>en_US.UTF-8</code>.)</p>

<p>Browsing the documentation for <code>java.util.Locale</code> proved more fruitful: it also contains a <code>setDefault</code> method, which sets the new “default” locale… JVM-wide.</p>

<p>Turns out another of the webapps used that for some sort of internal localisation. Clearly, the containment of tomcat7 is incomplete in this case.</p>

<p>Documenting for the larger ’net, in case someone else runs into this. It’s not as if things like this would be showing up in the USA, where the majority of development appears to happen.</p>
----
ID: evo-137
Date: 26.02.2015 14:24:50
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: tomcat7 init script is asynchronous
Tag: work debian

<p><a href="https://www.mirbsd.org/wtf.cgi?q=TIL">TIL</a>: the init script of <code>tomcat7</code> in Debian is asynchronous.</p>

<p>For some piece of software, our rollout (install and upgrade) process works like this:</p>

<ul>
 <li><code>service tomcat7 stop</code></li>
 <li><code>rm -rf /var/lib/tomcat7/webapps/appname{,.war}</code></li>
 <li><code>cp newfile.war /var/lib/tomcat7/webapps/appname.war</code></li>
 <li><code>service tomcat7 start</code> # ← here</li>
 <li><code>service tomcat7 stop</code></li>
 <li>edit some config files under <code>/var/lib/tomcat7/webapps/appname/WEB-INF/</code></li>
 <li><code>service tomcat7 start</code></li>
</ul>

<p>The first tomcat7 start “here” is just to unzip the *.war files. For some reason, people like to let tomcat7 do that.</p>

<p>This failed today; there were two webapps. Manually unzipping it also did not work for some reason.</p>

<p>Re-doing it, inserting a <code>sleep 30</code> after the “here”, made it work.</p>

<p>In a perfect world, initscripts only return when the service is running, so that the next one started in a nice sequential (not parallel!) init or manual start sequence can do what it needs to, assuming the previous command has fully finished.</p>

<p>In this perfect world, those who <em>do</em> wish for faster startup times use a different init system, one that starts things in parallel, for example. Even there, dependencies will wish for the depended-on service to be fully running when they are started; even more so, since the delays between starting things seem to be less for that other init system.</p>

<p>So, this is not about the init system, but about the init script; a change that would be a win-win for users of both init schemes.</p>

<p><b>Update:</b> Someone already contacted me with feedback: they suggested to wait until the “shutdown port” is listened on by tomcat7. We’ll look at this later. In the meantime, we’re trying to also get rid of the “config (and logs) in webapps/” part…</p>

<hr />

<p>PS: If someone is interested in an init script (Debian/LSB sysvinit, I made the effort to finally learn that… some months before the other system came) that starts Wildfly (formerly known as JBoss AS) synchronously, waiting until all *.?ar files are fully “deployed” before returning (though with a timeout in case it won’t ever finish), just <a href="mailto:t.glaser@tarent.de">ask</a> (maybe it will become a dialogue, in which we can improve it together). (We have two versions of it, the more actively maintained one is in a secret internal project though, so I’d have to merge it and ready it for publication though, plus the older one is AGPLv3, the newer one was relicenced to <a href="https://www.mirbsd.org/MirOS-Licence.htm">a BSDish licence</a>.)</p>
----
ID: evo-140
Date: 26.02.2015 16:09:23
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: tomcat7 log encoding
Tag: work debian

<p><a href="https://www.mirbsd.org/wtf.cgi?q=TIL">TIL</a>: the encoding of the <code>catalina.out</code> file is dependent on the system locale, using standard Debian wheezy <code>tomcat7</code> package.</p>

<p>Fix for ‘?’ instead of umlauts in it:</p>

<pre>
cat &gt;&gt;/etc/default/tomcat7 &lt;&lt;EOF
LC_CTYPE=C.UTF-8
export LC_CTYPE
EOF
</pre>

<p>My “problem” here is that I have the system locale be the “C” locale, to get predictable behaviour; applications that need it can set a locale by themselves. (Many don’t bother with POSIX locales and use different/separate means of determining especially encoding, but possibly also <a href="https://www.mirbsd.org/wtf.cgi?q=i18n">i18n</a>/<a href="https://www.mirbsd.org/wtf.cgi?q=l10n">l10n</a>. But it seems the POSIX locales are getting more and more used.)</p>

<p><b>Update:</b> There is also adding <tt>-Dfile.encoding=UTF-8</tt> to <tt>$JAVA_OPTS</tt> which seems to be more promising: no fiddling with locales, no breakage if someone defined <tt>LC_ALL</tt> already, and it sets <em>precisely</em> what it should set (the encoding) and nothing else (since the encoding does not need to correlate to any locale setting, why should it).</p>
----
ID: evo-150
Date: 05.03.2015 14:07:10
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: I have to give you that one
Tag: work debian

<p>After seeing what the Wildfly (formerly JBoss AS) and Liferay combo does to <code>/tmp</code>, and somewhat attempting to fix it, I saw <code>JVM_TMP</code> in the Debian tomcat7 init script and thought, oh no, not another one.</p>

<p>Is that even safe, what they do here, or is that a possibility to instantly pwn?</p>

<p>The net is full of literature for how to obtain temporary files and directories, but there is nothing about how to reliably obtain paths under <code>/tmp</code> or, more generally, directories not just writable for one single user (think the g+w thing that got FusionForge CVE-2013-1423).</p>

<p>The scenario here is: I am root, and I want to start something as another user, and pass it a stable path, such as <code>/tmp/liferay</code>. So I can just <code>mkdir /tmp/liferay || die; chown thatuser /tmp/liferay</code> and, in the “stop” process, <code>rm -rf /tmp/liferay</code>, right? (Of course not. Also, bad example, as the liferay thing can also be started as thatuser, and our devs regularily need to do that, the init script is there just for the admin convenience and reboot-safety. But I still am interested if there is a secure way to achieve this.)</p>

<p>The tomcat7 scenario is “trivial”: on That Other Init System™, it would just get its private /tmp declared in the .service file, and good is, no more hassle. That's one I have to give you. (No idea if this is actually shipped in jessie. Our production systems run wheezy anyway, so there is not even the slightest bit of temptation. Plus, it would not solve the liferay issue, see above. Still, a point for going into the right direction.)</p>

<p>The idea here is the same. It creates a directory on start and tears it down on stop. If there was nothing to do on start, the init script could just use <code>mktemp -d</code>. Heck, maybe it still should, but it would need to note down, and communicate to the stop instance, the actual name used. What a drag…</p>

<p>This is something I see popping up from time to time. I want to use stable paths for SSH session multiplexing control sockets in my ssh_config(5) file, but have them on tmpfs (Linux) or mfs (BSD) so they get properly removed on reboot. No Unix traditionally has per-user temporary directories that are clean <em>and</em> created after reboot. (Adjusting the paths is trivial once you have them.) Android has it worse, what with not having a world-writable tmp directory, which the shell needs e.g. for here documents; there are two components here, to have a directory the current user can write to, and to know its location. Some fail at the first, some at the second, some at both, and the classic /tmp is not the cure, as we have seen. (But if you ever see mksh erroring out due to lack of write permissions somewhere (including <code>/sqlite_stmt_journals</code> which used to be it) as non-root on Android, or even as root, set <tt>TMPDIR</tt> to something writable; it's tracked, so the change gets active immediately.)</p>
----
ID: evo-154
Date: 17.04.2015 13:54:55
Author: t.glaser@tarent.de (EvolvisForge blog)
Title: Tricks for using Googlemail at work
Tag: work debian

<p>For these who similarily suffer from having to use Googlemail at work. If anyone else has more of these, please do share.</p>

<h3>Deactivate the spamfilter</h3>

<p>The site admins can do that. Otherwise, you <em>will</em> have work-relevant eMails, for example from your own OTRS system, end up in Spam (where you don’t see it, as their IMAP sucks) and deleted without asking 30 days later. (AIUI, the only way to get eMails actually deleted from Google…)</p>

<h3>Do not use their SMTP service</h3>

<p>Use your own outgoing MTA. This brings back the, well, not feature but should-have-been-granted-but-Google-doesn’t-do-it-anyway that, when you write to a mailing list, you also get your own messages into your own INBOX.</p>

<h3>Calendars…</h3>

<p>I have no solutions for this. I stopped using the Googlemail calendars because they didn’t think it a problem that, when I accept an invitation in Kontact (KDEPIM as packaged in Debian sid), the organiser of the calendar item in the <em>sender’s calendar</em> (for which I do not have write permissions) changes to me (so the actual meeting organiser cannot change anything afterwards) and/or calendar items get doubled. I now run a local <tt>uw-imapd</tt> (forward-ported to sid by means of a binNMU) for sent-mail folders etc. and a local iCalendar directory for calendars.</p>
----
Date: 27.08.2015 14:12
Author: tg@
Title: Go enjoy shell
Tag: debian fun pcli

<p class="boxhead">Dimitri, I personally enjoy shell…</p><div class="boxtext">
 <pre>
tglase@tglase:~ $ x=車賈滑豈更串句龜龜契金喇車賈滑豈更串句龜龜契金喇
tglase@tglase:~ $ echo ${x::12}
車賈滑豈更串句龜龜契金喇
tglase@tglase:~ $ printf '%s\n' 'import sys' 'print(sys.argv[1][:12])' &gt;x.py
tglase@tglase:~ $ python x.py $x
車賈滑豈
 </pre>
</div><p class="boxfoot">… much more than Python, actually. (Python is
 <em>the</em> language in which you <em>do not</em> want to write code
 dealing with strings, due to UnicodeDecodeError and all; even py3k is
 not much better.)</p>
<p>I would have commented on your post if <a
 href="http://blog.surgut.co.uk/2015/08/go-enjoy-python3.html">it</a>
 allowed doing so without getting a proprietary Google+ account.</p>
----
Date: 27.10.2015 16:29
Author: tg@
Title: Oktobr Rain
Tag: fun twitxr

<p>The title is a pun on “November Rain” and “Красный Октябрь” (Red
 Oktober, or nice october)… as a follow-up on my earlier <a
 href="@@RELPATH@@permalinks/wlog-10-tg_e20150428-tg.htm">Sakura</a>
 weblog entry. Again, small images as links to bigger ones:</p>
<p><a href="http://mirsolutions.de/pub/octrainA.jpg"><img
 alt="OR1" src="http://mirsolutions.de/pub/octrain1.jpg" /></a></p>
<p><a href="http://mirsolutions.de/pub/octrainB.jpg"><img
 alt="OR2" src="http://mirsolutions.de/pub/octrain2.jpg" /></a></p>
----
Date: 13.11.2015
Author: tg@
Title: no more Munzee in stats

<p>My <a href="@@RELPATH@@WPtg.htm">waypoint statistics</a> and
 supporting scripts ceased to handle Munzee in any way whatsoever.
 This is because they’re getting ridiculous, especially in amount,
 and loss of play fun due to a too slow “äpp”. This means that my
 figure is now much closer to the real geocaching count, and you
 have to look at two, separate, statpics to get the entire scoop,
 but then, the separation does make it all clearer ☺</p>
<p><a href="http://fish.mirbsd.org/wptg.htm#banners" style="border:0;"><img
 style="border:0;" alt="mirabilos’ Waypoints"
 src="@@RELPATH@@WPtg.png" /></a> • <a style="border:0;"
 href="https://www.munzee.com/m/mirabilos/"><img style="border:0;"
 src="https://www.munzee.com/embed/mirabilos/"
 alt="It’s all about the numbers: Munzee"/></a></p>
----
Date: 28.11.2015 18:42
Author: tg@
Title: FixedMisc [MirOS] for GNU GRUB2
Tag: debian fun news

<p>If you install the <tt>xfonts-base</tt> package from <a
 href="https://www.mirbsd.org/~tg/Debs/debidx.htm">my APT repository</a>
 you now not only get the <tt>FixedMisc [MirOS]</tt> type from <a
 href="@@RELPATH@@about.htm#project">The MirOS Project type foundry</a>
 for the X Window System, but now also for GNU GRUB2:</p>
<!-- RSS stop --><p><img src="http://mirsolutions.de/privat/fmgrub.png"
 alt="FixedMisc [MirOS] for GNU GRUB2 – Screenshot" /></p>
<p>Just add <tt>GRUB_FONT=/usr/share/grub/FixedMisc.pf2</tt>
 to <tt>/etc/default/grub</tt>, make sure gfxterm is enabled
 (usually by commenting out <tt>GRUB_TERMINAL=console</tt> and
 removing the comment sign before <tt>GRUB_GFXMODE=640x480</tt>),
 run <tt>sudo update-grub</tt> and be happy at the next reboot.</p>
<p>The combining and Katakana characters depicted in the above
 screenshot are the result of manual <tt>grub.cfg</tt> editing
 and for demonstration (bragging) purposes <em>only</em>.</p>
<p>The <a href="https://www.mirbsd.org/~tg/Debs/NEWS.rss">RSS
 feed of my APT repository</a> will also contain such news…</p>
----
Date: 13.02.2016 18:10
Author: tg@
Title: The things you find in upstream code…
Tag: archaeology bug pcli rant security snapshot

<p class="boxhead">I had just gotten an eMail from the nightly
 <tt>/etc/security</tt> cronjob that the mailbox from the user
 <tt><i>foo</i>.lock</tt> belongs to the user <tt><i>foo</i></tt>
 (name changed to protect the… innocent? well, I know that guy
 from #OpenBSD on IRC, so… YMMV… anyway). Of course, I wanted to
 change that to exclude mbox lockfiles…</p><div class="boxtext">
 <pre>
	# Mailboxes should be owned by user and unreadable.
	ls -l /var/mail | sed 1d | \
	awk '$3 != $9 \
		{ print "user " $9 " mailbox is owned by " $3 }
 </pre>
</div><p class="boxfoot">… oh wow. Needless to say I fixed that,
 although you <em>must</em> update your stat(1) first; it now
 has a possibility to generate NUL-terminated output (or any
 separator, really) which I used for this. (And no, Schily, I’m
 still of the opinion that NUL termination, even when one has to
 add it to each utility separately, is the better way to go.)</p>
<p>Dear OpenBSD developers, repeat after me:<br />
 <strong>Do n̲o̲t̲ parse ls(1) output!</strong><br />
 Or write 100 lines of it, or something, until it sinks in.</p>
<p>(It can take some writing for it to sink in… just yesternight
 the fanfiction I was reading was at the point where Dolores
 Umbridge uses her Blood Quill on the students. Coincidence.)</p>
----
Date: 13.11.2016 20:28
Author: tg@
Title: “I don’t like computers”
Tag: debian pcli personal rant tip

<p>cnuke@ spotted something on the internet, and shared. Do <a
 href="https://www.happyassassin.net/2016/11/04/i-dont-like-computers/">read
 this, including the comments</a>. It’s so true. (My car is 30 years old, I
 use computers mostly for sirc, lynx and ssh, and I especially do not buy any
 product that needs to be “online” to work.)</p>
<p>Nice parts of the internet, to offset this, though, do exist. IRC as a way
 of cheap (affordable), mostly reliant, communication that’s easy enough to do
 with TELNET.EXE if necessary. Fanfiction; easy proliferation of people’s art
 (literature, in this case). Fast access to documentation and source code;
 OpenBSD’s AnonCVS was a first, nowadays almost everything (not Tom Dickey’s
 projects (lynx, ncurses, xterm, cdk, …), nor GNU bash, though) is on a public
 version control system repository. (Now people need to learn to not rewrite
 history, just commit whatever shit they do, to record thought process, not
 produce the perfect-looking patch.) Livestreams too, I guess, but ever since
 live365.com went dead due to a USA law change on 2016-01-02, it got bad.</p>
----
Date: 08.03.2017 22:00
Author: tg@
Title: Updated Debian packaging example: PHP webapp with dbconfig-common
Tag: debian pcli snippet tip work

<p>Since I use this as base for other PHP packages like <a
 href="https://evolvis.org/projects/simkolab/">SimKolab</a>, I’ve updated <a
 href="@@RELPATH@@permalinks/wlog-10-tg_e20140515-tg.htm">my packaging
 example</a> with:</p><ul>
 <li>PHP 7 support (untested, as I need <tt>libapache2-mod-php5</tt>)</li>
 <li>tons more utility code for you to use</li>
 <li>a class autoloader, with example (build time, for now)</li>
 <li>(at build time) running a PHPUnit testsuite (unless nocheck)</li>
</ul>
<p>The old features (Apache 2.2 and 2.4 support, dbconfig-common, etc.)
 are, of course, still there. Support for other webservers could be
 contributed by <em>you</em>, and I could extend the autoloader to
 work at runtime (using dpkg triggers) to include dependencies as
 packaged in other Debian packages. See, nobody needs “composer”! ☻</p>
<p>Feel free to check it out, play around with it, install it, test it,
 send me improvement patches and feature requests, etc. — it’s <a
 href="https://evolvis.org/plugins/scmgit/cgi-bin/gitweb.cgi?p=shellsnippets/hello-php-world.git">here</a>
 with a mirror at GitHub (since I wrote it myself <em>and</em> the <a
 href="@@RELPATH@@MirOS-Licence.htm">licence</a> is permissive enough
 anyway).</p>
<p>This posting and the code behind it are sponsored by my employer <a
 href="https://www.tarent.de/" style="color:red;">⮡ tarent</a>.</p>
----
Date: 16.03.2017 23:12
Author: tg@
Title: Updates to the last two posts
Tag: bug debian grml news pcli rant snippet tip work

<p>Someone from the FSF’s licencing department posted an official-looking
 thing saying they don’t believe <a
 href="permalinks/wlog-10_e20170301-tg.htm">GitHub’s new ToS</a> to be
 problematic with copyleft. Well, my lawyer (not my personal one, nor for
 The MirOS Project, but related to another association, informally) does
 agree with <em>my</em> reading of the new ToS, <em>and</em> I can point
 out at least a clause in the GPLv1 (I really don’t have time right now)
 which says contrary (but does this mean the FSF generally waives the
 restrictions of the GPL for anything on GitHub?). I’ll eMail GitHub Legal
 directly and will try to continue getting this fixed (as soon as I have
 enough time for it) as I’ll otherwise be forced to force GitHub to remove
 stuff from me (but with someone else as original author) under GPL, such
 as… tinyirc and e3.</p>
<p><a href="@@RELPATH@@permalinks/wlog-10-tg_e20170308-tg.htm">My
 <tt>dbconfig-common</tt> Debian packaging example</a> got a rather hefty
 upgrade because <tt>dbconfig-common</tt> (unlike <em>any</em> other DB
 schema framework I know of) doesn’t apply the upgrades on a fresh install
 (and doesn’t automatically put the upgrades into a transaction either)
 but only upgrades between Debian package versions (which can be funny
 with backports, but AFAICT that part is handled correctly). I now append
 the upgrades to the initial-version-as-seen-in-the-source to generate
 the initial-version-as-shipped-in-the-binary-package (optionally, only
 if it’s named .in) removing all transaction stuff from the upgrade
 files and wrapping the whole shit in <tt>BEGIN;</tt> and <tt>COMMIT;</tt>
 after merging. (This should at least not break nōn-PostgreSQL databases
 and… well, database-like-ish things I cannot test for obvious (SQLite
 is illegal, at least in Germany, but potentially worldwide, and then
 PostgreSQL is the only remaining Open Source database left ;) reasons.)</p>
----
