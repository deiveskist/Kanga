#include <iostream>
#include "Esqueleto_Reduce.h"

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
class MyReduce: public Reduce<IN,OUT>{
  public:
    MyReduce(OUT* (&func)(IN*,IN*),IN *list_in,OUT * data_out,int tam_list, int num_th) : Reduce<IN,OUT>(func,list_in,data_out,tam_list, num_th){}
   ~MyReduce(){};
  /*
    como usar os metodos Split e Merge ???
   */
};

Nodo* func(Nodo * elemento1, Nodo * elemento2){
  Nodo * no = new Nodo();
  int v = elemento1->getX()+elemento2->getX(); //soma dois elementos
  no->setX(v);
  return no;
}


int main(int argc, char **argv){
 // AnahyVM::init(argc, argv);
  int ta=5;
  Nodo lista_in[ta];
  Nodo * data_out= new Nodo();
  
 cout << "Entrada do Reduce: " ;
  for(int i=0; i< ta;i++){ 
    lista_in[i].setX(i+1);
    cout << i+1 << " ";
  }
  cout << endl;  
   
  MyReduce<Nodo,Nodo> *red = new MyReduce<Nodo,Nodo>(func,lista_in,data_out,ta,ta);
  red->run();
  
  data_out=red->getDataOut();
  
  cout <<"Saida do Reduce: " << data_out->getX() <<" " << endl;  
  
    
  //AnahyVM::terminate();
  return 0;
}
