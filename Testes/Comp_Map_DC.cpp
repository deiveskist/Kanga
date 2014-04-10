#include <stdlib.h>
#include "DC.h"
#include "Map.h"

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
    if( this->n < 3) return 1;
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

int main(int argc, char **argv){
  int n=atoi(argv[1]);
     
 
  int i;
  Fib **vetIn = new Fib*[n];
  Fib **vetOut;
   
  DC<Fib> *dcFib = new DC<Fib>(); 
  for(i=0; i< n; i++){
    vetIn[i]=new Fib(i+1);
  }

  
  printf("\n");

  Map<Fib,Fib> *map= new Map<Fib,Fib>(dcFib,vetIn,vetOut,n);
  map->start();
  map->join();

  printf("\n");

  for(i=0; i< n; i++){
    vetOut[i]->print();
  }

  printf("\n");
   return 0;
}