/*
 * Farm.h
 *
 *  Created on: 14/11/2013
 *      Author: deives
 */

#ifndef FARM_H_
#define FARM_H_

#include "Thread.h"
#include "Kanga.h"

namespace kanga{
  
template<class T>
class Farm : public Kanga<T,int>{
      
  public:
    Farm(){
     this->funcUser=NULL;
     this->efunc=NULL;
     this->in=0;
     this->nThreads=0;
    }
    
    Farm(const Farm<T> &e){
     this->funcUser=e.funcUser;
     this->efunc=e.efunc;
     this->in=e.in;
     this->nThreads=e.nThreads;
    }
    
    Farm(int* (*f) (T*), T * in, int nThreads){
      this->funcUser=f;
      this->efunc=true;
      this->in=in;
      this->length=nThreads;
    }
    
    Farm(int* (*f) (T*), int nThreads) {
      this->funcUser=f;
      this->listIn=0;
      this->efunc=true; 
      this->length=nThreads;
    }
    /*
    Farm(Kanga<IN,OUT> * obj, IN ** matIn, OUT **& matOut, int nThreads) : out(o){      
      this->obj=obj;
      this->funcUser=NULL;
      this->efunc=false;
    }*/
    
    void start(){
     this->threads= new Kanga<T,int>*[this->length];
     for(i=0; i < this->length; i++) {
      this->threads[i]=new Thread<T,int>(this->funcUser,this->listIn);
      this->threads[i]->start();
     }     
    }
    
    void join(){
     for(i=0; i< this->length; i++){
       this->threads[i]->join();
      }
    }
    
    Kanga<int,T> * clone(){
      return new Farm<T>(this->funcUser,this->length);
    }

    Kanga<int,T> * clone(T * listIn, T *& listOut){
    //  return new Farm<T>(this->funcUser,listIn,listOut,this->length);
    }
  
    virtual ~Farm(){
      delete this->obj;
    }

    void setFunction(int* (*f) (T*);){
      this->funcUser=f;
      this->efunc=true;
    }
    
    void setLength(int n){
      this->nThreads=n;
    }
   
    private:
      int i;
      int nThreads;
      T * in;
      int length;
      Kanga<T,int> ** threads;
      T * listIn;
      //OUT * out;
      //OUT ** listOutp;
      int* (*funcUser) (T*);
      Kanga<T,int> * obj;
      bool efunc;
};

}//end namespace
#endif /* FARM_H_ */