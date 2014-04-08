#ifndef Esqueletos_DC_H
#define Esqueletos_DC_H

#include "Esqueleto.h"
#include "Esqueleto_SM.h"

template<class IN, class OUT>
class DC : public EsqueletoSM<IN,OUT> , public Esqueleto<IN,OUT> {
  protected:
    int valor;
    IN* data_in;
    OUT* data_out;
    OUT * aux;
    int resultado;
    int numero_dados;
    //Problema intervalo;
  private:
    static const int lado_dir=0;
    static const int lado_esq=1;
    
    struct Dados{
	IN *pro;
	DC<IN,OUT> *dc; 
    };    

    static void *thread_func( void *obj){
      Dados  d = *(Dados*)obj;
      OUT * out =reinterpret_cast<DC *>(d.dc)->exe(d.pro);
      return out;
    }   

  public:
   
    DC(){
      this->data_in=NULL;
      this->data_out=NULL;
      this->aux=NULL;
      this->resultado=0;
      this->numero_dados=0;
    }
    
    DC(const DC &e){
      this->data_in=e.data_in;
      this->data_out=e.data_out;
      this->resultado=0;
      this->numero_dados=0;
    }
    
    DC(IN *prob_in, OUT *prob_out) : Esqueleto<IN,OUT>(){
      this->data_in=prob_in;  
      this->data_out=new OUT();
    }

    void run(){
      this->data_out=this->exe(this->data_in);     
    }
    
    IN* exe(IN * sub_val){
      void *ptr_esq;
      void *ptr_dir;
      pthread_t m_thread1,m_thread2;    
      Dados th_dir,th_esq;
      OUT *vdir,*vesq;
       
      if(this->base_Condition(sub_val)==true){
	return sub_val;
       }
       else{
         IN *spl_dir=this->split(sub_val,lado_dir);
	       IN *spl_esq=this->split(sub_val,lado_esq);
	
         th_dir.pro=spl_dir;
	       th_dir.dc =this;
	 
	       th_esq.pro=spl_esq;
	       th_esq.dc=this;
	  
         pthread_create(&m_thread1,NULL,thread_func,&th_dir);
         pthread_create(&m_thread2,NULL,thread_func,&th_esq);
	  
         pthread_join(m_thread1,&ptr_dir);
	       pthread_join(m_thread2,&ptr_esq);
	 
         vdir = ((OUT *)ptr_dir);
         vesq = ((OUT *)ptr_esq);
         this->aux=this->merge(vdir,vesq);
	       return this->aux;
      }
  }
  
  virtual ~DC(){}

  virtual IN* split(IN *inter,int lado)const{};
  virtual OUT* merge(IN * p_dir, IN* p_esq)const{};
  virtual bool base_Condition(IN * spl )const{};
 
  OUT* getDataOut(){
    return this->data_out;
  }
};

#endif
