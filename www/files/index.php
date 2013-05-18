<?php
/* $MirOS: www/files/index.php,v 1.2 2007/10/02 18:55:00 tg Exp $ */
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
	/* --- begin www3 hooks --- */
	$i = 0;
	$flag = false;	/* don't accept zero-length strings */
	while ($i < strlen($rq)) {
		$c = ord($rq[$i]);
		$i++;
		if (($c == 0x2D) || ($c == 0x5F) ||
		    (($c >= 0x30) && ($c <= 0x39)) ||
		    (($c >= 0x41) && ($c <= 0x5A)) ||
		    (($c >= 0x61) && ($c <= 0x7A))) {
			$flag = true;
			continue;
		}
		$flag = false;
		break;
	}
	if ($flag) {
		$fhtm = is_readable($rq . ".htm");
		$fphp = is_readable($rq . ".php");
		if (!empty($_SERVER["HTTPS"]))
			$svr = "https";
		else
			$svr = "http";
		$svr .= "://" . $_SERVER['HTTP_HOST'];
		if ($fphp)
			$fn = $svr . "/" . $rq . ".php";
		else if ($fhtm)
			$fn = $svr . "/" . $rq . ".htm";
		else
			$fn = false;
		if ($fn !== false) {
			header("Status: 301 Moved Permanently", true, 301);
			header("Location: " . $fn, true);
			echo "Please go to " . $fn . " instead!";
			exit;
		}
	}
	/* --- end www3 hooks --- */
	if (is_readable("content/".mybase64($rq).".override")) {
		header('Content-Type: text/html');
		$fn = file_get_contents("content/".mybase64($rq).".override");
		readfile(rtrim($fn));
		exit;
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
		    "<a href=\"/htman/i386/man\\2/\\1.htm\">\\0</a>", ereg_replace(
		    "([0-9A-z][-.,0-9A-z]*)\((DOCS|PAPERS|PSD|SMM|USD)\)",
		    "<a href=\"/htman/i386/man\\2/\\1.htm\">\\0</a>", $cmsc));
	}
 ?>
</div>
<div class="heading">
 <img class="hdrlnks" src="pics/logo-grey.png"
  alt="MirOS Logo" />
</div>
<?php include("vend.php"); ?>
