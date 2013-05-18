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
 <p style="margin-bottom:0px;">What do you think about the following</p>
 <div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;">
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
	MirBSD demo.66h.42h.de 9 Kv#9s81-stable-20060627 GENERIC#92 sparc
  </pre>
 </div><p style="margin-top:0px;">(ciruZ thinks it is pretty cool ;)</p>
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
 <p>Thie image: <img src="http://www.opencaching.de/statpics/106521.jpg"
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
 <p><a href="/?licence">/?licence</a> is now up to date again, and links
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

 <p>Okay, the <a href="/newsite/">new website is online</a>, with fixes.
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
  option <tt>-fomit-frame-pointer</tt> &ndash; cought by my favourite <a
  href="/?jupp">text editor</a>.</p>
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
  regexp code. While cought using the 'P' option (cf. malloc.conf(5)), I
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
Date: 04.01.2006
Author: bsiegert@

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
 and I can use <a href="/?jupp">jupp</a>; no BSD make there though).</p>
----
Date: 15.06.2007
Title: I'm bored so lemme write something here…
Author: tg@

<p>We now have an uppercase Eszett (ſz ligature) ẞ in the fixed-misc fonts
 and my <a href="/cvs.cgi/contrib/samples/dot.Xmodmap">keymap</a>; it maps
 towlower(L'ẞ' == 0x1E9E) = L'ß' == 0x00DF, whose upper-case mapping stays
 at L"SS" though. I sent the changes in the font to Markus Kuhn, hoping he
 will integrate them in the next stock XFree86® (and that x.org crap too…)
 version.</p>
<p><a href="@@RELPATH@@mksh.htm">mksh</a> is now a better <tt>/bin/sh</tt>
 for some people in Debilian who don't know of Korn Shell tradition. Also,
 it won't try to execute ELF, a.out, COFF, gzip and NE any longer.</p>
<p>Been working on <a href="https://www.freewrt.org/trac/">FreeWRT</a> all
 the time (even during the dayjob), so I didn't have the energy left to do
 more on the SPARC issues.</p>
----
Date: 25.06.2007
Title: libnointl
Author: tg@

<p>Before I forget to write this down… today, I released a piece of code I
 call <a href="/cvs.cgi/contrib/hosted/libnointl/">libnointl</a>. This was
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
 is unneccessary). I'm even thinking of removing all pre-R30 stuff off the
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
<p>Somehow, I also managed to wreck something in my other pet project – <a
 href="https://www.freewrt.org/">FreeWRT</a>. It is often annoying to work
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
 able to make <a href="https://www.freewrt.org/">FreeWRT 1.1</a> shine, so
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
<p>At work, I hacked some major C code for FreeWRT today, namely in the <a
 href="https://www.freewrt.org/svn/branches/common-nfo/tools/nfotiser/">nfotiser</a>
 (and <a href="https://www.freewrt.org/svn/branches/common-nfo/tools/sqlite/nfohelpr.h">here</a>).
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
 I bet they’ll be using GPLv3 next – and GFDL for the <span style="text-decoration:line-through;">man</span>
 er… <span style="text-decoration:line-through;">texinfo</span> pages (now what, GNU software doesn’t use manual
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

<ol><li><p><a name="bsiegert-20070902-ref1"></a>Miller, P.&nbsp;A.,
 Recursive Make Considered Harmful, <i>AUUGN Journal of AUUG Inc.</i>,
 <b>19</b> (1), 14&ndash;25 (1998).</p>
 <p>URL: <a
 href="http://miller.emu.id.au/pmiller/books/rmch/">http://miller.emu.id.au/pmiller/books/rmch/</a></p></li></ol>
----
