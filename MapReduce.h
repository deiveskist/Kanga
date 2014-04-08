/*
 * MapReduce.h
 *
 *  Created on: 15/10/2013
 *      Author: deives
 */

#ifndef MAPREDUCE_H_
#define MAPREDUCE_H_


#include "Thread.h"
#include "DataParallelism.h"

namespace kanga{

template<class IN,class OUT>
class MapReduce : public DataParallelism<IN,OUT>{
  
  public:
    MapReduce(): DataParallelism<IN,OUT>(){
     this->funcMap=NULL;
     this->funcReduce=NULL;
     this->efunc=NULL;
     this->objMap=NULL;
     this->objRed=NULL;   
     this->pri=true;
    }
    
    MapReduce(const MapReduce &e) : DataParallelism<IN,OUT>(e){
     this->funcMap=e.funcMap;
     this->funcReduce=e.funcReduce;
     this->efunc=e.efunc;    
     this->objRed=e.objRed;
     this->objMap=e.objMap;
     this->pri=e.pri;
    }
    
    MapReduce(OUT* (*fMap)(IN*), OUT* (*fReduce)(OUT*,OUT*), IN * listIn, OUT *& listOut, int length) : DataParallelism<IN,OUT>(listIn,listOut,length)
    {
      this->funcMap=fMap;
      this->funcReduce=fReduce;
      this->efunc=true;
      this->pri=true;
      this->listInter= new OUT[length];
     }
    
    MapReduce(OUT* (*fMap)(IN*), OUT* (*fReduce)(OUT*,OUT*), int length) : DataParallelism<IN,OUT>(length)
    {
      this->funcMap=fMap;
      this->funcReduce=fReduce;
      this->efunc=true; 
      this->pri=true;
      this->listInter= new OUT[length];
    }
    
    MapReduce(Kanga<IN,OUT> * objMap, Kanga<IN,OUT> * objRed, IN **matIn, OUT *&listOut, int length): DataParallelism<IN,OUT>(matIn,listOut,length)
    {
      this->objMap=objMap;
      this->objRed=objRed;
      this->funcMap=NULL;
      this->funcReduce=NULL;
      this->efunc=false;
    }
         
    void start(){
       this->matOutTemp1= new OUT*[this->length];
      if(this->efunc==true){
	     thdrun = new Thread< MapReduce< IN,OUT> ,OUT>(&MapReduce< IN, OUT>::tRun,this);
	     thdrun->start();
      }
      else if(this->efunc==false){
	     thdrun = new Thread< MapReduce< IN,OUT> ,OUT>(&MapReduce< IN, OUT>::tRunComp,this);
	     thdrun->start();  
      }  
    }
    
    void join(){
      if(this->efunc==true){
      	thdrun->join();
        this->listOut=this->thdrun->getDataOut();
      }
      else if(this->efunc==false){
	     thdrun->join();
       this->listOut=this->thdrun->getDataOut();   
      }      
    }
  
    Kanga<IN,OUT> * clone(){
      return new MapReduce< IN,OUT>(this->funcMap,this->funcReduce,this->length);
    }
  
    OUT * getDataOut(){
      return this->listOut;
    }

    virtual ~MapReduce(){
      delete this->objRed;
      delete this->objMap;
    }

    void setFunction(OUT* (*fMap)(IN*), OUT* (*fReduce)(OUT*,OUT*)){
      this->funcMap=fMap;
      this->funcReduce=fReduce;
      this->efunc=true;
    }
    
    void setLength(int n){
      this->length=n;
    }
    
  private:
      
