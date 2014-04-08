#!/bin/bash

for i in $(seq 30)
do 
 echo -n "40000 ; "
 ./DCTestPIAnahy 40000 -v 4
done

for i in $(seq 30)
do 
 echo -n "45000 ; "
 ./DCTestPIAnahy 45000 -v 4
done

for i in $(seq 30)
do 
 echo -n "50000 ; "
 ./DCTestPIAnahy 50000 -v 4
done

for i in $(seq 30)
do 
  echo -n "55000 ; "
 ./DCTestPIAnahy 55000 -v 4
done


