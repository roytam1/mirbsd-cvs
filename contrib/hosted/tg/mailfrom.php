<?php
/*-
 * $MirOS: contrib/hosted/tg/mailfrom.php,v 1.5 2013/02/18 10:16:34 tg Exp $
 *-
 * Copyright © 2012, 2013, 2016
 *	mirabilos <t.glaser@tarent.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
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
 * The correct way to send eMail from PHP. Do not bug the poor people
 * in #sendmail on Freenode IRC if you’re doing it wrong.
 *
 * Usage example:
 *	$res = util_sendmail('noreply@example.com',
 *	    array('user@example.com', 'ceo@example.com'),
 *	    array(
 *		'From' => 'Webserver <noreply@example.com>',
 *		'To' => 'Random L. User <user@example.com>',
 *		'Cc' => 'PHB <ceo@example.com>',
 *		'Subject' => 'Testmail äöüß € ☺',
 *		'MIME-Version' => '1.0',
 *		'Content-Type' => 'text/plain; charset=UTF-8',
 *		'Content-Transfer-Encoding' => '8bit',
 *	    ), array(
 *		'Hello!',
 *		'',
 *		'This is a test äöüß € ☺ mail.',
 *	    ));
 *
 *	echo $res[0] ? "Success\n" : ("Failure\n" . print_r($res, true));
 *
 * The body could have been passed as a string (with lines separated
 * by \n, \r\n or even \r) instead of as an array of lines, as well.
 * This is probably most useful when the text gets passed from other
 * code. For headers, this is not supported due to the mandatory en‐
 * coding of them this function performs, by the standards.
 *
 * Suggested further reading:
 * ‣ http://me.veekun.com/blog/2012/04/09/php-a-fractal-of-bad-design/
 * ‣ http://gynvael.coldwind.pl/?id=492
 * ‣ https://en.wikiquote.org/wiki/Rasmus_Lerdorf
 * ‣ http://www.rfc-editor.org/rfc/rfc822.txt and its successors
 * ‣ http://www.cs.tut.fi/~jkorpela/rfc/822addr.html
 */

/**
 * util_sendmail_encode_hdr() - Encode an eMail header
 *
 * This function wraps the PHP mb_encode_mimeheader function,
 * permitting short headers (like Content-Type usually is) to
 * pass through unencoded (because if Content-Type is encoded
 * at least Postfix does not handle the eMail correctly).
 *
 * @param	string	$fname
 *		The name of the eMail header to use, which
 *		must not preg_match /[^!-9;-~]/ (not checked)
 * @param	string	$ftext
 *		The unstructured field text to encode
 * @result	string
 *		The encoded header field, without trailing CRLF
 */
function util_sendmail_encode_hdr($fname, $ftext) {
	$old_encoding = mb_internal_encoding();
	mb_internal_encoding('UTF-8');
	$rv = util_sendmail_encode_hdr_int($fname, $ftext);
	mb_internal_encoding($old_encoding);
	return $rv;
}
function util_sendmail_encode_hdr_int($fname, $ftext) {
	$field = $fname . ': ' . $ftext;
	if (strlen($field) > 78 || preg_match('/[^ -~]/', $field) !== 0) {
		$field = mb_encode_mimeheader($field, 'UTF-8', 'Q', "\015\012");
	}
	return $field;
}

/**
 * util_sendmail_valid() - Check an eMail address for validity
 *
 * Check address syntax. For the localpart, we only
 * permit a dot-atom, not a quoted-string or any of
 * the obsolete forms, here, and the domain is mat‐
 * ched using the modern standard, allowing numeric
 * labels as per most zones including the root zone
 * but otherwise per DNS/DARPA. Domain literals and
 * whitespace are not permitted. The domain part is
 * expected to be an FQDN resolving to an MX, AAAA,
 * or A RR – the caller can verify that itself once
 * validity is established by a truthy return value
 * from this function.
 *
 * @param	string	$adr
 *		The eMail address (RFC822 addr-spec) to check
 * @result	1 if the addr-spec is valid, 0 if not, false
 *		if an error occurred (same as preg_match)
 */
function util_sendmail_valid($adr) {
	return preg_match(
	    "_^[-!#-'*+/-9=?A-Z^-~]+(\.[-!#-'*+/-9=?A-Z^-~]+)*@(?=.{1,255}\$)[0-9A-Za-z]([-0-9A-Za-z]{0,61}[0-9A-Za-z])?(\.[0-9A-Za-z]([-0-9A-Za-z]{0,61}[0-9A-Za-z])?)*\$_",
	    $adr);
}

