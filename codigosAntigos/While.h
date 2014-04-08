/*
 * WHILE.h
 *
 *  Created on: 17/10/2013
 *      Author: deives
 */

#ifndef WHILE_H_
#define WHILE_H_

#include "Thread.h"
#include "ParallelInterface.h"

template<class IN, class OUT>
class While : public ParallelInterface<IN,OUT> {
  private:
    ParallelInterface<INt,OUTt> *obj;
    bool cond;
    Thread<While<IN,OUT> *, OUT> *thdrun;
    
  public:
    While(){
      this->obj=NULL;
            
    }
    
    While(const WHILE<IN,OUT>& e){
      this->obj = e.obj;
      this->cond=e.cond;
    }
    
    While(ParalleIInterface<IN,OUT>* obj){
      this->obj=obj;
    }
    
    static OUT run(WHILE<IN,OUT> *){
      
    }
    void start(){
//      thdrun = new Thread<WHILE<INt,OUTt,INf,OUTf> *,ParallelInterface<IN,OUT>* >(WHILE<INt,OUTt,INf,OUTf>::run,this);
//      thdrun->start();
    }
    
    void join(){
//       thdrun->join();
//       this->objOut=this->thdrun->getDataOut();
    }
    
    virtual ~While(){
      
    }
};

#endif /* While_H_ */