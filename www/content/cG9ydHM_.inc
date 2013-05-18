<small class="rcsid">$MirOS: www/content/cG9ydHM_.inc,v 1.7 2006/01/20 13:08:10 tg Exp $</small>
<h1>MirPorts: The MirOS Ports Framework</h1>

<h2>Installation instructions</h2>

<p>Please refer to the <a href="/cman/man8/Setup.sh.htm">installer's
 manual page</a> for an invocation reference.</p>

<p>On MirOS BSD, you can do the backwards-compatible</p><pre>
 $ cd /usr/ports
 $ make setup
</pre><p>as well (SUDO is invoked automatically).</p>

<h2>Using the MirPorts Framework</h2>

<p>To be filled in...</p>
<p>Basically:</p><pre>
 $ cd /usr/ports/editors/joe
 $ <b>m</b>make install clean
 $ echo export EDITOR=/usr/mpkg/bin/jupp &gt;&gt;~/.profile
</pre>

<h2>Writing ports for the framework</h2>

<p>To be filled in...</p>
