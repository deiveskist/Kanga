#ifndef Esqueleto_IF_H
#define Esqueleto_IF_H

#include "Esqueleto.h"

template< class IN, class OUT>
class FOR : public Esqueleto<IN,OUT>{
    Esqueleto<IN,OUT> *esqueleto;
    int iteracoes;
    
  public:
    FOR(){}

    FOR(const Esqueleto<IN,OUT>& e){
      this->iteracoes=e.iteracoes; 
      this->esqueleto = e.esqueleto;
    }

    FOR(int iteracoes,OUT (*func)(IN), IN data_in): Esqueleto<IN,OUT>(func)
    {
      this->esqueleto = new Esqueleto<IN,OUT>(func,data_in);
      this->iteracoes=iteracoes;      
    }

    FOR(int iteracoes, Esqueleto<IN,OUT> *esq): Esqueleto<IN,OUT>()
    {
	this->iteracoes=iteracoes;
	this->esqueleto=esq;
    }
    
    virtual ~FOR(){
     delete this->esqueleto;
    };
   
    void run(){
       for(int i=0; i< this->iteracoes; i++){
            this->esqueleto->run();
            this->esqueleto->set_Data_in(this->esqueleto->get_Data_Out()); 
       }     
    }
};

#endif
