<small class="rcsid">$MirOS: www/content/cG9ydHM_.inc,v 1.17 2004/11/28 22:19:29 tg Exp $</small>
<h1>MirPorts: The MirOS Ports Framework</h1>

<h2>General</h2>

<h3>Index</h3><ol>
<li><a href="#about">About</a></li>
<li><a href="#install">Installing MirPorts</a></li>
<li><a href="#otheros">... on other OSes</a></li>
<li><a href="#using">Using MirPorts</a></li>
<li><a href="#diffopenbsd">Difference to OpenBSD ports</a></li>
<li><a href="#diffmirports">Difference to old MirPorts</a></li>
</ol>

<h3 id="about">About</h3>

<p>MirPorts is our solution for installing third-party software. The following
 platforms are supported:</p>
<ul>
 <li>MirOS (both -stable and -current)</li>
 <li>OpenBSD 3.4, 3.5 and 3.6 (last formal release)</li>
</ul>

<p>MirPorts is a derivative from the <a
 href="http://www.openbsd.org/ports.html">OpenBSD ports tree</a>. The OpenBSD
 sources are imported and merged regularly.</p>

<p>Many ports which have been removed from the OpenBSD tree for political
 reasons have been kept in MirPorts. Among these are DJB software (djbdns,
 daemontools, ucspi-tcp), jdk and ast-ksh (broken).</p>

<p>MirPorts shall also be a <strong>platform for rejected or "unofficial"
 ports</strong> (such as cups, sane, transcode or proftpd). Thus, it can
 be regarded as an alternative
 or a supplement to OpenBSD's ports tree. If you have a port that has not been
 committed in OpenBSD, feel free to contact the MirOS developers.</p>

<p><strong>We are looking</strong> for people wanting to ensure quality
 of MirPorts under MirOS and OpenBSD. If you are interested, have at least
 one year experience with the OpenBSD Ports Tree, and are not scared of
 <tt>bsd.port.mk</tt>; please contact us.</p>

<h2>Getting started</h2>

<h3 id="install">Installing MirPorts</h3>

<p><strong>ATTENTION:</strong> This information is out of date!<br />
 Current installation: check out to any directory, cd there and run
 <tt>make setup SUDO=sudo</tt> with appropriate permissions.</p>

<p>For a list of <strong>caveats</strong> for upgraders, see <a
 href="#caveats">below</a>.</p>

