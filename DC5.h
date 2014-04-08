/*
 * DC.h
 *
 * 
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
    this->proIn=new T();
   }
   
   DC(const DC<T> &e) : proOut(e.proOut){
     this->proIn=e.proIn;
     this->proOut=e.proOut;   
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
     //delete this->dcDir;
    // delete this->dcEsq;
     delete this->thdrun;
     delete this->proIn;
     delete this->proOut;
     //delete this->proDir;
     //delete this->proEsq; 
   }
   
   void start(){
    
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
    T * t;

    struct Para{
      T* pro;
      DC<T> *dc; 
    }; 

    static T * tRun(DC<T> *dc){
      return dc->runDCPara(dc->proIn);
    }

    static T * tRun1(Para* para){
      return para->dc->runDC(para->pro);
    }

    static T * tRunPara(Para *para){
       return para->dc->runDCPara(para->pro);
    }

   T* runDCPara(T * pro){
      T * proDir;
      T * proEsq;
     if(pro->base()==1){
        pro->conquista();
        return pro;
      }
      else{

         Para *p = new Para;
         proDir=pro->divisaoDir();
         proEsq=pro->divisaoEsq();
         p->pro=proDir;
         p->dc=this;

         proEsq=this->runDCPara(proEsq);

         Thread<Para , T> * thdDir = new Thread<Para, T>(&DC::tRunPara,p);
         DC<T>::quantos=DC<T>::quantos+1;
         thdDir->start();
         //proEsq=this->runDCPara(proEsq);
         thdDir->join();

         proDir=thdDir->getDataOut();
         pro->combina(proDir,proEsq);
         delete proDir;
         delete proEsq;
         delete p;

         return pro;

         //return this->proIn;
      }
    }


    T* runDC(T * pro){
      T * proDir;
      T * proEsq;
     if(pro->base()==1){
        pro->conquista();
        return pro;
      }
      else{
         
         Para *p = new Para;
         proDir=pro->divisaoDir();
         proEsq=pro->divisaoEsq();
         p->pro=proDir; 
         p->dc=this;

         Thread<Para , T> * thdDir = new Thread<Para, T>(&DC::tRunPara,p);
         DC<T>::quantos=DC<T>::quantos+1;
         thdDir->start();
         proEsq=this->runDCSeq(proEsq);
         thdDir->join();  
         
         proDir=thdDir->getDataOut();
         pro->combina(proDir,proEsq);  
         //delete proDir;
         //delete proEsq;
         //delete p;

         return pro;

         //return this->proIn;
      }
    }
};

template<class T> int DC<T>::quantos = 0;

};

#endif /* DC_H_ */
