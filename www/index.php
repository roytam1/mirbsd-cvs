<?php
/* $MirOS: www/index.php,v 1.19 2006/06/09 20:31:14 tg Exp $ */
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
		$rq = "fornow";
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
</div>
<div class="content">
 <div style="border:4px ridge red; margin:0px 24px 0px 24px; padding:12px;">
  <h1>Important message</h1>
  <p>This website is currently under reconstruction. The information
   you find here is probably out of date and not maintained any more
   in favour of the new website. If you want to volunteer helping us
   to set up the new website (same design, KISS content), mail Benny
   at bsiegert@mirbsd.de, thanks.</p>
  <p>Continue at your own risk&#8230;</p>
 </div>
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
