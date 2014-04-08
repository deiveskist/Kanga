#include <iostream>
#include "Esqueleto_DC.h"

using namespace std;

template<class IN, class OUT>
class Mydc_merge_sort : public DC<IN,OUT>{
 public:  
 Mydc_merge_sort(IN *_in, OUT *_out): DC<IN,OUT>(_in,_out){}

 ~Mydc_merge_sort(){} 

 IN *split(IN *problema,int lado)const{
   int tam;
   IN *pro;
   
   if(problema->get_Tam()%2==0){
        pro = new IN(problema->get_Tam()/2);
        tam=problema->get_Tam()/2;
	if(lado==0){
	  for(int i=0; i< tam ; i++) pro->set_Dado(problema->get_Dado(i));  
	 }
	 else{
	  for(int i=tam; i< problema->get_Tam() ; i++) pro->set_Dado(problema->get_Dado(i));
	 }
   }
   else{
	if(lado==0){
	  pro = new IN(problema->get_Tam()/2);
	  tam=problema->get_Tam()/2+1;
	  for(int i=0; i< tam ; i++) pro->set_Dado(problema->get_Dado(i));  
	}
	else{
	  pro = new IN(problema->get_Tam()/2+1);
	  tam=problema->get_Tam()/2;
	  for(int i=tam; i< problema->get_Tam() ; i++) pro->set_Dado(problema->get_Dado(i));
	}
   }
  return pro;
 }

 OUT* merge(IN  *dir, IN *esq)const {
   int tam = dir->get_Tam()+esq->get_Tam();
   IN *p = new IN(tam); 
     
  if(dir->get_Dado(0) < esq->get_Dado(0)){
    for(int i=0; i< dir->get_Tam(); i++){
      p->set_Dado(dir->get_Dado(i));
    }
    
    for(int i=0; i< esq->get_Tam(); i++){
      p->set_Dado(esq->get_Dado(i));
    }
   }
  else{
    for(int i=0; i< esq->get_Tam(); i++){
      p->set_Dado(esq->get_Dado(i));
    }
       
    for(int i=0; i< dir->get_Tam(); i++){
      p->set_Dado(dir->get_Dado(i));
   }
  }
  return p;
 }
 
 bool base_Condition(IN* pro)const{
  if(pro->get_Tam() > 1) return false;
  else if(pro->get_Tam() == 1) return true;
 }  
};

template<class IN, class OUT>
class Mydc_quick_sort: public DC<IN,OUT>
{
 public:  
 Mydc_quick_sort(IN *_in, OUT *_out): DC<IN,OUT>(_in,_out){}
 ~Mydc_quick_sort(){} 

 IN *split(IN *problema,int lado)const{
  int tam;
  IN *pro;
   
  if(problema->get_Tam()%2==0){
    pro = new IN(problema->get_Tam()/2);
    tam=problema->get_Tam()/2;
    if(lado==0){
      for(int i=0; i< tam ; i++) pro->set_Dado(problema->get_Dado(i));  
    }
    else{
      for(int i=tam; i< problema->get_Tam() ; i++) pro->set_Dado(problema->get_Dado(i));
    }
   }
  else{
    if(lado==0){
      pro = new IN(problema->get_Tam()/2);
      tam=problema->get_Tam()/2+1;
      for(int i=0; i< tam ; i++) pro->set_Dado(problema->get_Dado(i));  
    }
    else{
      pro = new IN(problema->get_Tam()/2+1);
      tam=problema->get_Tam()/2;
      for(int i=tam; i< problema->get_Tam() ; i++) pro->set_Dado(problema->get_Dado(i));
    }
   }
   return pro;
 }

 OUT* merge(IN  *dir, IN *esq)const {
  int tam = dir->get_Tam()+esq->get_Tam();
  IN *p = new IN(tam); 
  if(dir->get_Dado(0) < esq->get_Dado(0)){
    for(int i=0; i< dir->get_Tam(); i++){
      p->set_Dado(dir->get_Dado(i));
    }
    
    for(int i=0; i< esq->get_Tam(); i++){
      p->set_Dado(esq->get_Dado(i));
    }
  }
  else{
    for(int i=0; i< esq->get_Tam(); i++){
      p->set_Dado(esq->get_Dado(i));
    }
       
    for(int i=0; i< dir->get_Tam(); i++){
      p->set_Dado(dir->get_Dado(i));
    }
       
  }
  return p;   
 }
 
