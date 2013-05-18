# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.68 2008/03/14 16:17:36 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20080314
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=d19b5c1eecf2d401ebf7fae9b5718faa
	distinfo_sum=3651682254
	distinfo_size=366667
	distinfo_date="Mar 14 17:11"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=33
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=dbe6561bf94c4a85f92aecc22fe2c8b9
	distinfo_sum=507273168
	distinfo_size=252600
	distinfo_date="Mar  2 06:16"
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
	f_ver=20080314
	f_dist=pkgtools-$f_ver.cgz
	f_path=mir/pkgtools
	distinfo_md5=9c8e443a06cfd6d94fa6204a9821346e
	distinfo_sum=4223936452
	distinfo_size=114573
	distinfo_date="Mar 14 17:11"
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
