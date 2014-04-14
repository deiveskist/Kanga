#include <stdio.h>
#include <stdlib.h>
#define PTHREADS
#include "../DC.h"

using namespace kanga;

class Fib : public ProblemaDC{
 private:
 	int n;

 public:
  Fib(){
  	this->n=0;
  }	

  Fib(const Fib &e ){
  	this->n=e.n;
  }

  Fib(int n){
   this->n=n;
  } 

  ~Fib(){

   }

  int base(){
  	if(this->n >0 && this->n < 3) return 1;
  	return 0;
  }

  Fib* divisaoEsq(){  
    return new Fib(this->n-1);
  }

  Fib* divisaoDir(){  
    return new Fib(this->n-2);
  }

  void conquista(){
  	//if(this->n==1 || this->n==2) this->n=1;
    this->n=this->fib(this->n);
  }

  void combina(Fib* x, Fib* y){
    //printf("%d %d \n",x->n,y->n);
  	this->n=x->n+y->n;
  }

  void setData(int  n){
    this->n=n;
  }

  int getDataOut(){
    return this->n;
  }

  int fib(int n){
   if (n == 1) return 1;                             
   else if (n == 2) return 1;                 
   else return this->fib(n - 1) + this->fib(n - 2);
  }

  void print(){
    printf("%d ",this->n);
  }
};

int fib(int n){
  if (n == 1) return 1;                             
  else if (n == 2) return 1;                 
  else return fib(n - 1) + fib(n - 2);
}


int main(int argc, char **argv){

  int n=atoi(argv[1]);
  printf("fib de %d : %d\n", n,fib(n));
  Fib *fibIn = new Fib(n);
  Fib *fibOut = new Fib();  
 
  DC<Fib> *dcFib = new DC<Fib>(fibIn,fibOut);
  dcFib->start();
  dcFib->join();
  //fibOut=dcFib->getDataOut();
  printf("result do DC ");
  fibOut->print();

}