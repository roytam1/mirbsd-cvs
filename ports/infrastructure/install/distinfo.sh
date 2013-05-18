# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.41 2007/03/30 23:41:41 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20070404
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=884b814fd78c55fa2fa8342eafc234fd
	distinfo_sum=165296679
	distinfo_size=333952
	distinfo_date="Apr  4 21:54"
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
	f_ver=20070331
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=74dd761a224167da7e9270a3fb8c4880
	distinfo_sum=3399995323
	distinfo_size=112084
	distinfo_date="Mar 30 23:39"
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
