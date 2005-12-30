<small class="rcsid">$MirOS: www/content/d2xvZy04.inc,v 1.5 2005/12/29 15:04:04 bsiegert Exp $</small>
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
</div>

<p id="eof">Good luck, have fun, take care etc.pp</p>
