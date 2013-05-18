# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.89 2009/06/22 10:05:27 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20090801
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=47c63503210054d86db80040474f1f71
	distinfo_sum=788720631
	distinfo_size=372063
	distinfo_date="Aug  1 18:46"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=39
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=b2eeb4fe4ccac2704e1440e53cd2672c
	distinfo_sum=4103085544
	distinfo_size=278476
	distinfo_date="Aug  2 10:09"
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
	f_key=
	f_ver=20090801
	f_dist=pkgtools-$f_ver.mcz
	f_path=mir/pkgtools
	distinfo_md5=87378c95bde1c219d4a09e6bb8ccb897
	distinfo_sum=2864495035
	distinfo_size=180188
	distinfo_date="Aug  1 18:40"
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
