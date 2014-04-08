#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "compute_time.c"

#include "AnahyVM.h"
#include "AnahyJob.h"

int fib(int n){
  if (n == 1) return 1;                             
  else if (n == 2) return 1;                 
  else return fib(n - 1) + fib(n - 2);
}

void * func(void* arg){
  int x = *(int*)arg;
  
  x=fib(x);
  int *p=new int;
  *p=x;
  return (void*)p; 
}

int main(int argc,char *argv[]){
  AnahyVM::init(argc, argv);
  int TAM = atoi(argv[1]);
  int vetIn[TAM], vetOut[TAM], i;
  AnahyJob jobs[TAM];
  void *threadReturn;
 
  // cout << "Entrada do Map: " ;
  for(i=0; i<TAM; i++) vetIn[i]=40;
   // cout << i+1 << " ";
  //cout << endl;

  time_log_start();  
  for(i = 0; i < TAM; i++){
    jobs[i].init(func, &vetIn[i], NULL);
    AnahyVM::fork(&jobs[i]);
  }

  for(i = 0; i < TAM; i++){
    AnahyVM::join(&jobs[i], &(threadReturn));
    vetOut[i]= *static_cast<int*> (threadReturn);
    //printf("%d ", vetOut[i]);
  }
  //printf("\n");   
  time_log_stop();

  AnahyVM::terminate();
}