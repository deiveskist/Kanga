#include <iostream>

//#include "/home/deives/Anahy-3/SRC/AnahyVM.h"
//#include "/home/deives/Anahy-3/SRC/AnahyJob.h"

#include "Esqueleto_MapReduce.h"

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
class MyMapReduce: public MapReduce<IN,OUT>{
  public:
   MyMapReduce(OUT* (&func_map)(IN*),OUT* (&func_reduce)(IN*,IN*),IN* list_in,OUT* data_out, int tam_list, int num_th) : MapReduce<IN,OUT>(func_map,func_reduce,list_in,data_out,tam_list, num_th){}
   ~MyMapReduce(){};
    IN* split(IN *list_in,int n_thread) const{
        Nodo * no = new Nodo();
	*no = list_in[n_thread];
        return no;
    }
    OUT* merge(OUT *list_out, int n_thread,  OUT split_out)const {
      list_out[n_thread]=split_out;
      return list_out;
   }
};


Nodo* funcMap( Nodo * elemento ){
  Nodo * no = new Nodo();
  int v = elemento->getX();
  no->setX(v);
  return no;
}

Nodo* funcReduce(Nodo * elemento1, Nodo * elemento2){
  Nodo * no = new Nodo();
  int v = elemento1->getX()+elemento2->getX(); //soma dois elementos
  no->setX(v);
  return no;
}

int main(int argc, char **argv){
 //   AnahyVM::init(argc, argv);
  // testa com uma função
  int ta=5;
  Nodo lista_in[ta];
  Nodo *data_out;
  cout<< "Entrada do MapReduce: ";
  for(int i=0; i< ta;i++){ 
//     Nodo no(i+1);
    lista_in[i].setX(i+1);
    cout << i+1 << " ";
  }
  cout << endl;  

  MyMapReduce<Nodo,Nodo> *mapred= new MyMapReduce<Nodo,Nodo>(funcMap,funcReduce,lista_in,data_out,ta,ta);
  mapred->run();
  data_out=mapred->getDataOut();
  
  cout <<"Saida do MapReduce: "<< data_out->getX() <<" " << endl;  
  return 0;
}
