#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "compute_time.c"

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
  pthread_exit((void*)p); 
}

int main(int argc,char *argv[]){
  int TAM = atoi(argv[1]);
  int vetIn[TAM], vetOut[TAM], i;
  pthread_t threads[TAM];
  void *threadReturn;
 
  // cout << "Entrada do Map: " ;
  for(i=0; i<TAM; i++) vetIn[i]=40;
   // cout << i+1 << " ";
  //cout << endl;

  time_log_start();  
  for(i = 0; i < TAM; i++){
    pthread_create(&threads[i],NULL, func, &vetIn[i]);
  }

  for(i = 0; i < TAM; i++){
    pthread_join(threads[i],&(threadReturn));
    vetOut[i]= *static_cast<int*> (threadReturn);
   // printf("%d ", vetOut[i]);
  }
 // printf("\n");   
  time_log_stop();
}