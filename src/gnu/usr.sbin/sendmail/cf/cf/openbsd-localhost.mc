divert(-1)dnl
#
# $MirOS: src/gnu/usr.sbin/sendmail/cf/cf/openbsd-localhost.mc,v 1.13 2015/05/25 14:58:41 tg Exp $
# @(#)openbsd-proto.mc $Revision$
#
# Copyright (c) 2002, 2003, 2004, 2005, 2007, 2008, 2011, 2015
#	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
# Copyright (c) 1998 Sendmail, Inc.  All rights reserved.
# Copyright (c) 1983 Eric P. Allman.  All rights reserved.
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# By using this file, you agree to the terms and conditions set
# forth in the LICENSE file which can be found at the top level of
# the sendmail distribution.

#
#  This configuration only runs sendmail on the localhost interface.
#  This allows mail on the local host to work without accepting
#  connections from the net at large.
#

divert(0)dnl
VERSIONID(`$MirOS: src/gnu/usr.sbin/sendmail/cf/cf/openbsd-localhost.mc,v 1.13 2015/05/25 14:58:41 tg Exp $')dnl
OSTYPE(openbsd)dnl
dnl
dnl
dnl If you have only a non-static IP address you may wish to forward
dnl outgoing mail through your ISP's mail server to prevent matching
dnl one of the dial-up DNS black holes. Just uncomment the following
dnl line and replace mail.myisp.net with the hostname of your ISP's
dnl mail server.
dnl
dnl define(`SMART_HOST', `[mail.myisp.net]')dnl
dnl
dnl
dnl Disable EXPN and VRFY to help thwart address harvesters and
dnl require senders to say hello.
dnl
define(`confPRIVACY_FLAGS',
  `authwarnings,needmailhelo,noexpn,novrfy,nobodyreturn')dnl
dnl
dnl
dnl We wish to make the existence of the local-host-names and
dnl trusted-users files optional, hence the "-o" below.
dnl
define(`confCW_FILE', `-o MAIL_SETTINGS_DIR`'local-host-names')dnl
define(`confCT_FILE', `-o MAIL_SETTINGS_DIR`'trusted-users')dnl
dnl
dnl
dnl Use of UUCP-style addresses in the modern internet are generally
dnl an error (and sometimes used by spammers) so disable support for
dnl them. To simply treat '!' as a normal character, change `reject'
dnl to `nospecial'.
dnl
FEATURE(`nouucp', `reject')dnl
dnl
dnl
dnl The access database allows for certain actions to be taken
dnl based on the source or destination address.
dnl The access database file should be considered optional.
dnl
FEATURE(`access_db', `hash -o -T<TMPF> MAIL_SETTINGS_DIR`'access',
  `relaytofulladdress')dnl
FEATURE(`blacklist_recipients')dnl
dnl
dnl
dnl Enable support for /etc/mail/local-host-names.
dnl Contains hostnames that should be considered local.
dnl
FEATURE(`use_cw_file')dnl
dnl
dnl
dnl Enable support for /etc/mail/mailertable.
dnl
FEATURE(`mailertable', `hash -o MAIL_SETTINGS_DIR`'mailertable')dnl
dnl
dnl
dnl Enable support for /etc/mail/trusted-users.
dnl Users listed herein may spoof mail from other users.
dnl
FEATURE(`use_ct_file')dnl
dnl
dnl
dnl Enable support for /etc/mail/virtusertable.
dnl Used to do N -> N address mapping.
dnl
FEATURE(`virtusertable', `hash -o MAIL_SETTINGS_DIR`'virtusertable')dnl
dnl
dnl
dnl Rewrite (unqualified) outgoing email addresses using the
dnl mapping listed in /etc/mail/genericstable
dnl
FEATURE(`genericstable', `hash -o MAIL_SETTINGS_DIR`'genericstable')dnl
dnl
dnl
dnl Normally only local addresses are rewritten.  By using
dnl generics_entire_domain and either GENERICS_DOMAIN
dnl or GENERICS_DOMAIN_FILE addresses from hosts in the
dnl specified domain(s) will be rewritten too.
dnl
dnl FEATURE(`generics_entire_domain')dnl
dnl GENERICS_DOMAIN(`othercompany.com')dnl
dnl GENERICS_DOMAIN_FILE(`MAIL_SETTINGS_DIR`'generics-domains')dnl
dnl
dnl
dnl Include the local host domain even on locally delivered mail
dnl (which would otherwise contain only the username).
dnl
FEATURE(`always_add_domain')dnl
dnl
dnl
FEATURE(`accept_unresolvable_domains')dnl
dnl
dnl
dnl Configuration of MTA/MSA addresses:
dnl
FEATURE(`no_default_msa')dnl
dnl
dnl Accept incoming connections on IPv4 and IPv6 loopback,
dnl both port 25 (SMTP) and port 587 (MSA).
dnl
DAEMON_OPTIONS(`Family=inet, Address=127.0.0.1, Name=MTA')dnl
DAEMON_OPTIONS(`Family=inet6, Address=::1, Name=MTA6, M=O')dnl
DAEMON_OPTIONS(`Family=inet, Address=127.0.0.1, Port=587, Name=MSA, M=E')dnl
DAEMON_OPTIONS(`Family=inet6, Address=::1, Port=587, Name=MSA6, M=O, M=E')dnl
dnl
dnl Use either IPv4 or IPv6 for outgoing connections.
dnl
CLIENT_OPTIONS(`Family=inet, Address=0.0.0.0')dnl
CLIENT_OPTIONS(`Family=inet6, Address=::')dnl
dnl
dnl
dnl Some broken nameservers will return SERVFAIL (a temporary failure)
dnl on T_AAAA (IPv6) lookups.
dnl
define(`confBIND_OPTS', `WorkAroundBrokenAAAA')dnl
dnl
dnl
dnl TLS/SSL support; read starttls(8) to use.
dnl
dnl MirOS speaks STARTTLS by default; the certificate is
dnl built during first bootup and self-signed.
dnl You should get a real certificate as soon as possible.
dnl
define(`confCACERT_PATH',	`/etc/ssl/certs')dnl
define(`confCACERT',		`/etc/ssl/deflt-ca.cer')dnl
define(`confSERVER_CERT',	`/etc/ssl/default.cer')dnl
define(`confCLIENT_CERT',	`/etc/ssl/default.cer')dnl
define(`confSERVER_KEY',	`/etc/ssl/private/default.key')dnl
define(`confCLIENT_KEY',	`/etc/ssl/private/default.key')dnl
define(`confCIPHER_LIST',	`kEECDH+aRSA:kEDH+aRSA:!COMPLEMENTOFDEFAULT:!ADH:!AECDH:-MEDIUM:!LOW:!EXPORT:!aNULL:!eNULL:!PSK:!aECDH:!DES:!MD5:EDH-DSS-DES-CBC3-SHA:ECDHE-RSA-RC4-SHA:RC4-SHA')dnl
dnl define(`confDH_PARAMETERS',	`/etc/ssl/dhparams.pem')dnl
define(`confRAND_FILE',		`/dev/arandom')dnl
dnl
dnl
dnl MirOS enables special handling of eMail by default in order
dnl to be compatible to most of the internet mail servers.
dnl
dnl Handling of unescaped 8-bit messages
dnl
dnl - Strip the eigth bit (done when listening to the 'net)
dnl
define(`confSEVEN_BIT_INPUT', `True')dnl
dnl
dnl if confSEVEN_BIT_INPUT==False AND MIME8TO7 not =0 in Makefile
dnl - Convert them to valid MIME data (done in submit.mc)
dnl
dnl define(`confEIGHT_BIT_HANDLING', `mimefy')dnl
dnl
dnl
dnl Sanitise default mailer flags
dnl Escape lines starting with unescaped "From "
dnl
define(`_DEF_LOCAL_MAILER_FLAGS', `LlsDFMAw5:/|@q')dnl
define(`LOCAL_MAILER_FLAGS', `rmnS67E')dnl
define(`_DEF_LOCAL_SHELL_FLAGS', `LlsDFMoq')dnl
define(`LOCAL_SHELL_FLAGS', `eu67E')dnl
define(`_DEF_SMTP_MAILER_FLAGS', `LmDFMuX')dnl
define(`SMTP_MAILER_FLAGS', `67E')dnl
dnl
dnl
dnl Adhere to ~/.etc standard of MirOS
dnl
define(`confFORWARD_PATH',
  `$z/.etc/forward.$w:$z/.etc/forward:$z/.forward.$w:$z/.forward')dnl
dnl
dnl Say hello to our friendly user
dnl
define(`confSMTP_LOGIN_MSG',
  `$j ready at $b\n >> Bitte keine Werbung einwerfen! <<\nWho do you wanna pretend to be today?')dnl
dnl
dnl Raise some pool sizes and timeouts
dnl
define(`confMCI_CACHE_SIZE', `32')dnl
define(`confTO_QUEUERETURN', `14d')dnl
dnl
dnl
dnl That's all, folks.
dnl
dnl
MAILER(`local')dnl
MAILER(`smtp')dnl
dnl
dnl
LOCAL_RULESETS
dnl
dnl
dnl Enable to play "Towers of Hanoi"
dnl
############################################
###  Ruleset 49 -- a.s.r Towers of Hanoi ###
############################################
S49
RHANOI:$+	$:1 2 3$1
R$-$-$-$*[$+]	$:$1$2$3$4
R$-$-$-		$@$1$2$3
R$-$-$-@$*	$:$>49 $1$3$2$4
R$-$-$-$*	$:$>49 $2$3$1$4[Move top disc of peg $1 to peg $3]
R$-$-$-$*	$:$3$2$1@$4

# Usage:
#   echo '49 HANOI:@@@@' | sendmail -bt -d21
dnl
dnl
dnl End of file.
dnl
