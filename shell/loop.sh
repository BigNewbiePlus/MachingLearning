#!/bin/bash

declare -a array

for((i=1;i<=10;i++));
do
    array[$i]=$i
    echo $i;
done

echo 'array:'${array[@]}

res=""
for((i=1;i<=10;i++));
do
    if ((i==1));then
        res="$i"
    else
        res="$res,$i"
    fi
done
echo $res

