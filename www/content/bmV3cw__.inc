<small class="rcsid">$MirOS: www/content/bmV3cw__.inc,v 1.34 2005/11/16 22:30:09 tg Exp $</small>

<h1>Current MirOS News</h1><ul>

<li>17.11.2005<br />Work on LKMs has been done to the extent that they can
	be used again. make(1) now knows the <tt>.trace</tt> operation. In
	MirPorts you can now specify CVS server, tag/date and module paths
	as a &quot;pseudo distfile&quot; instead of rolling your own; they
	will still be checksummed. The pkgtools port has been converted to
	use this new mechanism; we'll see if it creates trouble.</li>

<li>16.11.2005<br />The new MirPorts installer both works on all supported
	platforms now and has got a manual page. Several ports were fixed,
	updated and tested on some of the platforms; the infrastructure is
	further improved as well. Some helpers used during the build got a
	polish. Some annoying DEBUGLIBS and DEBUGPROGS bugs were fixed and
	the kernel and bootloader now work properly too. The long-standing
	timekeeping issues are all solved, the GNU mktime testsuite works.
	Some documentation has been updated. Work on I18N has continued as
	well as some more merging of OpenBSD. Lynx has been updated, and a
	bunch of OpenBSD ksh patches flew in. upkg, the MirOS setup manual
	page, and some other "old stuff" was touched again. Almost all our
	portable tools have had at least one new release.</li>

<li>03.10.2005<br />After about 2&frac12; years, our first mirror (in USA)
	goes offline. Thanks to bsdadvocacy.org for hosting us so long, at
	the very beginning even though the OpenBSD team disapproved.<br />
	Also, the etherkiller.de mirror disappeared, and the tamu.edu was,
	IIRC, taken offline some time ago. This means, at the moment there
	is only one, central, place to retrieve MirOS BSD (in Germany): <a
	href="https://mirbsd.mirsolutions.de:445/">mirbsd.mirsolutions.de</a><br />
	There has been some further work ongoing related to both the ports
	stuff (infrastructure fixes and port updates) and libc (it builds,
	but this is only a small step towards both I18N and unbreaking the
	current CVS HEAD).</li>

</ul>
<p>For older news, please refer to the <a href="/?older">historical news
 page</a>, or the developers' weblog.</p>
