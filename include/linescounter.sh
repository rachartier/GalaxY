#!/bin/bash
res=0

IFS="
"

for f in `find . ! -type d`;
do
let " res += `wc -l $f | awk '{print $1}'`  "
done
echo $res
