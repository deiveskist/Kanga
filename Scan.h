/*
 * Scan.h
 */

#ifndef SCAN_H_
#define SCAN_H_
#include <cmath>
#include "Thread.h"
#include "DataParallelism.h"

namespace kanga{ 

template<class T>
class Scan : public DataParallelism<T,T>{
  public:
    Scan(): DataParallelism<T,T>(){
      this->funcUser=NULL;
      this->efunc=NULL;
      this->numIter=0; 
      this->pri=true;
      this->obj=NULL;
    }

    Scan(const Scan &e): DataParallelism<T,T>(e){
     this->funcUser=e.funcUser;
     this->efunc=e.efunc;
     this->pri=e.pri;
     this->numIter=e.numIter; 
     this->dist=e.dist;
     this->iter=e.iter;
    }

    Scan(T* (*f) (T*,T*), T * listIn, T *& listOut, int length) : DataParallelism<T,T>(listIn,listOut,length) {
     this->funcUser=f;
     this->efunc=true;
     this->pri=true;
     this->numIter=ceil(log2(length));
     this->dist=1;
     this->iter=0;     
     this->obj=NULL;
    }

    Scan(T* (*f) (T*,T*), int length) : DataParallelism<T,T>(length){
      this->funcUser=f;
      this->efunc=true;
      this->pri=true;
      this->numIter=ceil(log2(length));
       this->obj=NULL;this->dist=1;
      this->iter=0;
      this->obj=NULL;
    }

    Scan(Kanga<T,T> * obj, T ** matIn, T **& matOut, int length) : DataParallelism<T,T>(matIn,matOut,length){
      this->obj=obj;
      this->funcUser=NULL;
      this->efunc=false;
    } 
        
    Kanga<T,T> * clone(){
      return new Scan<T>(this->funcUser,this->length);
    }

    Kanga<T,T> * clone(T * listIn, T *& listOut){
      return new Scan<T>(this->funcUser,listIn,listOut,this->length);
    }
      
    virtual ~Scan(){
      delete this->obj;
    }

    void start();
    void join();
    
    void setFunction(T* (*f) (T*,T*)){
      this->funcUser=f;
      this->pri=true;
    }

 private:
    
    T* (*funcUser)(T*,T*);// ponteiro para o funcao do usuario
    int i,dist, iter, numIter, numThreads;
    bool pri, efunc;
    Kanga<T,T> * obj;   // ponteiro para o objeto da composicao
    Thread<Scan<T>, T> *thdrun; //
    
    static T* tRun(Scan<T>* scan){
      return scan->run();
    }

    static T* tRunComp(Scan<T> *scan){
      return scan->runComp();
    }

    T* run();
    T* runComp(){}
};

template<class T>
void Scan<T>::start(){
  try{
      if(this->efunc==true){
        try{
          if(this->funcUser==NULL || this->listIn==NULL || this->length==0){ // verifica se o objeto foi inicializado corretamente 
            throw KException();
          }
          else{  
            this->threads= new Kanga<T,T>*[this->length];
            thdrun = new Thread<Scan<T> , T>(&Scan<T>::tRun,this);
            thdrun->start();
          }
        }
        catch(KException& e){
          std::cout << e.what() << std::endl;
          return ;
        }
      }
      else if(this->efunc==false){
        try{
          if(this->obj==NULL || this->length==0){ 
            throw KException();
          }
          else{    
             this->threads= new Kanga<T,T>*[this->length];
             thdrun = new Thread<Scan<T> , T>(&Scan<T>::tRunComp,this);
             thdrun->start();

          }
        }
        catch(KException& e){
          std::cout << e.what() << std::endl;
          return ;
        }
      }  
      else throw KException();
  }
  catch(KException& e){ 
    std::cout <<e.what() << std::endl;
    return ;
  }
}

template<class T>
void Scan<T>::join(){
  try{
    if(this->efunc==true){
      thdrun->join();
      this->listOut=this->thdrun->getDataOut();
    }
    else if(this->efunc==false){
      thdrun->join();
    }      
    else throw KException();
  }
  catch(KException& e){ 
    std::cout <<e.what() << std::endl;
    return ;
  }
}


template<class T>
T* Scan<T>::run(){
  this->listOutTemp[0]=this->listIn[0]; 
  this->threads= new Kanga<T,T>*[this->length]; 
  this->listInp= new T*[this->length];
  while(this->iter < this->numIter){
    this->numThreads=this->length-this->dist;
    if(this->pri==true){
      this->pri=false;
      for(i=0;i<  this->numThreads;i++){
         this->listInp[i]=&this->listIn[i];
         this->listInp[i+this->dist]=&this->listIn[i+this->dist];
         this->threads[i]=new Thread<T,T>(this->funcUser,&this->listIn[i], &this->listIn[i+this->dist]);
         this->threads[i]->start();
         }
      }
      else{
        for(i=0;i<  this->numThreads;i++){
          this->listInp[i]=&this->listOutTemp[i];
          this->listInp[i+this->dist]=&this->listOutTemp[i+this->dist];
          this->threads[i]=new Thread<T,T>(this->funcUser,&this->listOutTemp[i], &this->listOutTemp[i+this->dist]);
          this->threads[i]->start();
        }
      }
        
      for(i=0;i < this->numThreads;i++){
        this->threads[i]->join();
        this->listOutTemp[i+this->dist] = *this->threads[i]->getDataOut();
      }
        
      this->dist=this->dist+this->dist;
      this->iter++; 
   }
  return this->listOutTemp;
}  
};//end namespace

#endif /* SCAN_H_ */