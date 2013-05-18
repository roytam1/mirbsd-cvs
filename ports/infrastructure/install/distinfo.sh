# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.38 2007/03/08 11:01:47 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20061228
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=59ddd32dc839f29ac837f5a066a48177
	distinfo_sum=1219540297
	distinfo_size=333485
	distinfo_date="Dec 28 04:07"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=29b
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=a21850403bd30bab461f2fc9f9b803b8
	distinfo_sum=1632152196
	distinfo_size=238113
	distinfo_date="Mar 10 21:42"
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
	f_ver=20070308
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=b454b014530bff0f56144783d00fdb52
	distinfo_sum=2290738921
	distinfo_size=111009
	distinfo_date="Mar  8 10:56"
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
