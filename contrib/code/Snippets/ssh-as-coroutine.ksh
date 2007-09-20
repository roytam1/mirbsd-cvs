#!/bin/mksh
# $MirOS$

ssh -T tglaser@unixforge.de 'mksh 2>&1' |&
print -p 'print @MARKER@'
while IFS= read -pr line; do
	[[ $line = @MARKER@ ]] && break
	print -r "| $line"
done
print -p 'ls; print @MARKER@'
print ==================================================================
while IFS= read -pr line; do
	[[ $line = @MARKER@ ]] && break
	print -r "| $line"
done
print -p 'ls CVS; print @MARKER@'
print ==================================================================
while IFS= read -pr line; do
	[[ $line = @MARKER@ ]] && break
	print -r "| $line"
done
print -p 'ls cvs; print @MARKER@'
print ==================================================================
while IFS= read -pr line; do
	[[ $line = @MARKER@ ]] && break
	print -r "| $line"
done
print -p exit
print ==================================================================
while IFS= read -pr line; do
	print -r "| $line"
done
print ==================================================================
jobs
exit 0
