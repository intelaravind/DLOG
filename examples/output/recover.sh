#!/bin/bash
#Author Aravind

if [ "$DLOG_PATH" = "" ]; then
    echo "DLOG_PATH not found. Please export the path"
    exit
fi

search_dir=`pwd`
#echo $search_dir
for entry in "$search_dir"/*.tag
do
#  echo "${entry%.*}"
$DLOG_PATH/DLOG_FINALIZER.out ${entry%.*}
done




