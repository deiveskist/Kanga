#include <stdio.h>
#include "ParallelInterface.h"
#include "Thread.h"

class ProblemaDC{
  public:
  virtual int base(){}
  virtual ProblemaDC* divisaoDir(){}
  virtual ProblemaDC* divisaoEsq(){}
  virtual void conquista(){}
  virtual void combina(ProblemaDC* esq, ProblemaDC* dir){}
//  virtual ProblemaDC* clone(){}
  virtual void print(){}
 // virtual void setData(IN * data){}
 // virtual void getData(){}
};

#define MAX 1000
int arr[MAX];

void mergeSort(int low,int mid,int high);

void partition(int low,int high){

    int mid;

    if(low<high){
         mid=(low+high)/2;
         partition(low,mid);
         partition(mid+1,high);
         mergeSort(low,mid,high);
    }
}

void mergeSort(int low,int mid,int high){

    int i,m,k,l,temp[MAX];

    l=low;
    i=low;
    m=mid+1;

    while((l<=mid)&&(m<=high)){

         if(arr[l]<=arr[m]){
             temp[i]=arr[l];
             l++;
         }
         else{
             temp[i]=arr[m];
             m++;
         }
         i++;
    }

    if(l>mid){
         for(k=m;k<=high;k++){
             temp[i]=arr[k];
             i++;
         }
    }
    else{
         for(k=l;k<=mid;k++){
             temp[i]=arr[k];
             i++;
         }
    }
   
    for(k=low;k<=high;k++){
         arr[k]=temp[k];
    }
  //for(int v=low; v < high; v++) printf("%d ", arr[v]);
   // printf("\n");
}

class PMergeSort: public ProblemaDC{
private:
  int inicio,meio,fim;
  int i,aux, j, k;
  int tam;
public:
  PMergeSort(){
    this->inicio=0;
    this->meio=0;
    this->fim=0;
    this->tam=0;
  }

  PMergeSort(const PMergeSort& e){
    this->inicio=e.inicio;
    this->meio=meio;
    this->fim=fim;
    this->tam=e.tam;
  }

  PMergeSort(int inicio,int fim){
    this->inicio=inicio;
    this->meio=meio;
    this->fim=fim;
    this->meio=(inicio+fim)/2;
    this->tam=fim-inicio;

  }
  
  int base(){
    if(this->tam < 3) return 1;
    return 0;
  }

  PMergeSort* divisaoDir(){  
      //printf("dir ini: %d fim: %d \n",this->inicio,this->meio);
     return new PMergeSort(this->inicio,this->meio);

  }

  PMergeSort* divisaoEsq(){  
    //printf("esq ini: %d fim: %d \n",this->meio+1,this->fim);
     return new PMergeSort(this->meio+1,this->fim);
     
  }

  void conquista(){
     partition(this->inicio,this->fim);    
  }

  void combina(PMergeSort* esq, PMergeSort* dir){
    int t;
    for(i=esq->inicio; i <=esq->fim;i++) printf("%d ", arr[i]);
    printf("\n");

    for(i=dir->inicio; i <=dir->fim;i++) printf("%d ", arr[i]);
    printf("\n");
  
    printf("dir: %d esq: %d \n",dir->tam,esq->tam);
    if(dir->tam < esq->tam) t=dir->tam+1;
    else t=esq->tam+1;

    if(arr[esq->inicio] > arr[dir->inicio] ){

        for(i=0; i < t; i++){
           aux=arr[esq->inicio+i];
           arr[esq->inicio+i]=arr[dir->inicio+i];
           arr[dir->inicio+i]=aux;
        }
      
    } 
    else if(arr[esq->inicio] < arr[dir->inicio] ){

      for(i=0; i < t; i++){
         aux=arr[dir->inicio+i];
         arr[dir->inicio+i]=arr[esq->inicio+i];
         arr[esq->inicio+i]=aux;
      }
    }
   
  }
};


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
  	if( this->n < 20) return 1;
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
    printf("%d \n",this->n);
  }


};


template< class T>
class DC : public ParallelInterface<T,T> {
 public:
   DC(){
    this->proIn=NULL;  
   }
   
   DC(const DC<T> &e){
     this->proIn=e.proIn;   
   }
  
