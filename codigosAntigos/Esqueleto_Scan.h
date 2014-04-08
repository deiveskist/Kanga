#ifndef Esqueleto_Scan_H
#define Esqueleto_Scan_H

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>

#include "Esqueleto.h"
#include "Esqueleto_SM.h"

template< class IN, class OUT>
class Scan : public EsqueletoSM<IN,OUT> , public Esqueleto<IN,OUT> {
  private:
     struct Dados{
      Esqueleto<IN,OUT> *esqueleto;
	IN* _in1;
	IN* _in2;
	OUT* _out;
 	int id;
    };  
    
    int num_threads;
    int tam_list;
    
    OUT ou;
    void *vptr_return;
    IN  *list_in;
    OUT *list_out;
//     AnahyJob *jobs;
    pthread_t *threads;
    bool efunc;
    bool eesq; 
    Esqueleto<IN,OUT> *esqueleto;
    OUT* (*func_user)(IN*,IN*);
    bool pri;
   
    Dados *func_dados;
    int num_passos;
    
    int dist;
    int iter;       
    static void *thread_func( void *args){
      Dados *dado = static_cast<Dados* >(args);
      OUT *value = new OUT();
      dado->esqueleto->setDataIn(dado->_in1,dado->_in2);
      dado->esqueleto->run();
      value = dado->esqueleto->getDataOut();
      return  value;
    }
    
  public:
    Scan() : Esqueleto<IN,OUT>(){
      this->esqueleto=new Esqueleto<IN,OUT>();
      this->num_threads=0;
      this->tam_list=0;
      this->list_in=NULL;
      this->list_out=NULL;
      this->threads = NULL;
      this->func_dados = NULL;
      this->vptr_return=0;
      this->efunc=false;
      this->eesq=false;
    }
    
    Scan( const Scan<IN,OUT> &e) : Esqueleto<IN,OUT>(){
      this->esqueleto=e.esqueleto;
      this->num_threads=e.num_threads;
      this->tam_list=e.tam_list;
      this->list_in=e.list_in;
      this->list_out=e.list_out;
      this->threads =e.threads;
      this->vptr_return=0;
    }
    
    Scan(OUT* (&func)(IN*,IN*), IN *list_in, OUT *list_out,int tam_list, int num_th) : Esqueleto<IN,OUT>(){
	this->func_user=func;
	this->num_threads=num_th;
        this->tam_list=tam_list;
        this->list_in = new IN[this->tam_list];
        this->list_out= new OUT[this->tam_list];
	this->list_out=list_out;
        for(int i=0; i< this->tam_list;i++) this->list_in[i]=list_in[i];
	
//      this->threads = new pthread_t[this->num_threads];
        this->list_out[0]=this->list_in[0]; 
	this->vptr_return=0;
        this->efunc=true;
        this->eesq=false;
        this->num_passos=ceil(log2(this->tam_list));
        this->dist=1;
        this->pri=true;
	this->iter=0;
	this->func_dados=NULL;
   }
    Scan(Esqueleto<IN,OUT> *esq,IN *list_in, OUT *list_out,int tam_list, int num_th): EsqueletoSM<IN,OUT>(esq) 
    {
	this->esqueleto =esq;
        this->num_threads=num_th;
        this->tam_list=tam_list;
        this->list_in=list_in;
        this->list_out=list_out;
        threads = new pthread_t[this->num_threads];
    }
   
    virtual ~Scan(){};
   
    void run(){
      
      while(this->iter < this->num_passos){
	this->num_threads=this->tam_list-this->dist;
// 	jobs = new  AnahyJob[num_threads];
	this->threads = new pthread_t[this->num_threads];
	this->func_dados= new Dados[this->num_threads];
	this->fork_jobs();
        this->join_jobs();
	this->dist=dist+dist;
	this->iter++; 
	this->list_out[this->iter]=this->list_in[this->iter];
	
// 	for(int j = 0; j < this->tam_list; j++){
// 	  printf("%d ",this->list_out[j].getX());
//   	}
//   	printf("\n");
      }
      this->iter++;
      this->list_out[this->iter]=this->list_in[this->iter];
      

    /*
      for(int j = 0; j < this->tam_list; j++){
	  this->list_out[j]=this->list_in[j];
      }
     */ 
    }
    
  private:
    void fork_jobs(){
     
    for(int i = 0; i < this->num_threads; i++){
        this->func_dados[i].id=i;
        this->func_dados[i].esqueleto=new Esqueleto<IN,OUT>(this->func_user);
        /*
	this->func_dados[i]._in1=new OUT(this->list_in[i]);     
        this->func_dados[i]._in2=new OUT(this->list_in[i+this->dist]);
	*/
	
	this->func_dados[i]._in1=this->split(this->list_in,i);
        this->func_dados[i]._in2=this->split(this->list_in,i+this->dist);
	
	pthread_create(&(this->threads[i]),NULL,thread_func,&this->func_dados[i]); 
        
        //jobs[j].init(thread_func,&func_dados[j],NULL);
        //AnahyVM::fork(&jobs[j]);
      }
   }

   void join_jobs(){
      for(int i = 0; i < this->num_threads; i++){
//      AnahyVM::join(&this->jobs[i],&vptr_return);
        pthread_join(this->threads[i],&(vptr_return));
        this->ou = *static_cast<OUT*> (vptr_return);

//  	this->list_in[i+this->dist]=ou;
        this->list_in=this->merge(this->list_in,i+dist,ou);
       }
    }
};

#endif