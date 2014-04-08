#include <iostream>

#include "Seq.h"
#include "Thread.h"

int dobro(int x){
  return x*2;
}

int triplo(int x){
  return x*3;
} 

int main(){    
  Seq<int,int> *seq= new Seq<int,int>(2,0,0);
  seq->add(new Thread<int,int>(dobro,1));
  seq->add(new Thread<int,int>(triplo,2));
  
  seq->start();
  seq->join();
  
  c
  
  

  return 0;
}