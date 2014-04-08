#include <iostream>
#include <stdio.h>
#define PTHREADS
#include "Reduce.h"
#include "Zip.h"
using namespace pi;
using namespace std;

int* func(int* x, int* y){
  *x=*x+*y;
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

int maior(int a, int b){
  if(a > b) return a;
  else return b;
}


int main(){
  int ta=100;
  int *listaIn = new int[ta];
  int *dataOut; 
  int i;
  
  
  for(i=0; i< ta;i++){
    listaIn[i]=i+1;
    cout << i+1 << " ";
  }
  int valor;
  cout << endl;
  Reduce<int> *red= new Reduce<int>(func,listaIn, dataOut,ta);
  red->start();
  red->join();
  
  cout << *dataOut <<endl;
  
 // cout << endl;
  //cout << endl;
   
  int **matIn;
  int * listOut;
  
  int row = 2;
  int col = 10;
    
  cout << "Entrada do Reduce Composite: " ;
  cout <<"\n";
  matIn = CreateMatrix(row, col);
  MatrixInput(matIn, row, col);
  PrintMatrix(matIn, row, col);
  cout << endl;

  Zip<int,int> *zip = new Zip<int,int>(func,col);
  Reduce<int> *redfora = new Reduce<int>(zip,matIn,listOut,row);
  redfora->start();
  redfora->join();
  //listOut= redfora->getDataOut();
  cout <<" Saida do MapComposite: ";
  cout <<"\n";
  
  for(i=0; i< col;i++){ 
    printf("%3d ", listOut[i]);
  }
  printf("\n");
  

  //####################################3
/*
 int tam=500;
  int *listaInMaior = new int[tam];
  int *dataOutMaior; 
  
  
   cout << "Entrada do Reduce Maior: " ;
  cout <<"\n";
  for(i=0; i< tam;i++){
    listaInMaior[i]=i+1;
  //  cout << i+1 << " ";
  }
  cout << endl;
  Reduce<int> *redMaior= new Reduce<int>(maior,listaInMaior, dataOutMaior,tam);
  redMaior->start();
  redMaior->join();

  cout <<" Saida do MapComposite: " << endl;
  
  cout << *dataOutMaior <<endl;
  
  cout << endl;
  cout << endl;
  */
  return 0;
}