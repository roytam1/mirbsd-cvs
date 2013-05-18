<!-- PageID: ports -->
<small class="rcsid">$MirOS: www/content/cG9ydHM_.inc,v 1.10 2006/08/09 16:19:47 tg Exp $</small>
<h1>MirPorts: The MirOS Ports Framework</h1>

<p>The official MirPorts homepage can always be reached at <a
 href="http://mirbsd.de/ports">http://mirbsd.de/ports</a> which
 redirects to a &quot;known working&quot; mirror.</p>

<h2>Installation instructions</h2>

<p>Please refer to the <a href="/cman/man8/Setup.sh.htm">installer's
 manual page</a> for an invocation reference.</p>

<p>On MirOS BSD, you can do the backwards-compatible</p><pre>
 $ cd /usr/ports
 $ make setup
</pre><p>as well (SUDO is invoked automatically).</p>

<h3>Macintosh users</h3>

<p>You might need the following commands. They assume the Bourne
 shell (GNU bash is pre-installed) as user shell; source SetEnv.csh
 if using the C shell (tcsh) instead. bash is still required to
 build, though.</p><pre>
 $ localbase=$HOME/.mpkg	# or something similarily sensible
 $ cd ports
 $ mkdir -p $localbase/bin
 $ MKSH=$localbase/bin/mksh bash Setup.sh -uel $localbase
 $ . $localbase/db/SetEnv.sh	# repeat each time you want to use it
</pre>

<h2>Using the MirPorts Framework</h2>

<p>To be filled in...</p>
<p>Basically:</p><pre>
 $ cd /usr/ports/editors/joe
 $ <b>m</b>make install clean
 $ echo export EDITOR=/usr/mpkg/bin/jupp &gt;&gt;~/.profile
</pre>

<h2>Writing ports for the framework</h2>

<p>To be filled in...</p>
