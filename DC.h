/*
 * DC.h
 *
 *  Created on: 7/11/2013
 *      Author: deives
 */

#ifndef DC_H_
#define DC_H_

#include "Kanga.h"
#include "Thread.h"

namespace kanga{

class ProblemaDC{
  public:
  virtual int base(){};
  virtual ProblemaDC* divisaoDir(){};
  virtual ProblemaDC* divisaoEsq(){};
  virtual void conquista(){};
  virtual void combina(ProblemaDC* esq, ProblemaDC* dir){};
  virtual void print(){};
};

template< class T>
class DC : public Kanga<T,T> {
 public:

 static int quantos;

   DC() : proOut(t){
    this->dcDir=new Kanga<T,T>();
    this->dcEsq=new Kanga<T,T>();
    this->proIn=new T();
   }
   
   DC(const DC<T> &e) : proOut(e.proOut){
     this->proIn=e.proIn;
     this->proOut=e.proOut;   
     this->dcDir=e.dcDir;
     this->dcEsq=e.dcEsq;
     this->proIn=e.proIn;
     //this->proOut=e.proOut;
   }

   DC(T *proIn) : proOut(t){
     //DC<T>::quantos=DC<T>::quantos+1;    
     this->proIn=proIn;
   }
  
   DC(T * proIn, T * &proOut) : proOut(proOut){
     this->proIn=proIn;
   }
   
   ~DC(){
     delete this->dcDir;
     delete this->dcEsq;
     delete this->thdrun;
     delete this->proIn;
     delete this->proOut;
     delete this->proDir;
     delete this->proEsq; 
   }
   
   void start(){
      DC<T>::quantos=DC<T>::quantos+1;
      thdrun = new Thread< DC<T> , T>(&DC::tRun,this);
      thdrun->start();
      
   }
   
   void join(){
     thdrun->join();
     this->proOut=this->thdrun->getDataOut();
     //this->proOut=this->proIn;
     
   }
   
    Kanga<T,T> * clone(){
      return new DC<T>();
    }

    Kanga<T,T> * clone(T * proIn, T*& proOut){
      return new DC<T>(proIn,proOut);
    }

   void setDataIn(T * pro){
    this->proIn=pro;
    this->proIn->print();
   }

   T * getDataOut(){
     return this->proOut;
   }

   void printQ(){
    printf(" ; %d \n",DC<T>::quantos);
   }

  private:
   
    Thread< DC<T> , T > *thdrun; 
    pthread_mutex_t mutex;
    T * proIn;
    T *& proOut;
    T * proDir;
    T * proEsq;
    T * t;

    Kanga<T,T> * dcDir;
    Kanga<T,T> * dcEsq;

    static T * tRun(DC<T> *dc){
      return dc->runDC();
    }

    T* runDC(){
      if(this->proIn->base()==1){
        this->proIn->conquista();
        return this->proIn;
      }
      else{
      
         this->proDir= this->proIn->divisaoDir();
         this->proEsq=this->proIn->divisaoEsq();
         
          dcDir=new DC<T>(this->proDir);
          dcEsq=new DC<T>(this->proEsq);
          dcDir->start();
           
          this->proEsq=dcEsq->runDC();
           

          dcDir->join();  
          this->proDir=dcDir->getDataOut();
          this->proIn->combina(this->proDir,this->proEsq);  
         //}
         return this->proIn;
      }
    }
};

template<class T> int DC<T>::quantos = 0;

};

#endif /* DC_H_ */



