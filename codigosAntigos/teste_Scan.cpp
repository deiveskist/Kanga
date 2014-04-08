#include <iostream>
#include "Esqueleto_Scan.h"

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
class MyScan: public Scan<IN,OUT>{
  public:
    MyScan(OUT* (&func)(IN*,IN*),IN *list_in, OUT *list_out, int tam_list, int num_th) : Scan<IN,OUT>(func,list_in,list_out,tam_list, num_th){}
   ~MyScan(){ };
    IN*  split(IN *list_in,int n_thread) const{
        Nodo * no = new Nodo();
	*no = list_in[n_thread];
        return no;
    }
    
   OUT* merge(OUT *list_out, int n_thread,  OUT split_out)const {
        list_out[n_thread]=split_out;
	return list_out;
   }
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
  Nodo lista_out[ta];
 cout << "Entrada do Scan: " ;
  for(int i=0; i< ta;i++){ 
    lista_in[i].setX(i+1);
    cout << i+1 << " ";
  }
  cout << endl;  

  MyScan<Nodo,Nodo> *scan = new MyScan<Nodo,Nodo>(func,lista_in,lista_out,ta,ta);
  scan->run();
 
  cout << "Saida do Scan: " ;
  for(int i=0; i< ta;i++) cout << lista_out[i].getX() <<" ";
  
  cout << endl;  
  //AnahyVM::terminate();
  return 0;
}
