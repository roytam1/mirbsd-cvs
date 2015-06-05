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
** Diffie-Hellman-Parameters: (1024 bit)
**     prime:
**         00:d8:96:41:e9:c9:32:5c:9e:d5:a6:da:43:ee:9e:
**         83:06:43:84:1c:d6:b7:30:61:5c:4b:50:d5:50:ab:
**         d0:d4:79:1b:bf:e5:01:1a:fd:8d:d0:f0:70:4f:43:
**         64:22:19:50:0e:96:6a:52:a2:81:27:c8:eb:a0:f3:
**         54:5a:d6:a1:8b:83:c0:ee:27:7e:7c:d5:48:24:0b:
**         45:8f:3c:c4:3f:2b:fa:fb:7c:4a:ca:5d:fd:0d:13:
**         a1:29:17:8e:70:29:6c:70:6e:89:b3:2a:ae:d3:f7:
**         8a:b1:9e:45:da:74:a6:e5:66:8d:1f:07:21:84:02:
**         b9:c6:9e:f5:c8:c6:eb:4b:5b
**     generator: 2 (0x2)
*/

static const unsigned char dh1024_p[] = {
    0xD8, 0x96, 0x41, 0xE9, 0xC9, 0x32, 0x5C, 0x9E, 0xD5, 0xA6, 0xDA, 0x43,
    0xEE, 0x9E, 0x83, 0x06, 0x43, 0x84, 0x1C, 0xD6, 0xB7, 0x30, 0x61, 0x5C,
    0x4B, 0x50, 0xD5, 0x50, 0xAB, 0xD0, 0xD4, 0x79, 0x1B, 0xBF, 0xE5, 0x01,
    0x1A, 0xFD, 0x8D, 0xD0, 0xF0, 0x70, 0x4F, 0x43, 0x64, 0x22, 0x19, 0x50,
    0x0E, 0x96, 0x6A, 0x52, 0xA2, 0x81, 0x27, 0xC8, 0xEB, 0xA0, 0xF3, 0x54,
    0x5A, 0xD6, 0xA1, 0x8B, 0x83, 0xC0, 0xEE, 0x27, 0x7E, 0x7C, 0xD5, 0x48,
    0x24, 0x0B, 0x45, 0x8F, 0x3C, 0xC4, 0x3F, 0x2B, 0xFA, 0xFB, 0x7C, 0x4A,
    0xCA, 0x5D, 0xFD, 0x0D, 0x13, 0xA1, 0x29, 0x17, 0x8E, 0x70, 0x29, 0x6C,
    0x70, 0x6E, 0x89, 0xB3, 0x2A, 0xAE, 0xD3, 0xF7, 0x8A, 0xB1, 0x9E, 0x45,
    0xDA, 0x74, 0xA6, 0xE5, 0x66, 0x8D, 0x1F, 0x07, 0x21, 0x84, 0x02, 0xB9,
    0xC6, 0x9E, 0xF5, 0xC8, 0xC6, 0xEB, 0x4B, 0x5B,
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
