<?php
/* $MirOS$ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
 *-
 * This is a library for the home page.
 */

$has_vfuncs = 1;
$is_admin = 0;

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
 * read cookie telling which CSS to use
 */
function getcsscookie()
{
	global $is_admin;

	$tmp = "nonexistent";
	if (!empty($_COOKIE['usecss'])) {
		$tmp = "vs".$_COOKIE['usecss'].".css";
	}
	if (!is_readable($tmp)) {
		$tmp = "vstyle.css";
	}

	if ($tmp === "vsroot.css") {
		$is_admin = 1;
	} else {
		$is_admin = 2;
	}
	return $tmp;
}

/*
 * Is admin?
 */
function isadm()
{
	global $is_admin;

	if ($is_admin == 0)
		getcsscookie();
	return ($is_admin === 1) ? true : false;
}
?>
