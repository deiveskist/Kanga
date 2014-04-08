/*
 * Zip.h
 *
 *  Created on: 31/01/2014
 *      Author: deives
 */

#ifndef ZIP_H_
#define ZIP_H_

#include "Thread.h"
#include "DataParallelism.h"

namespace kanga{

template<class IN, class OUT>
class Zip : public DataParallelism<IN,OUT>{
 public:
  Zip(): DataParallelism<IN,OUT>(){
    this->funcUser=NULL;
    this->efunc=NULL;
    this->listIn2=NULL;
  }
    
  Zip(const Zip<IN,OUT> &e) : DataParallelism<IN,OUT>(e){
    this->funcUser=e.funcUser;
    this->efunc=e.efunc;
    this->listIn2=e.listIn2;
  }
    
  Zip(OUT* (*f) (IN*,IN*), IN * listIn,IN * listIn2, OUT *& listOut, int length) : DataParallelism<IN,OUT>(listIn,listOut,length){
    this->funcUser=f;
    this->efunc=true;
    this->listIn2=listIn2;
    this->obj=NULL; 
  }
    
  Zip(OUT* (*f) (IN*,IN*), int length) : DataParallelism<IN,OUT>(length){
    this->funcUser=f;
    this->efunc=true; 
    this->obj=NULL; 
    this->listIn2=NULL;
  }
    
  Zip(Kanga<IN,OUT> * obj, IN ** matIn, OUT **& matOut, int length) : DataParallelism<IN,OUT>(matIn,matOut,length){      
    this->obj=obj;
    this->funcUser=NULL;
    this->efunc=false;
  }
    
  void start(){
    if(this->efunc==true){
	    this->threads= new Kanga<IN,OUT>*[this->length];
    	for(i=0; i < this->length; i++) {
        this->listInp[i]=&this->listIn[i];
        this->threads[i]=new Thread<IN,OUT>(this->funcUser,&this->listIn[i],&this->listIn2[i]);
    	  this->threads[i]->start();
     	}     
    }
    else if(this->efunc==false){
      this->threads= new Kanga<IN,OUT>*[this->length];
     	for(i=0; i < this->length; i++){
        this->threads[i]->start();
    	}
    }
  }
    
  void join(){
    if(this->efunc==true){
      this->listOut=this->listOutTemp;
     	for(i=0; i< this->length; i++){
    	  this->threads[i]->join();
	      this->listOutTemp[i]=*this->threads[i]->getDataOut();
        //this->listOutTemp[i]= this->threads[i]->getDataOut();
	    }
    }
    else if(this->efunc==false){
      this->matOut=this->matOutTemp;
     	for(i=0; i< this->length; i++){
     	  this->threads[i]->join();
    	  //this->matOutTemp[i]=this->threads[i]->getDataOut();
      }    
    }
  }
    
  Kanga<IN,OUT> * clone(){
    return new Zip<IN,OUT>(this->funcUser,this->length);
  }

  Kanga<IN,OUT> * clone(IN * listIn,IN * listIn2, OUT *& listOut){
    return new Zip<IN,OUT>(this->funcUser,listIn,listIn2,listOut,this->length);
  }
  
  virtual ~Zip(){
    delete obj;
    delete listIn2;
    delete listOutp;
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
    OUT ** listOutp;
    IN * listIn2;
    OUT* (*funcUser) (IN*,IN*);
    Kanga<IN,OUT> * obj;
    bool efunc;
};

}//end namespace
#endif /* Zip_H_ */