#!bin/bash
#First you can use grep (-n) to find the number of lines of string.
#Then you can use awk to separate the answer

in=$1
s=$2
out=$3

grep -n $s $in | cut -d: -f1 > $out
#awk '/$s/{print FNR}' $in > $out

