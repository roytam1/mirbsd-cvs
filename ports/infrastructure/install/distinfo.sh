# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.50 2007/05/26 22:38:27 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20070626
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=11327c85e3ca13d541553c777a0d7481
	distinfo_sum=3853713572
	distinfo_size=359299
	distinfo_date="Jun 26 19:10"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=29f
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=83b4ca84faa1a1ea4cf6db6eb41a0384
	distinfo_sum=2910491928
	distinfo_size=240805
	distinfo_date="May 26 22:34"
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
	f_ver=20070517
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=29faa4654d185f04c62b7726bac67b2b
	distinfo_sum=2194673558
	distinfo_size=112553
	distinfo_date="May 17 01:18"
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
