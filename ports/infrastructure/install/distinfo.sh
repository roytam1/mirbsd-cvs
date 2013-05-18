# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.13 2005/12/20 19:57:53 tg Exp $

case $what in
make)
	f_ver=20051220
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=9292cb3afdd722ab675ca28d93073f21
	distinfo_sum=3435254991
	distinfo_size=312523
	distinfo_date="Dec 20 19:18"
	;;
mksh)
	f_ver=26
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=5493dce94a914f6ecc5b797c617b603f
	distinfo_sum=2644744404
	distinfo_size=228407
	distinfo_date="Nov 24 19:46"
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
