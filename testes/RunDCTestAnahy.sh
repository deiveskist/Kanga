#!/bin/bash

for i in $(seq 30)
do 
 echo -n "40000 ; "
 ./DCTestAnahy 40000 -v 4
done

for i in $(seq 30)
do 
  echo -n "45000 ; "
 ./DCTestAnahy 45000 -v 4
done

for i in $(seq 30)
do 
  echo -n "50000 ; "
 ./DCTestAnahy 50000 -v 4
done

for i in $(seq 30)
do 
  echo -n "55000 ; "
 ./DCTestAnahy 55000 -v 4
done
