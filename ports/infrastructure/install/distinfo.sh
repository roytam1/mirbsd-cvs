# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.74 2008/07/11 11:22:16 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20080411
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=37977f171c81672af1de0c8f2d1bc9a1
	distinfo_sum=2958711126
	distinfo_size=371230
	distinfo_date="Apr 11 20:24"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=35b
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=0e96cd3f8141b7abc679bbb303a8be2c
	distinfo_sum=4126823992
	distinfo_size=263452
	distinfo_date="Jul 18 13:49"
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
	f_ver=20080411
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=fb65931966308e9f3edede1d9a21d625
	distinfo_sum=2720463249
	distinfo_size=115888
	distinfo_date="Apr 11 20:25"
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
