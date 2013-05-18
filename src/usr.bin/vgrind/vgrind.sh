#!/bin/mksh
# $MirOS: src/usr.bin/vgrind/vgrind.sh,v 1.5 2005/05/14 14:52:52 tg Exp $
#-
# Copyright (c) 2005 Thorsten Glaser <tg@mirbsd.org>
# Copyright (c) 2005 Han Boetes <han@mijncomputer.nl>
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

# Allow troff to be overridden
TROFF=${TROFF:=troff}

name=${0##*/}
vf=/usr/libexec/vfontedpr
tm=/usr/share/tmac

unset voptions options files f head

while [ $# -gt 0 ]; do
	case $1 {
	-f)
		f=filter
		options="$options $1"
		;;
	-t)
		voptions="$voptions -t"
		;;
	-o*)
		voptions="$voptions $1"
		;;
	-W)
		voptions="$voptions -W"
		;;
	-d)
		if [[ -z $2 ]]; then
			print -u2 "$name: -d option must have argument"
			exit 1
		fi
		options="$options $1 $2"
		shift
		;;
	-h)
		if [[ -z $2 ]]; then
			print -u2 "$name: -h option must have argument"
			exit 1
		fi
		head="$2"
		shift
		;;
	-*)
		options="$options $1"
		;;
	*)
		files="$files $1"
		;;
	esac
	shift
done

if [ -r index ]; then
	print >nindex
	for i in $files; do
		# make up a sed delete command for filenames
		# being careful about slashes.
		print "? $i ?d" | sed -e "s:/:\\/:g" -e "s:?:/:g" >>nindex
	done
	sed -f nindex index >xindex
	if [[ $f = filter ]]; then
		if [[ -n $head ]]; then
			$vf $options -h "$head" $files
		else
			$vf $options $files
		fi | cat $tm/tmac.vgrind -
	else
		if [[ -n $head ]]; then
			$vf $options -h "$head" $files
		else
			$vf $options $files
		fi | $TROFF -rx1 $voptions -i -mvgrind 2>>xindex
	fi
	sort -df +0 -2 xindex >index
	rm {n,x}index
elif [[ $f = filter ]]; then
	if [[ -n $head ]]; then
		$vf $options -h "$head" $files
	else
		$vf $options $files
	fi | cat $tm/tmac.vgrind -
else
	if [[ -n $head ]]; then
		$vf $options -h "$head" $files
	else
		$vf $options $files
	fi | $TROFF -i $voptions -mvgrind
fi
