# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.97 2009/12/26 16:12:08 tg Exp $

case $what in
make)
	f_key=gzsigkey.pub
	f_ver=20100110
	f_dist=mirmake-$f_ver.cpio.gz
	f_path=mir/make
	distinfo_md5=2f64ac79c22d0524d777580153151460
	distinfo_sum=3315356924
	distinfo_size=383713
	distinfo_date="Jan 10 13:36"
	;;
mksh)
	f_key=gzsigkey.pub
	f_ver=39
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=b2eeb4fe4ccac2704e1440e53cd2672c
	distinfo_sum=4103085544
	distinfo_size=278476
	distinfo_date="Aug  2 10:09"
	;;
mtree)
	f_key=gzsigkey.pub
	f_ver=20091122
	f_dist=mirmtree-$f_ver.cpio.gz
	f_path=mir/mtree
	distinfo_md5=2af647aa0564064434e4eedd475e705e
	distinfo_sum=926768756
	distinfo_size=19523
	distinfo_date="Nov 22 20:48"
	;;
nroff)
	f_key=gzsigkey.pub
	f_ver=20091122
	f_dist=mirnroff-$f_ver.cpio.gz
	f_path=mir/nroff
	distinfo_md5=288945978e5612ad6d900b0e29fdf8db
	distinfo_sum=2278748484
	distinfo_size=237087
	distinfo_date="Nov 22 20:49"
	;;
pkgtools)
	f_key=
	f_ver=20091226
	f_dist=pkgtools-$f_ver.mcz
	f_path=mir/pkgtools
	distinfo_md5=b3f6ea641503f641c7e3248bfd9592d3
	distinfo_sum=2704938110
	distinfo_size=189081
	distinfo_date="Dec 26 16:05"
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
