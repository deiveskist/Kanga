/*
 * Reduce.h
 */

#ifndef REDUCE_H_
#define REDUCE_H_
#include "Thread.h"
#include "DataParallelism.h"

namespace kanga{

template<class T>
class Reduce : public DataParallelism<T,T>{
  public:
    Reduce(): DataParallelism<T,T>(){
      this->funcUser=NULL;
      this->efunc=NULL;
      this->pri=true;
    }

    Reduce(const Reduce &e): DataParallelism<T,T>(e){
      this->funcUser=e.funcUser;
      this->efunc=e.efunc;
      this->pri=e.pri;
    }

    Reduce( T* (*f) (T*,T*), T * listIn, T *& listOut, int length) : DataParallelism<T,T>(listIn,listOut,length) {
      this->funcUser=f;
      this->efunc=true;
      this->pri=true;
    }

    Reduce(T* (*f) (T*,T*), int length) : DataParallelism<T,T>(length){
      this->funcUser=f;
      this->efunc=true;
      this->pri=true;
    }

    Reduce(Kanga<T,T> * obj, T ** matIn,T *& listOut, int length ) : DataParallelism<T,T>(matIn,listOut,length){
      this->obj=obj;
      this->funcUser=NULL;
      this->efunc=false;
      this->pri=true;
    }
   
    void start();
    void join();
       
    Kanga<T,T> * clone(){
      return new Reduce<T>(this->funcUser,this->length);
    }

    Kanga<T,T> * clone(T * listIn, T *& listOut){
      return new Reduce<T>(this->funcUser,listIn,listOut,this->length);
    }
     
    virtual ~Reduce(){
      delete this->obj;
    }
    
    void setFunction(T* (*f) (T*,T*)){
      this->funcUser=f;
      this->efunc=true;
    }
    
  private:
    
    int i;
    T *ptrData;
    T * (*funcUser) (T*,T*); // ponteiro para a funcao do usuario
    Kanga<T,T> * obj; // ponteiro para o objeto da composicao
    bool efunc;
    bool pri;
    bool impar;
    T dataAux;
    T* matAux;
    Thread< Reduce<T> , T > *thdrun;// ponteiro para o thread 
    
    static T* tRun(Reduce<T> *red){
      return red->run();
    }

    static T* tRunComp(Reduce<T> *red){
      return red->runComp();
    }

