#!/bin/bash

for i in $(seq 30)
do 
 echo -n "40000 ; "
 ./DCTestPthread 40000
done

for i in $(seq 30)
do 
  echo -n "45000 ; "
 ./DCTestPthread 45000
done

for i in $(seq 30)
do 
  echo -n "50000 ; "
 ./DCTestPthread 50000
done

for i in $(seq 30)
do 
  echo -n "55000 ; "
 ./DCTestPthread 55000
done
