# $MirOS$

case $what in
mksh)
	f_dist=mksh-R24c.cpio.gz
	f_path=mir/mksh/$f_dist
	distinfo_md5=7b7b7afb595da75d27b2f08655320600
	distinfo_sum=2460615772
	distinfo_size=224603
	distinfo_date="Sep 12 19:29"
	;;
*)
	echo Do not call me directly. >&2
	exit 1
	;;
esac
f_md5="MD5 ($f_dist) = $distinfo_md5"
f_sum="$distinfo_sum $distinfo_size $f_dist"
f_md5sum="$distinfo_md5  $f_dist"
f_lsline=": -r--r--r--  1 tg  miros-cvsall  $distinfo_size $distinfo_date $f_dist"
