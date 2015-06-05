#if 0
=pod
#endif
/*                      _             _
**  _ __ ___   ___   __| |    ___ ___| |  mod_ssl
** | '_ ` _ \ / _ \ / _` |   / __/ __| |  Apache Interface to OpenSSL
** | | | | | | (_) | (_| |   \__ \__ \ |  www.modssl.org
** |_| |_| |_|\___/ \__,_|___|___/___/_|  ftp.modssl.org
**                      |_____|
** ssl_engine_dh.c 
** Diffie-Hellman Built-in Temporary Parameters
*/

/* ====================================================================
 * Copyright (c) 1998-2003 Ralf S. Engelschall. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by
 *     Ralf S. Engelschall <rse@engelschall.com> for use in the
 *     mod_ssl project (http://www.modssl.org/)."
 *
 * 4. The names "mod_ssl" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    rse@engelschall.com.
 *
 * 5. Products derived from this software may not be called "mod_ssl"
 *    nor may "mod_ssl" appear in their names without prior
 *    written permission of Ralf S. Engelschall.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by
 *     Ralf S. Engelschall <rse@engelschall.com> for use in the
 *     mod_ssl project (http://www.modssl.org/)."
 *
 * THIS SOFTWARE IS PROVIDED BY RALF S. ENGELSCHALL ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL RALF S. ENGELSCHALL OR
 * HIS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 */

#include "mod_ssl.h"

__RCSID("$MirOS$");

/* ----BEGIN GENERATED SECTION-------- */

/*
** Diffie-Hellman-Parameters: (512 bit)
**     prime:
**         00:f8:7f:ba:c1:13:78:20:54:b3:29:6c:ac:b2:e3:
**         c2:cb:b3:b5:5b:0d:44:31:e4:8e:81:df:bd:43:6d:
**         b7:01:8f:8b:3f:89:f2:c5:cf:19:bb:1b:40:9c:02:
**         a9:59:c5:39:b5:4f:28:05:eb:67:47:8b:9b:ff:c5:
**         48:bc:e4:68:6b
**     generator: 2 (0x2)
** Diffie-Hellman-Parameters: (1024 bit)
**     prime:
**         00:c0:39:85:d1:74:35:70:cc:9a:cc:51:2a:ee:64:
**         9e:7f:46:50:52:ba:66:13:0d:2f:bb:1f:1e:6c:ba:
**         b6:ba:b5:11:93:ab:cc:94:a5:3c:a3:68:19:57:82:
**         95:46:7a:9e:2d:5a:60:47:1f:85:e3:f2:89:98:eb:
**         0d:79:ba:f4:b9:04:37:f2:66:5f:b8:69:22:5e:e2:
**         ed:b0:52:13:a3:e0:f7:3f:60:04:1a:bb:1e:25:b9:
**         94:ce:15:5e:d3:4a:68:b9:56:ee:b2:de:c5:4e:35:
**         4d:62:3c:8e:f5:cf:f3:7c:32:7a:c0:05:83:1d:d0:
**         8a:c7:13:85:84:d6:df:55:0b
**     generator: 2 (0x2)
*/

static const unsigned char dh512_p[] = {
    0xF8, 0x7F, 0xBA, 0xC1, 0x13, 0x78, 0x20, 0x54, 0xB3, 0x29, 0x6C, 0xAC,
    0xB2, 0xE3, 0xC2, 0xCB, 0xB3, 0xB5, 0x5B, 0x0D, 0x44, 0x31, 0xE4, 0x8E,
    0x81, 0xDF, 0xBD, 0x43, 0x6D, 0xB7, 0x01, 0x8F, 0x8B, 0x3F, 0x89, 0xF2,
    0xC5, 0xCF, 0x19, 0xBB, 0x1B, 0x40, 0x9C, 0x02, 0xA9, 0x59, 0xC5, 0x39,
    0xB5, 0x4F, 0x28, 0x05, 0xEB, 0x67, 0x47, 0x8B, 0x9B, 0xFF, 0xC5, 0x48,
    0xBC, 0xE4, 0x68, 0x6B,
};
static const unsigned char dh512_g[] = {
    0x02,
};

