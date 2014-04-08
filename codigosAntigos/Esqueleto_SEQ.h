#ifndef Esqueleto_SEQ_H
#define Esqueleto_SEQ_H

#include "Esqueleto.h"

template< class IN, class OUT>
class SEQ : public Esqueleto<IN,OUT>{
    Esqueleto<IN,OUT> *esqueleto;
    list< Esqueleto<IN,OUT> * > list_seq;
    int num_esqueletos;
  public:
    SEQ(){
      this->esqueleto=NULL;
      this->list_seq=NULL;
      this->num_esqueletos=0;
    }

    SEQ(const Esqueleto<IN,OUT>& e){
      this->esqueleto=e.esqueleto;
      this->list_seq=e.list_seq;
      this->num_esqueletos=e.num_esqueletos;
    }

    SEQ(int num_esqueletos): Esqueleto<IN,OUT>()
    {
      this->num_esqueletos=num_esqueletos;
      list_seq.resize(this->num_esqueletos);
    }

    void add(Esqueleto<IN,OUT> *esqueleto){
      this->list_seq.push_back(esqueleto);
    }

    void add(OUT (*func)(IN)){
      esqueleto = new Esqueleto<IN,OUT>(func);
      this->list_seq.push_back(esqueleto);
    }

    void add(OUT (*func)(IN), IN data_in){
      esqueleto = new Esqueleto<IN,OUT>(func,data_in);
      this->list_seq.push_back(esqueleto);
    }
  
    virtual ~SEQ(){
	delete esqueleto;     
    };
   
    void run(){
    	while (!list_seq.empty())
  	{
    	   this->esqueleto=list_seq.front();
           this->esqueleto->run();
	   list_seq.pop_front();
  	}
    }
};


/*
 Cada esqueleto deve retornar a sua saida para o proximo esqueleto??
 
 */
#endif
