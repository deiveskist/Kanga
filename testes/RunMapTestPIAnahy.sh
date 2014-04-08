#!/bin/bash

for i in $(seq 30)
do 
 echo -n "1 ; "
 ./MapTestPIAnahy 1 -v 4
done

for i in $(seq 30)
do 
  echo -n "2 ; "
 ./MapTestPIAnahy 2 -v 4
done

for i in $(seq 30)
do 
  echo -n "4 ; "
 ./MapTestPIAnahy 4 -v 4
done

for i in $(seq 30)
do 
  echo -n "8 ; "
 ./MapTestPIAnahy 8 -v 4
done
