<?php
/* $MirBSD: www/vfuncs.php,v 1.6 2004/11/12 17:54:19 tg Exp $
 *-
 * Copyright (c) 1999, 2002, 2003, 2004
 *	Thorsten Glaser <tg@66h.42h.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. All marketing or advertising materials mentioning features or
 *    use of this product must display the following acknowledgement:
 *    * This product includes material provided by Thorsten Glaser.
 * 4. Neither the name of Thorsten Glaser or the MirOS project nor
 *    the names of their contributors may be used to endorse or pro-
 *    mote products derived from this software without specific prior
 *    written permission.
 * 5. If this work is used on world wide web pages, the authors must
 *    be given due credits in the site's imprint.
 * 6. This licence automatically ends if the site of licensee is not
 *    easily distinguishable from Thorsten Glaser's personal homepage
 *    or the MirOS project's site.
 * 7. This licence does not cover usage of the pictures used on the
 *    pages, especially not the BSD Dæmon or the MirOS/MirAbile logo.
 *
 * This work is provided "as is" with no explicit or implicit warran-
 * ties whatsoever to the maximum extend permitted by applicable law;
 * in no event may an author or contributor be held liable for damage
 * that is, directly or indirectly, caused by the work, even if advi-
 * sed of the possibility of such damage.
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