/**
 * util_sendmail() - Send an eMail
 *
 * This function should be used in place of the PHP mail() function.
 *
 * @param	string	$sender
 *		The eMail address to use as envelope sender
 * @param	string|array(string+)	$recip
 *		The eMail address(es) of the recipient(s),
 *		that is, To: Cc: and Bcc:
 * @param	array(string=>string*)	$hdrs
 *		The headers, unencoded, as UTF-8 key/value pairs
 * @param	string|array(string*)	$body
 *		The eMail body. If an array, line by line.
 * @result	array(bool, int, string)
 *		On success, the first element is true, otherwise
 *		false, and the second element contains an error
 *		code (from the operating system, usually 0‥255,
 *		or PHP, usually -1) or false, then the third
 *		element contains a hint what went wrong.
 */
function util_sendmail($sender, $recip, $hdrs, $body) {
	$old_encoding = mb_internal_encoding();
	if (!mb_internal_encoding('UTF-8')) {
		mb_internal_encoding($old_encoding);
		return array(false, false,
		    'mb_internal_encoding("UTF-8") failed');
	}

	/* check eMail addresses and shellescape them */

	$adrs = array();
	if (!is_array($recip)) {
		$recip = array($recip);
	}
	/* the first address only */
	$what = 'Sender';
	array_unshift($recip, $sender);
	foreach ($recip as $i => $adr) {
		if (!is_string($adr)) {
			mb_internal_encoding($old_encoding);
			return array(false, false,
			    $what . ' not a string');
		}
		$adr = trim($adr);
		/* check addr-spec syntax */
		if (!util_sendmail_valid($adr)) {
			mb_internal_encoding($old_encoding);
			return array(false, false,
			    $what . ' not a valid address: ' . $adr);
		}
		$recip[$i] = $adr;
		/* quote for shell */
		$adrs[] = "'" . str_replace("'", "'\\''", $adr) . "'";
		/* all but the first address */
		$what = 'Recipient';
	}

	/* handle the mail header */

	$msg = array();
	$hdr_seen = array();
	foreach ($hdrs as $k => $v) {
		/* do some checks */
		if (strlen(($k = strval($k))) < 1) {
			mb_internal_encoding($old_encoding);
			return array(false, false,
			    'Empty header found');
		}
		if (preg_match('/[^!-9;-~]/', $k) !== 0) {
			mb_internal_encoding($old_encoding);
			return array(false, false,
			    'Illegal char in header: ' . $k);
		}
		/* lowercase, independent on the locale */
		$kf = strtr($k,
		    'QWERTYUIOPASDFGHJKLZXCVBNM',
		    'qwertyuiopasdfghjklzxcvbnm');
		if (isset($hdr_seen[$kf])) {
			mb_internal_encoding($old_encoding);
			return array(false, false,
			    'Duplicate header: ' . $kf);
		}
		$hdr_seen[$kf] = true;
		/* append to message */
		$msg[] = util_sendmail_encode_hdr_int($k, $v);
	}

	/* handle mandatory header fields */

	if (!isset($hdr_seen['date'])) {
		/* date() is locale-independent and thus correct here */
		$msg[] = util_sendmail_encode_hdr_int('Date', date('r'));
	}
	if (!isset($hdr_seen['from'])) {
		$msg[] = util_sendmail_encode_hdr_int('From', $recip[0]);
	}

	$msg[] = '';

	/* take care of the body */

	if (!is_array($body)) {
		/*
		 * First, convert all CR-LF pairs into LF, so we
		 * then have either Unix or Macintosh line endings
		 */
		$body = str_replace("\015\012", "\012", strval($body));
		/*
		 * Now, detect which of these two, and convert them
		 * to array lines. Preference on Unix (or converted
		 * ASCII) over Macintosh: if an LF is found, use it.
		 */
		$body = explode(strpos($body, "\012") === false ?
		    "\015" : "\012", $body);
	}

	foreach ($body as $v) {
		$v = strval($v);
		if (strlen($v) > 998) {
			mb_internal_encoding($old_encoding);
			return array(false, false,
			    'Line too long: ' . $v);
		}
		$msg[] = $v;
	}

	/* generate a mail message from that */

	$body = implode("\015\012", $msg) . "\015\012";

	/* this is only safe because $adrs is shell-escaped */
	$adrs[0] = '/usr/sbin/sendmail -f' . $adrs[0] . ' -i --';
	$cmd = implode(' ', $adrs);

	if (($p = popen($cmd, 'wb')) === false) {
		mb_internal_encoding($old_encoding);
		return array(false, false,
		    "Could not popen($cmd, 'wb');");
	}
	if (!($i = fwrite($p, $body)) || $i != strlen($body)) {
		mb_internal_encoding($old_encoding);
		return array(false, false,
		    "Could not fwrite: $i");
	}
	mb_internal_encoding($old_encoding);
	if (($i = pclose($p)) == -1 ||
	    (function_exists('pcntl_wifexited') && !pcntl_wifexited($i))) {
		return array(false, -1);
	}
	if (!function_exists('pcntl_wexitstatus')) {
		return array(true, -1);
	}
	$i = pcntl_wexitstatus($i);
	return array(!$i, $i);
}