 bool base_Condition(IN* pro)const{
  if(pro->get_Tam() > 1) return false;
  else if(pro->get_Tam() == 1) return true;
 }

};

class Problema{
    int *vet; 
    int p;
    int tam;
    int final;
    int inicial;
    
    int meio;
   
    public: 
    Problema(int ta){
      this->tam=ta;
      this->inicial=0;
      this->vet = new int[tam];
    }
    
    Problema(){
      this->vet=NULL;
      this->inicial=0;
      this->tam=0;
    }

    Problema( const Problema &e){
     this->vet=e.vet;
     this->tam=e.tam;
     this->inicial=e.inicial;
     for(int i; i<e.tam; i++)
        this->vet[i]=e.vet[i];
    }

    void set_Dado(int n){
        if(this->inicial < this->tam) {
          this->vet[this->inicial]=n;
          this->inicial++;
        } 
    }

    int get_Dado(int pos){
        return this->vet[pos];
    } 
    int get_Tam(){
        return this->tam;
    }

    void remove(){
        this->tam--;
    }
};


template<class IN, class OUT>
class Mydc_fib: public DC<IN,OUT>
{
 public:  
 Mydc_fib(IN *_in, OUT *_out): DC<IN,OUT>(_in,_out){}

 ~Mydc_fib(){} 

 IN *split(IN *problema,int lado)const{
   IN *pro;
   
   if(lado==0){
      pro = new IN(problema->get_Dado()-1);
   }
   else{
       pro = new IN(problema->get_Dado()-2); 
   }
   return pro;
 }

 OUT* merge(IN  *dir, IN *esq)const {
  IN *p = new IN(dir->get_Dado()+esq->get_Dado()); 
  return p;   
 }
 
 bool base_Condition(IN* pro)const{
  if(pro->get_Dado() > 1) return false;
  else  return true;
 }
 
};


template<class IN, class OUT>
class Mydc_fib2: public DC<IN,OUT>
{
 public:  
 Mydc_fib2(IN *_in, OUT *_out): DC<IN,OUT>(_in,_out){}
~Mydc_fib2(){} 

 IN *split(IN *problema,int lado)const{
   IN *pro;
   
   if(lado==0){
      pro = new IN(problema->get_Dado()-1);
   }
   else{
       pro = new IN(problema->get_Dado()-2); 
   }
   return pro;
 }

 OUT* merge(IN  *dir, IN *esq)const {
   IN *p = new IN(dir->get_Dado()+esq->get_Dado()); 
   return p;  
 }
 
 bool base_Condition(IN* pro)const{
  if(pro->get_Dado() > 1) return false;
  else  return true;
 }
};

class Problema_fib{
    int valor;
       
    public: 
    Problema_fib(int val){
      this->valor=val;
    }
    
    Problema_fib(){
      this->valor=0;
    }

    Problema_fib( const Problema_fib &e){
     this->valor=e.valor;
    }

    void set_Dado(int val){
        this->valor=val;
    }

    int get_Dado(){
        return this->valor;
    } 
    ~Problema_fib(){}
};



int main(){
   int tamanho=10;
   Problema *pro_in = new Problema(tamanho);
   Problema *pro_out = new Problema();
   
   cout << "Teste o Merge Sorte" << endl;
   cout <<"Vetor de entrada : " ;
   for(int i=tamanho; i > 0; i--){ 
     pro_in->set_Dado(i);
     cout << i << " "; 
   }
   cout << endl;
   
   Mydc_merge_sort<Problema,Problema> *my = new Mydc_merge_sort<Problema,Problema>(pro_in,pro_out);
   my->run();
   pro_out=my->getDataOut();
  cout <<"Vetor de saida: " ;   
  for(int i=0; i<tamanho; i++) cout << pro_out->get_Dado(i) << " "; 
  cout << endl;
  cout <<endl; 
  
  cout << "Test Fibonaci" << endl;
  
  Problema_fib *pro_in_fib = new Problema_fib(10);
  Problema_fib *pro_out_fib = new Problema_fib();
    
  Mydc_fib<Problema_fib,Problema_fib> *my_fib = new Mydc_fib<Problema_fib,Problema_fib>(pro_in_fib,pro_out_fib);
  my_fib->run();
  pro_out_fib=my_fib->getDataOut();
  
  cout << pro_out_fib->get_Dado() <<endl;

  
  return 0;
}
