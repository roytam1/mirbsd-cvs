#!/bin/mksh
# $MirOS: src/usr.bin/fdialog/tests/runTest.sh,v 1.1.7.1 2005/03/06 16:52:42 tg Exp $
# $ekkoBSD: runTest.sh,v 1.3 2004/02/18 19:45:40 dave Exp $

FDIALOG=${FDIALOG:=fdialog} export FDIALOG
OUT=$(mktemp /tmp/fdialog_test.XXXXXXXXXX) || exit 1
LOG=logfile

TEST=$1

if [ "${TEST}" = "" ] ; then
	echo "No test specified."
	exit 2
fi

if [ ! -s "${TEST}" ] ; then
	echo "No test found called ${TEST}"
	exit 1
fi

/bin/mksh ${TEST} 3> ${OUT} 2>&3

if [ $? -ne 0 ] ; then
	echo "=======" >> ${LOG}
	echo "${TEST} failed, it said:" >> ${LOG}
	cat ${OUT} >> ${LOG}
	echo "=======" >> ${LOG}
else
	cat ${OUT} && rm -f ${OUT}
fi
