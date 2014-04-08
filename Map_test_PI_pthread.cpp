#include "Map.h"
#include "compute_time.c"
int func(int x){
  return x*2;
}

int main(int argc,char *argv[]){
  time_log_start();
  int TAM = atoi(argv[1]);
  int *vetIn = new int[TAM];
  int *vetOut;
  int i;
  
 
 // cout << "Entrada do Map: " ;
  for(i=0; i< TAM;i++) vetIn[i]=i+1;
   // cout << i+1 << " ";
  //cout << endl;

  Map<int,int> *map= new Map<int,int>(func,vetIn,vetOut,TAM);
  map->start();
  map->join();
  //cout << "Saida do Map: " ;
  //for(i=0; i< TAM;i++) cout << lista_out[i] <<" ";
  time_log_stop();
}  