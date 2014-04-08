#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "compute_time.c"

#include "Anahy-3/SRC/AnahyVM.h"
#include "Anahy-3/SRC/AnahyJob.h"

struct VetIn{
  int x;
  int y;
  int a;
};

void *func(void *arg){
 int *ret = new int;
 VetIn n = *(VetIn*)arg;
 *ret = n.a * n.x + n.y;
 return ret;
}

int main(int argc,char *argv[]){
  AnahyVM::init(argc, argv);
  int tamSax=atoi(argv[1]);
  AnahyJob jobs[tamSax];
  int i;
  void *threadReturn;
 
  VetIn* vetinSax = new VetIn[tamSax];
  int vetOutSax[tamSax];

  //cout << "Entrada do Map Sax: " ;
  for(i=0; i< tamSax;i++){
    vetinSax[i].x=i+1;
    vetinSax[i].a=10;
    vetinSax[i].y=i*2;
    //cout << i+1 << " ";
  }
  //cout << endl;

  time_log_start();  
  for(i = 0; i < tamSax; i++){
    jobs[i].init(func, &vetinSax[i], NULL);
    AnahyVM::fork(&jobs[i]);
    
  }

  for(i = 0; i < tamSax; i++){
    AnahyVM::join(&jobs[i], &(threadReturn));
    vetOutSax[i]= *static_cast<int*> (threadReturn);
   // printf("%d ", vetOutSax[i]);
  }
 // printf("\n");   
  time_log_stop();

  AnahyVM::terminate();
}