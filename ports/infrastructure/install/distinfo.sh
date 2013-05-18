# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.28 2006/10/13 17:25:59 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20061013
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=d6b22513a9973242e2ef5e5458a82c10
	distinfo_sum=3949920323
	distinfo_size=332040
	distinfo_date="Oct 13 16:50"
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
	f_ver=200611081800
	f_dist=pkgtools-$f_ver.mcz
	f_path=mir/pkgtools
	distinfo_md5=b137cbc09844ff77d0ff0184fed6bc97
	distinfo_sum=1465738689
	distinfo_size=160115
	distinfo_date="Nov  8 18:01"
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
