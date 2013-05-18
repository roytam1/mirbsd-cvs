<?php
/* $MirOS: www/index.php,v 1.16 2006/01/13 03:49:38 tg Exp $ */
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
