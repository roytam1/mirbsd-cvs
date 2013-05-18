# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.87 2009/05/31 19:00:33 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20081229
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=31cbbd75b90974e24a0b322509f48604
	distinfo_sum=46001797
	distinfo_size=371897
	distinfo_date="Dec 29 22:44"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=38c
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=692192a6468b5f5c5e559756f1851766
	distinfo_sum=860103691
	distinfo_size=276630
	distinfo_date="Jun 10 19:41"
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
	f_key=
	f_ver=20081229
	f_dist=pkgtools-$f_ver.mcz
	f_path=mir/pkgtools
	distinfo_md5=b3ccac71d4a1d81507dad3b7447617ec
	distinfo_sum=1152825409
	distinfo_size=180154
	distinfo_date="Dec 29 19:50"
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
