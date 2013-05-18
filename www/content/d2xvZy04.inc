<!-- PageID: wlog-8 -->
<small class="rcsid">$MirOS: www/content/d2xvZy04.inc,v 1.40 2006/02/21 03:36:06 tg Exp $</small>
<h1>MirBSD &ndash; WTF, We Have a Release!?</h1>
<p><small><a href="#eof">bottom</a> or <a href="/?older">older</a>
 editions</small></p>

<div class="wlentry">
<h3 id="e20051227">27.12.2005 by bsiegert@</h3>
<p>We finally have a new release, over two years after #7! To
celebrate this event, rotate the wlog and start a new one.</p>
</div>

<div class="wlentry">
 <h3 id="e20051227b">27.12.2005 by tg@</h3>
 <p>I've been prodded by bsiegert@ to write here again. Curious, isn't
  it? After the last release I've been the only one to write here. But
  today is somehow unproductive... I can't get myself to do something;
  will probably hunt some autoconf bugs later. I got a new laptop HDD,
  80 GB and waaaaaay faster, and re-installed BSD. pb@openbsd, who has
  arrived at the OpenBSD booth @22C3 in the meantime, didn't recognise
  me as I showed up in front of him until I threatened to throw all 70
  or so MirOS CDs we have at them.</p>
</div>

<div class="wlentry">
 <h3 id="e20051228">28.12.2005 by tg@</h3>
 <p>Another very cold (outside) and hot (inside) day at the 22nd Chaos
  Communication Congress (Berlin, Germany). The &quot;others&quot; are
  out for food (bsiegert@, a friend of his and our booth slave), Thai,
  this time, while I'm still sitting here and just fixed mplayer (that
  included fixing and upgrading a shitload of other ports). Drinking a
  newly found thing, vanilla flavoured Soy milk, and a local specialty
  (Fa&szlig;brause) I'm hacking away, while the NOC complains that we,
  all of us together, are using a mere 7% of the 16 Gbit/s uplink, and
  the CAcert.org guy is seemingly confused (but they at least do their
  thing so that it WFM).</p>
 <p>Opera segfaults, and I guess my next target will be porting ptrace
  support for the Linuxulator from NetBSD&reg;, or asking Kurt Miller,
  who seems to have already done it, for his patch. Drinking more milk
  and juice and less alcohol during the night time should also help...
  but I'm more sleepy than really tired. They offer Club-Mate, but not
  the brother IceT, so I'm left off the caffe&iuml;ne circle (coffee's
  too expensive as well).</p>
 <p>I notice I can't write coherent &quot;day-to-day palaver&quot; log
  entries... I s'pose I should go back to coding. Who is going to read
  this anyway? People are busy complaining the FTP servers are slow (I
  think FTP deserves to die <b>fast</b> anyway).</p>
</div>

<div class="wlentry">
 <h3 id="e20051229">29.12.2005 by bsiegert@</h3>
 <p>I am writing this just after midnight, so the second day of 22C3 has
  just ended. Did some updated ports for GNOME 2.12.2, hopefully I will
  have it finished by the time GNOME 2.14 comes out&nbsp;...</p>
 <p>I saw three more or less interesting talks today. The first one was by
  Dan Kaminsky is called "Black Ops Of TCP/IP 2005.5". He basically showed
  what you can do with a <i>really</i> fat pipe: scan the entire internet!
  He also showed a real-time traffic graphing tool and an estimate of the
  number of machines infected by the Sony rootkit: at least 700.000
  machines, more likely over a million. To quote <a
  href="http://www.schneier.com/blog/archives/2005/11/sonys_drm_rootk.html">Bruce
  Schneier</a>: "What happens when the creators of malware collude with the
  very companies we hire to protect us from that malware?"</p>
 <p>After that, there as a talk about <a
  href="http://codespeak.net/pypy/">PyPy</a>, a Python implementation
  written in Python. This actually makes sense because it is self-hosting
  and it can translate Python code into C and even JavaScript for native
  compilation. The third talk was a real highlight -- "Das literarische
  Code-Quartett". Examples of good and bad code, commented in a very fun
  way. Definitely a must.</p>
</div>

