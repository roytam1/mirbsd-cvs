# Copyright (c) 2008
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-
# Irssi extension to support MirSirc's randex protocol

use vars qw($VERSION %IRSSI);
$VERSION = sprintf "%d.%02d",
    q$MirOS: ports/net/irssi/files/randex.pl,v 1.6 2008/07/20 22:53:08 tg Exp $
    =~ m/,v (\d+)\.(\d+) /;
%IRSSI = (
	authors		=> 'Thorsten Glaser',
	contact		=> 'tg@mirbsd.de',
	name		=> 'randex',
	description	=> 'implement MirSirc\'s randex protocol',
	license		=> 'MirOS',
	url		=> 'http://cvs.mirbsd.de/ports/net/sirc/dist/dsircp',
	changed		=> $VERSION,
	modules		=> 'BSD::arc4random',
	commands	=> "randex"
);

use BSD::arc4random qw(:all);
use Fcntl qw(:DEFAULT :flock);
use File::Path qw(mkpath);
use File::Basename qw(dirname);

our $irssi_ctcp_version_reply = '';

sub
cmd_randex
{
	my ($data, $server, $witem) = @_;
	my $recip = undef;
	my $towho;
	my $s;

	if (!$server || !$server->{connected}) {
		Irssi::print("Not connected to server");
		return;
	}

	if ($data) {
		$recip = $server;
		$towho = $data;
	} elsif ($witem && ($witem->{type} eq "QUERY")) {
		$recip = $witem->{server};
		$towho = $witem->{name};
	}
	if (!defined($recip)) {
		Irssi::print("You must specify a nick or channel!");
		return;
	}

	$s = pack("u", arc4random_bytes(32, "for $towho"));
	chop($s);
	$recip->send_raw("PRIVMSG ${towho} :\caENTROPY ${s}\ca");
	Irssi::print("Initiating the RANDEX protocol with ${towho}")
	    unless Irssi::settings_get_bool("rand_quiet");
}

sub
cmd_randstir
{
	arc4random_stir();
	Irssi::timeout_remove($tmo_randfile) if defined($tmo_randfile);
	randfile_timeout(1);
	Irssi::print("Entropy pool stirred.")
	    unless Irssi::settings_get_bool("rand_quiet");
}

sub
process_entropy_request
{
	my ($server, $args, $nick, $address, $target) = @_;
	my $evalue = pack("u", arc4random_bytes(32,
	    "from $nick $args $address $target"));
	chop($evalue);
	Irssi::print("${nick} initiated the RANDEX protocol with ${target}")
	    unless Irssi::settings_get_bool("rand_quiet");
	$server->ctcp_send_reply("NOTICE ${nick} :\caRANDOM ${evalue}\ca");
}

sub
process_random_response
{
	my ($server, $args, $nick, $address, $target) = @_;
	my $t = (BSD::arc4random::have_kintf() ? "" : "not ") .
	    "pushing to kernel";

	arc4random_pushb("by $nick $args $address $target");
	Irssi::print("RANDEX protocol reply from $nick to $target, $t")
	    unless Irssi::settings_get_bool("rand_quiet");
}

sub
process_ctcp_before
{
	my $v = Irssi::settings_get_str("ctcp_version_reply");

	if (!$v) {
		$v = 'irssi v$J - running on $sysname $sysarch';
	}
	$irssi_ctcp_version_reply = $v;
	$v .= " (RANDOM=" . $RANDOM . ")";
	Irssi::settings_set_str("ctcp_version_reply", $v);
}

sub
process_ctcp_after
{
	if ($irssi_ctcp_version_reply) {
		Irssi::settings_set_str("ctcp_version_reply",
		    $irssi_ctcp_version_reply);
	}
}

sub
randfile_loadstore
{
	my $randfile = Irssi::settings_get_str("randfile");
	my $tryread = 0;
	my $data = '';
	my $dlen = 0;
	my $fh;
	my $fhopen = 0;
	my $dir;

	$randfile = $ENV{'HOME'} . "/.pgp/randseed.bin"
	    if (!defined($randfile) || !$randfile);
	$dir = dirname($randfile);
	if (! -d $dir) {
		eval { mkpath([$dir]) };
		if ($@) {
			$randfile = "/tmp/randfile." . $RANDOM;
		}
	}
	$randfile = "/tmp/randfile." . $RANDOM unless (-d dirname($randfile));
	Irssi::settings_set_str("randfile", $randfile);
	stat($randfile);
	if (-b _ || -c _) {
		$tryread = 4;
	} elsif (-s _) {
		$tryread = -s $_;
	}
	if ($tryread && sysopen($fh, $randfile, O_RDWR)) {
		$fhopen = 1;
		$dlen = sysread($fh, $data, $tryread)
		    or $fhopen = 0;
		if (defined($dlen) && $dlen) {
			my $d = $data;

			$data = arc4random_bytes(1024);
			$dlen = 1024;
			arc4random_addrandom($d);
		} else {
			$dlen = 0;
			$data = '';
		}
		close($fh) unless $fhopen;
	}
	if (!$fhopen && sysopen($fh, $randfile, O_WRONLY | O_CREAT, 0600)) {
		$fhopen = 1;
	}
	if (!$fhopen) {
		Irssi::print("Cannot write to randfile '$randfile'!");
		return;
	}
	if (!flock($fh, LOCK_EX)) {
		Irssi::print("warning: cannot lock '$randfile'");
	}
	truncate($fh, 0);
	$data .= arc4random_bytes(1560 - $dlen);
	syswrite($fh, $data, length($data));
	close($fh);
}

