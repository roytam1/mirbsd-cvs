<small class="rcsid">$MirBSD: www/content/YW5vbmN2cw__.inc,v 1.31 2005/01/23 12:06:15 tg Exp $</small>
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

<p>We've got a private rsync server now, <tt>thor.66h.42h.de</tt>,
 from which the various public mirrors sync. For a list of these,
 again, please refer to the <a href="/?mirrors">Mirrors</a> page.</p>

<p>Using <tt>mirbsd.bsdadvocacy.org</tt> as anonRSYNC server:<br />
 The following command line could be used to mirror the entire
 CVS repository, or download area, respectively. Please do not make
 excessive use of the rsync command, since it imposes a lot of traffic.
<br />
 Please consider using a <a
 href="/MirOS/CVS/cvsroot-20050123.cgz">recent (2005-01-23) snapshot</a>
 tarball (<a href="/MirOS/CVS/cvsroot-20050123.cgz.asc">PGP signature</a>)
 of the CVS repository as a base for rsync use.</p>
<pre><!-- nice /usr/local/bin/rsync -\
-delete -rxlztpg \
  -\
-rsync-path=/usr/bin/rsync \
  mirbsd-cvs@mirbsd.bsdadvocacy.org:/cvs/ /var/anoncvs/anoncvs/cvs -->
nice /usr/local/bin/rsync --delete -rxlztpg \
  --rsync-path=/usr/bin/rsync \
  mirbsd-cvs@mirbsd.bsdadvocacy.org:/ocvs/ /var/anoncvs/anoncvs/ocvs
nice /usr/local/bin/rsync --delete -rxlztpg \
  --rsync-path=/usr/bin/rsync \
  mirbsd-cvs@mirbsd.bsdadvocacy.org:/MirOS/ /var/www/htdocs/MirOS
</pre><p>
 Please be sure to check for problems (the CVS snapshot might contain
 lock files, because our way of mirroring isn't fully optimized yet),
 and not modify the command line (<code>-v --progress</code> should be
 not problematic; <code>-a</code> is not needed, and <code>-c</code>
 is too traffic and load intensive so its use is prohibited), especially
 do add a trailing slash on the server path and do not add one on the
 client path!<br />Let me repeat it: the <tt>mirbsd.bsdadvocacy.org</tt>
 server used is just an example, look at the <a href="/?mirrors">list</a>.</p>

<p>For a peek into &quot;ncvs&quot; you can sync with the command</p>
<pre>nice /usr/local/bin/rsync --delete -rxlztpg \
  --rsync-path=/usr/bin/rsync \
  _anoncvs@mirsolutions.de:/ncvs/ /var/anoncvs/anoncvs/cvs</pre>
<p>(with key only) and get the CVS repository seed file from <a
 href="/MirOS/CVS/cvsrepo-20050123.cgz">2005-01-23</a> (<a
 href="/MirOS/CVS/cvsrepo-20050123.cgz.asc">PGP signature</a>) for a
 quicker initial rsync.</p>