<div class="wlentry">
 <h3 id="e20051230">30.12.2005 by tg@</h3>
 <p>The chaos continues. But some real work is done &ndash; we now can
  support the scenario &quot;some shared library depends on another of
  their kind&quot; (for now, only unofficially, but it will be MFCs by
  bsiegert@ I think).</p>
 <p>Today is clean-up and go day. We asked the people from OpenBSD (we
  have to clean up and work, no time), NetBSD&reg; (they want to drive
  away early, like 18:00, due to the weather), DragonFly BSD (they say
  there will be ice rain so they'll hunt home at 15:00) to eat with us
  at the great Indian restaurant, and FreeBSD didn't even show up (the
  same procedure as every year). But we're gaining popularity not only
  among the other BSDs, but as well with the congress participiants (a
  spokesman calling them "Dear congress... err... people" in a speaker
  announcement).</p>
 <p>Some media are writing off each other, leading to people believing
  we have released MirOS Windows XP or something. We had to unconfuse;
  we hope to be able to correct this mistake in each publication where
  it shows up.</p>
 <p>I've got headaches. Everything is being broken down, including the
  big HP switches, so the network'll probably cease to exist RSN. Benz
  is watching a last presentation, then we'll head to the Indian, then
  back home. See you all in the new (christian/western) year!</p>
</div>

<div class="wlentry">
 <h3 id="e20060101">01.01.2006 by tg@</h3>
 <p>I've hacked on an enforcement for ports versioning and drafted the
  "package era" scheme we'll probably be using, pending results of the
  discussion with all other active MirPorts developers (hrhr).</p>
 <p>The INDEX was regenerated after I fixed several ports with damaged
  version numbers but the versions used before that are quite probably
  <em>not</em> upgradable.</p>
 <p>sirc and ssfe are now capable of displaying "cool looking" unicode
  (and ASCII) time stamps.</p>
 <p>I changed all my (user and root) passwords and generated a new ssh
  key after returning from 22C3 (where I shut down the boxen remotely,
  as the last thing before they switched off the network). This is the
  best thing to do, since keys and passwords should be rotated yearly,
  or at least periodically, anyway, and I can't think of a better time
  than after the Chaos Communication Congress.</p>
</div>

