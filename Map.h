/*
 * Map.h
 * Implementa o esqueleto Map.
 * Aplica a fução de entrada em cada elemento do vetor de entrada
 * Uma thread para cada elemento do vetor de entrada. 
 *  
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
     this->obj=NULL;
    }
    
    Map(const Map<IN,OUT> &e) : DataParallelism<IN,OUT>(e){
     this->funcUser=e.funcUser;
     this->efunc=e.efunc;
     this->obj=e.obj;
    }
    
    Map(OUT* (*f) (IN*), IN * listIn, OUT *& listOut, int length) : DataParallelism<IN,OUT>(listIn,listOut,length){
      this->funcUser=f;
      this->efunc=true;
      this->obj=NULL;
    }
    
    Map(OUT* (*f) (IN*), int length) : DataParallelism<IN,OUT>(length){
      this->funcUser=f;
      this->efunc=true; 
      this->obj=NULL;
    }
    
    Map(Kanga<IN,OUT> * obj, IN ** matIn, OUT **& matOut, int length) : DataParallelism<IN,OUT>(matIn,matOut,length){      
      this->obj=obj;
      this->funcUser=NULL;
      this->efunc=false;
    }
    
    void start();
    void join();
    
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
    
    private:
      int i;
      OUT ** listOutp;
      OUT* (*funcUser) (IN*); // ponteiro  para a função do usuario
      Kanga<IN,OUT> * obj; // ponteiro para o objeto da composicao
      bool efunc; // bool para determinar que execucao: true -> execucao basica; false -> execucao da composicao
};

// Implementacao do start
// Um thread é criado para cada elemento do vetor de entrada
// Dispara os threads
template<class IN, class OUT>
void Map<IN,OUT>::start(){
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
            this->threads[i]=new Thread<IN,OUT>(this->funcUser,this->listInp[i]);
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
void Map<IN,OUT>::join(){
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
    else throw KException(); // é executada caso o objeto do Map não foi inicializado corretamente
  }
  catch(KException& e){ 
    std::cout << e.what() << std::endl;
    return ;
  }  
}

}//end namespace

#endif /* MAP_H_ */
