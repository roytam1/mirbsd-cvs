# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.43 2007/04/23 12:22:20 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20070430
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=e32d0b865386ae4a49206a726b8718ed
	distinfo_sum=3351559557
	distinfo_size=334017
	distinfo_date="Apr 30 12:52"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=29c
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=183957bfcbf7ca212843d6ca85be2fce
	distinfo_sum=3771424446
	distinfo_size=240022
	distinfo_date="Apr 23 11:45"
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
	f_ver=20070430
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=d08dc5cf10e7b78d9b5c1e5f7022f737
	distinfo_sum=1491877663
	distinfo_size=112055
	distinfo_date="Apr 30 12:53"
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
