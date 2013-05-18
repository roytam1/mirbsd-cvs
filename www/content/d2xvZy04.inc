<small class="rcsid">$MirOS: www/content/d2xvZy04.inc,v 1.16 2006/01/18 07:02:40 tg Exp $</small>
<h1>MirBSD &ndash; WTF, We Have a Release!?</h1>
<p><small><a href="#eof">bottom</a> or <a href="/?older">older</a>
 editions</small></p>

<div class="wlentry">
<h3>27.12.2005 by bsiegert@</h3>
<p>We finally have a new release, over two years after #7! To
celebrate this event, rotate the wlog and start a new one.</p>
</div>

<div class="wlentry">
 <h3>27.12.2005 by tg@</h3>
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
 <h3>28.12.2005 by tg@</h3>
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
 <h3>29.12.2005 by bsiegert@</h3>
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
 <h3>30.12.2005 by tg@</h3>
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
 <h3>01.01.2006 by tg@</h3>
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
 <h3>02.01.2006 by tg@</h3>
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
 <h3>13.01.2006 by tg@</h3>
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
 <h3>15.01.2006 by tg@</h3>
 <p>Things are settling down... installed software on &#39764;&#29579;
  but still not complete. It now does mail (for all domains), OpenVPN,
  a minimalistic www proxy, and of course NTP and its own (non-public)
  DNS. But that's about it. Time will show.<br />Also, I need to phone
  the hoster regarding the domain issues. They're worse than appearing
  at first, since the wildcard is gone.</p>
 <p>Fixed some annoying minor bugs in roff2htm and /cvs/CVSROOT.</p>
</div>

<div class="wlentry">
 <h3>17.01.2006 by tg@</h3>
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

<p id="eof">Good luck, have fun, take care etc.pp</p>
