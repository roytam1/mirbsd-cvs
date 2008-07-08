# $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $
#-
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

package BSD::arc4random;

use 5.000;
use strict;
use warnings;

BEGIN {
	require Exporter;
	require DynaLoader;
	our ($VERSION, @ISA, @EXPORT, @EXPORT_OK, %EXPORT_TAGS);
	$VERSION = 0.01;
	@ISA = qw(Exporter DynaLoader);
	@EXPORT = qw(&arc4random &arc4random_pushb &arc4random_pushk);
	%EXPORT_TAGS = ();
	@EXPORT_OK = qw();
}
our @EXPORT_OK;

bootstrap BSD::arc4random $BSD::arc4random::VERSION;

sub
arc4random()
{
	my $rv;

	print "D: calling arc4random()...";
	$rv = arc4random_xs();
	print " got ${rv}\n";
	return $rv;
}

sub
arc4random_pushb($)
{
	my $buf = shift;
	my $rv;

	print "D: calling arc4random_pushb(${buf})...";
	$rv = arc4random_pushb_xs($buf);
	print " got ${rv}\n";
	return $rv;
}

sub
arc4random_pushk($)
{
	my $buf = shift;
	my $rv;

	print "D: calling arc4random_pushk(${buf})...";
	$rv = arc4random_pushk_xs($buf);
	print " got ${rv}\n";
	return $rv;
}

1;
__END__

=head1 NAME

BSD::arc4random - Perl interface to the arc4 random number generator

=head1 SYNOPSIS

  use BSD::arc4random;
  $v = arc4random();
  $v = arc4random_pushb("entropy to pass to the system");
  $v = arc4random_pushk("entropy to pass to the kernel");

=head1 DESCRIPTION

This set of functions maps the L<arc4random(3)> family of libc functions
into Perl code.

=item B<arc4random>

This function returns an unsigned 32-bit integer random value.

=item B<arc4random_pushb>

This function first pushes the argument to the kernel if possible,
then the entropy returned by the kernel into the libc pool, then
returns an unsigned 32-bit integer random value from it.

=item B<arc4random_pushk>

This function first pushes the argument to the kernel if possible,
then returns an unsigned 32-bit integer random value from the kernel.

=head1 CAVEATS

More functions will be implemented soon.

=head1 AUTHOR

Thorsten Glaser, E<lt>tg@mirbsd.deE<gt>

=head1 SEE ALSO

The L<arc4random(3)> manual page, available online at:
L<http://www.mirbsd.org/man/arc4random.3>

=head1 COPYRIGHT AND LICENSE

Copyright (c) 2008 Thorsten Glaser

This module is covered by the MirOS Licence.

=cut
