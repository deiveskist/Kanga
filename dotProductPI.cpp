#define ANAHY
#include "Zip.h"
#include "Reduce.h"

int *mult_f(int *a,int *b){ *a=(*a) * (*b); return a; }
int *plus_f(int *a,int *b){ *a=(*a) + (*b); return a; }

int main(int argc, char** argv){
 AnahyVM::init(argc, argv);
 pi::ParallelInterface<int,int> *dotProduct;
 int vetIn0[10], vetIn1[10], *vetOut,*out, i;
 for(i=0;i<10;i++){
  vetIn0[i]=i+1;
  vetIn1[i]=i+2;
 }

 dotProduct = new pi::Zip<int,int>(mult_f,vetIn0,vetIn1,vetOut,10);
 dotProduct->start();
 dotProduct->join();

 dotProduct = new pi::Reduce<int>(plus_f,vetOut,out,10);
 dotProduct->start();
 dotProduct->join();
 
 pi::Zip<int,int> dot(mult_f,vetIn0,vetIn1,vetOut,10);
 dot.start();
 dot.join();

 pi::Reduce<int> red(plus_f,vetOut,out,10);
 red.start();
 red.join();
 cout << *out << endl;
 delete out;
 AnahyVM::terminate();
 return 0;
} 