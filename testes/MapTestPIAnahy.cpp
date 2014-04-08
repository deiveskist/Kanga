#include <iostream>
#define ANAHY
#include "../Map.h"
#include "compute_time.c"

int fib(int n){
  if (n == 1) return 1;                             
  else if (n == 2) return 1;                 
  else return fib(n - 1) + fib(n - 2);
}

int* func(int* x){
  *x= fib(*x);
  return x;
}

using namespace kanga;
using namespace std;
int main(int argc,char *argv[]){
 
  AnahyVM::init(argc, argv);
  int TAM = atoi(argv[1]);
  int *vetIn = new int[TAM];
  int *vetOut;
  int i;
 
 // cout << "Entrada do Map: " ;
  for(i=0; i< TAM;i++) vetIn[i]=40;
   // cout << i+1 << " ";
  //cout << endl;
  time_log_start();
  Map<int,int> *map= new Map<int,int>(func,vetIn,vetOut,TAM);
  map->start();
  map->join();
  time_log_stop();
  AnahyVM::terminate();
  //cout << "Saida do Map: " ;
  //for(i=0; i< TAM;i++) cout << vetOut[i] <<" ";
  //cout<< endl; 
  
}  