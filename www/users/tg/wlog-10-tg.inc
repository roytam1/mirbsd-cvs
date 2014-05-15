RCSID: $MirOS: www/users/tg/wlog-10-tg.inc,v 1.7 2014/05/14 22:33:37 tg Exp $
Date: 14.04.2014 19:22
Author: tg@
Title: Enough of IT…
Tag: geocache rant

<p>I’ve been only sleeping, cooking and geocaching this weekend.
 Rather productive. Better than being angry at idiots, slowpokes
 (StartCom and Mozilla in particular), etc.</p>
<p><a href="@@RELPATH@@wptg.htm#banners" style="border:0;"><img
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
 “Maibaum”</a> (may pole, one of its many meanings). Click on
 the picture to get a slightly different one which has the text
 better legible.</p>
<p><a href="@@RELPATH@@pics/wlog/Ada-Maibaum.jpg"><img
 alt="Ada-Maibaum" src="@@RELPATH@@pics/wlog/Ada_Maibaum.jpg" /></a></p>
----
Date: 13.05.2014 16:25
Author: tg@
Title: Lügen haben lange Leitern
Tag: debian fun politics rant twitxr

<p><a href="@@RELPATH@@pics/wlog/anti-nrw.jpg"><img
 style="float:right; margin-left:1em; margin-bottom:3px;"
 alt="Photo von Laternenmast mit Wahlplakaten, oben Pro NRW, unten…"
 src="@@RELPATH@@pics/wlog/anti_nrw.jpg" /></a></p>
<p>Endlich tut mal jemand was gegen <a
 href="https://de.wikipedia.org/wiki/B%C3%BCrgerbewegung_pro_NRW">die
 rechte Hetzpartei</a>! – Ein Arbeitskollege fragt, ob man die nicht
 einfach mit einem langen Heckenschneider abmachen kann… aber sie so
 lächerlich zu machen hat auch was ☺</p>
<p>Finally, someone is doing something against <a
 href="https://en.wikipedia.org/wiki/Pro_NRW">this Nazi party</a>!
 A coworker wondered whether it’s legal to cut them off with a long
 tool, but making them ridiculous like this is also funny ☻</p>
<p>(Explanation: the “Pro NRW” people put their campaign thingies
 (sorry, I don’t speak English well) up on lamp posts very high,
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
Tag: debian

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
----
