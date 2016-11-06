RCSID: $MirOS: www/data/wlog-9.inc,v 1.103 2015/09/10 19:46:28 tg Exp $
Date: 25.06.2006
Author: tg@

 <p>I'm committing this as 2006-06-25, but actually, I haven't slept for
  <em>more</em> than 31 (thirty-one) hours now, so it could very well be
  under 2006-06-24. I'm going to sleep now, but not without releasing an
  ISO of MirOS #9semel on BitTorrent.</p>
 <p>There's now a new BitTorrent info page not linked
  anywhere except from the tracker (and here). It ought to describe what
  the torrent will give you.</p>

----
Date: 27.06.2006
Author: tg@

 <p>On a rainy day, I'm continuing to hack on sparc again. I haven't yet
  found why dynamic linking breaks, just how to break it even more, plus
  without a working gdb there isn't much I can do. On the other hand, my
  kernel didn't panic yet, so I'm going to make it a static arch for now
  and get back to ld.so(1) support later.</p>
 <p>On a related side note, we're currently developing #9-stable in HEAD
  and will branch that later. I want a #9bis to be out both as soon as I
  can and sparc works reliably, and with as few differences from #9semel
  as possible. This also gives us a chance to polish ports and docs.</p>
 <p>Benny is moving homes at the moment.</p>
 <p>Oh, and FrOSCon was a full success, best event I ever attended. I've
  intended to write more here but I'm still done with.</p>
 <p>Which &lt;censored/&gt; set the maximum datasize for sparc to a mere
  128 MiB, in contrast to i386's 1 GiB? Bumped to 320 MiB in order to be
  able to build gcc&#8230; kernel really seems stable now, compiled both
  cross and natively.</p>

----
Date: 29.06.2006
Author: tg@

 <p>I've built MirOS (base and gcc) entirely on the sparc and have fixed
  the GNU Debugger in the progress as well. I'll have to change a little
  code in order to silent gcc, but that's not much left.</p>
 <p>In order to fix a few security leaks, I updated libpng and freetype2
  as well. I yet have to re-build the entire X-Windowing system in order
  to test whether this actually does not break anything. Neither has the
  XFree86 environment been ported to the new sparc system.</p>
 <p>After the bump of autoconf to version 2.60 everything must be tested
  and libtool ought to be bumped as well.</p>
 <p>Finally, I must make sure that distrib/ works on sparc and release a
  first snapshot &ndash; optimally as live-cd :) but I'm not going there
  yet.</p>

----
Date: 30.06.2006
Author: tg@

 <p>My sparc has just gone NOPIC=no, i.e. builds ld.so(1) and shared lib
  stuff just fine. bsiegert@ isn't (sadly) reachable by phone though, so
  I continued to hack on autoconf/libtool, regenerated all the stuff and
  then threw in the new perl. Now I've got to, after refining a few more
  code pieces, check if everything (including X11) builds on i386 again.
  On sparc, I've got to take what I've got, build the distrib/ stuff and
  a snapshot in order to install that on another hard disc.</p>
 <p>I think -rHEAD is in pretty good shape, I'll upgrade as much as I'll
  be able to do in the next days, try to get a stable sparc development,
  build and test environment, and fix everything outstanding in the base
  system. Regarding ports, I won't do much but leave that to Benny, I'll
  do base system in the meanwhile and hope he fixes these ports which do
  need it. (autoconf 2.60 is in, but I don't think there's any fallout.)
  Thus, we can (tentatively) release #9bis in two or three weeks.</p>
 <p>It's family weekend for me, don't expect too many commits. Also, I'm
  in that "computers suck" mood again but the weather (too hot) keeps me
  from giving in to it.</p>
 <p>On the other hand, the <a href="http://www.netzladen.org/">Netzladen
  (usual place)</a> has got me back&#8230; at least for drinking some <a
  href="http://www.cafe-libertad.de/">fine Met (honey wine)</a>.</p>
 <p>Benny, when are you going to commit that full-japanese wlog entry of
  yours?</p>

----
Date: 02.07.2006
Author: tg@

 <p>After backporting and fixing stuff, this is mainly unbreaking -rHEAD
  and letting changes settle down. xterm didn't get updated (yet &ndash;
  maybe xterm-213 works better than xterm-215, but for now we still have
  xterm-200), half of OpenBSD's XF4 fixes were added and some of our own
  devised (especially since neither XFree86&reg; 4.6 nor x.org trunk can
  be built with freetype 2.2&#8230;) and things simplified. Now, I build
  everything on i386 (in order to check for regressions) and sparc (want
  to add a 9 GB disc drive and install a snapshot on that, to get rid of
  NFS, but there's no snapshot yet). Also a.out debugging symbol handler
  is back in kernel (sounds like Japanese Engrish eh?) since I fixed the
  point of breakage.</p>
 <p>MirOS boots just fine on a Thinkpad X41, just the Broadcom shit does
  not like to work. I may backport that, says Benny who just moved to an
  appartement in the Germany-France-Switzerland border region and except
  not having a phone (tomorrow) and internet (modem) is doing fine.</p>
 <p>Reading more code for FreeWRT&#8230; it's cruel. configure is mixing
  build and host system up &ndash; look at libdnet, but keep a vomit bag
  handy.<br />By the way&#8230; many people dislike subversion, like me,
  especially after having used it for a few weeks.</p>
 <p>Plans? What plans?</p>
 <p>I could do an auto-livecd for sparc too. Easily. But mine is running
  on VT420 on serial console. Also, it is slow. So spare me. (I offer to
  still do it if users request it. Don't forget releases are <em>no</em>
  live CDs.</p>
 <p>Very late edition, a.k.a. WTF is date(1)?<br />I'm through with i386
  and committed the distrib/lists changes, where I also shuffled some of
  the things I know won't run on sparc away into md.i386 files. Some has
  been disabled, even though it builds on sparc, like iopctl(8), because
  the hardware just doesn't exist. I then screwed around a little in gcc
  and found out we're still building a threaded gcc even though that's a
  java only thing, and optimised Makefile.lang (not yet tested). Note, a
  threaded gcc probably doesn't work on sparc. I decided against keeping
  the libobjc_gc wrappers unless manually (NO_BOEHMGC=no) or via depends
  (NO_JAVA=no) enabled, and for keeping c++, Objective-C, and GNU Pascal
  available on sparc, because there's no reason (except size which is no
  issue with gcc bloat, er gcc 3, anyway) to differ between platforms at
  all. They're small enough to not slow down by more than a few hours or
  so of build time ;-)</p>

----
Date: 03.07.2006
Author: tg@

 <p>I thought it would be a good day, fixing lots of sparc and MI stuff,
  hacking on mksh(1), hacking on myBB for a friend, hacking on FreeWRT's
  mksh (making it cleaner) and the profile, maybe Debian mksh update and
  add sample ~/.mkshrc &ndash; the sparc is doing fine &ndash; but SOL I
  am&#8230; the internet connection went away.</p>
 <p class="boxhead">What do you think about the following</p>
 <div class="boxtext">
  <pre>
	tg@demo:~ $ cat x.pas ; gpc x.pas ; ./a.out ; file a.out ; ldd a.out ; dmesg | fgrep cpu ; uname -a
	program Hallo;
	begin
	  writeln('Hello, World!');
	end.
	Hello, World!
	a.out: ELF 32-bit MSB executable, SPARC, version 1, for MirOS BSD, dynamically linked (uses shared libs), not stripped
	a.out:
		Start    End      Type Open Ref GrpRef Name
		00000000 00000000 exe  1    0   0      a.out
		1725c000 17899000 rlib 0    1   0      /usr/lib/libgpc.so.2.1
		23735000 23d57000 rlib 0    1   0      /usr/lib/libm.so.5.0
		16b9b000 1725c000 rlib 0    1   0      /usr/lib/libc.so.38.4
		21750000 21750000 rtld 0    1   0      /usr/libexec/ld.so
	cpu0 at mainbus0: TMS390Z50 v0 or TMS390Z55 @ 75 MHz, on-chip FPU
	cpu0: physical 20K instruction (64 b/l), 16K data (32 b/l), 1024K external (32 b/l) cache enabled
	MirBSD demo.mirbsd.org 9 Kv#9s81-stable-20060627 GENERIC#92 sparc
  </pre>
 </div><p class="boxfoot">(ciruZ thinks it is pretty cool ;)</p>
 <p>Okay, there's not much more to do except letting the sparc compile a
  full system during the night and installing that, as well as rsynching
  the repo to my laptop. I hope I'll soon be at the point where I can do
  the HDD swapping and get rid of sucky NFS.</p>
 <p>I have a mosquito lamp now &ndash; UV light and a high-voltage thing
  killing them. But they're flying away from that and around in the room
  as if it were disgusting them. *sigh*</p>

----
Date: 04.07.2006
Author: tg@

 <p>It's been even hotter, thus I'm still not sleeping (I'm 7 hours past
  midnight already) but enjoying the only cool hours right now. Insects,
  these beasts! They've been plagueing me worse than ever tonight.</p>
 <p>Yay! The libc major bump turned out to be necessary, an API changed,
  an API vanished. And the sparc snapshot due will even have both shared
  libraries &ndash; rebuilding everything takes too long and I so dearly
  want to get rid of NFS. At least, I'm now already diving in the depths
  of src/distrib/ and will try my best to make as few regressions as can
  (no miniroot yet, as time permits).</p>
 <p>I wonder if we can use NetBSD&reg;'s makefs(8) for the floppies (any
  case, it'd just rock!) and maybe mr.fs and miniroot9.fs too (with some
  flag to make space or something). One also should look at its ISO 9660
  building capabilities later (for MirOS #10 then).</p>
 <p>I guess I'll have to bring out an i386 snapshot too, after the login
  manager changes I suggested to miros-discuss@ the other day, and to be
  fulfilling the &quot;debt&quot; to bring all the security updates out.
  The overall code is still sort of flaky, but improving. I wonder if it
  would be better to first fix everything known on sparc (including that
  miniroot, and maybe even a text-only live CD) beforehand, as to unveil
  pending MI bugs.</p>
 <p>Is anyone reading this here anyway?</p>

----
Date: 05.07.2006
Author: tg@

 <p><tt>mksh R27e</tt> is spreading slowly, but the goal of mksh's world
  domination is getting closer&#8230;</p>
 <p>Originally I had decided to go to bed earlier today, but somehow I'm
  fascinated by the just-finishing (tarmk stage) sparc snapshot build. I
  will publish that snapshot on BT now and afterwards try to hack on the
  miniroot and live CD (text-only for now) so it won't matter if I break
  stuff. Then I'll put a bigger HDD into the sparc and reinstall.</p>
 <p>Some of that old code is <em>so</em> scary&#8230;</p>
 <p>makefs(8) from TNF has appeared, and I already have filed the bug <a
  href="http://www.NetBSD.org/cgi-bin/query-pr-single.pl?number=33924">toolchain/33924</a>
  in their gnats ;) I hope they'll help improving it so we might someday
  get rid of mkisofs(8) in base. I also opened another report &ndash; <a
  href="http://www.NetBSD.org/cgi-bin/query-pr-single.pl?number=33925">toolchain/33925</a>
  with the filesystem size off by a block issue from 2003 or so.</p>
 <p>I haven't been able to work much on ports, as expected. Benny on the
  other hand is currently trying to buy internet access via a modem. Yes
  a (USB-attached soft)modem, that analog phone line thingie. He'll work
  a little on ports then, but don't expect too much from him either.</p>
 <p>I might also have some real-life things to take care of. I still am,
  additionally, looking for a job. Offers and donations welcome.</p>
 <p>IPv6 tunnel providers suck. All of them. And perl(1) sucks more.</p>
 <p>It finally cooled down today with a thunderstorm. Problem: both soil
  and air are wetter now, so if the sun comes back, it'll be sticky.</p>

----
Date: 06.07.2006
Author: tg@

 <p>The <a href="http://bsdnews.com/view_story.php3?story_id=5889">story
  on Daily D&aelig;monnews</a> I submitted today got accepted!</p>
 <p>surrounder from #UnixNL helps seeding BT, dankjewel!</p>
 <p>I <strong>did</strong> get rid of binstall (the joke) now. And also,
  fd0 on machines without floppy. <tt>boot.net</tt> is also superfluous,
  as the elf2aout(1)-generated boot can be used as netbootloader as well
  (and quite well) &ndash; why not, since <tt>bsd.rd.net</tt> is created
  just the same way.</p>
 <p>Benny now has internet access at home. I still am trying to prod him
  to commit that all-japanese wlog entry of his, though. (Wait! That one
  would even be committed to /?wlog-8 right? Damn boy you're late.)</p>
 <p>It actually <em>is</em> cooler than the days before, good.</p>

----
Date: 08.07.2006
Author: tg@

 <p>Sourcemage GNU/Linux users might now also be able to use mksh(1) and
  Debian GNU/Linux has accepted the update. After mksh R27e though, I've
  fixed the regression testsuite to pass if invoked as root, which a few
  people seem to require&#8230; these who never learn&#8230; furthermore
  I got rid of a few bytes in <tt>/etc/profile</tt> on FreeWRT (and thus
  in ports/shells/mksh/pkg/DESCR too), using the <tt>local</tt> keyword,
  ipv the <tt>typeset</tt> keyword.</p>
 <p>We now have adduser(8) and openssl(1) asn1octetstream (which is also
  documented in openssltool(1), and will be fed upstream), to complement
  my vnconfig(8) -f addition. That was quite some hard work, done with a
  bottle of Met and bottles of beer shared among us at yofuh's place. It
  is HOT!</p>
 <p>I also fixed contrib/samples/etc_profile for foreign hexdump(1) that
  doesn't support %_aX, added some acronymes, and benz did cups. The web
  page of <a href="http://mirbsd.de/mksh">mksh</a> got pushed up to -current and a text
  about its requirements.</p>
 <p>Adding the above functionality is a milestone, btw.</p>

----
Date: 09.07.2006
Author: tg@

 <p>Thanks to Dr. Pfeffer (pepper) of BOSng, I've now also been out to a
  geocacheing session for the first time, with his Windows&reg; PDA that
  can do GPS. It took us <em>quite</em> some time, but it was helluv fun
  and I hope we'll continue the journey.</p>
 <p>The image: <img src="http://www.opencaching.de/statpics/106521.jpg"
  alt="statistics" /> will show the hopefully increasing number although
  I won't join the hype. I don't like hypes.</p>

----
Date: 16.07.2006
Author: tg@

 <p>I started to hack on MirOS again &ndash; despite the heat &ndash; on
  the distrib stuff, specifically (using makefs(8), and synching between
  the architectures), wbx@ called me out for some FreeWRT work *sigh* (I
  have some TODO there too). So that's it for today I guess. But I'll be
  back.</p>
 <p>Benny finally inaugurated the aqua category in MirPorts.</p>
 <hr />
 <p>Hm&#8230; hacking on FreeWRT&#8230; bad code quality, although I may
  not rant as much as I want because, as a core developer over there too
  (yes, I really am one) I represent the project *sigh* but at least the
  rants won't be found here that easily.</p>
 <p>paxmirabilis (MirCpio, aka pax(1) cpio(1) tar(1)) is now being used,
  instead of GNU tar. It got some enhancements (eg. extracting to stderr
  or rough glibc compatibility) in the progress and might include direct
  gzip I/O, and even ZIP (maybe zip, at first only unzip) support later.
  Yay for MirOS!</p>
 <p>My idea is to replace busybox' cpio/tar/pax by paxmirabilis as well,
  but that will probably only be an option. No idea which one is smaller
  though.</p>
 <p>We also plan to make the packaging system more alike to MirPorts, to
  reduce overhead and improve legibility. Targets such as update-patches
  will be added, and the other targets renamed too. In general, we would
  like to clean up the mess left there&#8230;</p>
 <p>Maybe it could generate Config.in and the ipkg control file from the
  Makefile then (for the developer to check in, though) kind of like the
  DESCRIPTION and CATEGORY fields in a MirPort.</p>
 <p>There's much more stuff to do, but for now I'm cursing about da shit
  (Linux&reg; / iptables) being unextractable on a case-insensitive fuck
  filesystem like the damned Macintosh have.</p>
 <p>Ew, yeah. ncurses was being configured for the build system, instead
  of the target system. Many ports call autoconf (seen by the message to
  please provide AUTOCONF_VERSION environment variable), or are in other
  respects plainly broken, or try to access /dev/pts or something. A few
  ports still use host tools (e.g. openssl uses nm).</p>
 <p>For MirOS, I should plan to feed back binutils and gcc-4.3 ports (to
  cross-build from lunox to MirOS, at least) to the FSF. Maybe we could,
  then, even make a Soekris FreeWRT with MirOS kernel and BSD libc? That
  all isn't even limited to WRT boxen anyway, we plan much more.</p>
 <p>Oh yes, and the entropy d&aelig;mon&#8230; need to investigate about
  how *nix IPC works best though.</p>
 <p>#include &lt;rant/usual/subversion&gt;</p>
 <p>If I get the clues about when mksh segfaults, we should bring out an
  mksh R28 with the fix, I think. Optimally so that mksh R28 is the code
  which corresponds to MirOS #9bis. Other fixes, such as manual page, or
  so, are of course greatly appreciated. Send diffs ;)</p>
 <p>Most funny thing of today: Mac OSX Tiger comes with /usr/bin/make as
  GNU make 3.80, but this apparently is not &quot;new enough&quot; for a
  certain package manager, namely Fink, which brings in its own version,
  GNU make 3.79.1 &ndash; do I need to say that both don't run correctly
  and the MirPorts Framework is required for GNU make 3.81 on Mac OSX as
  of now? Besides&#8230; someone tell the FSF that case-insensitive file
  systems are <em>not</em> only occuring on DOS/Windows&reg;!</p>

----
Date: 19.07.2006
Author: bsiegert@

 <p>It has been a rather long time since I have written something here.
  In the meantime, I moved to Saint-Louis and begun my summer
  internship. I am working on explosives, and dangerous ones at that.
  But the people at the institute are very nice and let me work freely
  on my subject. There is not much to do in the evening, as the town
  is small. Even if Switzerland and Basel are only a few hundred metres
  away (really!), I don't go there too often.</p>
 <p>After all the interesting talk with Uriel on FrOSCon, I really installed
  Plan 9 on two machines and tried to work with it. In fact, I am writing
  this in the acme editor on Plan 9. I managed to get my own user
  environment as well as TeX running. There is even a web browser
  called Abaco, which does about as much as dillo but has only 5000
  lines of code. It even does tabbed windows, acme-style. The only
  downside is that I cannot commit from Plan 9 as the ssh client only
  does ssh1.</p>
 <p>But even with all the other stuff, I still do MirOS and MirPorts
  development. I am on a modem line here so don't expect stuff that
  requires huge downloads. I have been working on wxGTK 2.6.3 with
  the libtool patch from pkgsrc. So far, I got segfaults in gcc and even
  in /bin/sh during the build. I don't know why but the Makefiles
  expect <tt>$(top_builddir)</tt> to end with a slash, which terribly
  confuses the poor shell. I also have distfiles for cairo 1.2 and gtk+
  2.10 on my machine, so this might come in the not-too-distant
  future. I finally put something into the aqua category: AquaTerm.
  However, there are no other ports that use it at the moment.
  math/gnuplot will pick it up if it is installed, I am changing that.</p>
 <p>I am getting slower with all the typing because I am constantly
  changing keyboards between German, French and US&mdash;the
  latter for example here in Plan 9 because I don't know how to
  change the keyboard layout ...</p>

----
Date: 21.07.2006
Author: tg@

 <p>Other than fixing the website ;) I did only some minor stuff just to
  keep activity. I also &quot;have to&quot; hack on FreeWRT but it's way
  too hot for anything productive.</p>
 <p>GNU make sucks.</p>
 <p>Benny should just use the US keyboard layout anywhere.</p>
 <p>I had a hard time fixing FreeWRT, but I eventually succeeded. MirOS,
  on the other hand, didn't get short either: I renamed /bin/sh to nbsh,
  to have the option of changing it to mksh until the bugs are found and
  fixed (nbsh(1) will be kept anyway, so people can check their scripts,
  to make sure they still work with ash) while they're reported upstream
  (to TNF), and we got a pciutils (lspci) port. gecko2 installed MirOS 9
  and current ports, and we thusly found a small buglet in MirPorts (GNU
  stuff) which got fixed as well. (growfs(8) works well.) I also did few
  more minor things to clean up and prepare for other changes.</p>

