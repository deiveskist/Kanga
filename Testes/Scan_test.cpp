/*
 * Scan_test.cpp
 *

 */
#include <iostream>
#include <stdio.h>
#define PTHREADS
#include "../Scan.h"

using namespace std;
using namespace kanga;

int* func(int* x, int* y){
  int a =*x+*y;
  int *r= new int;
  *r=a;
  return r;
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
      printf("%3d ", matrix[i][j]);
    }
    cout << endl;
  }
}

int main(int argc, char **argv){
 //   AnahyVM::init(argc, argv);
  int ta=4;
  int *lista_in = new int[ta];
  int *lista_out;
  int i;

  Scan<int> scan1;
  scan1.start();
  scan1.join();
  
  cout << "Entrada do Scan: " ;
  cout << endl;
  for(i=0; i< ta;i++){
    lista_in[i]=i+1;
    printf("%3d ",i+1);
  }
  printf("\n");
  Scan<int> *scan= new Scan<int>(func,lista_in,lista_out,ta);
  scan->start();
  scan->join();
  cout << "Saida do Scan: " << endl;
  for(i=0; i< ta;i++){ 
    
    printf("%3d ",lista_out[i]);
  }
  cout << endl;
  
  return 0;
}