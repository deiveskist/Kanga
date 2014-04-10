#include <stdio.h>

#define PTHREADS

#include "DC.h"
#define MAX 100
int arr[MAX];

void mergeSort(int low,int mid,int high);

void partition(int low,int high){

    int mid;

    if(low<high){
         mid=(low+high)/2;
         partition(low,mid);
         partition(mid+1,high);
         mergeSort(low,mid,high);
    }
}

void mergeSort(int low,int mid,int high){

    int i,m,k,l,temp[MAX];
 
    l=low;
    i=low;
    m=mid+1;

    while((l<=mid)&&(m<=high)){

         if(arr[l]<=arr[m]){
             temp[i]=arr[l];
             l++;
         }
         else{
             temp[i]=arr[m];
             m++;
         }
         i++;
    }

    if(l>mid){
         for(k=m;k<=high;k++){
             temp[i]=arr[k];
             i++;
         }
    }
    else{
         for(k=l;k<=mid;k++){
             temp[i]=arr[k];
             i++;
         }
    }
   
    for(k=low;k<=high;k++){
         arr[k]=temp[k];
    }
  //for(int v=low; v < high; v++) {
  	 //printf("%d ", arr[v]);
   //}
   // printf("\n");
}

class PMergeSort: public ProblemaDC{
private:
  int inicio,meio,fim;
  int i,aux, j, k;
  int tam;
public:
  PMergeSort(){
    this->inicio=0;
    this->meio=0;
    this->fim=0;
    this->tam=0;
  }

  PMergeSort(const PMergeSort& e){
    this->inicio=e.inicio;
    this->meio=meio;
    this->fim=fim;
    this->tam=e.tam;
  }

  PMergeSort(int inicio,int fim){
    this->inicio=inicio;
    this->meio=meio;
    this->fim=fim;
    this->meio=(inicio+fim)/2;
    this->tam=fim-inicio;

  }

  PMergeSort(int inicio,int fim, int tam){
    this->inicio=inicio;
    this->meio=meio;
    this->fim=fim;
    this->meio=(inicio+fim)/2;
    this->tam=tam;

  }
  
  int base(){
    if(this->tam < 3) return 1;
    return 0;
  }

  PMergeSort* divisaoDir(){  
    //  printf("dir ini: %d fim: %d \n",this->inicio,this->meio);
     return new PMergeSort(this->inicio,this->meio,(this->tam+1)/2);

  }

  PMergeSort* divisaoEsq(){  
    //printf("esq ini: %d fim: %d \n",this->meio+1,this->fim);
     return new PMergeSort(this->meio+1,this->fim,this->tam/2);
     
  }

  void conquista(){
     //partition(this->inicio,this->fim);    
    mergeSort(this->inicio,this->meio,this->fim);
  }

  void combina(PMergeSort* esq, PMergeSort* dir){
        
    if(esq->inicio < dir->inicio){
       i=esq->inicio;
       j=dir->inicio;
      while(j <= dir->fim){
        k=i;
        while (k < j) {
          if(arr[k] > arr[j]){
            aux=arr[k];
            arr[k]=arr[j];
            arr[j]=aux;
          
          }
           k++;
        }
        j++;
        i++;
      }  
    }
    else{
       i=esq->inicio;
       j=dir->inicio;
     while(i <= dir->fim){
        k=j;
        while (k <= i) {
         // if(arr[k] > arr[j]){
            aux=arr[k];
            arr[k]=arr[i];
            arr[i]=aux;
            k++;
          //}
        }
        j++;
        i++;
      } 
    }
  }  
};

int main(int argc, char **argv){
  int n=atoi(argv[1]);

  int i;
  for(i=0;i<n;i++) arr[i]=n-i;

  for(i=0; i < n;i++) printf("%d ", arr[i]); 
  printf("\n"); 
  PMergeSort *mergeIn = new PMergeSort(0,n-1,n);
  PMergeSort *mergeOut= new PMergeSort();
  
  DC<PMergeSort> *dcMerge = new DC<PMergeSort>(mergeIn,mergeOut);
  dcMerge->start();
  dcMerge->join();

  for(i=0; i < n;i++) printf("%d ", arr[i]);
    printf("\n");
  return 0;
}