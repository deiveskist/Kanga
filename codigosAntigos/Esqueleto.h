#ifndef Esqueletos_H
#define Esqueletos_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>   
extern "C"
{
 #include <pthread.h>
}

#include <vector>
#include <list>

//#include "/home/deives/Anahy-3/SRC/AnahyVM.h"
//#include "/home/deives/Anahy-3/SRC/AnahyJob.h"

using namespace std;

/*
Classe Esqueleto: Todos os esqueletos Herdam o seus metodos get,set e run

*/
template<class IN, class OUT>
class Esqueleto {
  private:
    IN *data_in1;
    IN *data_in2;
    OUT *data_out;
    int t_func;
    OUT* (*func_user_um)(IN*);
    OUT* (*func_user_dois)(IN*,IN*);
    static OUT foo( IN ) { return NULL; }
     
  public:
    Esqueleto(){
     // func_user= foo;
    }
   
    Esqueleto(OUT* (*func_)(IN*)){
      func_user_um=func_;
      t_func=0;
    }
    
    Esqueleto(OUT* (*func_)(IN*,IN*)){
      func_user_dois=func_;
      t_func=1;
    }
 
    Esqueleto(OUT* (*func_)(IN*), IN* data){
      this->func_user_um=func_;
      this->data_in1=data;
      t_func=0;
    }

    Esqueleto(OUT* (*func_)(IN*,IN*), IN* data1,IN* data2){
      this->func_user_dois=func_;
      this->data_in1=data1;
      this->data_in2=data2;
      t_func=1;
    }
    
    Esqueleto(const Esqueleto<IN,OUT>& e){
       if(e.t_func==0){
	  this->func_user_um=&e.func_user_um;
	  this->data_in1=e.data_in1;
       }
       else{
	  this->func_user_dois=e.func_user_dois;
	  this->data_in1=e.data_in1;
	  this->data_in3=e.data_in2;
      }
    }

    virtual void run(){
       // printf("run esquel ");
	if(this->t_func==0)
	  this->data_out=this->func_user_um(this->data_in1);
	else
	  this->data_out=this->func_user_dois(this->data_in1,this->data_in2);
    }

    virtual void setDataIn(IN *data){
       this->data_in1=data; 
    }
    
    virtual void setDataIn(IN *data1,IN *data2){
       this->data_in1=data1; 
       this->data_in2=data2; 
    }
    
    virtual OUT * getDataOut(){
       return this->data_out;
    }
    
    virtual ~Esqueleto(){};
};

#endif