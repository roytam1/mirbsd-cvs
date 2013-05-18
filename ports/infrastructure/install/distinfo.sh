# $MirOS: ports/infrastructure/install/distinfo.sh,v 1.79 2008/11/29 12:15:47 tg Exp $

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
	f_ver=36b
	f_dist=mksh-R$f_ver.cpio.gz
	f_path=mir/mksh
	distinfo_md5=e5f4cfbc55b6fe8211f99d231125224d
	distinfo_sum=1799491822
	distinfo_size=264821
	distinfo_date="Dec 13 21:32"
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
	f_ver=20081129
	f_dist=pkgtools-$f_ver.mcz
	f_path=mir/pkgtools
	distinfo_md5=54805824bc12d990ed7db0898a4d953e
	distinfo_sum=2014336416
	distinfo_size=180140
	distinfo_date="Nov 29 12:10"
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
