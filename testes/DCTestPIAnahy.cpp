#include <stdio.h>
#include "compute_time.c"
#define ANAHY

#include "../DC5.h"
using namespace kanga;

void merge(int *a,int i, int j)
{
  int mid = (i+j)/2;
  int ai = i;
  int bi = mid+1;

 int *newa= new int[j-i+1];
  int newai = 0;

  while(ai <= mid && bi <= j) {
    if (a[ai] > a[bi])
        newa[newai++] = a[bi++];
    else                    
        newa[newai++] = a[ai++];
  }

  while(ai <= mid) {
    newa[newai++] = a[ai++];
  }

  while(bi <= j) {
    newa[newai++] = a[bi++];
  }

  for (ai = 0; ai < (j-i+1) ; ai++)
    a[i+ai] = newa[ai];

  delete newa;
}

class PMergeSort: public ProblemaDC{
private:
  int inicio,meio,fim;
  int i,aux, j, k;
  int tam;
  int *arr;
public:
  PMergeSort(){
    this->inicio=0;
    this->meio=0;
    this->fim=0;
    this->tam=0;
    this->arr=NULL;
  }

  PMergeSort(const PMergeSort& e){
    this->inicio=e.inicio;
    this->meio=meio;
    this->fim=fim;
    this->tam=e.tam;
    this->arr=e.arr;
  }

  PMergeSort(int *arr,int inicio,int fim){
    this->inicio=inicio;
    this->meio=meio;
    this->fim=fim;
    this->meio=(inicio+fim)/2;
    this->tam=fim-inicio;
    this->arr=arr;

  }

  PMergeSort(int *arr,int inicio,int fim, int tam){
    this->inicio=inicio;
    this->meio=meio;
    this->fim=fim;
    this->meio=(inicio+fim)/2;
    this->tam=tam;
    this->arr=arr;
  }
  
  ~PMergeSort(){
 
  } 

  int base(){
    if(this->inicio < this->fim) return 0;
    else return 1;
  }

  PMergeSort* divisaoDir(){  
    //  printf("dir ini: %d fim: %d \n",this->inicio,this->meio);
    return new PMergeSort(this->arr,this->inicio,this->meio,(this->tam+1)/2);
  }

  PMergeSort* divisaoEsq(){  
    //printf("esq ini: %d fim: %d \n",this->meio+1,this->fim);
    return new PMergeSort(this->arr,this->meio+1,this->fim,this->tam/2);
  }

  void conquista(){
     //partition(this->inicio,this->fim);    
    merge(this->arr,this->inicio,this->fim);
  }

  void combina(PMergeSort* esq, PMergeSort* dir){
        
    if(esq->inicio < dir->inicio){
      merge(arr,esq->inicio,dir->fim);
    }
    else{
      merge(arr,dir->inicio,esq->fim);
    }
  }  
};

int main(int argc, char **argv){
  AnahyVM::init(argc, argv);
  int n=atoi(argv[1]);
  int *arr = new int[n];
  int i;
  for(i=0;i<n;i++) arr[i]=n-i;

  //for(i=0; i < n;i++) printf("%d ", arr[i]); 
  //printf("\n");
 
  PMergeSort *mergeIn = new PMergeSort(arr,0,n-1,n);
  PMergeSort *mergeOut= new PMergeSort();
  
  time_log_start();  
  DC<PMergeSort> *dcMerge = new DC<PMergeSort>(mergeIn,mergeOut);

  dcMerge->start();
  dcMerge->join();
  time_log_stop();

  //for(i=0; i < n;i++) 
  printf("; %d ; %d ",arr[0], arr[n-1]);
  //printf("\n");
 
  
  AnahyVM::terminate();
  dcMerge->printQ();
  
  //delete mergeIn;
  //delete mergeOut;
  //delete dcMerge;
  delete arr;
  return 0;
}
