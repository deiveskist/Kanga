#ifndef EsqueletosSM_H
#define EsqueletosSM_H

#include "Esqueleto.h"

template< class IN, class OUT>
class EsqueletoSM  {
 private:	    
    Esqueleto<IN,OUT> *esqueleto;
    static OUT foo(IN){ return NULL;}	
 protected:
   // virtual IN * split(IN *list_in, int n_thread)const=0;
  //  virtual OUT * merge(OUT *list_out1, int n_thread,  OUT out_split)const{};
    
 public:	
  EsqueletoSM(Esqueleto<IN,OUT> * esq){
     this->esqueleto = esq;  
   }
   
   EsqueletoSM(const Esqueleto<IN,OUT>& e){
       this->esqueleto=esqueleto;
   }
    
   EsqueletoSM(const Esqueleto<IN,OUT>*& e){
       this->esqueleto=esqueleto;
   }
    
   EsqueletoSM(){
   
   }
   virtual ~EsqueletoSM(){};
};

#endif