/*


template< class IN, class OUT>
class DC : public Kanga<IN,OUT> {
 public:
   DC(){
     this->div=NULL;
     this->conq=NULL;
     this->base=NULL;
     this->dataIn=NULL;
     this->dataOut=NULL;
   }
   
   DC(const DC<IN,OUT> &e){
     this->div=e.div;
     this->conq=e.conq;
     this->base=e.base;
     this->alterBaseIn=e.alterBaseIn;
     this->dataIn=e.dataIn;
     this->dataOut=e.dataOut;
   
   }
  
   DC(IN* (*divide)(IN*), OUT* (*combine) (OUT*,OUT*), bool (*isSimple) (IN*), OUT* (*solve)(IN*), IN* dataIn, OUT*& dataOut){
     this->divide=divide;
     this->combine=combine;
     this->isSimple=isSimple;
     this->solve=solve;
     this->dataIn=dataIn;
     this->dataOut=dataOut;
     pthread_mutex_init(&mutex, NULL);
   }

    DC(IN* (*divide)(IN*), OUT* (*combine) (OUT*,OUT*), bool (*isSimple) (IN*), OUT* (*solve)(IN*)){
     this->divide=divide;
     this->combine=combine;
     this->isSimple=isSimple;
     this->solve=solve;
     pthread_mutex_init(&mutex, NULL);
   }
   
   ~DC(){
     delete this->dcDir;
     delete this->dcEsq;
     delete this->thdrun;
     pthread_mutex_destroy(&mutex);
   }
   
   void start(){
      thdrun = new Thread< DC<IN,OUT> , OUT>(&DC<IN,OUT>::tRun,this);
      thdrun->start();  
   }
   
   void join(){
     thdrun->join();
     this->dataOut=this->thdrun->getDataOut();
   }
   
   Kanga<IN,OUT> * clone(){
      return new DC<IN,OUT>(this->divide,this->combine,this->isSimple,this->solve,this->dataIn,this->dataOut);
   }
   
   // OUT * getListOut(){
   //   return this->dataOut;
   // }

   void setDataIn(IN * dataIn){
    this->dataIn=dataIn;
   }

   OUT * getDataOut(){
    return this->dataOut;
   }

  private:
    IN* (*divide) (IN*);
    OUT* (*solve) (IN*);
    OUT* (*combine) (OUT*,OUT*);
    bool (*isSimple) (IN*);
    IN  *dataIn;
    OUT *dataOutTemp;
    OUT *dataOut;
    Thread< DC<IN,OUT> , OUT > *thdrun; 
    pthread_mutex_t mutex;
    Kanga<IN,OUT> * dcDir;
    Kanga<IN,OUT> * dcEsq;
    Thread< DC<IN,OUT> , OUT > *thdir;
    Thread< DC<IN,OUT> , OUT > *thesq;  
    
    IN *dataOutDir;
    IN *dataOutEsq;

    IN *esq;
    IN *dir;
    IN *auxDivide;

    static OUT * tRun(DC<IN,OUT> *dc){
      return dc->run();
    }

    OUT* run(){
      if(this->isSimple(this->dataIn)==true){
        // printf("entro aqui %d \n",*this->dataIn);
         return this->solve(this->dataIn);
      }
      else{

        // printf("dataIN %d \n ",this->dataIn->n);
         dir=this->divide(this->dataIn);
         esq=this->divide(dir);

         if(this->isSimple(dir)==true && this->isSimple(esq)==true)
         {
           dataOutDir=this->solve(dir);    
           dataOutEsq=this->solve(esq);    
           return this->combine(dataOutDir,dataOutEsq); 
         }
         else if(this->isSimple(dir)==true && this->isSimple(esq)==false) {
             
          /*
           this->dataIn=esq;
           thesq = new Thread< DC<IN,OUT> , OUT>(&DC<IN,OUT>::tRun,this);
           thesq->start();  

           thesq->join();
           dataOutEsq=this->thesq->getDataOut();
           */ 
          /*
          dcEsq=new DC<IN,OUT>(this->divide,this->combine,this->isSimple,this->solve,esq,this->dataOut);
          dcEsq->start();
          dataOutDir=this->solve(dir);
          dcEsq->join();
          dataOutEsq=dcEsq->getDataOut();
          
          return this->combine(dataOutDir,dataOutEsq); 
         }
         else if(this->isSimple(dir)==false && this->isSimple(esq)==true) {
         */
              

          /*

          this->dataIn=dir;
          thdir = new Thread< DC<IN,OUT> , OUT>(&DC<IN,OUT>::tRun,this);
          thdir->start();  

          thdir->join();
          dataOutDir=this->thdir->getDataOut();
          */

          /*
          dcDir=new DC<IN,OUT>(this->divide,this->combine,this->isSimple,this->solve,dir,this->dataOut);
          dcDir->start();
           dataOutEsq=this->solve(esq);
          dcDir->join();
          dataOutDir=dcDir->getDataOut();
        
          return this->combine(dataOutDir,dataOutEsq); 

         }
         else if(this->isSimple(this->dataIn)==false && this->isSimple(this->dataIn)==false) {
          
          dcDir=new DC<IN,OUT>(this->divide,this->combine,this->isSimple,this->solve,dir,this->dataOut);
          dcEsq=new DC<IN,OUT>(this->divide,this->combine,this->isSimple,this->solve,esq,this->dataOut);
          dcDir->start();
          dcEsq->start();

          dcEsq->join();
          dcDir->join();
          dataOutEsq=dcDir->getDataOut();
          dataOutDir=dcEsq->getDataOut();
          */
           
           /*
          this->dataIn=dir;
          thdir = new Thread< DC<IN,OUT> , OUT>(&DC<IN,OUT>::tRun,this);
          thdir->start();  

          thdir->join();
          dataOutDir=this->thdir->getDataOut();

          this->dataIn=esq;
          thesq = new Thread< DC<IN,OUT> , OUT>(&DC<IN,OUT>::tRun,this);
          thesq->start();  

          thesq->join();
          dataOutEsq=this->thesq->getDataOut();
          */
/*

           return this->combine(dataOutDir,dataOutEsq); 
         }

      }
    }
};



*/
