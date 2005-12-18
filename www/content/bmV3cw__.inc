<small class="rcsid">$MirOS: www/content/bmV3cw__.inc,v 1.42 2005/12/16 16:53:40 tg Exp $</small>

<h1>Current MirOS News</h1><ul>

<li>18.12.2005<br />First public development snapshot of tg@'s fork of the
	sirc IRC client, <a href="https://tg.mirsolutions.de:445/bsd/mirsirc-20051218.tgz">MirSirc</a>,
	released for peer review (relative to <tt>/usr/local</tt>).<br />A
	lot of pending fixes for the build of the whole system was revised
	and committed in an overnight no-sleep session at Netzladen.</li>

<li>16.12.2005<br />MirPorts Framework: first step at implementing package
	upgrades (works for very simple setups).<br />CVS: finally, passes
	the CVSREADONLYFS environment variable (or -R flag) to the server,
	if using the :ext: protocol (rsh/ssh). Might break with quite some
	servers, including anoncvssh until today, but it's worth the pain.
	Trust me.<br />Several ports updated / fixed: chemtool cups djbdns
	esound esp-ghostscript gentium-font libtool* mirmake openvpn opera
	pine/c-client/imapd sirc terminus-font xmms.<br />Perl on Mac OS X
	and malloc fixed in the ports infrastructure.<br />*) No final fix
	yet, communicating with upstream.</li>

<li>14.12.2005<br />Updating project servers to new snapshot; expect some,
	minor, instabilities. Switched IRC channel from OFTC to FreeForge,
	with SSL soon and VPN already enabled: server thor.66h.42h.de:6667
	or irc.freeforge.net:6667 channel #mirbsd</li>

<li>07.12.2005<br />New i386 binary snapshot, source snapshot and CVS repo
	cpio bowl available for public download. Happy Birthday!</li>

</ul>
<p>For older news, please refer to the <a href="/?older">historical news
 page</a>, or the developers' weblog.</p>
