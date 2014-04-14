/*
* Classe abstrata Kanga
* Todos os metodos são virtuais 
* Define a interface
*/
#ifndef Kanga_H
#define Kanga_H
#include <iostream>
#include <string>
#include <exception>
  
using namespace std;
namespace kanga{
 
template<class IN, class OUT>
class Kanga {
  public:
   virtual OUT* runDC(){}; 
   virtual void start()=0; // inicia a execução do esqueleto
   virtual void join()=0;  // sincroniza a execução do esqueleto
   virtual void setDataIn(IN* data)=0; // seta os dados de entrada do esqueleto
   virtual void setDataIn(IN* dataIn, IN * dataIn1){};
   virtual void setDataOut(OUT*& data){};
   virtual OUT *getDataOut()=0; // retorna os dados de saída
   virtual Kanga<IN,OUT> * clone(){}; // cria clones do objeto
   virtual Kanga<IN,OUT> * clone(IN * listIn, OUT *& listOut){};
   virtual Kanga<IN,OUT> * clone(IN * listIn1, IN * listIn2, OUT *& listOut){};
   virtual void setFunction(OUT* (*f) (IN*)){};
   virtual void setFunction(OUT* (*f) (IN*,IN*)){};
};


struct KException : public exception
{
  const char * what () const throw ()
  {
    return "Objeto não inicializado corretamente";
  }
};

};//end namespace

#endif
