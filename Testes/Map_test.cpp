/*
 * Map_test.cpp
 *
 *  Created on: 25/09/2013
 *      Author: deives
 */
#include <iostream>
#include <stdio.h> 

#define PTHREADS

#include "../Map.h"
#include "../Fork.h"
#include "../Reduce.h"
#include "../Scan.h" 

using namespace std;
using namespace kanga;

int* func(int* x){
  //cout << *x << endl;
  int a = *x+10;
  int *r= new int;
  *r=a;
  return r;
}

int* funcRed(int* x, int* y){
  int a =*x+*y;
  int *r= new int;
  *r=a;
  return r;
}

int* funcScan(int* x, int* y){
  ///printf("x %d y  %d \n", *x,*y);
  int a =*x+*y;
  int *r= new int;
  *r=a;
  return r;
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

int* soma6(int* x){
  *x=*x+6;
  return x; 
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
      matrix[i][j]=i;
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

struct VetIn{
  int x;
  int y;
  int a;
};

int * funcSax( VetIn* n){
  int v = n->a * n->x + n->y;
  int * c=&v;
 return c;
}

int main(int argc, char **argv){
   //AnahyVM::init(argc, argv);
  // testa com uma função
 
  int ta=10;
  int *lista_in = new int[ta];
  int *lista_out;
  int i;
  
  kanga::Map<int,int> map1;
  map1.setFunction(func);
  map1.start(); 
  map1.join();

  cout << "Entrada do Map: " ;
  for(i=0; i< ta;i++){
    lista_in[i]=i+1;
    cout << i+1 << " ";
  }
  cout << endl;
  
  Map<int,int> *map= new Map<int,int>(func,lista_in,lista_out,ta);
  map->start();
  map->join();
  cout << "Saida do Map: " ;
  for(i=0; i< ta;i++) cout << lista_out[i] <<" ";

  cout << endl;
  cout << endl;
//##############################################################  
 
  int **matIn;
  int **matOut;
  
  int row = 4;
  int col = 4;
    
  cout << "Entrada do Map com Map: " ;
  cout <<"\n";
  matIn = CreateMatrix(row, col);
  
  MatrixInput(matIn, row, col);
  
  PrintMatrix(matIn, row, col);
  cout << endl;
 
  Map<int,int> *mapdentro = new Map<int,int>(func,col);
  Map<int,int> *mapfora = new Map<int,int>(mapdentro,matIn,matOut,row);
  mapfora->start();
  mapfora->join();
 
  cout <<" Saida do Map com Map: ";
  cout <<"\n";
  PrintMatrix(matOut, row, col);

  //##############################################################  
 
  int **matIn1;
  int **matOut1;
  int* (*listFunc[4])(int*) = {dobro,triplo,soma2,soma4};
  int row1 = 4;
  int col1 = 4;
  cout << "Entrada do Map com Fork: " << endl;
  matIn1 = CreateMatrix(row1, col1);
  
  MatrixInput(matIn1, row1, col1);
  
  PrintMatrix(matIn1, row1, col1);
  cout << endl;
 
  Fork<int,int> *forkdentro = new Fork<int,int>(listFunc,col1);
  Map<int,int> *mapfora1 = new Map<int,int>(forkdentro,matIn1,matOut1,row1);
  mapfora1->start();
  mapfora1->join();
 
  cout <<" Saida do Map com Fork: " << endl;
  PrintMatrix(matOut1, row1, col1);


//##############################################################  
 
  int **matIn2;
  int **matOut2;
  
  int row2 = 4;
  int col2 = 4;
    
  cout << "Entrada do Map com Reduce: " << endl;
  matIn2 = CreateMatrix(row2, col2);
  
  MatrixInput(matIn2, row2, col2);
  
  PrintMatrix(matIn2, row2, col2);
  cout << endl;
 
  Reduce<int> *reddentro = new Reduce<int>(funcRed,col2);
  Map<int,int> *mapfora2 = new Map<int,int>(reddentro,matIn2,matOut2,row2);
  mapfora2->start();
  mapfora2->join();
 
  cout <<" Saida do Map com Reduce: " << endl;
  PrintMatrix(matOut2, row2, 1);

  //##############################################################  
 
  int **matIn3;
  int **matOut3;
  
  int row3 = 4;
  int col3 = 4;
    
  cout << "Entrada do Map com Scan: " << endl;
  matIn3 = CreateMatrix(row3, col3);
  
  MatrixInput(matIn3, row3, col3);
  
  PrintMatrix(matIn3, row3, col3);
  cout << endl;
 
  Scan<int> *scandentro = new Scan<int>(funcScan,col3);
  Map<int,int> *mapfora3 = new Map<int,int>(scandentro,matIn3,matOut3,row3);
  mapfora3->start();
  mapfora3->join();
 
  cout <<" Saida do Map com Scan: " << endl;
  PrintMatrix(matOut3, row3, col3);
    
//##############################################################

  int tamSax=10;
  VetIn* vetinSax = new VetIn[tamSax];
  int *vetOutSax;
  cout << "Entrada do Map Sax: " ;
  for(i=0; i< tamSax;i++){
    vetinSax[i].x=i+1;
    vetinSax[i].a=10;
    vetinSax[i].y=i*2;
    cout << i+1 << " ";
  }
  cout << endl;
  
  Map<VetIn,int> *mapSax= new Map<VetIn,int>(funcSax,vetinSax,vetOutSax,tamSax);
  mapSax->start();
  mapSax->join();
  cout << "Saida do Map Sax: " ;
  for(i=0; i< tamSax;i++) cout << vetOutSax[i] <<" ";
  cout << endl;
  /**/
  //##############################################################

    
  // int **matIn;
  // int **matOut;
  
  // int row = 10;
  // int col = 10;
    
  // cout << "Entrada do MapComposite: " ;
  // cout <<"\n";
  // matIn = CreateMatrix(row, col);
  
  // MatrixInput(matIn, row, col);
  
  // PrintMatrix(matIn, row, col);
  // cout << endl;
 

  // Map<int,int> *mapdentro = new Map<int,int>(func,col);
  // Map<int,int> *mapfora = new Map<int,int>(mapdentro,matIn,matOut,row);
  // mapfora->start();
  // mapfora->join();
 
  // cout <<" Saida do MapComposite: ";
  // cout <<"\n";
  // PrintMatrix(matOut, row, col);
 // AnahyVM::terminate();
  return 0;
}
