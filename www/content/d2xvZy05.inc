<!-- PageID: wlog-9 -->
<small class="rcsid">$MirOS: www/content/d2xvZy05.inc,v 1.3 2006/06/28 00:49:59 tg Exp $</small>
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

<p id="eof">Good luck, have fun, take care etc.pp</p>
