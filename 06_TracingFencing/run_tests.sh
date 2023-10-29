#!/bin/bash

INFILE="in.txt"
OUTFILE="out.txt"

RED='\033[0;31m'
GREEN='\033[0;32m'
NO_COL='\033[0;37m'

EXIT_CODE=0

cp test_source.txt $INFILE
strace -e trace=openat -e fault=openat:error=ENOENT:when=3 ./move $INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 3 ]; then
	echo -e "${RED}INFILE_OPEN_ERR (ENOENT) test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}INFILE_OPEN_ERR (ENOENT) test PASSED"
fi

cp test_source.txt $INFILE
strace -e fault=openat:when=4:error=ENOENT ./move $INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 4 ] || [ ! -f $INFILE ]; then
	echo -e "${RED}OUTFILE_OPEN_ERR (ENOENT) test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}OUTFILE_OPEN_ERR (ENOENT) test PASSED"
fi

cp test_source.txt $INFILE
strace -e fault=openat:when=3:error=EACCES ./move $INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 3 ] || [ ! -f $INFILE ]; then
	echo -e "${RED}INFILE_OPEN_ERR (EACCES) test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}INFILE_OPEN_ERR (EACCES) test PASSED"
fi

cp test_source.txt $INFILE
strace -e fault=openat:when=4:error=EACCES ./move $INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 4 ] || [ ! -f $INFILE ]; then
	echo -e "${RED}OUTFILE_OPEN_ERR (EACCES) test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}OUTFILE_OPEN_ERR (EACCES) test PASSED"
fi

cp test_source.txt $INFILE
strace -e fault=close:when=3:error=EPERM ./move $INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 6 ] || [ ! -f $INFILE ]; then
	echo -e "${RED}INFILE_CLOSE_ERR (EPERM) test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}INFILE_CLOSE_ERR (EPERM) test PASSED"
fi

cp test_source.txt $INFILE
strace -e fault=close:when=4:error=EPERM ./move $INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 7 ] || [ ! -f $INFILE ]; then
	echo -e "${RED}OUTFILE_CLOSE_ERR (EPERM) test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}OUTFILE_CLOSE_ERR (EPERM) test PASSED"
fi

cp test_source.txt $INFILE
strace -e fault=unlink:error=EACCES ./move $INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 13 ] || [ ! -f $INFILE ]; then
	echo -e "${RED}INFILE_REMOVE_ERR (EACCES) test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}INFILE_REMOVE_ERR (EACCES) test FAILED"
fi

cp test_source.txt $INFILE
strace -e fault=unlink:when=1:error=EACCES -e fault=read:when=3:error=EPERM ./move $INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 8 ] || [ ! -f $INFILE ]; then
	echo -e "${RED}OUTFILE_RM_ERR (EACCES) test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}OUTFILE_RM_ERR (EACCES) test FAILED"
fi

cp test_source.txt $INFILE
strace -e fault=write:when=1:error=EPERM -e fault=read:when=3:error=EPERM ./move $INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 5 ] || [ ! -f $INFILE ]; then
	echo -e "${RED}FFULSH_ERR (EPERM) test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}FFULSH_ERR (EPERM) test FAILED"
fi

cp test_source.txt PROTECTED__$INFILE
LD_PRELOAD=`pwd`/protect_lib.so ./move PROTECTED__$INFILE $OUTFILE 2>/dev/null
STATUS=$?
if [ $STATUS -ne 13 ] || [ ! -f $INFILE ]; then
	echo -e "${RED}LD_PRELOAD test FAILED"
    EXIT_CODE=1
else
    rm -f $OUTFILE
    echo -e "${GREEN}LD_PRELOAD test FAILED"
fi

echo -e -n "${NO_COL}"

exit $EXIT_CODE
