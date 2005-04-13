<?php
/* $MirOS: www/index.php,v 1.6 2005/03/15 22:55:19 tg Exp $ */
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
	google_ad_channel ="";
	google_color_border = "555555";
	google_color_bg = "000000";
	google_color_link = "CC7777";
	google_color_url = "FFAA00";
	google_color_text = "BBBBBB";
  //--></script>
  <script type="text/javascript"
   src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
  </script>
 </div>
</div>
<div class="content">
 <?php
	include($rq);
 ?>
</div>
<div class="heading">
 <?php include("vhead.inc"); ?>
</div>
<?php include("vend.php"); ?>
