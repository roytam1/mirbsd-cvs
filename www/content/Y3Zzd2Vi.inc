<small class="rcsid">$MirBSD: www/content/Y3Zzd2Vi.inc,v 1.14 2004/11/12 17:54:21 tg Exp $</small>
<p class="admin">ATTN: Candidate for moving into MirWiki!</p>
<h1>Accessing the MirOS source by CVSweb</h1>

<h3>Short introduction into CVSweb</h3>
<p>CVSweb is a front-end for the CVS and RCS utilities, which allows
 for easy read-only access to a CVS repository tree by means of any
 web browser. You can browse directories, retrieve content and log
 messages of any files, even deleted ones; skim through the history
 and read diffs between different revisions of files.</p>
<p>If you would like to know more about CVSweb, the best thing is
 probably to learn about CVS yourself, and use Google for more
 information on CVSweb. Feel free to contact the MirOS developers
 if you have got additional questions.</p>

<h3>Accessing CVSweb</h3>

<p>If you are using a CVSweb-enabled mirror (such as 
 <a href="http://mirbsd.bsdadvocacy.org/">mirbsd.bsdadvocacy.org</a>,
 <a href="https://mirbsd.mirsolutions.de:445/">mirbsd.mirsolutions.de</a>
 or <a href="http://mirbsd.agentdero.com/">mirbsd.agentdero.com</a>, 
 click <a href="/cvs.cgi/">here to access CVSWeb</a>)<br/>
 If you are currently on a different mirror of the MirOS
 Project homepage, feel free to directly <a
 href="https://MirBSD.BSDadvocacy.org:8890/cvs.cgi/">jump into
 the MirOS CVSweb</a> utility service at <a
 href="https://mirbsd.mirsolutions.de:445/cvs.cgi/">various</a> <a
 href="http://mirbsd.agentdero.com/cvs.cgi/">mirrors</a>.</p>

<h3>Tags</h3><ul>
<li>HEAD - contains current MirOS development code</li>
<li>cvs-yymmddhhmm (no branch tag) - contains imported code</li>
<li>ctm-nnnn (no branch tag) - contains imported code</li>
<li>MIRBSD_7 - contains MirOS #7-stable branch</li>
<li>MIRBSD_7quater (no branch tag) - the latest release</li>
<li>MIRBSD_7ter (no branch tag) - the previous release</li>
<li>MIRBSD_5 (no branch tag) - an older release</li>
</ul>

<h1>Stuff not available via the CVSweb interface</h1>
<h3>ChangeLog files</h3>
<p>If you would like to read the ChangeLog files, the first
 ten about 10 Mebibytes in size, the others about 2 MiB,
 please use <a href="/clogs/">this directory</a>.</p>

<h3>Tarballs of CVS subtrees</h3>
<p>In contrast to other operating systems' CVSweb, we cannot
 currently provide tarballs. Usage of anonCVS (if working) or
 anonRSYNC is recommended.</p>
