<!-- PageID: wlog-9 -->
<small class="rcsid">$MirOS: www/content/d2xvZy05.inc,v 1.12 2006/07/06 13:40:40 tg Exp $</small>
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
  doesn't support %_aX, added some acronymes, and benz did cups.</p>
</div>

<p id="eof">Good luck, have fun, take care etc.pp</p>
