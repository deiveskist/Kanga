#!/bin/sh

#conta linhas
cM_PI_p=0 
cM_pt=0
cM_PI_A=0
cM_A=0

#testa de o arquivos de saida existem
# caso existem os remove
if [ -e Map_test_PI_pthread.txt ]; then

	rm Map_test_PI_pthread.txt

fi

if [ -e Map_test_pthread.txt ]; then

	rm Map_test_pthread.txt
fi

if [ -e Map_test_PI_Anahy.txt ]; then

        rm Map_test_PI_Anahy.txt

fi

if [ -e Map_test_Anahy.txt ]; then

        rm Map_test_Anahy.txt
fi

# vetor de entrada com 500 elementos == 500 threads

#for i in $(seq 1 30)
#do
 #  echo -n  "$cM_PI_p ; " 
 # ../Map_test_PI_pthread 500  >> Map_test_PI_pthread.txt
   #cM_PI_p=cM_PI_p+1
  
#done

#for i in $(seq 1 30)
#do
 #  echo -n  "$cM_p ;"
   #cM_p=CM_p+1
   #../Map_test_pthread 500  >> Map_test_pthread.txt
#done

for i in $(seq 1 30)
do
  #echo -n  "$cM_PI_A ; " >> Map_test_PI_Anahy.txt
  #cM_PI_A=cM_PI_A+1
 ../Map_test_PI_Anahy 500  >> Map_test_PI_Anahy.txt
done

for i in $(seq 1 30)
do
   #echo -n "$cM_A ; " >> Map_test_Anahy.txt
   #cM_A=cM_A+1
 ../Map_test_Anahy 500  >> Map_test_Anahy.txt
done

# vetor de entrada com 1000 elementos == 1000 threads

#for i in $(seq 1 30)
#do
   #echo -n  "$cM_PI_p ; "  >> Map_test_PI_pthread.txt 
  #../Map_test_PI_pthread 1000  >> Map_test_PI_pthread.txt
   #cM_PI_p=cM_PI_p+1

#done

#for i in $(seq 1 30)
#do
   #echo -n  "$cM_p ; " >>  Map_test_pthread.txt
   #cM_p=CM_p+1
 #../Map_test_pthread 1000  >> Map_test_pthread.txt
#done

for i in $(seq 1 30)
do
  #echo -n  "$cM_PI_A ; " >> Map_test_PI_Anahy.txt
  #cM_PI_A=cM_PI_A+1
 ../Map_test_PI_Anahy 1000  >> Map_test_PI_Anahy.txt
done

for i in $(seq 1 30)
do
   #echo -n "$cM_A ; " >> Map_test_Anahy.txt
   #cM_A=cM_A+1
 ../Map_test_Anahy 1000  >> Map_test_Anahy.txt
done


# vetor de entrada com 1500 elementos == 1500 threads

#for i in $(seq 1 30)
#do
   #echo -n  "$cM_PI_p ; "  >> Map_test_PI_pthread.txt 
  #../Map_test_PI_pthread 1500  >> Map_test_PI_pthread.txt
   #cM_PI_p=cM_PI_p+1

#done

#for i in $(seq 1 30)
#do
   #echo -n  "$cM_p ; " >>  Map_test_pthread.txt
   #cM_p=CM_p+1
 #../Map_test_pthread 1500  >> Map_test_pthread.txt
#done

for i in $(seq 1 30)
do
  #echo -n  "$cM_PI_A ; " >> Map_test_PI_Anahy.txt
  #cM_PI_A=cM_PI_A+1
 ../Map_test_PI_Anahy 1500  >> Map_test_PI_Anahy.txt
done

for i in $(seq 1 30)
do
   #echo -n "$cM_A ; " >> Map_test_Anahy.txt
   #cM_A=cM_A+1
 ../Map_test_Anahy 1500  >> Map_test_Anahy.txt
done

# vetor de entrada com 2000 elementos == 2000 threads

#for i in $(seq 1 30)
#do
   #echo -n  "$cM_PI_p ; "  >> Map_test_PI_pthread.txt 
  #../Map_test_PI_pthread 2000  >> Map_test_PI_pthread.txt
   #cM_PI_p=cM_PI_p+1

#done

#for i in $(seq 1 30)
#do
   #echo -n  "$cM_p ; " >>  Map_test_pthread.txt
   #cM_p=CM_p+1
 #../Map_test_pthread 2000  >> Map_test_pthread.txt
#done

for i in $(seq 1 30)
do
  #echo -n  "$cM_PI_A ; " >> Map_test_PI_Anahy.txt
  #cM_PI_A=cM_PI_A+1
 ../Map_test_PI_Anahy 2000  >> Map_test_PI_Anahy.txt
done

for i in $(seq 1 30)
do
   #echo -n "$cM_A ; " >> Map_test_Anahy.txt
   #cM_A=cM_A+1
 ../Map_test_Anahy 2000  >> Map_test_Anahy.txt
done

# vetor de entrada com 2500 elementos == 1500 threads

#for i in $(seq 1 30)
#do
   #echo -n  "$cM_PI_p ; "  >> Map_test_PI_pthread.txt 
  #../Map_test_PI_pthread 2500  >> Map_test_PI_pthread.txt
   #cM_PI_p=cM_PI_p+1

#done

#for i in $(seq 1 30)
#do
   #echo -n  "$cM_p ; " >>  Map_test_pthread.txt
   #cM_p=CM_p+1
 #../Map_test_pthread 2500  >> Map_test_pthread.txt
#done

for i in $(seq 1 30)
do
  #echo -n  "$cM_PI_A ; " >> Map_test_PI_Anahy.txt
  #cM_PI_A=cM_PI_A+1
 ../Map_test_PI_Anahy 2500  >> Map_test_PI_Anahy.txt
done

for i in $(seq 1 30)
do
   #echo -n "$cM_A ; " >> Map_test_Anahy.txt
   #cM_A=cM_A+1
 ../Map_test_Anahy 2500  >> Map_test_Anahy.txt
done

