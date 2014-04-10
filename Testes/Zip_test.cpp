#include <iostream>
#define PTHREADS
#include "Zip.h"
#include "Reduce.h"

using namespace std;
using namespace pi;

int* mult(int *a,int *b){
	*a=(*a) * (*b);
	return a;
}

int * plusf(int *a,int *b){
  *a=(*a) + (*b);
  return a;	
}

int main(){
 ParallelInterface<int,int>	*dotProduct;
 int vetIn1[10], vetIn2[10], *vetOut,*out, i;
 for(i=0;i<10;i++){
 	vetIn2[i]=i;
 	vetIn1[i]=i+1;
 }

 dotProduct = new Zip<int,int>(mult,vetIn1,vetIn2,vetOut,10);
 dotProduct->start();
 dotProduct->join();

 dotProduct = new Reduce<int>(plusf,vetOut,out,10);
 dotProduct->start();
 dotProduct->join();
 cout << *out << endl;
 return 0;
}