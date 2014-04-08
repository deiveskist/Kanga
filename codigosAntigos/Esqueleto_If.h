#ifndef Esqueleto_IF_H
#define Esqueleto_IF_H

#include "Esqueleto.h"

template< class INtrue, class OUTtrue, class INfalse, class OUTfalse>
class IF 
{
  private:
    Esqueleto<INtrue,OUTtrue> *esqueleto_true;
    Esqueleto<INfalse,OUTfalse> *esqueleto_false;
    bool cond;
  public:
    IF(){
      this->esqueleto_false=NULL;
      this->esqueleto_true=NULL;
    }
    
    IF(const IF<INtrue,OUTtrue,INfalse,OUTfalse>& e){
      this->cond=e.cond; 
      this->esqueleto_true = e.esqueleto_true;
      this->esqueleto_false= e.esqueleto_false;
    }
    
    IF(OUTtrue (*func_true)(INtrue), OUTfalse (*func_false)(INfalse))
    {
      this->esqueleto_true = new Esqueleto<INtrue,OUTtrue>(func_true);
      this->esqueleto_false= new Esqueleto<INfalse,OUTfalse>(func_false);
    }

    IF(OUTtrue (*func_true)(INtrue), Esqueleto<INfalse,OUTfalse> *falsecase)
    {
	
	this->esqueleto_true = new Esqueleto<INtrue,OUTtrue>(func_true);
	this->esqueleto_false= falsecase;
    } 

    IF(Esqueleto<INtrue,OUTtrue> *truecase, OUTfalse (*func_false)(INfalse))
    {
      
      this->esqueleto_true = truecase;
      this->esqueleto_false= new Esqueleto<INfalse,OUTfalse>(func_false);
    } 

    IF(Esqueleto<INtrue,OUTtrue> *truecase,  Esqueleto<INfalse,OUTfalse> *falsecase)
    {
      this->esqueleto_true = truecase;
      this->esqueleto_false= falsecase;
    }
    
    virtual ~IF(){
     delete this->esqueleto_true;
     delete this->esqueleto_false;
    };
   
    void run(bool cond){
     
      if(cond == true){  
          this->esqueleto_true->run();
      }
      else{
          this->esqueleto_false->run();
      }
    }
};

#endif
