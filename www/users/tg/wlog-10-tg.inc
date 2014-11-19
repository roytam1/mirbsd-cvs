RCSID: $MirOS: www/users/tg/wlog-10-tg.inc,v 1.18 2014/11/19 13:34:20 tg Exp $
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
