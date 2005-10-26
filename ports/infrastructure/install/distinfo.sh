# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.6 2005/10/25 21:27:23 tg Exp $

case $what in
cksum)
	f_dist=mircksum-20050912.cpio.gz
	f_path=mir/cksum
	distinfo_md5=c072abe84ab399ef2fba8a8e505154fc
	distinfo_sum=3300899251
	distinfo_size=14479
	distinfo_date="Sep 12 19:06"
	;;
cpio)
	f_dist=paxmirabilis-20050912.cpio.gz
	f_path=mir/cpio
	distinfo_md5=3ebf552572a9f561f8590ef3f44b8740
	distinfo_sum=1040864534
	distinfo_size=118793
	distinfo_date="Sep 12 19:09"
	;;
make)
	f_dist=mirmake-20051021.cpio.gz
	f_path=mir/make
	distinfo_md5=4e094f84e82ddb46d8c70a398c356565
	distinfo_sum=2281267503
	distinfo_size=313308
	distinfo_date="Oct 21 20:02"
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
sort)
	f_dist=mirsort-20050912.cpio.gz
	f_path=mir/sort
	distinfo_md5=409a55b90312b306024f9e22e32e06a6
	distinfo_sum=108354838
	distinfo_size=21356
	distinfo_date="Sep 12 19:36"
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
