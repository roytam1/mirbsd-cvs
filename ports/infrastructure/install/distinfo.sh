# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.9 2005/11/16 15:57:04 tg Exp $

case $what in
make)
	f_dist=mirmake-20051116.cpio.gz
	f_path=mir/make
	distinfo_md5=07b2a31b818d7d2202d3584f1f8bf18d
	distinfo_sum=3911444794
	distinfo_size=313526
	distinfo_date="Nov 16 17:15"
	;;
mksh)
	f_dist=mksh-R25.cpio.gz
	f_path=mir/mksh
	distinfo_md5=ec9095ee279225fed82523044803bc32
	distinfo_sum=4110975346
	distinfo_size=228743
	distinfo_date="Oct 26 08:56"
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
