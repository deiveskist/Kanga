#ifndef Esqueletos_Reduce_H
#define Esqueletos_Reduce_H

#include "Esqueleto.h"
#include "Esqueleto_SM.h"


template<class IN, class OUT>
class Reduce : public EsqueletoSM<IN,OUT> , public Esqueleto<IN,OUT> {
  private:    
    struct Dados{
      Esqueleto<IN,OUT> *esqueleto;
	IN* _in1;
	IN*  _in2;
	OUT* _out;
 	int id;
    };  
    
    int num_threads; // numero de threads que serão utilizadas
    int tam_list; // tamanho da lista de entrada/saida
    //AnahyJob *jobs;
    OUT ou;
    void *vptr_return;
    IN  *list_in;
    OUT *data_out;	 
    OUT valor_final_reduce;
    //AnahyJob *jobs;
    pthread_t *threads;
    bool efunc;
    bool eesq;  
    OUT* (*func_user)(IN*,IN*);
    Esqueleto<IN,OUT> *esqueleto;
    Dados *func_dados;
    IN dado_rest;
    int tam;
    bool impar;
   
    static void *thread_func( void *args){
      Dados *dado = static_cast<Dados* >(args);
      OUT *value = new OUT();
      dado->esqueleto->setDataIn(dado->_in1,dado->_in2);
      dado->esqueleto->run();
      value = dado->esqueleto->getDataOut();
      return  value;
    }
    
  public:
    
    Reduce() : Esqueleto<IN,OUT>(){
      this->esqueleto=new Esqueleto<IN,OUT>();
      this->num_threads=0;
      this->tam_list=0;
      this->list_in=NULL;
      this->data_out=NULL;
      this->threads = NULL;
      this->func_dados = NULL;
      this->vptr_return=0;
      this->efunc=false;
      this->eesq=false;
    }   
    
    Reduce(const Reduce<IN,OUT> &e) : Esqueleto<IN,OUT>() {
      this->esqueleto=e.esqueleto;
      this->num_threads=e.num_threads;
      this->tam_list=e.tam_list;
      this->list_in=e.list_in;
      this->data_out=e.data_out;
      this->threads =e.threads;
      this->vptr_return=0;
    }
    
    Reduce(OUT* (&func)(IN*,IN*),IN *list,OUT *data_out, int tam_list, int num_th) : Esqueleto<IN,OUT>(){
      this->func_user=func;
      this->num_threads=num_th;
      this->tam_list=tam_list;
      this->list_in = new IN[this->tam_list];
      this->data_out= new OUT();
      for(int i=0; i< tam_list;i++) this->list_in[i]=list[i];
      
      this->data_out=data_out;
      this->efunc=true;
      this->eesq=false;
      this->vptr_return=0;
      this->efunc=true;
      this->eesq=false;
      this->tam=this->tam_list;
      this->impar=false;
    }

    ~Reduce(){
      delete this->list_in;
      delete this->data_out;
      delete this->func_dados;
      delete this->threads;
      delete this->esqueleto;
    }
    
   void fork_jobs(){
     
    for(int i = 0; i < this->num_threads; i++){
      this->func_dados[i].esqueleto=new Esqueleto<IN,OUT>(this->func_user);
      this->func_dados[i]._in1=new OUT(this->list_in[2*i]);     
      this->func_dados[i]._in2=new OUT(this->list_in[(2*i)+1]);
      pthread_create(&(this->threads[i]),NULL,thread_func,  &this->func_dados[i]); 
      //printf("a %d  %d  f  ",func_dados[j].para1,func_dados[j].para2);
      //jobs[j].init(thread_func,&func_dados[j],NULL);
      //AnahyVM::fork(&jobs[j]);
      }
   }

   void join_jobs(){
      for(int i = 0; i < this->num_threads; i++){
        //  AnahyVM::join(&this->jobs[i],&vptr_return);
        pthread_join(this->threads[i],&(vptr_return));
        this->ou = *static_cast<OUT*> (vptr_return);
        
	this->list_in[i]=this->ou;
//      this->merge(this->list_in,i,ou);
       }
    }

    void run(){
      
      while(this->tam > 1){
	if(this->tam%2==0){ 
	  this->num_threads=this->tam/2;
	  this->tam=this->tam/2;
	}
	else{
	  this->num_threads=this->tam/2;
	  this->dado_rest= this->list_in[this->tam-1];
	  this->tam=this->tam/2; 
	  this->tam++;
	  this->impar=true;
	}
	
// 	jobs = new  AnahyJob[num_threads];
	this->threads = new pthread_t[this->num_threads];
	this->func_dados = new Dados[this->tam];

	this->fork_jobs();
	this->join_jobs();   	
	
	if(this->impar==true){
		this->list_in[tam-1]=dado_rest;
		this->impar=false;
	}
		
// 		for(int j = 0; j < this->tam; j++){
// 		  printf(" %d",list_in[j]);
// 		}
// 		printf("\n");
    	}
   
	this->data_out=new OUT(this->list_in[0]);
	
    }	
    
    OUT * getDataOut(void){
      return this->data_out;
    }
 
    IN * split(IN *list_in,int n_thread) const{
    }

    OUT * merge(OUT *data_out, int n_thread,  OUT split_out)const {

   }

};

#endif
