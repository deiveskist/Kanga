#include <iostream>
#include "Esqueleto_Map.h"

using namespace std;
class Nodo{
  private:
    int x;
    
  public:
  
    Nodo(const Nodo &e){
      this->x=e.x;
    }
    
    Nodo(){
      this->x=0;
    }
    
    Nodo(int x){
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
        Nodo no[2];
	no[0] = list_in[n_thread];
	no[1] = list_in[n_thread];
       return no;
    }
    
   OUT * merge(OUT *list_out, int n_thread,  OUT split_out)const {
        list_out[n_thread]=split_out;
	return list_out;
   }
};


Nodo* func( Nodo * elemento ){
  Nodo * no = new Nodo();
  int v = elemento->getX();
  no->setX(v * 2);
  return no;
}

int main(int argc, char **argv){
 //   AnahyVM::init(argc, argv);
  // testa com uma função
  int ta=10;
  Nodo lista_in[ta];
  Nodo lista_out[ta];
  cout << "Entrada do Map: " ;
  for(int i=0; i< ta;i++){ 
    lista_in[i].setX(i+1);
    cout << i+1 << " ";
  }
  cout << endl;  
  
  MyMap<Nodo,Nodo> *mymap = new MyMap<Nodo,Nodo>(func,lista_in,lista_out,ta,5);
  mymap->run();  
  cout << "Saida do Map: " ;
  for(int i=0; i< ta;i++) cout << lista_out[i].getX() <<" ";
  
  cout << endl;  
  
}