#!/bin/bash

#compila os codigos dos testes Map
g++ MapTestPthread.cpp -o MapTestPthread -lpthread 

g++ MapTestPIPthread.cpp -o MapTestPIPthread -lpthread 

g++ MapTestAnahy.cpp -o MapTestAnahy *.o  -lpthread

g++ MapTestPIAnahy.cpp -o MapTestPIAnahy *.o  -lpthread

echo "Compilous os testes do Map"

#compila os codigos dos testes DC
g++ DCTestPthread.cpp -o DCTestPthread -lpthread 

g++ DCTestPIPthread.cpp -o DCTestPIPthread -lpthread 

g++ DCTestAnahy.cpp -o DCTestAnahy *.o  -lpthread

g++ DCTestPIAnahy.cpp -o DCTestPIAnahy *.o  -lpthread

echo "Compilous os testes do DC"

#verifica se os arquivos existem de dados dos testes do Map
if [ -e Dados/Map_test_PI_Pthread.txt ]; then
     rm Dados/Map_test_PI_Pthread.txt
fi

if [ -e Dados/Map_test_PI_Anahy.txt ]; then
     rm Dados/Map_test_PI_Anahy.txt
fi

if [ -e Dados/Map_test_Pthread.txt ]; then
     rm Dados/Map_test_Pthread.txt
fi

if [ -e Dados/Map_test_Anahy.txt ]; then
     rm Dados/Map_test_Anahy.txt
fi

#verifica se os arquivos existem de dados dos testes do DC
if [ -e Dados/DC_test_PI_Pthread.txt ]; then
     rm Dados/DC_test_PI_Pthread.txt
fi

if [ -e Dados/DC_test_PI_Anahy.txt ]; then
     rm Dados/DC_test_PI_Anahy.txt
fi

if [ -e Dados/DC_test_Pthread.txt ]; then
     rm Dados/DC_test_Pthread.txt
fi

if [ -e Dados/DC_test_Anahy.txt ]; then
     rm Dados/DC_test_Anahy.txt
fi

#excuta os scritps e insere nos arquivos do Map
echo "Inicia a Executção dos testes do Map \n"
#sh RunMapTestPthread.sh >> Dados/Map_test_Pthread.txt

echo "Executou Map_test_Pthread \n"
#sh RunMapTestAnahy.sh >> Dados/Map_test_Anahy.txt

echo "Executou Map_test_Anahy \n"

#sh RunMapTestPIAnahy.sh >> Dados/Map_test_PI_Anahy.txt

echo "Executou Map_test_PI_Anahy \n"
#sh RunMapTestPIPthread.sh >> Dados/Map_test_PI_Pthread.txt
echo "Executou Map_test_PI_Pthread\n"

echo "Executou os testes do Map \n"

#excuta os scritps e insere nos arquivos do DC
echo "Inicia a Executção dos testes do DC \n"
sh RunDCTestPthread.sh >> Dados/DC_test_Pthread.txt

echo "Executou DC_test_Pthread \n"

sh RunDCTestAnahy.sh >> Dados/DC_test_Anahy.txt

echo "Executou DC_test_Anahy \n"

sh RunDCTestPIAnahy.sh >> Dados/DC_test_PI_Anahy.txt

echo "Executou DC_test_PI_Anahy \n"

sh RunDCTestPIPthread.sh >> Dados/DC_test_PI_Pthread.txt

echo "Executou DC_test_PI_Pthread \n"

echo "Executou os testes do DC \n"

echo "Terminou todo!!!!!"

