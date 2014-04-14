/*
 * Fork.h
 * Implementa o esqueleto Fork.
 * Uma função e um thread para cada elemento do vetor de entrada
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
    
    Fork(OUT* (*(*f))(IN*), IN * listIn, OUT *& listOut, int length) : DataParallelism<IN,OUT>(listIn,listOut,length){
      this->funcUser=f;
      this->efunc=true;
      this->listObj=NULL;    
    }
    
    Fork(OUT* (*(*f))(IN*), int length) : DataParallelism<IN,OUT>(length){
      this->funcUser=f;
      this->efunc=true; 
      this->listObj=NULL;
    }
    
    Fork(Kanga<IN,OUT> ** listObj, IN ** matIn, OUT **& matOut, int length) : DataParallelism<IN,OUT>(matIn,matOut,length){
      this->listObj=listObj;
      this->funcUser=NULL;
      this->efunc=false;
    }

    void start();
    void join();
  
    Kanga<IN,OUT> * clone(){
      return new Fork<IN,OUT>(this->funcUser,this->length);
    }

    Kanga<IN,OUT> * clone(IN * listIn, OUT *& listOut){
      return new Fork<IN,OUT>(this->funcUser,listIn,listOut,this->length);
    }
    
    virtual ~Fork(){
      delete this->listObj;
    }

    void setFunction(OUT* (*(*f)) (IN*)){
      this->funcUser=f;
      this->efunc=true;
    }
    
    void setLength(int n){
      this->length=n;
    }
    
  private:
    int i;
    OUT* (*(*funcUser)) (IN*); // ponteiro para o vetor de funcoes
    bool efunc; // bool para determinar que execucao: true -> execucao basica; false -> execucao da composicao
    Kanga<IN,OUT> ** listObj; // ponteiro para o vetor de objetos
};


// Implementacao do start
// Um thread é criado para cada elemento do vetor de entrada
// E um existe uma função ou um objeto para cada elemento do vetor de entrada
template<class IN, class OUT>
void Fork<IN,OUT>::start(){
  try{
    if(this->efunc==true){// aplica as funcoes em cada elementos
      try{
          if(this->funcUser==NULL || this->listIn==NULL || this->length==0){ // verifica se o objeto foi inicializado corretamente 
            throw KException();
          }
          else{  
            this->threads= new Kanga<IN,OUT>*[this->length];
            for(i=0;i<this->length;i++){
              this->listInp[i]=&this->listIn[i];
              this->threads[i]=new Thread<IN,OUT>(this->funcUser[i],this->listInp[i]);
              this->threads[i]->start();
            }
          }  
        }
        catch(KException& e){
          std::cout << e.what() << std::endl;
          return ;
        }
    }
    else if(this->efunc==false){//realiza a composição dos objetos
      try{
        if(this->listObj==NULL || this->length==0){ 
          throw KException();
        }
        else{  
            this->threads= new Kanga<IN,OUT>*[this->length];
            for(this->i=0; i < this->length; i++) {
              this->threads[i]=this->listObj[i]->clone(this->matIn[i],this->matOutTemp[i]);
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

template<class IN, class OUT>
void Fork<IN,OUT>::join(){
  try{
    if(this->efunc==true){// realiza o join em cada thread da função
      this->listOut=this->listOutTemp;
      for(i=0; i< this->length; i++){
        this->threads[i]->join();
        this->listOutTemp[i]= *this->threads[i]->getDataOut();
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
#endif /* FORK_H_ */