    T* run();
    T* runComp();
};

template<class T>
void Reduce<T>::start(){
  try{
      if(this->efunc==true){
        try{
          if(this->funcUser==NULL || this->listIn==NULL || this->length==0){ // verifica se o objeto foi inicializado corretamente 
            throw KException();
          }
          else{  
            this->threads= new Kanga<T,T>*[this->length];
            thdrun = new Thread<Reduce<T> , T>(&Reduce<T>::tRun,this);
            thdrun->start();
          }
        }
        catch(KException& e){
          std::cout << e.what() << std::endl;
          return ;
        }
      }
      else if(this->efunc==false){
        try{
          if(this->obj==NULL || this->length==0){ 
            throw KException();
          }
          else{    
             this->threads= new Kanga<T,T>*[this->length];
             thdrun = new Thread<Reduce<T> , T>(&Reduce<T>::tRunComp,this);
             thdrun->start();

          }
        }
        catch(KException& e){
          std::cout << e.what() << std::endl;
          return ;
        }
      }  
      else throw KException();
  }
  catch(KException& e){ 
    std::cout <<e.what() << std::endl;
    return ;
  }
}

template<class T>
void Reduce<T>::join(){
  try{
    if(this->efunc==true){
      thdrun->join();
      this->listOut=this->thdrun->getDataOut();
    }
    else if(this->efunc==false){
      thdrun->join();
      this->listOut=this->thdrun->getDataOut();
    }      
    else throw KException();
  }
  catch(KException& e){ 
    std::cout <<e.what() << std::endl;
    return ;
  }
}

// implementa a reducao de um vetor
template<class T>
T* Reduce<T>::run(){
  if(this->length == 1){// base da recursao // o tamanho do vetor deve ser igual a um 
    this->listInp[0]=&this->listOutTemp[0];
    return this->listInp[0];
  }
  else{
    if(this->pri==true){// primeira etapa da recursão
      this->pri=false;
      if(this->length%2==0){ // verifica se o tamanho do vetor é par ou impar
        this->length=this->length/2;
      }
      else{
        this->dataAux=this->listIn[this->length-1];
        this->length= this->length/2; 
        this->length++;
        this->impar=true;
        this->listOutTemp[this->length+1]=this->dataAux;
      }
  
      for(i=0;i<this->length;i++){
        this->listInp[2*i]=&this->listIn[2*i];
        this->listInp[(2*i)+1]=&this->listIn[(2*i)+1];
        this->threads[i]=new Thread<T,T>(this->funcUser,this->listInp[2*i],this->listInp[(2*i)+1]);
        this->threads[i]->start();
      }
    }
    else{// resto das recurcoes
      if(this->length%2==0){ 
        this->length=this->length/2;
      }
      else{
        this->dataAux=this->listOutTemp[this->length-1];
        this->length=this->length/2; 
        this->length++;
        this->impar=true;
        this->listOutTemp[this->length+1]=this->dataAux;
      }

      for(i=0;i< this->length;i++){
        this->listInp[2*i]=&this->listOutTemp[2*i];
        this->listInp[(2*i)+1]=&this->listOutTemp[(2*i)+1];
        this->threads[i]=new Thread<T,T>(this->funcUser,this->listInp[2*i],this->listInp[(2*i)+1]);
        this->threads[i]->start();
      }
    }

    for(i=0;i< this->length;i++){// loop para sincronizar os threads
      this->threads[i]->join();
      this->listOutTemp[i] = *this->threads[i]->getDataOut();
    }
    if(this->impar==true){
      this->listOutTemp[this->length-1]=this->dataAux;
      this->impar=false;
    }
      
    return this->run();
  }//fecha o else
}//fecha do metodo 


// implementa a execucao da composicao do Reduce
template<class T>
T* Reduce<T>::runComp(){
  if(this->length == 1){// base da recursao // o tamanho do vetor deve ser igual a um 
    return this->matOutTemp[0];
  }
  else{
    if(this->pri==true){ // primeira etapa da recursão
      this->pri=false;
      if(this->length%2==0){ // verifica se o tamanho do vetor é par ou impar
        this->length=this->length/2;
      }
      else{
        this->matAux=this->matIn[this->length-1];
        this->length= this->length/2; 
        this->length++;
        this->impar=true;
        this->matOutTemp[this->length+1]=this->matAux;
      }
      for(i=0;i<this->length;i++){// dispara os threads
          this->threads[i]=this->obj->clone(this->matIn[2*i],this->matIn[(2*i)+1],this->matOutTemp[i]);
          this->threads[i]->start();
        }
      }
      else{// resto das recurcoes
        if(this->length%2==0){ 
          this->length=this->length/2;
        }
        else{
          this->matAux=this->matOutTemp[this->length-1];
          this->length=this->length/2; 
          this->length++;
          this->impar=true;
          this->matOutTemp[this->length+1]=this->matAux;
        }

        for(i=0;i< this->length;i++){// dispara os threads
            this->threads[i]=this->obj->clone(this->matOutTemp[2*i],this->matOutTemp[(2*i)+1],this->matOutTemp[i]);
            this->threads[i]->start();
        }
      }

      for(i=0;i< this->length;i++){// loop para sincronizar os threads
          this->threads[i]->join();
      }
      
      if(this->impar==true){
        this->matOutTemp[this->length-1]=this->matAux;
        this->impar=false;
      }
      return this->runComp();
  }//fecha o else
}//fecha do metodo 

};//end namespace
#endif /* REDUCE_H_ */