<small class="rcsid">$MirOS: www/content/bmV3cw__.inc,v 1.14 2005/03/30 12:57:00 tg Exp $</small>

<h1>Current MirOS News</h1><ul>

<li>12.04.2005<br />
	There has been a new release of MirMake, along with distfiles for:
	MirCksum (tested, ports/essentials/cksum), MirNroff (untested). If
	you use MirPorts/Darwin, you must execute the installation script,
	<tt>ports/infrastructure/install/Setup-Darwin.sh</tt>, again.</li>

<li>30.03.2005<br />
	Today we present a new, binary and source, snapshot to the general
	public. This snapshot comes with i386 binaries, source code for X,
	the base system (including gnu and gcc) as well as the latest cool
	MirPorts checkout. It's available for retrieval at the usual place
	as well as our <a href="http://f.scarywater.net/miros/">BitTorrent
	tracker</a> (while there, don't forget to donate the sysop of this
	tracker because he is giving this service to us for free). Also, a
	new CVS Repository snapshot has been published.<br />These are all
	signed using the new personal PGP key of developer tg@ that should
	be available from the public keyserver network, for example at the
	DFN-PCA keyserver.<br />C++ support is included, yet still (except
	for xlock) not working correctly due to a GCC bug.</li>

<li>28.03.2005<br />
	The MirOS Project proudly announces that MirPorts is open for both
	using and modifying again and the transition to the new repository
	has finished successfully. Several ports have been updated, mostly
	to newer versions than OpenBSD 3.7-current has to offer.<br />Also
	GCC 3.4 is now almost feature-complete, with C, Objective-C, gcov,
	protoize, unprotoize, Pascal, Ada and C++ support in the compiler,
	leaving only java missing; with support libraries for all of these
	front-ends &ndash; however, libstdc++-v3 is still slightly broken,
	meaning anything which uses iostreams dumps core, we'll leave that
	to fix for someone who actually knows what templates are.<br />The
	C++ breakage does not affect libGLU and xlock, the latter thus now
	comes with all OpenGL modi as well.</li>

<li>25.03.2005<br />
	We have imported gcc 3.4-stable (20050325), currently working with
	the C, Ada, Objective-C and C++ front-ends and Ada and Objective-C
	support libraries. Support for exception handling through a shared
	libgcc has been written and is currently being tested. After C++'s
	support library has been added a new feature snapshot will be made
	available to the general public for testing.</li>

</ul>
<p>For older news, please refer to the <a href="/?older">historical news
 page</a>, or the developers' weblog.</p>
