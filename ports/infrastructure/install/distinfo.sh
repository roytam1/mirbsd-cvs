# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.54 2007/07/10 20:48:16 tg Exp $

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
	f_ver=30
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=184a63aa5b1450581dc463148f3d245e
	distinfo_sum=1122404631
	distinfo_size=245700
	distinfo_date="Jul 26 19:21"
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
	f_ver=20070726
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=63fa10ca9281e624394a975f0be58b93
	distinfo_sum=2273439363
	distinfo_size=112685
	distinfo_date="Jul 26 11:02"
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
