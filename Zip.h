/*
 * Zip.h
 * Implementa o Esqueleto Zip
 *  Reduz dois vetores a um vetor utilizando a funcao do usuario 
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
    
  void start();
  void join();
    
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
  }
    
  private:
    int i;
    OUT ** listOutp;
    IN * listIn2;
    OUT* (*funcUser) (IN*,IN*); // ponteiro para a funcao do usuario
    Kanga<IN,OUT> * obj;      // ponteiro para o objeto da composicao
    bool efunc;              // bool para determinar que execucao: true -> execucao basica; false -> execucao da composicao 
};


// Implementacao do start
// Um thread é criado para cada elemento do vetor de entrada
// Dispara os threads
template<class IN, class OUT>
void Zip<IN,OUT>::start(){
  try{
    if(this->efunc==true){// aplica a função em cada elementos
      try{
        if(this->funcUser==NULL || this->listIn==NULL || this->length==0){ // verifica se o objeto foi inicializado corretamente 
          throw KException();
        }
        else{  
          this->threads= new Kanga<IN,OUT>*[this->length];
          for(i=0; i < this->length; i++){ // cria os threads e invoca o método start de cada thread
            this->listInp[i]=&this->listIn[i];
            this->threads[i]=new Thread<IN,OUT>(this->funcUser,&this->listIn[i],&this->listIn2[i]);
            this->threads[i]->start();
          }     
        }
      }
      catch(KException& e){
        std::cout << e.what() << std::endl;
        return ;
      }
    }
    else if(this->efunc==false){ //realiza a composição dos objetos
      try{
        if(this->obj==NULL || this->length==0){ 
          throw KException();
        }
        else{  
          this->threads= new Kanga<IN,OUT>*[this->length];
          for(i=0; i < this->length; i++){// realiza
            this->threads[i]=this->obj->clone(this->matIn[i],this->matOutTemp[i]);
            this->threads[i]->start();
          }
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

// implementa o método join
// realiza a sincronizacao do threads
template<class IN, class OUT>  
void Zip<IN,OUT>::join(){
 try{
  if(this->efunc==true){
    this->listOut=this->listOutTemp;
    for(i=0; i< this->length; i++){// realiza o join em cada thread da função
       this->threads[i]->join();
       this->listOutTemp[i]=*this->threads[i]->getDataOut();
      }
    }
    else if(this->efunc==false){// realiza a sincronização dos objetos compostos
      this->matOut=this->matOutTemp;
      for(i=0; i< this->length; i++){
        this->threads[i]->join();
      }
    }
    else throw KException(); // é executada caso o objeto do Zip não foi inicializado corretamente
  }
  catch(KException& e){ 
    std::cout << e.what() << std::endl;
    return ;
  }  
}

}//end namespace
#endif /* Zip_H_ */