    OUT* run(){
      //Parte do Map ///
      this->threadsMap= new Kanga<IN,OUT>*[this->length];
      for(i=0; i < this->length; i++) {
          this->threadsMap[i]=new Thread<IN,OUT>(this->funcMap,&this->listIn[i]);
          this->threadsMap[i]->start();
      }

      for(i=0; i< this->length; i++){
          this->threadsMap[i]->join();
          this->listInter[i]=*this->threadsMap[i]->getDataOut();
// 	  printf("%d \n",this->listIn[i]);
      }

      //Parte do Reduce//
      this->threadsRed= new Kanga<OUT,OUT>*[this->length];
      while(this->length > 1){
        if(this->pri==true){
	         this->pri=false;
           if(this->length%2==0){ 
            this->length=this->length/2;
           }
           else{
            this->dataAux=this->listInter[this->length-1];
      	    this->length= this->length/2; 
      	    this->length++;
      	    this->impar=true;
      	    //this->listOutTemp[this->length+1]=this->dataAux;
          }
                 
          for(i=0;i< this->length;i++){
            this->threadsRed[i]=new Thread<OUT,OUT>(this->funcReduce,&this->listInter[2*i],&this->listInter[(2*i)+1]);
            this->threadsRed[i]->start();
          }
        }
  
        else{

          if(this->length%2==0){ 
             this->length=this->length/2;
          }
          else{
            this->dataAux=this->listInter[this->length-1];
    	      this->length=this->length/2; 
    	      this->length++;
    	      this->impar=true;
    	      this->listInter[this->length+1]=this->dataAux;
          }
          for(i=0;i< this->length;i++){
            this->threadsRed[i]=new Thread<OUT,OUT>(this->funcReduce,&this->listOutTemp[2*i], &this->listOutTemp[(2*i)+1]);
            this->threadsRed[i]->start();
          }
        }

        for(i=0;i< this->length;i++){
           this->threadsRed[i]->join();
    	     this->listOutTemp[i] = *this->threadsRed[i]->getDataOut();
        }   
       /* 
        if(this->impar==true){
          this->listInter[this->length-1]=this->dataAux;
          this->impar=false;
        }
        */
     /* 
       for(int j = 0; j < this->length; j++){
           cout <<" " << this->listOut[j];
       }
       cout << endl;
     */  
      }
      return &this->listOutTemp[0];
    }

    static OUT * tRun(MapReduce<IN,OUT> *mapred){
      return mapred->run();
    }

    int i;
    OUT *ptrData;
    OUT* (*funcMap)(IN*);
    OUT* (*funcReduce)(OUT*, OUT*);
    OUT dataOut;
    OUT * listInter;
    Kanga<IN,OUT> * objMap;
    Kanga<IN,OUT> * objRed;
    bool efunc;
    bool pri;
    bool impar;
    OUT dataAux;
    OUT *matAux;
    Thread<MapReduce< IN, OUT> ,OUT> *thdrun;
    Kanga< IN, OUT> **threadsMap;
    Kanga< OUT, OUT> **threadsRed;
    OUT **matOutTemp1;
 
    static OUT* tRunComp(MapReduce<IN,OUT> *mapred){
      return mapred->runComp();
    }

    void stepMapMat(){
      this->threadsMap= new Kanga<IN,OUT>*[this->length];
      for(i=0; i < this->length; i++) {
        this->threadsMap[i]=this->objMap->clone( this->matIn[i], this->matOutTemp[i]);
        this->threadsMap[i]->start();
      }
   
      for(i=0; i< this->length; i++){
        this->threadsMap[i]->join();
      }
    }

    OUT* stepRedMat(){
     
      this->threadsRed = new Kanga<IN,OUT>*[this->length];
      if(this->length == 1){
        return this->matOutTemp[0];
      }
      else{
        if(this->length%2==0){ 
          this->length=this->length/2;
        }
        else{
          this->matAux=this->matOutTemp[this->length-1];
          this->length=this->length/2; 
          this->length++;
          this->impar=true;
          this->matOutTemp[this->length+1]=this->matAux;
        }

        for(i=0; i< this->length ; i++){
          this->threadsRed[i]=this->objRed->clone(this->matOutTemp[2*i],this->matOutTemp[(2*i)+1],this->matOutTemp[i]);
          this->threadsRed[i]->start();
        }
      }//fecha o else

      for(i=0;i< this->length;i++){
        this->threadsRed[i]->join();
      }
      if(this->impar==true){
        this->matOutTemp[this->length-1]=this->matAux;
        this->impar=false;
      }
      return this->stepRedMat();
    }

    OUT* runComp(){
    	this->stepMapMat();
      return this->stepRedMat();
    }
};//end classe

}//end namespace
#endif /* MapReduce_H_ */
