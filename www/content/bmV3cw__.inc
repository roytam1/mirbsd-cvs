<!-- PageID: news -->
<small class="rcsid">$MirOS: www/content/bmV3cw__.inc,v 1.56 2006/02/15 20:41:51 tg Exp $</small>

<h1>Current MirOS News</h1><ul>

<li>21.02.2006<br />Improvements and bug fixes in the randomness area; the
	arc4random_add(3) function finally works as designed. PHP contains
	SQLite2; Midnight Commander has been updated after 3 years. ssh(1)
	was updated to OpenSSH-current and the code was cleaned up. Compat
	ports were fixed as well as bugs in the package upgrader. Keys for
	vnconfig(8) can now be stored in an external file.</li>

<li>15.02.2006<br />There is a <a href="/MirOS/current/i386-20060215/">new
	snapshot</a> with all the features below (attention: ssh/scp(1) is
	not updated regarding CVE-2006-0225 yet). There is also a new repo
	seed. Ports of this snapshot are not used to update #8 because the
	overall quality is in an unknown state.</li>

<li>30.01.2006<br />We now have an iconv(3) implementation by Citrus (from
	NetBSD&reg;) in the base system, used by lynx(1). There is also an
	nl_langinfo(CODESET) now which works.<br />Switched to use mmap(2)
	malloc(2), enjoy the breakage in third-party applications ;)<br />
	Security updates for perl(1) and the kernel. Updated mksh(1) also.
	We do not deliver precompiled perl header files any more.<br />gcc
	now complains if CFLAGS are not honoured.</li>

<li>26.01.2006<br />There are new, working, permanent homepages of both <a
	href="http://mirbsd.de/jupp">jupp</a> and the MirBSD korn shell <a
	href="http://mirbsd.de/mksh">mksh</a> these are redirections which
	are hosted in waldi's Zope and (usually) point to a working mirror
	just like for <a href="http://mirbsd.de/">MirOS itself</a> and the
	<a href="http://cvs.mirbsd.de/">MirOS CVSweb</a> redirector.<br />
	There is also a new version of jupp released, joe-3.1jupp5.</li>

<li>24.01.2006<br />Progress is being made both in ports as in base. A new
	snapshot is scheduled to be uploaded in a few days also fixing the
	HTML problems with the online manual pages.</li>

<li>20.01.2006<br />Some of the domain issues have been solved, and the #1
	well-known mirror (mirbsd.mirsolutions.de) is back up and running,
	although only with a kludge. Expect mirbsd.org to point to the new
	master server soonish, and some overhaul of the website content to
	reflect the changes. The old CVS repositories have been frozen and
	published as a cpio-ball (all three together); there will be zero,
	really no commits at all any more to ocvs.<br />The G**gle Ads are
	gone from the website and will cease to exist in the manual pages,
	too. They closed my account for supposed abuse which I (tg@) can't
	have done (only installed opera afterwards to login and check if I
	can see something in the logs, couldn't login already), right when
	the first payment was about to be issued (accumulated some 100 USD
	in over 10 months), and do not react on my enquiring eMail at all.
	This just sucks, and they do owe me that money.<br />Check out the
	<a href="/?wlog-8">web log</a> too, it's a bit more active than in
	the past (not much though).<br />MirSirc has been updated in ports
	relative to the public preview, use that. A new <tt>/cvs</tt> cpio
	ball will be published quite soon, too.</li>

</ul>
<p>For older news, please refer to the <a href="/?older">historical news
 page</a>, or the developers' weblog.</p>
