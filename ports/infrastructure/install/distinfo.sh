# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.75 2008/07/18 13:52:02 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20081013
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=339e0e3c86c6cbb75c117f67441d4a92
	distinfo_sum=1340365595
	distinfo_size=371439
	distinfo_date="Oct 13 20:36"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=35b
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=0e96cd3f8141b7abc679bbb303a8be2c
	distinfo_sum=4126823992
	distinfo_size=263452
	distinfo_date="Jul 18 13:49"
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
	f_ver=20081012
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=301873c249ea50113de4e186f10d8e70
	distinfo_sum=3007122026
	distinfo_size=117677
	distinfo_date="Oct 12 18:52"
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
