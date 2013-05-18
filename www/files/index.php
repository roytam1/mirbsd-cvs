<?php
/* $MirOS: www/files/index.php,v 1.9 2008/05/03 02:20:26 tg Exp $ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
 */

/*
 * base64 encoding, file system safe
 * used for locating of arguments
 */
function mybase64($arg)
{
	$tmp1 = base64_encode($arg);
	$balt = array("+", "=", "/");
	$bneu = array(".", "_", "-");
	$tmp2 = str_replace($balt, $bneu, $tmp1);
	return $tmp2;
}

/*
 * From the PHP Website:
 * Parse include statement but return its output
 * instead of sending it to the client (false on error)
 */
function get_include_contents($filename) {
	if (is_file($filename)) {
		ob_start();
		include $filename;
		$contents = ob_get_contents();
		ob_end_clean();
		return $contents;
	}
	return false;
}

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
	if (!$flag) {
		$rq = "content/".mybase64($rq).".inc";
		if (!is_readable($rq)) {
			$flag = true;
			$rq = "main";
		}
	}
	if ($flag) {
		if (!empty($_SERVER["HTTPS"]))
			$svr = "https";
		else
			$svr = "http";
		$svr .= "://" . $_SERVER['HTTP_HOST'];
		$fn = $svr . "/main.htm";
		if (is_readable($rq . ".htm"))
			$fn = $svr . "/" . $rq . ".htm";
		else {
			$rq = "content/".mybase64($rq).".inc";
			if (is_readable($rq))
				$fn = false;
		}
		if ($fn !== false) {
			header("Status: 301 Moved Permanently", true, 301);
			header("Location: " . $fn, true);
			echo "Please go to " . $fn . " instead!";
			exit;
		}
	}
	/* --- end www3 hooks --- */

 // Send HTTP headers our way
 header("Content-type: text/html; charset=utf-8");

 // Send HTML headers our way
 echo "<?xml version=\"1.0\"?>\r\n";
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
 "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"><head>
 <meta http-equiv="content-type" content="text/html; charset=utf-8" />
 <meta name="MSSmartTagsPreventParsing" content="TRUE" />
 <link rel="stylesheet" type="text/css" href="vstyle.css" />
 <meta name="author" content="Thorsten Glaser" />
 <meta name="copyright" content="All rights reserved. Redistribution except for scientific and educational uses strictly prohibited." />
 <meta name="owner" content="The MirOS Project and The MirPorts Framework" />
 <meta name="licence" content="see the source files in CVSWEB for details" />
 <!-- $MirOS: www/mk/tmpl.pre,v 1.14 2008/03/14 21:13:09 tg Exp $ -->
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
  <li><a href="/main.htm">Main</a><ul class="lv2">
	<li><a href="/wlog-10.htm">Weblog</a> for #10</li>
	<li><a href="/oldnews.htm">Old News</a> &amp; WLog</li>
  </ul></li>
  <li><a href="/?about">About</a></li>
<!-- these are not in a usable state
  <li><a href="/?docs">Documentation</a></li>
  <li><a href="/?faq">FAQ</a></li>
-->
  <li class="spacer"><a href="/getting.htm">Download</a></li>
  <li><a href="/irc.htm">IRC</a></li>
  <li><a href="/projects.htm">Project Ideas</a></li>
  <li><a href="/danke.htm">Donate</a></li>
  <li>Manpages<ul class="lv2">
    <li><a href="/htman/i386/">i386</a></li>
    <li><a href="/htman/sparc/">sparc</a></li>
  </ul></li>
  <li><a href="/ports.htm">MirPorts</a> Framework</li>
  <li>Subprojects<ul class="lv2">
	<li><a href="/jupp.htm">jupp</a> Editor</li>
	<li><a href="/mksh.htm">mksh</a> Shell</li>
  </ul></li>
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
 <a href="main.htm"><img class="hdrlnks"
  src="pics/logo-grey.png" alt="MirOS Logo" /></a>
</div>
<div class="footer"><p>• <a
 href="http://mirbsd.de/impressum">Impressum</a> • <a
 href="http://validator.w3.org/check/referer">Valid HTML!</a> • <a
 href="mailto:miros-discuss@66h.42h.de">E-Mail</a> contact to the
 MirOS Project •</p>
<p class="rcsdiv">Generated using the old, abandoned CMS</p>
</div>
</body></html>