   DC(T *proIn){
     this->proIn=proIn;
     
     this->proOut= new T();
     pthread_mutex_init(&mutex, NULL);
   }
   
   ~DC(){
     delete this->dcDir;
     delete this->dcEsq;
     delete this->thdrun;
     delete this->proIn;
     delete this->proOut;
     delete this->proDir;
     delete this->proEsq;
     pthread_mutex_destroy(&mutex);
   }
   
   void start(){
      thdrun = new Thread< DC<T> , T>(&DC::tRun,this);
      thdrun->start();  
   }
   
   void join(){
     thdrun->join();
     this->proOut=this->thdrun->getDataOut();
   }
   
  
   void setDataIn(T * pro){
    this->proIn=pro;
   }

   T * getDataOut(){
     return this->proOut;
   }

  private:
    
    Thread< DC<T> , T > *thdrun; 
    pthread_mutex_t mutex;
    T * proIn;
    T * proOut;
    T * proDir;
    T * proEsq;
    ParallelInterface<T,T> * dcDir;
    ParallelInterface<T,T> * dcEsq;

    static T * tRun(DC<T> *dc){
      return dc->run();
    }

    T* run(){
      if(this->proIn->base()==1){
        this->proIn->conquista();
        return this->proIn;
      }
      else{
         //this->proDir= new T();
         //this->proEsq= new T();
         
         //this->proIn->divisao(); 
         //this->proIn->print();
         this->proDir= this->proIn->divisaoDir();
         //this->proDir->divisao();

         //this->proIn->divisao(); 
         this->proEsq=this->proIn->divisaoEsq();
         //this->proEsq->divisao();

         //this->proEsq->print();
         //this->proDir->print();
/*
         if(this->proDir->base()==1 && this->proEsq->base()==1)
         {
           this->proDir->conquista();
           this->proEsq->conquista();
           this->proOut->combina(this->proDir,this->proEsq); 
          
         }
         else if(this->proDir->base()==1 && this->proEsq->base()==0){
          this->proDir->conquista();
  
          dcEsq=new DC<T>(this->proEsq);
          dcEsq->start();

          dcEsq->join();

          this->proEsq=dcEsq->getDataOut();
          this->proOut->combina(this->proDir,this->proEsq); 
  
  
         }

         if(this->proDir->base()==0 && this->proEsq->base()==1){

          this->proEsq->conquista();

          dcDir=new DC<T>(this->proDir);
          dcDir->start();

          dcDir->join();
          this->proDir=dcDir->getDataOut();
        
        
          this->proOut->combina(this->proDir,this->proEsq); 
         }
         else if(this->proDir->base()==0 && this->proEsq->base()==0) {
          */
          dcDir=new DC<T>(this->proDir);
          dcEsq=new DC<T>(this->proEsq);
          dcDir->start();
          dcEsq->start();

          dcEsq->join();
          dcDir->join();
          this->proDir=dcDir->getDataOut();
          this->proEsq=dcEsq->getDataOut();
          this->proOut->combina(this->proDir,this->proEsq);  
        //}
         
         return this->proOut;
      }
    }
};

int fib(int n){
  if (n == 1) return 1;                             
  else if (n == 2) return 1;                 
  else return fib(n - 1) + fib(n - 2);
}

int main(int argc, char **argv){
  int n=atoi(argv[1]);
  /*printf("fib de %d Ã©: %d\n", n,fib(n));
  Fib *fibIn = new Fib(n);
  Fib *fibOut = new Fib();  
 
  DC<Fib> *dcFib = new DC<Fib>(fibIn);
  dcFib->start();
  dcFib->join();
  fibOut=dcFib->getDataOut();
  printf("result do DC ");
  fibOut->print();
  */

  int i;
  for(i=0;i<n;i++){
     arr[i]=n-i;}

  for(i=0; i < n;i++) printf("%d ", arr[i]);
    printf("\n");

  PMergeSort *mergeIn = new PMergeSort(0,n-1);
  PMergeSort *mergeOut= new PMergeSort();
  
  DC<PMergeSort> *dcMerge = new DC<PMergeSort>(mergeIn);
  dcMerge->start();
  dcMerge->join();

  for(i=0; i < n;i++) printf("%d ", arr[i]);
    printf("\n");
  return 0;
}