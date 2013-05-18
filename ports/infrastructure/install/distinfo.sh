# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.22 2006/06/23 15:16:05 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20060623
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=615fda6f18c5aa15585ada2eec0d4ed4
	distinfo_sum=2612686355
	distinfo_size=313405
	distinfo_date="Jun 23 15:23"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=27d
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=c35648b7e8842e8d9012570b3f148189
	distinfo_sum=1647130257
	distinfo_size=229667
	distinfo_date="Jun 23 15:09"
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