my $tmo_randfile = undef;
my $rmo_randstir = undef;
my $g_interval;
my $g_stirival;

sub
randfile_timeout
{
	my $status = shift;
	my $interval = $g_interval = Irssi::settings_get_int("rand_interval");

	if (!defined($interval) || $interval !~ /^[0-9]+$/) {
		$interval = 900;
	}
	Irssi::settings_set_int("rand_interval", $interval);
	if (($status == 0 && $interval > 0) || $status == 1) {
		randfile_loadstore();
	}
	$interval = 900 if ($interval == 0);
	$tmo_randfile = Irssi::timeout_add_once($interval * 1000,
	    "randfile_timeout", 0);
}

sub
randstir_timeout
{
	my $status = shift;
	my $interval = $g_stirival = Irssi::settings_get_int("arc4stir_interval");

	if (!defined($interval) || $interval !~ /^[0-9]+$/) {
		$interval = 7200;
	}
	Irssi::settings_set_int("arc4stir_interval", $interval);
	if ($status == 0 && $interval > 0) {
		arc4random_stir();
	}
	if (BSD::arc4random::have_kintf()) {
		# when we can push to the kernel, periodic stirring
		# is superfluous
		$tmo_randstir = undef;
		return;
	}
	$interval = 7200 if ($interval == 0);
	$tmo_randstir = Irssi::timeout_add_once($interval * 1000,
	    "randstir_timeout", 0);
}

sub
sig_setup_changed
{
	if ($g_interval != Irssi::settings_get_int("rand_interval")) {
		Irssi::timeout_remove($tmo_randfile) if defined($tmo_randfile);
		randfile_timeout(2);
	}
	if ($g_stirival != Irssi::settings_get_int("arc4stir_interval")) {
		Irssi::timeout_remove($tmo_randstir) if defined($tmo_randstir);
		randstir_timeout(2);
	}
}

sub
sig_quitting
{
	randfile_loadstore();
}

# interval in which to re-read and re-write the randseed.bin file (seconds)
Irssi::settings_add_int("randex", "rand_interval", 900);
# interval in which to request new entropy from the kernel into the libc
# pool, in seconds; ignored if we have the kernel push interface
Irssi::settings_add_int("randex", "arc4stir_interval", 7200);
# path to the randseed.bin file
{
	my $randfile = $ENV{'RANDFILE'};

	if (!defined($randfile) || !$randfile) {
		# IMPORTANT!: do *not* use ~/.gnupg/random_seed,
		# since it is not just a binary chunk of entropy
		# but a dumped internal data structure; gpg WILL
		# NOT LOAD a randseed file we write, pgp-2.6.3in
		# however is as fine with it as PuTTY and others
		$randfile = $ENV{'HOME'} . "/.pgp/randseed.bin";
	}
	Irssi::settings_add_str("randex", "randfile", $randfile);
}
# do not write to the main window unless something fatal happens
Irssi::settings_add_bool("randex", "rand_quiet", 0);

Irssi::signal_add('gui exit', \&sig_quitting);
Irssi::command_bind('randex', 'cmd_randex');
Irssi::command_bind('randstir', 'cmd_randstir');
Irssi::signal_add('ctcp msg entropy', \&process_entropy_request);
Irssi::signal_add('ctcp reply random', \&process_random_response);
Irssi::ctcp_register("ENTROPY");
Irssi::signal_add_first('ctcp msg version', \&process_ctcp_before);
Irssi::signal_add_last('ctcp msg version', \&process_ctcp_after);
Irssi::print("randex.pl ${VERSION} loaded, entropy is " .
    (BSD::arc4random::have_kintf() ? "" : "not ") .
    "pushed to the kernel");
randfile_timeout(1);
randstir_timeout(1);
Irssi::signal_add('setup changed', \&sig_setup_changed);

1;
