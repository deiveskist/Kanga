#!/bin/bash

for i in $(seq 30)
do 
 echo -n "1 ; "
 ./MapTestPIPthread 1 
done

for i in $(seq 30)
do 
  echo -n "2 ; "
 ./MapTestPIPthread 2 
done

for i in $(seq 30)
do 
  echo -n "4 ; "
 ./MapTestPIPthread 4 
done

for i in $(seq 30)
do 
  echo -n "8 ; "
 ./MapTestPIPthread 8 
done