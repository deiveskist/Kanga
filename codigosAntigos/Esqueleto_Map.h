#ifndef Esqueletos_Map_H
#define Esqueletos_Map_H

#include "Esqueleto.h"
#include "Esqueleto_SM.h"

/*
 É preciso implementar a composição
 e a melhorar a forma de retornar a OUT
 */

using namespace std;
   
template<class IN, class OUT>
class Map : public EsqueletoSM<IN,OUT> , public Esqueleto<IN,OUT> {
  private:
    struct Dados{ // struct utilizada para passar o esqueleto e os dados paras threads
      Esqueleto<IN,OUT> *esqueleto;
      IN * _in;
      OUT * _out;
      int id;
    };
    
    int num_threads; // numero de threads que serão utilizadas
    int tam_list; // tamanho da lista de entrada/saida
    //AnahyJob *jobs;
    IN  *list_in; 
    OUT  *list_out;
    pthread_t *threads;
    bool efunc;
    bool eesq;  
    // AnahyJob *jobs;
   
    Esqueleto<IN,OUT> *esqueleto;
    OUT ou;
    void *vptr_return;
    OUT* (*func_user)(IN*);
    Dados *func_dados;
  public:

    Map() : Esqueleto<IN,OUT>(){
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
    
    Map( const Map<IN,OUT> &e) : Esqueleto<IN,OUT>(){
      this->esqueleto=e.esqueleto;
      this->num_threads=e.num_threads;
      this->tam_list=e.tam_list;
      this->list_in=e.list_in;
      this->list_out=e.list_out;
      this->threads =e.threads;
      this->vptr_return=0;
    }  

    Map( OUT* (&func)(IN*), IN *list_in, OUT *list_out,int tam_list, int num_th) : Esqueleto<IN,OUT>() {
      this->func_user=func;
      // this->esqueleto=new Esqueleto<IN,OUT>(func_);
      this->num_threads=num_th;
      this->tam_list=tam_list;
      this->list_in = new IN[this->tam_list];
      this->list_out= new OUT[this->tam_list];
      for(int i=0; i< tam_list;i++) this->list_in[i]=list_in[i];
      this->list_out=list_out;
      this->threads = new pthread_t[this->num_threads];
      this->func_dados = new Dados[this->num_threads];
      this->vptr_return=0;
      this->efunc=true;
      this->eesq=false;
	    //	this->jobs = new AnahyJob[this->num_threads];
   }

    Map(Esqueleto<IN,OUT>* esq,IN *list_in, OUT *list_out,int tam_list, int num_th): Esqueleto<IN,OUT>() {
	    this->esqueleto =esq;
      this->num_threads=num_th;
      this->tam_list=tam_list;
      this->list_in = new IN[this->tam_list];
      this->list_out= new OUT[this->tam_list];
      for(int i=0; i< tam_list;i++) this->list_in[i]=list_in[i];
      //this->esqueleto->set_Data_out(list_out);
      this->threads = new pthread_t[this->num_threads];
      this->func_dados = new Dados[this->num_threads];
      this->vptr_return=0;
      this->efunc=false;
      this->eesq=true;
    }

    Map(OUT* (&func)(IN*),int tam_list, int num_th): Esqueleto<IN,OUT>() {
      this->func_user=func;
	    //this->esqueleto = new Esqueleto<IN,OUT>(func_);
      this->num_threads =num_th;
      this->tam_list =tam_list;
      this->threads = new pthread_t[this->num_threads];
	    this->func_dados = new Dados[this->num_threads];
      this->vptr_return=0;
      this->efunc=true;
      this->eesq=false;
    }
    Map(Esqueleto<IN,OUT> *esq,int tam_list, int num_th): EsqueletoSM<IN,OUT>(esq) {
      this->esqueleto =esq;
      this->num_threads=num_th;
      this->tam_list=tam_list;
      //this->list_in=NULL;
      //this->list_out=NULL;
      this->threads = new pthread_t[this->num_threads];
      this->func_dados = new Dados[this->num_threads];
      this->vptr_return=0;
      this->efunc=false;
      this->eesq=true;
    }
       
    virtual ~Map(){
      delete this->list_in;
      delete this->list_out;
      delete this->func_dados;
      delete this->threads;
      delete this->esqueleto;
    }
  
    void run(){
      this->fork_jobs();
      this->join_jobs();
    }
    
    OUT* getDataOut(){
      return list_out;
    }
     
  private:
    
    void fork_jobs(){
      for(int i = 0; i < this->num_threads; i++) {   
 	IN * spl=this->split(this->list_in,i);
	this->func_dados[i]._in=spl;
	
        if(this->efunc==true)
	  this->func_dados[i].esqueleto=new Esqueleto<IN,OUT>(this->func_user);
        else if(this->eesq=true)
	  this->func_dados[i].esqueleto=this->esqueleto;
        
// 	this->jobs[i].init(thread_func,&func_dados[i],NULL);
//        AnahyVM::fork(&jobs[i]); 
	pthread_create(&(this->threads[i]),NULL,thread_func,  &this->func_dados[i]); 
      }
    }
    
    void join_jobs(){
      for(int i = 0; i < this->num_threads; i++){
//	AnahyVM::join(&this->jobs[i],&vptr_return);
	pthread_join(this->threads[i],&(vptr_return));
	this->ou = *static_cast<OUT*> (vptr_return);
        this->list_out=this->merge(list_out,i,ou);
      }
    }

    static void* thread_func(void *args){
      Dados *dado = static_cast<Dados* >(args);
      OUT *value = new OUT();
      dado->esqueleto->setDataIn(dado->_in);
      dado->esqueleto->run();
      value = dado->esqueleto->getDataOut();
      return  value;
     } 

    void set_Data_in(IN list_in) {
      this->list_in=&list_in;
    }
    
    void set_Data_out(OUT *list_out) {
      this->list_out=list_out;
    }
    
   /* 
    IN  split(IN *list_in,int n_thread) const{
          return &list_in[n_thread];
    }

    void merge(OUT *list_out, int n_thread,  OUT split_out)const {
         list_out[n_thread]=split_out;
    }
    */   
};

#endif
