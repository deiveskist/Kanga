#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "compute_time.c"
#include "AnahyVM.h"
#include "AnahyJob.h"

typedef struct node {
 int i;
 int j;
 int *arr;

} NODE;

void merge(int *a, int i, int j)
{
        int mid = (i+j)/2;
        int ai = i;
        int bi = mid+1;

        int newa[j-i+1], newai = 0;

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

}

void * mergesort(void *a)
{
  NODE *p = (NODE *)a;
  if(p->i < p->j){

  NODE n1, n2;
  int mid = (p->i+p->j)/2;
  AnahyJob job;

   n1.i = p->i;
   n1.j = mid;
   n1.arr= p->arr;

   n2.i = mid+1;
   n2.j = p->j;
   n2.arr= p->arr;

   job.init(mergesort, &n1,NULL);
   AnahyVM::fork(&job);
   mergesort(&n2);      
   AnahyVM::join(&job, NULL);
   merge(p->arr, p->i, p->j);
  }
  return NULL;
}

void mergesortSeq(int *a,int inicio, int fim)
{
  if (inicio < fim){
    int meio = (inicio+fim)/2;
    mergesortSeq(a,inicio,meio);
    mergesortSeq(a,meio+1,fim);
    merge(a,inicio, fim);
  }  
}


int main(int argc, char **argv){
   AnahyVM::init(argc, argv);
  int n=atoi(argv[1]);
  int a[n];
  int i;

  for(i=0;i<n;i++) a[i]=n-i;
  int meio=(0+(n-1))/2;
  NODE m;
  m.i = 0;
  m.j = meio;
  m.arr=a;
  AnahyJob job;
  int ret; 

  job.init(mergesort, &m,NULL);
   time_log_start();

  AnahyVM::fork(&job);
   mergesortSeq(a,meio+1,n-1);

  AnahyVM::join(&job, NULL);

  merge(a,0,n-1);
  time_log_stop();

  printf("; %d ; %d \n",a[0],a[n-1]);
 
  AnahyVM::terminate();
  return 0;
}
