#!/bin/bash

EXPECTED=($(md5sum ./rhasher.c))
GOT=($(echo "MD5 rhasher.c" | ./rhasher))

RED='\033[0;31m'
GREEN='\033[0;32m'
NO_COL='\033[0;37m'

EXIT_CODE=0

EXPECTED=($(md5sum ./rhasher.c))
GOT=($(echo "MD5 rhasher.c" | ./rhasher))
if [[ ${EXPECTED[0]} != ${GOT[1]} ]];
then
    echo -e "${RED}md5 hash test failed"
    EXIT_CODE=1
else
    echo -e "${GREEN}md5 hash test passed"
fi

EXPECTED=($(sha1sum ./rhasher.c))
GOT=($(echo "SHA1 rhasher.c" | ./rhasher))
if [[ ${EXPECTED[0]} != ${GOT[1]} ]];
then
    echo -e "${RED}sha1 hash test failed"
    EXIT_CODE=1
else
    echo -e "${GREEN}sha1 hash test passed"
fi
echo -e -n "${NO_COL}"

exit $EXIT_CODE
