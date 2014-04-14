#include <iostream>
#include <stdio.h>
#define PTHREADS
//#define ANAHY

#include "../Fork.h"

using namespace kanga;

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


int main(int argc, char **argv){
  //  AnahyVM::init(argc, argv);
  // testa com uma função
  int* (*func[5])(int*) = {dobro,triplo,soma2,soma4,soma6};
  int ta=5;
  int *lista_in = new int[ta];
  int *lista_out;
  int i;
  
  Fork<int,int> fork1;
  fork1.start();
  fork1.join();

  cout << "Entrada do Fork: " ;
  for(i=0; i< ta;i++){
    lista_in[i]=i+1;
    cout << i+1 << " ";
  }
  cout << endl;
  Fork<int,int> *fork= new Fork<int,int>(func,lista_in,lista_out,ta);
  fork->start();
  fork->join();
  
  cout << "Saida do Fork: " ;
  for(i=0; i< ta;i++) cout << lista_out[i] <<" ";

  
  cout << endl;
  cout << endl;
   
  int **matIn;
  int **matOut;
  
  int row = 5;
  int col = 5;

  /*
  for (i = 0; i < row; i++) {
    matIn[i] = new int[col];
    matOut[i] = new int[col];
  }
  
  */

  cout << "Entrada do Fork Composite: " ;
  cout <<"\n";
  matIn = CreateMatrix(row, col);
  
  MatrixInput(matIn, row, col);
  PrintMatrix(matIn, row, col);
  cout << endl;

  /*Fork<int,int> *forkdentro = new Fork<int,int>(func,col);
  Fork<int,int> *forkfora = new Fork<int,int>(forkdentro,matIn,matOut,row);
  forkfora->start();
  forkfora->join();
  */ 
  cout <<" Saida do Fork Composite: ";
  cout <<"\n";
  //PrintMatrix(matOut, row, col);
  //AnahyVM::terminate();
  return 0;
}
