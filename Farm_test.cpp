#include <iostream>
#include <stdio.h> 

#define PTHREADS
#include "Farm.h"

using namespace std;
using namespace pi;

int valor=0;

int* runF(int *a){
	printf("Valor: %d \n",valor);
	valor++;
	return 0;
}

class Task{
  
};

int main(int argc, char **argv){
 
 Farm<int> *farm= new Farm<int>(runF,10);
 farm->start();
 farm->join();
    
 return 0;
}