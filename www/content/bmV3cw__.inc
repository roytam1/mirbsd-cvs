<!-- PageID: news -->
<small class="rcsid">$MirOS: www/content/bmV3cw__.inc,v 1.65 2006/04/06 12:00:59 tg Exp $</small>

<h1>Current MirOS News</h1><ul>

<li>11.04.2006<br />On <a href="http://f.scarywater.net/miros/">BitTorrent
	</a> there is a new snapshot available, which, for the first time,
	is a combined Live/Install CD. From now on, you can also cat(1) or
	dd(1) the ISO (either cdrom8.iso or the live/install ISO) onto the
	hard disc and just load it from there, without installboot(8/i386)
	needing to be run (it's included on the CD already). There are few
	bugs in this snapshot, some of which I already know and fixed. I'd
	appreciate everyone to test it and send in results, whether failed
	or succeeded (especially if there is a regression e.g. regarding a
	normal installation). Thanks!</li>

<li>06.04.2006<br />The Ada and GCJ compilers are no longer delivered with
	MirOS-current. Users who require them must now build these drivers
	manually by changing <tt>/etc/make.cfg</tt> and building the "gcc"
	module. Note: GNAT (the Ada compiler of GCC) requires itself to be
	built (you can pull it from an older snapshot or #8-stable).</li>

<li>29.03.2006<br />We've added a new server to the Freeforge IRC network,
	<tt>herc.66h.42h.de</tt> Port 6668 (SSL), 6667 and 6666 (non-SSL).
	You can either directly connect to that server or the round-robin,
	<tt>irc.66h.42h.de</tt> (or <tt>irc4.66h.42h.de</tt> for IPv4-only
	or <tt>irc6.66h.42h.de</tt> for IPv6-only connections). Note: this
	server does have IPv6 connectivity, however it's only a SixXS over
	ADSL (consumer line) connection, so don't overload it.</li>

<li>27.03.2006<br />In case you have acquired a MirOS CD-ROM "FOSDEM 2006"
	edition please verify the checksums of the data on the CD. Some of
	the CDs we distributed at FOSDEM were burned from a bad ISO.</li>

</ul>
<p>For older news, please refer to the <a href="/?older">historical news
 page</a>, or the developers' weblog.</p>
