<small class="rcsid">$MirOS: www/content/bmV3cw__.inc,v 1.12 2005/03/26 01:20:42 tg Exp $</small>

<h1>Current MirOS News</h1><ul>

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

<li>22.03.2005<br />
	The MirOS Project has obtained a new logo to identify the project.
	It will look quite familiar for a couple of you, but we obtained a
	full permit to identify it with anything MirBSD&trade;.<br />Also,
	the GNU Compiler Collection 3.4.4 has made it into the source tree
	and is being ported; XFree86&reg; has been contacted.</li>

<li>20.03.2005<br />
	We have updated our XFree86&trade; to the recently released 4.5.0,
	with only minor breakage along the way. Also, MirPorts are getting
	fixed by bsiegert@ after the transition to the new CVS repository.
	This means the next snapshot will rock even more, especially since
	X11 is built using systrace now, too; we'd appreciate if our users
	were going to test them hard and help fixing problems.<br />As for
	the website design changes: it's not yet finished, but we're still
	waiting for delivery of the new images. Stay tuned.</li>

</ul>
<p>For older news, please refer to the <a href="/?older">historical news
 page</a>, or the developers' weblog.</p>