----
Date: 23.07.2006
Author: tg@

 <p>I planned to write a more lengthy wlog entry but since I have gecko2
  here visiting me for a few days I don't get to do as much stuff as I'd
  like to (but on the other hand he helps me cleaning up the appartement
  and spots a few rare MirPorts bugs). Thus, this must suffice:</p>
 <p>I wonder why Benny is still using the ancient operating system, Plan
  9, when there is <a href="http://sshdos.sf.net/">an SSH v.2 client</a>
  for the progressive operating system MS-DOS&reg; &ndash; he should use
  that instead, so he could directly commit from there. (For the record,
  an <a href="http://ftp.kiarchive.ru/pub/msdos/unixlike/korn/">MS-Shell
  2.3</a>, along with a few unix-like utilities, runs on 8088 CPUs quite
  fine, along with <a href="http://www.fdisk.com/doslynx/bobcat.htm">the
  best web browser ever</a> (but if you have an 80386, you be better use
  <a href="http://www.rahul.net/dkaufman/">the real thing, complete with
  HTTPS/SSL support</a> instead). The site even has an entropy gathering
  d&aelig;mon (URANDOM$), so&#8230; Benny, now please get and install <a
  href="http://www.drdos.net/">some DOS</a> or my well-known image.</p>
 <p>That MS-DOS shell above has got most (not all tho) mksh(1) features!
  Yay for <a href="http://mirbsd.de/mksh">the Korn Shell</a>!</p>
 <p>If you update MirPorts, don't forget to re-run Setup.sh(8)</p>
 <p>I've finally got my lazy arse around to start the redesign and sparc
  enhancement of <tt>src/distrib/</tt>, but couldn't yet finish the work
  as &#12466;&#12483;&#12467;&#12491;&#12367;&#12435; wants me to sleep.
  I've even merged bsd.rd, floppy <em>and</em> iso9660 images generation
  into that and will try to make it even better. The sparc miniroot was,
  still, not touched by me though. Also, there's no live CD yet :)</p>
 <p>Don't forget to always use <b>irc.mirbsd.org:6668</b> to connect the
  Freeforge IRC network (use port 6666 if your IRC client does not speak
  TLS/SSL and you're too lazy to add an irc bridge in inetd.conf(5)). We
  still sit in <tt>#bsd</tt> and <tt>#mirbsd</tt> (as well as Freenode's
  <tt>#mksh</tt>).</p>
 <p>mksh(1) is now /bin/sh, the other one is nbsh(1) (/bin/nbsh) for now
  until the bugs are fixed. When MirOS #9bis gets released, its codebase
  will be tagged as the next version of mksh (R27f) as well.</p>
 <p>I probably forgot many thing but it's late and this FreeWRT thingy's
  been distracting me (let's let wbx handle stabilising ;) and it hasn't
  yet cooled down much either. So please forgive me.</p>

----
Date: 26.07.2006
Author: tg@

 <p>I planned to write a more lengthy wlog entry but since I have gecko2
  here visiting me for a few days I don't get to do as much stuff as I'd
  like to (but on the other hand he helps me cleaning up the appartement
  but also makes me work :'( hard&#8230;). And now I even have headaches
  and get some VPN DNS whatever confusion instead of working on distrib.
  Also he tells me to goto bed at weird early hours, and so.</p>
 <p>But the kitchen already looks more clean, and I did my job too.</p>
 <p>It's <strong>too</strong> warm a summer.</p>

----
Date: 28.07.2006
Author: tg@

 <p>More fun with FreeWRT (it sucks) and IRC (we now bridge a channel in
  two networks, but the TCL plugin for eggdrop sucks worse, so ciruZ has
  threatened to rewrite it (including the bot) in Ruby &ndash; so gecko2
  can't configure it to death <em>and</em> it won't talk).</p>
 <p>It's still fairly warm.</p>
 <p><tt>herc.mirbsd.org</tt> now serves dynamic IPv4&#8230; TTL is 60 so
  beware, and it can't be updated in case herc goes down.</p>

----
Date: 30.07.2006
Author: tg@

 <p>Benny has started fixing the website, finally (thanks!)</p>
 <p>He also committed a www/firesomething security update.</p>
 <p>Yay for bsiegert!</p>
 <hr />
 <p>I've played around and fixed a little too, not too much.</p>

----
Date: 03.08.2006
Author: tg@

 <p>I did some major cool mksh(1) work. Please test the beta. Details in
  <tt>#mksh</tt> (freenode).</p>
 <p>I'm off for the weekend.</p>

----
Date: 08.08.2006
Author: tg@

 <p>I just came back from a prolonged weekend at my best friend's place.
  That's why there hasn't been much activity, except Benny's starting an
  update on documentation.</p>
 <p><a href="http://www.feyrer.de/NetBSD/blog.html/nb_20060808_0118.html">Hubert</a>
  should just always use <tt>cvs -Rq up -PAd</tt> like every CVS user in
  the world (according to MirOS docs). I did think of implementing a tag
  in the output for sticky files for him, but I don't think it's worth a
  try because stickiness can actually be useful (tracking branches).</p>

----
Date: 09.08.2006
Author: tg@

 <p>Today it was rainy, depressive, and headaches arrived. Not the best,
  but a chance to hack something. I couldn't do much, but I improved the
  shell again and got an old NetBSD&reg; PR (30842) finally fixed.</p>
 <p>I also cleaned up some of the stuff in src/etc/ (especially rc which
  should be faster and more reliable now). Works for me.</p>
 <p>I've also started on reworking the text of the <a href="http://mirbsd.de/mksh">mksh
  page</a>, but can't get myself to finish it. Call it summer hole.</p>
 <p>Although I'm still looking for employment I can't get myself around,
  sending out applications etc., because of these bad circumstances like
  the weather etc. If someone wants to pay 1000 &euro; netto (i.e. taxes
  and so on already subtracted), or more, for a unix developer or admin,
  please contact me.</p>

----
Date: 10.08.2006
Author: tg@

 <p>Despite it all, I made lynx and GNU groff mirports, reinstated tyler
  as developer by his own request, fixed *roff macros (new MirNroff cpio
  distfile for Interix might be required soon), enhanced and fixed docs,
  helped FreeWRT people (website/server is down, we know), etc.</p>
 <p><a href="@@RELPATH@@MirOS-Licence">Licence</a> is now up to date again, and links
  are actually links.</p>
 <p>Sendmail 8.13.8 is out, but not a high-priority update.</p>

----
Date: 18.08.2006
Author: tg@

 <p><a href="http://mirbsd.de/mksh">mksh</a> is now probably ready to release R28.</p>
 <p>If the person responsible for the existence of /usr/bin/libtool on a
  Mac, which is <em>not</em> GNU libtool, and that this pathname is hard
  coded in gcc's specs file, gets to meet me, in a park at dark night, I
  can't be held responsible for the outcome&#8230;</p>
 <p>I hope src/distrib/ is in usable shape again. I'll fix missing parts
  and build a snapshot afterwards, maybe without live cd for now, though
  that'd suck. The sparc live cd is not completed, although the miniroot
  should be buildable now, for the first time in MirOS ever.</p>

----
Date: 19.08.2006
Author: tg@

 <p>I unbroke HEAD, so snapshots can be built. I couldn't yet finally do
  the required work on the baselive CD, due to distraction (chess with a
  friend who needed attention) in the evening. Expect a new snapshot (of
  i386 only) soon (sparc will take fairly longer).</p>
 <p>tyler@ yelled at me in Jabber today to "STOP COMMITTING SO MUCH :p",
  and then begged for MirPorts ${SYSCONFDIR}/screenrc&#8230; seems as if
  he found a unique selling point, finally&#8230;</p>

----
Date: 24.08.2006
Author: tg@

 <p>During a Netzladen session @LUUSA, mksh(1) now works on Plan 9.</p>
 <p>I've been hacking random stuff, improving and adding user feedback I
  got, but I'm still primarily looking for a job in the area programming
  or system/network administration. Contact me if you have any hints, in
  this region.</p>
 <p>While we're tracking down a few remaining bugs in the package tools,
  our lynx port is the best one available for the Mac and I'm submitting
  offsprings (e.g. mksh, mirmake) to the FSF directory.</p>
 <p>bsiegert@ and tyler@ started hacking on the new website.</p>

----
Date: 26.08.2006
Author: tg@

 <p>Tonight I must write down my thoughts again, as to sort them and may
  bsiegert@ help me with some, as it touches MirPorts and the Macintosh.
  First off I found that ranlib(1) is needed on Darwin and added it back
  to &lt;bsd.lib.mk&gt; in an if clause. Now, we're already building the
  standard mirmake library in ${LOCALBASE}/share/mmake/libmirmake.a (the
  default location is different, but I'm focusing on MirPorts, willingly
  forgetting MirMake works on GNU/Linux too for now). I intend on adding
  a lot of functions to libmirmake &ndash; already added arc4random_push
  for systems which don't have it (i.e. everything other than MirOS), an
  arc4random(3) suite for systems which don't have <em>that</em> (Darwin
  didn't have it in older versions (I now scan with autoconf-style tests
  instead of using hardcoded #ifdefs) and the one of Interix sucks, and,
  it can be replaced by one spawning an EGD later), libohash, fgetln(3),
  i.e. everything which is required for MirMake anyway and more. Now, an
  enhanced libmirmake is not a problem. but not a benefit either, unless
  it gets used, which it doesn't, yet. Adding "-L${.SYSMK} -lmirmake" to
  LDFLAGS is a way to easily do that, but then we're entering the libgcc
  hell: what if we link libfoo, update libmirmake, and link progbar with
  libfoo? Suddenly, we have two different versions of libmirmake's code.
  Clash. That's why we need libgcc_s.so and libmirmake.dylib. Now that's
  not the problem either (I started versioning it already), but where to
  place the library? Can we use rpaths etc. so that on all systems, when
  we link against libmirmake, its location is added to the binary built,
  or library, of course, so that it can be found even if it's outside of
  any normal shared library paths and LD_LIBRARY_PATH variables? Or must
  I go the way to place it in ${LOCALBASE}/lib like any other shlibs? In
  the latter case, we could probably do a two-stage build of everything,
  leaving the Interix bootstrap (NOMAN) case up to the caller; that's an
  interesting yet slower (in compile times) outcome. Or did I overlook a
  totally different thing?</p>
 <p>Maybe we should call libmirmake libshouldbeinlibc &ndash; oh wait, a
  library of that name already exists in GNU OS. (On that matter, Debian
  currently investigates the case of libast, which exists twice as well,
  once as &quot;assorted spiffy things&quot; and once in e.g. ksh93 (the
  shell), where the latter definitively has age precedence. I wonder how
  MirPorts is going to handle this and who's going to do it. Fact is, we
  can't have two libraries with the same name, and the devel/libast port
  is probably going to have to change its name.</p>
 <p>While tinkering with the mirmake build system, I also added autoconf
  style scans to mksh's. And mirmake's build should definitively stop if
  errors are encountered. PS: Solaris /bin/sh is&#8230; weird.</p>
 <p>Developing on Windows&reg; 2000 is different. Not that productive if
  you ask me, you're much more limited if you are used to terminal-based
  operations. At least, the combination of PuTTY, Cygwin (ssh, scp, cvs,
  working text editor whose poll loop doesn't, like 16-bit DOS jupp, get
  my laptop to turn itself off due to heat), and Interix provides a work
  environment which is slightly suitable, but I still don't have perl5.8
  for the mksh testsuite or stuff like that, and my fan is spinning. The
  hardware support of MirOS is so much better.</p>
 <p>bsiegert@ might also want to convert ports/Hints into something more
  usable to the end user, and we had a request for MirPort howtos on the
  mailing list today too. <a href="http://sysjail.bsd.lv/">Sysjail</a> 1
  was released today, and I like the benchmarks, which show MirOS easily
  outperforming OpenBSD and even NetBSD&reg; in most things.</p>
 <p>Angelo (the MacWorm hacker) is currently in town. I got quite drunk,
  last night, I must admit. I had an interesting hangover today. Hacking
  helped me to overcome it though, as did much sleep (too much). This is
  not improving my bank account's or my work situation though.</p>

----
Date: 27.08.2006
Author: bsiegert@

 <p>I started working on the all-new MirOS website in the all-new
  <tt>web</tt> module. At the moment, no new content nor design has been
  incorporated. However, I started writing a parser for news and wlog
  entries. These entries can be dynamically converted to HTML and RSS
  formats.</p>
 <p>The entry format is largely self-explanatory and like an e-mail
  message. The header has metadata of the form "Name: value" and is
  delimited by an empty line. Then comes the body, delimited by a line
  with four hyphens. New entries are added at the bottom but I show an
  example of sorting antichronologically on <tt>index.php</tt>.</p>
 <p>There won't be any more base64-coded filenames. I rather want to use
  php like you would use server-side includes, i.e. <tt>&lt;?php require
  "header.php" ?&gt;</tt>.</p>
 <p>tyler@ pointed me to <a href="http://www.oswd.org/">oswd.org</a>, a
  website with free design templates. I have some ideas on how I would
  like it to look but nothing definitive yet.</p>

----
Date: 27.08.2006
Author: tg@

 <p>Okay, the <a href="@@ABSPATH@@/newsite/">new website is online</a>, with fixes.
  I don't think using other peoples' design is a good thing, because, if
  you don't use a design of your own which you <em>don't</em> licence to
  others freely, you aren't safe from copycats. This is a reason for the
  &quot;must not copy the design of MirOS or (my) personal webpage&quot;
  clause in the old www/LICENCE file, by the way. (I don't like the news
  entry format much &ndash; it has too much red tape (everything before,
  and <em>especially</em> the colon-space (use an equals sign, if you're
  going to use a key-value pair at all!), in the header).</p>
 <p>Played with MacOS 7.5.3 in Basilisk &#8545; and SheepShaver today. I
  think the GUI is quite intuitive. The OSnews article on GEOS was quite
  the good read for the evening too, and fasm (flat assembler) looks not
  bad either, and it has a funny BSD-style licence.</p>
 <p>On the other hand I ended up doing my own letter form for a DIN 5008
  letter all afternoon, because there are no good ones available, and no
  single one for Lotus Word Pro 9.5 (Millennium Edition) for Windows, at
  all! This sucks, the freely available specs (the standard itself costs
  some 30-50 &euro;) suck and contradict themselves, but IMHO, I crafted
  something usable which doesn't make me look bad to my hopefully future
  employer at the first look. (On related news, I am still looking for a
  job, anyone?)<br />PS: Long live (AFPL) Ghostscript!</p>
 <p>I'm pondering to release mksh R28 now, codename <tt>Pleitegeier</tt>
  (not an <a href="http://grml.org/">austrian word</a> though). I should
  move some of the MI Plan 9 support code into the branch though, as I'm
  suspicious of it causing issues with job control in Plan 9 itself. The
  <a href="http://directory.fsf.org/search/fsd-search.py?q=mksh">FSF and
  UNESCO directory of Free Software</a> sadly still doesn't list it.</p>
 <p>I should convert the entire repository to strict ISO_646.irv:1991 or
  UTF-8 conformance. Maybe post-#9bis, because I'd really like to get it
  out of the doors, but then really (including change logs, mailx(1) and
  submit.cf default, etc.) and correctly.</p>
 <p>Cygwin, Interix, various Mac and Windows instances, GNU and BSD suck
  <em>all</em>, just in different flavours and strengths. And Solaris is
  the funny dot on the i. (What is Plan 9 APE then? I guess I don't want
  to even know.)</p>

----
Date: 03.09.2006
Author: tg@

 <p>Yeah, to hell with OSI, the FSF now has two webpages which are under
  the MirOS licence: <a href="http://directory.fsf.org/mksh.html">mksh's
  page</a> and <a href="http://directory.fsf.org/mirmake.html">mirmake's
  page</a>, and <a href="http://directory.fsf.org/jupp.html">the page of
  jupp the editor</a>. Cool!</p>
 <p>We have a <a href="http://www.mirbsd.org/newsite/">new design</a>, I
  must say I'm&#8230; shocked. (And make these &lt;h2&gt; smaller in the
  CSS, please.)</p>
 <p>Other than that, not much noteworthy happened.</p>
----
Date: 13.09.2006
Author: tg@

 <p>The more you work with software, the more it sucks. I found out that
  I have to rewrite at least mksh(1)'s emacs editing mode, due to design
  bugs rendering command-line editing with tabs broken, but better re-do
  the whole damned thing (taking 64-bit integers and wide chars into the
  initial design considerations). Same goes for MirPorts, after stumping
  across a bazillion more quoting bugs. If I had the money&#8230;</p>
 <p>&Agrave; propos rewriting&#8230; don't you dare mention FreeWRT.</p>
 <p>A computer-illiterate visitor today decided the new design sucks too
  and prefers the old one. Yay! I still wonder why we didn't keep my CMS
  (or rather, excuse for not having a CMS) and changed only the content;
  dynamic page elements, such as news or wlog, could've been implemented
  within the existing framework as well.</p>
 <p>Yep, MirOS now hosts foreign projects within its CVS. Trusted people
  only, of course. (Time to redesign CVS's operation.)</p>
 <p>I'm missing a lot more catch-up things but you should have a look at
  <a href="http://bsdstats.org/">BSDstats</a> and their sub-page over <a
  href="http://bsdstats.org/mirbsd/">MirOS</a>.</p>
 <p>Somehow I've been missing &quot;the spirit&quot; lately. Add to that
  the truth that, out of MirOS, I've basically written <em>nothing</em>,
  only doing integration work or writing (sometimes larger, such as with
  e.g. djbdns) patches. Even these rarely add major functionality. Magic
  is only contained in the one thing I have really written myself and of
  which I can be proud, the licence. Sucks, if you consider yourself not
  a lawyer but a programmer, eh? On the other hand, integration work is,
  both, importand and a good starting point into snapping how all works.
  Maybe I should really &quot;clone&quot; MirBSD again, this time not as
  an OpenBSD fork, but as a modular smallish system not even self-hosted
  in the beginning. Starting with the cvs- and ctm-based infrastructure,
  then some kind of packaging tools, initial utilities including an mksh
  rewrite, a bootloader, kernel, installer, third-party apps. But that's
  a thing I can't do alone unless I dedicate myself fully to it and some
  other person maintains MirOS. I guess I will never get that far. Wise,
  it is not, to reinvent the wheel. Building upon and improving existing
  solutions (which suck) is the way to go in this world. Does this suck?
  I guess it does. And I guess I'm not the first dreamer.</p>
 <p>And I guess I don't have the vigour to do even one of them :'(</p>

----
Date: 20.09.2006
Author: tg@

 <p>I hope the last wlog entry did not scare too many of you. First, I'm
  apologising to Benny for slandering his effort. Second, MirOS is going
  to continue, and in fact, Benny and I have talked about long-term plan
  (not 9) regarding packages, syspkgs, and so on. This is, seriously, an
  idea that will take years to complete, so we won't discuss it for now,
  unless someone asks us (over a few beers *hint hint*).</p>
 <p>While my work situation did not improve yet, I hope to be invited to
  a personal talk at some companies soon&#8230; who knows&#8230;</p>
 <p>I hacked quite well on fwcf &ndash; our first hosted foreign project
  &ndash; that's some good creative work, finally.</p>
 <p>mksh(1) world domination is going to succeed.</p>
 <p>-rHEAD contains lots of security updates; yes I promised a snapshot,
  quite some time ago actually, to be out shortly. Okay okay.</p>

----
Date: 21.09.2006
Author: tg@

 <p>Someone remind me to get <tt>Darren Tucker</tt> a beer.</p>
 <p>I need plumbing in Plan 9! If I select a line like</p><pre>
/usr/src/foo/bar/bar.c:123: warning: fnord
 </pre><p>then I mark the filename with the mouse, type "jupp ", hit the
  middle mouse button, press return. That could be easier. Plan 9.</p>
 <p>A person asked me in private mail how he could use the root account,
  on his freshly installed (in MS Virtual PC) MirOS. I told him that one
  uses sudo(8), but I still wonder why people do not ask in public, on a
  mailing list. Even if you ask in German there, you won't be considered
  impolite because about half of our usership could still make use of an
  answer in that language. (Of course it's better to write English.) But
  keeping these mailing lists and the archives is work, so, please, if a
  question appears, use these, or at least IRC.</p>
 <p>Update: looks like it's greylisting. If the 451 is received the user
  gets a failure reply even though the message will be sent correctly ~4
  hours later. If everyone would just be using IPv6&#8230; at this rate,
  spammers will be using IPv6 before the rest of the world. Even the uni
  of D&uuml;sseldorf.</p>
 <p>make(1) needs a break-and-continue mode. Oh, and, if you change some
  types in the compiler, make sure to re-build and install all libraries
  before rebuilding the system, otherwise xlock might not link because a
  symbol was missing in libstdc++ (do I need to change the shlib version
  now? no idea, I think nm might know).</p>

----
Date: 24.09.2006
Author: tg@

 <p>Did some serious FreeWRT hacking at wbx@' place yesterday. He showed
  me how to roll my own Sushi and we had enough wine to get me a serious
  hangover today.</p>
 <p>Benny and I agreed on renaming #9bis into #10 because some seriously
  deep changes which could not entirely be avoided. This way we can also
  polish a little more and make one or two user-visible changes, but I'm
  trying to not delay the release any more for that reason. Afterwards a
  #11 will be released, with the goal &quot;sync with OpenBSD 4&quot;. I
  also have plans for #12 which will take quite a long time.</p>

----
Date: 03.10.2006
Author: tg@

 <p>Advertising pays off, the Sourcemage guy (morfic) not only fixed the
  spell (their lingo for port), but also threw its name into some random
  IRC conversations in places I don't dwell. Cool.</p>
 <p>I got a surprise when, preparing the new snapshot with Live CD to be
  issued, the BSDstats.org code didn't run any more. Luckily, we got the
  bugs and updates past that state. Getting ftp(1) to not pretend it can
  handle HTTP/1.1 responses did surely help.</p>
 <p>Installing Windows&reg; 2000 on a Pentium &#8544; notebook without a
  CD-ROM drive can be entertaining. While it's a real PITA, having MirOS
  at hand eases the pain very much. (And I discovered a local DoS attack
  in our kernel, default installation, during the process.) However, the
  ancient game (Age of Empires &#8544;) I was installing&#8230; I needed
  a no-cd crack, and all failed but one, which was merely a text file of
  15k credits and four &quot;patch these and be happy&quot; instructions
  &ndash; what I did. Now, which editor can I use on DOS for a 1'622'016
  bytes executable? Volkov Commander and debug.exe fail, so I used jupp.
  Yes, right. A Cygwin compiled (4 files: libcygwin, libncurses, jupprc,
  jupp) executable of my favourite text editor. And it worked for me and
  saved my arse from the pain of copying back and forth, without a putty
  installed (yet &ndash; will follow). To only change a 7504 conditional
  jump into an EB63 at D769F and adjust F7D8 at D7706 to 4090 is enough,
  contrary to the beliefs of people making 500+ KiB RAR/ACE files with a
  PE binary (can you spell trojan?) inside. Anyway, the laptop initially
  wasn't intended for gaming but for office work under Windows. However,
  the hardware (Compaq Armada 4220T) is cool, so I saved some 384 MiB on
  wd0 for a full (yet kept quite minimal) MirOS+X11 install, using a DOS
  PAGEFILE.SYS for swap.</p>
 <p>I spotted quite some bugs working on the snapshot &ndash; I believe,
  it's already in a <em>much</em> better shape than #9. And I kept a few
  great ideas for past the snapshot, even. (So that people can upgrade a
  running system to get the security fixes, some of which I incorporated
  before That &#416;ther BSD.) What I didn't spot is Benny.</p>

----
Date: 18.10.2006
Author: tg@

 <p>High-End: we now run past 2038 as well: in 2100 (32 bit), almost no-
  thing breaks, except a few library functions and ffs (UFSv1) timestam-
  ps, in 2200 (33 bit), network and shutdown don't work any more, but we
  at least don't crash.</p>
 <p>Weird-End: sysctl(3) ddb.crash now can force a kernel panic.</p>
 <p>Low-End: I'm helping Vutral (real name known) to install MirOS on an
  8 MiB RAM 80486DX system. That's fun, but the serial console is a slow
  UMTS link, which is NOT fun.</p>
 <p>French-End: Benny apparently is in Germany now and of course, thanks
  Deutsche Telekom, he doesn't have internet access. *sigh*</p>
 <p>Data-End: I lost herc:/home and one of two underlying parts of raid0
  (RAID level 1) alias herc:/ &ndash; and as if that would not be enough
  I had an rsync accident (missing directory level on destination combi-
  ned with --delete) losing most of the stuff in my $HOME which was in a
  directory on /&#8230; note to self: dont keep backups within $HOME but
  use a dedicated directory tree.</p>
 <p>GNU End: gcc miscompiles not only C++ but also C code with a certain
  option <tt>-fomit-frame-pointer</tt> &ndash; caught by my favourite <a
  href="@@RELPATH@@jupp.htm">text editor</a>.</p>
 <p>Money End: At last, I get some state money (by far not enough), more
  might come, but I'd prefer a job. OTOH they'll pay for new teeth, more
  than they had paid if I were employed. But the pain's the same.</p>
----
Date: 20.10.2006
Author: bsiegert@

 <p>I haven't written anything here for quite a while, so here is a
  little update. I moved out of France and now live in Saarbr&uuml;cken.
  I will hopefully have both telephone and DSL service soon&mdash;it is
  scheduled for tuesday, but let's say I will believe it when I see it.
  I started work on a port of Qt 4.2.0, as close as possible to the
  upstream sources. Those crazy patches from OpenBSD often break more
  than they fix. Qt is quite a beast though: a 36 MiB .tar.gz with no
  .tar.bz2 available, non-standard configure, .la files generated by C++
  code, etc. Now I know why I like Gtk+ better :). Seriously, the
  tarball gained more than 4 MiB since 4.1.x. I knew that Mozilla is
  bloated (Firef*x is ~36 MiB compressed) but I was shocked to see Qt is
  just as big.</p>
 <p>And now for something completely different: While writing the report
  for my summer internship, I came across a number of problems regarding
  pictures and their insertion into a LaTeX document. I will note my
  solutions here so that I don't forget what I did, even if this is a
  wee bit off-topic.</p>
 <p>First problem: Inserting a plot done with gnuplot. Obviously, there
  are many ways to do this but here is what I do. My gnuplot file looks
  like this (example):</p>
<pre>set encoding iso_8859_1
set term postscript color solid eps enhanced lw 2 "Helvetica" 20
set output "sucres2.eps"
set xlabel "Temp{\351}rature ({\260}C)"
set ylabel "Heat Flow (W/g)"
set key top right
plot [150:200] 	"bs06.4Kmin.txt" using 1:3 with lines title "exc{\350}s en chlorate"
</pre>
 <p>The "set term" line is the most important here. color solid gets me
  a coloured plot without dashed lines. eps generates a correct bounding
  box and makes the plot a nice 12x7 cm. enhanced allows me to write
  stuff like "CO_2" and accented characters: {\260} for example inserts
  the latin-1 character with the octal code 260, a degrees sign. lw 2
  makes the lines a bit thicker for better visibility. The 20-point font
  is good if you scale down the plot (like me).</p>
 <p>Now you'll need to transform this into a pdf file. Use epstopdf:</p>

<pre>$ epstopdf -d sucres2.eps
* Input filename: sucres2.eps
* BoundingBox comment: %%BoundingBox:
* Output filename: sucres2.pdf
* Ghostscript command: "C:\Program Files\gs\gs8.54\bin\gswin32c.exe"
* Compression: on
* Ghostscript pipe: "C:\Program Files\gs\gs8.54\bin\gswin32c.exe" -q -sDEVICE=pdfwrite  -sOutputFile=sucres2.pdf - -c quit
* Scanning header for BoundingBox
* Old BoundingBox: 50 50 410 302
* New BoundingBox: 0 0 360 252
* Offset: -50 -50
* Ready.
</pre>

 <p>Note the correct bounding box. For inserting this, I do:</p>

<pre>\begin{figure}
\centering\includegraphics[width=8cm]{Plots/sucres2}
\caption{foo}%
\label{fig:sucres}
\end{figure}
</pre>

 <p>Figures you have only as Word drawings are a whole different beast.
  But there is a way to do it: First, mark all elements of the drawing,
  copy it and insert it into a new document by itself. Important: You
  have to position it as close as possible to the lower left corner of
  the page, as this the origin in PostScript. Next, use File &gt; Print,
  select a PostScript printer and check Print to file. Open the
  resulting .prn file in GSview (I assume you are under Windows -- you
  use Word, right?). Select File &gt; PS to EPS and uncheck Automatically
  calculate Bounding Box. Select the margins of your drawing with the
  mouse and save it under a file name ending in .eps.</p>
 <p>Now comes the interesting part: You open the .eps file in a text
  editor. Among the first lines, you will see a BoundingBox DSC comment,
  like this:</p>
 <p><tt>%%BoundingBox: 11 11 363 209</tt></p>
 <p>Note these values. Search for "PageSize". You will find a line
  like:</p>
 <p><tt>&lt;&lt;/PageSize [595 842] /ImagingBBox null&gt;&gt;
  setpagedevice</tt></p>
 <p>Replace the values in the brackets by the third and fourth value
  from the bounding box above. Save and quit. Again, use epstopdf like
  above. Open the pdf in Acrobat Reader. It should have only your graph
  without any additional white space around. For the insertion into your
  LaTeX document, use the same lines as above.</p>
----
Title: Thoughts on MirPorts dependency handling
Author: bsiegert@
Date: 22.10.2006

 <p>While I was in the train today, I looked at some of the more arcane
  inner workings of MirPorts: internal dependency handling.</p>
 <p>Packages have dependencies. There are three types of them in
  MirPorts: build, run and library dependencies. I won't talk about the
  former here. MirPorts inherited a very convoluted way of handling
  those dependencies from OpenBSD, including several passes over the
  packing list using various scripts and the infamous <tt>pkg</tt>
  utility. <tt>pkg</tt> is essentially undocumented and constitutes a
  failed attempt of Marc Espie to rewrite the pkgtools in perl. It has
  only one subcommand, <tt>pkg dependencies</tt> with three
  sub-subcommands <tt>show</tt>, <tt>solve</tt> and <tt>check</tt>.</p>
 <p>Dependencies are declared via the LIB_DEPENDS and RUN_DEPENDS
  variables in the port Makefile, for example:</p>
 <pre>LIB_DEPENDS=           apr::devel/apr/apr</pre>
 <p>From there, they are passed to a recursive solver in bsd.port.mk,
  which outputs commands like</p>
 <pre>@libdepend apr-util-0.9.12-0-bsddb:apr.0.9:apr-*:apr-0.9.12-0</pre>
 <p>into <tt>w-*/pkg/depends</tt>. The four arguments are called name,
  libspec, pattern, and def. The <tt>@newdepend</tt> directive is for
  run depends and does not have a libspec. The <tt>depends</tt> file is
  fed to <tt>pkg dependencies solve</tt>, which replaces these lines
  by</p>
 <pre>@comment libdepend apr.0.9:subversion-1.4.0-0-bsddb:apr-*:apr-0.9.12-0</pre>
 <p>Note the changed order of the arguments! What it also does is
  resolve the dependency and write a <i>static</i> <tt>@pkgdep</tt> line
  like</p>
 <pre>@pkgdep apr-0.9.12-0</pre>
 <p>on top. All of those are output into w-*/pkg/PLIST. Upon
  installation, <tt>pkg_add</tt> only cares about the <tt>@pkgdep</tt>
  directives.</p>
 <p>There are a number of problems with this approach. I would like to
  replace <tt>pkg</tt> entirely by C code inside the pkgtools. The
  advantage is a much reduced complexity, the removal of the liability
  that is pkg, and more flexibility: If packages are upgradeable, the
  final resolution of the dependencies should be done by
  <tt>pkg_add</tt> when installing the package. If you have a newer
  version of a dependency installed, we can check if the library version
  matches and still allow the installation. <tt>pkg_upgrade</tt> would
  also profit massively, as the current implementation leaves the
  <tt>@pkgdep</tt> lines intact so that they are effectively
  unfulfilled. This project is promising but it will take me some time.
  Be patient.</p>
 <p>If you want to discuss this, please use the miros-discuss mailing
  list.</p>
----
Date: 24.10.2006
Author: tg@

 <p>After the odds and ends from last time, now the Health End: I'll not
  be available/online for a few days &ndash; I have an appointment at my
  dentist (ouch!) tomorrow, for 1&#189; hours. I'll be recovering at the
  best grandmother ever's place for a while afterwards.</p>
 <p>Stuff like Te&#935; above isn't off-topic, this is open for personal
  ramblings after all, dear Benny. But I must say we prefer non-bzip2'd,
  i.e. gzip(1)ped or compress(1)ed, distfiles (zip, lzh are even better,
  because bzip2 is dead slow and memory hungry), but for e.g. iceweasel,
  it's okay to use bzip2 distfiles because nobody's going to compile it,
  at least not on a machine below 2 GHz, anyway.</p>
 <p>If I can concentrate at all, I've got a few projects I could work at
  during the next days. One of these is an ncursesw mirport (including a
  "wide" flavour for the lynx mirport), another would be to re-work the,
  at least i386, bootloader interna (see below). Also, I've got an idea,
  sorry Benny, how to do a new website for us, which I could code first,
  propose then. Maybe I'll hack a bit on it. It uses a totally different
  approach than both www and web modules.</p>
 <p>Bootloader&#8230; yeah. A few ideas: make stuff like PBR/bootxx, and
  the two MBRs, shell scripts that install themselves, nuke installboot.
  We need a C language helper for looking up block numbers (for ffs) but
  e.g. CD-ROM or raw disc image installs can do without. I'll try to not
  add MirOS specifics, so it could be run on e.g. GNU/Linux too. Also, I
  want a micro-PBR which just loads another PBR from say, sector 15 of a
  CD-ROM, which fits into the first 128 bytes of the first sector, so it
  can coexist with a Sun disklabel. Then, the bootloader could determine
  by reading a sector from the disc whether it's El Torito or not, so we
  won't need mkisofs(8)' -boot-info-table option any more and can use an
  unified bootloader for Live-CD and Live-HDD ;-) boots. That one could,
  then, also make use of MBR partitions &ndash; for example so we have a
  "boot hd0a:/bsd" as usual, "boot hd0,3:/bsd" for MBR partition (that's
  the only way to boot off a FAT partition if the disklabel doesn't have
  a slice for that filesystem), "boot hd0,2,0:/bsd" for extended ones. A
  "machine partinfo" command to display MBR and disklabel entries would,
  of course, make sense and complete that all. Finally, if I get the new
  installboot(8) replacement to be endian-independent and to convert the
  sparc one as well, dual-boot CDs will be much easier. (The sparc stuff
  needs a fake disklabel, but we could even hardcode that, much like the
  hardcoded MBR for macppc.)</p>
----
Date: 28.10.2006
Author: tg@

 <p>I'm back, and we have libncursesw-5.5 as libcurses replacement in da
  tree. One of my teeth still aches, but the doctor will see after it on
  tuesday and pull the strings from the other wounds. (Yuck.)</p>
 <p>Let's see when I can tend to the other projects&#8230; (someone want
  to take on wsconfig(8)?)</p>
 <p>Today, I recompiled screen and mc, and made centericq (sort of) utf8
  capable&#8230; enough for what I need.</p>
----
Date: 29.10.2006
Author: tg@

 <p><img src="http://www.opencaching.de/statpics/106521.jpg" alt="Fun is
  when you found it: Geocacheing with Dr. Pfeffer &amp; Co." />The BOSng
  Duo has struck again, old fun in a new location, and I found my second
  cache rather easily.</p>
 <p>Other than that, I guess we have a new snapshot, and frozen-bubble 2
  with multiplayer is said to be out. I'll check that ASAP. Update: It's
  <a href="http://www.frozen-bubble.org/">true</a>, but IMHO, the new <a
  href="http://www.frozen-bubble.org/downloads/">dependencies</a> suck a
  little.</p>
----
Title: Happy Birthday, cnuke@!
Date: 30.10.2006
Author: tg@

 <p>Note to self: read operator(7) throughoutly, especially the priority
  level of the ?: ternary operator.</p>
----
Date: 01.11.2006
Author: tg@

 <p>While building with MALLOC_OPTIONS=AFGHPZ I found a bug in perl(1)'s
  regexp code. While caught using the 'P' option (cf. malloc.conf(5)), I
  tracked it down to an out-of-bounds write to an array of uint32_ts due
  to a false estimate of the array size. I however can't seem to fix it.
  Also, and this sucks, I decided to write iconv(1) and locale(1) but as
  of now, after trying to hack perl and drinking some Met, can't get my,
  admittedly lazy, arse to do it.</p>
 <p>On the other hand, I fixed more in cap_mkdb(1) and hope that OpenBSD
  will merge the fixes.</p>
 <p>I'm also intending to do a quick utf-8 hack to mksh(1) &ndash; utf-8
  codeset will make backspace remove entire multibyte sequences. Also, I
  plan on adding a '-c &lt;charset&gt;' or so flag to the editors in the
  base system (i.e. ed(1) and vi(1)) so that it'll setlocale(3), then if
  nl_langinfo(3) CODESET replies something different iconv(3) between em
  (need to take latin1 fallback for 'C' locale into account, discuss the
  issue on mailing list first).</p>
 <p>bsiegert@ has phone, yet no 'net, at home now. Yay!</p>
 <p>Actually I won't implement the conversion routine for the editors as
  I found that it's much easier to just open a pipe to iconv(1), which I
  added (written myself) today. locale(1) was taken from TNF though.</p>
----
Date: 04.11.2006
Author: tg@

 <p>I'm not allowed to be the first one. FreeBSD&reg; Ports beat me by a
  mere 16 hours, porting frozen-bubble 2. NetBSD&reg; pkgsrc&reg; hasn't
  updated from version 1, and OpenBSD ports don't even know what that is
  (probably they don't read <a href="http://www.symlink.ch/">news</a>? I
  don't care though, as MirPorts work on that too). It doesn't play back
  the demos (signal 27, SIGPROF, during shelling out to bzcat), and once
  perl crashed with signal 6 (SIGABRT) for me, but that might just be an
  overly large memory eater&#8230;</p>
 <p>On the low-tech side, I fixed more stuff in nroff(1). I like it.</p>
----
Date: 05.11.2006
Author: tg@

 <p>(Not commenting on mksh(1) changes here, see the ML.)</p>
 <p>Yay, my DSL provider just gave me a static IPv4 address. Too bad, it
  does cost me a lot! 4.90 &euro; per month plus once to set it up. How?
  IP addresses must not be paid for, they say. <b>And</b> I don't get to
  set my reverse DNS. Now, funnily, even their own MTA won't accept mail
  from me, which it did before, from the dial-up pool addresses.</p>
----
Title: pkgtools: dependency handling changes
Author: bsiegert@
Date: 13.11.2006

<p>I spent eight hours in the train today, one more than planned. I had
 20 minutes for changing trains but mine was 22 minutes late. Tough
 luck.</p>

<p>I was going to rewrite the dependency handling stuff in the pkgtools
 but I had to clean up the convoluted mess that is pkg_do() in pkg_add.
 The function contained more than 500 lines of code. I did some
 refactoring: the automatic loading of dependencies is now done in
 separate functions. I think recursive autoloading via ftp is broken but
 we don't have binary packages on ftp anyway. However, recording of
 dependencies is now handled much more sanely. Before, the tools did two
 passes over the plist: one for checking the dependencies and one for
 recording them.  Wildcards were newly expanded each time so you could
 not be sure you record the dependency on the same package you checked
 earlier.</p>

<p>For the user, there should be no functional change. pkg_add now
 creates a <tt>$LOCALBASE/db/pkg/pkgname/+DEPENDS</tt> file,
 which contains the correct forward dependencies for the package. This
 file is essentially unused at the moment but will be more important
 later.</p>

<p>These changes will eventually lead to abandoning the dependency
 checker in perl. I already got rid of all calls to <tt>pkg dependencies
 check</tt> in bsd.port.mk; these can be replaced by calling
 <tt>pkg_info -qe</tt>.</p>
----
Author: tg@
Date: 13.11.2006

 <p>An update to the wlog entry of two days ago: I found out that gcc is
  not entirely consistently with the const qualifier and a means to cast
  it away: define a union with two slots &ndash; a <tt>const void *</tt>
  and a <tt>void *</tt> one&#8230; maybe required for const-correctness,
  because some of the interfaces (such as execve(2)) suck, but it is NOT
  an excuse for bad code, so don't you ever use it unless impossible AND
  guaranteed.</p>
 <p>I did upload a St. Martin snapshot to unixforge (you can download it
  <a href="http://www.mirbsd.org/MirOS/ISOs/">here</a>), but there isn't
  a changelog yet, that's why it wasn't announced. Just so you know.</p>
----
Author: tg@
Date: 23.11.2006

 <p>Great thanks to Pascal Bleser from FOSDEM for building SuSE packages
  of mksh(1). Benny already says, in a few years people won't talk about
  me as &quot;the MirBSD man&quot; any more but as "the mksh developer".
  And he kind of likes the shell, he admits, even though he prefers that
  Plan 9 shell called rc. He says the other *nix shells aren't really in
  active development anyway and only add bload (for example zmodload). I
  do invest quite some time in mksh, and it stays a scripting shell, but
  with good interactive usability.</p>
 <p>And a rant: X11 doesn't do everything right. Even that old venerable
  Windows&reg; 3.1 did do mouse-keyboard event serialisation right. When
  the system is under load and I type into an xterm and press the middle
  mouse button in between, the mouse lags. Seriously, quite a lot.</p>
----
Title: wlog from a plane
Date: 04.01.2007
Author: bsiegert@
# bsiegert@ doesn't know 2006 from 2007 when he flies
ID: e20060104-bsiegert

<p>This wlog entry was written on the flight from Dresden to Stuttgart.
 Flying is great: While it would take me about eight hours using
 so-called high-speed trains, the flight is only 50 minutes!</p>

<p>So we are in 2007 now. 23c3 is over. It was fun, even if tg@ did not
 manage to come. My security-related highlight was the talk "A not so
 smart card", where it was shown how trivial it is to duplicate a Swiss
 PostCard or a French Carte Bleue so that your clone will accept any PIN
 (they called it a "yes card"). As a user of a Carte Bleue, I frankly
 found it very unsettling. At least they don't use 384-bit RSA any more,
 as the Swiss still do. All in all, I attended a lot of talks. I also
 fixed a few bugs in the pkgtools and ported Gtk+ 2.10 along with
 dependencies. There are lots of circular dependencies lurking in the
 shadows there.</p>
----
Date: 05.01.2007
Author: tg@

<p>Yay! Benny lives!</p>
----
Date: 19.03.2007
Author: bsiegert@

<p>I should write more often. That said, I am in the middle of the
 period of my diploma examinations. So far, everything went really
 well&mdash;in the TOEIC (Test of English for International
 Communication) for example, I scored 985 out of 990.</p>

<p>Some MirOS-related news: I actually added a feature to MirLibtool:
 code for treating <tt>-Wl,--library-after</tt>, our equivalent to
 <tt>-idirafter</tt> for include files. I was surprised that libtool
 itself is quite readable code. One disadvantage of my patch: The
 library-after parameter is written into the <tt>.la</tt> file; older
 libtools trying to link against the file might barf with an "unhandled
 library argument" error message. This is not an issue inside MirPorts
 but could be an obstacle against including it upstream.</p>

<p>I am currently doing a bulk build of all packages on schaaf (a
 hopelessly slow 667MHz VIA C3). Doing a bulk build is very easy. You
 need to do the following things:</p>

<ol>
 <li>Start on a freshly installed MirOS system with plenty of space on
  the hard disk. Set up MirPorts via <tt>make setup</tt>.</li>
 <li>Set some variables we need via <tt>export BIN_PACKAGES=Yes
  TRUST_PACKAGES=Yes BULK=Yes BATCH=Yes</tt>.</li>
 <li>Go to <tt>/usr/ports</tt> and create a <tt>Logs</tt>
  directory.</li>
 <li>In <tt>/usr/ports</tt>, run the command <tt>mmake -k package clean
  2&gt;&amp;1 | perl /usr/ports/infrastructure/scripts/portslogger
  /usr/ports/Logs</tt>.</li>
 <li>Wait a few days for the build to be over. Note that <tt>make
  -k</tt> is needed to skip ports that don't build. Some of those will
  have a bulk cookie and a package file that is 0 bytes.</li>
 <li>Now comes the fun (?) part: check the build log of all packages
  that failed to build. Start with the packages with 0 bytes.</li>
</ol>

<p>Update: I had to cancel the bulk build as the machine was running
 too hot.</p>
----
Date: 07.05.2007
Author: tg@

 <p>Oops, I stayed out of bed for too long, again. Anyway, I had days of
  illness and enough hacking mood to do something. NetBSD&#174; pkgsrc&#174; works
  on MirOS now, and I ported over their svis(3) and OpenBSDs sdiff(1). I
  just wonder why I always have to fix <em>their</em> bugs&#8230;</p>
 <p>Nah, I have no intent in reviving this wlog, just ranting once.</p>
----
Date: 12.06.2007
Author: tg@
Title: SPARC port updates

<p>Okay, since this thing is here anyway, let's use it to update you
 people on the progress of the sparc port.</p>
<p>The kernel boots and runs fine. The hardware seems to be okay,
 the new HDD (sd0) gets a little warm at times, but that doesn't
 seem to cause any problems.</p>
<p>I reliably get segmentation faults for a lot of things – usually
 things that access the network, more rarely during compiling. Can't
 get stack traces as the stack is corrupt.</p>
<p>Just to be safe, I'll try out the other 9 GB HDD tyler got me.
 Maybe this one <em>is</em> the cause of the troubles, but I don't
 think so. On the other hand, I might just try to upgrade the existing
 #9 snapshot to #10 via source and with NO_ADA=Yes set. If that works…</p>
<p>As I said, having sparc support is not a release criterium for #10,
 but it'd still be nice to have. I already spotted bugs… but don't expect
 me to hack much on it, I've got a dayjob requiring full attention and
 hacking skills (mostly embedded GNU/Linux for mips, though, but luckily
 most shell scripting I do is in <a href="@@RELPATH@@mksh.htm">mksh</a>,
 and I can use <a href="@@RELPATH@@jupp.htm">jupp</a>; no BSD make there though).</p>
----
Date: 15.06.2007
Title: I'm bored so lemme write something here…
Author: tg@

<p>We now have an uppercase Eszett (ſz ligature) ẞ in the fixed-misc fonts
 and my <a href="@@RELPATH@@cvs.cgi/contrib/samples/dot.Xmodmap">keymap</a>; it maps
 towlower(L'ẞ' == 0x1E9E) = L'ß' == 0x00DF, whose upper-case mapping stays
 at L"SS" though. I sent the changes in the font to Markus Kuhn, hoping he
 will integrate them in the next stock XFree86® (and that x.org crap too…)
 version.</p>
<p><a href="@@RELPATH@@mksh.htm">mksh</a> is now a better <tt>/bin/sh</tt>
 for some people in Debilian who don't know of Korn Shell tradition. Also,
 it won't try to execute ELF, a.out, COFF, gzip and NE any longer.</p>
<p>Been working on FreeWRT all
 the time (even during the dayjob), so I didn't have the energy left to do
 more on the SPARC issues.</p>
----
Date: 25.06.2007
Title: libnointl
Author: tg@

<p>Before I forget to write this down… today, I released a piece of code I
 call <a href="@@RELPATH@@cvs.cgi/contrib/hosted/libnointl/">libnointl</a>. This was
 an original idea (and implementation¹) of mine, but I only got it because
 of swishy (Dale Anderson) who complained about his cross-compiling issues
 and troubles to me in IRC (I'm feeling the same when working for and with
 FreeWRT; he's also using µClibc, but non-POSIX FSH paths). Thanks for the
 intuition; if I get famous (FreeWRT and OpenWrt are already adopting it),
 you shall become it too.</p>
<p>¹) The API is part from gettext's <tt>libintl.h</tt> header – only from
 the non-copyrightable interface part only – and the ABI is re-engineered,
 using nm(1). There is one function actually doing something inside, whose
 implementation is from Dr. Dobb's Journal (but easily doable within a few
 minutes, and found at many other places on the net), optimised by me, and
 adjusted to match GNU gettext libintl's behavious, of course.</p>
<p>Han Boetes suggested to feed it back to the GNU gettext people… I guess
 they won't like the licence (MirBSD licence + advertising clause, but GPL
 compatible), as it's a GNU project they probably want the paperwork.</p>
----
Date: 27.06.2007
Author: tg@

<p>It's mksh-bash compatibility week, apparently. Now, <tt>${foo:2:3}</tt>
 works, but these must be numbers, not arithmetic expressions, as of yet –
 this should be fixed soon though. Also, <tt>${foo/bar/baz}</tt> (regexp),
 as well as its companion <tt>${foo//bar/baz}</tt> (like g appended) won't
 be much of a problem but I'll implement <tt>${foo:S/bar/baz/g}</tt> first
 followed by <tt>${foo:C/bar/baz/gx}</tt>, make(1)-style (x = to use POSIX
 extended regexps instead of basic). Of course, this'll only work if a few
 functions like regcomp(3) are in libc and functional and MKSH_SMALL isn't
 defined ☺</p>
<p>MirBSD Secure Shell (sshd) is now built as position-independent code to
 make it even more than OpenBSD's OpenSSH. Yay! (bsiegert@ thinks so too.)
 Eat this ☻</p>
----
Date: 08.07.2007
Author: bsiegert@
Title: On dependencies, once more

<p>As part of the GNOME update to 2.18, I added a python flavour to
 libxml2. This seems to confuse pkg_add and triggers a bug (one more)
 in the dependency handling code. Incidentally, the code in question is
 written in Perl by Marc Espie.</p>

<p>To completely fix the bug requires removing pkg(1) completely, which
 I will not be able to do before MirOS #10. As a first step, the verbose
 output of pkg is now more meaningful, allowing (hopefully) to debug
 the issue.</p>

<p>The way dependencies are handled is deeply flawed and is one of the
 biggest weaknesses in the current MirPorts framework. pkg(1) converts
 the dependencies into static @pkgdep lines of the form "@pkgdep
 libxml-2.6.14-2". If a libspec cannot be resolved, the adding almost
 certainly fails *sigh*.</p>
----
Date: 09.07.2007
Author: tg@

<p>Not the best day for fate… herc had an almost-panic in the UFS code, my
 bedside lamp got crashed by the telephone receiver when gecko2 called me,
 I had to nuke tcpdump(8) due to §202c StGB, and mksh R29g was only almost
 tested before release (it defines <tt>_LARGEFILE_SOURCE=1</tt> even if it
 is unnecessary). I am even thinking of removing all pre-R30 stuff off the
 <a href="@@RELPATH@@mksh.htm">mksh page</a> once R30 is out (which might,
 I must admit, not happen before MirOS #10, but it <em>will</em> rock). At
 least MirOS #10RC2 is going to happen soon, despite some bugs in the pak-
 kage tools bsiegert@ is trying to hunt down right now.</p>
<p>À propos gecko2: as he (and zeno) are booth staff, bsiegert@ and I have
 agreed to enable them to post wlogs here, so don't be shocked. kimnotyze,
 probably hoping to get an entry ticket from me, said he'll help out staff
 at <a href="http://www.froscon.de/">FrOSCon</a> as well, but doesn't wlog
 as of now (this may change if he's involved more).</p>
<p>I added cprng to the base system, a daemon tjat tries to gather entropy
 from measuring the difference between the CPU clock and timer interrupt –
 an interesting idea, yet it doesn't work on all hardware. Still better to
 have it than to not have good <em>local</em> entropy, besides it's fed to
 the kernel random(9) subsystem alongside with tty(4), disc and network IO
 (and possibly truly random stuff from the VIA C3/C7 RNG, hifn(4) cards or
 even from hotbits/fourmilab/randomnumbers.info). The mix is what makes it
 good, but arc4random(3) with multiple concurrent accesses is a difference
 to more popular OSes ☺ which makes it truly great. So just use one source
 of entropy – <tt>/dev/arandom</tt> – which is rather high-quality even if
 its absolute entropy count is less than the one from urandom.</p>
<p>Somehow, I also managed to wreck something in my other pet project –
 FreeWRT. It is often annoying to work
 with Linux, and this shows it one more time: module loading doesn't work,
 and we have issues with binary-only stuff (BLOBs) too. Still it is slowly
 being undermined by addition of mir-tools to the system ☻ and – while a̲l̲l̲
 embedded system development kits suck, this one sucks the least.</p>
<p>A few days ago, I had access to a Soekris vpn1411 card – hifn(4) – that
 just worked™ out of the box on a bsd.rd kernel. Nice. I noted that rdate,
 as well as uuencode(1) and uudecode(1) and their base64 variants were not
 available, so I added them; rdate(8) even fits on the small floppy (8KiB)
 and is now The Official ping6(8) Replacement™ on floppy, since the latter
 is about 28K.</p>
<p>Today I officially declare that gdb(1) isn't usable on MirOS. I tracked
 down an GCC bug but was confused because a “load register with immediate”
 opcode appeared to change memory (the stack frame – the print command did
 not seem to be affected). But hey, I eventually found the bug. Now, all I
 wait for is Sun to release their compiler under MIT licence… as if.</p>
----
Date: 11.07.2007
Author: tg@

<p>I think one of the two HDDs in herc which compose the RAID 1 (software,
 using raid(4) – RAIDframe) is definitively failing. I need a replacement;
 maybe I'll do as few activity as possible on <tt>/MirOS/</tt> and the CVS
 repository in the meantime to extend its life span. This sucks, and I see
 I won't be able to relax next weekend either.</p>
<p>We have a new snapshot – MirOS #10 RC2 – yet not announced on the front
 page because I need to rsync it to the mirrors first (RAID issue) and put
 up a torrent (time issue, I do have a dayjob now). But it should appear @
 the http mirrors (heph and allbsd.org) soon, in <tt>/MirOS/current/</tt>,
 as usual.</p>
----
Date: 26.07.2007
Author: tg@

<p>Yesterday, I talked some with the MidnightBSD people. I think that they
 are quite okay and invited them over for FrOSCon. Maybe at least one from
 that bunch comes, then we'll finally have all BSDs at once.</p>
<p>My dayjob is really keeping me busy, I'm almost only home for sleeping;
 but that's okay, I even get to do mksh stuff at work since it's the shell
 of choice in FreeWRT Trunk (to be 1.1), which is what we use and develop.
 Speaking of mksh, I'd like to release R30 rather sooner than later.</p>
<p>Benny's busy coding WinAPI at work, poor lad, but it could be worse, as
 STL or MFC or so. On the other hand, he <em>does</em> still fix ports and
 package tools (we have a security updated BIND now, for instance). Thanks
 Benny, we really appreciate that.</p>
<p>Speaking of MirPorts – the MidnightBSD people have “mports”, which seem
 to be FreeBSD ports based (*grins* I wonder why they didn't use pkgsrc®…)
 and I suggested them to use MirPorts as a second choice (like pkgsrc® for
 us), after Archite (coming from OgreBSD) couldn't persuade them to choose
 only MirPorts he'll probably look into that now. We'll help, but we can't
 maintain it. I just wish dfjoerg would commit the MirBSD bits in pkgsrc®,
 since otherwise I wonder why I did all that work if nobody's going to use
 it due to missing upstream inclusion. Lazy git. mksh's still at R29f.</p>
<p>From time to time, I'm uploading a new snapshot to the netinstall dir –
 it pays off to look there. Today's one was tested on a WRAP board.</p>
----
Date: 05.08.2007
Author: tg@

<p><img alt="Fun is when you found it – Geocacheing with Dr. Pfeffer &amp;
 Co." src="http://www.opencaching.de/statpics/106521.jpg" /></p>
<p>The BOSng Duo has found another cache, although with minor injuries, we
 hooked up a friend to the fun and had a definitively nice view.</p>
----
Date: 08.08.2007
Author: tg@
Title: SPARC is dead, long live SPARC!

<p>It looks as if I finally have found a few cases of bad programming that
 caused the segfaults and other misbehaviour on sparc. Now let's just come
 all the former Debian GNU/Linux/sparc users. Okay, I've got to compile it
 a few times more, and pre-#10 I'd like to do one more code change, namely
 the switch from suncons to vt100, but… what the hey ☺ I'm happy.</p>
<p>I'm currently building on a 75 MHz SuperSPARC and would be glad if some
 nice person would send me one of these 233 MHz HyperSPARC modules that've
 been made by ROSS (I think), and some more RAM for a SPARCstation 20 UP –
 we don't support SMP on sparc either. And I desparately need 1-2 testers,
 since I don't use a monitor/keyboard/mouse zs console but “merely” a real
 <a href="http://vt100.net/docs/vt420-uu/">DEC VT420</a> on ttya.</p>
<p>On HTML: see <a href="http://marc.info/?m=118635601729218">my rants</a>
 about standards.</p>
<p>Anyway, despite the bugs found during the sparc compiling progress, our
 tree is in a pretty sane state and ready for release every day or so. I'm
 postponing it a bit in the hope less bugs will be found post-release, and
 Benny is still continuing his ports work, despite having to create slides
 for that <a href="http://programm.froscon.org/2007/events/6.en.html">talk
 at FrOSCon</a> <em>and</em> doing his diploma stuff all day. Thanks Benny
 what would MirOS be without you.</p>
<p>I've still got my dayjob, and working with parsing, databases, SQL, and
 C string operations at the same time isn't really fun. But it's me who is
 able to make FreeWRT 1.1 shine, so
 I've got to do it. I bet it'll have been a lot of fun once I'm done. Just
 the way there is hard. So be it. On the contrary, my boss's got a Zaurus,
 and Dr. Pfeffer's geocacheing software (in Java™) runs on it. And he will
 not only make these trips with us but also lend it to one of us if he has
 no time but we want to go. That's the benefit of a small company.</p>
----
Date: 09.08.2007
Author: tg@

<p>There are interesting things to be found in anybody's source tree. This
 time, it is Schily again. Well, it could be cleaned up, and arc4random(3)
 got improved as well, except I <em>still</em> think it should have a kind
 of timer for smaller entropy adds (⅛ of the arc4 key size).</p>
<p>On the other hand SPARC looks rock solid now, I could even build a gnat
 (GCC's Ada part) today. Let's hope we'll have a snapshot in 2-3 days, and
 maybe MirOS #10/sparc will be in #10semel this time.</p>
<p>The website… some things are difficult to do until you go to the toilet
 and come back with a great idea. Put back mtimes on the pages.</p>
<p>At work, I hacked some major C code for FreeWRT today, namely in the
 nfotiser
 (and here[link removed]).
 That's a complicated programme, difficult to do even for me (mostly since
 it grows high-level stuff, data structures, and not only close-to-machine
 stuff, especially the SQL stuff), but it turns out to become fun once you
 get into “hacking mode”.</p>
<p>Tonight's after-work event is <a href="http://luusa.org/">LUUSA</a> (at
 the <a href="http://netzladen.org/">Netzladen</a>) again.</p>
<p>Waldemar brought his Zaurus, but there's no Ewe VM. On the other hand –
 after some kernel patches and downloading Ewe149-Linux-x86.zip as well as
 cachewolf_linux_0.9n_patch_4.zip – the first from ewesoft.com, the second
 from cachewolf.de – and unpacking, it worked out of the box; remember the
 device name is relative to <tt>/dev</tt> (I had to use “cuaU0” and “9600”
 as baud rate, add myself to group dialer too). I did need some shared lib
 from Debian GNU/Linux for that (libgcc_s.so.1) though. Compiling Ewe is –
 at the moment – apparently impossible, it always segfaults both on MirBSD
 (i386) and Ångström Linux (armv5tel/Zaurus). I'm importing caches from my
 site (opencaching.de) now, after recentering to my current location (as I
 am too lazy to figure out the GPS position of my home right now). Now, if
 I had a <strong>huge</strong> battery on this laptop (the current one can
 hold an hour or so only), I could use it for geocacheing.</p>
<p>UPDATE: This even led to spotting bugs in MirPorts and CacheWolf.</p>
----
Date: 10.08.2007
Author: tg@

<p>While I didn't have much time today during work due to some lecture, my
 SPARCstation 20 was busy building a snapshot (and still is, and even will
 still be the next day or more), Dr. Pfeffer improved CacheWolf further, I
 bought a GPS mouse at ePray (together with Addy, the “&amp; friends” part
 from <a href="@@RELPATH@@permalinks/wlog-9_e20070805-tg.htm">the last</a>
 try, and an intern who seems to like the idea), read raw NMEA 0183 output
 from wbx@’s device and conjured nmeadecode(8) which, until we get nmea(4)
 and friends, will just read the serial stuff from userland, timestamp it,
 act as simple NTP server (to use with <tt>serverloop</tt> in ntpd.conf(5)
 and bound on a different port), and display position data to stdout.</p>
----
Date: 11.08.2007
Author: tg@

<p>I didn't get to hack today, plus I slept too much (06:00 ‥ 18:00), thus
 missed some of the day (did not expect it to be sunny tho) and was tired.
 To add insult to injury, when having diner in the city some freak thought
 it would be nice to flatten my bike tyre. I had to walk back, and arrived
 home at about midnight. I guess it's reading idly for tonight, maybe that
 hacking mood will get back some other day. I've discussed nmeadecode – or
 rather the idea for it – with some friends now and like it more and more,
 as most of them do. Still have to discuss it with Pfeffer.</p>
<p>I just built gcj on odem (still works, yay), took much over an hour, at
 1 GHz even, and will try to build CacheWolf with it (can become developer
 then) to create a jar (for sunjdk or so, just to verify) or compile a jar
 (official one, or one built myself if possible) to a native executable to
 use instead of ewe with compat_linux(8). If that works, I'll build gcj on
 wbx@'s Zaurus, even if it takes a week or so. Cross fingers for me.</p>
<p>Seems as if ciruZ likes the geocacheing concept. Oh wonder…</p>
----
Date: 12.08.2007
Author: tg@
Title: A Good Day™

<p>Today was quite the nice day. After sleeping long I started my day with
 style: chilly, having a coffee, and booting my cell phone, which I turned
 off during the night because I phoned the battery empty last evening… wbx
 called me, came over later (after some mksh(1) hackery: set -o arc4random
 was added), and we went geocacheing again. And hacking. The SPARC build’s
 complete, Ewe (that single-threaded embedded VM for Java™ which CacheWolf
 uses, that’s the application Dr. Pfeffer likes to use for geocacheing and
 I’d even use as a GPS navigator…) works natively on MirBSD – what more do
 I want? (Ok, I could think of some things, but I’m happy nevertheless.) I
 face bad future though: we infected wbx@ with the gc virus, so he’ll make
 me port X11 to FreeWRT to use it on the OpenMoko with his nokernel target
 I guess. *sigh*<br />Oh well, I can use his Zaurus in exchange then; that
 beast at least has longer-lasting batteries than my notebook.</p>
<p>I've uploaded the snapshot to <tt>/MirOS/current/sparc/</tt> (the older
 one is archived at <tt>sparc9</tt>), but did not announce it yet, because
 we need to have some more persons actually test it and report success for
 especially the vt100 wscons change. The floppy image is probably going to
 die though, and installboot doesn’t like the miniroot (yet).</p>
----
Date: 13.08.2007
Author: tg@

<p>There are days you just want to go back to bed. This is one of them and
 I’m beginning to hate my 42½ hour working weeks again.</p>
<p>Lynx is buggy, trying to convery my nicely working solutions to kludges
 around broken GnuTLS (with no reason to exist), since the latter does not
 support even some basic OpenSSL function calls, and they have to autofool
 for it. Guess who’s going to fix that? Okay, I already did, so…</p>
<p>Due to my recent ability to compile <a href="http://www.cachewolf.de/">
 CacheWolf</a> with gcj, it’s not in base again. Yeah, call me selfish, it
 is nothing new. Anyway, it won’t hurt since it’ll reside in the “ada” set
 which almost nobody installs, and isn’t selected by default either. Also,
 it’s i386 only (quelle surprise). Maybe someone can make use of it. gcj’s
 also enough for university students’ needs (except that gij is broken). I
 recall Benny telling me that boehm-gc with threads wo’t work; gcj uses it
 and seems to work relatively stable. Java™ still sucks, especially if you
 have two different line ending conventions in a windows-1252 encoded file
 and the docs are in the same charset except for some UTF-8+BOM…</p>
----
Date: 17.08.2007
Author: tg@

<p>My SPARC is building XFree86® for the umptieth time, but I still expect
 it to finish cleanly this time. We nuked all the cropped fonts, will only
 install the full Unicode fonts now (needs some more RAM, but less overall
 as you need some of them anyway, and reduces build time); on very low-mem
 systems you would want to build your own font subset anyway.</p>
<p>I invited the XFree86® developers to FrOSCon – all two of them – but it
 looks like they can’t come. Too bad.</p>
<p>I started writing “I’m” instead of “I'm” – typographically better, much
 better in fixed-misc font even, but drives people crazy (and away from OS
 without Unicode support such as OpenBSD and most Linuxes), funny. Oh, and
 swishy, our IRC Kiwi, is using my keyboard layout now too. Strike!</p>
<p>With MirOS BSD #10 we’ll release mksh R31, no big deal. It needs tests,
 just like the sparc port, so please check it out of CVS and test it.</p>
<p>No progress on the nmeadecode(8) front (yet), but fixed some endianness
 bugs in OpenNTPD. I should call it MirNTPD, I suppose. And rdate(8).</p>
<p>We also spotted some bugs in the ports infrastructure again (better pre
 than post release ☺) and I fixed the problem that COPTS were passed twice
 in imake(1) build environments.</p>
<p>Finally weekend, I’m so happy. Benny today finished the slides for that
 autotools presentation he’s going to hold at FrOSCon, 42 in total (wonder
 why…) and is happy about the weekend too. Open source developers should –
 in my opinion – get two hours a day off work to hack. (But I can’t really
 complain, I’m off quite well with my company. Thanks to my bosses, if you
 should happen to read this.)</p>
<p>Benny is also trying to upgrade the www/firesomething (Iceweasel) port.
 Apparently with success. I still don’t like applications that use glib2 –
 even though I probably will need one, as I might be switching to mcabber,
 from centericq; I dropped all ICQ/Yahoo!/MSN contacts tonight.</p>
<p>Oh yeah. FreeWRT. Zaurus/Ångström. Kernel modules. Packages. Linux JUST
 SUCKS, get it. Things I take for granted just aren’t in there yet – worse
 is that most of them won’t make it in since it’s a bunch of packages from
 many authors, contributed with “here’s my code, please add it, have fun –
 and someone should write the docs”. Sometimes, Theo is right. He’s also a
 lot of right (can I say that?) regarding open source’d (what a word…) NIC
 drivers from vendors, compared with getting specs and hardware and coding
 one’s own drivers. Vendors suck. More than Theo, at least.</p>
<p>Compared to other operating systems out there, we still suck least.</p>
----
Date: 19.08.2007
Author: tg@

<p>This sucks: we apparently also got the wrong cable for the Zaurus spitz
 (SL-C3200) – one that does not support USB host mode. Add the Ewe runtime
 issues (now: segfault in GetLocale() or something like that) to it – plus
 the CacheWolf issues… damn I think it would’ve had some great educational
 impacts on our geocacheing newbie of the day. But odem was enough…</p>
<p>I finally got my GPS mouse, wbx@’s is an uslcom(4) at 9k6,8N1; and mine
 is an uplcom(4) at 4k8,8N1; no problems so far, this is actually the very
 baud rate specified by NMEA 0183, and its precision is better by one post
 comma digit (unsure how to call it in English). This means I’ve been <img
 src="http://www.opencaching.de/statpics/106521.jpg" alt="Geocacheing with
 wbx &amp; Co. – Fun is when Jonas found it" /> outdoors again, with quite
 some success. I suppose I’ve got to fix the Zaurus issues with Ewe soon –
 but Cachewolf seems to have some trouble with my version of the GPS mouse
 which transmits the GPGSV lines only every second second (heh…). In short
 this means it didn’t work and we were left with wbx@’s less precise mouse
 which, interestingly, had fairly good precision this time but didn’t seem
 to actualise the position as we drove or walked. Weird. Or CacheWolf is a
 little bit more buggy than we thought.</p>
<p>Looks like I’ve got to work on nmeadecode(8) now for real. If only…</p>
<p>mksh(1) now got a “rename” builtin just calling rename(2). I fragged an
 embedded system (Mikrotik Routerboard 532 with FreeWRT) by trying to move
 the old directories aside and new directories in place during an upgrade,
 not remembering that <tt>/bin/mv</tt> was dynamically linked…</p>
<p>I could reproduce the “detached mksh busy loop” issue on the Zaurus but
 not track it down (of course). So far, it seems to only happen on Linux –
 I definitively need help from the community here.</p>
<p>We got MirOS #10 RC4 (i386) out as well as #10 RC2a (sparc), now with X
 but still not really tested. Both on the mirrors. After reïnstalling that
 SPARCstation and fixing some SIGBUS, I’m now trying to get a final candid
 for sparc out before actually releasing #10 into the wild.</p>
<p>*sighs* I guess I’ve got to add <tt>-Wcast-align</tt> to COPTS globally
 on my sparc, do a full build’n’fix round. Developers just aren’t aware of
 these issues, and gcc on i386 can’t even reproduce these warnings with an
 extra option (say <tt>-fstrict-align</tt>, that’d be great).</p>
<p>Benny (who seems to be much too lazy to do any wlogging) has to cut off
 way too much content from his talk. He said he needed 1:06 hrs and didn’t
 even mention everything… too bad, it really was great stuff.</p>
----
Title: FrOSCon 2007, Day 0
Date: 24.08.2007
Author: tg@

<p>This is day 0 of <a href="http://www.froscon.org/">FrOSCon 2007</a>, the
 event whose planning of a “LinuxTag Bonn” started out during some car ride
 to FOSDEM. I’m not yet there, because I am committed to committing all the
 local Ms from my various source trees first, as “herc” (or rather rant) is
 a little working right now (after rebuilding the RAID several times during
 last night, which made me sleepy…) and I’d rather get it done now.</p>
<p>Expect a wlog entry per day per developer (well, at least me), and these
 are constantly updated (maybe, we’re lazy slackers after all).</p>
<p>*sigh* Benny updated the index but didn't commit the other migrated HTML
 files. This website just became <em>more</em> broken in a sudden.</p>
<p>Interesting: geocacheing now works, but CacheWolf cannot handle 4800 bps
 – but <tt>cu -l /dev/cuaU0 -s 4800 &lt;&gt;/dev/ptyp5 &gt;&amp;0</tt> plus
 using <tt>/dev/ttyp5</tt> as “serial” device helped…</p>
<p>We just ate a little and now are going home. FrOSCon looks superb, but a
 Live CD Image is still not there. It's closing time...</p>
----
Title: FrOSCon 2007, Day 1
Date: 25.08.2007
Author: tg@

<p>Where’s my MirOS flag, I wonder? Anyway, we finally got ISOs, I am fully
 under strain, and the food is good and the net working.</p>
<p>ciruZ did me a mcabber port, now I need to learn how to use it. Dropping
 all non-Jabber connections was fun. (He tells me to write “js” as name, as
 he doesn’t use that nick any longer. I guess you call it “Richtigstellung”
 in German press law.)</p>
<p>Benny is constantly annoying me too… I’d better go and eat something.</p>
<p>… the grill is dimensioned much too low and it’s hard to get the grilled
 sausages. Luckily, users contributed some Altbier, and other visitors went
 to the barbecue queue for me. Thanks!</p>
<p>Something seems to be wrong with manpages on the sparc. Maybe that could
 be fixed during the next build. No idea. I guess it could be a caste-align
 issue. I do not even want to fix the bootloder, the code is so ugly.</p>
----
Title: FrOSCon is over
Date: 27.08.2007
Author: bsiegert@

<p>Along with this post, I am inserting a vim modeline into the source
 of this page. Finally.</p>

<p>As said in the title, FrOSCon 2007 is over. IMHO, it was one of the
 best conferences I have ever attended. I loved the relaxed atmosphere,
 the cool people, the catering, and the Free Beer&mdash;sponsored by
 O'Reilly, who really deserve more credit for that. There were many
 niceties and little things that made the conference truly
 great&mdash;like the Wii lounge, where I played some tennis against
 Marius from AllBSD.</p>

<p>I was not at all happy with the way our booth was handled though: It
 consisted of a row of tables, the showcase computer standing with the
 monitor to the front. <i>Behind</i> the tables, three to six persons
 were sitting crouched behind their laptops, only one of which (tg@)
 actually using MirOS. The others were not even familiar with the
 project, with its goals or with the content of the flyers. The showcase
 was almost only ever used for showing something when I was present,
 doing so myself. Flyers and CDs were not proactively handed out to
 visitors, they had to get these themselves.  Note: I will not accept
 this behavior again from someone with an exhibitor's pass for
 MirOS.</p>

<p>On a more positive note, my talk <a
 href="http://programm.froscon.org/2007/events/6.de.html">automake,
 autoconf, libtool&mdash;an introduction to the GNU build system</a> was
 a success.  The lecture hall was almost full; the audience was
 interested and critical, asking many questions along the way and at the
 end. (Thank you for that.) I started 15 minutes late because the video
 team did not have a new cassette for recording. They called a helper
 over DECT, asking for a new one. The helper came five minutes later,
 asked if we were the ones that called and went off again to actually
 get the cassette. It was truly a WTF moment for all of us, the audience
 waiting. I made it through at an impressive speed: All my original
 slides as well as the demo were in, and even with questions, I made it
 in about 50 to 55 minutes.</p>

<p>In the abstract, I had made a bold statement about cmake being a
 flawed concept compared to the autotools, but I did not have any data
 points to actually back up my claim, and promptly I got some questions
 about this weak point of mine. Sorry for the unsatisfying answers.</p>

<p>The slides in PDF format as well as the code examples are
 downloadable from the FrOSCon program website. If you attended the
 talk, I would be happy to receive some feedback, remarks and criticism
 via the form on the same page.</p>

<p>Oh, and it is true that the website here is somewhat broken now
 because I did not commit all of my changes. The point is that commit
 windows, with a r/w CVS repository, are rare now for some reason.
 Halfway through my commits, I was distracted and could not finish. By
 and large, and contrary to popular belief, a conference and exhibition
 where you have a booth is not a good place or time for hacking.</p>
<!-- vim:se tw=72 ai sw=1 ft=html enc=UTF-8: -->
----
Date: 28.08.2007
Author: tg@

<p>FrOSCon is over for me now as well, with the end of the two days I took
 off to replenish after the event. I used it to chill, rest, not do much –
 so far it worked, I feel okay going to work tomorrow, not strained.</p>
<p>Since yesterday, I’m officially a developer of Cachewolf, thar software
 Dr. Pfeffer and I use for geocacheing. And I fixed a bug. In Java™. Urgh.
 But it works now (for some low values of work). And they use svn. Yuck. I
 can’t use non-7bit chars in the commit messages, because J�rg Schilling’s
 fucking BerliOS setup wrecks the emails if I enable use of locales in the
 <tt>post-commit</tt> hook, which worked for FreeWRT. Line endings as well
 as character encodings (they use mostly windows-1252) are cruel too – but
 probably can be fixed. I need to start some discussion about that. To use
 gcj for compiling, I’ve prepared a <tt>comp-gcj.sh</tt> and even a simple
 Makefile, but I want to clean the mess up some more before committing the
 nuggets, because it’s easier (also for Ewe and Jewel) to have the classes
 from external libraries unpacked in the tree.</p>
<p>GNU ed sucks – it is less BSD ed(1) compatible in more recent versions…
 I bet they’ll be using GPLv3 next – and GFDL for the <span class="s">man</span>
 er… <span class="s">texinfo</span> pages (now what, GNU software doesn’t use manual
 pages any more, and almost no GNU/Linux distribution has texinfo).</p>
<p>I would have listened to the grml talk at MoeLUG tonight, but nobody of
 my mates with cars wanted to go. Too bad, I really liked the Altbier.</p>
----
Date: 29.08.2007
Author: tg@
Title: Happy 5th birthday, MirBSD!

<p>For its birthday, it got further improvements to the www source code as
 well as a merged page more; unity of mind, and consens between developers
 regarding how to handle the next events and J�rg Schilling, and nobody, I
 think, noticed. But how fitting that Theo de Raadt is now guilty of doing
 actual harm to his own project, by shouting at Linux® developers, so that
 they use GPL-only instead of BSD/GPL dual licencing for their fork of his
 ath(4) OpenHAL (after fixing a licence violation that they were correctly
 accused of). At least me and nbd from OpenWrt think so.</p>
<p>These are quiet times, and I worked long today (biking up a mountain to
 the server housing farm *sigh*, and hating Subversion even more), as did,
 or so I think, Benny. My SPARCstation (demo.mirbsd.org) finished creating
 a new snapshot, hereby dubbed MirOS #10 RC6, which will be uploaded soon,
 along with a recent one for the i386 architecture. I hope it works really
 well, so that we can release as soon as possible (and tested; XTaran took
 it okay and is currently backing up his stuff, thanks).</p>
----
Author: bsiegert@
Date: 31.08.2007

<p>I had some feedback for my FrOSCon talk from J&ouml;rg&mdash;better
 known for MirOS users as J?rg&mdash;Schilling, who did not even attend
 it. Somebody told him I had been mocking his poor excuse for a build
 system. Since then, mails have been going back and forth. He accused me
 of spreading lies, being generally misinformed and (that is the part I
 like best) having made a bad talk. In fact, the latter is also the
 subject of his mail. Good to know that he can sense what I said from
 500&nbsp;km away.</p>

<p>It was impossible for me to get any kind of factual argument across
 to J&ouml;rg. For instance, every time I said something about his
 Makefiles, he kept on talking about smake. I am not the slightest bit
 interested in smake. The really interesting questions were not answered
 by him: Why are there 325 files in the RULES subdirectory in the
 cdrtools source (and 48 READMEs)? Why are there two Makefile fragments,
 <tt>i386-openbsd-cc.rul</tt> and <tt>i386-openbsd-gcc.rul</tt>, which
 are otherwise completely equal and choose to ignore the user's choice
 of C compiler? How do you want to achieve platform-independence if all
 you have is 325 platform-specific files?</p>

<p>The answer is that you should just install smake, and thanks to its
 magical capabilities (which J.S. calls "automake functions" to further
 confuse everyone), everything will work. I refuse to look at smake, but
 for me, this just shifts the problem further: How do the Makefiles of
 smake work? Should I install smake to build that too? Keep in mind that
 this is somehow better than automake, which works with the native
 make(1) or GNU make, and for which no additional software needs to be
 installed, at least <i>a priori</i>.</p>

<p>So, to conclude, I stand fully behind what I said, and I will not
 "correct" any statements I made. Regarding the licence issues behind
 the Schily Makefiles, different people have different opinions. And
 J&ouml;rg, you should be ashamed of yourself for saying:</p>

<blockquote><p>"Schade, da&szlig; Du die L&uuml;gen der OpenSoure [sic!]
 Feinde bei Debian unreflektiert wiederholst."</p></blockquote>

<p>I mean, really.</p>
----
Date: 02.09.2007
Author: tg@

<p>Yesterday morning, wbx@ prodded me to hunt that bsd.rd vs bootloader,
 bsd.rd.net working, bug, together. Turns out I had to fix an error in a
 check if the kernel is not too big, turns out bsd.rd was too big, so we
 decided to bump the RELOC value a little.</p>
<p>Forking is “in”: MirBSD, FreeWRT, Ewe, GForge… what’s next?</p>
<p>Things that suck: too small partitions for mirroring <tt>/cvs</tt> on
 a 2 GiB drive which also hosts a #7quater installation, with too big of
 a block and fragment size to fit all comma-v files.</p>
<p>I’m somehow not in a hacking mood right now, we basically just need a
 few more people testing #10RC6, then recompiling (from a clean install)
 it and releasing that. Or so I think.</p>
<p>The weekend is intended for relaxing, I think I have done so. I’m not
 even in the mood to bike to the city and have some big dinner, for me a
 couple of butterbread and some sinalco cola+cherry juice+beer will last
 that evening. The only thing which sucks is that I have to wash clothes
 because I’m going to Berlin this week (business trip). I really hope my
 laziness will allow me to get a set of clean clothes for THAT ☺</p>
<p>I wonder where Benny is, this weekend. Probably relaxing, too ☻☺</p>
----
Title: Talk feedback: recursive make
Author: bsiegert@
Date: 02.09.2007

<p>Diego Biurrun, who was both actually present and interested in my
 FrOSCon talk, pointed me to a paper called "Recursive Make Considered
 Harmful" <a href="#bsiegert-20070902-ref1">[1]</a>. (Thank you!) In
 response to the question he asked about this during the Q&amp;A
 session, I said that recursive Make is automake's default and only
 behavior. This is not true.</p>

<p>The author of the paper starts with an example project very much like
 mine (two .c files, one header) and creates an artificial module
 boundary. Unsurprisingly, dependencies do not work as they should any
 more. I have witnessed this phenomenon and have seen large recursive
 build systems fall apart. Continuing a mozilla build for example takes
 unacceptably long, and you see many IDL files unnecessarily being
 regenerated.</p>

<p>However, implementing the one-Makefile-per-project technique outlined
 by Miller is actually very easy to do in automake. Older automake
 versions did not have good support for source files in other
 directories but this has not been a problem at least since automake
 1.8.</p>

<p>If you paid close attention, the Makefile.am I created in the talk
 was not really recursive because only one Makefile actually did some
 compiling. In fact, you can merge Makefile.am and src/Makefile.am into
 one file, like this:</p>

<blockquote><pre>ACLOCAL_AMFLAGS = -I .

bin_PROGRAMS = hw
hw_SOURCES = src/main.c src/hello.h
hw_LDADD = libhello.la

lib_LTLIBRARIES = libhello.la
libhello_la_SOURCES = src/hello.c src/hello.h
libhello_la_LDFLAGS = -version-info ${LIBHELLO_VER}
</pre></blockquote>

<p>If you insert all your targets into one Makefile.am, the
 automatically inserted stuff from automake only needs to be inserted
 once, thus you get a lower overhead. Dependency tracking should be even
 more efficient, and build times should decrease. One technique proposed
 by Miller is to use per-project Makefile fragments which are included
 by the main Makefile. Automake supports an <tt>include</tt> directive,
 which is directly evaluated during the automake run and thus fully
 portable.</p>

<p>One problem I see with this approach is that all objects are put into
 one directory. Thus, you will have problems if different files in
 different directories have the same name. For example, compiling both
 <tt>foo/main.c</tt> and <tt>bar/main.c</tt> inside the same Makefile.am
 will not work. I do not know if there is an easy solution to this
 problem&mdash;perhaps an automake option to put the object files in
 subdirectories. Any automake expert reading this, please contact me if
 you know of something.</p>

<h3>References</h3>

<ol><li><p><a id="bsiegert-20070902-ref1"></a>Miller, P.&nbsp;A.,
 Recursive Make Considered Harmful, <i>AUUGN Journal of AUUG Inc.</i>,
 <b>19</b> (1), 14&ndash;25 (1998).</p>
 <p>URL: <a
 href="http://miller.emu.id.au/pmiller/books/rmch/">http://miller.emu.id.au/pmiller/books/rmch/</a></p></li></ol>
----
Date: 03.09.2007
Author: tg@
Title: My new laptop – company owned

<p>I wonder why companies produce such crap. No, really. And I wonder
 even more why the previous owner (a colleague who went off looking for
 a better paid job, probably with less good working climate) asked for
 exactly this laptop, as it doesn’t even work without any troubles on
 his beloved Deb*an G*U/L*n*x (all product names are changed because
 I don’t want to be sued). It's a S*ny V*io, a brand which never had
 any good reputation in our circles. MirOS won’t run natively on it our
 of the box (okay, I could build a custom kernel, but hey, maybe these
 dual cores can better be used with VirtualB*x or something like that,
 even be running in parallel with W*nd*ws). But still, I had my fair
 share of fight with the D*b*an-Inst*ller, which doesn’t even come with
 fdisk. I managed to wreck it, expect this wlog entry to be amended by
 a photo of that (which, at the moment, is located on the mobile phone
 of my intern, which has a camera built in).</p>
<p>At least I have a use for these G**gle “Go Code!” stickers now – to
 cover the built-in “webcam”… <strong>Who the fuck produces or buys such
 kind of crap?</strong> Sorry for the emphasis, but <em>I just do not
 fucking get it</em>. And of course, w*ldi and b*nz tell me that there
 are no such bugs in the Inst*ller mentioned above. (There are a lot more,
 for instance I cannot choose UTC as timezone, neither grub2 nor grub nor
 lilo worked – but I got the latter installed manually now, etc.)</p>
<p>This new orking device still has more hours of “fun” for me, but as
 for tomorrow, I’ll be driving to Berlin. I left that craptop at work.
 I’ve got better things to do in the evenings.</p>
----
Date: 07.09.2007
Author: tg@

<p>I have been in Berlin for some kind of business trip, and I finally
 could get a hold of a beer called “Krusovice”, it’s a black beer, and
 I really like it. Benny does, too. I drank it in a restaurant called
 “Ranke 2”, which was recommended to me by Przemysław, thanks a lot!
 We managed to buy some bottles in a beverage store (alongside with a
 lot of bottles of “Berliner Faßbrause” – the local speciality, some
 kind of herb lemonad – as well as a few interesting beers, such as
 <span style="font-family:Fraktur;">Neuzeller Kloster-Bräu Kirsch
 Bier</span>, <span style="font-family:cursive;">Kirsch Porter</span>
 <span style="font-variant:small-caps;">Das fruchtige Schwarze</span>,
 <span style="font-family:Fraktur;">Neuzeller Kloster-Bräu Schwarzer
 Abt</span> <span style="font-variant:small-caps;">Schwarzbier</span>,
 Duckstein (Rotblondes Original – Auf Buchenholz gereift). Beats my
 usual Schlösser Alt with Cola and optionally cherry juice ☺<br />At
 Ranke 2, I also drank a “Danziger Goldwasser” to close the stomach
 after the good diner, which was something new for me as well; I must
 admit I liked it, but not as much as croatian Julishka.</p>
<p><a href="@@RELPATH@@mksh.htm">mksh R31</a> is out, grab it while
 it’s hot ☻</p>
<p>The SPARCstation is almost done building just another snapshot,
 with the bootloader vs bsd.rd bug fixed. I suppose this means that
 the release is imminent, despite XFree86® (4.5 → 4.7), ncurses (5.5
 → 5.6 or even CVS version) and maybe more waiting for updates. Ce
 la vieh. We’ll do that afterwards, and of course we ensure that #10
 users can use later MirPorts snapshots.</p>
<p>Oeps. I had to re-roll the mksh-R31.cpio.gz distfile. Damn. But
 the Debian upgrade was already done. On the other hand, lintian did
 bitch a little, so Debian accumulates two “nice to have” fixes now.</p>
----
Author: bsiegert@
Date: 10.09.2007

<p>I am doing pretty much nothing for MirOS these days as I have only
 three weeks left for my diploma thesis. Hopefully, in a month or so, I
 will be a real <i>Diplom-Chemiker</i>. We will see what happens
 then.</p>

<p>I spent a very relaxing weekend at my girlfriend's place. On the way
 there, I got so bored that I almost finished a research paper ;).
 Writing a paper is nicer than writing a thesis because you pick one
 specific subject and try to make a concise statement. It also makes you
 realise which experiments are still missing ;).</p>

<p>And the paper is in English. I discovered that writing scientific
 texts in English is easier for me than in German because the majority
 of existing literature is also in English. After a while, you get used
 to the typical style, and it sucks when you cannot reproduce that in
 German. I also have some problems with terms for which I do not know
 the correct German expression :/.</p>

<p>Question to the interested reader: it seems that if you encounter
 some totally bogus paper, it is almost always published by Elsevier.
 Why is that? Discuss.</p>
----
Date: 12.09.2007
Author: tg@

<p>Just to not strain the poor packagers, there will be no mksh minor
 release tomorrow ☺ At least, I hope there’ll be no more late real life
 bug reports for problems I deem important enough.</p>
<p>I “found” my 10<sup>th</sup> <img alt="Virtual Geocacheing is fun too"
 src="http://www.opencaching.de/statpics/106521.jpg" /> Geocache, which
 means that, on OpenCaching.de, the website I prefer for being devoid of
 the capitalistic attitude which prevails on GeoCaching.com, despite most
 other CacheWolf involved seem to not like, use or even know it, I can
 mark one cache as favoured. I did. Nice view from there…</p>
<p>Woo-hoo! Even homsn got his arse moved, Arch GNU/Linux now has mksh
 R31c, like Fedora, Gentoo, soon Fink. World domination, anyone?</p>
----
Date: 13.09.2007
Author: tg@

<p>I’ve just put the last polishing steps for some in-tree software into
 cvs, and I suppose the release is imminent. If but XTaran would deliver
 some more sparc test results… I have no idea if XFree86® works there, nor
 if the ISO is bootable, I can just hope.</p>
<p>Since I’m fairly busy with my dayjob <em>and</em> have increased duties
 and responsibilities at FreeWRT, and Benny is working on his diploma, and
 we’re okay with the current code quality, I assume that what we have in
 the tree right now will be the final release.</p>
<p>Oh damn. I still need to work on the dual-arch bootable CD stuff. Crap.
 That means some more coding (where the assembly part is the easier half…)
 and possibly testing. But it’ll rock.</p>
----
Author: bsiegert@
Date: 14.09.2007

<p>Writing a diploma thesis is really a job where you can see how the
 UNIX style is superior to what Windows users are used to. Using (in my
 case) LaTeX and a Revision Control System (Subversion here), you enjoy
 lots of benefits: I can give the source code to someone for revision,
 tag the version I gave out, check in what I get back and merge. Compare
 this to using Word (eek) or OpenOffice.org: you can track changes, but
 if you work on the document in the meantime, it is not so easy to merge
 changes from two sources.</p>

<p>Add the fact that the result so far looks absolutely gorgeous, with
 nice margins, well-placed images and a great text font (I love
 Palatino). And the LaTeX way of doing automatic numbering and links
 worked perfectly when I decided in the middle to restructure what I
 already had. Managing my references with BibTeX, especially with <a
 href="http://bibdesk.sourceforge.net/">BibDesk</a> as a Mac&nbsp;OS
 front-end, is also a pleasure.</p>

<p>We had a discussion on IRC (#mirbsd, of course) about Revision
 Control Systems, triggered by tg@ whining about Subversion again. Let
 me just say that we have different opinions on this topic.</p>

<p>Apparently, GNU arch is more or less dead, many people are jumping on
 the git bandwagon. bzr (sp?) and Mercurial (hg) are also popular
 choices but seen less usable. I will definitely port svk though. They
 promise the good parts from Subversion without the overhead of
 libsvn_wc. "In fact, one of the motivations for writing svk was to get
 rid of that Spaghetti code." Sounds interesting. Working copies are
 smaller, checkouts are faster, mirroring is easier, they claim. Let's
 see.</p>
----
Date: 24.09.2007
Author: tg@

<p>Besides bumping the number of <img alt="A cachetour and nice weather"
 src="http://www.opencaching.de/statpics/106521.jpg" /> geocaches up, to
 18 caches found, three geocoins found, and only one DNF, I admit having
 been a tad lazy lately.</p>
<p>At the moment, we’re testing the current HEAD code intensively, and I
 think that, despite theoretically being able to release any time now, a
 good chance to find bugs (like these which led to mksh R31b, or that my
 vnd(4) encrypted home works more reliably now) shouldn’t pass unnoticed
 (and Benny is still fixing ports).</p>
<p>I will probably get my new server tomorrow. It will replace herc, and
 – sadly – its hostname too, since a Micro-ATX board only comes with two
 PCI slots (at least one too few for me anyway) and no ISA slots. But it
 is a fast machine, I already got the dmesg, has one Gig RAM, and at the
 moment, the Padlock AES/RNG stuff isn’t yet recognised (some hacking to
 do – but solidly setting it up is what counts now). Well, this opens an
 opportunity to use some spare Pentium Ⅰ board to write a framebuffer in
 the kernel for the Hercules card (and compatibles). If I get time.</p>
<p>You wouldn’t believe it: at work, I’m writing a user-friendly (woah!)
 front-end using dialog (yes, me!) for BIND (me the djbdns user)… and it
 is still sort of fun (sure, I’m using mksh for both the main programme,
 input loop and all, and parsing the zone file (slightly more restricted
 format than default, but good enough for us). It runs ssh as coroutine.
 (That’s why MirPorts’ misc/dialog is more recent than Debian sid…) When
 my boss sees it, I want to see his face. I bet it’ll be not unlike that
 of Benny when he first saw the Baselive-CD preboot selection menu.</p>
<p>Is this called summer laziness? I’m actually not really interested in
 hacking at the moment, even though we could use a release, and I could,
 as well, make use of my nmeadecode(8) project, since herc is now a pool
 server for Germany and Europe at the NTP Pool project. Quite a good one
 with a score of 20.0 at the moment, and an average offset of -53 ms (to
 the pool tester, which is an SNTP client), with a consistent and rather
 low standard deviation (0‥-100 ms), in contrast to Hephaistos, whose is
 pretty unpredictable. And nobody bitched for me using OpenNTPD.</p>
<p>Ah, yes, the dual-arch boot CD issue. I have plans. Stay tuned. Is is
 possible after all, I just need to get my SPARCstation 20 to boot off a
 CD-RW to test it…</p>
<p>Spam to the company mail account sucks.</p>
<p>Ah yes, and I better not respond to Benny’s above posting. But I will
 see if svk can be of use to access svn repositories, since I’m bound to
 use them in a couple of projects of mine. Well, not my projects, since,
 obviously, they would be using CVS then, but which I work on.</p>
<p>Benny and XTaran have won, <a href="@@RELPATH@@mksh.htm">mksh</a> (or
 rather, <tt>dot.mkshrc</tt>) now has <tt>dirs</tt>, <tt>pushd</tt>, and
 <tt>popd</tt> (exactly as csh(1) had them). The hooks <tt>chpwd</tt> as
 well as <tt>precmd</tt> were added to please some zsh freaks. (The dirs
 stuff uses <tt>chpwd</tt> now, for simplicity.)</p>
<p>mksh(1) still doesn’t correctly work (continue is broken) with the <a
 href="http://www.feyrer.de/NetBSD/blog.html/nb_20070917_0016.html">promising</a> <a
 href="http://undeadly.org/cgi?action=article&amp;sid=20070915195203&amp;mode=expanded">portable
 C compiler</a> though. <a href="http://marc.info/?m=119066747905967">It
 really is a pity</a>, but I don’t have a clue (yet).</p>
<p>(Damn, now I coded a whole lot of crap, even added C7 RNG/AES support
 despite planning to not hack. I guess I should get a life. On the other
 hand, the weather isn’t promising enough for that.)</p>
----
Date: 27.09.2007
Author: tg@

<p>Why does every friggin’ SPARCstation 20 from the last millennium make
 it easier to build a SCSI-based system with the modernst SCA hard discs
 (U-320 LVD) than a brand-new not-even-off-the-shelf server system?</p>
<p>The good part is I learned much more about SCSI today <em>again</em>.
 <br />The bad part is: I gave out 1 € (plus 10 € shipping…) on ePray to
 gain a bunch of 68-pin ./. 80-pin connectors. ☹</p>
<p>The remainder of my new server is looking good, though.</p>
----
Date: 28.09.2007
Author: tg@

<p>We’re actually very very close to release. I’m helf off by the issues
 with the SCSI cabling (see my earlier posting), my laziness (or rather,
 I’d like to call it being unable to enter deep hacking mode for a while
 ☺ honestly!), and a few missing things.</p>
<p>Well, I went and did some of the things. I read much source of kernel
 random(4) and random(9) stuff as well as OpenSSL, fixed a lot of things
 I found (oO ☻) and wrote a script (mircvs://contrib/code/Snippets/ is a
 good place for them…) to create a seed file for “openssl genrsa -rand”.
 This can be used to generate a <em>large</em> (4 Kib or so) secret key;
 since I still have the sparc and nwt (80486DX-33) around, I’ll just use
 two keys on tear: this one publically and an 1024 bit key bound only to
 the LAN (might even make it IPv6 only to annoy my visitors even more…).
 I also made arandom(4) reseed much more often if we have a hardware RNG
 (every 64 seconds instead of 10 minutes; I hope that’s okay, but we get
 64 Bytes of new entropy every 10 ms, so I guess…).</p>
<p>syslog(3) and friends are stupid, they truncate waay too often; I did
 a würgaround in logger(1) for now, letting it split up conservatively –
 at 512 bytes already; doesn’t catch all-binaries but what the hey…</p>
<p>There’s a new <tt>src/distrib/tools</tt> directory now, with releng’s
 playground. Like MirOS #7ter, we want to make the release CD dual-arch,
 bootable. But since #7, things have changed – you can use our ISOs as a
 kind of Live-HDD, Live-CompactFlash, etc. so this functionality must be
 retained (I know how now, I just have to code it… and get my sparc PROM
 to boot off a burned CD-RW). And I could even do this to the #10 series
 mini-ISO (cdrom10.iso). Having an ISO of approximately 8 MiB size, boot
 both architectures off it. Yay! (as benz would say)</p>
<p>pcc’s in the works, I like the activity but not the split and some of
 the directions… but at the moment I’ll only monitor (and contribute the
 needed MirOS support bits, of course) since we’re busy with other – and
 much more important – things, the impending release for instance.</p>
<p><tt>herc</tt> is in the <a href="http://www.pool.ntp.org/">NTP server
 pool</a>… so will <tt>tear</tt> be, but I wonder if we should do a same
 for entropy distribution (like randomnumbers.info et al. do)? Since the
 box has a hardware RNG and a pretty good in-kernel mixer, I’m having it
 exported to the public anyway (but not too well-known since my internet
 connection cannot handle much load).</p>
<p>Speaking of entropy… ICQ logs conversations proactively, according to
 ciruZ, so we sort of decided to just send random data to each other. We
 didn’t set it up yet, but is anyone else interested? Does ICQ close the
 accounts when they just send to random other accounts? I have some very
 evil ideas for mksh scripts… *grins*</p>
----
Date: 01.10.2007
Author: tg@

<p>Why does it always have to be us BSDers that have to find the bugs in
 crappy GNU saftware? Today’s thanks go to Peter Valchev for being truly
 helpful in tracking down something that I first thought of as an endian
 difference issue in UMAC-64 (the new one in ssh(1), you know). It turns
 out this was a bug in libgcc, and while libc contains “better” code, it
 wasn’t used due to the linkage order. Fixed. Thanks, pvalchev!</p>
<p>We’re a lot closer to release, despite the recent fluctuation, as I’m
 done with preparing the manifold-boot CD stuff and could quite simplify
 sparc support overall, as a side result. Now, just minor stuff is still
 to be done (especially my new server and the SCSI cabling), and we need
 a few full OS rebuilds… *sigh* so much for sleeping quietly, subsequent
 nights I will enjoy the sounds of a SPARCstation again.</p>
<p>I wonder where Benny is, he hasn’t been contactable for a while. Last
 thing I remember is he tried moving to France again. There you go…</p>
<p>The guy from the company where I bought my new server called today. A
 service to the customer… they always call and see if one is happy. That
 is new to me (as is that weird chassis) but not bad.</p>
<p>pkgsrc® is hereby officially dead. I cannot write an eMail (or rather
 I get bounces) to the official MAINTAINER address of mksh, and nobody’s
 caring. Hey, even Debian does get it! (And <a href="@@RELPATH@@mksh.htm#otheros">others</a>…
 you should be ashamed of yourself.) Coverity mostly relies on pkgsrc® –
 otherwise I’d have posted results of their latest scans already.</p>
----
Date: 05.10.2007
Author: tg@

<p>Today, not only <img alt="Teaching the younguns: fun in the outdoors"
 src="http://www.opencaching.de/statpics/106521.jpg" />me, but also <img
 src="http://www.opencaching.de/images/statpics/statpic120445.jpg"
 alt="weird nick, eh?" />gecko2 found another two caches. And: I think I
 hooked up Benny, as I found a couple in the vicinity of his hometown at
 his parents’ place.</p>
----
Date: 07.10.2007
Author: tg@

<p>Phew, we got a #10RC7 for both i386 and (days later) sparc now. Now I
 can refine the manifold-boot setup CD (7 MiB or so), maybe I’ll be able
 to create it on only one architecture, since “self-installing bootxx we
 are almost there”, and hardlink the HTML docs which are the same on all
 architectures (ignoring bugs in nroff(1) on sparc).</p>
<p>But first, let’s go geocacheing again, with Dr. Pfeffer, Addy, gecko2
 (alias Turodagnir) and myself. It’s good weather today. And because I’m
 not going to have tomorrow off I’d better enjoy the weekend.</p>
----
Date: 14.10.2007
Author: tg@

<p>FWIW, current CacheWolf development snapshots are available from <a
 href="https://herc.mirbsd.org/pub/cw/">my server</a>, please don’t
 overuse its bandwidth…</p>
<p>I did another <img src="http://www.opencaching.de/statpics/106521.jpg"
 alt="stats fun" />two geocaches with Dr. Pfeffer, who doesn’t have any
 internet access nor a statpic yet though. <em>Update:</em> He has now,
 <img src="http://www.opencaching.de/images/statpics/statpic106523.jpg"
 alt="only 26/24 caches?" />it looks like I’ve almost got him there.</p>
<p><a href="@@RELPATH@@mksh.htm">mksh</a> R31d is released, I just didn’t
 have any time to prepare a distfile yet. Please see the list of changes,
 <strong>everybody</strong> is strongly advised to upgrade.</p>
<p>Ordering things online sucks. I still do not have my SCSI converters.
 No progress on the MirBSD server front yet. I hope to be able to host a
 little box at my workplace. Maybe a VM. And the other equipment I wanted
 (flashlights for geocacheing, for instance) only has been brought to the
 packet service now, let’s see how long it takes… I wish I had a beer.</p>
----
Date: 15.10.2007
Author: tg@

<p>Today morning, I showed our website to a colleague. She told me she
 quite likes the design, the colours don’t hurt the eye. This has to be
 said (she allowed me to quote her here), in the face of all the critique
 on the current theme. (That said, the theme is not going to stay in an
 unmodified form though. I recognise there are problems.) She suggested
 we put the gothic ASCII-Art text into a graphic, together with the two
 logos. And “IEs for Linux” shows that a certain graphical browser has
 quite big issues with CSS in general.</p>
<p>My SCA adapters still haven’t arrived. I guess someone cries for a
 bad review at ePray.</p>
<p><a href="@@RELPATH@@mksh.htm#clog">mksh R31d</a> is there, finally.
 Well, at least the distfile. Since I’m at work right now, I cannot
 really do a proper release commit series (www, ports, etc).<br />This
 release is dedicated to spaetzle@freewrt.org who kept bugging me to
 look for another busy-loop spinning bug, and to a certain BSD-licenced
 <a href="http://pcc.ludd.ltu.se/">compiler</a> whose optimiser bug has
 yet to be fixed, still. (I’m running with /bin/mksh compiled with pcc
 without -O but with -xdeljumps o MirBSD right now.) Ah, and the distfiles
 are there now, finally, too.</p>
<p>Dr. Pfeffer now has a statpic (we had a meal (Döner Kebap) together,
 and I “persuaded” him to configure it) at OpenCaching now, see above,
 but the cache we wanted to do during lunch break, with my colleague,
 was unavailable. Closed during the winter, and the cache owner neither
 knew about it nor believed me at first (though she later fixed the
 information and thanked me or so, but at first… nah nevermind).</p>
<p>Benny’s back and in France again (ok he’ll travel to Dresden tomorrow,
 I guess he’s more on the train line than on the internet line ☺).
 Just good to know he still cares ☻</p>
<p>Waldemar wants me to produce SPARC CDs… *sigh* guess I really have to
 work harder on the MI installboot(8) stuff. Damn. But o-okay.</p>
<p>Sometimes, cloning autotools isn’t fun. For instance, when you realise
 that cutting down its triplet of compile-time, link-time and run-time
 checks is good, but you do need compile-time checks, since not everything
 can be done as link-time check (e.g. checking for declarations when using
 deliberately wrong ones to make the compile clash – these clash at link
 time when the declaration actually was not existent). Oh well. Fixed.</p>
----
Date: 18.10.2007
Author: tg@

<p>Okay, what has happened the last few days in MirWRT-Land? I’m sort of
 feeling ill, sneezing a lot, coughing some, having to depollute quite
 often. I wonder… I <em>am</em> taking some vitamins…</p>
<p>My SCA adapters arrived on Tuesday. Almost in the night. Okay. That
 was a bad review at ePray. Or so I thought. It did not accept that from
 me without me passing some kind of driving licence-alike test… weirdos.
 Then I got a “function not available”, went back in the browser history,
 had to edit the line again because € was changed to &amp;#8634; which was,
 in total, too long… submitted… rejoiced… or so I thought. They accepted
 it – finally – but then asked me if I want to add that guy to the list of
 my preferred sellers. Yeaaah, of course…</p>
<p>Then I worked on MI installboot(8), got done with the sparc part at a
 <a href="http://netzladen.org/">Netzladen</a> hacking session (well, more
 of a hacking-alone session, fukami just chilled and occasionally smoked
 (grr…) and Dr. Pfeffer came late – although he hacked on CacheWolf and I
 helped him test some diffs). I think I can now do what wbx@ prodded me for
 quite strongly on the phone: create a sparc bootable CD on i386 (or even
 non-MirBSD, for that matter). After bootxx/i386 is converted, I think I’m
 going to stop working on this until past the release, but it’s good to see
 that it works and can probably be easy to finish.</p>
<p>On Wednesday, I managed to add the SCSI discs (all five of them, after
 stealing jumpers from old boxen) to tear. They work quite nice, except the
 chassis is now humming. Well, 10kRPM drives. Okay. I low-level-formatted
 them of course, neither do I need or want the data which was on them before
 nor do I desire bad blocks if I have the chance to scan for them (Benny asks
 me “why” every time I do low-level formats, but I still believe in them,
 even though these aren’t MFM or RLL discs any more). And they’re really
 <strong>fast</strong>, I was amazed. I think I won’t need to RAID 1 the CVS
 repository into memory for speed, even if I could now.</p>
<p>Well, next on the agenda would be migrating to tear while releasing and
 already coding some post-release stuff. Damn, hen-egg problem. I wonder,
 but not about how I’m going to solve it but when I get my lazy arse moved ☺
 We’re making good progress nevertheless.</p>
<p>Benny agreed (via the phone) to speed up the build by several hours (on a
 P2-350 – probably much more on the sparc) by just linking HTML manual pages
 if the catman page is only a link too. I implemented it, but since these
 generated from &lt;bsd.man.mk&gt;’s MLINKS are hardlinked, I needed inode
 tracking and cacheing, <tt>ino_t</tt> is unsigned 32-bit, so mksh’s arrays
 need to be able to use 32, not 31, bit as index. Done now, and it pleased
 me to shock my packagers, doing as if mksh R32 were impending ☻</p>
<p>Ah yes, Opera got a security upgrade, and while playing with AWStats at
 work, I realised our Lynx didn’t get counted as Lynx but MSIE… sucks though
 it helps with certain sites, so I changed that. Can’t have enough people
 noticing the small ones (Lynx as well as MirBSD). Really.</p>
<p>I <em>am</em> going to have to write an install.sparc(7) page – talking
 with the MidnightBSD people I realised few people know how to netboot a
 sparc, and since all of our manual pages are online, I just could have
 pointed him there. But the mnbsd people are all quite nice.</p>
----
Date: 20.10.2007
Author: tg@

<p>I suppose this is the day my best friend moves back into this city, and
 since it’s due to his girlfriend I guess credit goes to her. Good. Now we
 can hang around more than the last years.</p>
<p>Today though I was at the others’ place (at cnuke@ and bogus), together
 with Kabelaffe, and we hacked a little, everybody on his own project, as
 we used to do in the past as well. I managed to create self-installing i386
 boot blocks, integrated the chain boot block and SunOS disklabel, and now
 everything is ready for MI installboot(8).</p>
<p>I also started to poke around the kernel for using the hardware-aided AES
 functions modern CPUs (not crypto extension cards!) provide. UVM swapencrypt
 is going to use this code soon. vnd(4) will use the OCF – crypto(9) – for
 operations though, so that users can select the actual algorithm used, and
 we retain backwards compatibility (plus, software blowfish is a little less
 CPU intensive than software Rĳndaël (AES)). I’ll have to write some glue
 first though, as the APIs differ. And I’m still wondering how to test all
 of this… I guess tear will have to hold for it prior to going live.</p>
<p>I still did not make any progress with the merged manual pages though.
 (Making a list which of them is the same between arches.) Although this
 would be nice to spot gcc/sparc/nroff bugs as well.</p>
<p>I had some conversation with Miod; maybe we should get boot.net back,
 as bsd.net kernels can’t be debugged (due to having their symbol table
 stripped, Miod says, but I don’t think it’s entirely stripped from what
 I see at elf2aout(1)’s code). But I still need some helpful people to
 e.g. maintain an mksh port inside OpenBSD Ports… and we definitively
 need a kernel coder inside the MirOS project.</p>
<p>It’s getting cold. Winter is near. Okay, so is Samhain.</p>
----
Date: 21.10.2007
Author: tg@

<p>Okay, the boot blocks are MI, the manual pages are split, generated
 much faster, and I’ve been working on the AES improvements. Today the
 weather doesn’t make me (or Dr. Pfeffer either) feel like going out,
 even though there are some interesting new caches in the area.</p>
<p>I’m still waiting for half of the equipment I ordered, but tear can
 finally be installed now (I’ll just change the internal cabling a bit
 beforehand though, to make my nerves more at ease).</p>
<p>UPDATE: Changing the cabling wasn’t easily possible, but I cleaned
 up the inside a little. But RAID initialisation definitively took too
 long, and afterwards I filled /dev/rsd0b with /dev/arandom at about
 80 KiB/s, which is most truly not enough for an U160 SCSI device, not
 to speak about the U320 devices I also have in there. So I need a new
 SCSI HBA, which is supported by MirBSD and handles U320 LVD drives.
 This sucks. And it postpones usage of my new server quite a bit. The
 devices almost all share IRQ 11, which sucks even more. I gather from
 Xen/Linux console output that ACPI devices have 256 IRQ lines? This
 would be the one and only reason for me to adopt it…</p>
----
Date: 22.10.2007
Author: tg@

<p>I played a little around at work, and MirOS does boot fine, even <a
 href="http://article.gmane.org/gmane.os.miros.general/7327">with
 networking</a>, in a Xen HVM configuration. Since it was at work, I
 couldn’t really do much. It was tricky, though. My boss now wants to
 know if Windows® would also work (I assume so, now I know how).</p>
<p>FreeWRT nor also has online manual pages,
 now guess whose script is doing the job. Right. I’m especially proud
 of the fact that this was in no way paid work (and that ekkoBSD was
 not for void either). I thought, after having hacked on it for quite
 a bit on the last days, that my other project (I am, after all, the
 provisional project leader until wbx@ is no longer <tt>EAVAIL</tt>)
 could benefit from it as well – I think manpages are a unique selling
 point in the embedded GNU/Linux distribution market (others have their
 own USPs… such as working X11…), and I discussed the idea with wbx@ a
 long time ago already; now it’s there. Of course, the packagers need
 to make sure themselves that their do-install targets actually provide
 the manpages, formatted or not, no matter, to the system.</p>
<p>herc crashed today due to a panic. This sucks. No idea why, and I
 had no time to check either, since the system is live. raid(4) boxen
 seem to tend to crash more often under low-ram, much-I/O situations.
 No data was lost, though.</p>
----
Date: 23.10.2007
Author: tg@

<p>Working on two OS projects has very nice synergy effects. Today, as
 yesterday, it affected manual page availability for both projects in
 a very positive way.</p>
<p>Damn. pax(1) has a bug on FreeWRT on the targets themselves. (And
 my WL-500g still doesn’t have any network on trunk, this seems to be
 a different bug.) And I have no idea yet as to why.</p>
<p>When Dr. Pfeffer doesn’t want to go geocaching, I do. They amount
 to 26 now, although 1 isn’t listed at the <img alt="ad-infested"
 src="http://img.geocaching.com/stats/img.aspx?txt=Hacking+MirBSD+since+2002&amp;uid=d6aaa6ad-797c-419a-91b3-8cf6a5b40658" />
 commercial site, and 2 aren’t listed at the open site.</p>
----
Date: 27.10.2007
Author: tg@

<p>Synergy effects are the best. The geocacheing software Cachewolf now has
 automatically
 generated nightly builds thanks to a FreeWRT box, whose developers help
 testing and spotting all the bugs in <a href="@@RELPATH@@mksh.htm">mksh</a>,
 make(1) and the HTML manpage stuff, and all projects get better. Wow.</p>
<p>I feel a little ill at the moment, which quite sucks. Not even bad enough
 to be unable to work, just… anyway, my bosses sent me to the Doctor.</p>
<p>I have generated a new 5120 bit RSA host key for use on tear (my new
 server), so that we can continue working on the #10 release timely even
 though the box is still not ready. (SCSI HBA woes, at the moment. Gosh!)</p>
<p>Benny, despite busy moving, is working on MirPorts again. Austriancoder
 and spaetzle are helping with FreeWRT. It’s good to know you’re not alone.
 Users are giving actual feedback. People (e.g. developers of other projects)
 are helping pro bono. The world is a good place still. Despite…</p>
----
Author: bsiegert@
Date: 28.10.2007

<p>The svk port is alive and kicking at <tt>devel/svk</tt>. I have used
 it for some simple RCS and merging scenarios with my gf's diploma
 thesis, and it seems to be working very well, better than subversion
 even. Startup time is very long (up to 10 seconds, even for <tt>svk
 help</tt>) but once it gets going, the operations themselves are
 quicker. And smerge is just very cool: you can merge one branch into
 another without manually keeping track of branch points and the like.
 It seems to me that svk can replace CVS's vendor branches easily,
 something Subversion does not do. Nice.</p>

<p>I should be starting my PhD thesis in november but I am still
 struggling with the bureaucrats. The problem is that I do not have the
 diploma itself, i.e. the peace of paper, as the evaluation of the
 thesis is not finished. So my employer told me to get a "provisional
 attestation" (?). Now, suddenly they tell me that they cannot take the
 one I sent them into account because my thesis is not yet noted. Great.
 Grr.</p>

<p>I tried to install my <i>T-Com Speedport W701V</i> router at my
 parents' place, only to have it crashing on me. It seems that the thing
 is stuck in an endless reset loop. The action of mine that brought it
 into this state was clicking "Step-by-step DSL installation". So much
 for T-Com (that does not exist as a brand any more anyway, I think) and
 for our channel motto <i>Technik ist schei&szlig;e und funktioniert
 nicht.</i> How right.</p>

<p><b>Update 20071231:</b> T-Com exchanged the router without a fuss.
 Apparently, this is a known problem.</p>
----
Date: 29.10.2007
Author: tg@

<p>gcc is crap, and I have no idea how to figure out where the cause of
 today’s herc/rant outage, kern_sysctl + 0x2f6, is, since it seems to
 have reordered the functions. Damn it.</p>
<p>I managed to get Dr. Pfeffer to go cache hunting with me again, and we
 didn’t find one (the most easy one), but the other two (at 18:00 and at
 19:00 local time, almost exactly). And at 16:00 I had the cache near his
 home location ☺ This makes, considering not both sites list all caches,
 a total of 29 (an offset of 3 at <img alt="freely caching is more fun!"
 src="http://www.opencaching.de/statpics/106521.jpg" />OC, and 2 at <img
 src="http://img.geocaching.com/stats/img.aspx?txt=FreeWRT+Project+Leader&amp;uid=d6aaa6ad-797c-419a-91b3-8cf6a5b40658"
 alt="travel bugs only here" />GC. Now I dropped a TB at an OC-only cache
 and am still trying to sort out THIS mess ☺</p>
<p>It’s raining now. Shit, considering I left my bike at Dr. Pfeffer’s
 place yesterday (due to me staying at some other place over night, where
 we did the caches), and I need it tomorrow (or rather not, if it’s still
 raining by then).</p>
<p>As usual, no data got lost (at HERC/RANT), and I held the cache in my
 hand almost immediately.</p>
----
Date: 22.11.2007
Author: bsiegert@

<p>I <i>finally</i> have the time (and the possibility!) to write a wlog
 entry. Thorsten has been absent since the end of november. The problem
 is that many MirOS services, mostly e-mail and the CVS master, were
 running on herc.mirbsd.org, which is located in tg's apartment. Now
 that he is not there, herc is also down. This means that mails do not
 work. I do not have the subscriber list for the mailing lists so I
 cannot resurrect these.</p>

<p>gecko's server aka anoncvs.mirbsd.org is the new CVS master. It is
 running Debian GNU/Linux with an older version of CVS. Thus, I had to
 fiddle a lot with the scripts in CVSROOT. The most obvious effect is
 that new commits do not have commitids; they get the process group of
 the commit process instead, which is meaningless and not unique.</p>

<p>However, as said on the news page, development continues, even if
 MirOS #10 will be pushed back even more. To follow CVS, look at the
 changelogs or into the cvsweb. anoncvs is running great.</p>

<p>There were two <b>security</b>-related commits this week: one in
 <tt>src/usr.bin/perl</tt>, the other in <tt>ports/devel/pcre</tt>.
 Please update those two. A binary package to replace perl in base will
 be available RSN.</p>

<p><b>Update 20071126:</b> See <a
 href="@@RELPATH@@permalinks/news_e20071126-nn.htm">news entry</a>.</p>
----
Author: bsiegert@
Date: 26.12.2007

<p>I fixed a very annoying bug (for me) in the build system for the
 website. It turns out that <tt>unset</tt> returns 1 in mksh (but not in
 bash) when the variable was unset before. However, make breaks as soon
 as one command fails. Adding a simple <tt>||&nbsp;true</tt> helps.</p>

<p>As seen in the news section, I will be in Berlin for 24C3. You should
 come, too. The talks and the atmosphere are great. The train journey
 was a bit more cumbersome than usual though: our ICE train was replaced
 by an InterCity. No reservations, not enough space and worst of all: no
 coffee.</p>

<p>Update (20.02.2008 tg@): Read <a
 href="@@RELPATH@@permalinks/wlog-9_e20080220-tg.htm">this</a>.</p>
----
Author: bsiegert@
Date: 31.12.2007
Title: mksh bug

<p>The problem from the last entry really seems to be a bug in ksh. In
 mksh, unsetting a non-existing variable gives a return value of 1. If
 <tt>set -e</tt> is active, then the script breaks at this point. This
 behaviour seems to be the same for the other ksh instances such as
 pdksh. From the mksh(1) manpage:</p>

<blockquote><p>Unset the named parameters (-v, the default) or functions
 (-f).  The exit status is non-zero if any of the parameters were
 already unset, zero otherwise.</p></blockquote>

<p>However, SUSv3 clearly mandates that <tt>unset</tt> must return a
 zero exit state in this case. And it seems to be a sane thing
 actually: in any case, the result is the same afterwards, i.e. the
 variable is unset. I could care less if it was set before. Btw, both
 bash and tcsh return 0. zsh returns 1.</p>

<p>I think I will leave this here for tg@'s return. It will be up to
 him to decide.</p>

<p>Update (20.02.2008 tg@): Read <a
 href="@@RELPATH@@permalinks/wlog-9_e20080220-tg.htm">this</a>.</p>

<p>Oh well, today is december 31. Happy new year 2008, everyone!</p>
----
Author: bsiegert@
Date: 07.02.2008

<p>I am making the first steps on my new MacBook Pro &ndash; a fine
 machine. I had had a bug report last year that MirMake does not build
 on a new Intel Mac running Mac&nbsp;OS 10.5 "Leopard". During 24C3, I
 had tried unsuccessfully to fix this. Now I finally know the
 reason.</p>

<p>It is an incompatibility between the getopt.h and getopt_long.c
 that come with MirMake and the ones in Leopard's libSystem. It seems
 that Apple has changed some function implementations to be UNIX2003
 compatible. The old ones have been preserved for binary
 compatibility, and the choice is done via "symbol variants", like
 <tt>_getopt@UNIX2003</tt>. The upshot is that you <i>need</i> to use
 the system header.</p>

<p>I devised a fix (use the system getopt(3) in Darwin) but I now I
need to figure out how to make a new mirmake release.</p>

<p>In other news, I am working on the talk for FOSDEM 2008 in
 Bruxelles. Stay tuned for more stuff about build systems (see
 news).</p>
----
Title: mirmake-20080218 Release Notes
Author: bsiegert@
Date: 19.02.2008

<p>The 20080218 release of mirmake is the first in about four months. It
 contains one important bugfix:</p>

<ul><li>Mac OS 10.5 ("Leopard") and Intel Macintosh machines are now
 supported.</li></ul>

<p>This new Darwin version is now UNIX2003(TM)-certified; to achieve
 compatibility, "symbol variants" are used for some functions, such as
 getopt(3). This, however, breaks the getopt implementation that comes
 with mirmake. Thus, the build system was changed to make sure that the
 native getopt is always used on Darwin platforms.</p>

<p>mirmake is a portable version of the MirOS make(1) program. It also
 contains the BSD Makefiles, i.e. bsd.prog.mk(5) and friends, some
 utilities like realpath(1), and a compatibility library (libmirmake)
 that has implementations for some functions not available on the target
 system&mdash;most notably hash functions for md5, sha1, sha2, and tiger
 hashes.</p>

<p>mirmake-20080218 can be downloaded from <a
 href="@@ABSPATH@@/MirOS/dist/mir/make/">/MirOS/dist/mir/make</a> on this
 server. The file hashes are:</p>

<pre>MD5 (mirmake-20080218.cpio.gz) = 5e6ecc4432b61e39e9907737d058309c
RMD160 (mirmake-20080218.cpio.gz) = 75de9d3a51570948935b31fb8a280a3ad00757a7
SHA1 (mirmake-20080218.cpio.gz) = 17251b1db87ceed85bd82dc52ca7ace7f7c77786
</pre>
----
Author: tg@
Date: 20.02.2008
Title: mksh not buggy

<p>As an update to Benny's <a
 href="@@RELPATH@@permalinks/wlog-9_e20071226-bsiegert.htm">first wlog entry</a>
 mentioning <a href="@@RELPATH@@permalinks/wlog-9_e20071231-bsiegert.htm">a
 possible mksh bug</a> I have to say that this was fixed in <a
 href="@@RELPATH@@mksh.htm">mksh R31b</a>: <i>The “unset” builtin always
 returns zero, even if the variable was already unset, as per SUSv3
 (reported by Arkadiusz Miskiewicz via pld-linux → oksh)</i></p>
----
Author: tg@
Date: 20.02.2008

<p>As a side note, sorry for the inconvenience. As you might have already
 read, “herc” had a hardware failure (broken keyboard controller chip, due
 to a screw short-circuiting it), and it was “resurrected” inside of “rant”,
 which cannot, however, be easily booted (as the discs were IDE, and it can
 only boot from SCSI or – via the fxp(4) card – PXE). Due to my away time, I
 was unable to restart the box after it hung up. I was, as of now, unable to
 finally transfer services to “tear”, the new box (VIA C7), because I still
 need a working SCSI U320 (or U160) controller. The planned-impending (but
 then delayed) transfer of services to “tear” caused me to not fix the “herc”
 hardware first (as it would not be worth the effort).</p>
<p>We will be working on restoring all services onto “herc”/“rant” within
 the next days, try to get a SCSI HA ASAP, and build an improved (and
 possibly more failsafe) infrastructure.</p>
<p>The unplanned away time causes a late #10 release, and it will not be in
 time for <a href="http://www.fosdem.org/">FOSDEM</a>, but it will come.
 Also, some things (nroff, Unicode) have been thought through once again,
 with interesting results, which will lead to further improvements in these
 areas in the future.</p>
----
Author: tg@
Date: 22.02.2008

<p>Today, I merged back the cvs repository from hephaistos and tweaked both
 the ChangeLog and idcache as well as the ,v files to have sort of correct
 Commit IDs. I'll have to go through a few files worth of diff, but that'll
 follow next. Benny has done good work, and also thanks a lot to gecko2.</p>
<p>The process group IDs have been preserved in the lower 32 bit of the new
 commit ids, the upper 44 bit are, as usual, the time.</p>
<p>We'll resume normal-heavy operation very soon, so keep your INBOXen ready
 :)</p>
----
Author: tg@
Date: 24.02.2008
Title: FOSDEM Zwischenbericht

<p>We actually distributed about 182 CDs yesterday, and today, early morning,
 no CDs are left any more. We’re also about to run out of flyers. Benny’s
 showcase box aided really in catching users (especially the pink mouse, for
 the female part of the visitors, who tried Frozen-Bubble when we offered it
 to them).</p>
<p>Benny and I also decided on Unicode improvements and hacked Mac OSX Leopard
 support into MirPorts, this time correctly. This is really weird, and both of
 my fellow Mac fanboys decided that Leopard is quite buggy and thusly sucks.
 Probably due to the UNIX2003 certification?</p>
<p>Bruxelles is fun, and the hotel was very good (not really cheap, but not
 too expensive either). Sadly we probably don’t have any time to really go
 geocacheing, and our usual restaurant – le petite planéte – no longer exists,
 although we found a suitable replacement, with a delicious Assiette Mergues.
 Belgian beer was as good as usual, although it makes getting up early on the
 next day more difficult. The OpenBSD people donated 3 cans of Jupiler to us,
 which was unexpected but makes room for hopes of improvement.</p>
<p>The frietjes booth outside actually understood my attempts to talk to them
 in dutch and, although my pronunciacion is very bad (of course), she told me
 it’s not too bad overall (for a duitslander). They seem to pronounce ‘ie’ as
 a long ‘i’… I need more practice, but this part of Bruxelles is mostly french
 only.</p>
----
Date: 26.02.2008
Author: tg@

<p>Dang, it’s much too late again, but I hacked some cool things into mksh,
 which were planned for some time; now I need someone to test this. Also,
 here strings (<tt>hd &lt;&lt;&lt;$str</tt>) are now documented (and do NOT
 work like in GNU bash unless <tt>$str</tt> is double-quoted), whereas the
 replacement substitution – <tt>${foo/b+(a)@(r|R)?(\/*)/baz}</tt> – isn’t.
 This should, however, further improve people coming from other shells.</p>
<p>Benny is still working on security updates – now: X11. I should better
 get my ports and ssh etc. upgraded too. If I just knew what was important
 now… we need actual user feedback for this, I think.</p>
<p>I wish OpenBSD’d update their sendmail(8), so we can do that too ☻</p>
----
Date: 28.02.2008
Author: tg@

<p>OpenBSD <em>is</em> weird. They did, in 4.3-beta locked-tree state, link
 OpenCVS to the build, but no fixes for the necessary sendmail upgrade or <a
 href="http://www.securityfocus.com/bid/27647/info">IP ID vulnerability</a>
 yet (or even planned).</p>
<p xml:lang="de">Schon mal geröstete und schokierte SOJABOHNEN gesehen? Hmm…
 die schmecken ja sogar. Ziemlich herzhaft.</p>
<p>Now I’m fixing Debian fixes to upstream software. Funny. But people who
 re-invent strdup(3) do belong shot, even if their crapware is public domain.
 Luckily, mgcc(1) catches <tt>sizeof (char *)</tt>.</p>
<p>I’m done with ${foo/bar/baz} support in mksh(1); the mcabber port can now
 do umlauts (stupid implementation, they should use more native functions,
 especially since they do link against libncursesw).</p>
<p>The MirPorts main page is now connected again. Rob “rjek” Kendrick is
 currently porting his small, fast, CSS capable, JS planned, NetSurf browser
 to MirOS (many thanks here!).</p>
<p>Benny is doing good progress on the XFree86® security fixes.</p>
----
Date: 29.02.2008
Author: tg@
Title: mksh releng

<p>I managed to ssh into all possible boxen to test whether the upcoming
 release of <a href="@@RELPATH@@mksh.htm">mksh</a> will work on them (well,
 the Debian GNU/kFreeBSD qemu instance had to be upgraded first). I even
 installed some Linux 2.4 and then OpenBSD on wbx’ Zaurus since nobody of
 them could give me a shell.</p>
<p>Still some testing to do, but I’m okay with what we have, not only for
 mksh(1) but also for the entire OS. Expect #10 finally next week or so.</p>
----
Date: 01.03.2008
Author: tg@

<p>Why do I always find bugs at almost after release time? Why do I let my
 coffee become cold, have too few milk at home, etc? Why do I sometimes
 forget to <tt>mount -uw /x</tt> before qemu’ing an image placed on that
 filesystem? Why do I sometimes forget to plug in the power of the laptop
 and then wonder why it suddenly turns off, having no APM nor ACPI?</p>
<p>I’d like to call a vote for <a href="@@RELPATH@@ports.htm">MirPorts</a>:
 replace the <tt>FLAVOR</tt> and <tt>FLAVORS</tt> variables by these with
 correct spelling (<tt>FLAVOUR</tt> and <tt>FLAVOURS</tt>), keep it as it
 is, support both with English preferred, support both with American dialect
 preferred? I’m strongly tending to British English and would like to have
 this general policy in MirOS.</p>
<p>OpenBSD/zaurus works, although it’s a PITA to get a working Linux 2.4 on
 it first. The USB NIC (aue(4)) doesn’t work, though (not enough power); but
 it at least tries, under OpenBSD, while it is ignored under Linux 2.4 and
 2.6; my USB stick works on the Zaurus but not on the laptop or the WL-500g;
 a CF card reader only works on the Asus box, so I must use that for data
 transfer (and cannot use ntpd(8), which sucks) with smallish 16 MiB and 32
 MiB CF cards from my digital camera…</p>
<p>And why do some bugs found past the last minute need so lengthy attempts
 at fixing because it cannot be done inside the current implementation?</p>
----
Date: 02.03.2008
Author: tg@

<p>After pushing out the mksh distfiles, ports, etc. (and, of course,
 spotting a couple of bugs too much for my taste), I finally found time
 to work some more on my TODO. rm(1) now can do random overwrites including
 file (and directory) renaming to random values before unlink(2)ing (and
 rmdir(2)ing). Thanks to TNF, again, for some of their code and bugs.</p>
<p>Another thing is putting the installer onto the Baselive CD. This would
 not easily be possible as of now, I see, because it uses, for example,
 some hard-coded paths like <tt>/mnt</tt> and commands like <tt>umount
 -a -t nonfs</tt>, which could cause normal operation on the rest of the
 running Live CD environment to cease. So this will not be in the tree in
 time for #10semel. Sorry, Benny, it was a good idea we had.</p>
<p>I also upgraded OpenSSH, but un-did the unifdef(1) <tt>-DBSD_AUTH</tt>
 change, as we need a non-BSD-auth version of sshd(8) for <tt>bsd.rd</tt>.
 During the process, of course, bugs were spotted… e.g. in the docs. Of
 course, the new internal sftp subsystem isn’t on the ramdisc, either.</p>
<p>And, I upgraded Sendmail, without the support of OpenBSD…</p>
<p>Note: new kernels and old <tt>/sbin/sysctl</tt> and
 <tt>/usr/bin/uname</tt>, and vice versa, will not have the
 <tt>kern.ospatchlevel</tt> entry, which is required to build
 XFree86® and/or imake(1) with MirOS.</p>
----
Author: bsiegert@
Date: 06.03.2008

<p>Now that tg@ is back, MirOS has certainly regained its momentum.
 Great work, it is good to have a developer like him.</p>

<p>For the last six months, we always distributed the same snapshot on
 exhibitions. I am almost ashamed to admit that the CDs we had at <a
 href="http://www.fosdem.org/2008/">FOSDEM 2008</a> were burned from the
 <a href="http://www.froscon.org/">FrOSCon 2007</a> ISO image that I had
 lying around on the showcase box, schaaf.mirbsd.org. So my radical
 proposal was: the code we have has had a lot of testing already and has
 shown no show-stopper bugs (except on the new Intel Macs, but that is
 another story). So: let's release what we have and call it MirOS
 #10.</p>
 
<p>However, we urgently needed to apply some security fixes first. My
 task was X. I managed to update the included freetype to 2.3.5, which
 contains many security-relevant bugfixes and is recommended for all
 users. Alas, many places under <tt>xc/</tt> have to be touched for it
 to integrate well. I also applied the X.org patch from OpenBSD
 4.2-stable. I had to do the applying by hand as there seemed to be some
 coding style changes from XFree86 to X.org but the code itself seems to
 have been mostly unchanged since 1987 or so. Some of it does not even
 have ANSI prototypes (in XFree86 at least).</p>

<p>Some ports have also been updated, mostly security fixes. My build
 machine is now MirOS in Parallels on a MacBook Pro. I have
 <tt>aqua/qt4-mac</tt> in my tree but it does not install quite right
 yet. A new, unified Ghostscript port is also in the pipeline. However,
 convincing the build system to <em>only</em> use the system zlib proves
 difficult.</p>
----
Date: 06.03.2008
Author: tg@

<p>Thanks Benny, I’m glad to have a developer like you too.</p>
<p>Whew. mksh is done. I hacked a little on mcabber, and <strong>if</strong>
 your libc is recent enough, it even can display the new uppercase eszett
 the DIN proposed onto us (ẞ ← it’s in fixed-misc in MirBSD, and in a few
 other fonts such as the Linux Libertine). Mine wasn’t, of course. My work
 system is, actually, too old… (currently I’m building i386 stuff either in
 a chroot or in a dual-boot).</p>
----
Date: 09.03.2008
Author: tg@

<p>The code is almost frozen, we’re only waiting for a few updates that
 should still go in. Benny allowed me to add the ‘u’ to the flavour
 variables of MirPorts, after a year or so of thinking about it ☺</p>
<p>I fought the Leopard today, but I won: we can now use our own
 getopt(3) suite on Mac OSX 10.5 again, and some other bugs and minor
 issues have been fixed too. Plus, all the hashes, including ADLER32,
 SFV, SUMA, TIGER and WHIRLPOOL, now work on Darwin too (tested on both
 i386 and macppc).</p>
<p>Now it’s release engineering. I have started tagging, after a few
 final updates and fixes, and asked Benny to write a release announcement.
 Let’s see when the builds are done, calculate a good four days for the
 sparc side. Afterwards, we’ll switch to wlog-10, and back up the repo to
 get it all on one CD (i386, sparc, source, CVS).</p>
----
Date: 10.03.2008
Author: tg@

<p>The i386 part of the #10semel release is already built, but, oh WTF we
 don’t have a codename for this release yet. Well, the sparc part is still
 compiling, which leaves us another few days to think of one. I’m already
 uploading part of the sets, so that the distribution process will be
 quicker later. (Some of the files will change later on, though.)</p>
<p>Benny already has written a release announcement draft. Like I said, he
 <em>is</em> my best man. He didn’t even attempt to list the changes, which
 might even be the better approach… In the meantime, I’m updating some of
 the web pages already – you can, in theory, netinstall #10 now, but some
 links will have to be fixed later.</p>
<p>I still <strong>urgently</strong> need a SCSI host adapter for my new
 server <tt>tear</tt>, U160 or U320, SCA LVD, 32-bit PCI, no RAID, supported
 by MirBSD (i.e. OpenBSD 3.5), as the current one, donated by wbx@, has <a
 href="http://marc.info/?m=119299679527756">issues</a>. Or a fix. Plans to
 migrate to <tt>tear</tt> have been postponed due to this problem, which
 makes the progress in the project seriously suffer.</p>
----
Date: 11.03.2008
Author: tg@

<p>This is probably the last entry in this wlog. If you are using the RSS
 feeds, you might either want to subscribe to <a
 href="@@RELPATH@@wlog-10.rss">https://www.mirbsd.org/wlog-10.rss</a>, or
 change your subscription to the new (as of yesterday) feed at <a
 href="@@RELPATH@@wlog.rss">https://www.mirbsd.org/wlog.rss</a>, which is
 a symbolic link to the current developers’ weblog.</p>
<p>A fix for the ppp(8) security vulnerability has been committed to
 MirOS #10-stable already. This is still in time for the release, and
 will be included in the source10.ngz dist set as well as in both i386
 and sparc base10.ngz dist sets. Thanks to TNF’s replaced, who mentioned
 the issue to me in the <tt>#!/bin/mksh</tt> channel in IRC.</p>
----
Date: 12.03.2008
Author: tg@

<p>Oh, another wlog entry ☺</p>
<p>I found out that, actually, you can commit into both a branch and HEAD
 within the same directory on the same commit command. It’s just our log
 scripts which suck. This will be fixed RSN. It works if you use another,
 <em>different</em> directory as the last one (like I thought). This also
 means you can ignore commitid 10047D8245653D8184A and 10047D8248447FC1F5F,
 as these never went live.</p>
<p>Someone wants to do <a href="http://article.gmane.org/gmane.comp.embedded.freewrt.bugs/1856">an
 appliance with FreeWRT</a>, maybe I can let him hire (and pay) me for that.
 I could definitively need the money at the moment (hint hint).</p>
<p>If not, I can always port MirPorts to MidnightBSD…</p>
<p>… and I actually did, this will lead to some changes, even a few real
 improvements not only for mnbsd but for mbsd too.</p>
----
Date: 13.03.2008
Author: tg@
Title: Das Beste zum Schluß

<p xml:lang="de">Für lange Zugfahrten o.ä, wo man keine Lust hat zu hacken, ist
 ganz gut dies hier geeignet: z.Zt. 128 je ca. 200 Lynx-Seiten umfassende <a
 href="http://www.thorsten-oberbossel.de/deutsch/hp/fanfic.shtml">Harry Potter
 Fanfics</a>, die ein recht logisches, aber manchmal nerviges Universum, das
 jedoch sich streng nach dem Original richtet, aufspannen. Einfach runterladen
 und dann offline lesen.</p>
<p xml:lang="de">Ich bin ja ehrlich gesagt immer noch am sicken, daß Freenode
 mir einfach den Nick „lynx“ geklaut hat… jetzt kann ich gar nicht mehr so
 deutlich anzeigen, daß ich am Schmökern bin. Merke: wer „linked nicks“ hat,
 sollte diese <em>trotzdem</em> alle 29 Tage mal touchieren, da man im Staff
 nicht nachfragt, selbst wenn der Hauptkontakt gerade online ist.</p>
<p xml:lang="en">I’m still pissed about Freenode taking the nick “lynx” away
 from right under my arse, having been online with the main nick of “linked
 nicks” (the NickServ feature), just because I had not used that nickname for
 a while. Note: touch all alternative nicks every 29 days. RichiH says it’s
 policy to at least ask the owner, but seemingly they don’t.</p>
----
Date: 13.03.2008
Author: tg@

<p>Today, I helped wbx@ to clean up his basement: DECstations, SPARCstations,
 VAXstations, Alphas, mac68k, hppa, SGI O2 and Indy, and some other boxen
 either went to the recycling company today or will tomorrow. gecko2@ retains
 some mac68k and maybe one hppa, I try to get some 32-bit sparc parts, and
 bogus got an E450 (heavy!) and an Ultra1 for toying around with, as he now
 exclusively runs Solaris.</p>
<p>It’s annoying that not every CPU works in every SPARCstation – for example,
 the two SPARCstation 10 we found have 33 MHz CPUs and 400 MiB HDDs, one has
 OpenBSD on it, one Solaris 5. Nice. Tomorrow we’ll look at the two
 SPARCstation 5 which are still there. The monitor sadly doesn’t work. Maybe
 one VGA conversion cable from the SGIs will help, but I don’t have a monitor
 capable of doing the sunfb 1152x900 (maybe with a zx(4) card…)</p>
<p>The SPARCstation 20 of mine (“demo”) has finished building the release
 kernels and tarballs, so I can proceed with the release engineering process
 ASAP. Like I said, we’ll do a unified medium. As with i386, the preliminary
 dist sets may show up on the download mirrors already for a while…</p>
<p>Building the release took about 6h22′ at 1 GHz on i386, and 81h22′ on 75
 MHz on sparc, for what it’s worth.</p>
----
Date: 13.03.2008
Author: tg@
Title: GPLv3

<p>It’s really annoying. This is actually a pre-release issue. There is a
 port, editors/nano, which snuck in before the release, containing GPLv3
 licenced stuff. This means that I either have to remove nano from the
 mirports tree for #10 or read the GPLv3 and allow it into the tree.</p>
<p>Looking for OpenBSD’s opinion on GPLv3 in ports, I found that my “dear
 friend”, the oksh developer, has struck again: his oksh-0.3 is GPLv3’d
 now. (At least he did not remove the UCB copyright from some files.) And
 to add insult to injury, the description of <a
 href="http://linux.softpedia.com/get/System/Shells/oksh-9881.shtml">oksh
 at Softpedia</a>, which is almost certainly provided by my “dear friend”
 Henry Jensen &lt;hjensen@delilinux.de&gt;, pretends that mksh(1) is not
 Bourne compatible (which it is, at least no less than oksh) and buggy,
 which it definitively is <strong>not</strong>. He said that, at the time
 of his forking, mksh was buggy, but could not tell me one single actual
 point. His only complaint against mksh was that it does not support the
 GNU bash-like <tt>$PS1</tt> hackery. *sigh* (Did I mention that oksh-0.1
 violated the MirOS licence on mksh?)</p>
<p>Phew, I read through it. And I think we have a sort of <a
 href="http://marc.info/?m=120545412919084">official stance</a> on the
 GPLv3 (even though bsiegert@ of course has to agree to make it truly
 official). I still don’t like it, but it could be worse, and for ports
 we do not need to care <em>that</em> much.</p>
----
Date: 14.03.2008
Author: tg@

<p>Yay! I got a SPARCstation 20, a SPARCstation 10, and a SPARCstation 5,
 several CPUs and sbus cards, an external HDD, an external CD, and some
 more toys, from wbx@ – he has no sparc parts left now. Sad, as he is the
 initiator of MirOS/sparc. Good, because I can cluster them now. I could
 test the framebuffer, XFree86®, even build binary packages with distcc
 if Benny ports it (I still have to get on friendly terms with distcc
 first though, and I won’t use it for official releases).</p>
<p>Being the better OpenBSD sometimes sucks. For instance, if our make(1)
 implicit rules generate <tt>grammar.h</tt> from <tt>grammar.y</tt>, and
 not <tt>y.tab.h</tt>, as a certain <tt>lex.l</tt> wanted to include. Well,
 that could be fixed – re-rolled ports10.ngz with new games/bsdgames.</p>
<p>I’m building a number of selected binary packages on the sparc and very
 few basic ones for i386, to add to the release ISO. (More binary packages
 can be downloaded from our mirrors later.) This is holding us a little,
 but I’ve got plenty of time over the weekend to carefully finish the
 release engineering process. Better than having bugs, eh?</p>
<p>I actually found a bug in <tt>gnu.port.mk</tt> during porting to mnbsd;
 gecko2@ had found it too but I couldn’t reproduce it back then.</p>
<p>Sorry for all the delay in the release announcement and publication,
 but first we have to get the ISOs ready – since they contain i386, sparc,
 source <em>and</em> CVS it’s a tad difficult and quite time-consuming.</p>
<p>Ha! Giving support in <tt>#cvs</tt> in IRC and being called life saviour,
 master, etc. is really giving me the chills, in a good way.</p>
<p>I’m exhausted, will continue hacking on the release tomorrow.</p>
<p>I’m trying to hand-bake a floppy for the sparc though. It won’t contain
 an installer, but enough to download an installer onto a HDD. Ports have
 aborted (gnupg can’t import keys, but decrypt them just fine – weird), but
 I’ve got enough for tomorrow.</p>
----
Date: 16.03.2008
Author: tg@

<p>Sometimes it’s good to double-check. Benny has found a bug in my fix to
 gnu.port.mk, leading to incorrect dependencies. I couldn’t get the sparc
 floppy to boot – several NetBSD® users had the same problem, leading to <a
 href="http://mail-index.netbsd.org/port-sparc/2001/09/05/0003.html">a
 posting about how to clean a sparc floppy drive</a>, luckily. Note that I
 am lazy, that’s why I just tested the floppy in my SS10 instead. This gave
 me quite a hard shock, though.</p>
<p>I prepared the Mini-ISO, and – new – a Midi-ISO containing the floppy
 images as well (if extra netboot kernels were required, they would be also
 on it, but boot.net is enough), which will take the place of cdrom10.iso on
 the download area, while the Mini-ISO will sit on the release ISO.</p>
<p>This means we’re now all set to release today. *crosses fingers*</p>
----
