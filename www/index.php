<?php
/* $MirBSD: www/index.php,v 1.15 2005/01/09 11:55:47 tg Exp $
 *-
 * Copyright (c) 1999, 2002, 2003, 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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
	This is copyrighted material. For the full licence text, see the
	MirOS CVSweb or the CSS file. In no event may text from this page
	be simply copied into another website under an unfree or otherwise
	mismatching licence, such as the GNU Free Documentation License.
 -->
</head><body>
<div class="index">
 <ul class="lv1">
  <?php include($ridx); ?>
 </ul>
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
