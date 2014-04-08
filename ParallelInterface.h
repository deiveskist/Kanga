#ifndef Kanga_H
#define Kanga_H

//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>
//#include <utility>   


//using namespace std;
namespace kanga{
  
template<class IN, class OUT>
class Kanga {
  protected:
   
  public:
   virtual void start(){};
   virtual void join(){};
  // virtual void setFunction(OUT* (*f) (IN*)){};
   //virtual void setFunction(OUT* (*f) (IN*,IN*)){};
   //virtual void setFunction(OUT* (*(*f)) (IN*)){};
   //virtual void setLength(int n){};
   virtual void setDataIn(IN* data){};
   virtual void setDataIn(IN* dataIn, IN * dataIn1){};
   virtual void setDataOut(OUT*& data){};
   virtual OUT *getDataOut(){};
   virtual Kanga<IN,OUT> * clone(){};
   virtual Kanga<IN,OUT> * clone(IN * listIn, OUT *& listOut){};
   virtual Kanga<IN,OUT> * clone(IN * listIn1, IN * listIn2, OUT *& listOut){};

};

}//end namespace

#endif