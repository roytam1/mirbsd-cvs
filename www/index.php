<?php
/* $MirOS: www/index.php,v 1.15 2005/12/06 13:37:53 tg Exp $ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
 *-
 * This is the "master" CMS manager file. It streams content.
 */

	require("vfuncs.php");

	if (!empty($_SERVER["QUERY_STRING"])) {
		$qs = $_SERVER["QUERY_STRING"];
		$rq = urldecode($qs);
		$qs = "?".$qs;
	} else {
		$rq = "main";
		$qs = "";
	}
	$ridx="content/".mybase64($rq).".index";
	$rq = "content/".mybase64($rq).".inc";
	if (!is_readable($rq)) {
		if (!empty($_SERVER["HTTPS"])) {
			$proto="https";
		} else {
			$proto="http";
		}
		header("Status: 404 Content Not Found");
		header("Location: ".$proto."://".
		    $_SERVER['HTTP_HOST']."/404.php".$qs);
		exit;
	}
	if (!is_readable($ridx)) {
		$ridx="vindex.inc";
	}
	require("vbegin.php");
?>
 <title>MirOS/MirPorts: a wonderful operating system for a world of peace</title>
 <meta name="robots" content="index, follow" />
 <!--
	This is copyrighted material. For the full licence text, see the file
	LICENCE in the current directory. In no event may text from this page
	be simply copied into another work covered by an unfree (or otherwise
	mismatching) licence, such as the GNU Free Documentation License.
 -->
</head><body>
<div class="index">
 <ul class="lv1">
  <?php include($ridx); ?>
 </ul>
 <div style="margin-left:12px;margin-top:12px;margin-bottom:12px;">
  <script type="text/javascript"><!--
	google_ad_client = "pub-0266998858986985";
	google_ad_width = 160;
	google_ad_height = 600;
	google_ad_format = "160x600_as";
	google_ad_channel = "8915127517";
	google_color_border = "555555";
	google_color_bg = "000000";
	google_color_link = "995555";
	google_color_url = "FFAA00";
	google_color_text = "BBBBBB";
  //--></script>
  <script type="text/javascript"
   src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
  </script>
 </div>
 <form method="get" action="http://www.google.com/custom">
  <table style="margin-left:6px;margin-right:6px;">
   <tr><td valign="top" align="left" colspan="2">
    <input type="text" name="q" maxlength="255" value="" style="width:160px;" />
    <input type="hidden" name="client" value="pub-0266998858986985" />
    <input type="hidden" name="forid" value="1" />
    <input type="hidden" name="ie" value="UTF-8" />
    <input type="hidden" name="oe" value="UTF-8" />
    <input type="hidden" name="cof" value="GALT:#FFAA00;GL:1;DIV:#0033FF;VLC:FFAA00;AH:center;BGC:000000;LBGC:333333;ALC:FFFFFF;LC:FFFFFF;T:CCCCCC;GFNT:8888DD;GIMP:33FF33;LH:92;LW:98;L:http://www.66h.42h.de/pics/logosmw.png;S:http://mirbsd.org/;LP:1;FORID:1;" />
    <input type="hidden" name="safe" value="off" />
    <input type="hidden" name="num" value="100" />
   </td></tr>
   <tr><td valign="top" align="left"><a
    href="http://www.google.com/"><img style="border:0px;width:75px;"
    src="http://www.google.com/logos/Logo_25blk.gif" alt="Google" /></a>
   </td><td valign="middle" align="right">
    <input type="submit" name="sa" value="Search" style="width:80px;" />
   </td></tr>
  </table>
 </form>
</div>
<div class="content">
 <?php
	$cmsc = get_include_contents($rq);
	if ($cmsc === false) {
 ?>
		<p>Error during including CMS content file!</p>
 <?php
	} else {
		echo ereg_replace(
		    "([0-9A-z][-.,0-9A-z]*)\(([1-9])[/0-9A-Za-z]*\)",
		    "<a href=\"/man\\2/\\1.htm\">\\0</a>", ereg_replace(
		    "([0-9A-z][-.,0-9A-z]*)\((PAPERS|PSD|SMM|USD)\)",
		    "<a href=\"/cman/man\\2/\\1.htm\">\\0</a>", $cmsc));
	}
 ?>
</div>
<div class="heading">
 <img class="hdrlnks" src="pics/logosmw.png"
  alt="MirOS Logo" />
<pre class="hdrflf">     ___                                                  __
    -   ---___- ,,                  /\\,/\\,            ,-||-,     -_-/
       (' ||    ||                 /| || ||   '        ('|||  )   (_ /
      ((  ||    ||/\\  _-_         || || ||  \\ ,._-_ (( |||--)) (_ --_
     ((   ||    || || || \\        ||=|= ||  ||  ||   (( |||--))   --_ )
      (( //     || || ||/         ~|| || ||  ||  ||    ( / |  )   _/  ))
        -____-  \\ |/ \\,/         |, \\,\\, \\  \\,    -____-   (_-_-
                  _/              _-                    <a href="/LICENCE"><small>Website Licence</small></a></pre>
 <img class="hdrrhts" src="pics/quilt.png"
  alt="Collage with MirOS and MirPorts impressions" />
</div>
<?php include("vend.php"); ?>
