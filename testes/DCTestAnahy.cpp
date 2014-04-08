#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "compute_time.c"

#include "AnahyVM.h"
#include "AnahyJob.h"


int quantos=0;
int *a;

typedef struct node {
  int i;
  int j;
 
}NODE;

void mergesortSeq( int inicio, int fim);
void merge( int i, int j);
void * mergesortMain(void *a);
void * mergesortPara(void *a);

void merge( int i, int j)
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

void * mergesort(void *a)
{
   NODE *p = (NODE *)a;
   if (p->i >= p->j) return NULL;
   quantos++;
   NODE n1, n2;
  
   int mid = (p->i+p->j)/2;
   AnahyJob job1, job2;
  
    n1.i = p->i;
    n1.j = mid;
    
    n2.i = mid+1;
    n2.j = p->j;
   
    //mergesort(n3);
    job1.init(mergesort, &n1,NULL);
    AnahyVM::fork(&job1);
    mergesort(&n2);
    AnahyVM::join(&job1, NULL);
   // mergesort(n3);
    merge(p->i, p->j);
   return NULL;
         
}
/*
void * mergesortPara(void *a)
{
  NODE *p = (NODE *)a;

  if (p->i < p->j){ //return NULL;
    quantos++;
    NODE n1, n2;
    int mid = (p->i+p->j)/2;
    AnahyJob job1, job2;
   // NODE *n3 = new NODE;
    n1.i = p->i;
    n1.j = mid;
      
    n2.i = mid+1;
    n2.j = p->j;
      
   //     n3->i= mid+1;
   //     n3->j= p->j;
      
    job1.init(mergesortPara, &n1,NULL);
    AnahyVM::fork(&job1);
    AnahyVM::join(&job1, NULL);
    mergesortPara(&n2);
    merge(p->i, p->j);
   }
}

void mergesortSeq(int *a, int inicio, int fim)
{
  if(inicio < fim){
    int meio = (inicio+fim)/2;
    mergesortSeq(a,inicio,meio);
    mergesortSeq(a,meio+1,fim);
    merge(inicio, fim);
  }  
}
*/

int main(int argc, char **argv){
  AnahyVM::init(argc, argv);
  int n=atoi(argv[1]);
  int i;
  a = new int[n];
  for(i=0;i<n;i++) a[i]=n-i;

  NODE m;
  m.i = 0;
  m.j = n-1;
  
  AnahyJob job;
   
  job.init(mergesort, &m, NULL);
  time_log_start();
  AnahyVM::fork(&job);
  AnahyVM::join(&job, NULL);
  time_log_stop();

  //for (i = 0; i < n; i++) printf ("%d ", a[i]);
  //printf ("\n");

  AnahyVM::terminate();
  printf("; %d ; %d ; %d \n",a[0], a[n-1],quantos);

  //delete a;
  return 0;
}
