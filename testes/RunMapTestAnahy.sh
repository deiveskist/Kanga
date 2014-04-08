#!/bin/bash

for i in $(seq 30)
do 
 echo -n "1 ; "
 ./MapTestAnahy 1 -v 4
done

for i in $(seq 30)
do 
  echo -n "2 ; "
 ./MapTestAnahy 2 -v 4
done

for i in $(seq 30)
do 
  echo -n "4 ; "
 ./MapTestAnahy 4 -v 4
done

for i in $(seq 30)
do 
  echo -n "8 ; "
 ./MapTestAnahy 8 -v 4
done
