# socks.pl, by Roger Espel Llima <odar@pobox.com>
#
# This script makes sirc talk through SOCKS proxies with the SOCKSv4
# protocol.  sirc must be version 2.2 or greater.
#
# This script must be loaded before attempting to connect to the server,
# so in a system-wide SOCKSified sirc installation, it is best to add
# the line  &load("socks.pl");   to the system's sircrc.pl.
#
# Before using sirc through a SOCKS proxy, the user must set the
# environment variable SOCKS_SERVER to the address of the SOCKS proxy
# (the firewall).  This can be an IP address or a hostname, assuming
# that the local host is able to resolve the it.  If the proxy is
# running on a port other than 1080, it must be given in the environment
# variable SOCKS_PORT.
#
# If the local host cannot resolve names outside of the firewalled
# network, *and* if your SOCKS server implements the SOCKS4A extension
# of the SOCKS protocol (which lets the local client pass hostnames
# instead of resolved addresses to the SOCKS proxy), then set the
# environment variable SOCKS_DNS to 1, and sirc will try to use it.
#
# If the SOCKSified sirc is able to talk to your SOCKS host, and has
# sufficient permissions for the connections, you should be able to 
# connect to servers and accept DCC CHATs and DCC SENDs.  
#
# To be able to send out DCC CHAT and SEND requests, the SOCKS protocol
# requires that you specify the IP address of the remote host that will
# connect to you.  This script provides the command 
# /setrem <hostname or IP> for this; use it before the DCC command.
#
# Since the remote host will generally be the same as the one appearing
# in the remote user's WHOIS, you can use the shortcuts /sdc <nick>
# and /sds <nick> <filename>  to automatically look up the remote host
# and initiate a DCC CHAT or DCC SEND.

$add_ons.="+socks.pl" if $add_ons !~ /socks/;

$socks_server=&resolve($ENV{"SOCKS_SERVER"});
$socks_dns=defined($ENV{"SOCKS_DNS"});
$socks_userid=(getpwuid($<))[0];
$socks_port=$ENV{"SOCKS_PORT"} || 1080;

sub connect {
  $_[0]=&newfh;
  local($fh, $host, $port)=@_;
  local($adr, $otherend, $request, $answer, $xtra)=&resolve($host);
  &tell("*\cbE\cb* SOCKS_SERVER not set or invalid"), return 0 
    unless $socks_server;
  $lastport=$port;
  if (!$adr) {
    &tell("*\cbE\cb* Hostname `$host' not found"), return 0 if !$socks_dns;
    $xtra=$host."\c@";
    $adr=pack("x3 c", 1);
  } else {
    $xtra='';
  }
  $request=pack("c c n a4 a* x a*", 4, 1, $port, $adr, $socks_userid, $xtra);
  $otherend=pack("S n a4 x8", &AF_INET, $socks_port, $socks_server);
  &print("*\cbE\cb* Out of file descriptors"), return 0
    unless socket($fh, &PF_INET, &SOCK_STREAM, 0);
  $trysock=$fh;
  $SIG{'QUIT'}='sigquit';
  if (!connect($fh, $otherend) || 
      syswrite($fh, $request, length($request)) != length($request) ||
      sysread($fh, $answer, 8) != 8 ||
      $answer !~ /^\000Z/) {
    &print("*\cbE\cb* Can't connect to host: " . ($! ? $! : "SOCKS error"));
    close $fh;
    $SIG{'QUIT'}='IGNORE';
    return 0;
  }
  $SIG{'QUIT'}='IGNORE';
  $bindaddr=$socks_server;
  select($fh); $|=1; select(STDOUT);
  return 1;
}

sub listen {
  $_[0]=&newfh;
  local($fh)=@_;
  &tell("*\cbE\cb* SOCKS_SERVER not set or invalid"), return 0 
    unless $socks_server;
  &tell("*\cbE\cb* Remote host not specified"), return 0 unless $remote_host;
  local($adr, $otherend, $request, $answer, $ip, $port, $xtra)=&resolve($remote_host);
  if (!$adr) {
    &tell("*\cbE\cb* Hostname `$remote_host' not found"), return 0 
      if !$socks_dns;
    $xtra=$remote_host."\c@";
    $adr=pack("x3 c", 1);
  } else {
    $xtra='';
  }
  &tell("*\cbE\cb* Out of file descriptors"), return 0
    unless socket($fh, &PF_INET, &SOCK_STREAM, 0);
  $request=pack("c c n a4 a* x a*", 4, 2, $lastport, $adr, $socks_userid, $xtra);
  $otherend=pack("S n a4 x8", &AF_INET, $socks_port, $socks_server);
  $trysock=$fh;
  $SIG{'QUIT'}='sigquit';
  if (!connect($fh, $otherend) || 
      syswrite($fh, $request, length($request)) != length($request) ||
      sysread($fh, $answer, 8) != 8 ||
      $answer !~ /^\000Z/) {
    &print("*\cbE\cb* Can't connect to host: " . ($! ? $! : "SOCKS error"));
    close $fh;
    $SIG{'QUIT'}='IGNORE';
    return 0;
  }
  $SIG{'QUIT'}='IGNORE';
  ($port, $ip)=(unpack("c c n a4", $answer))[2,3];
  $bindaddr=$ip || $socks_server;
  select($fh); $|=1; select(STDOUT);
  return $port;
}

sub accept {
  local($answer);
  $_[0]=$_[1];
  &tell("*\cbE\cb* SOCKS error"), return 0
    unless (sysread($_[0], $answer, 8) == 8 && $answer =~ /^\000Z/);
  1;
}

sub cmd_setrem {
  &getarg;
  $remote_host=$newarg;
}
&addcmd("setrem");

sub cmd_sdc {
  &getarg;
  &tell("*\cbE\cb* I need an argument") if $newarg eq '';
  &userhost($newarg, "\$remote_host=\$host; &docommand('/dcc chat $newarg');");
}
&addcmd("sdc");

sub cmd_sds {
  &getarg;
  &tell("*\cbE\cb* I need two arguments") if $newarg eq '' || $args eq '';
  &userhost($newarg, "\$remote_host=\$host; &docommand('/dcc send $newarg $args');");
}
&addcmd("sds");

