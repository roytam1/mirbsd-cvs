<!-- PageID: news -->
<small class="rcsid">$MirOS: www/content/bmV3cw__.inc,v 1.60 2006/03/01 21:40:10 tg Exp $</small>

<h1>Current MirOS News</h1><ul>

<li>19.03.2006<br />We've added a new server to the Freeforge IRC network,
	<tt>maou.66h.42h.de</tt> Port 6668 (SSL), 6667 and 6666 (non-SSL).
	You can either directly connect to that server or the round-robin,
	<tt>irc.66h.42h.de</tt> (or <tt>irc4.66h.42h.de</tt> for IPv4-only
	connections). We sit on channel <tt>#mirbsd</tt> and <tt>#bsd</tt>
	like before.</li>

<li>01.03.2006<br />Again success building a cross-compiler to i386 Debian
	GNU/Linux from MirOS (tested with printf(1) because GNU libc is an
	ugly piece of shit unable to build mksh(1) sh(1) date(1) etc.) but
	this time with GCC 3.4.6 and <tt>--with-sysroot</tt>.</li>

<li>26.02.2006<br />The MirOS Project glances by appearance at FOSDEM 2006
	and sells T-Shirts and CD-Rs of the latest snapshot which also has
	an upgraded OpenSSH.</li>

<li>21.02.2006<br />Improvements and bug fixes in the randomness area; the
	arc4random_add(3) function finally works as designed. PHP contains
	SQLite2; Midnight Commander has been updated after 3 years. ssh(1)
	was updated to OpenSSH-current and the code was cleaned up. Compat
	ports were fixed as well as bugs in the package upgrader. Keys for
	vnconfig(8) can now be stored in an external file. Access logs for
	httpd(8) are now stored in a different format displaying SSL infos
	(whether SSL was used and which crypto suite chosen).</li>

</ul>
<p>For older news, please refer to the <a href="/?older">historical news
 page</a>, or the developers' weblog.</p>
