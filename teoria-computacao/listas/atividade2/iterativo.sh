#!/bin/bash
c=0
i=$1

while [ $i -gt 0 ] 
do 
   i=$((i - 1)) 
   c=$((c + 2)) 
done

echo "$c"