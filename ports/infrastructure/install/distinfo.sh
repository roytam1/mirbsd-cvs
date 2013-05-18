# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.20 2006/05/26 23:44:17 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20060527
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=70ab093586bc500c2f8aa43e9429cb4b
	distinfo_sum=2863654567
	distinfo_size=313202
	distinfo_date="May 27 19:34"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=27c
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=d8bad9d412f6b6b1e36123a09103bed9
	distinfo_sum=453299949
	distinfo_size=229579
	distinfo_date="May 27 20:34"
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
