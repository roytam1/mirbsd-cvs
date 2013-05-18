# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.16 2006/01/27 11:32:45 tg Exp $

case $what in
make)
	f_ver=20051230
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=abda4474f437d8054e637ac5ee4b5c2b
	distinfo_sum=2103851589
	distinfo_size=312541
	distinfo_date="Dec 30 00:19"
	;;
mksh)
	f_ver=26c
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=b2fcc52314b07b31d4b4452da5f6ffc8
	distinfo_sum=549554166
	distinfo_size=228360
	distinfo_date="Jan 30 11:52"
	;;
mtree)
	f_ver=20050912
	f_dist=mirmtree-$f_ver.cpio.gz
	f_path=mir/mtree
	distinfo_md5=86cf94a633f136d650f76d065bbd7e0e
	distinfo_sum=3117223138
	distinfo_size=17999
	distinfo_date="Sep 12 19:19"
	;;
nroff)
	f_ver=20050912
	f_dist=mirnroff-$f_ver.cpio.gz
	f_path=mir/nroff
	distinfo_md5=c9336d68a54a1965e37fcf4dab19cba3
	distinfo_sum=1195567255
	distinfo_size=224960
	distinfo_date="Sep 12 19:34"
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
