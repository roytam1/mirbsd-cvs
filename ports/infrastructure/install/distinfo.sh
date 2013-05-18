# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.31 2006/12/28 00:22:18 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20061228
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=4fecfd81e9c0a256da3f19a74e5f70a3
	distinfo_sum=1888263115
	distinfo_size=333487
	distinfo_date="Dec 28 02:17"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=28
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=1869f79961c365c65116974706a56c67
	distinfo_sum=3110135037
	distinfo_size=230291
	distinfo_date="Sep  1 23:15"
	;;
mtree)
	f_key=signkey
	f_ver=20050912
	f_dist=mirmtree-$f_ver.cpio.gz
	f_path=mir/mtree
	distinfo_md5=86cf94a633f136d650f76d065bbd7e0e
	distinfo_sum=3117223138
	distinfo_size=17999
	distinfo_date="Sep 12 19:19"
	;;
nroff)
	f_key=signkey
	f_ver=20050912
	f_dist=mirnroff-$f_ver.cpio.gz
	f_path=mir/nroff
	distinfo_md5=c9336d68a54a1965e37fcf4dab19cba3
	distinfo_sum=1195567255
	distinfo_size=224960
	distinfo_date="Sep 12 19:34"
	;;
pkgtools)
	f_key=none
	f_ver=20061228
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=a5204f4e071907e6809ac132bbb3d7f5
	distinfo_sum=1002938415
	distinfo_size=108978
	distinfo_date="Dec 28 00:15"
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