static DH *get_dh512(void)
{
    DH *dh;

    if ((dh = DH_new()) == NULL)
        return (NULL);
    dh->p = BN_bin2bn(dh512_p, sizeof(dh512_p), NULL);
    dh->g = BN_bin2bn(dh512_g, sizeof(dh512_g), NULL);
    if ((dh->p == NULL) || (dh->g == NULL))
        return (NULL);
    return (dh);
}
static const unsigned char dh1024_p[] = {
    0xC0, 0x39, 0x85, 0xD1, 0x74, 0x35, 0x70, 0xCC, 0x9A, 0xCC, 0x51, 0x2A,
    0xEE, 0x64, 0x9E, 0x7F, 0x46, 0x50, 0x52, 0xBA, 0x66, 0x13, 0x0D, 0x2F,
    0xBB, 0x1F, 0x1E, 0x6C, 0xBA, 0xB6, 0xBA, 0xB5, 0x11, 0x93, 0xAB, 0xCC,
    0x94, 0xA5, 0x3C, 0xA3, 0x68, 0x19, 0x57, 0x82, 0x95, 0x46, 0x7A, 0x9E,
    0x2D, 0x5A, 0x60, 0x47, 0x1F, 0x85, 0xE3, 0xF2, 0x89, 0x98, 0xEB, 0x0D,
    0x79, 0xBA, 0xF4, 0xB9, 0x04, 0x37, 0xF2, 0x66, 0x5F, 0xB8, 0x69, 0x22,
    0x5E, 0xE2, 0xED, 0xB0, 0x52, 0x13, 0xA3, 0xE0, 0xF7, 0x3F, 0x60, 0x04,
    0x1A, 0xBB, 0x1E, 0x25, 0xB9, 0x94, 0xCE, 0x15, 0x5E, 0xD3, 0x4A, 0x68,
    0xB9, 0x56, 0xEE, 0xB2, 0xDE, 0xC5, 0x4E, 0x35, 0x4D, 0x62, 0x3C, 0x8E,
    0xF5, 0xCF, 0xF3, 0x7C, 0x32, 0x7A, 0xC0, 0x05, 0x83, 0x1D, 0xD0, 0x8A,
    0xC7, 0x13, 0x85, 0x84, 0xD6, 0xDF, 0x55, 0x0B,
};
static const unsigned char dh1024_g[] = {
    0x02,
};

static DH *get_dh1024(void)
{
    DH *dh;

    if ((dh = DH_new()) == NULL)
        return (NULL);
    dh->p = BN_bin2bn(dh1024_p, sizeof(dh1024_p), NULL);
    dh->g = BN_bin2bn(dh1024_g, sizeof(dh1024_g), NULL);
    if ((dh->p == NULL) || (dh->g == NULL))
        return (NULL);
    return (dh);
}
/* ----END GENERATED SECTION---------- */

DH *ssl_dh_GetTmpParam(int nKeyLen)
{
    DH *dh;

    if (nKeyLen == 512)
        dh = get_dh512();
    else if (nKeyLen == 1024)
        dh = get_dh1024();
    else
        dh = get_dh1024();
    return dh;
}

DH *ssl_dh_GetParamFromFile(char *file)
{
    DH *dh = NULL;
    BIO *bio;

    if ((bio = BIO_new_file(file, "r")) == NULL)
        return NULL;
    dh = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
    BIO_free(bio);
    return (dh);
}

/*
=cut
##
##  Embedded Perl script for generating the temporary DH parameters
##

require 5.003;
use strict;

#   configuration
my $file  = $0;
my $begin = '----BEGIN GENERATED SECTION--------';
my $end   = '----END GENERATED SECTION----------';

#   read ourself and keep a backup
open(FP, "<$file") || die;
my $source = '';
$source .= $_ while (<FP>);
close(FP);
open(FP, ">$file.bak") || die;
print FP $source;
close(FP);

#   generate the DH parameters
print "1. Generate 1024 bit Diffie-Hellman parameters (p, g)\n";
my $rand = '';
foreach $file (qw(/var/log/messages /var/adm/messages 
                  /kernel /vmunix /vmlinuz /etc/hosts /etc/resolv.conf)) {
    if (-f $file) {
        $rand = $file     if ($rand eq '');
        $rand .= ":$file" if ($rand ne '');
    }
}
$rand = "-rand $rand" if ($rand ne '');
system("openssl gendh $rand -out dh1024.pem 1024");

#   generate DH param info 
my $dhinfo = '';
open(FP, "openssl dh -noout -text -in dh1024.pem |") || die;
$dhinfo .= $_ while (<FP>);
close(FP);
$dhinfo =~ s|^|** |mg;
$dhinfo = "\n\/\*\n$dhinfo\*\/\n\n";

#   generate C source from DH params
my $dhsource = '';
open(FP, "openssl dh -noout -C -in dh1024.pem | indent -npro -st -bad -nbs -ncdb -ci2 -ncsp -di0 -i4 -l80 -lc72 -nlp -nlpi -npsl -TBIO -TDH | expand |") || die;
$dhsource .= $_ while (<FP>);
close(FP);
$dhsource =~ s|(DH\s+\*get_dh)|static $1|sg;
$dhsource =~ s|(get_dh\d+)\(\)|$1(void)|sg;
$dhsource =~ s|static unsigned char|static const unsigned char|sg;

#   generate output
my $o = $dhinfo . $dhsource;

#   insert the generated code at the target location
$source =~ s|(\/\* $begin.+?\n).*\n(.*?\/\* $end)|$1$o$2|s;

#   and update the source on disk
print "Updating file `$file'\n";
open(FP, ">$file") || die;
print FP $source;
close(FP);

#   cleanup
unlink("dh1024.pem");

=pod
*/
