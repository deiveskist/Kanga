/*
 * Scan.h
 *
 *  Created on: 30/09/2013
 *      Author: deives
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
    }

    Scan(T* (*f) (T*,T*), int length) : DataParallelism<T,T>(length)
    {
      this->funcUser=f;
      this->efunc=true;
      this->pri=true;
      this->numIter=ceil(log2(length));
      this->dist=1;
      this->iter=0;
    }

    Scan(Kanga<T,T> * obj, T ** matIn, T **& matOut, int length) : DataParallelism<T,T>(matIn,matOut,length)
    {
      this->obj=obj;
      this->funcUser=NULL;
      this->efunc=false;
    } 
     
    void start(){
      if(this->efunc==true){
        
        
        
       	thdrun = new Thread< Scan<T>, T>(&Scan<T>::tRun,this);
        thdrun->start();
      }
      else if(this->efunc==false){
    	  this->threads= new Kanga<T,T>*[this->length];
        for(this->i=0; i < this->length; i++){
          this->threads[i]=this->obj->clone(this->matIn[i],this->matOutTemp[i]);
          //this->threads[i]->setDataOut(this->matOutTemp[i]);
          //this->threads[i]->setDataIn(this->matIn[i]);
          this->threads[i]->start();
        }
      }
    }

    void join(){
      if(this->efunc==true){
	     thdrun->join();
	     this->listOut=this->thdrun->getDataOut();
//  	this->listOut=this->listOutTemp;
      }
      else if(this->efunc==false){
       	for(i=0; i< this->length; i++){
      	  this->threads[i]->join();
          //this->matOutTemp[i]=this->threads[i]->getListOut();
      }
      this->matOut=this->matOutTemp;
    }
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

  void setFunction(OUT* (*f) (IN*,IN*)){
    this->funcUser=f;
    this->pri=true;
  }
    
  void setLength(int n){
    this->length=n;
  }

 private:
    int i;
    T* (*funcUser)(T*,T*);
    int dist;
    int iter; 
    int numIter;
    bool pri;
    bool efunc;
    Kanga<T,T> * obj;
    Thread<Scan<T>, T> *thdrun;
    int numThreads;
    
    static T* tRun(Scan<T>* scan){
      return scan->run();
    }
     
    T* run(){
      /*
      if(this->iter == this->numIter){
        return this->listOutTemp;
      }
      else{*/
         int i=0;
     this->iter=0;
     this->dist=1;
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
      	
        //if(this->pri==true){
          //this->pri=false;
        	for(i=0;i < this->numThreads;i++){
        	  this->threads[i]->join();
            //printf("%d ",*this->threads[i]->getDataOut());
            //int at= *this->threads[i]->getDataOut();
        	  this->listOutTemp[i+this->dist] = *this->threads[i]->getDataOut();
            //this->listOutTemp[i+this->dist] =at;
          }
      	//} 
        //else{
        /*  this->pri=true;
          for(i=0;i < this->numThreads;i++){
          this->threads[i]->join();
          //printf("%d ",*this->threads[i]->getDataOut());
          int at= *this->threads[i]->getDataOut();
          //this->listOutTemp[i+this->dist] = *this->threads[i]->getDataOut();
          this->listIn[i+this->dist] =at;
         } 
        }*/
        //printf("\n");

      	this->dist=this->dist+this->dist;
        //printf("dist %d\n", this->dist );
    	  this->iter++; 
        
      	//for(int j = 0; j < this->length; j++){
  	      //printf("%d ",this->listOutTemp[j]);
  	    //}
  	   // printf("\n");

        //return this->run();
      }
      return this->listOutTemp;
    }  
    //return this->listOutTemp;
  //}
};

}//end namespace

#endif /* SCAN_H_ */