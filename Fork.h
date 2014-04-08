/*
 * Fork.h
 *
 *  Created on: 30/09/2013
 *      Author: deives
 */

#ifndef FORK_H_
#define FORK_H_

#include "Thread.h"
#include "DataParallelism.h"

namespace kanga{

template<class IN, class OUT>
class Fork : public DataParallelism<IN,OUT>{
  public:
    Fork(): DataParallelism<IN,OUT>(){
     this->funcUser=NULL;
     this->efunc=NULL;
     this->listObj=NULL;
    }
    
    Fork(const Fork &e) : DataParallelism<IN,OUT>(e){
     this->funcUser=e.funcUser;
     this->efunc=e.efunc;
     this->listObj=e.listObj;
    }
    
    Fork(OUT* (*(*f))(IN*), IN * listIn, OUT *& listOut, int length) : DataParallelism<IN,OUT>(listIn,listOut,length) {
      this->funcUser=f;
      this->efunc=true;
      this->listObj=NULL;    
    }
    
    Fork(OUT* (*(*f))(IN*), int length) : DataParallelism<IN,OUT>(length)
    {
      this->funcUser=f;
      this->efunc=true; 
      this->listObj=NULL;
    }
    
    Fork(Kanga<IN,OUT> * listObj, IN ** matIn, OUT **& matOut, int length) : DataParallelism<IN,OUT>(matIn,matOut,length)
    {
      this->listObj=listObj;
      this->funcUser=NULL;
      this->efunc=false;
    }

    void start(){
      if(this->efunc==true){
	      this->threads= new Kanga<IN,OUT>*[this->length];
      	for(i=0;i<this->length;i++){
          this->listInp[i]=&this->listIn[i];
      	  this->threads[i]=new Thread<IN,OUT>(this->funcUser[i],this->listInp[i]);
      	  this->threads[i]->start();
      	}
      }
      else if(this->efunc==false){
	      this->threads= new Kanga<IN,OUT>*[this->length];
      	for(this->i=0; i < this->length; i++) {
       	  this->threads[i]=this->listObj[i]->clone(this->matIn[i],this->matOutTemp[i]);
      	  this->threads[i]->start();
      	}
      }
    }

    void join(){
      if(this->efunc==true){
        this->listOut=this->listOutTemp;
         for(i=0; i< this->length; i++){
      	   this->threads[i]->join();
	         this->listOutTemp[i]= *this->threads[i]->getDataOut();
	       }
	       
      }
      else if(this->efunc==false){
        this->matOut=this->matOutTemp;
      	for(i=0; i< this->length; i++){
      	  this->threads[i]->join();
      	  //this->matOutTemp[i]=this->threads[i]->getListOut();
        }
              
      }
    }

    Kanga<IN,OUT> * clone(){
      return new Fork<IN,OUT>(this->funcUser,this->length);
    }

    Kanga<IN,OUT> * clone(IN * listIn, OUT *& listOut){
      return new Fork<IN,OUT>(this->funcUser,listIn,listOut,this->length);
    }
    
    virtual ~Fork(){
      delete this->obj;
    }

    void setFunction(OUT* (*(*funcUser)) (IN*)){
      this->funcUser=f;
      this->efunc=true;
    }
    
    void setLength(int n){
      this->length=n;
    }
    
  private:
    int i;
    OUT* (*(*funcUser)) (IN*);
    Kanga<IN,OUT> * obj;
    bool efunc;
};

}//end namespace
#endif /* FORK_H_ */
