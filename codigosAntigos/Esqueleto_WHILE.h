#ifndef Esqueleto_WHILE_H
#define Esqueleto_WHILE_H

#include "Esqueleto.h"

template< class IN, class OUT>
class WHILE : public Esqueleto<IN,OUT>{
    Esqueleto<IN,OUT> *esqueleto;
    bool cond;
    
  public:
    WHILE(){}

    WHILE(const Esqueleto<IN,OUT>& e){
      this->cond=e.cond; 
      this->esqueleto = e.esqueleto;
    }

    WHILE(bool cond,OUT (*func)(IN), IN data_in): Esqueleto<IN,OUT>(func)
    {
      this->esqueleto = new Esqueleto<IN,OUT>(func,data_in);
      this->cond=cond;      
    }

    WHILE(bool cond, Esqueleto<IN,OUT> *esq): Esqueleto<IN,OUT>()
    {
	this->cond=cond;
	this->esqueleto=esq;
    }
    
    virtual ~WHILE(){
     delete this->esqueleto;
    };
   
    void run(){
       while(this->cond){
            this->esqueleto->run();
            this->esqueleto->set_Data_in(this->esqueleto->get_Data_Out()); 
         }     
    }
};

#endif