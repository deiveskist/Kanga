#include <stdio.h>
#include "compute_time.c"

int *arr;

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

    int i,m,k,l,*temp;
    temp = new int[high-low+1];
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

int main(int argc, char **argv){

  int n=atoi(argv[1]);
  arr = new int[n];
  
  int i;
  for(i=0;i<n;i++) arr[i]=n-i;
  
  time_log_start();  
  partition(0,n-1); 
  time_log_stop();
  
  printf("%d \n",arr[n-1]);
  delete arr;
  return 0;
}

