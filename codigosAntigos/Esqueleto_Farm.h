#ifndef Esqueletos_Farm_H
#define Esqueletos_Farm_H

#include "Esqueleto.h"
#include "Esqueleto_SM.h"

/*
 É preciso implementar a composição
 e a melhorar a forma de retornar a OUT
 */


using namespace std;
   
template<class IN, class OUT>
class Farm : public EsqueletoSM<IN,OUT> , public Esqueleto<IN,OUT> {
  private:
    struct Dados{ // struct utilizada para passar o esqueleto e os dados paras threads
      Esqueleto<IN,OUT> *esqueleto;
      IN* _in;
      OUT* _out;
    };
    
    int num_threads; // numero de threads que serão utilizadas
    int tam_list; // tamanho da lista de entrada/saida
    //AnahyJob *jobs;
    IN  *data_in; 
    OUT *data_out;
    pthread_t *threads;
    bool efunc;
    bool eesq;  
    // AnahyJob *jobs;
   
    Esqueleto<IN,OUT> *esqueleto;
    
    Dados saida;
    OUT ou;
    void *vptr_return;
    OUT* (*func_user)(IN*);
     
    Dados *func_dados;
  public:

    Farm() : Esqueleto<IN,OUT>(){
      this->esqueleto=new Esqueleto<IN,OUT>();
      this->num_threads=0;
      this->tam_list=0;
      this->data_in=NULL;
      this->data_out=NULL;
      this->threads = NULL;
      this->func_dados = NULL;
      this->vptr_return=0;
      this->efunc=false;
      this->eesq=false;
    }
    
    Farm( const Farm<IN,OUT> &e) : Esqueleto<IN,OUT>(){
      this->esqueleto=e.esqueleto;
      this->num_threads=e.num_threads;
      this->tam_list=e.tam_list;
      this->data_in=e.data_in;
      this->data_out=e.data_out;
      this->threads =e.threads;
      this->vptr_return=0;
	    //func_dados = e.func_dados;
    }  

    Farm( OUT* (&func)(IN*), IN *data_in, OUT *data_out, int num_th) : Esqueleto<IN,OUT>() {
      this->func_user=func;
      
      this->num_threads=num_th;
      this->data_in = data_in;
      this->data_out= data_out;
      this->threads = new pthread_t[this->num_threads];
      this->func_dados = new Dados[this->num_threads];
      this->vptr_return=0;
      this->efunc=true;
      this->eesq=false;
	    //	this->jobs = new AnahyJob[this->num_threads];
   }

    Farm(Esqueleto<IN,OUT>* esq,IN *data_in, OUT *data_out, int num_th): EsqueletoSM<IN,OUT>() {
      this->esqueleto =esq;
      this->num_threads=num_th;
      this->data_in = data_in;
      this->data_out= data_out;
      this->threads = new pthread_t[this->num_threads];
      this->func_dados = new Dados[this->num_threads];
      this->vptr_return=0;
      this->efunc=false;
      this->eesq=true;
    }

    Farm(OUT* (&func)(IN*), int num_th): Esqueleto<IN,OUT>() {
      this->func_user=func;
    //this->esqueleto = new Esqueleto<IN,OUT>(func_);
      this->num_threads =num_th;
     
      this->threads = new pthread_t[this->num_threads];
      this->func_dados = new Dados[this->num_threads];
      this->vptr_return=0;
      this->efunc=true;
      this->eesq=false;
    }
    
    Farm(Esqueleto<IN,OUT> *esq, int num_th): EsqueletoSM<IN,OUT>(esq) {
      this->esqueleto =esq;
      this->num_threads=num_th;
      //this->data_in=NULL;
      //this->data_out=NULL;
      this->threads = new pthread_t[this->num_threads];
      this->func_dados = new Dados[this->num_threads];
      this->vptr_return=0;
      this->efunc=false;
      this->eesq=true;
    }
       
    virtual ~Farm(){
      delete this->data_in;
      delete this->data_out;
      delete this->func_dados;
      delete this->threads;
      delete this->esqueleto;
    }
  
    void run(){
      this->fork_jobs();// Criar os Workers e envia os dados aos workers
      this->join_jobs();// termina e recebe os dados dos workers
    }
    
     
    OUT * getDataOut(){
         return this->data_out;
    }

  private:
    void fork_jobs(){
      for(int i = 0; i < this->num_threads; i++) {   
	      this->func_dados[i]._in=this->split(this->data_in,i);
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
        //         this->merge(data_out,i,ou);
      }
    }
    // Este metodo representa os workers
    static void* thread_func(void *args){
      Dados *dado = static_cast<Dados* >(args);
      OUT *value = new OUT();
      dado->esqueleto->setDataIn(dado->_in);
      dado->esqueleto->run();
      value = dado->esqueleto->getDataOut();
      return  value;
    }
    
   /* 
    IN  split(IN *data_in,int n_thread) const{
          return &data_in[n_thread];
    }

    void merge(OUT *data_out, int n_thread,  OUT split_out)const {
         data_out[n_thread]=split_out;
    }
    */   
};

#endif
