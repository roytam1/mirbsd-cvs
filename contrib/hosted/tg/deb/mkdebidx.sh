#!/bin/mksh
rcsid='$MirOS: contrib/hosted/tg/deb/mkdebidx.sh,v 1.25 2009/10/03 18:35:57 tg Exp $'
#-
# Copyright (c) 2008, 2009, 2010
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.

allarchs='all amd64 i386'
ourkey=0x405422DD

function putfile {
	tee $1 | gzip -n9 >$1.gz
}

export LC_ALL=C TZ=UTC
unset LANG LANGUAGE
cd "$(dirname "$0")"

suites=:
for suite in "$@"; do
	suites=:dists/$suite$suites
done

allsuites=
for suite in dists/*; do
	allsuites="$allsuites${allsuites:+ }${suite##*/}"
	[[ $suites = : || $suites = *:$suite:* ]] || continue
	archs=
	. $suite/distinfo.sh
	: ${archs:=$allarchs}
	components=Components:
	for dist in $suite/*; do
		[[ -d $dist/. ]] || continue
		components="$components ${dist##*/}"
		for arch in $archs; do
			mkdir -p $dist/binary-$arch
			print "\n===> Creating ${dist#dists/}/$arch/Packages\n"
			dpkg-scanpackages -a $arch $dist | \
			    putfile $dist/binary-$arch/Packages
		done
		mkdir -p $dist/source
		print "\n===> Creating ${dist#dists/}/Sources"
		dpkg-scansources $dist | putfile $dist/source/Sources
		print done.
	done
	print "\n===> Creating ${suite#dists/}/Release.gpg"
	(cat <<-EOF
		Origin: The MirOS Project
		Label: wtf
		Suite: ${suite##*/}
		Codename: ${suite##*/}
		Date: $(date)
		Architectures: $archs source
		$components
		Description: WTF ${nick} Repository
		MD5Sum:
	EOF
	cd $suite
	find * -name Packages\* -o -name Sources\* -o -name Release | \
	    sort | while read n; do
		set -A x -- $(md5sum $n)
		print \ ${x[0]} $(stat -c '%s %n' $n)
	done) >$suite/Release
	gpg -u $ourkey -sb $suite/Release
	mv -f $suite/Release.sig $suite/Release.gpg
done

print "\n===> Creating debidx.htm\n"

set -A preplsrc
set -A prepldst
integer nsrc=0 nbin=0 nrpl=0
br='<br />'

# syntax:	${suitename}/${distname}/${pN}/${pp} <suite>
# example:	sid/wtf/openntpd/i386 lenny
if [[ -s mkdebidx.lnk ]]; then
	while read pn pd; do
		[[ $pn = @(#)* ]] && continue
		if [[ $pn != +([a-z0-9_])/+([a-z0-9_-])/+([!/])/@(%|=|+([a-z0-9])) || \
		    $pd != +([a-z0-9_]) ]]; then
			print -u2 "Invalid lnk line '$pn' '$pd'"
			continue
		fi
		preplsrc[nrpl]=$pn
		prepldst[nrpl++]=$pd
	done <mkdebidx.lnk
fi

for suite in dists/*; do
	for dist in $suite/*; do
		[[ -d $dist/. ]] || continue
		suitename=${suite##*/}
		if [[ $suitename != +([a-z0-9_]) ]]; then
			print -u2 "Invalid suite name '$suitename'"
			continue 2
		fi
		distname=${dist##*/}
		if [[ $distname != +([a-z0-9_-]) ]]; then
			print -u2 "Invalid dist name '$distname'"
			continue
		fi

		pn=; pv=; pd=; pp=; pN=; pf=

		gzip -dc $dist/source/Sources.gz |&
		while IFS= read -pr line; do
			case $line {
			(@(Package: )*)
				pn=${line##Package:*([	 ])}
				;;
			(@(Version: )*)
				pv=${line##Version:*([	 ])}
				;;
			(@(Binary: )*)
				pd=${line##Binary:*([	 ])}
				;;
			(@(Directory: )*)
				pp=${line##Directory:*([	 ])}
				;;
			(?*)	# anything else
				;;
			(*)	# empty line
				if [[ -n $pn && -n $pv && -n $pd && -n $pp ]]; then
					i=0
					while (( i < nsrc )); do
						[[ ${sp_name[i]} = $pn && \
						    ${sp_dist[i]} = $distname ]] && break
						let i++
					done
					if (( i == nsrc )); then
						let nsrc++
						pvo=
						ppo=
					else
						eval pvo=\$\{sp_ver_${suitename}[i]\}
						eval ppo=\$\{sp_dir_${suitename}[i]\}
					fi
					sp_name[i]=$pn
					sp_dist[i]=$distname
					#sp_suites[i]="${sp_suites[i]} $suitename"
					if (( nrpl )); then
						x=${suitename}/${distname}/${pn}/source
						j=0
						while (( j < nrpl )); do
							[[ ${preplsrc[j]} = $x ]] && break
							let j++
						done
						(( j < nrpl )) && pv="${pv}from ${prepldst[j]}"
					fi
					eval sp_ver_${suitename}[i]='${pvo:+$pvo,}$pv'
					eval sp_dir_${suitename}[i]='${ppo:+$ppo,}$pp/'
					sp_desc[i]=${sp_desc[i]},$pd
				fi
				pn=; pv=; pd=; pp=
				;;
			}
		done

		gzip -dc $dist/binary-*/Packages.gz |&
		while IFS= read -pr line; do
			case $line {
			(@(Package: )*)
				pN=${line##Package:*([	 ])}
				;;
			(@(Source: )*)
				pn=${line##Source:*([	 ])}
				;;
			(@(Version: )*)
				pv=${line##Version:*([	 ])}
				;;
			(@(Description: )*)
				pd=${line##Description:*([	 ])}
				;;
			(@(Architecture: )*)
				pp=${line##Architecture:*([	 ])}
				;;
			(@(Filename: )*)
				pf=${line##Filename:*([	 ])}
				;;
			(?*)	# anything else
				;;
			(*)	# empty line
				[[ -n $pn ]] || pn=$pN
				if [[ -n $pn && -n $pv && -n $pd && -n $pp ]]; then
					i=0
					while (( i < nbin )); do
						[[ ${bp_disp[i]} = $pN && ${bp_desc[i]} = $pd && \
						    ${bp_dist[i]} = $distname ]] && break
						let i++
					done
					(( i == nbin )) && let nbin++
					bp_name[i]=$pn
					bp_disp[i]=$pN
					bp_dist[i]=$distname
					#bp_suites[i]="${bp_suites[i]} $suitename"
					if (( nrpl )); then
						x=${suitename}/${distname}/${pN}/${pp}
						j=0
						while (( j < nrpl )); do
							[[ ${preplsrc[j]} = $x ]] && break
							let j++
						done
						(( j < nrpl )) && pv="from ${prepldst[j]}"
					fi
					[[ -n $pf ]] && pv="<a href=\"$pf\">$pv</a>"
					pv="$pp: $pv"
					eval x=\${bp_ver_${suitename}[i]}
					[[ $br$x$br = *@($br$pv$br)* ]] || x=$x${x:+$br}$pv
					eval bp_ver_${suitename}[i]=\$x
					bp_desc[i]=$pd
				fi
				pn=; pv=; pd=; pp=; pN=
				;;
			}
		done
	done
done

(cat <<'EOF'
<?xml version="1.0"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
 "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"><head>
 <meta http-equiv="content-type" content="text/html; charset=utf-8" />
 <meta name="MSSmartTagsPreventParsing" content="TRUE" />
 <title>MirDebian “WTF” Repository Index</title>
 <meta name="generator" content="$MirOS: contrib/hosted/tg/deb/mkdebidx.sh,v 1.25 2009/10/03 18:35:57 tg Exp $" />
 <style type="text/css">
  table {
   border: 1px solid black;
   border-collapse: collapse;
   text-align: left;
   vertical-align: top;
  }
  tr {
   border: 1px solid black;
   text-align: left;
   vertical-align: top;
  }
  td {
   border: 1px solid black;
   text-align: left;
   vertical-align: top;
  }
  th {
   background-color: #000000;
   color: #FFFFFF;
  }
  .srcpkgline {
   background-color: #CCCCCC;
  }
 </style>
</head><body>
<h1>MirDebian “WTF” Repository</h1>
<p><a href="dists/">Browse</a> the repository or read about how to amend <a
 href="sources.txt">/etc/apt/sources.list</a> in order to use it.</p>
<h2>Suites</h2>
<ul>
EOF

allsuites=$(for suitename in $allsuites; do
	print $suitename
done | sort -u)

for suitename in $allsuites; do
	suite=dists/$suitename
	. $suite/distinfo.sh
	print -n " <li>${suite##*/}: <a href=\"$suite/\">$desc</a> (dists:"
	for dist in $suite/*; do
		[[ -d $dist/. ]] || continue
		distname=${dist##*/}
		print -n " <a href=\"$suite/$distname/\">$distname</a>"
	done
	print ")</li>"
done
print "</ul>"
print "<h2>Packages</h2>"
print "<table width=\"100%\"><thead>"
print "<tr class=\"tablehead\">"
print " <th>package name</th>"
print " <th>dist</th>"
print " <th>description</th>"
for suitename in $allsuites; do
	print " <th>$suitename</th>"
done
print "</tr></thead><tbody>"

set -A bp_sort
i=0
while (( i < nbin )); do
	print $i ${bp_disp[i++]} #${bp_suites[i]}
done | sort -k2 |&
while read -p num rest; do
	bp_sort[${#bp_sort[*]}]=$num
done

i=0
while (( i < nsrc )); do
	print $i ${sp_name[i++]}
done | sort -k2 |&
while read -p num rest; do
	print "\n<!-- sp #$num = ${sp_name[num]} -->"
	print "<tr class=\"srcpkgline\">"
	print " <td class=\"srcpkgname\">${sp_name[num]}</td>"
	print " <td class=\"srcpkgdist\">${sp_dist[num]}</td>"
	pd=
	for x in $(tr ', ' '\n' <<<"${sp_desc[num]}" | sort -u); do
		[[ -n $x ]] && pd="$pd, $x"
	done
	print " <td class=\"srcpkgdesc\">Binary:${pd#,}</td>"
	for suitename in $allsuites; do
		eval pvo=\${sp_ver_${suitename}[num]}
		eval ppo=\${sp_dir_${suitename}[num]}
		saveIFS=$IFS
		IFS=,
		set -A pva -- $pvo
		set -A ppa -- $ppo
		IFS=$saveIFS
		(( ${#pva[*]} )) || pva[0]=
		y=
		i=0
		while (( i < ${#pva[*]} )); do
			pv=${pva[i]}
			pp=${ppa[i]}
			if [[ $pv = *@()* ]]; then
				pvdsc=${pv%%@()*}
				pv=${pv##*@()}
			else
				pvdsc=$pv
			fi
			if [[ -z $pv ]]; then
				pv=-
				if (( nrpl )); then
					x=${suitename}/${sp_dist[num]}/${sp_name[num]}/%
					j=0
					while (( j < nrpl )); do
						[[ ${preplsrc[j]} = $x ]] && break
						let j++
					done
					(( j < nrpl )) && pv=${prepldst[j]}
				fi
			elif [[ $pp != ?(/) ]]; then
				pv="<a href=\"$pp${sp_name[num]}_${pvdsc##+([0-9]):}.dsc\">$pv</a>"
			fi
			[[ $pp != ?(/) ]] && pv="<a href=\"$pp\">[dir]</a> $pv"
			y=${y:+"$y<br />"}$pv
			let i++
		done
		print " <td class=\"srcpkgitem\">$y</td>"
	done
	print "</tr>"
	k=0
	while (( k < nbin )); do
		(( (i = bp_sort[k++]) < 0 )) && continue
		[[ ${bp_name[i]} = ${sp_name[num]} && \
		    ${bp_dist[i]} = ${sp_dist[num]} ]] || continue
		bp_sort[k - 1]=-1
		#print "<!-- bp #$i for${bp_suites[i]} -->"
		print "<!-- bp #$i -->"
		print "<tr class=\"binpkgline\">"
		print " <td class=\"binpkgname\">${bp_disp[i]}</td>"
		print " <td class=\"binpkgdesc\" colspan=\"2\">${bp_desc[i]}</td>"
		for suitename in $allsuites; do
			eval pv=\${bp_ver_${suitename}[i]}
			if [[ -z $pv ]]; then
				pv=-
				if (( nrpl )); then
					x=${suitename}/${sp_dist[num]}/${sp_name[num]}/%
					j=0
					while (( j < nrpl )); do
						[[ ${preplsrc[j]} = $x ]] && break
						let j++
					done
					(( j < nrpl )) && pv=${prepldst[j]}
				fi
			fi
			print " <td class=\"binpkgitem\">$pv</td>"
		done
		print "</tr>"
	done
done

num=0
for i in ${bp_sort[*]}; do
	(( i < 0 )) && continue
	if (( !num )); then
		print "\n<!-- sp ENOENT -->"
		print "<tr class=\"srcpkgline\">"
		print " <td class=\"srcpkgname\">~ENOENT~</td>"
		print " <td class=\"srcpkgdesc\" colspan=\"2\">binary" \
		    "packages without a matching source package</td>"
		for suitename in $allsuites; do
			print " <td class=\"srcpkgitem\">-</td>"
		done
		print "</tr>"
		num=1
	fi
	#print "<!-- bp #$i for${bp_suites[i]} -->"
	print "<!-- bp #$i -->"
	print "<tr class=\"binpkgline\">"
	print " <td class=\"binpkgname\">${bp_disp[i]}</td>"
	print " <td class=\"binpkgdist\">${bp_dist[i]}</td>"
	print " <td class=\"binpkgdesc\">${bp_desc[i]}</td>"
	for suitename in $allsuites; do
		eval pv=\${bp_ver_${suitename}[i]}
		if [[ -z $pv ]]; then
			pv=-
			if (( nrpl )); then
				x=${suitename}/${bp_dist[num]}/${bp_disp[num]}/=
				j=0
				while (( j < nrpl )); do
					[[ ${preplsrc[j]} = $x ]] && break
					let j++
				done
				(( j < nrpl )) && pv=${prepldst[j]}
			fi
		fi
		print " <td class=\"binpkgitem\">$pv</td>"
	done
	print "</tr>"
done

cat <<EOF

</tbody></table>

<p>• <a href="http://validator.w3.org/check/referer">Valid XHTML/1.1!</a>
 • <small>Generated on $(date +'%F %T') by <tt
 style="white-space:pre;">$rcsid</tt></small> •</p>
</body></html>
EOF

:) >debidx.htm
print done.
