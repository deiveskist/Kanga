#ifndef Esqueletos_MapReduce_H
#define Esqueletos_MapReduce_H

#include "Esqueleto.h"
#include "Esqueleto_SM.h"

//Talvez deva herdar coisas do Esqueleto Reduce????//

template< class IN, class OUT>
class MapReduce: public EsqueletoSM<IN,OUT> , public Esqueleto<IN,OUT> {
  private:
     struct Dados{ // struct utilizada para passar o esqueleto e os dados paras threads
      Esqueleto<IN,OUT> *esqueleto;
      IN *_in1;
      IN *_in2;
      OUT *_out;
      bool efunc;
    };
    
    int num_threads; // numero de threads que serão utilizadas
    int tam_list; // tamanho da lista de entrada/saida
    //AnahyJob *jobs;
    IN  *list_in; 
    OUT  *data_out;
    pthread_t *threads;
    bool efunc;
    bool eesq;  
      
    Esqueleto<IN,OUT> *esqueleto;
    
    Dados saida;
    OUT ou;
    IN* spl;
    bool part_map;
    void *vptr_return;
    OUT* (*func_map)(IN*);
    OUT* (*func_reduce)(IN*,IN*);    
    Dados *func_dados;
  
    IN dado_rest;
    int tam;
    bool impar;
   
  public:
     MapReduce(){
      this->func_map=NULL;
      this->func_reduce=NULL;
      this->num_threads=0;
      this->tam_list=0;
      this->tam=this->tam_list;	
      this->list_in = NULL;
      this->data_out= NULL;
      this->threads =NULL;
      this->func_dados = NULL;
      this->vptr_return=0;
      this->efunc=false;
      this->eesq=false;
      this->valor_final_MapReduce=0;
      this->part_map=true;
    }

    MapReduce(const MapReduce &e){
      this->func_map=e.func_map;
      this->func_reduce=e.func_reduce;
      this->num_threads=e.num_th;
      this->tam_list=e.tam_list;
      this->tam=this->tam_list;
      this->list_in = new IN[this->tam_list];
      this->data_out= new OUT();	
      for(int i=0; i< tam_list;i++) this->list_in[i]=e.list[i];
      this->data_out=e.data_out;
      this->threads = e.threads;
      this->func_dados = e.func_dados;
      this->vptr_return=0;
      this->efunc=e.efunc;
      this->eesq=e.eesq;
      this->part_map=e.part_map;
    }		

    MapReduce(OUT* (&func_map)(IN*), OUT* (&func_reduce)(IN*,IN*), IN *list_in, OUT* data_out, int tam_list, int num_th) : Esqueleto<IN,OUT>(){
      this->func_map=func_map;
      this->func_reduce=func_reduce;
      this->num_threads=num_th;
      this->tam_list=tam_list;
      this->tam=this->tam_list;
      this->list_in = new IN[this->tam_list];
      for(int i=0; i< tam_list;i++) this->list_in[i]=list_in[i];
      this->data_out=data_out;
      this->threads = new pthread_t[this->num_threads];
      this->func_dados = new Dados[this->num_threads];
      this->vptr_return=0;
      this->efunc=true;
      this->eesq=false;
    
      this->part_map=true;
    }

    ~MapReduce(){
      delete this->list_in;
      //delete this->data_out;	
      delete this->func_dados;
      delete this->threads;
      delete this->esqueleto;
    }
    
    OUT* getDataOut(void){ 
 	return this->data_out;
    }
    
    void run(){
	this->fork_Jobs();
	this->join_Jobs();
	this->part_map=false;
	this->run_Reduce(); 
    }
    
  private:
    static void* thread_Func(void *args){
      Dados *dado = static_cast<Dados* >(args);
      OUT *value = new OUT();
      if(dado->efunc==true)
	     dado->esqueleto->setDataIn(dado->_in1);
      else 
	     dado->esqueleto->setDataIn(dado->_in1,dado->_in2);

      dado->esqueleto->run();
      value = dado->esqueleto->getDataOut();
      return  value;
     }
    
 
   void fork_Jobs(){
      for(int i = 0; i < this->num_threads; i++) {   
	  if(this->part_map==true){
	    if(this->efunc==true)
		    this->func_dados[i].esqueleto=new Esqueleto<IN,OUT>(this->func_map);
	    else if(this->eesq=true)
		    this->func_dados[i].esqueleto=this->esqueleto;
	    
	    this->func_dados[i]._in1=this->split(this->list_in,i);
	  }
	  else{
	    if(this->efunc==true)
		  this->func_dados[i].esqueleto=new Esqueleto<IN,OUT>(this->func_reduce);
	    else if(this->eesq=true)
		  this->func_dados[i].esqueleto=this->esqueleto;
//	    this->func_dados[i]._in1= this->list_in[2*i];     
//	    this->func_dados[i]._in2=this->list_in[(2*i)+1];
	    this->func_dados[i]._in1= this->split(this->list_in,2*i);     
	    this->func_dados[i]._in2= this->split(this->list_in,(2*i)+1); 

	  }
  
  // 	this->jobs[i].init(thread_func,&func_dados[i],NULL);
  //      AnahyVM::fork(&jobs[i]); 
	  pthread_create(&(this->threads[i]),NULL,thread_Func,&this->func_dados[i]); 
	}
    }
    
    void join_Jobs(){
      for(int i = 0; i < this->num_threads; i++){
//	AnahyVM::join(&this->jobs[i],&vptr_return);
        pthread_join(this->threads[i],&vptr_return);
        this->ou = *static_cast<OUT*> (vptr_return);
//       printf("%d %d - ",i,this->ou);
        this->list_in=this->merge(list_in,i,this->ou);
      }
    }
   
    void run_Reduce(){
      while(this->tam > 1){
      	if(this->tam%2==0){ 
      	  this->num_threads=this->tam/2;
      	  this->tam=this->tam/2;
      	}
      	else{
   	  this->num_threads=this->tam/2;
//     	  this->dado_rest= this->list_in[this->tam-1];
          this->dado_rest=*static_cast<IN*> (this->split(this->list_in,this->tam-1));
      	  this->tam=this->tam/2;
	  this->tam++;
      	  this->impar=true;
      	}
		//jobs = new  AnahyJob[num_threads];
	this->threads = new pthread_t[this->num_threads];
	this->func_dados = new Dados[this->tam];
	this->fork_Jobs();
	this->join_Jobs();   	

	if(this->impar==true){
		this->list_in[tam-1]=dado_rest;
		this->impar=false;
	}
	/*	
	for(int j = 0; j < this->tam; j++){
	  printf(" %d",list_in[j]);
	}
	printf("\n");*/
      }
      this->data_out=new OUT(this->list_in[0]);
    }
};

#endif
