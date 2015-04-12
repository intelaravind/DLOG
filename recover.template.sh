#!/bin/bash
#Author Aravind

SRC_PATH="autoconf will replace me"

search_dir=`pwd`
#echo $search_dir
for entry in "$search_dir"/*.tag
do
#  echo "${entry%.*}"
$SRC_PATH/DLOG_FINALIZER ${entry%.*}
done




