<!-- PageID: wlog-9 -->
<small class="rcsid">$MirOS: www/content/d2xvZy05.inc,v 1.21 2006/07/22 05:24:37 tg Exp $</small>
<h1>MirBSD &ndash; WTF is Verpeilungsfaktor?</h1>
<p><small><a href="#eof">bottom</a> or <a href="/?older">older</a>
 editions</small></p>

<div class="wlentry">
 <h3 id="e20060625">25.06.2006 by tg@</h3>
 <p>I'm committing this as 2006-06-25, but actually, I haven't slept for
  <em>more</em> than 31 (thirty-one) hours now, so it could very well be
  under 2006-06-24. I'm going to sleep now, but not without releasing an
  ISO of MirOS #9semel on BitTorrent.</p>
 <p>There's now a new <a href="/?bt">BitTorrent info page</a> not linked
  anywhere except from the tracker (and here). It ought to describe what
  the torrent will give you.</p>
</div>

<div class="wlentry">
 <h3 id="e20060627">27.06.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060629">29.06.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060630">30.06.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060702">02.07.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060703">03.07.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060704">04.07.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060705">05.07.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060706">06.07.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060708">08.07.2006 by tg@</h3>
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
  page of <a href="/?mksh">mksh</a> got pushed up to -current and a text
  about its requirements.</p>
 <p>Adding the above functionality is a milestone, btw.</p>
</div>

<div class="wlentry">
 <h3 id="e20060709">09.07.2006 by tg@</h3>
 <p>Thanks to Dr. Pfeffer (pepper) of BOSng, I've now also been out to a
  geocacheing session for the first time, with his Windows&reg; PDA that
  can do GPS. It took us <em>quite</em> some time, but it was helluv fun
  and I hope we'll continue the journey.</p>
 <p>Thie image: <img src="http://www.opencaching.de/statpics/106521.jpg"
  alt="statistics" /> will show the hopefully increasing number although
  I won't join the hype. I don't like hypes.</p>
</div>

<div class="wlentry">
 <h3 id="e20060716">16.07.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="b20060719">19.07.2006 by bsiegert@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060721">21.07.2006 by tg@</h3>
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
</div>

<div class="wlentry">
 <h3 id="e20060723">23.07.2006 by tg@</h3>
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
  Yay for the Korn Shell!</p>
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
</div>

<p id="eof">Good luck, have fun, take care etc.pp</p>
