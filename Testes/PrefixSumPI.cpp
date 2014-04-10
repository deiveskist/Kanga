#include <iostream>

#define ANAHY
#include "Scan.h"

using namespace std;

int* sum(int* x, int* y){ *x = *x+*y; return x;}

int main(int argc, char **argv){
 AnahyVM::init(argc, argv);
  int v0[10], *r, i;
  for(i=0; i< 10;i++) v0[i]=i+1;
  
  pi::Scan<int> *scan= new pi::Scan<int>(sum,v0,r,10);
  scan->start();
  scan->join();
   
  for(i=0; i< 10;i++){ 
    cout << r[i] << " ";
  }
  cout << endl;
  AnahyVM::terminate();
  return 0;
}