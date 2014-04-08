#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "compute_time.c"
int quantos=0;
int *a;

typedef struct node {
  int i;
  int j;
}NODE;

void merge(int i, int j)
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
        if (p->i < p->j){ // return NULL;
        quantos++;
        NODE n1, n2;
        int mid = (p->i+p->j)/2;
        pthread_t tid1, tid2;
        int ret;

        n1.i = p->i;
        n1.j = mid;

        n2.i = mid+1;
        n2.j = p->j;
        
        mergesort(&n2);

        pthread_create(&tid1, NULL, mergesort, &n1);

        pthread_join(tid1, NULL);
            
        merge(p->i, p->j);
        }
   
}


int main(int argc, char **argv){
  quantos=0;
  int n=atoi(argv[1]);
  a = new int[n];
  int i;

  for(i=0;i<n;i++) a[i]=n-i;

  NODE m;
  m.i = 0;
  m.j = n-1;
  pthread_t tid;
 
  time_log_start(); 
  pthread_create(&tid, NULL, mergesort, &m);
  
  pthread_join(tid, NULL);
  time_log_stop();
  
  printf("; %d ; %d ; %d \n",a[0], a[n-1],quantos);
  //delete a;
 
  return 0;
}
