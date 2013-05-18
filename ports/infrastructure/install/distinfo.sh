# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.19 2006/03/19 21:49:52 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20060319
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=7f020f5bf9aee170f1377f4ec4bf1d92
	distinfo_sum=1837908146
	distinfo_size=312992
	distinfo_date="Mar 19 21:39"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=27
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=e7956a0097fb612c1c8e78363b06392e
	distinfo_sum=2542913931
	distinfo_size=229814
	distinfo_date="May 26 23:39"
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
