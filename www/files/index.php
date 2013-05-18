<?php
/* $MirOS: www/files/index.php,v 1.7 2008/05/03 02:05:26 tg Exp $ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
 *-
 * This is the "master" CMS manager file. It streams content.
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

 // Declare global variables
 unset($tg_svr);
 unset($tg_bws);
 unset($tg_pts);
 unset($tg_sur);
 unset($tg_pfad);
 unset($tg_pflv);
 unset($tg_htt0);
 unset($tg_htt1);
 unset($tg_htlv);
 unset($tg_realm);

 // get server environment
 $tg_svr = strtolower($_SERVER["HTTP_HOST"]);
 if (strpos($tg_svr, ":")) {
	$tg_svp = substr($tg_svr, strpos($tg_svr, ":") + 1);
	$tg_svr = substr($tg_svr, 0, strpos($tg_svr, ":"));
 } else	$tg_svp = "80";
 $tg_bws = $_SERVER["HTTP_USER_AGENT"];
 $tg_pts = $_SERVER["REQUEST_URI"];
 if (!empty($_SERVER["SCRIPT_URI"])) {
	$tg_sur = $_SERVER["SCRIPT_URI"];
 } else {
	$tg_sur = "http://" . $tg_svr . $tg_pts;
 }

 // Try to find out the offset to this file per server
 $i = substr_count($tg_pts, "/");
 $sl = $i ? $i - 1 : 0;
 $tg_ist = 2;

 // get local variables:
 //  $sl = number of subdirectory layers			(default: 0 [DEL:1])
 //  $ht = HTML type (0=transitional 1=strict 2=XHTML/1.1)	(default: 2)

 if (!isset($sl)) { $sl = "0"; }
 if (!isset($ht)) { $ht = "2"; }

 // Generate possible subdirectory layers
 if ($sl == "0") {
	$tg_pfad = "";
	$tg_pflv = 0;
 } else if ($sl == "1") {
	$tg_pfad = "../";
	$tg_pflv = 1;
 } else if ($sl == "2") {
	$tg_pfad = "../../";
	$tg_pflv = 2;
 } else if ($sl == "3") {
	$tg_pfad = "../../../";
	$tg_pflv = 3;
 } else if ($sl == "4") {
	$tg_pfad = "../../../../";
	$tg_pflv = 4;
 } else if ($sl == "5") {
	$tg_pfad = "../../../../../";
	$tg_pflv = 5;
 } else if ($sl == "6") {
	$tg_pfad = "../../../../../../";
	$tg_pflv = 6;
 } else if ($sl == "7") {
	$tg_pfad = "../../../../../../../";
	$tg_pflv = 7;
 } else if ($sl == "8") {
	$tg_pfad = "../../../../../../../../";
	$tg_pflv = 8;
 } else {
	header("Content-type: text/plain");
	echo "Script error: subdirectory layers!\r\n";
	exit;
 }

 unset($tg_noie);
 $tg_realm = 2;

 // Fill in HTML flavour dependant variables
 if ($ht == "0") {
	$tg_htt0 = "XHTML 1.0 Transitional";
	$tg_htt1 = "xhtml1/DTD/xhtml1-transitional";
	$tg_htlv = 0;
 } else if ($ht == "1") {
	$tg_htt0 = "XHTML 1.0 Strict";
	$tg_htt1 = "xhtml1/DTD/xhtml1-strict";
	$tg_htlv = 1;
 } else if ($ht == "2") {
	$tg_htt0 = "XHTML 1.1";
	$tg_htt1 = "xhtml11/DTD/xhtml11";
	$tg_htlv = 2;
 } else {
	header("Content-type: text/plain");
	echo "Script error: HTML subtype!\r\n";
	exit;
 }

 // Unset locals
 unset($i);
 unset($sl);
 unset($ht);
 unset($tmp);

 // Marker that this script has been executed
 $tg_init = "v11";

 // Send HTTP headers our way
 header("Content-type: text/html; charset=utf-8");
 // XXX? header("Pragma: no-cache");

 // Send HTML headers our way
 echo "<?xml version=\"1.0\"?>\r\n";
?><!DOCTYPE html PUBLIC "-//W3C//DTD <?php echo "${tg_htt0}"; ?>//EN"
 "http://www.w3.org/TR/<?php echo "${tg_htt1}"; ?>.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"<?php
	if ($tg_htlv < 2) echo ' lang="en"';	?>><head>
 <meta name="MSSmartTagsPreventParsing" content="TRUE" />
 <link rel="stylesheet" type="text/css" href="vstyle.css" />
 <meta name="author" content="Thorsten Glaser" />
 <meta name="copyright" content="All rights reserved. Redistribution except for scientific and educational uses strictly prohibited." />
 <meta name="owner" content="The MirOS Project and The MirPorts Framework" />
 <meta name="licence" content="see the source files in CVSWEB for details" />
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
	<li><a href="/wlog-9.htm">Weblog</a> for #9</li>
	<li><a href="/?older">Old News</a> &amp; Log</li>
  </ul></li>
  <li><a href="/?about">About</a></li>
<!-- these are not in a usable state
  <li><a href="/?docs">Documentation</a></li>
  <li><a href="/?faq">FAQ</a></li>
-->
  <li class="spacer"><a href="/getting.htm">Download</a><!-- <ul class="lv2">
	<li><a href="/?mirrors">Mirrors</a></li>
  </ul>--></li>
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
 <img class="hdrlnks" src="pics/logo-grey.png"
  alt="MirOS Logo" />
</div>
<div class="footer">
&bull; <a href="http://mirbsd.de/impressum">Impressum</a> &bull;
<a href="http://validator.w3.org/check/referer">Valid <?php
	echo substr_replace($tg_htt0, "/", strpos($tg_htt0, " "), 1)."!</a>\n";
?> - <a href="http://jigsaw.w3.org/css-validator/validator?warning=1&amp;profile=none&amp;uri=<?php
	echo urlencode($tg_sur);	?>">Valid CSS!</a><?php
?> - <small><a href="mailto:miros-discuss@66h.42h.de">eMail</a>
 contact to</small> the MirOS Project</div>
</body></html>
