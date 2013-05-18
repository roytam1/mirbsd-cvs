<?php
/* $MirOS: www/404.php,v 1.9 2006/01/19 01:23:57 tg Exp $ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
 *-
 * Show a fancy 404 page, and more info if user is admin.
 */

 $tg_noss="1";
 $tg_noie="1";
 require("vbegin.php");

	if (!empty($_SERVER["QUERY_STRING"])) {
		$rq = urldecode($_SERVER["QUERY_STRING"]);
	} else {
		$rq = "main";
	}
	$rq = mybase64($rq).".inc";
?>
 <title>404 - N&uuml;s jefonde!</title>
 <meta name="RCSId" content="$MirOS: www/404.php,v 1.9 2006/01/19 01:23:57 tg Exp $" />
 <meta name="robots" content="index, follow" />
 <style type="text/css"><!--
a.wmd {
	font:8pt/11pt verdana,sans-serif;
}
a.mir {
	font-family:Times,Times New Roman,serif;
	color:blue;
	text-decoration:none;
}
a.mir:hover {
	text-decoration:underline;
}
.wmds {
	font:8pt/11pt verdana,sans-serif;
}
.wmdb {
	font:13pt/15pt verdana,sans-serif;
}
a.wmd:link {
	color:red;
}
a.wmd:visited {
	color:#4e4e4e;
}
body {
	background-color:white;
	color:black;
}
 --></style>
</head><body>
<?php
 if (isadm()) {
?>
<h1>File Name Generation</h1>
<p>The file you requested:
 <tt><?php echo $_SERVER["QUERY_STRING"]; ?></tt> (still
 in urlencoded form) has the following filename:</p><pre>
<?php echo "www/content/".$rq; ?>
</pre>
<?php
 }
?>
<table width="400" cellpadding="3" cellspacing="5">
<tr style="height:40px;"><td valign="middle" align="left">
  <a class="wmd" href="http://mirbsd.de/"><img
  src="/pics/404-info.png" style="border:0px;" width="25" height="33"
  alt="[Info]" /></a>
 </td><td align="left" valign="middle" style="width:360px;">
  <h1 class="wmdb">These Weapons of Mass Destruction cannot be displayed</h1>
 </td>
</tr><tr><td colspan="2" class="wmds" style="width:400px;">The
  weapons you are looking for are currently unavailable. The country might
  be experiencing technical difficulties, or you may need to adjust your
  weapons inspectors mandate.
 </td>
</tr><tr><td colspan="2" class="wmds" style="width:400px;">
  <hr style="color:#C0C0C0; border-style:solid;" />
  <p>Please try the following:</p><ul>
   <li>Click the <a class="wmd"
    href="http://www.amazon.co.uk/exec/obidos/ASIN/B0000A08JQ/weaponsofmass-21"><img
    src="/pics/404-ref.png" alt="refresh.png (141 bytes)" width="13" height="16"
    style="vertical-align:middle; border:0px;" /></a> Regime change button,
    or try again later.<br /></li>
   <li>If you are George Bush and typed the country's name in the address bar,
    make sure that it is spelled correctly. (IRAQ).<br />
   </li>
   <li>To check your weapons inspector settings, click the <b>UN</b> menu, and
    then click <b>Weapons Inspector Options</b>. On the <b>Security Council</b>
    tab, click <b>Consensus</b>. The settings should match those provided by
    your government or NATO.
   </li>
   <li>If the Security Council has enabled it, The United States of America can
    examine your country and automatically discover Weapons of Mass
    Destruction.<br />If you would like to use the CIA to try and discover
    them,<br />click <a class="wmd"
    href="http://www.amazon.co.uk/exec/obidos/ASIN/074325239X/weaponsofmass-21"><img
    src="/pics/404-det.png" alt="Detect Settings" width="16" height="16"
    style="vertical-align:middle; border:0px;" /> Detect weapons</a>
   </li>
   <li>Some countries require 128 thousand troops to liberate them. Click the
    <b>Panic</b> menu and then click <b>About US foreign policy</b> to
    determine what regime they will install.
   </li>
   <li>If you are an Old European Country trying to protect your interests,
    make sure your options are left wide open as long as possible. Click the
    <b>Tools</b> menu, and then click on <b>League of Nations</b>. On the
    Advanced tab, scroll to the Head in the Sand section and check settings
    for your exports to Iraq.
   </li>
   <li>Click the <a class="wmd"
    href="http://www.amazon.co.uk/exec/obidos/ASIN/B000053W4Z/weaponsofmass-21"><img
    style="vertical-align:text-bottom; border:0px;" src="/pics/404-bomb.png"
    width="24" height="18" alt="*boom*" />Bomb</a> button if you are Donald
    Rumsfeld.</li>
  </ul>
  <p><br /></p>
  <h2 class="wmds">Cannot find weapons or CIA
   Error<br />Iraqi Explorer<br />
  <a class="wmd" href="http://www.coxar.pwp.blueyonder.co.uk/about.htm"
   style="font-size:x-small;">Get the WMD 404 T-shirt.</a></h2>
 </td>
</tr>
</table>
<hr style="height:3px;" /><p>
<a class="mir" href="http://validator.w3.org/check/referer">Valid
 XHTML/1.1!</a> - <a class="mir"
 href="http://jigsaw.w3.org/css-validator/validator?warning=1&amp;profile=none&amp;uri=<?php
	echo urlencode($tg_sur);	?>">Valid
 CSS!</a> - <small>Jokes aside, come to </small><a class="wmd" href="/">the
 MirOS site</a><small> if you want to know more.</small></p>
</body></html>
