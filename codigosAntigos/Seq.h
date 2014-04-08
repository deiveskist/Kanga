/*
 * Seq.h
 *
 *  Created on: 18/10/2013
 *      Author: deives
 */

#ifndef SEQ_H_
#define SEQ_H_


#include "Thread.h"
#include "ParallelInterface.h"

template<class IN, class OUT>
class Seq : public ParallelInterface<IN,OUT>{
  public:
    Seq(){
      this->sequence=NULL;
      this->length=0;
      this->end=0;
    }

    Seq(const Seq<IN,OUT> &e){
      this->sequence=e.sequence;
      this->length=e.length;
      this->end=e.end;
    }

    Seq(int length, IN dataIN, OUT dataOut){
      this->sequence= new Threads[length];
      this->length=length;
      this->dataIn=dataIn;
      this->dataOut=dataOut;
    }
    
    void add(ParallelInterface<IN,OUT> * obj){
      this->sequence[this->end].thread=obj;
      this->end++;
    }

    void start(){
      thdrun = new Thread< Seq<IN,OUT> *,OUT>(Seq<IN,OUT>::run,this);
      thdrun->start();
    }
    
    void join(){
      thdrun->join();
      this->dataOut=this->thdrun->getDataOut();
    }

 private:
   struct Threads{
     ParallelInterface<IN,OUT> *thread;
   };
   
   Threads *sequence;
   int length;
   int end;
   IN dataIn;
   OUT dataOut;
   
   
   Thread<Seq<IN,OUT> *,OUT> *thdrun;
   bool pri;
   
   static OUT run(Seq<IN,OUT> *seq){
     OUT aux;
     int i=0;
     for(i=0; i< seq->length; i++){
       if(seq->pri==true){
	 seq->sequence[i].thread->setDataIn(seq->dataIn);
	 seq->sequence[i].thread->start();
	 seq->sequence[i].thread->join();
	 aux=seq->sequence[i].thread->getDataOut();
	 seq->pri=false;
      }
      else{
	seq->sequence[i].thread->setDataIn(aux);
	seq->sequence[i].thread->start();
	seq->sequence[i].thread->join();
	aux=seq->sequence[i].thread->getDataOut();	
 	}
    }
    return aux;
    }
};


#endif /* Seq_H_ */ 