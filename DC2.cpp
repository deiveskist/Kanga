#include <stdio.h>
#include "ParallelInterface.h"
#include "Thread.h"

template<class IN,class OUT>
class ProblemaDC{
  public:
  virtual IN* aloca(){};
  virtual int base(){}
  virtual void divisao(){}
  virtual void conquista(){}
  virtual void combina(OUT* x, OUT* y){}
  virtual void setData(IN * data){}
  virtual OUT* getData(){}
  virtual void print(){}
};

struct Fib{
  int n;
};

template<class IN,class OUT>
class SolveFib : public ProblemaDC<IN,OUT>{
 private:
 	Fib *fib;
  Fib *a;
 public:
  SolveFib(){
  	this->fib=NULL;
  }	

  SolveFib(const SolveFib &e ){
  	this->fib=e.fib;
  }

  SolveFib(IN* fib){
   this->fib=fib;
  } 
  
  int base(){
  	if( this->fib->n < 3) return 1;
  	return 0;
  }

  void divisao(){  
    this->fib->n=this->fib->n--;
  }

  void conquista(){
  	if(this->fib->n==1 || this->fib->n==2) this->fib->n=1;
  }

  void combina(OUT* x, OUT* y){
  	this->fib->n=x->n+x->n;
  }


  void setData(IN * n){
    this->fib=n;
  }

  OUT * getData(){
    return this->fib;
  }

  IN * aloca(){
    return new Fib;
  }

  void print(){
    //printf("%d \n",this->n);
  }

};

template< class IN, class OUT>
class DC : public ParallelInterface<IN,OUT> {
 public:
   DC(){
    this->problema=NULL;  
   }
   
   DC(const DC<IN,OUT> &e){
     this->problema=e.problema;   
   }
  
   DC(ProblemaDC<IN,OUT> *problema, IN *dataIn,OUT *dataOut){
     this->proIn=problema;
     this->dataIn=dataIn;
     this->dir= new IN();
     this->esq= new IN();
     this->dataOut=new OUT();
     this->proOut= new ProblemaDC<IN,OUT>();
     pthread_mutex_init(&mutex, NULL);
   }
   
   ~DC(){
     delete this->dcDir;
     delete this->dcEsq;
     delete this->thdrun;
     pthread_mutex_destroy(&mutex);
   }
   
   void start(){
      thdrun = new Thread< DC<IN,OUT> , OUT >(&DC<IN,OUT>::tRun,this);
      thdrun->start();  
   }
   
   void join(){
     this->proIn->setData(this->dataIn);  
     thdrun->join();
     this->dataOut=this->thdrun->getDataOut();
     //printf("%d \n",*this->dataOut);
   }
   
   void setDataIn(IN * data){
    this->dataIn=data;
   }

   OUT * getDataOut(){
     return this->dataOut;
   }

  private:
    IN * dataIn;
    OUT *dataOut;
    IN *esq;
    IN *dir;
    Thread< DC<IN,OUT> , OUT > *thdrun; 
    pthread_mutex_t mutex;
    ProblemaDC<IN,OUT> * proIn;
    ProblemaDC<IN,OUT> * proOut;
    ProblemaDC<IN,OUT> * proDir;
    ProblemaDC<IN,OUT> * proEsq;
    ParallelInterface<IN,OUT> * dcDir;
    ParallelInterface<IN,OUT> * dcEsq;
    int tdir;
    int tesq;

    OUT *dataOutDir;
    OUT *dataOutEsq;
    static OUT * tRun(DC<IN,OUT> *dc){
      return dc->run();
    }

    OUT* run(){
      if(this->proIn->base()==1){
        this->proIn->conquista();
        return this->proIn->getData();
      }
      else{
         this->dir=proIn->aloca();
         this->proIn->setData(this->dataIn); 
         this->proIn->divisao();
         this->tdir=this->proIn->base();
         this->dir=this->proIn->getData();
         this->proIn->print();
         printf(" tdir : %d dir %d \n",this->tdir,this->dir->n);


         this->esq=this->proIn->aloca();
         this->proIn->setData(this->dir);
         this->proIn->divisao();
         this->tesq=this->proIn->base();
         this->esq=this->proIn->getData();
         printf(" tesq : %d esq %d \n",this->tesq,this->esq->n);
        
        if(this->tdir==1 && this->tesq==1)
         {
           this->proIn->setData(this->dir);  
           this->proIn->conquista();
           this->dataOutDir=this->proIn->getData();

           this->proIn->setData(this->esq);  
           this->proIn->conquista();
           this->dataOutEsq=this->proIn->getData();

           this->proIn->combina(this->dataOutDir,this->dataOutEsq);
           this->dataOut=this->proIn->getData();
           return this->dataOut;
         }
         else if(this->tdir==1 && this->tesq==0){
          
          //printf("this->proDir kkkk"); this->proDir->print();
          dcEsq=new DC<IN,OUT>(this->proIn,this->esq,this->dataOut);
          dcEsq->start();

          this->proIn->setData(this->dir);
          this->proIn->conquista();
          this->dataOutEsq=this->proIn->getData();  

          dcEsq->join();

          this->dataOutEsq=dcEsq->getDataOut();
          this->proIn->combina(this->dataOutDir,this->dataOutEsq);
          this->dataOut=this->proIn->getData();
          return this->dataOut;
         }

         else if(this->tdir==0 && this->tesq==1){
           printf("this->proDir %d \n",this->dir->n);
          dcDir=new DC<IN,OUT>(this->proIn,this->dir,this->dataOut);
          dcDir->start();

          this->proIn->setData(this->esq);
          this->proIn->conquista();
          this->dataOutEsq=this->proIn->getData();  

          dcDir->join();
          this->dataOutDir=dcDir->getDataOut();
          this->proIn->combina(this->dataOutDir,this->dataOutEsq);
          this->dataOut=this->proIn->getData();
          return this->dataOut;
         }
         else if(this->tdir==0 && this->tesq==0) {
          
          dcDir=new DC<IN,OUT>(this->proIn,this->dir,this->dataOut);
          dcEsq=new DC<IN,OUT>(this->proIn,this->esq,this->dataOut);
          dcDir->start();
          dcEsq->start();

          dcEsq->join();
          dcDir->join();
          this->dataOutEsq=dcDir->getDataOut();
          this->dataOutDir=dcEsq->getDataOut();
          this->proIn->combina(this->dataOutDir,this->dataOutEsq);
          this->dataOut=this->proIn->getData();
          return this->dataOut;
         }
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

  printf("fib de %d é: %d\n", n,fib(n));
  Fib *fibIn = new Fib();
  Fib *fibOut = new Fib();
  fibIn->n=n;
    
  SolveFib<Fib,Fib> *solvefib = new SolveFib<Fib,Fib>(fibIn);
  
  DC<Fib, Fib> *dcFib = new DC<Fib,Fib>(solvefib,fibIn,fibOut);
  dcFib->start();
  dcFib->join();
  fibOut=dcFib->getDataOut();

  printf("result do DC %d \n",fibOut->n);
  
  return 0;
}