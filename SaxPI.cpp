#include <iostream>
#include <stdio.h> 

#define ANAHY
#include "Zip.h"

using namespace std;
using namespace pi;

int* saxpy(int* x, int* y){ *x= (*x)*10 + (*y); return x;}

int main(int argc, char **argv){
 AnahyVM::init(argc, argv);
 int i, vetX[10], vetY[10],*vetOutax,*vetOut;

 for(i=0; i<10 ;i++){ vetX[i]=i+1; vetY[i]=i*2;}
  
 
 Zip<int,int> *zip= new Zip<int,int>(saxpy,vetX,vetY,vetOut,10);
 zip->start();
 zip->join();

 cout << "Saida do Map Sax: " ;
 for(i=0; i<10; i++) cout << vetOut[i] <<" ";
 cout << endl;
 AnahyVM::terminate();

 return 0;
}