# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.8 2005/11/10 13:21:42 tg Exp $

case $what in
make)
	f_dist=mirmake-20051110.cpio.gz
	f_path=mir/make
	distinfo_md5=9a01674148cef91365df230d3823f692
	distinfo_sum=295657392
	distinfo_size=313393
	distinfo_date="Nov 10 13:01"
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
