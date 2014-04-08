/*
 * For.h
 *
 *  Created on: 19/10/2013
 *      Author: deives
 */

#ifndef FOR_H_
#define FOR_H_

#include "Thread.h"
#include "ParallelInterface.h"

template<class IN, class OUT>
class For : public ParallelInterface<IN,OUT> {
  public:
    For(){
      this->obj=NULL;
      this->iter=0;      
    }
    
    For(const For<IN,OUT>& e){
      this->obj = e.obj;
      this->iter=e.iter;
    }
    
    For(ParalleIInterface<IN,OUT>* obj,int iter){
      this->obj=obj;
      this->iter=iter;
    }
    
    void start(){
      thdrun = new Thread<WHILE<INt,OUTt,INf,OUTf> *,ParallelInterface<IN,OUT>* >(WHILE<INt,OUTt,INf,OUTf>::run,this);
      thdrun->start();
    }
    
    void join(){
      thdrun->join();
      this->objOut=this->thdrun->getDataOut();
    }
    
    virtual ~For(){
      
    }
    
  private:
    ParallelInterface<INt,OUTt> *obj;
    int iter;
    Thread<WHILE<IN,OUT> *, OUT> *thdrun;
    bool pri;
    
    static OUT run(For<IN,OUT> * forr){
      int i;
      OUT aux;
      for(i=0;i < forr->iter; i++ ){
	if(forr->pri==true){
	 forr->obj->setDataIn(seq->dataIn);
	 forr->obj->start();
	 forr->obj->join();
	 aux=forr->obj->getDataOut();
	 forr->pri=false;
	}
	else{
	  forr->obj->setDataIn(aux);
	  forr->obj->start();
	  forr->obj->join();
	  aux=forr->obj->getDataOut();	
 	}
      }
    }
};

#endif /* For_H_ */