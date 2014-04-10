#include <iostream>

#define PTHREADS

#include "Thread.h"



using namespace std;

int* func(int* a){
  
  return a;
}

double* func2(double* a,double *b){
  return a;
}

float * func3(float *a){
 return a;
}

int main(int argc, char **argv){
  ///AnahyVM::init(argc, argv);
  int n=10;
  int *in=&n;
  int *out;
  
  Thread<int,int>* thread1 = new Thread<int,int>(func,in,out);
  thread1->start();
  thread1->join();
  cout<< *out << endl;
  
  double v1=100;
  double v2=11;
  double *in2=&v1;
  double *in3=&v2;  
  double *out2;
  Thread<double,double>* thread2 = new Thread<double,double>(func2,in2,in3,out2); 
  thread2->start();
  thread2->join();
  cout<< *thread2->getDataOut() << endl;
  cout<< *out2 << endl;

  Thread<float,float>* thread3 = new Thread<float,float>();
  thread3->setFunc(func3);
  float m=200;
  float *mi=&m;
  float *mout;
  thread3->setDataIn(mi);
  thread3->start();
  thread3->join();
  cout<< *thread3->getDataOut() << endl;
  //AnahyVM::terminate();
  return 0;
}