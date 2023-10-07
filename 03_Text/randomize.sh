#!/bin/bash

if [ -z $1 ]; then
    echo "Usage: ./randomize.sh DELAY"
    exit 1
else
    DELAY=$1
fi


TEXT=()
clear

LINE_NUM=0

while IFS= read -r LINE; do
    LEN=${#LINE}
    for (( OFFSET=0 ; OFFSET<$LEN ; OFFSET++)); do
        TEXT+=("$OFFSET^$LINE_NUM^${LINE:OFFSET:1}")
    done
    LINE_NUM=$((LINE_NUM+1))
done

TEXT=($(shuf -e "${TEXT[@]}"))

for LINE in ${TEXT[@]}; do
    readarray -d "^" -t ELEM <<< $LINE
    tput cup ${ELEM[1]} ${ELEM[0]}
    # process case if we have "^" dilimeter in text
    if [[ ${#ELEM[@]} -eq 4 ]]; then
        echo -n "^"
    else
        echo -n ${ELEM[2]}
    fi
    sleep $DELAY
done
tput cup $LINE_NUM 0
