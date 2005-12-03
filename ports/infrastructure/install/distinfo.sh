# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.10 2005/11/16 17:17:48 tg Exp $

case $what in
make)
	f_dist=mirmake-20051124.cpio.gz
	f_path=mir/make
	distinfo_md5=238f4d5ef5489a8067836fc196356fdb
	distinfo_sum=3292272645
	distinfo_size=312753
	distinfo_date="Nov 24 21:39"
	;;
mksh)
	f_dist=mksh-R26.cpio.gz
	f_path=mir/mksh
	distinfo_md5=5493dce94a914f6ecc5b797c617b603f
	distinfo_sum=2644744404
	distinfo_size=228407
	distinfo_date="Nov 24 19:46"
	;;
mtree)
	f_dist=mirmtree-20050912.cpio.gz
	f_path=mir/mtree
	distinfo_md5=86cf94a633f136d650f76d065bbd7e0e
	distinfo_sum=3117223138
	distinfo_size=17999
	distinfo_date="Sep 12 19:19"
	;;
nroff)
	f_dist=mirnroff-20050912.cpio.gz
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
