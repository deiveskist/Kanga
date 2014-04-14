#include <iostream>
#include <stdio.h>
#define PTHREADS
#include "MapReduce.h"
#include "Map.h"
#include "Fork.h"
#include "Scan.h"
#include "Zip.h"

using namespace pi;
using namespace std;

int* funcmap(int *x){
  //*x++;
  return x;
}

int* funcreduce(int* x, int* y){
  int *v = new int;
  *v=*x+*y;
  return v;
}

int **CreateMatrix(int row, int col) {
  int **matrix = new int*[row];
  int i;
  for (i = 0; i < row; i++) {
    matrix[i] = new int[col];
  }
  return matrix;
}

// Take input for the matrix.
void MatrixInput(int **matrix, int row, int col) {
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      matrix[i][j]=i+j+1;
    }
  }
}

void PrintMatrix(int **matrix, int row, int col) {
  int i, j;
  for (i = 0; i < row; i++) {
     for (j = 0; j < col; j++) {
      printf("%3d", matrix[i][j]);
     }
    cout << endl;
  }
}

struct DotProduct{
  int x;
  int y;
  int r;
};

DotProduct*  multiFunc(DotProduct* e){
  e->r= e->x*e->y;
  return e;
}

DotProduct* plusFunc(DotProduct* a,DotProduct* b){
  a->r=a->r+b->r;
  return a;
}

int* dobro(int *x){
  *x=*x*2;
  return x;
}

int* triplo(int *x){
  *x=*x*3;
  return x;
} 

int* soma2(int* x){
  *x=*x+2;
  return x;
}

int* soma4(int* x){
  *x=*x+4;
  return x; 
}


int main(){
 
  int ta=5;
  int *listaIn = new int[ta];
  int *dataOut; 
  int i;
      
  for(i=0; i< ta;i++){
    listaIn[i]=i+1;
    cout << i+1 << " ";
  }

  cout << endl;

  MapReduce<int,int> *mapred= new MapReduce<int,int>(funcmap,funcreduce,listaIn, dataOut,ta);
  mapred->start();
  mapred->join();
  
  cout << *dataOut <<endl;
  cout << endl;
  cout << endl;

//#####################################################  
  int **matIn;
  int * listOut;
  int row = 2;
  int col = 4;
    
  cout << "Entrada do MapReduce Composite: " << endl;
  
  matIn = CreateMatrix(row, col);
  MatrixInput(matIn, row, col);
  PrintMatrix(matIn, row, col);
  cout << endl;

  Map<int,int> *map = new Map<int,int>(funcmap,col);
  Zip<int,int> *zip = new Zip<int,int>(funcreduce,col);
  MapReduce<int,int> *mapredComp = new MapReduce<int,int>(map,zip,matIn,listOut,row);
  mapredComp->start();
  mapredComp->join();
 
  cout <<"Saida do MapReduce Composite: " << endl;
  
  for(i=0; i< col;i++){ 
    printf("%3d ", listOut[i]);
  }
  cout << endl;
  cout << endl;

  //#####################################################  
  //int **matIn;
  //int * listOut;
  
  int* (*listFunc[4])(int*) = {dobro,triplo,soma2,soma4};
    
  cout << "Entrada do MapReduce Composite: " << endl;
  
  matIn = CreateMatrix(row, col);
  MatrixInput(matIn, row, col);
  PrintMatrix(matIn, row, col);
  cout << endl;

  Fork<int,int> *fork = new Fork<int,int>(listFunc,col);
  
  mapredComp = new MapReduce<int,int>(fork,zip,matIn,listOut,row);
  mapredComp->start();
  mapredComp->join();
 
  cout <<"Saida do MapReduce Composite: " << endl;
  
  for(i=0; i< col;i++){ 
    printf("%3d ", listOut[i]);
  }
  cout << endl;
  cout << endl;


//#####################################################
 /* 
  int lenDot=10;  
  DotProduct *dot = new DotProduct[lenDot];
  DotProduct *dotOut;
  cout << "Entrada do MapReduce DotProduct: " << endl;
  for(i=0; i< lenDot;i++){
    dot[i].x=i+1;
    dot[i].y=i+2;
  }

  MapReduce<DotProduct,DotProduct> *mapredDot= new MapReduce<DotProduct,DotProduct>(multiFunc,plusFunc, dot,dotOut,lenDot);
//  mapredDot->start();
  //mapredDot->join();

  cout <<"Saida do MapReduce DotProduct: ";
  //cout << *dotOut <<endl;
  */
  return 0;
}