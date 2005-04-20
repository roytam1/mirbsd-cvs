<small class="rcsid">$MirOS: www/content/bmV3cw__.inc,v 1.16 2005/04/19 22:17:20 tg Exp $</small>

<h1>Current MirOS News</h1><ul>

<li>20.04.2005<br />
	We're closer to solving that X/GLX problem, thanks to David Dawes,
	who is tracking it down to threads at the moment. The promised new
	<a href="/?clog-2005#snap0420">snapshot</a> is available as usual,
	via the BitTorrent tracker. Direct downloads should work soon too.
	Please report functional installs but especially failures, to help
	making MirOS #8 the best release ever.</li>

<li>19.04.2005<br />
	The current development version of MirOS has received numerous bug
	fixes in gcc, XFree86&reg; and others over the last few days. Also
	the in-tree CVS has been updated to fix a security issue, which <a
	href="https://ccvs.cvshome.org/servlets/NewsItemView?newsItemID=142">is
	described at the CVS homepage</a> and has got new features able to
	improve our infrastructure. Furthermore, after a long period of no
	port being available, the GNU Debugger is now integrated in MirOS,
	as part of GNU Binutils, again (we are using a development version
	from January 2005). Only CLI for now, the TUI requires, as of now,
	linking against GNU libreadline which does not come with MirOS any
	more. Fixes for libedit are probably easy.<br />The fixes are made
	available via a new development snapshot, which is currently being
	built and expected to hit the mirrors within the next 2 days.</li>

<li>12.04.2005<br />
	There has been a new release of MirMake, along with distfiles for:
	MirCksum (tested, ports/essentials/cksum), MirNroff (untested). If
	you use MirPorts/Darwin, you must execute the installation script,
	<tt>ports/infrastructure/install/Setup-Darwin.sh</tt>, again.</li>

</ul>
<p>For older news, please refer to the <a href="/?older">historical news
 page</a>, or the developers' weblog.</p>
