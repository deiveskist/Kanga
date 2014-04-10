#include <iostream>

#define ANAHY
#include "Reduce.h"

using namespace std;

int* func(int* x, int* y){ *x=*x+*y; return x; }

int main(int argc, char** argv){
 AnahyVM::init(argc, argv);	
 int v0[10],*dataOut, i;
 
 for(i=0; i< 10;i++) v0[i]=i+1;
 
 pi::Reduce<int> *red = new pi::Reduce<int>(func,v0, dataOut,10);
 red->start();
 red->join();
 double average = *dataOut/10; 
 cout << average << endl;
 AnahyVM::terminate();
 return 0;
}  