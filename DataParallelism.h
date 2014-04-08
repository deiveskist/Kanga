/*
 * DataParallelism.h
 *
 *  Created on: 30/10/2013
 *      Author: deives
 */

#ifndef DATAPARALLELISM_H_
#define DATAPARALLELISM_H_

#include "Kanga.h"
#include "Thread.h"

namespace kanga{ 

template< class IN, class OUT>
class DataParallelism : public Kanga<IN,OUT> {
 public:

  DataParallelism() : listOut(v), matOut(m){
    this->length=0;
    this->listIn=NULL;
    this->listOutTemp=NULL;
    this->listOut=NULL;
    this->dataOut=NULL;
    this->matIn=NULL;
    this->matOutTemp=NULL;
    this->matOut=NULL;
    this->threads=NULL;
  }
  
  DataParallelism(const DataParallelism<IN,OUT> &e) : listOut(e.listOut), matOut(e.matOut){
    this->length=e.length;
    this->listIn=e.listIn;
    this->listOutTemp=e.listOutTemp;
    this->matIn=e.matIn;
    this->matOutTemp=e.matOutTemp;
    this->threads=e.threads;
   }

  DataParallelism(IN * listIn, OUT *& listOut, int length): listOut(listOut), matOut(m){
    this->listIn=listIn;
    this->length=length;
    this->listOutTemp = new OUT[length];
    this->listInp= new IN*[length];
  }
   
  DataParallelism(IN ** matIn, OUT *& listOut, int length) : matOut(m),listOut(listOut){
    this->matIn=matIn;
    this->length=length;
    this->matOutTemp= new OUT*[length];
    this->listOutTemp= new OUT[length];
    this->listInp= new IN*[length];
  }

  DataParallelism(IN ** matIn, OUT **& matOut, int length) : matOut(matOut),listOut(v){
    this->matIn=matIn;
    this->length=length;
    this->matOutTemp= new OUT*[length];
    this->listInp= new IN*[length];
  }
  
  DataParallelism(int length): matOut(m),listOut(v) {
    this->listIn= new IN[length];
    this->listOutTemp = new OUT[length];
    this->length=length;    
    this->listInp= new IN*[length];
  }
  
  void setDataIn(IN *listIn){
    this->listIn=listIn;
  }
  
  void setDataOut(OUT *&listOut){
      this->listOut=listOut;
  }
    
  OUT * geDataOut(){
    return this->listOut;
  } 
  
  virtual ~DataParallelism(){
    delete this->listIn;
    delete this->listOut;
    delete this->matIn;
    delete this->matOut;
    delete this->matOutTemp;
    delete this->listOutTemp;
    delete this->threads;
  }
  
  
 protected:
  Kanga<IN,OUT> **threads;
  int length;
  IN *listIn;
  OUT *&listOut;
  OUT *listOutTemp;
  IN **matIn;
  OUT **&matOut;
  OUT **matOutTemp;
  OUT **m;
  OUT *v;
  IN **listInp; 

};

}//end namespace

#endif /* DATAPARALLELISM_H_ */
