<!-- PageID: anoncvs -->
<small class="rcsid">$MirOS: www/content/YW5vbmN2cw__.inc,v 1.13 2006/06/12 23:48:56 tg Exp $</small>
<h1>Anonymous CVS access to the MirOS repository</h1>

<h3 id="what">What is anonCVS?</h3>
<p>#include &lt;nice_blurb_about_what_anoncvs_is.h&gt;<br />
#include &lt;nice_blurb_about_what_anonrsync_is.h&gt;</p>

<p>As you may have noticed, our website is still pretty a mess.
 There are more detailed information about AnonCVS on the <a
 href="http://www.OpenBSD.org/anoncvs.html">Other BSD guys place</a>.</p>

<h3 id="cvs">AnonCVS servers</h3>

<p>Please see the list on the <a href="/?mirrors">Mirrors</a>
 page for all known anonCVS and anonRSYNC servers as well
 as their update period.</p>

<h3 id="rsync">How to AnonRSYNC</h3>

<p>At the moment, this information is in a state of flux. In the future,
 you will be able to use <tt>mirbsd.org</tt> as rsync or anoncvs mirror.
 Please bear with us.</p>

<p>Using <tt>mirbsd.org</tt> as anonRSYNC server:<br />
 The following command line could be used to mirror the entire
 CVS repository, or download area, respectively. Please do not make
 excessive use of the rsync command, since it imposes a lot of traffic.
<br />
 Please consider using a <a
 href="/MirOS/CVS/cvsrepo-20061004.cgz">recent (2006-10-04) snapshot</a>
 tarball (gzsig(1)d)
 of the CVS Repository (or for the old CVSROOT, the final snapshot from <a
 href="/MirOS/CVS/cvsroot-historic.cgz">2006-01-20</a>)
 as a base for rsync use in order to speed up the initial
 synchronisation and reduce load and traffic on the servers.
 These files are, of course, gzsig(1)d.</p>
<pre>nice rsync --delete -rxlztpgK --rsync-path=/bin/rsync \
  anoncvs@anoncvs.mirbsd.org:/cvs/ /var/anoncvs/anoncvs/cvs
nice rsync --delete -rxlztpgK --rsync-path=/bin/rsync \
  anoncvs@anoncvs2.mirbsd.org:/ocvs/ /var/anoncvs/anoncvs/ocvs
nice rsync --delete -rxlztpgK --rsync-path=/bin/rsync \
  anoncvs@anoncvs.mirbsd.org:/MirOS/ /var/www/htdocs/MirOS
</pre><p>
 Please be sure to check for problems (the CVS snapshot might contain
 lock files, because our way of mirroring isn't fully optimised yet),
 and not modify the command line (<code>-vP</code> should be
 not problematic; <code>-a</code> is not needed, and <code>-c</code>
 is too traffic and load intensive so its use is prohibited), especially
 do add a trailing slash on the server path and do not add one on the
 client path!<br />Let me repeat it: the <tt>mirbsd.org</tt>
 server used is just an example, look at the <a href="/?mirrors">list</a>.</p>
