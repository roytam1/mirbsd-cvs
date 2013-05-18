# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.59 2007/10/03 17:49:15 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20070702
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=13b428c7d9501fe95bb270b0cca47d9b
	distinfo_sum=1284334785
	distinfo_size=359315
	distinfo_date="Jul  2 14:46"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=31d
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=a7c77428bd2b887c1583095a00c84aac
	distinfo_sum=2627854612
	distinfo_size=249234
	distinfo_date="Oct 15 00:42"
	;;
mtree)
	f_key=signkey
	f_ver=20050912
	f_dist=mirmtree-$f_ver.cpio.gz
	f_path=mir/mtree
	distinfo_md5=86cf94a633f136d650f76d065bbd7e0e
	distinfo_sum=3117223138
	distinfo_size=17999
	distinfo_date="Sep 12  2005"
	;;
nroff)
	f_key=signkey
	f_ver=20050912
	f_dist=mirnroff-$f_ver.cpio.gz
	f_path=mir/nroff
	distinfo_md5=c9336d68a54a1965e37fcf4dab19cba3
	distinfo_sum=1195567255
	distinfo_size=224960
	distinfo_date="Sep 12  2005"
	;;
pkgtools)
	f_key=gzsigkey.pub
	f_ver=20071003
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=805862591198fa909c9bdcc7c7f38b6c
	distinfo_sum=3099951929
	distinfo_size=112517
	distinfo_date="Oct  3 17:47"
	;;
*)
	echo Do not call me directly. >&2
	exit 1
	;;
esac
f_path=$f_path/$f_dist
f_md5="MD5 ($f_dist) = $distinfo_md5"
f_sum="$distinfo_sum $distinfo_size $f_dist"
f_md5sum="$distinfo_md5  $f_dist"
f_lsline=": -r--r--r--  1 tg  miros-cvsall  $distinfo_size $distinfo_date $f_dist"
