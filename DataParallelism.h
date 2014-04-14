/* Classe que modela os esqueletos de paralelismo de dados
 * armazena varaveis dos esqueletos: Map, Reduce, Zip, Fork, Scan, MapReduce
 */

#ifndef DATAPARALLELISM_H_
#define DATAPARALLELISM_H_

#include "Kanga.h"
#include "Thread.h"

namespace kanga{ 

template< class IN, class OUT>
class DataParallelism : public Kanga<IN,OUT> {
 public:
  DataParallelism() : listOut(v), matOut(m){
    this->length=0;
    this->listIn=NULL;
    this->listOutTemp=NULL;
    this->listOut=NULL;
    this->matIn=NULL;
    this->matOutTemp=NULL;
    this->matOut=NULL;
    this->threads=NULL;
  }
  
  DataParallelism(const DataParallelism<IN,OUT> &e) : listOut(e.listOut), matOut(e.matOut){
    this->length=e.length;
    this->listIn=e.listIn;
    this->listOutTemp=e.listOutTemp;
    this->matIn=e.matIn;
    this->matOutTemp=e.matOutTemp;
    this->threads=e.threads;
   }

  DataParallelism(IN * listIn, OUT *& listOut, int length): listOut(listOut), matOut(m){
    this->listIn=listIn;
    this->length=length;
    this->listOutTemp = new OUT[length];
    this->listInp= new IN*[length];
    this->matIn=NULL;
    this->matOutTemp=NULL;
    this->matOut=NULL;
  }
   
  DataParallelism(IN ** matIn, OUT *& listOut, int length) : matOut(m),listOut(listOut){
    this->matIn=matIn;
    this->length=length;
    this->matOutTemp= new OUT*[length];
    this->listOutTemp= new OUT[length];
    this->listInp= new IN*[length];
    this->listIn=NULL;
    this->listOut=NULL;
  }

  DataParallelism(IN ** matIn, OUT **& matOut, int length) : matOut(matOut),listOut(v){
    this->matIn=matIn;
    this->length=length;
    this->matOutTemp= new OUT*[length];
    this->listInp= new IN*[length];
  }
  
  DataParallelism(int length): matOut(m),listOut(v) {
    this->listIn= new IN[length];
    this->listOutTemp = new OUT[length];
    this->length=length;    
    this->listInp= new IN*[length];
    this->matIn=NULL;
    this->matOutTemp=NULL;
    this->matOut=NULL;
  }
  
  void setDataIn(IN *listIn){// seta o vetor de entrada
    this->listIn=listIn;
  }
  
  void setDataOut(OUT *&listOut){// seta a referencia para o vetor de saída
      this->listOut=listOut;
  }

  void setLength(int n){// seta o tamanho do vetor de entrada
    this->length=n;
  }
    
  OUT * getDataOut(){
    return this->listOut;
  } 
  
  virtual ~DataParallelism(){
    delete this->listIn;
    //delete this->listOut;
    delete this->matIn;
    //delete this->matOut;
    delete this->matOutTemp;
    //delete this->listOutTemp;
    delete this->threads;
  }
  
  
 protected:
  Kanga<IN,OUT> **threads;
  int length; // tamanho do vetor de entrada
  IN *listIn; // ponteiro para o vetor de entrada
  OUT *&listOut; // referencia para o vetor de saida
  OUT *listOutTemp; // ponteiro para a memoria do vetor de saida
  IN **matIn; // ponteiro para o vetor de ponteiros
  OUT **&matOut;
  OUT **matOutTemp;
  OUT **m;
  OUT *v;
  IN **listInp; 

};

}//end namespace

#endif /* DATAPARALLELISM_H_ */
