#!/bin/bash

for i in $(seq 30)
do 
 echo -n "1 ; "
 ./MapTestPthread 1
done

for i in $(seq 30)
do 
  echo -n "2 ; "
 ./MapTestPthread 2
done

for i in $(seq 30)
do 
  echo -n "4 ; "
 ./MapTestPthread 4
done

for i in $(seq 30)
do 
  echo -n "8 ; "
 ./MapTestPthread 8
done