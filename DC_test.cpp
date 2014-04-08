#include "DC.h"

bool isSimpleFib(int* n){
  //printf("entro base %d \n",*n);
  if( *n ==1  ) return true;
  else return false;
}

int fib(int n){
  if (n == 1) return 1;                             
  else if (n == 2) return 1;                 
  else return fib(n - 1) + fib(n - 2);
}


int* divFib(int* v){  
  //printf(" divide %d \n", *v);
  *v=*v-1;
  //printf(" divide %d \n", *v);
  return v;
}

int* solveFib(int* n){
   int *v = new int;
   if( *n == 0 || *n==1) *v=1;
   return v;
}
int* conqFib(int * x, int * y){
  int *v = new int;
   *x=*x+*y;
  return x;
}

struct MergeParam{
  int *vet;
  int inicio;
  int fim ;
  int vecSize;
};


 bool isSimpleMerge(MergeParam *p){
// //   printf("entro base %d \n",*tam);
   if( p->vecSize<=5) return true;
   else return false;
}

MergeParam* divMerge(MergeParam *p){  
  // printf("%d \n", n);
   p->vecSize= p->vecSize-1;
   return p;
}

MergeParam* solveMerge(MergeParam *p){
   // merge(p->vet, p->inicio,5,p->fim);
    return p;
}

MergeParam *conqMerge(MergeParam *p, MergeParam  *q){
   return p;
}


struct Fib{
  int n;
};

bool isSimpleFib(Fib* a){
  // printf("entro base %d \n",a->n);
  if( a->n < 3) return true;
  else return false;
}

Fib* divFib(Fib* v){  
 // printf("%d \n", n);
  Fib *a= new Fib;
  a->n=v->n-1;  
  return a;
}

Fib* solveFib(Fib* n){
   if(n->n==1 || n->n==2){
     n->n=1;  
    return n;
   } 
   return n;
}

Fib* conqFib(Fib*  x, Fib * y){
 // printf("%d %d \n",x->n,y->n);
  x->n=x->n+y->n;

  return x;
}

int main(int argc, char **argv){
  int n=atoi(argv[1]);
  //printf("fib de %d é: %d\n", n,fib(n));
  Fib *fibIn = new Fib;
  fibIn->n=n;  

  Fib *fibOut;  
  DC<Fib, Fib> *dcFib = new DC<Fib, Fib>(divFib,conqFib,isSimpleFib,solveFib,fibIn,fibOut);
  dcFib->start();
  dcFib->join();
  fibOut=dcFib->getDataOut();
  printf("result do DC %d \n",fibOut->n);
  
  // int tam=10;
  // int * vet= new int[10];
  // int i=0;
  
  // for(i=tam-1;i > 0;i--) vet[i]=i;
  
  // MergeParam *paramIn = new MergeParam;
  // paramIn->vecSize=tam;
  // paramIn->vet=vet;
  // paramIn->inicio=0;
  // paramIn->fim=tam-1;
  // MergeParam *paramOut;
    
  // DC<MergeParam, MergeParam> *dcMergeSort = new DC<MergeParam, MergeParam>(divMerge,conqMerge,isSimpleMerge,solveMerge,paramIn,paramOut);
  // dcMergeSort->start();
  // dcMergeSort->join();

  // for(i=0;i < tam;i++) printf("%d ",vet[i]);
  //   printf("\n");
  
  return 0;
}

