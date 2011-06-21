<?php
	/* stupid short_open_tag *curse* idiot defaults */
	echo '<' . '?xml version="1.0"?' . ">\r\n";
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
 "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"><head>
 <meta http-equiv="content-type" content="text/html; charset=utf-8" />
 <title>Website Visitor Counter script by Thorsten Glaser</title>
</head><body><?php
/*-
 * $MirOS: contrib/hosted/tg/historic/ctr.php,v 1.3 2010/11/10 16:14:56 tg Exp $
 *-
 * Copyright © 2006, 2010, 2011
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 *-
 * Use this as follows (probably better with CDATA, but what the hey):
 *	<script type="text/javascript" language="JavaScript"><!--
 *		var debug = 0;	// auf 1 setzen zum Debuggen
 *		document.write('<iframe height="70" width="120" align="center" scrolling="no" marginheight="0" marginwidth="0" src="http://{server}/ctr.php?debug=' + debug + '&amp;id=' + escape(document.location) + ' frameborder="0" />');
 *	//--></script>
 */

/* the following function taken from the MirBSD homepage */
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
 * We call this to abort sanely.
 */
function s_die($message)
{
	global $odata;

	echo "\n<h1>Fatal script error</h1>\n";
	echo "<p>Execution of the counter script aborted due to the\n";
	echo " following error:\n";
	echo " <span style=\"color:red;\">" . $message . "</span></p>\n";
	if ($odata)
		echo "<hr />\n" . $odata . "\n";
	echo "</body></html>\n";
	exit(1);
}

/*
 * Setup: get docroot/../files/<our stuff> as path prefix,
 * "id" passed by user, and "debug" flag. Sanitise "id".
 */
flush(); /* so that the above is sent */
$docroot = $_SERVER["DOCUMENT_ROOT"];
$arg_id = $_REQUEST["id"];
$arg_debug = $_REQUEST["debug"];
/* trim HTML anchor if present */
$hofs = strpos($arg_id, "#");
if ($hofs !== false)
	$arg_id = substr($arg_id, 0, $hofs);
$hofs = strpos($arg_id, "?");
if ($hofs !== false)
	$arg_id = substr($arg_id, 0, $hofs);
$hofs = strpos($arg_id, " ");
if ($hofs !== false)
	$arg_id = substr($arg_id, 0, $hofs);
$hofs = strpos($arg_id, "	");
if ($hofs !== false)
	$arg_id = substr($arg_id, 0, $hofs);
if (strlen($arg_id) < 1)
	s_die("Argument 'id' not passed!");

$pathpfx = dirname($docroot) . "/files/ctr_stuff/";
if (isset($arg_debug) && ($arg_debug != "0"))
	$debug = true;
else
	$debug = false;
$our_id = $pathpfx . mybase64($arg_id) . ".ctr";
global $odata;
$odata = false;

$my_today = (int)gmdate('Ymd');

if ($debug) {
	echo "\n<p>We've arrived at a sane state.</p><ul>\n";
	echo " <li>docroot: " . htmlentities($docroot) . "</li>\n";
	echo " <li>arg_id: " . htmlentities($arg_id) . "</li>\n";
	echo " <li>arg_debug: " . htmlentities($arg_debug) . "</li>\n";
	echo " <li>pathpfx: " . htmlentities($pathpfx) . "</li>\n";
	echo " <li>our_id: " . htmlentities($our_id) . "</li>\n";
	echo " <li>current time: " . $my_today . " " .
	    gmdate('H:i:s') . " UTC</li>\n";
	echo "</ul>";
	flush();
}

/*
 * The following code is the real trick:
 * - open the file ($our_id)
 * - acquire exclusive advisory lock on the file
 *   THIS MAY BLOCK, so keep the following code path as small as possible!
 * - read the file into four variables:
 *   + count_today
 *   + count_yday
 *   + count_rest
 *   + stamp_today
 * - check if stamp_today is today, if not:
 *   + count_rest += count_yday
 *   + count_yday = count_today
 *   + count_today = 0
 *   + stamp_today = <today>
 * - increment count_today
 * - write back the file
 * - release the lock (KEEP THE CODE PATH TILL HERE SMALL!)
 *
 * Then we'd ideally format the output. But it's useful
 * to already have output when aborting...
 */

if (file_exists($our_id)) {
	if (($fh = fopen($our_id, "rb+")) == false)
		s_die("Could not open ID file (" .
		    htmlentities(mybase64($arg_id)) . ")!");
} else {
	if (($fh = fopen($our_id, "wb+")) == false)
		s_die("Could not create ID file (" .
		    htmlentities(mybase64($arg_id)) . ")!");
}
if (!flock($fh, LOCK_EX))
	s_die("Could not lock ID file (".
	    htmlentities(mybase64($arg_id)) . ")!");
$count_today = 0;
$count_yday = 0;
$count_rest = 0;
$stamp_today = 0;
if (($idata = fgetcsv($fh, 1024, ':')) != false) {
	if (isset($idata[0])) {
		$count_today = (int)$idata[0];
		if ($count_today < 0)
			$count_today = 0;
	}
	if (isset($idata[1])) {
		$count_yday = (int)$idata[1];
		if ($count_yday < 0)
			$count_yday = 0;
	}
	if (isset($idata[2])) {
		$count_rest = (int)$idata[2];
		if ($count_rest < 0)
			$count_rest = 0;
	}
	if (isset($idata[3])) {
		$stamp_today = (int)$idata[3];
		if ($stamp_today < 20061222 || $stamp_today > 20371231)
			$stamp_today = 0;
	}
}

if ($stamp_today < $my_today) {
	$count_rest += $count_yday;
	$count_yday = $count_today;
	$count_today = 0;
}
$stamp_today = $my_today;
$count_today++;

$count_everything = $count_rest + $count_yday + $count_today;
/* +++ begin +++ format the output +++ */
$odata = "<table style=\"font-size:x-small;\">
 <tr>
  <th colspan=\"2\">Seitenbesucher</th>
 </tr><tr>
  <td>Gestern</td>
  <td align=\"right\">${count_yday}
 </tr><tr>
  <td>Heute</td>
  <td align=\"right\">${count_today}
 </tr><tr>
  <td>Gesamt</td>
  <td align=\"right\">${count_everything}</td>
 </tr>
</table>";
/* +++ end +++ format the output +++ */

if (!rewind($fh)) {
	if (!flock($fh, LOCK_UN))
		s_die("Couldn't unlock file on error handler" .
		    " trying to abort on failure to rewind!");
	s_die("Couldn't rewind the file!");
}
if (!ftruncate($fh, 0)) {
	if (!flock($fh, LOCK_UN))
		s_die("Couldn't unlock file on error handler" .
		    " trying to abort on failure to truncate!");
	s_die("Couldn't truncate the file!");
}
if (!fputs($fh,
    "${count_today}:${count_yday}:${count_rest}:${stamp_today}:0\n")) {
/*if (!fputcsv($fh, array($count_today, $count_yday, $count_rest,
    $stamp_today, 0), ':')) { ** not in php4 } */
	if (!flock($fh, LOCK_UN))
		s_die("Couldn't unlock file on error handler" .
		    " trying to abort on failure to write output!");
	s_die("Couldn't write output to the file!");
}
if (!flock($fh, LOCK_UN))
	s_die("Couldn't unlock file after processing!");
if (!fclose($fh))
	s_die("Couldn't safely close the file!");

/* ok, we're done; output and exit */

echo $odata . "\n";
?></body></html>
