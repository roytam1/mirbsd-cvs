<?php
/* $MirOS: www/vbegin.php,v 1.5 2005/12/18 16:36:54 tg Exp $ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
 *-
 * This is the process header, mostly shared with Thorsten Glasers personal
 * homepage. Editors must be aware of the fact that I reserve the right
 * to synchronize these two.
 */

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

 if (empty($has_vfuncs)) {
	require("vfuncs.php");
 }

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

 // Style Sheet
 $tg_ucss = getcsscookie();

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
<?php
 // Stylesheet link
 if ($tg_realm == 2) {
	if (!isset($tg_noss)) {
?> <link rel="stylesheet" type="text/css" href="<?php
		echo "${tg_pfad}${tg_ucss}"; ?>" />
<?php
	}
 } else if ($tg_realm != 3) {
?> <link rel="stylesheet" type="text/css" href="<?php
	echo "${tg_pfad}"; ?>rstil.css" />
<?php
 }

 // Stylesheet MS Internet Exploder Crash Service ;-)
 if (empty($tg_noie) && (strstr($tg_bws, "MSIE "))) {
?> <style type="text/css"> <!--
  p { cssText:font-weight:bold; } --></style>
<?php
 }
?>
 <meta name="author" content="Thorsten Glaser" />
 <meta name="copyright" content="All rights reserved. Redistribution except for scientific and educational uses strictly prohibited." />
 <meta name="owner" content="The MirOS Project and The MirPorts Framework" />
 <meta name="licence" content="see the source files in CVSWEB for details" />
