/*
 Implementa a classe Thread
 Um objeto desta classe cria um thread
*/

#ifndef Thread_H
#define Thread_H

#include "Kanga.h"

#ifdef PTHREADS
  #include <pthread.h>


#elif defined ANAHY

 #include "Anahy-3/SRC/AnahyVM.h"
 #include "Anahy-3/SRC/AnahyJob.h"

#endif

namespace kanga{

template<class IN, class OUT>
class Thread : public Kanga<IN,OUT>{
  public:
    Thread(): dataOut(out) {
     this->dataIn1=NULL;
     this->dataIn2=NULL;
     
     this->dataOutInter=NULL;
     this->obj=NULL;
    }
     
    Thread(const Thread<IN,OUT>& e) : dataOut(e.dataOut){
      if(e.typeFunc==0){
       this->funcUserUm=&e.funcUserUm;
       this->dataIn1=e.dataIn1;
       this->threadData = e.threadData; 
      }
      else{
       this->func_user_dois=e.funcUserDois;
       this->dataIn1=e.dataIn1;
       this->dataIn2=e.dataIn2;
      }
      this->thid=e.thid;
      this->thread=e.thread;
      this->typeFunc=e.typeFunc;
   }
   
   Thread(OUT* (*func)(IN*)): dataOut(out){
    this->funcUserUm=func;
    this->typeFunc=0;
   }
    
   Thread(OUT* (*func)(IN*,IN*)): dataOut(out){
    this->funcUserDois=func;
    this->typeFunc=1;
   }

   Thread(OUT* (*func)(IN*), IN *dataIn): dataOut(out){
      this->funcUserUm=func;
      this->dataIn1=dataIn;
      this->typeFunc=0;
   }

  // Thread(OUT* (*func)(IN*), IN *dataIn,OUT *&dataOut) : dataOut(dataOut){
    //  this->funcUserUm=func;
     // this->dataIn1=dataIn;
     // this->typeFunc=0;
   //}

   Thread(OUT* (*func)(IN*,IN*), IN* dataIn1,IN* dataIn2): dataOut(out){
      this->funcUserDois=func;
      this->dataIn1=dataIn1;
      this->dataIn2=dataIn2;
      this->dataOutInter = new OUT();
      this->typeFunc=1;
    }

   Thread(OUT* (*func)(IN*,IN*), IN* dataIn1,IN* dataIn2,OUT *&dataOut): dataOut(dataOut){
      this->funcUserDois=func;
      this->dataIn1=dataIn1;
      this->dataIn2=dataIn2;
      this->dataOutInter = new OUT();
      this->typeFunc=1;
    }

    Thread(Kanga<IN,OUT> *obj, IN* dataIn, OUT *&dataOut ): dataOut(dataOut){
      this->obj=obj;
      this->dataIn1=dataIn;
      this->typeFunc=2;
    }

    Thread(Kanga<IN,OUT> *obj, IN* dataIn1, IN* dataIn2, OUT *&dataOut ): dataOut(dataOut){
      this->obj=obj;
      this->dataIn1=dataIn1;
      this->dataIn2=dataIn2;
      this->typeFunc=2;
    }

    void start(){
    try{
       if(this->threadFunc==NULL || this->dataIn1==NULL){
         throw KException();
       }
       else{  
         #ifdef PTHREADS
          pthread_create(&thid,NULL, &this->threadFunc, this); 
         
         #elif defined ANAHY
          job.init(&this->threadFunc, this, NULL);
          AnahyVM::fork(&job);
         #endif
       }
      }
      catch(KException& e){
        std::cout << e.what() << std::endl;
        return ;
      }  
    }

    void join(){
      #ifdef PTHREADS
        pthread_join(thid,&(threadReturn));

      #elif defined ANAHY
        AnahyVM::join(&job, &(threadReturn));
      #endif
     
      //AnahyVM::join(&job, &(threadReturn));
      //this->dataOut = static_cast<Thread*> (threadReturn);
    }

    void setFunction(OUT* (*f) (IN*)){
      this->funcUserUm=f;
      this->typeFunc=0;
    }
    
     void setFunc(OUT* (*func)(IN*)){
      this->funcUserDois=func;
      this->typeFunc=1;
    }

    void setDataIn(IN* data){
       this->dataIn1=data; 
    }
    
    void setDataIn(IN* data1,IN* data2){
       this->dataIn1=data1; 
       this->dataIn2=data2; 
    }
    
    void setDataOut(OUT*& data){
      this->dataOut=data;
    }

    OUT * getDataOut(){
       return this->dataOut;
    }
    
    virtual ~Thread(){
      delete obj;
    };

    private:
    OUT * out;  
    IN *dataIn1;
    IN *dataIn2;
    OUT *dataOutInter;
    OUT *&dataOut;
    int typeFunc;
    void *threadReturn;
    OUT* (*funcUserUm)(IN*);
    OUT* (*funcUserDois)(IN*,IN*);
    Kanga<IN,OUT> *obj;
   
    #ifdef PTHREADS
      pthread_t thid;

     #elif defined ANAHY
        AnahyJob job;
     #endif
      

    void run(){
      if(this->typeFunc==0){
        this->dataOutInter= this->funcUserUm(this->dataIn1);
      }
      else if(this->typeFunc==1){
       this->dataOutInter = this->funcUserDois(this->dataIn1,this->dataIn2);
      }
      else if(this->typeFunc==2){
        this->obj->start();
        this->obj->join();
      }
      this->dataOut=this->dataOutInter;
    }

    static void* threadFunc(void *args){
      Thread *th = static_cast<Thread* >(args);
      OUT *value = new OUT();
      th->run();
      return  value; 
    } 
};

}//end namespace
#endif
