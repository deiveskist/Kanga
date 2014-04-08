/*
 * Map.h
 *
 *  Created on: 30/10/2013
 *      Author: deives
 */

#ifndef MAP_H_
#define MAP_H_


#include "Thread.h"
#include "DataParallelism.h"

namespace kanga{

template<class IN, class OUT>
class Map : public DataParallelism<IN,OUT>{
      
  public:
    Map(): DataParallelism<IN,OUT>(){
     this->funcUser=NULL;
     this->efunc=NULL;
    }
    
    Map(const Map<IN,OUT> &e) : DataParallelism<IN,OUT>(e){
     this->funcUser=e.funcUser;
     this->efunc=e.efunc;
    }
    
    Map(OUT* (*f) (IN*), IN * listIn, OUT *& listOut, int length) : DataParallelism<IN,OUT>(listIn,listOut,length)
    {
      this->funcUser=f;
      this->efunc=true;
     
     }
    
    Map(OUT* (*f) (IN*), int length) : DataParallelism<IN,OUT>(length)
    {
      this->funcUser=f;
      this->efunc=true; 
    }
    
    Map(Kanga<IN,OUT> * obj, IN ** matIn, OUT **& matOut, int length) : DataParallelism<IN,OUT>(matIn,matOut,length)
    {      
      this->obj=obj;
      this->funcUser=NULL;
      this->efunc=false;
    }
    
    void start(){
      if(this->efunc==true){
	      this->threads= new Kanga<IN,OUT>*[this->length];
      	for(i=0; i < this->length; i++) {
          this->listInp[i]=&this->listIn[i];
          this->threads[i]=new Thread<IN,OUT>(this->funcUser,this->listInp[i]);
      	  this->threads[i]->start();
      	}     
      }
      else if(this->efunc==false){
        this->threads= new Kanga<IN,OUT>*[this->length];
      	for(i=0; i < this->length; i++){
          //this->obj->setDataOut(this->matOutTemp[i]);
      	  //this->threads[i]=this->obj->clone(this->matIn[i],this->matOutTemp[i]);
          this->threads[i]=this->obj->clone(this->matIn[i],this->matOutTemp[i]);
      	  //this->threads[i]->setDataOut(this->matOutTemp[i]);
      	  //this->threads[i]->setDataIn(this->matIn[i]);
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
      return new Map<IN,OUT>(this->funcUser,this->length);
    }

    Kanga<IN,OUT> * clone(IN * listIn, OUT *& listOut){
      return new Map<IN,OUT>(this->funcUser,listIn,listOut,this->length);
    }
  
    virtual ~Map(){
      delete this->obj;
    }

    void setFunction(OUT* (*f) (IN*)){
      this->funcUser=f;
      this->efunc=true;
    }
    
    void setLength(int n){
      this->length=n;
    }
   
   
    private:
      int i;
      OUT ** listOutp;
      OUT* (*funcUser) (IN*);
      Kanga<IN,OUT> * obj;
      bool efunc;
};

}//end namespace
#endif /* MAP_H_ */
