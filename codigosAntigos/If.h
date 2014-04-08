/*
 * If.h
 *
 *  Created on: 17/10/2013
 *      Author: deives
 */

#ifndef IF_H_
#define IF_H_

#include "Thread.h"
#include "ParallelInterface.h"

template<class INt, class OUTt, class INf, class OUTf>
class If {
  private:
    ParallelInterface<INt,OUTt> *objTrue;
    ParallelInterface<INf,OUTf> *objFalse;
    bool cond;
    ParallelInterface<INf,OUTf> *objOut;
    Thread<If<INt,OUTt,INf,OUTf> *,ParallelInterface<IN,OUT> *> *thdrun;
  public:
    If(){
      this->objTrue=NULL;
      this->objFalse=NULL;
    }
    
    If(const If<INt,OUTt,INf,OUTf>& e){
      this->objTrue = e.objTrue;
      this->objFalse=e.objFalse;
    }
    
    If(ParalleIInterface<INt,OUTt>* objTrue, ParalleIInterface<INf,OUTf> *objFalse){
      this->objTrue=objTrue;
      this->objFalse=objFalse;
    }
    
    static ParallelInterface<IN,OUT>* run(If<INt,OUTt,INf,OUTf> *iff){
      if(iff->cond==true){
	return iff->objTrue;
      }
      else{
	return iff->objFalse;
      }      
    }
    void start(){
     thdrun = new Thread<If<INt,OUTt,INf,OUTf> *,ParallelInterface<IN,OUT>* >(If<INt,OUTt,INf,OUTf>::run,this);
     thdrun->start();
    }
    
    void join(){
      thdrun->join();
      this->objOut=this->thdrun->getDataOut();
    }
    
    virtual ~If(){
      
    }
};

#endif /* If_H_ */