<div class="wlentry">
 <h3 id="e20060102">02.01.2006 by tg@</h3>
 <p>I've ordered a new dedicated server which will cost me a lot less,
  namely 19.90 &euro; the first 18 months and then 29 &euro; (also per
  month) with the same functionality at the same hoster. I'm compiling
  a new snapshot these days to set it up with this &ndash; so thor has
  outlived and will not be continued, but switching will not be a pain
  either.</p>
 <p>My friend <tt>bogus</tt> was here for a bottle of Met and just did
  the same. The new hostnames will be fungor (his choice) and... well,
  &#39764;&#29579; (&#12414;&#12362;&#12358;) is mine. The meal we had
  at the yugoslawian (croatian) was tasteful, by the way.</p>
 <p>I baked an Atheros kernel for <tt>gecko2</tt>'s Soekris net4801 he
  purchased (which was formerly known as <tt>loki</tt>) which works...
  much to my surprise. But it's not ready for commit, e.g. I nuked the
  wi(4) support to compile, ifconfig(8) doesn't operate properly, etc.
  (but he can access wireless LANs with it). I wouldn't buy ath(4) tho
  (I just don't trust them).</p>
 <p>I somehow miss bsiegert@ here &ndash; there's lots of fixes he may
  (should) be doing now...</p>
 <p>Somehow we're gaining <a
  href="http://www.pro-linux.de/news/2005/9093.html">good</a> <a
  href="http://www.symlink.ch/article.pl?sid=05/12/30/1030208&amp;mode=nested">press</a>
  and <a href="http://www.osnews.com/comment.php?news_id=13124#79739">user reviews</a> (and <a
  href="http://www.osnews.com/comment.php?news_id=13124&amp;offset=20#80467">slander</a> which shows
  that the &quot;others&quot; are not only recognising us but also see
  us as dangerous to them (their popularity? user base? I've converted
  at least one OpenBSD person to MirOS during 22C3). Nice to know.</p>
 <p>I tought bogus some MirPorts and upgraded the ext2fs-progs port in
  the meantime (also adding a static flavour later, to benefit a weird
  setup of my new dedicated server). The idea is to have a 16 MiB wd0a
  with a partition ID != 0x27, containing a /boot installed with -P as
  to recognise the partition, and one or two ramdisk kernels, and some
  text files (e.g. disklabel, fdisk output). Then, a 16 MiB extfs with
  a gzip'd image of the first 16 MiB (including MBR, PBR, 4.2BSD FFS),
  a stand-alone MBR, and what else you could need to recover. The rest
  is a standard 0x27 partition with the wd0a of a regular boot, /home,
  swap, whatever. The "irregular" wd0a need not even be in there.</p>
</div>

<div class="wlentry">
 <h3 id="e20060113">13.01.2006 by tg@</h3>
 <p>I've fixed a few things (code cleanliness) and built a snapshot to
  see if it works (another one &ndash; there was one on 03.01. already
  which bsiegert@ has announced today at freshmeat). This one also has
  taken care of the always changing domains. I'm updating MirOS #8 (by
  mkdir updates) with current MirPorts as well.</p>
 <p>My little brother and bogus came here, teaching me Maths, drinking
  Met and having fun, after a good meal. I need it; university is some
  weird shit, something else really. It's not my favourite but I still
  want to do 2 semesters before going to work (so I can continue later
  if I want).</p>
 <p>Nothing else in peculiar... bsiegert@ has got a girlfriend, thusly
  #8-stable is lagging quite a bit. My new dedicated server also could
  need some more attention.</p>
</div>

<div class="wlentry">
 <h3 id="e20060115">15.01.2006 by tg@</h3>
 <p>Things are settling down... installed software on &#39764;&#29579;
  but still not complete. It now does mail (for all domains), OpenVPN,
  a minimalistic www proxy, and of course NTP and its own (non-public)
  DNS. But that's about it. Time will show.<br />Also, I need to phone
  the hoster regarding the domain issues. They're worse than appearing
  at first, since the wildcard is gone.</p>
 <p>Fixed some annoying minor bugs in roff2htm and /cvs/CVSROOT.</p>
</div>

<div class="wlentry">
 <h3 id="e20060117">17.01.2006 by tg@</h3>
 <p>Wow, I've been attending university once again. This time for that
  #1 boring thing &ndash; Economics (BWL), held by a female VWL doctor
  with a voice more cruel than should be allowed... at least we do not
  have to do an exam, only attend and do a presentation and home work.
  And I scored well in English (the other class in which attendance is
  mandatory). I've worked on my Maths, and theorectical CS is trivial.
  But as for the others, I don't know. Plus in the beginning they told
  us that we would automatically be subscribed for the exams &ndash; I
  was told today I should better have done that myself in December. So
  I probably can't do any exams except English this semester.</p>
 <p>Been working on djbdns today, once again. Now I've incorportated a
  lot more patches (from tinydns.org) and can do AXFR via inetd(8). So
  I will probably use AXFR and NOTIFY requests in the future, with two
  friends (bogus and maybe gecko2 or someone else) doing backup NS for
  me (and HERC might still do too, but using classical rsync/scp). And
  the best thing: it actually works and required virtually no patches.
  There's still no (working) UCSPI-TCP port though. We did have one in
  the past, from OpenBSD, but it never worked correctly, nor addressed
  all the issues we had with it. (DJB sucks.)</p>
 <p>I discovered more bugs in pkg_upgrade(8) which bsiegert@ hopefully
  will fix (or at least decide which fix is correct, I can think of at
  least three possible fixes, preferring the one most complex).</p>
 <p>I had announced the <a href="/?clog-2006#snap0113">snapshot of Jan
  13</a> on FM and it actually showed up.</p>
 <p><tt>*.mirsolutions.de</tt> works, once again. Costly phone call to
  the provider sponsored by yours truly. Now go and <a href="/?danke">
  donate</a> some money via PayPal.</p>
 <p><a href="http://article.gmane.org/gmane.os.miros.general/1635">The
  comment</a> on the GPLv3 actually got modded <tt>+1, Insightful</tt>
  on <a href="http://www.symlink.lu/">Symlink</a>, the German slashdot
  equivalent (which, in contrast to its English counterpart, still can
  be accessed with Lynx correctly).</p>
 <p>A new <a href="http://www.froscon.org/wiki/CallforPapers">Call for
  papers</a> by the <a href="http://www.froscon.de/">FROSCON</a> Orga.
  This is dubbed the &quot;LinuxTag Bonn&quot; and replaces the former
  LinuxTag Karlsruhe (now Wiesbaden, where ever that may be) for us...
  we've organised a BSD room (the orga team are drinking mates of mine
  so it wasn't too difficult). DragonFly BSD will come (per Joerg) and
  Wim will obviously attend. NetBSD&reg; hopefully will appear too; as
  for FreeBSD&reg; I couldn't ask them since they weren't there (again
  as usual) at 22C3. <a href="http://undeadly.org/cgi?action=article&amp;sid=20060117101506&amp;mode=expanded">The
  OpenBSD magazine</a> has it too (as does Symlink).</p>
 <p>Did I mention our kernels are now always gzip'd? And we now got <a
  href="http://article.gmane.org/gmane.os.miros.general/1628">a permit
  to use GNU FDLd sources</a> in CVS by RMS himself (please read my <a
  href="http://article.gmane.org/gmane.os.miros.general/1626">enquiry,
  with definition of &quot;IT&quot;</a>, too).</p>
 <p>I tried to ask the Opera guys for a statically linked native Linux
  binary or even (preferred) an OpenBSD binary. They told me some info
  about glibc and Linux incompatibilities, I'll try...</p>
 <p>Older mailing list activity includes: an analysis of handling this
  year's leap second (FreeBSD 0, MirOS 2), FOSDEM, user enquiries, and
  spam. I suggest you read it for yourself.</p>
</div>

<div class="wlentry">
 <h3 id="e20060120">20.01.2006 by tg@</h3>
 <p>Published a cpio ball of ocvs+ncvs1 and historic. bsiegert@ agreed
  they be closed and sealed now. It's only on herc and maou tho.</p>
 <p>Slowly going on with setting up maou. After all, thor''ll cease to
  exist mid-February, IIRC.</p>
 <p>Removed ads. G**gle closed my account for supposed abuse.</p>
 <p>Added Debian GNU/Linux i386 emulation libs; makes Opera work. I'll
  hack it up even further though.</p>
 <p>I think I'll use /usr/bin/logger in axfrdns (net/djbdns).</p>
 <p>Planning on putting this on Planet Symlink (by a conversion script
  to be hacked) &ndash; aus der es-ist-zwar-kein-blog-aber-warum-nicht
  Abteilung... I wonder if XTaran will do it.</p>
 <p>Enough for today. Gotta do some work; then dinner at the Croatian,
  with wbx, le, Angelo (the first Mac OSX worm creator), Judith, miro,
  bogus etc.; then using <a href="http://www.netzladen.org/">the usual
  place</a> to hang around, maybe hack on the website some more.</p>
</div>

<div class="wlentry">
 <h3 id="e20060124">24.01.2006 by tg@</h3>
 <p>Got something decent to eat, drink (beer, cola) and snack. Hacked,
  djbdns-axfr, sirc/ssfe now improved, savecore(8) does gzip(1)d files
  and the zlib API sucks. compress(1)' implementation also sucks.</p>
 <p>All hardware sucks, all software sucks... but actually the overall
  suckage of MirOS is pretty darn low.</p>
</div>

<div class="wlentry">
 <h3 id="e20060126">26.01.2006 by tg@</h3>
 <p>Oh, already last day of the semester? (Well, tomorrow. Luckily, so
  I've still a minimal chance to be allowed to take exams this time...
  I better should; on 30th of January, the first one is scheduled). In
  English I graduated with an 1.3 (that's like 96%), and Economics was
  taken for granted.</p>
 <p>I fixed php5-core but encountered a package tools bug which Benny,
  hopefully, will fix. I've also redesigned my keyboard layout since I
  don't read Japanese anyway, but having Umlauts (Meta-style) in Opera
  is more important (and I've got back my Ellipsis ;). I get &auml; by
  pressing either Meta-d or Mode_switch-d (and not Mode_switch-a which
  was used by dot.Xmodmap.light for DAUs) as I'm used to from the text
  console, wscons(4).</p>
 <p>I was thrown out of Netzladen today... no idea if I'll continue to
  hang around there. Probably not, saves me 4 &euro; monthly.</p>
 <p>On the other hand, this leaded to an unexpected, not-Mate-induced,
  peak in productivity, not only yielding a much cooler, artistic, new
  keyboard layout, but to the release of <a href="/?jupp">joe-3.1jupp5
  </a> as well.</p>
 <p>And because I didn't find this, admittedly older, reference in the
  bookmark list I keep, I thought I don't want to keep it from you, as
  it's also my opinion on trends and AJAX: Felix von Leitner speaks on
  <a href="http://blog.fefe.de/?ts=bda6ce31">hypes</a>.</p>
</div>

<div class="wlentry">
 <h3 id="e20060129">29.01.2006 by bsiegert@</h3>
 <p>Wow, exactly one month since I have written my last wlog entry.
  After 22C3, I have done very little work on MirOS, owing to two
  factors: my girlfriend and the january exams (seven of them!). The
  latter are over now, and I feel confident about the results for
  courses like Optics, Solid State Physics and (worst of all)
  Statistical Properties of Polymers, to name but a few.</p>
 <p>I am still struggling with firefox 1.5 and its component libs.
  The problem seems to be related to shared library interdependencies.
  The current state of my port might work on -current. I could just
  churn out an update of #8-stable that contains the linker bugfix and
  have that as a minimum requirement.</p>
 <p>What else? If you have the opportunity, go see <a
  href="http://www.luecke-im-system.de/"><i>L&uuml;cke im System</i></a>
  (the original title is <i>Absolut</i>) at a cinema. IMHO, it is the
  first "hacker" movie which is credible both in story and technical
  aspects. And what makes it all the more frightening is that the movie
  is based on a true story. The synopsis: Two friends develop a virus
  which one of them has to install at a bank. He wakes up in the
  hospital two days later, having had an accident after work that day.
  He has lost any recollection of that day. What has happened? Did he
  really install the virus? Are <i>they</i> after him?</p>
</div>

<div class="wlentry">
 <h3 id="e20060130">30.01.2006 by tg@</h3>
 <p>Benny, do you still live in 2005? ;-)</p>
 <p>I managed to appear at two exams today, finally: Operating Systems 1
  and Technical Computer Science 1 (basically, Physics and Electronics).
  I hope I've passed both but actually I am not sure. Weird stuff.</p>
 <p>There's an mksh R26c with a few updates, and this one is about to be
  submitted to Debian again. I wonder when Gentoo will update.</p>
 <p>I'm pondering to update Lynx but I'd like to have a libiconv to link
  with so I can enable japanese-utf8 support. On other news, I still got
  no answer from Bruno Haible, maybe I should mail him again. We need to
  have that libutf8 code.</p>
 <p>I'd make a snapshot and install &#39764;&#29579; for the second time
  but there's still an infrastructure bug pending in ports, some samples
  checks by Benny, and a few other port fixes, so I'll probably postpone
  it another while. This sucks but we can bear with it; thor is still up
  and running stable enough for a while (yet can't test new ports, sigh)
  and the redirection is working for now; no abundant traffic. The state
  of the base system is quite well, it's only ports which need more work
  (much more). Of course there are a few bugs, but that's normal, you'll
  have to live with them as usual. We try to fix them, though.</p>
 <p>Dang! Hubert Feyrer has changed his "blog software" so I must update
  the hyperlinks. (Scripts around vi(1)? What were you thinking? To do a
  thing like that... you script ed(1)!) I've sent him some more material
  for his fun pages &ndash; reading symlink is still worth it sometimes,
  but rarely.</p>
 <p>I at <a href="http://chemnitzer.linux-tage.de/2006/info/">Chemnitzer
  Linuxtage</a>? Possible, if someone sponsors me. I must get there (and
  back) safely &ndash; by train or, preferred, car sharing with somebody
  from the Bonn region, and live there somewhere (a place to sleep). Any
  offers? <a href="mailto:tg@mirbsd.de">Mail</a> me.</p>
</div>

<div class="wlentry">
 <h3 id="e20060131">31.01.2006 by tg@</h3>
 <p>bsiegert@ will probably kill me, or use some other means of violence
  (who knows), but at least it's done. mgcc(1) now aborts if CFLAGS (and
  COPTS, or rather, _DEFCOPTS) are not honoured, with an optional abort,
  not yet active, if they are given twice. This depends on a variable to
  be set in the environment, thus doesn't affect manual builds except by
  an informal note.</p>
 <p>We now have mmap(2) malloc(3), TCP tuning diffs (SYN packets 4 bytes
  smaller), and my libc is still working. I am amazed. I will rebuild my
  entire system then.</p>
 <p>nl_langinfo(CODESET), citrus iconv(3), security-fixed perl(1)... now
  he just can't kill me ;) Also did some major www updates to keep track
  of source changes (still commented out though).</p>
 <p>More later... if I'm still living by then ;)</p>
 <p>Seems as if Benny is sleeping... weird, he said his exams period was
  over... fixed build of base system, so I could do a snapshot again, if
  I wanted (and ports were ready - damn pkgtools bug).</p>
 <p>h2ph(1) was indeed used, but it seems to be minor. gcc now builds as
  well (non-C languages just ignore -fhonour-copts which seems easier to
  me), except libjava which I didn't test due to tiredness (lack of time
  and sleep).</p>
 <p>I somehow expect iconv(3) and nl_langinfo(3) CODESET support to have
  some impact on something... but nothing until now. Wait to see whether
  we rename libcitrus_iconv to libiconv (selection via -L works).</p>
</div>

<div class="wlentry">
 <h3 id="e20060201">01.02.2006 by tg@</h3>   
 <p>I've been working on libiconv integration into MirPorts today which,
  the way I did it, also benefits Darwin. I also hacked a bit on varouus
  iconv(3)-using ports including centericq, and changed the linuxulator,
  respectively the porting framework, so that opera runs better.</p>
 <p>Should I really go to the exam tomorrow? Chances are I get 40% while
  to pass you need to have more than 50%.</p>
 <p>Soryu (&#x60e3;&#x6d41;&#x30fb;&#x30a2;&#x30b9;&#x30ab;&#x30fb;&#x30e9;&#x30f3;&#x30b0;&#x30ec;&#x30fc;
  is his nickname, "Stanley Rost" is the real name according to his CMS'
  copyright) pointed me via <a href="http://mirbsd.de/irc">IRC</a> to an
  ambiente stream at radioio.com &ndash; a site which offers two quality
  variants on the website (AM quality and FM quality, wtf?)<br />Now the
  fun part: Opera opens a pop-up and offers to download an m3u file when
  asking for an mp3 stream (thank goddess, I only have mpg123 installed,
  playing music on the pentium &#x2160; router). The filename: A1med.m3u
  (this of course raises suspicions) &ndash; so I test-run the AM stream
  and get presented an A1lo.m3u. Interesting. Viewing the source it's an
  easy task to see the URI, so I ftp(1) A1hi.m3u which in fact exists! I
  guess it's a subscriber-only feature, but 128 kbps 44k1Hz J/S MP3 is a
  lot better than 64 kbps 22k05Hz J/S, isn't it? Now I'm listening to <a
  href="http://radioio.sc.llnwd.net:8610/">the stream</a> and will sleep
  (or at least try to). I decided that I have no chance to pass the exam
  scheduled for tomorrow, that's the only reason to still be awake.</p>
</div>

<div class="wlentry">
 <h3 id="e20060202">02.02.2006 by tg@</h3>   
 <p>So, I did sleep long and not take the exam. I would not have passed,
  anyway.</p>
 <p>Some lazy day today, but I'll continue hacking on various stuff. And
  (as announced) I broke mySQL for there is no maintainer. We have real,
  happy, users of MirOS who also appear in IRC, so I fixed a few things,
  based upon their feedback. Also I persuaded a bunch of BSD guys to add
  <tt>#bsd</tt> (or even <tt>#mirbsd</tt>) on Freeforge to their connect
  list and autojoin.</p>
 <p>Tomorrow I'll have to do a few different things over the day, so may
  not have the time to work on MirOS.</p>
</div>

<div class="wlentry">
 <h3 id="e20060209">09.02.2006 by tg@</h3>
 <p>Still trouble with my life cycle. Getting up early nearly killed me,
  so I slept during noon a little while. But at least there are a few of
  my friends still not leaving me.</p>
 <p>I must admit that I'm spending a larger amount than I used to or I'd
  like to, even, on "common" internet activity &ndash; chatting (Jabber,
  ICQ, MSN, Yahoo, IRC) and web-based message boards (with Opera). It is
  not what I'd like to do but there are a few persons I got to know over
  time. Besides, with Benny spending time with a girlfriend... which I'm
  still hoping to eventually acquire as well.</p>
 <p>I started a bulk build and, annoyed by the crap we took over from "a
  BSD focusing on clean code", did some major commits. This probably has
  broken some more stuff but I'm doing bulk builds to see where. I won't
  fix ports which don't build (except for the easy cases) just mark them
  as ${BROKEN}, so we at least know.</p>
 <p>Does anyone still have wishes for the next snapshot? I'm about ready
  to build one. Except for ports, as usual. Lack of communication can be
  quite annoying.</p>
 <p>With mmap(2) malloc(3) we need the OpenBSD X11 fixes ported. I asked
  ciruZ already, but if someone volunteers, please say so since it's not
  yet clear whether he will try it at least.</p>
 <p>That's all, folks. If I got more feedback I'd write more, besides, I
  don't even know which topics are of interest to you.</p>
 <p>homsn (Daniel Hommel) has packaged mksh(1) for Arch GNU/Linux!</p>
</div>

<div class="wlentry">
 <h3 id="e20060214">14.02.2006 by tg@</h3>
 <p>Benny is in Japan now &ndash; nice, eh? I think I'd better get a new
  snapshot built and &#39764;&#29579; installed before it's too late for
  merging the old server. I've played a bit with the build system though
  (some stuff I always wanted to re-do, if we weren't going for syspkgs,
  there was more work in that area).</p>
 <p>At the moment, no lectures at university, I'm sleeping too long (and
  too much probably) and not getting anything productive done. I already
  am waiting for FOSDEM but probably can't go to CLT.</p>
 <p>Ports are in a rather questionable state, I'm prepared having to fix
  everything on maou prior to installing. Someone ought to continue bulk
  build and break work.</p>
</div>

<div class="wlentry">
 <h3 id="e20060215">15.02.2006 by tg@</h3>
 <p>Built a snapshot in an overnighter. Have fun, help testing. Caution,
  ports are a mess.</p>
 <p>No idea how I can tell Benny by different means... we've got a place
  to stay in Leuven &ndash; 2 developers, 2 Trittbrettfahrer.</p>
</div>

<div class="wlentry">
 <h3 id="e20060220">20.02.2006 by tg@</h3>
 <p>I've been outside a lot, but under-the-hood FOSDEM planning coninues
  and we'll probably have CDs with yet another new snapshot, and I ought
  to bring the MirShirts with me as well.</p>
 <p>Hacked a little on vnconfig(8) (in preparation for the key file hack
  inspired by GeNUA's Marcus Popp) and ssh(1), sshd(8) (in order to make
  them exchange randomness with the peer (via our own arc4random_push(3)
  interface so it's strictly optional).</p>
 <p>Also added a workaround to lynx(1) to improve handling of the broken
  CAcert.org website. Fix comes later.</p>
 <p>bsiegert@ actually phoned me today, meaning he still lives...</p>
 <p>I've updated the essentials/pkgtools port after fixing a few bugs in
  pkg_upgrade. I've also updated mc (difficult, and I don't like some of
  the changes) and, finally, mirex (contrib/samples) (even with the new,
  not yet in use, gzsig(1) key but still without bsiegert@ having looked
  whether his information is correct). Makes me wonder if the version of
  that port is now correct...</p>
 <p>Forcing USE_CXX=no ports to use 'false' as ${CXX} since now.</p>
</div>

<div class="wlentry">
 <h3 id="e20060221">21.02.2006 by tg@</h3>
 <p>Today I just was in a hacking mood and besides updating ssh(1) wrote
  vnconfig(8) keyfile support from scratch using PEM, fixed djb fetching
  of distfiles, updated and fixed misc/mc for good, helped porters which
  need iconv.m4, added SQLite2 to php-core and a little advertising (for
  the MirPorts Framework), hacked net/openvpn the same as ssh, fixed the
  arc4random_push(3) stuff I use for months in the kernel, so that it is
  finally usable, did a few man pages and build improvements, even fixed
  a lot of OpenSSH code regarding to gcc warnings.</p>
 <p>bsiegert@ actually showed up in IRC today... did not do much though.
  I wonder whether we'll be able to do FOSDEM like we want, since I'm in
  the mood for everything save housework which includes washing clothes,
  for example certain t-shirts.</p>
</div>

<p id="eof">Good luck, have fun, take care etc.pp</p>
