#!/bin/bash

for i in $(seq 30)
do 
 echo -n "40000 ; "
 ./DCTestPIPthread 40000
done

for i in $(seq 30)
do 
  echo -n "45000 ; "
 ./DCTestPIPthread 45000
done

for i in $(seq 30)
do 
  echo -n "50000 ; "
 ./DCTestPIPthread 50000
done

for i in $(seq 30)
do 
  echo -n "55000 ; "
 ./DCTestPIPthread 55000
done