<p>On June 15th, 2004 MirPorts have gone through a flag day. If you
 are using a MirOS system older than June 15th, you must upgrade:
 users of #7-stable can upgrade MirPorts from CVS or using the
 &quot;ports34.tgz&quot; or &quot;ports7.ngz&quot; distribution sets
 made public, but have to patch their system (some of the patches have
 gone into CVS after #7quater has been released). Users of older -current
 snapshots will have to update their base installation or hack the *.mk
 files themselfes.</p>
<p>The sets are upgradable; all other users have to do a
 fresh checkout. You retrieve MirPorts either via anonCVS, or get a
 copy of the MirOS repository via anonRSYNC and check out via local
 CVS.</p>

<p>The MirPorts Framework is contained in the <tt>ports</tt> module
 within the MirOS repository. Usually, this module is checked out from
 within <tt>/usr</tt>, so that MirPorts lives within <tt>/usr/ports</tt>.
 On OpenBSD, it is common to put MirPorts into <tt>/usr/mirports</tt> if
 you want to use both, or into <tt>/usr/ports</tt> if you want to use
 only MirPorts.<br />
 It is recommended that this directory belong to a normal
 user, and installation is only done via sudo(8).</p>
 
<p>An example of a MirPorts installation without <tt>ports34.tgz</tt>
 ("user" is a user account you normally work on):</p>

<pre># cd /usr
# mkdir ports
# chown user:user ports
 (the next steps are done as regular user)
$ cd /usr
$ export CVS_RSH=ssh <em>(csh: setenv CVS_RSH ssh)</em>
$ cvs -d mirbsd-cvs@mirbsd.bsdadvocacy.org:/ocvs -qz3 checkout -PA ports
 <em>(the password is "</em>anoncvs<em>")</em></pre>

<p>If you need to move framework to a different directory, make sure
 first that there are no working directories (w-PKGNAME) left, then
 move the <tt>/usr/ports</tt> directory and add a line like<br />
 <tt>PORTSDIR=/path/to/mirports</tt><br />
 to your /etc/mk.conf file.</p>

<h3 id="otheros">Other Operating Systems</h3>

<p>If you do <em>not</em> use MirOS-current, you will have to prepare
 your operating system for MirPorts. Check out MirPorts (usually you
 want to do that from CVS) and read the information at
 <tt>ports/infrastructure/compat/XXX/README</tt>, where <tt>XXX</tt>
 is the name of your operating system in lowercase.</p>

<p>If you use OpenBSD, you have three options:</p>

<ul><li>You use OpenBSD ports and only want a few programs from MirPorts. Check
 out MirPorts into an arbitrary directory (not /usr/ports) and keep using the
 infrastructure from OpenBSD. This might work, but beware of changes and
 incompatibilities (see below), which you will have to resolve yourself.<br />
 In fact, recently most autoconf'd ports &quot;need&quot; MirLibtool and will
 not work with the OpenBSD Ports Tree, which itself was modified in a totally
 different way.</li>
<li>You want use only MirPorts. Delete the contents of /usr/ports and check
 out MirPorts there. Before using it, install the MirOS package tools and
 sysmake files from <tt>mpsup</tt>, as said above. Be sure to also run
 <tt>ports/infrastructure/stools/scan/pkg_scan.sh</tt> and
 <tt>ports/infrastructure/etc/mkuserdb</tt> as root before using MirPorts.</li>
<li>Use the new install shell script, so you have the MirPorts Framework
 in e.g. <tt>/usr/mirports</tt> and the OpenBSD Ports Tree in
 <tt>/usr/ports</tt> and can use both at the same time.</li>
</ul>

<h3 id="using">Using MirPorts</h3>

<p>Usage is very straightforward. The following steps should help you
 successfully install your first port:</p>

<ol>
 <li>Install MirPorts as described above.</li>
 <li>Go to the <tt>/usr/ports</tt> directory.</li>
 <li>To search for a specific port, enter <tt>make search key=foo</tt>
  (replace "foo" by your keyword).</li>
 <li>The ports are organized in categories (subdirectories). Every port
  resides in its own directory. Change to the directory of the port you would
  like to install (e.g. <tt>misc/screen</tt>).</li>
 <li>Some ports have flavours, for example if you want to use arts or esd
  instead of or parallel to native sunaudio, or whether you want to have
  support for Berkeley DB version 4, or build some X11 frontend. Run the
  <tt>make show=FLAVORS</tt> (no U in flavour here due to some braindeadness
  in the country where the mere idea of a ports framework arose) command
  in order to learn about possible flavours.</li>
 <li>Run <tt>make install</tt> in this directory. This will download the
  source code of the program, build it, create a binary package and install
  it. If you want to use flavours, add them to the <em>environment</em>
  (NOT make) variable FLAVOR, separated by spaces.</li>
 <li>You might want to issue <tt>make clean</tt> afterwards. If you want to
  remove an already installed port, either use <tt>make uninstall</tt> (if
  you have not upgraded MirPorts since), or look at the real package name
  (the first column of <tt>pkg_info -L</tt> output) and give that as parameter
  to the <tt>pkg_delete</tt> command.</li>
</ol>

<h1 id="caveats">Caveats</h1>

<h2 id="diffmirports">Differences to older MirPorts versions</h2><ul>

<li>MODGNU_CONFIG_GUESS_DIRS was called MODGNU_TWIDDLE_DIRS in MirPorts
 for some time, and is back to MODGNU_CONFIG_GUESS_DIRS now.</li>
<li>"make install" install all subpackages by default. If you want to
 turn off this behaviour, set <tt>PREFER_SUBPKG_INSTALL=no</tt> in
 <tt>/etc/mk.conf</tt>.</li>
<li>You must patch your system makefile includes (/usr/share/mk/sys.mk)
 and copy over some. You also must copy an OSDEP makefile include to
 PORTSDIR/infrastructure/mk/mirports.osdep.mk if you use MirOS #7-stable
 or OpenBSD/ekkoBSD. For more details, see above.</li>

</ul>

<h2 id="diffopenbsd">Differences to OpenBSD ports</h2>

<p>This list is incomplete.</p>

<ul><li>For autoconf, we use the AUTOCONF_NEW switch, whereas OpenBSD uses
 AUTOCONF_VERSION. AUTOCONF_NEW=Yes means version 2.59.</li>
<li>CONFIGURE_STYLE=autoconf activates MirLibtool; you can control this
 via MODGNU_MIRLIBTOOL={yes|no}.</li>
<li>There is a new CONFIGURE_STYLE=autogen.</li>
<li>databases/db/v3 and databases/db/v4 are gone. We only have db4 in
 databases/db.</li>
<li>The Ghostscript fonts port is called print/ghostscript/fonts-std (there is
 also a fonts-cjk source package, but no port for it)</li>
<!-- TODO: MirLibtool blurb etc. -->
</ul>
