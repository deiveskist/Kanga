/*
 * DC.h
   Implementa o Esqueleto Divisao e Conquista
*/

#ifndef DC_H_
#define DC_H_
#include "Kanga.h"
#include "Thread.h"

namespace kanga{

//Classe auxiliar utilizada para descrever o problema de entrada
// o usuario deve implementar todos os metodos  
//  o problema sempre é dividido em somente dois problemas
class ProblemaDC{
  public:
  virtual int base()=0;// verifica se o problema é trivial
  virtual ProblemaDC* divisaoDir()=0; // divide o problema
  virtual ProblemaDC* divisaoEsq()=0; // divide o problema
  virtual void conquista()=0; // soluciona os sub-problemas
  virtual void combina(ProblemaDC* esq, ProblemaDC* dir)=0; //combina as sub-solucoes
};

template< class T>
class DC : public Kanga<T,T> {
 public:
   DC() : proOut(t){
    this->proIn=NULL;
    this->proOut=NULL;
   }
   
   DC(const DC<T> &e) : proOut(e.proOut){
     this->proIn=e.proIn;
     this->proOut=e.proOut;   
   }

   DC(T *proIn) : proOut(t){
     this->proIn=proIn;
   }
  
   DC(T * proIn, T * &proOut) : proOut(proOut){
     this->proIn=proIn;
   }
   
   ~DC(){
     delete this->thdrun;
     delete this->proIn;
     delete this->proOut;
   }
   
   void start(){
     this->pAux = new Para;
     this->pAux->pro=this->proIn;
     this->pAux->dc=this;
     thdrun = new Thread<Para, T>(&DC::tRunPara,p);
     thdrun->start();
      
   }
   
   void join(){
     thdrun->join();
     this->proOut=this->thdrun->getDataOut();
       
   }
   
    Kanga<T,T> * clone(){
      return new DC<T>();
    }

    Kanga<T,T> * clone(T * proIn, T*& proOut){
      return new DC<T>(proIn,proOut);
    }

   void setDataIn(T * pro){
    this->proIn=pro;
    this->proIn->print();
   }

   T * getDataOut(){
     return this->proOut;
   }

  private:
   
   struct Para{// estrutura auxiliar 
      T* pro;
      DC<T> *dc; 
    };

    Para *pAux; 
    Thread<Para , T> *thdrun; 
    T * proIn;   // ponteiro para o problema de entrada
    T *& proOut; // referencia para  a solucao do problema

    static T * tRunPara(Para *p){ 
      return p->dc->runDCPara(p->pro);
    }

    T* runDCPara(T * pro); // executa a divisao e conquista   
};

template<class T>
T* DC<T>::runDCPara(T * pro){
  if(pro->base()==1){// verifica se o problema é trivial
     pro->conquista(); // sendo trivial, realiza a conquista
     return pro;
  }
  else{ // realiza da divisao 
    T * proDir;
    T * proEsq;
    Para *p = new Para;
    // divide em dois sub-problemas
    p->pro=pro->divisaoDir(); 
    p->dc=this;
    proEsq=pro->divisaoEsq();
    
    Thread<Para , T> * thdDir = new Thread<Para, T>(&DC::tRunPara,p);// cria um thread para um sub-problema

    thdDir->start();  
    proEsq=this->runDCPara(proEsq); // soluciona um sub-problema no thread atual, sequencial
    thdDir->join();
    proDir=thdDir->getDataOut();

    pro->combina(proDir,proEsq); // combina as sub-solucoes 
    delete proDir;
    delete proEsq;
    delete p;

    return pro;// retorna a solucao
    }
 }
};

#endif /* DC_H_ */
