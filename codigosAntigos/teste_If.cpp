#include <iostream>
#include "Esqueleto_If.h"
#include "Esqueleto_Map.h"
#include "Esqueleto_Reduce.h"
using namespace std;
class NodoMap{
  private:
    int x;
    
  public:
  
    NodoMap(const NodoMap &e){
      this->x=e.x;
    }
    
    NodoMap(){
      this->x=0;
    }
    
    NodoMap(int x){
      this->x=x;
    }
    
    void setX(int x){
      this->x=x;
    }
    
    int getX(){
      return this->x;
    }
};


template<class IN, class OUT>
class MyMap: public Map<IN,OUT>{
  public:
    MyMap(OUT* (&func)(IN*),IN *list_in, OUT *list_out,int tam_list, int num_th) : Map<IN,OUT>(func,list_in,list_out,tam_list, num_th){}
   ~MyMap(){ };
    
    IN * split(IN *list_in,int n_thread) const{
        NodoMap * no = new NodoMap();
	*no = list_in[n_thread];
        return no;
    }
    
   OUT * merge(OUT *list_out, int n_thread,  OUT split_out)const {
        list_out[n_thread]=split_out;
	return list_out;
   }
};

class NodoReduce{
  private:
    int x;
    
  public:
  
    NodoReduce(const NodoReduce &e){
      this->x=e.x;
    }
    
    NodoReduce(){
      this->x=0;
    }
    
    NodoReduce(int x){
      this->x=x;
    }
    
    void setX(int x){
      this->x=x;
    }
    
    int getX(){
      return this->x;
    }
};

template<class IN, class OUT>
class MyReduce: public Reduce<IN,OUT>{
  public:
    MyReduce(OUT* (&func)(IN*,IN*),IN *list_in,OUT * data_out,int tam_list, int num_th) : Reduce<IN,OUT>(func,list_in,data_out,tam_list, num_th){}
   ~MyReduce(){};
  /*
    como usar os metodos Split e Merge ???
   */
};

NodoReduce* funcReduce(NodoReduce * elemento1, NodoReduce * elemento2){
  NodoReduce * no = new NodoReduce();
  int v = elemento1->getX()+elemento2->getX(); //soma dois elementos
  no->setX(v);
  return no;
}

NodoMap* funcMap( NodoMap * elemento ){
  NodoMap * no = new NodoMap();
  int v = elemento->getX();
  no->setX(v * 2);
  return no;
}

int main(int argc, char **argv){
 // AnahyVM::init(argc, argv);
  int ta=5;
  NodoMap lista_in_map[ta];
  NodoMap lista_out[ta];
  
  NodoReduce lista_in_red[ta];
  NodoReduce * data_out= new NodoReduce();
  
 
  for(int i=0; i< ta;i++){ 
    lista_in_map[i].setX(i+1);
    lista_in_red[i].setX(i+1);
    cout << i+1 << " ";
  }
  cout << endl;  
  MyMap<NodoMap,NodoMap> *mymap = new MyMap<NodoMap,NodoMap>(funcMap,lista_in_map,lista_out,ta,ta); 
  MyReduce<NodoReduce,NodoReduce> *myred = new MyReduce<NodoReduce,NodoReduce>(funcReduce,lista_in_red,data_out,ta,ta);
  
  IF<NodoMap,NodoMap,NodoReduce,NodoReduce> *myif = new IF<NodoMap,NodoMap,NodoReduce,NodoReduce>(mymap,myred);
  myif->run(true);
  
  cout << "Saida do Map: " ;
  for(int i=0; i< ta;i++) cout << lista_out[i].getX() <<" ";
  
  cout << endl;  
  
  myif->run(false);
  data_out=myred->getDataOut();
  
  cout <<"Saida do Reduce: " << data_out->getX() <<" " << endl;  
  //AnahyVM::terminate();
  return 0;
}


